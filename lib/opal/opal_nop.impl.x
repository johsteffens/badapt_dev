/** Author and Copyright 2019 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

func (bl_t solve_default( const, opal_context* context, opal_holor_s** a, :solve_result_s* result )) =
{
    ASSERT( result );
    opal_holor_s.2 r = result.h;
    r.1 =< NULL;
    sz_t arity = o.arity();
    bl_t can_settle = ( arity > 0 );
    bl_t vacant = ( arity == 0 );
    tp_t r_type = TYPEOF_f2_t;
    bl_t r_htp  = false;
    bl_t active = false;

    bhvm_shape_s* base_shape = bhvm_shape_s!^^;

    for( sz_t i = 0; i < arity; i++ )
    {
        if( !a[i] ) return false;
        if( a[i].h.v.type == TYPEOF_f3_t ) r_type = TYPEOF_f3_t;
        if( i == 0 )
        {
            base_shape.copy( a[i].h.s );
        }
        else
        {
            if( o.eci() )
            {
                if( a[i].h.s.size > base_shape.size )
                {
                    if( !a[i].h.s.is_sub( base_shape ) ) return false;
                    base_shape.copy( a[i].h.s );
                }
                else
                {
                    if( !base_shape.is_sub( a[i].h.s ) ) return false;
                }
            }
            else
            {
                if( base_shape.is_equal( a[i].h.s ) ) return false;
            }
            if( ( a[0].m.htp != a[i].m.htp ) && a[0].h.s.size > 0 && a[i].h.s.size > 0 ) return false;
        }

        r_htp = a[ i ].m.htp;
        active = active || a[i].m.active;
        vacant = vacant || ( a[i].h.v.size == 0 );
    }

    can_settle = !active;

    r.1 =< opal_holor_s!;

    bhvm_holor_s* hr = r.1.h;
    r.1.m.htp = r_htp;
    r.1.m.active = active;

    if( arity > 0 ) hr.s.copy( base_shape );

    hr.set_type( r_type );

    if( !vacant )
    {
         hr.fit_size();

        // We setup a mini frame and run vop_ap on it.
        bhvm_mcode_hbase_s* hbase = bhvm_mcode_hbase_s!^^.set_size( arity + 1 );
        bhvm_vop_arr_ci_s* arr_ci = bhvm_vop_arr_ci_s!^^.set_size( arity + 1 );

        for( sz_t i = 0; i <= arity; i++ )
        {
            hbase.holor_adl.[ i ] = bcore_fork( ( i < arity ) ? a[ i ].h.1 : hr );
            arr_ci.[ i ].i = i;
            arr_ci.[ i ].c = ( i < arity ) ? 'a' + i : 'y';
        }

        result.type_vop_ap = o.defines_type_vop_ap() ? o.type_vop_ap() : 0;
        assert( result.type_vop_ap );

        bhvm_vop_a_run( bhvm_vop_t_create( result.type_vop_ap ).scope().set_args( arr_ci ), hbase.holor_adl.data );
    }

    result.can_settle = can_settle;
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 *  Function 'solve' executes operator.solve to compute a holor.
 *  If a holor can be computed (vacant or determined), the solve-route is considered finished
 *  and will not be processed again. A detached result (o.h == NULL) causes a route to be reentered.
 *  If operator.solve settles, all uplinks are removed and the operator is switched to a final arity0
 *  version via opal_op_a_settle.
 *  After settling, the graph can be run through an optimizer minimizing its structure.
 */
func (void solve_node_default( mutable, opal_net_node_s* node, opal_net_node_adl_s* deferred )) =
{
    if( node.flag ) return; // cyclic link

    node.flag = true;

    if( node.result ) return;

    sz_t arity = o.arity();
    if( arity != node.upls.size )
    {
        node.err_fa( "Operator arity #<sz_t> differs from node arity #<sz_t>", arity, node.upls.size );
    }

    #define opal_MAX_ARITY 4 /* increase this number when assertion below fails */
    ASSERT( arity <= opal_MAX_ARITY );
    opal_holor_s* arg_h[ opal_MAX_ARITY ] = { NULL };

    for( sz_t i = 0; i < arity; i++ )
    {
        opal_net_node_s* arg_n = node.upls.[ i ].node;
        if( arg_n )
        {
            if( !arg_n.result ) arg_n.solve( deferred );
            ASSERT( arg_n.result );
            arg_h[ i ] = arg_n.result.h;
            ASSERT( arg_h[ i ] );
        }
    }

    node.nop_solve( arg_h );

    if( node.result.can_settle )
    {
        o.settle( node.context, node.result, node.nop, node.result );
        node.upls.clear();
        if( !node.result.reducible )
        {
            if( node.result.h ) node.result.h.h.v.clear();
        }
    }

    node.flag = false;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_param_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_param_s) ::.solve =
{
    result.h =< a[0].clone();
    result.can_settle    = !a[0].m.active;
    result.type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_param_s) ::.settle =
{
    opal_nop_ar0_param_s* nop_param = opal_nop_ar0_param_s!;
    nop_param.h = result.h.clone();
    out_nop.1 =< nop_param;
    opal_nop_solve_result_s* r = opal_nop_solve_result_s!;
    r.h = nop_param.h.fork();
    out_result.1 =< r;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_adaptive_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_adaptive_s) ::.solve =
{
    if( a[0] )
    {
        if( a[0].m.active )
        {
            result.msg =< st_s!;
            result.msg.push_fa
            (
                "\nAdaptive initialization evaluates to an active expression."
                "\nConsider using 'constof' to turn the active expression into a constant."
            );
            return false;
        }
        result.h =< a[0].clone();
        result.h.m.active = true;
        result.can_settle = true;
    }

    result.reducible = false; // keep subsequent graph intact
    result.codable = false;
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func( :ar1_adaptive_s ) ::.settle =
{
    opal_nop_ar0_adaptive_s* adaptive = opal_nop_ar0_adaptive_s!;
    adaptive.h = result.h.clone();
    adaptive.h.m.name = o.name;
    opal_nop_solve_result_s* r = opal_nop_solve_result_s!;
    r.h = adaptive.h.fork();
    out_result.1 =< r;
    out_nop.1 =< adaptive;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_output_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_output_s) ::.solve =
{
    result.h =< opal_holor_s!;
    result.h.h.fork_from( a[0].h );
    result.h.m.htp = a[0].m.htp;
    result.h.m.active = a[0].m.active;
    result.can_settle = (result.h) && !result.h.m.active;
    result.type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_output_s) ::.mcode_push_dp_holor =
{
    bhvm_holor_s* h = bhvm_holor_s!^.copy_shape_type( result.h.h );
    sz_t idx = mcf.push_hm( h, result.h.m );
    mcf.track_vop_push_d( TYPEOF_track_dp_setup,  bhvm_vop_ar0_determine_s!.setup( idx ) );
    mcf.track_vop_push_d( TYPEOF_track_dp_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_rand_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_rand_s) ::.solve =
{
    result.h =< a[0].clone();
    if( result.h )
    {
        bcore_prsg* prsg = context.get_prsg();
        if( !result.h.h.v.size ) result.h.h.fit_size();

        f3_t min     = -0.5;
        f3_t max     =  0.5;
        f3_t density =  1.0;

        opal_nop_ar0_rand_s* nop_rand = opal_nop_ar0_rand_s!;
        nop_rand.prsg = prsg.clone();
        nop_rand.min = min;
        nop_rand.max = max;
        nop_rand.density = density;

        result.h.h.v.set_random( density, min, max, prsg );
        nop_rand.h = result.h.clone();

        result.h.m.active = true;
        result.can_settle = true;
        result.codable    = false;

        result.attached =< nop_rand;
    }
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_rand_s) ::.settle =
{
    ASSERT( result.attached?._ == TYPEOF_opal_nop_ar0_rand_s );
    opal_nop_ar0_rand_s* nop_rand = result.attached.cast( opal_nop_ar0_rand_s* );
    out_nop.1 =< nop_rand.fork();
    opal_nop_solve_result_s* r = opal_nop_solve_result_s!;
    r.h = nop_rand.h.fork();
    out_result.1 =< r;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_cast_htp_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_cast_htp_s) ::.solve =
{
    if( a[0] )
    {
        result.h =< opal_holor_s!;
        result.h.h.fork_from( a[0].h );
        result.h.m.copy( a[0].m );
        result.h.m.htp = !a[0].m.htp;
    }
    result.can_settle = result.h && !result.h.m.active;
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_cast_htp_s) ::.mcode_push_ap_holor =
{
    bhvm_holor_s* h = result.h.h;
    opal_holor_meta_s* m = result.h.m;
    sz_t idx = mcf.push_hm( h, m );
    mcf.track_vop_push_d( TYPEOF_track_ap_setup,  bhvm_vop_ar1_fork_s!.setup( arr_ci.i_of_c( 'a' ), idx ) );
    mcf.track_vop_push_d( TYPEOF_track_ap_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_cast_htp_s) ::.mcode_push_dp_holor =
{
    bhvm_holor_s* h = bhvm_holor_s!^.copy_shape_type( result.h.h );
    opal_holor_meta_s* m = result.h.m;
    sz_t idx = mcf.push_hm( h, m );
    mcf.track_vop_push_d( TYPEOF_track_dp_setup, bhvm_vop_ar1_fork_s!.setup( arr_ci.i_of_c( 'f' ), idx ) );
    mcf.track_vop_push_d( TYPEOF_track_dp_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_reshape_s, opal_nop_ar2_reshape_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_reshape_s) ::.solve =
{
    if( a[0] )
    {
        opal_holor_s_attach( &result.h, opal_holor_s_create() );

        bhvm_holor_s* ha = &a[0].h;
        bhvm_holor_s* hy = &result.h.h;
        if( bhvm_shape_s_get_volume( &o.shape ) !=  bhvm_shape_s_get_volume( &ha.s ) )
        {
            st_s_attach( &result.msg, st_s_create() );
            st_s_push_fa( result.msg, "Reshaping from volume #<sz_t> to volume #<sz_t>.", bhvm_shape_s_get_volume( &ha.s ), bhvm_shape_s_get_volume( &o.shape ) );
            return false;
        }

        bhvm_shape_s_copy( &hy.s, &o.shape );
        bhvm_value_s_fork_from( &hy.v, &ha.v );

        opal_holor_meta_s_copy( &result.h.m, &a[0].m );
        result.h.m.htp = false; // htp flag is being reset
    }
    result.can_settle = result.h && !result.h.m.active;
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

/** Solves node by changing nop: ar2_reshape . ar1_reshape.
 *  Shape is extracted from the uplink channel 0.
 *  Channel 0 is then replaced by channel 1.
 */
func (:ar2_reshape_s) ::.solve_node =
{
    if( node.flag ) return; // cyclic link

    node.flag = true;

    if( node.result ) return;

    ASSERT( node.upls.size == 2 );
    opal_net_node_s* arg0 = node.upls.data[ 0 ].node;
    opal_net_node_s* arg1 = node.upls.data[ 1 ].node;

    if( arg0 && arg1 )
    {
        if( !arg0.result ) arg0.solve( deferred );
        if( !arg1.result ) arg1.solve( deferred );

        ASSERT( arg0.result && arg0.result.h );
        ASSERT( arg1.result && arg1.result.h );

        opal_nop_ar1_reshape_s* ar1_reshape = opal_nop_ar1_reshape_s!;
        ar1_reshape.shape.copy( arg0.result.h.h.s );

        node.upls.clear();
        node.upls.push_d( opal_net_link_s! ).node = arg1;

        node.nop =< ar1_reshape;
        node.nop_solve( arg1.result.h );

        if( node.result.can_settle )
        {
            o.settle( node.context, node.result, node.nop, node.result );
            node.upls.clear();
        }
    }

    node.flag = false;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_reshape_s) ::.mcode_push_ap_holor =
{
    bhvm_holor_s* h = result.h.h;
    opal_holor_meta_s* m = result.h.m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, m );
    bhvm_vop_ar1_reshape_s* vop_reshape = bhvm_vop_ar1_reshape_s!.setup( arr_ci.i_of_c( 'a' ), idx );
    vop_reshape.shape.copy( o.shape );
    mcf.track_vop_push_d( TYPEOF_track_ap_setup, vop_reshape );
    mcf.track_vop_push_d( TYPEOF_track_ap_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_reshape_s) ::.mcode_push_dp_holor =
{
    bhvm_holor_s* h = bhvm_holor_s!^.copy_shape_type( result.h.h );
    opal_holor_meta_s* m = result.h.m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, m );
    bhvm_vop_ar1_reshape_s* vop_reshape = bhvm_vop_ar1_reshape_s!.setup( arr_ci.i_of_c( 'f' ), idx );
    vop_reshape.shape.copy( o.shape );
    mcf.track_vop_push_d( TYPEOF_track_dp_setup, vop_reshape );
    mcf.track_vop_push_d( TYPEOF_track_dp_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_mul_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_bmul_s) ::.solve =
{
    ASSERT( result );
    opal_holor_s** r = result.h;
    r.1 =< ( a[0] && a[1] ) ? opal_holor_s! : NULL;

    void (*f)( const bhvm_holor_s* a, const bhvm_holor_s* b, bhvm_holor_s* r );
    f = NULL;

    if( *r )
    {
        result.h.m.active = a[0].m.active || a[1].m.active;

        opal_holor_s* lha = a[0];
        opal_holor_s* lhb = a[1];
        opal_holor_s* lhr = r;
        bhvm_holor_s* ha = lha.h;
        bhvm_holor_s* hb = lhb.h;
        bhvm_holor_s* hr = lhr.h;
        hr.set_type( ha.v.type == TYPEOF_f2_t && hb.v.type == TYPEOF_f2_t ? TYPEOF_f2_t : TYPEOF_f3_t );

        bl_t a_htp = lha.m.htp;
        bl_t b_htp = lhb.m.htp;
        bl_t r_htp = false;

        if( ha.s.size == 0 )
        {
            if( hb.s.size == 0 )
            {
                result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                verbatim_C{ f = bhvm_hop_ar2_eci_mul_s_f };
                hr.s.set_data_na( 0 );
                r_htp = false;
            }
            else if( hb.s.size == 1 )
            {
                if( b_htp )
                {
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_eci_mul_s_f };
                    hr.s.set_data_na( 1, hb.s.[ 0 ] );
                    r_htp = true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if( ha.s.size == 1 )
        {
            if( hb.s.size == 0 )
            {
                if( !a_htp )
                {
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_eci_mul_s_f };
                    hr.s.set_data_na( 1, ha.s.[ 0 ] );
                    r_htp = false;
                }
                else
                {
                    return false;
                }
            }
            else if( hb.s.size == 1 )
            {
                if( a_htp && !b_htp )  // dot product
                {
                    if( ha.s.[ 0 ] != hb.s.[ 0 ] ) return false;
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_eci_mul_s_f };
                    hr.s.set_data_na( 0 );
                    r_htp = false;
                }
                else if( !a_htp && b_htp )  // outer product
                {
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvm_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_mul_vvm_s_f };
                    hr.s.set_data_na( 2, hb.s.[ 0 ], ha.s.[ 0 ] );
                    r_htp = false;
                }
                else
                {
                    return false;
                }
            }
            else if( hb.s.size == 2 )
            {
                if( !a_htp ) return false;
                if( b_htp )
                {
                    if( ha.s.[ 0 ] != hb.s.[ 0 ] ) return false;
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vtv_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_mul_vtv_s_f };
                    hr.s.set_data_na( 1, hb.s.[ 1 ] );
                }
                else
                {
                    if( ha.s.[ 0 ] != hb.s.[ 1 ] ) return false;
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vmv_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_mul_vmv_s_f };
                    hr.s.set_data_na( 1, hb.s.[ 0 ] );
                }
                r_htp = true;
            }
            else
            {
                return false;
            }
        }
        else if( ha.s.size == 2 )
        {
            if( hb.s.size == 0 )
            {
                return false;
            }
            else if( hb.s.size == 1 )
            {
                if( b_htp ) return false;
                if( a_htp )
                {
                    if( ha.s.[ 1 ] != hb.s.[ 0 ] ) return false;
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tvv_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_mul_tvv_s_f };
                    hr.s.set_data_na( 1, ha.s.[ 0 ] );
                }
                else
                {
                    if( ha.s.[ 0 ] != hb.s.[ 0 ] ) return false;
                    result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mvv_s;
                    result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_a_s;
                    result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_b_s;
                    verbatim_C{ f = bhvm_hop_ar2_mul_mvv_s_f };
                    hr.s.set_data_na( 1, ha.s.[ 1 ] );
                }
                r_htp = false;
            }
            else if( hb.s.size == 2 )
            {
                if( a_htp )
                {
                    if( b_htp )
                    {
                        if( ha.s.[ 1 ] != hb.s.[ 0 ] ) return false;
                        result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_ttm_s;
                        result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_a_s;
                        result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_b_s;
                        verbatim_C{ f = bhvm_hop_ar2_mul_ttm_s_f };
                        hr.s.set_data_na( 2, hb.s.[ 1 ], ha.s.[ 0 ] );
                    }
                    else
                    {
                        if( ha.s.[ 1 ] != hb.s.[ 1 ] ) return false;
                        result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tmm_s;
                        result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_a_s;
                        result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_b_s;
                        verbatim_C{ f = bhvm_hop_ar2_mul_tmm_s_f };
                        hr.s.set_data_na( 2, hb.s.[ 0 ], ha.s.[ 0 ] );
                    }
                    r_htp = false;
                }
                else
                {
                    if( b_htp )
                    {
                        if( ha.s.[ 0 ] != hb.s.[ 0 ] ) return false;
                        result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mtm_s;
                        result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_a_s;
                        result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_b_s;
                        verbatim_C{ f = bhvm_hop_ar2_mul_mtm_s_f };
                        hr.s.set_data_na( 2, hb.s.[ 1 ], ha.s.[ 1 ] );
                    }
                    else
                    {
                        if( ha.s.[ 0 ] != hb.s.[ 1 ] ) return false;
                        result.type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mmm_s;
                        result.type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_a_s;
                        result.type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_b_s;
                        verbatim_C{ f = bhvm_hop_ar2_mul_mmm_s_f };
                        hr.s.set_data_na( 2, hb.s.[ 0 ], ha.s.[ 1 ] );
                    }
                    r_htp = false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        lhr.m.htp = r_htp;

        if( ( ha.v.size > 0 ) && ( hb.v.size > 0 ) )
        {
            ASSERT( f );
            hr.fit_size();
            f( ha, hb, hr );
        }
    }

    result.can_settle = ( result.h && !result.h.m.active );
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_(c)cat_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_cat_s) ::.solve =
{
    result.h =< ( a[0] && a[1] ) ? opal_holor_s! : NULL;
    if( result.h )
    {
        result.h.m.active = a[0].m.active || a[1].m.active;
        bhvm_holor_s* ha = a[0].h;
        bhvm_holor_s* hb = a[1].h;
        bhvm_holor_s* hr = result.h.h;
        if( !ha.cat_can( hb ) ) return false;
        ha.cat_set( hb, hr );
    }
    result.can_settle = ( result.h && !result.h.m.active );
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_ccat_s) ::.solve =
{
    result.h =< ( a[0] && a[1] ) ? opal_holor_s! : NULL;
    if( result.h )
    {
        result.h.m.active = a[0].m.active || a[1].m.active;
        bhvm_holor_s* ha = a[0].h;
        bhvm_holor_s* hb = a[1].h;
        bhvm_holor_s* hr = result.h.h;
        if( !ha.ccat_can( hb ) ) return false;
        ha.ccat_set( hb, hr );
    }
    result.can_settle = ( result.h && !result.h.m.active );
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_order_inc_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_order_inc_s) ::.solve =
{
    result.h =< ( a[0] && a[1] ) ? opal_holor_s! : NULL;
    if( result.h )
    {
        result.h.m.copy( a[1].m );

        bhvm_holor_s* ha = a[0].h;
        bhvm_holor_s* hb = a[1].h;
        bhvm_holor_s* hr = result.h.h;
        if( ha.v.size != 1 ) return false;
        sz_t dim = ha.f3_get_scalar();
        if( dim <= 0 ) return false;
        hb.order_inc_set( dim, hr );

        bhvm_vop_ar1_order_inc_s* order_inc = bhvm_vop_ar1_order_inc_s!;
        order_inc.dim = dim;
        result.attached =< order_inc;
    }
    result.can_settle = ( result.h && !result.h.m.active );
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_order_inc_s) ::.mcode_push_ap_track =
{
    bhvm_vop* vop = result.attached.clone();
    vop.set_index( 0, arr_ci.i_of_c( 'b' ) );  // default signature 'ay' would be incorrect in this case
    vop.set_index( 1, arr_ci.i_of_c( 'y' ) );
    mcf.track_vop_push_d( TYPEOF_track_ap, vop );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_order_dec_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_order_dec_s) ::.solve =
{
    result.h =< NULL;
    if( a[0] && a[0].m.htp ) return false;
    result.h =< ( a[0] && a[1] ) ? opal_holor_s! : NULL;

    if( result.h )
    {
        result.h.m.copy( a[0].m );

        bhvm_holor_s* ha = a[0].h;
        bhvm_holor_s* hb = a[1].h;
        bhvm_holor_s* hr = result.h.h;
        if( hb.v.size != 1 )
        {
            result.msg =< st_s!;
            result.msg.push_fa( "Index must be a scalar." );
            return false;
        }

        sz_t index = hb.f3_get_scalar();
        if( ha.s.size == 0 ) return false;

        if( index < 0 || index >= ha.s.data[ ha.s.size - 1 ] )
        {
            result.msg =< st_s!;
            result.msg.push_fa( "Index value #<sz_t> is out of range (0 ... #<sz_t>).", index, ha.s.data[ ha.s.size - 1 ] - 1 );
            return false;
        }

        ha.order_dec_weak( index, hr );
        bhvm_vop_ar1_order_dec_weak_s* order_dec_weak = bhvm_vop_ar1_order_dec_weak_s!;
        order_dec_weak.idx = index;
        result.attached =< order_dec_weak;
    }
    result.can_settle = ( result.h && !result.h.m.active );
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_order_dec_s) ::.mcode_push_ap_holor =
{
    bhvm_holor_s* h = result.h.h;
    opal_holor_meta_s* m = result.h.m;
    sz_t idx = mcf.push_hm( h, m );
    bhvm_vop_ar1_order_dec_weak_s* weak = result.attached.cast( bhvm_vop_ar1_order_dec_weak_s* ).clone();
    mcf.track_vop_push_d( TYPEOF_track_ap_setup, weak.setup( arr_ci.i_of_c( 'a' ), idx ) );
    mcf.track_vop_push_d( TYPEOF_track_ap_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_order_dec_s) ::.mcode_push_dp_holor =
{
    bhvm_holor_s* h = bhvm_holor_s!^.copy_shape_type( result.h.h );
    opal_holor_meta_s* m = result.h.m;
    sz_t idx = mcf.push_hm( h, m );
    bhvm_vop_ar1_order_dec_weak_s* weak = result.attached.cast( bhvm_vop_ar1_order_dec_weak_s* ).clone();
    mcf.track_vop_push_d( TYPEOF_track_dp_setup, weak.setup( arr_ci.i_of_c( 'f' ), idx ) );
    mcf.track_vop_push_d( TYPEOF_track_dp_shelve, bhvm_vop_ar0_vacate_s!.setup( idx ) );
    return idx;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_cyclic_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_cyclic_s) ::.solve =
{
    if( a[0] )
    {
        result.h =< opal_holor_s!;
        result.can_settle = false; // cyclic results never settle
        result.h.m.active = true;  // cyclic results are always active
        result.h.m.name   = o.name;

        bhvm_holor_s* ha = a[0].h;
        bhvm_holor_s* hr = result.h.h;
        hr.s.copy( ha.s );
        hr.v.set_type( ha.v.type );

        if( a[0].m.active )
        {
            result.msg =< st_s!;
            result.msg.push_fa
            (
                "\nCyclic initialization evaluates to an active expression."
                "\nConsider using 'constof' to turn the active expression into a constant."
            );
            return false;
        }

        if( a[1] )
        {
            bhvm_holor_s* hb = a[1].h;
            if( !ha.s.is_equal( hb.s ) ) return false;
        }
    }
    else
    {
        if( a[1] ) return false;
        result.h =< NULL;
    }
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_cyclic_s) ::.solve_node =
{
    if( node.flag ) return; // cyclic link

    node.flag = true;

    ASSERT( node.upls.size == 2 );

    opal_holor_s* arg_h[ 2 ] = { NULL };
    opal_net_node_s* arg_n = NULL;

    arg_n = node.upls.[ 0 ].node;
    arg_n.solve( NULL );
    arg_h[ 0 ] = arg_n.result.h;
    node.nop_solve( arg_h );

    if( deferred )
    {
        deferred.push_d( bcore_fork( node ) );
    }
    else
    {
        arg_n = node.upls.[ 1 ].node;
        arg_n.solve( NULL );
        arg_h[ 1 ] = arg_n.result.h;
        node.nop_solve( arg_h );
    }

    node.flag = false;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_rands_s

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_rands_s) ::.solve =
{
    ASSERT( context );
    result.h =< ( a[0] && a[1] ) ? a[1].clone() : NULL;
    if( result.h )
    {
        if( !result.h.h.v.size ) result.h.h.fit_size();

        bhvm_holor_s* ha = a[0].h;
        if( ha.v.size == 0 )
        {
            result.msg =< st_s!;
            result.msg.push_fa( "Seed must be determined." );
            return false;
        }

        f3_t vseed = ha.v.get_f3( 0 );

        f3_t min     = -0.5;
        f3_t max     =  0.5;
        f3_t density =  1.0;
        u3_t rseed   =  ( ( tanh( vseed ) + 1.0 ) * 0.5 ) * 0xFFFFFFFFFFFFFFFFull;

        bcore_prsg* prsg = opal_context_a_get_prsg( context ).clone().scope();
        prsg.reseed( rseed );

        result.h.h.v.set_random( density, min, max, prsg );
        result.h.m.active = true;
        result.can_settle = true;
        result.codable    = false;

        opal_nop_ar0_rand_s* nop_rand = opal_nop_ar0_rand_s!;
        nop_rand.h = result.h.clone();

        prsg.reseed( rseed );
        nop_rand.prsg = prsg.clone();
        nop_rand.min = min;
        nop_rand.max = max;
        nop_rand.density = density;
        result.attached =< nop_rand;
    }
    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_rands_s) ::.settle =
{
    ASSERT( result.attached?._ == TYPEOF_opal_nop_ar0_rand_s );
    opal_nop_ar0_rand_s* nop_rand = result.attached.cast( opal_nop_ar0_rand_s* );
    out_nop.1 =< nop_rand.fork();
    opal_nop_solve_result_s* r = opal_nop_solve_result_s!;
    r.h = nop_rand.h.fork();
    out_result.1 =< r;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

