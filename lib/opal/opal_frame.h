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

/** A frame is a self contained operator on holors for axon- and dendrite pass
 *  It is designed combining net semantics with HVM
 */

/**********************************************************************************************************************/

#ifndef OPAL_FRAME_H
#define OPAL_FRAME_H

#include "opal_net.h"
#include "opal_xoila_out.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( opal_frame, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// holor indexing group
group :hidx =
{
    signature @* clear( mutable );
    signature @* push(  mutable, sz_t index );

    signature sz_t get_idx( const, sz_t index );
    signature sz_t get_pclass_idx( const, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );
    signature sz_t get_size( const );

    signature bhvm_holor_s*     get_holor( const, const bhvm_mcode_hbase_s* hbase, sz_t index );
    signature bhvm_mcode_hmeta* get_hmeta( const, const bhvm_mcode_hbase_s* hbase, sz_t index );

    signature bhvm_holor_s*     get_pclass_holor( const, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );
    signature bhvm_mcode_hmeta* get_pclass_hmeta( const, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );

    signature @* replace_index( mutable, bcore_arr_sz_s* index_map );

    stamp : = aware :
    {
        bcore_arr_sz_s => arr;
        func : .clear     = { if( o.arr ) o.arr.clear(); return o; };
        func : .push      = { o.arr!.push( index ); return o; };

        func : .get_idx   = { assert( index >= 0 && index < o.arr->size ); return o.arr?.[ index ]; };
        func : .get_size  = { return o.arr ? o.arr->size : 0; };
        func : .get_holor = { return hbase.get_holor( o.get_idx( index ) ); };
        func : .get_hmeta = { return hbase.get_hmeta( o.get_idx( index ) ); };

        func : .get_pclass_idx =
        {
            const bhvm_mcode_hmeta* hmeta = o.get_hmeta( hbase, index );
            return ( hmeta ) ? hmeta.get_node().get_pclass_idx( pclass ) : -1;
        };

        func : .get_pclass_holor = { return hbase.get_holor( o.get_pclass_idx( hbase, pclass, index ) ); };
        func : .get_pclass_hmeta = { return hbase.get_hmeta( o.get_pclass_idx( hbase, pclass, index ) ); };

        func : .replace_index =
        {
            foreach( sz_t* e in o.arr )
            {
                sz_t old_index = *e;
                assert( old_index >= 0 && old_index < index_map->size );
                sz_t new_index = index_map.[ old_index ];
                if( new_index >= 0 ) *e = new_index;
            }
            return o;
        };

    };

    stamp :ads = aware bcore_array { :s []; };
};

/// frame member functions

signature void reset( mutable );
signature void setup( mutable );
signature void check_integrity( const );

signature @* setup_from_source(      mutable, bcore_source* source, const bhvm_holor_s** en, sz_t size_en );
signature @* setup_from_st(          mutable,   const st_s* st,     const bhvm_holor_s** en, sz_t size_en );
signature @* setup_from_sc(          mutable,         sc_t  sc,     const bhvm_holor_s** en, sz_t size_en );
signature @* create_from_source(     plain,   bcore_source* source, const bhvm_holor_s** en, sz_t size_en );
signature @* create_from_st(         plain,     const st_s* st,     const bhvm_holor_s** en, sz_t size_en );
signature @* create_from_sc(         plain,           sc_t  sc,     const bhvm_holor_s** en, sz_t size_en );
signature @* setup_from_source_adl(  mutable, bcore_source* source, const bhvm_holor_adl_s* en );
signature @* setup_from_st_adl(      mutable,   const st_s* st,     const bhvm_holor_adl_s* en );
signature @* setup_from_sc_adl(      mutable,         sc_t  sc,     const bhvm_holor_adl_s* en );
signature @* create_from_source_adl( plain,   bcore_source* source, const bhvm_holor_adl_s* en );
signature @* create_from_st_adl(     plain,     const st_s* st,     const bhvm_holor_adl_s* en );
signature @* create_from_sc_adl(     plain,           sc_t  sc,     const bhvm_holor_adl_s* en );

signature sz_t get_size_en( const ); // number of entry channels
signature sz_t get_size_ex( const ); // number of exit channels
signature sz_t get_size_ada( const ); // number of adaptive channels

signature bhvm_holor_s* get_ap_en(  mutable, sz_t index );
signature bhvm_holor_s* get_dp_en(  mutable, sz_t index );
signature bhvm_holor_s* get_ap_ex(  mutable, sz_t index );
signature bhvm_holor_s* get_dp_ex(  mutable, sz_t index );
signature bhvm_holor_s* get_ap_ada( mutable, sz_t index );
signature bhvm_holor_s* get_dp_ada( mutable, sz_t index );

signature @* run( mutable, tp_t track);
signature @* run_ap(     mutable, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex );
signature @* run_dp(     mutable, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en );
signature @* run_ap_adl( mutable, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex ); // allocates out
signature @* run_dp_adl( mutable, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en ); // allocates out

/** Explicitly re-binds holors (typically by running setup tracks).
 *  This can be necessary when certain holors have been externally reallocated.
 *  Use with care!
 */
signature @* bind_holors( mutable );

stamp : = aware :
{
    /// pre-setup parameters
    aware bcore_sink -> log;

    /// In frames the context is part of the regular parameter set including serialization.
    aware opal_context -> context;

    /// post-setup data
    bhvm_mcode_frame_s => mcf;

    bl_t is_cyclic; // indicates that the underlying graph is cyclic

    /// frame has been setup
    bl_t is_setup;

    sz_t size_en; // number of entry holors (per ap/dp cycle)
    sz_t size_ex; // number of exit holors (per ap/dp cycle)

    :hidx_s hidx_en;  // entry index
    :hidx_s hidx_ex;  // exit index
    :hidx_s hidx_ada; // adaptive index

    func : .reset =
    {
        if( !o.is_setup ) return;
        if( !o.mcf ) return;
        o.mcf.track_run( TYPEOF_track_ap_shelve );
        o.mcf.track_run( TYPEOF_track_dp_shelve );
        o.is_setup = false;
    };

    func : .bind_holors =
    {
        o.mcf.track_run( TYPEOF_track_ap_setup );
        o.mcf.track_run( TYPEOF_track_dp_setup );
        return o;
    };

    func : .setup =
    {
        if( o.is_setup ) return;
        if( !o.mcf ) return;
        o.bind_holors();
        o.is_setup = true;
    };

    func : .check_integrity;

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t is_setup = o.is_setup; o.reset(); o.is_setup = is_setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o.is_setup ) { o.reset(); o.setup(); } o.check_integrity(); };
    func bcore_inst_call . copy_x  = { if( o.is_setup ) { o.reset(); o.setup(); } o.check_integrity(); };

    /// frame setup from string or source; 'in' can be NULL
    func : .setup_from_source;
    func : .setup_from_st = { BLM_INIT(); BLM_RETURNV( @*, o.setup_from_source( BLM_A_PUSH( bcore_source_string_s_create_from_string( st ) ), en, size_en ) ); };
    func : .setup_from_sc = { st_s st; st_s_init_weak_sc( &st, sc ); return @_setup_from_st( o, &st, en, size_en ); };
    func : .create_from_source     = { return (@!).setup_from_source( source, en, size_en ); };
    func : .create_from_st         = { return (@!).setup_from_st(     st,     en, size_en ); };
    func : .create_from_sc         = { return (@!).setup_from_sc(     sc,     en, size_en ); };
    func : .setup_from_source_adl  = { return o.setup_from_source( source, en ? ( const bhvm_holor_s** )en.data : NULL, en ? en.size : 0 ); };
    func : .setup_from_st_adl      = { return o.setup_from_st(     st,     en ? ( const bhvm_holor_s** )en.data : NULL, en ? en.size : 0 ); };
    func : .setup_from_sc_adl      = { return o.setup_from_sc(     sc,     en ? ( const bhvm_holor_s** )en.data : NULL, en ? en.size : 0 ); };
    func : .create_from_source_adl = { return (@!).setup_from_source_adl( source, en ); };
    func : .create_from_st_adl     = { return (@!).setup_from_st_adl(         st, en ); };
    func : .create_from_sc_adl     = { return (@!).setup_from_sc_adl(         sc, en ); };

    func : .get_size_en  = { return o.hidx_en .get_size(); };
    func : .get_size_ex  = { return o.hidx_ex .get_size(); };
    func : .get_size_ada = { return o.hidx_ada.get_size(); };

    func : .get_ap_en  = { return o.hidx_en .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func : .get_dp_en  = { return o.hidx_en .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };
    func : .get_ap_ex  = { return o.hidx_ex .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func : .get_dp_ex  = { return o.hidx_ex .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };
    func : .get_ap_ada = { return o.hidx_ada.get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func : .get_dp_ada = { return o.hidx_ada.get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };

    func : .run_ap;
    func : .run_dp;
    func : .run_ap_adl;
    func : .run_dp_adl;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :custom_hmeta = aware :
{
    sz_t ur_slot;
    sz_t ur_src;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// frame specialized in unrolling cyclic networks
stamp :cyclic = aware :
{
    /// pre-setup parameters
    :s => frame;

    /// number of unrolled cycles
    sz_t unroll_size = 2;

    /// state data ...

    /// frame has been setup
    bl_t is_setup = false;

    /// current unroll process index
    sz_t unroll_index = 0;

    /// unrolled ap tracks
    bhvm_mcode_track_adl_s => track_adl_ap;
    bhvm_mcode_track_adl_s => track_adl_dp;
    bhvm_mcode_track_adl_s => track_adl_ap_setup;

    /// unrolled hindex
    :hidx_ads_s hidx_ads_en;  // entry index
    :hidx_ads_s hidx_ads_ex;  // exit index

    /// functions ...
    func : .bind_holors;
    func : .reset;
    func : .setup;

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t is_setup = o.is_setup; o.reset(); o.is_setup = is_setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o.is_setup ) { o.reset(); o.setup(); } };
    func bcore_inst_call . copy_x  = { if( o.is_setup ) { o.reset(); o.setup(); } };

    func : .get_size_en  = { return o.frame.get_size_en(); };
    func : .get_size_ex  = { return o.frame.get_size_ex(); };
    func : .get_size_ada = { return o.frame.get_size_ada(); };

    func : .run_ap;
    func : .run_ap_adl;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void opal_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex );
void opal_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en );

/// resets all cyclic values to the initialization value
void opal_frame_s_cyclic_reset( opal_frame_s* o );

void opal_frame_s_disassemble_to_sink( const opal_frame_s* o, bcore_sink* sink );

void opal_frame_cyclic_s_setup_from_frame( opal_frame_cyclic_s* o, const opal_frame_s* frame, sz_t unroll_size );

void opal_frame_cyclic_s_disassemble_to_sink( const opal_frame_cyclic_s* o, bcore_sink* sink );

/// resets all cyclic values to the initialization
void opal_frame_cyclic_s_cyclic_reset( opal_frame_cyclic_s* o );

/// resets cyclic values; runs track_ap for all slots assuming all input/output holors are provided in sequence
void opal_frame_cyclic_s_run_ap_adl_flat( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex );

///  runs track_dp for all slots assuming all input/output holors are provided in sequence
void opal_frame_cyclic_s_run_dp_adl_flat( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en );

/**********************************************************************************************************************/

#endif // OPAL_FRAME_H
