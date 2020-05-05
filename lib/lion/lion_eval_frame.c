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

#include "lion_eval_frame.h"

#ifdef TYPEOF_lion_eval_frame

/**********************************************************************************************************************/
/// lion_frame_s

// ---------------------------------------------------------------------------------------------------------------------

/** Estimates jacobians for entry and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [in-channels][out-channels]
 */
static void frame_s_estimate_jacobian_en( const lion_frame_s* const_o, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();

    lion_frame_s* o = BLM_CLONE( lion_frame_s, const_o );
    ASSERT( o->setup );

    bhvm_holor_adl_s* adl_en = BLM_CLONE( bhvm_holor_adl_s, en );
    bhvm_holor_adl_s* adl_ex = BLM_CREATE( bhvm_holor_adl_s );
    bhvm_holor_adl_s* adl_rf = BLM_CREATE( bhvm_holor_adl_s );
    lion_frame_s_run_ap_adl( o, adl_en, adl_ex );
    bhvm_holor_adl_s_copy( adl_rf, adl_ex );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, adl_en->size );

    BFOR_SIZE( i, adl_en->size )
    {
        bhvm_holor_s* h_en = adl_en->data[ i ];
        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, adl_ex->size );

        BFOR_EACH( j, &h_en->v )
        {
            f3_t v_en = bhvm_value_s_get_f3( &h_en->v, j );
            bhvm_value_s_set_f3( &h_en->v, j, v_en + epsilon );
            lion_frame_s_run_ap_adl( o, adl_en, adl_ex );
            BFOR_SIZE( k, adl_ex->size )
            {
                bhvm_holor_s* h_ex = adl_ex->data[ k ];
                bhvm_holor_s* h_rf = adl_rf->data[ k ];

                if( !jac_adl->data[ k ] ) jac_adl->data[ k ] = bhvm_holor_s_create();
                bhvm_holor_s* h_jc = jac_adl->data[ k ];
                if( h_jc->v.size == 0 )
                {
                    bhvm_shape_s_set_data_na( &h_jc->s, 2, h_ex->v.size, h_en->v.size );
                    bhvm_holor_s_set_type( h_jc, TYPEOF_f3_t );
                    bhvm_holor_s_fit_size( h_jc );
                }

                BFOR_EACH( l, &h_ex->v )
                {
                    f3_t v_ex = bhvm_value_s_get_f3( &h_ex->v, l );
                    f3_t v_rf = bhvm_value_s_get_f3( &h_rf->v, l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    bhvm_value_s_set_f3( &h_jc->v, j * h_jc->s.data[ 0 ] + l, v_gr );
                }
            }
            bhvm_value_s_set_f3( &h_en->v, j, v_en );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/** Estimates jacobians for adaptive and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [ada-channels][out-channels]
 */
static void frame_s_estimate_jacobian_ada( const lion_frame_s* const_o, const bhvm_holor_adl_s* adl_en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();
    lion_frame_s* o = BLM_CLONE( lion_frame_s, const_o );
    ASSERT( o->setup );

    bhvm_holor_adl_s* adl_ex = BLM_CREATE( bhvm_holor_adl_s );
    lion_frame_s_run_ap_adl( o, adl_en, adl_ex );

    sz_t size_ada = lion_frame_hidx_s_get_size( &o->hidx_ada );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, size_ada );

    BFOR_SIZE( i, size_ada )
    {
        bhvm_holor_s* h_ada = lion_frame_s_get_ap_ada( o, i );

        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, o->size_ex );

        BFOR_EACH( j, &h_ada->v )
        {
            f3_t v_ada = bhvm_value_s_get_f3( &h_ada->v, j );
            bhvm_value_s_set_f3( &h_ada->v, j, v_ada + epsilon );
            bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );
            BFOR_SIZE( k, o->size_ex )
            {
                bhvm_holor_s* h_ex = lion_frame_s_get_ap_ex( o, k );
                bhvm_holor_s* h_rf = adl_ex->data[ k ];

                if( !jac_adl->data[ k ] ) jac_adl->data[ k ] = bhvm_holor_s_create();
                bhvm_holor_s* h_jc = jac_adl->data[ k ];
                if( h_jc->v.size == 0 )
                {
                    bhvm_shape_s_set_data_na( &h_jc->s, 2, h_ex->v.size, h_ada->v.size );
                    bhvm_holor_s_set_type( h_jc, TYPEOF_f3_t );
                    bhvm_holor_s_fit_size( h_jc );
                }

                BFOR_EACH( l, &h_ex->v )
                {
                    f3_t v_ex = bhvm_value_s_get_f3( &h_ex->v, l );
                    f3_t v_rf = bhvm_value_s_get_f3( &h_rf->v, l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    bhvm_value_s_set_f3( &h_jc->v, j * h_jc->s.data[ 0 ] + l, v_gr );
                }
            }
            bhvm_value_s_set_f3( &h_ada->v, j, v_ada );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

lion_eval_frame_result_s* lion_eval_frame_plain_s_run( const lion_eval_frame_plain_s* o, lion_eval_frame_result_s* result )
{
    BLM_INIT();

    if( o->param.name.size > 0 && o->param.verbosity >= 2 ) bcore_sink_a_push_fa( o->param.log, "#<sc_t>:\n", o->param.name.sc );

    if( !o->param.src ) ERR_fa( "Source missing." );

    bcore_source* source = NULL;

    switch( *(aware_t*)o->param.src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = BLM_A_PUSH( bcore_file_open_source_path( ( const bcore_file_path_s* )o->param.src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = BLM_A_PUSH( bcore_source_string_s_create_from_string( ( const st_s* )o->param.src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->param.src ) );
        }
        break;
    }

    //ASSERT( o->param.in );

    const bhvm_holor_adl_s* adl_ap_en = o->param.in;
          bhvm_holor_adl_s* adl_ap_ex = BLM_CREATE( bhvm_holor_adl_s );

    lion_frame_s* frame0 = BLM_CREATE( lion_frame_s );
    if( o->param.verbosity >= 20 ) frame0->log = bcore_fork( o->param.log );

    lion_frame_s_setup_from_source_adl( frame0, source, adl_ap_en );

    /// test frame recovery/copying
    if( o->param.recovery_test )
    {
        lion_frame_s* frame1 = BLM_CREATE( lion_frame_s );
        bcore_bin_ml_a_copy( frame1, frame0 );
        frame0 = frame1;
    }

    /// test copying
    lion_frame_s* frame = BLM_CLONE( lion_frame_s, frame0 );

    if( frame->size_en > 0 )
    {
        if( !adl_ap_en )
        {
            WRN_fa( "Entry holors were not defined." );
        }
        else if( adl_ap_en->size != frame->size_en )
        {
            WRN_fa( "Number of expected entry holors (#<sz_t>) differs from number of provided entry holors (#<sz_t>).", frame->size_en, adl_ap_en->size );
        }
    }

    for( sz_t i = 0; i < o->ap_cycles; i++ )
    {
        lion_frame_s_run_ap_adl( frame, adl_ap_en, adl_ap_ex );

        if( o->param.verbosity >= 2 )
        {
            bcore_sink_a_push_fa( o->param.log, "Output (cycle #pl3 {#<sz_t>}): ", i );
            BFOR_EACH( j, adl_ap_ex )
            {
                bhvm_holor_s* h_hbo = adl_ap_ex->data[ j ];
                bhvm_holor_s_brief_to_sink( h_hbo, o->param.log );
                bcore_sink_a_push_fa( o->param.log, "#<sc_t>", j + 1 < adl_ap_ex->size ? ", " : "\n" );
            }
        }
    }

    BFOR_EACH( i, adl_ap_ex )
    {
        bhvm_holor_s* h_hbo = adl_ap_ex->data[ i ];
        if( o->param.out && o->param.out->size > i )
        {
            bhvm_holor_s* h_out = o->param.out->data[ i ];
            bl_t shape_dev = !bhvm_shape_s_is_equal( &h_out->s, &h_hbo->s );
            bl_t value_dev = shape_dev || ( bhvm_value_s_fdev_equ( &h_out->v, &h_hbo->v ) > o->param.max_dev );
            if( shape_dev || value_dev )
            {
                st_s* msg = BLM_CREATE( st_s );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "#<sc_t> deviation at output holor '#<sz_t>':", shape_dev ? "Shape" : "Value", i );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Frame output} " );
                bhvm_holor_s_brief_to_sink( h_hbo, (bcore_sink*)msg );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Expected output} " );
                bhvm_holor_s_brief_to_sink( h_out, (bcore_sink*)msg );
                ERR_fa( "#<st_s*>\n", msg );
            }
        }
        else
        {
            if( o->param.verbosity >= 0 )
            {
                bcore_sink_a_push_fa( o->param.log, "Frame out channel '#<sz_t>':\n", i );
                bhvm_holor_s_to_sink_nl( h_hbo, o->param.log );
            }
        }
    }

    if( o->param.verbosity >= 10 )
    {
        bcore_sink_a_push_fa( o->param.log, "\nBegin microcode disassembly\n\n" );
        lion_frame_s_disassemble_to_sink( frame, o->param.log );
        bcore_sink_a_push_fa( o->param.log, "End microcode disassembly\n\n" );
    }

    if( o->param.jacobian_test )
    {
        u2_t rval = 1234;

        if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "\nJacobian DP Test:\n" );

        bhvm_holor_adl_s* adl_dp_en = BLM_CLONE( bhvm_holor_adl_s, adl_ap_en );
        bhvm_holor_adl_s* adl_dp_ex = BLM_CLONE( bhvm_holor_adl_s, adl_ap_ex );
        BFOR_EACH( i, adl_dp_en ) bhvm_holor_s_zro( adl_dp_en->data[ i ] );

        BFOR_EACH( i, adl_dp_ex )
        {
            bhvm_value_s_set_random( &adl_dp_ex->data[ i ]->v, 1.0, -1, 1, &rval );
            if( o->param.verbosity >= 10 )
            {
                bcore_sink_a_push_fa( o->param.log, "Gradient exc #<sz_t>: ", i );
                bhvm_holor_s_to_sink_nl( adl_dp_ex->data[ i ], o->param.log );
            }
        }

        lion_frame_s_run_dp_adl( frame, adl_dp_ex, adl_dp_en );

        sz_t size_ex = lion_frame_s_get_size_ex( frame );
        bhvm_holor_mdl_s* mdl_jc = BLM_CREATE( bhvm_holor_mdl_s );

        /// testing entry channels
        if( lion_frame_s_get_size_en( frame ) )
        {
            if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "\nTesting #<sz_t> entry channels:\n", lion_frame_s_get_size_en( frame ) );

            frame_s_estimate_jacobian_en( frame, adl_ap_en, o->param.epsilon, mdl_jc );

            BFOR_SIZE( i, lion_frame_s_get_size_en( frame ) )
            {
                BLM_INIT();
                if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "enc #<sz_t>:\n", i );

                bhvm_holor_s* dp_en1 = adl_dp_en->data[ i ];
                bhvm_holor_s* dp_en2 = bhvm_holor_s_copy_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_en1 );
                bhvm_value_s_zro( &dp_en2->v );

                BFOR_SIZE( j, size_ex )
                {
                    BLM_INIT();
                    if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "exc #<sz_t>:\n", j );

                    bhvm_holor_s* h_jc = mdl_jc->data[ i ]->data[ j ];
                    if( o->param.verbosity >= 10 )
                    {
                        bcore_sink_a_push_fa( o->param.log, "Jacobian: " );
                        bhvm_holor_s_to_sink_nl( h_jc, o->param.log );
                    }

                    bhvm_holor_s* dp_ex1 = adl_dp_ex->data[ j ];
                    bhvm_holor_s* dp_ex2 = bhvm_holor_s_fork_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_ex1 );
                    lion_frame_sc_run_ap( "( y <- a, b, c ) { y = a + b ** c; }", ( const bhvm_holor_s*[] ) { dp_en2, h_jc, dp_ex2 }, 3, &dp_en2, 1 );
                    BLM_DOWN();
                }

                f3_t dev = bhvm_value_s_fdev_equ( &dp_en1->v, &dp_en2->v );

                bl_t error = dev > o->param.max_dev;

                if( error || o->param.verbosity >= 10 )
                {
                    st_s* st = BLM_CREATE( st_s );
                    st_s_push_fa( st, "dp-channel: #<sz_t>", i );
                    st_s_push_fa( st, ", dev: #<f3_t>", dev );
                    st_s_push_fa( st, "\ngradient (dp)          : " );
                    bhvm_holor_s_to_sink( dp_en1, ( bcore_sink* )st );
                    st_s_push_fa( st, "\ngradient (via jacobian): " );
                    bhvm_holor_s_to_sink( dp_en2, ( bcore_sink* )st );
                    st_s_push_fa( st, "\n" );
                    if( error )
                    {
                        st_s_push_fa( &result->msg, "\n#<sc_t>:", o->param.name.sc );
                        st_s_push_fa( &result->msg, "\nJacobian test failure:\n#<sc_t>\n", st->sc );
                        result->error = true;
                        BLM_RETURNV( lion_eval_frame_result_s*, result );
                    }
                    else
                    {
                        bcore_sink_a_push_fa( o->param.log, "#<sc_t>", st->sc );
                    }
                }

                BLM_DOWN();
            }
        }

        /// testing adaptive channels
        if( lion_frame_s_get_size_ada( frame ) )
        {
            if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "\nTesting #<sz_t> adaptive  channels:\n", lion_frame_s_get_size_ada( frame ) );

            frame_s_estimate_jacobian_ada( frame, adl_ap_en, o->param.epsilon, mdl_jc );

            BFOR_SIZE( i, lion_frame_s_get_size_ada( frame ) )
            {
                BLM_INIT();
                if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "adc #<sz_t>:\n", i );

                const bhvm_holor_s* dp_ada1 = lion_frame_s_get_dp_ada( frame, i );
                bhvm_holor_s* dp_ada2 = bhvm_holor_s_copy_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_ada1 );
                bhvm_value_s_zro( &dp_ada2->v );

                BFOR_SIZE( j, size_ex )
                {
                    BLM_INIT();
                    if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "exc #<sz_t>:\n", j );

                    bhvm_holor_s* h_jc = mdl_jc->data[ i ]->data[ j ];
                    if( o->param.verbosity >= 10 )
                    {
                        bcore_sink_a_push_fa( o->param.log, "Jacobian: " );
                        bhvm_holor_s_to_sink_nl( h_jc, o->param.log );
                    }

                    bhvm_holor_s* dp_ex1 = adl_dp_ex->data[ j ];
                    bhvm_holor_s* dp_ex2 = bhvm_holor_s_fork_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_ex1 );
                    lion_frame_sc_run_ap( "( y <- a, b, c ) { y = a + b ** c; }", ( const bhvm_holor_s*[] ) { dp_ada2, h_jc, dp_ex2 }, 3, &dp_ada2, 1 );
                    BLM_DOWN();
                }

                f3_t dev = bhvm_value_s_fdev_equ( &dp_ada1->v, &dp_ada2->v );

                bl_t error = dev > o->param.max_dev;

                if( error || o->param.verbosity >= 10 )
                {
                    st_s* st = BLM_CREATE( st_s );
                    st_s_push_fa( st, "dp-channel: #<sz_t>", i );
                    st_s_push_fa( st, ", dev: #<f3_t>", dev );
                    st_s_push_fa( st, "\ngradient (dp)          : " );
                    bhvm_holor_s_to_sink( dp_ada1, ( bcore_sink* )st );
                    st_s_push_fa( st, "\ngradient (via jacobian): " );
                    bhvm_holor_s_to_sink( dp_ada2, ( bcore_sink* )st );
                    st_s_push_fa( st, "\n" );
                    if( error )
                    {
                        st_s_push_fa( &result->msg, "\nJacobian test failure:\n#<sc_t>\n", st->sc );
                        result->error = true;
                        BLM_RETURNV( lion_eval_frame_result_s*, result );
                    }
                    else
                    {
                        bcore_sink_a_push_fa( o->param.log, "#<sc_t>", st->sc );
                    }
                }

                BLM_DOWN();
            }
        }
    }

    BLM_RETURNV( lion_eval_frame_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// lion_frame_cyclic_s

/** Estimates jacobians for entry and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [in-channels][out-channels]
 */
static void frame_cyclic_s_estimate_jacobian_en( const lion_frame_cyclic_s* const_o, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();

    lion_frame_cyclic_s* o = BLM_CLONE( lion_frame_cyclic_s, const_o );
    ASSERT( o->setup );

    bhvm_holor_adl_s* adl_en = BLM_CLONE( bhvm_holor_adl_s, en );
    bhvm_holor_adl_s* adl_ex = BLM_CREATE( bhvm_holor_adl_s );
    bhvm_holor_adl_s* adl_rf = BLM_CREATE( bhvm_holor_adl_s );
    lion_frame_cyclic_s_run_ap_adl_flat( o, adl_en, adl_ex );
    bhvm_holor_adl_s_copy( adl_rf, adl_ex );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, adl_en->size );

    BFOR_SIZE( i, adl_en->size )
    {
        bhvm_holor_s* h_en = adl_en->data[ i ];
        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, adl_ex->size );

        BFOR_EACH( j, &h_en->v )
        {
            f3_t v_en = bhvm_value_s_get_f3( &h_en->v, j );
            bhvm_value_s_set_f3( &h_en->v, j, v_en + epsilon );
            lion_frame_cyclic_s_run_ap_adl_flat( o, adl_en, adl_ex );
            BFOR_SIZE( k, adl_ex->size )
            {
                bhvm_holor_s* h_ex = adl_ex->data[ k ];
                bhvm_holor_s* h_rf = adl_rf->data[ k ];

                if( !jac_adl->data[ k ] ) jac_adl->data[ k ] = bhvm_holor_s_create();
                bhvm_holor_s* h_jc = jac_adl->data[ k ];
                if( h_jc->v.size == 0 )
                {
                    bhvm_shape_s_set_data_na( &h_jc->s, 2, h_ex->v.size, h_en->v.size );
                    bhvm_holor_s_set_type( h_jc, TYPEOF_f3_t );
                    bhvm_holor_s_fit_size( h_jc );
                }

                BFOR_EACH( l, &h_ex->v )
                {
                    f3_t v_ex = bhvm_value_s_get_f3( &h_ex->v, l );
                    f3_t v_rf = bhvm_value_s_get_f3( &h_rf->v, l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    bhvm_value_s_set_f3( &h_jc->v, j * h_jc->s.data[ 0 ] + l, v_gr );
                }
            }
            bhvm_value_s_set_f3( &h_en->v, j, v_en );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

lion_eval_frame_result_s* lion_eval_frame_cyclic_s_run( const lion_eval_frame_cyclic_s* o, lion_eval_frame_result_s* result )
{
    BLM_INIT();

    if( o->param.name.size > 0 && o->param.verbosity >= 2 ) bcore_sink_a_push_fa( o->param.log, "#<sc_t>:\n", o->param.name.sc );

    if( !o->param.src ) ERR_fa( "Source missing." );

    lion_frame_s* frame = BLM_CREATE( lion_frame_s );
    if( o->param.verbosity >= 20 ) frame->log = bcore_fork( o->param.log );

    bcore_source* source = NULL;

    switch( *(aware_t*)o->param.src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = BLM_A_PUSH( bcore_file_open_source_path( ( const bcore_file_path_s* )o->param.src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = BLM_A_PUSH( bcore_source_string_s_create_from_string( ( const st_s* )o->param.src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->param.src ) );
        }
        break;
    }

    const bhvm_holor_adl_s* adl_ap_en = o->param.in;
          bhvm_holor_adl_s* adl_ap_ex1 = BLM_CREATE( bhvm_holor_adl_s );
          bhvm_holor_adl_s* adl_ap_ex2 = BLM_CREATE( bhvm_holor_adl_s );

    lion_frame_s_setup_from_source_adl( frame, source, adl_ap_en );

    sz_t unroll_size = adl_ap_en->size / frame->size_en;
    ASSERT( unroll_size * frame->size_en == adl_ap_en->size );

    lion_frame_cyclic_s* frame_cyclic0 = BLM_CREATE( lion_frame_cyclic_s );
    lion_frame_cyclic_s_setup_from_frame( frame_cyclic0, frame, unroll_size );

    /// test frame recovery/copying
    if( o->param.recovery_test)
    {
        lion_frame_cyclic_s* frame_cyclic1 = BLM_CREATE( lion_frame_cyclic_s );
        bcore_bin_ml_a_copy( frame_cyclic1, frame_cyclic0 );
        frame_cyclic0 = frame_cyclic1;
    }

    lion_frame_cyclic_s* frame_cyclic  = BLM_CLONE( lion_frame_cyclic_s, frame_cyclic0 );

    lion_frame_cyclic_s_run_ap_adl_flat( frame_cyclic, adl_ap_en, adl_ap_ex1 );
    bhvm_holor_adl_s_set_size( adl_ap_ex2, adl_ap_ex1->size );
    BFOR_EACH( i, adl_ap_ex1 ) adl_ap_ex2->data[ i ] = bhvm_holor_s_create();

    sz_t size_en = frame->size_en;
    sz_t size_ex = frame->size_ex;

    for( sz_t i = 0; i < unroll_size; i++ )
    {
        ASSERT( adl_ap_en ->size >= ( i + 1 ) * size_en );
        ASSERT( adl_ap_ex2->size >= ( i + 1 ) * size_ex );
        lion_frame_s_run_ap( frame, ( const bhvm_holor_s** ) adl_ap_en->data + i * size_en, size_en, adl_ap_ex2->data + i * size_ex, size_ex );
    }

    if( o->param.verbosity >= 10 )
    {
        bcore_sink_a_push_fa( o->param.log, "Begin microcode disassembly\n\n" );
        lion_frame_cyclic_s_disassemble_to_sink( frame_cyclic, o->param.log );
        bcore_sink_a_push_fa( o->param.log, "End microcode disassembly\n\n" );
    }

    BFOR_EACH( i, adl_ap_ex1 )
    {
        bhvm_holor_s* h_ex1 = adl_ap_ex1->data[ i ];
        bhvm_holor_s* h_ex2 = adl_ap_ex2->data[ i ];
        if( o->param.out && o->param.out->size > i )
        {
            bhvm_holor_s* h_out = o->param.out->data[ i ];
            bl_t shape_dev = !bhvm_shape_s_is_equal( &h_out->s, &h_ex1->s );
            bl_t value_dev = shape_dev || ( bhvm_value_s_fdev_equ( &h_out->v, &h_ex1->v ) > o->param.max_dev );
            if( shape_dev || value_dev )
            {
                st_s* msg = BLM_CREATE( st_s );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "#<sc_t> deviation at output holor '#<sz_t>':", shape_dev ? "Shape" : "Value", i );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{frame_cyclic output} " );
                bhvm_holor_s_brief_to_sink( h_ex1, (bcore_sink*)msg );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{expected output} " );
                bhvm_holor_s_brief_to_sink( h_out, (bcore_sink*)msg );
                ERR_fa( "#<st_s*>\n", msg );
            }
        }
        else
        {
            if( o->param.verbosity >= 0 )
            {
                bcore_sink_a_push_fa( o->param.log, "Output #pl5 {[#<sz_t>]}: ", i );
                bhvm_holor_s_brief_to_sink( h_ex1, o->param.log );
                bcore_sink_a_push_fa( o->param.log, "\n" );
            }
        }

        {
            bl_t shape_dev = !bhvm_shape_s_is_equal( &h_ex2->s, &h_ex1->s );
            bl_t value_dev = shape_dev || ( bhvm_value_s_fdev_equ( &h_ex2->v, &h_ex1->v ) > o->param.max_dev );
            if( shape_dev || value_dev )
            {
                st_s* msg = BLM_CREATE( st_s );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "#<sc_t> deviation at output holor '#<sz_t>':", shape_dev ? "Shape" : "Value", i );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Output (frame_cyclic)} " );
                bhvm_holor_s_brief_to_sink( h_ex1, (bcore_sink*)msg );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Output (frame)} " );
                bhvm_holor_s_brief_to_sink( h_ex2, (bcore_sink*)msg );
                ERR_fa( "#<st_s*>\n", msg );
            }
        }

    }

    if( o->param.jacobian_test )
    {
        u2_t rval = 1234;

        if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "\nJacobian DP Test:\n" );

        bhvm_holor_adl_s* adl_dp_en = BLM_CLONE( bhvm_holor_adl_s, adl_ap_en  );
        bhvm_holor_adl_s* adl_dp_ex = BLM_CLONE( bhvm_holor_adl_s, adl_ap_ex1 );

        BFOR_EACH( i, adl_dp_ex )
        {
            bhvm_value_s_set_random( &adl_dp_ex->data[ i ]->v, 1.0, -1, 1, &rval );
            if( o->param.verbosity >= 10 )
            {
                bcore_sink_a_push_fa( o->param.log, "Gradient exc #<sz_t>: ", i );
                bhvm_holor_s_to_sink_nl( adl_dp_ex->data[ i ], o->param.log );
            }
        }

        lion_frame_cyclic_s_run_dp_adl_flat( frame_cyclic, adl_dp_ex, adl_dp_en );

        if( o->param.verbosity >= 10 )
        {
            BFOR_EACH( i, adl_dp_en )
            {
                bcore_sink_a_push_fa( o->param.log, "Gradient enc #<sz_t>: ", i );
                bhvm_holor_s_to_sink_nl( adl_dp_en->data[ i ], o->param.log );
            }
        }

        sz_t size_en = adl_dp_en->size;
        sz_t size_ex = adl_dp_ex->size;
        bhvm_holor_mdl_s* mdl_jc = BLM_CREATE( bhvm_holor_mdl_s );

        /// testing entry channels
        if( size_en )
        {
            if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "\nTesting #<sz_t> composite entry channels:\n", adl_ap_en->size );

            frame_cyclic_s_estimate_jacobian_en( frame_cyclic, adl_ap_en, o->param.epsilon, mdl_jc );

            BFOR_SIZE( i, size_en )
            {
                BLM_INIT();
                if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "enc #<sz_t>:\n", i );

                bhvm_holor_s* dp_en1 = adl_dp_en->data[ i ];
                bhvm_holor_s* dp_en2 = bhvm_holor_s_copy_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_en1 );
                bhvm_value_s_zro( &dp_en2->v );

                BFOR_SIZE( j, size_ex )
                {
                    BLM_INIT();
                    if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "exc #<sz_t>:\n", j );

                    bhvm_holor_s* h_jc = mdl_jc->data[ i ]->data[ j ];
                    if( o->param.verbosity >= 10 )
                    {
                        bcore_sink_a_push_fa( o->param.log, "Jacobian: " );
                        bhvm_holor_s_to_sink_nl( h_jc, o->param.log );
                    }

                    bhvm_holor_s* dp_ex1 = adl_dp_ex->data[ j ];
                    bhvm_holor_s* dp_ex2 = bhvm_holor_s_fork_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_ex1 );
                    lion_frame_sc_run_ap( "( y <- a, b, c ) { y = a + b ** c; }", ( const bhvm_holor_s*[] ) { dp_en2, h_jc, dp_ex2 }, 3, &dp_en2, 1 );
                    BLM_DOWN();
                }

                f3_t dev = bhvm_value_s_fdev_equ( &dp_en1->v, &dp_en2->v );
                bl_t error = dev > o->param.max_dev;

                if( error || o->param.verbosity >= 10 )
                {
                    st_s* st = BLM_CREATE( st_s );
                    st_s_push_fa( st, "dp-channel: #<sz_t>", i );
                    st_s_push_fa( st, ", dev: #<f3_t>", dev );
                    st_s_push_fa( st, "\ngradient (dp)          : " );
                    bhvm_holor_s_to_sink( dp_en1, ( bcore_sink* )st );
                    st_s_push_fa( st, "\ngradient (via jacobian): " );
                    bhvm_holor_s_to_sink( dp_en2, ( bcore_sink* )st );
                    st_s_push_fa( st, "\n" );
                    if( error )
                    {
                        st_s_push_fa( &result->msg, "\n#<sc_t>:", o->param.name.sc );
                        st_s_push_fa( &result->msg, "\nJacobian test failure:\n#<sc_t>\n", st->sc );
                        result->error = true;
                        BLM_RETURNV( lion_eval_frame_result_s*, result );
                    }
                    else
                    {
                        bcore_sink_a_push_fa( o->param.log, "#<sc_t>", st->sc );
                    }
                }

                BLM_DOWN();
            }
        }
    }

    BLM_RETURNV( lion_eval_frame_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_lion_eval_frame

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_eval_frame_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_eval_frame" ) ) )
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


