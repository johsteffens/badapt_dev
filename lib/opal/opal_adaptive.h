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

#ifndef OPAL_ADAPTIVE_BHPT_H
#define OPAL_ADAPTIVE_BHPT_H

#include "bmath_std.h"
#include "bhpt_std.h"
#include "bhvm_mcode.h"
#include "opal_net.h"
#include "opal_frame.h"
#include "opal.xo.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( opal_adaptive, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :s = aware bhpt_adaptive
{
    // === architecture parameters ================================

    aware =>     src;      // source (bcore_file_path_s or st_s with inline code)  (just for reference)
    opal_frame_s frame;

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // ==============================================================

    // === adaptive functions =======================================

    func bhpt_adaptive.get_format_en = { format.copy( o.holor_frame_en ); return format; };
    func bhpt_adaptive.get_format_ex = { format.copy( o.holor_frame_ex ); return format; };
    func bhpt_adaptive.axon_pass     = { o.frame.run_ap( cast( ax_en, const bhvm_holor_s** ), 1, ax_ex, 1 ); };
    func bhpt_adaptive.dendrite_pass = { o.frame.run_dp( cast( ag_ex, const bhvm_holor_s** ), 1, ( ag_en ) ? &ag_en : NULL, ( ag_en ) ? 1 : 0 ); };
    func bhpt_adaptive.cyclic_reset  = { o.frame.cyclic_reset(); };
    func bhpt_adaptive.rebind_holors = { o.frame.bind_holors(); };
    func bhpt_adaptive.get_adaptor_probe;
    func bhpt_adaptive.status_to_sink;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :builder_s = aware bhpt_builder
{
    aware => src; // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // === builder functions =======================================

    func bhpt_builder.set_format_en = { o.holor_frame_en.copy( format ); };
    func bhpt_builder.set_format_ex = { o.holor_frame_ex.copy( format ); };
    func bhpt_builder.create_adaptive;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :cyclic_s = aware bhpt_adaptive
{
    // === architecture parameters ================================

    aware =>     src;      // source (bcore_file_path_s or st_s with inline code)  (just for reference)
    opal_frame_cyclic_s frame;

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // ==============================================================

    /// accumulated dp data
    bhvm_holor_adl_s => dp_buffer;
    bl_t dp_value; // true in case a value was stored

    // === adaptive functions =======================================

    func bhpt_adaptive.get_format_en = { format.copy( o.holor_frame_en ); return format; };
    func bhpt_adaptive.get_format_ex = { format.copy( o.holor_frame_ex ); return format; };

    func bhpt_adaptive.axon_pass = { o.frame.run_ap( cast( ax_en, const bhvm_holor_s** ), 1, ax_ex, 1 ); };
    func bhpt_adaptive.dendrite_pass;
    func bhpt_adaptive.cyclic_reset;
    func bhpt_adaptive.get_adaptor_probe;
    func bhpt_adaptive.rebind_holors = { o.frame.bind_holors(); };
    func bhpt_adaptive.status_to_sink;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :cyclic_builder_s = aware bhpt_builder
{
    aware => src; // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;
    sz_t unroll_size;

    // === builder functions =======================================

    func bhpt_builder.set_format_en = { o.holor_frame_en.copy( format ); };
    func bhpt_builder.set_format_ex = { o.holor_frame_ex.copy( format ); };
    func bhpt_builder.create_adaptive;

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "opal_adaptive.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // OPAL_ADAPTIVE_BHPT_H
