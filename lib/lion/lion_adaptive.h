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

/// node operator

/**********************************************************************************************************************/

#ifndef LION_ADAPTIVE_H
#define LION_ADAPTIVE_H

#include "bmath_std.h"
#include "badapt_std.h"
#include "bhvm_mcode.h"
#include "lion_net.h"
#include "lion_frame.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_adaptive

PLANT_GROUP( lion_adaptive, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware badapt_adaptive
{
    // === architecture parameters ================================

    aware =>               src;      // source (bcore_file_path_s or st_s with inline code)  (just for reference)
    lion_frame_s           frame;
    badapt_dynamics_std_s  dynamics;
    sz_t                   in_size;  // input vector size
    sz_t                   out_size; // output vector size

    // ==============================================================

    // === adaptive functions =======================================
    func ^ : get_in_size  = { return o->in_size;  };
    func ^ : get_out_size = { return o->out_size; };
    func ^ : get_dynamics_std = { badapt_dynamics_std_s_copy( dynamics, &o->dynamics ); };
    func ^ : set_dynamics_std = { badapt_dynamics_std_s_copy( &o->dynamics, dynamics ); };

    func ^ : arc_to_sink;
    func ^ : minfer;
    func ^ : bgrad_adapt;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :builder = aware badapt_builder
{
    aware => src; // source (bcore_file_path_s or st_s with inline code)

    sz_t in_size;  // input vector size
    sz_t out_size; // output vector size

    badapt_dynamics_std_s dynamics;

    // === builder functions =======================================

    /// input vector size
    func ^ : get_in_size = { return o->in_size; };
    func ^ : set_in_size = { o->in_size = size; };

    /// output vector size
    func ^ : get_out_size = { return o->out_size; };
    func ^ : set_out_size = { o->out_size = size; };

    /// builds adaptive ready to be trained; passes ownership
    func ^ : build;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_adaptive

/**********************************************************************************************************************/

vd_t lion_adaptive_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_ADAPTIVE_H
