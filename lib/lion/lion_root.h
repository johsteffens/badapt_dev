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

/// Root Objects

/**********************************************************************************************************************/

#ifndef LION_ROOT_H
#define LION_ROOT_H

#include "bhvm_holor.h"
#include "bhvm_mcode.h"
#include "lion.xo.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion

XOILA_DEFINE_GROUP( lion, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void clear( m @* o );

stamp :hmeta_s = aware bhvm_mcode_hmeta
{
    aware bcore_inst => custom; // custom params

    /// associated mnode
    hidden bhvm_mcode_node_s -> mnode;

    tp_t name;

    /// pass-class (see bhvm_mcode_hmeta)
    tp_t pclass;

    // holor is transposed
    bl_t htp;

    /** Holor is a active (mutable, not constant).
     *  Active holors typically represent a variable in the virtual machine.
     *  They are normally depleted during shelving and actively initialized during setup.
     *  The opposite (passive) are holors carrying an immutable value (e.g a constant)
     *  In a network a holor is active if it depends on at least one active holor in
     *  such a manner that its change affects the resulting holor.
     *  Computations among passive holors are generally solved in the network and not converted into microcode.
     */
    bl_t active = true;

    func : .clear = { o->name = 0; o->htp = false; };

    func bhvm_mcode_hmeta . get_name     = { return o->name; };
    func bhvm_mcode_hmeta . get_pclass   = { return o->pclass; };
    func bhvm_mcode_hmeta . is_rollable  = { return !o->active || o->mnode->adaptive || ( o->mnode->cyclic && o->pclass == TYPEOF_pclass_ax1 ); };
    func bhvm_mcode_hmeta . is_active    = { return  o->active; };

    func bhvm_mcode_hmeta . get_custom = { return o->custom; };
    func bhvm_mcode_hmeta . set_custom = { bcore_inst_a_attach( &o->custom, bcore_inst_a_clone( custom ) ); return o->custom; };

    func bhvm_mcode_hmeta . get_node = { return o->mnode; };
    func bhvm_mcode_hmeta . set_node = { bhvm_mcode_node_s_attach( &o->mnode, bcore_fork( node ) ); };
};

stamp :holor_s = aware :
{
    :hmeta_s     m;
    bhvm_holor_s h;

    func bcore_fp .copy_typed;
};

// ---------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lion_holor_s_to_sink(      const lion_holor_s* o, bcore_sink* sink );
void lion_holor_s_to_sink_nl(   const lion_holor_s* o, bcore_sink* sink ); // appends newline
void lion_holor_s_to_stdout(    const lion_holor_s* o );
void lion_holor_s_to_stdout_nl( const lion_holor_s* o ); // appends newline

/** compacted version, single line */
void lion_holor_s_brief_to_sink(       const lion_holor_s* o, bcore_sink* sink );
void lion_holor_s_brief_to_stdout(     const lion_holor_s* o );

/** multiline version */
void lion_holor_s_formatted_to_sink(   const lion_holor_s* o, bcore_sink* sink );
void lion_holor_s_formatted_to_stdout( const lion_holor_s* o );

/// sets holor from text source
void lion_holor_s_parse( lion_holor_s* o, bcore_source* source );

#endif // TYPEOF_lion

/**********************************************************************************************************************/

vd_t lion_root_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_ROOT_H
