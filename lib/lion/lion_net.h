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
#include "lion_planted.h"

/**********************************************************************************************************************/

/// Tree group
#ifdef TYPEOF_lion_ctr

PLANT_GROUP( lion_ctr, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node = aware bcore_array
{
    sz_t id = -1;
    private lion_sem_cell_s -> cell;
    private :node_s -> parent;
    :node_s => [];
};

stamp :tree = aware :
{
    sz_t id_base = 0; // (incremented when adding nodes)
    :node_s => root;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_ctr

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_net

PLANT_GROUP( lion_net, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :link = aware :
{
    hidden vd_t /* :node_s* */ node; // (!) target is a node
};

stamp :links = aware bcore_array { :link_s => []; };

signature void solve( mutable );

/// returns the uplink index pointing to node; returns -1 if not found
signature sz_t up_index( const, const :node_s* node );
signature void set_nop_d( mutable, lion_nop* nop );

stamp :node = aware :
{
    :links_s upls; // uplinks
    :links_s dnls; // downlinks

    /** Temporary flag used for various tracing routines.
      * It is typically used to ensure a node is visited only once.
      * Normalized state: false
      */
    bl_t flag = false;

    /** Node ID.
     *  When the network cell is normalized, id is identical with the cell->body index.
     */
    sz_t id;

    /** Holor index.
     *  Indicates the location of the axon-holor for the node in the mcode framework.
     *  -1 means: Holor is not specified
     */
    sz_t hidx = -1;

    /** Gradient index.
     *  Indicates the location of the gradient holor for the node in the mcode framework.
     *  -1 means: Node needs no gradient or gradient is not specified;
     */
    sz_t gidx = -1;

    tp_t name;
    aware lion_nop -> nop;

    lion_nop_solve_result_s => result;

    hidden bcore_source_point_s -> source_point;

    func : :solve;

    func : :up_index =
    {
        BFOR_EACH( i, &o->upls ) if( o->upls.data[ i ]->node == node ) return i;
        return -1;
    };

    func : :set_nop_d =
    {
        ASSERT( o->result == NULL );
        lion_nop_a_attach( &o->nop, nop );
    };
};

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

signature void normalize( mutable );
signature void clear_flags( mutable );
signature bl_t is_consistent( const );
signature void clear_downlinks( mutable );
signature void set_downlinks( mutable );

stamp :cell = aware :
{
    sz_t max_depth = 32768; // maximum recursion depth
    :nodes_s body;
    :nodes_s encs; // entry channels
    :nodes_s excs; // exit channels

    func : :is_consistent;
    func : :normalize; // re-entrant

    func : :clear_flags =
    {
        BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
    };

    func : :solve =
    {
        BFOR_EACH( i, &o->excs ) :node_s_solve( o->excs.data[ i ] );
    };

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

/// A frame is a self contained operator on holors for axon- and dendrite pass

/// frame member functions

signature @* mutab_from_source( mutable, bcore_source* source );
signature @* mutab_from_st(     mutable, const st_s* st );
signature @* mutab_from_sc(     mutable,       sc_t  sc );
signature @* plain_from_source(   plain,  bcore_source* source );
signature @* plain_from_st(       plain,  const st_s* st );
signature @* plain_from_sc(       plain,        sc_t  sc );

signature :mutab_from_source setup_from_source(  const bhvm_holor_s** in );
signature :mutab_from_st     setup_from_st(      const bhvm_holor_s** in );
signature :mutab_from_sc     setup_from_sc(      const bhvm_holor_s** in );
signature :plain_from_source create_from_source( const bhvm_holor_s** in );
signature :plain_from_st     create_from_st(     const bhvm_holor_s** in );
signature :plain_from_sc     create_from_sc(     const bhvm_holor_s** in );
signature :mutab_from_source setup_from_source_adl(  const bhvm_holor_adl_s* in );
signature :mutab_from_st     setup_from_st_adl(      const bhvm_holor_adl_s* in );
signature :mutab_from_sc     setup_from_sc_adl(      const bhvm_holor_adl_s* in );
signature :plain_from_source create_from_source_adl( const bhvm_holor_adl_s* in );
signature :plain_from_st     create_from_st_adl(     const bhvm_holor_adl_s* in );
signature :plain_from_sc     create_from_sc_adl(     const bhvm_holor_adl_s* in );

signature sz_t get_size_en( const ); // number of entry channels
signature sz_t get_size_ex( const ); // number of exit channels
signature sz_t get_size_ada( const ); // number of adaptive channels

signature bhvm_holor_s* get_ap_en( mutable, sz_t index );
signature bhvm_holor_s* get_dp_en( mutable, sz_t index );
signature bhvm_holor_s* get_ap_ex( mutable, sz_t index );
signature bhvm_holor_s* get_dp_ex( mutable, sz_t index );
signature bhvm_holor_s* get_ap_ada( mutable, sz_t index );
signature bhvm_holor_s* get_dp_ada( mutable, sz_t index );

signature @* run( mutable, tp_t track);
signature @* run_ap(     mutable, const bhvm_holor_s**    in, bhvm_holor_s**    out );
signature @* run_dp(     mutable, const bhvm_holor_s**    in, bhvm_holor_s**    out );
signature @* run_ap_adl( mutable, const bhvm_holor_adl_s* in, bhvm_holor_adl_s* out ); // allocates out
signature @* run_dp_adl( mutable, const bhvm_holor_adl_s* in, bhvm_holor_adl_s* out ); // allocates out

stamp :frame = aware :
{
    bhvm_mcode_frame_s => mcf;
    bcore_arr_sz_s => idx_ap_en; // ap entry-holors
    bcore_arr_sz_s => idx_dp_en; // dp entry-holors (gradients)

    bcore_arr_sz_s => idx_ap_ex; // ap exit-holors
    bcore_arr_sz_s => idx_dp_ex; // dp exit-holors (gradients)

    bcore_arr_sz_s => idx_ap_ada; // ap adaptive-holors
    bcore_arr_sz_s => idx_dp_ada; // dp adaptive-holors

    /// microcode disassembly (set log to be populated during setup)
    hidden aware bcore_sink -> mcode_log;

    /// shelving/reconstitution
    func bcore_via_call : shelve =
    {
        if( !o->mcf ) return;
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_shelve_ap );
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_shelve_dp );
    };

    func bcore_via_call : mutated =
    {
        if( !o->mcf ) return;
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_setup_ap );
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_setup_dp );
    };

    func bcore_inst_call : copy_x = { @_mutated( o ); };

    /// frame setup from string or source; 'in' can be NULL
    func : :setup_from_source;
    func : :setup_from_st = { BLM_INIT(); BLM_RETURNV( @*, @_setup_from_source( o, BLM_A_PUSH( bcore_source_string_s_create_from_string( st ) ), in ) ); };
    func : :setup_from_sc = { st_s st; st_s_init_weak_sc( &st, sc ); return @_setup_from_st( o, &st, in ); };
    func : :create_from_source     = { @* o = @_create(); return @_setup_from_source( o, source, in ); };
    func : :create_from_st         = { @* o = @_create(); return @_setup_from_st(     o, st,     in ); };
    func : :create_from_sc         = { @* o = @_create(); return @_setup_from_sc(     o, sc,     in ); };
    func : :setup_from_source_adl  = { return @_setup_from_source( o, source, in ? ( const bhvm_holor_s** )in->data : NULL ); };
    func : :setup_from_st_adl      = { return @_setup_from_st(     o, st,     in ? ( const bhvm_holor_s** )in->data : NULL ); };
    func : :setup_from_sc_adl      = { return @_setup_from_sc(     o, sc,     in ? ( const bhvm_holor_s** )in->data : NULL ); };
    func : :create_from_source_adl = { return @_create_from_source( source,   in ? ( const bhvm_holor_s** )in->data : NULL ); };
    func : :create_from_st_adl     = { return @_create_from_st( st,           in ? ( const bhvm_holor_s** )in->data : NULL ); };
    func : :create_from_sc_adl     = { return @_create_from_sc( sc,           in ? ( const bhvm_holor_s** )in->data : NULL ); };

    func : :get_size_en  = { return o->idx_ap_en ? o->idx_ap_en->size : 0; };
    func : :get_size_ex  = { return o->idx_ap_ex ? o->idx_ap_ex->size : 0; };
    func : :get_size_ada = { return o->idx_ap_ada ? o->idx_ap_ada->size : 0; };

    func : :get_ap_en = { assert( o->idx_ap_en ); assert( index >= 0 && index < o->idx_ap_en->size ); return &o->mcf->hbase->holor_ads.data[ o->idx_ap_en->data[ index ] ]; };
    func : :get_dp_en = { assert( o->idx_dp_en ); assert( index >= 0 && index < o->idx_dp_en->size ); return &o->mcf->hbase->holor_ads.data[ o->idx_dp_en->data[ index ] ]; };
    func : :get_ap_ex = { assert( o->idx_ap_ex ); assert( index >= 0 && index < o->idx_ap_ex->size ); return &o->mcf->hbase->holor_ads.data[ o->idx_ap_ex->data[ index ] ]; };
    func : :get_dp_ex = { assert( o->idx_dp_ex ); assert( index >= 0 && index < o->idx_dp_ex->size ); return &o->mcf->hbase->holor_ads.data[ o->idx_dp_ex->data[ index ] ]; };

    func : :get_ap_ada = { assert( o->idx_ap_ada ); assert( index >= 0 && index < o->idx_ap_ada->size ); return &o->mcf->hbase->holor_ads.data[ o->idx_ap_ada->data[ index ] ]; };
    func : :get_dp_ada = { assert( o->idx_dp_ada ); assert( index >= 0 && index < o->idx_dp_ada->size ); return &o->mcf->hbase->holor_ads.data[ o->idx_dp_ada->data[ index ] ]; };

    func : :run;
    func : :run_ap;
    func : :run_dp;
    func : :run_ap_adl;
    func : :run_dp_adl;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

/**********************************************************************************************************************/
/// frame

void lion_net_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out );
void lion_net_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out );

/** Estimates jacobians for entry and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [in-channels][out-channels]
 */
void lion_net_frame_s_estimate_jacobian_en( const lion_net_frame_s* o, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl );

/** Estimates jacobians for adaptive and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [ada-channels][out-channels]
 */
void lion_net_frame_s_estimate_jacobian_ada( const lion_net_frame_s* o, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl );

#endif // TYPEOF_lion_net

/**********************************************************************************************************************/

vd_t lion_net_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_NET_H
