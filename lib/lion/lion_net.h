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

/// Network Objects

// TODO
// - (done) use double-nested-frame
// - (done) bhvm_value_s_fdev:   (allow all type variations)
// - (done) finish htp dp pass
// - (done) replace '=<' by '<-'
// - (done) current holor literal syntax: is problematic  (() clashes with expression evaluation in brackets), spaces (as catenation) clashes with operator interpretation
//        ... use same syntax as multidimensional arrays in C? {{1,2},{3,4}}
//        ... use ':' to cat holors? {{1:2}:{3:4}:{5:6}}  (seems most appropriate)
//        ... could holor opening '{' clash with cell block opening?  (looking ahead?)
//        ... should {1:2}:3 be {1:2:3}? (seems necessary if 1:2:3 == (1:2):3)
//                   problem: {#:#}:{#:#} == 2[2[# or 1[4[# ?
//        Solution: Use two catenation operators: constructive ':', conservative '::' (keeps order only increases leading dim)
//                      (#:#) :(#:#) == 2[2[#
//                      (#:#:#)      == 3[#
//                      (#:#) :#     == 3[#
//                      (#:#)::(#:#) == 4[#
//       With constructive catenation one can build any holor from scalars.
//       No dedicated rule of holor-bracing required because ':', '::' are just regular binary operators.
//
//
//
// - (done) replace ':' with '<:' for cell-cell or cell-holor concatenation
// - (done) use     ':' for holor concatenation

/**********************************************************************************************************************/

#ifndef LION_NET_H
#define LION_NET_H

#include "lion_sem.h"
#include "lion.xo.h"

/**********************************************************************************************************************/

/// Tree group
#ifdef TYPEOF_lion_ctr

XOILA_DEFINE_GROUP( lion_ctr, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node_s = aware bcore_array
{
    sz_t id = -1;
    private lion_sem_cell_s -> cell;
    private :node_s -> parent;
    :node_s => [];
};

stamp :tree_s = aware :
{
    sz_t id_base = 0; // (incremented when adding nodes)
    :node_s => root;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_ctr

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_net

XOILA_DEFINE_GROUP( lion_net, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :link_s = aware :
{
    hidden vd_t /* :node_s* */ node; // (!) target is a node
};

stamp :links_s = aware bcore_array { :link_s => []; };

signature void solve( mutable );

/// returns the uplink index pointing to node; returns -1 if not found
signature sz_t up_index( const, const :node_s* node );
signature void set_nop_d( mutable, lion_nop* nop );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature bl_t is_cyclic( const ) = { return false; };

stamp :node_s = aware :
{
    :links_s upls; // uplinks
    :links_s dnls; // downlinks

    tp_t name;

    /** Primary flag used for various tracing routines.
      * It is typically used to ensure a node is visited only once.
      * Normalized state: false
      */
    bl_t flag = false;

    /** Secondary flag (probe) used for various tracing routines.
      * It is typically used to to test for cycles/reentries in
      * recursive routines where 'flag' is already in use
      */
    bl_t probe = false;

    /** Node ID.
     *  When the network cell is normalized, id is identical with the cell->body index.
     */
    sz_t id;

    /// mnode is externally stored in a given mcode_frame
    hidden bhvm_mcode_node_s -> mnode;

    aware lion_nop -> nop;

    lion_nop_solve_result_s => result;

    hidden bcore_source_point_s -> source_point;

    //func : .solve;

    func : .up_index =
    {
        BFOR_EACH( i, &o->upls ) if( o->upls.data[ i ]->node == node ) return i;
        return -1;
    };

    func : .set_nop_d =
    {
        ASSERT( o->result == NULL );
        lion_nop_a_attach( &o->nop, nop );
    };

    func : .is_cyclic = { return ( o->mnode ) ? o->mnode->cyclic : lion_nop_a_is_cyclic( o->nop ); };
};

stamp :node_adl_s = aware bcore_array { :node_s => []; };

signature :node_s* get_by_id( mutable, sz_t id );

stamp :nodes_s = aware bcore_array
{
    :node_s => [];
    func : .get_by_id =
    {
        BFOR_EACH( i, o ) if( o->data[ i ]->id == id ) return o->data[ i ];
        return NULL;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void normalize( mutable );
signature void clear_flags( mutable ); /// clears flags
signature void clear_all_flags( mutable ); /// clears flags and probes
signature bl_t is_consistent( const );
signature void clear_downlinks( mutable );
signature void set_downlinks( mutable );

stamp :cell_s = aware :
{
    sz_t max_depth = 32768; // maximum recursion depth
    :nodes_s body;
    :nodes_s encs; // entry channels
    :nodes_s excs; // exit channels

    func : .is_consistent;
    func : .normalize; // re-entrant

    func : .clear_flags =
    {
        BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
    };

    func : .clear_all_flags =
    {
        BFOR_EACH( i, &o->body )
        {
            o->body.data[ i ]->flag = false;
            o->body.data[ i ]->probe = false;
        }
    };

    func : .solve;

    func : .clear_downlinks =
    {
        BFOR_EACH( i, &o->body ) :links_s_clear( &o->body.data[ i ]->dnls );
    };

    func : .set_downlinks;

    func bcore_inst_call . copy_x; // cell is copyable

    // cell is (currently) not transferable ( possible with dedicated shelve & mutated implementation )
    func bcore_via_call  . mutated = { ERR_fa( "Cannot reconstitute." ); };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/
/// node

/// Provides necessary mcode and holor data for isolated nodes that do not actively participate in computing an output
void lion_net_node_s_isolated_mcode_push( lion_net_node_s* o, bhvm_mcode_frame_s* mcf );

/**********************************************************************************************************************/
/// cell

/** Converts lion_sem_cell_s to lion_net_cell_s
 *  Requires a double-nested frame to allow correct processing of input channels with assignments (checked).
 */
void lion_net_cell_s_from_sem_cell
(
    lion_net_cell_s* o,
    lion_sem_cell_s* sem_cell,
    lion_nop* (*input_nop_create)( vd_t arg, sz_t in_idx, tp_t in_name, const lion_nop* cur_nop ),
    vd_t arg,
    bcore_sink* log
);

void lion_net_cell_s_graph_to_sink( lion_net_cell_s* o, bcore_sink* sink );
void lion_net_cell_s_mcode_push_ap( lion_net_cell_s* o, bhvm_mcode_frame_s* mcf );
void lion_net_cell_s_mcode_push_dp( lion_net_cell_s* o, bhvm_mcode_frame_s* mcf, bl_t entry_channels );

#endif // TYPEOF_lion_net

/**********************************************************************************************************************/

vd_t lion_net_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_NET_H
