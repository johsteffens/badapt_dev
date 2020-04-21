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

#ifndef LION_ADAPTIVE_BHPT_H
#define LION_ADAPTIVE_BHPT_H

#include "bmath_std.h"
#include "bhpt_std.h"
#include "bhvm_mcode.h"
#include "lion_net.h"
#include "lion_frame.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_adaptive_bhpt

PLANT_GROUP( lion_adaptive_bhpt, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp : = aware bhpt_adaptive
{
    // === architecture parameters ================================

    aware =>     src;      // source (bcore_file_path_s or st_s with inline code)  (just for reference)
    lion_frame_s frame;

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // ==============================================================

    // === adaptive functions =======================================

    func ^ : get_format_en = { bhvm_holor_s_copy( format, &o->holor_frame_en ); return format; };
    func ^ : get_format_ex = { bhvm_holor_s_copy( format, &o->holor_frame_ex ); return format; };

    func ^ : axon_pass;
    func ^ : dendrite_pass;
    func ^ : cyclic_reset;
    func ^ : get_hprobe_accugrad;
    func ^ : get_hprobe_adaptive;
    func ^ : status_to_sink;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :builder = aware bhpt_builder
{
    aware => src; // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // === builder functions =======================================

    func ^ : set_format_en = { bhvm_holor_s_copy( &o->holor_frame_en, format ); };
    func ^ : set_format_ex = { bhvm_holor_s_copy( &o->holor_frame_ex, format ); };
    func ^ : create_adaptive;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_adaptive_bhpt

/**********************************************************************************************************************/

vd_t lion_adaptive_bhpt_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_ADAPTIVE_BHPT_H
