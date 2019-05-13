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

#ifndef BADAPT_TRAINING_H
#define BADAPT_TRAINING_H

#include "bmath_std.h"
#include "badapt_features.h"

/**********************************************************************************************************************/
/// features
BCORE_FORWARD_OBJECT( badapt_training_guide );

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

BETH_PRECODE( badapt_training_data )
#ifdef BETH_PRECODE_SECTION
    self badapt_sample_s     = bcore_inst  { bmath_vf3_s in; bmath_vf3_s out; };
    self badapt_arr_sample_s = bcore_array { aware_t _; badapt_sample_s [] arr; };
#endif // BETH_PRECODE_SECTION

//----------------------------------------------------------------------------------------------------------------------

BETH_PRECODE( badapt_supplier )
#ifdef BETH_PRECODE_SECTION
    feature strict 'pa' sz_t get_in_size(  const );
    feature strict 'pa' sz_t get_out_size( const );
    feature strict 'pa' void fetch_batch_sample( mutable, badapt_sample_s*     dst );
    feature strict 'pa' void fetch_valid_sample( mutable, badapt_sample_s*     dst );
    feature        'pa' void fetch_batch_data(   mutable, badapt_arr_sample_s* dst, sz_t size ) = fetch_batch_data_default;
    feature        'pa' void fetch_valid_data(   mutable, badapt_arr_sample_s* dst, sz_t size ) = fetch_valid_data_default;

    // returns preferred loss function
    feature        'pa' const badapt_loss* preferred_loss( const );
#endif // BETH_PRECODE_SECTION

//----------------------------------------------------------------------------------------------------------------------

BETH_PRECODE( badapt_training_objects )
#ifdef BETH_PRECODE_SECTION

self badapt_trainer_s = bcore_inst
{
    aware_t _;

    // loss function (optional; overrides preferred loss of supplier)
    aware badapt_loss => loss;

    // ~~~ training parameters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    sz_t batch_size                 = 10000;
    sz_t batch_cycles_per_fetch     = 1;
    sz_t fetch_cycles_per_iteration = 4;
    sz_t valid_size                 = 10000; // validation happens after each iteration

    /// stopping criteria
    sz_t max_iterations = 10;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_trainer_state_s = bcore_inst
{
    aware_t _;

    f3_t rate      = 1.0; // learning rate
    sz_t iteration = 0;
    f3_t error     = 0;
    f3_t progress  = 0;
    f3_t bias      = 0;

    // adaptive to be trained
    aware badapt_adaptive => adaptive;

    // supplier implementing training features
    aware badapt_supplier => supplier;

    // training guide; called at each iteration;
    aware badapt_training_guide => guide = badapt_training_guide_std_s;

    // logging
    hidden aware bcore_sink -> log;

};
#endif // BETH_PRECODE_SECTION

void badapt_trainer_s_run( const badapt_trainer_s* o, badapt_trainer_state_s* state );

//----------------------------------------------------------------------------------------------------------------------

BETH_PRECODE( badapt_training_guide )
#ifdef BETH_PRECODE_SECTION

    // callback for training iterations; state can be changed; return value indicates if training shall continue
    feature strict 'a' bl_t callback( const, badapt_trainer_state_s* state );
#endif // BETH_PRECODE_SECTION

//----------------------------------------------------------------------------------------------------------------------

BETH_PRECODE( badapt_training_objects2 )
#ifdef BETH_PRECODE_SECTION

self badapt_training_guide_std_s = badapt_training_guide
{
    aware_t _;
    f3_t annealing_factor = 1.0;
    func badapt_training_guide : callback;
};

#endif // BETH_PRECODE_SECTION

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

vd_t badapt_training_signal_handler( const bcore_signal_s* o );

#endif  // BADAPT_TRAINING_H

