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

#include "lion_nop_eval.h"

/**********************************************************************************************************************/
/// eval

// ---------------------------------------------------------------------------------------------------------------------

void lion_nop_eval_generator_s_randomize_holor( const lion_nop_eval_generator_s* o, u2_t* rval, lion_holor_s* h )
{
    if( o->set_htp ) h->m.htp = ( f3_xsg1_sym( rval ) > 0 );

    if( o->set_shape )
    {
        ASSERT( o->set_dim );
        sz_t size = f3_xsg1_pos( rval ) * o->max_shape_size * 23 /* some prime */;
        size = size % ( o->max_shape_size + 1 );
        bhvm_shape_s_set_size( &h->h.s, size );
    }

    if( o->set_dim )
    {
        ASSERT( o->set_value );
        ASSERT( o->max_dim > 0 );
        BFOR_EACH( i, &h->h.s )
        {
            sz_t size = f3_xsg1_pos( rval ) * o->max_dim * 23;
            size = size % ( o->max_dim );
            h->h.s.data[ i ] = size + 1;
        }
    }

    if( o->set_v_type )
    {
        tp_t type = ( f3_xsg1_sym( rval ) > 0 ) ? TYPEOF_f2_t : TYPEOF_f3_t;
        bhvm_value_s_set_type( &h->h.v, type );
    }

    if( h->h.v.size > 0 && h->h.v.size != bhvm_shape_s_get_volume( &h->h.s ) )
    {
        bhvm_holor_s_fit_size( &h->h );
    }

    if( o->set_value )
    {
        bhvm_holor_s_fit_size( &h->h );
        bhvm_value_s_set_random( &h->h.v, 1.0, o->v_min, o->v_max, rval );
    }

    bhvm_holor_s_check_integrity( &h->h );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_nop_eval_result_s* lion_nop_eval_generator_s_run( const lion_nop_eval_generator_s* o )
{
    ASSERT( o->eval );
    u2_t rval = o->param.rval;
    for( sz_t i = 0; i < o->cycles; i++ )
    {
        BLM_INIT();
        lion_nop_eval_param_s* param = BLM_A_PUSH( lion_nop_eval_param_s_clone( &o->param ) );
        param->rval = bcore_xsg3_u2( param->rval + rval );
        if( param->ha ) lion_nop_eval_generator_s_randomize_holor( o, &rval, param->ha );
        if( param->hb ) lion_nop_eval_generator_s_randomize_holor( o, &rval, param->hb );
        if( param->hc ) lion_nop_eval_generator_s_randomize_holor( o, &rval, param->hc );
        if( param->hr ) lion_nop_eval_generator_s_randomize_holor( o, &rval, param->hr );
        lion_nop_eval* eval =  BLM_A_PUSH( lion_nop_eval_a_clone( o->eval ) );
        lion_nop_eval_a_set_param( eval, param );
        lion_nop_eval_result_s* r = BLM_A_PUSH( lion_nop_eval_a_run( eval ) );
        if( r && r->error )
        {
            if( bcore_arr_uz_s_find( &o->tolerated_cycles, 0, -1, i ) == o->tolerated_cycles.size )
            {
                st_s* s = BLM_A_PUSH( st_s_clone( &r->msg ) );
                st_s_copy_fa( &r->msg, "At cycle #<sz_t>:\n#<st_s*>", i, s );
                BLM_RETURNV( lion_nop_eval_result_s*, lion_nop_eval_result_s_clone( r ) );
            }
        }
        BLM_DOWN();
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_nop_eval_result_s* lion_nop_eval_ar1_s_run( const lion_nop_eval_ar1_s* o )
{
    BLM_INIT();
    if( !o->param.nop ) ERR_fa( "Operator missing." );

    lion_nop* nop = o->param.nop;

    lion_holor_s* ha = o->param.ha;
    lion_holor_s* hr = o->param.hr;

    ASSERT( ha );

    u2_t rval = o->param.rval;

    if( o->param.verbosity >= 4 )
    {
        sc_t symbol = lion_nop_a_symbol( nop );
        if( symbol )
        {
            bcore_sink_a_push_fa( o->param.log, " #<sc_t>( ", symbol );
        }
        else
        {
            bcore_sink_a_push_fa( o->param.log, " <#<sc_t>>( ", ifnameof( nop->_ ) );
        }

        lion_holor_s_to_sink( ha, o->param.log );
        bcore_sink_a_push_fa( o->param.log, " )\n" );
    }

    lion_nop_solve_result_s* result = BLM_CREATE( lion_nop_solve_result_s );

    lion_holor_s* a[ 1 ] = { ha };

    bl_t success = lion_nop_a_solve( nop, a, result );
    lion_holor_s* r = result->h;

    if( !success )
    {
        lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
        if( ( hr ) || o->param.verbosity > 5 )
        {
            st_s* msg = BLM_CREATE( st_s );

            if( ha )
            {
                st_s_push_fa( msg, "\n:a: " );
                lion_holor_s_brief_to_sink( ha, (bcore_sink*)msg );
            }

            if( result->msg ) st_s_push_fa( msg, "\n#<sc_t>", result->msg->sc );

            if( hr )
            {
                st_s_push_fa( &r->msg, "Cannot solve (a)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
                r->error = true;
            }
            else
            {
                bcore_sink_a_push_fa( o->param.log, "Cannot solve (a)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            }
        }

        BLM_RETURNV( lion_nop_eval_result_s*, r );
    }

    if( hr )
    {
        ASSERT( hr->m.htp == r->m.htp );
        if( !bhvm_holor_s_is_equal( &hr->h, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            lion_holor_s_brief_to_sink( r, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            lion_holor_s_brief_to_sink( hr, (bcore_sink*)msg );


            lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
            st_s_push_fa( &r->msg, "Operation '#<sc_t>' solve: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            r->error = true;
            BLM_RETURNV( lion_nop_eval_result_s*, r );
        }
    }
    else
    {
        if( o->param.verbosity >= 2 )
        {
            bcore_sink_a_push_fa( o->param.log, "r: " );
            lion_holor_s_to_sink( r, o->param.log );
            bcore_sink_a_push_fa( o->param.log, "\n" );
        }
    }

    if( result->codable )
    {
        bhvm_mcode_frame_s* frame = BLM_CREATE( bhvm_mcode_frame_s );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

        sz_t i_ina  = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'a', arr_ci );
        sz_t i_out  = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'y', arr_ci );
        sz_t i_gina = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'f', arr_ci );
        sz_t i_gout = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'z', arr_ci );

        bhvm_holor_s* ina  = &frame->hbase->holor_ads.data[ i_ina  ];
        bhvm_holor_s* out  = &frame->hbase->holor_ads.data[ i_out  ];
        bhvm_holor_s* gina = &frame->hbase->holor_ads.data[ i_gina ];
        bhvm_holor_s* gout = &frame->hbase->holor_ads.data[ i_gout ];

        bhvm_holor_s*  fin = BLM_A_PUSH( bhvm_holor_s_clone( out ) );
        bhvm_holor_s*  scl = BLM_CREATE( bhvm_holor_s );
        bhvm_holor_s_set_scalar_f3( scl, 1.0 );

        lion_nop_a_mcode_push_ap_track( nop, result,      arr_ci, frame );
        lion_nop_a_mcode_push_dp_track( nop, result, 'a', arr_ci, frame );

        bhvm_hop_ar0_zro_s_f( out );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_setup_ap );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_setup_dp );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap );

        bhvm_hop_ar0_zro_s_f( gina );

        /// choose fin such that energy is 1.0
        bhvm_value_s_set_random( &fin->v, 1.0, -1.0, 1.0, &rval );
        bhvm_hop_ar1_sqr_s_f( fin, scl );
        bhvm_holor_s_set_scalar_f3( scl, f3_srt( 1.0 / bhvm_value_s_get_f3( &scl->v, 0 ) ) );
        bhvm_hop_ar2_mul_vsv_s_f( fin, scl, fin );
        bhvm_hop_ar2_add_s_f( out, fin, fin );

        bhvm_hop_ar2_sub_s_f( out, fin, gout );
        bhvm_holor_s_set_scalar_f3( scl, 2.0 );
        bhvm_hop_ar2_mul_vsv_s_f( gout, scl, gout );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_dp );

        if( !bhvm_holor_s_is_equal( out, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            bhvm_holor_s_brief_to_sink( out, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            bhvm_holor_s_brief_to_sink( &r->h, (bcore_sink*)msg );

            lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
            st_s_push_fa( &r->msg, "Operation '#<sc_t>' mcode ap: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            r->error = true;
            BLM_RETURNV( lion_nop_eval_result_s*, r );
        }

        bhvm_hop_ar2_sub_sqr_s_f( out, fin, scl );
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

                bhvm_hop_ar1_sqr_s_f( out, scl );
                f3_t o0 = bhvm_value_s_get_f3( &scl->v, 0 );

                bhvm_hop_ar2_sub_sqr_s_f( out, fin, scl );
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

                    lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
                    st_s_push_fa( &r->msg, "#<sc_t>\n", msg->sc );
                    r->error = true;
                    BLM_RETURNV( lion_nop_eval_result_s*, r );
                }

                bhvm_value_s_set_f3( &in->v, i, v0 );
            }
        }
    }

    BLM_RETURNV( lion_nop_eval_result_s*, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_nop_eval_result_s* lion_nop_eval_ar2_s_run( const lion_nop_eval_ar2_s* o )
{
    BLM_INIT();
    if( !o->param.nop ) ERR_fa( "Operator missing." );

    lion_nop* nop = o->param.nop;

    lion_holor_s* ha = o->param.ha;
    lion_holor_s* hb = o->param.hb;
    lion_holor_s* hr = o->param.hr;

    ASSERT( ha );
    ASSERT( hb );

    u2_t rval = o->param.rval;

    if( o->param.verbosity >= 4 )
    {
        lion_holor_s_to_sink( ha, o->param.log );
        sc_t symbol = lion_nop_a_symbol( nop );
        if( symbol )
        {
            bcore_sink_a_push_fa( o->param.log, " #<sc_t> ", symbol );
        }
        else
        {
            bcore_sink_a_push_fa( o->param.log, " <#<sc_t>> ", ifnameof( nop->_ ) );
        }
        lion_holor_s_to_sink( hb, o->param.log );
        bcore_sink_a_push_fa( o->param.log, "\n" );
    }

    lion_nop_solve_result_s* result = BLM_CREATE( lion_nop_solve_result_s );

    lion_holor_s* a[ 2 ] = { ha, hb };

    bl_t success = lion_nop_a_solve( nop, a, result );
    lion_holor_s* r = result->h;

    if( !success )
    {
        lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
        if( ( hr ) || o->param.verbosity > 5 )
        {
            st_s* msg = BLM_CREATE( st_s );

            if( ha )
            {
                st_s_push_fa( msg, "\n:a: " );
                lion_holor_s_brief_to_sink( ha, (bcore_sink*)msg );
            }
            if( hb )
            {
                st_s_push_fa( msg, "\n:b: " );
                lion_holor_s_brief_to_sink( hb, (bcore_sink*)msg );
            }

            if( result->msg ) st_s_push_fa( msg, "\n#<sc_t>", result->msg->sc );

            if( hr )
            {
                st_s_push_fa( &r->msg, "Cannot solve (a,b)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
                r->error = true;
            }
            else
            {
                bcore_sink_a_push_fa( o->param.log, "Cannot solve (a,b)->r operation '#<sc_t>':#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            }
        }

        BLM_RETURNV( lion_nop_eval_result_s*, r );
    }

    if( hr )
    {
        ASSERT( hr->m.htp == r->m.htp );
        if( !bhvm_holor_s_is_equal( &hr->h, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            lion_holor_s_brief_to_sink( r, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            lion_holor_s_brief_to_sink( hr, (bcore_sink*)msg );


            lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
            st_s_push_fa( &r->msg, "Operation '#<sc_t>' solve: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            r->error = true;
            BLM_RETURNV( lion_nop_eval_result_s*, r );
        }
    }
    else
    {
        if( o->param.verbosity >= 2 )
        {
            bcore_sink_a_push_fa( o->param.log, "r: " );
            lion_holor_s_to_sink( r, o->param.log );
            bcore_sink_a_push_fa( o->param.log, "\n" );
        }
    }

    if( result->codable )
    {
        bhvm_mcode_frame_s* frame = BLM_CREATE( bhvm_mcode_frame_s );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

        sz_t i_ina  = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'a', arr_ci );
        sz_t i_inb  = bhvm_mcode_frame_s_push_hmc( frame, &hb->h, NULL, 'b', arr_ci );
        sz_t i_out  = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'y', arr_ci );
        sz_t i_gina = bhvm_mcode_frame_s_push_hmc( frame, &ha->h, NULL, 'f', arr_ci );
        sz_t i_ginb = bhvm_mcode_frame_s_push_hmc( frame, &hb->h, NULL, 'g', arr_ci );
        sz_t i_gout = bhvm_mcode_frame_s_push_hmc( frame,  &r->h, NULL, 'z', arr_ci );

        bhvm_holor_s* ina  = &frame->hbase->holor_ads.data[ i_ina  ];
        bhvm_holor_s* inb  = &frame->hbase->holor_ads.data[ i_inb  ];
        bhvm_holor_s* out  = &frame->hbase->holor_ads.data[ i_out  ];
        bhvm_holor_s* gina = &frame->hbase->holor_ads.data[ i_gina ];
        bhvm_holor_s* ginb = &frame->hbase->holor_ads.data[ i_ginb ];
        bhvm_holor_s* gout = &frame->hbase->holor_ads.data[ i_gout ];

        bhvm_holor_s*  fin = BLM_A_PUSH( bhvm_holor_s_clone( out ) );
        bhvm_holor_s*  scl = BLM_CREATE( bhvm_holor_s );
        bhvm_holor_s_set_scalar_f3( scl, 1.0 );

        lion_nop_a_mcode_push_ap_track( nop, result,      arr_ci, frame );
        lion_nop_a_mcode_push_dp_track( nop, result, 'a', arr_ci, frame );
        lion_nop_a_mcode_push_dp_track( nop, result, 'b', arr_ci, frame );

        bhvm_hop_ar0_zro_s_f( out );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_setup_ap );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_setup_dp );

        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_ap );

        bhvm_hop_ar0_zro_s_f( gina );
        bhvm_hop_ar0_zro_s_f( ginb );

        /// choose fin such that energy is 1.0
        bhvm_value_s_set_random( &fin->v, 1.0, -1.0, 1.0, &rval );
        bhvm_hop_ar1_sqr_s_f( fin, scl );
        bhvm_holor_s_set_scalar_f3( scl, f3_srt( 1.0 / bhvm_value_s_get_f3( &scl->v, 0 ) ) );
        bhvm_hop_ar2_mul_vsv_s_f( fin, scl, fin );
        bhvm_hop_ar2_add_s_f( out, fin, fin );

        bhvm_hop_ar2_sub_s_f( out, fin, gout );
        bhvm_holor_s_set_scalar_f3( scl, 2.0 );
        bhvm_hop_ar2_mul_vsv_s_f( gout, scl, gout );
        bhvm_mcode_frame_s_track_run( frame, TYPEOF_track_dp );

        if( !bhvm_holor_s_is_equal( out, &r->h ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            st_s_push_fa( msg, "\n:result   : " );
            bhvm_holor_s_brief_to_sink( out, (bcore_sink*)msg );
            st_s_push_fa( msg, "\n:expected : " );
            bhvm_holor_s_brief_to_sink( &r->h, (bcore_sink*)msg );

            lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
            st_s_push_fa( &r->msg, "Operation '#<sc_t>' mcode ap: Result failure.#<sc_t>\n", ifnameof( nop->_ ), msg->sc );
            r->error = true;
            BLM_RETURNV( lion_nop_eval_result_s*, r );
        }

        bhvm_hop_ar2_sub_sqr_s_f( out, fin, scl );
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

                bhvm_hop_ar1_sqr_s_f( out, scl );
                f3_t o0 = bhvm_value_s_get_f3( &scl->v, 0 );

                bhvm_hop_ar2_sub_sqr_s_f( out, fin, scl );
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

                    lion_nop_eval_result_s* r = lion_nop_eval_result_s_create();
                    st_s_push_fa( &r->msg, "#<sc_t>\n", msg->sc );
                    r->error = true;
                    BLM_RETURNV( lion_nop_eval_result_s*, r );
                }

                bhvm_value_s_set_f3( &in->v, i, v0 );
            }
        }
    }

    BLM_RETURNV( lion_nop_eval_result_s*, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_nop_eval_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_nop_eval" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "lion_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


