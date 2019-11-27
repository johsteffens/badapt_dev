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

#include "haptive_signal.h"
#include "haptive_planted.h"
#include "haptive_graph.h"
#include "haptive_eval.h"

//----------------------------------------------------------------------------------------------------------------------

vd_t haptive_signal_handler( const bcore_signal_s* o )
{
    vd_t ret = NULL;

    // non-local targets
    if( o->target != TYPEOF_local )
    {
        /// nothing yet
    }

    if( ret ) return ret;

    // local targets
    {
        bcore_fp_signal_handler arr[] =
        {
            haptive_planted_signal_handler,
            haptive_graph_signal_handler,
            haptive_eval_signal_handler,
        };

        ret = bcore_signal_s_broadcast( o, arr, sizeof( arr ) / sizeof( bcore_fp_signal_handler ) );
    }
    return ret;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
