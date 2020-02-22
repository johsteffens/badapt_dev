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

#include "lion_net_eval.h"

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

/** Estimates jacobians for entry and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [in-channels][out-channels]
 */
void lion_frame_s_estimate_jacobian_en( const lion_frame_s* const_o, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();
    lion_frame_s* o = BLM_CLONE( lion_frame_s, const_o );

    bhvm_holor_adl_s* ref = BLM_CREATE( bhvm_holor_adl_s );
    bhvm_holor_adl_s_set_size( ref, o->idx_ap_ex->size );
    BFOR_EACH( k, o->idx_ap_ex ) ref->data[ k ] = bhvm_holor_s_clone( lion_frame_s_get_ap_ex( o, k ) );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, o->idx_ap_en->size );

    BFOR_EACH( i, o->idx_ap_en )
    {
        bhvm_holor_s* h_en = lion_frame_s_get_ap_en( o, i );

        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, o->idx_ap_ex->size );

        BFOR_EACH( j, &h_en->v )
        {
            f3_t v_en = bhvm_value_s_get_f3( &h_en->v, j );
            bhvm_value_s_set_f3( &h_en->v, j, v_en + epsilon );
            bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );
            BFOR_EACH( k, o->idx_ap_ex )
            {
                bhvm_holor_s* h_ex = lion_frame_s_get_ap_ex( o, k );
                bhvm_holor_s* h_rf = ref->data[ k ];

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
void lion_frame_s_estimate_jacobian_ada( const lion_frame_s* const_o, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();
    lion_frame_s* o = BLM_CLONE( lion_frame_s, const_o );

    bhvm_holor_adl_s* ref = BLM_CREATE( bhvm_holor_adl_s );
    bhvm_holor_adl_s_set_size( ref, o->idx_ap_ex->size );
    BFOR_EACH( k, o->idx_ap_ex ) ref->data[ k ] = bhvm_holor_s_clone( lion_frame_s_get_ap_ex( o, k ) );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, o->idx_ap_ada->size );

    BFOR_EACH( i, o->idx_ap_ada )
    {
        bhvm_holor_s* h_ada = lion_frame_s_get_ap_ada( o, i );

        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, o->idx_ap_ex->size );

        BFOR_EACH( j, &h_ada->v )
        {
            f3_t v_ada = bhvm_value_s_get_f3( &h_ada->v, j );
            bhvm_value_s_set_f3( &h_ada->v, j, v_ada + epsilon );
            bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );
            BFOR_EACH( k, o->idx_ap_ex )
            {
                bhvm_holor_s* h_ex = lion_frame_s_get_ap_ex( o, k );
                bhvm_holor_s* h_rf = ref->data[ k ];

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

lion_net_eval_result_s* lion_net_eval_frame_s_run( const lion_net_eval_frame_s* o, lion_net_eval_result_s* result )
{
    BLM_INIT();

    if( o->param.name.size > 0 && o->param.verbosity >= 2 ) bcore_sink_a_push_fa( o->param.log, "#<sc_t>:\n", o->param.name.sc );

    if( !o->param.src ) ERR_fa( "Source missing." );

    lion_frame_s* frame = BLM_CREATE( lion_frame_s );
    frame->unrolled_cycles = o->unrolled_cycles;

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

    if( o->param.log && o->param.verbosity >= 10 )
    {
        bcore_sink_a_attach( &frame->mcode_log, bcore_fork( o->param.log ) );
        bcore_sink_a_push_fa( o->param.log, "Begin microcode disassembly\n\n" );
    }
    lion_frame_s_setup_from_source_adl( frame, source, adl_ap_en );
    if( o->param.log && o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "End microcode disassembly\n\n" );

    for( sz_t i = 0; i < o->recurrent_cycles; i++ ) lion_frame_s_run_ap_adl( frame, adl_ap_en, adl_ap_ex );

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
            bcore_sink_a_push_fa( o->param.log, "Frame out channel '#<sz_t>':\n", i );
            bhvm_holor_s_to_sink_nl( h_hbo, o->param.log );
        }
    }

    u2_t rval = 1234;

    if( o->jacobian_test )
    {
        if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "\nJacobian DP Test:\n" );

        bhvm_holor_adl_s* adl_dp_en = BLM_CLONE( bhvm_holor_adl_s, adl_ap_en );
        bhvm_holor_adl_s* adl_dp_ex = BLM_CLONE( bhvm_holor_adl_s, adl_ap_ex );

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

            lion_frame_s_estimate_jacobian_en( frame, o->param.epsilon, mdl_jc );

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
                    lion_frame_sc_run_ap( "( y <- a, b, c ) { y = a + b ** c; }", ( const bhvm_holor_s*[] ) { dp_en2, h_jc, dp_ex2 }, &dp_en2 );
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
                        BLM_RETURNV( lion_net_eval_result_s*, result );
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

            lion_frame_s_estimate_jacobian_ada( frame, o->param.epsilon, mdl_jc );
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
                    lion_frame_sc_run_ap( "( y <- a, b, c ) { y = a + b ** c; }", ( const bhvm_holor_s*[] ) { dp_ada2, h_jc, dp_ex2 }, &dp_ada2 );
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
                        BLM_RETURNV( lion_net_eval_result_s*, result );
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

    BLM_RETURNV( lion_net_eval_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_net_eval_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_net_eval" ) ) )
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


