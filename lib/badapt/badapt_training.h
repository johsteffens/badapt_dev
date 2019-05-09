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

BETH_PRECODE( badapt_training_data )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    self badapt_sample_s     = bcore_inst  { bmath_vf3_s in; bmath_vf3_s out; };
    self badapt_arr_sample_s = bcore_array { aware_t _; badapt_sample_s [] arr; };
#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BETH_PRECODE( badapt_supplier )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    feature strict 'par' void fetch_batch_sample( mutable, badapt_sample_s* dst );
    feature strict 'par' void fetch_valid_sample( mutable, badapt_sample_s* dst );
    feature        'par' void fetch_batch_data(   mutable, badapt_arr_sample_s* dst, sz_t size ) = fetch_batch_data_default;
    feature        'par' void fetch_valid_data(   mutable, badapt_arr_sample_s* dst, sz_t size ) = fetch_valid_data_default;
#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BETH_PRECODE( badapt_training_objects )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_trainer_s = bcore_inst
{
    aware_t _;

    // supplier implementing training features
    aware badapt_supplier => supplier;

    // ~~~ training parameters ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    sz_t batch_size                 = 10000;
    sz_t batch_cycles_per_fetch     = 2;
    sz_t fetch_cycles_per_iteration = 10;
    sz_t valid_size                 = 10000; // validation happens after each iteration

    /// stopping criteria
    sz_t max_iterations = 1000000;
    f3_t min_error      = 0;
    f3_t min_progress   = 0;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void badapt_trainer_s_run( const badapt_trainer_s* o, badapt_adaptive* adaptive );

/**********************************************************************************************************************/

vd_t badapt_training_signal_handler( const bcore_signal_s* o );

#endif  // BADAPT_TRAINING_H

