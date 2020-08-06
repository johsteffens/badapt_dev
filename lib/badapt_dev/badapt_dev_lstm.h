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

#ifndef BADAPT_DEV_LSTM_H
#define BADAPT_DEV_LSTM_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_xoila_out.h"

/**********************************************************************************************************************/
// tests

void badapt_dev_lstm_test_recurrent_abc();
void badapt_lstm_test_recurrent_abc();
void badapt_dev_lstm_test_recurrent_kjv();
void badapt_dev_lstm_test_recurrent_kjv2();

/**********************************************************************************************************************/

vd_t badapt_dev_lstm_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_DEV_LSTM_H
