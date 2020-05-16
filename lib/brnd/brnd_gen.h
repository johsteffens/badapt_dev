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

/** Pseudo Random generators.
 */

/**********************************************************************************************************************/

#ifndef BRND_GEN_H
#define BRND_GEN_H

#include "bmath_std.h"
#include "brnd_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_brnd_gen_stamp

PLANT_GROUP( brnd_gen_stamp, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stump brnd_gen_stump = aware brnd_gen
{
    func ^ :gen_f3 =
    {
        return min + ( max - min ) * ( ( f3_t )( @_gen_u3( o ) - @_min_u3( o ) ) / ( @_max_u3( o ) - @_min_u3( o ) ) );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group brnd_gen_lcg =
{

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stump :u2 = extending brnd_gen_stump
    {
        u2_t state = 16432;
        func ^ :max_u3 = { return 0xFFFFFFFFu; };
        func ^ :min_u3 = { return 0; };
        func ^ :reseed = { o->state = seed ^ ( seed >> 32 ); };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :v00 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_lcg_u2(  o->state ) ); }; };
    stamp :v01 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_lcg1_u2( o->state ) ); }; };
    stamp :v02 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_lcg2_u2( o->state ) ); }; };
    stamp :v03 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_lcg3_u2( o->state ) ); }; };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group brnd_gen_xsg =
{

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stump :u2 = extending brnd_gen_stump
    {
        u2_t state = 16432;
        func ^ :max_u3 = { return 0xFFFFFFFFu; };
        func ^ :min_u3 = { return 1; };
        func ^ :reseed = { o->state = u2_max( 1, seed ^ ( seed >> 32 ) ); };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :v00 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_xsg_u2(  o->state ) ); }; };
    stamp :v01 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_xsg1_u2( o->state ) ); }; };
    stamp :v02 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_xsg2_u2( o->state ) ); }; };
    stamp :v03 = extending :u2 { func ^ :gen_u3 = { return ( o->state = bcore_xsg3_u2( o->state ) ); }; };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};

/** A mock generator simply counting upward and rolling over.
 *  This generator is used to test the eval framework.
 */
stamp brnd_gen_count  = aware brnd_gen
{
    u2_t state = 0;
    func ^ :max_u3 = { return 0xFFFFFFFFu; };
    func ^ :min_u3 = { return 0; };
    func ^ :gen_u3 = { return ++o->state; };
    func ^ :gen_f3 = { return min + ( f3_t )@_gen_u3( o ) / ( ( max - min ) * @_max_u3( o ) ); };
    func ^ :reseed = { o->state = seed ^ ( seed >> 32 ); };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_brnd_gen_stamp

/**********************************************************************************************************************/

vd_t brnd_gen_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BRND_GEN_H
