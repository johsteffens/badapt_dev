/** Author and Copyright 2020 Johannes Bernhard Steffens
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

func (:generator_s) (void randomize_holor( const, opal_holor_s* h, bcore_prsg* prsg )) =
{
    if( o.set_htp ) h.m.htp = ( prsg.gen_f3( 0, 1 ) > 0.5 );

    if( o.set_shape )
    {
        ASSERT( o.set_dim );
        sz_t size = prsg.gen_f3( 0, 1 ) * o.max_shape_size * 23 /* some prime */;
        size = size % ( o.max_shape_size + 1 );
        h.h.s.set_size( size );
    }

    if( o.set_dim )
    {
        ASSERT( o.set_value );
        ASSERT( o.max_dim > 0 );
        foreach( sz_t* e in h.h.s )
        {
            sz_t size = prsg.gen_f3( 0, 1 ) * o.max_dim * 23;
            e.0 = ( size % ( o.max_dim ) ) + 1;
        }
    }

    if( o.set_v_type )
    {
        tp_t type = ( prsg.gen_f3( 0, 1 ) > 0.5 ) ? TYPEOF_f2_t : TYPEOF_f3_t;
        h.h.v.set_type( type );
    }

    if( h.h.v.size > 0 && h.h.v.size != h.h.s.get_volume() )
    {
        h.h.fit_size();
    }

    if( o.set_value )
    {
        h.h.fit_size();
        h.h.v.set_random( 1.0, o.v_min, o.v_max, prsg );
    }

     h.h.check_integrity();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:generator_s) :.run =
{
    ASSERT( o->eval );
    bcore_prsg* prsg = o.param.prsg.clone().scope();

    for( sz_t i = 0; i < o->cycles; i++ )
    {
        opal_eval_nop_param_s* param = o->param.clone().scope( scope_local );
        param.prsg.set_state_mix( param->prsg, prsg );
        if( param.ha ) o.randomize_holor( param.ha, prsg );
        if( param.hb ) o.randomize_holor( param.hb, prsg );
        if( param.hc ) o.randomize_holor( param.hc, prsg );
        if( param.hr ) o.randomize_holor( param.hr, prsg );
        opal_eval_nop* eval = o.eval.clone().scope( scope_local );
        eval.set_param( param );
        eval.run( result );
        if( result )
        {
            if( result.error )
            {
                if( o.tolerated_cycles.find( 0, -1, i ) == o.tolerated_cycles.size )
                {
                    st_s* s = result.msg.clone().scope( scope_local );
                    result.msg.copy_fa( "At cycle #<sz_t>:\n#<st_s*>", i, s );
                    return result;
                }

                result.error = false;
                result.tolerated_errors++;
                result.msg.clear();
            }
        }
    }

    return result;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar1_s) :.run =
{
    if( !o.param.nop ) ERR_fa( "Operator missing." );

    result.total_tests++;

    opal_nop* nop = o.param.nop;

    opal_holor_s* ha = o.param.ha;
    opal_holor_s* hr = o.param.hr;

    ASSERT( ha );

    bcore_prsg* prsg = o->param.prsg.clone().scope();

    if( o.param.verbosity >= 4 )
    {
        sc_t symbol = nop.symbol();
        if( symbol )
        {
            bcore_sink_a_push_fa( o->param.log, " #<sc_t>( ", symbol );
        }
        else
        {
            bcore_sink_a_push_fa( o->param.log, " <#<sc_t>>( ", ifnameof( nop->_ ) );
        }

        opal_holor_s_to_sink( ha, o.param.log );
        bcore_sink_a_push_fa( o.param.log, " )\n" );
    }

    opal_nop_solve_result_s* solve_result = opal_nop_solve_result_s!.scope();

    opal_holor_s* a[ 1 ] = { ha };

    bl_t success = nop.solve( o->context, a, solve_result );
    opal_holor_s* r = solve_result.h;

    result.solvable_tests += success;

    if( !success )
    {
        if( ( hr ) || o.param.verbosity > 5 )
        {
            st_s* msg = st_s!.scope();

            if( ha )
            {
                msg.push_fa( "\n:a: " );
                ha.brief_to_sink( msg );
            }

            if( solve_result.msg ) msg.push_fa( "\n#<sc_t>", solve_result.msg.sc );

            if( hr )
            {
                result.msg.push_fa( "Cannot solve (a)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop._ ), msg.sc );
                result.error = true;
            }
            else
            {
                o.param.log.push_fa( "Cannot solve (a)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop._ ), msg.sc );
            }
        }

        return result;
    }

    if( hr )
    {
        ASSERT( hr.m.htp == r.m.htp );
        if( !bhvm_holor_s_is_equal( &hr->h, &r->h ) )
        {
            st_s* msg = st_s!.scope();
            msg.push_fa( "\n:result   : " );
            r.brief_to_sink( msg );
            msg.push_fa( "\n:expected : " );
            hr.brief_to_sink( msg );

            result.msg.push_fa( "Operation '#<sc_t>' solve: Result failure.#<sc_t>\n", ifnameof( nop._ ), msg.sc );
            result.error = true;
            return result;
        }
    }
    else
    {
        if( o.param.verbosity >= 2 )
        {
            o.param.log.push_fa( "r: " );
            r.to_sink( o.param.log );
            o.param.log.push_fa( "\n" );
        }
    }

    if( solve_result.codable )
    {
        bhvm_mcode_frame_s* frame = bhvm_mcode_frame_s!.scope();
        bhvm_vop_arr_ci_s* arr_ci = bhvm_vop_arr_ci_s!.scope();

        sz_t i_ina  = frame.push_hmc( ha.h, NULL, 'a', arr_ci );
        sz_t i_out  = frame.push_hmc( r.h,  NULL, 'y', arr_ci );
        sz_t i_gina = frame.push_hmc( ha.h, NULL, 'f', arr_ci );
        sz_t i_gout = frame.push_hmc( r.h,  NULL, 'z', arr_ci );

        bhvm_holor_s* ina  = frame.hbase.holor_adl.[ i_ina  ];
        bhvm_holor_s* out  = frame.hbase.holor_adl.[ i_out  ];
        bhvm_holor_s* gina = frame.hbase.holor_adl.[ i_gina ];
        bhvm_holor_s* gout = frame.hbase.holor_adl.[ i_gout ];

        bhvm_holor_s* fin = out.clone().scope();
        bhvm_holor_s* scl = bhvm_holor_s!.scope();
        scl.set_scalar_f3( 1.0 );

        nop.mcode_push_ap_track( solve_result,      arr_ci, frame );
        nop.mcode_push_dp_track( solve_result, 'a', arr_ci, frame );

        bhvm_hop_ar0_zro_s_f( out );

        frame.track_run( TYPEOF_track_ap_setup );
        frame.track_run( TYPEOF_track_dp_setup );
        frame.track_run( TYPEOF_track_ap );

        bhvm_hop_ar0_zro_s_f( gina );

        /// choose fin such that energy is 1.0
        fin.v.set_random( 1.0, -1.0, 1.0, prsg );
        bhvm_hop_ar1_sqrsum_s_f( fin, scl );
        scl.set_scalar_f3( f3_srt( 1.0 / bhvm_value_s_get_f3( &scl->v, 0 ) ) );
        bhvm_hop_ar2_eci_mul_s_f( fin, scl, fin );
        bhvm_hop_ar2_eci_add_s_f( out, fin, fin );

        bhvm_hop_ar2_eci_sub_s_f( out, fin, gout );
        scl.set_scalar_f3( 2.0 );
        bhvm_hop_ar2_eci_mul_s_f( gout, scl, gout );
        frame.track_run( TYPEOF_track_dp );

        if( !out.is_equal( r.h ) )
        {
            st_s* msg = st_s_create_fa( "\n:result   : " ).scope();
            out.brief_to_sink( msg );
            msg.push_fa( "\n:expected : " );
            r.h.brief_to_sink( msg );

            result.msg.push_fa( "Operation '#<sc_t>' mcode ap: Result failure.#<sc_t>\n", ifnameof( nop._ ), msg.sc );
            result.error = true;
            return result;
        }

        bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
        f3_t e0 = scl.v.get_f3( 0 );

        // test gradients

        f3_t in_eps = 1e-4; // input epsilon
        f3_t gr_dev = 2e-1; // max relative gradient deviation
        f3_t en_min_dev = 1e-6; // significant energy deviation (tests with less deviations do not generate an error)
        f3_t en_max_dev = 0.1;  // too high energy deviation
        f3_t o0_max     = 1E1;  // max out energy

        {
            bhvm_holor_s*  in =  ina;
            bhvm_holor_s* gin = gina;
            for( sz_t i = 0; i < in.v.size; i++ )
            {
                f3_t v0 = in.v.get_f3( i );
                f3_t g0 = gin.v.get_f3( i );  // dp grad

                in.v.set_f3( i, v0 + in_eps );
                frame.track_run( TYPEOF_track_ap );

                bhvm_hop_ar1_sqrsum_s_f( out, scl );
                f3_t o0 = scl.v.get_f3( 0 );

                bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
                f3_t e1 = scl.v.get_f3( 0 );
                f3_t de = e1 - e0;
                f3_t g1 = de / in_eps;  // approximate grad

                if
                (
                    f3_abs( g0 - g1 ) > f3_max( f3_abs( g0 ), f3_abs( g1 ) ) * gr_dev &&
                    f3_abs( de ) > en_min_dev &&
                    f3_abs( de ) < en_max_dev &&
                    o0 < o0_max
                )
                {
                    st_s* msg = st_s!.scope();
                    msg.push_fa( "\nGradient test: Operation '#<sc_t>', 'dp_#<char>' element '#<sz_t>':", ifnameof( nop->_ ), 'a', i );
                    msg.push_fa( "\nina            : " );  ina.brief_to_sink( msg );
                    msg.push_fa( "\nout            : " );  out.brief_to_sink( msg );
                    msg.push_fa( "\nfin            : " );  fin.brief_to_sink( msg );
                    msg.push_fa( "\ngina           : " );  gina.brief_to_sink( msg );
                    msg.push_fa( "\ngout           : " );  gout.brief_to_sink( msg );
                    msg.pushf( "\nEnergy         : %+7.5g (e0) %+7.5g (e1) ", e0, e1 );
                    msg.pushf( "\nEnergy (out)   : %+7.5g", o0 );
                    msg.pushf( "\ne1 - e0        : %+7.5g", de );
                    msg.pushf( "\nEpsilon        : %+5.3g", in_eps );
                    msg.pushf( "\nApproximation  : %+5.3g", g1 );
                    msg.pushf( "\nDifferentiation: %+5.3g", g0 );

                    result.msg.push_fa( "#<sc_t>\n", msg.sc );
                    result.error = true;
                    return result;
                }

                in.v.set_f3( i, v0 );
            }
        }
    }

    return NULL;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:ar2_s) :.run =
{
    if( !o.param.nop ) ERR_fa( "Operator missing." );

    result.total_tests++;

    opal_nop* nop = o->param.nop;

    opal_holor_s* ha = o.param.ha;
    opal_holor_s* hb = o.param.hb;
    opal_holor_s* hr = o.param.hr;

    ASSERT( ha );
    ASSERT( hb );

    bcore_prsg* prsg = o->param.prsg.clone().scope();

    if( o.param.verbosity >= 4 )
    {
        ha.to_sink( o.param.log );
        sc_t symbol = nop.symbol();
        if( symbol )
        {
            o.param.log.push_fa( " #<sc_t> ", symbol );
        }
        else
        {
            o.param.log.push_fa( " <#<sc_t>> ", ifnameof( nop._ ) );
        }
        hb.to_sink( o.param.log );
        o.param.log.push_fa( "\n" );
    }

    opal_nop_solve_result_s* solve_result = opal_nop_solve_result_s!.scope();

    opal_holor_s* a[ 2 ] = { ha, hb };

    bl_t success = nop.solve( o->context, a, solve_result );
    opal_holor_s* r = solve_result.h;

    result.solvable_tests += success;

    if( !success )
    {
        if( ( hr ) || o.param.verbosity > 5 )
        {
            st_s* msg = st_s!.scope();

            if( ha )
            {
                msg.push_fa( "\n:a: " );
                ha.brief_to_sink( msg );
            }
            if( hb )
            {
                msg.push_fa( "\n:b: " );
                hb.brief_to_sink( msg );
            }

            if( solve_result.msg ) msg.push_fa( "\n#<sc_t>", solve_result.msg.sc );

            if( hr )
            {
                result.msg.push_fa( "Cannot solve (a,b)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop._ ), msg.sc );
                result.error = true;
            }
            else
            {
                o.param.log.push_fa( "Cannot solve (a,b)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop._ ), msg.sc );
            }
        }

        return result;
    }

    if( hr )
    {
        ASSERT( hr.m.htp == r.m.htp );
        if( !hr.h.is_equal( r.h ) )
        {
            st_s* msg = st_s!.scope();
            msg.push_fa( "\n:result   : " );
            r.brief_to_sink( msg );
            msg.push_fa( "\n:expected : " );
            hr.brief_to_sink( msg );
            result.msg.push_fa( "Operation '#<sc_t>' solve: Result failure.#<sc_t>\n", ifnameof( nop._ ), msg.sc );
            result.error = true;
            return result;
        }
    }
    else
    {
        if( o.param.verbosity >= 2 )
        {
            o.param.log.push_fa( "r: " );
            r.to_sink( o->param.log );
            o->param.log.push_fa( "\n" );
        }
    }

    if( solve_result->codable )
    {
        $* frame = bhvm_mcode_frame_s!.scope();
        $* arr_ci = bhvm_vop_arr_ci_s!.scope();

        sz_t i_ina  = frame.push_hmc( ha.h, NULL, 'a', arr_ci );
        sz_t i_inb  = frame.push_hmc( hb.h, NULL, 'b', arr_ci );
        sz_t i_out  = frame.push_hmc(  r.h, NULL, 'y', arr_ci );
        sz_t i_gina = frame.push_hmc( ha.h, NULL, 'f', arr_ci );
        sz_t i_ginb = frame.push_hmc( hb.h, NULL, 'g', arr_ci );
        sz_t i_gout = frame.push_hmc(  r.h, NULL, 'z', arr_ci );

        bhvm_holor_s* ina  = frame.hbase.holor_adl.[ i_ina  ];
        bhvm_holor_s* inb  = frame.hbase.holor_adl.[ i_inb  ];
        bhvm_holor_s* out  = frame.hbase.holor_adl.[ i_out  ];
        bhvm_holor_s* gina = frame.hbase.holor_adl.[ i_gina ];
        bhvm_holor_s* ginb = frame.hbase.holor_adl.[ i_ginb ];
        bhvm_holor_s* gout = frame.hbase.holor_adl.[ i_gout ];

        bhvm_holor_s*  fin = out.clone().scope();
        bhvm_holor_s*  scl = bhvm_holor_s!.scope();
        scl.set_scalar_f3( 1.0 );

        nop.mcode_push_ap_track( solve_result,      arr_ci, frame );
        nop.mcode_push_dp_track( solve_result, 'a', arr_ci, frame );
        nop.mcode_push_dp_track( solve_result, 'b', arr_ci, frame );

        bhvm_hop_ar0_zro_s_f( out );

        frame.track_run( TYPEOF_track_ap_setup );
        frame.track_run( TYPEOF_track_dp_setup );
        frame.track_run( TYPEOF_track_ap );

        bhvm_hop_ar0_zro_s_f( gina );
        bhvm_hop_ar0_zro_s_f( ginb );

        /// choose fin such that energy is 1.0
        fin.v.set_random( 1.0, -1.0, 1.0, prsg );
        bhvm_hop_ar1_sqrsum_s_f( fin, scl );
        scl.set_scalar_f3( f3_srt( 1.0 / bhvm_value_s_get_f3( &scl->v, 0 ) ) );
        bhvm_hop_ar2_eci_mul_s_f( fin, scl, fin );
        bhvm_hop_ar2_eci_add_s_f( out, fin, fin );

        bhvm_hop_ar2_eci_sub_s_f( out, fin, gout );
        scl.set_scalar_f3( 2.0 );
        bhvm_hop_ar2_eci_mul_s_f( gout, scl, gout );
        frame.track_run( TYPEOF_track_dp );

        if( !out.is_equal( r.h ) )
        {
            st_s* msg = st_s!.scope();
            msg.push_fa( "\n:result   : " );
            out.brief_to_sink( msg );
            msg.push_fa( "\n:expected : " );
            r.h.brief_to_sink( msg );

            result.msg.push_fa( "Operation '#<sc_t>' mcode ap: Result failure.#<sc_t>\n", ifnameof( nop._ ), msg.sc );
            result.error = true;
            return result;
        }

        bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
        f3_t e0 = scl.v.get_f3( 0 );

        // test gradients

        f3_t in_eps = 1e-4; // input epsilon
        f3_t gr_dev = 2e-1; // max relative gradient deviation
        f3_t en_min_dev = 1e-6; // significant energy deviation (tests with less deviations do not generate an error)
        f3_t en_max_dev = 0.1;  // too high energy deviation
        f3_t o0_max     = 1E1;  // max out energy

        for( sz_t ch = 0; ch < 2; ch++ )
        {
            bhvm_holor_s*  in = ( ch == 0 ) ?  ina :  inb;
            bhvm_holor_s* gin = ( ch == 0 ) ? gina : ginb;
            for( sz_t i = 0; i < in.v.size; i++ )
            {
                f3_t v0 = in.v.get_f3( i );
                f3_t g0 = gin.v.get_f3( i );  // dp grad

                in.v.set_f3( i, v0 + in_eps );
                frame.track_run( TYPEOF_track_ap );

                bhvm_hop_ar1_sqrsum_s_f( out, scl );
                f3_t o0 = scl.v.get_f3( 0 );

                bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
                f3_t e1 = scl.v.get_f3( 0 );
                f3_t de = e1 - e0;
                f3_t g1 = de / in_eps;  // approximate grad

                bl_t error =
                (
                    f3_abs( g0 - g1 ) > f3_max( f3_abs( g0 ), f3_abs( g1 ) ) * gr_dev &&
                    f3_abs( de ) > en_min_dev &&
                    f3_abs( de ) < en_max_dev &&
                    o0 < o0_max
                );


                if( error || ( o.param.verbosity >= 10 ) )
                {
                    st_s* msg = st_s!.scope();
                    msg.push_fa( "\nGradient test: Operation '#<sc_t>', 'dp_#<char>' element '#<sz_t>':", ifnameof( nop->_ ), ( char )( 'a' + ch ), i );
                    msg.push_fa( "\nina            : " );  ina.brief_to_sink( msg );
                    msg.push_fa( "\ninb            : " );  inb.brief_to_sink( msg );
                    msg.push_fa( "\nout            : " );  out.brief_to_sink( msg );
                    msg.push_fa( "\nfin            : " );  fin.brief_to_sink( msg );
                    msg.push_fa( "\ngina           : " );  gina.brief_to_sink( msg );
                    msg.push_fa( "\nginb           : " );  ginb.brief_to_sink( msg );
                    msg.push_fa( "\ngout           : " );  gout.brief_to_sink( msg );
                    msg.pushf( "\nEnergy         : %+7.5g (e0) %+7.5g (e1) ", e0, e1 );
                    msg.pushf( "\nEnergy (out)   : %+7.5g", o0 );
                    msg.pushf( "\ne1 - e0        : %+7.5g", de );
                    msg.pushf( "\nEpsilon        : %+5.3g", in_eps );
                    msg.pushf( "\nApproximation  : %+5.3g", g1 );
                    msg.pushf( "\nDifferentiation: %+5.3g", g0 );

                    if( error )
                    {
                        result.msg.push_fa( "#<sc_t>\n", msg->sc );
                        result.error = true;
                        return result;
                    }
                    else
                    {
                        o.param.log.push_fa( " #<sc_t>\n", msg->sc );
                    }
                }

                in.v.set_f3( i, v0 );
            }
        }
    }

    return NULL;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
