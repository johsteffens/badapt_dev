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
#include "lion.xo.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_frame

XOILA_DEFINE_GROUP( lion_frame, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
        func : .clear     = { if( o->arr ) bcore_arr_sz_s_clear( o->arr ); return o; };
        func : .push      = { if( !o->arr ) o->arr = bcore_arr_sz_s_create(); bcore_arr_sz_s_push( o->arr, index ); return o; };

        func : .get_idx   = { assert( o->arr ); assert( index >= 0 && index < o->arr->size ); return o->arr->data[ index ]; };
        func : .get_size  = { return o->arr ? o->arr->size : 0; };
        func : .get_holor = { return bhvm_mcode_hbase_s_get_holor( hbase, @_get_idx( o, index ) ); };
        func : .get_hmeta = { return bhvm_mcode_hbase_s_get_hmeta( hbase, @_get_idx( o, index ) ); };

        func : .get_pclass_idx =
        {
            c bhvm_mcode_hmeta* hmeta = @_get_hmeta( o, hbase, index );
            if( hmeta ) return bhvm_mcode_node_s_get_pclass_idx( bhvm_mcode_hmeta_a_get_node( hmeta ), pclass );
            return -1;
        };

        func : .get_pclass_holor = { return bhvm_mcode_hbase_s_get_holor( hbase, @_get_pclass_idx( o, hbase, pclass, index ) ); };
        func : .get_pclass_hmeta = { return bhvm_mcode_hbase_s_get_hmeta( hbase, @_get_pclass_idx( o, hbase, pclass, index ) ); };

        func : .replace_index =
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

    stamp :ads_s = aware x_array
    {
        :s [];
        wrap x_array.push_c;
    };
};

/// frame member functions

signature void reset( m @* o );
signature void setup( m @* o );
signature void check_integrity( c @* o );

signature m @* setup_from_source(      m @* o, m bcore_source* source, c bhvm_holor_s** en, sz_t size_en );
signature m @* setup_from_st(          m @* o,         c st_s* st,     c bhvm_holor_s** en, sz_t size_en );
signature m @* setup_from_sc(          m @* o,           sc_t  sc,     c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_source(             m bcore_source* source, c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_st(                        c st_s* st,      c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_sc(                          sc_t  sc,      c bhvm_holor_s** en, sz_t size_en );
signature m @* setup_from_source_adl(  m @* o, m bcore_source* source, c bhvm_holor_adl_s* en );
signature m @* setup_from_st_adl(      m @* o,        c st_s* st,      c bhvm_holor_adl_s* en );
signature m @* setup_from_sc_adl(      m @* o,          sc_t  sc,      c bhvm_holor_adl_s* en );
signature d @* create_from_source_adl(         m bcore_source* source, c bhvm_holor_adl_s* en );
signature d @* create_from_st_adl(                    c st_s* st,      c bhvm_holor_adl_s* en );
signature d @* create_from_sc_adl(                      sc_t  sc,      c bhvm_holor_adl_s* en );

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

/** Explicitly re-binds holors (typically by running setup tracks).
 *  This can be necessary when certain holors have been externally reallocated.
 *  Use with care!
 */
signature m @* bind_holors( m @* o );

stamp :s = aware :
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

    func : .reset =
    {
        if( !o->setup ) return;
        if( !o->mcf ) return;
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_shelve );
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp_shelve );
        o->setup = false;
    };

    func : .bind_holors =
    {
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_setup );
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp_setup );
        return o;
    };

    func : .setup =
    {
        if( o->setup ) return;
        if( !o->mcf ) return;
        @_bind_holors( o );
        o->setup = true;
    };

    func : .check_integrity;

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t setup = o->setup; @_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o->setup ) { @_reset( o ); @_setup( o ); }  @_check_integrity( o ); };
    func bcore_inst_call . copy_x  = { if( o->setup ) { @_reset( o ); @_setup( o ); }  @_check_integrity( o ); };

    /// frame setup from string or source; 'in' can be NULL
    func : .setup_from_source;
    func : .setup_from_st = { BLM_INIT(); BLM_RETURNV( @*, @_setup_from_source( o, BLM_A_PUSH( bcore_source_string_s_create_from_string( st ) ), en, size_en ) ); };
    func : .setup_from_sc = { st_s st; st_s_init_weak_sc( &st, sc ); return @_setup_from_st( o, &st, en, size_en ); };
    func : .create_from_source     = { d @* o = @_create(); return @_setup_from_source( o, source, en, size_en ); };
    func : .create_from_st         = { d @* o = @_create(); return @_setup_from_st(     o, st,     en, size_en ); };
    func : .create_from_sc         = { d @* o = @_create(); return @_setup_from_sc(     o, sc,     en, size_en ); };
    func : .setup_from_source_adl  = { return @_setup_from_source( o, source, en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 ); };
    func : .setup_from_st_adl      = { return @_setup_from_st(     o, st,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 ); };
    func : .setup_from_sc_adl      = { return @_setup_from_sc(     o, sc,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 ); };
    func : .create_from_source_adl = { return @_create_from_source( source,   en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 ); };
    func : .create_from_st_adl     = { return @_create_from_st( st,           en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 ); };
    func : .create_from_sc_adl     = { return @_create_from_sc( sc,           en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 ); };

    func : .get_size_en  = { return :hidx_s_get_size( &o->hidx_en ); };
    func : .get_size_ex  = { return :hidx_s_get_size( &o->hidx_ex ); };
    func : .get_size_ada = { return :hidx_s_get_size( &o->hidx_ada ); };

    func : .get_ap_en  = { return :hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ax0, index ); };
    func : .get_dp_en  = { return :hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ag0, index ); };
    func : .get_ap_ex  = { return :hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ax0, index ); };
    func : .get_dp_ex  = { return :hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ag0, index ); };
    func : .get_ap_ada = { return :hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ax0, index ); };
    func : .get_dp_ada = { return :hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ag0, index ); };

    func : .run_ap;
    func : .run_dp;
    func : .run_ap_adl;
    func : .run_dp_adl;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :custom_hmeta_s = aware :
{
    sz_t ur_slot;
    sz_t ur_src;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// frame specialized in unrolling cyclic networks
stamp :cyclic_s = aware :
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
    func : .bind_holors;
    func : .reset;
    func : .setup;

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t setup = o->setup; @_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o->setup ) { @_reset( o ); @_setup( o ); } };
    func bcore_inst_call . copy_x  = { if( o->setup ) { @_reset( o ); @_setup( o ); } };

    func : .get_size_en  = { return :s_get_size_en(  o->frame ); };
    func : .get_size_ex  = { return :s_get_size_ex(  o->frame ); };
    func : .get_size_ada = { return :s_get_size_ada( o->frame ); };

    func : .run_ap;
    func : .run_ap_adl;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lion_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex );
void lion_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en );

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
