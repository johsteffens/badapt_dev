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

#include "brnd_eval.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_brnd_eval

// ---------------------------------------------------------------------------------------------------------------------

brnd_eval_result_s* brnd_eval_errf_s_run( const brnd_eval_errf_s* o, brnd_eval_result_s* result )
{
    sz_t k = 6;
    f3_t p = 0.95;
    bl_t success = true;

    f3_t csq = bmath_stat_chisqu_cdf_inv( k, p,   &success );
    f3_t cdf = bmath_stat_chisqu_cdf(     k, csq, &success );
    ASSERT( success );
    bcore_sink_a_push_fa( o->param.log, "#<f3_t>\n", csq );
    bcore_sink_a_push_fa( o->param.log, "#<f3_t>\n", cdf );

    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_brnd_eval

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t brnd_eval_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "brnd_eval" ) ) )
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


