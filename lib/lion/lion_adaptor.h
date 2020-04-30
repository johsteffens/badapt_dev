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

/// bhpt adaptive

/**********************************************************************************************************************/

#ifndef LION_ADAPTOR_H
#define LION_ADAPTOR_H

#include "bmath_std.h"
#include "bhpt_sketch.h"
#include "lion_net.h"
#include "lion_frame.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_adaptor

PLANT_GROUP( lion_adaptor, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :frame = aware bhpt_adaptor
{
    /// source should define cell ( axon_out, grad_out <- axon_in, grad_in ) { ... };
    aware => src; // source (bcore_file_path_s or st_s with inline code)

    hidden lion_frame_s => frame;

    func bhpt_adaptor : reset = { if( o->frame ) lion_frame_s_cyclic_reset( o->frame ); };
    func bhpt_adaptor : adapt;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_adaptor

/**********************************************************************************************************************/

vd_t lion_adaptor_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_ADAPTOR_H
