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

/** Jordan Recurrent Network
 *
 *  Schematics (activation omitted):
 *
 *       vec_input---->wgt_input-----.
 *                                  (+)-->vec_hidden-->wgt_hidden-->vec_output
 *    .->vec_context-->wgt_context---'                                   |
 *    |                                                                  |
 *    '------------------------------------------------------------------'
 *
 */

#ifndef BADAPT_DEV_JRN_H
#define BADAPT_DEV_JRN_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_precoded.h"
#include "badapt_jrn.h"

/**********************************************************************************************************************/
// tests

void badapt_dev_jrn_s_test_recurrent_kjv();

/**********************************************************************************************************************/

vd_t badapt_dev_jrn_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_DEV_JRN_H
