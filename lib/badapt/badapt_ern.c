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

#include "bcore_std.h"
#include "bmath_std.h"
#include "bmath_plot.h"
#include "badapt_ern.h"
#include "badapt_trainer.h"
#include "badapt_dev_problem.h"

/**********************************************************************************************************************/
// badapt_ern_s

// ---------------------------------------------------------------------------------------------------------------------
#ifdef TYPEOF_badapt_ern_s
sz_t badapt_ern_s_get_in_size(  const badapt_ern_s* o )
{
    return o->size_input;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_ern_s_get_out_size( const badapt_ern_s* o )
{
    return o->size_output;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_get_dynamics( const badapt_ern_s* o, badapt_dynamics_s* dynamics )
{
    badapt_dynamics_s_copy( dynamics, &o->dynamics );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_set_dynamics( badapt_ern_s* o, const badapt_dynamics_s* dynamics )
{
    badapt_dynamics_s_copy( &o->dynamics, dynamics );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_arc_to_sink( const badapt_ern_s* o, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#<sc_t>\n",  ifnameof( *(aware_t*)o ) );
    bcore_sink_a_push_fa( sink, "size input:  #<sz_t>\n", o->size_input );
    bcore_sink_a_push_fa( sink, "size hidden: #<sz_t>\n", o->wgt_input.rows );
    bcore_sink_a_push_fa( sink, "size output: #<sz_t>\n", o->size_output );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_minfer( badapt_ern_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    ASSERT( in->size == o->size_input );

    bmath_vf3_s_copy( &o->vec_input, in );
    bmath_vf3_s_swapr( &o->vec_hidden, &o->vec_recur );
    bmath_vf3_s_set_size( &o->vec_hidden, o->wgt_input.rows );

    if( o->vec_recur.size > 0 )
    {
        bmath_mf3_s_mul_vec(     &o->wgt_recur, &o->vec_recur, &o->vec_hidden );
        bmath_mf3_s_mul_vec_add( &o->wgt_input, &o->vec_input, &o->vec_hidden, &o->vec_hidden );
    }
    else
    {
        bmath_mf3_s_mul_vec( &o->wgt_input, &o->vec_input, &o->vec_hidden );
    }

    badapt_activator_a_infer( o->activator_hidden, &o->vec_hidden, &o->vec_hidden );

    bmath_vf3_s_set_size( &o->vec_output, o->wgt_hidden.rows );
    bmath_mf3_s_mul_vec( &o->wgt_hidden, &o->vec_hidden, &o->vec_output );
    badapt_activator_a_infer( o->activator_output, &o->vec_output, &o->vec_output );

    if( out ) bmath_vf3_s_cpy( &o->vec_output, out );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_bgrad( const badapt_ern_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    bmath_vf3_s* grad_output = bmath_vf3_s_create_set_size( o->wgt_hidden.rows );
    bmath_vf3_s* grad_hidden = bmath_vf3_s_create_set_size( o->wgt_input.rows );

    bmath_vf3_s_cpy( grad_out, grad_output );

    badapt_activator_a_adapt( o->activator_output, grad_output, grad_output, &o->vec_output, o->dynamics.epsilon );
    bmath_mf3_s_htp_mul_vec( &o->wgt_hidden, grad_output, grad_hidden );          // GH <- W^T * GO
    badapt_activator_a_adapt( o->activator_output, grad_hidden, grad_hidden, &o->vec_hidden, o->dynamics.epsilon );
    if( grad_in ) bmath_mf3_s_htp_mul_vec( &o->wgt_input, grad_hidden, grad_in ); // grad_in <- W^T * GH

    bmath_vf3_s_discard( grad_hidden );
    bmath_vf3_s_discard( grad_output );
}

// ---------------------------------------------------------------------------------------------------------------------

static void badapt_ern_s_update_wgt( const badapt_ern_s* o, const bmath_vf3_s* vec_in, bmath_mf3_s* w, const bmath_vf3_s* grad_out )
{
    assert( w->rows == grad_out->size );
    assert( w->cols == vec_in->size );

    f3_t l2_reg_factor = ( 1.0 - o->dynamics.lambda_l2  * o->dynamics.epsilon );
    f3_t l1_reg_offset = o->dynamics.lambda_l1 * o->dynamics.epsilon;

    for( sz_t i = 0; i < w->rows; i++ )
    {
        f3_t* wr = w->data + i * w->stride;
        f3_t gi = o->dynamics.epsilon * grad_out->data[ i ];
        for( sz_t j = 0; j < w->cols; j++ ) wr[ j ] = ( wr[ j ] + vec_in->data[ j ] * gi ) * l2_reg_factor;
        if( l1_reg_offset > 0 )
        {
            for( sz_t j = 0; j < w->cols; j++ ) wr[ j ] += ( wr[ j ] > 0 ) ? -l1_reg_offset : l1_reg_offset;
        }
    }

//    bmath_vf3_s_to_stdout( vec_in );
//    bmath_mf3_s_to_stdout( w );

    assert( !bmath_mf3_s_is_nan( w ) );

}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_bgrad_adapt( badapt_ern_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    bmath_vf3_s* grad_output = bmath_vf3_s_create_set_size( o->wgt_hidden.rows );
    bmath_vf3_s* grad_hidden = bmath_vf3_s_create_set_size( o->wgt_input.rows );

    bmath_vf3_s_cpy( grad_out, grad_output );

    badapt_activator_a_adapt( o->activator_output, grad_output, grad_output, &o->vec_output, o->dynamics.epsilon );
    bmath_mf3_s_htp_mul_vec( &o->wgt_hidden, grad_output, grad_hidden );          // GH <- W^T * GO
    badapt_ern_s_update_wgt( o, &o->vec_hidden, &o->wgt_hidden, grad_output );
    badapt_activator_a_adapt( o->activator_output, grad_hidden, grad_hidden, &o->vec_hidden, o->dynamics.epsilon );
    if( grad_in ) bmath_mf3_s_htp_mul_vec( &o->wgt_input, grad_hidden, grad_in ); // grad_in <- W^T * GH
    badapt_ern_s_update_wgt( o, &o->vec_input, &o->wgt_input, grad_hidden );
    if( o->vec_recur.size > 0 )
    {
        badapt_ern_s_update_wgt( o, &o->vec_recur, &o->wgt_recur, grad_hidden );
    }

    bmath_vf3_s_discard( grad_hidden );
    bmath_vf3_s_discard( grad_output );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// badapt_builder_ern_s

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_builder_ern_s_get_in_size( const badapt_builder_ern_s* o )
{
    return o->size_input;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_builder_ern_s_set_in_size( badapt_builder_ern_s* o, sz_t size )
{
    o->size_input = size;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_builder_ern_s_get_out_size( const badapt_builder_ern_s* o )
{
    return o->size_output;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_builder_ern_s_set_out_size( badapt_builder_ern_s* o, sz_t size )
{
    o->size_output = size;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* badapt_builder_ern_s_build( const badapt_builder_ern_s* o )
{
    ASSERT( o->size_input > 0 );
    ASSERT( o->size_output > 0 );

    BCORE_LIFE_INIT();

    u2_t random_state = o->random_seed;
    badapt_ern_s* ern = badapt_ern_s_create();

    ern->size_input  = o->size_input;
    ern->size_output = o->size_output;

    badapt_dynamics_s_copy( &ern->dynamics, &o->dynamics );

    bmath_mf3_s_set_size( &ern->wgt_input,  o->size_hidden, o->size_input );
    bmath_mf3_s_set_size( &ern->wgt_recur,  o->size_hidden, o->size_hidden );
    bmath_mf3_s_set_size( &ern->wgt_hidden, o->size_output, o->size_hidden );
    bmath_mf3_s_set_random( &ern->wgt_input,  false, false, 0, 1.0, -0.5, 0.5, &random_state );
    bmath_mf3_s_set_random( &ern->wgt_recur,  false, false, 0, 1.0, -0.02, 0.02, &random_state );
    bmath_mf3_s_set_random( &ern->wgt_hidden, false, false, 0, 1.0, -0.5, 0.5, &random_state );

    ern->activator_hidden = badapt_activator_a_clone( o->activator_hidden );
    ern->activator_output = badapt_activator_a_clone( o->activator_output );

    BCORE_LIFE_RETURN( ( badapt_adaptive* )ern );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// tests


void badapt_ern_s_run_training( badapt_supplier* problem, badapt_builder* builder, const badapt_trainer_batch_s* trainer )
{
    BCORE_LIFE_INIT();
    badapt_training_state* state = BCORE_LIFE_A_PUSH( badapt_trainer_batch_s_create_state( trainer ) );
    badapt_supplier_a_setup_builder( problem, builder );
    badapt_training_state_a_set_adaptive( state, BCORE_LIFE_A_PUSH( badapt_builder_a_build( builder ) ) );
    badapt_training_state_a_set_supplier( state, problem );
    badapt_training_state_a_set_guide( state, ( badapt_guide* )BCORE_LIFE_A_PUSH( badapt_guide_std_s_create() ) );
    badapt_adaptive_a_arc_to_sink( badapt_training_state_a_get_adaptive( state ), BCORE_STDOUT );
    badapt_trainer_batch_s_run( trainer, ( badapt_training_state* )state );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_ern_s_test_recurrent_kjv()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_recurrent_kjv_s, problem );
    BCORE_LIFE_CREATE( badapt_builder_ern_s,   builder );
    BCORE_LIFE_CREATE( badapt_trainer_batch_s, trainer );

    builder->size_hidden = 32;
    builder->dynamics.epsilon   = 0.0001;
    builder->dynamics.lambda_l2 = 100;
//    builder->dynamics.lambda_l1 = 0.0001;

    builder->activator_hidden = badapt_activator_create_from_names( "bias", "leaky_relu" );
    builder->activator_output = badapt_activator_create_from_names( "bias", "tanh" );

    trainer->fetch_cycles_per_iteration = 10;
    trainer->batch_cycles_per_fetch = 1;
    trainer->max_iterations = 100;

    badapt_ern_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

#endif

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t badapt_ern_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_ern" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_precoder:
        {
            bcore_precoder_compile( "badapt_dev_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


