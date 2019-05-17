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
#include "badapt_mlp.h"
#include "badapt_training.h"
#include "badapt_problem.h"

/**********************************************************************************************************************/
// badapt_mlp_s

// ---------------------------------------------------------------------------------------------------------------------
#ifdef TYPEOF_badapt_mlp_s
sz_t badapt_mlp_s_get_in_size(  const badapt_mlp_s* o )
{
    return o->arr_layer.arr_size > 0 ? o->arr_layer.arr_data[ 0 ].input_size : 0;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_mlp_s_get_out_size( const badapt_mlp_s* o )
{
    return o->arr_layer.arr_size > 0 ? o->arr_layer.arr_data[ o->arr_layer.arr_size - 1 ].kernels : 0;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_get_dynamics( const badapt_mlp_s* o, badapt_dynamics_s* dynamics )
{
    badapt_dynamics_s_copy( dynamics, &o->dynamics );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_set_dynamics( badapt_mlp_s* o, const badapt_dynamics_s* dynamics )
{
    badapt_dynamics_s_copy( &o->dynamics, dynamics );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_arc_to_sink( const badapt_mlp_s* o, bcore_sink* sink )
{
    sz_t pad = 24;
    sz_t weights = 0;
    sz_t ops = 0;
    for( sz_t i = 0; i < o->arr_layer.arr_size; i++ )
    {
        const bmath_mf3_s* w = &o->arr_layer.arr_data[ i ].wgt;
        weights += w->size;
        ops     += w->size;
    }

    bcore_sink_a_push_fa( sink, "#pn.{input size } #pl3 {#<sz_t>}\n", pad, badapt_mlp_s_get_in_size( o ) );
    bcore_sink_a_push_fa( sink, "#pn.{output size } #pl3 {#<sz_t>}\n", pad, badapt_mlp_s_get_out_size( o ) );

    bcore_sink_a_push_fa( sink, "#pn.{layers } #pl3 {#<sz_t>}\n",  pad, o->arr_layer.arr_size );
    bcore_sink_a_push_fa( sink, "#pn.{weights } #pl3 {#<sz_t>}\n", pad, weights );
    bcore_sink_a_push_fa( sink, "#pn.{ops } #pl3 {#<sz_t>}\n",     pad, ops );

    for( sz_t i = 0; i < o->arr_layer.arr_size; i++ )
    {
        const badapt_mlp_layer_s* layer = &o->arr_layer.arr_data[ i ];

        const bmath_mf3_s* w = &layer->wgt;
        const bmath_vf3_s* b = &layer->out;
        st_s* st_activation = st_s_create();

        st_s_push_fa( st_activation, "#<sc_t>", ifnameof( *( aware_t* )layer->act ) );
        st_s_push_fa( st_activation, " : #<sc_t>", ifnameof( *( aware_t* )badapt_activator_a_get_activation( layer->act ) ) );

        bcore_sink_a_push_fa( sink,
                              "layer #pl2 {#<sz_t>}:"
                              " a(#pl2 {#<sz_t>})"
                              " w(#pl2 {#<sz_t>} x #pl2 {#<sz_t>})"
                              " b(#pl2 {#<sz_t>})"
                              " #<sc_t>"
                              "\n",
                              i, layer->input_size, w->rows, w->cols, b->size, st_activation->sc );

        st_s_discard( st_activation );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_infer( const badapt_mlp_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    if( o->arr_layer.arr_size == 0 ) ERR_fa( "Network was not setup. Call setup() first." );
    bmath_vf3_s a, b;
    bmath_vf3_s_init( &a );
    bmath_vf3_s_init( &b );
    bmath_vf3_s_set_space( &a, o->max_buffer_size );
    bmath_vf3_s_set_space( &b, o->max_buffer_size );

    bmath_vf3_s_copy( &a, in );

    for( sz_t i = 0; i < o->arr_layer.arr_size; i++ )
    {
        badapt_mlp_layer_s* layer = &o->arr_layer.arr_data[ i ];
        const bmath_mf3_s* w = &layer->wgt;
        b.size = w->rows;
        bmath_mf3_s_mul_vec( w, &a, &b );       // b = w * a
        badapt_activator_a_infer( layer->act, &b, &b );
        bmath_vf3_s_swapr( &a, &b );
    }

    if( out ) bmath_vf3_s_cpy( &a, out );

    bmath_vf3_s_down( &a );
    bmath_vf3_s_down( &b );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_minfer( badapt_mlp_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    if( o->arr_layer.arr_size == 0 ) ERR_fa( "Network was not setup. Call setup() first." );
    bmath_vf3_s_cpy( in, &o->in );
    bmath_vf3_s* b = NULL;
    for( sz_t i = 0; i < o->arr_layer.arr_size; i++ )
    {
        badapt_mlp_layer_s* layer = &o->arr_layer.arr_data[ i ];
        const bmath_vf3_s* a = ( i > 0 ) ? &o->arr_layer.arr_data[ i - 1 ].out : &o->in;
        b = &layer->out;
        const bmath_mf3_s* w = &layer->wgt;
        if( b->size != w->rows ) bmath_vf3_s_set_size( b, w->rows );

        bmath_mf3_s_mul_vec( w, a, b );       // b = w * a
        badapt_activator_a_infer( layer->act, b, b );
    }
    if( out ) bmath_vf3_s_cpy( b, out );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_bgrad( const badapt_mlp_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    bmath_vf3_s ga, gb;
    bmath_vf3_s_init( &ga );
    bmath_vf3_s_init( &gb );
    bmath_vf3_s_set_space( &ga, o->max_buffer_size );
    bmath_vf3_s_set_space( &gb, o->max_buffer_size );
    bmath_vf3_s_copy( &gb, grad_out );

    for( sz_t i = o->arr_layer.arr_size - 1; i >= 0; i-- )
    {
        badapt_mlp_layer_s* layer = &o->arr_layer.arr_data[ i ];
        const bmath_vf3_s* b = &layer->out;
        const bmath_mf3_s* w = &layer->wgt;
        ga.size = w->cols;
        badapt_activator_a_bgrad( layer->act, &gb, &gb, b );
        bmath_mf3_s_htp_mul_vec( w, &gb, &ga );          // GA <- W^T * GB
        bmath_vf3_s_swapr( &ga, &gb );
    }

    if( grad_in ) bmath_vf3_s_cpy( &gb, grad_in );

    bmath_vf3_s_down( &ga );
    bmath_vf3_s_down( &gb );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_bgrad_adapt( badapt_mlp_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    bmath_vf3_s ga, gb;
    bmath_vf3_s_init( &ga );
    bmath_vf3_s_init( &gb );
    bmath_vf3_s_set_space( &ga, o->max_buffer_size );
    bmath_vf3_s_set_space( &gb, o->max_buffer_size );
    bmath_vf3_s_copy( &gb, grad_out );

    for( sz_t i = o->arr_layer.arr_size - 1; i >= 0; i-- )
    {
        badapt_mlp_layer_s* layer = &o->arr_layer.arr_data[ i ];
        const bmath_vf3_s* a = ( i > 0 ) ? &o->arr_layer.arr_data[ i - 1 ].out : &o->in;
        const bmath_vf3_s* b = &o->arr_layer.arr_data[ i ].out;
              bmath_mf3_s* w = &layer->wgt;

        ga.size = w->cols;

        badapt_activator_a_adapt( layer->act, &gb, &gb, b, o->dynamics.epsilon );
        bmath_mf3_s_htp_mul_vec( w, &gb, &ga );          // GA <- W^T * GB

        f3_t l2_reg_factor = ( 1.0 - o->dynamics.lambda_l2  * o->dynamics.epsilon );
        f3_t l1_reg_offset = o->dynamics.lambda_l1 * o->dynamics.epsilon;

        for( sz_t i = 0; i < w->rows; i++ )
        {
            f3_t* wr = w->data + i * w->stride;
            f3_t gi = o->dynamics.epsilon * gb.data[ i ];
            for( sz_t j = 0; j < w->cols; j++ ) wr[ j ] = ( wr[ j ] + a->data[ j ] * gi ) * l2_reg_factor;
            if( l1_reg_offset > 0 )
            {
                for( sz_t j = 0; j < w->cols; j++ ) wr[ j ] += ( wr[ j ] > 0 ) ? -l1_reg_offset : l1_reg_offset;
            }
        }

        bmath_vf3_s_swapr( &ga, &gb );
    }

    if( grad_in ) bmath_vf3_s_cpy( &gb, grad_in );

    bmath_vf3_s_down( &ga );
    bmath_vf3_s_down( &gb );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// badapt_builder_mlp_funnel_s

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_builder_mlp_funnel_s_get_in_size( const badapt_builder_mlp_funnel_s* o )
{
    return o->input_size;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_builder_mlp_funnel_s_set_in_size( badapt_builder_mlp_funnel_s* o, sz_t size )
{
    o->input_size = size;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_builder_mlp_funnel_s_get_out_size( const badapt_builder_mlp_funnel_s* o )
{
    return o->output_kernels;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_builder_mlp_funnel_s_set_out_size( badapt_builder_mlp_funnel_s* o, sz_t size )
{
    o->output_kernels = size;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* badapt_builder_mlp_funnel_s_build( const badapt_builder_mlp_funnel_s* o )
{
    ASSERT( o->layers >= 2 );
    ASSERT( o->input_size     > 0 );
    ASSERT( o->output_kernels > 0 );

    BCORE_LIFE_INIT();

    u2_t random_state = o->random_seed;
    badapt_mlp_s* mlp = badapt_mlp_s_create();
    badapt_mlp_arr_layer_s_set_size( &mlp->arr_layer, o->layers );

    f3_t kernels = o->input_kernels;

    const badapt_mlp_layer_s* prev_layer = NULL;

    // first layer
    {
        badapt_mlp_layer_s* layer = &mlp->arr_layer.arr_data[ 0 ];
        layer->input_size = o->input_size;
        layer->kernels = lrint( kernels );
        prev_layer = layer;
    }

    for( sz_t i = 1; i < o->layers - 1; i++ )
    {
        kernels *= ( 1.0 + o->kernels_rate );
        badapt_mlp_layer_s* layer = &mlp->arr_layer.arr_data[ i ];
        layer->input_size = prev_layer->kernels;
        layer->kernels = lrint( kernels );
        prev_layer = layer;
    }

    // last layer
    {
        badapt_mlp_layer_s* layer = &mlp->arr_layer.arr_data[ o->layers - 1 ];
        layer->input_size = prev_layer->kernels;
        layer->kernels = o->output_kernels;
    }

    sz_t max_buffer_size = 0;

    // set up matrix and activator
    for( sz_t i = 0; i < o->layers; i++ )
    {
        badapt_mlp_layer_s* layer = &mlp->arr_layer.arr_data[ i ];
        bmath_mf3_s_set_size( &layer->wgt, layer->kernels, layer->input_size );
        bmath_mf3_s_set_random( &layer->wgt, false, false, 0, 1.0, -0.5, 0.5, &random_state );
        layer->act = badapt_activator_a_clone( badapt_arr_layer_activator_s_get_activator( &o->arr_layer_activator, i, o->layers ) );
        badapt_activator_a_setup( layer->act );
        max_buffer_size = sz_max( max_buffer_size, layer->input_size );
        max_buffer_size = sz_max( max_buffer_size, layer->kernels );
    }

    mlp->max_buffer_size = max_buffer_size;

    bmath_vf3_s_set_size( &mlp->in, o->input_size );

    badapt_dynamics_s_copy( &mlp->dynamics, &o->dynamics ); //TODO: activate

    BCORE_LIFE_RETURN( ( badapt_adaptive* )mlp );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_run_training( badapt_supplier* problem, badapt_builder* builder, const badapt_trainer_s* trainer )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_trainer_state_s,       state );
    BCORE_LIFE_CREATE( badapt_training_guide_std_s,  guide );
    badapt_supplier_a_setup_builder( problem, builder );
    state->adaptive = badapt_builder_a_build( builder );
    badapt_supplier_a_replicate( &state->supplier, problem );
    badapt_training_guide_a_replicate( &state->guide, ( badapt_training_guide* )guide );
    state->log = bcore_inst_a_clone( ( bcore_inst* )BCORE_STDOUT );
    badapt_adaptive_a_arc_to_sink( state->adaptive, BCORE_STDOUT );
    badapt_trainer_s_run( trainer, state );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_test_sine_random()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_sine_random_s, problem );
    BCORE_LIFE_CREATE( badapt_builder_mlp_funnel_s,  builder );
    BCORE_LIFE_CREATE( badapt_trainer_s,             trainer );

    problem->input_size = 32;

    builder->input_kernels = 16;
    builder->layers        = 4;
    builder->kernels_rate  = 0;
    builder->random_seed   = 124;
    builder->dynamics.epsilon  = 0.0008;

    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "bias", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator, -1, "bias", "tanh" );

    trainer->fetch_cycles_per_iteration = 10;
    trainer->max_iterations = 10;

    badapt_mlp_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_test_binary_add()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_binary_add_s, problem );
    BCORE_LIFE_CREATE( badapt_builder_mlp_funnel_s, builder );
    BCORE_LIFE_CREATE( badapt_trainer_s,            trainer );

    problem->bits = 8;

    builder->input_kernels = 32;
    builder->layers        = 6;
    builder->kernels_rate  = -0.1;
    builder->random_seed   = 124;
    builder->dynamics.epsilon   = 0.00005;
    builder->dynamics.lambda_l1 = 0.0001;

    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "bias", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator, -1, "bias", "tanh" );

    trainer->fetch_cycles_per_iteration = 30;
    trainer->max_iterations = 10;

    badapt_mlp_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_test_binary_mul()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_binary_mul_s, problem );
    BCORE_LIFE_CREATE( badapt_builder_mlp_funnel_s, builder );
    BCORE_LIFE_CREATE( badapt_trainer_s,            trainer );

    problem->bits = 5;

    builder->input_kernels = 32;
    builder->layers        = 6;
    builder->kernels_rate  = 0.1;
    builder->random_seed   = 124;
    builder->dynamics.epsilon   = 0.0001;
    builder->dynamics.lambda_l1 = 0.001;

    /// Note: To solve the multiplyier a bias seems inhibiting (for addition it seems supportive)
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "plain", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator, -1, "plain", "tanh" );

    trainer->fetch_cycles_per_iteration = 30;
    trainer->max_iterations = 10;

    badapt_mlp_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_test_binary_xsg3()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_binary_xsg3_s, problem );
    BCORE_LIFE_CREATE( badapt_builder_mlp_funnel_s,  builder );
    BCORE_LIFE_CREATE( badapt_trainer_s,             trainer );

    /// xsg3 <= 17 bits is learned very easily with 2 layers, while >= 18 bits seems extremely difficult for any configurations
    problem->bits = 17;

    builder->input_kernels = 30;
    builder->layers        = 2;
    builder->kernels_rate  = 0;
    builder->random_seed   = 124;
    builder->dynamics.epsilon   = 0.0001;
    builder->dynamics.lambda_l1 = 0.001;

    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "plain", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator, -1, "bias",  "tanh" );

    trainer->fetch_cycles_per_iteration = 30;
    trainer->max_iterations = 10;

    badapt_mlp_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_test_binary_hash()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_binary_hash_s, problem );
    BCORE_LIFE_CREATE( badapt_builder_mlp_funnel_s,  builder );
    BCORE_LIFE_CREATE( badapt_trainer_s,             trainer );

    problem->bits = 9;
    problem->reverse = true;

    builder->input_kernels = 32;
    builder->layers        = 6;
    builder->kernels_rate  = 0;
    builder->random_seed   = 125;
    builder->dynamics.epsilon   = 0.001;
//    builder->dynamics.lambda_l1 = 0.001;
    builder->dynamics.lambda_l2 = 0.001;

    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "bias", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator, -1, "bias",  "tanh" );

    trainer->fetch_cycles_per_iteration = 30;
    trainer->max_iterations = 100;

    badapt_mlp_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_test_polynom()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_polynom_s,     problem );
    BCORE_LIFE_CREATE( badapt_builder_mlp_funnel_s,  builder );
    BCORE_LIFE_CREATE( badapt_trainer_s,             trainer );

    problem->input_size  = 16;
    problem->output_size = 8;   // polynomial order + 1
    problem->range       = 2.0; // +/- range of coefficients
    problem->noise_level = 0.001;

    builder->input_kernels = 32;
    builder->layers        = 3;
    builder->kernels_rate  = 0;
    builder->random_seed   = 125;
    builder->dynamics.epsilon   = 0.001;
//    builder->dynamics.lambda_l1 = 0.001;
    builder->dynamics.lambda_l2 = 0.001;

//    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "bias", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator,  0, "bias", "leaky_relu" );
    badapt_arr_layer_activator_s_push_from_names( &builder->arr_layer_activator, -1, "bias", "tanh" );

    trainer->fetch_cycles_per_iteration = 3;
    trainer->batch_cycles_per_fetch = 10;
    trainer->max_iterations = 100;

    badapt_mlp_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

#endif

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t badapt_mlp_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_mlp" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            badapt_mlp_s_test_sine_random();
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

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


