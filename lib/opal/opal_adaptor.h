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

/// The adaptor defines a method for updating adaptive holors from accumulated gradients.

/**********************************************************************************************************************/

#ifndef OPAL_ADAPTOR_H
#define OPAL_ADAPTOR_H

#include "bmath_std.h"
#include "bhpt_sketch.h"
#include "opal_net.h"
#include "opal_frame.h"
#include "opal_xoila_out.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( opal_adaptor, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :frame = aware bhpt_adaptor
{
    /// source should define cell ( axon_out, grad_out <- axon_in, grad_in ) { ... };
    aware => src; // source (bcore_file_path_s or st_s with inline code)

    hidden opal_frame_s => frame;

    func bhpt_adaptor : reset = { if( o->frame ) opal_frame_s_cyclic_reset( o->frame ); };
    func bhpt_adaptor : adapt;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // OPAL_ADAPTOR_H
