/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019, 2020 J.B.Steffens
 *  Last File Update: 2020-07-11T12:39:16Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  opal_context.h
 *  opal_holor.h
 *  opal_nop.h
 *  opal_eval_nop.h
 *
 */

#ifndef OPAL_PLANTED_H
#define OPAL_PLANTED_H

#include "bcore_control.h"

//To force a rebuild of this target by the plant-compiler, reset the hash key value below to 0.
#define HKEYOF_opal_planted 545664339

#define TYPEOF_opal_planted 1626965476

/**********************************************************************************************************************/
// source: opal_context.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_context

#define TYPEOF_opal_context 3099042715
#define TYPEOF_opal_context_s 434522221
#define TYPEOF_opal_context_std_s 2227413215
#define BETH_EXPAND_ITEM_opal_context_std_s \
  BCORE_DECLARE_OBJECT( opal_context_std_s ) \
    {aware_t _;bcore_prsg* prsg;}; \
  static inline bcore_prsg* opal_context_std_s_get_prsg( opal_context_std_s* o ){return o->prsg;}
#define BETH_EXPAND_GROUP_opal_context \
  BCORE_FORWARD_OBJECT( opal_context ); \
  BCORE_FORWARD_OBJECT( opal_context_std_s ); \
  typedef bcore_prsg* (*opal_context_get_prsg)( opal_context* o ); \
  BCORE_DECLARE_SPECT( opal_context ) \
  { \
      bcore_spect_header_s header; \
      opal_context_get_prsg get_prsg; \
  }; \
  static inline opal_context* opal_context_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_context, t ); return ( opal_context* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_context_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_context ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_context ) \
  static inline bl_t opal_context_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_context ); } \
  static inline bcore_prsg* opal_context_a_get_prsg( opal_context* o ) { const opal_context_s* p = opal_context_s_get_aware( o ); assert( p->get_prsg ); return p->get_prsg( o ); } \
  static inline bl_t opal_context_a_defines_get_prsg( const opal_context* o ) { return opal_context_s_get_aware( o )->get_prsg != NULL; } \
  BETH_EXPAND_ITEM_opal_context_std_s

/**********************************************************************************************************************/
// source: opal_holor.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_holor

#define TYPEOF_opal_holor 490103714
#define TYPEOF_opal_holor_s 703559388
#define TYPEOF_opal_holor_meta_s 3624388628
#define BETH_EXPAND_ITEM_opal_holor_meta_s \
  BCORE_DECLARE_OBJECT( opal_holor_meta_s ) \
    {aware_t _;bcore_inst* custom;bhvm_mcode_node_s* mnode;tp_t name;tp_t pclass;bl_t htp;bl_t active;}; \
  static inline void opal_holor_meta_s_clear( opal_holor_meta_s* o ){o->name = 0; o->htp = false;} \
  static inline tp_t opal_holor_meta_s_get_name( const opal_holor_meta_s* o ){return o->name;} \
  static inline tp_t opal_holor_meta_s_get_pclass( const opal_holor_meta_s* o ){return o->pclass;} \
  static inline bl_t opal_holor_meta_s_is_rollable( const opal_holor_meta_s* o ){return !o->active || o->mnode->adaptive || ( o->mnode->cyclic && o->pclass == TYPEOF_pclass_ax1 );} \
  static inline bl_t opal_holor_meta_s_is_active( const opal_holor_meta_s* o ){return  o->active;} \
  static inline bcore_inst* opal_holor_meta_s_get_custom( const opal_holor_meta_s* o ){return o->custom;} \
  static inline bcore_inst* opal_holor_meta_s_set_custom( opal_holor_meta_s* o, const bcore_inst* custom ){bcore_inst_a_attach( &o->custom, bcore_inst_a_clone( custom ) ); return o->custom;} \
  static inline bhvm_mcode_node_s* opal_holor_meta_s_get_node( const opal_holor_meta_s* o ){return o->mnode;} \
  static inline void opal_holor_meta_s_set_node( opal_holor_meta_s* o, bhvm_mcode_node_s* node ){bhvm_mcode_node_s_attach( &o->mnode, bcore_fork( node ) );}
#define TYPEOF_opal_holor_s 703559388
#define BETH_EXPAND_ITEM_opal_holor_s \
  BCORE_DECLARE_OBJECT( opal_holor_s ) \
    {aware_t _;opal_holor_meta_s m;bhvm_holor_s h;}; \
  void opal_holor_s_copy_typed( opal_holor_s* o, tp_t type, vc_t src );
#define BETH_EXPAND_GROUP_opal_holor \
  BCORE_FORWARD_OBJECT( opal_holor ); \
  BCORE_FORWARD_OBJECT( opal_holor_meta_s ); \
  BCORE_FORWARD_OBJECT( opal_holor_s ); \
  BETH_EXPAND_ITEM_opal_holor_meta_s \
  BETH_EXPAND_ITEM_opal_holor_s

/**********************************************************************************************************************/
// source: opal_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop

#define TYPEOF_opal_nop 2985948757
#define TYPEOF_opal_nop_s 2514142647
#define TYPEOF_track_ap 2993192456
#define TYPEOF_track_dp 2960475861
#define TYPEOF_track_ap_setup 3800687238
#define TYPEOF_track_dp_setup 1874372795
#define TYPEOF_track_ap_shelve 3671763698
#define TYPEOF_track_dp_shelve 2171378817
#define TYPEOF_track_dp_cyclic_zero_grad 3106917965
#define TYPEOF_track_ap_cyclic_reset 3819301030
#define TYPEOF_track_ap_cyclic_update 4132214
#define TYPEOF_track_dp_adaptive_zero_grad 1201855212
#define TYPEOF_opal_nop_solve_result_s 2394002165
#define BETH_EXPAND_ITEM_opal_nop_solve_result_s \
  BCORE_DECLARE_OBJECT( opal_nop_solve_result_s ) \
    {aware_t _;opal_holor_s* h;st_s* msg;bl_t settled;bl_t codable;bl_t reducible;tp_t type_vop_ap;tp_t type_vop_dp_a;tp_t type_vop_dp_b;tp_t type_vop_dp_c;vd_t attached;};
#define BETH_EXPAND_GROUP_opal_nop \
  BCORE_FORWARD_OBJECT( opal_nop ); \
  BCORE_FORWARD_OBJECT( opal_nop_solve_result_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar3 ); \
  typedef sz_t (*opal_nop_arity)( const opal_nop* o ); \
  typedef sz_t (*opal_nop_priority)( const opal_nop* o ); \
  typedef sc_t (*opal_nop_symbol)( const opal_nop* o ); \
  typedef bl_t (*opal_nop_reserved)( const opal_nop* o ); \
  typedef opal_nop* (*opal_nop_create_op_of_arn)( const opal_nop* o, sz_t n ); \
  typedef bl_t (*opal_nop_eci)( const opal_nop* o ); \
  typedef bl_t (*opal_nop_solve)( const opal_nop* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  typedef void (*opal_nop_solve_node)( opal_nop* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ); \
  typedef bl_t (*opal_nop_is_cyclic)( const opal_nop* o ); \
  typedef bl_t (*opal_nop_is_adaptive)( const opal_nop* o ); \
  typedef void (*opal_nop_settle)( const opal_nop* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  typedef tp_t (*opal_nop_type_vop_ap)( const opal_nop* o ); \
  typedef tp_t (*opal_nop_type_vop_dp_a)( const opal_nop* o ); \
  typedef tp_t (*opal_nop_type_vop_dp_b)( const opal_nop* o ); \
  typedef tp_t (*opal_nop_type_vop_dp_c)( const opal_nop* o ); \
  typedef sz_t (*opal_nop_mcode_push_ap_holor)( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef sz_t (*opal_nop_mcode_push_dp_holor)( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef void (*opal_nop_mcode_push_ap_track)( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef void (*opal_nop_mcode_push_dp_track)( const opal_nop* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BCORE_DECLARE_SPECT( opal_nop ) \
  { \
      bcore_spect_header_s header; \
      opal_nop_arity arity; \
      opal_nop_priority priority; \
      opal_nop_symbol symbol; \
      opal_nop_reserved reserved; \
      opal_nop_create_op_of_arn create_op_of_arn; \
      opal_nop_eci eci; \
      opal_nop_solve solve; \
      opal_nop_solve_node solve_node; \
      opal_nop_is_cyclic is_cyclic; \
      opal_nop_is_adaptive is_adaptive; \
      opal_nop_settle settle; \
      opal_nop_type_vop_ap type_vop_ap; \
      opal_nop_type_vop_dp_a type_vop_dp_a; \
      opal_nop_type_vop_dp_b type_vop_dp_b; \
      opal_nop_type_vop_dp_c type_vop_dp_c; \
      opal_nop_mcode_push_ap_holor mcode_push_ap_holor; \
      opal_nop_mcode_push_dp_holor mcode_push_dp_holor; \
      opal_nop_mcode_push_ap_track mcode_push_ap_track; \
      opal_nop_mcode_push_dp_track mcode_push_dp_track; \
  }; \
  static inline opal_nop* opal_nop_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_nop, t ); return ( opal_nop* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_nop_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_nop ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop ) \
  static inline bl_t opal_nop_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_nop ); } \
  static inline sz_t opal_nop_a_arity( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->arity ); return p->arity( o ); } \
  static inline bl_t opal_nop_a_defines_arity( const opal_nop* o ) { return true; } \
  static inline sz_t opal_nop_arity__( const opal_nop* o ){ERR_fa( "Not implemented in '#<sc_t>'.", ifnameof( o->_ ) ); return -1;} \
  static inline sz_t opal_nop_a_priority( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->priority ); return p->priority( o ); } \
  static inline bl_t opal_nop_a_defines_priority( const opal_nop* o ) { return true; } \
  static inline sz_t opal_nop_priority__( const opal_nop* o ){return 10;} \
  static inline sc_t opal_nop_a_symbol( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->symbol ); return p->symbol( o ); } \
  static inline bl_t opal_nop_a_defines_symbol( const opal_nop* o ) { return true; } \
  static inline sc_t opal_nop_symbol__( const opal_nop* o ){return NULL;} \
  static inline bl_t opal_nop_a_reserved( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->reserved ); return p->reserved( o ); } \
  static inline bl_t opal_nop_a_defines_reserved( const opal_nop* o ) { return true; } \
  static inline bl_t opal_nop_reserved__( const opal_nop* o ){return false;} \
  static inline opal_nop* opal_nop_a_create_op_of_arn( const opal_nop* o, sz_t n ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->create_op_of_arn ); return p->create_op_of_arn( o, n ); } \
  static inline bl_t opal_nop_a_defines_create_op_of_arn( const opal_nop* o ) { return true; } \
  static inline opal_nop* opal_nop_create_op_of_arn__( const opal_nop* o, sz_t n ){return ( opal_nop_a_arity( o ) == n ) ? opal_nop_a_clone( o ) : NULL;} \
  BETH_EXPAND_ITEM_opal_nop_solve_result_s \
  static inline bl_t opal_nop_a_eci( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->eci ); return p->eci( o ); } \
  static inline bl_t opal_nop_a_defines_eci( const opal_nop* o ) { return true; } \
  static inline bl_t opal_nop_eci__( const opal_nop* o ){return false;} \
  static inline bl_t opal_nop_a_solve( const opal_nop* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->solve ); return p->solve( o, context, a, result ); } \
  static inline bl_t opal_nop_a_defines_solve( const opal_nop* o ) { return true; } \
  bl_t opal_nop_solve__( const opal_nop* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline void opal_nop_a_solve_node( opal_nop* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->solve_node ); p->solve_node( o, node, deferred ); } \
  static inline bl_t opal_nop_a_defines_solve_node( const opal_nop* o ) { return opal_nop_s_get_aware( o )->solve_node != NULL; } \
  static inline bl_t opal_nop_a_is_cyclic( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->is_cyclic ); return p->is_cyclic( o ); } \
  static inline bl_t opal_nop_a_defines_is_cyclic( const opal_nop* o ) { return true; } \
  static inline bl_t opal_nop_is_cyclic__( const opal_nop* o ){return false;} \
  static inline bl_t opal_nop_a_is_adaptive( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->is_adaptive ); return p->is_adaptive( o ); } \
  static inline bl_t opal_nop_a_defines_is_adaptive( const opal_nop* o ) { return true; } \
  static inline bl_t opal_nop_is_adaptive__( const opal_nop* o ){return false;} \
  static inline void opal_nop_a_settle( const opal_nop* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->settle ); p->settle( o, context, result, out_nop, out_result ); } \
  static inline bl_t opal_nop_a_defines_settle( const opal_nop* o ) { return true; } \
  void opal_nop_settle__( const opal_nop* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  static inline tp_t opal_nop_a_type_vop_ap( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->type_vop_ap ); return p->type_vop_ap( o ); } \
  static inline bl_t opal_nop_a_defines_type_vop_ap( const opal_nop* o ) { return opal_nop_s_get_aware( o )->type_vop_ap != NULL; } \
  static inline tp_t opal_nop_a_type_vop_dp_a( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->type_vop_dp_a ); return p->type_vop_dp_a( o ); } \
  static inline bl_t opal_nop_a_defines_type_vop_dp_a( const opal_nop* o ) { return opal_nop_s_get_aware( o )->type_vop_dp_a != NULL; } \
  static inline tp_t opal_nop_a_type_vop_dp_b( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->type_vop_dp_b ); return p->type_vop_dp_b( o ); } \
  static inline bl_t opal_nop_a_defines_type_vop_dp_b( const opal_nop* o ) { return opal_nop_s_get_aware( o )->type_vop_dp_b != NULL; } \
  static inline tp_t opal_nop_a_type_vop_dp_c( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->type_vop_dp_c ); return p->type_vop_dp_c( o ); } \
  static inline bl_t opal_nop_a_defines_type_vop_dp_c( const opal_nop* o ) { return opal_nop_s_get_aware( o )->type_vop_dp_c != NULL; } \
  static inline sz_t opal_nop_a_mcode_push_ap_holor( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->mcode_push_ap_holor ); return p->mcode_push_ap_holor( o, result, arr_ci, mcf ); } \
  static inline bl_t opal_nop_a_defines_mcode_push_ap_holor( const opal_nop* o ) { return true; } \
  sz_t opal_nop_mcode_push_ap_holor__( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_a_mcode_push_dp_holor( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->mcode_push_dp_holor ); return p->mcode_push_dp_holor( o, result, arr_ci, mcf ); } \
  static inline bl_t opal_nop_a_defines_mcode_push_dp_holor( const opal_nop* o ) { return true; } \
  sz_t opal_nop_mcode_push_dp_holor__( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void opal_nop_a_mcode_push_ap_track( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->mcode_push_ap_track ); p->mcode_push_ap_track( o, result, arr_ci, mcf ); } \
  static inline bl_t opal_nop_a_defines_mcode_push_ap_track( const opal_nop* o ) { return true; } \
  void opal_nop_mcode_push_ap_track__( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void opal_nop_a_mcode_push_dp_track( const opal_nop* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->mcode_push_dp_track ); p->mcode_push_dp_track( o, result, ch_id, arr_ci, mcf ); } \
  static inline bl_t opal_nop_a_defines_mcode_push_dp_track( const opal_nop* o ) { return true; } \
  void opal_nop_mcode_push_dp_track__( const opal_nop* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BETH_EXPAND_GROUP_opal_nop_ar0 \
  BETH_EXPAND_GROUP_opal_nop_ar1 \
  BETH_EXPAND_GROUP_opal_nop_ar2 \
  BETH_EXPAND_GROUP_opal_nop_ar3

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar0

#define TYPEOF_opal_nop_ar0 3082113767
#define TYPEOF_opal_nop_ar0_s 3946507713
#define TYPEOF_opal_nop_ar0_literal_s 2921523873
#define BETH_EXPAND_ITEM_opal_nop_ar0_literal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_literal_s ) \
    {aware_t _;opal_holor_s* h;}; \
  static inline sz_t opal_nop_ar0_literal_s_arity( const opal_nop_ar0_literal_s* o ){return 0;} \
  bl_t opal_nop_ar0_literal_s_solve( const opal_nop_ar0_literal_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar0_param_s 4145390963
#define BETH_EXPAND_ITEM_opal_nop_ar0_param_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_param_s ) \
    {aware_t _;opal_holor_s* h;}; \
  static inline sz_t opal_nop_ar0_param_s_arity( const opal_nop_ar0_param_s* o ){return 0;} \
  bl_t opal_nop_ar0_param_s_solve( const opal_nop_ar0_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar0_adaptive_s 4191624816
#define BETH_EXPAND_ITEM_opal_nop_ar0_adaptive_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_adaptive_s ) \
    {aware_t _;opal_holor_s* h;}; \
  static inline sz_t opal_nop_ar0_adaptive_s_arity( const opal_nop_ar0_adaptive_s* o ){return 0;} \
  static inline bl_t opal_nop_ar0_adaptive_s_is_adaptive( const opal_nop_ar0_adaptive_s* o ){return true;} \
  bl_t opal_nop_ar0_adaptive_s_solve( const opal_nop_ar0_adaptive_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar0_adaptive_s_mcode_push_ap_holor( const opal_nop_ar0_adaptive_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar0_adaptive_s_mcode_push_dp_holor( const opal_nop_ar0_adaptive_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_opal_nop_ar0_rand_s 330543217
#define BETH_EXPAND_ITEM_opal_nop_ar0_rand_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_rand_s ) \
    {aware_t _;opal_holor_s* h;bcore_prsg* prsg;f3_t min;f3_t max;f3_t density;}; \
  static inline sz_t opal_nop_ar0_rand_s_arity( const opal_nop_ar0_rand_s* o ){return 0;} \
  bl_t opal_nop_ar0_rand_s_solve( const opal_nop_ar0_rand_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar0_rand_s_mcode_push_ap_holor( const opal_nop_ar0_rand_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define BETH_EXPAND_GROUP_opal_nop_ar0 \
  BCORE_FORWARD_OBJECT( opal_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_literal_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_param_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_adaptive_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_rand_s ); \
  BETH_EXPAND_ITEM_opal_nop_ar0_literal_s \
  BETH_EXPAND_ITEM_opal_nop_ar0_param_s \
  BETH_EXPAND_ITEM_opal_nop_ar0_adaptive_s \
  BETH_EXPAND_ITEM_opal_nop_ar0_rand_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar1

#define TYPEOF_opal_nop_ar1 3065336148
#define TYPEOF_opal_nop_ar1_s 1846751622
#define TYPEOF_opal_nop_ar1_identity_s 1126997449
#define BETH_EXPAND_ITEM_opal_nop_ar1_identity_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_identity_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_identity_s_arity( const opal_nop_ar1_identity_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_identity_s_reserved( const opal_nop_ar1_identity_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_identity_s_priority( const opal_nop_ar1_identity_s* o ){return 8;} \
  bl_t opal_nop_ar1_identity_s_solve( const opal_nop_ar1_identity_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_f3_s 2901120332
#define BETH_EXPAND_ITEM_opal_nop_ar1_f3_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_f3_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_f3_s_arity( const opal_nop_ar1_f3_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_f3_s_reserved( const opal_nop_ar1_f3_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_f3_s_priority( const opal_nop_ar1_f3_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_f3_s_symbol( const opal_nop_ar1_f3_s* o ){return "f3_t";} \
  bl_t opal_nop_ar1_f3_s_solve( const opal_nop_ar1_f3_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_f2_s 705909127
#define BETH_EXPAND_ITEM_opal_nop_ar1_f2_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_f2_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_f2_s_arity( const opal_nop_ar1_f2_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_f2_s_reserved( const opal_nop_ar1_f2_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_f2_s_priority( const opal_nop_ar1_f2_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_f2_s_symbol( const opal_nop_ar1_f2_s* o ){return "f2_t";} \
  bl_t opal_nop_ar1_f2_s_solve( const opal_nop_ar1_f2_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_neg_s 2319373791
#define BETH_EXPAND_ITEM_opal_nop_ar1_neg_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_neg_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_neg_s_arity( const opal_nop_ar1_neg_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_neg_s_reserved( const opal_nop_ar1_neg_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_neg_s_priority( const opal_nop_ar1_neg_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_neg_s_symbol( const opal_nop_ar1_neg_s* o ){return "neg";} \
  static inline tp_t opal_nop_ar1_neg_s_type_vop_ap( const opal_nop_ar1_neg_s* o ){return TYPEOF_bhvm_vop_ar1_neg_s;} \
  static inline tp_t opal_nop_ar1_neg_s_type_vop_dp_a( const opal_nop_ar1_neg_s* o ){return TYPEOF_bhvm_vop_ar1_neg_dp_s;} \
  opal_nop* opal_nop_ar1_neg_s_create_op_of_arn( const opal_nop_ar1_neg_s* o, sz_t n );
#define TYPEOF_opal_nop_ar1_floor_s 2947439403
#define BETH_EXPAND_ITEM_opal_nop_ar1_floor_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_floor_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_floor_s_arity( const opal_nop_ar1_floor_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_floor_s_reserved( const opal_nop_ar1_floor_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_floor_s_priority( const opal_nop_ar1_floor_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_floor_s_symbol( const opal_nop_ar1_floor_s* o ){return "floor";} \
  static inline tp_t opal_nop_ar1_floor_s_type_vop_ap( const opal_nop_ar1_floor_s* o ){return TYPEOF_bhvm_vop_ar1_floor_s;} \
  static inline sz_t opal_nop_ar1_floor_s_mcode_push_dp_holor( const opal_nop_ar1_floor_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar1_ceil_s 2292597622
#define BETH_EXPAND_ITEM_opal_nop_ar1_ceil_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_ceil_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_ceil_s_arity( const opal_nop_ar1_ceil_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_ceil_s_reserved( const opal_nop_ar1_ceil_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_ceil_s_priority( const opal_nop_ar1_ceil_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_ceil_s_symbol( const opal_nop_ar1_ceil_s* o ){return "ceil";} \
  static inline tp_t opal_nop_ar1_ceil_s_type_vop_ap( const opal_nop_ar1_ceil_s* o ){return TYPEOF_bhvm_vop_ar1_ceil_s;} \
  static inline sz_t opal_nop_ar1_ceil_s_mcode_push_dp_holor( const opal_nop_ar1_ceil_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar1_abs_s 2379512073
#define BETH_EXPAND_ITEM_opal_nop_ar1_abs_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_abs_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_abs_s_arity( const opal_nop_ar1_abs_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_abs_s_reserved( const opal_nop_ar1_abs_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_abs_s_priority( const opal_nop_ar1_abs_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_abs_s_symbol( const opal_nop_ar1_abs_s* o ){return "abs";} \
  static inline tp_t opal_nop_ar1_abs_s_type_vop_ap( const opal_nop_ar1_abs_s* o ){return TYPEOF_bhvm_vop_ar1_abs_s;} \
  static inline tp_t opal_nop_ar1_abs_s_type_vop_dp_a( const opal_nop_ar1_abs_s* o ){return TYPEOF_bhvm_vop_ar2_abs_dp_s;}
#define TYPEOF_opal_nop_ar1_exp_s 2669670406
#define BETH_EXPAND_ITEM_opal_nop_ar1_exp_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_exp_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_exp_s_arity( const opal_nop_ar1_exp_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_exp_s_reserved( const opal_nop_ar1_exp_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_exp_s_priority( const opal_nop_ar1_exp_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_exp_s_symbol( const opal_nop_ar1_exp_s* o ){return "exp";} \
  static inline tp_t opal_nop_ar1_exp_s_type_vop_ap( const opal_nop_ar1_exp_s* o ){return TYPEOF_bhvm_vop_ar1_exp_s;} \
  static inline tp_t opal_nop_ar1_exp_s_type_vop_dp_a( const opal_nop_ar1_exp_s* o ){return TYPEOF_bhvm_vop_ar2_exp_dp_s;}
#define TYPEOF_opal_nop_ar1_log_s 1656194559
#define BETH_EXPAND_ITEM_opal_nop_ar1_log_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_log_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_log_s_arity( const opal_nop_ar1_log_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_log_s_reserved( const opal_nop_ar1_log_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_log_s_priority( const opal_nop_ar1_log_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_log_s_symbol( const opal_nop_ar1_log_s* o ){return "log";} \
  static inline tp_t opal_nop_ar1_log_s_type_vop_ap( const opal_nop_ar1_log_s* o ){return TYPEOF_bhvm_vop_ar1_log_s;} \
  static inline tp_t opal_nop_ar1_log_s_type_vop_dp_a( const opal_nop_ar1_log_s* o ){return TYPEOF_bhvm_vop_ar2_log_dp_s;}
#define TYPEOF_opal_nop_ar1_inv_s 183938606
#define BETH_EXPAND_ITEM_opal_nop_ar1_inv_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_inv_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_inv_s_arity( const opal_nop_ar1_inv_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_inv_s_reserved( const opal_nop_ar1_inv_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_inv_s_priority( const opal_nop_ar1_inv_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_inv_s_symbol( const opal_nop_ar1_inv_s* o ){return "inv";} \
  static inline tp_t opal_nop_ar1_inv_s_type_vop_ap( const opal_nop_ar1_inv_s* o ){return TYPEOF_bhvm_vop_ar1_inv_s;} \
  static inline tp_t opal_nop_ar1_inv_s_type_vop_dp_a( const opal_nop_ar1_inv_s* o ){return TYPEOF_bhvm_vop_ar2_inv_dp_s;}
#define TYPEOF_opal_nop_ar1_sqr_s 237451399
#define BETH_EXPAND_ITEM_opal_nop_ar1_sqr_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sqr_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_sqr_s_arity( const opal_nop_ar1_sqr_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_sqr_s_reserved( const opal_nop_ar1_sqr_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_sqr_s_priority( const opal_nop_ar1_sqr_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_sqr_s_symbol( const opal_nop_ar1_sqr_s* o ){return "sqr";} \
  static inline tp_t opal_nop_ar1_sqr_s_type_vop_ap( const opal_nop_ar1_sqr_s* o ){return TYPEOF_bhvm_vop_ar1_sqr_s;} \
  static inline tp_t opal_nop_ar1_sqr_s_type_vop_dp_a( const opal_nop_ar1_sqr_s* o ){return TYPEOF_bhvm_vop_ar2_sqr_dp_s;}
#define TYPEOF_opal_nop_ar1_srt_s 3061013986
#define BETH_EXPAND_ITEM_opal_nop_ar1_srt_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_srt_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_srt_s_arity( const opal_nop_ar1_srt_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_srt_s_reserved( const opal_nop_ar1_srt_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_srt_s_priority( const opal_nop_ar1_srt_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_srt_s_symbol( const opal_nop_ar1_srt_s* o ){return "srt";} \
  static inline tp_t opal_nop_ar1_srt_s_type_vop_ap( const opal_nop_ar1_srt_s* o ){return TYPEOF_bhvm_vop_ar1_srt_s;} \
  static inline tp_t opal_nop_ar1_srt_s_type_vop_dp_a( const opal_nop_ar1_srt_s* o ){return TYPEOF_bhvm_vop_ar2_srt_dp_s;}
#define TYPEOF_opal_nop_ar1_sigm_s 3531812595
#define BETH_EXPAND_ITEM_opal_nop_ar1_sigm_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sigm_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_sigm_s_arity( const opal_nop_ar1_sigm_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_sigm_s_reserved( const opal_nop_ar1_sigm_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_sigm_s_priority( const opal_nop_ar1_sigm_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_sigm_s_symbol( const opal_nop_ar1_sigm_s* o ){return "sigm";} \
  static inline tp_t opal_nop_ar1_sigm_s_type_vop_ap( const opal_nop_ar1_sigm_s* o ){return TYPEOF_bhvm_vop_ar1_sigm_s;} \
  static inline tp_t opal_nop_ar1_sigm_s_type_vop_dp_a( const opal_nop_ar1_sigm_s* o ){return TYPEOF_bhvm_vop_ar2_sigm_dp_s;}
#define TYPEOF_opal_nop_ar1_sigm_hard_s 1420344077
#define BETH_EXPAND_ITEM_opal_nop_ar1_sigm_hard_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sigm_hard_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_sigm_hard_s_arity( const opal_nop_ar1_sigm_hard_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_sigm_hard_s_reserved( const opal_nop_ar1_sigm_hard_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_sigm_hard_s_priority( const opal_nop_ar1_sigm_hard_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_sigm_hard_s_symbol( const opal_nop_ar1_sigm_hard_s* o ){return "sigm_hard";} \
  static inline tp_t opal_nop_ar1_sigm_hard_s_type_vop_ap( const opal_nop_ar1_sigm_hard_s* o ){return TYPEOF_bhvm_vop_ar1_sigm_hard_s;} \
  static inline tp_t opal_nop_ar1_sigm_hard_s_type_vop_dp_a( const opal_nop_ar1_sigm_hard_s* o ){return TYPEOF_bhvm_vop_ar2_sigm_hard_dp_s;}
#define TYPEOF_opal_nop_ar1_sigm_leaky_s 579189838
#define BETH_EXPAND_ITEM_opal_nop_ar1_sigm_leaky_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sigm_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_sigm_leaky_s_arity( const opal_nop_ar1_sigm_leaky_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_sigm_leaky_s_reserved( const opal_nop_ar1_sigm_leaky_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_sigm_leaky_s_priority( const opal_nop_ar1_sigm_leaky_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_sigm_leaky_s_symbol( const opal_nop_ar1_sigm_leaky_s* o ){return "sigm_leaky";} \
  static inline tp_t opal_nop_ar1_sigm_leaky_s_type_vop_ap( const opal_nop_ar1_sigm_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_sigm_leaky_s;} \
  static inline tp_t opal_nop_ar1_sigm_leaky_s_type_vop_dp_a( const opal_nop_ar1_sigm_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_sigm_leaky_dp_s;}
#define TYPEOF_opal_nop_ar1_tanh_s 1003648350
#define BETH_EXPAND_ITEM_opal_nop_ar1_tanh_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_tanh_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_tanh_s_arity( const opal_nop_ar1_tanh_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_tanh_s_reserved( const opal_nop_ar1_tanh_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_tanh_s_priority( const opal_nop_ar1_tanh_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_tanh_s_symbol( const opal_nop_ar1_tanh_s* o ){return "tanh";} \
  static inline tp_t opal_nop_ar1_tanh_s_type_vop_ap( const opal_nop_ar1_tanh_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_s;} \
  static inline tp_t opal_nop_ar1_tanh_s_type_vop_dp_a( const opal_nop_ar1_tanh_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_dp_s;}
#define TYPEOF_opal_nop_ar1_tanh_hard_s 3927447666
#define BETH_EXPAND_ITEM_opal_nop_ar1_tanh_hard_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_tanh_hard_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_tanh_hard_s_arity( const opal_nop_ar1_tanh_hard_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_tanh_hard_s_reserved( const opal_nop_ar1_tanh_hard_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_tanh_hard_s_priority( const opal_nop_ar1_tanh_hard_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_tanh_hard_s_symbol( const opal_nop_ar1_tanh_hard_s* o ){return "tanh_hard";} \
  static inline tp_t opal_nop_ar1_tanh_hard_s_type_vop_ap( const opal_nop_ar1_tanh_hard_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_hard_s;} \
  static inline tp_t opal_nop_ar1_tanh_hard_s_type_vop_dp_a( const opal_nop_ar1_tanh_hard_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_hard_dp_s;}
#define TYPEOF_opal_nop_ar1_tanh_leaky_s 3582257179
#define BETH_EXPAND_ITEM_opal_nop_ar1_tanh_leaky_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_tanh_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_tanh_leaky_s_arity( const opal_nop_ar1_tanh_leaky_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_tanh_leaky_s_reserved( const opal_nop_ar1_tanh_leaky_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_tanh_leaky_s_priority( const opal_nop_ar1_tanh_leaky_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_tanh_leaky_s_symbol( const opal_nop_ar1_tanh_leaky_s* o ){return "tanh_leaky";} \
  static inline tp_t opal_nop_ar1_tanh_leaky_s_type_vop_ap( const opal_nop_ar1_tanh_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_leaky_s;} \
  static inline tp_t opal_nop_ar1_tanh_leaky_s_type_vop_dp_a( const opal_nop_ar1_tanh_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_leaky_dp_s;}
#define TYPEOF_opal_nop_ar1_softplus_s 3580288627
#define BETH_EXPAND_ITEM_opal_nop_ar1_softplus_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_softplus_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_softplus_s_arity( const opal_nop_ar1_softplus_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_softplus_s_reserved( const opal_nop_ar1_softplus_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_softplus_s_priority( const opal_nop_ar1_softplus_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_softplus_s_symbol( const opal_nop_ar1_softplus_s* o ){return "softplus";} \
  static inline tp_t opal_nop_ar1_softplus_s_type_vop_ap( const opal_nop_ar1_softplus_s* o ){return TYPEOF_bhvm_vop_ar1_softplus_s;} \
  static inline tp_t opal_nop_ar1_softplus_s_type_vop_dp_a( const opal_nop_ar1_softplus_s* o ){return TYPEOF_bhvm_vop_ar2_softplus_dp_s;}
#define TYPEOF_opal_nop_ar1_softmax_s 3481254879
#define BETH_EXPAND_ITEM_opal_nop_ar1_softmax_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_softmax_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_softmax_s_arity( const opal_nop_ar1_softmax_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_softmax_s_reserved( const opal_nop_ar1_softmax_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_softmax_s_priority( const opal_nop_ar1_softmax_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_softmax_s_symbol( const opal_nop_ar1_softmax_s* o ){return "softmax";} \
  static inline tp_t opal_nop_ar1_softmax_s_type_vop_ap( const opal_nop_ar1_softmax_s* o ){return TYPEOF_bhvm_vop_ar1_softmax_s;} \
  static inline tp_t opal_nop_ar1_softmax_s_type_vop_dp_a( const opal_nop_ar1_softmax_s* o ){return TYPEOF_bhvm_vop_ar2_softmax_dp_s;}
#define TYPEOF_opal_nop_ar1_relu_s 1795153249
#define BETH_EXPAND_ITEM_opal_nop_ar1_relu_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_relu_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_relu_s_arity( const opal_nop_ar1_relu_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_relu_s_reserved( const opal_nop_ar1_relu_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_relu_s_priority( const opal_nop_ar1_relu_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_relu_s_symbol( const opal_nop_ar1_relu_s* o ){return "relu";} \
  static inline tp_t opal_nop_ar1_relu_s_type_vop_ap( const opal_nop_ar1_relu_s* o ){return TYPEOF_bhvm_vop_ar1_relu_s;} \
  static inline tp_t opal_nop_ar1_relu_s_type_vop_dp_a( const opal_nop_ar1_relu_s* o ){return TYPEOF_bhvm_vop_ar2_relu_dp_s;}
#define TYPEOF_opal_nop_ar1_relu_leaky_s 1252957948
#define BETH_EXPAND_ITEM_opal_nop_ar1_relu_leaky_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_relu_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_relu_leaky_s_arity( const opal_nop_ar1_relu_leaky_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_relu_leaky_s_reserved( const opal_nop_ar1_relu_leaky_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_relu_leaky_s_priority( const opal_nop_ar1_relu_leaky_s* o ){return 8;} \
  static inline sc_t opal_nop_ar1_relu_leaky_s_symbol( const opal_nop_ar1_relu_leaky_s* o ){return "relu_leaky";} \
  static inline tp_t opal_nop_ar1_relu_leaky_s_type_vop_ap( const opal_nop_ar1_relu_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_relu_leaky_s;} \
  static inline tp_t opal_nop_ar1_relu_leaky_s_type_vop_dp_a( const opal_nop_ar1_relu_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_relu_leaky_dp_s;}
#define TYPEOF_opal_nop_ar1_output_s 2930607458
#define BETH_EXPAND_ITEM_opal_nop_ar1_output_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_output_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_output_s_arity( const opal_nop_ar1_output_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_output_s_reserved( const opal_nop_ar1_output_s* o ){return true;} \
  bl_t opal_nop_ar1_output_s_solve( const opal_nop_ar1_output_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar1_output_s_mcode_push_dp_holor( const opal_nop_ar1_output_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_opal_nop_ar1_adaptive_s 3358937521
#define BETH_EXPAND_ITEM_opal_nop_ar1_adaptive_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_adaptive_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t opal_nop_ar1_adaptive_s_arity( const opal_nop_ar1_adaptive_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_adaptive_s_reserved( const opal_nop_ar1_adaptive_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_adaptive_s_priority( const opal_nop_ar1_adaptive_s* o ){return 8;} \
  static inline bl_t opal_nop_ar1_adaptive_s_is_adaptive( const opal_nop_ar1_adaptive_s* o ){return true;} \
  bl_t opal_nop_ar1_adaptive_s_solve( const opal_nop_ar1_adaptive_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar1_adaptive_s_settle( const opal_nop_ar1_adaptive_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result );
#define TYPEOF_opal_nop_ar1_dimof_s 3680486330
#define BETH_EXPAND_ITEM_opal_nop_ar1_dimof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_dimof_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_dimof_s_arity( const opal_nop_ar1_dimof_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_dimof_s_reserved( const opal_nop_ar1_dimof_s* o ){return true;} \
  static inline sc_t opal_nop_ar1_dimof_s_symbol( const opal_nop_ar1_dimof_s* o ){return "dimof";} \
  static inline sz_t opal_nop_ar1_dimof_s_priority( const opal_nop_ar1_dimof_s* o ){return 8;} \
  bl_t opal_nop_ar1_dimof_s_solve( const opal_nop_ar1_dimof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_volof_s 1766689793
#define BETH_EXPAND_ITEM_opal_nop_ar1_volof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_volof_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_volof_s_arity( const opal_nop_ar1_volof_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_volof_s_reserved( const opal_nop_ar1_volof_s* o ){return true;} \
  static inline sc_t opal_nop_ar1_volof_s_symbol( const opal_nop_ar1_volof_s* o ){return "volof";} \
  static inline sz_t opal_nop_ar1_volof_s_priority( const opal_nop_ar1_volof_s* o ){return 8;} \
  bl_t opal_nop_ar1_volof_s_solve( const opal_nop_ar1_volof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_constof_s 1513942155
#define BETH_EXPAND_ITEM_opal_nop_ar1_constof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_constof_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_constof_s_arity( const opal_nop_ar1_constof_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_constof_s_reserved( const opal_nop_ar1_constof_s* o ){return true;} \
  static inline sc_t opal_nop_ar1_constof_s_symbol( const opal_nop_ar1_constof_s* o ){return "constof";} \
  static inline sz_t opal_nop_ar1_constof_s_priority( const opal_nop_ar1_constof_s* o ){return 8;} \
  bl_t opal_nop_ar1_constof_s_solve( const opal_nop_ar1_constof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_zeroof_s 432562780
#define BETH_EXPAND_ITEM_opal_nop_ar1_zeroof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_zeroof_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_zeroof_s_arity( const opal_nop_ar1_zeroof_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_zeroof_s_reserved( const opal_nop_ar1_zeroof_s* o ){return true;} \
  static inline sc_t opal_nop_ar1_zeroof_s_symbol( const opal_nop_ar1_zeroof_s* o ){return "zeroof";} \
  static inline sz_t opal_nop_ar1_zeroof_s_priority( const opal_nop_ar1_zeroof_s* o ){return 8;} \
  bl_t opal_nop_ar1_zeroof_s_solve( const opal_nop_ar1_zeroof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_shapeof_s 3455027109
#define BETH_EXPAND_ITEM_opal_nop_ar1_shapeof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_shapeof_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_shapeof_s_arity( const opal_nop_ar1_shapeof_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_shapeof_s_reserved( const opal_nop_ar1_shapeof_s* o ){return true;} \
  static inline sc_t opal_nop_ar1_shapeof_s_symbol( const opal_nop_ar1_shapeof_s* o ){return "shapeof";} \
  static inline sz_t opal_nop_ar1_shapeof_s_priority( const opal_nop_ar1_shapeof_s* o ){return 8;} \
  bl_t opal_nop_ar1_shapeof_s_solve( const opal_nop_ar1_shapeof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar1_rand_s 1983336028
#define BETH_EXPAND_ITEM_opal_nop_ar1_rand_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_rand_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_rand_s_arity( const opal_nop_ar1_rand_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_rand_s_reserved( const opal_nop_ar1_rand_s* o ){return true;} \
  static inline sc_t opal_nop_ar1_rand_s_symbol( const opal_nop_ar1_rand_s* o ){return "rand";} \
  static inline sz_t opal_nop_ar1_rand_s_priority( const opal_nop_ar1_rand_s* o ){return 8;} \
  bl_t opal_nop_ar1_rand_s_solve( const opal_nop_ar1_rand_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar1_rand_s_settle( const opal_nop_ar1_rand_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result );
#define TYPEOF_opal_nop_ar1_cast_htp_s 3755972059
#define BETH_EXPAND_ITEM_opal_nop_ar1_cast_htp_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_cast_htp_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_cast_htp_s_arity( const opal_nop_ar1_cast_htp_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_cast_htp_s_reserved( const opal_nop_ar1_cast_htp_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_cast_htp_s_priority( const opal_nop_ar1_cast_htp_s* o ){return 12;} \
  static inline sc_t opal_nop_ar1_cast_htp_s_symbol( const opal_nop_ar1_cast_htp_s* o ){return "htp";} \
  bl_t opal_nop_ar1_cast_htp_s_solve( const opal_nop_ar1_cast_htp_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar1_cast_htp_s_mcode_push_ap_holor( const opal_nop_ar1_cast_htp_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar1_cast_htp_s_mcode_push_dp_holor( const opal_nop_ar1_cast_htp_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_opal_nop_ar1_reshape_s 3136133987
#define BETH_EXPAND_ITEM_opal_nop_ar1_reshape_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_reshape_s ) \
    {aware_t _;bhvm_shape_s shape;}; \
  static inline sz_t opal_nop_ar1_reshape_s_arity( const opal_nop_ar1_reshape_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_reshape_s_reserved( const opal_nop_ar1_reshape_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_reshape_s_priority( const opal_nop_ar1_reshape_s* o ){return 8;} \
  bl_t opal_nop_ar1_reshape_s_solve( const opal_nop_ar1_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar1_reshape_s_mcode_push_ap_holor( const opal_nop_ar1_reshape_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar1_reshape_s_mcode_push_dp_holor( const opal_nop_ar1_reshape_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define BETH_EXPAND_GROUP_opal_nop_ar1 \
  BCORE_FORWARD_OBJECT( opal_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_identity_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_f3_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_f2_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_neg_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_floor_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_ceil_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_abs_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_exp_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_log_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_inv_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_sqr_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_srt_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_sigm_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_sigm_hard_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_sigm_leaky_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_tanh_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_tanh_hard_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_tanh_leaky_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_softplus_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_softmax_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_relu_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_relu_leaky_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_output_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_adaptive_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_dimof_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_volof_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_constof_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_zeroof_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_shapeof_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_rand_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_cast_htp_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_reshape_s ); \
  BETH_EXPAND_ITEM_opal_nop_ar1_identity_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_f3_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_f2_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_neg_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_floor_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_ceil_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_abs_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_exp_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_log_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_inv_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_sqr_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_srt_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_sigm_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_sigm_hard_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_sigm_leaky_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_tanh_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_tanh_hard_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_tanh_leaky_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_softplus_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_softmax_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_relu_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_relu_leaky_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_output_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_adaptive_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_dimof_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_volof_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_constof_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_zeroof_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_shapeof_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_rand_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_cast_htp_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_reshape_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar2

#define TYPEOF_opal_nop_ar2 3115669005
#define TYPEOF_opal_nop_ar2_s 3190290431
#define TYPEOF_opal_nop_ar2_add_s 2635304359
#define BETH_EXPAND_ITEM_opal_nop_ar2_add_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_add_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_add_s_arity( const opal_nop_ar2_add_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_add_s_reserved( const opal_nop_ar2_add_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_add_s_priority( const opal_nop_ar2_add_s* o ){return 8;} \
  static inline bl_t opal_nop_ar2_add_s_eci( const opal_nop_ar2_add_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_add_s_symbol( const opal_nop_ar2_add_s* o ){return "+";} \
  static inline tp_t opal_nop_ar2_add_s_type_vop_ap( const opal_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar2_add_s;} \
  static inline tp_t opal_nop_ar2_add_s_type_vop_dp_a( const opal_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_a_s;} \
  static inline tp_t opal_nop_ar2_add_s_type_vop_dp_b( const opal_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_opal_nop_ar2_sub_s 2073966342
#define BETH_EXPAND_ITEM_opal_nop_ar2_sub_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_sub_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_sub_s_arity( const opal_nop_ar2_sub_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_sub_s_reserved( const opal_nop_ar2_sub_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_sub_s_priority( const opal_nop_ar2_sub_s* o ){return 8;} \
  static inline bl_t opal_nop_ar2_sub_s_eci( const opal_nop_ar2_sub_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_sub_s_symbol( const opal_nop_ar2_sub_s* o ){return "-";} \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_ap( const opal_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar2_sub_s;} \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_dp_a( const opal_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar1_sub_dp_a_s;} \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_dp_b( const opal_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar1_sub_dp_b_s;} \
  opal_nop* opal_nop_ar2_sub_s_create_op_of_arn( const opal_nop_ar2_sub_s* o, sz_t n );
#define TYPEOF_opal_nop_ar2_mul_s 2786603658
#define BETH_EXPAND_ITEM_opal_nop_ar2_mul_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_mul_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_mul_s_arity( const opal_nop_ar2_mul_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_mul_s_reserved( const opal_nop_ar2_mul_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_mul_s_priority( const opal_nop_ar2_mul_s* o ){return 10;} \
  static inline bl_t opal_nop_ar2_mul_s_eci( const opal_nop_ar2_mul_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_mul_s_symbol( const opal_nop_ar2_mul_s* o ){return "*";} \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_ap( const opal_nop_ar2_mul_s* o ){return TYPEOF_bhvm_vop_ar2_mul_s;} \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_dp_a( const opal_nop_ar2_mul_s* o ){return TYPEOF_bhvm_vop_ar2_mul_dp_a_s;} \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_dp_b( const opal_nop_ar2_mul_s* o ){return TYPEOF_bhvm_vop_ar2_mul_dp_b_s;}
#define TYPEOF_opal_nop_ar2_div_s 3463025611
#define BETH_EXPAND_ITEM_opal_nop_ar2_div_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_div_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_div_s_arity( const opal_nop_ar2_div_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_div_s_reserved( const opal_nop_ar2_div_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_div_s_priority( const opal_nop_ar2_div_s* o ){return 10;} \
  static inline bl_t opal_nop_ar2_div_s_eci( const opal_nop_ar2_div_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_div_s_symbol( const opal_nop_ar2_div_s* o ){return "/";} \
  static inline tp_t opal_nop_ar2_div_s_type_vop_ap( const opal_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar2_div_s;} \
  static inline tp_t opal_nop_ar2_div_s_type_vop_dp_a( const opal_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar2_div_dp_a_s;} \
  static inline tp_t opal_nop_ar2_div_s_type_vop_dp_b( const opal_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar3_div_dp_b_s;}
#define TYPEOF_opal_nop_ar2_pow_s 344626922
#define BETH_EXPAND_ITEM_opal_nop_ar2_pow_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_pow_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_pow_s_arity( const opal_nop_ar2_pow_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_pow_s_reserved( const opal_nop_ar2_pow_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_pow_s_priority( const opal_nop_ar2_pow_s* o ){return 12;} \
  static inline bl_t opal_nop_ar2_pow_s_eci( const opal_nop_ar2_pow_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_pow_s_symbol( const opal_nop_ar2_pow_s* o ){return "^";} \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_ap( const opal_nop_ar2_pow_s* o ){return TYPEOF_bhvm_vop_ar2_pow_s;} \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_dp_a( const opal_nop_ar2_pow_s* o ){return TYPEOF_bhvm_vop_ar3_pow_dp_a_s;} \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_dp_b( const opal_nop_ar2_pow_s* o ){return TYPEOF_bhvm_vop_ar3_pow_dp_b_s;}
#define TYPEOF_opal_nop_ar2_bmul_s 4009502772
#define BETH_EXPAND_ITEM_opal_nop_ar2_bmul_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_bmul_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_bmul_s_arity( const opal_nop_ar2_bmul_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_bmul_s_reserved( const opal_nop_ar2_bmul_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_bmul_s_priority( const opal_nop_ar2_bmul_s* o ){return 10;} \
  static inline sc_t opal_nop_ar2_bmul_s_symbol( const opal_nop_ar2_bmul_s* o ){return "**";} \
  bl_t opal_nop_ar2_bmul_s_solve( const opal_nop_ar2_bmul_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define TYPEOF_opal_nop_ar2_logic_equal_s 802904141
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_equal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_equal_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_equal_s_arity( const opal_nop_ar2_logic_equal_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_equal_s_reserved( const opal_nop_ar2_logic_equal_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_equal_s_priority( const opal_nop_ar2_logic_equal_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_equal_s_eci( const opal_nop_ar2_logic_equal_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_equal_s_symbol( const opal_nop_ar2_logic_equal_s* o ){return "==";} \
  static inline tp_t opal_nop_ar2_logic_equal_s_type_vop_ap( const opal_nop_ar2_logic_equal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_equal_s;} \
  static inline sz_t opal_nop_ar2_logic_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_unequal_s 1311373380
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_unequal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_unequal_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_unequal_s_arity( const opal_nop_ar2_logic_unequal_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_unequal_s_reserved( const opal_nop_ar2_logic_unequal_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_unequal_s_priority( const opal_nop_ar2_logic_unequal_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_unequal_s_eci( const opal_nop_ar2_logic_unequal_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_unequal_s_symbol( const opal_nop_ar2_logic_unequal_s* o ){return "!=";} \
  static inline tp_t opal_nop_ar2_logic_unequal_s_type_vop_ap( const opal_nop_ar2_logic_unequal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_unequal_s;} \
  static inline sz_t opal_nop_ar2_logic_unequal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_unequal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_larger_s 3554713720
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_larger_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_larger_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_larger_s_arity( const opal_nop_ar2_logic_larger_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_larger_s_reserved( const opal_nop_ar2_logic_larger_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_larger_s_priority( const opal_nop_ar2_logic_larger_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_larger_s_eci( const opal_nop_ar2_logic_larger_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_larger_s_symbol( const opal_nop_ar2_logic_larger_s* o ){return ">";} \
  static inline tp_t opal_nop_ar2_logic_larger_s_type_vop_ap( const opal_nop_ar2_logic_larger_s* o ){return TYPEOF_bhvm_vop_ar2_logic_larger_s;} \
  static inline sz_t opal_nop_ar2_logic_larger_s_mcode_push_dp_holor( const opal_nop_ar2_logic_larger_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_smaller_s 3872490393
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_smaller_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_smaller_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_smaller_s_arity( const opal_nop_ar2_logic_smaller_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_smaller_s_reserved( const opal_nop_ar2_logic_smaller_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_smaller_s_priority( const opal_nop_ar2_logic_smaller_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_smaller_s_eci( const opal_nop_ar2_logic_smaller_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_smaller_s_symbol( const opal_nop_ar2_logic_smaller_s* o ){return "<";} \
  static inline tp_t opal_nop_ar2_logic_smaller_s_type_vop_ap( const opal_nop_ar2_logic_smaller_s* o ){return TYPEOF_bhvm_vop_ar2_logic_smaller_s;} \
  static inline sz_t opal_nop_ar2_logic_smaller_s_mcode_push_dp_holor( const opal_nop_ar2_logic_smaller_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_larger_equal_s 4287251147
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_larger_equal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_larger_equal_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_arity( const opal_nop_ar2_logic_larger_equal_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_larger_equal_s_reserved( const opal_nop_ar2_logic_larger_equal_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_priority( const opal_nop_ar2_logic_larger_equal_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_larger_equal_s_eci( const opal_nop_ar2_logic_larger_equal_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_larger_equal_s_symbol( const opal_nop_ar2_logic_larger_equal_s* o ){return ">=";} \
  static inline tp_t opal_nop_ar2_logic_larger_equal_s_type_vop_ap( const opal_nop_ar2_logic_larger_equal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_larger_equal_s;} \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_larger_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_smaller_equal_s 1912517170
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_smaller_equal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_smaller_equal_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_arity( const opal_nop_ar2_logic_smaller_equal_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_smaller_equal_s_reserved( const opal_nop_ar2_logic_smaller_equal_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_priority( const opal_nop_ar2_logic_smaller_equal_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_smaller_equal_s_eci( const opal_nop_ar2_logic_smaller_equal_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_smaller_equal_s_symbol( const opal_nop_ar2_logic_smaller_equal_s* o ){return "<=";} \
  static inline tp_t opal_nop_ar2_logic_smaller_equal_s_type_vop_ap( const opal_nop_ar2_logic_smaller_equal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_smaller_equal_s;} \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_smaller_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_and_s 3794587412
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_and_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_and_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_and_s_arity( const opal_nop_ar2_logic_and_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_and_s_reserved( const opal_nop_ar2_logic_and_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_and_s_priority( const opal_nop_ar2_logic_and_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_and_s_eci( const opal_nop_ar2_logic_and_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_and_s_symbol( const opal_nop_ar2_logic_and_s* o ){return "&&";} \
  static inline tp_t opal_nop_ar2_logic_and_s_type_vop_ap( const opal_nop_ar2_logic_and_s* o ){return TYPEOF_bhvm_vop_ar2_logic_and_s;} \
  static inline sz_t opal_nop_ar2_logic_and_s_mcode_push_dp_holor( const opal_nop_ar2_logic_and_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_logic_or_s 935785202
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_or_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_or_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_logic_or_s_arity( const opal_nop_ar2_logic_or_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_logic_or_s_reserved( const opal_nop_ar2_logic_or_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_logic_or_s_priority( const opal_nop_ar2_logic_or_s* o ){return 6;} \
  static inline bl_t opal_nop_ar2_logic_or_s_eci( const opal_nop_ar2_logic_or_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_logic_or_s_symbol( const opal_nop_ar2_logic_or_s* o ){return "||";} \
  static inline tp_t opal_nop_ar2_logic_or_s_type_vop_ap( const opal_nop_ar2_logic_or_s* o ){return TYPEOF_bhvm_vop_ar2_logic_or_s;} \
  static inline sz_t opal_nop_ar2_logic_or_s_mcode_push_dp_holor( const opal_nop_ar2_logic_or_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_opal_nop_ar2_cat_s 2733504900
#define BETH_EXPAND_ITEM_opal_nop_ar2_cat_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_cat_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_cat_s_arity( const opal_nop_ar2_cat_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_cat_s_reserved( const opal_nop_ar2_cat_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_cat_s_priority( const opal_nop_ar2_cat_s* o ){return 6;} \
  static inline sc_t opal_nop_ar2_cat_s_symbol( const opal_nop_ar2_cat_s* o ){return ":";} \
  bl_t opal_nop_ar2_cat_s_solve( const opal_nop_ar2_cat_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_ap( const opal_nop_ar2_cat_s* o ){return TYPEOF_bhvm_vop_ar2_cat_s;} \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_dp_a( const opal_nop_ar2_cat_s* o ){return TYPEOF_bhvm_vop_ar1_cat_dp_a_s;} \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_dp_b( const opal_nop_ar2_cat_s* o ){return TYPEOF_bhvm_vop_ar1_cat_dp_b_s;}
#define TYPEOF_opal_nop_ar2_ccat_s 4100985691
#define BETH_EXPAND_ITEM_opal_nop_ar2_ccat_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_ccat_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_ccat_s_arity( const opal_nop_ar2_ccat_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_ccat_s_reserved( const opal_nop_ar2_ccat_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_ccat_s_priority( const opal_nop_ar2_ccat_s* o ){return 8;} \
  static inline sc_t opal_nop_ar2_ccat_s_symbol( const opal_nop_ar2_ccat_s* o ){return "::";} \
  bl_t opal_nop_ar2_ccat_s_solve( const opal_nop_ar2_ccat_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_ap( const opal_nop_ar2_ccat_s* o ){return TYPEOF_bhvm_vop_ar2_ccat_s;} \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_dp_a( const opal_nop_ar2_ccat_s* o ){return TYPEOF_bhvm_vop_ar1_ccat_dp_a_s;} \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_dp_b( const opal_nop_ar2_ccat_s* o ){return TYPEOF_bhvm_vop_ar1_ccat_dp_b_s;}
#define TYPEOF_opal_nop_ar2_order_inc_s 4266137955
#define BETH_EXPAND_ITEM_opal_nop_ar2_order_inc_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_order_inc_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_order_inc_s_arity( const opal_nop_ar2_order_inc_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_order_inc_s_reserved( const opal_nop_ar2_order_inc_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_order_inc_s_priority( const opal_nop_ar2_order_inc_s* o ){return 21;} \
  static inline sc_t opal_nop_ar2_order_inc_s_symbol( const opal_nop_ar2_order_inc_s* o ){return "[";} \
  bl_t opal_nop_ar2_order_inc_s_solve( const opal_nop_ar2_order_inc_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_order_inc_s_mcode_push_ap_track( const opal_nop_ar2_order_inc_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline tp_t opal_nop_ar2_order_inc_s_type_vop_dp_a( const opal_nop_ar2_order_inc_s* o ){return 0;} \
  static inline tp_t opal_nop_ar2_order_inc_s_type_vop_dp_b( const opal_nop_ar2_order_inc_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_opal_nop_ar2_order_dec_s 435788403
#define BETH_EXPAND_ITEM_opal_nop_ar2_order_dec_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_order_dec_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_order_dec_s_arity( const opal_nop_ar2_order_dec_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_order_dec_s_reserved( const opal_nop_ar2_order_dec_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_order_dec_s_priority( const opal_nop_ar2_order_dec_s* o ){return 20;} \
  static inline sc_t opal_nop_ar2_order_dec_s_symbol( const opal_nop_ar2_order_dec_s* o ){return "]";} \
  bl_t opal_nop_ar2_order_dec_s_solve( const opal_nop_ar2_order_dec_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar2_order_dec_s_mcode_push_ap_holor( const opal_nop_ar2_order_dec_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar2_order_dec_s_mcode_push_dp_holor( const opal_nop_ar2_order_dec_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_opal_nop_ar2_cyclic_s 3706205743
#define BETH_EXPAND_ITEM_opal_nop_ar2_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_cyclic_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t opal_nop_ar2_cyclic_s_arity( const opal_nop_ar2_cyclic_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_cyclic_s_reserved( const opal_nop_ar2_cyclic_s* o ){return true;} \
  static inline sz_t opal_nop_ar2_cyclic_s_priority( const opal_nop_ar2_cyclic_s* o ){return 8;} \
  static inline bl_t opal_nop_ar2_cyclic_s_is_cyclic( const opal_nop_ar2_cyclic_s* o ){return true;} \
  bl_t opal_nop_ar2_cyclic_s_solve( const opal_nop_ar2_cyclic_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline void opal_nop_ar2_cyclic_s_mcode_push_ap_track( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ERR_fa( "Not implemented." );} \
  static inline void opal_nop_ar2_cyclic_s_mcode_push_dp_track( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ERR_fa( "Not implemented." );} \
  static inline sz_t opal_nop_ar2_cyclic_s_mcode_push_dp_holor( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ERR_fa( "Not implemented." ); return -1;}
#define TYPEOF_opal_nop_ar2_rands_s 3400032036
#define BETH_EXPAND_ITEM_opal_nop_ar2_rands_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_rands_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_rands_s_arity( const opal_nop_ar2_rands_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_rands_s_reserved( const opal_nop_ar2_rands_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_rands_s_symbol( const opal_nop_ar2_rands_s* o ){return "rands";} \
  static inline sz_t opal_nop_ar2_rands_s_priority( const opal_nop_ar2_rands_s* o ){return 8;} \
  bl_t opal_nop_ar2_rands_s_solve( const opal_nop_ar2_rands_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_rands_s_settle( const opal_nop_ar2_rands_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result );
#define TYPEOF_opal_nop_ar2_reshape_s 3345941670
#define BETH_EXPAND_ITEM_opal_nop_ar2_reshape_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_reshape_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar2_reshape_s_arity( const opal_nop_ar2_reshape_s* o ){return 2;} \
  static inline bl_t opal_nop_ar2_reshape_s_reserved( const opal_nop_ar2_reshape_s* o ){return true;} \
  static inline sc_t opal_nop_ar2_reshape_s_symbol( const opal_nop_ar2_reshape_s* o ){return "reshape";} \
  static inline sz_t opal_nop_ar2_reshape_s_priority( const opal_nop_ar2_reshape_s* o ){return 8;} \
  bl_t opal_nop_ar2_reshape_s_solve( const opal_nop_ar2_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result );
#define BETH_EXPAND_GROUP_opal_nop_ar2 \
  BCORE_FORWARD_OBJECT( opal_nop_ar2 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_add_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_sub_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_mul_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_div_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_pow_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_bmul_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_equal_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_unequal_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_larger_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_smaller_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_larger_equal_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_smaller_equal_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_and_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_logic_or_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_cat_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_ccat_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_order_inc_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_order_dec_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_cyclic_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_rands_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar2_reshape_s ); \
  BETH_EXPAND_ITEM_opal_nop_ar2_add_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_sub_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_mul_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_div_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_pow_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_bmul_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_equal_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_unequal_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_larger_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_smaller_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_larger_equal_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_smaller_equal_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_and_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_logic_or_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_cat_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_ccat_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_order_inc_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_order_dec_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_cyclic_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_rands_s \
  BETH_EXPAND_ITEM_opal_nop_ar2_reshape_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar3

#define TYPEOF_opal_nop_ar3 3098891386
#define TYPEOF_opal_nop_ar3_s 1606629796
#define TYPEOF_opal_nop_ar3_iff_s 2253549920
#define BETH_EXPAND_ITEM_opal_nop_ar3_iff_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar3_iff_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar3_iff_s_arity( const opal_nop_ar3_iff_s* o ){return 3;} \
  static inline bl_t opal_nop_ar3_iff_s_reserved( const opal_nop_ar3_iff_s* o ){return true;} \
  static inline sz_t opal_nop_ar3_iff_s_priority( const opal_nop_ar3_iff_s* o ){return 4;} \
  static inline bl_t opal_nop_ar3_iff_s_eci( const opal_nop_ar3_iff_s* o ){return true;} \
  static inline sc_t opal_nop_ar3_iff_s_symbol( const opal_nop_ar3_iff_s* o ){return "iff";} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_ap( const opal_nop_ar3_iff_s* o ){return TYPEOF_bhvm_vop_ar3_iff_s;} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_a( const opal_nop_ar3_iff_s* o ){return 0;} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_b( const opal_nop_ar3_iff_s* o ){return TYPEOF_bhvm_vop_ar2_iff_dp_b_s;} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_c( const opal_nop_ar3_iff_s* o ){return TYPEOF_bhvm_vop_ar2_iff_dp_c_s;}
#define BETH_EXPAND_GROUP_opal_nop_ar3 \
  BCORE_FORWARD_OBJECT( opal_nop_ar3 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar3_iff_s ); \
  BETH_EXPAND_ITEM_opal_nop_ar3_iff_s

/**********************************************************************************************************************/
// source: opal_eval_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_eval_nop

#define TYPEOF_opal_eval_nop 4188901640
#define TYPEOF_opal_eval_nop_s 3173082098
#define TYPEOF_opal_eval_nop_result_s 327116934
#define BETH_EXPAND_ITEM_opal_eval_nop_result_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_result_s ) \
    {aware_t _;sz_t total_tests;sz_t solvable_tests;sz_t tolerated_errors;bl_t error;st_s msg;}; \
  void opal_eval_nop_result_s_resolve( const opal_eval_nop_result_s* o );
#define TYPEOF_opal_eval_nop_param_s 3224023100
#define BETH_EXPAND_ITEM_opal_eval_nop_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_param_s ) \
    {aware_t _;opal_nop* nop;opal_holor_s* ha;opal_holor_s* hb;opal_holor_s* hc;opal_holor_s* hr;bcore_sink* log;sz_t verbosity;bcore_prsg* prsg;}; \
  static inline void opal_eval_nop_param_s_init_x( opal_eval_nop_param_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  void opal_eval_nop_param_s_set( opal_eval_nop_param_s* o, const opal_eval_nop_param_s* src );
#define TYPEOF_opal_eval_nop_generator_s 2743071660
#define BETH_EXPAND_ITEM_opal_eval_nop_generator_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_generator_s ) \
    {aware_t _;opal_eval_nop_param_s param;bl_t set_htp;bl_t set_value;bl_t set_shape;bl_t set_dim;bl_t set_v_type;sz_t max_shape_size;sz_t max_dim;f3_t v_min;f3_t v_max;sz_t cycles;bcore_arr_uz_s tolerated_cycles;opal_eval_nop* eval;}; \
  opal_eval_nop_result_s* opal_eval_nop_generator_s_run( const opal_eval_nop_generator_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_generator_s_set_param( opal_eval_nop_generator_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  s2_t opal_eval_nop_generator_s_main( opal_eval_nop_generator_s* o, const bcore_arr_st_s* args );
#define TYPEOF_opal_eval_nop_show_param_s 47537560
#define BETH_EXPAND_ITEM_opal_eval_nop_show_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_show_param_s ) \
    {aware_t _;opal_eval_nop_param_s param;}; \
  static inline void opal_eval_nop_show_param_s_set_param( opal_eval_nop_show_param_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  s2_t opal_eval_nop_show_param_s_main( opal_eval_nop_show_param_s* o, const bcore_arr_st_s* args ); \
  static inline opal_eval_nop_result_s* opal_eval_nop_show_param_s_run( const opal_eval_nop_show_param_s* o, opal_eval_nop_result_s* result ){bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result;}
#define TYPEOF_opal_eval_nop_arr_s 271786002
#define BETH_EXPAND_ITEM_opal_eval_nop_arr_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_eval_nop, );}; \
  static inline opal_eval_nop_arr_s* opal_eval_nop_arr_s_set_space( opal_eval_nop_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_eval_nop_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_eval_nop_arr_s* opal_eval_nop_arr_s_set_size( opal_eval_nop_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_eval_nop_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_eval_nop_arr_s* opal_eval_nop_arr_s_clear( opal_eval_nop_arr_s* o ) { bcore_array_t_set_space( TYPEOF_opal_eval_nop_arr_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_eval_nop* opal_eval_nop_arr_s_push_c( opal_eval_nop_arr_s* o, const opal_eval_nop* v ) { bcore_array_t_push( TYPEOF_opal_eval_nop_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_eval_nop* opal_eval_nop_arr_s_push_d( opal_eval_nop_arr_s* o,       opal_eval_nop* v ) { bcore_array_t_push( TYPEOF_opal_eval_nop_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_eval_nop* opal_eval_nop_arr_s_push_t( opal_eval_nop_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_opal_eval_nop, t ); \
      bcore_array_t_push( TYPEOF_opal_eval_nop_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_eval_nop_set_s 802013493
#define BETH_EXPAND_ITEM_opal_eval_nop_set_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_set_s ) \
    {aware_t _;opal_eval_nop_param_s param;opal_eval_nop_arr_s arr;}; \
  static inline void opal_eval_nop_set_s_set_param( opal_eval_nop_set_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  s2_t opal_eval_nop_set_s_main( opal_eval_nop_set_s* o, const bcore_arr_st_s* args ); \
  opal_eval_nop_result_s* opal_eval_nop_set_s_run( const opal_eval_nop_set_s* o, opal_eval_nop_result_s* result );
#define TYPEOF_opal_eval_nop_ar1_s 626857419
#define BETH_EXPAND_ITEM_opal_eval_nop_ar1_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_ar1_s ) \
    {aware_t _;opal_eval_nop_param_s param;opal_context* context;}; \
  opal_eval_nop_result_s* opal_eval_nop_ar1_s_run( const opal_eval_nop_ar1_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_ar1_s_set_param( opal_eval_nop_ar1_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  s2_t opal_eval_nop_ar1_s_main( opal_eval_nop_ar1_s* o, const bcore_arr_st_s* args );
#define TYPEOF_opal_eval_nop_ar2_s 3619862610
#define BETH_EXPAND_ITEM_opal_eval_nop_ar2_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_ar2_s ) \
    {aware_t _;opal_eval_nop_param_s param;opal_context* context;}; \
  opal_eval_nop_result_s* opal_eval_nop_ar2_s_run( const opal_eval_nop_ar2_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_ar2_s_set_param( opal_eval_nop_ar2_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  s2_t opal_eval_nop_ar2_s_main( opal_eval_nop_ar2_s* o, const bcore_arr_st_s* args );
#define BETH_EXPAND_GROUP_opal_eval_nop \
  BCORE_FORWARD_OBJECT( opal_eval_nop ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_result_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_param_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_generator_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_show_param_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_arr_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_set_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_ar1_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_nop_ar2_s ); \
  typedef void (*opal_eval_nop_set_param)( opal_eval_nop* o, const opal_eval_nop_param_s* param ); \
  typedef opal_eval_nop_result_s* (*opal_eval_nop_run)( const opal_eval_nop* o, opal_eval_nop_result_s* result ); \
  BCORE_DECLARE_SPECT( opal_eval_nop ) \
  { \
      bcore_spect_header_s header; \
      opal_eval_nop_set_param set_param; \
      opal_eval_nop_run run; \
  }; \
  static inline opal_eval_nop* opal_eval_nop_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_eval_nop, t ); return ( opal_eval_nop* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_eval_nop_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_eval_nop ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_eval_nop ) \
  static inline bl_t opal_eval_nop_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_eval_nop ); } \
  BETH_EXPAND_ITEM_opal_eval_nop_result_s \
  BETH_EXPAND_ITEM_opal_eval_nop_param_s \
  static inline void opal_eval_nop_a_set_param( opal_eval_nop* o, const opal_eval_nop_param_s* param ) { const opal_eval_nop_s* p = opal_eval_nop_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param ); } \
  static inline bl_t opal_eval_nop_a_defines_set_param( const opal_eval_nop* o ) { return opal_eval_nop_s_get_aware( o )->set_param != NULL; } \
  static inline opal_eval_nop_result_s* opal_eval_nop_a_run( const opal_eval_nop* o, opal_eval_nop_result_s* result ) { const opal_eval_nop_s* p = opal_eval_nop_s_get_aware( o ); assert( p->run ); return p->run( o, result ); } \
  static inline bl_t opal_eval_nop_a_defines_run( const opal_eval_nop* o ) { return opal_eval_nop_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_opal_eval_nop_generator_s \
  BETH_EXPAND_ITEM_opal_eval_nop_show_param_s \
  BETH_EXPAND_ITEM_opal_eval_nop_arr_s \
  BETH_EXPAND_ITEM_opal_eval_nop_set_s \
  BETH_EXPAND_ITEM_opal_eval_nop_ar1_s \
  BETH_EXPAND_ITEM_opal_eval_nop_ar2_s

/**********************************************************************************************************************/

vd_t opal_planted_signal_handler( const bcore_signal_s* o );

#endif // OPAL_PLANTED_H
// BETH_PLANT_SIGNATURE 3080972944
