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

#include "lion_signal.h"
#include "lion_planted.h"
#include "lion_root.h"
#include "lion_nop.h"
#include "lion_nop_eval.h"
#include "lion_sem.h"
#include "lion_net.h"
#include "lion_net_eval.h"
#include "lion_frame.h"
#include "lion_adaptive.h"

//----------------------------------------------------------------------------------------------------------------------

vd_t lion_signal_handler( const bcore_signal_s* o )
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
            lion_planted_signal_handler,
            lion_root_signal_handler,
            lion_nop_signal_handler,
            lion_nop_eval_signal_handler,
            lion_sem_signal_handler,
            lion_net_signal_handler,
            lion_net_eval_signal_handler,
            lion_frame_signal_handler,
            lion_adaptive_signal_handler,
        };

        ret = bcore_signal_s_broadcast( o, arr, sizeof( arr ) / sizeof( bcore_fp_signal_handler ) );
    }
    return ret;
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
