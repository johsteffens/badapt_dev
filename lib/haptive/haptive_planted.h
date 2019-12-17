/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019 J.B.Steffens
 *  Last File Update: 2019-12-12T12:53:52Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  haptive_graph.h
 *  haptive_eval.h
 *
 */

#ifndef HAPTIVE_PLANTED_H
#define HAPTIVE_PLANTED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: haptive_graph.h

//----------------------------------------------------------------------------------------------------------------------
// group: haptive

#define TYPEOF_haptive 900637884
#define TYPEOF_haptive_s 201032990
#define TYPEOF_cell 1759288501
#define TYPEOF_if 959999494
#define TYPEOF_then 3844270454
#define TYPEOF_else 3183434736
#define TYPEOF_op_class_regular 3052243102
#define TYPEOF_op_class_cast 1822035321
#define TYPEOF_mcode_name_infer 2452732934
#define TYPEOF_mcode_name_bp_grad 96056269
#define TYPEOF_mcode_name_setup 4135648683
#define TYPEOF_mcode_name_shelve 2166922705
#define TYPEOF_mcode_name_zero_adaptive_grad 1641647912
#define TYPEOF_mcode_name_cast 510677301
#define TYPEOF_mcode_name_cast_reverse 182560416
#define TYPEOF_mcode_name_ap_init 445533098
#define TYPEOF_holor_type_data 393476823
#define TYPEOF_holor_type_depletable 4171047993
#define TYPEOF_holor_type_adaptive 612987657
#define TYPEOF_holor_type_adaptive_grad 3377896594
#define TYPEOF_holor_type_cast 1844256624
#define TYPEOF_haptive_context_s 1662433658
#define BETH_EXPAND_ITEM_haptive_context_s \
  BCORE_DECLARE_OBJECT( haptive_context_s ) \
    {aware_t _;bcore_hmap_name_s hmap_name;bcore_arr_st_s arr_symbol_op2;haptive_sem_cell_s cell;bcore_arr_tp_s control_types;bcore_mutex_s* randomizer_mutex;bl_t randomizer_is_locked;u2_t randomizer_rval;};
#define BETH_EXPAND_GROUP_haptive \
  BCORE_FORWARD_OBJECT( haptive ); \
  BCORE_FORWARD_OBJECT( haptive_op ); \
  BCORE_FORWARD_OBJECT( haptive_sem ); \
  BCORE_FORWARD_OBJECT( haptive_ctr ); \
  BCORE_FORWARD_OBJECT( haptive_net ); \
  BCORE_FORWARD_OBJECT( haptive_vm ); \
  BCORE_FORWARD_OBJECT( haptive_context_s ); \
  BETH_EXPAND_GROUP_haptive_op \
  BETH_EXPAND_GROUP_haptive_sem \
  BETH_EXPAND_GROUP_haptive_ctr \
  BETH_EXPAND_GROUP_haptive_net \
  BETH_EXPAND_GROUP_haptive_vm \
  BETH_EXPAND_ITEM_haptive_context_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op

#define TYPEOF_haptive_op 856750966
#define TYPEOF_haptive_op_s 2197502312
#define BETH_EXPAND_GROUP_haptive_op \
  BCORE_FORWARD_OBJECT( haptive_op ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar0 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar3 ); \
  typedef sz_t (*haptive_op_get_arity)( const haptive_op* o ); \
  typedef tp_t (*haptive_op_get_class)( const haptive_op* o ); \
  typedef sz_t (*haptive_op_get_priority)( const haptive_op* o ); \
  typedef sc_t (*haptive_op_get_symbol)( const haptive_op* o ); \
  typedef haptive_op* (*haptive_op_create_op_of_arn)( const haptive_op* o, sz_t n ); \
  typedef s2_t (*haptive_op_solve)( const haptive_op* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  typedef bl_t (*haptive_op_solve_each_channel)( const haptive_op* o ); \
  typedef haptive_op* (*haptive_op_create_final)( const haptive_op* o, bhvm_hf3_s* h ); \
  typedef bhvm_hf3_vm_op* (*haptive_op_create_vm_op_ap_init)( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  typedef bhvm_hf3_vm_op* (*haptive_op_create_vm_op_ap_init_set_idx)( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  typedef bhvm_hf3_vm_op* (*haptive_op_create_vm_op_ap)( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  typedef bhvm_hf3_vm_op* (*haptive_op_create_vm_op_ap_set_idx)( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  typedef bhvm_hf3_vm_op* (*haptive_op_create_vm_op_dp)( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  typedef bhvm_hf3_vm_op* (*haptive_op_create_vm_op_dp_set_idx)( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  BCORE_DECLARE_SPECT( haptive_op ) \
  { \
      bcore_spect_header_s header; \
      haptive_op_get_arity get_arity; \
      haptive_op_get_class get_class; \
      haptive_op_get_priority get_priority; \
      haptive_op_get_symbol get_symbol; \
      haptive_op_create_op_of_arn create_op_of_arn; \
      haptive_op_solve solve; \
      haptive_op_solve_each_channel solve_each_channel; \
      haptive_op_create_final create_final; \
      haptive_op_create_vm_op_ap_init create_vm_op_ap_init; \
      haptive_op_create_vm_op_ap_init_set_idx create_vm_op_ap_init_set_idx; \
      haptive_op_create_vm_op_ap create_vm_op_ap; \
      haptive_op_create_vm_op_ap_set_idx create_vm_op_ap_set_idx; \
      haptive_op_create_vm_op_dp create_vm_op_dp; \
      haptive_op_create_vm_op_dp_set_idx create_vm_op_dp_set_idx; \
  }; \
  static inline haptive_op* haptive_op_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_haptive_op, t ); return ( haptive_op* )bcore_inst_t_create( t ); } \
  static inline bl_t haptive_op_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_haptive_op ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( haptive_op ) \
  static inline bl_t haptive_op_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_haptive_op ); } \
  static inline sz_t haptive_op_a_get_arity( const haptive_op* o ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->get_arity ); return p->get_arity( o ); } \
  static inline bl_t haptive_op_a_defines_get_arity( const haptive_op* o ) { return true; } \
  static inline tp_t haptive_op_a_get_class( const haptive_op* o ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->get_class ); return p->get_class( o ); } \
  static inline bl_t haptive_op_a_defines_get_class( const haptive_op* o ) { return true; } \
  static inline tp_t haptive_op_get_class__( const haptive_op* o ){return TYPEOF_op_class_regular;} \
  static inline sz_t haptive_op_a_get_priority( const haptive_op* o ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->get_priority ); return p->get_priority( o ); } \
  static inline bl_t haptive_op_a_defines_get_priority( const haptive_op* o ) { return true; } \
  static inline sz_t haptive_op_get_priority__( const haptive_op* o ){return 10;} \
  static inline sc_t haptive_op_a_get_symbol( const haptive_op* o ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->get_symbol ); return p->get_symbol( o ); } \
  static inline bl_t haptive_op_a_defines_get_symbol( const haptive_op* o ) { return true; } \
  static inline sc_t haptive_op_get_symbol__( const haptive_op* o ){return NULL;} \
  static inline haptive_op* haptive_op_a_create_op_of_arn( const haptive_op* o, sz_t n ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_op_of_arn ); return p->create_op_of_arn( o, n ); } \
  static inline bl_t haptive_op_a_defines_create_op_of_arn( const haptive_op* o ) { return true; } \
  static inline haptive_op* haptive_op_create_op_of_arn__( const haptive_op* o, sz_t n ){return ( haptive_op_a_get_arity( o ) == n ) ? haptive_op_a_clone( o ) : NULL;} \
  static inline s2_t haptive_op_a_solve( const haptive_op* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->solve ); return p->solve( o, r, a, msg ); } \
  static inline bl_t haptive_op_a_defines_solve( const haptive_op* o ) { return haptive_op_s_get_aware( o )->solve != NULL; } \
  static inline bl_t haptive_op_a_solve_each_channel( const haptive_op* o ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->solve_each_channel ); return p->solve_each_channel( o ); } \
  static inline bl_t haptive_op_a_defines_solve_each_channel( const haptive_op* o ) { return true; } \
  static inline bl_t haptive_op_solve_each_channel__( const haptive_op* o ){return false;} \
  static inline haptive_op* haptive_op_a_create_final( const haptive_op* o, bhvm_hf3_s* h ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_final ); return p->create_final( o, h ); } \
  static inline bl_t haptive_op_a_defines_create_final( const haptive_op* o ) { return true; } \
  haptive_op* haptive_op_create_final__( const haptive_op* o, bhvm_hf3_s* h ); \
  static inline bhvm_hf3_vm_op* haptive_op_a_create_vm_op_ap_init( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_vm_op_ap_init ); return p->create_vm_op_ap_init( o, vmf, arr_sig, arr_idx ); } \
  static inline bl_t haptive_op_a_defines_create_vm_op_ap_init( const haptive_op* o ) { return true; } \
  static inline bhvm_hf3_vm_op* haptive_op_create_vm_op_ap_init__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return NULL;} \
  static inline bhvm_hf3_vm_op* haptive_op_a_create_vm_op_ap_init_set_idx( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_vm_op_ap_init_set_idx ); return p->create_vm_op_ap_init_set_idx( o, vmf, arr_sig, arr_idx ); } \
  static inline bl_t haptive_op_a_defines_create_vm_op_ap_init_set_idx( const haptive_op* o ) { return true; } \
  bhvm_hf3_vm_op* haptive_op_create_vm_op_ap_init_set_idx__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  static inline bhvm_hf3_vm_op* haptive_op_a_create_vm_op_ap( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_vm_op_ap ); return p->create_vm_op_ap( o, vmf, arr_sig, arr_idx ); } \
  static inline bl_t haptive_op_a_defines_create_vm_op_ap( const haptive_op* o ) { return true; } \
  static inline bhvm_hf3_vm_op* haptive_op_create_vm_op_ap__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return NULL;} \
  static inline bhvm_hf3_vm_op* haptive_op_a_create_vm_op_ap_set_idx( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_vm_op_ap_set_idx ); return p->create_vm_op_ap_set_idx( o, vmf, arr_sig, arr_idx ); } \
  static inline bl_t haptive_op_a_defines_create_vm_op_ap_set_idx( const haptive_op* o ) { return true; } \
  bhvm_hf3_vm_op* haptive_op_create_vm_op_ap_set_idx__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  static inline bhvm_hf3_vm_op* haptive_op_a_create_vm_op_dp( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_vm_op_dp ); return p->create_vm_op_dp( o, vmf, arr_sig, arr_idx, ch_id ); } \
  static inline bl_t haptive_op_a_defines_create_vm_op_dp( const haptive_op* o ) { return true; } \
  static inline bhvm_hf3_vm_op* haptive_op_create_vm_op_dp__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){return NULL;} \
  static inline bhvm_hf3_vm_op* haptive_op_a_create_vm_op_dp_set_idx( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ) { const haptive_op_s* p = haptive_op_s_get_aware( o ); assert( p->create_vm_op_dp_set_idx ); return p->create_vm_op_dp_set_idx( o, vmf, arr_sig, arr_idx, ch_id ); } \
  static inline bl_t haptive_op_a_defines_create_vm_op_dp_set_idx( const haptive_op* o ) { return true; } \
  bhvm_hf3_vm_op* haptive_op_create_vm_op_dp_set_idx__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  BETH_EXPAND_GROUP_haptive_op_ar0 \
  BETH_EXPAND_GROUP_haptive_op_ar1 \
  BETH_EXPAND_GROUP_haptive_op_ar2 \
  BETH_EXPAND_GROUP_haptive_op_ar3

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar0

#define TYPEOF_haptive_op_ar0 2820452508
#define TYPEOF_haptive_op_ar0_s 2223423294
#define TYPEOF_haptive_op_ar0_literal_s 1596885370
#define BETH_EXPAND_ITEM_haptive_op_ar0_literal_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar0_literal_s ) \
    {aware_t _;bhvm_hf3_s* h;}; \
  s2_t haptive_op_ar0_literal_s_solve( const haptive_op_ar0_literal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar0_literal_s_get_arity( const haptive_op_ar0_literal_s* o ){return 0;}
#define TYPEOF_haptive_op_ar0_input_s 1735675625
#define BETH_EXPAND_ITEM_haptive_op_ar0_input_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar0_input_s ) \
    {aware_t _;bhvm_hf3_s* h;}; \
  s2_t haptive_op_ar0_input_s_solve( const haptive_op_ar0_input_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar0_input_s_get_arity( const haptive_op_ar0_input_s* o ){return 0;}
#define TYPEOF_haptive_op_ar0_adaptive_s 4110665497
#define BETH_EXPAND_ITEM_haptive_op_ar0_adaptive_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar0_adaptive_s ) \
    {aware_t _;bhvm_hf3_s* h;tp_t name;}; \
  s2_t haptive_op_ar0_adaptive_s_solve( const haptive_op_ar0_adaptive_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar0_adaptive_s_get_arity( const haptive_op_ar0_adaptive_s* o ){return 0;}
#define BETH_EXPAND_GROUP_haptive_op_ar0 \
  BCORE_FORWARD_OBJECT( haptive_op_ar0 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar0_literal_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar0_input_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar0_adaptive_s ); \
  BETH_EXPAND_ITEM_haptive_op_ar0_literal_s \
  BETH_EXPAND_ITEM_haptive_op_ar0_input_s \
  BETH_EXPAND_ITEM_haptive_op_ar0_adaptive_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar1

#define TYPEOF_haptive_op_ar1 2837230127
#define TYPEOF_haptive_op_ar1_s 3786295577
#define TYPEOF_haptive_op_ar1_identity_s 3722502060
#define BETH_EXPAND_ITEM_haptive_op_ar1_identity_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_identity_s ) \
    {aware_t _;}; \
  s2_t haptive_op_ar1_identity_s_solve( const haptive_op_ar1_identity_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_identity_s_create_vm_op_ap( const haptive_op_ar1_identity_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_identity_s_create_vm_op_dp( const haptive_op_ar1_identity_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_cpy_s_create();} \
  static inline sz_t haptive_op_ar1_identity_s_get_arity( const haptive_op_ar1_identity_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_neg_s 1108668352
#define BETH_EXPAND_ITEM_haptive_op_ar1_neg_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_neg_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_neg_s_get_symbol( const haptive_op_ar1_neg_s* o ){return "neg";} \
  static inline sz_t haptive_op_ar1_neg_s_get_priority( const haptive_op_ar1_neg_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_neg_s_solve( const haptive_op_ar1_neg_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_neg_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_neg_s_create_vm_op_ap( const haptive_op_ar1_neg_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_neg_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_neg_s_create_vm_op_dp( const haptive_op_ar1_neg_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_neg_s_create();} \
  haptive_op* haptive_op_ar1_neg_s_create_op_of_arn( const haptive_op_ar1_neg_s* o, sz_t n ); \
  static inline sz_t haptive_op_ar1_neg_s_get_arity( const haptive_op_ar1_neg_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_floor_s 116536248
#define BETH_EXPAND_ITEM_haptive_op_ar1_floor_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_floor_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_floor_s_get_symbol( const haptive_op_ar1_floor_s* o ){return "floor";} \
  static inline sz_t haptive_op_ar1_floor_s_get_priority( const haptive_op_ar1_floor_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_floor_s_solve( const haptive_op_ar1_floor_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_floor_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_floor_s_create_vm_op_ap( const haptive_op_ar1_floor_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_floor_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_floor_s_create_vm_op_dp( const haptive_op_ar1_floor_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar0_dp_ca_floor_s_create();} \
  static inline sz_t haptive_op_ar1_floor_s_get_arity( const haptive_op_ar1_floor_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_ceil_s 2402776267
#define BETH_EXPAND_ITEM_haptive_op_ar1_ceil_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_ceil_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_ceil_s_get_symbol( const haptive_op_ar1_ceil_s* o ){return "ceil";} \
  static inline sz_t haptive_op_ar1_ceil_s_get_priority( const haptive_op_ar1_ceil_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_ceil_s_solve( const haptive_op_ar1_ceil_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_ceil_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_ceil_s_create_vm_op_ap( const haptive_op_ar1_ceil_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_ceil_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_ceil_s_create_vm_op_dp( const haptive_op_ar1_ceil_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar0_dp_ca_ceil_s_create();} \
  static inline sz_t haptive_op_ar1_ceil_s_get_arity( const haptive_op_ar1_ceil_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_exp_s 1898334025
#define BETH_EXPAND_ITEM_haptive_op_ar1_exp_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_exp_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_exp_s_get_symbol( const haptive_op_ar1_exp_s* o ){return "exp";} \
  static inline sz_t haptive_op_ar1_exp_s_get_priority( const haptive_op_ar1_exp_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_exp_s_solve( const haptive_op_ar1_exp_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_exp_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_exp_s_create_vm_op_ap( const haptive_op_ar1_exp_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_exp_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_exp_s_create_vm_op_dp( const haptive_op_ar1_exp_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_exp_s_create();} \
  static inline sz_t haptive_op_ar1_exp_s_get_arity( const haptive_op_ar1_exp_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_lgst_s 1600681072
#define BETH_EXPAND_ITEM_haptive_op_ar1_lgst_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_lgst_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_lgst_s_get_symbol( const haptive_op_ar1_lgst_s* o ){return "lgst";} \
  static inline sz_t haptive_op_ar1_lgst_s_get_priority( const haptive_op_ar1_lgst_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_lgst_s_solve( const haptive_op_ar1_lgst_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_lgst_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_lgst_s_create_vm_op_ap( const haptive_op_ar1_lgst_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_lgst_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_lgst_s_create_vm_op_dp( const haptive_op_ar1_lgst_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_lgst_s_create();} \
  static inline sz_t haptive_op_ar1_lgst_s_get_arity( const haptive_op_ar1_lgst_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_lgst_hard_s 3587624952
#define BETH_EXPAND_ITEM_haptive_op_ar1_lgst_hard_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_lgst_hard_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_lgst_hard_s_get_symbol( const haptive_op_ar1_lgst_hard_s* o ){return "lgst_hard";} \
  static inline sz_t haptive_op_ar1_lgst_hard_s_get_priority( const haptive_op_ar1_lgst_hard_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_lgst_hard_s_solve( const haptive_op_ar1_lgst_hard_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_lgst_hard_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_lgst_hard_s_create_vm_op_ap( const haptive_op_ar1_lgst_hard_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_lgst_hard_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_lgst_hard_s_create_vm_op_dp( const haptive_op_ar1_lgst_hard_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_lgst_hard_s_create();} \
  static inline sz_t haptive_op_ar1_lgst_hard_s_get_arity( const haptive_op_ar1_lgst_hard_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_lgst_leaky_s 1839494669
#define BETH_EXPAND_ITEM_haptive_op_ar1_lgst_leaky_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_lgst_leaky_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_lgst_leaky_s_get_symbol( const haptive_op_ar1_lgst_leaky_s* o ){return "lgst_leaky";} \
  static inline sz_t haptive_op_ar1_lgst_leaky_s_get_priority( const haptive_op_ar1_lgst_leaky_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_lgst_leaky_s_solve( const haptive_op_ar1_lgst_leaky_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_lgst_leaky_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_lgst_leaky_s_create_vm_op_ap( const haptive_op_ar1_lgst_leaky_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_lgst_leaky_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_lgst_leaky_s_create_vm_op_dp( const haptive_op_ar1_lgst_leaky_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_lgst_leaky_s_create();} \
  static inline sz_t haptive_op_ar1_lgst_leaky_s_get_arity( const haptive_op_ar1_lgst_leaky_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_tanh_s 1042884931
#define BETH_EXPAND_ITEM_haptive_op_ar1_tanh_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_tanh_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_tanh_s_get_symbol( const haptive_op_ar1_tanh_s* o ){return "tanh";} \
  static inline sz_t haptive_op_ar1_tanh_s_get_priority( const haptive_op_ar1_tanh_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_tanh_s_solve( const haptive_op_ar1_tanh_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_tanh_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_tanh_s_create_vm_op_ap( const haptive_op_ar1_tanh_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_tanh_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_tanh_s_create_vm_op_dp( const haptive_op_ar1_tanh_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_tanh_s_create();} \
  static inline sz_t haptive_op_ar1_tanh_s_get_arity( const haptive_op_ar1_tanh_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_tanh_hard_s 2164453949
#define BETH_EXPAND_ITEM_haptive_op_ar1_tanh_hard_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_tanh_hard_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_tanh_hard_s_get_symbol( const haptive_op_ar1_tanh_hard_s* o ){return "tanh_hard";} \
  static inline sz_t haptive_op_ar1_tanh_hard_s_get_priority( const haptive_op_ar1_tanh_hard_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_tanh_hard_s_solve( const haptive_op_ar1_tanh_hard_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_tanh_hard_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_tanh_hard_s_create_vm_op_ap( const haptive_op_ar1_tanh_hard_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_tanh_hard_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_tanh_hard_s_create_vm_op_dp( const haptive_op_ar1_tanh_hard_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_tanh_hard_s_create();} \
  static inline sz_t haptive_op_ar1_tanh_hard_s_get_arity( const haptive_op_ar1_tanh_hard_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_tanh_leaky_s 4029199902
#define BETH_EXPAND_ITEM_haptive_op_ar1_tanh_leaky_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_tanh_leaky_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_tanh_leaky_s_get_symbol( const haptive_op_ar1_tanh_leaky_s* o ){return "tanh_leaky";} \
  static inline sz_t haptive_op_ar1_tanh_leaky_s_get_priority( const haptive_op_ar1_tanh_leaky_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_tanh_leaky_s_solve( const haptive_op_ar1_tanh_leaky_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_tanh_leaky_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_tanh_leaky_s_create_vm_op_ap( const haptive_op_ar1_tanh_leaky_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_tanh_leaky_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_tanh_leaky_s_create_vm_op_dp( const haptive_op_ar1_tanh_leaky_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_tanh_leaky_s_create();} \
  static inline sz_t haptive_op_ar1_tanh_leaky_s_get_arity( const haptive_op_ar1_tanh_leaky_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_softplus_s 1357244482
#define BETH_EXPAND_ITEM_haptive_op_ar1_softplus_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_softplus_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_softplus_s_get_symbol( const haptive_op_ar1_softplus_s* o ){return "softplus";} \
  static inline sz_t haptive_op_ar1_softplus_s_get_priority( const haptive_op_ar1_softplus_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_softplus_s_solve( const haptive_op_ar1_softplus_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_softplus_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_softplus_s_create_vm_op_ap( const haptive_op_ar1_softplus_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_softplus_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_softplus_s_create_vm_op_dp( const haptive_op_ar1_softplus_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_softplus_s_create();} \
  static inline sz_t haptive_op_ar1_softplus_s_get_arity( const haptive_op_ar1_softplus_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_relu_s 1734110320
#define BETH_EXPAND_ITEM_haptive_op_ar1_relu_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_relu_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_relu_s_get_symbol( const haptive_op_ar1_relu_s* o ){return "relu";} \
  static inline sz_t haptive_op_ar1_relu_s_get_priority( const haptive_op_ar1_relu_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_relu_s_solve( const haptive_op_ar1_relu_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_relu_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_relu_s_create_vm_op_ap( const haptive_op_ar1_relu_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_relu_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_relu_s_create_vm_op_dp( const haptive_op_ar1_relu_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_relu_s_create();} \
  static inline sz_t haptive_op_ar1_relu_s_get_arity( const haptive_op_ar1_relu_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_relu_leaky_s 3862474253
#define BETH_EXPAND_ITEM_haptive_op_ar1_relu_leaky_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_relu_leaky_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_relu_leaky_s_get_symbol( const haptive_op_ar1_relu_leaky_s* o ){return "relu_leaky";} \
  static inline sz_t haptive_op_ar1_relu_leaky_s_get_priority( const haptive_op_ar1_relu_leaky_s* o ){return 8;} \
  static inline s2_t haptive_op_ar1_relu_leaky_s_solve( const haptive_op_ar1_relu_leaky_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ){return haptive_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_relu_leaky_s_fx );} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_relu_leaky_s_create_vm_op_ap( const haptive_op_ar1_relu_leaky_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_relu_leaky_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_relu_leaky_s_create_vm_op_dp( const haptive_op_ar1_relu_leaky_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_relu_leaky_s_create();} \
  static inline sz_t haptive_op_ar1_relu_leaky_s_get_arity( const haptive_op_ar1_relu_leaky_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_htp_s 2248194830
#define BETH_EXPAND_ITEM_haptive_op_ar1_htp_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_htp_s ) \
    {aware_t _;}; \
  static inline tp_t haptive_op_ar1_htp_s_get_class( const haptive_op_ar1_htp_s* o ){return TYPEOF_op_class_cast;} \
  static inline sz_t haptive_op_ar1_htp_s_get_priority( const haptive_op_ar1_htp_s* o ){return 8;} \
  s2_t haptive_op_ar1_htp_s_solve( const haptive_op_ar1_htp_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_htp_s_create_vm_op_ap( const haptive_op_ar1_htp_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cast_htp_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_htp_s_create_vm_op_dp( const haptive_op_ar1_htp_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_cast_htp_s_create();} \
  static inline sz_t haptive_op_ar1_htp_s_get_arity( const haptive_op_ar1_htp_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_output_s 3401051791
#define BETH_EXPAND_ITEM_haptive_op_ar1_output_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_output_s ) \
    {aware_t _;}; \
  s2_t haptive_op_ar1_output_s_solve( const haptive_op_ar1_output_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_output_s_create_vm_op_ap( const haptive_op_ar1_output_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar1_output_s_create_vm_op_dp( const haptive_op_ar1_output_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ){ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_cpy_s_create();} \
  static inline sz_t haptive_op_ar1_output_s_get_arity( const haptive_op_ar1_output_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_adaptive_s 1988274712
#define BETH_EXPAND_ITEM_haptive_op_ar1_adaptive_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_adaptive_s ) \
    {aware_t _;tp_t name;}; \
  static inline sc_t haptive_op_ar1_adaptive_s_get_symbol( const haptive_op_ar1_adaptive_s* o ){return "adaptive";} \
  static inline sz_t haptive_op_ar1_adaptive_s_get_priority( const haptive_op_ar1_adaptive_s* o ){return 8;} \
  s2_t haptive_op_ar1_adaptive_s_solve( const haptive_op_ar1_adaptive_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  haptive_op* haptive_op_ar1_adaptive_s_create_final( const haptive_op_ar1_adaptive_s* o, bhvm_hf3_s* h ); \
  static inline sz_t haptive_op_ar1_adaptive_s_get_arity( const haptive_op_ar1_adaptive_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_dimof_s 893675473
#define BETH_EXPAND_ITEM_haptive_op_ar1_dimof_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_dimof_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar1_dimof_s_get_symbol( const haptive_op_ar1_dimof_s* o ){return "dimof";} \
  static inline sz_t haptive_op_ar1_dimof_s_get_priority( const haptive_op_ar1_dimof_s* o ){return 8;} \
  s2_t haptive_op_ar1_dimof_s_solve( const haptive_op_ar1_dimof_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar1_dimof_s_get_arity( const haptive_op_ar1_dimof_s* o ){return 1;}
#define TYPEOF_haptive_op_ar1_random_s 110295153
#define BETH_EXPAND_ITEM_haptive_op_ar1_random_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar1_random_s ) \
    {aware_t _;u2_t rseed;}; \
  static inline sc_t haptive_op_ar1_random_s_get_symbol( const haptive_op_ar1_random_s* o ){return "random";} \
  static inline sz_t haptive_op_ar1_random_s_get_priority( const haptive_op_ar1_random_s* o ){return 8;} \
  s2_t haptive_op_ar1_random_s_solve( const haptive_op_ar1_random_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar1_random_s_get_arity( const haptive_op_ar1_random_s* o ){return 1;}
#define BETH_EXPAND_GROUP_haptive_op_ar1 \
  BCORE_FORWARD_OBJECT( haptive_op_ar1 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_identity_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_neg_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_floor_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_ceil_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_exp_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_lgst_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_lgst_hard_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_lgst_leaky_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_tanh_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_tanh_hard_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_tanh_leaky_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_softplus_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_relu_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_relu_leaky_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_htp_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_output_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_adaptive_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_dimof_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar1_random_s ); \
  BETH_EXPAND_ITEM_haptive_op_ar1_identity_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_neg_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_floor_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_ceil_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_exp_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_lgst_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_lgst_hard_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_lgst_leaky_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_tanh_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_tanh_hard_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_tanh_leaky_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_softplus_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_relu_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_relu_leaky_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_htp_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_output_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_adaptive_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_dimof_s \
  BETH_EXPAND_ITEM_haptive_op_ar1_random_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar2

#define TYPEOF_haptive_op_ar2 2854007746
#define TYPEOF_haptive_op_ar2_s 1436075068
#define TYPEOF_haptive_op_ar2_bmul_s 2984255481
#define BETH_EXPAND_ITEM_haptive_op_ar2_bmul_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_bmul_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_bmul_s_get_symbol( const haptive_op_ar2_bmul_s* o ){return "**";} \
  static inline sz_t haptive_op_ar2_bmul_s_get_priority( const haptive_op_ar2_bmul_s* o ){return 9;} \
  s2_t haptive_op_ar2_bmul_s_solve( const haptive_op_ar2_bmul_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar2_bmul_s_create_vm_op_ap( const haptive_op_ar2_bmul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_bmul_s_create();} \
  bhvm_hf3_vm_op* haptive_op_ar2_bmul_s_create_vm_op_dp( const haptive_op_ar2_bmul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  static inline sz_t haptive_op_ar2_bmul_s_get_arity( const haptive_op_ar2_bmul_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_mul_s 2333743137
#define BETH_EXPAND_ITEM_haptive_op_ar2_mul_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_mul_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_mul_s_get_symbol( const haptive_op_ar2_mul_s* o ){return "*";} \
  static inline sz_t haptive_op_ar2_mul_s_get_priority( const haptive_op_ar2_mul_s* o ){return 9;} \
  s2_t haptive_op_ar2_mul_s_solve( const haptive_op_ar2_mul_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  bhvm_hf3_vm_op* haptive_op_ar2_mul_s_create_vm_op_ap( const haptive_op_ar2_mul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ); \
  bhvm_hf3_vm_op* haptive_op_ar2_mul_s_create_vm_op_dp( const haptive_op_ar2_mul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  static inline sz_t haptive_op_ar2_mul_s_get_arity( const haptive_op_ar2_mul_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_add_s 507445292
#define BETH_EXPAND_ITEM_haptive_op_ar2_add_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_add_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_add_s_get_symbol( const haptive_op_ar2_add_s* o ){return "+";} \
  static inline sz_t haptive_op_ar2_add_s_get_priority( const haptive_op_ar2_add_s* o ){return 8;} \
  s2_t haptive_op_ar2_add_s_solve( const haptive_op_ar2_add_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar2_add_s_create_vm_op_ap( const haptive_op_ar2_add_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_add_s_create();} \
  bhvm_hf3_vm_op* haptive_op_ar2_add_s_create_vm_op_dp( const haptive_op_ar2_add_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  static inline sz_t haptive_op_ar2_add_s_get_arity( const haptive_op_ar2_add_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_sub_s 3915630525
#define BETH_EXPAND_ITEM_haptive_op_ar2_sub_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_sub_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_sub_s_get_symbol( const haptive_op_ar2_sub_s* o ){return "-";} \
  static inline sz_t haptive_op_ar2_sub_s_get_priority( const haptive_op_ar2_sub_s* o ){return 8;} \
  s2_t haptive_op_ar2_sub_s_solve( const haptive_op_ar2_sub_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar2_sub_s_create_vm_op_ap( const haptive_op_ar2_sub_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_sub_s_create();} \
  bhvm_hf3_vm_op* haptive_op_ar2_sub_s_create_vm_op_dp( const haptive_op_ar2_sub_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id ); \
  haptive_op* haptive_op_ar2_sub_s_create_op_of_arn( const haptive_op_ar2_sub_s* o, sz_t n ); \
  static inline sz_t haptive_op_ar2_sub_s_get_arity( const haptive_op_ar2_sub_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_equal_s 249548095
#define BETH_EXPAND_ITEM_haptive_op_ar2_equal_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_equal_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_equal_s_get_symbol( const haptive_op_ar2_equal_s* o ){return "==";} \
  static inline sz_t haptive_op_ar2_equal_s_get_priority( const haptive_op_ar2_equal_s* o ){return 6;} \
  s2_t haptive_op_ar2_equal_s_solve( const haptive_op_ar2_equal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_equal_s_get_arity( const haptive_op_ar2_equal_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_larger_s 1346535242
#define BETH_EXPAND_ITEM_haptive_op_ar2_larger_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_larger_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_larger_s_get_symbol( const haptive_op_ar2_larger_s* o ){return ">";} \
  static inline sz_t haptive_op_ar2_larger_s_get_priority( const haptive_op_ar2_larger_s* o ){return 6;} \
  s2_t haptive_op_ar2_larger_s_solve( const haptive_op_ar2_larger_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_larger_s_get_arity( const haptive_op_ar2_larger_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_smaller_s 3169127723
#define BETH_EXPAND_ITEM_haptive_op_ar2_smaller_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_smaller_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_smaller_s_get_symbol( const haptive_op_ar2_smaller_s* o ){return "<";} \
  static inline sz_t haptive_op_ar2_smaller_s_get_priority( const haptive_op_ar2_smaller_s* o ){return 6;} \
  s2_t haptive_op_ar2_smaller_s_solve( const haptive_op_ar2_smaller_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_smaller_s_get_arity( const haptive_op_ar2_smaller_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_larger_equal_s 603459713
#define BETH_EXPAND_ITEM_haptive_op_ar2_larger_equal_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_larger_equal_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_larger_equal_s_get_symbol( const haptive_op_ar2_larger_equal_s* o ){return ">=";} \
  static inline sz_t haptive_op_ar2_larger_equal_s_get_priority( const haptive_op_ar2_larger_equal_s* o ){return 6;} \
  s2_t haptive_op_ar2_larger_equal_s_solve( const haptive_op_ar2_larger_equal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_larger_equal_s_get_arity( const haptive_op_ar2_larger_equal_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_smaller_equal_s 2989271408
#define BETH_EXPAND_ITEM_haptive_op_ar2_smaller_equal_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_smaller_equal_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_smaller_equal_s_get_symbol( const haptive_op_ar2_smaller_equal_s* o ){return "<=";} \
  static inline sz_t haptive_op_ar2_smaller_equal_s_get_priority( const haptive_op_ar2_smaller_equal_s* o ){return 6;} \
  s2_t haptive_op_ar2_smaller_equal_s_solve( const haptive_op_ar2_smaller_equal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_smaller_equal_s_get_arity( const haptive_op_ar2_smaller_equal_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_logic_and_s 4227634991
#define BETH_EXPAND_ITEM_haptive_op_ar2_logic_and_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_logic_and_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_logic_and_s_get_symbol( const haptive_op_ar2_logic_and_s* o ){return "&";} \
  static inline sz_t haptive_op_ar2_logic_and_s_get_priority( const haptive_op_ar2_logic_and_s* o ){return 6;} \
  s2_t haptive_op_ar2_logic_and_s_solve( const haptive_op_ar2_logic_and_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_logic_and_s_get_arity( const haptive_op_ar2_logic_and_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_logic_or_s 2130890827
#define BETH_EXPAND_ITEM_haptive_op_ar2_logic_or_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_logic_or_s ) \
    {aware_t _;}; \
  static inline sc_t haptive_op_ar2_logic_or_s_get_symbol( const haptive_op_ar2_logic_or_s* o ){return "|";} \
  static inline sz_t haptive_op_ar2_logic_or_s_get_priority( const haptive_op_ar2_logic_or_s* o ){return 6;} \
  s2_t haptive_op_ar2_logic_or_s_solve( const haptive_op_ar2_logic_or_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_logic_or_s_get_arity( const haptive_op_ar2_logic_or_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_index_s 1044964511
#define BETH_EXPAND_ITEM_haptive_op_ar2_index_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_index_s ) \
    {aware_t _;}; \
  static inline sz_t haptive_op_ar2_index_s_get_priority( const haptive_op_ar2_index_s* o ){return 20;} \
  s2_t haptive_op_ar2_index_s_solve( const haptive_op_ar2_index_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_index_s_get_arity( const haptive_op_ar2_index_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_inc_order_s 3681973472
#define BETH_EXPAND_ITEM_haptive_op_ar2_inc_order_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_inc_order_s ) \
    {aware_t _;}; \
  static inline sz_t haptive_op_ar2_inc_order_s_get_priority( const haptive_op_ar2_inc_order_s* o ){return 20;} \
  s2_t haptive_op_ar2_inc_order_s_solve( const haptive_op_ar2_inc_order_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_inc_order_s_get_arity( const haptive_op_ar2_inc_order_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_cat_s 2696809875
#define BETH_EXPAND_ITEM_haptive_op_ar2_cat_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_cat_s ) \
    {aware_t _;}; \
  static inline sz_t haptive_op_ar2_cat_s_get_priority( const haptive_op_ar2_cat_s* o ){return 6;} \
  s2_t haptive_op_ar2_cat_s_solve( const haptive_op_ar2_cat_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar2_cat_s_get_arity( const haptive_op_ar2_cat_s* o ){return 2;}
#define TYPEOF_haptive_op_ar2_recurrent_s 304285521
#define BETH_EXPAND_ITEM_haptive_op_ar2_recurrent_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar2_recurrent_s ) \
    {aware_t _;tp_t name;}; \
  static inline sz_t haptive_op_ar2_recurrent_s_get_priority( const haptive_op_ar2_recurrent_s* o ){return 8;} \
  static inline bl_t haptive_op_ar2_recurrent_s_solve_each_channel( const haptive_op_ar2_recurrent_s* o ){return true;} \
  s2_t haptive_op_ar2_recurrent_s_solve( const haptive_op_ar2_recurrent_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline bhvm_hf3_vm_op* haptive_op_ar2_recurrent_s_create_vm_op_ap_init( const haptive_op_ar2_recurrent_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_ay_s_create();} \
  static inline bhvm_hf3_vm_op* haptive_op_ar2_recurrent_s_create_vm_op_ap( const haptive_op_ar2_recurrent_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx ){return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_by_s_create();} \
  static inline sz_t haptive_op_ar2_recurrent_s_get_arity( const haptive_op_ar2_recurrent_s* o ){return 2;}
#define BETH_EXPAND_GROUP_haptive_op_ar2 \
  BCORE_FORWARD_OBJECT( haptive_op_ar2 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_bmul_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_mul_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_add_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_sub_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_equal_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_larger_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_smaller_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_larger_equal_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_smaller_equal_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_logic_and_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_logic_or_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_index_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_inc_order_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_cat_s ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar2_recurrent_s ); \
  BETH_EXPAND_ITEM_haptive_op_ar2_bmul_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_mul_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_add_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_sub_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_equal_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_larger_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_smaller_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_larger_equal_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_smaller_equal_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_logic_and_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_logic_or_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_index_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_inc_order_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_cat_s \
  BETH_EXPAND_ITEM_haptive_op_ar2_recurrent_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar3

#define TYPEOF_haptive_op_ar3 2870785365
#define TYPEOF_haptive_op_ar3_s 3525385399
#define TYPEOF_haptive_op_ar3_branch_s 2163821808
#define BETH_EXPAND_ITEM_haptive_op_ar3_branch_s \
  BCORE_DECLARE_OBJECT( haptive_op_ar3_branch_s ) \
    {aware_t _;}; \
  static inline sz_t haptive_op_ar3_branch_s_get_priority( const haptive_op_ar3_branch_s* o ){return  5;} \
  s2_t haptive_op_ar3_branch_s_solve( const haptive_op_ar3_branch_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg ); \
  static inline sz_t haptive_op_ar3_branch_s_get_arity( const haptive_op_ar3_branch_s* o ){return  3;}
#define BETH_EXPAND_GROUP_haptive_op_ar3 \
  BCORE_FORWARD_OBJECT( haptive_op_ar3 ); \
  BCORE_FORWARD_OBJECT( haptive_op_ar3_branch_s ); \
  BETH_EXPAND_ITEM_haptive_op_ar3_branch_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_sem

#define TYPEOF_haptive_sem 1069326628
#define TYPEOF_haptive_sem_s 3209242262
#define TYPEOF_haptive_sem_link_s 4008788567
#define BETH_EXPAND_ITEM_haptive_sem_link_s \
  BCORE_DECLARE_OBJECT( haptive_sem_link_s ) \
    {aware_t _;tp_t name;haptive_sem_link_s* up;haptive_sem_link_s* dn;vd_t cell;bl_t exit;}; \
  static inline tp_t haptive_sem_link_s_get_name( const haptive_sem_link_s* o ){return o->name;}
#define TYPEOF_haptive_sem_links_s 4201010668
#define BETH_EXPAND_ITEM_haptive_sem_links_s \
  BCORE_DECLARE_OBJECT( haptive_sem_links_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( haptive_sem_link_s, );}; \
  haptive_sem_link_s* haptive_sem_links_s_get_link_by_name( haptive_sem_links_s* o, tp_t name ); \
  bl_t haptive_sem_links_s_name_exists( const haptive_sem_links_s* o, tp_t name ); \
  haptive_sem_link_s* haptive_sem_links_s_get_link_by_up( haptive_sem_links_s* o, haptive_sem_link_s* up ); \
  haptive_sem_link_s* haptive_sem_links_s_get_link_by_dn( haptive_sem_links_s* o, haptive_sem_link_s* dn ); \
  sz_t haptive_sem_links_s_get_index_by_link( haptive_sem_links_s* o, haptive_sem_link_s* link ); \
  sz_t haptive_sem_links_s_count_open( const haptive_sem_links_s* o ); \
  static inline void haptive_sem_links_s_set_space( haptive_sem_links_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_haptive_sem_links_s, ( bcore_array* )o, size ); } \
  static inline void haptive_sem_links_s_set_size( haptive_sem_links_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_haptive_sem_links_s, ( bcore_array* )o, size ); } \
  static inline void haptive_sem_links_s_clear( haptive_sem_links_s* o ) { bcore_array_t_set_space( TYPEOF_haptive_sem_links_s, ( bcore_array* )o, 0 ); } \
  static inline haptive_sem_link_s* haptive_sem_links_s_push_c( haptive_sem_links_s* o, const haptive_sem_link_s* v ) { bcore_array_t_push( TYPEOF_haptive_sem_links_s, ( bcore_array* )o, sr_twc( TYPEOF_haptive_sem_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_sem_link_s* haptive_sem_links_s_push_d( haptive_sem_links_s* o,       haptive_sem_link_s* v ) { bcore_array_t_push( TYPEOF_haptive_sem_links_s, ( bcore_array* )o, sr_tsd( TYPEOF_haptive_sem_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_sem_link_s* haptive_sem_links_s_push( haptive_sem_links_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_haptive_sem_links_s, ( bcore_array* )o, sr_t_create( TYPEOF_haptive_sem_link_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_haptive_sem_body_s 2061707067
#define BETH_EXPAND_ITEM_haptive_sem_body_s \
  BCORE_DECLARE_OBJECT( haptive_sem_body_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( haptive_sem, );}; \
  bl_t haptive_sem_body_s_name_exists( const haptive_sem_body_s* o, tp_t name ); \
  haptive_sem* haptive_sem_body_s_get_sem_by_name( haptive_sem_body_s* o, tp_t name ); \
  static inline void haptive_sem_body_s_set_space( haptive_sem_body_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_haptive_sem_body_s, ( bcore_array* )o, size ); } \
  static inline void haptive_sem_body_s_set_size( haptive_sem_body_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_haptive_sem_body_s, ( bcore_array* )o, size ); } \
  static inline void haptive_sem_body_s_clear( haptive_sem_body_s* o ) { bcore_array_t_set_space( TYPEOF_haptive_sem_body_s, ( bcore_array* )o, 0 ); } \
  static inline haptive_sem* haptive_sem_body_s_push_c( haptive_sem_body_s* o, const haptive_sem* v ) { bcore_array_t_push( TYPEOF_haptive_sem_body_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_sem* haptive_sem_body_s_push_d( haptive_sem_body_s* o,       haptive_sem* v ) { bcore_array_t_push( TYPEOF_haptive_sem_body_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_sem* haptive_sem_body_s_push_t( haptive_sem_body_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_haptive_sem, t ); \
      bcore_array_t_push( TYPEOF_haptive_sem_body_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_haptive_sem_cell_s 3369430867
#define BETH_EXPAND_ITEM_haptive_sem_cell_s \
  BCORE_DECLARE_OBJECT( haptive_sem_cell_s ) \
    {aware_t _;tp_t name;haptive_sem_links_s encs;haptive_sem_links_s excs;haptive_sem_body_s* body;haptive_op* op;sz_t priority;haptive_sem_cell_s* parent;bcore_source_point_s source_point;}; \
  static inline tp_t haptive_sem_cell_s_get_name( const haptive_sem_cell_s* o ){return o->name;} \
  static inline sz_t haptive_sem_cell_s_get_arity( const haptive_sem_cell_s* o ){return haptive_sem_links_s_count_open(       &o->encs       );} \
  static inline haptive_sem_link_s* haptive_sem_cell_s_get_enc_by_name( haptive_sem_cell_s* o, tp_t name ){return haptive_sem_links_s_get_link_by_name( &o->encs, name );} \
  static inline haptive_sem_link_s* haptive_sem_cell_s_get_exc_by_name( haptive_sem_cell_s* o, tp_t name ){return haptive_sem_links_s_get_link_by_name( &o->excs, name );} \
  static inline haptive_sem_link_s* haptive_sem_cell_s_get_enc_by_open( haptive_sem_cell_s* o ){return haptive_sem_links_s_get_link_by_up(   &o->encs, NULL );} \
  static inline haptive_sem_link_s* haptive_sem_cell_s_get_enc_by_dn( haptive_sem_cell_s* o, haptive_sem_link_s* dn ){return haptive_sem_links_s_get_link_by_dn(   &o->encs, dn   );} \
  static inline sz_t haptive_sem_cell_s_get_priority( const haptive_sem_cell_s* o ){return o->priority;} \
  haptive_sem_cell_s* haptive_sem_cell_s_get_cell_by_name( haptive_sem_cell_s* o, tp_t name ); \
  haptive_sem_link_s* haptive_sem_cell_s_get_link_by_name( haptive_sem_cell_s* o, tp_t name );
#define TYPEOF_haptive_sem_stack_flag_s 1664665544
#define BETH_EXPAND_ITEM_haptive_sem_stack_flag_s \
  BCORE_DECLARE_OBJECT( haptive_sem_stack_flag_s ) \
    {aware_t _;};
#define BETH_EXPAND_GROUP_haptive_sem \
  BCORE_FORWARD_OBJECT( haptive_sem ); \
  BCORE_FORWARD_OBJECT( haptive_sem_link_s ); \
  BCORE_FORWARD_OBJECT( haptive_sem_links_s ); \
  BCORE_FORWARD_OBJECT( haptive_sem_body_s ); \
  BCORE_FORWARD_OBJECT( haptive_sem_cell_s ); \
  BCORE_FORWARD_OBJECT( haptive_sem_stack_flag_s ); \
  typedef tp_t (*haptive_sem_get_name)( const haptive_sem* o ); \
  BCORE_DECLARE_SPECT( haptive_sem ) \
  { \
      bcore_spect_header_s header; \
      haptive_sem_get_name get_name; \
  }; \
  static inline haptive_sem* haptive_sem_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_haptive_sem, t ); return ( haptive_sem* )bcore_inst_t_create( t ); } \
  static inline bl_t haptive_sem_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_haptive_sem ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( haptive_sem ) \
  static inline bl_t haptive_sem_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_haptive_sem ); } \
  static inline tp_t haptive_sem_a_get_name( const haptive_sem* o ) { const haptive_sem_s* p = haptive_sem_s_get_aware( o ); assert( p->get_name ); return p->get_name( o ); } \
  static inline bl_t haptive_sem_a_defines_get_name( const haptive_sem* o ) { return true; } \
  static inline tp_t haptive_sem_get_name__( const haptive_sem* o ){return 0;} \
  BETH_EXPAND_ITEM_haptive_sem_link_s \
  BETH_EXPAND_ITEM_haptive_sem_links_s \
  BETH_EXPAND_ITEM_haptive_sem_body_s \
  BETH_EXPAND_ITEM_haptive_sem_cell_s \
  BETH_EXPAND_ITEM_haptive_sem_stack_flag_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_ctr

#define TYPEOF_haptive_ctr 705654132
#define TYPEOF_haptive_ctr_s 3887095654
#define TYPEOF_haptive_ctr_node_s 1617412499
#define BETH_EXPAND_ITEM_haptive_ctr_node_s \
  BCORE_DECLARE_OBJECT( haptive_ctr_node_s ) \
    {aware_t _;sz_t id;haptive_sem_cell_s* cell;haptive_ctr_node_s* parent;BCORE_ARRAY_DYN_LINK_STATIC_S( haptive_ctr_node_s, );}; \
  static inline void haptive_ctr_node_s_set_space( haptive_ctr_node_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_haptive_ctr_node_s, ( bcore_array* )o, size ); } \
  static inline void haptive_ctr_node_s_set_size( haptive_ctr_node_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_haptive_ctr_node_s, ( bcore_array* )o, size ); } \
  static inline void haptive_ctr_node_s_clear( haptive_ctr_node_s* o ) { bcore_array_t_set_space( TYPEOF_haptive_ctr_node_s, ( bcore_array* )o, 0 ); } \
  static inline haptive_ctr_node_s* haptive_ctr_node_s_push_c( haptive_ctr_node_s* o, const haptive_ctr_node_s* v ) { bcore_array_t_push( TYPEOF_haptive_ctr_node_s, ( bcore_array* )o, sr_twc( TYPEOF_haptive_ctr_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_ctr_node_s* haptive_ctr_node_s_push_d( haptive_ctr_node_s* o,       haptive_ctr_node_s* v ) { bcore_array_t_push( TYPEOF_haptive_ctr_node_s, ( bcore_array* )o, sr_tsd( TYPEOF_haptive_ctr_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_ctr_node_s* haptive_ctr_node_s_push( haptive_ctr_node_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_haptive_ctr_node_s, ( bcore_array* )o, sr_t_create( TYPEOF_haptive_ctr_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_haptive_ctr_tree_s 173480675
#define BETH_EXPAND_ITEM_haptive_ctr_tree_s \
  BCORE_DECLARE_OBJECT( haptive_ctr_tree_s ) \
    {aware_t _;sz_t id_base;haptive_ctr_node_s* root;};
#define BETH_EXPAND_GROUP_haptive_ctr \
  BCORE_FORWARD_OBJECT( haptive_ctr ); \
  BCORE_FORWARD_OBJECT( haptive_ctr_node_s ); \
  BCORE_FORWARD_OBJECT( haptive_ctr_tree_s ); \
  BETH_EXPAND_ITEM_haptive_ctr_node_s \
  BETH_EXPAND_ITEM_haptive_ctr_tree_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_net

#define TYPEOF_haptive_net 3463331372
#define TYPEOF_haptive_net_s 887168270
#define TYPEOF_haptive_net_link_s 891386447
#define BETH_EXPAND_ITEM_haptive_net_link_s \
  BCORE_DECLARE_OBJECT( haptive_net_link_s ) \
    {aware_t _;vd_t node;};
#define TYPEOF_haptive_net_links_s 2523006868
#define BETH_EXPAND_ITEM_haptive_net_links_s \
  BCORE_DECLARE_OBJECT( haptive_net_links_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( haptive_net_link_s, );}; \
  static inline void haptive_net_links_s_set_space( haptive_net_links_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_haptive_net_links_s, ( bcore_array* )o, size ); } \
  static inline void haptive_net_links_s_set_size( haptive_net_links_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_haptive_net_links_s, ( bcore_array* )o, size ); } \
  static inline void haptive_net_links_s_clear( haptive_net_links_s* o ) { bcore_array_t_set_space( TYPEOF_haptive_net_links_s, ( bcore_array* )o, 0 ); } \
  static inline haptive_net_link_s* haptive_net_links_s_push_c( haptive_net_links_s* o, const haptive_net_link_s* v ) { bcore_array_t_push( TYPEOF_haptive_net_links_s, ( bcore_array* )o, sr_twc( TYPEOF_haptive_net_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_net_link_s* haptive_net_links_s_push_d( haptive_net_links_s* o,       haptive_net_link_s* v ) { bcore_array_t_push( TYPEOF_haptive_net_links_s, ( bcore_array* )o, sr_tsd( TYPEOF_haptive_net_link_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_net_link_s* haptive_net_links_s_push( haptive_net_links_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_haptive_net_links_s, ( bcore_array* )o, sr_t_create( TYPEOF_haptive_net_link_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_haptive_net_node_s 3528501243
#define BETH_EXPAND_ITEM_haptive_net_node_s \
  BCORE_DECLARE_OBJECT( haptive_net_node_s ) \
    {aware_t _;haptive_net_links_s upls;haptive_net_links_s dnls;bl_t flag;sz_t id;sz_t gid;tp_t name;haptive_op* op;bhvm_hf3_s* h;bcore_source_point_s* source_point;}; \
  void haptive_net_node_s_solve( haptive_net_node_s* o );
#define TYPEOF_haptive_net_nodes_s 515475384
#define BETH_EXPAND_ITEM_haptive_net_nodes_s \
  BCORE_DECLARE_OBJECT( haptive_net_nodes_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( haptive_net_node_s, );}; \
  haptive_net_node_s* haptive_net_nodes_s_get_by_id( haptive_net_nodes_s* o, sz_t id ); \
  static inline void haptive_net_nodes_s_set_space( haptive_net_nodes_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_haptive_net_nodes_s, ( bcore_array* )o, size ); } \
  static inline void haptive_net_nodes_s_set_size( haptive_net_nodes_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_haptive_net_nodes_s, ( bcore_array* )o, size ); } \
  static inline void haptive_net_nodes_s_clear( haptive_net_nodes_s* o ) { bcore_array_t_set_space( TYPEOF_haptive_net_nodes_s, ( bcore_array* )o, 0 ); } \
  static inline haptive_net_node_s* haptive_net_nodes_s_push_c( haptive_net_nodes_s* o, const haptive_net_node_s* v ) { bcore_array_t_push( TYPEOF_haptive_net_nodes_s, ( bcore_array* )o, sr_twc( TYPEOF_haptive_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_net_node_s* haptive_net_nodes_s_push_d( haptive_net_nodes_s* o,       haptive_net_node_s* v ) { bcore_array_t_push( TYPEOF_haptive_net_nodes_s, ( bcore_array* )o, sr_tsd( TYPEOF_haptive_net_node_s, v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_net_node_s* haptive_net_nodes_s_push( haptive_net_nodes_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_haptive_net_nodes_s, ( bcore_array* )o, sr_t_create( TYPEOF_haptive_net_node_s ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_haptive_net_cell_s 2229557803
#define BETH_EXPAND_ITEM_haptive_net_cell_s \
  BCORE_DECLARE_OBJECT( haptive_net_cell_s ) \
    {aware_t _;sz_t max_depth;haptive_net_nodes_s body;haptive_net_nodes_s encs;haptive_net_nodes_s excs;}; \
  bl_t haptive_net_cell_s_is_consistent( const haptive_net_cell_s* o ); \
  void haptive_net_cell_s_normalize( haptive_net_cell_s* o ); \
  void haptive_net_cell_s_clear_flags( haptive_net_cell_s* o ); \
  void haptive_net_cell_s_solve( haptive_net_cell_s* o ); \
  void haptive_net_cell_s_clear_downlinks( haptive_net_cell_s* o ); \
  void haptive_net_cell_s_set_downlinks( haptive_net_cell_s* o ); \
  void haptive_net_cell_s_copy_x( haptive_net_cell_s* o ); \
  static inline void haptive_net_cell_s_mutated( haptive_net_cell_s* o ){ERR_fa( "Cannot reconstitute." );}
#define BETH_EXPAND_GROUP_haptive_net \
  BCORE_FORWARD_OBJECT( haptive_net ); \
  BCORE_FORWARD_OBJECT( haptive_net_link_s ); \
  BCORE_FORWARD_OBJECT( haptive_net_links_s ); \
  BCORE_FORWARD_OBJECT( haptive_net_node_s ); \
  BCORE_FORWARD_OBJECT( haptive_net_nodes_s ); \
  BCORE_FORWARD_OBJECT( haptive_net_cell_s ); \
  BETH_EXPAND_ITEM_haptive_net_link_s \
  BETH_EXPAND_ITEM_haptive_net_links_s \
  BETH_EXPAND_ITEM_haptive_net_node_s \
  BETH_EXPAND_ITEM_haptive_net_nodes_s \
  BETH_EXPAND_ITEM_haptive_net_cell_s

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_vm

#define TYPEOF_haptive_vm 1274955440
#define TYPEOF_haptive_vm_s 1912019146
#define TYPEOF_haptive_vm_adaptive_s 1615901349
#define BETH_EXPAND_ITEM_haptive_vm_adaptive_s \
  BCORE_DECLARE_OBJECT( haptive_vm_adaptive_s ) \
    {aware_t _;st_s sig;vd_t src;bhvm_hf3_vm_frame_s vm;badapt_dynamics_std_s dynamics;sz_t in_size;sz_t out_size;sz_t index_in;sz_t index_out;sz_t index_grad_out;bcore_arr_sz_s index_arr_adaptive;}; \
  static inline sz_t haptive_vm_adaptive_s_get_in_size( const haptive_vm_adaptive_s* o ){return o->in_size;} \
  static inline sz_t haptive_vm_adaptive_s_get_out_size( const haptive_vm_adaptive_s* o ){return o->out_size;} \
  static inline void haptive_vm_adaptive_s_get_dynamics_std( const haptive_vm_adaptive_s* o, badapt_dynamics_std_s* dynamics ){badapt_dynamics_std_s_copy( dynamics, &o->dynamics );} \
  static inline void haptive_vm_adaptive_s_set_dynamics_std( haptive_vm_adaptive_s* o, const badapt_dynamics_std_s* dynamics ){badapt_dynamics_std_s_copy( &o->dynamics, dynamics );} \
  void haptive_vm_adaptive_s_arc_to_sink( const haptive_vm_adaptive_s* o, bcore_sink* sink ); \
  void haptive_vm_adaptive_s_minfer( haptive_vm_adaptive_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
  void haptive_vm_adaptive_s_bgrad_adapt( haptive_vm_adaptive_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );
#define TYPEOF_haptive_vm_builder_s 1229612882
#define BETH_EXPAND_ITEM_haptive_vm_builder_s \
  BCORE_DECLARE_OBJECT( haptive_vm_builder_s ) \
    {aware_t _;st_s sig;vd_t src;sz_t in_size;sz_t out_size;badapt_dynamics_std_s dynamics;u2_t rseed;}; \
  static inline sz_t haptive_vm_builder_s_get_in_size( const haptive_vm_builder_s* o ){return o->in_size;} \
  static inline void haptive_vm_builder_s_set_in_size( haptive_vm_builder_s* o, sz_t size ){o->in_size = size;} \
  static inline sz_t haptive_vm_builder_s_get_out_size( const haptive_vm_builder_s* o ){return o->out_size;} \
  static inline void haptive_vm_builder_s_set_out_size( haptive_vm_builder_s* o, sz_t size ){o->out_size = size;} \
  badapt_adaptive* haptive_vm_builder_s_build( const haptive_vm_builder_s* o );
#define BETH_EXPAND_GROUP_haptive_vm \
  BCORE_FORWARD_OBJECT( haptive_vm ); \
  BCORE_FORWARD_OBJECT( haptive_vm_adaptive_s ); \
  BCORE_FORWARD_OBJECT( haptive_vm_builder_s ); \
  BETH_EXPAND_ITEM_haptive_vm_adaptive_s \
  BETH_EXPAND_ITEM_haptive_vm_builder_s

/**********************************************************************************************************************/
// source: haptive_eval.h

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_eval

#define TYPEOF_haptive_eval 2825530635
#define TYPEOF_haptive_eval_s 2463022429
#define TYPEOF_haptive_eval_grad_s 2708993990
#define BETH_EXPAND_ITEM_haptive_eval_grad_s \
  BCORE_DECLARE_OBJECT( haptive_eval_grad_s ) \
    {aware_t _;f3_t epsilon;bhvm_hf3_vm_frame_s* vmf;bhvm_hf3_adl_s* in;bhvm_hf3_adl_s* out;s2_t verbosity;f3_t max_dev;bcore_sink* log;}; \
  static inline void haptive_eval_grad_s_init_x( haptive_eval_grad_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  s2_t haptive_eval_grad_s_run( const haptive_eval_grad_s* o ); \
  static inline s2_t haptive_eval_grad_s_main( haptive_eval_grad_s* o, const bcore_arr_st_s* args ){return haptive_eval_grad_s_run( o );}
#define TYPEOF_haptive_eval_e2e_s 70660180
#define BETH_EXPAND_ITEM_haptive_eval_e2e_s \
  BCORE_DECLARE_OBJECT( haptive_eval_e2e_s ) \
    {aware_t _;st_s name;st_s sig;vd_t src;bhvm_hf3_adl_s* in;bhvm_hf3_adl_s* out;sz_t infer_cycles;s2_t verbosity;f3_t max_dev;bcore_sink* log;haptive_eval_grad_s* grad;}; \
  static inline void haptive_eval_e2e_s_init_x( haptive_eval_e2e_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  s2_t haptive_eval_e2e_s_run( const haptive_eval_e2e_s* o ); \
  static inline s2_t haptive_eval_e2e_s_main( haptive_eval_e2e_s* o, const bcore_arr_st_s* args ){return haptive_eval_e2e_s_run( o );}
#define TYPEOF_haptive_eval_arr_s 1794550753
#define BETH_EXPAND_ITEM_haptive_eval_arr_s \
  BCORE_DECLARE_OBJECT( haptive_eval_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( haptive_eval, );}; \
  static inline void haptive_eval_arr_s_set_space( haptive_eval_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_haptive_eval_arr_s, ( bcore_array* )o, size ); } \
  static inline void haptive_eval_arr_s_set_size( haptive_eval_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_haptive_eval_arr_s, ( bcore_array* )o, size ); } \
  static inline void haptive_eval_arr_s_clear( haptive_eval_arr_s* o ) { bcore_array_t_set_space( TYPEOF_haptive_eval_arr_s, ( bcore_array* )o, 0 ); } \
  static inline haptive_eval* haptive_eval_arr_s_push_c( haptive_eval_arr_s* o, const haptive_eval* v ) { bcore_array_t_push( TYPEOF_haptive_eval_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_eval* haptive_eval_arr_s_push_d( haptive_eval_arr_s* o,       haptive_eval* v ) { bcore_array_t_push( TYPEOF_haptive_eval_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline haptive_eval* haptive_eval_arr_s_push_t( haptive_eval_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_haptive_eval, t ); \
      bcore_array_t_push( TYPEOF_haptive_eval_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_haptive_eval_set_s 1729270278
#define BETH_EXPAND_ITEM_haptive_eval_set_s \
  BCORE_DECLARE_OBJECT( haptive_eval_set_s ) \
    {aware_t _;st_s set_name;st_s sig;bhvm_hf3_adl_s* in;bhvm_hf3_adl_s* out;s2_t verbosity;f3_t max_dev;haptive_eval_arr_s arr;bcore_sink* log;}; \
  static inline void haptive_eval_set_s_init_x( haptive_eval_set_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  s2_t haptive_eval_set_s_run( const haptive_eval_set_s* o ); \
  static inline s2_t haptive_eval_set_s_main( haptive_eval_set_s* o, const bcore_arr_st_s* args ){return haptive_eval_set_s_run( o );}
#define BETH_EXPAND_GROUP_haptive_eval \
  BCORE_FORWARD_OBJECT( haptive_eval ); \
  BCORE_FORWARD_OBJECT( haptive_eval_grad_s ); \
  BCORE_FORWARD_OBJECT( haptive_eval_e2e_s ); \
  BCORE_FORWARD_OBJECT( haptive_eval_arr_s ); \
  BCORE_FORWARD_OBJECT( haptive_eval_set_s ); \
  typedef s2_t (*haptive_eval_run)( const haptive_eval* o ); \
  BCORE_DECLARE_SPECT( haptive_eval ) \
  { \
      bcore_spect_header_s header; \
      haptive_eval_run run; \
  }; \
  static inline haptive_eval* haptive_eval_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_haptive_eval, t ); return ( haptive_eval* )bcore_inst_t_create( t ); } \
  static inline bl_t haptive_eval_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_haptive_eval ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( haptive_eval ) \
  static inline bl_t haptive_eval_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_haptive_eval ); } \
  static inline s2_t haptive_eval_a_run( const haptive_eval* o ) { const haptive_eval_s* p = haptive_eval_s_get_aware( o ); assert( p->run ); return p->run( o ); } \
  static inline bl_t haptive_eval_a_defines_run( const haptive_eval* o ) { return haptive_eval_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_haptive_eval_grad_s \
  BETH_EXPAND_ITEM_haptive_eval_e2e_s \
  BETH_EXPAND_ITEM_haptive_eval_arr_s \
  BETH_EXPAND_ITEM_haptive_eval_set_s

/**********************************************************************************************************************/

vd_t haptive_planted_signal_handler( const bcore_signal_s* o );

#endif // HAPTIVE_PLANTED_H
