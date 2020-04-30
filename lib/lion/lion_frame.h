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

#ifndef LION_FRAME_H
#define LION_FRAME_H

#include "lion_net.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_frame

PLANT_GROUP( lion_frame, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
        func : :clear     = { if( o->arr ) bcore_arr_sz_s_clear( o->arr ); return o; };
        func : :push      = { if( !o->arr ) o->arr = bcore_arr_sz_s_create(); bcore_arr_sz_s_push( o->arr, index ); return o; };

        func : :get_idx   = { assert( o->arr ); assert( index >= 0 && index < o->arr->size ); return o->arr->data[ index ]; };
        func : :get_size  = { return o->arr ? o->arr->size : 0; };
        func : :get_holor = { return bhvm_mcode_hbase_s_get_holor( hbase, @_get_idx( o, index ) ); };
        func : :get_hmeta = { return bhvm_mcode_hbase_s_get_hmeta( hbase, @_get_idx( o, index ) ); };

        func : :get_pclass_idx =
        {
            const bhvm_mcode_hmeta* hmeta = @_get_hmeta( o, hbase, index );
            if( hmeta ) return bhvm_mcode_node_s_get_pclass_idx( bhvm_mcode_hmeta_a_get_node( hmeta ), pclass );
            return -1;
        };

        func : :get_pclass_holor = { return bhvm_mcode_hbase_s_get_holor( hbase, @_get_pclass_idx( o, hbase, pclass, index ) ); };
        func : :get_pclass_hmeta = { return bhvm_mcode_hbase_s_get_hmeta( hbase, @_get_pclass_idx( o, hbase, pclass, index ) ); };

        func : :replace_index =
        {
            BFOR_EACH( i, o->arr )
            {
                sz_t old_index = o->arr->data[ i ];
                assert( old_index >= 0 && old_index < index_map->size );
                sz_t new_index = index_map->data[ old_index ];
                if( new_index >= 0 ) o->arr->data[ i ] = new_index;
            }
            return o;
        };

    };

    stamp :ads = aware bcore_array { :s []; };
};

/// frame member functions

signature @* mutab_from_source( mutable, bcore_source* source );
signature @* mutab_from_st(     mutable, const st_s* st );
signature @* mutab_from_sc(     mutable,       sc_t  sc );
signature @* plain_from_source(   plain,  bcore_source* source );
signature @* plain_from_st(       plain,  const st_s* st );
signature @* plain_from_sc(       plain,        sc_t  sc );

signature void reset( mutable );
signature void setup( mutable );
signature void check_integrity( const );

signature :mutab_from_source setup_from_source(      const bhvm_holor_s** en );
signature :mutab_from_st     setup_from_st(          const bhvm_holor_s** en );
signature :mutab_from_sc     setup_from_sc(          const bhvm_holor_s** en );
signature :plain_from_source create_from_source(     const bhvm_holor_s** en );
signature :plain_from_st     create_from_st(         const bhvm_holor_s** en );
signature :plain_from_sc     create_from_sc(         const bhvm_holor_s** en );
signature :mutab_from_source setup_from_source_adl(  const bhvm_holor_adl_s* en );
signature :mutab_from_st     setup_from_st_adl(      const bhvm_holor_adl_s* en );
signature :mutab_from_sc     setup_from_sc_adl(      const bhvm_holor_adl_s* en );
signature :plain_from_source create_from_source_adl( const bhvm_holor_adl_s* en );
signature :plain_from_st     create_from_st_adl(     const bhvm_holor_adl_s* en );
signature :plain_from_sc     create_from_sc_adl(     const bhvm_holor_adl_s* en );

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
signature @* run_ap(     mutable, const bhvm_holor_s**    en, bhvm_holor_s**    ex );
signature @* run_dp(     mutable, const bhvm_holor_s**    ex, bhvm_holor_s**    en );
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

    /// post-setup data
    bhvm_mcode_frame_s => mcf;

    bl_t is_cyclic; // indicates that the underlying graph is cyclic

    /// frame has been setup
    bl_t setup;

    sz_t size_en; // number of entry holors (per ap/dp cycle)
    sz_t size_ex; // number of exit holors (per ap/dp cycle)

    :hidx_s hidx_en;  // entry index
    :hidx_s hidx_ex;  // exit index
    :hidx_s hidx_ada; // adaptive index

    func : :reset =
    {
        if( !o->setup ) return;
        if( !o->mcf ) return;
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_shelve );
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp_shelve );
        o->setup = false;
    };

    func : :bind_holors =
    {
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_setup );
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp_setup );
        return o;
    };

    func : :setup =
    {
        if( o->setup ) return;
        if( !o->mcf ) return;
        @_bind_holors( o );
        o->setup = true;
    };

    func : :check_integrity;

    /// shelving/reconstitution
    func bcore_via_call  : shelve  = { bl_t setup = o->setup; @_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  : mutated = { if( o->setup ) { @_reset( o ); @_setup( o ); }  @_check_integrity( o ); };
    func bcore_inst_call : copy_x  = { if( o->setup ) { @_reset( o ); @_setup( o ); }  @_check_integrity( o ); };

    /// frame setup from string or source; 'in' can be NULL
    func : :setup_from_source;
    func : :setup_from_st = { BLM_INIT(); BLM_RETURNV( @*, @_setup_from_source( o, BLM_A_PUSH( bcore_source_string_s_create_from_string( st ) ), en ) ); };
    func : :setup_from_sc = { st_s st; st_s_init_weak_sc( &st, sc ); return @_setup_from_st( o, &st, en ); };
    func : :create_from_source     = { @* o = @_create(); return @_setup_from_source( o, source, en ); };
    func : :create_from_st         = { @* o = @_create(); return @_setup_from_st(     o, st,     en ); };
    func : :create_from_sc         = { @* o = @_create(); return @_setup_from_sc(     o, sc,     en ); };
    func : :setup_from_source_adl  = { return @_setup_from_source( o, source, en ? ( const bhvm_holor_s** )en->data : NULL ); };
    func : :setup_from_st_adl      = { return @_setup_from_st(     o, st,     en ? ( const bhvm_holor_s** )en->data : NULL ); };
    func : :setup_from_sc_adl      = { return @_setup_from_sc(     o, sc,     en ? ( const bhvm_holor_s** )en->data : NULL ); };
    func : :create_from_source_adl = { return @_create_from_source( source,   en ? ( const bhvm_holor_s** )en->data : NULL ); };
    func : :create_from_st_adl     = { return @_create_from_st( st,           en ? ( const bhvm_holor_s** )en->data : NULL ); };
    func : :create_from_sc_adl     = { return @_create_from_sc( sc,           en ? ( const bhvm_holor_s** )en->data : NULL ); };

    func : :get_size_en  = { return :hidx_s_get_size( &o->hidx_en ); };
    func : :get_size_ex  = { return :hidx_s_get_size( &o->hidx_ex ); };
    func : :get_size_ada = { return :hidx_s_get_size( &o->hidx_ada ); };

    func : :get_ap_en  = { return :hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ax0, index ); };
    func : :get_dp_en  = { return :hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ag0, index ); };
    func : :get_ap_ex  = { return :hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ax0, index ); };
    func : :get_dp_ex  = { return :hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ag0, index ); };
    func : :get_ap_ada = { return :hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ax0, index ); };
    func : :get_dp_ada = { return :hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ag0, index ); };

    func : :run_ap;
    func : :run_dp;
    func : :run_ap_adl;
    func : :run_dp_adl;
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
    bl_t setup = false;

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
    func : :bind_holors;
    func : :reset;
    func : :setup;

    /// shelving/reconstitution
    func bcore_via_call  : shelve  = { bl_t setup = o->setup; @_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  : mutated = { if( o->setup ) { @_reset( o ); @_setup( o ); } };
    func bcore_inst_call : copy_x  = { if( o->setup ) { @_reset( o ); @_setup( o ); } };

    func : :get_size_en  = { return :s_get_size_en(  o->frame ); };
    func : :get_size_ex  = { return :s_get_size_ex(  o->frame ); };
    func : :get_size_ada = { return :s_get_size_ada( o->frame ); };

    func : :run_ap;
    func : :run_ap_adl;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lion_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** en, bhvm_holor_s** ex );
void lion_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** ex, bhvm_holor_s** en );

/// resets all cyclic values to the initialization
void lion_frame_s_cyclic_reset( lion_frame_s* o );

void lion_frame_s_disassemble_to_sink( const lion_frame_s* o, bcore_sink* sink );

void lion_frame_cyclic_s_setup_from_frame( lion_frame_cyclic_s* o, const lion_frame_s* frame, sz_t unroll_size );

void lion_frame_cyclic_s_disassemble_to_sink( const lion_frame_cyclic_s* o, bcore_sink* sink );

/// resets all cyclic values to the initialization
void lion_frame_cyclic_s_cyclic_reset( lion_frame_cyclic_s* o );

/// resets cyclic values; runs track_ap for all slots assuming all input/output holors are provided in sequence
void lion_frame_cyclic_s_run_ap_adl_flat( lion_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex );

///  runs track_dp for all slots assuming all input/output holors are provided in sequence
void lion_frame_cyclic_s_run_dp_adl_flat( lion_frame_cyclic_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en );

#endif // TYPEOF_lion_frame

/**********************************************************************************************************************/

vd_t lion_frame_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_FRAME_H
