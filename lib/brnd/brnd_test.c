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

#include "brnd_test.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_brnd_test_stamp

// ---------------------------------------------------------------------------------------------------------------------

f3_t brnd_test_uniform_dist_s_run( const brnd_test_uniform_dist_s* o, const brnd_gen* src_gen )
{
    ASSERT( o->slots > 0 );
    BLM_INIT();
    f3_t score = 0;

    brnd_gen* gen = BLM_A_PUSH( brnd_gen_a_clone( src_gen ) );

    bcore_arr_sz_s* hist = BLM_CREATE( bcore_arr_sz_s );
    bcore_arr_sz_s_fill( hist, o->slots, 0 );
    BFOR_SIZE( i, o->samples )
    {
        f3_t v = brnd_gen_a_gen_f3( gen, 0.0, 1.0 );
        sz_t idx = sz_min( o->slots - 1, v * o->slots );
        hist->data[ idx ]++;
    }

    f3_t n0i = ( ( f3_t )o->samples ) / o->slots;
    f3_t chi_sqr = 0;

    BFOR_EACH( i, hist )
    {
        f3_t n1i = hist->data[ i ];
        chi_sqr += f3_sqr( n1i - n0i ) / n0i;
    }

    sz_t k = o->slots - 1;
    bl_t success = true;
    f3_t p_limit = 0.99;
    f3_t x_limit = bmath_stat_chisqu_cdf_inv( k, p_limit, &success );
    ASSERT( success );
    if( chi_sqr <= x_limit )
    {
        f3_t p = bmath_stat_chisqu_cdf( k, chi_sqr, &success );
        ASSERT( success );
        score = 1.0 - p;
    }
    else
    {
        score = 0;
    }

    BLM_RETURNV( f3_t, score );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_brnd_test_stamp

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t brnd_test_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "brnd_test" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "brnd_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


