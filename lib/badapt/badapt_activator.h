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

#ifndef BADAPT_ACTIVATOR_H
#define BADAPT_ACTIVATOR_H

#include "bmath_std.h"
#include "badapt_precoded.h"
#include "badapt_features.h"

/**********************************************************************************************************************/

/// activation function
BETH_PRECODE( badapt_activation_objects )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_activation_tanh_s = badapt_activation
{
    aware_t _;
    func badapt_activation : fx;
    func badapt_activation : dy;
};

self badapt_activation_relu_s = badapt_activation
{
    aware_t _;
    func badapt_activation : fx;
    func badapt_activation : dy;
};

self badapt_activation_leaky_relu_s = badapt_activation
{
    aware_t _;
    func badapt_activation : fx;
    func badapt_activation : dy;
};

self badapt_activation_softplus_s = badapt_activation
{
    aware_t _;
    func badapt_activation : fx;
    func badapt_activation : dy;
};

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

/// activation function
BETH_PRECODE( badapt_activator_objects )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

self badapt_activator_plain_s = badapt_activator
{
    sr_s activation;
    func badapt_activator : setup;
    func badapt_activator : reset;
    func badapt_activator : infer;
    func badapt_activator : bgrad;
    func badapt_activator : adapt;
};

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

vd_t badapt_activator_signal_handler( const bcore_signal_s* o );

#endif  // BADAPT_ACTIVATOR_H

