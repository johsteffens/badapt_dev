/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-12-01T10:47:49Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying xoila source code.
 *  Source code defining this file is distributed across following files:
 *
 *  opal_context.h
 *  opal_holor.h
 *  opal_nop.h
 *  opal_eval_nop.h
 *  opal_sem.h
 *  opal_net.h
 *  opal_frame.h
 *  opal_eval_frame.h
 *  opal_adaptive.h
 *  opal_adaptor.h
 *  opal_adaptive.x
 *  opal_eval_frame.x
 *  opal_nop.x
 *
 */

#ifndef __opal_xo_H
#define __opal_xo_H

#include "bcore_control.h"

//To force a rebuild of this target by xoico, reset the hash key value below to 0.
#define HKEYOF_opal_xo 0x9414285EE1023F67ull

#define TYPEOF_opal_xo 0xD100E4B5B48FA9EDull

/**********************************************************************************************************************/
// source: opal_context.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_context

#define TYPEOF_opal_context 0x6A3588D344C618FBull
#define TYPEOF_opal_context_spect_s 0x02E20C344393189Bull
#define BETH_EXPAND_GROUP_opal_context \
  BCORE_FORWARD_OBJECT( opal_context ); \
  typedef bcore_prsg* (*opal_context_get_prsg)( opal_context* o ); \
  typedef sc_t (*opal_context_nameof)( const opal_context* o, tp_t name ); \
  typedef sc_t (*opal_context_ifnameof)( const opal_context* o, tp_t name ); \
  typedef tp_t (*opal_context_typeof)( const opal_context* o, sc_t name ); \
  typedef tp_t (*opal_context_entypeof)( opal_context* o, sc_t name ); \
  XOILA_DECLARE_SPECT( opal_context ) \
  { \
      bcore_spect_header_s header; \
      opal_context_get_prsg get_prsg; \
      opal_context_nameof nameof; \
      opal_context_ifnameof ifnameof; \
      opal_context_typeof typeof; \
      opal_context_entypeof entypeof; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_context ) \
  static inline bcore_prsg* opal_context_a_get_prsg( opal_context* o ){ const opal_context_spect_s* p = opal_context_spect_s_get_aware( o ); assert( p->get_prsg ); return p->get_prsg( o );} \
  static inline bl_t opal_context_a_defines_get_prsg( const opal_context* o ){ return  true;} \
  static inline bcore_prsg* opal_context_get_prsg_default( opal_context* o ){ OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return  NULL;} \
  static inline sc_t opal_context_a_nameof( const opal_context* o, tp_t name ){ const opal_context_spect_s* p = opal_context_spect_s_get_aware( o ); assert( p->nameof ); return p->nameof( o, name );} \
  static inline bl_t opal_context_a_defines_nameof( const opal_context* o ){ return  true;} \
  static inline sc_t opal_context_nameof_default( const opal_context* o, tp_t name ){ OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return  NULL;} \
  static inline sc_t opal_context_a_ifnameof( const opal_context* o, tp_t name ){ const opal_context_spect_s* p = opal_context_spect_s_get_aware( o ); assert( p->ifnameof ); return p->ifnameof( o, name );} \
  static inline bl_t opal_context_a_defines_ifnameof( const opal_context* o ){ return  true;} \
  static inline sc_t opal_context_ifnameof_default( const opal_context* o, tp_t name ){ OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return  NULL;} \
  static inline tp_t opal_context_a_typeof( const opal_context* o, sc_t name ){ const opal_context_spect_s* p = opal_context_spect_s_get_aware( o ); assert( p->typeof ); return p->typeof( o, name );} \
  static inline bl_t opal_context_a_defines_typeof( const opal_context* o ){ return  true;} \
  static inline tp_t opal_context_typeof_default( const opal_context* o, sc_t name ){ OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return  0;} \
  static inline tp_t opal_context_a_entypeof( opal_context* o, sc_t name ){ const opal_context_spect_s* p = opal_context_spect_s_get_aware( o ); assert( p->entypeof ); return p->entypeof( o, name );} \
  static inline bl_t opal_context_a_defines_entypeof( const opal_context* o ){ return  true;} \
  static inline tp_t opal_context_entypeof_default( opal_context* o, sc_t name ){ OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return  0;}

/**********************************************************************************************************************/
// source: opal_holor.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_holor

#define TYPEOF_opal_holor 0x5E258D3F8532A302ull
#define TYPEOF_opal_holor_spect_s 0x57FFB1BA7F4DD76Eull
#define TYPEOF_opal_holor_meta_s 0x2D7EAC11889E62F4ull
#define BETH_EXPAND_ITEM_opal_holor_meta_s \
  BCORE_DECLARE_OBJECT( opal_holor_meta_s ) \
  { \
      aware_t _; \
      bcore_inst* custom; \
      bhvm_mcode_node_s* mnode; \
      tp_t name; \
      bcore_inst* sem_id; \
      tp_t pclass; \
      bl_t htp; \
      bl_t active; \
  }; \
  static inline void opal_holor_meta_s_clear( opal_holor_meta_s* o ); \
  static inline tp_t opal_holor_meta_s_get_name( const opal_holor_meta_s* o ); \
  static inline tp_t opal_holor_meta_s_get_pclass( const opal_holor_meta_s* o ); \
  static inline bl_t opal_holor_meta_s_is_rollable( const opal_holor_meta_s* o ); \
  static inline bl_t opal_holor_meta_s_is_active( const opal_holor_meta_s* o ); \
  static inline bcore_inst* opal_holor_meta_s_get_custom( const opal_holor_meta_s* o ); \
  static inline bcore_inst* opal_holor_meta_s_set_custom( opal_holor_meta_s* o, const bcore_inst* custom ); \
  static inline bhvm_mcode_node_s* opal_holor_meta_s_get_node( const opal_holor_meta_s* o ); \
  static inline void opal_holor_meta_s_set_node( opal_holor_meta_s* o, bhvm_mcode_node_s* node ); \
  static inline void opal_holor_meta_s_clear( opal_holor_meta_s* o ){ o->name = 0; o->htp = false;} \
  static inline tp_t opal_holor_meta_s_get_name( const opal_holor_meta_s* o ){ return  o->name;} \
  static inline tp_t opal_holor_meta_s_get_pclass( const opal_holor_meta_s* o ){ return  o->pclass;} \
  static inline bl_t opal_holor_meta_s_is_rollable( const opal_holor_meta_s* o ){ return  !o->active || o->mnode->adaptive || ( o->mnode->cyclic && o->pclass == TYPEOF_pclass_ax1 );} \
  static inline bl_t opal_holor_meta_s_is_active( const opal_holor_meta_s* o ){ return   o->active;} \
  static inline bcore_inst* opal_holor_meta_s_get_custom( const opal_holor_meta_s* o ){ return  o->custom;} \
  static inline bcore_inst* opal_holor_meta_s_set_custom( opal_holor_meta_s* o, const bcore_inst* custom ){ return  bcore_inst_a_attach( &(o->custom ), (bcore_inst*)( bcore_inst_a_clone(custom)));} \
  static inline bhvm_mcode_node_s* opal_holor_meta_s_get_node( const opal_holor_meta_s* o ){ return  o->mnode;} \
  static inline void opal_holor_meta_s_set_node( opal_holor_meta_s* o, bhvm_mcode_node_s* node ){ bhvm_mcode_node_s_attach( &(o->mnode ),  bcore_fork( node ));}
#define TYPEOF_opal_holor_s 0x91F077AD82B25A1Cull
#define BETH_EXPAND_ITEM_opal_holor_s \
  BCORE_DECLARE_OBJECT( opal_holor_s ) \
  { \
      aware_t _; \
      opal_holor_meta_s m; \
      bhvm_holor_s h; \
  }; \
  void opal_holor_s_copy_typed( opal_holor_s* o, tp_t type, vc_t src );
#define BETH_EXPAND_GROUP_opal_holor \
  BCORE_FORWARD_OBJECT( opal_holor ); \
  BCORE_FORWARD_OBJECT( opal_holor_meta_s ); \
  BCORE_FORWARD_OBJECT( opal_holor_s ); \
  XOILA_DECLARE_SPECT( opal_holor ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_holor ) \
  BETH_EXPAND_ITEM_opal_holor_meta_s \
  BETH_EXPAND_ITEM_opal_holor_s

/**********************************************************************************************************************/
// source: opal_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop; embeds: opal_nop.x

#define TYPEOF_opal_nop 0x5D8297C19F02FCB5ull
#define TYPEOF_opal_nop_spect_s 0x9BF3343720664D91ull
#define TYPEOF_opal_nop_context_s 0x79C53054B56D41E3ull
#define BETH_EXPAND_ITEM_opal_nop_context_s \
  BCORE_DECLARE_OBJECT( opal_nop_context_s ) \
  { \
      aware_t _; \
      bcore_prsg* prsg; \
  }; \
  static inline bcore_prsg* opal_nop_context_s_get_prsg( opal_nop_context_s* o ); \
  static inline bcore_prsg* opal_nop_context_s_get_prsg( opal_nop_context_s* o ){ return  o->prsg;}
#define TYPEOF_track_ap 0x21E3A89A8C4A41E8ull
#define TYPEOF_track_dp 0x21F4A69A8C58B1B5ull
#define TYPEOF_track_ap_setup 0x78F0792E15C7E5C6ull
#define TYPEOF_track_dp_setup 0x2069E5DBBC7B0BBBull
#define TYPEOF_track_ap_shelve 0xBFC4C545E92192D2ull
#define TYPEOF_track_dp_shelve 0x56C690F342C2E701ull
#define TYPEOF_track_dp_cyclic_zero_grad 0x8DB5B98827B54B0Dull
#define TYPEOF_track_ap_cyclic_reset 0xFC2295E35CF7B886ull
#define TYPEOF_track_ap_cyclic_update 0xC5E85A23C30AD256ull
#define TYPEOF_track_dp_adaptive_zero_grad 0x48EB409A91B4D6ECull
#define TYPEOF_opal_nop_solve_result_s 0xEF49212A771B03F5ull
#define BETH_EXPAND_ITEM_opal_nop_solve_result_s \
  BCORE_DECLARE_OBJECT( opal_nop_solve_result_s ) \
  { \
      aware_t _; \
      opal_holor_s* h; \
      st_s* msg; \
      bl_t can_settle; \
      bl_t codable; \
      bl_t reducible; \
      tp_t type_vop_ap; \
      tp_t type_vop_dp_a; \
      tp_t type_vop_dp_b; \
      tp_t type_vop_dp_c; \
      vd_t attached; \
  };
#define BETH_EXPAND_GROUP_opal_nop \
  BCORE_FORWARD_OBJECT( opal_nop ); \
  BCORE_FORWARD_OBJECT( opal_nop_context_s ); \
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
  typedef bl_t (*opal_nop_is_param)( const opal_nop* o ); \
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
  XOILA_DECLARE_SPECT( opal_nop ) \
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
      opal_nop_is_param is_param; \
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
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop ) \
  BETH_EXPAND_ITEM_opal_nop_context_s \
  static inline sz_t opal_nop_a_arity( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->arity ); return p->arity( o );} \
  static inline bl_t opal_nop_a_defines_arity( const opal_nop* o ){ return  true;} \
  static inline sz_t opal_nop_arity_default( const opal_nop* o ){ ERR_fa( "Not implemented in '#<sc_t>'.", ifnameof( o->_ ) ); return  -1;} \
  static inline sz_t opal_nop_a_priority( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->priority ); return p->priority( o );} \
  static inline bl_t opal_nop_a_defines_priority( const opal_nop* o ){ return  true;} \
  static inline sz_t opal_nop_priority_default( const opal_nop* o ){ return  10;} \
  static inline sc_t opal_nop_a_symbol( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->symbol ); return p->symbol( o );} \
  static inline bl_t opal_nop_a_defines_symbol( const opal_nop* o ){ return  true;} \
  static inline sc_t opal_nop_symbol_default( const opal_nop* o ){ return  NULL;} \
  static inline bl_t opal_nop_a_reserved( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->reserved ); return p->reserved( o );} \
  static inline bl_t opal_nop_a_defines_reserved( const opal_nop* o ){ return  true;} \
  static inline bl_t opal_nop_reserved_default( const opal_nop* o ){ return  false;} \
  static inline opal_nop* opal_nop_a_create_op_of_arn( const opal_nop* o, sz_t n ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->create_op_of_arn ); return p->create_op_of_arn( o, n );} \
  static inline bl_t opal_nop_a_defines_create_op_of_arn( const opal_nop* o ){ return  true;} \
  static inline opal_nop* opal_nop_create_op_of_arn_default( const opal_nop* o, sz_t n ){ return  ( opal_nop_a_arity(o) == n ) ? opal_nop_a_clone(o) : NULL;} \
  BETH_EXPAND_ITEM_opal_nop_solve_result_s \
  static inline bl_t opal_nop_a_eci( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->eci ); return p->eci( o );} \
  static inline bl_t opal_nop_a_defines_eci( const opal_nop* o ){ return  true;} \
  static inline bl_t opal_nop_eci_default( const opal_nop* o ){ return  false;} \
  static inline bl_t opal_nop_a_solve( const opal_nop* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->solve ); return p->solve( o, context, a, result );} \
  static inline bl_t opal_nop_a_defines_solve( const opal_nop* o ){ return  true;} \
  bl_t opal_nop_solve__( const opal_nop* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline void opal_nop_a_solve_node( opal_nop* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->solve_node ); p->solve_node( o, node, deferred );} \
  static inline bl_t opal_nop_a_defines_solve_node( const opal_nop* o ){ return  true;} \
  void opal_nop_solve_node__( opal_nop* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ); \
  static inline bl_t opal_nop_a_is_param( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->is_param ); return p->is_param( o );} \
  static inline bl_t opal_nop_a_defines_is_param( const opal_nop* o ){ return  true;} \
  static inline bl_t opal_nop_is_param_default( const opal_nop* o ){ return  false;} \
  static inline bl_t opal_nop_a_is_cyclic( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->is_cyclic ); return p->is_cyclic( o );} \
  static inline bl_t opal_nop_a_defines_is_cyclic( const opal_nop* o ){ return  true;} \
  static inline bl_t opal_nop_is_cyclic_default( const opal_nop* o ){ return  false;} \
  static inline bl_t opal_nop_a_is_adaptive( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->is_adaptive ); return p->is_adaptive( o );} \
  static inline bl_t opal_nop_a_defines_is_adaptive( const opal_nop* o ){ return  true;} \
  static inline bl_t opal_nop_is_adaptive_default( const opal_nop* o ){ return  false;} \
  static inline void opal_nop_a_settle( const opal_nop* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->settle ); p->settle( o, context, result, out_nop, out_result );} \
  static inline bl_t opal_nop_a_defines_settle( const opal_nop* o ){ return  true;} \
  void opal_nop_settle_default( const opal_nop* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  static inline tp_t opal_nop_a_type_vop_ap( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->type_vop_ap ); return p->type_vop_ap( o );} \
  static inline bl_t opal_nop_a_defines_type_vop_ap( const opal_nop* o ){ return  opal_nop_spect_s_get_aware( o )->type_vop_ap != NULL;} \
  static inline tp_t opal_nop_a_type_vop_dp_a( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->type_vop_dp_a ); return p->type_vop_dp_a( o );} \
  static inline bl_t opal_nop_a_defines_type_vop_dp_a( const opal_nop* o ){ return  opal_nop_spect_s_get_aware( o )->type_vop_dp_a != NULL;} \
  static inline tp_t opal_nop_a_type_vop_dp_b( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->type_vop_dp_b ); return p->type_vop_dp_b( o );} \
  static inline bl_t opal_nop_a_defines_type_vop_dp_b( const opal_nop* o ){ return  opal_nop_spect_s_get_aware( o )->type_vop_dp_b != NULL;} \
  static inline tp_t opal_nop_a_type_vop_dp_c( const opal_nop* o ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->type_vop_dp_c ); return p->type_vop_dp_c( o );} \
  static inline bl_t opal_nop_a_defines_type_vop_dp_c( const opal_nop* o ){ return  opal_nop_spect_s_get_aware( o )->type_vop_dp_c != NULL;} \
  static inline sz_t opal_nop_a_mcode_push_ap_holor( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->mcode_push_ap_holor ); return p->mcode_push_ap_holor( o, result, arr_ci, mcf );} \
  static inline bl_t opal_nop_a_defines_mcode_push_ap_holor( const opal_nop* o ){ return  true;} \
  sz_t opal_nop_mcode_push_ap_holor_default( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_a_mcode_push_dp_holor( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->mcode_push_dp_holor ); return p->mcode_push_dp_holor( o, result, arr_ci, mcf );} \
  static inline bl_t opal_nop_a_defines_mcode_push_dp_holor( const opal_nop* o ){ return  true;} \
  sz_t opal_nop_mcode_push_dp_holor_default( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void opal_nop_a_mcode_push_ap_track( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->mcode_push_ap_track ); p->mcode_push_ap_track( o, result, arr_ci, mcf );} \
  static inline bl_t opal_nop_a_defines_mcode_push_ap_track( const opal_nop* o ){ return  true;} \
  void opal_nop_mcode_push_ap_track_default( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void opal_nop_a_mcode_push_dp_track( const opal_nop* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ const opal_nop_spect_s* p = opal_nop_spect_s_get_aware( o ); assert( p->mcode_push_dp_track ); p->mcode_push_dp_track( o, result, ch_id, arr_ci, mcf );} \
  static inline bl_t opal_nop_a_defines_mcode_push_dp_track( const opal_nop* o ){ return  true;} \
  void opal_nop_mcode_push_dp_track_default( const opal_nop* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BETH_EXPAND_GROUP_opal_nop_ar0 \
  BETH_EXPAND_GROUP_opal_nop_ar1 \
  BETH_EXPAND_GROUP_opal_nop_ar2 \
  BETH_EXPAND_GROUP_opal_nop_ar3

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar0

#define TYPEOF_opal_nop_ar0 0xE97C6858169E7CA7ull
#define TYPEOF_opal_nop_ar0_spect_s 0x3FAAE48406C00B97ull
#define TYPEOF_opal_nop_ar0_literal_s 0x631CD4B122107E81ull
#define BETH_EXPAND_ITEM_opal_nop_ar0_literal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_literal_s ) \
  { \
      aware_t _; \
      opal_holor_s* h; \
  }; \
  static inline sz_t opal_nop_ar0_literal_s_arity( const opal_nop_ar0_literal_s* o ); \
  bl_t opal_nop_ar0_literal_s_solve( const opal_nop_ar0_literal_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar0_literal_s_arity( const opal_nop_ar0_literal_s* o ){ return  0;}
#define TYPEOF_opal_nop_ar0_param_s 0xABC662B39BED96B3ull
#define BETH_EXPAND_ITEM_opal_nop_ar0_param_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_param_s ) \
  { \
      aware_t _; \
      opal_holor_s* h; \
  }; \
  static inline sz_t opal_nop_ar0_param_s_arity( const opal_nop_ar0_param_s* o ); \
  static inline bl_t opal_nop_ar0_param_s_is_param( const opal_nop_ar0_param_s* o ); \
  bl_t opal_nop_ar0_param_s_solve( const opal_nop_ar0_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar0_param_s_arity( const opal_nop_ar0_param_s* o ){ return  0;} \
  static inline bl_t opal_nop_ar0_param_s_is_param( const opal_nop_ar0_param_s* o ){ return  true;}
#define TYPEOF_opal_nop_ar0_adaptive_s 0x9D0B1A56C88471D0ull
#define BETH_EXPAND_ITEM_opal_nop_ar0_adaptive_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_adaptive_s ) \
  { \
      aware_t _; \
      opal_holor_s* h; \
  }; \
  static inline sz_t opal_nop_ar0_adaptive_s_arity( const opal_nop_ar0_adaptive_s* o ); \
  static inline bl_t opal_nop_ar0_adaptive_s_is_adaptive( const opal_nop_ar0_adaptive_s* o ); \
  bl_t opal_nop_ar0_adaptive_s_solve( const opal_nop_ar0_adaptive_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar0_adaptive_s_mcode_push_ap_holor( const opal_nop_ar0_adaptive_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar0_adaptive_s_mcode_push_dp_holor( const opal_nop_ar0_adaptive_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar0_adaptive_s_arity( const opal_nop_ar0_adaptive_s* o ){ return  0;} \
  static inline bl_t opal_nop_ar0_adaptive_s_is_adaptive( const opal_nop_ar0_adaptive_s* o ){ return  true;}
#define TYPEOF_opal_nop_ar0_rand_s 0x70D10473CFDDF3F1ull
#define BETH_EXPAND_ITEM_opal_nop_ar0_rand_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar0_rand_s ) \
  { \
      aware_t _; \
      opal_holor_s* h; \
      bcore_prsg* prsg; \
      f3_t min; \
      f3_t max; \
      f3_t density; \
  }; \
  static inline sz_t opal_nop_ar0_rand_s_arity( const opal_nop_ar0_rand_s* o ); \
  bl_t opal_nop_ar0_rand_s_solve( const opal_nop_ar0_rand_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar0_rand_s_mcode_push_ap_holor( const opal_nop_ar0_rand_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar0_rand_s_arity( const opal_nop_ar0_rand_s* o ){ return  0;}
#define BETH_EXPAND_GROUP_opal_nop_ar0 \
  BCORE_FORWARD_OBJECT( opal_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_literal_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_param_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_adaptive_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar0_rand_s ); \
  XOILA_DECLARE_SPECT( opal_nop_ar0 ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop_ar0 ) \
  BETH_EXPAND_ITEM_opal_nop_ar0_literal_s \
  BETH_EXPAND_ITEM_opal_nop_ar0_param_s \
  BETH_EXPAND_ITEM_opal_nop_ar0_adaptive_s \
  BETH_EXPAND_ITEM_opal_nop_ar0_rand_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar1

#define TYPEOF_opal_nop_ar1 0xE97C6758169E7AF4ull
#define TYPEOF_opal_nop_ar1_spect_s 0xE07A3B9E2ED058ACull
#define TYPEOF_opal_nop_ar1_identity_s 0x3CC80AE8128EE529ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_identity_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_identity_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_identity_s_arity( const opal_nop_ar1_identity_s* o ); \
  static inline bl_t opal_nop_ar1_identity_s_reserved( const opal_nop_ar1_identity_s* o ); \
  static inline sz_t opal_nop_ar1_identity_s_priority( const opal_nop_ar1_identity_s* o ); \
  bl_t opal_nop_ar1_identity_s_solve( const opal_nop_ar1_identity_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_identity_s_arity( const opal_nop_ar1_identity_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_identity_s_reserved( const opal_nop_ar1_identity_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_identity_s_priority( const opal_nop_ar1_identity_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_param_s 0xDD6D775FCE2B0850ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_param_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_param_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_param_s_arity( const opal_nop_ar1_param_s* o ); \
  static inline bl_t opal_nop_ar1_param_s_reserved( const opal_nop_ar1_param_s* o ); \
  static inline sz_t opal_nop_ar1_param_s_priority( const opal_nop_ar1_param_s* o ); \
  bl_t opal_nop_ar1_param_s_solve( const opal_nop_ar1_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar1_param_s_settle( const opal_nop_ar1_param_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  static inline sz_t opal_nop_ar1_param_s_arity( const opal_nop_ar1_param_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_param_s_reserved( const opal_nop_ar1_param_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_param_s_priority( const opal_nop_ar1_param_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_f3_s 0x7DAC139B2B550F0Cull
#define BETH_EXPAND_ITEM_opal_nop_ar1_f3_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_f3_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_f3_s_arity( const opal_nop_ar1_f3_s* o ); \
  static inline bl_t opal_nop_ar1_f3_s_reserved( const opal_nop_ar1_f3_s* o ); \
  static inline sz_t opal_nop_ar1_f3_s_priority( const opal_nop_ar1_f3_s* o ); \
  static inline sc_t opal_nop_ar1_f3_s_symbol( const opal_nop_ar1_f3_s* o ); \
  bl_t opal_nop_ar1_f3_s_solve( const opal_nop_ar1_f3_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_f3_s_arity( const opal_nop_ar1_f3_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_f3_s_reserved( const opal_nop_ar1_f3_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_f3_s_priority( const opal_nop_ar1_f3_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_f3_s_symbol( const opal_nop_ar1_f3_s* o ){ return  "f3_t";}
#define TYPEOF_opal_nop_ar1_f2_s 0x84FB4C9B2F1731E7ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_f2_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_f2_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_f2_s_arity( const opal_nop_ar1_f2_s* o ); \
  static inline bl_t opal_nop_ar1_f2_s_reserved( const opal_nop_ar1_f2_s* o ); \
  static inline sz_t opal_nop_ar1_f2_s_priority( const opal_nop_ar1_f2_s* o ); \
  static inline sc_t opal_nop_ar1_f2_s_symbol( const opal_nop_ar1_f2_s* o ); \
  bl_t opal_nop_ar1_f2_s_solve( const opal_nop_ar1_f2_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_f2_s_arity( const opal_nop_ar1_f2_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_f2_s_reserved( const opal_nop_ar1_f2_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_f2_s_priority( const opal_nop_ar1_f2_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_f2_s_symbol( const opal_nop_ar1_f2_s* o ){ return  "f2_t";}
#define TYPEOF_opal_nop_ar1_neg_s 0x8479714F149FD1BFull
#define BETH_EXPAND_ITEM_opal_nop_ar1_neg_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_neg_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_neg_s_arity( const opal_nop_ar1_neg_s* o ); \
  static inline bl_t opal_nop_ar1_neg_s_reserved( const opal_nop_ar1_neg_s* o ); \
  static inline sz_t opal_nop_ar1_neg_s_priority( const opal_nop_ar1_neg_s* o ); \
  static inline sc_t opal_nop_ar1_neg_s_symbol( const opal_nop_ar1_neg_s* o ); \
  static inline tp_t opal_nop_ar1_neg_s_type_vop_ap( const opal_nop_ar1_neg_s* o ); \
  static inline tp_t opal_nop_ar1_neg_s_type_vop_dp_a( const opal_nop_ar1_neg_s* o ); \
  opal_nop* opal_nop_ar1_neg_s_create_op_of_arn( const opal_nop_ar1_neg_s* o, sz_t n ); \
  static inline sz_t opal_nop_ar1_neg_s_arity( const opal_nop_ar1_neg_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_neg_s_reserved( const opal_nop_ar1_neg_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_neg_s_priority( const opal_nop_ar1_neg_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_neg_s_symbol( const opal_nop_ar1_neg_s* o ){ return  "neg";} \
  static inline tp_t opal_nop_ar1_neg_s_type_vop_ap( const opal_nop_ar1_neg_s* o ){ return  TYPEOF_bhvm_vop_ar1_neg_s;} \
  static inline tp_t opal_nop_ar1_neg_s_type_vop_dp_a( const opal_nop_ar1_neg_s* o ){ return  TYPEOF_bhvm_vop_ar1_neg_dp_s;}
#define TYPEOF_opal_nop_ar1_floor_s 0xEA452BD529DF7D8Bull
#define BETH_EXPAND_ITEM_opal_nop_ar1_floor_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_floor_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_floor_s_arity( const opal_nop_ar1_floor_s* o ); \
  static inline bl_t opal_nop_ar1_floor_s_reserved( const opal_nop_ar1_floor_s* o ); \
  static inline sz_t opal_nop_ar1_floor_s_priority( const opal_nop_ar1_floor_s* o ); \
  static inline sc_t opal_nop_ar1_floor_s_symbol( const opal_nop_ar1_floor_s* o ); \
  static inline tp_t opal_nop_ar1_floor_s_type_vop_ap( const opal_nop_ar1_floor_s* o ); \
  static inline sz_t opal_nop_ar1_floor_s_mcode_push_dp_holor( const opal_nop_ar1_floor_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar1_floor_s_arity( const opal_nop_ar1_floor_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_floor_s_reserved( const opal_nop_ar1_floor_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_floor_s_priority( const opal_nop_ar1_floor_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_floor_s_symbol( const opal_nop_ar1_floor_s* o ){ return  "floor";} \
  static inline tp_t opal_nop_ar1_floor_s_type_vop_ap( const opal_nop_ar1_floor_s* o ){ return  TYPEOF_bhvm_vop_ar1_floor_s;} \
  static inline sz_t opal_nop_ar1_floor_s_mcode_push_dp_holor( const opal_nop_ar1_floor_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar1_ceil_s 0xF05F26790FDE2CB6ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_ceil_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_ceil_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_ceil_s_arity( const opal_nop_ar1_ceil_s* o ); \
  static inline bl_t opal_nop_ar1_ceil_s_reserved( const opal_nop_ar1_ceil_s* o ); \
  static inline sz_t opal_nop_ar1_ceil_s_priority( const opal_nop_ar1_ceil_s* o ); \
  static inline sc_t opal_nop_ar1_ceil_s_symbol( const opal_nop_ar1_ceil_s* o ); \
  static inline tp_t opal_nop_ar1_ceil_s_type_vop_ap( const opal_nop_ar1_ceil_s* o ); \
  static inline sz_t opal_nop_ar1_ceil_s_mcode_push_dp_holor( const opal_nop_ar1_ceil_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar1_ceil_s_arity( const opal_nop_ar1_ceil_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_ceil_s_reserved( const opal_nop_ar1_ceil_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_ceil_s_priority( const opal_nop_ar1_ceil_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_ceil_s_symbol( const opal_nop_ar1_ceil_s* o ){ return  "ceil";} \
  static inline tp_t opal_nop_ar1_ceil_s_type_vop_ap( const opal_nop_ar1_ceil_s* o ){ return  TYPEOF_bhvm_vop_ar1_ceil_s;} \
  static inline sz_t opal_nop_ar1_ceil_s_mcode_push_dp_holor( const opal_nop_ar1_ceil_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar1_abs_s 0x54039A0BA0D6BB49ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_abs_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_abs_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_abs_s_arity( const opal_nop_ar1_abs_s* o ); \
  static inline bl_t opal_nop_ar1_abs_s_reserved( const opal_nop_ar1_abs_s* o ); \
  static inline sz_t opal_nop_ar1_abs_s_priority( const opal_nop_ar1_abs_s* o ); \
  static inline sc_t opal_nop_ar1_abs_s_symbol( const opal_nop_ar1_abs_s* o ); \
  static inline tp_t opal_nop_ar1_abs_s_type_vop_ap( const opal_nop_ar1_abs_s* o ); \
  static inline tp_t opal_nop_ar1_abs_s_type_vop_dp_a( const opal_nop_ar1_abs_s* o ); \
  static inline sz_t opal_nop_ar1_abs_s_arity( const opal_nop_ar1_abs_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_abs_s_reserved( const opal_nop_ar1_abs_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_abs_s_priority( const opal_nop_ar1_abs_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_abs_s_symbol( const opal_nop_ar1_abs_s* o ){ return  "abs";} \
  static inline tp_t opal_nop_ar1_abs_s_type_vop_ap( const opal_nop_ar1_abs_s* o ){ return  TYPEOF_bhvm_vop_ar1_abs_s;} \
  static inline tp_t opal_nop_ar1_abs_s_type_vop_dp_a( const opal_nop_ar1_abs_s* o ){ return  TYPEOF_bhvm_vop_ar2_abs_dp_s;}
#define TYPEOF_opal_nop_ar1_exp_s 0x64762F0893163AE6ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_exp_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_exp_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_exp_s_arity( const opal_nop_ar1_exp_s* o ); \
  static inline bl_t opal_nop_ar1_exp_s_reserved( const opal_nop_ar1_exp_s* o ); \
  static inline sz_t opal_nop_ar1_exp_s_priority( const opal_nop_ar1_exp_s* o ); \
  static inline sc_t opal_nop_ar1_exp_s_symbol( const opal_nop_ar1_exp_s* o ); \
  static inline tp_t opal_nop_ar1_exp_s_type_vop_ap( const opal_nop_ar1_exp_s* o ); \
  static inline tp_t opal_nop_ar1_exp_s_type_vop_dp_a( const opal_nop_ar1_exp_s* o ); \
  static inline sz_t opal_nop_ar1_exp_s_arity( const opal_nop_ar1_exp_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_exp_s_reserved( const opal_nop_ar1_exp_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_exp_s_priority( const opal_nop_ar1_exp_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_exp_s_symbol( const opal_nop_ar1_exp_s* o ){ return  "exp";} \
  static inline tp_t opal_nop_ar1_exp_s_type_vop_ap( const opal_nop_ar1_exp_s* o ){ return  TYPEOF_bhvm_vop_ar1_exp_s;} \
  static inline tp_t opal_nop_ar1_exp_s_type_vop_dp_a( const opal_nop_ar1_exp_s* o ){ return  TYPEOF_bhvm_vop_ar2_exp_dp_s;}
#define TYPEOF_opal_nop_ar1_log_s 0xA9BA311A3E621C9Full
#define BETH_EXPAND_ITEM_opal_nop_ar1_log_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_log_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_log_s_arity( const opal_nop_ar1_log_s* o ); \
  static inline bl_t opal_nop_ar1_log_s_reserved( const opal_nop_ar1_log_s* o ); \
  static inline sz_t opal_nop_ar1_log_s_priority( const opal_nop_ar1_log_s* o ); \
  static inline sc_t opal_nop_ar1_log_s_symbol( const opal_nop_ar1_log_s* o ); \
  static inline tp_t opal_nop_ar1_log_s_type_vop_ap( const opal_nop_ar1_log_s* o ); \
  static inline tp_t opal_nop_ar1_log_s_type_vop_dp_a( const opal_nop_ar1_log_s* o ); \
  static inline sz_t opal_nop_ar1_log_s_arity( const opal_nop_ar1_log_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_log_s_reserved( const opal_nop_ar1_log_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_log_s_priority( const opal_nop_ar1_log_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_log_s_symbol( const opal_nop_ar1_log_s* o ){ return  "log";} \
  static inline tp_t opal_nop_ar1_log_s_type_vop_ap( const opal_nop_ar1_log_s* o ){ return  TYPEOF_bhvm_vop_ar1_log_s;} \
  static inline tp_t opal_nop_ar1_log_s_type_vop_dp_a( const opal_nop_ar1_log_s* o ){ return  TYPEOF_bhvm_vop_ar2_log_dp_s;}
#define TYPEOF_opal_nop_ar1_inv_s 0xABD3D42B29A3D8CEull
#define BETH_EXPAND_ITEM_opal_nop_ar1_inv_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_inv_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_inv_s_arity( const opal_nop_ar1_inv_s* o ); \
  static inline bl_t opal_nop_ar1_inv_s_reserved( const opal_nop_ar1_inv_s* o ); \
  static inline sz_t opal_nop_ar1_inv_s_priority( const opal_nop_ar1_inv_s* o ); \
  static inline sc_t opal_nop_ar1_inv_s_symbol( const opal_nop_ar1_inv_s* o ); \
  static inline tp_t opal_nop_ar1_inv_s_type_vop_ap( const opal_nop_ar1_inv_s* o ); \
  static inline tp_t opal_nop_ar1_inv_s_type_vop_dp_a( const opal_nop_ar1_inv_s* o ); \
  static inline sz_t opal_nop_ar1_inv_s_arity( const opal_nop_ar1_inv_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_inv_s_reserved( const opal_nop_ar1_inv_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_inv_s_priority( const opal_nop_ar1_inv_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_inv_s_symbol( const opal_nop_ar1_inv_s* o ){ return  "inv";} \
  static inline tp_t opal_nop_ar1_inv_s_type_vop_ap( const opal_nop_ar1_inv_s* o ){ return  TYPEOF_bhvm_vop_ar1_inv_s;} \
  static inline tp_t opal_nop_ar1_inv_s_type_vop_dp_a( const opal_nop_ar1_inv_s* o ){ return  TYPEOF_bhvm_vop_ar2_inv_dp_s;}
#define TYPEOF_opal_nop_ar1_sqr_s 0x70972B637342AF27ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_sqr_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sqr_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_sqr_s_arity( const opal_nop_ar1_sqr_s* o ); \
  static inline bl_t opal_nop_ar1_sqr_s_reserved( const opal_nop_ar1_sqr_s* o ); \
  static inline sz_t opal_nop_ar1_sqr_s_priority( const opal_nop_ar1_sqr_s* o ); \
  static inline sc_t opal_nop_ar1_sqr_s_symbol( const opal_nop_ar1_sqr_s* o ); \
  static inline tp_t opal_nop_ar1_sqr_s_type_vop_ap( const opal_nop_ar1_sqr_s* o ); \
  static inline tp_t opal_nop_ar1_sqr_s_type_vop_dp_a( const opal_nop_ar1_sqr_s* o ); \
  static inline sz_t opal_nop_ar1_sqr_s_arity( const opal_nop_ar1_sqr_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_sqr_s_reserved( const opal_nop_ar1_sqr_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_sqr_s_priority( const opal_nop_ar1_sqr_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_sqr_s_symbol( const opal_nop_ar1_sqr_s* o ){ return  "sqr";} \
  static inline tp_t opal_nop_ar1_sqr_s_type_vop_ap( const opal_nop_ar1_sqr_s* o ){ return  TYPEOF_bhvm_vop_ar1_sqr_s;} \
  static inline tp_t opal_nop_ar1_sqr_s_type_vop_dp_a( const opal_nop_ar1_sqr_s* o ){ return  TYPEOF_bhvm_vop_ar2_sqr_dp_s;}
#define TYPEOF_opal_nop_ar1_srt_s 0x868C634B8CC45102ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_srt_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_srt_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_srt_s_arity( const opal_nop_ar1_srt_s* o ); \
  static inline bl_t opal_nop_ar1_srt_s_reserved( const opal_nop_ar1_srt_s* o ); \
  static inline sz_t opal_nop_ar1_srt_s_priority( const opal_nop_ar1_srt_s* o ); \
  static inline sc_t opal_nop_ar1_srt_s_symbol( const opal_nop_ar1_srt_s* o ); \
  static inline tp_t opal_nop_ar1_srt_s_type_vop_ap( const opal_nop_ar1_srt_s* o ); \
  static inline tp_t opal_nop_ar1_srt_s_type_vop_dp_a( const opal_nop_ar1_srt_s* o ); \
  static inline sz_t opal_nop_ar1_srt_s_arity( const opal_nop_ar1_srt_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_srt_s_reserved( const opal_nop_ar1_srt_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_srt_s_priority( const opal_nop_ar1_srt_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_srt_s_symbol( const opal_nop_ar1_srt_s* o ){ return  "srt";} \
  static inline tp_t opal_nop_ar1_srt_s_type_vop_ap( const opal_nop_ar1_srt_s* o ){ return  TYPEOF_bhvm_vop_ar1_srt_s;} \
  static inline tp_t opal_nop_ar1_srt_s_type_vop_dp_a( const opal_nop_ar1_srt_s* o ){ return  TYPEOF_bhvm_vop_ar2_srt_dp_s;}
#define TYPEOF_opal_nop_ar1_sigm_s 0xB6E9B117BCD52AD3ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_sigm_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sigm_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_sigm_s_arity( const opal_nop_ar1_sigm_s* o ); \
  static inline bl_t opal_nop_ar1_sigm_s_reserved( const opal_nop_ar1_sigm_s* o ); \
  static inline sz_t opal_nop_ar1_sigm_s_priority( const opal_nop_ar1_sigm_s* o ); \
  static inline sc_t opal_nop_ar1_sigm_s_symbol( const opal_nop_ar1_sigm_s* o ); \
  static inline tp_t opal_nop_ar1_sigm_s_type_vop_ap( const opal_nop_ar1_sigm_s* o ); \
  static inline tp_t opal_nop_ar1_sigm_s_type_vop_dp_a( const opal_nop_ar1_sigm_s* o ); \
  static inline sz_t opal_nop_ar1_sigm_s_arity( const opal_nop_ar1_sigm_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_sigm_s_reserved( const opal_nop_ar1_sigm_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_sigm_s_priority( const opal_nop_ar1_sigm_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_sigm_s_symbol( const opal_nop_ar1_sigm_s* o ){ return  "sigm";} \
  static inline tp_t opal_nop_ar1_sigm_s_type_vop_ap( const opal_nop_ar1_sigm_s* o ){ return  TYPEOF_bhvm_vop_ar1_sigm_s;} \
  static inline tp_t opal_nop_ar1_sigm_s_type_vop_dp_a( const opal_nop_ar1_sigm_s* o ){ return  TYPEOF_bhvm_vop_ar2_sigm_dp_s;}
#define TYPEOF_opal_nop_ar1_sigm_hard_s 0xC611260169036C0Dull
#define BETH_EXPAND_ITEM_opal_nop_ar1_sigm_hard_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sigm_hard_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_sigm_hard_s_arity( const opal_nop_ar1_sigm_hard_s* o ); \
  static inline bl_t opal_nop_ar1_sigm_hard_s_reserved( const opal_nop_ar1_sigm_hard_s* o ); \
  static inline sz_t opal_nop_ar1_sigm_hard_s_priority( const opal_nop_ar1_sigm_hard_s* o ); \
  static inline sc_t opal_nop_ar1_sigm_hard_s_symbol( const opal_nop_ar1_sigm_hard_s* o ); \
  static inline tp_t opal_nop_ar1_sigm_hard_s_type_vop_ap( const opal_nop_ar1_sigm_hard_s* o ); \
  static inline tp_t opal_nop_ar1_sigm_hard_s_type_vop_dp_a( const opal_nop_ar1_sigm_hard_s* o ); \
  static inline sz_t opal_nop_ar1_sigm_hard_s_arity( const opal_nop_ar1_sigm_hard_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_sigm_hard_s_reserved( const opal_nop_ar1_sigm_hard_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_sigm_hard_s_priority( const opal_nop_ar1_sigm_hard_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_sigm_hard_s_symbol( const opal_nop_ar1_sigm_hard_s* o ){ return  "sigm_hard";} \
  static inline tp_t opal_nop_ar1_sigm_hard_s_type_vop_ap( const opal_nop_ar1_sigm_hard_s* o ){ return  TYPEOF_bhvm_vop_ar1_sigm_hard_s;} \
  static inline tp_t opal_nop_ar1_sigm_hard_s_type_vop_dp_a( const opal_nop_ar1_sigm_hard_s* o ){ return  TYPEOF_bhvm_vop_ar2_sigm_hard_dp_s;}
#define TYPEOF_opal_nop_ar1_sigm_leaky_s 0x6EF06A77671A69AEull
#define BETH_EXPAND_ITEM_opal_nop_ar1_sigm_leaky_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_sigm_leaky_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_sigm_leaky_s_arity( const opal_nop_ar1_sigm_leaky_s* o ); \
  static inline bl_t opal_nop_ar1_sigm_leaky_s_reserved( const opal_nop_ar1_sigm_leaky_s* o ); \
  static inline sz_t opal_nop_ar1_sigm_leaky_s_priority( const opal_nop_ar1_sigm_leaky_s* o ); \
  static inline sc_t opal_nop_ar1_sigm_leaky_s_symbol( const opal_nop_ar1_sigm_leaky_s* o ); \
  static inline tp_t opal_nop_ar1_sigm_leaky_s_type_vop_ap( const opal_nop_ar1_sigm_leaky_s* o ); \
  static inline tp_t opal_nop_ar1_sigm_leaky_s_type_vop_dp_a( const opal_nop_ar1_sigm_leaky_s* o ); \
  static inline sz_t opal_nop_ar1_sigm_leaky_s_arity( const opal_nop_ar1_sigm_leaky_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_sigm_leaky_s_reserved( const opal_nop_ar1_sigm_leaky_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_sigm_leaky_s_priority( const opal_nop_ar1_sigm_leaky_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_sigm_leaky_s_symbol( const opal_nop_ar1_sigm_leaky_s* o ){ return  "sigm_leaky";} \
  static inline tp_t opal_nop_ar1_sigm_leaky_s_type_vop_ap( const opal_nop_ar1_sigm_leaky_s* o ){ return  TYPEOF_bhvm_vop_ar1_sigm_leaky_s;} \
  static inline tp_t opal_nop_ar1_sigm_leaky_s_type_vop_dp_a( const opal_nop_ar1_sigm_leaky_s* o ){ return  TYPEOF_bhvm_vop_ar2_sigm_leaky_dp_s;}
#define TYPEOF_opal_nop_ar1_tanh_s 0x5E4008F12305DCDEull
#define BETH_EXPAND_ITEM_opal_nop_ar1_tanh_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_tanh_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_tanh_s_arity( const opal_nop_ar1_tanh_s* o ); \
  static inline bl_t opal_nop_ar1_tanh_s_reserved( const opal_nop_ar1_tanh_s* o ); \
  static inline sz_t opal_nop_ar1_tanh_s_priority( const opal_nop_ar1_tanh_s* o ); \
  static inline sc_t opal_nop_ar1_tanh_s_symbol( const opal_nop_ar1_tanh_s* o ); \
  static inline tp_t opal_nop_ar1_tanh_s_type_vop_ap( const opal_nop_ar1_tanh_s* o ); \
  static inline tp_t opal_nop_ar1_tanh_s_type_vop_dp_a( const opal_nop_ar1_tanh_s* o ); \
  static inline sz_t opal_nop_ar1_tanh_s_arity( const opal_nop_ar1_tanh_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_tanh_s_reserved( const opal_nop_ar1_tanh_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_tanh_s_priority( const opal_nop_ar1_tanh_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_tanh_s_symbol( const opal_nop_ar1_tanh_s* o ){ return  "tanh";} \
  static inline tp_t opal_nop_ar1_tanh_s_type_vop_ap( const opal_nop_ar1_tanh_s* o ){ return  TYPEOF_bhvm_vop_ar1_tanh_s;} \
  static inline tp_t opal_nop_ar1_tanh_s_type_vop_dp_a( const opal_nop_ar1_tanh_s* o ){ return  TYPEOF_bhvm_vop_ar2_tanh_dp_s;}
#define TYPEOF_opal_nop_ar1_tanh_hard_s 0xDED6AB2822172EF2ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_tanh_hard_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_tanh_hard_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_tanh_hard_s_arity( const opal_nop_ar1_tanh_hard_s* o ); \
  static inline bl_t opal_nop_ar1_tanh_hard_s_reserved( const opal_nop_ar1_tanh_hard_s* o ); \
  static inline sz_t opal_nop_ar1_tanh_hard_s_priority( const opal_nop_ar1_tanh_hard_s* o ); \
  static inline sc_t opal_nop_ar1_tanh_hard_s_symbol( const opal_nop_ar1_tanh_hard_s* o ); \
  static inline tp_t opal_nop_ar1_tanh_hard_s_type_vop_ap( const opal_nop_ar1_tanh_hard_s* o ); \
  static inline tp_t opal_nop_ar1_tanh_hard_s_type_vop_dp_a( const opal_nop_ar1_tanh_hard_s* o ); \
  static inline sz_t opal_nop_ar1_tanh_hard_s_arity( const opal_nop_ar1_tanh_hard_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_tanh_hard_s_reserved( const opal_nop_ar1_tanh_hard_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_tanh_hard_s_priority( const opal_nop_ar1_tanh_hard_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_tanh_hard_s_symbol( const opal_nop_ar1_tanh_hard_s* o ){ return  "tanh_hard";} \
  static inline tp_t opal_nop_ar1_tanh_hard_s_type_vop_ap( const opal_nop_ar1_tanh_hard_s* o ){ return  TYPEOF_bhvm_vop_ar1_tanh_hard_s;} \
  static inline tp_t opal_nop_ar1_tanh_hard_s_type_vop_dp_a( const opal_nop_ar1_tanh_hard_s* o ){ return  TYPEOF_bhvm_vop_ar2_tanh_hard_dp_s;}
#define TYPEOF_opal_nop_ar1_tanh_leaky_s 0xD4378B03EDF8F55Bull
#define BETH_EXPAND_ITEM_opal_nop_ar1_tanh_leaky_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_tanh_leaky_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_tanh_leaky_s_arity( const opal_nop_ar1_tanh_leaky_s* o ); \
  static inline bl_t opal_nop_ar1_tanh_leaky_s_reserved( const opal_nop_ar1_tanh_leaky_s* o ); \
  static inline sz_t opal_nop_ar1_tanh_leaky_s_priority( const opal_nop_ar1_tanh_leaky_s* o ); \
  static inline sc_t opal_nop_ar1_tanh_leaky_s_symbol( const opal_nop_ar1_tanh_leaky_s* o ); \
  static inline tp_t opal_nop_ar1_tanh_leaky_s_type_vop_ap( const opal_nop_ar1_tanh_leaky_s* o ); \
  static inline tp_t opal_nop_ar1_tanh_leaky_s_type_vop_dp_a( const opal_nop_ar1_tanh_leaky_s* o ); \
  static inline sz_t opal_nop_ar1_tanh_leaky_s_arity( const opal_nop_ar1_tanh_leaky_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_tanh_leaky_s_reserved( const opal_nop_ar1_tanh_leaky_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_tanh_leaky_s_priority( const opal_nop_ar1_tanh_leaky_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_tanh_leaky_s_symbol( const opal_nop_ar1_tanh_leaky_s* o ){ return  "tanh_leaky";} \
  static inline tp_t opal_nop_ar1_tanh_leaky_s_type_vop_ap( const opal_nop_ar1_tanh_leaky_s* o ){ return  TYPEOF_bhvm_vop_ar1_tanh_leaky_s;} \
  static inline tp_t opal_nop_ar1_tanh_leaky_s_type_vop_dp_a( const opal_nop_ar1_tanh_leaky_s* o ){ return  TYPEOF_bhvm_vop_ar2_tanh_leaky_dp_s;}
#define TYPEOF_opal_nop_ar1_softplus_s 0xC7D764105D304A53ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_softplus_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_softplus_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_softplus_s_arity( const opal_nop_ar1_softplus_s* o ); \
  static inline bl_t opal_nop_ar1_softplus_s_reserved( const opal_nop_ar1_softplus_s* o ); \
  static inline sz_t opal_nop_ar1_softplus_s_priority( const opal_nop_ar1_softplus_s* o ); \
  static inline sc_t opal_nop_ar1_softplus_s_symbol( const opal_nop_ar1_softplus_s* o ); \
  static inline tp_t opal_nop_ar1_softplus_s_type_vop_ap( const opal_nop_ar1_softplus_s* o ); \
  static inline tp_t opal_nop_ar1_softplus_s_type_vop_dp_a( const opal_nop_ar1_softplus_s* o ); \
  static inline sz_t opal_nop_ar1_softplus_s_arity( const opal_nop_ar1_softplus_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_softplus_s_reserved( const opal_nop_ar1_softplus_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_softplus_s_priority( const opal_nop_ar1_softplus_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_softplus_s_symbol( const opal_nop_ar1_softplus_s* o ){ return  "softplus";} \
  static inline tp_t opal_nop_ar1_softplus_s_type_vop_ap( const opal_nop_ar1_softplus_s* o ){ return  TYPEOF_bhvm_vop_ar1_softplus_s;} \
  static inline tp_t opal_nop_ar1_softplus_s_type_vop_dp_a( const opal_nop_ar1_softplus_s* o ){ return  TYPEOF_bhvm_vop_ar2_softplus_dp_s;}
#define TYPEOF_opal_nop_ar1_softmax_s 0xEF97C56CCDDFB71Full
#define BETH_EXPAND_ITEM_opal_nop_ar1_softmax_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_softmax_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_softmax_s_arity( const opal_nop_ar1_softmax_s* o ); \
  static inline bl_t opal_nop_ar1_softmax_s_reserved( const opal_nop_ar1_softmax_s* o ); \
  static inline sz_t opal_nop_ar1_softmax_s_priority( const opal_nop_ar1_softmax_s* o ); \
  static inline sc_t opal_nop_ar1_softmax_s_symbol( const opal_nop_ar1_softmax_s* o ); \
  static inline tp_t opal_nop_ar1_softmax_s_type_vop_ap( const opal_nop_ar1_softmax_s* o ); \
  static inline tp_t opal_nop_ar1_softmax_s_type_vop_dp_a( const opal_nop_ar1_softmax_s* o ); \
  static inline sz_t opal_nop_ar1_softmax_s_arity( const opal_nop_ar1_softmax_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_softmax_s_reserved( const opal_nop_ar1_softmax_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_softmax_s_priority( const opal_nop_ar1_softmax_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_softmax_s_symbol( const opal_nop_ar1_softmax_s* o ){ return  "softmax";} \
  static inline tp_t opal_nop_ar1_softmax_s_type_vop_ap( const opal_nop_ar1_softmax_s* o ){ return  TYPEOF_bhvm_vop_ar1_softmax_s;} \
  static inline tp_t opal_nop_ar1_softmax_s_type_vop_dp_a( const opal_nop_ar1_softmax_s* o ){ return  TYPEOF_bhvm_vop_ar2_softmax_dp_s;}
#define TYPEOF_opal_nop_ar1_relu_s 0xBFEE43BD8082FD01ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_relu_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_relu_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_relu_s_arity( const opal_nop_ar1_relu_s* o ); \
  static inline bl_t opal_nop_ar1_relu_s_reserved( const opal_nop_ar1_relu_s* o ); \
  static inline sz_t opal_nop_ar1_relu_s_priority( const opal_nop_ar1_relu_s* o ); \
  static inline sc_t opal_nop_ar1_relu_s_symbol( const opal_nop_ar1_relu_s* o ); \
  static inline tp_t opal_nop_ar1_relu_s_type_vop_ap( const opal_nop_ar1_relu_s* o ); \
  static inline tp_t opal_nop_ar1_relu_s_type_vop_dp_a( const opal_nop_ar1_relu_s* o ); \
  static inline sz_t opal_nop_ar1_relu_s_arity( const opal_nop_ar1_relu_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_relu_s_reserved( const opal_nop_ar1_relu_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_relu_s_priority( const opal_nop_ar1_relu_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_relu_s_symbol( const opal_nop_ar1_relu_s* o ){ return  "relu";} \
  static inline tp_t opal_nop_ar1_relu_s_type_vop_ap( const opal_nop_ar1_relu_s* o ){ return  TYPEOF_bhvm_vop_ar1_relu_s;} \
  static inline tp_t opal_nop_ar1_relu_s_type_vop_dp_a( const opal_nop_ar1_relu_s* o ){ return  TYPEOF_bhvm_vop_ar2_relu_dp_s;}
#define TYPEOF_opal_nop_ar1_relu_leaky_s 0xCBF43165ADC9871Cull
#define BETH_EXPAND_ITEM_opal_nop_ar1_relu_leaky_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_relu_leaky_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_relu_leaky_s_arity( const opal_nop_ar1_relu_leaky_s* o ); \
  static inline bl_t opal_nop_ar1_relu_leaky_s_reserved( const opal_nop_ar1_relu_leaky_s* o ); \
  static inline sz_t opal_nop_ar1_relu_leaky_s_priority( const opal_nop_ar1_relu_leaky_s* o ); \
  static inline sc_t opal_nop_ar1_relu_leaky_s_symbol( const opal_nop_ar1_relu_leaky_s* o ); \
  static inline tp_t opal_nop_ar1_relu_leaky_s_type_vop_ap( const opal_nop_ar1_relu_leaky_s* o ); \
  static inline tp_t opal_nop_ar1_relu_leaky_s_type_vop_dp_a( const opal_nop_ar1_relu_leaky_s* o ); \
  static inline sz_t opal_nop_ar1_relu_leaky_s_arity( const opal_nop_ar1_relu_leaky_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_relu_leaky_s_reserved( const opal_nop_ar1_relu_leaky_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_relu_leaky_s_priority( const opal_nop_ar1_relu_leaky_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar1_relu_leaky_s_symbol( const opal_nop_ar1_relu_leaky_s* o ){ return  "relu_leaky";} \
  static inline tp_t opal_nop_ar1_relu_leaky_s_type_vop_ap( const opal_nop_ar1_relu_leaky_s* o ){ return  TYPEOF_bhvm_vop_ar1_relu_leaky_s;} \
  static inline tp_t opal_nop_ar1_relu_leaky_s_type_vop_dp_a( const opal_nop_ar1_relu_leaky_s* o ){ return  TYPEOF_bhvm_vop_ar2_relu_leaky_dp_s;}
#define TYPEOF_opal_nop_ar1_output_s 0xFA4DD8BFC5ED8422ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_output_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_output_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_output_s_arity( const opal_nop_ar1_output_s* o ); \
  static inline bl_t opal_nop_ar1_output_s_reserved( const opal_nop_ar1_output_s* o ); \
  bl_t opal_nop_ar1_output_s_solve( const opal_nop_ar1_output_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar1_output_s_mcode_push_dp_holor( const opal_nop_ar1_output_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar1_output_s_arity( const opal_nop_ar1_output_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_output_s_reserved( const opal_nop_ar1_output_s* o ){ return  true;}
#define TYPEOF_opal_nop_ar1_adaptive_s 0x2667C807DFE25151ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_adaptive_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_adaptive_s ) \
  { \
      aware_t _; \
      tp_t name; \
  }; \
  static inline sz_t opal_nop_ar1_adaptive_s_arity( const opal_nop_ar1_adaptive_s* o ); \
  static inline bl_t opal_nop_ar1_adaptive_s_reserved( const opal_nop_ar1_adaptive_s* o ); \
  static inline sz_t opal_nop_ar1_adaptive_s_priority( const opal_nop_ar1_adaptive_s* o ); \
  static inline bl_t opal_nop_ar1_adaptive_s_is_adaptive( const opal_nop_ar1_adaptive_s* o ); \
  bl_t opal_nop_ar1_adaptive_s_solve( const opal_nop_ar1_adaptive_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar1_adaptive_s_settle( const opal_nop_ar1_adaptive_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  static inline sz_t opal_nop_ar1_adaptive_s_arity( const opal_nop_ar1_adaptive_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_adaptive_s_reserved( const opal_nop_ar1_adaptive_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_adaptive_s_priority( const opal_nop_ar1_adaptive_s* o ){ return  8;} \
  static inline bl_t opal_nop_ar1_adaptive_s_is_adaptive( const opal_nop_ar1_adaptive_s* o ){ return  true;}
#define TYPEOF_opal_nop_ar1_dimof_s 0xCAD96736ED89269Aull
#define BETH_EXPAND_ITEM_opal_nop_ar1_dimof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_dimof_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_dimof_s_arity( const opal_nop_ar1_dimof_s* o ); \
  static inline bl_t opal_nop_ar1_dimof_s_reserved( const opal_nop_ar1_dimof_s* o ); \
  static inline sc_t opal_nop_ar1_dimof_s_symbol( const opal_nop_ar1_dimof_s* o ); \
  static inline sz_t opal_nop_ar1_dimof_s_priority( const opal_nop_ar1_dimof_s* o ); \
  bl_t opal_nop_ar1_dimof_s_solve( const opal_nop_ar1_dimof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_dimof_s_arity( const opal_nop_ar1_dimof_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_dimof_s_reserved( const opal_nop_ar1_dimof_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar1_dimof_s_symbol( const opal_nop_ar1_dimof_s* o ){ return  "dimof";} \
  static inline sz_t opal_nop_ar1_dimof_s_priority( const opal_nop_ar1_dimof_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_volof_s 0x4E3C7B4BDA366E81ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_volof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_volof_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_volof_s_arity( const opal_nop_ar1_volof_s* o ); \
  static inline bl_t opal_nop_ar1_volof_s_reserved( const opal_nop_ar1_volof_s* o ); \
  static inline sc_t opal_nop_ar1_volof_s_symbol( const opal_nop_ar1_volof_s* o ); \
  static inline sz_t opal_nop_ar1_volof_s_priority( const opal_nop_ar1_volof_s* o ); \
  bl_t opal_nop_ar1_volof_s_solve( const opal_nop_ar1_volof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_volof_s_arity( const opal_nop_ar1_volof_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_volof_s_reserved( const opal_nop_ar1_volof_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar1_volof_s_symbol( const opal_nop_ar1_volof_s* o ){ return  "volof";} \
  static inline sz_t opal_nop_ar1_volof_s_priority( const opal_nop_ar1_volof_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_constof_s 0x086B3BCCE9284E6Bull
#define BETH_EXPAND_ITEM_opal_nop_ar1_constof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_constof_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_constof_s_arity( const opal_nop_ar1_constof_s* o ); \
  static inline bl_t opal_nop_ar1_constof_s_reserved( const opal_nop_ar1_constof_s* o ); \
  static inline sc_t opal_nop_ar1_constof_s_symbol( const opal_nop_ar1_constof_s* o ); \
  static inline sz_t opal_nop_ar1_constof_s_priority( const opal_nop_ar1_constof_s* o ); \
  bl_t opal_nop_ar1_constof_s_solve( const opal_nop_ar1_constof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_constof_s_arity( const opal_nop_ar1_constof_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_constof_s_reserved( const opal_nop_ar1_constof_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar1_constof_s_symbol( const opal_nop_ar1_constof_s* o ){ return  "constof";} \
  static inline sz_t opal_nop_ar1_constof_s_priority( const opal_nop_ar1_constof_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_zeroof_s 0x9A876F08A728A8BCull
#define BETH_EXPAND_ITEM_opal_nop_ar1_zeroof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_zeroof_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_zeroof_s_arity( const opal_nop_ar1_zeroof_s* o ); \
  static inline bl_t opal_nop_ar1_zeroof_s_reserved( const opal_nop_ar1_zeroof_s* o ); \
  static inline sc_t opal_nop_ar1_zeroof_s_symbol( const opal_nop_ar1_zeroof_s* o ); \
  static inline sz_t opal_nop_ar1_zeroof_s_priority( const opal_nop_ar1_zeroof_s* o ); \
  bl_t opal_nop_ar1_zeroof_s_solve( const opal_nop_ar1_zeroof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_zeroof_s_arity( const opal_nop_ar1_zeroof_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_zeroof_s_reserved( const opal_nop_ar1_zeroof_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar1_zeroof_s_symbol( const opal_nop_ar1_zeroof_s* o ){ return  "zeroof";} \
  static inline sz_t opal_nop_ar1_zeroof_s_priority( const opal_nop_ar1_zeroof_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_shapeof_s 0x607FFB5CE289C145ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_shapeof_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_shapeof_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_shapeof_s_arity( const opal_nop_ar1_shapeof_s* o ); \
  static inline bl_t opal_nop_ar1_shapeof_s_reserved( const opal_nop_ar1_shapeof_s* o ); \
  static inline sc_t opal_nop_ar1_shapeof_s_symbol( const opal_nop_ar1_shapeof_s* o ); \
  static inline sz_t opal_nop_ar1_shapeof_s_priority( const opal_nop_ar1_shapeof_s* o ); \
  bl_t opal_nop_ar1_shapeof_s_solve( const opal_nop_ar1_shapeof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar1_shapeof_s_arity( const opal_nop_ar1_shapeof_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_shapeof_s_reserved( const opal_nop_ar1_shapeof_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar1_shapeof_s_symbol( const opal_nop_ar1_shapeof_s* o ){ return  "shapeof";} \
  static inline sz_t opal_nop_ar1_shapeof_s_priority( const opal_nop_ar1_shapeof_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_rand_s 0x0B773E0B122403DCull
#define BETH_EXPAND_ITEM_opal_nop_ar1_rand_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_rand_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_rand_s_arity( const opal_nop_ar1_rand_s* o ); \
  static inline bl_t opal_nop_ar1_rand_s_reserved( const opal_nop_ar1_rand_s* o ); \
  static inline sc_t opal_nop_ar1_rand_s_symbol( const opal_nop_ar1_rand_s* o ); \
  static inline sz_t opal_nop_ar1_rand_s_priority( const opal_nop_ar1_rand_s* o ); \
  bl_t opal_nop_ar1_rand_s_solve( const opal_nop_ar1_rand_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar1_rand_s_settle( const opal_nop_ar1_rand_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  static inline sz_t opal_nop_ar1_rand_s_arity( const opal_nop_ar1_rand_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_rand_s_reserved( const opal_nop_ar1_rand_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar1_rand_s_symbol( const opal_nop_ar1_rand_s* o ){ return  "rand";} \
  static inline sz_t opal_nop_ar1_rand_s_priority( const opal_nop_ar1_rand_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar1_cast_htp_s 0x1032F115DF7DD21Bull
#define BETH_EXPAND_ITEM_opal_nop_ar1_cast_htp_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_cast_htp_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar1_cast_htp_s_arity( const opal_nop_ar1_cast_htp_s* o ); \
  static inline bl_t opal_nop_ar1_cast_htp_s_reserved( const opal_nop_ar1_cast_htp_s* o ); \
  static inline sz_t opal_nop_ar1_cast_htp_s_priority( const opal_nop_ar1_cast_htp_s* o ); \
  static inline sc_t opal_nop_ar1_cast_htp_s_symbol( const opal_nop_ar1_cast_htp_s* o ); \
  bl_t opal_nop_ar1_cast_htp_s_solve( const opal_nop_ar1_cast_htp_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar1_cast_htp_s_mcode_push_ap_holor( const opal_nop_ar1_cast_htp_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar1_cast_htp_s_mcode_push_dp_holor( const opal_nop_ar1_cast_htp_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar1_cast_htp_s_arity( const opal_nop_ar1_cast_htp_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_cast_htp_s_reserved( const opal_nop_ar1_cast_htp_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_cast_htp_s_priority( const opal_nop_ar1_cast_htp_s* o ){ return  12;} \
  static inline sc_t opal_nop_ar1_cast_htp_s_symbol( const opal_nop_ar1_cast_htp_s* o ){ return  "htp";}
#define TYPEOF_opal_nop_ar1_reshape_s 0xB239B8D91930E8C3ull
#define BETH_EXPAND_ITEM_opal_nop_ar1_reshape_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_reshape_s ) \
  { \
      aware_t _; \
      bhvm_shape_s shape; \
  }; \
  static inline sz_t opal_nop_ar1_reshape_s_arity( const opal_nop_ar1_reshape_s* o ); \
  static inline bl_t opal_nop_ar1_reshape_s_reserved( const opal_nop_ar1_reshape_s* o ); \
  static inline sz_t opal_nop_ar1_reshape_s_priority( const opal_nop_ar1_reshape_s* o ); \
  bl_t opal_nop_ar1_reshape_s_solve( const opal_nop_ar1_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar1_reshape_s_mcode_push_ap_holor( const opal_nop_ar1_reshape_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar1_reshape_s_mcode_push_dp_holor( const opal_nop_ar1_reshape_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar1_reshape_s_arity( const opal_nop_ar1_reshape_s* o ){ return  1;} \
  static inline bl_t opal_nop_ar1_reshape_s_reserved( const opal_nop_ar1_reshape_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar1_reshape_s_priority( const opal_nop_ar1_reshape_s* o ){ return  8;}
#define BETH_EXPAND_GROUP_opal_nop_ar1 \
  BCORE_FORWARD_OBJECT( opal_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_identity_s ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar1_param_s ); \
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
  XOILA_DECLARE_SPECT( opal_nop_ar1 ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop_ar1 ) \
  BETH_EXPAND_ITEM_opal_nop_ar1_identity_s \
  BETH_EXPAND_ITEM_opal_nop_ar1_param_s \
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

#define TYPEOF_opal_nop_ar2 0xE97C6A58169E800Dull
#define TYPEOF_opal_nop_ar2_spect_s 0xF68BF1BB0F1FE049ull
#define TYPEOF_opal_nop_ar2_add_s 0xB96052B9BA4582E7ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_add_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_add_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_add_s_arity( const opal_nop_ar2_add_s* o ); \
  static inline bl_t opal_nop_ar2_add_s_reserved( const opal_nop_ar2_add_s* o ); \
  static inline sz_t opal_nop_ar2_add_s_priority( const opal_nop_ar2_add_s* o ); \
  static inline bl_t opal_nop_ar2_add_s_eci( const opal_nop_ar2_add_s* o ); \
  static inline sc_t opal_nop_ar2_add_s_symbol( const opal_nop_ar2_add_s* o ); \
  static inline tp_t opal_nop_ar2_add_s_type_vop_ap( const opal_nop_ar2_add_s* o ); \
  static inline tp_t opal_nop_ar2_add_s_type_vop_dp_a( const opal_nop_ar2_add_s* o ); \
  static inline tp_t opal_nop_ar2_add_s_type_vop_dp_b( const opal_nop_ar2_add_s* o ); \
  static inline sz_t opal_nop_ar2_add_s_arity( const opal_nop_ar2_add_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_add_s_reserved( const opal_nop_ar2_add_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_add_s_priority( const opal_nop_ar2_add_s* o ){ return  8;} \
  static inline bl_t opal_nop_ar2_add_s_eci( const opal_nop_ar2_add_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_add_s_symbol( const opal_nop_ar2_add_s* o ){ return  "+";} \
  static inline tp_t opal_nop_ar2_add_s_type_vop_ap( const opal_nop_ar2_add_s* o ){ return  TYPEOF_bhvm_vop_ar2_add_s;} \
  static inline tp_t opal_nop_ar2_add_s_type_vop_dp_a( const opal_nop_ar2_add_s* o ){ return  TYPEOF_bhvm_vop_ar1_add_dp_a_s;} \
  static inline tp_t opal_nop_ar2_add_s_type_vop_dp_b( const opal_nop_ar2_add_s* o ){ return  TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_opal_nop_ar2_sub_s 0x2A19BB45DAC68786ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_sub_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_sub_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_sub_s_arity( const opal_nop_ar2_sub_s* o ); \
  static inline bl_t opal_nop_ar2_sub_s_reserved( const opal_nop_ar2_sub_s* o ); \
  static inline sz_t opal_nop_ar2_sub_s_priority( const opal_nop_ar2_sub_s* o ); \
  static inline bl_t opal_nop_ar2_sub_s_eci( const opal_nop_ar2_sub_s* o ); \
  static inline sc_t opal_nop_ar2_sub_s_symbol( const opal_nop_ar2_sub_s* o ); \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_ap( const opal_nop_ar2_sub_s* o ); \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_dp_a( const opal_nop_ar2_sub_s* o ); \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_dp_b( const opal_nop_ar2_sub_s* o ); \
  opal_nop* opal_nop_ar2_sub_s_create_op_of_arn( const opal_nop_ar2_sub_s* o, sz_t n ); \
  static inline sz_t opal_nop_ar2_sub_s_arity( const opal_nop_ar2_sub_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_sub_s_reserved( const opal_nop_ar2_sub_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_sub_s_priority( const opal_nop_ar2_sub_s* o ){ return  8;} \
  static inline bl_t opal_nop_ar2_sub_s_eci( const opal_nop_ar2_sub_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_sub_s_symbol( const opal_nop_ar2_sub_s* o ){ return  "-";} \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_ap( const opal_nop_ar2_sub_s* o ){ return  TYPEOF_bhvm_vop_ar2_sub_s;} \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_dp_a( const opal_nop_ar2_sub_s* o ){ return  TYPEOF_bhvm_vop_ar1_sub_dp_a_s;} \
  static inline tp_t opal_nop_ar2_sub_s_type_vop_dp_b( const opal_nop_ar2_sub_s* o ){ return  TYPEOF_bhvm_vop_ar1_sub_dp_b_s;}
#define TYPEOF_opal_nop_ar2_mul_s 0xEB7B4439E877710Aull
#define BETH_EXPAND_ITEM_opal_nop_ar2_mul_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_mul_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_mul_s_arity( const opal_nop_ar2_mul_s* o ); \
  static inline bl_t opal_nop_ar2_mul_s_reserved( const opal_nop_ar2_mul_s* o ); \
  static inline sz_t opal_nop_ar2_mul_s_priority( const opal_nop_ar2_mul_s* o ); \
  static inline bl_t opal_nop_ar2_mul_s_eci( const opal_nop_ar2_mul_s* o ); \
  static inline sc_t opal_nop_ar2_mul_s_symbol( const opal_nop_ar2_mul_s* o ); \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_ap( const opal_nop_ar2_mul_s* o ); \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_dp_a( const opal_nop_ar2_mul_s* o ); \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_dp_b( const opal_nop_ar2_mul_s* o ); \
  static inline sz_t opal_nop_ar2_mul_s_arity( const opal_nop_ar2_mul_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_mul_s_reserved( const opal_nop_ar2_mul_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_mul_s_priority( const opal_nop_ar2_mul_s* o ){ return  10;} \
  static inline bl_t opal_nop_ar2_mul_s_eci( const opal_nop_ar2_mul_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_mul_s_symbol( const opal_nop_ar2_mul_s* o ){ return  "*";} \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_ap( const opal_nop_ar2_mul_s* o ){ return  TYPEOF_bhvm_vop_ar2_mul_s;} \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_dp_a( const opal_nop_ar2_mul_s* o ){ return  TYPEOF_bhvm_vop_ar2_mul_dp_a_s;} \
  static inline tp_t opal_nop_ar2_mul_s_type_vop_dp_b( const opal_nop_ar2_mul_s* o ){ return  TYPEOF_bhvm_vop_ar2_mul_dp_b_s;}
#define TYPEOF_opal_nop_ar2_div_s 0x46DAFD544F0AC1EBull
#define BETH_EXPAND_ITEM_opal_nop_ar2_div_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_div_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_div_s_arity( const opal_nop_ar2_div_s* o ); \
  static inline bl_t opal_nop_ar2_div_s_reserved( const opal_nop_ar2_div_s* o ); \
  static inline sz_t opal_nop_ar2_div_s_priority( const opal_nop_ar2_div_s* o ); \
  static inline bl_t opal_nop_ar2_div_s_eci( const opal_nop_ar2_div_s* o ); \
  static inline sc_t opal_nop_ar2_div_s_symbol( const opal_nop_ar2_div_s* o ); \
  static inline tp_t opal_nop_ar2_div_s_type_vop_ap( const opal_nop_ar2_div_s* o ); \
  static inline tp_t opal_nop_ar2_div_s_type_vop_dp_a( const opal_nop_ar2_div_s* o ); \
  static inline tp_t opal_nop_ar2_div_s_type_vop_dp_b( const opal_nop_ar2_div_s* o ); \
  static inline sz_t opal_nop_ar2_div_s_arity( const opal_nop_ar2_div_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_div_s_reserved( const opal_nop_ar2_div_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_div_s_priority( const opal_nop_ar2_div_s* o ){ return  10;} \
  static inline bl_t opal_nop_ar2_div_s_eci( const opal_nop_ar2_div_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_div_s_symbol( const opal_nop_ar2_div_s* o ){ return  "/";} \
  static inline tp_t opal_nop_ar2_div_s_type_vop_ap( const opal_nop_ar2_div_s* o ){ return  TYPEOF_bhvm_vop_ar2_div_s;} \
  static inline tp_t opal_nop_ar2_div_s_type_vop_dp_a( const opal_nop_ar2_div_s* o ){ return  TYPEOF_bhvm_vop_ar2_div_dp_a_s;} \
  static inline tp_t opal_nop_ar2_div_s_type_vop_dp_b( const opal_nop_ar2_div_s* o ){ return  TYPEOF_bhvm_vop_ar3_div_dp_b_s;}
#define TYPEOF_opal_nop_ar2_pow_s 0x6A2BDCA5372CC0EAull
#define BETH_EXPAND_ITEM_opal_nop_ar2_pow_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_pow_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_pow_s_arity( const opal_nop_ar2_pow_s* o ); \
  static inline bl_t opal_nop_ar2_pow_s_reserved( const opal_nop_ar2_pow_s* o ); \
  static inline sz_t opal_nop_ar2_pow_s_priority( const opal_nop_ar2_pow_s* o ); \
  static inline bl_t opal_nop_ar2_pow_s_eci( const opal_nop_ar2_pow_s* o ); \
  static inline sc_t opal_nop_ar2_pow_s_symbol( const opal_nop_ar2_pow_s* o ); \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_ap( const opal_nop_ar2_pow_s* o ); \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_dp_a( const opal_nop_ar2_pow_s* o ); \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_dp_b( const opal_nop_ar2_pow_s* o ); \
  static inline sz_t opal_nop_ar2_pow_s_arity( const opal_nop_ar2_pow_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_pow_s_reserved( const opal_nop_ar2_pow_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_pow_s_priority( const opal_nop_ar2_pow_s* o ){ return  12;} \
  static inline bl_t opal_nop_ar2_pow_s_eci( const opal_nop_ar2_pow_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_pow_s_symbol( const opal_nop_ar2_pow_s* o ){ return  "^";} \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_ap( const opal_nop_ar2_pow_s* o ){ return  TYPEOF_bhvm_vop_ar2_pow_s;} \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_dp_a( const opal_nop_ar2_pow_s* o ){ return  TYPEOF_bhvm_vop_ar3_pow_dp_a_s;} \
  static inline tp_t opal_nop_ar2_pow_s_type_vop_dp_b( const opal_nop_ar2_pow_s* o ){ return  TYPEOF_bhvm_vop_ar3_pow_dp_b_s;}
#define TYPEOF_opal_nop_ar2_bmul_s 0xA6779907ABFBCBF4ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_bmul_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_bmul_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_bmul_s_arity( const opal_nop_ar2_bmul_s* o ); \
  static inline bl_t opal_nop_ar2_bmul_s_reserved( const opal_nop_ar2_bmul_s* o ); \
  static inline sz_t opal_nop_ar2_bmul_s_priority( const opal_nop_ar2_bmul_s* o ); \
  static inline sc_t opal_nop_ar2_bmul_s_symbol( const opal_nop_ar2_bmul_s* o ); \
  bl_t opal_nop_ar2_bmul_s_solve( const opal_nop_ar2_bmul_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline sz_t opal_nop_ar2_bmul_s_arity( const opal_nop_ar2_bmul_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_bmul_s_reserved( const opal_nop_ar2_bmul_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_bmul_s_priority( const opal_nop_ar2_bmul_s* o ){ return  10;} \
  static inline sc_t opal_nop_ar2_bmul_s_symbol( const opal_nop_ar2_bmul_s* o ){ return  "**";}
#define TYPEOF_opal_nop_ar2_logic_equal_s 0xDB53FF1855A0762Dull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_equal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_equal_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_equal_s_arity( const opal_nop_ar2_logic_equal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_equal_s_reserved( const opal_nop_ar2_logic_equal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_equal_s_priority( const opal_nop_ar2_logic_equal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_equal_s_eci( const opal_nop_ar2_logic_equal_s* o ); \
  static inline sc_t opal_nop_ar2_logic_equal_s_symbol( const opal_nop_ar2_logic_equal_s* o ); \
  static inline tp_t opal_nop_ar2_logic_equal_s_type_vop_ap( const opal_nop_ar2_logic_equal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_equal_s_arity( const opal_nop_ar2_logic_equal_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_equal_s_reserved( const opal_nop_ar2_logic_equal_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_equal_s_priority( const opal_nop_ar2_logic_equal_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_equal_s_eci( const opal_nop_ar2_logic_equal_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_equal_s_symbol( const opal_nop_ar2_logic_equal_s* o ){ return  "==";} \
  static inline tp_t opal_nop_ar2_logic_equal_s_type_vop_ap( const opal_nop_ar2_logic_equal_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_equal_s;} \
  static inline sz_t opal_nop_ar2_logic_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_unequal_s 0x7293E2BD53EA6004ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_unequal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_unequal_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_unequal_s_arity( const opal_nop_ar2_logic_unequal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_unequal_s_reserved( const opal_nop_ar2_logic_unequal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_unequal_s_priority( const opal_nop_ar2_logic_unequal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_unequal_s_eci( const opal_nop_ar2_logic_unequal_s* o ); \
  static inline sc_t opal_nop_ar2_logic_unequal_s_symbol( const opal_nop_ar2_logic_unequal_s* o ); \
  static inline tp_t opal_nop_ar2_logic_unequal_s_type_vop_ap( const opal_nop_ar2_logic_unequal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_unequal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_unequal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_unequal_s_arity( const opal_nop_ar2_logic_unequal_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_unequal_s_reserved( const opal_nop_ar2_logic_unequal_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_unequal_s_priority( const opal_nop_ar2_logic_unequal_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_unequal_s_eci( const opal_nop_ar2_logic_unequal_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_unequal_s_symbol( const opal_nop_ar2_logic_unequal_s* o ){ return  "!=";} \
  static inline tp_t opal_nop_ar2_logic_unequal_s_type_vop_ap( const opal_nop_ar2_logic_unequal_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_unequal_s;} \
  static inline sz_t opal_nop_ar2_logic_unequal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_unequal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_larger_s 0x2A11ADCD8108BE78ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_larger_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_larger_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_larger_s_arity( const opal_nop_ar2_logic_larger_s* o ); \
  static inline bl_t opal_nop_ar2_logic_larger_s_reserved( const opal_nop_ar2_logic_larger_s* o ); \
  static inline sz_t opal_nop_ar2_logic_larger_s_priority( const opal_nop_ar2_logic_larger_s* o ); \
  static inline bl_t opal_nop_ar2_logic_larger_s_eci( const opal_nop_ar2_logic_larger_s* o ); \
  static inline sc_t opal_nop_ar2_logic_larger_s_symbol( const opal_nop_ar2_logic_larger_s* o ); \
  static inline tp_t opal_nop_ar2_logic_larger_s_type_vop_ap( const opal_nop_ar2_logic_larger_s* o ); \
  static inline sz_t opal_nop_ar2_logic_larger_s_mcode_push_dp_holor( const opal_nop_ar2_logic_larger_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_larger_s_arity( const opal_nop_ar2_logic_larger_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_larger_s_reserved( const opal_nop_ar2_logic_larger_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_larger_s_priority( const opal_nop_ar2_logic_larger_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_larger_s_eci( const opal_nop_ar2_logic_larger_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_larger_s_symbol( const opal_nop_ar2_logic_larger_s* o ){ return  ">";} \
  static inline tp_t opal_nop_ar2_logic_larger_s_type_vop_ap( const opal_nop_ar2_logic_larger_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_larger_s;} \
  static inline sz_t opal_nop_ar2_logic_larger_s_mcode_push_dp_holor( const opal_nop_ar2_logic_larger_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_smaller_s 0x2568290BE99FD579ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_smaller_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_smaller_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_smaller_s_arity( const opal_nop_ar2_logic_smaller_s* o ); \
  static inline bl_t opal_nop_ar2_logic_smaller_s_reserved( const opal_nop_ar2_logic_smaller_s* o ); \
  static inline sz_t opal_nop_ar2_logic_smaller_s_priority( const opal_nop_ar2_logic_smaller_s* o ); \
  static inline bl_t opal_nop_ar2_logic_smaller_s_eci( const opal_nop_ar2_logic_smaller_s* o ); \
  static inline sc_t opal_nop_ar2_logic_smaller_s_symbol( const opal_nop_ar2_logic_smaller_s* o ); \
  static inline tp_t opal_nop_ar2_logic_smaller_s_type_vop_ap( const opal_nop_ar2_logic_smaller_s* o ); \
  static inline sz_t opal_nop_ar2_logic_smaller_s_mcode_push_dp_holor( const opal_nop_ar2_logic_smaller_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_smaller_s_arity( const opal_nop_ar2_logic_smaller_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_smaller_s_reserved( const opal_nop_ar2_logic_smaller_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_smaller_s_priority( const opal_nop_ar2_logic_smaller_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_smaller_s_eci( const opal_nop_ar2_logic_smaller_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_smaller_s_symbol( const opal_nop_ar2_logic_smaller_s* o ){ return  "<";} \
  static inline tp_t opal_nop_ar2_logic_smaller_s_type_vop_ap( const opal_nop_ar2_logic_smaller_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_smaller_s;} \
  static inline sz_t opal_nop_ar2_logic_smaller_s_mcode_push_dp_holor( const opal_nop_ar2_logic_smaller_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_larger_equal_s 0xD94C7AC8CC86918Bull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_larger_equal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_larger_equal_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_arity( const opal_nop_ar2_logic_larger_equal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_larger_equal_s_reserved( const opal_nop_ar2_logic_larger_equal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_priority( const opal_nop_ar2_logic_larger_equal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_larger_equal_s_eci( const opal_nop_ar2_logic_larger_equal_s* o ); \
  static inline sc_t opal_nop_ar2_logic_larger_equal_s_symbol( const opal_nop_ar2_logic_larger_equal_s* o ); \
  static inline tp_t opal_nop_ar2_logic_larger_equal_s_type_vop_ap( const opal_nop_ar2_logic_larger_equal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_larger_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_arity( const opal_nop_ar2_logic_larger_equal_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_larger_equal_s_reserved( const opal_nop_ar2_logic_larger_equal_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_priority( const opal_nop_ar2_logic_larger_equal_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_larger_equal_s_eci( const opal_nop_ar2_logic_larger_equal_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_larger_equal_s_symbol( const opal_nop_ar2_logic_larger_equal_s* o ){ return  ">=";} \
  static inline tp_t opal_nop_ar2_logic_larger_equal_s_type_vop_ap( const opal_nop_ar2_logic_larger_equal_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_larger_equal_s;} \
  static inline sz_t opal_nop_ar2_logic_larger_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_larger_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_smaller_equal_s 0x02EC3516D727CA92ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_smaller_equal_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_smaller_equal_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_arity( const opal_nop_ar2_logic_smaller_equal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_smaller_equal_s_reserved( const opal_nop_ar2_logic_smaller_equal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_priority( const opal_nop_ar2_logic_smaller_equal_s* o ); \
  static inline bl_t opal_nop_ar2_logic_smaller_equal_s_eci( const opal_nop_ar2_logic_smaller_equal_s* o ); \
  static inline sc_t opal_nop_ar2_logic_smaller_equal_s_symbol( const opal_nop_ar2_logic_smaller_equal_s* o ); \
  static inline tp_t opal_nop_ar2_logic_smaller_equal_s_type_vop_ap( const opal_nop_ar2_logic_smaller_equal_s* o ); \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_smaller_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_arity( const opal_nop_ar2_logic_smaller_equal_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_smaller_equal_s_reserved( const opal_nop_ar2_logic_smaller_equal_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_priority( const opal_nop_ar2_logic_smaller_equal_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_smaller_equal_s_eci( const opal_nop_ar2_logic_smaller_equal_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_smaller_equal_s_symbol( const opal_nop_ar2_logic_smaller_equal_s* o ){ return  "<=";} \
  static inline tp_t opal_nop_ar2_logic_smaller_equal_s_type_vop_ap( const opal_nop_ar2_logic_smaller_equal_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_smaller_equal_s;} \
  static inline sz_t opal_nop_ar2_logic_smaller_equal_s_mcode_push_dp_holor( const opal_nop_ar2_logic_smaller_equal_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_and_s 0xBEF1692B1434DC94ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_and_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_and_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_and_s_arity( const opal_nop_ar2_logic_and_s* o ); \
  static inline bl_t opal_nop_ar2_logic_and_s_reserved( const opal_nop_ar2_logic_and_s* o ); \
  static inline sz_t opal_nop_ar2_logic_and_s_priority( const opal_nop_ar2_logic_and_s* o ); \
  static inline bl_t opal_nop_ar2_logic_and_s_eci( const opal_nop_ar2_logic_and_s* o ); \
  static inline sc_t opal_nop_ar2_logic_and_s_symbol( const opal_nop_ar2_logic_and_s* o ); \
  static inline tp_t opal_nop_ar2_logic_and_s_type_vop_ap( const opal_nop_ar2_logic_and_s* o ); \
  static inline sz_t opal_nop_ar2_logic_and_s_mcode_push_dp_holor( const opal_nop_ar2_logic_and_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_and_s_arity( const opal_nop_ar2_logic_and_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_and_s_reserved( const opal_nop_ar2_logic_and_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_and_s_priority( const opal_nop_ar2_logic_and_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_and_s_eci( const opal_nop_ar2_logic_and_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_and_s_symbol( const opal_nop_ar2_logic_and_s* o ){ return  "&&";} \
  static inline tp_t opal_nop_ar2_logic_and_s_type_vop_ap( const opal_nop_ar2_logic_and_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_and_s;} \
  static inline sz_t opal_nop_ar2_logic_and_s_mcode_push_dp_holor( const opal_nop_ar2_logic_and_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_logic_or_s 0x8F57AECDC5F91C32ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_logic_or_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_logic_or_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_logic_or_s_arity( const opal_nop_ar2_logic_or_s* o ); \
  static inline bl_t opal_nop_ar2_logic_or_s_reserved( const opal_nop_ar2_logic_or_s* o ); \
  static inline sz_t opal_nop_ar2_logic_or_s_priority( const opal_nop_ar2_logic_or_s* o ); \
  static inline bl_t opal_nop_ar2_logic_or_s_eci( const opal_nop_ar2_logic_or_s* o ); \
  static inline sc_t opal_nop_ar2_logic_or_s_symbol( const opal_nop_ar2_logic_or_s* o ); \
  static inline tp_t opal_nop_ar2_logic_or_s_type_vop_ap( const opal_nop_ar2_logic_or_s* o ); \
  static inline sz_t opal_nop_ar2_logic_or_s_mcode_push_dp_holor( const opal_nop_ar2_logic_or_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_logic_or_s_arity( const opal_nop_ar2_logic_or_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_logic_or_s_reserved( const opal_nop_ar2_logic_or_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_logic_or_s_priority( const opal_nop_ar2_logic_or_s* o ){ return  6;} \
  static inline bl_t opal_nop_ar2_logic_or_s_eci( const opal_nop_ar2_logic_or_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_logic_or_s_symbol( const opal_nop_ar2_logic_or_s* o ){ return  "||";} \
  static inline tp_t opal_nop_ar2_logic_or_s_type_vop_ap( const opal_nop_ar2_logic_or_s* o ){ return  TYPEOF_bhvm_vop_ar2_logic_or_s;} \
  static inline sz_t opal_nop_ar2_logic_or_s_mcode_push_dp_holor( const opal_nop_ar2_logic_or_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ return  -1;}
#define TYPEOF_opal_nop_ar2_cat_s 0x05FBE8BEB89AE344ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_cat_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_cat_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_cat_s_arity( const opal_nop_ar2_cat_s* o ); \
  static inline bl_t opal_nop_ar2_cat_s_reserved( const opal_nop_ar2_cat_s* o ); \
  static inline sz_t opal_nop_ar2_cat_s_priority( const opal_nop_ar2_cat_s* o ); \
  static inline sc_t opal_nop_ar2_cat_s_symbol( const opal_nop_ar2_cat_s* o ); \
  bl_t opal_nop_ar2_cat_s_solve( const opal_nop_ar2_cat_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_ap( const opal_nop_ar2_cat_s* o ); \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_dp_a( const opal_nop_ar2_cat_s* o ); \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_dp_b( const opal_nop_ar2_cat_s* o ); \
  static inline sz_t opal_nop_ar2_cat_s_arity( const opal_nop_ar2_cat_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_cat_s_reserved( const opal_nop_ar2_cat_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_cat_s_priority( const opal_nop_ar2_cat_s* o ){ return  6;} \
  static inline sc_t opal_nop_ar2_cat_s_symbol( const opal_nop_ar2_cat_s* o ){ return  ":";} \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_ap( const opal_nop_ar2_cat_s* o ){ return  TYPEOF_bhvm_vop_ar2_cat_s;} \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_dp_a( const opal_nop_ar2_cat_s* o ){ return  TYPEOF_bhvm_vop_ar1_cat_dp_a_s;} \
  static inline tp_t opal_nop_ar2_cat_s_type_vop_dp_b( const opal_nop_ar2_cat_s* o ){ return  TYPEOF_bhvm_vop_ar1_cat_dp_b_s;}
#define TYPEOF_opal_nop_ar2_ccat_s 0x3B5825640C9A9FDBull
#define BETH_EXPAND_ITEM_opal_nop_ar2_ccat_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_ccat_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_ccat_s_arity( const opal_nop_ar2_ccat_s* o ); \
  static inline bl_t opal_nop_ar2_ccat_s_reserved( const opal_nop_ar2_ccat_s* o ); \
  static inline sz_t opal_nop_ar2_ccat_s_priority( const opal_nop_ar2_ccat_s* o ); \
  static inline sc_t opal_nop_ar2_ccat_s_symbol( const opal_nop_ar2_ccat_s* o ); \
  bl_t opal_nop_ar2_ccat_s_solve( const opal_nop_ar2_ccat_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_ap( const opal_nop_ar2_ccat_s* o ); \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_dp_a( const opal_nop_ar2_ccat_s* o ); \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_dp_b( const opal_nop_ar2_ccat_s* o ); \
  static inline sz_t opal_nop_ar2_ccat_s_arity( const opal_nop_ar2_ccat_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_ccat_s_reserved( const opal_nop_ar2_ccat_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_ccat_s_priority( const opal_nop_ar2_ccat_s* o ){ return  8;} \
  static inline sc_t opal_nop_ar2_ccat_s_symbol( const opal_nop_ar2_ccat_s* o ){ return  "::";} \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_ap( const opal_nop_ar2_ccat_s* o ){ return  TYPEOF_bhvm_vop_ar2_ccat_s;} \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_dp_a( const opal_nop_ar2_ccat_s* o ){ return  TYPEOF_bhvm_vop_ar1_ccat_dp_a_s;} \
  static inline tp_t opal_nop_ar2_ccat_s_type_vop_dp_b( const opal_nop_ar2_ccat_s* o ){ return  TYPEOF_bhvm_vop_ar1_ccat_dp_b_s;}
#define TYPEOF_opal_nop_ar2_order_inc_s 0x8209412FD9D70323ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_order_inc_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_order_inc_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_order_inc_s_arity( const opal_nop_ar2_order_inc_s* o ); \
  static inline bl_t opal_nop_ar2_order_inc_s_reserved( const opal_nop_ar2_order_inc_s* o ); \
  static inline sz_t opal_nop_ar2_order_inc_s_priority( const opal_nop_ar2_order_inc_s* o ); \
  static inline sc_t opal_nop_ar2_order_inc_s_symbol( const opal_nop_ar2_order_inc_s* o ); \
  bl_t opal_nop_ar2_order_inc_s_solve( const opal_nop_ar2_order_inc_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_order_inc_s_mcode_push_ap_track( const opal_nop_ar2_order_inc_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline tp_t opal_nop_ar2_order_inc_s_type_vop_dp_a( const opal_nop_ar2_order_inc_s* o ); \
  static inline tp_t opal_nop_ar2_order_inc_s_type_vop_dp_b( const opal_nop_ar2_order_inc_s* o ); \
  static inline sz_t opal_nop_ar2_order_inc_s_arity( const opal_nop_ar2_order_inc_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_order_inc_s_reserved( const opal_nop_ar2_order_inc_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_order_inc_s_priority( const opal_nop_ar2_order_inc_s* o ){ return  21;} \
  static inline sc_t opal_nop_ar2_order_inc_s_symbol( const opal_nop_ar2_order_inc_s* o ){ return  "[";} \
  static inline tp_t opal_nop_ar2_order_inc_s_type_vop_dp_a( const opal_nop_ar2_order_inc_s* o ){ return  0;} \
  static inline tp_t opal_nop_ar2_order_inc_s_type_vop_dp_b( const opal_nop_ar2_order_inc_s* o ){ return  TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_opal_nop_ar2_order_dec_s 0x25BE43FCA36F0793ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_order_dec_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_order_dec_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_order_dec_s_arity( const opal_nop_ar2_order_dec_s* o ); \
  static inline bl_t opal_nop_ar2_order_dec_s_reserved( const opal_nop_ar2_order_dec_s* o ); \
  static inline sz_t opal_nop_ar2_order_dec_s_priority( const opal_nop_ar2_order_dec_s* o ); \
  static inline sc_t opal_nop_ar2_order_dec_s_symbol( const opal_nop_ar2_order_dec_s* o ); \
  bl_t opal_nop_ar2_order_dec_s_solve( const opal_nop_ar2_order_dec_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  sz_t opal_nop_ar2_order_dec_s_mcode_push_ap_holor( const opal_nop_ar2_order_dec_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t opal_nop_ar2_order_dec_s_mcode_push_dp_holor( const opal_nop_ar2_order_dec_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_order_dec_s_arity( const opal_nop_ar2_order_dec_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_order_dec_s_reserved( const opal_nop_ar2_order_dec_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_order_dec_s_priority( const opal_nop_ar2_order_dec_s* o ){ return  20;} \
  static inline sc_t opal_nop_ar2_order_dec_s_symbol( const opal_nop_ar2_order_dec_s* o ){ return  "]";}
#define TYPEOF_opal_nop_ar2_cyclic_s 0x540C907D1F408E0Full
#define BETH_EXPAND_ITEM_opal_nop_ar2_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_cyclic_s ) \
  { \
      aware_t _; \
      tp_t name; \
  }; \
  static inline sz_t opal_nop_ar2_cyclic_s_arity( const opal_nop_ar2_cyclic_s* o ); \
  static inline bl_t opal_nop_ar2_cyclic_s_reserved( const opal_nop_ar2_cyclic_s* o ); \
  static inline sz_t opal_nop_ar2_cyclic_s_priority( const opal_nop_ar2_cyclic_s* o ); \
  static inline bl_t opal_nop_ar2_cyclic_s_is_cyclic( const opal_nop_ar2_cyclic_s* o ); \
  bl_t opal_nop_ar2_cyclic_s_solve( const opal_nop_ar2_cyclic_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_cyclic_s_solve_node( opal_nop_ar2_cyclic_s* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ); \
  static inline void opal_nop_ar2_cyclic_s_mcode_push_ap_track( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void opal_nop_ar2_cyclic_s_mcode_push_dp_track( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_cyclic_s_mcode_push_dp_holor( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t opal_nop_ar2_cyclic_s_arity( const opal_nop_ar2_cyclic_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_cyclic_s_reserved( const opal_nop_ar2_cyclic_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar2_cyclic_s_priority( const opal_nop_ar2_cyclic_s* o ){ return  8;} \
  static inline bl_t opal_nop_ar2_cyclic_s_is_cyclic( const opal_nop_ar2_cyclic_s* o ){ return  true;} \
  static inline void opal_nop_ar2_cyclic_s_mcode_push_ap_track( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ ERR_fa( "Not implemented." );} \
  static inline void opal_nop_ar2_cyclic_s_mcode_push_dp_track( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ ERR_fa( "Not implemented." );} \
  static inline sz_t opal_nop_ar2_cyclic_s_mcode_push_dp_holor( const opal_nop_ar2_cyclic_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ ERR_fa( "Not implemented." ); return  -1;}
#define TYPEOF_opal_nop_ar2_rands_s 0x730B8F6E7A942D24ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_rands_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_rands_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_rands_s_arity( const opal_nop_ar2_rands_s* o ); \
  static inline bl_t opal_nop_ar2_rands_s_reserved( const opal_nop_ar2_rands_s* o ); \
  static inline sc_t opal_nop_ar2_rands_s_symbol( const opal_nop_ar2_rands_s* o ); \
  static inline sz_t opal_nop_ar2_rands_s_priority( const opal_nop_ar2_rands_s* o ); \
  bl_t opal_nop_ar2_rands_s_solve( const opal_nop_ar2_rands_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_rands_s_settle( const opal_nop_ar2_rands_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result ); \
  static inline sz_t opal_nop_ar2_rands_s_arity( const opal_nop_ar2_rands_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_rands_s_reserved( const opal_nop_ar2_rands_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_rands_s_symbol( const opal_nop_ar2_rands_s* o ){ return  "rands";} \
  static inline sz_t opal_nop_ar2_rands_s_priority( const opal_nop_ar2_rands_s* o ){ return  8;}
#define TYPEOF_opal_nop_ar2_reshape_s 0x4A0AA8C27D0792E6ull
#define BETH_EXPAND_ITEM_opal_nop_ar2_reshape_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar2_reshape_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar2_reshape_s_arity( const opal_nop_ar2_reshape_s* o ); \
  static inline bl_t opal_nop_ar2_reshape_s_reserved( const opal_nop_ar2_reshape_s* o ); \
  static inline sc_t opal_nop_ar2_reshape_s_symbol( const opal_nop_ar2_reshape_s* o ); \
  static inline sz_t opal_nop_ar2_reshape_s_priority( const opal_nop_ar2_reshape_s* o ); \
  bl_t opal_nop_ar2_reshape_s_solve( const opal_nop_ar2_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_reshape_s_solve_node( opal_nop_ar2_reshape_s* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ); \
  static inline sz_t opal_nop_ar2_reshape_s_arity( const opal_nop_ar2_reshape_s* o ){ return  2;} \
  static inline bl_t opal_nop_ar2_reshape_s_reserved( const opal_nop_ar2_reshape_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar2_reshape_s_symbol( const opal_nop_ar2_reshape_s* o ){ return  "reshape";} \
  static inline sz_t opal_nop_ar2_reshape_s_priority( const opal_nop_ar2_reshape_s* o ){ return  8;}
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
  XOILA_DECLARE_SPECT( opal_nop_ar2 ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop_ar2 ) \
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

#define TYPEOF_opal_nop_ar3 0xE97C6958169E7E5Aull
#define TYPEOF_opal_nop_ar3_spect_s 0xBE7DF2406DA0C906ull
#define TYPEOF_opal_nop_ar3_iff_s 0x4CA37E772D4CCAC0ull
#define BETH_EXPAND_ITEM_opal_nop_ar3_iff_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar3_iff_s ) \
  { \
      aware_t _; \
  }; \
  static inline sz_t opal_nop_ar3_iff_s_arity( const opal_nop_ar3_iff_s* o ); \
  static inline bl_t opal_nop_ar3_iff_s_reserved( const opal_nop_ar3_iff_s* o ); \
  static inline sz_t opal_nop_ar3_iff_s_priority( const opal_nop_ar3_iff_s* o ); \
  static inline bl_t opal_nop_ar3_iff_s_eci( const opal_nop_ar3_iff_s* o ); \
  static inline sc_t opal_nop_ar3_iff_s_symbol( const opal_nop_ar3_iff_s* o ); \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_ap( const opal_nop_ar3_iff_s* o ); \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_a( const opal_nop_ar3_iff_s* o ); \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_b( const opal_nop_ar3_iff_s* o ); \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_c( const opal_nop_ar3_iff_s* o ); \
  static inline sz_t opal_nop_ar3_iff_s_arity( const opal_nop_ar3_iff_s* o ){ return  3;} \
  static inline bl_t opal_nop_ar3_iff_s_reserved( const opal_nop_ar3_iff_s* o ){ return  true;} \
  static inline sz_t opal_nop_ar3_iff_s_priority( const opal_nop_ar3_iff_s* o ){ return  4;} \
  static inline bl_t opal_nop_ar3_iff_s_eci( const opal_nop_ar3_iff_s* o ){ return  true;} \
  static inline sc_t opal_nop_ar3_iff_s_symbol( const opal_nop_ar3_iff_s* o ){ return  "iff";} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_ap( const opal_nop_ar3_iff_s* o ){ return  TYPEOF_bhvm_vop_ar3_iff_s;} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_a( const opal_nop_ar3_iff_s* o ){ return  0;} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_b( const opal_nop_ar3_iff_s* o ){ return  TYPEOF_bhvm_vop_ar2_iff_dp_b_s;} \
  static inline tp_t opal_nop_ar3_iff_s_type_vop_dp_c( const opal_nop_ar3_iff_s* o ){ return  TYPEOF_bhvm_vop_ar2_iff_dp_c_s;}
#define BETH_EXPAND_GROUP_opal_nop_ar3 \
  BCORE_FORWARD_OBJECT( opal_nop_ar3 ); \
  BCORE_FORWARD_OBJECT( opal_nop_ar3_iff_s ); \
  XOILA_DECLARE_SPECT( opal_nop_ar3 ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop_ar3 ) \
  BETH_EXPAND_ITEM_opal_nop_ar3_iff_s

/**********************************************************************************************************************/
// source: opal_eval_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_eval_nop

#define TYPEOF_opal_eval_nop 0x4A5BE4CC16DB8CE8ull
#define TYPEOF_opal_eval_nop_spect_s 0x000176D624C2FA30ull
#define TYPEOF_opal_eval_nop_result_s 0x08E93DE88DAA6BE6ull
#define BETH_EXPAND_ITEM_opal_eval_nop_result_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_result_s ) \
  { \
      aware_t _; \
      sz_t total_tests; \
      sz_t solvable_tests; \
      sz_t tolerated_errors; \
      bl_t error; \
      st_s msg; \
  }; \
  void opal_eval_nop_result_s_resolve( const opal_eval_nop_result_s* o );
#define TYPEOF_opal_eval_nop_param_s 0x32B6053F9508C09Cull
#define BETH_EXPAND_ITEM_opal_eval_nop_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_param_s ) \
  { \
      aware_t _; \
      opal_nop* nop; \
      opal_holor_s* ha; \
      opal_holor_s* hb; \
      opal_holor_s* hc; \
      opal_holor_s* hr; \
      bcore_sink* log; \
      sz_t verbosity; \
      bcore_prsg* prsg; \
  }; \
  static inline void opal_eval_nop_param_s_init_x( opal_eval_nop_param_s* o ); \
  void opal_eval_nop_param_s_set( opal_eval_nop_param_s* o, const opal_eval_nop_param_s* src ); \
  static inline void opal_eval_nop_param_s_init_x( opal_eval_nop_param_s* o ){ o->log = bcore_fork( BCORE_STDOUT );}
#define TYPEOF_opal_eval_nop_generator_s 0x6106F6806ECFE34Cull
#define BETH_EXPAND_ITEM_opal_eval_nop_generator_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_generator_s ) \
  { \
      aware_t _; \
      opal_eval_nop_param_s param; \
      bl_t set_htp; \
      bl_t set_value; \
      bl_t set_shape; \
      bl_t set_dim; \
      bl_t set_v_type; \
      sz_t max_shape_size; \
      sz_t max_dim; \
      f3_t v_min; \
      f3_t v_max; \
      sz_t cycles; \
      bcore_arr_uz_s tolerated_cycles; \
      opal_eval_nop* eval; \
  }; \
  opal_eval_nop_result_s* opal_eval_nop_generator_s_run( const opal_eval_nop_generator_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_generator_s_set_param( opal_eval_nop_generator_s* o, const opal_eval_nop_param_s* param ); \
  er_t opal_eval_nop_generator_s_main( opal_eval_nop_generator_s* o, bcore_main_frame_s* frame ); \
  static inline void opal_eval_nop_generator_s_set_param( opal_eval_nop_generator_s* o, const opal_eval_nop_param_s* param ){ opal_eval_nop_param_s_set(&(o->param),param );}
#define TYPEOF_opal_eval_nop_show_param_s 0x9EFE40A781EDAFB8ull
#define BETH_EXPAND_ITEM_opal_eval_nop_show_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_show_param_s ) \
  { \
      aware_t _; \
      opal_eval_nop_param_s param; \
  }; \
  static inline void opal_eval_nop_show_param_s_set_param( opal_eval_nop_show_param_s* o, const opal_eval_nop_param_s* param ); \
  er_t opal_eval_nop_show_param_s_main( opal_eval_nop_show_param_s* o, bcore_main_frame_s* frame ); \
  static inline opal_eval_nop_result_s* opal_eval_nop_show_param_s_run( const opal_eval_nop_show_param_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_show_param_s_set_param( opal_eval_nop_show_param_s* o, const opal_eval_nop_param_s* param ){ opal_eval_nop_param_s_set(&(o->param),param );} \
  static inline opal_eval_nop_result_s* opal_eval_nop_show_param_s_run( const opal_eval_nop_show_param_s* o, opal_eval_nop_result_s* result ){ bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return  result;}
#define TYPEOF_opal_eval_nop_arr_s 0xC0F16F22EB64D772ull
#define BETH_EXPAND_ITEM_opal_eval_nop_arr_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_arr_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_eval_nop, ); \
  }; \
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
#define TYPEOF_opal_eval_nop_set_s 0xC584D398EAD92ED5ull
#define BETH_EXPAND_ITEM_opal_eval_nop_set_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_set_s ) \
  { \
      aware_t _; \
      opal_eval_nop_param_s param; \
      opal_eval_nop_arr_s arr; \
  }; \
  static inline void opal_eval_nop_set_s_set_param( opal_eval_nop_set_s* o, const opal_eval_nop_param_s* param ); \
  er_t opal_eval_nop_set_s_main( opal_eval_nop_set_s* o, bcore_main_frame_s* frame ); \
  opal_eval_nop_result_s* opal_eval_nop_set_s_run( const opal_eval_nop_set_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_set_s_set_param( opal_eval_nop_set_s* o, const opal_eval_nop_param_s* param ){ opal_eval_nop_param_s_set(&(o->param),param );}
#define TYPEOF_opal_eval_nop_ar1_s 0x057C32243444E70Bull
#define BETH_EXPAND_ITEM_opal_eval_nop_ar1_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_ar1_s ) \
  { \
      aware_t _; \
      opal_eval_nop_param_s param; \
      opal_context* context; \
  }; \
  opal_eval_nop_result_s* opal_eval_nop_ar1_s_run( const opal_eval_nop_ar1_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_ar1_s_set_param( opal_eval_nop_ar1_s* o, const opal_eval_nop_param_s* param ); \
  er_t opal_eval_nop_ar1_s_main( opal_eval_nop_ar1_s* o, bcore_main_frame_s* frame ); \
  static inline void opal_eval_nop_ar1_s_set_param( opal_eval_nop_ar1_s* o, const opal_eval_nop_param_s* param ){ opal_eval_nop_param_s_set(&(o->param),param );}
#define TYPEOF_opal_eval_nop_ar2_s 0xE99CAF2423F21432ull
#define BETH_EXPAND_ITEM_opal_eval_nop_ar2_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_ar2_s ) \
  { \
      aware_t _; \
      opal_eval_nop_param_s param; \
      opal_context* context; \
  }; \
  opal_eval_nop_result_s* opal_eval_nop_ar2_s_run( const opal_eval_nop_ar2_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_ar2_s_set_param( opal_eval_nop_ar2_s* o, const opal_eval_nop_param_s* param ); \
  er_t opal_eval_nop_ar2_s_main( opal_eval_nop_ar2_s* o, bcore_main_frame_s* frame ); \
  static inline void opal_eval_nop_ar2_s_set_param( opal_eval_nop_ar2_s* o, const opal_eval_nop_param_s* param ){ opal_eval_nop_param_s_set(&(o->param),param );}
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
  XOILA_DECLARE_SPECT( opal_eval_nop ) \
  { \
      bcore_spect_header_s header; \
      opal_eval_nop_set_param set_param; \
      opal_eval_nop_run run; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_eval_nop ) \
  BETH_EXPAND_ITEM_opal_eval_nop_result_s \
  BETH_EXPAND_ITEM_opal_eval_nop_param_s \
  static inline void opal_eval_nop_a_set_param( opal_eval_nop* o, const opal_eval_nop_param_s* param ){ const opal_eval_nop_spect_s* p = opal_eval_nop_spect_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param );} \
  static inline bl_t opal_eval_nop_a_defines_set_param( const opal_eval_nop* o ){ return  opal_eval_nop_spect_s_get_aware( o )->set_param != NULL;} \
  static inline opal_eval_nop_result_s* opal_eval_nop_a_run( const opal_eval_nop* o, opal_eval_nop_result_s* result ){ const opal_eval_nop_spect_s* p = opal_eval_nop_spect_s_get_aware( o ); assert( p->run ); return p->run( o, result );} \
  static inline bl_t opal_eval_nop_a_defines_run( const opal_eval_nop* o ){ return  opal_eval_nop_spect_s_get_aware( o )->run != NULL;} \
  BETH_EXPAND_ITEM_opal_eval_nop_generator_s \
  BETH_EXPAND_ITEM_opal_eval_nop_show_param_s \
  BETH_EXPAND_ITEM_opal_eval_nop_arr_s \
  BETH_EXPAND_ITEM_opal_eval_nop_set_s \
  BETH_EXPAND_ITEM_opal_eval_nop_ar1_s \
  BETH_EXPAND_ITEM_opal_eval_nop_ar2_s

/**********************************************************************************************************************/
// source: opal_sem.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem

#define TYPEOF_opal_sem 0x119AE3C204812B93ull
#define TYPEOF_opal_sem_spect_s 0x62BD65BF920870F3ull
#define TYPEOF_cell 0xD98B1E90FD653435ull
#define TYPEOF_opal_sem_link_s 0xFF23A8EDAE00D066ull
#define BETH_EXPAND_ITEM_opal_sem_link_s \
  BCORE_DECLARE_OBJECT( opal_sem_link_s ) \
  { \
      aware_t _; \
      tp_t name; \
      bl_t protected; \
      bl_t visible; \
      opal_sem_link_s* up; \
      opal_sem_link_s* dn; \
      vd_t cell; \
      bl_t exit; \
  }; \
  static inline tp_t opal_sem_link_s_get_name( const opal_sem_link_s* o ); \
  static inline void opal_sem_link_s_set_name_visible( opal_sem_link_s* o, tp_t name ); \
  static inline void opal_sem_link_s_set_name_invisible( opal_sem_link_s* o, tp_t name ); \
  static inline bl_t opal_sem_link_s_is_visible( const opal_sem_link_s* o ); \
  static inline tp_t opal_sem_link_s_get_name( const opal_sem_link_s* o ){ return  o->name;} \
  static inline void opal_sem_link_s_set_name_visible( opal_sem_link_s* o, tp_t name ){ o->name = name; o->visible = true;} \
  static inline void opal_sem_link_s_set_name_invisible( opal_sem_link_s* o, tp_t name ){ o->name = name; o->visible = false;} \
  static inline bl_t opal_sem_link_s_is_visible( const opal_sem_link_s* o ){ return  o->visible;}
#define TYPEOF_opal_sem_links_s 0x7F8BACDF36F759C7ull
#define BETH_EXPAND_ITEM_opal_sem_links_s \
  BCORE_DECLARE_OBJECT( opal_sem_links_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_sem_link_s, ); \
  }; \
  opal_sem_link_s* opal_sem_links_s_get_link_by_name( opal_sem_links_s* o, tp_t name ); \
  bl_t opal_sem_links_s_name_exists( const opal_sem_links_s* o, tp_t name ); \
  opal_sem_link_s* opal_sem_links_s_get_link_by_up( opal_sem_links_s* o, opal_sem_link_s* up ); \
  opal_sem_link_s* opal_sem_links_s_get_link_by_dn( opal_sem_links_s* o, opal_sem_link_s* dn ); \
  sz_t opal_sem_links_s_get_index_by_link( opal_sem_links_s* o, opal_sem_link_s* link ); \
  sz_t opal_sem_links_s_count_open( const opal_sem_links_s* o ); \
  static inline opal_sem_links_s* opal_sem_links_s_set_space( opal_sem_links_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_sem_links_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_sem_links_s* opal_sem_links_s_set_size( opal_sem_links_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_sem_links_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_sem_links_s* opal_sem_links_s_clear( opal_sem_links_s* o ) { bcore_array_t_set_space( TYPEOF_opal_sem_links_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_sem_link_s* opal_sem_links_s_push_c( opal_sem_links_s* o, const opal_sem_link_s* v ) { bcore_array_t_push( TYPEOF_opal_sem_links_s, ( bcore_array* )o, sr_twc( TYPEOF_opal_sem_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_sem_link_s* opal_sem_links_s_push_d( opal_sem_links_s* o,       opal_sem_link_s* v ) { bcore_array_t_push( TYPEOF_opal_sem_links_s, ( bcore_array* )o, sr_tsd( TYPEOF_opal_sem_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_sem_link_s* opal_sem_links_s_push( opal_sem_links_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_opal_sem_links_s, ( bcore_array* )o, sr_t_create( TYPEOF_opal_sem_link_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_sem_body_s 0x3B804C70042BB2FAull
#define BETH_EXPAND_ITEM_opal_sem_body_s \
  BCORE_DECLARE_OBJECT( opal_sem_body_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_sem, ); \
  }; \
  bl_t opal_sem_body_s_name_exists( const opal_sem_body_s* o, tp_t name ); \
  opal_sem* opal_sem_body_s_get_sem_by_name( opal_sem_body_s* o, tp_t name ); \
  static inline opal_sem_body_s* opal_sem_body_s_set_space( opal_sem_body_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_sem_body_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_sem_body_s* opal_sem_body_s_set_size( opal_sem_body_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_sem_body_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_sem_body_s* opal_sem_body_s_clear( opal_sem_body_s* o ) { bcore_array_t_set_space( TYPEOF_opal_sem_body_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_sem* opal_sem_body_s_push_c( opal_sem_body_s* o, const opal_sem* v ) { bcore_array_t_push( TYPEOF_opal_sem_body_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_sem* opal_sem_body_s_push_d( opal_sem_body_s* o,       opal_sem* v ) { bcore_array_t_push( TYPEOF_opal_sem_body_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_sem* opal_sem_body_s_push_t( opal_sem_body_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_opal_sem, t ); \
      bcore_array_t_push( TYPEOF_opal_sem_body_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_sem_cell_s 0xC780A2C0EE839242ull
#define BETH_EXPAND_ITEM_opal_sem_cell_s \
  BCORE_DECLARE_OBJECT( opal_sem_cell_s ) \
  { \
      aware_t _; \
      tp_t name; \
      bl_t visible; \
      opal_sem_links_s encs; \
      opal_sem_links_s excs; \
      opal_sem_body_s* body; \
      opal_sem_cell_s* parent; \
      opal_sem_context_s* context; \
      sz_t priority; \
      opal_nop* nop; \
      bcore_source_point_s source_point; \
      opal_sem_cell_s* wrapped_cell; \
  }; \
  static inline tp_t opal_sem_cell_s_get_name( const opal_sem_cell_s* o ); \
  static inline void opal_sem_cell_s_set_name_visible( opal_sem_cell_s* o, tp_t name ); \
  static inline void opal_sem_cell_s_set_name_invisible( opal_sem_cell_s* o, tp_t name ); \
  static inline bl_t opal_sem_cell_s_is_visible( const opal_sem_cell_s* o ); \
  static inline sz_t opal_sem_cell_s_get_arity( const opal_sem_cell_s* o ); \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_name( opal_sem_cell_s* o, tp_t name ); \
  static inline opal_sem_link_s* opal_sem_cell_s_get_exc_by_name( opal_sem_cell_s* o, tp_t name ); \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_open( opal_sem_cell_s* o ); \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_dn( opal_sem_cell_s* o, opal_sem_link_s* dn ); \
  static inline sz_t opal_sem_cell_s_get_priority( const opal_sem_cell_s* o ); \
  static inline bl_t opal_sem_cell_s_is_wrapper( const opal_sem_cell_s* o ); \
  opal_sem_cell_s* opal_sem_cell_s_get_cell_by_name( opal_sem_cell_s* o, tp_t name ); \
  opal_sem_link_s* opal_sem_cell_s_get_link_by_name( opal_sem_cell_s* o, tp_t name ); \
  static inline tp_t opal_sem_cell_s_get_name( const opal_sem_cell_s* o ){ return  o->name;} \
  static inline void opal_sem_cell_s_set_name_visible( opal_sem_cell_s* o, tp_t name ){ o->name = name; o->visible = true;} \
  static inline void opal_sem_cell_s_set_name_invisible( opal_sem_cell_s* o, tp_t name ){ o->name = name; o->visible = false;} \
  static inline bl_t opal_sem_cell_s_is_visible( const opal_sem_cell_s* o ){ return  o->visible;} \
  static inline sz_t opal_sem_cell_s_get_arity( const opal_sem_cell_s* o ){ return  opal_sem_links_s_count_open(&(o->encs));} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_name( opal_sem_cell_s* o, tp_t name ){ return  opal_sem_links_s_get_link_by_name(&(o->encs),name );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_exc_by_name( opal_sem_cell_s* o, tp_t name ){ return  opal_sem_links_s_get_link_by_name(&(o->excs),name );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_open( opal_sem_cell_s* o ){ return  opal_sem_links_s_get_link_by_up(&(o->encs),NULL );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_dn( opal_sem_cell_s* o, opal_sem_link_s* dn ){ return  opal_sem_links_s_get_link_by_dn(&(o->encs),dn   );} \
  static inline sz_t opal_sem_cell_s_get_priority( const opal_sem_cell_s* o ){ return  o->priority;} \
  static inline bl_t opal_sem_cell_s_is_wrapper( const opal_sem_cell_s* o ){ return  o->wrapped_cell != NULL && o->nop == NULL && o->body == NULL;}
#define TYPEOF_opal_sem_stack_flag_s 0x80C5E705470926D5ull
#define BETH_EXPAND_ITEM_opal_sem_stack_flag_s \
  BCORE_DECLARE_OBJECT( opal_sem_stack_flag_s ) \
  { \
      aware_t _; \
  };
#define BETH_EXPAND_GROUP_opal_sem \
  BCORE_FORWARD_OBJECT( opal_sem ); \
  BCORE_FORWARD_OBJECT( opal_sem_context ); \
  BCORE_FORWARD_OBJECT( opal_sem_id ); \
  BCORE_FORWARD_OBJECT( opal_sem_link_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_links_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_body_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_cell_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_stack_flag_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_builder ); \
  BCORE_FORWARD_OBJECT( opal_sem_tree ); \
  typedef tp_t (*opal_sem_get_name)( const opal_sem* o ); \
  typedef bl_t (*opal_sem_is_visible)( const opal_sem* o ); \
  typedef void (*opal_sem_set_name_visible)( opal_sem* o, tp_t name ); \
  typedef void (*opal_sem_set_name_invisible)( opal_sem* o, tp_t name ); \
  XOILA_DECLARE_SPECT( opal_sem ) \
  { \
      bcore_spect_header_s header; \
      opal_sem_get_name get_name; \
      opal_sem_is_visible is_visible; \
      opal_sem_set_name_visible set_name_visible; \
      opal_sem_set_name_invisible set_name_invisible; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_sem ) \
  BETH_EXPAND_GROUP_opal_sem_context \
  BETH_EXPAND_GROUP_opal_sem_id \
  static inline tp_t opal_sem_a_get_name( const opal_sem* o ){ const opal_sem_spect_s* p = opal_sem_spect_s_get_aware( o ); assert( p->get_name ); return p->get_name( o );} \
  static inline bl_t opal_sem_a_defines_get_name( const opal_sem* o ){ return  true;} \
  static inline tp_t opal_sem_get_name_default( const opal_sem* o ){ return  0;} \
  static inline bl_t opal_sem_a_is_visible( const opal_sem* o ){ const opal_sem_spect_s* p = opal_sem_spect_s_get_aware( o ); assert( p->is_visible ); return p->is_visible( o );} \
  static inline bl_t opal_sem_a_defines_is_visible( const opal_sem* o ){ return  true;} \
  static inline bl_t opal_sem_is_visible_default( const opal_sem* o ){ return  true;} \
  static inline void opal_sem_a_set_name_visible( opal_sem* o, tp_t name ){ const opal_sem_spect_s* p = opal_sem_spect_s_get_aware( o ); assert( p->set_name_visible ); p->set_name_visible( o, name );} \
  static inline bl_t opal_sem_a_defines_set_name_visible( const opal_sem* o ){ return  opal_sem_spect_s_get_aware( o )->set_name_visible != NULL;} \
  static inline void opal_sem_a_set_name_invisible( opal_sem* o, tp_t name ){ const opal_sem_spect_s* p = opal_sem_spect_s_get_aware( o ); assert( p->set_name_invisible ); p->set_name_invisible( o, name );} \
  static inline bl_t opal_sem_a_defines_set_name_invisible( const opal_sem* o ){ return  opal_sem_spect_s_get_aware( o )->set_name_invisible != NULL;} \
  BETH_EXPAND_ITEM_opal_sem_link_s \
  BETH_EXPAND_ITEM_opal_sem_links_s \
  BETH_EXPAND_ITEM_opal_sem_body_s \
  BETH_EXPAND_ITEM_opal_sem_cell_s \
  BETH_EXPAND_ITEM_opal_sem_stack_flag_s \
  BETH_EXPAND_GROUP_opal_sem_builder \
  BETH_EXPAND_GROUP_opal_sem_tree

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_context

#define TYPEOF_opal_sem_context 0x93D6278720517767ull
#define TYPEOF_opal_sem_context_spect_s 0xCF9F2A3121FF5957ull
#define TYPEOF_opal_sem_context_s 0xBC8FE9EF583316A1ull
#define BETH_EXPAND_ITEM_opal_sem_context_s \
  BCORE_DECLARE_OBJECT( opal_sem_context_s ) \
  { \
      aware_t _; \
      opal_nop_context_s nop_context; \
      bcore_hmap_name_s hmap_name; \
      bcore_arr_st_s arr_symbol_op2; \
      bcore_hmap_tp_s control_types; \
      bcore_hmap_tp_s reserved_names; \
  }; \
  static inline bcore_prsg* opal_sem_context_s_get_prsg( opal_sem_context_s* o ); \
  void opal_sem_context_s_setup( opal_sem_context_s* o, opal_sem_cell_s* frame ); \
  static inline sc_t opal_sem_context_s_nameof( const opal_sem_context_s* o, tp_t name ); \
  static inline sc_t opal_sem_context_s_ifnameof( const opal_sem_context_s* o, tp_t name ); \
  static inline tp_t opal_sem_context_s_typeof( const opal_sem_context_s* o, sc_t name ); \
  static inline tp_t opal_sem_context_s_entypeof( opal_sem_context_s* o, sc_t name ); \
  opal_sem_cell_s* opal_sem_context_s_setup_cell( opal_sem_context_s* o, opal_sem_cell_s* cell ); \
  opal_sem_cell_s* opal_sem_context_s_create_cell( opal_sem_context_s* o ); \
  static inline bcore_prsg* opal_sem_context_s_get_prsg( opal_sem_context_s* o ){ return  opal_nop_context_s_get_prsg(&(o->nop_context));} \
  static inline sc_t opal_sem_context_s_nameof( const opal_sem_context_s* o, tp_t name ){ return  bcore_hmap_name_s_get_sc(&(o->hmap_name),name );} \
  static inline sc_t opal_sem_context_s_ifnameof( const opal_sem_context_s* o, tp_t name ){ sc_t sc = opal_sem_context_s_nameof(o,name ); return  sc ? sc : "";} \
  static inline tp_t opal_sem_context_s_typeof( const opal_sem_context_s* o, sc_t name ){ return  btypeof( name );} \
  static inline tp_t opal_sem_context_s_entypeof( opal_sem_context_s* o, sc_t name ){ return  bcore_hmap_name_s_set_sc(&(o->hmap_name),name );}
#define BETH_EXPAND_GROUP_opal_sem_context \
  BCORE_FORWARD_OBJECT( opal_sem_context ); \
  BCORE_FORWARD_OBJECT( opal_sem_context_s ); \
  XOILA_DECLARE_SPECT( opal_sem_context ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_sem_context ) \
  BETH_EXPAND_ITEM_opal_sem_context_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_id

#define TYPEOF_opal_sem_id 0x56D6EE4EE146CDA9ull
#define TYPEOF_opal_sem_id_spect_s 0x4DB120DE8702C365ull
#define TYPEOF_opal_sem_id_s 0xFA4C51F178E4DB03ull
#define BETH_EXPAND_ITEM_opal_sem_id_s \
  BCORE_DECLARE_OBJECT( opal_sem_id_s ) \
  { \
      aware_t _; \
      bcore_arr_tp_s arr_tp; \
  }; \
  static inline void opal_sem_id_s_clear( opal_sem_id_s* o ); \
  static inline void opal_sem_id_s_set( opal_sem_id_s* o, tp_t tp ); \
  static inline void opal_sem_id_s_push_child( opal_sem_id_s* o, tp_t tp ); \
  static inline void opal_sem_id_s_push_parent( opal_sem_id_s* o, tp_t tp ); \
  void opal_sem_id_s_to_string( const opal_sem_id_s* o, const opal_context* context, st_s* s ); \
  static inline void opal_sem_id_s_clear( opal_sem_id_s* o ){ bcore_arr_tp_s_clear(&(o->arr_tp));} \
  static inline void opal_sem_id_s_set( opal_sem_id_s* o, tp_t tp ){ bcore_arr_tp_s_clear(&(o->arr_tp)); bcore_arr_tp_s_push(&(o->arr_tp),tp );} \
  static inline void opal_sem_id_s_push_child( opal_sem_id_s* o, tp_t tp ){ bcore_arr_tp_s_push(&(o->arr_tp),tp );} \
  static inline void opal_sem_id_s_push_parent( opal_sem_id_s* o, tp_t tp ){ bcore_arr_tp_s_push_left(&(o->arr_tp),tp );}
#define BETH_EXPAND_GROUP_opal_sem_id \
  BCORE_FORWARD_OBJECT( opal_sem_id ); \
  BCORE_FORWARD_OBJECT( opal_sem_id_s ); \
  XOILA_DECLARE_SPECT( opal_sem_id ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_sem_id ) \
  BETH_EXPAND_ITEM_opal_sem_id_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_builder

#define TYPEOF_opal_sem_builder 0xFDB7521C8FDF88A3ull
#define TYPEOF_opal_sem_builder_spect_s 0x4F36401018C91003ull
#define TYPEOF_opal_sem_builder_s 0x7FED14E5533C84A5ull
#define BETH_EXPAND_ITEM_opal_sem_builder_s \
  BCORE_DECLARE_OBJECT( opal_sem_builder_s ) \
  { \
      aware_t _; \
      opal_sem_context_s* context; \
      opal_sem_cell_s* cell_context; \
      opal_sem_cell_s* cell_frame; \
  }; \
  er_t opal_sem_builder_s_build_from_source( opal_sem_builder_s* o, opal_sem_cell_s* cell, bcore_source* source );
#define BETH_EXPAND_GROUP_opal_sem_builder \
  BCORE_FORWARD_OBJECT( opal_sem_builder ); \
  BCORE_FORWARD_OBJECT( opal_sem_builder_s ); \
  XOILA_DECLARE_SPECT( opal_sem_builder ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_sem_builder ) \
  BETH_EXPAND_ITEM_opal_sem_builder_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_tree

#define TYPEOF_opal_sem_tree 0x56E89C090E7A32B4ull
#define TYPEOF_opal_sem_tree_spect_s 0x58D4EB9FF6542F6Cull
#define TYPEOF_opal_sem_tree_node_s 0xA4637EA997769B13ull
#define BETH_EXPAND_ITEM_opal_sem_tree_node_s \
  BCORE_DECLARE_OBJECT( opal_sem_tree_node_s ) \
  { \
      aware_t _; \
      sz_t id; \
      opal_sem_cell_s* cell; \
      opal_sem_tree_node_s* parent; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_sem_tree_node_s, ); \
  }; \
  void opal_sem_tree_node_s_push_parents_to_sem_id( const opal_sem_tree_node_s* o, opal_sem_id_s* sem_id ); \
  void opal_sem_tree_node_s_get_sem_id( const opal_sem_tree_node_s* o, opal_sem_id_s* sem_id ); \
  static inline opal_sem_tree_node_s* opal_sem_tree_node_s_set_space( opal_sem_tree_node_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_sem_tree_node_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_sem_tree_node_s* opal_sem_tree_node_s_set_size( opal_sem_tree_node_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_sem_tree_node_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_sem_tree_node_s* opal_sem_tree_node_s_clear( opal_sem_tree_node_s* o ) { bcore_array_t_set_space( TYPEOF_opal_sem_tree_node_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_sem_tree_node_s* opal_sem_tree_node_s_push_c( opal_sem_tree_node_s* o, const opal_sem_tree_node_s* v ) { bcore_array_t_push( TYPEOF_opal_sem_tree_node_s, ( bcore_array* )o, sr_twc( TYPEOF_opal_sem_tree_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_sem_tree_node_s* opal_sem_tree_node_s_push_d( opal_sem_tree_node_s* o,       opal_sem_tree_node_s* v ) { bcore_array_t_push( TYPEOF_opal_sem_tree_node_s, ( bcore_array* )o, sr_tsd( TYPEOF_opal_sem_tree_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_sem_tree_node_s* opal_sem_tree_node_s_push( opal_sem_tree_node_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_opal_sem_tree_node_s, ( bcore_array* )o, sr_t_create( TYPEOF_opal_sem_tree_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_sem_tree_s 0xAEB9953E128E38C6ull
#define BETH_EXPAND_ITEM_opal_sem_tree_s \
  BCORE_DECLARE_OBJECT( opal_sem_tree_s ) \
  { \
      aware_t _; \
      sz_t id_base; \
      opal_sem_tree_node_s* root; \
  }; \
  er_t opal_sem_tree_s_enter( opal_sem_tree_s* o, opal_sem_cell_s* cell, opal_sem_tree_node_s* node_in, opal_sem_tree_node_s** node_out ); \
  er_t opal_sem_tree_s_exit( opal_sem_tree_s* o, opal_sem_cell_s* cell, bl_t test_for_wrapper, opal_sem_tree_node_s* node_in, opal_sem_tree_node_s** node_out );
#define BETH_EXPAND_GROUP_opal_sem_tree \
  BCORE_FORWARD_OBJECT( opal_sem_tree ); \
  BCORE_FORWARD_OBJECT( opal_sem_tree_node_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_tree_s ); \
  XOILA_DECLARE_SPECT( opal_sem_tree ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_sem_tree ) \
  BETH_EXPAND_ITEM_opal_sem_tree_node_s \
  BETH_EXPAND_ITEM_opal_sem_tree_s

/**********************************************************************************************************************/
// source: opal_net.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_net

#define TYPEOF_opal_net 0x5D6D8FC19EF09313ull
#define TYPEOF_opal_net_spect_s 0xB8A61FE34ECFC873ull
#define TYPEOF_opal_net_link_s 0xBEC64DD7FCB55AE6ull
#define BETH_EXPAND_ITEM_opal_net_link_s \
  BCORE_DECLARE_OBJECT( opal_net_link_s ) \
  { \
      aware_t _; \
      opal_net_node_s* node; \
  };
#define TYPEOF_opal_net_links_s 0xD5746702F3BEB147ull
#define BETH_EXPAND_ITEM_opal_net_links_s \
  BCORE_DECLARE_OBJECT( opal_net_links_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_net_link_s, ); \
  }; \
  static inline opal_net_links_s* opal_net_links_s_set_space( opal_net_links_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_net_links_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_net_links_s* opal_net_links_s_set_size( opal_net_links_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_net_links_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_net_links_s* opal_net_links_s_clear( opal_net_links_s* o ) { bcore_array_t_set_space( TYPEOF_opal_net_links_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_net_link_s* opal_net_links_s_push_c( opal_net_links_s* o, const opal_net_link_s* v ) { bcore_array_t_push( TYPEOF_opal_net_links_s, ( bcore_array* )o, sr_twc( TYPEOF_opal_net_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_net_link_s* opal_net_links_s_push_d( opal_net_links_s* o,       opal_net_link_s* v ) { bcore_array_t_push( TYPEOF_opal_net_links_s, ( bcore_array* )o, sr_tsd( TYPEOF_opal_net_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_net_link_s* opal_net_links_s_push( opal_net_links_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_opal_net_links_s, ( bcore_array* )o, sr_t_create( TYPEOF_opal_net_link_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_net_node_s 0x9351C9C406B6173Aull
#define BETH_EXPAND_ITEM_opal_net_node_s \
  BCORE_DECLARE_OBJECT( opal_net_node_s ) \
  { \
      aware_t _; \
      opal_net_links_s upls; \
      opal_net_links_s dnls; \
      tp_t name; \
      opal_sem_id_s* sem_id; \
      bl_t flag; \
      bl_t probe; \
      sz_t id; \
      bhvm_mcode_node_s* mnode; \
      opal_nop* nop; \
      opal_nop_solve_result_s* result; \
      opal_context* context; \
      bcore_source_point_s* source_point; \
  }; \
  sz_t opal_net_node_s_up_index( const opal_net_node_s* o, const opal_net_node_s* node ); \
  void opal_net_node_s_set_nop_d( opal_net_node_s* o, opal_nop* nop ); \
  static inline bl_t opal_net_node_s_is_cyclic( const opal_net_node_s* o ); \
  static inline bl_t opal_net_node_s_is_cyclic( const opal_net_node_s* o ){ return  ( o->mnode ) ? o->mnode->cyclic : opal_nop_a_is_cyclic(o->nop);}
#define TYPEOF_opal_net_node_adl_s 0x509B15320CE81796ull
#define BETH_EXPAND_ITEM_opal_net_node_adl_s \
  BCORE_DECLARE_OBJECT( opal_net_node_adl_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_net_node_s, ); \
  }; \
  static inline opal_net_node_adl_s* opal_net_node_adl_s_set_space( opal_net_node_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_net_node_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_net_node_adl_s* opal_net_node_adl_s_set_size( opal_net_node_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_net_node_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_net_node_adl_s* opal_net_node_adl_s_clear( opal_net_node_adl_s* o ) { bcore_array_t_set_space( TYPEOF_opal_net_node_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_net_node_s* opal_net_node_adl_s_push_c( opal_net_node_adl_s* o, const opal_net_node_s* v ) { bcore_array_t_push( TYPEOF_opal_net_node_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_opal_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_net_node_s* opal_net_node_adl_s_push_d( opal_net_node_adl_s* o,       opal_net_node_s* v ) { bcore_array_t_push( TYPEOF_opal_net_node_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_opal_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_net_node_s* opal_net_node_adl_s_push( opal_net_node_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_opal_net_node_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_opal_net_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_net_nodes_s 0xB7AE4517C9DAF203ull
#define BETH_EXPAND_ITEM_opal_net_nodes_s \
  BCORE_DECLARE_OBJECT( opal_net_nodes_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_net_node_s, ); \
  }; \
  opal_net_node_s* opal_net_nodes_s_get_by_id( opal_net_nodes_s* o, sz_t id ); \
  static inline opal_net_nodes_s* opal_net_nodes_s_set_space( opal_net_nodes_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_net_nodes_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_net_nodes_s* opal_net_nodes_s_set_size( opal_net_nodes_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_net_nodes_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_net_nodes_s* opal_net_nodes_s_clear( opal_net_nodes_s* o ) { bcore_array_t_set_space( TYPEOF_opal_net_nodes_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_net_node_s* opal_net_nodes_s_push_c( opal_net_nodes_s* o, const opal_net_node_s* v ) { bcore_array_t_push( TYPEOF_opal_net_nodes_s, ( bcore_array* )o, sr_twc( TYPEOF_opal_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_net_node_s* opal_net_nodes_s_push_d( opal_net_nodes_s* o,       opal_net_node_s* v ) { bcore_array_t_push( TYPEOF_opal_net_nodes_s, ( bcore_array* )o, sr_tsd( TYPEOF_opal_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_net_node_s* opal_net_nodes_s_push( opal_net_nodes_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_opal_net_nodes_s, ( bcore_array* )o, sr_t_create( TYPEOF_opal_net_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_net_cell_s 0x872347AB3D381CC2ull
#define BETH_EXPAND_ITEM_opal_net_cell_s \
  BCORE_DECLARE_OBJECT( opal_net_cell_s ) \
  { \
      aware_t _; \
      sz_t max_depth; \
      opal_net_nodes_s body; \
      opal_net_nodes_s encs; \
      opal_net_nodes_s excs; \
      opal_context* context; \
  }; \
  bl_t opal_net_cell_s_is_consistent( const opal_net_cell_s* o ); \
  void opal_net_cell_s_normalize( opal_net_cell_s* o ); \
  void opal_net_cell_s_clear_flags( opal_net_cell_s* o ); \
  void opal_net_cell_s_clear_all_flags( opal_net_cell_s* o ); \
  void opal_net_cell_s_solve( opal_net_cell_s* o ); \
  void opal_net_cell_s_clear_downlinks( opal_net_cell_s* o ); \
  void opal_net_cell_s_set_downlinks( opal_net_cell_s* o ); \
  void opal_net_cell_s_copy_x( opal_net_cell_s* o, const opal_net_cell_s* src ); \
  static inline void opal_net_cell_s_mutated( opal_net_cell_s* o ); \
  static inline void opal_net_cell_s_mutated( opal_net_cell_s* o ){ ERR_fa( "Cannot reconstitute." );}
#define BETH_EXPAND_GROUP_opal_net \
  BCORE_FORWARD_OBJECT( opal_net ); \
  BCORE_FORWARD_OBJECT( opal_net_link_s ); \
  BCORE_FORWARD_OBJECT( opal_net_links_s ); \
  BCORE_FORWARD_OBJECT( opal_net_node_s ); \
  BCORE_FORWARD_OBJECT( opal_net_node_adl_s ); \
  BCORE_FORWARD_OBJECT( opal_net_nodes_s ); \
  BCORE_FORWARD_OBJECT( opal_net_cell_s ); \
  BCORE_FORWARD_OBJECT( opal_net_builder ); \
  typedef bl_t (*opal_net_is_cyclic)( const opal_net* o ); \
  XOILA_DECLARE_SPECT( opal_net ) \
  { \
      bcore_spect_header_s header; \
      opal_net_is_cyclic is_cyclic; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_net ) \
  BETH_EXPAND_ITEM_opal_net_link_s \
  BETH_EXPAND_ITEM_opal_net_links_s \
  static inline bl_t opal_net_a_is_cyclic( const opal_net* o ){ const opal_net_spect_s* p = opal_net_spect_s_get_aware( o ); assert( p->is_cyclic ); return p->is_cyclic( o );} \
  static inline bl_t opal_net_a_defines_is_cyclic( const opal_net* o ){ return  true;} \
  static inline bl_t opal_net_is_cyclic_default( const opal_net* o ){ return  false;} \
  BETH_EXPAND_ITEM_opal_net_node_s \
  BETH_EXPAND_ITEM_opal_net_node_adl_s \
  BETH_EXPAND_ITEM_opal_net_nodes_s \
  BETH_EXPAND_ITEM_opal_net_cell_s \
  BETH_EXPAND_GROUP_opal_net_builder

//----------------------------------------------------------------------------------------------------------------------
// group: opal_net_builder

#define TYPEOF_opal_net_builder 0x53A00C404CA6E023ull
#define TYPEOF_opal_net_builder_spect_s 0xDFC82E42BE465783ull
#define TYPEOF_opal_net_builder_s 0x86E50E9200C00825ull
#define BETH_EXPAND_ITEM_opal_net_builder_s \
  BCORE_DECLARE_OBJECT( opal_net_builder_s ) \
  { \
      aware_t _; \
      opal_sem_builder_s sem_builder; \
      bhvm_holor_adl_s input_holors; \
      bcore_sink* log; \
  }; \
  static inline void opal_net_builder_s_fork_log( opal_net_builder_s* o, bcore_sink* log ); \
  void opal_net_builder_s_fork_input_holors( opal_net_builder_s* o, const bhvm_holor_s** input_holors, sz_t size_input_holors ); \
  void opal_net_builder_s_build_from_source( opal_net_builder_s* o, opal_net_cell_s* net_cell, bcore_source* source ); \
  static inline void opal_net_builder_s_fork_log( opal_net_builder_s* o, bcore_sink* log ){ bcore_sink_a_attach( &(o->log ), (bcore_sink*)( bcore_fork( log )));}
#define BETH_EXPAND_GROUP_opal_net_builder \
  BCORE_FORWARD_OBJECT( opal_net_builder ); \
  BCORE_FORWARD_OBJECT( opal_net_builder_s ); \
  XOILA_DECLARE_SPECT( opal_net_builder ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_net_builder ) \
  BETH_EXPAND_ITEM_opal_net_builder_s

/**********************************************************************************************************************/
// source: opal_frame.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_frame

#define TYPEOF_opal_frame 0xB871A75DF4155775ull
#define TYPEOF_opal_frame_spect_s 0x065A082D2A859751ull
#define TYPEOF_opal_frame_s 0x269090A5B208E077ull
#define BETH_EXPAND_ITEM_opal_frame_s \
  BCORE_DECLARE_OBJECT( opal_frame_s ) \
  { \
      aware_t _; \
      bcore_sink* log; \
      opal_context* context; \
      bhvm_mcode_frame_s* mcf; \
      bl_t is_cyclic; \
      bl_t is_setup; \
      sz_t size_en; \
      sz_t size_ex; \
      opal_frame_hidx_s hidx_en; \
      opal_frame_hidx_s hidx_ex; \
      opal_frame_hidx_s hidx_ada; \
  }; \
  void opal_frame_s_reset( opal_frame_s* o ); \
  opal_frame_s* opal_frame_s_bind_holors( opal_frame_s* o ); \
  void opal_frame_s_setup( opal_frame_s* o ); \
  void opal_frame_s_check_integrity( const opal_frame_s* o ); \
  static inline void opal_frame_s_shelve( opal_frame_s* o ); \
  static inline void opal_frame_s_mutated( opal_frame_s* o ); \
  static inline void opal_frame_s_copy_x( opal_frame_s* o, const opal_frame_s* src ); \
  opal_frame_s* opal_frame_s_setup_from_source( opal_frame_s* o, bcore_source* source, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_setup_from_st( opal_frame_s* o, const st_s* st, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_setup_from_sc( opal_frame_s* o, sc_t sc, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_create_from_source( bcore_source* source, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_create_from_st( const st_s* st, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_create_from_sc( sc_t sc, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_setup_from_source_adl( opal_frame_s* o, bcore_source* source, const bhvm_holor_adl_s* en ); \
  static inline opal_frame_s* opal_frame_s_setup_from_st_adl( opal_frame_s* o, const st_s* st, const bhvm_holor_adl_s* en ); \
  static inline opal_frame_s* opal_frame_s_setup_from_sc_adl( opal_frame_s* o, sc_t sc, const bhvm_holor_adl_s* en ); \
  static inline opal_frame_s* opal_frame_s_create_from_source_adl( bcore_source* source, const bhvm_holor_adl_s* en ); \
  static inline opal_frame_s* opal_frame_s_create_from_st_adl( const st_s* st, const bhvm_holor_adl_s* en ); \
  static inline opal_frame_s* opal_frame_s_create_from_sc_adl( sc_t sc, const bhvm_holor_adl_s* en ); \
  static inline sz_t opal_frame_s_get_size_en( const opal_frame_s* o ); \
  static inline sz_t opal_frame_s_get_size_ex( const opal_frame_s* o ); \
  static inline sz_t opal_frame_s_get_size_ada( const opal_frame_s* o ); \
  static inline bhvm_holor_s* opal_frame_s_get_ap_en( opal_frame_s* o, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_s_get_dp_en( opal_frame_s* o, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_s_get_ap_ex( opal_frame_s* o, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_s_get_dp_ex( opal_frame_s* o, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_s_get_ap_ada( opal_frame_s* o, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_s_get_dp_ada( opal_frame_s* o, sz_t index ); \
  opal_frame_s* opal_frame_s_run_ap( opal_frame_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex ); \
  opal_frame_s* opal_frame_s_run_dp( opal_frame_s* o, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en ); \
  opal_frame_s* opal_frame_s_run_ap_adl( opal_frame_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex ); \
  opal_frame_s* opal_frame_s_run_dp_adl( opal_frame_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en ); \
  void opal_frame_s_mutable_estimate_jacobian_en( opal_frame_s* o, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl ); \
  void opal_frame_s_estimate_jacobian_en( const opal_frame_s* o, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl ); \
  void opal_frame_s_mutable_estimate_jacobian_ada( opal_frame_s* o, const bhvm_holor_adl_s* adl_en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl ); \
  void opal_frame_s_estimate_jacobian_ada( const opal_frame_s* o, const bhvm_holor_adl_s* adl_en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl ); \
  static inline void opal_frame_s_shelve( opal_frame_s* o ){ bl_t is_setup = o->is_setup; opal_frame_s_reset(o); o->is_setup = is_setup; /* setup flag remembers o's setup state before shelving */} \
  static inline void opal_frame_s_mutated( opal_frame_s* o ){ if( o->is_setup ) { opal_frame_s_reset(o); opal_frame_s_setup(o); } opal_frame_s_check_integrity(o);} \
  static inline void opal_frame_s_copy_x( opal_frame_s* o, const opal_frame_s* src ){ if( o->is_setup ) { opal_frame_s_reset(o); opal_frame_s_setup(o); } opal_frame_s_check_integrity(o);} \
  static inline opal_frame_s* opal_frame_s_setup_from_st( opal_frame_s* o, const st_s* st, const bhvm_holor_s** en, sz_t size_en ){ BLM_INIT(); BLM_RETURNV( opal_frame_s*, opal_frame_s_setup_from_source(o,BLM_A_PUSH( bcore_source_string_s_create_from_string(st ) ), en, size_en ) );} \
  static inline opal_frame_s* opal_frame_s_setup_from_sc( opal_frame_s* o, sc_t sc, const bhvm_holor_s** en, sz_t size_en ){ st_s st; st_s_init_weak_sc( &st, sc ); return  opal_frame_s_setup_from_st( o,&st, en, size_en );} \
  static inline opal_frame_s* opal_frame_s_create_from_source( bcore_source* source, const bhvm_holor_s** en, sz_t size_en ){ return  opal_frame_s_setup_from_source((opal_frame_s_create()),source, en, size_en );} \
  static inline opal_frame_s* opal_frame_s_create_from_st( const st_s* st, const bhvm_holor_s** en, sz_t size_en ){ return  opal_frame_s_setup_from_st((opal_frame_s_create()),st,     en, size_en );} \
  static inline opal_frame_s* opal_frame_s_create_from_sc( sc_t sc, const bhvm_holor_s** en, sz_t size_en ){ return  opal_frame_s_setup_from_sc((opal_frame_s_create()),sc,     en, size_en );} \
  static inline opal_frame_s* opal_frame_s_setup_from_source_adl( opal_frame_s* o, bcore_source* source, const bhvm_holor_adl_s* en ){ return  opal_frame_s_setup_from_source(o,source, en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_setup_from_st_adl( opal_frame_s* o, const st_s* st, const bhvm_holor_adl_s* en ){ return  opal_frame_s_setup_from_st(o,st,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_setup_from_sc_adl( opal_frame_s* o, sc_t sc, const bhvm_holor_adl_s* en ){ return  opal_frame_s_setup_from_sc(o,sc,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_create_from_source_adl( bcore_source* source, const bhvm_holor_adl_s* en ){ return  opal_frame_s_setup_from_source_adl((opal_frame_s_create()),source, en );} \
  static inline opal_frame_s* opal_frame_s_create_from_st_adl( const st_s* st, const bhvm_holor_adl_s* en ){ return  opal_frame_s_setup_from_st_adl((opal_frame_s_create()),st, en );} \
  static inline opal_frame_s* opal_frame_s_create_from_sc_adl( sc_t sc, const bhvm_holor_adl_s* en ){ return  opal_frame_s_setup_from_sc_adl((opal_frame_s_create()),sc, en );} \
  static inline sz_t opal_frame_s_get_size_en( const opal_frame_s* o ){ return  opal_frame_hidx_s_get_size(&(o->hidx_en ));} \
  static inline sz_t opal_frame_s_get_size_ex( const opal_frame_s* o ){ return  opal_frame_hidx_s_get_size(&(o->hidx_ex ));} \
  static inline sz_t opal_frame_s_get_size_ada( const opal_frame_s* o ){ return  opal_frame_hidx_s_get_size(&(o->hidx_ada));} \
  static inline bhvm_holor_s* opal_frame_s_get_ap_en( opal_frame_s* o, sz_t index ){ return  opal_frame_hidx_s_get_pclass_holor(&(o->hidx_en ),o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_dp_en( opal_frame_s* o, sz_t index ){ return  opal_frame_hidx_s_get_pclass_holor(&(o->hidx_en ),o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_ap_ex( opal_frame_s* o, sz_t index ){ return  opal_frame_hidx_s_get_pclass_holor(&(o->hidx_ex ),o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_dp_ex( opal_frame_s* o, sz_t index ){ return  opal_frame_hidx_s_get_pclass_holor(&(o->hidx_ex ),o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_ap_ada( opal_frame_s* o, sz_t index ){ return  opal_frame_hidx_s_get_pclass_holor(&(o->hidx_ada),o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_dp_ada( opal_frame_s* o, sz_t index ){ return  opal_frame_hidx_s_get_pclass_holor(&(o->hidx_ada),o->mcf->hbase, TYPEOF_pclass_ag0, index );}
#define TYPEOF_opal_frame_custom_hmeta_s 0x93A48653768D3B59ull
#define BETH_EXPAND_ITEM_opal_frame_custom_hmeta_s \
  BCORE_DECLARE_OBJECT( opal_frame_custom_hmeta_s ) \
  { \
      aware_t _; \
      sz_t ur_slot; \
      sz_t ur_src; \
  };
#define TYPEOF_opal_frame_cyclic_s 0x995E0A8DD44E6957ull
#define BETH_EXPAND_ITEM_opal_frame_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_frame_cyclic_s ) \
  { \
      aware_t _; \
      opal_frame_s* frame; \
      sz_t unroll_size; \
      bl_t is_setup; \
      sz_t unroll_index; \
      bhvm_mcode_track_adl_s* track_adl_ap; \
      bhvm_mcode_track_adl_s* track_adl_dp; \
      bhvm_mcode_track_adl_s* track_adl_ap_setup; \
      opal_frame_hidx_ads_s hidx_ads_en; \
      opal_frame_hidx_ads_s hidx_ads_ex; \
  }; \
  opal_frame_cyclic_s* opal_frame_cyclic_s_bind_holors( opal_frame_cyclic_s* o ); \
  void opal_frame_cyclic_s_reset( opal_frame_cyclic_s* o ); \
  void opal_frame_cyclic_s_setup( opal_frame_cyclic_s* o ); \
  static inline void opal_frame_cyclic_s_shelve( opal_frame_cyclic_s* o ); \
  static inline void opal_frame_cyclic_s_mutated( opal_frame_cyclic_s* o ); \
  static inline void opal_frame_cyclic_s_copy_x( opal_frame_cyclic_s* o, const opal_frame_cyclic_s* src ); \
  static inline sz_t opal_frame_cyclic_s_get_size_en( const opal_frame_cyclic_s* o ); \
  static inline sz_t opal_frame_cyclic_s_get_size_ex( const opal_frame_cyclic_s* o ); \
  static inline sz_t opal_frame_cyclic_s_get_size_ada( const opal_frame_cyclic_s* o ); \
  opal_frame_cyclic_s* opal_frame_cyclic_s_run_ap( opal_frame_cyclic_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex ); \
  opal_frame_cyclic_s* opal_frame_cyclic_s_run_ap_adl( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex ); \
  void opal_frame_cyclic_s_mutable_estimate_jacobian_en( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl ); \
  void opal_frame_cyclic_s_estimate_jacobian_en( const opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl ); \
  static inline void opal_frame_cyclic_s_shelve( opal_frame_cyclic_s* o ){ bl_t is_setup = o->is_setup; opal_frame_cyclic_s_reset(o); o->is_setup = is_setup; /* setup flag remembers o's setup state before shelving */} \
  static inline void opal_frame_cyclic_s_mutated( opal_frame_cyclic_s* o ){ if( o->is_setup ) { opal_frame_cyclic_s_reset(o); opal_frame_cyclic_s_setup(o); }} \
  static inline void opal_frame_cyclic_s_copy_x( opal_frame_cyclic_s* o, const opal_frame_cyclic_s* src ){ if( o->is_setup ) { opal_frame_cyclic_s_reset(o); opal_frame_cyclic_s_setup(o); }} \
  static inline sz_t opal_frame_cyclic_s_get_size_en( const opal_frame_cyclic_s* o ){ return  opal_frame_s_get_size_en(o->frame);} \
  static inline sz_t opal_frame_cyclic_s_get_size_ex( const opal_frame_cyclic_s* o ){ return  opal_frame_s_get_size_ex(o->frame);} \
  static inline sz_t opal_frame_cyclic_s_get_size_ada( const opal_frame_cyclic_s* o ){ return  opal_frame_s_get_size_ada(o->frame);}
#define BETH_EXPAND_GROUP_opal_frame \
  BCORE_FORWARD_OBJECT( opal_frame ); \
  BCORE_FORWARD_OBJECT( opal_frame_hidx ); \
  BCORE_FORWARD_OBJECT( opal_frame_s ); \
  BCORE_FORWARD_OBJECT( opal_frame_custom_hmeta_s ); \
  BCORE_FORWARD_OBJECT( opal_frame_cyclic_s ); \
  XOILA_DECLARE_SPECT( opal_frame ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_frame ) \
  BETH_EXPAND_GROUP_opal_frame_hidx \
  BETH_EXPAND_ITEM_opal_frame_s \
  BETH_EXPAND_ITEM_opal_frame_custom_hmeta_s \
  BETH_EXPAND_ITEM_opal_frame_cyclic_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_frame_hidx

#define TYPEOF_opal_frame_hidx 0x52B2BB21BA315475ull
#define TYPEOF_opal_frame_hidx_spect_s 0x9C9E1CB0FE433451ull
#define TYPEOF_opal_frame_hidx_s 0xD4D8DFE337DB6577ull
#define BETH_EXPAND_ITEM_opal_frame_hidx_s \
  BCORE_DECLARE_OBJECT( opal_frame_hidx_s ) \
  { \
      aware_t _; \
      bcore_arr_sz_s* arr; \
  }; \
  static inline opal_frame_hidx_s* opal_frame_hidx_s_clear( opal_frame_hidx_s* o ); \
  static inline opal_frame_hidx_s* opal_frame_hidx_s_push( opal_frame_hidx_s* o, sz_t index ); \
  static inline sz_t opal_frame_hidx_s_get_idx( const opal_frame_hidx_s* o, sz_t index ); \
  static inline sz_t opal_frame_hidx_s_get_size( const opal_frame_hidx_s* o ); \
  static inline bhvm_holor_s* opal_frame_hidx_s_get_holor( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ); \
  static inline bhvm_mcode_hmeta* opal_frame_hidx_s_get_hmeta( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ); \
  sz_t opal_frame_hidx_s_get_pclass_idx( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_hidx_s_get_pclass_holor( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ); \
  static inline bhvm_mcode_hmeta* opal_frame_hidx_s_get_pclass_hmeta( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ); \
  opal_frame_hidx_s* opal_frame_hidx_s_replace_index( opal_frame_hidx_s* o, bcore_arr_sz_s* index_map ); \
  static inline opal_frame_hidx_s* opal_frame_hidx_s_clear( opal_frame_hidx_s* o ){ if( o->arr ) bcore_arr_sz_s_clear(o->arr); return  o;} \
  static inline opal_frame_hidx_s* opal_frame_hidx_s_push( opal_frame_hidx_s* o, sz_t index ){ bcore_arr_sz_s_push(BCORE_PASS_CREATE(bcore_arr_sz_s,o->arr),index ); return  o;} \
  static inline sz_t opal_frame_hidx_s_get_idx( const opal_frame_hidx_s* o, sz_t index ){ assert( index >= 0 && index < o->arr->size ); return  BCORE_PASS_TEST(bcore_arr_sz_s,o->arr)->data[ index ];} \
  static inline sz_t opal_frame_hidx_s_get_size( const opal_frame_hidx_s* o ){ return  o->arr ? o->arr->size : 0;} \
  static inline bhvm_holor_s* opal_frame_hidx_s_get_holor( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ){ return  bhvm_mcode_hbase_s_get_holor(hbase,opal_frame_hidx_s_get_idx(o,index ) );} \
  static inline bhvm_mcode_hmeta* opal_frame_hidx_s_get_hmeta( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ){ return  bhvm_mcode_hbase_s_get_hmeta(hbase,opal_frame_hidx_s_get_idx(o,index ) );} \
  static inline bhvm_holor_s* opal_frame_hidx_s_get_pclass_holor( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ){ return  bhvm_mcode_hbase_s_get_holor(hbase,opal_frame_hidx_s_get_pclass_idx(o,hbase, pclass, index ) );} \
  static inline bhvm_mcode_hmeta* opal_frame_hidx_s_get_pclass_hmeta( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ){ return  bhvm_mcode_hbase_s_get_hmeta(hbase,opal_frame_hidx_s_get_pclass_idx(o,hbase, pclass, index ) );}
#define TYPEOF_opal_frame_hidx_ads_s 0x3B15C6EBF08B98D2ull
#define BETH_EXPAND_ITEM_opal_frame_hidx_ads_s \
  BCORE_DECLARE_OBJECT( opal_frame_hidx_ads_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_SOLID_STATIC_S( opal_frame_hidx_s, ); \
  }; \
  static inline opal_frame_hidx_ads_s* opal_frame_hidx_ads_s_set_space( opal_frame_hidx_ads_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_frame_hidx_ads_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_frame_hidx_ads_s* opal_frame_hidx_ads_s_set_size( opal_frame_hidx_ads_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_frame_hidx_ads_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_frame_hidx_ads_s* opal_frame_hidx_ads_s_clear( opal_frame_hidx_ads_s* o ) { bcore_array_t_set_space( TYPEOF_opal_frame_hidx_ads_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_frame_hidx_s* opal_frame_hidx_ads_s_push_c( opal_frame_hidx_ads_s* o, const opal_frame_hidx_s* v ) { bcore_array_t_push( TYPEOF_opal_frame_hidx_ads_s, ( bcore_array* )o, sr_twc( TYPEOF_opal_frame_hidx_s, v ) ); return &o->data[ o->size - 1 ]; } \
  static inline opal_frame_hidx_s* opal_frame_hidx_ads_s_push_d( opal_frame_hidx_ads_s* o,       opal_frame_hidx_s* v ) { bcore_array_t_push( TYPEOF_opal_frame_hidx_ads_s, ( bcore_array* )o, sr_tsd( TYPEOF_opal_frame_hidx_s, v ) ); return &o->data[ o->size - 1 ]; } \
  static inline opal_frame_hidx_s* opal_frame_hidx_ads_s_push( opal_frame_hidx_ads_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_opal_frame_hidx_ads_s, ( bcore_array* )o, sr_null() ); \
      return &o->data[ o->size - 1 ]; \
  }
#define BETH_EXPAND_GROUP_opal_frame_hidx \
  BCORE_FORWARD_OBJECT( opal_frame_hidx ); \
  BCORE_FORWARD_OBJECT( opal_frame_hidx_s ); \
  BCORE_FORWARD_OBJECT( opal_frame_hidx_ads_s ); \
  XOILA_DECLARE_SPECT( opal_frame_hidx ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_frame_hidx ) \
  BETH_EXPAND_ITEM_opal_frame_hidx_s \
  BETH_EXPAND_ITEM_opal_frame_hidx_ads_s

/**********************************************************************************************************************/
// source: opal_eval_frame.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_eval_frame; embeds: opal_eval_frame.x

#define TYPEOF_opal_eval_frame 0x4B9F7CCD20FCA388ull
#define TYPEOF_opal_eval_frame_spect_s 0x379D07D300BA11D0ull
#define TYPEOF_opal_eval_frame_result_s 0xB85688A323270006ull
#define BETH_EXPAND_ITEM_opal_eval_frame_result_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_result_s ) \
  { \
      aware_t _; \
      bl_t error; \
      st_s msg; \
  }; \
  void opal_eval_frame_result_s_resolve( opal_eval_frame_result_s* o );
#define TYPEOF_opal_eval_frame_param_s 0x6C3E8DE6385E6B3Cull
#define BETH_EXPAND_ITEM_opal_eval_frame_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_param_s ) \
  { \
      aware_t _; \
      bcore_sink* log; \
      sz_t verbosity; \
      u3_t rval; \
      st_s name; \
      bcore_inst* src; \
      bhvm_holor_adl_s* in; \
      bhvm_holor_adl_s* out; \
      bl_t recovery_test; \
      bl_t jacobian_test; \
      f3_t max_dev; \
      f3_t epsilon; \
  }; \
  static inline void opal_eval_frame_param_s_init_x( opal_eval_frame_param_s* o ); \
  void opal_eval_frame_param_s_set( opal_eval_frame_param_s* o, const opal_eval_frame_param_s* src ); \
  static inline void opal_eval_frame_param_s_init_x( opal_eval_frame_param_s* o ){ o->log = bcore_fork( BCORE_STDOUT );}
#define TYPEOF_opal_eval_frame_show_param_s 0x4D82F0C5D0D28C18ull
#define BETH_EXPAND_ITEM_opal_eval_frame_show_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_show_param_s ) \
  { \
      aware_t _; \
      opal_eval_frame_param_s param; \
  }; \
  static inline void opal_eval_frame_show_param_s_set_param( opal_eval_frame_show_param_s* o, const opal_eval_frame_param_s* param ); \
  er_t opal_eval_frame_show_param_s_main( opal_eval_frame_show_param_s* o, bcore_main_frame_s* frame ); \
  static inline opal_eval_frame_result_s* opal_eval_frame_show_param_s_run( const opal_eval_frame_show_param_s* o, opal_eval_frame_result_s* result ); \
  static inline void opal_eval_frame_show_param_s_set_param( opal_eval_frame_show_param_s* o, const opal_eval_frame_param_s* param ){ opal_eval_frame_param_s_set(&(o->param),param );} \
  static inline opal_eval_frame_result_s* opal_eval_frame_show_param_s_run( const opal_eval_frame_show_param_s* o, opal_eval_frame_result_s* result ){ bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return  result;}
#define TYPEOF_opal_eval_frame_arr_s 0xA8EB91B9450EB892ull
#define BETH_EXPAND_ITEM_opal_eval_frame_arr_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_arr_s ) \
  { \
      aware_t _; \
      BCORE_ARRAY_DYN_LINK_STATIC_S( opal_eval_frame, ); \
  }; \
  static inline opal_eval_frame_arr_s* opal_eval_frame_arr_s_set_space( opal_eval_frame_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_opal_eval_frame_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_eval_frame_arr_s* opal_eval_frame_arr_s_set_size( opal_eval_frame_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_opal_eval_frame_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline opal_eval_frame_arr_s* opal_eval_frame_arr_s_clear( opal_eval_frame_arr_s* o ) { bcore_array_t_set_space( TYPEOF_opal_eval_frame_arr_s, ( bcore_array* )o, 0 ); return o; } \
  static inline opal_eval_frame* opal_eval_frame_arr_s_push_c( opal_eval_frame_arr_s* o, const opal_eval_frame* v ) { bcore_array_t_push( TYPEOF_opal_eval_frame_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_eval_frame* opal_eval_frame_arr_s_push_d( opal_eval_frame_arr_s* o,       opal_eval_frame* v ) { bcore_array_t_push( TYPEOF_opal_eval_frame_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline opal_eval_frame* opal_eval_frame_arr_s_push_t( opal_eval_frame_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_opal_eval_frame, t ); \
      bcore_array_t_push( TYPEOF_opal_eval_frame_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_opal_eval_frame_set_s 0xABCBF62F43117B75ull
#define BETH_EXPAND_ITEM_opal_eval_frame_set_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_set_s ) \
  { \
      aware_t _; \
      opal_eval_frame_param_s param; \
      opal_eval_frame_arr_s arr; \
  }; \
  static inline void opal_eval_frame_set_s_set_param( opal_eval_frame_set_s* o, const opal_eval_frame_param_s* param ); \
  er_t opal_eval_frame_set_s_main( opal_eval_frame_set_s* o, bcore_main_frame_s* frame ); \
  opal_eval_frame_result_s* opal_eval_frame_set_s_run( const opal_eval_frame_set_s* o, opal_eval_frame_result_s* result ); \
  static inline void opal_eval_frame_set_s_set_param( opal_eval_frame_set_s* o, const opal_eval_frame_param_s* param ){ opal_eval_frame_param_s_set(&(o->param),param );}
#define TYPEOF_opal_eval_frame_plain_s 0x9FB160FC03FA1C31ull
#define BETH_EXPAND_ITEM_opal_eval_frame_plain_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_plain_s ) \
  { \
      aware_t _; \
      opal_eval_frame_param_s param; \
      sz_t ap_cycles; \
  }; \
  static inline void opal_eval_frame_plain_s_set_param( opal_eval_frame_plain_s* o, const opal_eval_frame_param_s* param ); \
  er_t opal_eval_frame_plain_s_main( opal_eval_frame_plain_s* o, bcore_main_frame_s* frame ); \
  opal_eval_frame_result_s* opal_eval_frame_plain_s_run( const opal_eval_frame_plain_s* o, opal_eval_frame_result_s* result ); \
  static inline void opal_eval_frame_plain_s_set_param( opal_eval_frame_plain_s* o, const opal_eval_frame_param_s* param ){ opal_eval_frame_param_s_set(&(o->param),param );}
#define TYPEOF_opal_eval_frame_cyclic_s 0xDDE64EC20A199D3Cull
#define BETH_EXPAND_ITEM_opal_eval_frame_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_cyclic_s ) \
  { \
      aware_t _; \
      opal_eval_frame_param_s param; \
  }; \
  static inline void opal_eval_frame_cyclic_s_set_param( opal_eval_frame_cyclic_s* o, const opal_eval_frame_param_s* param ); \
  er_t opal_eval_frame_cyclic_s_main( opal_eval_frame_cyclic_s* o, bcore_main_frame_s* frame ); \
  opal_eval_frame_result_s* opal_eval_frame_cyclic_s_run( const opal_eval_frame_cyclic_s* o, opal_eval_frame_result_s* result ); \
  static inline void opal_eval_frame_cyclic_s_set_param( opal_eval_frame_cyclic_s* o, const opal_eval_frame_param_s* param ){ opal_eval_frame_param_s_set(&(o->param),param );}
#define BETH_EXPAND_GROUP_opal_eval_frame \
  BCORE_FORWARD_OBJECT( opal_eval_frame ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_result_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_param_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_show_param_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_arr_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_set_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_plain_s ); \
  BCORE_FORWARD_OBJECT( opal_eval_frame_cyclic_s ); \
  typedef opal_eval_frame_result_s* (*opal_eval_frame_run)( const opal_eval_frame* o, opal_eval_frame_result_s* result ); \
  typedef void (*opal_eval_frame_set_param)( opal_eval_frame* o, const opal_eval_frame_param_s* param ); \
  XOILA_DECLARE_SPECT( opal_eval_frame ) \
  { \
      bcore_spect_header_s header; \
      opal_eval_frame_run run; \
      opal_eval_frame_set_param set_param; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_eval_frame ) \
  BETH_EXPAND_ITEM_opal_eval_frame_result_s \
  static inline opal_eval_frame_result_s* opal_eval_frame_a_run( const opal_eval_frame* o, opal_eval_frame_result_s* result ){ const opal_eval_frame_spect_s* p = opal_eval_frame_spect_s_get_aware( o ); assert( p->run ); return p->run( o, result );} \
  static inline bl_t opal_eval_frame_a_defines_run( const opal_eval_frame* o ){ return  opal_eval_frame_spect_s_get_aware( o )->run != NULL;} \
  BETH_EXPAND_ITEM_opal_eval_frame_param_s \
  BETH_EXPAND_ITEM_opal_eval_frame_show_param_s \
  static inline void opal_eval_frame_a_set_param( opal_eval_frame* o, const opal_eval_frame_param_s* param ){ const opal_eval_frame_spect_s* p = opal_eval_frame_spect_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param );} \
  static inline bl_t opal_eval_frame_a_defines_set_param( const opal_eval_frame* o ){ return  opal_eval_frame_spect_s_get_aware( o )->set_param != NULL;} \
  BETH_EXPAND_ITEM_opal_eval_frame_arr_s \
  BETH_EXPAND_ITEM_opal_eval_frame_set_s \
  BETH_EXPAND_ITEM_opal_eval_frame_plain_s \
  BETH_EXPAND_ITEM_opal_eval_frame_cyclic_s

/**********************************************************************************************************************/
// source: opal_adaptive.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_adaptive; embeds: opal_adaptive.x

#define TYPEOF_opal_adaptive 0x14329F62AB3B1A2Eull
#define TYPEOF_opal_adaptive_spect_s 0xC6C6D96C0F8CBF5Aull
#define TYPEOF_opal_adaptive_s 0x3A11CE1909CC2850ull
#define BETH_EXPAND_ITEM_opal_adaptive_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_s ) \
  { \
      aware_t _; \
      vd_t src; \
      opal_frame_s frame; \
      bhvm_holor_s holor_frame_en; \
      bhvm_holor_s holor_frame_ex; \
  }; \
  static inline bhvm_holor_s* opal_adaptive_s_get_format_en( const opal_adaptive_s* o, bhvm_holor_s* format ); \
  static inline bhvm_holor_s* opal_adaptive_s_get_format_ex( const opal_adaptive_s* o, bhvm_holor_s* format ); \
  static inline void opal_adaptive_s_axon_pass( opal_adaptive_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ); \
  static inline void opal_adaptive_s_dendrite_pass( opal_adaptive_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ); \
  static inline void opal_adaptive_s_cyclic_reset( opal_adaptive_s* o ); \
  static inline void opal_adaptive_s_rebind_holors( opal_adaptive_s* o ); \
  bhpt_adaptor_probe_s* opal_adaptive_s_get_adaptor_probe( const opal_adaptive_s* o, bhpt_adaptor_probe_s* probe ); \
  void opal_adaptive_s_status_to_sink( const opal_adaptive_s* o, sz_t verbosity, bcore_sink* sink ); \
  static inline bhvm_holor_s* opal_adaptive_s_get_format_en( const opal_adaptive_s* o, bhvm_holor_s* format ){ bhvm_holor_s_copy(format,&(o->holor_frame_en )); return  format;} \
  static inline bhvm_holor_s* opal_adaptive_s_get_format_ex( const opal_adaptive_s* o, bhvm_holor_s* format ){ bhvm_holor_s_copy(format,&(o->holor_frame_ex )); return  format;} \
  static inline void opal_adaptive_s_axon_pass( opal_adaptive_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ){ opal_frame_s_run_ap(&(o->frame),((const bhvm_holor_s**)(&(ax_en))), 1,&( ax_ex), 1 );} \
  static inline void opal_adaptive_s_dendrite_pass( opal_adaptive_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ){ opal_frame_s_run_dp(&(o->frame),((const bhvm_holor_s**)(&(ag_ex))), 1, ( ag_en ) ? &ag_en : NULL, ( ag_en ) ? 1 : 0 );} \
  static inline void opal_adaptive_s_cyclic_reset( opal_adaptive_s* o ){ opal_frame_s_cyclic_reset( &(o->frame));} \
  static inline void opal_adaptive_s_rebind_holors( opal_adaptive_s* o ){ opal_frame_s_bind_holors(&(o->frame));}
#define TYPEOF_opal_adaptive_builder_s 0xD5FB511296336B1Cull
#define BETH_EXPAND_ITEM_opal_adaptive_builder_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_builder_s ) \
  { \
      aware_t _; \
      vd_t src; \
      bhvm_holor_s holor_frame_en; \
      bhvm_holor_s holor_frame_ex; \
  }; \
  static inline void opal_adaptive_builder_s_set_format_en( opal_adaptive_builder_s* o, const bhvm_holor_s* format ); \
  static inline void opal_adaptive_builder_s_set_format_ex( opal_adaptive_builder_s* o, const bhvm_holor_s* format ); \
  bhpt_adaptive* opal_adaptive_builder_s_create_adaptive( const opal_adaptive_builder_s* o ); \
  static inline void opal_adaptive_builder_s_set_format_en( opal_adaptive_builder_s* o, const bhvm_holor_s* format ){ bhvm_holor_s_copy(&(o->holor_frame_en),format );} \
  static inline void opal_adaptive_builder_s_set_format_ex( opal_adaptive_builder_s* o, const bhvm_holor_s* format ){ bhvm_holor_s_copy(&(o->holor_frame_ex),format );}
#define TYPEOF_opal_adaptive_cyclic_s 0xC0FD71845612D3E6ull
#define BETH_EXPAND_ITEM_opal_adaptive_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_cyclic_s ) \
  { \
      aware_t _; \
      vd_t src; \
      opal_frame_cyclic_s frame; \
      bhvm_holor_s holor_frame_en; \
      bhvm_holor_s holor_frame_ex; \
      bhvm_holor_adl_s* dp_buffer; \
      bl_t dp_value; \
  }; \
  static inline bhvm_holor_s* opal_adaptive_cyclic_s_get_format_en( const opal_adaptive_cyclic_s* o, bhvm_holor_s* format ); \
  static inline bhvm_holor_s* opal_adaptive_cyclic_s_get_format_ex( const opal_adaptive_cyclic_s* o, bhvm_holor_s* format ); \
  static inline void opal_adaptive_cyclic_s_axon_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ); \
  static inline void opal_adaptive_cyclic_s_rebind_holors( opal_adaptive_cyclic_s* o ); \
  void opal_adaptive_cyclic_s_dp_buffer_create( opal_adaptive_cyclic_s* o ); \
  void opal_adaptive_cyclic_s_dp_buffer_reset( opal_adaptive_cyclic_s* o ); \
  void opal_adaptive_cyclic_s_dp_buffer_apply( opal_adaptive_cyclic_s* o ); \
  void opal_adaptive_cyclic_s_dp_buffer_apply_reset( opal_adaptive_cyclic_s* o ); \
  void opal_adaptive_cyclic_s_dendrite_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ); \
  void opal_adaptive_cyclic_s_cyclic_reset( opal_adaptive_cyclic_s* o ); \
  bhpt_adaptor_probe_s* opal_adaptive_cyclic_s_get_adaptor_probe( const opal_adaptive_cyclic_s* o, bhpt_adaptor_probe_s* probe ); \
  void opal_adaptive_cyclic_s_status_to_sink( const opal_adaptive_cyclic_s* o, sz_t verbosity, bcore_sink* sink ); \
  static inline bhvm_holor_s* opal_adaptive_cyclic_s_get_format_en( const opal_adaptive_cyclic_s* o, bhvm_holor_s* format ){ bhvm_holor_s_copy(format,&(o->holor_frame_en )); return  format;} \
  static inline bhvm_holor_s* opal_adaptive_cyclic_s_get_format_ex( const opal_adaptive_cyclic_s* o, bhvm_holor_s* format ){ bhvm_holor_s_copy(format,&(o->holor_frame_ex )); return  format;} \
  static inline void opal_adaptive_cyclic_s_axon_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ){ opal_frame_cyclic_s_run_ap(&(o->frame),((const bhvm_holor_s**)(&(ax_en))), 1,&( ax_ex), 1 );} \
  static inline void opal_adaptive_cyclic_s_rebind_holors( opal_adaptive_cyclic_s* o ){ opal_frame_cyclic_s_bind_holors(&(o->frame));}
#define TYPEOF_opal_adaptive_cyclic_builder_s 0x00AB0A725B97B216ull
#define BETH_EXPAND_ITEM_opal_adaptive_cyclic_builder_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_cyclic_builder_s ) \
  { \
      aware_t _; \
      vd_t src; \
      bhvm_holor_s holor_frame_en; \
      bhvm_holor_s holor_frame_ex; \
      sz_t unroll_size; \
  }; \
  static inline void opal_adaptive_cyclic_builder_s_set_format_en( opal_adaptive_cyclic_builder_s* o, const bhvm_holor_s* format ); \
  static inline void opal_adaptive_cyclic_builder_s_set_format_ex( opal_adaptive_cyclic_builder_s* o, const bhvm_holor_s* format ); \
  bhpt_adaptive* opal_adaptive_cyclic_builder_s_create_adaptive( const opal_adaptive_cyclic_builder_s* o ); \
  static inline void opal_adaptive_cyclic_builder_s_set_format_en( opal_adaptive_cyclic_builder_s* o, const bhvm_holor_s* format ){ bhvm_holor_s_copy(&(o->holor_frame_en),format );} \
  static inline void opal_adaptive_cyclic_builder_s_set_format_ex( opal_adaptive_cyclic_builder_s* o, const bhvm_holor_s* format ){ bhvm_holor_s_copy(&(o->holor_frame_ex),format );}
#define BETH_EXPAND_GROUP_opal_adaptive \
  BCORE_FORWARD_OBJECT( opal_adaptive ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_s ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_builder_s ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_cyclic_s ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_cyclic_builder_s ); \
  XOILA_DECLARE_SPECT( opal_adaptive ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_adaptive ) \
  BETH_EXPAND_ITEM_opal_adaptive_s \
  BETH_EXPAND_ITEM_opal_adaptive_builder_s \
  BETH_EXPAND_ITEM_opal_adaptive_cyclic_s \
  BETH_EXPAND_ITEM_opal_adaptive_cyclic_builder_s

/**********************************************************************************************************************/
// source: opal_adaptor.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_adaptor

#define TYPEOF_opal_adaptor 0xCB423D6445E8BD55ull
#define TYPEOF_opal_adaptor_spect_s 0x755FAF40E2D82231ull
#define TYPEOF_opal_adaptor_frame_s 0xD0F6530E7722F299ull
#define BETH_EXPAND_ITEM_opal_adaptor_frame_s \
  BCORE_DECLARE_OBJECT( opal_adaptor_frame_s ) \
  { \
      aware_t _; \
      vd_t src; \
      opal_frame_s* frame; \
  }; \
  static inline void opal_adaptor_frame_s_reset( opal_adaptor_frame_s* o ); \
  void opal_adaptor_frame_s_adapt( opal_adaptor_frame_s* o, const bhpt_adaptor_node_s* node ); \
  static inline void opal_adaptor_frame_s_reset( opal_adaptor_frame_s* o ){ if( o->frame ) opal_frame_s_cyclic_reset( o->frame);}
#define BETH_EXPAND_GROUP_opal_adaptor \
  BCORE_FORWARD_OBJECT( opal_adaptor ); \
  BCORE_FORWARD_OBJECT( opal_adaptor_frame_s ); \
  XOILA_DECLARE_SPECT( opal_adaptor ) \
  { \
      bcore_spect_header_s header; \
  }; \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_adaptor ) \
  BETH_EXPAND_ITEM_opal_adaptor_frame_s

/**********************************************************************************************************************/

vd_t opal_xo_signal_handler( const bcore_signal_s* o );

#endif // __opal_xo_H
// XOILA_OUT_SIGNATURE 0x44A5F484BE7E7C3Aull
