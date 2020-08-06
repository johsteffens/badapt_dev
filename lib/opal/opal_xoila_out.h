/** This file was generated from beth-plant source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-08-06T10:04:15Z
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
 *  opal_sem.h
 *  opal_net.h
 *  opal_frame.h
 *  opal_eval_frame.h
 *  opal_adaptive.h
 *  opal_adaptor.h
 *
 */

#ifndef OPAL_XOILA_OUT_H
#define OPAL_XOILA_OUT_H

#include "bcore_control.h"

//To force a rebuild of this target by the plant-compiler, reset the hash key value below to 0.
#define HKEYOF_opal_xoila_out 2787505930

#define TYPEOF_opal_xoila_out 2896734280

/**********************************************************************************************************************/
// source: opal_context.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_context

#define TYPEOF_opal_context 3099042715
#define TYPEOF_opal_context_s 434522221
#define BETH_EXPAND_GROUP_opal_context \
  BCORE_FORWARD_OBJECT( opal_context ); \
  typedef bcore_prsg* (*opal_context_get_prsg)( opal_context* o ); \
  typedef sc_t (*opal_context_nameof)( const opal_context* o, tp_t name ); \
  typedef sc_t (*opal_context_ifnameof)( const opal_context* o, tp_t name ); \
  typedef tp_t (*opal_context_typeof)( const opal_context* o, sc_t name ); \
  typedef tp_t (*opal_context_entypeof)( opal_context* o, sc_t name ); \
  BCORE_DECLARE_SPECT( opal_context ) \
  { \
      bcore_spect_header_s header; \
      opal_context_get_prsg get_prsg; \
      opal_context_nameof nameof; \
      opal_context_ifnameof ifnameof; \
      opal_context_typeof typeof; \
      opal_context_entypeof entypeof; \
  }; \
  static inline opal_context* opal_context_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_context, t ); return ( opal_context* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_context_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_context ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_context ) \
  static inline bl_t opal_context_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_context ); } \
  static inline bcore_prsg* opal_context_a_get_prsg( opal_context* o ) { const opal_context_s* p = opal_context_s_get_aware( o ); assert( p->get_prsg ); return p->get_prsg( o ); } \
  static inline bl_t opal_context_a_defines_get_prsg( const opal_context* o ) { return true; } \
  static inline bcore_prsg* opal_context_get_prsg__( opal_context* o ){OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return NULL;} \
  static inline sc_t opal_context_a_nameof( const opal_context* o, tp_t name ) { const opal_context_s* p = opal_context_s_get_aware( o ); assert( p->nameof ); return p->nameof( o, name ); } \
  static inline bl_t opal_context_a_defines_nameof( const opal_context* o ) { return true; } \
  static inline sc_t opal_context_nameof__( const opal_context* o, tp_t name ){OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return NULL;} \
  static inline sc_t opal_context_a_ifnameof( const opal_context* o, tp_t name ) { const opal_context_s* p = opal_context_s_get_aware( o ); assert( p->ifnameof ); return p->ifnameof( o, name ); } \
  static inline bl_t opal_context_a_defines_ifnameof( const opal_context* o ) { return true; } \
  static inline sc_t opal_context_ifnameof__( const opal_context* o, tp_t name ){OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return NULL;} \
  static inline tp_t opal_context_a_typeof( const opal_context* o, sc_t name ) { const opal_context_s* p = opal_context_s_get_aware( o ); assert( p->typeof ); return p->typeof( o, name ); } \
  static inline bl_t opal_context_a_defines_typeof( const opal_context* o ) { return true; } \
  static inline tp_t opal_context_typeof__( const opal_context* o, sc_t name ){OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return 0;} \
  static inline tp_t opal_context_a_entypeof( opal_context* o, sc_t name ) { const opal_context_s* p = opal_context_s_get_aware( o ); assert( p->entypeof ); return p->entypeof( o, name ); } \
  static inline bl_t opal_context_a_defines_entypeof( const opal_context* o ) { return true; } \
  static inline tp_t opal_context_entypeof__( opal_context* o, sc_t name ){OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return 0;}

/**********************************************************************************************************************/
// source: opal_holor.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_holor

#define TYPEOF_opal_holor 490103714
#define TYPEOF_opal_holor_s 703559388
#define TYPEOF_opal_holor_meta_s 3624388628
#define BETH_EXPAND_ITEM_opal_holor_meta_s \
  BCORE_DECLARE_OBJECT( opal_holor_meta_s ) \
    {aware_t _;bcore_inst* custom;bhvm_mcode_node_s* mnode;tp_t name;bcore_inst* sem_id;tp_t pclass;bl_t htp;bl_t active;}; \
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
#define TYPEOF_opal_nop_context_s 1495285475
#define BETH_EXPAND_ITEM_opal_nop_context_s \
  BCORE_DECLARE_OBJECT( opal_nop_context_s ) \
    {aware_t _;bcore_prsg* prsg;}; \
  static inline bcore_prsg* opal_nop_context_s_get_prsg( opal_nop_context_s* o ){return o->prsg;}
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
    {aware_t _;opal_holor_s* h;st_s* msg;bl_t can_settle;bl_t codable;bl_t reducible;tp_t type_vop_ap;tp_t type_vop_dp_a;tp_t type_vop_dp_b;tp_t type_vop_dp_c;vd_t attached;};
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
  static inline opal_nop* opal_nop_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_nop, t ); return ( opal_nop* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_nop_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_nop ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_nop ) \
  static inline bl_t opal_nop_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_nop ); } \
  BETH_EXPAND_ITEM_opal_nop_context_s \
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
  static inline bl_t opal_nop_a_defines_solve_node( const opal_nop* o ) { return true; } \
  void opal_nop_solve_node__( opal_nop* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ); \
  static inline bl_t opal_nop_a_is_param( const opal_nop* o ) { const opal_nop_s* p = opal_nop_s_get_aware( o ); assert( p->is_param ); return p->is_param( o ); } \
  static inline bl_t opal_nop_a_defines_is_param( const opal_nop* o ) { return true; } \
  static inline bl_t opal_nop_is_param__( const opal_nop* o ){return false;} \
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
  static inline bl_t opal_nop_ar0_param_s_is_param( const opal_nop_ar0_param_s* o ){return true;} \
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
#define TYPEOF_opal_nop_ar1_param_s 3762375216
#define BETH_EXPAND_ITEM_opal_nop_ar1_param_s \
  BCORE_DECLARE_OBJECT( opal_nop_ar1_param_s ) \
    {aware_t _;}; \
  static inline sz_t opal_nop_ar1_param_s_arity( const opal_nop_ar1_param_s* o ){return 1;} \
  static inline bl_t opal_nop_ar1_param_s_reserved( const opal_nop_ar1_param_s* o ){return true;} \
  static inline sz_t opal_nop_ar1_param_s_priority( const opal_nop_ar1_param_s* o ){return 8;} \
  bl_t opal_nop_ar1_param_s_solve( const opal_nop_ar1_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar1_param_s_settle( const opal_nop_ar1_param_s* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result );
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
  void opal_nop_ar2_cyclic_s_solve_node( opal_nop_ar2_cyclic_s* o, opal_net_node_s* node, opal_net_node_adl_s* deferred ); \
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
  bl_t opal_nop_ar2_reshape_s_solve( const opal_nop_ar2_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result ); \
  void opal_nop_ar2_reshape_s_solve_node( opal_nop_ar2_reshape_s* o, opal_net_node_s* node, opal_net_node_adl_s* deferred );
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
  er_t opal_eval_nop_generator_s_main( opal_eval_nop_generator_s* o, bcore_main_frame_s* frame );
#define TYPEOF_opal_eval_nop_show_param_s 47537560
#define BETH_EXPAND_ITEM_opal_eval_nop_show_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_show_param_s ) \
    {aware_t _;opal_eval_nop_param_s param;}; \
  static inline void opal_eval_nop_show_param_s_set_param( opal_eval_nop_show_param_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  er_t opal_eval_nop_show_param_s_main( opal_eval_nop_show_param_s* o, bcore_main_frame_s* frame ); \
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
  er_t opal_eval_nop_set_s_main( opal_eval_nop_set_s* o, bcore_main_frame_s* frame ); \
  opal_eval_nop_result_s* opal_eval_nop_set_s_run( const opal_eval_nop_set_s* o, opal_eval_nop_result_s* result );
#define TYPEOF_opal_eval_nop_ar1_s 626857419
#define BETH_EXPAND_ITEM_opal_eval_nop_ar1_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_ar1_s ) \
    {aware_t _;opal_eval_nop_param_s param;opal_context* context;}; \
  opal_eval_nop_result_s* opal_eval_nop_ar1_s_run( const opal_eval_nop_ar1_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_ar1_s_set_param( opal_eval_nop_ar1_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  er_t opal_eval_nop_ar1_s_main( opal_eval_nop_ar1_s* o, bcore_main_frame_s* frame );
#define TYPEOF_opal_eval_nop_ar2_s 3619862610
#define BETH_EXPAND_ITEM_opal_eval_nop_ar2_s \
  BCORE_DECLARE_OBJECT( opal_eval_nop_ar2_s ) \
    {aware_t _;opal_eval_nop_param_s param;opal_context* context;}; \
  opal_eval_nop_result_s* opal_eval_nop_ar2_s_run( const opal_eval_nop_ar2_s* o, opal_eval_nop_result_s* result ); \
  static inline void opal_eval_nop_ar2_s_set_param( opal_eval_nop_ar2_s* o, const opal_eval_nop_param_s* param ){opal_eval_nop_param_s_set( &o->param, param );} \
  er_t opal_eval_nop_ar2_s_main( opal_eval_nop_ar2_s* o, bcore_main_frame_s* frame );
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
// source: opal_sem.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem

#define TYPEOF_opal_sem 2402503155
#define TYPEOF_opal_sem_s 998054677
#define TYPEOF_cell 1759288501
#define TYPEOF_opal_sem_link_s 3914525542
#define BETH_EXPAND_ITEM_opal_sem_link_s \
  BCORE_DECLARE_OBJECT( opal_sem_link_s ) \
    {aware_t _;tp_t name;bl_t protected;bl_t visible;opal_sem_link_s* up;opal_sem_link_s* dn;vd_t cell;bl_t exit;}; \
  static inline tp_t opal_sem_link_s_get_name( const opal_sem_link_s* o ){return o->name;} \
  static inline void opal_sem_link_s_set_name_visible( opal_sem_link_s* o, tp_t name ){o->name = name; o->visible = true;} \
  static inline void opal_sem_link_s_set_name_invisible( opal_sem_link_s* o, tp_t name ){o->name = name; o->visible = false;} \
  static inline bl_t opal_sem_link_s_is_visible( const opal_sem_link_s* o ){return o->visible;}
#define TYPEOF_opal_sem_links_s 583018727
#define BETH_EXPAND_ITEM_opal_sem_links_s \
  BCORE_DECLARE_OBJECT( opal_sem_links_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_sem_link_s, );}; \
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
#define TYPEOF_opal_sem_body_s 4148845946
#define BETH_EXPAND_ITEM_opal_sem_body_s \
  BCORE_DECLARE_OBJECT( opal_sem_body_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_sem, );}; \
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
#define TYPEOF_opal_sem_cell_s 1449135970
#define BETH_EXPAND_ITEM_opal_sem_cell_s \
  BCORE_DECLARE_OBJECT( opal_sem_cell_s ) \
    {aware_t _;tp_t name;bl_t visible;opal_sem_links_s encs;opal_sem_links_s excs;opal_sem_body_s* body;opal_sem_cell_s* parent;opal_sem_context_s* context;sz_t priority;opal_nop* nop;bcore_source_point_s source_point;opal_sem_cell_s* wrapped_cell;}; \
  static inline tp_t opal_sem_cell_s_get_name( const opal_sem_cell_s* o ){return o->name;} \
  static inline void opal_sem_cell_s_set_name_visible( opal_sem_cell_s* o, tp_t name ){o->name = name; o->visible = true;} \
  static inline void opal_sem_cell_s_set_name_invisible( opal_sem_cell_s* o, tp_t name ){o->name = name; o->visible = false;} \
  static inline bl_t opal_sem_cell_s_is_visible( const opal_sem_cell_s* o ){return o->visible;} \
  static inline sz_t opal_sem_cell_s_get_arity( const opal_sem_cell_s* o ){return opal_sem_links_s_count_open(       &o->encs       );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_name( opal_sem_cell_s* o, tp_t name ){return opal_sem_links_s_get_link_by_name( &o->encs, name );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_exc_by_name( opal_sem_cell_s* o, tp_t name ){return opal_sem_links_s_get_link_by_name( &o->excs, name );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_open( opal_sem_cell_s* o ){return opal_sem_links_s_get_link_by_up(   &o->encs, NULL );} \
  static inline opal_sem_link_s* opal_sem_cell_s_get_enc_by_dn( opal_sem_cell_s* o, opal_sem_link_s* dn ){return opal_sem_links_s_get_link_by_dn(   &o->encs, dn   );} \
  static inline sz_t opal_sem_cell_s_get_priority( const opal_sem_cell_s* o ){return o->priority;} \
  static inline bl_t opal_sem_cell_s_is_wrapper( const opal_sem_cell_s* o ){return o->wrapped_cell != NULL && o->nop == NULL && o->body == NULL;} \
  opal_sem_cell_s* opal_sem_cell_s_get_cell_by_name( opal_sem_cell_s* o, tp_t name ); \
  opal_sem_link_s* opal_sem_cell_s_get_link_by_name( opal_sem_cell_s* o, tp_t name );
#define TYPEOF_opal_sem_stack_flag_s 2567426165
#define BETH_EXPAND_ITEM_opal_sem_stack_flag_s \
  BCORE_DECLARE_OBJECT( opal_sem_stack_flag_s ) \
    {aware_t _;};
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
  BCORE_DECLARE_SPECT( opal_sem ) \
  { \
      bcore_spect_header_s header; \
      opal_sem_get_name get_name; \
      opal_sem_is_visible is_visible; \
      opal_sem_set_name_visible set_name_visible; \
      opal_sem_set_name_invisible set_name_invisible; \
  }; \
  static inline opal_sem* opal_sem_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_sem, t ); return ( opal_sem* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_sem_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_sem ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_sem ) \
  static inline bl_t opal_sem_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_sem ); } \
  BETH_EXPAND_GROUP_opal_sem_context \
  BETH_EXPAND_GROUP_opal_sem_id \
  static inline tp_t opal_sem_a_get_name( const opal_sem* o ) { const opal_sem_s* p = opal_sem_s_get_aware( o ); assert( p->get_name ); return p->get_name( o ); } \
  static inline bl_t opal_sem_a_defines_get_name( const opal_sem* o ) { return true; } \
  static inline tp_t opal_sem_get_name__( const opal_sem* o ){return 0;} \
  static inline bl_t opal_sem_a_is_visible( const opal_sem* o ) { const opal_sem_s* p = opal_sem_s_get_aware( o ); assert( p->is_visible ); return p->is_visible( o ); } \
  static inline bl_t opal_sem_a_defines_is_visible( const opal_sem* o ) { return true; } \
  static inline bl_t opal_sem_is_visible__( const opal_sem* o ){return true;} \
  static inline void opal_sem_a_set_name_visible( opal_sem* o, tp_t name ) { const opal_sem_s* p = opal_sem_s_get_aware( o ); assert( p->set_name_visible ); p->set_name_visible( o, name ); } \
  static inline bl_t opal_sem_a_defines_set_name_visible( const opal_sem* o ) { return opal_sem_s_get_aware( o )->set_name_visible != NULL; } \
  static inline void opal_sem_a_set_name_invisible( opal_sem* o, tp_t name ) { const opal_sem_s* p = opal_sem_s_get_aware( o ); assert( p->set_name_invisible ); p->set_name_invisible( o, name ); } \
  static inline bl_t opal_sem_a_defines_set_name_invisible( const opal_sem* o ) { return opal_sem_s_get_aware( o )->set_name_invisible != NULL; } \
  BETH_EXPAND_ITEM_opal_sem_link_s \
  BETH_EXPAND_ITEM_opal_sem_links_s \
  BETH_EXPAND_ITEM_opal_sem_body_s \
  BETH_EXPAND_ITEM_opal_sem_cell_s \
  BETH_EXPAND_ITEM_opal_sem_stack_flag_s \
  BETH_EXPAND_GROUP_opal_sem_builder \
  BETH_EXPAND_GROUP_opal_sem_tree

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_context

#define TYPEOF_opal_sem_context 3027567559
#define TYPEOF_opal_sem_context_s 1373951201
#define TYPEOF_opal_sem_context_s 1373951201
#define BETH_EXPAND_ITEM_opal_sem_context_s \
  BCORE_DECLARE_OBJECT( opal_sem_context_s ) \
    {aware_t _;opal_nop_context_s nop_context;bcore_hmap_name_s hmap_name;bcore_arr_st_s arr_symbol_op2;bcore_hmap_tp_s control_types;bcore_hmap_tp_s reserved_names;}; \
  static inline bcore_prsg* opal_sem_context_s_get_prsg( opal_sem_context_s* o ){return opal_nop_context_s_get_prsg( &o->nop_context );} \
  void opal_sem_context_s_setup( opal_sem_context_s* o, opal_sem_cell_s* frame ); \
  static inline sc_t opal_sem_context_s_nameof( const opal_sem_context_s* o, tp_t name ){return bcore_hmap_name_s_get_sc( &o->hmap_name, name );} \
  static inline sc_t opal_sem_context_s_ifnameof( const opal_sem_context_s* o, tp_t name ){sc_t sc = opal_sem_context_s_nameof( o, name ); return sc ? sc : "";} \
  static inline tp_t opal_sem_context_s_typeof( const opal_sem_context_s* o, sc_t name ){return btypeof( name );} \
  static inline tp_t opal_sem_context_s_entypeof( opal_sem_context_s* o, sc_t name ){return bcore_hmap_name_s_set_sc( &o->hmap_name, name );} \
  opal_sem_cell_s* opal_sem_context_s_setup_cell( opal_sem_context_s* o, opal_sem_cell_s* cell ); \
  opal_sem_cell_s* opal_sem_context_s_create_cell( opal_sem_context_s* o );
#define BETH_EXPAND_GROUP_opal_sem_context \
  BCORE_FORWARD_OBJECT( opal_sem_context ); \
  BCORE_FORWARD_OBJECT( opal_sem_context_s ); \
  BETH_EXPAND_ITEM_opal_sem_context_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_id

#define TYPEOF_opal_sem_id 450404681
#define TYPEOF_opal_sem_id_s 4106934275
#define TYPEOF_opal_sem_id_s 4106934275
#define BETH_EXPAND_ITEM_opal_sem_id_s \
  BCORE_DECLARE_OBJECT( opal_sem_id_s ) \
    {aware_t _;bcore_arr_tp_s arr_tp;}; \
  static inline void opal_sem_id_s_clear( opal_sem_id_s* o ){bcore_arr_tp_s_clear( &o->arr_tp );} \
  static inline void opal_sem_id_s_set( opal_sem_id_s* o, tp_t tp ){bcore_arr_tp_s_clear( &o->arr_tp ); bcore_arr_tp_s_push( &o->arr_tp, tp );} \
  static inline void opal_sem_id_s_push_child( opal_sem_id_s* o, tp_t tp ){bcore_arr_tp_s_push( &o->arr_tp, tp );} \
  static inline void opal_sem_id_s_push_parent( opal_sem_id_s* o, tp_t tp ){bcore_arr_tp_s_push_left( &o->arr_tp, tp );} \
  void opal_sem_id_s_to_string( const opal_sem_id_s* o, const opal_context* context, st_s* s );
#define BETH_EXPAND_GROUP_opal_sem_id \
  BCORE_FORWARD_OBJECT( opal_sem_id ); \
  BCORE_FORWARD_OBJECT( opal_sem_id_s ); \
  BETH_EXPAND_ITEM_opal_sem_id_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_builder

#define TYPEOF_opal_sem_builder 1308999267
#define TYPEOF_opal_sem_builder_s 3027956485
#define TYPEOF_opal_sem_builder_s 3027956485
#define BETH_EXPAND_ITEM_opal_sem_builder_s \
  BCORE_DECLARE_OBJECT( opal_sem_builder_s ) \
    {aware_t _;opal_sem_context_s* context;opal_sem_cell_s* cell_context;opal_sem_cell_s* cell_frame;}; \
  er_t opal_sem_builder_s_build_from_source( opal_sem_builder_s* o, opal_sem_cell_s* cell, bcore_source* source );
#define BETH_EXPAND_GROUP_opal_sem_builder \
  BCORE_FORWARD_OBJECT( opal_sem_builder ); \
  BCORE_FORWARD_OBJECT( opal_sem_builder_s ); \
  BETH_EXPAND_ITEM_opal_sem_builder_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_tree

#define TYPEOF_opal_sem_tree 2010001972
#define TYPEOF_opal_sem_tree_s 1064238374
#define TYPEOF_opal_sem_tree_node_s 1291463251
#define BETH_EXPAND_ITEM_opal_sem_tree_node_s \
  BCORE_DECLARE_OBJECT( opal_sem_tree_node_s ) \
    {aware_t _;sz_t id;opal_sem_cell_s* cell;opal_sem_tree_node_s* parent;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_sem_tree_node_s, );}; \
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
#define TYPEOF_opal_sem_tree_s 1064238374
#define BETH_EXPAND_ITEM_opal_sem_tree_s \
  BCORE_DECLARE_OBJECT( opal_sem_tree_s ) \
    {aware_t _;sz_t id_base;opal_sem_tree_node_s* root;}; \
  er_t opal_sem_tree_s_enter( opal_sem_tree_s* o, opal_sem_cell_s* cell, opal_sem_tree_node_s* node_in, opal_sem_tree_node_s** node_out ); \
  er_t opal_sem_tree_s_exit( opal_sem_tree_s* o, opal_sem_cell_s* cell, bl_t test_for_wrapper, opal_sem_tree_node_s* node_in, opal_sem_tree_node_s** node_out );
#define BETH_EXPAND_GROUP_opal_sem_tree \
  BCORE_FORWARD_OBJECT( opal_sem_tree ); \
  BCORE_FORWARD_OBJECT( opal_sem_tree_node_s ); \
  BCORE_FORWARD_OBJECT( opal_sem_tree_s ); \
  BETH_EXPAND_ITEM_opal_sem_tree_node_s \
  BETH_EXPAND_ITEM_opal_sem_tree_s

/**********************************************************************************************************************/
// source: opal_net.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_net

#define TYPEOF_opal_net 2850742067
#define TYPEOF_opal_net_s 3651653717
#define TYPEOF_opal_net_link_s 1463367078
#define BETH_EXPAND_ITEM_opal_net_link_s \
  BCORE_DECLARE_OBJECT( opal_net_link_s ) \
    {aware_t _;vd_t node;};
#define TYPEOF_opal_net_links_s 3829809703
#define BETH_EXPAND_ITEM_opal_net_links_s \
  BCORE_DECLARE_OBJECT( opal_net_links_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_net_link_s, );}; \
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
#define TYPEOF_opal_net_node_s 3101198586
#define BETH_EXPAND_ITEM_opal_net_node_s \
  BCORE_DECLARE_OBJECT( opal_net_node_s ) \
    {aware_t _;opal_net_links_s upls;opal_net_links_s dnls;tp_t name;opal_sem_id_s* sem_id;bl_t flag;bl_t probe;sz_t id;bhvm_mcode_node_s* mnode;opal_nop* nop;opal_nop_solve_result_s* result;opal_context* context;bcore_source_point_s* source_point;}; \
  sz_t opal_net_node_s_up_index( const opal_net_node_s* o, const opal_net_node_s* node ); \
  void opal_net_node_s_set_nop_d( opal_net_node_s* o, opal_nop* nop ); \
  static inline bl_t opal_net_node_s_is_cyclic( const opal_net_node_s* o ){return ( o->mnode ) ? o->mnode->cyclic : opal_nop_a_is_cyclic( o->nop );}
#define TYPEOF_opal_net_node_adl_s 2025295350
#define BETH_EXPAND_ITEM_opal_net_node_adl_s \
  BCORE_DECLARE_OBJECT( opal_net_node_adl_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_net_node_s, );}; \
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
#define TYPEOF_opal_net_nodes_s 3175198307
#define BETH_EXPAND_ITEM_opal_net_nodes_s \
  BCORE_DECLARE_OBJECT( opal_net_nodes_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_net_node_s, );}; \
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
#define TYPEOF_opal_net_cell_s 2933494946
#define BETH_EXPAND_ITEM_opal_net_cell_s \
  BCORE_DECLARE_OBJECT( opal_net_cell_s ) \
    {aware_t _;sz_t max_depth;opal_net_nodes_s body;opal_net_nodes_s encs;opal_net_nodes_s excs;opal_context* context;}; \
  bl_t opal_net_cell_s_is_consistent( const opal_net_cell_s* o ); \
  void opal_net_cell_s_normalize( opal_net_cell_s* o ); \
  void opal_net_cell_s_clear_flags( opal_net_cell_s* o ); \
  void opal_net_cell_s_clear_all_flags( opal_net_cell_s* o ); \
  void opal_net_cell_s_solve( opal_net_cell_s* o ); \
  void opal_net_cell_s_clear_downlinks( opal_net_cell_s* o ); \
  void opal_net_cell_s_set_downlinks( opal_net_cell_s* o ); \
  void opal_net_cell_s_copy_x( opal_net_cell_s* o ); \
  static inline void opal_net_cell_s_mutated( opal_net_cell_s* o ){ERR_fa( "Cannot reconstitute." );}
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
  BCORE_DECLARE_SPECT( opal_net ) \
  { \
      bcore_spect_header_s header; \
      opal_net_is_cyclic is_cyclic; \
  }; \
  static inline opal_net* opal_net_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_net, t ); return ( opal_net* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_net_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_net ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_net ) \
  static inline bl_t opal_net_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_net ); } \
  BETH_EXPAND_ITEM_opal_net_link_s \
  BETH_EXPAND_ITEM_opal_net_links_s \
  static inline bl_t opal_net_a_is_cyclic( const opal_net* o ) { const opal_net_s* p = opal_net_s_get_aware( o ); assert( p->is_cyclic ); return p->is_cyclic( o ); } \
  static inline bl_t opal_net_a_defines_is_cyclic( const opal_net* o ) { return true; } \
  static inline bl_t opal_net_is_cyclic__( const opal_net* o ){return false;} \
  BETH_EXPAND_ITEM_opal_net_node_s \
  BETH_EXPAND_ITEM_opal_net_node_adl_s \
  BETH_EXPAND_ITEM_opal_net_nodes_s \
  BETH_EXPAND_ITEM_opal_net_cell_s \
  BETH_EXPAND_GROUP_opal_net_builder

//----------------------------------------------------------------------------------------------------------------------
// group: opal_net_builder

#define TYPEOF_opal_net_builder 685280419
#define TYPEOF_opal_net_builder_s 2298087749
#define TYPEOF_opal_net_builder_s 2298087749
#define BETH_EXPAND_ITEM_opal_net_builder_s \
  BCORE_DECLARE_OBJECT( opal_net_builder_s ) \
    {aware_t _;opal_sem_builder_s sem_builder;bhvm_holor_adl_s input_holors;bcore_sink* log;}; \
  static inline void opal_net_builder_s_fork_log( opal_net_builder_s* o, bcore_sink* log ){bcore_sink_a_attach( &o->log, bcore_fork( log ) );} \
  void opal_net_builder_s_fork_input_holors( opal_net_builder_s* o, const bhvm_holor_s** input_holors, sz_t size_input_holors ); \
  void opal_net_builder_s_build_from_source( opal_net_builder_s* o, opal_net_cell_s* net_cell, bcore_source* source );
#define BETH_EXPAND_GROUP_opal_net_builder \
  BCORE_FORWARD_OBJECT( opal_net_builder ); \
  BCORE_FORWARD_OBJECT( opal_net_builder_s ); \
  BETH_EXPAND_ITEM_opal_net_builder_s

/**********************************************************************************************************************/
// source: opal_frame.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_frame

#define TYPEOF_opal_frame 2303180117
#define TYPEOF_opal_frame_s 2207737015
#define TYPEOF_opal_frame_s 2207737015
#define BETH_EXPAND_ITEM_opal_frame_s \
  BCORE_DECLARE_OBJECT( opal_frame_s ) \
    {aware_t _;bcore_sink* log;opal_context* context;bhvm_mcode_frame_s* mcf;bl_t is_cyclic;bl_t setup;sz_t size_en;sz_t size_ex;opal_frame_hidx_s hidx_en;opal_frame_hidx_s hidx_ex;opal_frame_hidx_s hidx_ada;}; \
  void opal_frame_s_reset( opal_frame_s* o ); \
  opal_frame_s* opal_frame_s_bind_holors( opal_frame_s* o ); \
  void opal_frame_s_setup( opal_frame_s* o ); \
  void opal_frame_s_check_integrity( const opal_frame_s* o ); \
  static inline void opal_frame_s_shelve( opal_frame_s* o ){bl_t setup = o->setup; opal_frame_s_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */} \
  static inline void opal_frame_s_mutated( opal_frame_s* o ){if( o->setup ) { opal_frame_s_reset( o ); opal_frame_s_setup( o ); }  opal_frame_s_check_integrity( o );} \
  static inline void opal_frame_s_copy_x( opal_frame_s* o ){if( o->setup ) { opal_frame_s_reset( o ); opal_frame_s_setup( o ); }  opal_frame_s_check_integrity( o );} \
  opal_frame_s* opal_frame_s_setup_from_source( opal_frame_s* o, bcore_source* source, const bhvm_holor_s** en, sz_t size_en ); \
  static inline opal_frame_s* opal_frame_s_setup_from_st( opal_frame_s* o, const st_s* st, const bhvm_holor_s** en, sz_t size_en ){BLM_INIT(); BLM_RETURNV( opal_frame_s*, opal_frame_s_setup_from_source( o, BLM_A_PUSH( bcore_source_string_s_create_from_string( st ) ), en, size_en ) );} \
  static inline opal_frame_s* opal_frame_s_setup_from_sc( opal_frame_s* o, sc_t sc, const bhvm_holor_s** en, sz_t size_en ){st_s st; st_s_init_weak_sc( &st, sc ); return opal_frame_s_setup_from_st( o, &st, en, size_en );} \
  static inline opal_frame_s* opal_frame_s_create_from_source( bcore_source* source, const bhvm_holor_s** en, sz_t size_en ){opal_frame_s* o = opal_frame_s_create(); return opal_frame_s_setup_from_source( o, source, en, size_en );} \
  static inline opal_frame_s* opal_frame_s_create_from_st( const st_s* st, const bhvm_holor_s** en, sz_t size_en ){opal_frame_s* o = opal_frame_s_create(); return opal_frame_s_setup_from_st(     o, st,     en, size_en );} \
  static inline opal_frame_s* opal_frame_s_create_from_sc( sc_t sc, const bhvm_holor_s** en, sz_t size_en ){opal_frame_s* o = opal_frame_s_create(); return opal_frame_s_setup_from_sc(     o, sc,     en, size_en );} \
  static inline opal_frame_s* opal_frame_s_setup_from_source_adl( opal_frame_s* o, bcore_source* source, const bhvm_holor_adl_s* en ){return opal_frame_s_setup_from_source( o, source, en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_setup_from_st_adl( opal_frame_s* o, const st_s* st, const bhvm_holor_adl_s* en ){return opal_frame_s_setup_from_st(     o, st,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_setup_from_sc_adl( opal_frame_s* o, sc_t sc, const bhvm_holor_adl_s* en ){return opal_frame_s_setup_from_sc(     o, sc,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_create_from_source_adl( bcore_source* source, const bhvm_holor_adl_s* en ){return opal_frame_s_create_from_source( source,   en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_create_from_st_adl( const st_s* st, const bhvm_holor_adl_s* en ){return opal_frame_s_create_from_st( st,           en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline opal_frame_s* opal_frame_s_create_from_sc_adl( sc_t sc, const bhvm_holor_adl_s* en ){return opal_frame_s_create_from_sc( sc,           en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline sz_t opal_frame_s_get_size_en( const opal_frame_s* o ){return opal_frame_hidx_s_get_size( &o->hidx_en );} \
  static inline sz_t opal_frame_s_get_size_ex( const opal_frame_s* o ){return opal_frame_hidx_s_get_size( &o->hidx_ex );} \
  static inline sz_t opal_frame_s_get_size_ada( const opal_frame_s* o ){return opal_frame_hidx_s_get_size( &o->hidx_ada );} \
  static inline bhvm_holor_s* opal_frame_s_get_ap_en( opal_frame_s* o, sz_t index ){return opal_frame_hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_dp_en( opal_frame_s* o, sz_t index ){return opal_frame_hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_ap_ex( opal_frame_s* o, sz_t index ){return opal_frame_hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_dp_ex( opal_frame_s* o, sz_t index ){return opal_frame_hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_ap_ada( opal_frame_s* o, sz_t index ){return opal_frame_hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* opal_frame_s_get_dp_ada( opal_frame_s* o, sz_t index ){return opal_frame_hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  opal_frame_s* opal_frame_s_run_ap( opal_frame_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex ); \
  opal_frame_s* opal_frame_s_run_dp( opal_frame_s* o, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en ); \
  opal_frame_s* opal_frame_s_run_ap_adl( opal_frame_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex ); \
  opal_frame_s* opal_frame_s_run_dp_adl( opal_frame_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en );
#define TYPEOF_opal_frame_custom_hmeta_s 2503994969
#define BETH_EXPAND_ITEM_opal_frame_custom_hmeta_s \
  BCORE_DECLARE_OBJECT( opal_frame_custom_hmeta_s ) \
    {aware_t _;sz_t ur_slot;sz_t ur_src;};
#define TYPEOF_opal_frame_cyclic_s 3859514071
#define BETH_EXPAND_ITEM_opal_frame_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_frame_cyclic_s ) \
    {aware_t _;opal_frame_s* frame;sz_t unroll_size;bl_t setup;sz_t unroll_index;bhvm_mcode_track_adl_s* track_adl_ap;bhvm_mcode_track_adl_s* track_adl_dp;bhvm_mcode_track_adl_s* track_adl_ap_setup;opal_frame_hidx_ads_s hidx_ads_en;opal_frame_hidx_ads_s hidx_ads_ex;}; \
  opal_frame_cyclic_s* opal_frame_cyclic_s_bind_holors( opal_frame_cyclic_s* o ); \
  void opal_frame_cyclic_s_reset( opal_frame_cyclic_s* o ); \
  void opal_frame_cyclic_s_setup( opal_frame_cyclic_s* o ); \
  static inline void opal_frame_cyclic_s_shelve( opal_frame_cyclic_s* o ){bl_t setup = o->setup; opal_frame_cyclic_s_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */} \
  static inline void opal_frame_cyclic_s_mutated( opal_frame_cyclic_s* o ){if( o->setup ) { opal_frame_cyclic_s_reset( o ); opal_frame_cyclic_s_setup( o ); }} \
  static inline void opal_frame_cyclic_s_copy_x( opal_frame_cyclic_s* o ){if( o->setup ) { opal_frame_cyclic_s_reset( o ); opal_frame_cyclic_s_setup( o ); }} \
  static inline sz_t opal_frame_cyclic_s_get_size_en( const opal_frame_cyclic_s* o ){return opal_frame_s_get_size_en(  o->frame );} \
  static inline sz_t opal_frame_cyclic_s_get_size_ex( const opal_frame_cyclic_s* o ){return opal_frame_s_get_size_ex(  o->frame );} \
  static inline sz_t opal_frame_cyclic_s_get_size_ada( const opal_frame_cyclic_s* o ){return opal_frame_s_get_size_ada( o->frame );} \
  opal_frame_cyclic_s* opal_frame_cyclic_s_run_ap( opal_frame_cyclic_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex ); \
  opal_frame_cyclic_s* opal_frame_cyclic_s_run_ap_adl( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex );
#define BETH_EXPAND_GROUP_opal_frame \
  BCORE_FORWARD_OBJECT( opal_frame ); \
  BCORE_FORWARD_OBJECT( opal_frame_hidx ); \
  BCORE_FORWARD_OBJECT( opal_frame_s ); \
  BCORE_FORWARD_OBJECT( opal_frame_custom_hmeta_s ); \
  BCORE_FORWARD_OBJECT( opal_frame_cyclic_s ); \
  BETH_EXPAND_GROUP_opal_frame_hidx \
  BETH_EXPAND_ITEM_opal_frame_s \
  BETH_EXPAND_ITEM_opal_frame_custom_hmeta_s \
  BETH_EXPAND_ITEM_opal_frame_cyclic_s

//----------------------------------------------------------------------------------------------------------------------
// group: opal_frame_hidx

#define TYPEOF_opal_frame_hidx 672256437
#define TYPEOF_opal_frame_hidx_s 472666071
#define TYPEOF_opal_frame_hidx_s 472666071
#define BETH_EXPAND_ITEM_opal_frame_hidx_s \
  BCORE_DECLARE_OBJECT( opal_frame_hidx_s ) \
    {aware_t _;bcore_arr_sz_s* arr;}; \
  static inline opal_frame_hidx_s* opal_frame_hidx_s_clear( opal_frame_hidx_s* o ){if( o->arr ) bcore_arr_sz_s_clear( o->arr ); return o;} \
  static inline opal_frame_hidx_s* opal_frame_hidx_s_push( opal_frame_hidx_s* o, sz_t index ){if( !o->arr ) o->arr = bcore_arr_sz_s_create(); bcore_arr_sz_s_push( o->arr, index ); return o;} \
  static inline sz_t opal_frame_hidx_s_get_idx( const opal_frame_hidx_s* o, sz_t index ){assert( o->arr ); assert( index >= 0 && index < o->arr->size ); return o->arr->data[ index ];} \
  static inline sz_t opal_frame_hidx_s_get_size( const opal_frame_hidx_s* o ){return o->arr ? o->arr->size : 0;} \
  static inline bhvm_holor_s* opal_frame_hidx_s_get_holor( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ){return bhvm_mcode_hbase_s_get_holor( hbase, opal_frame_hidx_s_get_idx( o, index ) );} \
  static inline bhvm_mcode_hmeta* opal_frame_hidx_s_get_hmeta( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ){return bhvm_mcode_hbase_s_get_hmeta( hbase, opal_frame_hidx_s_get_idx( o, index ) );} \
  sz_t opal_frame_hidx_s_get_pclass_idx( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ); \
  static inline bhvm_holor_s* opal_frame_hidx_s_get_pclass_holor( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ){return bhvm_mcode_hbase_s_get_holor( hbase, opal_frame_hidx_s_get_pclass_idx( o, hbase, pclass, index ) );} \
  static inline bhvm_mcode_hmeta* opal_frame_hidx_s_get_pclass_hmeta( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ){return bhvm_mcode_hbase_s_get_hmeta( hbase, opal_frame_hidx_s_get_pclass_idx( o, hbase, pclass, index ) );} \
  opal_frame_hidx_s* opal_frame_hidx_s_replace_index( opal_frame_hidx_s* o, bcore_arr_sz_s* index_map );
#define TYPEOF_opal_frame_hidx_ads_s 3521098546
#define BETH_EXPAND_ITEM_opal_frame_hidx_ads_s \
  BCORE_DECLARE_OBJECT( opal_frame_hidx_ads_s ) \
    {aware_t _;BCORE_ARRAY_DYN_SOLID_STATIC_S( opal_frame_hidx_s, );}; \
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
  BETH_EXPAND_ITEM_opal_frame_hidx_s \
  BETH_EXPAND_ITEM_opal_frame_hidx_ads_s

/**********************************************************************************************************************/
// source: opal_eval_frame.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_eval_frame

#define TYPEOF_opal_eval_frame 785128296
#define TYPEOF_opal_eval_frame_s 673046290
#define TYPEOF_opal_eval_frame_result_s 3179823334
#define BETH_EXPAND_ITEM_opal_eval_frame_result_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_result_s ) \
    {aware_t _;bl_t error;st_s msg;}; \
  void opal_eval_frame_result_s_resolve( opal_eval_frame_result_s* o );
#define TYPEOF_opal_eval_frame_param_s 2283680028
#define BETH_EXPAND_ITEM_opal_eval_frame_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_param_s ) \
    {aware_t _;bcore_sink* log;sz_t verbosity;u3_t rval;st_s name;vd_t src;bhvm_holor_adl_s* in;bhvm_holor_adl_s* out;bl_t recovery_test;bl_t jacobian_test;f3_t max_dev;f3_t epsilon;}; \
  static inline void opal_eval_frame_param_s_init_x( opal_eval_frame_param_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  void opal_eval_frame_param_s_set( opal_eval_frame_param_s* o, const opal_eval_frame_param_s* src );
#define TYPEOF_opal_eval_frame_show_param_s 2983012792
#define BETH_EXPAND_ITEM_opal_eval_frame_show_param_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_show_param_s ) \
    {aware_t _;opal_eval_frame_param_s param;}; \
  static inline void opal_eval_frame_show_param_s_set_param( opal_eval_frame_show_param_s* o, const opal_eval_frame_param_s* param ){opal_eval_frame_param_s_set( &o->param, param );} \
  er_t opal_eval_frame_show_param_s_main( opal_eval_frame_show_param_s* o, bcore_main_frame_s* frame ); \
  static inline opal_eval_frame_result_s* opal_eval_frame_show_param_s_run( const opal_eval_frame_show_param_s* o, opal_eval_frame_result_s* result ){bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result;}
#define TYPEOF_opal_eval_frame_arr_s 528657778
#define BETH_EXPAND_ITEM_opal_eval_frame_arr_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( opal_eval_frame, );}; \
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
#define TYPEOF_opal_eval_frame_set_s 1038200085
#define BETH_EXPAND_ITEM_opal_eval_frame_set_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_set_s ) \
    {aware_t _;opal_eval_frame_param_s param;opal_eval_frame_arr_s arr;}; \
  static inline void opal_eval_frame_set_s_set_param( opal_eval_frame_set_s* o, const opal_eval_frame_param_s* param ){opal_eval_frame_param_s_set( &o->param, param );} \
  er_t opal_eval_frame_set_s_main( opal_eval_frame_set_s* o, bcore_main_frame_s* frame ); \
  opal_eval_frame_result_s* opal_eval_frame_set_s_run( const opal_eval_frame_set_s* o, opal_eval_frame_result_s* result );
#define TYPEOF_opal_eval_frame_plain_s 3361958737
#define BETH_EXPAND_ITEM_opal_eval_frame_plain_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_plain_s ) \
    {aware_t _;opal_eval_frame_param_s param;sz_t ap_cycles;}; \
  opal_eval_frame_result_s* opal_eval_frame_plain_s_run( const opal_eval_frame_plain_s* o, opal_eval_frame_result_s* result ); \
  static inline void opal_eval_frame_plain_s_set_param( opal_eval_frame_plain_s* o, const opal_eval_frame_param_s* param ){opal_eval_frame_param_s_set( &o->param, param );} \
  er_t opal_eval_frame_plain_s_main( opal_eval_frame_plain_s* o, bcore_main_frame_s* frame );
#define TYPEOF_opal_eval_frame_cyclic_s 1180851996
#define BETH_EXPAND_ITEM_opal_eval_frame_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_eval_frame_cyclic_s ) \
    {aware_t _;opal_eval_frame_param_s param;}; \
  opal_eval_frame_result_s* opal_eval_frame_cyclic_s_run( const opal_eval_frame_cyclic_s* o, opal_eval_frame_result_s* result ); \
  static inline void opal_eval_frame_cyclic_s_set_param( opal_eval_frame_cyclic_s* o, const opal_eval_frame_param_s* param ){opal_eval_frame_param_s_set( &o->param, param );} \
  er_t opal_eval_frame_cyclic_s_main( opal_eval_frame_cyclic_s* o, bcore_main_frame_s* frame );
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
  BCORE_DECLARE_SPECT( opal_eval_frame ) \
  { \
      bcore_spect_header_s header; \
      opal_eval_frame_run run; \
      opal_eval_frame_set_param set_param; \
  }; \
  static inline opal_eval_frame* opal_eval_frame_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_opal_eval_frame, t ); return ( opal_eval_frame* )bcore_inst_t_create( t ); } \
  static inline bl_t opal_eval_frame_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_opal_eval_frame ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( opal_eval_frame ) \
  static inline bl_t opal_eval_frame_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_opal_eval_frame ); } \
  BETH_EXPAND_ITEM_opal_eval_frame_result_s \
  static inline opal_eval_frame_result_s* opal_eval_frame_a_run( const opal_eval_frame* o, opal_eval_frame_result_s* result ) { const opal_eval_frame_s* p = opal_eval_frame_s_get_aware( o ); assert( p->run ); return p->run( o, result ); } \
  static inline bl_t opal_eval_frame_a_defines_run( const opal_eval_frame* o ) { return opal_eval_frame_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_opal_eval_frame_param_s \
  BETH_EXPAND_ITEM_opal_eval_frame_show_param_s \
  static inline void opal_eval_frame_a_set_param( opal_eval_frame* o, const opal_eval_frame_param_s* param ) { const opal_eval_frame_s* p = opal_eval_frame_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param ); } \
  static inline bl_t opal_eval_frame_a_defines_set_param( const opal_eval_frame* o ) { return opal_eval_frame_s_get_aware( o )->set_param != NULL; } \
  BETH_EXPAND_ITEM_opal_eval_frame_arr_s \
  BETH_EXPAND_ITEM_opal_eval_frame_set_s \
  BETH_EXPAND_ITEM_opal_eval_frame_plain_s \
  BETH_EXPAND_ITEM_opal_eval_frame_cyclic_s

/**********************************************************************************************************************/
// source: opal_adaptive.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_adaptive

#define TYPEOF_opal_adaptive 1058255374
#define TYPEOF_opal_adaptive_s 431057104
#define TYPEOF_opal_adaptive_s 431057104
#define BETH_EXPAND_ITEM_opal_adaptive_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_s ) \
    {aware_t _;vd_t src;opal_frame_s frame;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;}; \
  static inline bhvm_holor_s* opal_adaptive_s_get_format_en( const opal_adaptive_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_en ); return format;} \
  static inline bhvm_holor_s* opal_adaptive_s_get_format_ex( const opal_adaptive_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_ex ); return format;} \
  void opal_adaptive_s_axon_pass( opal_adaptive_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ); \
  void opal_adaptive_s_dendrite_pass( opal_adaptive_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ); \
  void opal_adaptive_s_cyclic_reset( opal_adaptive_s* o ); \
  bhpt_adaptor_probe_s* opal_adaptive_s_get_adaptor_probe( const opal_adaptive_s* o, bhpt_adaptor_probe_s* probe ); \
  static inline void opal_adaptive_s_rebind_holors( opal_adaptive_s* o ){opal_frame_s_bind_holors( &o->frame );} \
  void opal_adaptive_s_status_to_sink( const opal_adaptive_s* o, sz_t verbosity, bcore_sink* sink );
#define TYPEOF_opal_adaptive_builder_s 3443060476
#define BETH_EXPAND_ITEM_opal_adaptive_builder_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_builder_s ) \
    {aware_t _;vd_t src;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;}; \
  static inline void opal_adaptive_builder_s_set_format_en( opal_adaptive_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_en, format );} \
  static inline void opal_adaptive_builder_s_set_format_ex( opal_adaptive_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_ex, format );} \
  bhpt_adaptive* opal_adaptive_builder_s_create_adaptive( const opal_adaptive_builder_s* o );
#define TYPEOF_opal_adaptive_cyclic_s 3324695814
#define BETH_EXPAND_ITEM_opal_adaptive_cyclic_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_cyclic_s ) \
    {aware_t _;vd_t src;opal_frame_cyclic_s frame;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;bhvm_holor_adl_s* dp_buffer;bl_t dp_value;}; \
  static inline bhvm_holor_s* opal_adaptive_cyclic_s_get_format_en( const opal_adaptive_cyclic_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_en ); return format;} \
  static inline bhvm_holor_s* opal_adaptive_cyclic_s_get_format_ex( const opal_adaptive_cyclic_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_ex ); return format;} \
  void opal_adaptive_cyclic_s_axon_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ); \
  void opal_adaptive_cyclic_s_dendrite_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ); \
  void opal_adaptive_cyclic_s_cyclic_reset( opal_adaptive_cyclic_s* o ); \
  bhpt_adaptor_probe_s* opal_adaptive_cyclic_s_get_adaptor_probe( const opal_adaptive_cyclic_s* o, bhpt_adaptor_probe_s* probe ); \
  static inline void opal_adaptive_cyclic_s_rebind_holors( opal_adaptive_cyclic_s* o ){opal_frame_cyclic_s_bind_holors( &o->frame );} \
  void opal_adaptive_cyclic_s_status_to_sink( const opal_adaptive_cyclic_s* o, sz_t verbosity, bcore_sink* sink );
#define TYPEOF_opal_adaptive_cyclic_builder_s 649113942
#define BETH_EXPAND_ITEM_opal_adaptive_cyclic_builder_s \
  BCORE_DECLARE_OBJECT( opal_adaptive_cyclic_builder_s ) \
    {aware_t _;vd_t src;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;sz_t unroll_size;}; \
  static inline void opal_adaptive_cyclic_builder_s_set_format_en( opal_adaptive_cyclic_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_en, format );} \
  static inline void opal_adaptive_cyclic_builder_s_set_format_ex( opal_adaptive_cyclic_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_ex, format );} \
  bhpt_adaptive* opal_adaptive_cyclic_builder_s_create_adaptive( const opal_adaptive_cyclic_builder_s* o );
#define BETH_EXPAND_GROUP_opal_adaptive \
  BCORE_FORWARD_OBJECT( opal_adaptive ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_s ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_builder_s ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_cyclic_s ); \
  BCORE_FORWARD_OBJECT( opal_adaptive_cyclic_builder_s ); \
  BETH_EXPAND_ITEM_opal_adaptive_s \
  BETH_EXPAND_ITEM_opal_adaptive_builder_s \
  BETH_EXPAND_ITEM_opal_adaptive_cyclic_s \
  BETH_EXPAND_ITEM_opal_adaptive_cyclic_builder_s

/**********************************************************************************************************************/
// source: opal_adaptor.h

//----------------------------------------------------------------------------------------------------------------------
// group: opal_adaptor

#define TYPEOF_opal_adaptor 3603928821
#define TYPEOF_opal_adaptor_s 3242609687
#define TYPEOF_opal_adaptor_frame_s 842723161
#define BETH_EXPAND_ITEM_opal_adaptor_frame_s \
  BCORE_DECLARE_OBJECT( opal_adaptor_frame_s ) \
    {aware_t _;vd_t src;opal_frame_s* frame;}; \
  static inline void opal_adaptor_frame_s_reset( opal_adaptor_frame_s* o ){if( o->frame ) opal_frame_s_cyclic_reset( o->frame );} \
  void opal_adaptor_frame_s_adapt( opal_adaptor_frame_s* o, const bhpt_adaptor_node_s* node );
#define BETH_EXPAND_GROUP_opal_adaptor \
  BCORE_FORWARD_OBJECT( opal_adaptor ); \
  BCORE_FORWARD_OBJECT( opal_adaptor_frame_s ); \
  BETH_EXPAND_ITEM_opal_adaptor_frame_s

/**********************************************************************************************************************/

vd_t opal_xoila_out_signal_handler( const bcore_signal_s* o );

#endif // OPAL_XOILA_OUT_H
// BETH_PLANT_SIGNATURE 1760672411
