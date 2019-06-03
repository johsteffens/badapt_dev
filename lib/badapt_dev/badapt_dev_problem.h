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

#ifndef BADAPT_DEV_PROBLEM_H
#define BADAPT_DEV_PROBLEM_H

#include "bmath_std.h"
#include "badapt_loss.h"
#include "badapt_training.h"
#include "badapt_dev_precoded.h"

/**********************************************************************************************************************/

BETH_PRECODE( badapt_dev_problem_objects )
#ifdef BETH_PRECODE_SECTION

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Type: Recurrent Sequence Estimator
 *  Method: Estimate characters of KJV Bible
 */
self badapt_problem_recurrent_kjv_s = badapt_supplier
{
    aware_t _;
    aware bcore_source => source;
    bcore_arr_sz_s     => charmap;
    st_s               => charset;

    u0_t t_last_char = 0;
    u0_t v_last_char = 0;

    u2_t rval       = 1234;
    f3_t pos_tgt    =  0.9;
    f3_t neg_tgt    = -0.9;
    aware badapt_loss* preferred_loss = badapt_loss_l2_s;

    func badapt_supplier : preferred_loss;
    func badapt_supplier : get_in_size;
    func badapt_supplier : get_out_size;
    func badapt_supplier : fetch_sample_tio;
    func badapt_supplier : fetch_sample_vio;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_guide_char_encode_s = badapt_guide
{
    aware_t _;
    aware badapt_guide => guide_default = badapt_guide_std_s;
    bcore_arr_sz_s -> charmap;
    st_s           -> charset;
    f3_t pos_tgt    =  0.9;
    f3_t neg_tgt    = -0.9;
    func badapt_guide : callback;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // BETH_PRECODE_SECTION

/**********************************************************************************************************************/

vd_t badapt_dev_problem_signal_handler( const bcore_signal_s* o );

#endif  // BADAPT_DEV_PROBLEM_H

