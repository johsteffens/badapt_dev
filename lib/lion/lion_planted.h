/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019 J.B.Steffens
 *  Last File Update: 2019-12-27T18:50:41Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  lion_nop.h
 *  lion_nop_eval.h
 *
 */

#ifndef LION_PLANTED_H
#define LION_PLANTED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: lion_nop.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion

#define TYPEOF_lion 4074679679
#define TYPEOF_lion_s 2299906281
#define TYPEOF_lion_hmeta_s 2700535167
#define BETH_EXPAND_ITEM_lion_hmeta_s \
  BCORE_DECLARE_OBJECT( lion_hmeta_s ) \
    {aware_t _;tp_t name;tp_t class;bl_t htp;}; \
  static inline void lion_hmeta_s_clear( lion_hmeta_s* o ){o->name = o->class = 0; o->htp = false;}
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

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop

#define TYPEOF_lion_nop 2615133213
#define TYPEOF_lion_nop_s 2513597327
#define TYPEOF_nop_class_regular 1493355114
#define TYPEOF_nop_class_cast 431236789
#define TYPEOF_track_ap 2993192456
#define TYPEOF_track_dp 2960475861
#define TYPEOF_track_setup_ap 406272926
#define TYPEOF_track_setup_dp 103834499
#define TYPEOF_lion_nop_solve_result_s 490117549
#define BETH_EXPAND_ITEM_lion_nop_solve_result_s \
  BCORE_DECLARE_OBJECT( lion_nop_solve_result_s ) \
    {aware_t _;lion_holor_s* h;st_s* msg;bl_t settled;bl_t codable;bl_t reducible;tp_t type_vop_ap;tp_t type_vop_dp_a;tp_t type_vop_dp_b;tp_t type_vop_dp_c;};
#define TYPEOF_lion_nop_context_s 1954113275
#define BETH_EXPAND_ITEM_lion_nop_context_s \
  BCORE_DECLARE_OBJECT( lion_nop_context_s ) \
    {aware_t _;bcore_mutex_s* randomizer_mutex;bl_t randomizer_is_locked;u2_t randomizer_rval;};
#define BETH_EXPAND_GROUP_lion_nop \
  BCORE_FORWARD_OBJECT( lion_nop ); \
  BCORE_FORWARD_OBJECT( lion_nop_solve_result_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_context_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar3 ); \
  typedef sz_t (*lion_nop_arity)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_class)( const lion_nop* o ); \
  typedef sz_t (*lion_nop_priority)( const lion_nop* o ); \
  typedef sc_t (*lion_nop_symbol)( const lion_nop* o ); \
  typedef lion_nop* (*lion_nop_create_op_of_arn)( const lion_nop* o, sz_t n ); \
  typedef bl_t (*lion_nop_solve)( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  typedef bl_t (*lion_nop_requires_solve_for_each_channel)( const lion_nop* o ); \
  typedef lion_nop* (*lion_nop_create_final)( const lion_nop* o, lion_holor_s* h ); \
  typedef tp_t (*lion_nop_type_vop_ap)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_type_vop_dp_a)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_type_vop_dp_b)( const lion_nop* o ); \
  typedef tp_t (*lion_nop_type_vop_dp_c)( const lion_nop* o ); \
  typedef void (*lion_nop_mcode_push_ap)( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  typedef void (*lion_nop_mcode_push_dp)( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BCORE_DECLARE_SPECT( lion_nop ) \
  { \
      bcore_spect_header_s header; \
      lion_nop_arity arity; \
      lion_nop_class class; \
      lion_nop_priority priority; \
      lion_nop_symbol symbol; \
      lion_nop_create_op_of_arn create_op_of_arn; \
      lion_nop_solve solve; \
      lion_nop_requires_solve_for_each_channel requires_solve_for_each_channel; \
      lion_nop_create_final create_final; \
      lion_nop_type_vop_ap type_vop_ap; \
      lion_nop_type_vop_dp_a type_vop_dp_a; \
      lion_nop_type_vop_dp_b type_vop_dp_b; \
      lion_nop_type_vop_dp_c type_vop_dp_c; \
      lion_nop_mcode_push_ap mcode_push_ap; \
      lion_nop_mcode_push_dp mcode_push_dp; \
  }; \
  static inline lion_nop* lion_nop_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_nop, t ); return ( lion_nop* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_nop_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_nop ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_nop ) \
  static inline bl_t lion_nop_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_nop ); } \
  static inline sz_t lion_nop_a_arity( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->arity ); return p->arity( o ); } \
  static inline bl_t lion_nop_a_defines_arity( const lion_nop* o ) { return true; } \
  static inline sz_t lion_nop_arity__( const lion_nop* o ){ERR_fa( "Not implemented in '#<sc_t>'.", ifnameof( o->_ ) ); return -1;} \
  static inline tp_t lion_nop_a_class( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->class ); return p->class( o ); } \
  static inline bl_t lion_nop_a_defines_class( const lion_nop* o ) { return true; } \
  static inline tp_t lion_nop_class__( const lion_nop* o ){return TYPEOF_nop_class_regular;} \
  static inline sz_t lion_nop_a_priority( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->priority ); return p->priority( o ); } \
  static inline bl_t lion_nop_a_defines_priority( const lion_nop* o ) { return true; } \
  static inline sz_t lion_nop_priority__( const lion_nop* o ){return 10;} \
  static inline sc_t lion_nop_a_symbol( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->symbol ); return p->symbol( o ); } \
  static inline bl_t lion_nop_a_defines_symbol( const lion_nop* o ) { return true; } \
  static inline sc_t lion_nop_symbol__( const lion_nop* o ){return NULL;} \
  static inline lion_nop* lion_nop_a_create_op_of_arn( const lion_nop* o, sz_t n ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->create_op_of_arn ); return p->create_op_of_arn( o, n ); } \
  static inline bl_t lion_nop_a_defines_create_op_of_arn( const lion_nop* o ) { return true; } \
  static inline lion_nop* lion_nop_create_op_of_arn__( const lion_nop* o, sz_t n ){return ( lion_nop_a_arity( o ) == n ) ? lion_nop_a_clone( o ) : NULL;} \
  BETH_EXPAND_ITEM_lion_nop_solve_result_s \
  static inline bl_t lion_nop_a_solve( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->solve ); return p->solve( o, a, result ); } \
  static inline bl_t lion_nop_a_defines_solve( const lion_nop* o ) { return true; } \
  bl_t lion_nop_solve__( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  static inline bl_t lion_nop_a_requires_solve_for_each_channel( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->requires_solve_for_each_channel ); return p->requires_solve_for_each_channel( o ); } \
  static inline bl_t lion_nop_a_defines_requires_solve_for_each_channel( const lion_nop* o ) { return true; } \
  static inline bl_t lion_nop_requires_solve_for_each_channel__( const lion_nop* o ){return false;} \
  static inline lion_nop* lion_nop_a_create_final( const lion_nop* o, lion_holor_s* h ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->create_final ); return p->create_final( o, h ); } \
  static inline bl_t lion_nop_a_defines_create_final( const lion_nop* o ) { return true; } \
  lion_nop* lion_nop_create_final__( const lion_nop* o, lion_holor_s* h ); \
  static inline tp_t lion_nop_a_type_vop_ap( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_ap ); return p->type_vop_ap( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_ap( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_ap != NULL; } \
  static inline tp_t lion_nop_a_type_vop_dp_a( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_dp_a ); return p->type_vop_dp_a( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_dp_a( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_dp_a != NULL; } \
  static inline tp_t lion_nop_a_type_vop_dp_b( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_dp_b ); return p->type_vop_dp_b( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_dp_b( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_dp_b != NULL; } \
  static inline tp_t lion_nop_a_type_vop_dp_c( const lion_nop* o ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->type_vop_dp_c ); return p->type_vop_dp_c( o ); } \
  static inline bl_t lion_nop_a_defines_type_vop_dp_c( const lion_nop* o ) { return lion_nop_s_get_aware( o )->type_vop_dp_c != NULL; } \
  static inline void lion_nop_a_mcode_push_ap( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->mcode_push_ap ); p->mcode_push_ap( o, result, arr_ci, mcf ); } \
  static inline bl_t lion_nop_a_defines_mcode_push_ap( const lion_nop* o ) { return true; } \
  void lion_nop_mcode_push_ap__( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  static inline void lion_nop_a_mcode_push_dp( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) { const lion_nop_s* p = lion_nop_s_get_aware( o ); assert( p->mcode_push_dp ); p->mcode_push_dp( o, result, ch_id, arr_ci, mcf ); } \
  static inline bl_t lion_nop_a_defines_mcode_push_dp( const lion_nop* o ) { return true; } \
  void lion_nop_mcode_push_dp__( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ); \
  BETH_EXPAND_ITEM_lion_nop_context_s \
  BETH_EXPAND_GROUP_lion_nop_ar0 \
  BETH_EXPAND_GROUP_lion_nop_ar1 \
  BETH_EXPAND_GROUP_lion_nop_ar2 \
  BETH_EXPAND_GROUP_lion_nop_ar3

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar0

#define TYPEOF_lion_nop_ar0 1811831167
#define TYPEOF_lion_nop_ar0_s 2802537705
#define TYPEOF_lion_nop_ar0_zro_s 1993411467
#define BETH_EXPAND_ITEM_lion_nop_ar0_zro_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_zro_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar0_zro_s_arity( const lion_nop_ar0_zro_s* o ){return 0;} \
  static inline sz_t lion_nop_ar0_zro_s_priority( const lion_nop_ar0_zro_s* o ){return 8;} \
  bl_t lion_nop_ar0_zro_s_solve( const lion_nop_ar0_zro_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar0_one_s 1291903798
#define BETH_EXPAND_ITEM_lion_nop_ar0_one_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_one_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar0_one_s_arity( const lion_nop_ar0_one_s* o ){return 0;} \
  static inline sz_t lion_nop_ar0_one_s_priority( const lion_nop_ar0_one_s* o ){return 8;} \
  bl_t lion_nop_ar0_one_s_solve( const lion_nop_ar0_one_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar0_literal_s 2343955625
#define BETH_EXPAND_ITEM_lion_nop_ar0_literal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_literal_s ) \
    {aware_t _;lion_holor_s* h;}; \
  static inline sz_t lion_nop_ar0_literal_s_arity( const lion_nop_ar0_literal_s* o ){return 0;} \
  bl_t lion_nop_ar0_literal_s_solve( const lion_nop_ar0_literal_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar0_input_s 2631293942
#define BETH_EXPAND_ITEM_lion_nop_ar0_input_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_input_s ) \
    {aware_t _;lion_holor_s* h;}; \
  static inline sz_t lion_nop_ar0_input_s_arity( const lion_nop_ar0_input_s* o ){return 0;} \
  bl_t lion_nop_ar0_input_s_solve( const lion_nop_ar0_input_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar0_adaptive_s 2775076616
#define BETH_EXPAND_ITEM_lion_nop_ar0_adaptive_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar0_adaptive_s ) \
    {aware_t _;lion_holor_s* h;}; \
  static inline sz_t lion_nop_ar0_adaptive_s_arity( const lion_nop_ar0_adaptive_s* o ){return 0;} \
  bl_t lion_nop_ar0_adaptive_s_solve( const lion_nop_ar0_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define BETH_EXPAND_GROUP_lion_nop_ar0 \
  BCORE_FORWARD_OBJECT( lion_nop_ar0 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_zro_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_one_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_literal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_input_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar0_adaptive_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar0_zro_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_one_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_literal_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_input_s \
  BETH_EXPAND_ITEM_lion_nop_ar0_adaptive_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar1

#define TYPEOF_lion_nop_ar1 1795053548
#define TYPEOF_lion_nop_ar1_s 1250111182
#define TYPEOF_lion_nop_ar1_identity_s 2451425137
#define BETH_EXPAND_ITEM_lion_nop_ar1_identity_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_identity_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_identity_s_arity( const lion_nop_ar1_identity_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_identity_s_priority( const lion_nop_ar1_identity_s* o ){return 8;} \
  bl_t lion_nop_ar1_identity_s_solve( const lion_nop_ar1_identity_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_neg_s 594087751
#define BETH_EXPAND_ITEM_lion_nop_ar1_neg_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_neg_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_neg_s_arity( const lion_nop_ar1_neg_s* o ){return 1;} \
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
  static inline sz_t lion_nop_ar1_floor_s_priority( const lion_nop_ar1_floor_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_floor_s_symbol( const lion_nop_ar1_floor_s* o ){return "floor";} \
  static inline tp_t lion_nop_ar1_floor_s_type_vop_ap( const lion_nop_ar1_floor_s* o ){return TYPEOF_bhvm_vop_ar1_floor_s;} \
  static inline tp_t lion_nop_ar1_floor_s_type_vop_dp_a( const lion_nop_ar1_floor_s* o ){return TYPEOF_bhvm_vop_ar0_nul_dp_s;}
#define TYPEOF_lion_nop_ar1_ceil_s 505367678
#define BETH_EXPAND_ITEM_lion_nop_ar1_ceil_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_ceil_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_ceil_s_arity( const lion_nop_ar1_ceil_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_ceil_s_priority( const lion_nop_ar1_ceil_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_ceil_s_symbol( const lion_nop_ar1_ceil_s* o ){return "ceil";} \
  static inline tp_t lion_nop_ar1_ceil_s_type_vop_ap( const lion_nop_ar1_ceil_s* o ){return TYPEOF_bhvm_vop_ar1_ceil_s;} \
  static inline tp_t lion_nop_ar1_ceil_s_type_vop_dp_a( const lion_nop_ar1_ceil_s* o ){return TYPEOF_bhvm_vop_ar0_nul_dp_s;}
#define TYPEOF_lion_nop_ar1_exp_s 4255037934
#define BETH_EXPAND_ITEM_lion_nop_ar1_exp_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_exp_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_exp_s_arity( const lion_nop_ar1_exp_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_exp_s_priority( const lion_nop_ar1_exp_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_exp_s_symbol( const lion_nop_ar1_exp_s* o ){return "exp";} \
  static inline tp_t lion_nop_ar1_exp_s_type_vop_ap( const lion_nop_ar1_exp_s* o ){return TYPEOF_bhvm_vop_ar1_exp_s;} \
  static inline tp_t lion_nop_ar1_exp_s_type_vop_dp_a( const lion_nop_ar1_exp_s* o ){return TYPEOF_bhvm_vop_ar2_exp_dp_s;}
#define TYPEOF_lion_nop_ar1_inv_s 2310849958
#define BETH_EXPAND_ITEM_lion_nop_ar1_inv_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_inv_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_inv_s_arity( const lion_nop_ar1_inv_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_inv_s_priority( const lion_nop_ar1_inv_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_inv_s_symbol( const lion_nop_ar1_inv_s* o ){return "inv";} \
  static inline tp_t lion_nop_ar1_inv_s_type_vop_ap( const lion_nop_ar1_inv_s* o ){return TYPEOF_bhvm_vop_ar1_inv_s;} \
  static inline tp_t lion_nop_ar1_inv_s_type_vop_dp_a( const lion_nop_ar1_inv_s* o ){return TYPEOF_bhvm_vop_ar2_inv_dp_s;}
#define TYPEOF_lion_nop_ar1_lgst_s 3065196921
#define BETH_EXPAND_ITEM_lion_nop_ar1_lgst_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_lgst_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_lgst_s_arity( const lion_nop_ar1_lgst_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_lgst_s_priority( const lion_nop_ar1_lgst_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_lgst_s_symbol( const lion_nop_ar1_lgst_s* o ){return "lgst";} \
  static inline tp_t lion_nop_ar1_lgst_s_type_vop_ap( const lion_nop_ar1_lgst_s* o ){return TYPEOF_bhvm_vop_ar1_lgst_s;} \
  static inline tp_t lion_nop_ar1_lgst_s_type_vop_dp_a( const lion_nop_ar1_lgst_s* o ){return TYPEOF_bhvm_vop_ar2_lgst_dp_s;}
#define TYPEOF_lion_nop_ar1_lgst_hard_s 1955989631
#define BETH_EXPAND_ITEM_lion_nop_ar1_lgst_hard_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_lgst_hard_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_lgst_hard_s_arity( const lion_nop_ar1_lgst_hard_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_lgst_hard_s_priority( const lion_nop_ar1_lgst_hard_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_lgst_hard_s_symbol( const lion_nop_ar1_lgst_hard_s* o ){return "lgst_hard";} \
  static inline tp_t lion_nop_ar1_lgst_hard_s_type_vop_ap( const lion_nop_ar1_lgst_hard_s* o ){return TYPEOF_bhvm_vop_ar1_lgst_hard_s;} \
  static inline tp_t lion_nop_ar1_lgst_hard_s_type_vop_dp_a( const lion_nop_ar1_lgst_hard_s* o ){return TYPEOF_bhvm_vop_ar2_lgst_hard_dp_s;}
#define TYPEOF_lion_nop_ar1_lgst_leaky_s 2965570548
#define BETH_EXPAND_ITEM_lion_nop_ar1_lgst_leaky_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_lgst_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_lgst_leaky_s_arity( const lion_nop_ar1_lgst_leaky_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_lgst_leaky_s_priority( const lion_nop_ar1_lgst_leaky_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_lgst_leaky_s_symbol( const lion_nop_ar1_lgst_leaky_s* o ){return "lgst_leaky";} \
  static inline tp_t lion_nop_ar1_lgst_leaky_s_type_vop_ap( const lion_nop_ar1_lgst_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_lgst_leaky_s;} \
  static inline tp_t lion_nop_ar1_lgst_leaky_s_type_vop_dp_a( const lion_nop_ar1_lgst_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_lgst_leaky_dp_s;}
#define TYPEOF_lion_nop_ar1_tanh_s 772292870
#define BETH_EXPAND_ITEM_lion_nop_ar1_tanh_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_tanh_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_tanh_s_arity( const lion_nop_ar1_tanh_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_tanh_s_priority( const lion_nop_ar1_tanh_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_tanh_s_symbol( const lion_nop_ar1_tanh_s* o ){return "tanh";} \
  static inline tp_t lion_nop_ar1_tanh_s_type_vop_ap( const lion_nop_ar1_tanh_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_s;} \
  static inline tp_t lion_nop_ar1_tanh_s_type_vop_dp_a( const lion_nop_ar1_tanh_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_dp_s;}
#define TYPEOF_lion_nop_ar1_tanh_hard_s 1582636522
#define BETH_EXPAND_ITEM_lion_nop_ar1_tanh_hard_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_tanh_hard_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_tanh_hard_s_arity( const lion_nop_ar1_tanh_hard_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_tanh_hard_s_priority( const lion_nop_ar1_tanh_hard_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_tanh_hard_s_symbol( const lion_nop_ar1_tanh_hard_s* o ){return "tanh_hard";} \
  static inline tp_t lion_nop_ar1_tanh_hard_s_type_vop_ap( const lion_nop_ar1_tanh_hard_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_hard_s;} \
  static inline tp_t lion_nop_ar1_tanh_hard_s_type_vop_dp_a( const lion_nop_ar1_tanh_hard_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_hard_dp_s;}
#define TYPEOF_lion_nop_ar1_tanh_leaky_s 2422520131
#define BETH_EXPAND_ITEM_lion_nop_ar1_tanh_leaky_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_tanh_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_tanh_leaky_s_arity( const lion_nop_ar1_tanh_leaky_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_tanh_leaky_s_priority( const lion_nop_ar1_tanh_leaky_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_tanh_leaky_s_symbol( const lion_nop_ar1_tanh_leaky_s* o ){return "tanh_leaky";} \
  static inline tp_t lion_nop_ar1_tanh_leaky_s_type_vop_ap( const lion_nop_ar1_tanh_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_tanh_leaky_s;} \
  static inline tp_t lion_nop_ar1_tanh_leaky_s_type_vop_dp_a( const lion_nop_ar1_tanh_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_tanh_leaky_dp_s;}
#define TYPEOF_lion_nop_ar1_softplus_s 2242492955
#define BETH_EXPAND_ITEM_lion_nop_ar1_softplus_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_softplus_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_softplus_s_arity( const lion_nop_ar1_softplus_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_softplus_s_priority( const lion_nop_ar1_softplus_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_softplus_s_symbol( const lion_nop_ar1_softplus_s* o ){return "softplus";} \
  static inline tp_t lion_nop_ar1_softplus_s_type_vop_ap( const lion_nop_ar1_softplus_s* o ){return TYPEOF_bhvm_vop_ar1_softplus_s;} \
  static inline tp_t lion_nop_ar1_softplus_s_type_vop_dp_a( const lion_nop_ar1_softplus_s* o ){return TYPEOF_bhvm_vop_ar2_softplus_dp_s;}
#define TYPEOF_lion_nop_ar1_relu_s 1447672377
#define BETH_EXPAND_ITEM_lion_nop_ar1_relu_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_relu_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_relu_s_arity( const lion_nop_ar1_relu_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_relu_s_priority( const lion_nop_ar1_relu_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_relu_s_symbol( const lion_nop_ar1_relu_s* o ){return "relu";} \
  static inline tp_t lion_nop_ar1_relu_s_type_vop_ap( const lion_nop_ar1_relu_s* o ){return TYPEOF_bhvm_vop_ar1_relu_s;} \
  static inline tp_t lion_nop_ar1_relu_s_type_vop_dp_a( const lion_nop_ar1_relu_s* o ){return TYPEOF_bhvm_vop_ar2_relu_dp_s;}
#define TYPEOF_lion_nop_ar1_relu_leaky_s 1869882548
#define BETH_EXPAND_ITEM_lion_nop_ar1_relu_leaky_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_relu_leaky_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_relu_leaky_s_arity( const lion_nop_ar1_relu_leaky_s* o ){return 1;} \
  static inline sz_t lion_nop_ar1_relu_leaky_s_priority( const lion_nop_ar1_relu_leaky_s* o ){return 8;} \
  static inline sc_t lion_nop_ar1_relu_leaky_s_symbol( const lion_nop_ar1_relu_leaky_s* o ){return "relu_leaky";} \
  static inline tp_t lion_nop_ar1_relu_leaky_s_type_vop_ap( const lion_nop_ar1_relu_leaky_s* o ){return TYPEOF_bhvm_vop_ar1_relu_leaky_s;} \
  static inline tp_t lion_nop_ar1_relu_leaky_s_type_vop_dp_a( const lion_nop_ar1_relu_leaky_s* o ){return TYPEOF_bhvm_vop_ar2_relu_leaky_dp_s;}
#define TYPEOF_lion_nop_ar1_output_s 1113502298
#define BETH_EXPAND_ITEM_lion_nop_ar1_output_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_output_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_output_s_arity( const lion_nop_ar1_output_s* o ){return 1;} \
  bl_t lion_nop_ar1_output_s_solve( const lion_nop_ar1_output_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_adaptive_s 1680611337
#define BETH_EXPAND_ITEM_lion_nop_ar1_adaptive_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_adaptive_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t lion_nop_ar1_adaptive_s_arity( const lion_nop_ar1_adaptive_s* o ){return 1;} \
  static inline sc_t lion_nop_ar1_adaptive_s_symbol( const lion_nop_ar1_adaptive_s* o ){return "adaptive";} \
  static inline sz_t lion_nop_ar1_adaptive_s_priority( const lion_nop_ar1_adaptive_s* o ){return 8;} \
  bl_t lion_nop_ar1_adaptive_s_solve( const lion_nop_ar1_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  lion_nop* lion_nop_ar1_adaptive_s_create_final( const lion_nop_ar1_adaptive_s* o, lion_holor_s* h );
#define TYPEOF_lion_nop_ar1_dimof_s 2608787106
#define BETH_EXPAND_ITEM_lion_nop_ar1_dimof_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_dimof_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_dimof_s_arity( const lion_nop_ar1_dimof_s* o ){return 1;} \
  static inline sc_t lion_nop_ar1_dimof_s_symbol( const lion_nop_ar1_dimof_s* o ){return "dimof";} \
  static inline sz_t lion_nop_ar1_dimof_s_priority( const lion_nop_ar1_dimof_s* o ){return 8;} \
  bl_t lion_nop_ar1_dimof_s_solve( const lion_nop_ar1_dimof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_random_s 3482240456
#define BETH_EXPAND_ITEM_lion_nop_ar1_random_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_random_s ) \
    {aware_t _;u2_t rseed;}; \
  static inline sz_t lion_nop_ar1_random_s_arity( const lion_nop_ar1_random_s* o ){return 1;} \
  static inline sc_t lion_nop_ar1_random_s_symbol( const lion_nop_ar1_random_s* o ){return "random";} \
  static inline sz_t lion_nop_ar1_random_s_priority( const lion_nop_ar1_random_s* o ){return 8;} \
  bl_t lion_nop_ar1_random_s_solve( const lion_nop_ar1_random_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar1_cast_htp_s 2772432835
#define BETH_EXPAND_ITEM_lion_nop_ar1_cast_htp_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar1_cast_htp_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar1_cast_htp_s_arity( const lion_nop_ar1_cast_htp_s* o ){return 1;} \
  static inline tp_t lion_nop_ar1_cast_htp_s_class( const lion_nop_ar1_cast_htp_s* o ){return TYPEOF_nop_class_cast;} \
  static inline sz_t lion_nop_ar1_cast_htp_s_priority( const lion_nop_ar1_cast_htp_s* o ){return 8;} \
  bl_t lion_nop_ar1_cast_htp_s_solve( const lion_nop_ar1_cast_htp_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define BETH_EXPAND_GROUP_lion_nop_ar1 \
  BCORE_FORWARD_OBJECT( lion_nop_ar1 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_identity_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_neg_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_floor_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_ceil_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_exp_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_inv_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_lgst_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_lgst_hard_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_lgst_leaky_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_tanh_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_tanh_hard_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_tanh_leaky_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_softplus_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_relu_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_relu_leaky_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_output_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_adaptive_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_dimof_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_random_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar1_cast_htp_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar1_identity_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_neg_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_floor_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_ceil_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_exp_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_inv_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_lgst_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_lgst_hard_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_lgst_leaky_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_tanh_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_tanh_hard_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_tanh_leaky_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_softplus_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_relu_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_relu_leaky_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_output_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_adaptive_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_dimof_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_random_s \
  BETH_EXPAND_ITEM_lion_nop_ar1_cast_htp_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar2

#define TYPEOF_lion_nop_ar2 1845386405
#define TYPEOF_lion_nop_ar2_s 2593649991
#define TYPEOF_lion_nop_ar2_add_s 3353650847
#define BETH_EXPAND_ITEM_lion_nop_ar2_add_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_add_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_add_s_arity( const lion_nop_ar2_add_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_add_s_priority( const lion_nop_ar2_add_s* o ){return 8;} \
  static inline sc_t lion_nop_ar2_add_s_symbol( const lion_nop_ar2_add_s* o ){return "+";} \
  static inline tp_t lion_nop_ar2_add_s_type_vop_ap( const lion_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar2_add_s;} \
  static inline tp_t lion_nop_ar2_add_s_type_vop_dp_a( const lion_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_a_s;} \
  static inline tp_t lion_nop_ar2_add_s_type_vop_dp_b( const lion_nop_ar2_add_s* o ){return TYPEOF_bhvm_vop_ar1_add_dp_b_s;}
#define TYPEOF_lion_nop_ar2_sub_s 1752167710
#define BETH_EXPAND_ITEM_lion_nop_ar2_sub_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_sub_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_sub_s_arity( const lion_nop_ar2_sub_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_sub_s_priority( const lion_nop_ar2_sub_s* o ){return 8;} \
  static inline sc_t lion_nop_ar2_sub_s_symbol( const lion_nop_ar2_sub_s* o ){return "-";} \
  static inline tp_t lion_nop_ar2_sub_s_type_vop_ap( const lion_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar2_sub_s;} \
  static inline tp_t lion_nop_ar2_sub_s_type_vop_dp_a( const lion_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar1_sub_dp_a_s;} \
  static inline tp_t lion_nop_ar2_sub_s_type_vop_dp_b( const lion_nop_ar2_sub_s* o ){return TYPEOF_bhvm_vop_ar1_sub_dp_b_s;} \
  lion_nop* lion_nop_ar2_sub_s_create_op_of_arn( const lion_nop_ar2_sub_s* o, sz_t n );
#define TYPEOF_lion_nop_ar2_div_s 4076606099
#define BETH_EXPAND_ITEM_lion_nop_ar2_div_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_div_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_div_s_arity( const lion_nop_ar2_div_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_div_s_priority( const lion_nop_ar2_div_s* o ){return 10;} \
  static inline sc_t lion_nop_ar2_div_s_symbol( const lion_nop_ar2_div_s* o ){return "/";} \
  static inline tp_t lion_nop_ar2_div_s_type_vop_ap( const lion_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar2_div_s;} \
  static inline tp_t lion_nop_ar2_div_s_type_vop_dp_a( const lion_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar2_div_dp_a_s;} \
  static inline tp_t lion_nop_ar2_div_s_type_vop_dp_b( const lion_nop_ar2_div_s* o ){return TYPEOF_bhvm_vop_ar3_div_dp_b_s;}
#define TYPEOF_lion_nop_ar2_mul_s 2245955362
#define BETH_EXPAND_ITEM_lion_nop_ar2_mul_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_mul_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_mul_s_arity( const lion_nop_ar2_mul_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_mul_s_priority( const lion_nop_ar2_mul_s* o ){return 10;} \
  static inline sc_t lion_nop_ar2_mul_s_symbol( const lion_nop_ar2_mul_s* o ){return "*";} \
  bl_t lion_nop_ar2_mul_s_solve( const lion_nop_ar2_mul_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar2_bmul_s 2813275964
#define BETH_EXPAND_ITEM_lion_nop_ar2_bmul_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_bmul_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_bmul_s_arity( const lion_nop_ar2_bmul_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_bmul_s_priority( const lion_nop_ar2_bmul_s* o ){return 10;} \
  static inline sc_t lion_nop_ar2_bmul_s_symbol( const lion_nop_ar2_bmul_s* o ){return "**";} \
  bl_t lion_nop_ar2_bmul_s_solve( const lion_nop_ar2_bmul_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar2_equal_s 3049757132
#define BETH_EXPAND_ITEM_lion_nop_ar2_equal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_equal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_equal_s_arity( const lion_nop_ar2_equal_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_equal_s_priority( const lion_nop_ar2_equal_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_equal_s_symbol( const lion_nop_ar2_equal_s* o ){return "==";} \
  static inline tp_t lion_nop_ar2_equal_s_type_vop_ap( const lion_nop_ar2_equal_s* o ){return TYPEOF_bhvm_vop_ar2_equal_s;} \
  static inline tp_t lion_nop_ar2_equal_s_type_vop_dp_a( const lion_nop_ar2_equal_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_equal_s_type_vop_dp_b( const lion_nop_ar2_equal_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_larger_s 3146855563
#define BETH_EXPAND_ITEM_lion_nop_ar2_larger_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_larger_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_larger_s_arity( const lion_nop_ar2_larger_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_larger_s_priority( const lion_nop_ar2_larger_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_larger_s_symbol( const lion_nop_ar2_larger_s* o ){return ">";} \
  static inline tp_t lion_nop_ar2_larger_s_type_vop_ap( const lion_nop_ar2_larger_s* o ){return TYPEOF_bhvm_vop_ar2_larger_s;} \
  static inline tp_t lion_nop_ar2_larger_s_type_vop_dp_a( const lion_nop_ar2_larger_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_larger_s_type_vop_dp_b( const lion_nop_ar2_larger_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_smaller_s 2846597664
#define BETH_EXPAND_ITEM_lion_nop_ar2_smaller_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_smaller_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_smaller_s_arity( const lion_nop_ar2_smaller_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_smaller_s_priority( const lion_nop_ar2_smaller_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_smaller_s_symbol( const lion_nop_ar2_smaller_s* o ){return "<";} \
  static inline tp_t lion_nop_ar2_smaller_s_type_vop_ap( const lion_nop_ar2_smaller_s* o ){return TYPEOF_bhvm_vop_ar2_smaller_s;} \
  static inline tp_t lion_nop_ar2_smaller_s_type_vop_dp_a( const lion_nop_ar2_smaller_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_smaller_s_type_vop_dp_b( const lion_nop_ar2_smaller_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_larger_equal_s 743024144
#define BETH_EXPAND_ITEM_lion_nop_ar2_larger_equal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_larger_equal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_larger_equal_s_arity( const lion_nop_ar2_larger_equal_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_larger_equal_s_priority( const lion_nop_ar2_larger_equal_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_larger_equal_s_symbol( const lion_nop_ar2_larger_equal_s* o ){return ">=";} \
  static inline tp_t lion_nop_ar2_larger_equal_s_type_vop_ap( const lion_nop_ar2_larger_equal_s* o ){return TYPEOF_bhvm_vop_ar2_larger_equal_s;} \
  static inline tp_t lion_nop_ar2_larger_equal_s_type_vop_dp_a( const lion_nop_ar2_larger_equal_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_larger_equal_s_type_vop_dp_b( const lion_nop_ar2_larger_equal_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_smaller_equal_s 893676947
#define BETH_EXPAND_ITEM_lion_nop_ar2_smaller_equal_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_smaller_equal_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_smaller_equal_s_arity( const lion_nop_ar2_smaller_equal_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_smaller_equal_s_priority( const lion_nop_ar2_smaller_equal_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_smaller_equal_s_symbol( const lion_nop_ar2_smaller_equal_s* o ){return "<=";} \
  static inline tp_t lion_nop_ar2_smaller_equal_s_type_vop_ap( const lion_nop_ar2_smaller_equal_s* o ){return TYPEOF_bhvm_vop_ar2_smaller_equal_s;} \
  static inline tp_t lion_nop_ar2_smaller_equal_s_type_vop_dp_a( const lion_nop_ar2_smaller_equal_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_smaller_equal_s_type_vop_dp_b( const lion_nop_ar2_smaller_equal_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_logic_and_s 683893884
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_and_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_and_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_and_s_arity( const lion_nop_ar2_logic_and_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_logic_and_s_priority( const lion_nop_ar2_logic_and_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_logic_and_s_symbol( const lion_nop_ar2_logic_and_s* o ){return "&";} \
  static inline tp_t lion_nop_ar2_logic_and_s_type_vop_ap( const lion_nop_ar2_logic_and_s* o ){return TYPEOF_bhvm_vop_ar2_logic_and_s;} \
  static inline tp_t lion_nop_ar2_logic_and_s_type_vop_dp_a( const lion_nop_ar2_logic_and_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_logic_and_s_type_vop_dp_b( const lion_nop_ar2_logic_and_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_logic_or_s 1005674890
#define BETH_EXPAND_ITEM_lion_nop_ar2_logic_or_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_logic_or_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_logic_or_s_arity( const lion_nop_ar2_logic_or_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_logic_or_s_priority( const lion_nop_ar2_logic_or_s* o ){return 6;} \
  static inline sc_t lion_nop_ar2_logic_or_s_symbol( const lion_nop_ar2_logic_or_s* o ){return "|";} \
  static inline tp_t lion_nop_ar2_logic_or_s_type_vop_ap( const lion_nop_ar2_logic_or_s* o ){return TYPEOF_bhvm_vop_ar2_logic_or_s;} \
  static inline tp_t lion_nop_ar2_logic_or_s_type_vop_dp_a( const lion_nop_ar2_logic_or_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_logic_or_s_type_vop_dp_b( const lion_nop_ar2_logic_or_s* o ){return 0;}
#define TYPEOF_lion_nop_ar2_index_s 1705523628
#define BETH_EXPAND_ITEM_lion_nop_ar2_index_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_index_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_index_s_arity( const lion_nop_ar2_index_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_index_s_priority( const lion_nop_ar2_index_s* o ){return 20;} \
  bl_t lion_nop_ar2_index_s_solve( const lion_nop_ar2_index_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar2_inc_order_s 928704479
#define BETH_EXPAND_ITEM_lion_nop_ar2_inc_order_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_inc_order_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_inc_order_s_arity( const lion_nop_ar2_inc_order_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_inc_order_s_priority( const lion_nop_ar2_inc_order_s* o ){return 20;} \
  bl_t lion_nop_ar2_inc_order_s_solve( const lion_nop_ar2_inc_order_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar2_cat_s 2494514940
#define BETH_EXPAND_ITEM_lion_nop_ar2_cat_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_cat_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar2_cat_s_arity( const lion_nop_ar2_cat_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_cat_s_priority( const lion_nop_ar2_cat_s* o ){return 6;} \
  bl_t lion_nop_ar2_cat_s_solve( const lion_nop_ar2_cat_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define TYPEOF_lion_nop_ar2_recurrent_s 912007342
#define BETH_EXPAND_ITEM_lion_nop_ar2_recurrent_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar2_recurrent_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t lion_nop_ar2_recurrent_s_arity( const lion_nop_ar2_recurrent_s* o ){return 2;} \
  static inline sz_t lion_nop_ar2_recurrent_s_priority( const lion_nop_ar2_recurrent_s* o ){return 8;} \
  static inline bl_t lion_nop_ar2_recurrent_s_requires_solve_for_each_channel( const lion_nop_ar2_recurrent_s* o ){return true;} \
  bl_t lion_nop_ar2_recurrent_s_solve( const lion_nop_ar2_recurrent_s* o, lion_holor_s** a, lion_nop_solve_result_s* result ); \
  static inline tp_t lion_nop_ar2_recurrent_s_type_vop_dp_a( const lion_nop_ar2_recurrent_s* o ){return 0;} \
  static inline tp_t lion_nop_ar2_recurrent_s_type_vop_dp_b( const lion_nop_ar2_recurrent_s* o ){return 0;} \
  void lion_nop_ar2_recurrent_s_mcode_push_ap( const lion_nop_ar2_recurrent_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf );
#define BETH_EXPAND_GROUP_lion_nop_ar2 \
  BCORE_FORWARD_OBJECT( lion_nop_ar2 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_add_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_sub_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_div_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_mul_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_bmul_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_equal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_larger_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_smaller_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_larger_equal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_smaller_equal_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_and_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_logic_or_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_index_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_inc_order_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_cat_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar2_recurrent_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar2_add_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_sub_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_div_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_mul_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_bmul_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_equal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_larger_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_smaller_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_larger_equal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_smaller_equal_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_and_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_logic_or_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_index_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_inc_order_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_cat_s \
  BETH_EXPAND_ITEM_lion_nop_ar2_recurrent_s

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar3

#define TYPEOF_lion_nop_ar3 1828608786
#define TYPEOF_lion_nop_ar3_s 493893900
#define TYPEOF_lion_nop_ar3_branch_s 229442049
#define BETH_EXPAND_ITEM_lion_nop_ar3_branch_s \
  BCORE_DECLARE_OBJECT( lion_nop_ar3_branch_s ) \
    {aware_t _;}; \
  static inline sz_t lion_nop_ar3_branch_s_arity( const lion_nop_ar3_branch_s* o ){return 3;} \
  static inline sz_t lion_nop_ar3_branch_s_priority( const lion_nop_ar3_branch_s* o ){return  5;} \
  bl_t lion_nop_ar3_branch_s_solve( const lion_nop_ar3_branch_s* o, lion_holor_s** a, lion_nop_solve_result_s* result );
#define BETH_EXPAND_GROUP_lion_nop_ar3 \
  BCORE_FORWARD_OBJECT( lion_nop_ar3 ); \
  BCORE_FORWARD_OBJECT( lion_nop_ar3_branch_s ); \
  BETH_EXPAND_ITEM_lion_nop_ar3_branch_s

/**********************************************************************************************************************/
// source: lion_nop_eval.h

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_eval

#define TYPEOF_lion_nop_eval 39024840
#define TYPEOF_lion_nop_eval_s 669157042
#define TYPEOF_lion_nop_eval_result_s 734986310
#define BETH_EXPAND_ITEM_lion_nop_eval_result_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_result_s ) \
    {aware_t _;bl_t error;st_s msg;}; \
  void lion_nop_eval_result_s_resolve( lion_nop_eval_result_s* o );
#define TYPEOF_lion_nop_eval_param_s 1198003452
#define BETH_EXPAND_ITEM_lion_nop_eval_param_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_param_s ) \
    {aware_t _;lion_nop* nop;lion_holor_s* ha;lion_holor_s* hb;lion_holor_s* hc;lion_holor_s* hr;bcore_sink* log;sz_t verbosity;u2_t rval;}; \
  static inline void lion_nop_eval_param_s_init_x( lion_nop_eval_param_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  void lion_nop_eval_param_s_set( lion_nop_eval_param_s* o, const lion_nop_eval_param_s* src );
#define TYPEOF_lion_nop_eval_generator_s 3224773740
#define BETH_EXPAND_ITEM_lion_nop_eval_generator_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_generator_s ) \
    {aware_t _;lion_nop_eval_param_s param;bl_t set_htp;bl_t set_value;bl_t set_shape;bl_t set_dim;bl_t set_v_type;sz_t max_shape_size;sz_t max_dim;f3_t v_min;f3_t v_max;sz_t cycles;lion_nop_eval* eval;}; \
  static inline void lion_nop_eval_generator_s_set_param( lion_nop_eval_generator_s* o, const lion_nop_eval_param_s* param ){lion_nop_eval_param_s_set( &o->param, param );} \
  lion_nop_eval_result_s* lion_nop_eval_generator_s_run( const lion_nop_eval_generator_s* o ); \
  static inline s2_t lion_nop_eval_generator_s_main( lion_nop_eval_generator_s* o, const bcore_arr_st_s* args ){lion_nop_eval_result_s_resolve( lion_nop_eval_generator_s_run( o ) ); return 0;}
#define TYPEOF_lion_nop_eval_show_param_s 3833653080
#define BETH_EXPAND_ITEM_lion_nop_eval_show_param_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_show_param_s ) \
    {aware_t _;lion_nop_eval_param_s param;}; \
  static inline void lion_nop_eval_show_param_s_set_param( lion_nop_eval_show_param_s* o, const lion_nop_eval_param_s* param ){lion_nop_eval_param_s_set( &o->param, param );} \
  static inline lion_nop_eval_result_s* lion_nop_eval_show_param_s_run( const lion_nop_eval_show_param_s* o ){bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return NULL;} \
  static inline s2_t lion_nop_eval_show_param_s_main( lion_nop_eval_show_param_s* o, const bcore_arr_st_s* args ){lion_nop_eval_result_s_resolve( lion_nop_eval_show_param_s_run( o ) ); return 0;}
#define TYPEOF_lion_nop_eval_arr_s 3415604434
#define BETH_EXPAND_ITEM_lion_nop_eval_arr_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( lion_nop_eval, );}; \
  static inline void lion_nop_eval_arr_s_set_space( lion_nop_eval_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_lion_nop_eval_arr_s, ( bcore_array* )o, size ); } \
  static inline void lion_nop_eval_arr_s_set_size( lion_nop_eval_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_lion_nop_eval_arr_s, ( bcore_array* )o, size ); } \
  static inline void lion_nop_eval_arr_s_clear( lion_nop_eval_arr_s* o ) { bcore_array_t_set_space( TYPEOF_lion_nop_eval_arr_s, ( bcore_array* )o, 0 ); } \
  static inline lion_nop_eval* lion_nop_eval_arr_s_push_c( lion_nop_eval_arr_s* o, const lion_nop_eval* v ) { bcore_array_t_push( TYPEOF_lion_nop_eval_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_nop_eval* lion_nop_eval_arr_s_push_d( lion_nop_eval_arr_s* o,       lion_nop_eval* v ) { bcore_array_t_push( TYPEOF_lion_nop_eval_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline lion_nop_eval* lion_nop_eval_arr_s_push_t( lion_nop_eval_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_lion_nop_eval, t ); \
      bcore_array_t_push( TYPEOF_lion_nop_eval_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_lion_nop_eval_set_s 3945935093
#define BETH_EXPAND_ITEM_lion_nop_eval_set_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_set_s ) \
    {aware_t _;lion_nop_eval_param_s param;lion_nop_eval_arr_s arr;}; \
  static inline void lion_nop_eval_set_s_set_param( lion_nop_eval_set_s* o, const lion_nop_eval_param_s* param ){lion_nop_eval_param_s_set( &o->param, param );} \
  lion_nop_eval_result_s* lion_nop_eval_set_s_run( const lion_nop_eval_set_s* o ); \
  s2_t lion_nop_eval_set_s_main( lion_nop_eval_set_s* o, const bcore_arr_st_s* args );
#define TYPEOF_lion_nop_eval_ar1_s 1410963467
#define BETH_EXPAND_ITEM_lion_nop_eval_ar1_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_ar1_s ) \
    {aware_t _;lion_nop_eval_param_s param;}; \
  lion_nop_eval_result_s* lion_nop_eval_ar1_s_run( const lion_nop_eval_ar1_s* o ); \
  static inline void lion_nop_eval_ar1_s_set_param( lion_nop_eval_ar1_s* o, const lion_nop_eval_param_s* param ){lion_nop_eval_param_s_set( &o->param, param );} \
  static inline s2_t lion_nop_eval_ar1_s_main( lion_nop_eval_ar1_s* o, const bcore_arr_st_s* args ){lion_nop_eval_result_s_resolve( lion_nop_eval_ar1_s_run( o ) ); return 0;}
#define TYPEOF_lion_nop_eval_ar2_s 67527826
#define BETH_EXPAND_ITEM_lion_nop_eval_ar2_s \
  BCORE_DECLARE_OBJECT( lion_nop_eval_ar2_s ) \
    {aware_t _;lion_nop_eval_param_s param;}; \
  lion_nop_eval_result_s* lion_nop_eval_ar2_s_run( const lion_nop_eval_ar2_s* o ); \
  static inline void lion_nop_eval_ar2_s_set_param( lion_nop_eval_ar2_s* o, const lion_nop_eval_param_s* param ){lion_nop_eval_param_s_set( &o->param, param );} \
  static inline s2_t lion_nop_eval_ar2_s_main( lion_nop_eval_ar2_s* o, const bcore_arr_st_s* args ){lion_nop_eval_result_s_resolve( lion_nop_eval_ar2_s_run( o ) ); return 0;}
#define BETH_EXPAND_GROUP_lion_nop_eval \
  BCORE_FORWARD_OBJECT( lion_nop_eval ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_result_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_param_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_generator_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_show_param_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_arr_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_set_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_ar1_s ); \
  BCORE_FORWARD_OBJECT( lion_nop_eval_ar2_s ); \
  typedef lion_nop_eval_result_s* (*lion_nop_eval_run)( const lion_nop_eval* o ); \
  typedef void (*lion_nop_eval_set_param)( lion_nop_eval* o, const lion_nop_eval_param_s* param ); \
  BCORE_DECLARE_SPECT( lion_nop_eval ) \
  { \
      bcore_spect_header_s header; \
      lion_nop_eval_run run; \
      lion_nop_eval_set_param set_param; \
  }; \
  static inline lion_nop_eval* lion_nop_eval_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_lion_nop_eval, t ); return ( lion_nop_eval* )bcore_inst_t_create( t ); } \
  static inline bl_t lion_nop_eval_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_lion_nop_eval ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( lion_nop_eval ) \
  static inline bl_t lion_nop_eval_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_lion_nop_eval ); } \
  BETH_EXPAND_ITEM_lion_nop_eval_result_s \
  static inline lion_nop_eval_result_s* lion_nop_eval_a_run( const lion_nop_eval* o ) { const lion_nop_eval_s* p = lion_nop_eval_s_get_aware( o ); assert( p->run ); return p->run( o ); } \
  static inline bl_t lion_nop_eval_a_defines_run( const lion_nop_eval* o ) { return lion_nop_eval_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_lion_nop_eval_param_s \
  BETH_EXPAND_ITEM_lion_nop_eval_generator_s \
  BETH_EXPAND_ITEM_lion_nop_eval_show_param_s \
  static inline void lion_nop_eval_a_set_param( lion_nop_eval* o, const lion_nop_eval_param_s* param ) { const lion_nop_eval_s* p = lion_nop_eval_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param ); } \
  static inline bl_t lion_nop_eval_a_defines_set_param( const lion_nop_eval* o ) { return lion_nop_eval_s_get_aware( o )->set_param != NULL; } \
  BETH_EXPAND_ITEM_lion_nop_eval_arr_s \
  BETH_EXPAND_ITEM_lion_nop_eval_set_s \
  BETH_EXPAND_ITEM_lion_nop_eval_ar1_s \
  BETH_EXPAND_ITEM_lion_nop_eval_ar2_s

/**********************************************************************************************************************/

vd_t lion_planted_signal_handler( const bcore_signal_s* o );

#endif // LION_PLANTED_H
