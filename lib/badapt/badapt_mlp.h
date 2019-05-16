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
#include "badapt_features.h"
#include "badapt_precoded.h"
#include "badapt_activator.h"

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
    sz_t input_size;               // input vector size
    sz_t input_kernels   = 8;    // (default 8) kernels on input layer
    sz_t output_kernels  = 1;    // (default 1) kernels on output layer
    sz_t layers          = 2;    // (default 2) number of layers
    f3_t kernels_rate    = 0;    // (default 0) rate at which number of kernels increase per layer (negative: decrease); last layer excluded

    f3_t epsilon_rate    = 0.0001; // epsilon per rate
    f3_t epsilon         = -1;     // current learning rate (-1 means uninitialized)
    f3_t lambda_l1       = 0;      // l1-regularization
    f3_t lambda_l2       = 0;      // l2-regularization

    badapt_arr_layer_activator_s arr_layer_activator;

    u2_t random_state   = 1234; // (default: 1234) random state variable (for random initialization)
    // ==============================================================

    badapt_mlp_arr_layer_s arr_layer;     // layer array

    // === runtime data =============================================
    hidden sz_t        max_buffer_size;
    hidden bmath_vf3_s in;     // input vector weak map to arr_a[ 0 ]
    // ==============================================================

    // === adaptive functions =======================================
    func badapt_adaptive : reset;
    func badapt_adaptive : setup;

    func badapt_adaptive : get_in_size;
    func badapt_adaptive : set_in_size;
    func badapt_adaptive : get_out_size;
    func badapt_adaptive : set_out_size;

    func badapt_adaptive : get_rate;
    func badapt_adaptive : set_rate;
    func badapt_adaptive : get_lambda_l1;
    func badapt_adaptive : set_lambda_l1;
    func badapt_adaptive : get_lambda_l2;
    func badapt_adaptive : set_lambda_l2;

    func badapt_adaptive : arc_to_sink;
    func badapt_adaptive : infer;
    func badapt_adaptive : minfer;

    func badapt_adaptive : bgrad;
    func badapt_adaptive : bgrad_adapt;
    // ==============================================================
};

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void badapt_mlp_s_test_sine_random();
void badapt_mlp_s_test_binary_add();
void badapt_mlp_s_test_binary_mul();
void badapt_mlp_s_test_binary_xsg3();

/**********************************************************************************************************************/

vd_t badapt_mlp_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_MLP_H
