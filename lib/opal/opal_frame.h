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
#include "opal.xo.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( opal_frame, bcore_inst )
#ifdef XOILA_SECTION

// ---------------------------------------------------------------------------------------------------------------------

/// holor indexing group
group :hidx =
{
    signature m @* clear( m @* o );
    signature m @* push(  m @* o, sz_t index );

    signature sz_t get_idx( c @* o, sz_t index );
    signature sz_t get_pclass_idx( c @* o, c bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );
    signature sz_t get_size( c @* o );

    signature m bhvm_holor_s*     get_holor( c @* o, c bhvm_mcode_hbase_s* hbase, sz_t index );
    signature m bhvm_mcode_hmeta* get_hmeta( c @* o, c bhvm_mcode_hbase_s* hbase, sz_t index );

    signature m bhvm_holor_s*     get_pclass_holor( c @* o, c bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );
    signature m bhvm_mcode_hmeta* get_pclass_hmeta( c @* o, c bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );

    signature m @* replace_index( m @* o, m bcore_arr_sz_s* index_map );

    stamp :s = aware :
    {
        bcore_arr_sz_s => arr;
        func :.clear     = { if( o.arr ) o.arr.clear(); return o; };
        func :.push      = { o.arr!.push( index ); return o; };

        func :.get_idx   = { assert( index >= 0 && index < o.arr.size ); return o.arr?.[ index ]; };
        func :.get_size  = { return o.arr ? o.arr.size : 0; };
        func :.get_holor = { return hbase.get_holor( o.get_idx( index ) ); };
        func :.get_hmeta = { return hbase.get_hmeta( o.get_idx( index ) ); };

        func :.get_pclass_idx =
        {
            const bhvm_mcode_hmeta* hmeta = o.get_hmeta( hbase, index );
            return ( hmeta ) ? hmeta.get_node().get_pclass_idx( pclass ) : -1;
        };

        func :.get_pclass_holor = { return hbase.get_holor( o.get_pclass_idx( hbase, pclass, index ) ); };
        func :.get_pclass_hmeta = { return hbase.get_hmeta( o.get_pclass_idx( hbase, pclass, index ) ); };

        func :.replace_index =
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

    stamp :ads_s = aware x_array
    {
        :s [];
        wrap x_array.push_c;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/// frame member functions

signature void reset( m @* o );
signature void setup( m @* o );
signature void check_integrity( c @* o );

signature m @* setup_from_source(      m @* o, m bcore_source* source, c bhvm_holor_s** en, sz_t size_en );
signature m @* setup_from_st(          m @* o,         c st_s* st,     c bhvm_holor_s** en, sz_t size_en );
signature m @* setup_from_sc(          m @* o,           sc_t  sc,     c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_source(             m bcore_source* source, c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_st(                         c st_s* st,     c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_sc(                           sc_t  sc,     c bhvm_holor_s** en, sz_t size_en );
signature m @* setup_from_source_adl(  m @* o, m bcore_source* source, c bhvm_holor_adl_s* en );
signature m @* setup_from_st_adl(      m @* o,         c st_s* st,     c bhvm_holor_adl_s* en );
signature m @* setup_from_sc_adl(      m @* o,           sc_t  sc,     c bhvm_holor_adl_s* en );
signature d @* create_from_source_adl(         m bcore_source* source, c bhvm_holor_adl_s* en );
signature d @* create_from_st_adl(                     c st_s* st,     c bhvm_holor_adl_s* en );
signature d @* create_from_sc_adl(                       sc_t  sc,     c bhvm_holor_adl_s* en );

signature sz_t get_size_en( c @* o ); // number of entry channels
signature sz_t get_size_ex( c @* o ); // number of exit channels
signature sz_t get_size_ada( c @* o ); // number of adaptive channels

signature m bhvm_holor_s* get_ap_en(  m @* o, sz_t index );
signature m bhvm_holor_s* get_dp_en(  m @* o, sz_t index );
signature m bhvm_holor_s* get_ap_ex(  m @* o, sz_t index );
signature m bhvm_holor_s* get_dp_ex(  m @* o, sz_t index );
signature m bhvm_holor_s* get_ap_ada( m @* o, sz_t index );
signature m bhvm_holor_s* get_dp_ada( m @* o, sz_t index );

signature m @* run( m @* o, tp_t track);
signature m @* run_ap(     m @* o, c bhvm_holor_s** en, sz_t size_en, m bhvm_holor_s** ex, sz_t size_ex );
signature m @* run_dp(     m @* o, c bhvm_holor_s** ex, sz_t size_ex, m bhvm_holor_s** en, sz_t size_en );
signature m @* run_ap_adl( m @* o, c bhvm_holor_adl_s* en, m bhvm_holor_adl_s* ex ); // allocates out
signature m @* run_dp_adl( m @* o, c bhvm_holor_adl_s* ex, m bhvm_holor_adl_s* en ); // allocates out

signature void disassemble_to_sink( c @* o, m bcore_sink* sink );
signature void cyclic_reset( m @* o );


/** Explicitly re-binds holors (typically by running setup tracks).
 *  This can be necessary when certain holors have been externally reallocated.
 *  Use with care!
 */
signature m @* bind_holors( m @* o );

stamp :s = aware :
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

    func :.reset =
    {
        if( !o.is_setup ) return;
        if( !o.mcf ) return;
        o.mcf.track_run( TYPEOF_track_ap_shelve );
        o.mcf.track_run( TYPEOF_track_dp_shelve );
        o.is_setup = false;
    };

    func :.bind_holors =
    {
        o.mcf.track_run( TYPEOF_track_ap_setup );
        o.mcf.track_run( TYPEOF_track_dp_setup );
        return o;
    };

    func :.setup =
    {
        if( o.is_setup ) return;
        if( !o.mcf ) return;
        o.bind_holors();
        o.is_setup = true;
    };

    func :.check_integrity =
    {
        assert( o.context );
        assert( o.mcf );
        o.mcf.check_integrity();
    };

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t is_setup = o.is_setup; o.reset(); o.is_setup = is_setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o.is_setup ) { o.reset(); o.setup(); } o.check_integrity(); };
    func bcore_inst_call . copy_x  = { if( o.is_setup ) { o.reset(); o.setup(); } o.check_integrity(); };

    /// frame setup from string or source; 'in' can be NULL
    func :.setup_from_source;
    func :.setup_from_st = { return o.setup_from_source( bcore_source_string_s_create_from_string( st ).scope(), en, size_en ); };
    func :.setup_from_sc = { return o.setup_from_st( st_s_create_sc( sc ).scope(), en, size_en ); };
    func :.create_from_source     = { return @!.setup_from_source( source, en, size_en ); };
    func :.create_from_st         = { return @!.setup_from_st( st, en, size_en ); };
    func :.create_from_sc         = { return @!.setup_from_sc( sc, en, size_en ); };
    func :.setup_from_source_adl  = { return o.setup_from_source( source, en ? en.data.cast( const bhvm_holor_s** ) : NULL, en ? en.size : 0 ); };
    func :.setup_from_st_adl      = { return o.setup_from_st( st, en ? en.data.cast( const bhvm_holor_s** ) : NULL, en ? en.size : 0 ); };
    func :.setup_from_sc_adl      = { return o.setup_from_sc( sc, en ? en.data.cast( const bhvm_holor_s** ) : NULL, en ? en.size : 0 ); };
    func :.create_from_source_adl = { return @!.setup_from_source_adl( source, en ); };
    func :.create_from_st_adl     = { return @!.setup_from_st_adl( st, en ); };
    func :.create_from_sc_adl     = { return @!.setup_from_sc_adl( sc, en ); };

    func :.get_size_en  = { return o.hidx_en .get_size(); };
    func :.get_size_ex  = { return o.hidx_ex .get_size(); };
    func :.get_size_ada = { return o.hidx_ada.get_size(); };

    func :.get_ap_en  = { return o.hidx_en .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func :.get_dp_en  = { return o.hidx_en .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };
    func :.get_ap_ex  = { return o.hidx_ex .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func :.get_dp_ex  = { return o.hidx_ex .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };
    func :.get_ap_ada = { return o.hidx_ada.get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func :.get_dp_ada = { return o.hidx_ada.get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };

    func (m @* run( m @* o, tp_t track )) =
    {
        ASSERT( o->mcf );
        o.mcf.track_run( track );
        return o;
    };

    /// resets all cyclic values to the initialization value
    func :.cyclic_reset = { o.mcf.track_run( TYPEOF_track_ap_cyclic_reset ); };

    func :.run_ap;
    func :.run_dp;
    func :.run_ap_adl;
    func :.run_dp_adl;
    func :.disassemble_to_sink;
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :custom_hmeta_s = aware :
{
    sz_t ur_slot;
    sz_t ur_src;
};

// ---------------------------------------------------------------------------------------------------------------------

signature void setup_from_frame( m @* o, c opal_frame_s* frame, sz_t unroll_size );

/// resets cyclic values; runs track_ap for all slots assuming all input/output holors are provided in sequence
signature void run_ap_adl_flat( m @* o, c bhvm_holor_adl_s* en, m bhvm_holor_adl_s* ex );

/// runs track_dp for all slots assuming all input/output holors are provided in sequence
signature void run_dp_adl_flat( m @* o, c bhvm_holor_adl_s* ex, m bhvm_holor_adl_s* en );

/// frame specialized in unrolling cyclic networks
stamp :cyclic_s = aware :
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
    func :.bind_holors;
    func :.reset;
    func :.setup;

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t is_setup = o.is_setup; o.reset(); o.is_setup = is_setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o.is_setup ) { o.reset(); o.setup(); } };
    func bcore_inst_call . copy_x  = { if( o.is_setup ) { o.reset(); o.setup(); } };

    func :.get_size_en  = { return o.frame.get_size_en(); };
    func :.get_size_ex  = { return o.frame.get_size_ex(); };
    func :.get_size_ada = { return o.frame.get_size_ada(); };

    func :.run_ap;
    func :.run_ap_adl;
    func :.run_ap_adl_flat;
    func :.run_dp_adl_flat;

    func :.setup_from_frame;

    func :.disassemble_to_sink;

    /// resets all cyclic values to the initialization value
    func :.cyclic_reset =
    {
        o.frame.mcf.track_run( TYPEOF_track_ap_cyclic_reset );
        o.unroll_index = 0;
    };

};

// ---------------------------------------------------------------------------------------------------------------------

func (void sc_run_ap( sc_t sc, c bhvm_holor_s** en, sz_t size_en, m bhvm_holor_s** ex, sz_t size_ex )) =
{
    opal_frame_s_create_from_sc( sc, en, size_en ).scope().run_ap( en, size_en, ex, size_ex );
};

// ---------------------------------------------------------------------------------------------------------------------

func (void sc_run_dp( sc_t sc, c bhvm_holor_s** ex, sz_t size_ex, m bhvm_holor_s** en, sz_t size_en )) =
{
    opal_frame_s_create_from_sc( sc, ex, size_ex ).scope().run_dp( ex, size_ex, en, size_en );
};

// ---------------------------------------------------------------------------------------------------------------------

embed "opal_frame.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/

#endif // OPAL_FRAME_H
