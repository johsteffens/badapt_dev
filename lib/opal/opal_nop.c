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

#include "opal_nop.h"
#include "opal_net.h"

/**********************************************************************************************************************/
// opal_nop

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_solve__( const opal_nop* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( result );
    opal_holor_s** r = &result->h;
    opal_holor_s_detach( r );
    sz_t arity = opal_nop_a_arity( o );
    bl_t can_settle = ( arity > 0 );
    bl_t vacant = ( arity == 0 );
    tp_t r_type = TYPEOF_f2_t;
    bl_t r_htp  = false;
    bl_t active = false;

    bhvm_shape_s* base_shape = BLM_CREATE( bhvm_shape_s );

    for( sz_t i = 0; i < arity; i++ )
    {
        if( !a[i] ) BLM_RETURNV( bl_t, false );
        if( a[i]->h.v.type == TYPEOF_f3_t ) r_type = TYPEOF_f3_t;
        if( i == 0 )
        {
            bhvm_shape_s_copy( base_shape, &a[i]->h.s );
        }
        else
        {
            if( opal_nop_a_eci( o ) )
            {
                if( a[i]->h.s.size > base_shape->size )
                {
                    if( !bhvm_shape_s_is_sub( &a[i]->h.s, base_shape ) ) BLM_RETURNV( bl_t, false );
                    bhvm_shape_s_copy( base_shape, &a[i]->h.s );
                }
                else
                {
                    if( !bhvm_shape_s_is_sub( base_shape, &a[i]->h.s ) ) BLM_RETURNV( bl_t, false );
                }
            }
            else
            {
                if( !bhvm_shape_s_is_equal( base_shape, &a[i]->h.s ) ) BLM_RETURNV( bl_t, false );
            }
            //if( ( a[0]->m.htp != a[i]->m.htp ) ) BLM_RETURNV( bl_t, false );
            if( ( a[0]->m.htp != a[i]->m.htp ) && a[0]->h.s.size > 0 && a[i]->h.s.size > 0 ) BLM_RETURNV( bl_t, false );
        }

        r_htp = a[ i ]->m.htp;
        active = active || a[i]->m.active;
        vacant = vacant || ( a[i]->h.v.size == 0 );
    }

    can_settle = !active;

    opal_holor_s_attach( r, opal_holor_s_create() );
    bhvm_holor_s* hr = &(*r)->h;
    (*r)->m.htp = r_htp;
    (*r)->m.active = active;

    if( arity > 0 ) bhvm_shape_s_copy( &hr->s, base_shape );

    bhvm_holor_s_set_type( hr, r_type );

    if( !vacant )
    {
        bhvm_holor_s_fit_size( hr );

        // We setup a mini frame and run vop_ap on it.
        bhvm_mcode_hbase_s* hbase = BLM_CREATEC( bhvm_mcode_hbase_s, set_size, arity + 1 );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATEC( bhvm_vop_arr_ci_s,  set_size, arity + 1 );

        for( sz_t i = 0; i <= arity; i++ )
        {
            hbase->holor_adl.data[ i ] = bcore_fork( ( i < arity ) ? &a[ i ]->h : hr );
            arr_ci->data[ i ].i = i;
            arr_ci->data[ i ].c = ( i < arity ) ? 'a' + i : 'y';
        }

        result->type_vop_ap = opal_nop_defines_type_vop_ap( o ) ? opal_nop_a_type_vop_ap( o ) : 0;
        assert( result->type_vop_ap );

        bhvm_vop_a_run( bhvm_vop_a_set_args( BLM_A_PUSH( bhvm_vop_t_create( result->type_vop_ap ) ), arr_ci ), hbase->holor_adl.data );
    }

    result->can_settle = can_settle;
    BLM_RETURNV( bl_t, true );
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 *  Function 'solve' executes operator->solve to compute a holor.
 *  If a holor can be computed (vacant or determined), the solve-route is considered finished
 *  and will not be processed again. A detached result (o->h == NULL) causes a route to be reentered.
 *  If operator->solve settles, all uplinks are removed and the operator is switched to a final arity0
 *  version via opal_op_a_settle.
 *  After settling, the graph can be run through an optimizer minimizing its structure.
 */
void opal_nop_solve_node__( opal_nop* o, opal_net_node_s* node, opal_net_node_adl_s* deferred )
{
    if( node->flag ) return; // cyclic link

    node->flag = true;

    if( node->result ) return;

    sz_t arity = opal_nop_a_arity( o );
    if( arity != node->upls.size )
    {
        opal_net_node_s_err_fa( node, "Operator arity #<sz_t> differs from node arity #<sz_t>", arity, node->upls.size );
    }

    #define opal_MAX_ARITY 4 /* increase this number when assertion below fails */
    ASSERT( arity <= opal_MAX_ARITY );
    opal_holor_s* arg_h[ opal_MAX_ARITY ] = { NULL };

    for( sz_t i = 0; i < arity; i++ )
    {
        opal_net_node_s* arg_n = node->upls.data[ i ]->node;
        if( arg_n )
        {
            if( !arg_n->result ) opal_net_node_s_solve( arg_n, deferred );
            ASSERT( arg_n->result );
            arg_h[ i ] = arg_n->result->h;
            ASSERT( arg_h[ i ] );
        }
    }

    opal_net_node_s_nop_solve( node, arg_h );

    if( node->result->can_settle )
    {
        opal_nop_a_settle( o, node->context, node->result, &node->nop, &node->result );
        opal_net_links_s_clear( &node->upls );
        if( !node->result->reducible )
        {
            if( node->result->h ) bhvm_value_s_clear( &node->result->h->h.v );
        }
    }

    node->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_param_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar1_param_s_solve( const opal_nop_ar1_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, opal_holor_s_clone( a[0] ) );
    result->can_settle    = !a[0]->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_nop_ar1_param_s_settle( const opal_nop_ar1_param_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result )
{
    opal_nop_ar0_param_s* nop_param = opal_nop_ar0_param_s_create();
    nop_param->h = opal_holor_s_clone( result->h );
    opal_nop_a_attach( out_nop, ( opal_nop* )nop_param );
    opal_nop_solve_result_s* r = opal_nop_solve_result_s_create();
    r->h = bcore_fork( nop_param->h );
    opal_nop_solve_result_s_attach( out_result, r );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_adaptive_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar1_adaptive_s_solve( const opal_nop_ar1_adaptive_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        if( a[0]->m.active )
        {
            st_s_attach( &result->msg, st_s_create() );
            st_s_push_fa
            (
                result->msg,
                "\nAdaptive initialization evaluates to an active expression."
                "\nConsider using 'constof' to turn the active expression into a constant."
            );
            return false;
        }
        opal_holor_s_attach( &result->h, opal_holor_s_clone( a[0] ) );
        result->h->m.active = true;
        result->can_settle = true;
    }

    result->reducible = false; // keep subsequent graph intact
    result->codable = false;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_nop_ar1_adaptive_s_settle( const opal_nop_ar1_adaptive_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result )
{
    opal_nop_ar0_adaptive_s* adaptive = opal_nop_ar0_adaptive_s_create();
    adaptive->h = opal_holor_s_clone( result->h );
    adaptive->h->m.name = o->name;
    opal_nop_solve_result_s* r = opal_nop_solve_result_s_create();
    r->h = bcore_fork( adaptive->h );
    opal_nop_solve_result_s_attach( out_result, r );
    opal_nop_a_attach( out_nop, (opal_nop*)adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_output_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar1_output_s_solve( const opal_nop_ar1_output_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, opal_holor_s_create() );
    bhvm_holor_s_fork_from( &result->h->h, &a[0]->h );
    result->h->m.htp = a[0]->m.htp;
    result->h->m.active = a[0]->m.active;
    result->can_settle = (result->h) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar1_output_s_mcode_push_dp_holor( const opal_nop_ar1_output_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();

    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );

    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );

    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_rand_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar1_rand_s_solve( const opal_nop_ar1_rand_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, ( a[0] ) ? opal_holor_s_clone( a[0] ) : NULL );
    if( result->h )
    {
        bcore_prsg* prsg = opal_context_a_get_prsg( context );
        if( !result->h->h.v.size ) bhvm_holor_s_fit_size( &result->h->h );

        f3_t min     = -0.5;
        f3_t max     =  0.5;
        f3_t density =  1.0;

        opal_nop_ar0_rand_s* nop_rand = opal_nop_ar0_rand_s_create();
        nop_rand->prsg = bcore_prsg_a_clone( prsg );
        nop_rand->min = min;
        nop_rand->max = max;
        nop_rand->density = density;

        bhvm_value_s_set_random( &result->h->h.v, density, min, max, prsg );
        nop_rand->h = opal_holor_s_clone( result->h );

        result->h->m.active = true;
        result->can_settle  = true;
        result->codable     = false;

        bcore_inst_a_attach( (bcore_inst**)&result->attached, (bcore_inst*)nop_rand );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_nop_ar1_rand_s_settle( const opal_nop_ar1_rand_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result )
{
    ASSERT( result->attached );
    ASSERT( *( aware_t* )result->attached == TYPEOF_opal_nop_ar0_rand_s );
    opal_nop_ar0_rand_s* nop_rand = ( opal_nop_ar0_rand_s* )result->attached;
    opal_nop_a_attach( out_nop, bcore_fork( nop_rand ) );
    opal_nop_solve_result_s* r = opal_nop_solve_result_s_create();
    r->h = bcore_fork( nop_rand->h );
    opal_nop_solve_result_s_attach( out_result, r );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_cast_htp_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar1_cast_htp_s_solve( const opal_nop_ar1_cast_htp_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_create() );
        bhvm_holor_s_fork_from( &result->h->h, &a[0]->h );
        opal_holor_meta_s_copy( &result->h->m, &a[0]->m );
        result->h->m.htp = !a[0]->m.htp;
    }
    result->can_settle = result->h && !result->h->m.active;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar1_cast_htp_s_mcode_push_ap_holor
(
    const opal_nop_ar1_cast_htp_s* o,
    const opal_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    BLM_INIT();
    bhvm_holor_s* h = &result->h->h;
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'y', idx );

    bhvm_vop_ar1_fork_s* fork = bhvm_vop_ar1_fork_s_create();
    fork->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'a' );
    fork->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'y' );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup, ( bhvm_vop* )fork );

    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap_shelve, ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create(), arr_ci_l );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar1_cast_htp_s_mcode_push_dp_holor
(
    const opal_nop_ar1_cast_htp_s* o,
    const opal_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    BLM_INIT();

    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'z', idx );

    bhvm_vop_ar1_fork_s* fork = bhvm_vop_ar1_fork_s_create();
    fork->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'f' );
    fork->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    ASSERT( fork->i.v[ 0 ] >= 0 );
    ASSERT( fork->i.v[ 1 ] >= 0 );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_setup, ( bhvm_vop* )fork );

    bhvm_vop_ar0_vacate_s* vacate = bhvm_vop_ar0_vacate_s_create();
    vacate->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    ASSERT( vacate->i.v[ 0 ] >= 0 );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_shelve, ( bhvm_vop* )vacate );

    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar1_reshape_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar1_reshape_s_solve( const opal_nop_ar1_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_create() );

        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hy = &result->h->h;
        if( bhvm_shape_s_get_volume( &o->shape ) !=  bhvm_shape_s_get_volume( &ha->s ) )
        {
            st_s_attach( &result->msg, st_s_create() );
            st_s_push_fa( result->msg, "Reshaping from volume #<sz_t> to volume #<sz_t>.", bhvm_shape_s_get_volume( &ha->s ), bhvm_shape_s_get_volume( &o->shape ) );
            return false;
        }

        bhvm_shape_s_copy( &hy->s, &o->shape );
        bhvm_value_s_fork_from( &hy->v, &ha->v );

        opal_holor_meta_s_copy( &result->h->m, &a[0]->m );
        result->h->m.htp = false; // htp flag is being reset
    }
    result->can_settle = result->h && !result->h->m.active;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/** Solves node by changing nop: ar2_reshape -> ar1_reshape.
 *  Shape is extracted from the uplink channel 0.
 *  Channel 0 is then replaced by channel 1.
 */
void opal_nop_ar2_reshape_s_solve_node( opal_nop_ar2_reshape_s* o, opal_net_node_s* node, opal_net_node_adl_s* deferred )
{
    if( node->flag ) return; // cyclic link

    node->flag = true;

    if( node->result ) return;

    ASSERT( node->upls.size == 2 );
    opal_net_node_s* arg0 = node->upls.data[ 0 ]->node;
    opal_net_node_s* arg1 = node->upls.data[ 1 ]->node;

    if( arg0 && arg1 )
    {
        if( !arg0->result ) opal_net_node_s_solve( arg0, deferred );
        if( !arg1->result ) opal_net_node_s_solve( arg1, deferred );

        ASSERT( arg0->result && arg0->result->h );
        ASSERT( arg1->result && arg1->result->h );

        opal_nop_ar1_reshape_s* ar1_reshape = opal_nop_ar1_reshape_s_create();
        bhvm_shape_s_copy( &ar1_reshape->shape, &arg0->result->h->h.s );

        opal_net_links_s_clear( &node->upls );
        opal_net_links_s_push_d( &node->upls, opal_net_link_s_create() );
        node->upls.data[ 0 ]->node = arg1;

        opal_nop_a_attach( &node->nop, ( opal_nop* )ar1_reshape );
        opal_net_node_s_nop_solve( node, &arg1->result->h );

        if( node->result->can_settle )
        {
            opal_nop_a_settle( (opal_nop*)o, node->context, node->result, &node->nop, &node->result );
            opal_net_links_s_clear( &node->upls );
        }
    }

    node->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar1_reshape_s_mcode_push_ap_holor
(
    const opal_nop_ar1_reshape_s* o,
    const opal_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    BLM_INIT();
    bhvm_holor_s* h = &result->h->h;
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'y', idx );

    bhvm_vop_ar1_reshape_s* vop_reshape = bhvm_vop_ar1_reshape_s_create();
    vop_reshape->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'a' );
    vop_reshape->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'y' );
    bhvm_shape_s_copy( &vop_reshape->shape, &o->shape );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup, ( bhvm_vop* )vop_reshape );
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap_shelve, ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create(), arr_ci_l );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar1_reshape_s_mcode_push_dp_holor
(
    const opal_nop_ar1_reshape_s* o,
    const opal_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    BLM_INIT();

    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'z', idx );

    bhvm_vop_ar1_reshape_s* vop_reshape = bhvm_vop_ar1_reshape_s_create();
    vop_reshape->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'f' );
    vop_reshape->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    ASSERT( vop_reshape->i.v[ 0 ] >= 0 );
    ASSERT( vop_reshape->i.v[ 1 ] >= 0 );
    bhvm_shape_s_copy( &vop_reshape->shape, &o->shape );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_setup, ( bhvm_vop* )vop_reshape );

    bhvm_vop_ar0_vacate_s* vacate = bhvm_vop_ar0_vacate_s_create();
    vacate->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    ASSERT( vacate->i.v[ 0 ] >= 0 );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_shelve, ( bhvm_vop* )vacate );

    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_mul_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_bmul_s_solve( const opal_nop_ar2_bmul_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( result );
    opal_holor_s** r = &result->h;
    opal_holor_s_attach( r, ( a[0] && a[1] ) ? opal_holor_s_create() : NULL );

    void (*f)( const bhvm_holor_s* a, const bhvm_holor_s* b, bhvm_holor_s* r );
    f = NULL;

    if( *r )
    {
        result->h->m.active = a[0]->m.active || a[1]->m.active;

        opal_holor_s* lha = a[0];
        opal_holor_s* lhb = a[1];
        opal_holor_s* lhr = (*r);
        bhvm_holor_s* ha = &lha->h;
        bhvm_holor_s* hb = &lhb->h;
        bhvm_holor_s* hr = &lhr->h;
        bhvm_holor_s_set_type( hr, ha->v.type == TYPEOF_f2_t && hb->v.type == TYPEOF_f2_t ? TYPEOF_f2_t : TYPEOF_f3_t );

        bl_t a_htp = lha->m.htp;
        bl_t b_htp = lhb->m.htp;
        bl_t r_htp = false;

        if( ha->s.size == 0 )
        {
            if( hb->s.size == 0 )
            {
                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                    f =        bhvm_hop_ar2_eci_mul_s_f;
                bhvm_shape_s_set_data_na( &hr->s, 0 );
                r_htp = false;
            }
            else if( hb->s.size == 1 )
            {
                if( b_htp )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                        f =        bhvm_hop_ar2_eci_mul_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, hb->s.data[ 0 ] );
                    r_htp = true;
                }
                else
                {
                    BLM_RETURNV( bl_t, false );
                }
            }
            else
            {
                BLM_RETURNV( bl_t, false );
            }
        }
        else if( ha->s.size == 1 )
        {
            if( hb->s.size == 0 )
            {
                if( !a_htp )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                        f =        bhvm_hop_ar2_eci_mul_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, ha->s.data[ 0 ] );
                    r_htp = false;
                }
                else
                {
                    BLM_RETURNV( bl_t, false );
                }
            }
            else if( hb->s.size == 1 )
            {
                if( a_htp && !b_htp )  // dot product
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                        f =        bhvm_hop_ar2_eci_mul_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 0 );
                    r_htp = false;
                }
                else if( !a_htp && b_htp )  // outer product
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvm_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vvm_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 0 ], ha->s.data[ 0 ] );
                    r_htp = false;
                }
                else
                {
                    BLM_RETURNV( bl_t, false );
                }
            }
            else if( hb->s.size == 2 )
            {
                if( !a_htp ) BLM_RETURNV( bl_t, false );
                if( b_htp )
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vtv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vtv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, hb->s.data[ 1 ] );
                }
                else
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 1 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vmv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vmv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, hb->s.data[ 0 ] );
                }
                r_htp = true;
            }
            else
            {
                BLM_RETURNV( bl_t, false );
            }
        }
        else if( ha->s.size == 2 )
        {
            if( hb->s.size == 0 )
            {
                BLM_RETURNV( bl_t, false );
            }
            else if( hb->s.size == 1 )
            {
                if( b_htp ) BLM_RETURNV( bl_t, false );
                if( a_htp )
                {
                    if( ha->s.data[ 1 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tvv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_tvv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, ha->s.data[ 0 ] );
                }
                else
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mvv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_mvv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, ha->s.data[ 1 ] );
                }
                r_htp = false;
            }
            else if( hb->s.size == 2 )
            {
                if( a_htp )
                {
                    if( b_htp )
                    {
                        if( ha->s.data[ 1 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_ttm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_ttm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 1 ], ha->s.data[ 0 ] );
                    }
                    else
                    {
                        if( ha->s.data[ 1 ] != hb->s.data[ 1 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tmm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_tmm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 0 ], ha->s.data[ 0 ] );
                    }
                    r_htp = false;
                }
                else
                {
                    if( b_htp )
                    {
                        if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mtm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_mtm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 1 ], ha->s.data[ 1 ] );
                    }
                    else
                    {
                        if( ha->s.data[ 0 ] != hb->s.data[ 1 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mmm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_mmm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 0 ], ha->s.data[ 1 ] );
                    }
                    r_htp = false;
                }
            }
            else
            {
                BLM_RETURNV( bl_t, false );
            }
        }
        else
        {
            BLM_RETURNV( bl_t, false );
        }

        lhr->m.htp = r_htp;

        if( ( ha->v.size > 0 ) && ( hb->v.size > 0 ) )
        {
            ASSERT( f );
            bhvm_holor_s_fit_size( hr );
            f( ha, hb, hr );
        }
    }

    result->can_settle = ( result->h && !result->h->m.active );
    BLM_RETURNV( bl_t, true );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_(c)cat_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_cat_s_solve( const opal_nop_ar2_cat_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, ( a[0] && a[1] ) ? opal_holor_s_create() : NULL );
    if( result->h )
    {
        result->h->m.active = a[0]->m.active || a[1]->m.active;
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( !bhvm_holor_s_cat_can( ha, hb ) ) return false;
        bhvm_holor_s_cat_set( ha, hb, hr );
    }
    result->can_settle = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_ccat_s_solve( const opal_nop_ar2_ccat_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, ( a[0] && a[1] ) ? opal_holor_s_create() : NULL );
    if( result->h )
    {
        result->h->m.active = a[0]->m.active || a[1]->m.active;
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( !bhvm_holor_s_ccat_can( ha, hb ) ) return false;
        bhvm_holor_s_ccat_set( ha, hb, hr );
    }
    result->can_settle = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_order_inc_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_order_inc_s_solve( const opal_nop_ar2_order_inc_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, ( a[0] && a[1] ) ? opal_holor_s_create() : NULL );
    if( result->h )
    {
        opal_holor_meta_s_copy( &result->h->m, &a[1]->m );

        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( ha->v.size != 1 ) return false;
        sz_t dim = bhvm_holor_s_f3_get_scalar( ha );
        if( dim <= 0 ) return false;
        bhvm_holor_s_order_inc_set( hb, dim, hr );

        bhvm_vop_ar1_order_inc_s* order_inc = bhvm_vop_ar1_order_inc_s_create();
        order_inc->dim = dim;
        bhvm_vop_arr_s* vop_arr = bhvm_vop_arr_s_create();
        bhvm_vop_arr_s_push_d( vop_arr, ( bhvm_vop* )order_inc );
        bcore_inst_a_attach( (bcore_inst**)&result->attached, (bcore_inst*)vop_arr );
    }
    result->can_settle = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_nop_ar2_order_inc_s_mcode_push_ap_track( const opal_nop_ar2_order_inc_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    bhvm_vop* vop = bhvm_vop_a_clone( ( ( bhvm_vop_arr_s* )result->attached )->data[ 0 ] );
    bhvm_vop_a_set_index( vop, 0, bhvm_vop_arr_ci_s_i_of_c( arr_ci, 'b' ) );  // default signature 'ay' would be incorrect in this case
    bhvm_vop_a_set_index( vop, 1, bhvm_vop_arr_ci_s_i_of_c( arr_ci, 'y' ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap, vop );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_order_dec_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_order_dec_s_solve( const opal_nop_ar2_order_dec_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_detach( &result->h );
    if( a[0] && a[0]->m.htp ) return false;
    opal_holor_s_attach( &result->h, ( a[0] && a[1] ) ? opal_holor_s_create() : NULL );
    if( result->h )
    {
        opal_holor_meta_s_copy( &result->h->m, &a[0]->m );

        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( hb->v.size != 1 )
        {
            st_s_attach( &result->msg, st_s_create() );
            st_s_push_fa( result->msg, "Index must be a scalar." );
            return false;
        }

        sz_t index = bhvm_holor_s_f3_get_scalar( hb );
        if( ha->s.size == 0 ) return false;

        if( index < 0 || index >= ha->s.data[ ha->s.size - 1 ] )
        {
            st_s_attach( &result->msg, st_s_create() );
            st_s_push_fa( result->msg, "Index value #<sz_t> is out of range (0 ... #<sz_t>).", index, ha->s.data[ ha->s.size - 1 ] - 1 );
            return false;
        }

        bhvm_holor_s_order_dec_weak( ha, index, hr );
        bhvm_vop_ar1_order_dec_weak_s* order_dec_weak = bhvm_vop_ar1_order_dec_weak_s_create();
        order_dec_weak->idx = index;
        bhvm_vop_arr_s* vop_arr = bhvm_vop_arr_s_create();
        bhvm_vop_arr_s_push_d( vop_arr, ( bhvm_vop* )order_dec_weak );
        bcore_inst_a_attach( (bcore_inst**)&result->attached, (bcore_inst*)vop_arr );
    }
    result->can_settle = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar2_order_dec_s_mcode_push_ap_holor( const opal_nop_ar2_order_dec_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    bhvm_holor_s* h = &result->h->h;
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'y', idx );

    bhvm_vop_ar1_order_dec_weak_s* weak = bhvm_vop_ar1_order_dec_weak_s_clone( ( bhvm_vop_ar1_order_dec_weak_s* )( ( bhvm_vop_arr_s* )result->attached )->data[ 0 ] );
    weak->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'a' );
    weak->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'y' );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup, ( bhvm_vop* )weak );

    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap_shelve, ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create(), arr_ci_l );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t opal_nop_ar2_order_dec_s_mcode_push_dp_holor( const opal_nop_ar2_order_dec_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );

    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'z', idx );

    bhvm_vop_ar1_order_dec_weak_s* weak = bhvm_vop_ar1_order_dec_weak_s_clone( ( bhvm_vop_ar1_order_dec_weak_s* )( ( bhvm_vop_arr_s* )result->attached )->data[ 0 ] );
    weak->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'f' );
    weak->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_setup, ( bhvm_vop* )weak );

    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_cyclic_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_cyclic_s_solve( const opal_nop_ar2_cyclic_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_create() );
        result->can_settle  = false; // cyclic results never settle
        result->h->m.active = true;  // cyclic results are always active
        result->h->m.name   = o->name;

        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hr = &result->h->h;
        bhvm_shape_s_copy( &hr->s, &ha->s );
        bhvm_value_s_set_type( &hr->v, ha->v.type );

        if( a[0]->m.active )
        {
            st_s_attach( &result->msg, st_s_create() );
            st_s_push_fa
            (
                result->msg,
                "\nCyclic initialization evaluates to an active expression."
                "\nConsider using 'constof' to turn the active expression into a constant."
            );
            return false;
        }

        if( a[1] )
        {
            bhvm_holor_s* hb = &a[1]->h;
            if( !bhvm_shape_s_is_equal( &ha->s, &hb->s ) ) return false;
        }
    }
    else
    {
        if( a[1] ) return false;
        opal_holor_s_attach( &result->h, NULL );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_nop_ar2_cyclic_s_solve_node( opal_nop_ar2_cyclic_s* o, opal_net_node_s* node, opal_net_node_adl_s* deferred )
{
    if( node->flag ) return; // cyclic link

    node->flag = true;

    ASSERT( node->upls.size == 2 );

    opal_holor_s* arg_h[ 2 ] = { NULL };
    opal_net_node_s* arg_n = NULL;

    arg_n = node->upls.data[ 0 ]->node;
    opal_net_node_s_solve( arg_n, NULL );
    arg_h[ 0 ] = arg_n->result->h;
    opal_net_node_s_nop_solve( node, arg_h );

    if( deferred )
    {
        opal_net_node_adl_s_push_d( deferred, bcore_fork( node ) );
    }
    else
    {
        arg_n = node->upls.data[ 1 ]->node;
        opal_net_node_s_solve( arg_n, NULL );
        arg_h[ 1 ] = arg_n->result->h;
        opal_net_node_s_nop_solve( node, arg_h );
    }

    node->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// opal_nop_ar2_rands_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_nop_ar2_rands_s_solve( const opal_nop_ar2_rands_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( context );
    opal_holor_s_attach( &result->h, ( a[0] && a[1] ) ? opal_holor_s_clone( a[1] ) : NULL );
    if( result->h )
    {
        if( !result->h->h.v.size ) bhvm_holor_s_fit_size( &result->h->h );

        bhvm_holor_s* ha = &a[0]->h;
        if( ha->v.size == 0 )
        {
            st_s_attach( &result->msg, st_s_create() );
            st_s_push_fa( result->msg, "Seed must be determined." );
            return false;
        }

        f3_t vseed = bhvm_value_s_get_f3( &ha->v, 0 );

        f3_t min     = -0.5;
        f3_t max     =  0.5;
        f3_t density =  1.0;
        u3_t rseed   =  ( ( tanh( vseed ) + 1.0 ) * 0.5 ) * 0xFFFFFFFFFFFFFFFFull;

        bcore_prsg* prsg = BLM_A_PUSH( bcore_prsg_a_clone( opal_context_a_get_prsg( context ) ) );
        bcore_prsg_a_reseed( prsg, rseed );

        bhvm_value_s_set_random( &result->h->h.v, density, min, max, prsg );
        result->h->m.active = true;
        result->can_settle  = true;
        result->codable     = false;

        opal_nop_ar0_rand_s* nop_rand = opal_nop_ar0_rand_s_create();
        nop_rand->h = opal_holor_s_clone( result->h );

        bcore_prsg_a_reseed( prsg, rseed );
        nop_rand->prsg = bcore_prsg_a_clone( prsg );
        nop_rand->min = min;
        nop_rand->max = max;
        nop_rand->density = density;

        bcore_inst_a_attach( (bcore_inst**)&result->attached, (bcore_inst*)nop_rand );
    }
    BLM_RETURNV( bl_t, true );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_nop_ar2_rands_s_settle( const opal_nop_ar2_rands_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result )
{
    ASSERT( result->attached );
    ASSERT( *( aware_t* )result->attached == TYPEOF_opal_nop_ar0_rand_s );
    opal_nop_ar0_rand_s* nop_rand = ( opal_nop_ar0_rand_s* )result->attached;
    opal_nop_a_attach( out_nop, bcore_fork( nop_rand ) );
    opal_nop_solve_result_s* r = opal_nop_solve_result_s_create();
    r->h = bcore_fork( nop_rand->h );
    opal_nop_solve_result_s_attach( out_result, r );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


