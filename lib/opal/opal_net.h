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
#include "opal.xo.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_opal_net

XOILA_DEFINE_GROUP( opal_net, bcore_inst )
#ifdef XOILA_SECTION

stamp :link_s  = aware : { private aware :node_s* node; };
stamp :links_s = aware x_array
{
    :link_s => [];
    wrap x_array.clear;
    wrap x_array.push_d;
    wrap x_array.push;
};

signature void solve( mutable );

/// returns the uplink index pointing to node; returns -1 if not found
signature sz_t up_index( const, const :node_s* node );
signature void set_nop_d( mutable, opal_nop* nop );

// ---------------------------------------------------------------------------------------------------------------------

feature bl_t is_cyclic( const ) = { return false; };

signature void mcode_push_ap(               mutable, bhvm_mcode_frame_s* mcf );
signature void cyclic_mcode_push_ap_phase0( mutable, bhvm_mcode_frame_s* mcf );
signature void cyclic_mcode_push_ap_phase1( mutable, bhvm_mcode_frame_s* mcf );

signature void mcode_push_dp(               mutable, sz_t up_index, bhvm_mcode_frame_s* mcf );
signature void cyclic_mcode_push_dp_phase0( mutable, sz_t up_index, bhvm_mcode_frame_s* mcf );
signature void cyclic_mcode_push_dp_phase1( mutable,                bhvm_mcode_frame_s* mcf );
signature void cyclic_mcode_push_dp_phase2( mutable,                bhvm_mcode_frame_s* mcf );

/// Provides necessary mcode and holor data for isolated nodes that do not actively participate in computing an output
signature void isolated_mcode_push( mutable, bhvm_mcode_frame_s* mcf );

stamp :node_s = aware :
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

    func :.up_index =
    {
        foreach( $* e in o.upls ) if( e.node == node ) return __i;
        return -1;
    };

    func :.set_nop_d =
    {
        ASSERT( o->result == NULL );
        o.nop =< nop;
    };

    func :.is_cyclic = { return ( o.mnode ) ? o.mnode.cyclic : o.nop.is_cyclic(); };

    /// s. opal_nop_solve_node__
    func (void solve( mutable, opal_net_node_adl_s* deferred )) =
    {
        if( !o->nop ) o.err_fa( "Node has no operator." );
        o.nop.solve_node( o, deferred );
    };

    /// Outputs the graph structure in text form to sink
    func (void graph_to_sink( const, bcore_sink* sink )) = { o.trace_to_sink( 0, sink ); sink.push_fa( "\n" ); };

    /** Recursively sets downlinks for all non-flagged uplinks.
     *  Assumes initial state was normal.
     */
    func (void set_downlinks( mutable )) =
    {
        if( !o.flag )
        {
            o.flag = true;
            foreach( $* e in o.upls )
            {
                e.node.dnls.push().node = o;
                e.node.set_downlinks();
            }
        }
    };

    /** Recursively sets flags for all nodes reachable via uplink.
     *  Assumes initial state was normal.
     */
    func (void set_flags( mutable )) =
    {
        if( !o.flag )
        {
            o.flag = true;
            foreach( $* e in o->upls ) e.node.set_flags();
        }
    };

    func :.mcode_push_ap;
    func :.cyclic_mcode_push_ap_phase0;
    func :.cyclic_mcode_push_ap_phase1;
    func :.isolated_mcode_push;

    func :.mcode_push_dp;
    func :.cyclic_mcode_push_dp_phase0;
    func :.cyclic_mcode_push_dp_phase1;
    func :.cyclic_mcode_push_dp_phase2;
};

stamp :node_adl_s = aware x_array
{
    :node_s => [];
    wrap x_array.push_d;
};

signature :node_s* get_by_id( mutable, sz_t id );

stamp :nodes_s = aware x_array
{
    :node_s => [];
    func :.get_by_id =
    {
        foreach( $* e in o ) if( e.id == id ) return e;
        return NULL;
    };

    wrap x_array.set_size;
    wrap x_array.push;
    wrap x_array.push_d;
};

// ---------------------------------------------------------------------------------------------------------------------

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

    hidden aware opal_context -> context;

    func :.is_consistent;
    func :.normalize; // re-entrant

    func :.clear_flags =
    {
        foreach( $* e in o.body ) e.flag = false;
    };

    func :.clear_all_flags =
    {
        foreach( $* e in o.body )
        {
            e.flag = false;
            e.probe = false;
        }
    };

    func :.solve =
    {
        $* deferred = opal_net_node_adl_s!^^;
        foreach( $* e in o->excs  ) e.solve( deferred );
        foreach( $* e in deferred ) e.solve( NULL );
    };

    func :.clear_downlinks =
    {
        foreach( $* e in o.body ) e.dnls.clear();
    };

    func :.set_downlinks;

    func bcore_inst_call.copy_x; // cell is copyable

    // cell is (currently) not transferable ( possible with dedicated shelve & mutated implementation )
    func bcore_via_call.mutated = { ERR_fa( "Cannot reconstitute." ); };

    func (void graph_to_sink( const, bcore_sink* sink )) =
    {
        foreach( const opal_net_node_s* node in o.excs ) node.graph_to_sink( sink );
    };

    func :.mcode_push_ap;
    func (void mcode_push_dp( mutable, bhvm_mcode_frame_s* mcf, bl_t entry_channels ));

};

// ---------------------------------------------------------------------------------------------------------------------

/// Creates an input node operator at indexed global input channel
feature opal_nop* create_input_nop( const, sz_t in_idx, tp_t in_name, const opal_nop* cur_nop );

// network builder
group :builder = :
{
    signature void fork_log( mutable, bcore_sink* log );
    signature void fork_input_holors( mutable, const bhvm_holor_s** input_holors, sz_t size_input_holors );
    signature void build_from_source( mutable, opal_net_cell_s* net_cell, bcore_source* source );

    stamp :s = aware :
    {
        opal_sem_builder_s sem_builder;
        hidden bhvm_holor_adl_s input_holors;
        hidden aware bcore_sink -> log;

        func :.fork_log = { o->log =< bcore_fork( log ); };

        func :.fork_input_holors =
        {
            o.input_holors.set_size( size_input_holors );
            BFOR_EACH( i, &o->input_holors )
            {
                ASSERT( input_holors[ i ] );
                o->input_holors.[ i ] =< bcore_fork( ( bhvm_holor_s* )input_holors[ i ] );
            }
        };

        func ::.create_input_nop;

        func :.build_from_source;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

embed "opal_net.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/
/// node

/**********************************************************************************************************************/
/// cell

#endif // TYPEOF_opal_net

/**********************************************************************************************************************/

#endif // OPAL_NET_H
