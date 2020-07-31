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

/**********************************************************************************************************************/

#ifndef OPAL_NET_H
#define OPAL_NET_H

#include "opal_sem.h"
#include "opal_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_opal_net

PLANT_GROUP( opal_net, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :link = aware :
{
    hidden vd_t /* :node_s* */ node; // (!) target is a node
};

stamp :links = aware bcore_array { :link_s => []; };

signature void solve( mutable );

/// returns the uplink index pointing to node; returns -1 if not found
signature sz_t up_index( const, const :node_s* node );
signature void set_nop_d( mutable, opal_nop* nop );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' bl_t is_cyclic( const ) = { return false; };

stamp :node = aware :
{
    :links_s upls; // uplinks
    :links_s dnls; // downlinks

    tp_t name;

    opal_sem_id_s => sem_id;

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

    /** Low Level Node ID.
     *  When the network cell is normalized, id is identical with the cell->body index.
     */
    sz_t id;

    /// mnode is externally stored in a given mcode_frame
    hidden bhvm_mcode_node_s -> mnode;

    aware opal_nop -> nop;

    opal_nop_solve_result_s => result;

    hidden aware opal_context -> context;

    hidden bcore_source_point_s -> source_point;

    //func : :solve;

    func : :up_index =
    {
        BFOR_EACH( i, &o->upls ) if( o->upls.data[ i ]->node == node ) return i;
        return -1;
    };

    func : :set_nop_d =
    {
        ASSERT( o->result == NULL );
        opal_nop_a_attach( &o->nop, nop );
    };

    func : :is_cyclic = { return ( o->mnode ) ? o->mnode->cyclic : opal_nop_a_is_cyclic( o->nop ); };
};

stamp :node_adl = aware bcore_array { :node_s => []; };

signature :node_s* get_by_id( mutable, sz_t id );

stamp :nodes = aware bcore_array
{
    :node_s => [];
    func : :get_by_id =
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

stamp :cell = aware :
{
    sz_t max_depth = 32768; // maximum recursion depth
    :nodes_s body;
    :nodes_s encs; // entry channels
    :nodes_s excs; // exit channels

    hidden aware opal_context -> context;

    func : :is_consistent;
    func : :normalize; // re-entrant

    func : :clear_flags =
    {
        BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
    };

    func : :clear_all_flags =
    {
        BFOR_EACH( i, &o->body )
        {
            o->body.data[ i ]->flag = false;
            o->body.data[ i ]->probe = false;
        }
    };

    func : :solve;

    func : :clear_downlinks =
    {
        BFOR_EACH( i, &o->body ) :links_s_clear( &o->body.data[ i ]->dnls );
    };

    func : :set_downlinks;

    func bcore_inst_call : copy_x; // cell is copyable

    // cell is (currently) not transferable ( possible with dedicated shelve & mutated implementation )
    func bcore_via_call  : mutated = { ERR_fa( "Cannot reconstitute." ); };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// network builder
group :builder = :
{
    signature void fork_log( mutable, bcore_sink* log );
    signature void fork_input_holors( mutable, const bhvm_holor_s** input_holors, sz_t size_input_holors );
    signature void build_from_source( mutable, opal_net_cell_s* net_cell, bcore_source* source );

    stamp : = aware :
    {
        opal_sem_builder_s sem_builder;
        hidden bhvm_holor_adl_s input_holors;
        hidden aware bcore_sink -> log;

        func : :fork_log = { bcore_sink_a_attach( &o->log, bcore_fork( log ) ); };

        func : :fork_input_holors =
        {
            bhvm_holor_adl_s_set_size( &o->input_holors, size_input_holors );
            BFOR_EACH( i, &o->input_holors )
            {
                ASSERT( input_holors[ i ] );
                bhvm_holor_s_attach( &o->input_holors.data[ i ], bcore_fork( ( bhvm_holor_s* )input_holors[ i ] ) );
            }
        };

        func : :build_from_source;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/
/// node

/// Provides necessary mcode and holor data for isolated nodes that do not actively participate in computing an output
void opal_net_node_s_isolated_mcode_push( opal_net_node_s* o, bhvm_mcode_frame_s* mcf );

/**********************************************************************************************************************/
/// cell

/** Converts opal_sem_cell_s to opal_net_cell_s
 *  Requires a double-nested frame to allow correct processing of input channels with assignments (checked).
 */
void opal_net_cell_s_from_sem_cell
(
    opal_net_cell_s* o,
    opal_sem_cell_s* sem_cell,
    opal_nop* (*input_nop_create)( vd_t arg, sz_t in_idx, tp_t in_name, const opal_nop* cur_nop ),
    vd_t arg,
    bcore_sink* log
);

void opal_net_cell_s_graph_to_sink( opal_net_cell_s* o, bcore_sink* sink );
void opal_net_cell_s_mcode_push_ap( opal_net_cell_s* o, bhvm_mcode_frame_s* mcf );
void opal_net_cell_s_mcode_push_dp( opal_net_cell_s* o, bhvm_mcode_frame_s* mcf, bl_t entry_channels );

#endif // TYPEOF_opal_net

/**********************************************************************************************************************/

vd_t opal_net_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // OPAL_NET_H
