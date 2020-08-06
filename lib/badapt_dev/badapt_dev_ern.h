/** Author and Copyright 2019 Johannes Bernhard Steffens
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

/** Elman Recurrent Network
 *
 *    inference:
 *    h = a_h( w_hx * x + w_hc * c )
 *    c <- h;
 *    o = a_o( w_o * h )
 *
 */

#ifndef BADAPT_DEV_ERN_H
#define BADAPT_DEV_ERN_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_xoi_out.h"
#include "badapt_ern.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_badapt_dev_ern
XOILA_DEFINE_GROUP( badapt_dev_ern, bcore_inst )
#ifdef XOILA_SECTION

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif // XOILA_SECTION
#endif // TYPEOF_badapt_dev_ern


/**********************************************************************************************************************/
// tests

void badapt_ern_test_recurrent_abc();
void badapt_ern_test_recurrent_kjv();

/**********************************************************************************************************************/

vd_t badapt_dev_ern_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_DEV_ERN_H
