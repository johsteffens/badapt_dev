/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019, 2020 J.B.Steffens
 *  Last File Update: 2020-05-07T21:41:18Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  lion_root.h
 *  lion_nop.h
 *  lion_eval_nop.h
 *  lion_sem.h
 *  lion_net.h
 *  lion_frame.h
 *  lion_eval_frame.h
 *  lion_adaptive.h
 *  lion_adaptor.h
 *  lion_adaptive_bhpt.h
 *
 */

#ifndef LION_PLANTED_H
#define LION_PLANTED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: lion_root.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion

#define TYPEOF_lion 4074679679
#define TYPEOF_lion_s 2299906281
#define TYPEOF_lion_hmeta_s 2700535167
#define BETH_EXPAND_ITEM_lion_hmeta_s \
  BCORE_DECLARE_OBJECT( lion_hmeta_s ) \
    {aware_t _;bcore_inst* custom;bhvm_mcode_node_s* mnode;tp_t name;tp_t pclass;bl_t htp;bl_t active;}; \
  static inline void lion_hmeta_s_clear( lion_hmeta_s* o ){o->name = 0; o->htp = false;} \
  static inline tp_t lion_hmeta_s_get_name( const lion_hmeta_s* o ){return o->name;} \
  static inline tp_t lion_hmeta_s_get_pclass( const lion_hmeta_s* o ){return o->pclass;} \
  static inline bl_t lion_hmeta_s_is_rollable( const lion_hmeta_s* o ){return !o->active || o->mnode->adaptive || ( o->mnode->cyclic && o->pclass == TYPEOF_pclass_ax1 );} \
  static inline bl_t lion_hmeta_s_is_active( const lion_hmeta_s* o ){return  o->active;} \
  static inline bcore_inst* lion_hmeta_s_get_custom( const lion_hmeta_s* o ){return o->custom;} \
  static inline bcore_inst* lion_hmeta_s_set_custom( lion_hmeta_s* o, const bcore_inst* custom ){bcore_inst_a_attach( &o->custom, bcore_inst_a_clone( custom ) ); return o->custom;} \
  static inline bhvm_mcode_node_s* lion_hmeta_s_get_node( const lion_hmeta_s* o ){return o->mnode;} \
  static inline void lion_hmeta_s_set_node( lion_hmeta_s* o, bhvm_mcode_node_s* node ){bhvm_mcode_node_s_attach( &o->mnode, bcore_fork( node ) );}
#define TYPEOF_lion_holor_s 3848175284
#define BETH_EXPAND_ITEM_lion_holor_s \
  BCORE_DECLARE_OBJECT( lion_holor_s ) \
    {aware_t _;lion_hmeta_s m;bhvm_holor_s h;}; \
  void lion_holor_s_copy_typed( lion_holor_s* o, tp_t type, vc_t src );
#define BETH_EXPAND_GROUP_lion \
  BCORE_FORWARD_OBJECT( lion ); \
  BCORE_FORWARD_OBJECT( lion_hmeta_s ); \
  BCORE_FORWARD_OBJECT( lion_holor_s ); \
  BETH_EXPAND_ITEM_lion_hmeta_s \
  BETH_EXPAND_ITEM_lion_holor_s

/**********************************************************************************************************************/
// source: lion_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop

#define TYPEOF_lion_nop 2615133213
#define TYPEOF_lion_nop_s 2513597327
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
#define TYPEOF_lion_nop_solve_result_s 490117549
#define BETH_EXPAND_ITEM_lion_nop_solve_result_s \
  BCORE_DECLARE_OBJECT( lion_nop_solve_result_s ) \
    {aware_t _;lion_holor_s* h;st_s* msg;bl_t settled;bl_t codable;bl_t reducible;tp_t type_vop_ap;tp_t type_vop_dp_a;tp_t type_vop_dp_b;tp_t type_vop_dp_c;vd_t attached;};
#define TYPEOF_lion_nop_context_s 1954113275
#define BETH_EXPAND_ITEM_lion_nop_context_s \
  BCORE_DECLARE_OBJECT( lion_nop_context_s ) \
    {aware_t _;bcore_mutex_s randomizer_mutex;bl_t randomizer_is_locked;u2_t randomizer_rval;};
#define BETH_EXPAND_GROUP_lion_nop \
  BCORE_FORWARD_OBJECT( lion_nop ); \
  BCORE_FORWARD_OBJECT( lion_nop_solve_result_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_context_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar3 ); \
  typedef sz_t (*lion_nop_arity)( const lion_nop* o ); \
  typedef sz_t (*lion_nop_priority)( const lion_nop* o ); \
  typedef sc_t (*lion_nop_symbol)( const lion_nop* o ); \
  typedef bl_t (*lion_nop_reserved)( const lion_nop* o ); \
  typedef lion_nop* (*lion_nop_create_op_of_arn)( const lion_nop* o, sz_t n ); \
  typedef bl_t (*lion_nop_eci)( const lion_nop* o ); \
  typedef bl_t (*lion_nop_solve)( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  typedef void (*lion_nop_solve_node)( lion_nop* o, lion_net_node_s* node, lion_net_node_adl_s* deferred ); \
  typedef bl_t (*lion_nop_is_cyclic)( const lion_nop* o ); \
  typedef bl_t (*lion_nop_is_adaptive)( const lion_nop* o ); \
  typedef void (*lion_nop_settle)( const lion_nop* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result ); \
  typedef tp_t (*lion_nop_type_vop_ap)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_type_vop_dp_a)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_type_vop_dp_b)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_type_vop_dp_c)( const lion_nop* o ); \
  typedef sz_t (*lion_nop_mcode_push_ap_holor)( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef sz_t (*lion_nop_mcode_push_dp_holor)( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef void (*lion_nop_mcode_push_ap_track)( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef void (*lion_nop_mcode_push_dp_track)( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BCORE_DECLARE_SPECT( lion_nop ) \
  { \
      bcore_spect_header_s header; \
      lion_nop_arity arity; \
      lion_nop_priority priority; \
      lion_nop_symbol symbol; \
      lion_nop_reserved reserved; \
      lion_nop_create_op_of_arn create_op_of_arn; \
      lion_nop_eci eci; \
      lion_nop_solve solve; \
      lion_nop_solve_node solve_node; \
      lion_nop_is_cyclic is_cyclic; \
      lion_nop_is_adaptive is_adaptive; \
      lion_nop_settle settle; \
      lion_nop_type_vop_ap type_vop_ap; \
      lion_nop_type_vop_dp_a type_vop_dp_a; \
      lion_nop_type_vop_dp_b type_vop_dp_b; \
      lion_nop_type_vop_dp_c type_vop_dp_c; \
      lion_nop_mcode_push_ap_holor mcode_push_ap_holor; \
      lion_nop_mcode_push_dp_holor mcode_push_dp_holor; \
      lion_nop_mcode_push_ap_track mcode_push_ap_track; \
      lion_nop_mcode_push_dp_track mcode_push_dp_track; \
  }; \
  static inline lion_nop* lion_nop_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_nop, t ); return ( lion_nop* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_nop_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_nop ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_nop ) \
  static inline bl_t lion_nop_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_nop ); } \
  static inline sz_t lion_nop_a_arity( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->arity ); return p->arity( o ); } \
  static inline bl_t lion_nop_a_defines_arity( const lion_nop* o ) { return true; } \
  static inline sz_t lion_nop_arity__( const lion_nop* o ){ERR_fa( "Not implemented in '#<sc_t>'.", ifnameof( o->_ ) ); return -1;} \
  static inline sz_t lion_nop_a_priority( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->priority ); return p->priority( o ); } \
  static inline bl_t lion_nop_a_defines_priority( const lion_nop* o ) { return true; } \
  static inline sz_t lion_nop_priority__( const lion_nop* o ){return 10;} \
  static inline sc_t lion_nop_a_symbol( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->symbol ); return p->symbol( o ); } \
  static inline bl_t lion_nop_a_defines_symbol( const lion_nop* o ) { return true; } \
  static inline sc_t lion_nop_symbol__( const lion_nop* o ){return NULL;} \
  static inline bl_t lion_nop_a_reserved( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->reserved ); return p->reserved( o ); } \
  static inline bl_t lion_nop_a_defines_reserved( const lion_nop* o ) { return true; } \
  static inline bl_t lion_nop_reserved__( const lion_nop* o ){return false;} \
  static inline lion_nop* lion_nop_a_create_op_of_arn( const lion_nop* o, sz_t n ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->create_op_of_arn ); return p->create_op_of_arn( o, n ); } \
  static inline bl_t lion_nop_a_defines_create_op_of_arn( const lion_nop* o ) { return true; } \
  static inline lion_nop* lion_nop_create_op_of_arn__( const lion_nop* o, sz_t n ){return ( lion_nop_a_arity( o ) == n ) ? lion_nop_a_clone( o ) : NULL;} \
  BETH_EXPAND_ITEM_lion_nop_solve_result_s \
  static inline bl_t lion_nop_a_eci( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->eci ); return p->eci( o ); } \
  static inline bl_t lion_nop_a_defines_eci( const lion_nop* o ) { return true; } \
  static inline bl_t lion_nop_eci__( const lion_nop* o ){return false;} \
  static inline bl_t lion_nop_a_solve( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->solve ); return p->solve( o, a, result ); } \
  static inline bl_t lion_nop_a_defines_solve( const lion_nop* o ) { return true; } \
  bl_t lion_nop_solve__( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  static inline void lion_nop_a_solve_node( lion_nop* o, lion_net_node_s* node, lion_net_node_adl_s* deferred ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->solve_node ); p->solve_node( o, node, deferred ); } \
  static inline bl_t lion_nop_a_defines_solve_node( const lion_nop* o ) { return true; } \
  void lion_nop_solve_node__( lion_nop* o, lion_net_node_s* node, lion_net_node_adl_s* deferred ); \
  static inline bl_t lion_nop_a_is_cyclic( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->is_cyclic ); return p->is_cyclic( o ); } \
  static inline bl_t lion_nop_a_defines_is_cyclic( const lion_nop* o ) { return true; } \
  static inline bl_t lion_nop_is_cyclic__( const lion_nop* o ){return false;} \
  static inline bl_t lion_nop_a_is_adaptive( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->is_adaptive ); return p->is_adaptive( o ); } \
  static inline bl_t lion_nop_a_defines_is_adaptive( const lion_nop* o ) { return true; } \
  static inline bl_t lion_nop_is_adaptive__( const lion_nop* o ){return false;} \
  static inline void lion_nop_a_settle( const lion_nop* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->settle ); p->settle( o, result, out_nop, out_result ); } \
  static inline bl_t lion_nop_a_defines_settle( const lion_nop* o ) { return true; } \
  void lion_nop_settle__( const lion_nop* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result ); \
  static inline tp_t lion_nop_a_type_vop_ap( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_ap ); return p->type_vop_ap( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_ap( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_ap != NULL; } \
  static inline tp_t lion_nop_a_type_vop_dp_a( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_dp_a ); return p->type_vop_dp_a( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_dp_a( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_dp_a != NULL; } \
  static inline tp_t lion_nop_a_type_vop_dp_b( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_dp_b ); return p->type_vop_dp_b( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_dp_b( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_dp_b != NULL; } \
  static inline tp_t lion_nop_a_type_vop_dp_c( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_dp_c ); return p->type_vop_dp_c( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_dp_c( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_dp_c != NULL; } \
  static inline sz_t lion_nop_a_mcode_push_ap_holor( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->mcode_push_ap_holor ); return p->mcode_push_ap_holor( o, result, arr_ci, mcf ); } \
  static inline bl_t lion_nop_a_defines_mcode_push_ap_holor( const lion_nop* o ) { return true; } \
  sz_t lion_nop_mcode_push_ap_holor__( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline sz_t lion_nop_a_mcode_push_dp_holor( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->mcode_push_dp_holor ); return p->mcode_push_dp_holor( o, result, arr_ci, mcf ); } \
  static inline bl_t lion_nop_a_defines_mcode_push_dp_holor( const lion_nop* o ) { return true; } \
  sz_t lion_nop_mcode_push_dp_holor__( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void lion_nop_a_mcode_push_ap_track( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->mcode_push_ap_track ); p->mcode_push_ap_track( o, result, arr_ci, mcf ); } \
  static inline bl_t lion_nop_a_defines_mcode_push_ap_track( const lion_nop* o ) { return true; } \
  void lion_nop_mcode_push_ap_track__( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void lion_nop_a_mcode_push_dp_track( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->mcode_push_dp_track ); p->mcode_push_dp_track( o, result, ch_id, arr_ci, mcf ); } \
  static inline bl_t lion_nop_a_defines_mcode_push_dp_track( const lion_nop* o ) { return true; } \
  void lion_nop_mcode_push_dp_track__( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BETH_EXPAND_ITEM_lion_nop_context_s \
  BETH_EXPAND_GROUP_lion_nop_ar0 \
  BETH_EXPAND_GROUP_lion_nop_ar1 \
  BETH_EXPAND_GROUP_lion_nop_ar2 \
  BETH_EXPAND_GROUP_lion_nop_ar3

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar0

#define TYPEOF_lion_nop_ar0 1811831167
#define TYPEOF_lion_nop_ar0_s 2802537705
#define TYPEOF_lion_nop_ar0_literal_s 2343955625
#define BETH_EXPAND_ITEM_lion_nop_ar0_literal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_literal_s ) \
    {aware_t _;lion_holor_s* h;}; \
  static inline sz_t lion_nop_ar0_literal_s_arity( const lion_nop_ar0_literal_s* o ){return 0;} \
  bl_t lion_nop_ar0_literal_s_solve( const lion_nop_ar0_literal_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar0_param_s 4033884219
#define BETH_EXPAND_ITEM_lion_nop_ar0_param_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_param_s ) \
    {aware_t _;lion_holor_s* h;}; \
  static inline sz_t lion_nop_ar0_param_s_arity( const lion_nop_ar0_param_s* o ){return 0;} \
  bl_t lion_nop_ar0_param_s_solve( const lion_nop_ar0_param_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar0_adaptive_s 2775076616
#define BETH_EXPAND_ITEM_lion_nop_ar0_adaptive_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_adaptive_s ) \
    {aware_t _;lion_holor_s* h;}; \
  static inline sz_t lion_nop_ar0_adaptive_s_arity( const lion_nop_ar0_adaptive_s* o ){return 0;} \
  static inline bl_t lion_nop_ar0_adaptive_s_is_adaptive( const lion_nop_ar0_adaptive_s* o ){return true;} \
  bl_t lion_nop_ar0_adaptive_s_solve( const lion_nop_ar0_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  sz_t lion_nop_ar0_adaptive_s_mcode_push_ap_holor( const lion_nop_ar0_adaptive_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t lion_nop_ar0_adaptive_s_mcode_push_dp_holor( const lion_nop_ar0_adaptive_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_lion_nop_ar0_rand_s 2499391049
#define BETH_EXPAND_ITEM_lion_nop_ar0_rand_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_rand_s ) \
    {aware_t _;lion_holor_s* h;f3_t min;f3_t max;f3_t density;u2_t rval;}; \
  static inline sz_t lion_nop_ar0_rand_s_arity( const lion_nop_ar0_rand_s* o ){return 0;} \
  bl_t lion_nop_ar0_rand_s_solve( const lion_nop_ar0_rand_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  sz_t lion_nop_ar0_rand_s_mcode_push_ap_holor( const lion_nop_ar0_rand_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define BETH_EXPAND_GROUP_lion_nop_ar0 \
  BCORE_FORWARD_OBJECT( lion_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_literal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_param_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_adaptive_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_rand_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar0_literal_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_param_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_adaptive_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_rand_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar1

#define TYPEOF_lion_nop_ar1 1795053548
#define TYPEOF_lion_nop_ar1_s 1250111182
#define TYPEOF_lion_nop_ar1_identity_s 2451425137
#define BETH_EXPAND_ITEM_lion_nop_ar1_identity_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_identity_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_identity_s_arity( const lion_nop_ar1_identity_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_identity_s_reserved( const lion_nop_ar1_identity_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_identity_s_priority( const lion_nop_ar1_identity_s* o ){return 8;} \
  bl_t lion_nop_ar1_identity_s_solve( const lion_nop_ar1_identity_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_f3_s 259552180
#define BETH_EXPAND_ITEM_lion_nop_ar1_f3_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_f3_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_f3_s_arity( const lion_nop_ar1_f3_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_f3_s_reserved( const lion_nop_ar1_f3_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_f3_s_priority( const lion_nop_ar1_f3_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_f3_s_symbol( const lion_nop_ar1_f3_s* o ){return "f3_t";} \
  bl_t lion_nop_ar1_f3_s_solve( const lion_nop_ar1_f3_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_f2_s 1811978703
#define BETH_EXPAND_ITEM_lion_nop_ar1_f2_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_f2_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_f2_s_arity( const lion_nop_ar1_f2_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_f2_s_reserved( const lion_nop_ar1_f2_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_f2_s_priority( const lion_nop_ar1_f2_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_f2_s_symbol( const lion_nop_ar1_f2_s* o ){return "f2_t";} \
  bl_t lion_nop_ar1_f2_s_solve( const lion_nop_ar1_f2_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_neg_s 594087751
#define BETH_EXPAND_ITEM_lion_nop_ar1_neg_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_neg_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_neg_s_arity( const lion_nop_ar1_neg_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_neg_s_reserved( const lion_nop_ar1_neg_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_neg_s_priority( const lion_nop_ar1_neg_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_neg_s_symbol( const lion_nop_ar1_neg_s* o ){return "neg";} \
  static inline tp_t lion_nop_ar1_neg_s_type_vop_ap( const lion_nop_ar1_neg_s* o ){return TYPEOF_bhvm_vop_ar1_neg_s;} \
  static inline tp_t lion_nop_ar1_neg_s_type_vop_dp_a( const lion_nop_ar1_neg_s* o ){return TYPEOF_bhvm_vop_ar1_neg_dp_s;} \
  lion_nop* lion_nop_ar1_neg_s_create_op_of_arn( const lion_nop_ar1_neg_s* o, sz_t n );
#define TYPEOF_lion_nop_ar1_floor_s 1699262323
#define BETH_EXPAND_ITEM_lion_nop_ar1_floor_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_floor_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_floor_s_arity( const lion_nop_ar1_floor_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_floor_s_reserved( const lion_nop_ar1_floor_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_floor_s_priority( const lion_nop_ar1_floor_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_floor_s_symbol( const lion_nop_ar1_floor_s* o ){return "floor";} \
  static inline tp_t lion_nop_ar1_floor_s_type_vop_ap( const lion_nop_ar1_floor_s* o ){return TYPEOF_bhvm_vop_ar1_floor_s;} \
  static inline sz_t lion_nop_ar1_floor_s_mcode_push_dp_holor( const lion_nop_ar1_floor_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar1_ceil_s 505367678
#define BETH_EXPAND_ITEM_lion_nop_ar1_ceil_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_ceil_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_ceil_s_arity( const lion_nop_ar1_ceil_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_ceil_s_reserved( const lion_nop_ar1_ceil_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_ceil_s_priority( const lion_nop_ar1_ceil_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_ceil_s_symbol( const lion_nop_ar1_ceil_s* o ){return "ceil";} \
  static inline tp_t lion_nop_ar1_ceil_s_type_vop_ap( const lion_nop_ar1_ceil_s* o ){return TYPEOF_bhvm_vop_ar1_ceil_s;} \
  static inline sz_t lion_nop_ar1_ceil_s_mcode_push_dp_holor( const lion_nop_ar1_ceil_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar1_abs_s 292167937
#define BETH_EXPAND_ITEM_lion_nop_ar1_abs_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_abs_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_abs_s_arity( const lion_nop_ar1_abs_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_abs_s_reserved( const lion_nop_ar1_abs_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_abs_s_priority( const lion_nop_ar1_abs_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_abs_s_symbol( const lion_nop_ar1_abs_s* o ){return "abs";} \
  static inline tp_t lion_nop_ar1_abs_s_type_vop_ap( const lion_nop_ar1_abs_s* o ){return TYPEOF_bhvm_vop_ar1_abs_s;} \
  static inline tp_t lion_nop_ar1_abs_s_type_vop_dp_a( const lion_nop_ar1_abs_s* o ){return TYPEOF_bhvm_vop_ar2_abs_dp_s;}
#define TYPEOF_lion_nop_ar1_exp_s 4255037934
#define BETH_EXPAND_ITEM_lion_nop_ar1_exp_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_exp_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_exp_s_arity( const lion_nop_ar1_exp_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_exp_s_reserved( const lion_nop_ar1_exp_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_exp_s_priority( const lion_nop_ar1_exp_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_exp_s_symbol( const lion_nop_ar1_exp_s* o ){return "exp";} \
  static inline tp_t lion_nop_ar1_exp_s_type_vop_ap( const lion_nop_ar1_exp_s* o ){return TYPEOF_bhvm_vop_ar1_exp_s;} \
  static inline tp_t lion_nop_ar1_exp_s_type_vop_dp_a( const lion_nop_ar1_exp_s* o ){return TYPEOF_bhvm_vop_ar2_exp_dp_s;}
#define TYPEOF_lion_nop_ar1_log_s 4247310423
#define BETH_EXPAND_ITEM_lion_nop_ar1_log_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_log_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_log_s_arity( const lion_nop_ar1_log_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_log_s_reserved( const lion_nop_ar1_log_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_log_s_priority( const lion_nop_ar1_log_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_log_s_symbol( const lion_nop_ar1_log_s* o ){return "log";} \
  static inline tp_t lion_nop_ar1_log_s_type_vop_ap( const lion_nop_ar1_log_s* o ){return TYPEOF_bhvm_vop_ar1_log_s;} \
  static inline tp_t lion_nop_ar1_log_s_type_vop_dp_a( const lion_nop_ar1_log_s* o ){return TYPEOF_bhvm_vop_ar2_log_dp_s;}
#define TYPEOF_lion_nop_ar1_inv_s 2310849958
#define BETH_EXPAND_ITEM_lion_nop_ar1_inv_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_inv_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_inv_s_arity( const lion_nop_ar1_inv_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_inv_s_reserved( const lion_nop_ar1_inv_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_inv_s_priority( const lion_nop_ar1_inv_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_inv_s_symbol( const lion_nop_ar1_inv_s* o ){return "inv";} \
  static inline tp_t lion_nop_ar1_inv_s_type_vop_ap( const lion_nop_ar1_inv_s* o ){return TYPEOF_bhvm_vop_ar1_inv_s;} \
  static inline tp_t lion_nop_ar1_inv_s_type_vop_dp_a( const lion_nop_ar1_inv_s* o ){return TYPEOF_bhvm_vop_ar2_inv_dp_s;}
#define TYPEOF_lion_nop_ar1_sqr_s 3401947903
#define BETH_EXPAND_ITEM_lion_nop_ar1_sqr_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_sqr_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_sqr_s_arity( const lion_nop_ar1_sqr_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_sqr_s_reserved( const lion_nop_ar1_sqr_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_sqr_s_priority( const lion_nop_ar1_sqr_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_sqr_s_symbol( const lion_nop_ar1_sqr_s* o ){return "sqr";} \
  static inline tp_t lion_nop_ar1_sqr_s_type_vop_ap( const lion_nop_ar1_sqr_s* o ){return TYPEOF_bhvm_vop_ar1_sqr_s;} \
  static inline tp_t lion_nop_ar1_sqr_s_type_vop_dp_a( const lion_nop_ar1_sqr_s* o ){return TYPEOF_bhvm_vop_ar2_sqr_dp_s;}
#define TYPEOF_lion_nop_ar1_srt_s 250167130
#define BETH_EXPAND_ITEM_lion_nop_ar1_srt_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_srt_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_srt_s_arity( const lion_nop_ar1_srt_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_srt_s_reserved( const lion_nop_ar1_srt_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_srt_s_priority( const lion_nop_ar1_srt_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_srt_s_symbol( const lion_nop_ar1_srt_s* o ){return "srt";} \
  static inline tp_t lion_nop_ar1_srt_s_type_vop_ap( const lion_nop_ar1_srt_s* o ){return TYPEOF_bhvm_vop_ar1_srt_s;} \
  static inline tp_t lion_nop_ar1_srt_s_type_vop_dp_a( const lion_nop_ar1_srt_s* o ){return TYPEOF_bhvm_vop_ar2_srt_dp_s;}
#define TYPEOF_lion_nop_ar1_sigm_s 1352691899
#define BETH_EXPAND_ITEM_lion_nop_ar1_sigm_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_sigm_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_sigm_s_arity( const lion_nop_ar1_sigm_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_sigm_s_reserved( const lion_nop_ar1_sigm_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_sigm_s_priority( const lion_nop_ar1_sigm_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_sigm_s_symbol( const lion_nop_ar1_sigm_s* o ){return "sigm";} \
  static inline tp_t lion_nop_ar1_sigm_s_type_vop_ap( const lion_nop_ar1_sigm_s* o ){return TYPEOF_bhvm_vop_ar1_sigm_s;} \
  static inline tp_t lion_nop_ar1_sigm_s_type_vop_dp_a( const lion_nop_ar1_sigm_s* o ){return TYPEOF_bhvm_vop_ar2_sigm_dp_s;}
#define TYPEOF_lion_nop_ar1_sigm_hard_s 1313196453
#define BETH_EXPAND_ITEM_lion_nop_ar1_sigm_hard_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_sigm_hard_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_sigm_hard_s_arity( const lion_nop_ar1_sigm_hard_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_sigm_hard_s_reserved( const lion_nop_ar1_sigm_hard_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_sigm_hard_s_priority( const lion_nop_ar1_sigm_hard_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_sigm_hard_s_symbol( const lion_nop_ar1_sigm_hard_s* o ){return "sigm_hard";} \
  static inline tp_t lion_nop_ar1_sigm_hard_s_type_vop_ap( const lion_nop_ar1_sigm_hard_s* o ){return TYPEOF_bhvm_vop_ar1_sigm_hard_s;} \
  static inline tp_t lion_nop_ar1_sigm_hard_s_type_vop_dp_a( const lion_nop_ar1_sigm_hard_s* o ){return TYPEOF_bhvm_vop_ar2_sigm_hard_dp_s;}
#define TYPEOF_lion_nop_ar1_sigm_leaky_s 989360502
#define BETH_EXPAND_ITEM_lion_nop_ar1_sigm_leaky_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_sigm_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_sigm_leaky_s_arity( const lion_nop_ar1_sigm_leaky_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_sigm_leaky_s_reserved( const lion_nop_ar1_sigm_leaky_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_sigm_leaky_s_priority( const lion_nop_ar1_sigm_leaky_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_sigm_leaky_s_symbol( const lion_nop_ar1_sigm_leaky_s* o ){return "sigm_leaky";} \
  static inline tp_t lion_nop_ar1_sigm_leaky_s_type_vop_ap( const lion_nop_ar1_sigm_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_sigm_leaky_s;} \
  static inline tp_t lion_nop_ar1_sigm_leaky_s_type_vop_dp_a( const lion_nop_ar1_sigm_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_sigm_leaky_dp_s;}
#define TYPEOF_lion_nop_ar1_tanh_s 772292870
#define BETH_EXPAND_ITEM_lion_nop_ar1_tanh_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_tanh_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_tanh_s_arity( const lion_nop_ar1_tanh_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_tanh_s_reserved( const lion_nop_ar1_tanh_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_tanh_s_priority( const lion_nop_ar1_tanh_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_tanh_s_symbol( const lion_nop_ar1_tanh_s* o ){return "tanh";} \
  static inline tp_t lion_nop_ar1_tanh_s_type_vop_ap( const lion_nop_ar1_tanh_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_s;} \
  static inline tp_t lion_nop_ar1_tanh_s_type_vop_dp_a( const lion_nop_ar1_tanh_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_dp_s;}
#define TYPEOF_lion_nop_ar1_tanh_hard_s 1582636522
#define BETH_EXPAND_ITEM_lion_nop_ar1_tanh_hard_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_tanh_hard_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_tanh_hard_s_arity( const lion_nop_ar1_tanh_hard_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_tanh_hard_s_reserved( const lion_nop_ar1_tanh_hard_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_tanh_hard_s_priority( const lion_nop_ar1_tanh_hard_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_tanh_hard_s_symbol( const lion_nop_ar1_tanh_hard_s* o ){return "tanh_hard";} \
  static inline tp_t lion_nop_ar1_tanh_hard_s_type_vop_ap( const lion_nop_ar1_tanh_hard_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_hard_s;} \
  static inline tp_t lion_nop_ar1_tanh_hard_s_type_vop_dp_a( const lion_nop_ar1_tanh_hard_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_hard_dp_s;}
#define TYPEOF_lion_nop_ar1_tanh_leaky_s 2422520131
#define BETH_EXPAND_ITEM_lion_nop_ar1_tanh_leaky_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_tanh_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_tanh_leaky_s_arity( const lion_nop_ar1_tanh_leaky_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_tanh_leaky_s_reserved( const lion_nop_ar1_tanh_leaky_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_tanh_leaky_s_priority( const lion_nop_ar1_tanh_leaky_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_tanh_leaky_s_symbol( const lion_nop_ar1_tanh_leaky_s* o ){return "tanh_leaky";} \
  static inline tp_t lion_nop_ar1_tanh_leaky_s_type_vop_ap( const lion_nop_ar1_tanh_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_leaky_s;} \
  static inline tp_t lion_nop_ar1_tanh_leaky_s_type_vop_dp_a( const lion_nop_ar1_tanh_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_leaky_dp_s;}
#define TYPEOF_lion_nop_ar1_softplus_s 2242492955
#define BETH_EXPAND_ITEM_lion_nop_ar1_softplus_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_softplus_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_softplus_s_arity( const lion_nop_ar1_softplus_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_softplus_s_reserved( const lion_nop_ar1_softplus_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_softplus_s_priority( const lion_nop_ar1_softplus_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_softplus_s_symbol( const lion_nop_ar1_softplus_s* o ){return "softplus";} \
  static inline tp_t lion_nop_ar1_softplus_s_type_vop_ap( const lion_nop_ar1_softplus_s* o ){return TYPEOF_bhvm_vop_ar1_softplus_s;} \
  static inline tp_t lion_nop_ar1_softplus_s_type_vop_dp_a( const lion_nop_ar1_softplus_s* o ){return TYPEOF_bhvm_vop_ar2_softplus_dp_s;}
#define TYPEOF_lion_nop_ar1_softmax_s 2695309895
#define BETH_EXPAND_ITEM_lion_nop_ar1_softmax_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_softmax_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_softmax_s_arity( const lion_nop_ar1_softmax_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_softmax_s_reserved( const lion_nop_ar1_softmax_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_softmax_s_priority( const lion_nop_ar1_softmax_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_softmax_s_symbol( const lion_nop_ar1_softmax_s* o ){return "softmax";} \
  static inline tp_t lion_nop_ar1_softmax_s_type_vop_ap( const lion_nop_ar1_softmax_s* o ){return TYPEOF_bhvm_vop_ar1_softmax_s;} \
  static inline tp_t lion_nop_ar1_softmax_s_type_vop_dp_a( const lion_nop_ar1_softmax_s* o ){return TYPEOF_bhvm_vop_ar2_softmax_dp_s;}
#define TYPEOF_lion_nop_ar1_relu_s 1447672377
#define BETH_EXPAND_ITEM_lion_nop_ar1_relu_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_relu_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_relu_s_arity( const lion_nop_ar1_relu_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_relu_s_reserved( const lion_nop_ar1_relu_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_relu_s_priority( const lion_nop_ar1_relu_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_relu_s_symbol( const lion_nop_ar1_relu_s* o ){return "relu";} \
  static inline tp_t lion_nop_ar1_relu_s_type_vop_ap( const lion_nop_ar1_relu_s* o ){return TYPEOF_bhvm_vop_ar1_relu_s;} \
  static inline tp_t lion_nop_ar1_relu_s_type_vop_dp_a( const lion_nop_ar1_relu_s* o ){return TYPEOF_bhvm_vop_ar2_relu_dp_s;}
#define TYPEOF_lion_nop_ar1_relu_leaky_s 1869882548
#define BETH_EXPAND_ITEM_lion_nop_ar1_relu_leaky_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_relu_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_relu_leaky_s_arity( const lion_nop_ar1_relu_leaky_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_relu_leaky_s_reserved( const lion_nop_ar1_relu_leaky_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_relu_leaky_s_priority( const lion_nop_ar1_relu_leaky_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_relu_leaky_s_symbol( const lion_nop_ar1_relu_leaky_s* o ){return "relu_leaky";} \
  static inline tp_t lion_nop_ar1_relu_leaky_s_type_vop_ap( const lion_nop_ar1_relu_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_relu_leaky_s;} \
  static inline tp_t lion_nop_ar1_relu_leaky_s_type_vop_dp_a( const lion_nop_ar1_relu_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_relu_leaky_dp_s;}
#define TYPEOF_lion_nop_ar1_output_s 1113502298
#define BETH_EXPAND_ITEM_lion_nop_ar1_output_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_output_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_output_s_arity( const lion_nop_ar1_output_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_output_s_reserved( const lion_nop_ar1_output_s* o ){return true;} \
  bl_t lion_nop_ar1_output_s_solve( const lion_nop_ar1_output_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  sz_t lion_nop_ar1_output_s_mcode_push_dp_holor( const lion_nop_ar1_output_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_lion_nop_ar1_adaptive_s 1680611337
#define BETH_EXPAND_ITEM_lion_nop_ar1_adaptive_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_adaptive_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t lion_nop_ar1_adaptive_s_arity( const lion_nop_ar1_adaptive_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_adaptive_s_reserved( const lion_nop_ar1_adaptive_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_adaptive_s_priority( const lion_nop_ar1_adaptive_s* o ){return 8;} \
  static inline bl_t lion_nop_ar1_adaptive_s_is_adaptive( const lion_nop_ar1_adaptive_s* o ){return true;} \
  bl_t lion_nop_ar1_adaptive_s_solve( const lion_nop_ar1_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  void lion_nop_ar1_adaptive_s_settle( const lion_nop_ar1_adaptive_s* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result );
#define TYPEOF_lion_nop_ar1_dimof_s 2608787106
#define BETH_EXPAND_ITEM_lion_nop_ar1_dimof_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_dimof_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_dimof_s_arity( const lion_nop_ar1_dimof_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_dimof_s_reserved( const lion_nop_ar1_dimof_s* o ){return true;} \
  static inline sc_t lion_nop_ar1_dimof_s_symbol( const lion_nop_ar1_dimof_s* o ){return "dimof";} \
  static inline sz_t lion_nop_ar1_dimof_s_priority( const lion_nop_ar1_dimof_s* o ){return 8;} \
  bl_t lion_nop_ar1_dimof_s_solve( const lion_nop_ar1_dimof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_volof_s 1383010665
#define BETH_EXPAND_ITEM_lion_nop_ar1_volof_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_volof_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_volof_s_arity( const lion_nop_ar1_volof_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_volof_s_reserved( const lion_nop_ar1_volof_s* o ){return true;} \
  static inline sc_t lion_nop_ar1_volof_s_symbol( const lion_nop_ar1_volof_s* o ){return "volof";} \
  static inline sz_t lion_nop_ar1_volof_s_priority( const lion_nop_ar1_volof_s* o ){return 8;} \
  bl_t lion_nop_ar1_volof_s_solve( const lion_nop_ar1_volof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_constof_s 2972022227
#define BETH_EXPAND_ITEM_lion_nop_ar1_constof_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_constof_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_constof_s_arity( const lion_nop_ar1_constof_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_constof_s_reserved( const lion_nop_ar1_constof_s* o ){return true;} \
  static inline sc_t lion_nop_ar1_constof_s_symbol( const lion_nop_ar1_constof_s* o ){return "constof";} \
  static inline sz_t lion_nop_ar1_constof_s_priority( const lion_nop_ar1_constof_s* o ){return 8;} \
  bl_t lion_nop_ar1_constof_s_solve( const lion_nop_ar1_constof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_zeroof_s 689689716
#define BETH_EXPAND_ITEM_lion_nop_ar1_zeroof_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_zeroof_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_zeroof_s_arity( const lion_nop_ar1_zeroof_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_zeroof_s_reserved( const lion_nop_ar1_zeroof_s* o ){return true;} \
  static inline sc_t lion_nop_ar1_zeroof_s_symbol( const lion_nop_ar1_zeroof_s* o ){return "zeroof";} \
  static inline sz_t lion_nop_ar1_zeroof_s_priority( const lion_nop_ar1_zeroof_s* o ){return 8;} \
  bl_t lion_nop_ar1_zeroof_s_solve( const lion_nop_ar1_zeroof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_shapeof_s 3043285405
#define BETH_EXPAND_ITEM_lion_nop_ar1_shapeof_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_shapeof_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_shapeof_s_arity( const lion_nop_ar1_shapeof_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_shapeof_s_reserved( const lion_nop_ar1_shapeof_s* o ){return true;} \
  static inline sc_t lion_nop_ar1_shapeof_s_symbol( const lion_nop_ar1_shapeof_s* o ){return "shapeof";} \
  static inline sz_t lion_nop_ar1_shapeof_s_priority( const lion_nop_ar1_shapeof_s* o ){return 8;} \
  bl_t lion_nop_ar1_shapeof_s_solve( const lion_nop_ar1_shapeof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_rand_s 288306100
#define BETH_EXPAND_ITEM_lion_nop_ar1_rand_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_rand_s ) \
    {aware_t _;u2_t rseed;}; \
  static inline sz_t lion_nop_ar1_rand_s_arity( const lion_nop_ar1_rand_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_rand_s_reserved( const lion_nop_ar1_rand_s* o ){return true;} \
  static inline sc_t lion_nop_ar1_rand_s_symbol( const lion_nop_ar1_rand_s* o ){return "rand";} \
  static inline sz_t lion_nop_ar1_rand_s_priority( const lion_nop_ar1_rand_s* o ){return 8;} \
  bl_t lion_nop_ar1_rand_s_solve( const lion_nop_ar1_rand_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  void lion_nop_ar1_rand_s_settle( const lion_nop_ar1_rand_s* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result );
#define TYPEOF_lion_nop_ar1_cast_htp_s 2772432835
#define BETH_EXPAND_ITEM_lion_nop_ar1_cast_htp_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_cast_htp_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_cast_htp_s_arity( const lion_nop_ar1_cast_htp_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_cast_htp_s_reserved( const lion_nop_ar1_cast_htp_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_cast_htp_s_priority( const lion_nop_ar1_cast_htp_s* o ){return 12;} \
  static inline sc_t lion_nop_ar1_cast_htp_s_symbol( const lion_nop_ar1_cast_htp_s* o ){return "htp";} \
  bl_t lion_nop_ar1_cast_htp_s_solve( const lion_nop_ar1_cast_htp_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  sz_t lion_nop_ar1_cast_htp_s_mcode_push_ap_holor( const lion_nop_ar1_cast_htp_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t lion_nop_ar1_cast_htp_s_mcode_push_dp_holor( const lion_nop_ar1_cast_htp_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_lion_nop_ar1_reshape_s 3077918347
#define BETH_EXPAND_ITEM_lion_nop_ar1_reshape_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_reshape_s ) \
    {aware_t _;bhvm_shape_s shape;}; \
  static inline sz_t lion_nop_ar1_reshape_s_arity( const lion_nop_ar1_reshape_s* o ){return 1;} \
  static inline bl_t lion_nop_ar1_reshape_s_reserved( const lion_nop_ar1_reshape_s* o ){return true;} \
  static inline sz_t lion_nop_ar1_reshape_s_priority( const lion_nop_ar1_reshape_s* o ){return 8;} \
  bl_t lion_nop_ar1_reshape_s_solve( const lion_nop_ar1_reshape_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  sz_t lion_nop_ar1_reshape_s_mcode_push_ap_holor( const lion_nop_ar1_reshape_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t lion_nop_ar1_reshape_s_mcode_push_dp_holor( const lion_nop_ar1_reshape_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define BETH_EXPAND_GROUP_lion_nop_ar1 \
  BCORE_FORWARD_OBJECT( lion_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_identity_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_f3_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_f2_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_neg_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_floor_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_ceil_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_abs_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_exp_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_log_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_inv_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_sqr_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_srt_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_sigm_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_sigm_hard_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_sigm_leaky_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_tanh_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_tanh_hard_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_tanh_leaky_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_softplus_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_softmax_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_relu_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_relu_leaky_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_output_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_adaptive_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_dimof_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_volof_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_constof_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_zeroof_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_shapeof_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_rand_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_cast_htp_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_reshape_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar1_identity_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_f3_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_f2_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_neg_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_floor_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_ceil_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_abs_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_exp_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_log_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_inv_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_sqr_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_srt_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_sigm_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_sigm_hard_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_sigm_leaky_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_tanh_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_tanh_hard_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_tanh_leaky_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_softplus_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_softmax_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_relu_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_relu_leaky_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_output_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_adaptive_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_dimof_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_volof_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_constof_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_zeroof_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_shapeof_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_rand_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_cast_htp_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_reshape_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar2

#define TYPEOF_lion_nop_ar2 1845386405
#define TYPEOF_lion_nop_ar2_s 2593649991
#define TYPEOF_lion_nop_ar2_add_s 3353650847
#define BETH_EXPAND_ITEM_lion_nop_ar2_add_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_add_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_add_s_arity( const lion_nop_ar2_add_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_add_s_reserved( const lion_nop_ar2_add_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_add_s_priority( const lion_nop_ar2_add_s* o ){return 8;} \
  static inline bl_t lion_nop_ar2_add_s_eci( const lion_nop_ar2_add_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_add_s_symbol( const lion_nop_ar2_add_s* o ){return "+";} \
  static inline tp_t lion_nop_ar2_add_s_type_vop_ap( const lion_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar2_add_s;} \
  static inline tp_t lion_nop_ar2_add_s_type_vop_dp_a( const lion_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_a_s;} \
  static inline tp_t lion_nop_ar2_add_s_type_vop_dp_b( const lion_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_lion_nop_ar2_sub_s 1752167710
#define BETH_EXPAND_ITEM_lion_nop_ar2_sub_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_sub_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_sub_s_arity( const lion_nop_ar2_sub_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_sub_s_reserved( const lion_nop_ar2_sub_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_sub_s_priority( const lion_nop_ar2_sub_s* o ){return 8;} \
  static inline bl_t lion_nop_ar2_sub_s_eci( const lion_nop_ar2_sub_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_sub_s_symbol( const lion_nop_ar2_sub_s* o ){return "-";} \
  static inline tp_t lion_nop_ar2_sub_s_type_vop_ap( const lion_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar2_sub_s;} \
  static inline tp_t lion_nop_ar2_sub_s_type_vop_dp_a( const lion_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar1_sub_dp_a_s;} \
  static inline tp_t lion_nop_ar2_sub_s_type_vop_dp_b( const lion_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar1_sub_dp_b_s;} \
  lion_nop* lion_nop_ar2_sub_s_create_op_of_arn( const lion_nop_ar2_sub_s* o, sz_t n );
#define TYPEOF_lion_nop_ar2_mul_s 2245955362
#define BETH_EXPAND_ITEM_lion_nop_ar2_mul_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_mul_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_mul_s_arity( const lion_nop_ar2_mul_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_mul_s_reserved( const lion_nop_ar2_mul_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_mul_s_priority( const lion_nop_ar2_mul_s* o ){return 10;} \
  static inline bl_t lion_nop_ar2_mul_s_eci( const lion_nop_ar2_mul_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_mul_s_symbol( const lion_nop_ar2_mul_s* o ){return "*";} \
  static inline tp_t lion_nop_ar2_mul_s_type_vop_ap( const lion_nop_ar2_mul_s* o ){return TYPEOF_bhvm_vop_ar2_mul_s;} \
  static inline tp_t lion_nop_ar2_mul_s_type_vop_dp_a( const lion_nop_ar2_mul_s* o ){return TYPEOF_bhvm_vop_ar2_mul_dp_a_s;} \
  static inline tp_t lion_nop_ar2_mul_s_type_vop_dp_b( const lion_nop_ar2_mul_s* o ){return TYPEOF_bhvm_vop_ar2_mul_dp_b_s;}
#define TYPEOF_lion_nop_ar2_div_s 4076606099
#define BETH_EXPAND_ITEM_lion_nop_ar2_div_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_div_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_div_s_arity( const lion_nop_ar2_div_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_div_s_reserved( const lion_nop_ar2_div_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_div_s_priority( const lion_nop_ar2_div_s* o ){return 10;} \
  static inline bl_t lion_nop_ar2_div_s_eci( const lion_nop_ar2_div_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_div_s_symbol( const lion_nop_ar2_div_s* o ){return "/";} \
  static inline tp_t lion_nop_ar2_div_s_type_vop_ap( const lion_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar2_div_s;} \
  static inline tp_t lion_nop_ar2_div_s_type_vop_dp_a( const lion_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar2_div_dp_a_s;} \
  static inline tp_t lion_nop_ar2_div_s_type_vop_dp_b( const lion_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar3_div_dp_b_s;}
#define TYPEOF_lion_nop_ar2_pow_s 470395698
#define BETH_EXPAND_ITEM_lion_nop_ar2_pow_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_pow_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_pow_s_arity( const lion_nop_ar2_pow_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_pow_s_reserved( const lion_nop_ar2_pow_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_pow_s_priority( const lion_nop_ar2_pow_s* o ){return 12;} \
  static inline bl_t lion_nop_ar2_pow_s_eci( const lion_nop_ar2_pow_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_pow_s_symbol( const lion_nop_ar2_pow_s* o ){return "^";} \
  static inline tp_t lion_nop_ar2_pow_s_type_vop_ap( const lion_nop_ar2_pow_s* o ){return TYPEOF_bhvm_vop_ar2_pow_s;} \
  static inline tp_t lion_nop_ar2_pow_s_type_vop_dp_a( const lion_nop_ar2_pow_s* o ){return TYPEOF_bhvm_vop_ar3_pow_dp_a_s;} \
  static inline tp_t lion_nop_ar2_pow_s_type_vop_dp_b( const lion_nop_ar2_pow_s* o ){return TYPEOF_bhvm_vop_ar3_pow_dp_b_s;}
#define TYPEOF_lion_nop_ar2_bmul_s 2813275964
#define BETH_EXPAND_ITEM_lion_nop_ar2_bmul_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_bmul_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_bmul_s_arity( const lion_nop_ar2_bmul_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_bmul_s_reserved( const lion_nop_ar2_bmul_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_bmul_s_priority( const lion_nop_ar2_bmul_s* o ){return 10;} \
  static inline sc_t lion_nop_ar2_bmul_s_symbol( const lion_nop_ar2_bmul_s* o ){return "**";} \
  bl_t lion_nop_ar2_bmul_s_solve( const lion_nop_ar2_bmul_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar2_logic_equal_s 1792137045
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_equal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_equal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_equal_s_arity( const lion_nop_ar2_logic_equal_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_equal_s_reserved( const lion_nop_ar2_logic_equal_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_equal_s_priority( const lion_nop_ar2_logic_equal_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_equal_s_eci( const lion_nop_ar2_logic_equal_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_equal_s_symbol( const lion_nop_ar2_logic_equal_s* o ){return "==";} \
  static inline tp_t lion_nop_ar2_logic_equal_s_type_vop_ap( const lion_nop_ar2_logic_equal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_equal_s;} \
  static inline sz_t lion_nop_ar2_logic_equal_s_mcode_push_dp_holor( const lion_nop_ar2_logic_equal_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_unequal_s 3538892188
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_unequal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_unequal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_unequal_s_arity( const lion_nop_ar2_logic_unequal_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_unequal_s_reserved( const lion_nop_ar2_logic_unequal_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_unequal_s_priority( const lion_nop_ar2_logic_unequal_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_unequal_s_eci( const lion_nop_ar2_logic_unequal_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_unequal_s_symbol( const lion_nop_ar2_logic_unequal_s* o ){return "!=";} \
  static inline tp_t lion_nop_ar2_logic_unequal_s_type_vop_ap( const lion_nop_ar2_logic_unequal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_unequal_s;} \
  static inline sz_t lion_nop_ar2_logic_unequal_s_mcode_push_dp_holor( const lion_nop_ar2_logic_unequal_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_larger_s 1021284944
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_larger_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_larger_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_larger_s_arity( const lion_nop_ar2_logic_larger_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_larger_s_reserved( const lion_nop_ar2_logic_larger_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_larger_s_priority( const lion_nop_ar2_logic_larger_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_larger_s_eci( const lion_nop_ar2_logic_larger_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_larger_s_symbol( const lion_nop_ar2_logic_larger_s* o ){return ">";} \
  static inline tp_t lion_nop_ar2_logic_larger_s_type_vop_ap( const lion_nop_ar2_logic_larger_s* o ){return TYPEOF_bhvm_vop_ar2_logic_larger_s;} \
  static inline sz_t lion_nop_ar2_logic_larger_s_mcode_push_dp_holor( const lion_nop_ar2_logic_larger_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_smaller_s 3656145729
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_smaller_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_smaller_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_smaller_s_arity( const lion_nop_ar2_logic_smaller_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_smaller_s_reserved( const lion_nop_ar2_logic_smaller_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_smaller_s_priority( const lion_nop_ar2_logic_smaller_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_smaller_s_eci( const lion_nop_ar2_logic_smaller_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_smaller_s_symbol( const lion_nop_ar2_logic_smaller_s* o ){return "<";} \
  static inline tp_t lion_nop_ar2_logic_smaller_s_type_vop_ap( const lion_nop_ar2_logic_smaller_s* o ){return TYPEOF_bhvm_vop_ar2_logic_smaller_s;} \
  static inline sz_t lion_nop_ar2_logic_smaller_s_mcode_push_dp_holor( const lion_nop_ar2_logic_smaller_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_larger_equal_s 856673315
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_larger_equal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_larger_equal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_larger_equal_s_arity( const lion_nop_ar2_logic_larger_equal_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_larger_equal_s_reserved( const lion_nop_ar2_logic_larger_equal_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_larger_equal_s_priority( const lion_nop_ar2_logic_larger_equal_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_larger_equal_s_eci( const lion_nop_ar2_logic_larger_equal_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_larger_equal_s_symbol( const lion_nop_ar2_logic_larger_equal_s* o ){return ">=";} \
  static inline tp_t lion_nop_ar2_logic_larger_equal_s_type_vop_ap( const lion_nop_ar2_logic_larger_equal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_larger_equal_s;} \
  static inline sz_t lion_nop_ar2_logic_larger_equal_s_mcode_push_dp_holor( const lion_nop_ar2_logic_larger_equal_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_smaller_equal_s 2728185754
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_smaller_equal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_smaller_equal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_smaller_equal_s_arity( const lion_nop_ar2_logic_smaller_equal_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_smaller_equal_s_reserved( const lion_nop_ar2_logic_smaller_equal_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_smaller_equal_s_priority( const lion_nop_ar2_logic_smaller_equal_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_smaller_equal_s_eci( const lion_nop_ar2_logic_smaller_equal_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_smaller_equal_s_symbol( const lion_nop_ar2_logic_smaller_equal_s* o ){return "<=";} \
  static inline tp_t lion_nop_ar2_logic_smaller_equal_s_type_vop_ap( const lion_nop_ar2_logic_smaller_equal_s* o ){return TYPEOF_bhvm_vop_ar2_logic_smaller_equal_s;} \
  static inline sz_t lion_nop_ar2_logic_smaller_equal_s_mcode_push_dp_holor( const lion_nop_ar2_logic_smaller_equal_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_and_s 683893884
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_and_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_and_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_and_s_arity( const lion_nop_ar2_logic_and_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_and_s_reserved( const lion_nop_ar2_logic_and_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_and_s_priority( const lion_nop_ar2_logic_and_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_and_s_eci( const lion_nop_ar2_logic_and_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_and_s_symbol( const lion_nop_ar2_logic_and_s* o ){return "&&";} \
  static inline tp_t lion_nop_ar2_logic_and_s_type_vop_ap( const lion_nop_ar2_logic_and_s* o ){return TYPEOF_bhvm_vop_ar2_logic_and_s;} \
  static inline sz_t lion_nop_ar2_logic_and_s_mcode_push_dp_holor( const lion_nop_ar2_logic_and_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_logic_or_s 1005674890
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_or_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_or_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_or_s_arity( const lion_nop_ar2_logic_or_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_logic_or_s_reserved( const lion_nop_ar2_logic_or_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_logic_or_s_priority( const lion_nop_ar2_logic_or_s* o ){return 6;} \
  static inline bl_t lion_nop_ar2_logic_or_s_eci( const lion_nop_ar2_logic_or_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_logic_or_s_symbol( const lion_nop_ar2_logic_or_s* o ){return "||";} \
  static inline tp_t lion_nop_ar2_logic_or_s_type_vop_ap( const lion_nop_ar2_logic_or_s* o ){return TYPEOF_bhvm_vop_ar2_logic_or_s;} \
  static inline sz_t lion_nop_ar2_logic_or_s_mcode_push_dp_holor( const lion_nop_ar2_logic_or_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){return -1;}
#define TYPEOF_lion_nop_ar2_cat_s 2494514940
#define BETH_EXPAND_ITEM_lion_nop_ar2_cat_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_cat_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_cat_s_arity( const lion_nop_ar2_cat_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_cat_s_reserved( const lion_nop_ar2_cat_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_cat_s_priority( const lion_nop_ar2_cat_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_cat_s_symbol( const lion_nop_ar2_cat_s* o ){return ":";} \
  bl_t lion_nop_ar2_cat_s_solve( const lion_nop_ar2_cat_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  static inline tp_t lion_nop_ar2_cat_s_type_vop_ap( const lion_nop_ar2_cat_s* o ){return TYPEOF_bhvm_vop_ar2_cat_s;} \
  static inline tp_t lion_nop_ar2_cat_s_type_vop_dp_a( const lion_nop_ar2_cat_s* o ){return TYPEOF_bhvm_vop_ar1_cat_dp_a_s;} \
  static inline tp_t lion_nop_ar2_cat_s_type_vop_dp_b( const lion_nop_ar2_cat_s* o ){return TYPEOF_bhvm_vop_ar1_cat_dp_b_s;}
#define TYPEOF_lion_nop_ar2_ccat_s 1253892867
#define BETH_EXPAND_ITEM_lion_nop_ar2_ccat_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_ccat_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_ccat_s_arity( const lion_nop_ar2_ccat_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_ccat_s_reserved( const lion_nop_ar2_ccat_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_ccat_s_priority( const lion_nop_ar2_ccat_s* o ){return 8;} \
  static inline sc_t lion_nop_ar2_ccat_s_symbol( const lion_nop_ar2_ccat_s* o ){return "::";} \
  bl_t lion_nop_ar2_ccat_s_solve( const lion_nop_ar2_ccat_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  static inline tp_t lion_nop_ar2_ccat_s_type_vop_ap( const lion_nop_ar2_ccat_s* o ){return TYPEOF_bhvm_vop_ar2_ccat_s;} \
  static inline tp_t lion_nop_ar2_ccat_s_type_vop_dp_a( const lion_nop_ar2_ccat_s* o ){return TYPEOF_bhvm_vop_ar1_ccat_dp_a_s;} \
  static inline tp_t lion_nop_ar2_ccat_s_type_vop_dp_b( const lion_nop_ar2_ccat_s* o ){return TYPEOF_bhvm_vop_ar1_ccat_dp_b_s;}
#define TYPEOF_lion_nop_ar2_order_inc_s 2250225947
#define BETH_EXPAND_ITEM_lion_nop_ar2_order_inc_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_order_inc_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_order_inc_s_arity( const lion_nop_ar2_order_inc_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_order_inc_s_reserved( const lion_nop_ar2_order_inc_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_order_inc_s_priority( const lion_nop_ar2_order_inc_s* o ){return 21;} \
  static inline sc_t lion_nop_ar2_order_inc_s_symbol( const lion_nop_ar2_order_inc_s* o ){return "[";} \
  bl_t lion_nop_ar2_order_inc_s_solve( const lion_nop_ar2_order_inc_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  void lion_nop_ar2_order_inc_s_mcode_push_ap_track( const lion_nop_ar2_order_inc_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline tp_t lion_nop_ar2_order_inc_s_type_vop_dp_a( const lion_nop_ar2_order_inc_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_order_inc_s_type_vop_dp_b( const lion_nop_ar2_order_inc_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_lion_nop_ar2_order_dec_s 3205562379
#define BETH_EXPAND_ITEM_lion_nop_ar2_order_dec_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_order_dec_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_order_dec_s_arity( const lion_nop_ar2_order_dec_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_order_dec_s_reserved( const lion_nop_ar2_order_dec_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_order_dec_s_priority( const lion_nop_ar2_order_dec_s* o ){return 20;} \
  static inline sc_t lion_nop_ar2_order_dec_s_symbol( const lion_nop_ar2_order_dec_s* o ){return "]";} \
  bl_t lion_nop_ar2_order_dec_s_solve( const lion_nop_ar2_order_dec_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  sz_t lion_nop_ar2_order_dec_s_mcode_push_ap_holor( const lion_nop_ar2_order_dec_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  sz_t lion_nop_ar2_order_dec_s_mcode_push_dp_holor( const lion_nop_ar2_order_dec_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define TYPEOF_lion_nop_ar2_cyclic_s 2525737031
#define BETH_EXPAND_ITEM_lion_nop_ar2_cyclic_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_cyclic_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t lion_nop_ar2_cyclic_s_arity( const lion_nop_ar2_cyclic_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_cyclic_s_reserved( const lion_nop_ar2_cyclic_s* o ){return true;} \
  static inline sz_t lion_nop_ar2_cyclic_s_priority( const lion_nop_ar2_cyclic_s* o ){return 8;} \
  static inline bl_t lion_nop_ar2_cyclic_s_is_cyclic( const lion_nop_ar2_cyclic_s* o ){return true;} \
  bl_t lion_nop_ar2_cyclic_s_solve( const lion_nop_ar2_cyclic_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  void lion_nop_ar2_cyclic_s_solve_node( lion_nop_ar2_cyclic_s* o, lion_net_node_s* node, lion_net_node_adl_s* deferred ); \
  static inline void lion_nop_ar2_cyclic_s_mcode_push_ap_track( const lion_nop_ar2_cyclic_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ERR_fa( "Not implemented." );} \
  static inline void lion_nop_ar2_cyclic_s_mcode_push_dp_track( const lion_nop_ar2_cyclic_s* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ERR_fa( "Not implemented." );} \
  static inline sz_t lion_nop_ar2_cyclic_s_mcode_push_dp_holor( const lion_nop_ar2_cyclic_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ){ERR_fa( "Not implemented." ); return -1;}
#define TYPEOF_lion_nop_ar2_rands_s 1572255084
#define BETH_EXPAND_ITEM_lion_nop_ar2_rands_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_rands_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_rands_s_arity( const lion_nop_ar2_rands_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_rands_s_reserved( const lion_nop_ar2_rands_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_rands_s_symbol( const lion_nop_ar2_rands_s* o ){return "rands";} \
  static inline sz_t lion_nop_ar2_rands_s_priority( const lion_nop_ar2_rands_s* o ){return 8;} \
  bl_t lion_nop_ar2_rands_s_solve( const lion_nop_ar2_rands_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  void lion_nop_ar2_rands_s_settle( const lion_nop_ar2_rands_s* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result );
#define TYPEOF_lion_nop_ar2_reshape_s 4210154574
#define BETH_EXPAND_ITEM_lion_nop_ar2_reshape_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_reshape_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_reshape_s_arity( const lion_nop_ar2_reshape_s* o ){return 2;} \
  static inline bl_t lion_nop_ar2_reshape_s_reserved( const lion_nop_ar2_reshape_s* o ){return true;} \
  static inline sc_t lion_nop_ar2_reshape_s_symbol( const lion_nop_ar2_reshape_s* o ){return "reshape";} \
  static inline sz_t lion_nop_ar2_reshape_s_priority( const lion_nop_ar2_reshape_s* o ){return 8;} \
  bl_t lion_nop_ar2_reshape_s_solve( const lion_nop_ar2_reshape_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  void lion_nop_ar2_reshape_s_solve_node( lion_nop_ar2_reshape_s* o, lion_net_node_s* node, lion_net_node_adl_s* deferred );
#define BETH_EXPAND_GROUP_lion_nop_ar2 \
  BCORE_FORWARD_OBJECT( lion_nop_ar2 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_add_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_sub_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_mul_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_div_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_pow_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_bmul_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_equal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_unequal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_larger_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_smaller_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_larger_equal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_smaller_equal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_and_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_or_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_cat_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_ccat_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_order_inc_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_order_dec_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_cyclic_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_rands_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_reshape_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar2_add_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_sub_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_mul_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_div_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_pow_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_bmul_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_equal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_unequal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_larger_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_smaller_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_larger_equal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_smaller_equal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_and_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_or_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_cat_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_ccat_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_order_inc_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_order_dec_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_cyclic_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_rands_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_reshape_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar3

#define TYPEOF_lion_nop_ar3 1828608786
#define TYPEOF_lion_nop_ar3_s 493893900
#define TYPEOF_lion_nop_ar3_iff_s 4098068200
#define BETH_EXPAND_ITEM_lion_nop_ar3_iff_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar3_iff_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar3_iff_s_arity( const lion_nop_ar3_iff_s* o ){return 3;} \
  static inline bl_t lion_nop_ar3_iff_s_reserved( const lion_nop_ar3_iff_s* o ){return true;} \
  static inline sz_t lion_nop_ar3_iff_s_priority( const lion_nop_ar3_iff_s* o ){return 4;} \
  static inline bl_t lion_nop_ar3_iff_s_eci( const lion_nop_ar3_iff_s* o ){return true;} \
  static inline sc_t lion_nop_ar3_iff_s_symbol( const lion_nop_ar3_iff_s* o ){return "iff";} \
  static inline tp_t lion_nop_ar3_iff_s_type_vop_ap( const lion_nop_ar3_iff_s* o ){return TYPEOF_bhvm_vop_ar3_iff_s;} \
  static inline tp_t lion_nop_ar3_iff_s_type_vop_dp_a( const lion_nop_ar3_iff_s* o ){return 0;} \
  static inline tp_t lion_nop_ar3_iff_s_type_vop_dp_b( const lion_nop_ar3_iff_s* o ){return TYPEOF_bhvm_vop_ar2_iff_dp_b_s;} \
  static inline tp_t lion_nop_ar3_iff_s_type_vop_dp_c( const lion_nop_ar3_iff_s* o ){return TYPEOF_bhvm_vop_ar2_iff_dp_c_s;}
#define BETH_EXPAND_GROUP_lion_nop_ar3 \
  BCORE_FORWARD_OBJECT( lion_nop_ar3 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar3_iff_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar3_iff_s

/**********************************************************************************************************************/
// source: lion_eval_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_eval_nop

#define TYPEOF_lion_eval_nop 1484389248
#define TYPEOF_lion_eval_nop_s 4006561370
#define TYPEOF_lion_eval_nop_result_s 1590278622
#define BETH_EXPAND_ITEM_lion_eval_nop_result_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_result_s ) \
    {aware_t _;sz_t total_tests;sz_t solvable_tests;sz_t tolerated_errors;bl_t error;st_s msg;}; \
  void lion_eval_nop_result_s_resolve( const lion_eval_nop_result_s* o );
#define TYPEOF_lion_eval_nop_param_s 1752596292
#define BETH_EXPAND_ITEM_lion_eval_nop_param_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_param_s ) \
    {aware_t _;lion_nop* nop;lion_holor_s* ha;lion_holor_s* hb;lion_holor_s* hc;lion_holor_s* hr;bcore_sink* log;sz_t verbosity;u2_t rval;}; \
  static inline void lion_eval_nop_param_s_init_x( lion_eval_nop_param_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  void lion_eval_nop_param_s_set( lion_eval_nop_param_s* o, const lion_eval_nop_param_s* src );
#define TYPEOF_lion_eval_nop_generator_s 4173681572
#define BETH_EXPAND_ITEM_lion_eval_nop_generator_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_generator_s ) \
    {aware_t _;lion_eval_nop_param_s param;bl_t set_htp;bl_t set_value;bl_t set_shape;bl_t set_dim;bl_t set_v_type;sz_t max_shape_size;sz_t max_dim;f3_t v_min;f3_t v_max;sz_t cycles;bcore_arr_uz_s tolerated_cycles;lion_eval_nop* eval;}; \
  lion_eval_nop_result_s* lion_eval_nop_generator_s_run( const lion_eval_nop_generator_s* o, lion_eval_nop_result_s* result ); \
  static inline void lion_eval_nop_generator_s_set_param( lion_eval_nop_generator_s* o, const lion_eval_nop_param_s* param ){lion_eval_nop_param_s_set( &o->param, param );} \
  s2_t lion_eval_nop_generator_s_main( lion_eval_nop_generator_s* o, const bcore_arr_st_s* args );
#define TYPEOF_lion_eval_nop_show_param_s 1900711168
#define BETH_EXPAND_ITEM_lion_eval_nop_show_param_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_show_param_s ) \
    {aware_t _;lion_eval_nop_param_s param;}; \
  static inline void lion_eval_nop_show_param_s_set_param( lion_eval_nop_show_param_s* o, const lion_eval_nop_param_s* param ){lion_eval_nop_param_s_set( &o->param, param );} \
  s2_t lion_eval_nop_show_param_s_main( lion_eval_nop_show_param_s* o, const bcore_arr_st_s* args ); \
  static inline lion_eval_nop_result_s* lion_eval_nop_show_param_s_run( const lion_eval_nop_show_param_s* o, lion_eval_nop_result_s* result ){bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result;}
#define TYPEOF_lion_eval_nop_arr_s 2430604906
#define BETH_EXPAND_ITEM_lion_eval_nop_arr_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_eval_nop, );}; \
  static inline lion_eval_nop_arr_s* lion_eval_nop_arr_s_set_space( lion_eval_nop_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_eval_nop_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_eval_nop_arr_s* lion_eval_nop_arr_s_set_size( lion_eval_nop_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_eval_nop_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_eval_nop_arr_s* lion_eval_nop_arr_s_clear( lion_eval_nop_arr_s* o ) { bcore_array_t_set_space( TYPEOF_lion_eval_nop_arr_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_eval_nop* lion_eval_nop_arr_s_push_c( lion_eval_nop_arr_s* o, const lion_eval_nop* v ) { bcore_array_t_push( TYPEOF_lion_eval_nop_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_eval_nop* lion_eval_nop_arr_s_push_d( lion_eval_nop_arr_s* o,       lion_eval_nop* v ) { bcore_array_t_push( TYPEOF_lion_eval_nop_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_eval_nop* lion_eval_nop_arr_s_push_t( lion_eval_nop_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_lion_eval_nop, t ); \
      bcore_array_t_push( TYPEOF_lion_eval_nop_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_eval_nop_set_s 4193143789
#define BETH_EXPAND_ITEM_lion_eval_nop_set_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_set_s ) \
    {aware_t _;lion_eval_nop_param_s param;lion_eval_nop_arr_s arr;}; \
  static inline void lion_eval_nop_set_s_set_param( lion_eval_nop_set_s* o, const lion_eval_nop_param_s* param ){lion_eval_nop_param_s_set( &o->param, param );} \
  s2_t lion_eval_nop_set_s_main( lion_eval_nop_set_s* o, const bcore_arr_st_s* args ); \
  lion_eval_nop_result_s* lion_eval_nop_set_s_run( const lion_eval_nop_set_s* o, lion_eval_nop_result_s* result );
#define TYPEOF_lion_eval_nop_ar1_s 4184047427
#define BETH_EXPAND_ITEM_lion_eval_nop_ar1_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_ar1_s ) \
    {aware_t _;lion_eval_nop_param_s param;}; \
  lion_eval_nop_result_s* lion_eval_nop_ar1_s_run( const lion_eval_nop_ar1_s* o, lion_eval_nop_result_s* result ); \
  static inline void lion_eval_nop_ar1_s_set_param( lion_eval_nop_ar1_s* o, const lion_eval_nop_param_s* param ){lion_eval_nop_param_s_set( &o->param, param );} \
  s2_t lion_eval_nop_ar1_s_main( lion_eval_nop_ar1_s* o, const bcore_arr_st_s* args );
#define TYPEOF_lion_eval_nop_ar2_s 3377495594
#define BETH_EXPAND_ITEM_lion_eval_nop_ar2_s \
  BCORE_DECLARE_OBJECT( lion_eval_nop_ar2_s ) \
    {aware_t _;lion_eval_nop_param_s param;}; \
  lion_eval_nop_result_s* lion_eval_nop_ar2_s_run( const lion_eval_nop_ar2_s* o, lion_eval_nop_result_s* result ); \
  static inline void lion_eval_nop_ar2_s_set_param( lion_eval_nop_ar2_s* o, const lion_eval_nop_param_s* param ){lion_eval_nop_param_s_set( &o->param, param );} \
  s2_t lion_eval_nop_ar2_s_main( lion_eval_nop_ar2_s* o, const bcore_arr_st_s* args );
#define BETH_EXPAND_GROUP_lion_eval_nop \
  BCORE_FORWARD_OBJECT( lion_eval_nop ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_result_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_param_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_generator_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_show_param_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_arr_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_set_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_ar1_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_nop_ar2_s ); \
  typedef void (*lion_eval_nop_set_param)( lion_eval_nop* o, const lion_eval_nop_param_s* param ); \
  typedef lion_eval_nop_result_s* (*lion_eval_nop_run)( const lion_eval_nop* o, lion_eval_nop_result_s* result ); \
  BCORE_DECLARE_SPECT( lion_eval_nop ) \
  { \
      bcore_spect_header_s header; \
      lion_eval_nop_set_param set_param; \
      lion_eval_nop_run run; \
  }; \
  static inline lion_eval_nop* lion_eval_nop_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_eval_nop, t ); return ( lion_eval_nop* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_eval_nop_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_eval_nop ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_eval_nop ) \
  static inline bl_t lion_eval_nop_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_eval_nop ); } \
  BETH_EXPAND_ITEM_lion_eval_nop_result_s \
  BETH_EXPAND_ITEM_lion_eval_nop_param_s \
  static inline void lion_eval_nop_a_set_param( lion_eval_nop* o, const lion_eval_nop_param_s* param ) { const lion_eval_nop_s* p = lion_eval_nop_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param ); } \
  static inline bl_t lion_eval_nop_a_defines_set_param( const lion_eval_nop* o ) { return lion_eval_nop_s_get_aware( o )->set_param != NULL; } \
  static inline lion_eval_nop_result_s* lion_eval_nop_a_run( const lion_eval_nop* o, lion_eval_nop_result_s* result ) { const lion_eval_nop_s* p = lion_eval_nop_s_get_aware( o ); assert( p->run ); return p->run( o, result ); } \
  static inline bl_t lion_eval_nop_a_defines_run( const lion_eval_nop* o ) { return lion_eval_nop_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_lion_eval_nop_generator_s \
  BETH_EXPAND_ITEM_lion_eval_nop_show_param_s \
  BETH_EXPAND_ITEM_lion_eval_nop_arr_s \
  BETH_EXPAND_ITEM_lion_eval_nop_set_s \
  BETH_EXPAND_ITEM_lion_eval_nop_ar1_s \
  BETH_EXPAND_ITEM_lion_eval_nop_ar2_s

/**********************************************************************************************************************/
// source: lion_sem.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_sem

#define TYPEOF_lion_sem 2576968235
#define TYPEOF_lion_sem_s 2089841725
#define TYPEOF_lion_sem_context_s 2384100905
#define BETH_EXPAND_ITEM_lion_sem_context_s \
  BCORE_DECLARE_OBJECT( lion_sem_context_s ) \
    {aware_t _;bcore_hmap_name_s hmap_name;bcore_arr_st_s arr_symbol_op2;lion_sem_cell_s* cell;bcore_hmap_tp_s control_types;bcore_hmap_tp_s reserved_names;};
#define TYPEOF_cell 1759288501
#define TYPEOF_lion_sem_link_s 2798512654
#define BETH_EXPAND_ITEM_lion_sem_link_s \
  BCORE_DECLARE_OBJECT( lion_sem_link_s ) \
    {aware_t _;tp_t name;bl_t visible;lion_sem_link_s* up;lion_sem_link_s* dn;vd_t cell;bl_t exit;}; \
  static inline tp_t lion_sem_link_s_get_name( const lion_sem_link_s* o ){return o->name;} \
  static inline bl_t lion_sem_link_s_is_visible( const lion_sem_link_s* o ){return o->visible;}
#define TYPEOF_lion_sem_links_s 2159338623
#define BETH_EXPAND_ITEM_lion_sem_links_s \
  BCORE_DECLARE_OBJECT( lion_sem_links_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_sem_link_s, );}; \
  lion_sem_link_s* lion_sem_links_s_get_link_by_name( lion_sem_links_s* o, tp_t name ); \
  bl_t lion_sem_links_s_name_exists( const lion_sem_links_s* o, tp_t name ); \
  lion_sem_link_s* lion_sem_links_s_get_link_by_up( lion_sem_links_s* o, lion_sem_link_s* up ); \
  lion_sem_link_s* lion_sem_links_s_get_link_by_dn( lion_sem_links_s* o, lion_sem_link_s* dn ); \
  sz_t lion_sem_links_s_get_index_by_link( lion_sem_links_s* o, lion_sem_link_s* link ); \
  sz_t lion_sem_links_s_count_open( const lion_sem_links_s* o ); \
  static inline lion_sem_links_s* lion_sem_links_s_set_space( lion_sem_links_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_sem_links_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_sem_links_s* lion_sem_links_s_set_size( lion_sem_links_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_sem_links_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_sem_links_s* lion_sem_links_s_clear( lion_sem_links_s* o ) { bcore_array_t_set_space( TYPEOF_lion_sem_links_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_sem_link_s* lion_sem_links_s_push_c( lion_sem_links_s* o, const lion_sem_link_s* v ) { bcore_array_t_push( TYPEOF_lion_sem_links_s, ( bcore_array* )o, sr_twc( TYPEOF_lion_sem_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_sem_link_s* lion_sem_links_s_push_d( lion_sem_links_s* o,       lion_sem_link_s* v ) { bcore_array_t_push( TYPEOF_lion_sem_links_s, ( bcore_array* )o, sr_tsd( TYPEOF_lion_sem_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_sem_link_s* lion_sem_links_s_push( lion_sem_links_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_lion_sem_links_s, ( bcore_array* )o, sr_t_create( TYPEOF_lion_sem_link_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_sem_body_s 1290276002
#define BETH_EXPAND_ITEM_lion_sem_body_s \
  BCORE_DECLARE_OBJECT( lion_sem_body_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_sem, );}; \
  bl_t lion_sem_body_s_name_exists( const lion_sem_body_s* o, tp_t name ); \
  lion_sem* lion_sem_body_s_get_sem_by_name( lion_sem_body_s* o, tp_t name ); \
  static inline lion_sem_body_s* lion_sem_body_s_set_space( lion_sem_body_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_sem_body_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_sem_body_s* lion_sem_body_s_set_size( lion_sem_body_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_sem_body_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_sem_body_s* lion_sem_body_s_clear( lion_sem_body_s* o ) { bcore_array_t_set_space( TYPEOF_lion_sem_body_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_sem* lion_sem_body_s_push_c( lion_sem_body_s* o, const lion_sem* v ) { bcore_array_t_push( TYPEOF_lion_sem_body_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_sem* lion_sem_body_s_push_d( lion_sem_body_s* o,       lion_sem* v ) { bcore_array_t_push( TYPEOF_lion_sem_body_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_sem* lion_sem_body_s_push_t( lion_sem_body_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_lion_sem, t ); \
      bcore_array_t_push( TYPEOF_lion_sem_body_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_sem_cell_s 2003406506
#define BETH_EXPAND_ITEM_lion_sem_cell_s \
  BCORE_DECLARE_OBJECT( lion_sem_cell_s ) \
    {aware_t _;tp_t name;lion_sem_links_s encs;lion_sem_links_s excs;lion_sem_body_s* body;lion_nop* nop;lion_sem_cell_s* wrapped_cell;sz_t priority;lion_sem_cell_s* parent;bcore_source_point_s source_point;}; \
  static inline tp_t lion_sem_cell_s_get_name( const lion_sem_cell_s* o ){return o->name;} \
  static inline sz_t lion_sem_cell_s_get_arity( const lion_sem_cell_s* o ){return lion_sem_links_s_count_open(       &o->encs       );} \
  static inline lion_sem_link_s* lion_sem_cell_s_get_enc_by_name( lion_sem_cell_s* o, tp_t name ){return lion_sem_links_s_get_link_by_name( &o->encs, name );} \
  static inline lion_sem_link_s* lion_sem_cell_s_get_exc_by_name( lion_sem_cell_s* o, tp_t name ){return lion_sem_links_s_get_link_by_name( &o->excs, name );} \
  static inline lion_sem_link_s* lion_sem_cell_s_get_enc_by_open( lion_sem_cell_s* o ){return lion_sem_links_s_get_link_by_up(   &o->encs, NULL );} \
  static inline lion_sem_link_s* lion_sem_cell_s_get_enc_by_dn( lion_sem_cell_s* o, lion_sem_link_s* dn ){return lion_sem_links_s_get_link_by_dn(   &o->encs, dn   );} \
  static inline sz_t lion_sem_cell_s_get_priority( const lion_sem_cell_s* o ){return o->priority;} \
  static inline bl_t lion_sem_cell_s_is_wrapper( const lion_sem_cell_s* o ){return o->wrapped_cell != NULL && o->nop == NULL && o->body == NULL;} \
  lion_sem_cell_s* lion_sem_cell_s_get_cell_by_name( lion_sem_cell_s* o, tp_t name ); \
  lion_sem_link_s* lion_sem_cell_s_get_link_by_name( lion_sem_cell_s* o, tp_t name );
#define TYPEOF_lion_sem_stack_flag_s 3570599949
#define BETH_EXPAND_ITEM_lion_sem_stack_flag_s \
  BCORE_DECLARE_OBJECT( lion_sem_stack_flag_s ) \
    {aware_t _;};
#define BETH_EXPAND_GROUP_lion_sem \
  BCORE_FORWARD_OBJECT( lion_sem ); \
  BCORE_FORWARD_OBJECT( lion_sem_context_s ); \
  BCORE_FORWARD_OBJECT( lion_sem_link_s ); \
  BCORE_FORWARD_OBJECT( lion_sem_links_s ); \
  BCORE_FORWARD_OBJECT( lion_sem_body_s ); \
  BCORE_FORWARD_OBJECT( lion_sem_cell_s ); \
  BCORE_FORWARD_OBJECT( lion_sem_stack_flag_s ); \
  typedef tp_t (*lion_sem_get_name)( const lion_sem* o ); \
  typedef bl_t (*lion_sem_is_visible)( const lion_sem* o ); \
  BCORE_DECLARE_SPECT( lion_sem ) \
  { \
      bcore_spect_header_s header; \
      lion_sem_get_name get_name; \
      lion_sem_is_visible is_visible; \
  }; \
  static inline lion_sem* lion_sem_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_sem, t ); return ( lion_sem* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_sem_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_sem ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_sem ) \
  static inline bl_t lion_sem_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_sem ); } \
  BETH_EXPAND_ITEM_lion_sem_context_s \
  static inline tp_t lion_sem_a_get_name( const lion_sem* o ) { const lion_sem_s* p = lion_sem_s_get_aware( o ); assert( p->get_name ); return p->get_name( o ); } \
  static inline bl_t lion_sem_a_defines_get_name( const lion_sem* o ) { return true; } \
  static inline tp_t lion_sem_get_name__( const lion_sem* o ){return 0;} \
  static inline bl_t lion_sem_a_is_visible( const lion_sem* o ) { const lion_sem_s* p = lion_sem_s_get_aware( o ); assert( p->is_visible ); return p->is_visible( o ); } \
  static inline bl_t lion_sem_a_defines_is_visible( const lion_sem* o ) { return true; } \
  static inline bl_t lion_sem_is_visible__( const lion_sem* o ){return true;} \
  BETH_EXPAND_ITEM_lion_sem_link_s \
  BETH_EXPAND_ITEM_lion_sem_links_s \
  BETH_EXPAND_ITEM_lion_sem_body_s \
  BETH_EXPAND_ITEM_lion_sem_cell_s \
  BETH_EXPAND_ITEM_lion_sem_stack_flag_s

/**********************************************************************************************************************/
// source: lion_net.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_ctr

#define TYPEOF_lion_ctr 3678855967
#define TYPEOF_lion_ctr_s 4057964745
#define TYPEOF_lion_ctr_node_s 1758155246
#define BETH_EXPAND_ITEM_lion_ctr_node_s \
  BCORE_DECLARE_OBJECT( lion_ctr_node_s ) \
    {aware_t _;sz_t id;lion_sem_cell_s* cell;lion_ctr_node_s* parent;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_ctr_node_s, );}; \
  static inline lion_ctr_node_s* lion_ctr_node_s_set_space( lion_ctr_node_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_ctr_node_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_ctr_node_s* lion_ctr_node_s_set_size( lion_ctr_node_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_ctr_node_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_ctr_node_s* lion_ctr_node_s_clear( lion_ctr_node_s* o ) { bcore_array_t_set_space( TYPEOF_lion_ctr_node_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_ctr_node_s* lion_ctr_node_s_push_c( lion_ctr_node_s* o, const lion_ctr_node_s* v ) { bcore_array_t_push( TYPEOF_lion_ctr_node_s, ( bcore_array* )o, sr_twc( TYPEOF_lion_ctr_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_ctr_node_s* lion_ctr_node_s_push_d( lion_ctr_node_s* o,       lion_ctr_node_s* v ) { bcore_array_t_push( TYPEOF_lion_ctr_node_s, ( bcore_array* )o, sr_tsd( TYPEOF_lion_ctr_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_ctr_node_s* lion_ctr_node_s_push( lion_ctr_node_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_lion_ctr_node_s, ( bcore_array* )o, sr_t_create( TYPEOF_lion_ctr_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_ctr_tree_s 1294183698
#define BETH_EXPAND_ITEM_lion_ctr_tree_s \
  BCORE_DECLARE_OBJECT( lion_ctr_tree_s ) \
    {aware_t _;sz_t id_base;lion_ctr_node_s* root;};
#define BETH_EXPAND_GROUP_lion_ctr \
  BCORE_FORWARD_OBJECT( lion_ctr ); \
  BCORE_FORWARD_OBJECT( lion_ctr_node_s ); \
  BCORE_FORWARD_OBJECT( lion_ctr_tree_s ); \
  BETH_EXPAND_ITEM_lion_ctr_node_s \
  BETH_EXPAND_ITEM_lion_ctr_tree_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_net

#define TYPEOF_lion_net 2482589547
#define TYPEOF_lion_net_s 2858941821
#define TYPEOF_lion_net_link_s 2439788110
#define BETH_EXPAND_ITEM_lion_net_link_s \
  BCORE_DECLARE_OBJECT( lion_net_link_s ) \
    {aware_t _;vd_t node;};
#define TYPEOF_lion_net_links_s 2548442047
#define BETH_EXPAND_ITEM_lion_net_links_s \
  BCORE_DECLARE_OBJECT( lion_net_links_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_net_link_s, );}; \
  static inline lion_net_links_s* lion_net_links_s_set_space( lion_net_links_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_net_links_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_net_links_s* lion_net_links_s_set_size( lion_net_links_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_net_links_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_net_links_s* lion_net_links_s_clear( lion_net_links_s* o ) { bcore_array_t_set_space( TYPEOF_lion_net_links_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_net_link_s* lion_net_links_s_push_c( lion_net_links_s* o, const lion_net_link_s* v ) { bcore_array_t_push( TYPEOF_lion_net_links_s, ( bcore_array* )o, sr_twc( TYPEOF_lion_net_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_net_link_s* lion_net_links_s_push_d( lion_net_links_s* o,       lion_net_link_s* v ) { bcore_array_t_push( TYPEOF_lion_net_links_s, ( bcore_array* )o, sr_tsd( TYPEOF_lion_net_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_net_link_s* lion_net_links_s_push( lion_net_links_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_lion_net_links_s, ( bcore_array* )o, sr_t_create( TYPEOF_lion_net_link_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_net_node_s 950517890
#define BETH_EXPAND_ITEM_lion_net_node_s \
  BCORE_DECLARE_OBJECT( lion_net_node_s ) \
    {aware_t _;lion_net_links_s upls;lion_net_links_s dnls;tp_t name;bl_t flag;bl_t probe;sz_t id;bhvm_mcode_node_s* mnode;lion_nop* nop;lion_nop_solve_result_s* result;bcore_source_point_s* source_point;}; \
  sz_t lion_net_node_s_up_index( const lion_net_node_s* o, const lion_net_node_s* node ); \
  void lion_net_node_s_set_nop_d( lion_net_node_s* o, lion_nop* nop ); \
  static inline bl_t lion_net_node_s_is_cyclic( const lion_net_node_s* o ){return ( o->mnode ) ? o->mnode->cyclic : lion_nop_a_is_cyclic( o->nop );}
#define TYPEOF_lion_net_node_adl_s 2426533502
#define BETH_EXPAND_ITEM_lion_net_node_adl_s \
  BCORE_DECLARE_OBJECT( lion_net_node_adl_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_net_node_s, );}; \
  static inline lion_net_node_adl_s* lion_net_node_adl_s_set_space( lion_net_node_adl_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_net_node_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_net_node_adl_s* lion_net_node_adl_s_set_size( lion_net_node_adl_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_net_node_adl_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_net_node_adl_s* lion_net_node_adl_s_clear( lion_net_node_adl_s* o ) { bcore_array_t_set_space( TYPEOF_lion_net_node_adl_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_net_node_s* lion_net_node_adl_s_push_c( lion_net_node_adl_s* o, const lion_net_node_s* v ) { bcore_array_t_push( TYPEOF_lion_net_node_adl_s, ( bcore_array* )o, sr_twc( TYPEOF_lion_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_net_node_s* lion_net_node_adl_s_push_d( lion_net_node_adl_s* o,       lion_net_node_s* v ) { bcore_array_t_push( TYPEOF_lion_net_node_adl_s, ( bcore_array* )o, sr_tsd( TYPEOF_lion_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_net_node_s* lion_net_node_adl_s_push( lion_net_node_adl_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_lion_net_node_adl_s, ( bcore_array* )o, sr_t_create( TYPEOF_lion_net_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_net_nodes_s 2164516443
#define BETH_EXPAND_ITEM_lion_net_nodes_s \
  BCORE_DECLARE_OBJECT( lion_net_nodes_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_net_node_s, );}; \
  lion_net_node_s* lion_net_nodes_s_get_by_id( lion_net_nodes_s* o, sz_t id ); \
  static inline lion_net_nodes_s* lion_net_nodes_s_set_space( lion_net_nodes_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_net_nodes_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_net_nodes_s* lion_net_nodes_s_set_size( lion_net_nodes_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_net_nodes_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_net_nodes_s* lion_net_nodes_s_clear( lion_net_nodes_s* o ) { bcore_array_t_set_space( TYPEOF_lion_net_nodes_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_net_node_s* lion_net_nodes_s_push_c( lion_net_nodes_s* o, const lion_net_node_s* v ) { bcore_array_t_push( TYPEOF_lion_net_nodes_s, ( bcore_array* )o, sr_twc( TYPEOF_lion_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_net_node_s* lion_net_nodes_s_push_d( lion_net_nodes_s* o,       lion_net_node_s* v ) { bcore_array_t_push( TYPEOF_lion_net_nodes_s, ( bcore_array* )o, sr_tsd( TYPEOF_lion_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_net_node_s* lion_net_nodes_s_push( lion_net_nodes_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_lion_net_nodes_s, ( bcore_array* )o, sr_t_create( TYPEOF_lion_net_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_net_cell_s 2110716138
#define BETH_EXPAND_ITEM_lion_net_cell_s \
  BCORE_DECLARE_OBJECT( lion_net_cell_s ) \
    {aware_t _;sz_t max_depth;lion_net_nodes_s body;lion_net_nodes_s encs;lion_net_nodes_s excs;}; \
  bl_t lion_net_cell_s_is_consistent( const lion_net_cell_s* o ); \
  void lion_net_cell_s_normalize( lion_net_cell_s* o ); \
  void lion_net_cell_s_clear_flags( lion_net_cell_s* o ); \
  void lion_net_cell_s_clear_all_flags( lion_net_cell_s* o ); \
  void lion_net_cell_s_solve( lion_net_cell_s* o ); \
  void lion_net_cell_s_clear_downlinks( lion_net_cell_s* o ); \
  void lion_net_cell_s_set_downlinks( lion_net_cell_s* o ); \
  void lion_net_cell_s_copy_x( lion_net_cell_s* o ); \
  static inline void lion_net_cell_s_mutated( lion_net_cell_s* o ){ERR_fa( "Cannot reconstitute." );}
#define BETH_EXPAND_GROUP_lion_net \
  BCORE_FORWARD_OBJECT( lion_net ); \
  BCORE_FORWARD_OBJECT( lion_net_link_s ); \
  BCORE_FORWARD_OBJECT( lion_net_links_s ); \
  BCORE_FORWARD_OBJECT( lion_net_node_s ); \
  BCORE_FORWARD_OBJECT( lion_net_node_adl_s ); \
  BCORE_FORWARD_OBJECT( lion_net_nodes_s ); \
  BCORE_FORWARD_OBJECT( lion_net_cell_s ); \
  typedef bl_t (*lion_net_is_cyclic)( const lion_net* o ); \
  BCORE_DECLARE_SPECT( lion_net ) \
  { \
      bcore_spect_header_s header; \
      lion_net_is_cyclic is_cyclic; \
  }; \
  static inline lion_net* lion_net_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_net, t ); return ( lion_net* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_net_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_net ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_net ) \
  static inline bl_t lion_net_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_net ); } \
  BETH_EXPAND_ITEM_lion_net_link_s \
  BETH_EXPAND_ITEM_lion_net_links_s \
  static inline bl_t lion_net_a_is_cyclic( const lion_net* o ) { const lion_net_s* p = lion_net_s_get_aware( o ); assert( p->is_cyclic ); return p->is_cyclic( o ); } \
  static inline bl_t lion_net_a_defines_is_cyclic( const lion_net* o ) { return true; } \
  static inline bl_t lion_net_is_cyclic__( const lion_net* o ){return false;} \
  BETH_EXPAND_ITEM_lion_net_node_s \
  BETH_EXPAND_ITEM_lion_net_node_adl_s \
  BETH_EXPAND_ITEM_lion_net_nodes_s \
  BETH_EXPAND_ITEM_lion_net_cell_s

/**********************************************************************************************************************/
// source: lion_frame.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_frame

#define TYPEOF_lion_frame 1636885453
#define TYPEOF_lion_frame_s 1392811455
#define TYPEOF_lion_frame_s 1392811455
#define BETH_EXPAND_ITEM_lion_frame_s \
  BCORE_DECLARE_OBJECT( lion_frame_s ) \
    {aware_t _;bcore_sink* log;bhvm_mcode_frame_s* mcf;bl_t is_cyclic;bl_t setup;sz_t size_en;sz_t size_ex;lion_frame_hidx_s hidx_en;lion_frame_hidx_s hidx_ex;lion_frame_hidx_s hidx_ada;}; \
  void lion_frame_s_reset( lion_frame_s* o ); \
  lion_frame_s* lion_frame_s_bind_holors( lion_frame_s* o ); \
  void lion_frame_s_setup( lion_frame_s* o ); \
  void lion_frame_s_check_integrity( const lion_frame_s* o ); \
  static inline void lion_frame_s_shelve( lion_frame_s* o ){bl_t setup = o->setup; lion_frame_s_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */} \
  static inline void lion_frame_s_mutated( lion_frame_s* o ){if( o->setup ) { lion_frame_s_reset( o ); lion_frame_s_setup( o ); }  lion_frame_s_check_integrity( o );} \
  static inline void lion_frame_s_copy_x( lion_frame_s* o ){if( o->setup ) { lion_frame_s_reset( o ); lion_frame_s_setup( o ); }  lion_frame_s_check_integrity( o );} \
  lion_frame_s* lion_frame_s_setup_from_source( lion_frame_s* o, bcore_source* source, const bhvm_holor_s** en, sz_t size_en ); \
  static inline lion_frame_s* lion_frame_s_setup_from_st( lion_frame_s* o, const st_s* st, const bhvm_holor_s** en, sz_t size_en ){BLM_INIT(); BLM_RETURNV( lion_frame_s*, lion_frame_s_setup_from_source( o, BLM_A_PUSH( bcore_source_string_s_create_from_string( st ) ), en, size_en ) );} \
  static inline lion_frame_s* lion_frame_s_setup_from_sc( lion_frame_s* o, sc_t sc, const bhvm_holor_s** en, sz_t size_en ){st_s st; st_s_init_weak_sc( &st, sc ); return lion_frame_s_setup_from_st( o, &st, en, size_en );} \
  static inline lion_frame_s* lion_frame_s_create_from_source( bcore_source* source, const bhvm_holor_s** en, sz_t size_en ){lion_frame_s* o = lion_frame_s_create(); return lion_frame_s_setup_from_source( o, source, en, size_en );} \
  static inline lion_frame_s* lion_frame_s_create_from_st( const st_s* st, const bhvm_holor_s** en, sz_t size_en ){lion_frame_s* o = lion_frame_s_create(); return lion_frame_s_setup_from_st(     o, st,     en, size_en );} \
  static inline lion_frame_s* lion_frame_s_create_from_sc( sc_t sc, const bhvm_holor_s** en, sz_t size_en ){lion_frame_s* o = lion_frame_s_create(); return lion_frame_s_setup_from_sc(     o, sc,     en, size_en );} \
  static inline lion_frame_s* lion_frame_s_setup_from_source_adl( lion_frame_s* o, bcore_source* source, const bhvm_holor_adl_s* en ){return lion_frame_s_setup_from_source( o, source, en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline lion_frame_s* lion_frame_s_setup_from_st_adl( lion_frame_s* o, const st_s* st, const bhvm_holor_adl_s* en ){return lion_frame_s_setup_from_st(     o, st,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline lion_frame_s* lion_frame_s_setup_from_sc_adl( lion_frame_s* o, sc_t sc, const bhvm_holor_adl_s* en ){return lion_frame_s_setup_from_sc(     o, sc,     en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline lion_frame_s* lion_frame_s_create_from_source_adl( bcore_source* source, const bhvm_holor_adl_s* en ){return lion_frame_s_create_from_source( source,   en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline lion_frame_s* lion_frame_s_create_from_st_adl( const st_s* st, const bhvm_holor_adl_s* en ){return lion_frame_s_create_from_st( st,           en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline lion_frame_s* lion_frame_s_create_from_sc_adl( sc_t sc, const bhvm_holor_adl_s* en ){return lion_frame_s_create_from_sc( sc,           en ? ( const bhvm_holor_s** )en->data : NULL, en ? en->size : 0 );} \
  static inline sz_t lion_frame_s_get_size_en( const lion_frame_s* o ){return lion_frame_hidx_s_get_size( &o->hidx_en );} \
  static inline sz_t lion_frame_s_get_size_ex( const lion_frame_s* o ){return lion_frame_hidx_s_get_size( &o->hidx_ex );} \
  static inline sz_t lion_frame_s_get_size_ada( const lion_frame_s* o ){return lion_frame_hidx_s_get_size( &o->hidx_ada );} \
  static inline bhvm_holor_s* lion_frame_s_get_ap_en( lion_frame_s* o, sz_t index ){return lion_frame_hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* lion_frame_s_get_dp_en( lion_frame_s* o, sz_t index ){return lion_frame_hidx_s_get_pclass_holor( &o->hidx_en,  o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  static inline bhvm_holor_s* lion_frame_s_get_ap_ex( lion_frame_s* o, sz_t index ){return lion_frame_hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* lion_frame_s_get_dp_ex( lion_frame_s* o, sz_t index ){return lion_frame_hidx_s_get_pclass_holor( &o->hidx_ex,  o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  static inline bhvm_holor_s* lion_frame_s_get_ap_ada( lion_frame_s* o, sz_t index ){return lion_frame_hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ax0, index );} \
  static inline bhvm_holor_s* lion_frame_s_get_dp_ada( lion_frame_s* o, sz_t index ){return lion_frame_hidx_s_get_pclass_holor( &o->hidx_ada, o->mcf->hbase, TYPEOF_pclass_ag0, index );} \
  lion_frame_s* lion_frame_s_run_ap( lion_frame_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex ); \
  lion_frame_s* lion_frame_s_run_dp( lion_frame_s* o, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en ); \
  lion_frame_s* lion_frame_s_run_ap_adl( lion_frame_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex ); \
  lion_frame_s* lion_frame_s_run_dp_adl( lion_frame_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en );
#define TYPEOF_lion_frame_custom_hmeta_s 420203025
#define BETH_EXPAND_ITEM_lion_frame_custom_hmeta_s \
  BCORE_DECLARE_OBJECT( lion_frame_custom_hmeta_s ) \
    {aware_t _;sz_t ur_slot;sz_t ur_src;};
#define TYPEOF_lion_frame_cyclic_s 3706646511
#define BETH_EXPAND_ITEM_lion_frame_cyclic_s \
  BCORE_DECLARE_OBJECT( lion_frame_cyclic_s ) \
    {aware_t _;lion_frame_s* frame;sz_t unroll_size;bl_t setup;sz_t unroll_index;bhvm_mcode_track_adl_s* track_adl_ap;bhvm_mcode_track_adl_s* track_adl_dp;bhvm_mcode_track_adl_s* track_adl_ap_setup;lion_frame_hidx_ads_s hidx_ads_en;lion_frame_hidx_ads_s hidx_ads_ex;}; \
  lion_frame_cyclic_s* lion_frame_cyclic_s_bind_holors( lion_frame_cyclic_s* o ); \
  void lion_frame_cyclic_s_reset( lion_frame_cyclic_s* o ); \
  void lion_frame_cyclic_s_setup( lion_frame_cyclic_s* o ); \
  static inline void lion_frame_cyclic_s_shelve( lion_frame_cyclic_s* o ){bl_t setup = o->setup; lion_frame_cyclic_s_reset( o ); o->setup = setup; /* setup flag remembers o's setup state before shelving */} \
  static inline void lion_frame_cyclic_s_mutated( lion_frame_cyclic_s* o ){if( o->setup ) { lion_frame_cyclic_s_reset( o ); lion_frame_cyclic_s_setup( o ); }} \
  static inline void lion_frame_cyclic_s_copy_x( lion_frame_cyclic_s* o ){if( o->setup ) { lion_frame_cyclic_s_reset( o ); lion_frame_cyclic_s_setup( o ); }} \
  static inline sz_t lion_frame_cyclic_s_get_size_en( const lion_frame_cyclic_s* o ){return lion_frame_s_get_size_en(  o->frame );} \
  static inline sz_t lion_frame_cyclic_s_get_size_ex( const lion_frame_cyclic_s* o ){return lion_frame_s_get_size_ex(  o->frame );} \
  static inline sz_t lion_frame_cyclic_s_get_size_ada( const lion_frame_cyclic_s* o ){return lion_frame_s_get_size_ada( o->frame );} \
  lion_frame_cyclic_s* lion_frame_cyclic_s_run_ap( lion_frame_cyclic_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex ); \
  lion_frame_cyclic_s* lion_frame_cyclic_s_run_ap_adl( lion_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex );
#define BETH_EXPAND_GROUP_lion_frame \
  BCORE_FORWARD_OBJECT( lion_frame ); \
  BCORE_FORWARD_OBJECT( lion_frame_hidx ); \
  BCORE_FORWARD_OBJECT( lion_frame_s ); \
  BCORE_FORWARD_OBJECT( lion_frame_custom_hmeta_s ); \
  BCORE_FORWARD_OBJECT( lion_frame_cyclic_s ); \
  BETH_EXPAND_GROUP_lion_frame_hidx \
  BETH_EXPAND_ITEM_lion_frame_s \
  BETH_EXPAND_ITEM_lion_frame_custom_hmeta_s \
  BETH_EXPAND_ITEM_lion_frame_cyclic_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_frame_hidx

#define TYPEOF_lion_frame_hidx 1807719741
#define TYPEOF_lion_frame_hidx_s 945563247
#define TYPEOF_lion_frame_hidx_s 945563247
#define BETH_EXPAND_ITEM_lion_frame_hidx_s \
  BCORE_DECLARE_OBJECT( lion_frame_hidx_s ) \
    {aware_t _;bcore_arr_sz_s* arr;}; \
  static inline lion_frame_hidx_s* lion_frame_hidx_s_clear( lion_frame_hidx_s* o ){if( o->arr ) bcore_arr_sz_s_clear( o->arr ); return o;} \
  static inline lion_frame_hidx_s* lion_frame_hidx_s_push( lion_frame_hidx_s* o, sz_t index ){if( !o->arr ) o->arr = bcore_arr_sz_s_create(); bcore_arr_sz_s_push( o->arr, index ); return o;} \
  static inline sz_t lion_frame_hidx_s_get_idx( const lion_frame_hidx_s* o, sz_t index ){assert( o->arr ); assert( index >= 0 && index < o->arr->size ); return o->arr->data[ index ];} \
  static inline sz_t lion_frame_hidx_s_get_size( const lion_frame_hidx_s* o ){return o->arr ? o->arr->size : 0;} \
  static inline bhvm_holor_s* lion_frame_hidx_s_get_holor( const lion_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ){return bhvm_mcode_hbase_s_get_holor( hbase, lion_frame_hidx_s_get_idx( o, index ) );} \
  static inline bhvm_mcode_hmeta* lion_frame_hidx_s_get_hmeta( const lion_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, sz_t index ){return bhvm_mcode_hbase_s_get_hmeta( hbase, lion_frame_hidx_s_get_idx( o, index ) );} \
  sz_t lion_frame_hidx_s_get_pclass_idx( const lion_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ); \
  static inline bhvm_holor_s* lion_frame_hidx_s_get_pclass_holor( const lion_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ){return bhvm_mcode_hbase_s_get_holor( hbase, lion_frame_hidx_s_get_pclass_idx( o, hbase, pclass, index ) );} \
  static inline bhvm_mcode_hmeta* lion_frame_hidx_s_get_pclass_hmeta( const lion_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index ){return bhvm_mcode_hbase_s_get_hmeta( hbase, lion_frame_hidx_s_get_pclass_idx( o, hbase, pclass, index ) );} \
  lion_frame_hidx_s* lion_frame_hidx_s_replace_index( lion_frame_hidx_s* o, bcore_arr_sz_s* index_map );
#define TYPEOF_lion_frame_hidx_ads_s 1065889082
#define BETH_EXPAND_ITEM_lion_frame_hidx_ads_s \
  BCORE_DECLARE_OBJECT( lion_frame_hidx_ads_s ) \
    {aware_t _;BCORE_ARRAY_DYN_SOLID_STATIC_S( lion_frame_hidx_s, );}; \
  static inline lion_frame_hidx_ads_s* lion_frame_hidx_ads_s_set_space( lion_frame_hidx_ads_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_frame_hidx_ads_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_frame_hidx_ads_s* lion_frame_hidx_ads_s_set_size( lion_frame_hidx_ads_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_frame_hidx_ads_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_frame_hidx_ads_s* lion_frame_hidx_ads_s_clear( lion_frame_hidx_ads_s* o ) { bcore_array_t_set_space( TYPEOF_lion_frame_hidx_ads_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_frame_hidx_s* lion_frame_hidx_ads_s_push_c( lion_frame_hidx_ads_s* o, const lion_frame_hidx_s* v ) { bcore_array_t_push( TYPEOF_lion_frame_hidx_ads_s, ( bcore_array* )o, sr_twc( TYPEOF_lion_frame_hidx_s, v ) ); return &o->data[ o->size - 1 ]; } \
  static inline lion_frame_hidx_s* lion_frame_hidx_ads_s_push_d( lion_frame_hidx_ads_s* o,       lion_frame_hidx_s* v ) { bcore_array_t_push( TYPEOF_lion_frame_hidx_ads_s, ( bcore_array* )o, sr_tsd( TYPEOF_lion_frame_hidx_s, v ) ); return &o->data[ o->size - 1 ]; } \
  static inline lion_frame_hidx_s* lion_frame_hidx_ads_s_push( lion_frame_hidx_ads_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_lion_frame_hidx_ads_s, ( bcore_array* )o, sr_null() ); \
      return &o->data[ o->size - 1 ]; \
  }
#define BETH_EXPAND_GROUP_lion_frame_hidx \
  BCORE_FORWARD_OBJECT( lion_frame_hidx ); \
  BCORE_FORWARD_OBJECT( lion_frame_hidx_s ); \
  BCORE_FORWARD_OBJECT( lion_frame_hidx_ads_s ); \
  BETH_EXPAND_ITEM_lion_frame_hidx_s \
  BETH_EXPAND_ITEM_lion_frame_hidx_ads_s

/**********************************************************************************************************************/
// source: lion_eval_frame.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_eval_frame

#define TYPEOF_lion_eval_frame 661774064
#define TYPEOF_lion_eval_frame_s 3123776778
#define TYPEOF_lion_eval_frame_result_s 3567974798
#define BETH_EXPAND_ITEM_lion_eval_frame_result_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_result_s ) \
    {aware_t _;bl_t error;st_s msg;}; \
  void lion_eval_frame_result_s_resolve( lion_eval_frame_result_s* o );
#define TYPEOF_lion_eval_frame_param_s 1608970388
#define BETH_EXPAND_ITEM_lion_eval_frame_param_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_param_s ) \
    {aware_t _;bcore_sink* log;sz_t verbosity;u2_t rval;st_s name;vd_t src;bhvm_holor_adl_s* in;bhvm_holor_adl_s* out;bl_t recovery_test;bl_t jacobian_test;f3_t max_dev;f3_t epsilon;}; \
  static inline void lion_eval_frame_param_s_init_x( lion_eval_frame_param_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  void lion_eval_frame_param_s_set( lion_eval_frame_param_s* o, const lion_eval_frame_param_s* src );
#define TYPEOF_lion_eval_frame_show_param_s 3596640144
#define BETH_EXPAND_ITEM_lion_eval_frame_show_param_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_show_param_s ) \
    {aware_t _;lion_eval_frame_param_s param;}; \
  static inline void lion_eval_frame_show_param_s_set_param( lion_eval_frame_show_param_s* o, const lion_eval_frame_param_s* param ){lion_eval_frame_param_s_set( &o->param, param );} \
  s2_t lion_eval_frame_show_param_s_main( lion_eval_frame_show_param_s* o, const bcore_arr_st_s* args ); \
  static inline lion_eval_frame_result_s* lion_eval_frame_show_param_s_run( const lion_eval_frame_show_param_s* o, lion_eval_frame_result_s* result ){bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result;}
#define TYPEOF_lion_eval_frame_arr_s 1320617274
#define BETH_EXPAND_ITEM_lion_eval_frame_arr_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_eval_frame, );}; \
  static inline lion_eval_frame_arr_s* lion_eval_frame_arr_s_set_space( lion_eval_frame_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_eval_frame_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_eval_frame_arr_s* lion_eval_frame_arr_s_set_size( lion_eval_frame_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_eval_frame_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline lion_eval_frame_arr_s* lion_eval_frame_arr_s_clear( lion_eval_frame_arr_s* o ) { bcore_array_t_set_space( TYPEOF_lion_eval_frame_arr_s, ( bcore_array* )o, 0 ); return o; } \
  static inline lion_eval_frame* lion_eval_frame_arr_s_push_c( lion_eval_frame_arr_s* o, const lion_eval_frame* v ) { bcore_array_t_push( TYPEOF_lion_eval_frame_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_eval_frame* lion_eval_frame_arr_s_push_d( lion_eval_frame_arr_s* o,       lion_eval_frame* v ) { bcore_array_t_push( TYPEOF_lion_eval_frame_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_eval_frame* lion_eval_frame_arr_s_push_t( lion_eval_frame_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_lion_eval_frame, t ); \
      bcore_array_t_push( TYPEOF_lion_eval_frame_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_eval_frame_set_s 166463869
#define BETH_EXPAND_ITEM_lion_eval_frame_set_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_set_s ) \
    {aware_t _;lion_eval_frame_param_s param;lion_eval_frame_arr_s arr;}; \
  static inline void lion_eval_frame_set_s_set_param( lion_eval_frame_set_s* o, const lion_eval_frame_param_s* param ){lion_eval_frame_param_s_set( &o->param, param );} \
  s2_t lion_eval_frame_set_s_main( lion_eval_frame_set_s* o, const bcore_arr_st_s* args ); \
  lion_eval_frame_result_s* lion_eval_frame_set_s_run( const lion_eval_frame_set_s* o, lion_eval_frame_result_s* result );
#define TYPEOF_lion_eval_frame_plain_s 229993865
#define BETH_EXPAND_ITEM_lion_eval_frame_plain_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_plain_s ) \
    {aware_t _;lion_eval_frame_param_s param;sz_t ap_cycles;}; \
  lion_eval_frame_result_s* lion_eval_frame_plain_s_run( const lion_eval_frame_plain_s* o, lion_eval_frame_result_s* result ); \
  static inline void lion_eval_frame_plain_s_set_param( lion_eval_frame_plain_s* o, const lion_eval_frame_param_s* param ){lion_eval_frame_param_s_set( &o->param, param );} \
  s2_t lion_eval_frame_plain_s_main( lion_eval_frame_plain_s* o, const bcore_arr_st_s* args );
#define TYPEOF_lion_eval_frame_cyclic_s 2923935876
#define BETH_EXPAND_ITEM_lion_eval_frame_cyclic_s \
  BCORE_DECLARE_OBJECT( lion_eval_frame_cyclic_s ) \
    {aware_t _;lion_eval_frame_param_s param;}; \
  lion_eval_frame_result_s* lion_eval_frame_cyclic_s_run( const lion_eval_frame_cyclic_s* o, lion_eval_frame_result_s* result ); \
  static inline void lion_eval_frame_cyclic_s_set_param( lion_eval_frame_cyclic_s* o, const lion_eval_frame_param_s* param ){lion_eval_frame_param_s_set( &o->param, param );} \
  s2_t lion_eval_frame_cyclic_s_main( lion_eval_frame_cyclic_s* o, const bcore_arr_st_s* args );
#define BETH_EXPAND_GROUP_lion_eval_frame \
  BCORE_FORWARD_OBJECT( lion_eval_frame ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_result_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_param_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_show_param_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_arr_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_set_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_plain_s ); \
  BCORE_FORWARD_OBJECT( lion_eval_frame_cyclic_s ); \
  typedef lion_eval_frame_result_s* (*lion_eval_frame_run)( const lion_eval_frame* o, lion_eval_frame_result_s* result ); \
  typedef void (*lion_eval_frame_set_param)( lion_eval_frame* o, const lion_eval_frame_param_s* param ); \
  BCORE_DECLARE_SPECT( lion_eval_frame ) \
  { \
      bcore_spect_header_s header; \
      lion_eval_frame_run run; \
      lion_eval_frame_set_param set_param; \
  }; \
  static inline lion_eval_frame* lion_eval_frame_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_eval_frame, t ); return ( lion_eval_frame* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_eval_frame_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_eval_frame ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_eval_frame ) \
  static inline bl_t lion_eval_frame_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_eval_frame ); } \
  BETH_EXPAND_ITEM_lion_eval_frame_result_s \
  static inline lion_eval_frame_result_s* lion_eval_frame_a_run( const lion_eval_frame* o, lion_eval_frame_result_s* result ) { const lion_eval_frame_s* p = lion_eval_frame_s_get_aware( o ); assert( p->run ); return p->run( o, result ); } \
  static inline bl_t lion_eval_frame_a_defines_run( const lion_eval_frame* o ) { return lion_eval_frame_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_lion_eval_frame_param_s \
  BETH_EXPAND_ITEM_lion_eval_frame_show_param_s \
  static inline void lion_eval_frame_a_set_param( lion_eval_frame* o, const lion_eval_frame_param_s* param ) { const lion_eval_frame_s* p = lion_eval_frame_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param ); } \
  static inline bl_t lion_eval_frame_a_defines_set_param( const lion_eval_frame* o ) { return lion_eval_frame_s_get_aware( o )->set_param != NULL; } \
  BETH_EXPAND_ITEM_lion_eval_frame_arr_s \
  BETH_EXPAND_ITEM_lion_eval_frame_set_s \
  BETH_EXPAND_ITEM_lion_eval_frame_plain_s \
  BETH_EXPAND_ITEM_lion_eval_frame_cyclic_s

/**********************************************************************************************************************/
// source: lion_adaptive.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_adaptive

#define TYPEOF_lion_adaptive 789795542
#define TYPEOF_lion_adaptive_s 2891213576
#define TYPEOF_lion_adaptive_s 2891213576
#define BETH_EXPAND_ITEM_lion_adaptive_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_s ) \
    {aware_t _;vd_t src;lion_frame_s frame;badapt_dynamics_std_s dynamics;sz_t in_size;sz_t out_size;}; \
  static inline sz_t lion_adaptive_s_get_in_size( const lion_adaptive_s* o ){return o->in_size;} \
  static inline sz_t lion_adaptive_s_get_out_size( const lion_adaptive_s* o ){return o->out_size;} \
  static inline void lion_adaptive_s_get_dynamics_std( const lion_adaptive_s* o, badapt_dynamics_std_s* dynamics ){badapt_dynamics_std_s_copy( dynamics, &o->dynamics );} \
  static inline void lion_adaptive_s_set_dynamics_std( lion_adaptive_s* o, const badapt_dynamics_std_s* dynamics ){badapt_dynamics_std_s_copy( &o->dynamics, dynamics );} \
  void lion_adaptive_s_arc_to_sink( const lion_adaptive_s* o, bcore_sink* sink ); \
  void lion_adaptive_s_minfer( lion_adaptive_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
  void lion_adaptive_s_bgrad_adapt( lion_adaptive_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ); \
  void lion_adaptive_s_get_weights_min_max( const lion_adaptive_s* o, f3_t* min, f3_t* max );
#define TYPEOF_lion_adaptive_builder_s 937777220
#define BETH_EXPAND_ITEM_lion_adaptive_builder_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_builder_s ) \
    {aware_t _;vd_t src;sz_t in_size;sz_t out_size;badapt_dynamics_std_s dynamics;}; \
  static inline sz_t lion_adaptive_builder_s_get_in_size( const lion_adaptive_builder_s* o ){return o->in_size;} \
  static inline void lion_adaptive_builder_s_set_in_size( lion_adaptive_builder_s* o, sz_t size ){o->in_size = size;} \
  static inline sz_t lion_adaptive_builder_s_get_out_size( const lion_adaptive_builder_s* o ){return o->out_size;} \
  static inline void lion_adaptive_builder_s_set_out_size( lion_adaptive_builder_s* o, sz_t size ){o->out_size = size;} \
  badapt_adaptive* lion_adaptive_builder_s_build( const lion_adaptive_builder_s* o );
#define TYPEOF_lion_adaptive_cyclic_s 306213838
#define BETH_EXPAND_ITEM_lion_adaptive_cyclic_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_cyclic_s ) \
    {aware_t _;vd_t src;lion_frame_cyclic_s frame;badapt_dynamics_std_s dynamics;sz_t in_size;sz_t out_size;bhvm_holor_adl_s* dp_buffer;bl_t dp_value;}; \
  static inline sz_t lion_adaptive_cyclic_s_get_in_size( const lion_adaptive_cyclic_s* o ){return o->in_size;} \
  static inline sz_t lion_adaptive_cyclic_s_get_out_size( const lion_adaptive_cyclic_s* o ){return o->out_size;} \
  static inline void lion_adaptive_cyclic_s_get_dynamics_std( const lion_adaptive_cyclic_s* o, badapt_dynamics_std_s* dynamics ){badapt_dynamics_std_s_copy( dynamics, &o->dynamics );} \
  static inline void lion_adaptive_cyclic_s_set_dynamics_std( lion_adaptive_cyclic_s* o, const badapt_dynamics_std_s* dynamics ){badapt_dynamics_std_s_copy( &o->dynamics, dynamics );} \
  void lion_adaptive_cyclic_s_arc_to_sink( const lion_adaptive_cyclic_s* o, bcore_sink* sink ); \
  void lion_adaptive_cyclic_s_minfer( lion_adaptive_cyclic_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
  void lion_adaptive_cyclic_s_bgrad_adapt( lion_adaptive_cyclic_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ); \
  void lion_adaptive_cyclic_s_get_weights_min_max( const lion_adaptive_cyclic_s* o, f3_t* min, f3_t* max ); \
  void lion_adaptive_cyclic_s_reset( lion_adaptive_cyclic_s* o );
#define TYPEOF_lion_adaptive_cyclic_builder_s 1640287118
#define BETH_EXPAND_ITEM_lion_adaptive_cyclic_builder_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_cyclic_builder_s ) \
    {aware_t _;vd_t src;sz_t in_size;sz_t out_size;sz_t unroll_size;badapt_dynamics_std_s dynamics;}; \
  static inline sz_t lion_adaptive_cyclic_builder_s_get_in_size( const lion_adaptive_cyclic_builder_s* o ){return o->in_size;} \
  static inline void lion_adaptive_cyclic_builder_s_set_in_size( lion_adaptive_cyclic_builder_s* o, sz_t size ){o->in_size = size;} \
  static inline sz_t lion_adaptive_cyclic_builder_s_get_out_size( const lion_adaptive_cyclic_builder_s* o ){return o->out_size;} \
  static inline void lion_adaptive_cyclic_builder_s_set_out_size( lion_adaptive_cyclic_builder_s* o, sz_t size ){o->out_size = size;} \
  badapt_adaptive* lion_adaptive_cyclic_builder_s_build( const lion_adaptive_cyclic_builder_s* o );
#define BETH_EXPAND_GROUP_lion_adaptive \
  BCORE_FORWARD_OBJECT( lion_adaptive ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_s ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_builder_s ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_cyclic_s ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_cyclic_builder_s ); \
  BETH_EXPAND_ITEM_lion_adaptive_s \
  BETH_EXPAND_ITEM_lion_adaptive_builder_s \
  BETH_EXPAND_ITEM_lion_adaptive_cyclic_s \
  BETH_EXPAND_ITEM_lion_adaptive_cyclic_builder_s

/**********************************************************************************************************************/
// source: lion_adaptor.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_adaptor

#define TYPEOF_lion_adaptor 1865093325
#define TYPEOF_lion_adaptor_s 3132297919
#define TYPEOF_lion_adaptor_frame_s 3407775329
#define BETH_EXPAND_ITEM_lion_adaptor_frame_s \
  BCORE_DECLARE_OBJECT( lion_adaptor_frame_s ) \
    {aware_t _;vd_t src;lion_frame_s* frame;}; \
  static inline void lion_adaptor_frame_s_reset( lion_adaptor_frame_s* o ){if( o->frame ) lion_frame_s_cyclic_reset( o->frame );} \
  void lion_adaptor_frame_s_adapt( lion_adaptor_frame_s* o, const bhpt_adaptor_node_s* node );
#define BETH_EXPAND_GROUP_lion_adaptor \
  BCORE_FORWARD_OBJECT( lion_adaptor ); \
  BCORE_FORWARD_OBJECT( lion_adaptor_frame_s ); \
  BETH_EXPAND_ITEM_lion_adaptor_frame_s

/**********************************************************************************************************************/
// source: lion_adaptive_bhpt.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_adaptive_bhpt

#define TYPEOF_lion_adaptive_bhpt 1889049037
#define TYPEOF_lion_adaptive_bhpt_s 2515157951
#define TYPEOF_lion_adaptive_bhpt_s 2515157951
#define BETH_EXPAND_ITEM_lion_adaptive_bhpt_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_bhpt_s ) \
    {aware_t _;vd_t src;lion_frame_s frame;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;}; \
  static inline bhvm_holor_s* lion_adaptive_bhpt_s_get_format_en( const lion_adaptive_bhpt_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_en ); return format;} \
  static inline bhvm_holor_s* lion_adaptive_bhpt_s_get_format_ex( const lion_adaptive_bhpt_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_ex ); return format;} \
  void lion_adaptive_bhpt_s_axon_pass( lion_adaptive_bhpt_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ); \
  void lion_adaptive_bhpt_s_dendrite_pass( lion_adaptive_bhpt_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ); \
  void lion_adaptive_bhpt_s_cyclic_reset( lion_adaptive_bhpt_s* o ); \
  bhpt_adaptor_probe_s* lion_adaptive_bhpt_s_get_adaptor_probe( const lion_adaptive_bhpt_s* o, bhpt_adaptor_probe_s* probe ); \
  static inline void lion_adaptive_bhpt_s_rebind_holors( lion_adaptive_bhpt_s* o ){lion_frame_s_bind_holors( &o->frame );} \
  void lion_adaptive_bhpt_s_status_to_sink( const lion_adaptive_bhpt_s* o, sz_t verbosity, bcore_sink* sink );
#define TYPEOF_lion_adaptive_bhpt_builder_s 1403919155
#define BETH_EXPAND_ITEM_lion_adaptive_bhpt_builder_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_bhpt_builder_s ) \
    {aware_t _;vd_t src;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;}; \
  static inline void lion_adaptive_bhpt_builder_s_set_format_en( lion_adaptive_bhpt_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_en, format );} \
  static inline void lion_adaptive_bhpt_builder_s_set_format_ex( lion_adaptive_bhpt_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_ex, format );} \
  bhpt_adaptive* lion_adaptive_bhpt_builder_s_create_adaptive( const lion_adaptive_bhpt_builder_s* o );
#define TYPEOF_lion_adaptive_bhpt_cyclic_s 432058863
#define BETH_EXPAND_ITEM_lion_adaptive_bhpt_cyclic_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_bhpt_cyclic_s ) \
    {aware_t _;vd_t src;lion_frame_cyclic_s frame;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;bhvm_holor_adl_s* dp_buffer;bl_t dp_value;}; \
  static inline bhvm_holor_s* lion_adaptive_bhpt_cyclic_s_get_format_en( const lion_adaptive_bhpt_cyclic_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_en ); return format;} \
  static inline bhvm_holor_s* lion_adaptive_bhpt_cyclic_s_get_format_ex( const lion_adaptive_bhpt_cyclic_s* o, bhvm_holor_s* format ){bhvm_holor_s_copy( format, &o->holor_frame_ex ); return format;} \
  void lion_adaptive_bhpt_cyclic_s_axon_pass( lion_adaptive_bhpt_cyclic_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex ); \
  void lion_adaptive_bhpt_cyclic_s_dendrite_pass( lion_adaptive_bhpt_cyclic_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en ); \
  void lion_adaptive_bhpt_cyclic_s_cyclic_reset( lion_adaptive_bhpt_cyclic_s* o ); \
  bhpt_adaptor_probe_s* lion_adaptive_bhpt_cyclic_s_get_adaptor_probe( const lion_adaptive_bhpt_cyclic_s* o, bhpt_adaptor_probe_s* probe ); \
  static inline void lion_adaptive_bhpt_cyclic_s_rebind_holors( lion_adaptive_bhpt_cyclic_s* o ){lion_frame_cyclic_s_bind_holors( &o->frame );} \
  void lion_adaptive_bhpt_cyclic_s_status_to_sink( const lion_adaptive_bhpt_cyclic_s* o, sz_t verbosity, bcore_sink* sink );
#define TYPEOF_lion_adaptive_bhpt_cyclic_builder_s 140720899
#define BETH_EXPAND_ITEM_lion_adaptive_bhpt_cyclic_builder_s \
  BCORE_DECLARE_OBJECT( lion_adaptive_bhpt_cyclic_builder_s ) \
    {aware_t _;vd_t src;bhvm_holor_s holor_frame_en;bhvm_holor_s holor_frame_ex;sz_t unroll_size;}; \
  static inline void lion_adaptive_bhpt_cyclic_builder_s_set_format_en( lion_adaptive_bhpt_cyclic_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_en, format );} \
  static inline void lion_adaptive_bhpt_cyclic_builder_s_set_format_ex( lion_adaptive_bhpt_cyclic_builder_s* o, const bhvm_holor_s* format ){bhvm_holor_s_copy( &o->holor_frame_ex, format );} \
  bhpt_adaptive* lion_adaptive_bhpt_cyclic_builder_s_create_adaptive( const lion_adaptive_bhpt_cyclic_builder_s* o );
#define BETH_EXPAND_GROUP_lion_adaptive_bhpt \
  BCORE_FORWARD_OBJECT( lion_adaptive_bhpt ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_bhpt_s ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_bhpt_builder_s ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_bhpt_cyclic_s ); \
  BCORE_FORWARD_OBJECT( lion_adaptive_bhpt_cyclic_builder_s ); \
  BETH_EXPAND_ITEM_lion_adaptive_bhpt_s \
  BETH_EXPAND_ITEM_lion_adaptive_bhpt_builder_s \
  BETH_EXPAND_ITEM_lion_adaptive_bhpt_cyclic_s \
  BETH_EXPAND_ITEM_lion_adaptive_bhpt_cyclic_builder_s

/**********************************************************************************************************************/

vd_t lion_planted_signal_handler( const bcore_signal_s* o );

#endif // LION_PLANTED_H
