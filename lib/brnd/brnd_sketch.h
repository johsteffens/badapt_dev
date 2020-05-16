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

/** Sketch for a dev framework of (pseudo-)random generators.
 *  The principal purpose of these generators are
 *  random initialization, noise generation and Monte-Carlo-Testing.
 *  The targeted use case is adaptive initialization and training.
 *  Pseudo random generators studied here are neither intended nor
 *  deemed suitable for cryptographic purposes.
 */

/**********************************************************************************************************************/

#ifndef BRND_SKETCH_H
#define BRND_SKETCH_H

#include "bmath_std.h"
#include "brnd_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_brnd

PLANT_GROUP( brnd, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Random generator
group :gen =
{
    feature 'a' u3_t max_u3( const ); // maximum possible u3 value for given generator
    feature 'a' u3_t min_u3( const ); // minimum possible u3 value for given generator
    feature 'a' u3_t gen_u3( mutable ); // generates an integer random value
    feature 'a' f3_t gen_f3( mutable, f3_t min, f3_t max ); // generates a f3_t value within [min, max]
    feature 'a' void reseed(  mutable, u3_t seed ); // resets generator using an u3 seed (all seeds are allowed)
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Random test
group :test =
{
    /** Tests a random generator and returns a score between 0(not random) and 1(most random)
     *  In many tests the score can be assumed to to be a probability that the generated random
     *  samples exhibit a random behavior according to the test criterion.
     */
    feature 'a' f3_t run( const, const ::gen* gen );
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_brnd

/**********************************************************************************************************************/

vd_t brnd_sketch_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BRND_SKETCH_H
