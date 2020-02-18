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

stamp : = aware :
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

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lion_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out );
void lion_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out );

#endif // TYPEOF_lion_frame

/**********************************************************************************************************************/

vd_t lion_frame_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_FRAME_H
