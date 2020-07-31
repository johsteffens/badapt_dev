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

#include "opal_eval_nop.h"

/**********************************************************************************************************************/
/// eval

// ---------------------------------------------------------------------------------------------------------------------

void opal_eval_nop_generator_s_randomize_holor( const opal_eval_nop_generator_s* o, opal_holor_s* h, bcore_prsg* prsg )
{
    if( o->set_htp ) h->m.htp = ( bcore_prsg_a_gen_f3( prsg, 0, 1 ) > 0.5 );

    if( o->set_shape )
    {
        ASSERT( o->set_dim );
        sz_t size = bcore_prsg_a_gen_f3( prsg, 0, 1 ) * o->max_shape_size * 23 /* some prime */;
        size = size % ( o->max_shape_size + 1 );
        bhvm_shape_s_set_size( &h->h.s, size );
    }

    if( o->set_dim )
    {
        ASSERT( o->set_value );
        ASSERT( o->max_dim > 0 );
        BFOR_EACH( i, &h->h.s )
        {
            sz_t size = bcore_prsg_a_gen_f3( prsg, 0, 1 ) * o->max_dim * 23;
            size = size % ( o->max_dim );
            h->h.s.data[ i ] = size + 1;
        }
    }

    if( o->set_v_type )
    {
        tp_t type = ( bcore_prsg_a_gen_f3( prsg, 0, 1 ) > 0.5 ) ? TYPEOF_f2_t : TYPEOF_f3_t;
        bhvm_value_s_set_type( &h->h.v, type );
    }

    if( h->h.v.size > 0 && h->h.v.size != bhvm_shape_s_get_volume( &h->h.s ) )
    {
        bhvm_holor_s_fit_size( &h->h );
    }

    if( o->set_value )
    {
        bhvm_holor_s_fit_size( &h->h );
        bhvm_value_s_set_random( &h->h.v, 1.0, o->v_min, o->v_max, prsg );
    }

    bhvm_holor_s_check_integrity( &h->h );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_eval_nop_result_s* opal_eval_nop_generator_s_run( const opal_eval_nop_generator_s* o, opal_eval_nop_result_s* result )
{
    BLM_INIT();
    ASSERT( o->eval );
    bcore_prsg* prsg = BLM_A_PUSH( bcore_prsg_a_clone( o->param.prsg ) );

    for( sz_t i = 0; i < o->cycles; i++ )
    {
        BLM_INIT();
        opal_eval_nop_param_s* param = BLM_A_PUSH( opal_eval_nop_param_s_clone( &o->param ) );
        bcore_prsg_a_set_state_mix( param->prsg, param->prsg, prsg );
        if( param->ha ) opal_eval_nop_generator_s_randomize_holor( o, param->ha, prsg );
        if( param->hb ) opal_eval_nop_generator_s_randomize_holor( o, param->hb, prsg );
        if( param->hc ) opal_eval_nop_generator_s_randomize_holor( o, param->hc, prsg );
        if( param->hr ) opal_eval_nop_generator_s_randomize_holor( o, param->hr, prsg );
        opal_eval_nop* eval = BLM_A_PUSH( opal_eval_nop_a_clone( o->eval ) );
        opal_eval_nop_a_set_param( eval, param );
        opal_eval_nop_a_run( eval, result );
        if( result )
        {
            if( result->error )
            {
                if( bcore_arr_uz_s_find( &o->tolerated_cycles, 0, -1, i ) == o->tolerated_cycles.size )
                {
                    st_s* s = BLM_A_PUSH( st_s_clone( &result->msg ) );
                    st_s_copy_fa( &result->msg, "At cycle #<sz_t>:\n#<st_s*>", i, s );
                    BLM_RETURNV( opal_eval_nop_result_s*, result );
                }

                result->error = false;
                result->tolerated_errors++;
                st_s_clear( &result->msg );
            }
        }
        BLM_DOWN();
    }

    BLM_RETURNV( opal_eval_nop_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_eval_nop_result_s* opal_eval_nop_ar1_s_run( const opal_eval_nop_ar1_s* o, opal_eval_nop_result_s* result )
{
    BLM_INIT();
    if( !o->param.nop ) ERR_fa( "Operator missing." );

    result->total_tests++;

    opal_nop* nop = o->param.nop;

    opal_holor_s* ha = o->param.ha;
    opal_holor_s* hr = o->param.hr;

    ASSERT( ha );

    bcore_prsg* prsg = BLM_A_PUSH( bcore_prsg_a_clone( o->param.prsg ) );

    if( o->param.verbosity >= 4 )
    {
        sc_t symbol = opal_nop_a_symbol( nop );
        if( symbol )
        {
            bcore_sink_a_push_fa( o->param.log, " #<sc_t>( ", symbol );
        }
        else
        {
            bcore_sink_a_push_fa( o->param.log, " <#<sc_t>>( ", ifnameof( nop->_ ) );
        }

        opal_holor_s_to_sink( ha, o->param.log );
        bcore_sink_a_push_fa( o->param.log, " )\n" );
    }

    opal_nop_solve_result_s* solve_result = BLM_CREATE( opal_nop_solve_result_s );

    opal_holor_s* a[ 1 ] = { ha };

    bl_t success = opal_nop_a_solve( nop, o->context, a, solve_result );
    opal_holor_s* r = solve_result->h;

    result->solvable_tests += success;

    if( !success )
    {
        if( ( hr ) || o->param.verbosity > 5 )
        {
            st_s* msg = BLM_CREATE( st_s );

            if( ha )
            {
                st_s_push_fa( msg, "\n:a: " );
                opal_holor_s_brief_to_sink( ha, (bcore_sink*)msg );
            }

            if( solve_result->msg ) st_s_push_fa( msg, "\n#<sc_t>", solve_result->msg->sc );

            if( hr )
            {
                st_s_push_fa( &result->msg, "Cannot solve (a)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
                result->error = true;
            }
            else
            {
                bcore_sink_a_push_fa( o->param.log, "Cannot solve (a)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            }
        }

        BLM_RETURNV( opal_eval_nop_result_s*, result );
    }

    if( hr )
    {
        ASSERT( hr->m.htp == r->m.htp );
        if( !bhvm_holor_s_is_equal( &hr->h, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            opal_holor_s_brief_to_sink( r, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            opal_holor_s_brief_to_sink( hr, (bcore_sink*)msg );

            st_s_push_fa( &result->msg, "Operation '#<sc_t>' solve: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            result->error = true;
            BLM_RETURNV( opal_eval_nop_result_s*, result );
        }
    }
    else
    {
        if( o->param.verbosity >= 2 )
        {
            bcore_sink_a_push_fa( o->param.log, "r: " );
            opal_holor_s_to_sink( r, o->param.log );
            bcore_sink_a_push_fa( o->param.log, "\n" );
        }
    }

    if( solve_result->codable )
    {
        bhvm_mcode_frame_s* frame = BLM_CREATE( bhvm_mcode_frame_s );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

        sz_t i_ina  = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'a', arr_ci );
        sz_t i_out  = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'y', arr_ci );
        sz_t i_gina = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'f', arr_ci );
        sz_t i_gout = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'z', arr_ci );

        bhvm_holor_s* ina  = frame->hbase->holor_adl.data[ i_ina  ];
        bhvm_holor_s* out  = frame->hbase->holor_adl.data[ i_out  ];
        bhvm_holor_s* gina = frame->hbase->holor_adl.data[ i_gina ];
        bhvm_holor_s* gout = frame->hbase->holor_adl.data[ i_gout ];

        bhvm_holor_s*  fin = BLM_A_PUSH( bhvm_holor_s_clone( out ) );
        bhvm_holor_s*  scl = BLM_CREATE( bhvm_holor_s );
        bhvm_holor_s_set_scalar_f3( scl, 1.0 );

        opal_nop_a_mcode_push_ap_track( nop, solve_result,      arr_ci, frame );
        opal_nop_a_mcode_push_dp_track( nop, solve_result, 'a', arr_ci, frame );

        bhvm_hop_ar0_zro_s_f( out );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap_setup );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_dp_setup );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap );

        bhvm_hop_ar0_zro_s_f( gina );

        /// choose fin such that energy is 1.0
        bhvm_value_s_set_random( &fin->v, 1.0, -1.0, 1.0, prsg );
        bhvm_hop_ar1_sqrsum_s_f( fin, scl );
        bhvm_holor_s_set_scalar_f3( scl, f3_srt( 1.0 / bhvm_value_s_get_f3( &scl->v, 0 ) ) );
        bhvm_hop_ar2_eci_mul_s_f( fin, scl, fin );
        bhvm_hop_ar2_eci_add_s_f( out, fin, fin );

        bhvm_hop_ar2_eci_sub_s_f( out, fin, gout );
        bhvm_holor_s_set_scalar_f3( scl, 2.0 );
        bhvm_hop_ar2_eci_mul_s_f( gout, scl, gout );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_dp );

        if( !bhvm_holor_s_is_equal( out, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            bhvm_holor_s_brief_to_sink( out, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            bhvm_holor_s_brief_to_sink( &r->h, (bcore_sink*)msg );

            st_s_push_fa( &result->msg, "Operation '#<sc_t>' mcode ap: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            result->error = true;
            BLM_RETURNV( opal_eval_nop_result_s*, result );
        }

        bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
        f3_t e0 = bhvm_value_s_get_f3( &scl->v, 0 );

        // test gradients

        f3_t in_eps = 1e-4; // input epsilon
        f3_t gr_dev = 2e-1; // max relative gradient deviation
        f3_t en_min_dev = 1e-6; // significant energy deviation (tests with less deviations do not generate an error)
        f3_t en_max_dev = 0.1;  // too high energy deviation
        f3_t o0_max     = 1E1;  // max out energy

        {
            bhvm_holor_s*  in =  ina;
            bhvm_holor_s* gin = gina;
            for( sz_t i = 0; i < in->v.size; i++ )
            {
                f3_t v0 = bhvm_value_s_get_f3( &in->v, i );
                f3_t g0 = bhvm_value_s_get_f3( &gin->v, i );  // dp grad

                bhvm_value_s_set_f3( &in->v, i, v0 + in_eps );
                bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap );

                bhvm_hop_ar1_sqrsum_s_f( out, scl );
                f3_t o0 = bhvm_value_s_get_f3( &scl->v, 0 );

                bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
                f3_t e1 = bhvm_value_s_get_f3( &scl->v, 0 );
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
                    st_s* msg = BLM_CREATE( st_s );
                    st_s_push_fa( msg, "\nGradient test: Operation '#<sc_t>', 'dp_#<char>' element '#<sz_t>':", ifnameof( nop->_ ), 'a', i );
                    st_s_push_fa( msg, "\nina            : " );  bhvm_holor_s_brief_to_sink( ina, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\nout            : " );  bhvm_holor_s_brief_to_sink( out, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\nfin            : " );  bhvm_holor_s_brief_to_sink( fin, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\ngina           : " );  bhvm_holor_s_brief_to_sink( gina, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\ngout           : " );  bhvm_holor_s_brief_to_sink( gout, (bcore_sink*)msg );
                    st_s_pushf(   msg, "\nEnergy         : %+7.5g (e0) %+7.5g (e1) ", e0, e1 );
                    st_s_pushf(   msg, "\nEnergy (out)   : %+7.5g", o0 );
                    st_s_pushf(   msg, "\ne1 - e0        : %+7.5g", de );
                    st_s_pushf(   msg, "\nEpsilon        : %+5.3g", in_eps );
                    st_s_pushf(   msg, "\nApproximation  : %+5.3g", g1 );
                    st_s_pushf(   msg, "\nDifferentiation: %+5.3g", g0 );

                    st_s_push_fa( &result->msg, "#<sc_t>\n", msg->sc );
                    result->error = true;
                    BLM_RETURNV( opal_eval_nop_result_s*, result );
                }

                bhvm_value_s_set_f3( &in->v, i, v0 );
            }
        }
    }

    BLM_RETURNV( opal_eval_nop_result_s*, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_eval_nop_result_s* opal_eval_nop_ar2_s_run( const opal_eval_nop_ar2_s* o, opal_eval_nop_result_s* result )
{
    BLM_INIT();
    if( !o->param.nop ) ERR_fa( "Operator missing." );

    result->total_tests++;

    opal_nop* nop = o->param.nop;

    opal_holor_s* ha = o->param.ha;
    opal_holor_s* hb = o->param.hb;
    opal_holor_s* hr = o->param.hr;

    ASSERT( ha );
    ASSERT( hb );

    bcore_prsg* prsg = BLM_A_PUSH( bcore_prsg_a_clone( o->param.prsg ) );

    if( o->param.verbosity >= 4 )
    {
        opal_holor_s_to_sink( ha, o->param.log );
        sc_t symbol = opal_nop_a_symbol( nop );
        if( symbol )
        {
            bcore_sink_a_push_fa( o->param.log, " #<sc_t> ", symbol );
        }
        else
        {
            bcore_sink_a_push_fa( o->param.log, " <#<sc_t>> ", ifnameof( nop->_ ) );
        }
        opal_holor_s_to_sink( hb, o->param.log );
        bcore_sink_a_push_fa( o->param.log, "\n" );
    }

    opal_nop_solve_result_s* solve_result = BLM_CREATE( opal_nop_solve_result_s );

    opal_holor_s* a[ 2 ] = { ha, hb };

    bl_t success = opal_nop_a_solve( nop, o->context, a, solve_result );
    opal_holor_s* r = solve_result->h;

    result->solvable_tests += success;

    if( !success )
    {
        if( ( hr ) || o->param.verbosity > 5 )
        {
            st_s* msg = BLM_CREATE( st_s );

            if( ha )
            {
                st_s_push_fa( msg, "\n:a: " );
                opal_holor_s_brief_to_sink( ha, (bcore_sink*)msg );
            }
            if( hb )
            {
                st_s_push_fa( msg, "\n:b: " );
                opal_holor_s_brief_to_sink( hb, (bcore_sink*)msg );
            }

            if( solve_result->msg ) st_s_push_fa( msg, "\n#<sc_t>", solve_result->msg->sc );

            if( hr )
            {
                st_s_push_fa( &result->msg, "Cannot solve (a,b)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
                result->error = true;
            }
            else
            {
                bcore_sink_a_push_fa( o->param.log, "Cannot solve (a,b)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            }
        }

        BLM_RETURNV( opal_eval_nop_result_s*, result );
    }

    if( hr )
    {
        ASSERT( hr->m.htp == r->m.htp );
        if( !bhvm_holor_s_is_equal( &hr->h, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            opal_holor_s_brief_to_sink( r, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            opal_holor_s_brief_to_sink( hr, (bcore_sink*)msg );

            st_s_push_fa( &result->msg, "Operation '#<sc_t>' solve: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            result->error = true;
            BLM_RETURNV( opal_eval_nop_result_s*, result );
        }
    }
    else
    {
        if( o->param.verbosity >= 2 )
        {
            bcore_sink_a_push_fa( o->param.log, "r: " );
            opal_holor_s_to_sink( r, o->param.log );
            bcore_sink_a_push_fa( o->param.log, "\n" );
        }
    }

    if( solve_result->codable )
    {
        bhvm_mcode_frame_s* frame = BLM_CREATE( bhvm_mcode_frame_s );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

        sz_t i_ina  = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'a', arr_ci );
        sz_t i_inb  = bhvm_mcode_frame_s_push_hmc( frame, &hb->h, NULL, 'b', arr_ci );
        sz_t i_out  = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'y', arr_ci );
        sz_t i_gina = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'f', arr_ci );
        sz_t i_ginb = bhvm_mcode_frame_s_push_hmc( frame, &hb->h, NULL, 'g', arr_ci );
        sz_t i_gout = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'z', arr_ci );

        bhvm_holor_s* ina  = frame->hbase->holor_adl.data[ i_ina  ];
        bhvm_holor_s* inb  = frame->hbase->holor_adl.data[ i_inb  ];
        bhvm_holor_s* out  = frame->hbase->holor_adl.data[ i_out  ];
        bhvm_holor_s* gina = frame->hbase->holor_adl.data[ i_gina ];
        bhvm_holor_s* ginb = frame->hbase->holor_adl.data[ i_ginb ];
        bhvm_holor_s* gout = frame->hbase->holor_adl.data[ i_gout ];

        bhvm_holor_s*  fin = BLM_A_PUSH( bhvm_holor_s_clone( out ) );
        bhvm_holor_s*  scl = BLM_CREATE( bhvm_holor_s );
        bhvm_holor_s_set_scalar_f3( scl, 1.0 );

        opal_nop_a_mcode_push_ap_track( nop, solve_result,      arr_ci, frame );
        opal_nop_a_mcode_push_dp_track( nop, solve_result, 'a', arr_ci, frame );
        opal_nop_a_mcode_push_dp_track( nop, solve_result, 'b', arr_ci, frame );

        bhvm_hop_ar0_zro_s_f( out );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap_setup );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_dp_setup );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap );

        bhvm_hop_ar0_zro_s_f( gina );
        bhvm_hop_ar0_zro_s_f( ginb );

        /// choose fin such that energy is 1.0
        bhvm_value_s_set_random( &fin->v, 1.0, -1.0, 1.0, prsg );
        bhvm_hop_ar1_sqrsum_s_f( fin, scl );
        bhvm_holor_s_set_scalar_f3( scl, f3_srt( 1.0 / bhvm_value_s_get_f3( &scl->v, 0 ) ) );
        bhvm_hop_ar2_eci_mul_s_f( fin, scl, fin );
        bhvm_hop_ar2_eci_add_s_f( out, fin, fin );

        bhvm_hop_ar2_eci_sub_s_f( out, fin, gout );
        bhvm_holor_s_set_scalar_f3( scl, 2.0 );
        bhvm_hop_ar2_eci_mul_s_f( gout, scl, gout );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_dp );

        if( !bhvm_holor_s_is_equal( out, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            bhvm_holor_s_brief_to_sink( out, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            bhvm_holor_s_brief_to_sink( &r->h, (bcore_sink*)msg );

            st_s_push_fa( &result->msg, "Operation '#<sc_t>' mcode ap: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            result->error = true;
            BLM_RETURNV( opal_eval_nop_result_s*, result );
        }

        bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
        f3_t e0 = bhvm_value_s_get_f3( &scl->v, 0 );

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
            for( sz_t i = 0; i < in->v.size; i++ )
            {
                f3_t v0 = bhvm_value_s_get_f3( &in->v, i );
                f3_t g0 = bhvm_value_s_get_f3( &gin->v, i );  // dp grad

                bhvm_value_s_set_f3( &in->v, i, v0 + in_eps );
                bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap );

                bhvm_hop_ar1_sqrsum_s_f( out, scl );
                f3_t o0 = bhvm_value_s_get_f3( &scl->v, 0 );

                bhvm_hop_ar2_sub_sqrsum_s_f( out, fin, scl );
                f3_t e1 = bhvm_value_s_get_f3( &scl->v, 0 );
                f3_t de = e1 - e0;
                f3_t g1 = de / in_eps;  // approximate grad

                bl_t error =
                (
                    f3_abs( g0 - g1 ) > f3_max( f3_abs( g0 ), f3_abs( g1 ) ) * gr_dev &&
                    f3_abs( de ) > en_min_dev &&
                    f3_abs( de ) < en_max_dev &&
                    o0 < o0_max
                );


                if( error || ( o->param.verbosity >= 10 ) )
                {
                    st_s* msg = BLM_CREATE( st_s );
                    st_s_push_fa( msg, "\nGradient test: Operation '#<sc_t>', 'dp_#<char>' element '#<sz_t>':", ifnameof( nop->_ ), ( char )( 'a' + ch ), i );
                    st_s_push_fa( msg, "\nina            : " );  bhvm_holor_s_brief_to_sink( ina, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\ninb            : " );  bhvm_holor_s_brief_to_sink( inb, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\nout            : " );  bhvm_holor_s_brief_to_sink( out, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\nfin            : " );  bhvm_holor_s_brief_to_sink( fin, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\ngina           : " );  bhvm_holor_s_brief_to_sink( gina, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\nginb           : " );  bhvm_holor_s_brief_to_sink( ginb, (bcore_sink*)msg );
                    st_s_push_fa( msg, "\ngout           : " );  bhvm_holor_s_brief_to_sink( gout, (bcore_sink*)msg );
                    st_s_pushf(   msg, "\nEnergy         : %+7.5g (e0) %+7.5g (e1) ", e0, e1 );
                    st_s_pushf(   msg, "\nEnergy (out)   : %+7.5g", o0 );
                    st_s_pushf(   msg, "\ne1 - e0        : %+7.5g", de );
                    st_s_pushf(   msg, "\nEpsilon        : %+5.3g", in_eps );
                    st_s_pushf(   msg, "\nApproximation  : %+5.3g", g1 );
                    st_s_pushf(   msg, "\nDifferentiation: %+5.3g", g0 );

                    if( error )
                    {
                        st_s_push_fa( &result->msg, "#<sc_t>\n", msg->sc );
                        result->error = true;
                        BLM_RETURNV( opal_eval_nop_result_s*, result );
                    }
                    else
                    {
                        bcore_sink_a_push_fa( o->param.log, " #<sc_t>\n", msg->sc );
                    }
                }

                bhvm_value_s_set_f3( &in->v, i, v0 );
            }
        }
    }

    BLM_RETURNV( opal_eval_nop_result_s*, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


