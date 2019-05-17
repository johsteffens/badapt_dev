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

#ifndef BADAPT_MLP_H
#define BADAPT_MLP_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"

/**********************************************************************************************************************/

BETH_PRECODE( badapt_mlp )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_mlp_layer_s = bcore_inst
{
    aware_t _;
    sz_t input_size;
    sz_t kernels;
    bmath_mf3_s                wgt;
    aware  badapt_activator => act;
    hidden bmath_vf3_s         out;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_mlp_arr_layer_s = bcore_array { aware_t _; badapt_mlp_layer_s [] arr; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Simple scalable multi layer perceptron vector -> vector
 *  Set/change architecture parameters. Then run query/learn as needed.
 *  Call reset if parameters need change.
 */
self badapt_mlp_s = badapt_adaptive
{
    aware_t _;

    // === architecture parameters ================================

    badapt_dynamics_s      dynamics;
    badapt_mlp_arr_layer_s arr_layer;

    // === runtime data =============================================
    hidden sz_t        max_buffer_size;
    hidden bmath_vf3_s in;     // input vector weak map to arr_a[ 0 ]
    // ==============================================================

    // === adaptive functions =======================================
    func badapt_adaptive : get_in_size;
    func badapt_adaptive : get_out_size;

    func badapt_adaptive : get_dynamics;
    func badapt_adaptive : set_dynamics;

    func badapt_adaptive : arc_to_sink;
    func badapt_adaptive : infer;
    func badapt_adaptive : minfer;

    func badapt_adaptive : bgrad;
    func badapt_adaptive : bgrad_adapt;
    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Builder creating a funnel structure of kernels
self badapt_builder_mlp_funnel_s = badapt_builder
{
    aware_t _;

    sz_t input_size;               // input vector size
    sz_t input_kernels   = 8;      // kernels on input layer
    sz_t output_kernels  = 1;      // kernels on output layer
    sz_t layers          = 2;      // number of layers
    f3_t kernels_rate    = 0;      // rate at which number of kernels increase per layer (negative: decrease); last layer excluded
    u2_t random_seed     = 1234;   // random seed variable (for random initialization)
    badapt_dynamics_s dynamics;

    badapt_arr_layer_activator_s arr_layer_activator;

    // === builder functions =======================================

    /// input vector size
    func badapt_builder : get_in_size;
    func badapt_builder : set_in_size;

    /// output vector size
    func badapt_builder : get_out_size;
    func badapt_builder : set_out_size;

    /// builds adaptive ready to be trained; passes ownership
    func badapt_builder : build;

    // ==============================================================
};

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void badapt_mlp_s_test_sine_random();
void badapt_mlp_s_test_binary_add();
void badapt_mlp_s_test_binary_mul();
void badapt_mlp_s_test_binary_xsg3();
void badapt_mlp_s_test_binary_hash();
void badapt_mlp_s_test_polynom();

/**********************************************************************************************************************/

vd_t badapt_mlp_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_MLP_H
