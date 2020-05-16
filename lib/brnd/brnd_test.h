/** Author and Copyright 2020 Johannes Bernhard Steffens
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

/**********************************************************************************************************************/

/** Random Tests
 */

/**********************************************************************************************************************/

#ifndef BRND_TEST_H
#define BRND_TEST_H

#include "bmath_std.h"
#include "brnd_sketch.h"
#include "brnd_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_brnd_test_stamp

PLANT_GROUP( brnd_test_stamp, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Uniformity of value distribution.
 *  Score is the probability that a true random generator produces a uniformity
 *  of this generator based on a chi-squared-test.
 */
stamp brnd_test_uniform_dist  = aware brnd_test
{
    sz_t samples = 100000;
    sz_t slots   = 100; // number of slots across the value range
    func ^ :run;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Runs generator max_tests or the second occurrence
 *  on value which ever occurs first.
 *  If a second occurrence is detected, the score is
 *  <distance between first and second occurrence> / <max value - min value + 1>.
 *  Otherwise the score is 0.
 */
//stamp brnd_test_repetition  = aware brnd_test
//{
//    u3_t max_tests = 0x2;
//    u3_t value = 1547;
//    func ^ :run;
//};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_brnd_test_stamp

/**********************************************************************************************************************/

vd_t brnd_test_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BRND_TEST_H
