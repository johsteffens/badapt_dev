/** Copyright 2019 Johannes Bernhard Steffens
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

#include "badapt_test.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

void badapt_adaptive_a_test_sine_random( const badapt_adaptive* const_o )
{
    BCORE_LIFE_INIT();

    badapt_adaptive* o = BCORE_LIFE_A_PUSH( bcore_inst_a_clone( ( bcore_inst* )const_o ) );
    badapt_adaptive_a_set_in_size(  o, 32 );
    badapt_adaptive_a_set_out_size( o, 1 );
    badapt_adaptive_a_reset( o );
    badapt_adaptive_a_setup( o );
    badapt_adaptive_a_arc_to_sink( o, BCORE_STDOUT );

    // Learn differentiating between a sine wave of arbitrary amplitude and frequency from
    // a random walk curve.
    BCORE_LIFE_CREATE( bcore_arr_sr_s, pos_set_trn );
    BCORE_LIFE_CREATE( bcore_arr_sr_s, neg_set_trn );
    BCORE_LIFE_CREATE( bcore_arr_sr_s, pos_set_tst );
    BCORE_LIFE_CREATE( bcore_arr_sr_s, neg_set_tst );

    sz_t samples = 10000;
    u2_t rval = 123;
    for( sz_t i = 0; i < samples * 2; i++ )
    {
        sz_t input_size = badapt_adaptive_a_get_in_size( o );
        bmath_vf3_s* pos_vec = bmath_vf3_s_create();
        bmath_vf3_s* neg_vec = bmath_vf3_s_create();
        bmath_vf3_s_set_size( pos_vec, input_size );
        bmath_vf3_s_set_size( neg_vec, input_size );

        f3_t omega = 1.0 * f3_pi() * f3_rnd_pos( &rval );
        f3_t amplitude = 4.0 * f3_rnd_pos( &rval );

        f3_t rwalker = f3_rnd_sym( &rval );

        for( sz_t i = 0; i < input_size; i++ )
        {
            rwalker += f3_rnd_sym( &rval );
            f3_t vp = sin( omega * i ) * amplitude;
            f3_t vr = rwalker;
            f3_t vn = vr;

            pos_vec->data[ i ] = vp;
            neg_vec->data[ i ] = vn;
        }

        if( ( i & 1 ) == 0 )
        {
            bcore_arr_sr_s_push_sr( pos_set_trn, sr_asd( pos_vec ) );
            bcore_arr_sr_s_push_sr( neg_set_trn, sr_asd( neg_vec ) );
        }
        else
        {
            bcore_arr_sr_s_push_sr( pos_set_tst, sr_asd( pos_vec ) );
            bcore_arr_sr_s_push_sr( neg_set_tst, sr_asd( neg_vec ) );
        }
    }

    sz_t epochs = 30;
    f3_t learn_step = 0.0001;
    f3_t decay = 0.0001 * learn_step;
    f3_t pos_tgt = 0.9;
    f3_t neg_tgt = -pos_tgt;

    badapt_adaptive_a_set_step(  o, learn_step );
    badapt_adaptive_a_set_regularization( o, TYPEOF_badapt_regularization_l2, decay );

    for( sz_t i = 0; i < epochs; i++ )
    {
        f3_t err = 0;
        for( sz_t j = 0; j < samples; j++ )
        {
            const bmath_vf3_s* pos_vec = pos_set_trn->data[ j ].o;
            const bmath_vf3_s* neg_vec = neg_set_trn->data[ j ].o;
            f3_t pos_est = badapt_adaptive_a_adapt_l2_f3( o, pos_vec, pos_tgt );
            f3_t neg_est = badapt_adaptive_a_adapt_l2_f3( o, neg_vec, neg_tgt );
            err += f3_sqr( pos_est - pos_tgt );
            err += f3_sqr( neg_est - neg_tgt );
        }

        err = f3_srt( err / ( samples * 2 ) );

        bcore_msg_fa( "#pl6 {#<sz_t>}: err = #<f3_t>\n", i, err );
    }

    bcore_sink_buffer_s* sink_buf = BCORE_LIFE_A_PUSH( bcore_sink_buffer_s_create() );
    bcore_source_buffer_s* source_buf = BCORE_LIFE_A_PUSH( bcore_source_buffer_s_create() );
    bcore_bin_ml_a_to_sink( o, ( bcore_sink* )sink_buf );

    source_buf->data = sink_buf->data;
    source_buf->size = sink_buf->size;

    badapt_adaptive* o_tst = BCORE_LIFE_A_PUSH( bcore_inst_t_create( *( aware_t* )o ) );
    bcore_bin_ml_a_from_source( o_tst, ( bcore_source* )source_buf );
    badapt_adaptive_a_setup( o_tst );

    {
        f3_t err = 0;
        for( sz_t j = 0; j < samples; j++ )
        {
            const bmath_vf3_s* pos_vec = pos_set_tst->data[ j ].o;
            const bmath_vf3_s* neg_vec = neg_set_tst->data[ j ].o;
            f3_t pos_est = badapt_adaptive_a_infer_f3( o_tst, pos_vec );
            f3_t neg_est = badapt_adaptive_a_infer_f3( o_tst, neg_vec );
            err += f3_sqr( pos_est - pos_tgt );
            err += f3_sqr( neg_est - neg_tgt );
        }

        err = f3_srt( err / ( samples * 2 ) );

        bcore_msg_fa( "tst_err = #<f3_t>\n", err );
    }

    BCORE_LIFE_RETURN();
}


/**********************************************************************************************************************/

vd_t badapt_test_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_test" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            return NULL;
        }
        break;

        case TYPEOF_precoder:
        {
            bcore_precoder_compile( "badapt_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

/**********************************************************************************************************************/

