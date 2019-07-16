/** This file was generated by the plant-compiler. Not suitable for manual editing.
 *
 *  Copyright and License:
 *    If a specification exists for the repository or folder in which the file is located,
 *    that specification shall apply. Otherwise, the Copyright and License of the associated
 *    source code files containing beth plant-code shall apply.
 */

#ifndef BADAPT_DEV_PLANTED_H
#define BADAPT_DEV_PLANTED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: badapt_dev_problem

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_problem_objects

#define TYPEOF_badapt_dev_problem_objects 483428364
#define TYPEOF_badapt_dev_problem_objects_s 3324364078
#define TYPEOF_badapt_problem_recurrent_abc_s 3613882751
#define BETH_EXPAND_ITEM_badapt_problem_recurrent_abc_s \
  BCORE_DECLARE_OBJECT( badapt_problem_recurrent_abc_s ) \
    {aware_t _;sz_t index;u2_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
  static inline const badapt_loss* badapt_problem_recurrent_abc_s_preferred_loss( const badapt_problem_recurrent_abc_s* o ){ return o->preferred_loss; } \
  sz_t badapt_problem_recurrent_abc_s_get_in_size( const badapt_problem_recurrent_abc_s* o ); \
  sz_t badapt_problem_recurrent_abc_s_get_out_size( const badapt_problem_recurrent_abc_s* o ); \
  void badapt_problem_recurrent_abc_s_fetch_sample_tio( badapt_problem_recurrent_abc_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
  void badapt_problem_recurrent_abc_s_fetch_sample_vio( badapt_problem_recurrent_abc_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
#define TYPEOF_badapt_problem_recurrent_kjv_s 1636314442
#define BETH_EXPAND_ITEM_badapt_problem_recurrent_kjv_s \
  BCORE_DECLARE_OBJECT( badapt_problem_recurrent_kjv_s ) \
    {aware_t _;bcore_source* source;bcore_arr_sz_s* charmap;st_s* charset;u0_t t_last_char;u0_t v_last_char;u2_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
  static inline const badapt_loss* badapt_problem_recurrent_kjv_s_preferred_loss( const badapt_problem_recurrent_kjv_s* o ){ return o->preferred_loss; } \
  sz_t badapt_problem_recurrent_kjv_s_get_in_size( const badapt_problem_recurrent_kjv_s* o ); \
  sz_t badapt_problem_recurrent_kjv_s_get_out_size( const badapt_problem_recurrent_kjv_s* o ); \
  void badapt_problem_recurrent_kjv_s_fetch_sample_tio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
  void badapt_problem_recurrent_kjv_s_fetch_sample_vio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
#define TYPEOF_badapt_problem_recurrent_text_s 1449347910
#define BETH_EXPAND_ITEM_badapt_problem_recurrent_text_s \
  BCORE_DECLARE_OBJECT( badapt_problem_recurrent_text_s ) \
    {aware_t _;st_s text_file;st_s ignore_line_char;bcore_source* source;bcore_arr_sz_s* charmap;st_s* charset;u0_t t_last_char;u0_t v_last_char;u2_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
  static inline const badapt_loss* badapt_problem_recurrent_text_s_preferred_loss( const badapt_problem_recurrent_text_s* o ){ return o->preferred_loss; } \
  sz_t badapt_problem_recurrent_text_s_get_in_size( const badapt_problem_recurrent_text_s* o ); \
  sz_t badapt_problem_recurrent_text_s_get_out_size( const badapt_problem_recurrent_text_s* o ); \
  void badapt_problem_recurrent_text_s_fetch_sample_tio( badapt_problem_recurrent_text_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
  void badapt_problem_recurrent_text_s_fetch_sample_vio( badapt_problem_recurrent_text_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
#define TYPEOF_badapt_guide_char_encode_s 2263969302
#define BETH_EXPAND_ITEM_badapt_guide_char_encode_s \
  BCORE_DECLARE_OBJECT( badapt_guide_char_encode_s ) \
    {aware_t _;badapt_guide* guide_default;bcore_arr_sz_s* charmap;st_s* charset;f3_t pos_tgt;f3_t neg_tgt;st_s txt_trigger;sz_t txt_size;f3_t heat;}; \
  bl_t badapt_guide_char_encode_s_callback( const badapt_guide_char_encode_s* o, badapt_training_state* state );
#define BETH_EXPAND_GROUP_badapt_dev_problem_objects \
  BCORE_FORWARD_OBJECT( badapt_dev_problem_objects ); \
  BCORE_FORWARD_OBJECT( badapt_problem_recurrent_abc_s ); \
  BCORE_FORWARD_OBJECT( badapt_problem_recurrent_kjv_s ); \
  BCORE_FORWARD_OBJECT( badapt_problem_recurrent_text_s ); \
  BCORE_FORWARD_OBJECT( badapt_guide_char_encode_s ); \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_abc_s \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_kjv_s \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_text_s \
  BETH_EXPAND_ITEM_badapt_guide_char_encode_s

/**********************************************************************************************************************/
// source: badapt_dev_ern

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_ern

#define TYPEOF_badapt_dev_ern 3818246179
#define TYPEOF_badapt_dev_ern_s 3653613765
#define BETH_EXPAND_GROUP_badapt_dev_ern \
  BCORE_FORWARD_OBJECT( badapt_dev_ern );

/**********************************************************************************************************************/
// source: badapt_dev_lstm

/**********************************************************************************************************************/
// source: bsym

//----------------------------------------------------------------------------------------------------------------------
// group: bsym

#define TYPEOF_bsym 3737279812
#define TYPEOF_bsym_s 726515702
#define TYPEOF_bsym_source_info_s 1283233195
#define BETH_EXPAND_ITEM_bsym_source_info_s \
  BCORE_DECLARE_OBJECT( bsym_source_info_s ) \
    {aware_t _;bcore_source* source;sz_t index;};
#define BETH_EXPAND_GROUP_bsym \
  BCORE_FORWARD_OBJECT( bsym ); \
  BCORE_FORWARD_OBJECT( bsym_source_info_s ); \
  BCORE_FORWARD_OBJECT( bsym_op ); \
  BCORE_FORWARD_OBJECT( bsym_net ); \
  BCORE_FORWARD_OBJECT( bsym_sem ); \
  BETH_EXPAND_ITEM_bsym_source_info_s \
  BETH_EXPAND_GROUP_bsym_op \
  BETH_EXPAND_GROUP_bsym_net \
  BETH_EXPAND_GROUP_bsym_sem

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op

#define TYPEOF_bsym_op 3109786158
#define TYPEOF_bsym_op_s 1111123888
#define BETH_EXPAND_GROUP_bsym_op \
  BCORE_FORWARD_OBJECT( bsym_op ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar0 ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar1 ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar2 ); \
  typedef void (*bsym_op_trace_to_sink)( const bsym_op* o, sz_t indent, bcore_sink* sink ); \
  BCORE_DECLARE_SPECT( bsym_op ) \
  { \
      bcore_spect_header_s header; \
      bsym_op_trace_to_sink trace_to_sink; \
  }; \
  static inline bsym_op* bsym_op_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_bsym_op, t ); return ( bsym_op* )bcore_inst_t_create( t ); } \
  static inline bl_t bsym_op_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_bsym_op ); } \
  static inline bsym_op* bsym_op_a_clone( const bsym_op* o ) { return ( bsym_op* )bcore_inst_a_clone( ( bcore_inst* )o ); } \
  static inline void bsym_op_a_discard( bsym_op* o ) { bcore_inst_a_discard( ( bcore_inst* )o ); } \
  static inline void bsym_op_a_detach( bsym_op** o ) { if( !o ) return; bcore_inst_a_discard( ( bcore_inst* )*o ); *o = NULL; } \
  static inline void bsym_op_a_attach( bsym_op** o, bsym_op* src ) { if( src ) bcore_inst_a_attach( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline void bsym_op_a_replicate( bsym_op** o, const bsym_op* src ) { bcore_inst_a_replicate( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline bl_t bsym_op_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_bsym_op ); } \
  static inline void bsym_op_a_trace_to_sink( const bsym_op* o, sz_t indent, bcore_sink* sink ) { bsym_op_s_get_aware( o )->trace_to_sink( o, indent, sink ); } \
  static inline bl_t bsym_op_a_defines_trace_to_sink( const bsym_op* o ) { return true; } \
  static inline void bsym_op_trace_to_sink__( const bsym_op* o, sz_t indent, bcore_sink* sink ) {} \
  BETH_EXPAND_GROUP_bsym_op_ar0 \
  BETH_EXPAND_GROUP_bsym_op_ar1 \
  BETH_EXPAND_GROUP_bsym_op_ar2

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op_ar0

#define TYPEOF_bsym_op_ar0 580013156
#define TYPEOF_bsym_op_ar0_s 4056606166
#define TYPEOF_adaptive 857148571
#define TYPEOF_buffer 2170494075
#define TYPEOF_const 1716507092
#define TYPEOF_bsym_op_ar0_holor_s 1027345839
#define BETH_EXPAND_ITEM_bsym_op_ar0_holor_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar0_holor_s ) \
    {aware_t _;tp_t type;bmath_hf3_s hf3;}; \
  void bsym_op_ar0_holor_s_trace_to_sink( const bsym_op_ar0_holor_s* o, sz_t indent, bcore_sink* sink ); \
  bl_t bsym_op_ar0_holor_s_compute_hf3( const bsym_op_ar0_holor_s* o, bmath_hf3_s* r );
#define BETH_EXPAND_GROUP_bsym_op_ar0 \
  BCORE_FORWARD_OBJECT( bsym_op_ar0 ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar0_holor_s ); \
  typedef bl_t (*bsym_op_ar0_compute_hf3)( const bsym_op_ar0* o, bmath_hf3_s* r ); \
  BCORE_DECLARE_SPECT( bsym_op_ar0 ) \
  { \
      bcore_spect_header_s header; \
      bsym_op_ar0_compute_hf3 compute_hf3; \
  }; \
  static inline bsym_op_ar0* bsym_op_ar0_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_bsym_op_ar0, t ); return ( bsym_op_ar0* )bcore_inst_t_create( t ); } \
  static inline bl_t bsym_op_ar0_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_bsym_op_ar0 ); } \
  static inline bsym_op_ar0* bsym_op_ar0_a_clone( const bsym_op_ar0* o ) { return ( bsym_op_ar0* )bcore_inst_a_clone( ( bcore_inst* )o ); } \
  static inline void bsym_op_ar0_a_discard( bsym_op_ar0* o ) { bcore_inst_a_discard( ( bcore_inst* )o ); } \
  static inline void bsym_op_ar0_a_detach( bsym_op_ar0** o ) { if( !o ) return; bcore_inst_a_discard( ( bcore_inst* )*o ); *o = NULL; } \
  static inline void bsym_op_ar0_a_attach( bsym_op_ar0** o, bsym_op_ar0* src ) { if( src ) bcore_inst_a_attach( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline void bsym_op_ar0_a_replicate( bsym_op_ar0** o, const bsym_op_ar0* src ) { bcore_inst_a_replicate( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline bl_t bsym_op_ar0_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_bsym_op_ar0 ); } \
  static inline bl_t bsym_op_ar0_a_compute_hf3( const bsym_op_ar0* o, bmath_hf3_s* r ) { return bsym_op_ar0_s_get_aware( o )->compute_hf3( o, r ); } \
  static inline bl_t bsym_op_ar0_a_defines_compute_hf3( const bsym_op_ar0* o ) { return true; } \
  BETH_EXPAND_ITEM_bsym_op_ar0_holor_s

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op_ar1

#define TYPEOF_bsym_op_ar1 596790775
#define TYPEOF_bsym_op_ar1_s 1850949201
#define TYPEOF_bsym_op_ar1_linear_s 2596841019
#define BETH_EXPAND_ITEM_bsym_op_ar1_linear_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar1_linear_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar1_linear_s_get_symbol( const bsym_op_ar1_linear_s* o ){ return "linear"; } \
  static inline bl_t bsym_op_ar1_linear_s_compute_hf3( const bsym_op_ar1_linear_s* o, const bmath_hf3_s* a, bmath_hf3_s* r ){ bmath_hf3_s_copy( r, a ); return true; }
#define TYPEOF_bsym_op_ar1_tanh_s 444204091
#define BETH_EXPAND_ITEM_bsym_op_ar1_tanh_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar1_tanh_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar1_tanh_s_get_symbol( const bsym_op_ar1_tanh_s* o ){ return "tanh"  ; } \
  bl_t bsym_op_ar1_tanh_s_compute_hf3( const bsym_op_ar1_tanh_s* o, const bmath_hf3_s* a, bmath_hf3_s* r );
#define TYPEOF_bsym_op_ar1_dimof_s 1118792073
#define BETH_EXPAND_ITEM_bsym_op_ar1_dimof_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar1_dimof_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar1_dimof_s_get_symbol( const bsym_op_ar1_dimof_s* o ){ return "dimof" ; } \
  bl_t bsym_op_ar1_dimof_s_compute_hf3( const bsym_op_ar1_dimof_s* o, const bmath_hf3_s* a, bmath_hf3_s* r );
#define BETH_EXPAND_GROUP_bsym_op_ar1 \
  BCORE_FORWARD_OBJECT( bsym_op_ar1 ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar1_linear_s ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar1_tanh_s ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar1_dimof_s ); \
  typedef sc_t (*bsym_op_ar1_get_symbol)( const bsym_op_ar1* o ); \
  typedef bl_t (*bsym_op_ar1_compute_hf3)( const bsym_op_ar1* o, const bmath_hf3_s* a, bmath_hf3_s* r ); \
  BCORE_DECLARE_SPECT( bsym_op_ar1 ) \
  { \
      bcore_spect_header_s header; \
      bsym_op_ar1_get_symbol get_symbol; \
      bsym_op_ar1_compute_hf3 compute_hf3; \
  }; \
  static inline bsym_op_ar1* bsym_op_ar1_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_bsym_op_ar1, t ); return ( bsym_op_ar1* )bcore_inst_t_create( t ); } \
  static inline bl_t bsym_op_ar1_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_bsym_op_ar1 ); } \
  static inline bsym_op_ar1* bsym_op_ar1_a_clone( const bsym_op_ar1* o ) { return ( bsym_op_ar1* )bcore_inst_a_clone( ( bcore_inst* )o ); } \
  static inline void bsym_op_ar1_a_discard( bsym_op_ar1* o ) { bcore_inst_a_discard( ( bcore_inst* )o ); } \
  static inline void bsym_op_ar1_a_detach( bsym_op_ar1** o ) { if( !o ) return; bcore_inst_a_discard( ( bcore_inst* )*o ); *o = NULL; } \
  static inline void bsym_op_ar1_a_attach( bsym_op_ar1** o, bsym_op_ar1* src ) { if( src ) bcore_inst_a_attach( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline void bsym_op_ar1_a_replicate( bsym_op_ar1** o, const bsym_op_ar1* src ) { bcore_inst_a_replicate( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline bl_t bsym_op_ar1_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_bsym_op_ar1 ); } \
  static inline sc_t bsym_op_ar1_a_get_symbol( const bsym_op_ar1* o ) { return bsym_op_ar1_s_get_aware( o )->get_symbol( o ); } \
  static inline bl_t bsym_op_ar1_a_defines_get_symbol( const bsym_op_ar1* o ) { return true; } \
  static inline bl_t bsym_op_ar1_a_compute_hf3( const bsym_op_ar1* o, const bmath_hf3_s* a, bmath_hf3_s* r ) { return bsym_op_ar1_s_get_aware( o )->compute_hf3( o, a, r ); } \
  static inline bl_t bsym_op_ar1_a_defines_compute_hf3( const bsym_op_ar1* o ) { return bsym_op_ar1_s_get_aware( o )->compute_hf3 != NULL; } \
  BETH_EXPAND_ITEM_bsym_op_ar1_linear_s \
  BETH_EXPAND_ITEM_bsym_op_ar1_tanh_s \
  BETH_EXPAND_ITEM_bsym_op_ar1_dimof_s

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op_ar2

#define TYPEOF_bsym_op_ar2 613568394
#define TYPEOF_bsym_op_ar2_s 3837272692
#define TYPEOF_bsym_op_ar2_mul_s 3581603561
#define BETH_EXPAND_ITEM_bsym_op_ar2_mul_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar2_mul_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar2_mul_s_get_symbol( const bsym_op_ar2_mul_s* o ){ return "*"; } \
  bl_t bsym_op_ar2_mul_s_compute_hf3( const bsym_op_ar2_mul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r );
#define TYPEOF_bsym_op_ar2_hmul_s 3965658635
#define BETH_EXPAND_ITEM_bsym_op_ar2_hmul_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar2_hmul_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar2_hmul_s_get_symbol( const bsym_op_ar2_hmul_s* o ){ return "<*>"; } \
  bl_t bsym_op_ar2_hmul_s_compute_hf3( const bsym_op_ar2_hmul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r );
#define TYPEOF_bsym_op_ar2_plus_s 1005616789
#define BETH_EXPAND_ITEM_bsym_op_ar2_plus_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar2_plus_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar2_plus_s_get_symbol( const bsym_op_ar2_plus_s* o ){ return "+"; } \
  bl_t bsym_op_ar2_plus_s_compute_hf3( const bsym_op_ar2_plus_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r );
#define TYPEOF_bsym_op_ar2_minus_s 2024488711
#define BETH_EXPAND_ITEM_bsym_op_ar2_minus_s \
  BCORE_DECLARE_OBJECT( bsym_op_ar2_minus_s ) \
    {aware_t _;}; \
  static inline sc_t bsym_op_ar2_minus_s_get_symbol( const bsym_op_ar2_minus_s* o ){ return "-"; } \
  bl_t bsym_op_ar2_minus_s_compute_hf3( const bsym_op_ar2_minus_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r );
#define BETH_EXPAND_GROUP_bsym_op_ar2 \
  BCORE_FORWARD_OBJECT( bsym_op_ar2 ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar2_mul_s ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar2_hmul_s ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar2_plus_s ); \
  BCORE_FORWARD_OBJECT( bsym_op_ar2_minus_s ); \
  typedef sc_t (*bsym_op_ar2_get_symbol)( const bsym_op_ar2* o ); \
  typedef bl_t (*bsym_op_ar2_compute_hf3)( const bsym_op_ar2* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r ); \
  BCORE_DECLARE_SPECT( bsym_op_ar2 ) \
  { \
      bcore_spect_header_s header; \
      bsym_op_ar2_get_symbol get_symbol; \
      bsym_op_ar2_compute_hf3 compute_hf3; \
  }; \
  static inline bsym_op_ar2* bsym_op_ar2_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_bsym_op_ar2, t ); return ( bsym_op_ar2* )bcore_inst_t_create( t ); } \
  static inline bl_t bsym_op_ar2_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_bsym_op_ar2 ); } \
  static inline bsym_op_ar2* bsym_op_ar2_a_clone( const bsym_op_ar2* o ) { return ( bsym_op_ar2* )bcore_inst_a_clone( ( bcore_inst* )o ); } \
  static inline void bsym_op_ar2_a_discard( bsym_op_ar2* o ) { bcore_inst_a_discard( ( bcore_inst* )o ); } \
  static inline void bsym_op_ar2_a_detach( bsym_op_ar2** o ) { if( !o ) return; bcore_inst_a_discard( ( bcore_inst* )*o ); *o = NULL; } \
  static inline void bsym_op_ar2_a_attach( bsym_op_ar2** o, bsym_op_ar2* src ) { if( src ) bcore_inst_a_attach( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline void bsym_op_ar2_a_replicate( bsym_op_ar2** o, const bsym_op_ar2* src ) { bcore_inst_a_replicate( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline bl_t bsym_op_ar2_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_bsym_op_ar2 ); } \
  static inline sc_t bsym_op_ar2_a_get_symbol( const bsym_op_ar2* o ) { return bsym_op_ar2_s_get_aware( o )->get_symbol( o ); } \
  static inline bl_t bsym_op_ar2_a_defines_get_symbol( const bsym_op_ar2* o ) { return true; } \
  static inline bl_t bsym_op_ar2_a_compute_hf3( const bsym_op_ar2* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r ) { return bsym_op_ar2_s_get_aware( o )->compute_hf3( o, a, b, r ); } \
  static inline bl_t bsym_op_ar2_a_defines_compute_hf3( const bsym_op_ar2* o ) { return bsym_op_ar2_s_get_aware( o )->compute_hf3 != NULL; } \
  BETH_EXPAND_ITEM_bsym_op_ar2_mul_s \
  BETH_EXPAND_ITEM_bsym_op_ar2_hmul_s \
  BETH_EXPAND_ITEM_bsym_op_ar2_plus_s \
  BETH_EXPAND_ITEM_bsym_op_ar2_minus_s

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_net

#define TYPEOF_bsym_net 2379906484
#define TYPEOF_bsym_net_s 3178558630
#define TYPEOF_bsym_net_body_s 962574443
#define BETH_EXPAND_ITEM_bsym_net_body_s \
  BCORE_DECLARE_OBJECT( bsym_net_body_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( bsym_net, );}; \
  void bsym_net_body_s_copy_x( bsym_net_body_s* o ); \
  static inline void bsym_net_body_s_set_space( bsym_net_body_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_bsym_net_body_s, ( bcore_array* )o, size ); } \
  static inline void bsym_net_body_s_set_size( bsym_net_body_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_bsym_net_body_s, ( bcore_array* )o, size ); } \
  static inline void bsym_net_body_s_clear( bsym_net_body_s* o ) { bcore_array_t_set_space( TYPEOF_bsym_net_body_s, ( bcore_array* )o, 0 ); } \
  static inline void bsym_net_body_s_push_c( bsym_net_body_s* o, const bsym_net* v ) { bcore_array_t_push( TYPEOF_bsym_net_body_s, ( bcore_array* )o, sr_awc( v ) ); } \
  static inline void bsym_net_body_s_push_d( bsym_net_body_s* o,       bsym_net* v ) { bcore_array_t_push( TYPEOF_bsym_net_body_s, ( bcore_array* )o, sr_asd( v ) ); } \
  static inline bsym_net* bsym_net_body_s_push_t( bsym_net_body_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_bsym_net, t ); \
      bcore_array_t_push( TYPEOF_bsym_net_body_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return bcore_array_t_get_last( TYPEOF_bsym_net_body_s, ( bcore_array* )o ).o; \
  }
#define TYPEOF_bsym_net_address_s 190991353
#define BETH_EXPAND_ITEM_bsym_net_address_s \
  BCORE_DECLARE_OBJECT( bsym_net_address_s ) \
    {aware_t _;sz_t index;vd_t body;}; \
  void bsym_net_address_s_trace_to_sink( const bsym_net_address_s* o, sz_t indent, bcore_sink* sink ); \
  bmath_hf3_s* bsym_net_address_s_trace_compute_hf3( bsym_net_address_s* o ); \
  void bsym_net_address_s_trace_reset_hf3( bsym_net_address_s* o ); \
  sz_t bsym_net_address_s_trace_set_hf3_index( bsym_net_address_s* o, sz_t start_index );
#define TYPEOF_bsym_net_link_s 622852007
#define BETH_EXPAND_ITEM_bsym_net_link_s \
  BCORE_DECLARE_OBJECT( bsym_net_link_s ) \
    {aware_t _;tp_t name;bsym_net_address_s target;bsym_net_address_s root;bl_t flag;}; \
  static inline tp_t bsym_net_link_s_get_name( const bsym_net_link_s* o ){ return o->name; } \
  void bsym_net_link_s_set_body( bsym_net_link_s* o, bsym_net_body_s* body ); \
  void bsym_net_link_s_trace_to_sink( const bsym_net_link_s* o, sz_t indent, bcore_sink* sink ); \
  static inline bmath_hf3_s* bsym_net_link_s_trace_compute_hf3( bsym_net_link_s* o ){ return bsym_net_address_s_trace_compute_hf3(   &o->target ); } \
  static inline void bsym_net_link_s_trace_reset_hf3( bsym_net_link_s* o ){        bsym_net_address_s_trace_reset_hf3(     &o->target ); } \
  static inline sz_t bsym_net_link_s_trace_set_hf3_index( bsym_net_link_s* o, sz_t start_index ){ return bsym_net_address_s_trace_set_hf3_index( &o->target, start_index ); }
#define TYPEOF_bsym_net_node_s 1739206867
#define BETH_EXPAND_ITEM_bsym_net_node_s \
  BCORE_DECLARE_OBJECT( bsym_net_node_s ) \
    {aware_t _;tp_t name;BCORE_ARRAY_DYN_SOLID_STATIC_S( bsym_net_address_s, targets_ );bsym_net_address_s root;bsym_op* op;bsym_source_info_s source_info;bmath_hf3_s* hf3;sz_t hf3_index;bsym_net_address_s* new_root;}; \
  static inline tp_t bsym_net_node_s_get_name( const bsym_net_node_s* o ){ return o->name; } \
  void bsym_net_node_s_set_body( bsym_net_node_s* o, bsym_net_body_s* body ); \
  void bsym_net_node_s_trace_to_sink( const bsym_net_node_s* o, sz_t indent, bcore_sink* sink ); \
  bmath_hf3_s* bsym_net_node_s_trace_compute_hf3( bsym_net_node_s* o ); \
  void bsym_net_node_s_trace_reset_hf3( bsym_net_node_s* o ); \
  sz_t bsym_net_node_s_trace_set_hf3_index( bsym_net_node_s* o, sz_t start_index ); \
  static inline void bsym_net_node_s_set_space( bsym_net_node_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_bsym_net_node_s, ( bcore_array* )o, size ); } \
  static inline void bsym_net_node_s_set_size( bsym_net_node_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_bsym_net_node_s, ( bcore_array* )o, size ); } \
  static inline void bsym_net_node_s_clear( bsym_net_node_s* o ) { bcore_array_t_set_space( TYPEOF_bsym_net_node_s, ( bcore_array* )o, 0 ); } \
  static inline void bsym_net_node_s_push_c( bsym_net_node_s* o, const bsym_net_address_s* v ) { bcore_array_t_push( TYPEOF_bsym_net_node_s, ( bcore_array* )o, sr_twc( TYPEOF_bsym_net_address_s, v ) ); } \
  static inline void bsym_net_node_s_push_d( bsym_net_node_s* o,       bsym_net_address_s* v ) { bcore_array_t_push( TYPEOF_bsym_net_node_s, ( bcore_array* )o, sr_tsd( TYPEOF_bsym_net_address_s, v ) ); } \
  static inline bsym_net_address_s* bsym_net_node_s_push( bsym_net_node_s* o ) \
  { \
      bcore_array_t_push( TYPEOF_bsym_net_node_s, ( bcore_array* )o, sr_null() ); \
      return bcore_array_t_get_last( TYPEOF_bsym_net_node_s, ( bcore_array* )o ).o; \
  }
#define BETH_EXPAND_GROUP_bsym_net \
  BCORE_FORWARD_OBJECT( bsym_net ); \
  BCORE_FORWARD_OBJECT( bsym_net_body_s ); \
  BCORE_FORWARD_OBJECT( bsym_net_address_s ); \
  BCORE_FORWARD_OBJECT( bsym_net_link_s ); \
  BCORE_FORWARD_OBJECT( bsym_net_node_s ); \
  typedef void (*bsym_net_trace_to_sink)( const bsym_net* o, sz_t indent, bcore_sink* sink ); \
  typedef tp_t (*bsym_net_get_name)( const bsym_net* o ); \
  typedef void (*bsym_net_set_body)( bsym_net* o, bsym_net_body_s* body ); \
  typedef bmath_hf3_s* (*bsym_net_trace_compute_hf3)( bsym_net* o ); \
  typedef void (*bsym_net_trace_reset_hf3)( bsym_net* o ); \
  typedef sz_t (*bsym_net_trace_set_hf3_index)( bsym_net* o, sz_t start_index ); \
  BCORE_DECLARE_SPECT( bsym_net ) \
  { \
      bcore_spect_header_s header; \
      bsym_net_trace_to_sink trace_to_sink; \
      bsym_net_get_name get_name; \
      bsym_net_set_body set_body; \
      bsym_net_trace_compute_hf3 trace_compute_hf3; \
      bsym_net_trace_reset_hf3 trace_reset_hf3; \
      bsym_net_trace_set_hf3_index trace_set_hf3_index; \
  }; \
  static inline bsym_net* bsym_net_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_bsym_net, t ); return ( bsym_net* )bcore_inst_t_create( t ); } \
  static inline bl_t bsym_net_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_bsym_net ); } \
  static inline bsym_net* bsym_net_a_clone( const bsym_net* o ) { return ( bsym_net* )bcore_inst_a_clone( ( bcore_inst* )o ); } \
  static inline void bsym_net_a_discard( bsym_net* o ) { bcore_inst_a_discard( ( bcore_inst* )o ); } \
  static inline void bsym_net_a_detach( bsym_net** o ) { if( !o ) return; bcore_inst_a_discard( ( bcore_inst* )*o ); *o = NULL; } \
  static inline void bsym_net_a_attach( bsym_net** o, bsym_net* src ) { if( src ) bcore_inst_a_attach( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline void bsym_net_a_replicate( bsym_net** o, const bsym_net* src ) { bcore_inst_a_replicate( ( bcore_inst** )o, ( bcore_inst* )src ); } \
  static inline bl_t bsym_net_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_bsym_net ); } \
  static inline void bsym_net_a_trace_to_sink( const bsym_net* o, sz_t indent, bcore_sink* sink ) { bsym_net_s_get_aware( o )->trace_to_sink( o, indent, sink ); } \
  static inline bl_t bsym_net_a_defines_trace_to_sink( const bsym_net* o ) { return true; } \
  static inline void bsym_net_trace_to_sink__( const bsym_net* o, sz_t indent, bcore_sink* sink ) {} \
  static inline tp_t bsym_net_a_get_name( const bsym_net* o ) { return bsym_net_s_get_aware( o )->get_name( o ); } \
  static inline bl_t bsym_net_a_defines_get_name( const bsym_net* o ) { return true; } \
  static inline tp_t bsym_net_get_name__( const bsym_net* o ) { return 0; } \
  static inline void bsym_net_a_set_body( bsym_net* o, bsym_net_body_s* body ) { bsym_net_s_get_aware( o )->set_body( o, body ); } \
  static inline bl_t bsym_net_a_defines_set_body( const bsym_net* o ) { return true; } \
  static inline void bsym_net_set_body__( bsym_net* o, bsym_net_body_s* body ) {} \
  static inline bmath_hf3_s* bsym_net_a_trace_compute_hf3( bsym_net* o ) { return bsym_net_s_get_aware( o )->trace_compute_hf3( o ); } \
  static inline bl_t bsym_net_a_defines_trace_compute_hf3( const bsym_net* o ) { return true; } \
  static inline bmath_hf3_s* bsym_net_trace_compute_hf3__( bsym_net* o ) { return NULL; } \
  static inline void bsym_net_a_trace_reset_hf3( bsym_net* o ) { bsym_net_s_get_aware( o )->trace_reset_hf3( o ); } \
  static inline bl_t bsym_net_a_defines_trace_reset_hf3( const bsym_net* o ) { return true; } \
  static inline void bsym_net_trace_reset_hf3__( bsym_net* o ) {} \
  static inline sz_t bsym_net_a_trace_set_hf3_index( bsym_net* o, sz_t start_index ) { return bsym_net_s_get_aware( o )->trace_set_hf3_index( o, start_index ); } \
  static inline bl_t bsym_net_a_defines_trace_set_hf3_index( const bsym_net* o ) { return true; } \
  static inline sz_t bsym_net_trace_set_hf3_index__( bsym_net* o, sz_t start_index ) { return -1; } \
  BETH_EXPAND_ITEM_bsym_net_body_s \
  BETH_EXPAND_ITEM_bsym_net_address_s \
  BETH_EXPAND_ITEM_bsym_net_link_s \
  BETH_EXPAND_ITEM_bsym_net_node_s

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_sem

#define TYPEOF_bsym_sem 3159687756
#define TYPEOF_bsym_sem_s 1224764270
#define TYPEOF_bsym_sem_graph_s 701643229
#define BETH_EXPAND_ITEM_bsym_sem_graph_s \
  BCORE_DECLARE_OBJECT( bsym_sem_graph_s ) \
    {aware_t _;tp_t name;sz_t args_in;sz_t args_out;bsym_net_body_s body;bsym_sem_graph_base_s* graph_base;bcore_arr_st_s* arr_symbol_op2;bsym_source_info_s source_info;};
#define TYPEOF_bsym_sem_graph_base_s 3559002339
#define BETH_EXPAND_ITEM_bsym_sem_graph_base_s \
  BCORE_DECLARE_OBJECT( bsym_sem_graph_base_s ) \
    {aware_t _;bsym_sem_graph_base_s* parent;BCORE_ARRAY_DYN_LINK_STATIC_S( bsym_sem, );}; \
  static inline void bsym_sem_graph_base_s_set_space( bsym_sem_graph_base_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o, size ); } \
  static inline void bsym_sem_graph_base_s_set_size( bsym_sem_graph_base_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o, size ); } \
  static inline void bsym_sem_graph_base_s_clear( bsym_sem_graph_base_s* o ) { bcore_array_t_set_space( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o, 0 ); } \
  static inline void bsym_sem_graph_base_s_push_c( bsym_sem_graph_base_s* o, const bsym_sem* v ) { bcore_array_t_push( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o, sr_awc( v ) ); } \
  static inline void bsym_sem_graph_base_s_push_d( bsym_sem_graph_base_s* o,       bsym_sem* v ) { bcore_array_t_push( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o, sr_asd( v ) ); } \
  static inline bsym_sem* bsym_sem_graph_base_s_push_t( bsym_sem_graph_base_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_bsym_sem, t ); \
      bcore_array_t_push( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return bcore_array_t_get_last( TYPEOF_bsym_sem_graph_base_s, ( bcore_array* )o ).o; \
  }
#define TYPEOF_bsym_sem_stack_flag_s 1899517360
#define BETH_EXPAND_ITEM_bsym_sem_stack_flag_s \
  BCORE_DECLARE_OBJECT( bsym_sem_stack_flag_s ) \
    {aware_t _;};
#define BETH_EXPAND_GROUP_bsym_sem \
  BCORE_FORWARD_OBJECT( bsym_sem ); \
  BCORE_FORWARD_OBJECT( bsym_sem_graph_s ); \
  BCORE_FORWARD_OBJECT( bsym_sem_graph_base_s ); \
  BCORE_FORWARD_OBJECT( bsym_sem_stack_flag_s ); \
  BETH_EXPAND_ITEM_bsym_sem_graph_s \
  BETH_EXPAND_ITEM_bsym_sem_graph_base_s \
  BETH_EXPAND_ITEM_bsym_sem_stack_flag_s

/**********************************************************************************************************************/

vd_t badapt_dev_planted_signal_handler( const bcore_signal_s* o );

#endif // BADAPT_DEV_PLANTED_H
