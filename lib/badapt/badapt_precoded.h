/** This file was generated by the beth-precode-compiler. Not suitable for manual editing.
 *
 *  Copyright and License:
 *    If a specification exists for the repository or folder in which the file is located,
 *    that specification shall apply. Otherwise, the Copyright and License of the associated
 *    source code files containing beth-precode shall apply.
 */

#ifndef BADAPT_PRECODED_H
#define BADAPT_PRECODED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: badapt_features

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_adaptive

#define TYPEOF_badapt_adaptive 3626296374
#define TYPEOF_badapt_adaptive_s 2278398760
#define TYPEOF_badapt_regularization_l1 4238179826
#define TYPEOF_badapt_regularization_l2 4221402207
#define BETH_EXPAND_GROUP_badapt_adaptive \
  BCORE_FORWARD_OBJECT( badapt_adaptive ); \
  typedef void (*badapt_adaptive_reset)( badapt_adaptive* o ); \
  typedef void (*badapt_adaptive_setup)( badapt_adaptive* o ); \
  typedef sz_t (*badapt_adaptive_get_in_size)( const badapt_adaptive* o ); \
  typedef void (*badapt_adaptive_set_in_size)( badapt_adaptive* o, sz_t size ); \
  typedef sz_t (*badapt_adaptive_get_out_size)( const badapt_adaptive* o ); \
  typedef void (*badapt_adaptive_set_out_size)( badapt_adaptive* o, sz_t size ); \
  typedef void (*badapt_adaptive_infer)( const badapt_adaptive* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
  typedef void (*badapt_adaptive_minfer)( badapt_adaptive* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
  typedef void (*badapt_adaptive_bgrad)( const badapt_adaptive* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ); \
  typedef void (*badapt_adaptive_bgrad_adapt)( badapt_adaptive* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ); \
  typedef f3_t (*badapt_adaptive_get_step)( const badapt_adaptive* o ); \
  typedef void (*badapt_adaptive_set_step)( badapt_adaptive* o, f3_t val ); \
  typedef f3_t (*badapt_adaptive_get_regularization)( const badapt_adaptive* o, tp_t type ); \
  typedef void (*badapt_adaptive_set_regularization)( badapt_adaptive* o, tp_t type, f3_t val ); \
  typedef void (*badapt_adaptive_arc_to_sink)( const badapt_adaptive* o, bcore_sink* sink ); \
  typedef f3_t (*badapt_adaptive_infer_f3)( const badapt_adaptive* o, const bmath_vf3_s* in ); \
  typedef void (*badapt_adaptive_adapt_l2)( badapt_adaptive* o, const bmath_vf3_s* in, const bmath_vf3_s* target, bmath_vf3_s* out ); \
  typedef f3_t (*badapt_adaptive_adapt_l2_f3)( badapt_adaptive* o, const bmath_vf3_s* in, f3_t target ); \
  BCORE_DECLARE_SPECT( badapt_adaptive ) \
  { \
      bcore_spect_header_s header; \
      badapt_adaptive_reset reset; \
      badapt_adaptive_setup setup; \
      badapt_adaptive_get_in_size get_in_size; \
      badapt_adaptive_set_in_size set_in_size; \
      badapt_adaptive_get_out_size get_out_size; \
      badapt_adaptive_set_out_size set_out_size; \
      badapt_adaptive_infer infer; \
      badapt_adaptive_minfer minfer; \
      badapt_adaptive_bgrad bgrad; \
      badapt_adaptive_bgrad_adapt bgrad_adapt; \
      badapt_adaptive_get_step get_step; \
      badapt_adaptive_set_step set_step; \
      badapt_adaptive_get_regularization get_regularization; \
      badapt_adaptive_set_regularization set_regularization; \
      badapt_adaptive_arc_to_sink arc_to_sink; \
      badapt_adaptive_infer_f3 infer_f3; \
      badapt_adaptive_adapt_l2 adapt_l2; \
      badapt_adaptive_adapt_l2_f3 adapt_l2_f3; \
  }; \
  static inline void badapt_adaptive_p_reset( const badapt_adaptive_s* __p, badapt_adaptive* o ) { __p->reset( o ); } \
  static inline void badapt_adaptive_a_reset( badapt_adaptive* o ) { badapt_adaptive_s_get_aware( o )->reset( o ); } \
  static inline void badapt_adaptive_r_reset( const sr_s* o ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->reset( o->o ); } \
  static inline bl_t badapt_adaptive_p_defines_reset( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_reset( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_reset( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_setup( const badapt_adaptive_s* __p, badapt_adaptive* o ) { __p->setup( o ); } \
  static inline void badapt_adaptive_a_setup( badapt_adaptive* o ) { badapt_adaptive_s_get_aware( o )->setup( o ); } \
  static inline void badapt_adaptive_r_setup( const sr_s* o ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->setup( o->o ); } \
  static inline bl_t badapt_adaptive_p_defines_setup( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_setup( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_setup( const sr_s* o ) { return true; } \
  static inline sz_t badapt_adaptive_p_get_in_size( const badapt_adaptive_s* __p, const badapt_adaptive* o ) { return __p->get_in_size( o ); } \
  static inline sz_t badapt_adaptive_a_get_in_size( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->get_in_size( o ); } \
  static inline sz_t badapt_adaptive_r_get_in_size( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->get_in_size( o->o ); } \
  static inline bl_t badapt_adaptive_p_defines_get_in_size( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_get_in_size( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_get_in_size( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_set_in_size( const badapt_adaptive_s* __p, badapt_adaptive* o, sz_t size ) { __p->set_in_size( o, size ); } \
  static inline void badapt_adaptive_a_set_in_size( badapt_adaptive* o, sz_t size ) { badapt_adaptive_s_get_aware( o )->set_in_size( o, size ); } \
  static inline void badapt_adaptive_r_set_in_size( const sr_s* o, sz_t size ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->set_in_size( o->o, size ); } \
  static inline bl_t badapt_adaptive_p_defines_set_in_size( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_set_in_size( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_set_in_size( const sr_s* o ) { return true; } \
  static inline sz_t badapt_adaptive_p_get_out_size( const badapt_adaptive_s* __p, const badapt_adaptive* o ) { return __p->get_out_size( o ); } \
  static inline sz_t badapt_adaptive_a_get_out_size( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->get_out_size( o ); } \
  static inline sz_t badapt_adaptive_r_get_out_size( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->get_out_size( o->o ); } \
  static inline bl_t badapt_adaptive_p_defines_get_out_size( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_get_out_size( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_get_out_size( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_set_out_size( const badapt_adaptive_s* __p, badapt_adaptive* o, sz_t size ) { __p->set_out_size( o, size ); } \
  static inline void badapt_adaptive_a_set_out_size( badapt_adaptive* o, sz_t size ) { badapt_adaptive_s_get_aware( o )->set_out_size( o, size ); } \
  static inline void badapt_adaptive_r_set_out_size( const sr_s* o, sz_t size ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->set_out_size( o->o, size ); } \
  static inline bl_t badapt_adaptive_p_defines_set_out_size( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_set_out_size( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_set_out_size( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_infer( const badapt_adaptive_s* __p, const badapt_adaptive* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { __p->infer( o, in, out ); } \
  static inline void badapt_adaptive_a_infer( const badapt_adaptive* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { badapt_adaptive_s_get_aware( o )->infer( o, in, out ); } \
  static inline void badapt_adaptive_r_infer( const sr_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->infer( o->o, in, out ); } \
  static inline bl_t badapt_adaptive_p_defines_infer( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_infer( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_infer( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_minfer( const badapt_adaptive_s* __p, badapt_adaptive* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { __p->minfer( o, in, out ); } \
  static inline void badapt_adaptive_a_minfer( badapt_adaptive* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { badapt_adaptive_s_get_aware( o )->minfer( o, in, out ); } \
  static inline void badapt_adaptive_r_minfer( const sr_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->minfer( o->o, in, out ); } \
  static inline bl_t badapt_adaptive_p_defines_minfer( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_minfer( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_minfer( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_bgrad( const badapt_adaptive_s* __p, const badapt_adaptive* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ) { __p->bgrad( o, grad_in, grad_out ); } \
  static inline void badapt_adaptive_a_bgrad( const badapt_adaptive* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ) { badapt_adaptive_s_get_aware( o )->bgrad( o, grad_in, grad_out ); } \
  static inline void badapt_adaptive_r_bgrad( const sr_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ) { ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->bgrad( o->o, grad_in, grad_out ); } \
  static inline bl_t badapt_adaptive_p_defines_bgrad( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_bgrad( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_bgrad( const sr_s* o ) { return true; } \
  static inline void badapt_adaptive_p_bgrad_adapt( const badapt_adaptive_s* __p, badapt_adaptive* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ) { __p->bgrad_adapt( o, grad_in, grad_out ); } \
  static inline void badapt_adaptive_a_bgrad_adapt( badapt_adaptive* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ) { badapt_adaptive_s_get_aware( o )->bgrad_adapt( o, grad_in, grad_out ); } \
  static inline void badapt_adaptive_r_bgrad_adapt( const sr_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->bgrad_adapt( o->o, grad_in, grad_out ); } \
  static inline bl_t badapt_adaptive_p_defines_bgrad_adapt( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_bgrad_adapt( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_bgrad_adapt( const sr_s* o ) { return true; } \
  static inline f3_t badapt_adaptive_p_get_step( const badapt_adaptive_s* __p, const badapt_adaptive* o ) { return __p->get_step( o ); } \
  static inline f3_t badapt_adaptive_a_get_step( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->get_step( o ); } \
  static inline f3_t badapt_adaptive_r_get_step( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->get_step( o->o ); } \
  static inline bl_t badapt_adaptive_p_defines_get_step( const badapt_adaptive_s* __p ) { return __p->get_step != NULL; } \
  static inline bl_t badapt_adaptive_a_defines_get_step( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->get_step != NULL; } \
  static inline bl_t badapt_adaptive_r_defines_get_step( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->get_step != NULL; } \
  static inline void badapt_adaptive_p_set_step( const badapt_adaptive_s* __p, badapt_adaptive* o, f3_t val ) { __p->set_step( o, val ); } \
  static inline void badapt_adaptive_a_set_step( badapt_adaptive* o, f3_t val ) { badapt_adaptive_s_get_aware( o )->set_step( o, val ); } \
  static inline void badapt_adaptive_r_set_step( const sr_s* o, f3_t val ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->set_step( o->o, val ); } \
  static inline bl_t badapt_adaptive_p_defines_set_step( const badapt_adaptive_s* __p ) { return __p->set_step != NULL; } \
  static inline bl_t badapt_adaptive_a_defines_set_step( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->set_step != NULL; } \
  static inline bl_t badapt_adaptive_r_defines_set_step( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->set_step != NULL; } \
  static inline f3_t badapt_adaptive_p_get_regularization( const badapt_adaptive_s* __p, const badapt_adaptive* o, tp_t type ) { return __p->get_regularization( o, type ); } \
  static inline f3_t badapt_adaptive_a_get_regularization( const badapt_adaptive* o, tp_t type ) { return badapt_adaptive_s_get_aware( o )->get_regularization( o, type ); } \
  static inline f3_t badapt_adaptive_r_get_regularization( const sr_s* o, tp_t type ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->get_regularization( o->o, type ); } \
  static inline bl_t badapt_adaptive_p_defines_get_regularization( const badapt_adaptive_s* __p ) { return __p->get_regularization != NULL; } \
  static inline bl_t badapt_adaptive_a_defines_get_regularization( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->get_regularization != NULL; } \
  static inline bl_t badapt_adaptive_r_defines_get_regularization( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->get_regularization != NULL; } \
  static inline void badapt_adaptive_p_set_regularization( const badapt_adaptive_s* __p, badapt_adaptive* o, tp_t type, f3_t val ) { __p->set_regularization( o, type, val ); } \
  static inline void badapt_adaptive_a_set_regularization( badapt_adaptive* o, tp_t type, f3_t val ) { badapt_adaptive_s_get_aware( o )->set_regularization( o, type, val ); } \
  static inline void badapt_adaptive_r_set_regularization( const sr_s* o, tp_t type, f3_t val ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->set_regularization( o->o, type, val ); } \
  static inline bl_t badapt_adaptive_p_defines_set_regularization( const badapt_adaptive_s* __p ) { return __p->set_regularization != NULL; } \
  static inline bl_t badapt_adaptive_a_defines_set_regularization( const badapt_adaptive* o ) { return badapt_adaptive_s_get_aware( o )->set_regularization != NULL; } \
  static inline bl_t badapt_adaptive_r_defines_set_regularization( const sr_s* o ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->set_regularization != NULL; } \
  static inline void badapt_adaptive_p_arc_to_sink( const badapt_adaptive_s* __p, const badapt_adaptive* o, bcore_sink* sink ) { __p->arc_to_sink( o, sink ); } \
  static inline void badapt_adaptive_a_arc_to_sink( const badapt_adaptive* o, bcore_sink* sink ) { badapt_adaptive_s_get_aware( o )->arc_to_sink( o, sink ); } \
  static inline void badapt_adaptive_r_arc_to_sink( const sr_s* o, bcore_sink* sink ) { ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->arc_to_sink( o->o, sink ); } \
  static inline bl_t badapt_adaptive_p_defines_arc_to_sink( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_arc_to_sink( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_arc_to_sink( const sr_s* o ) { return true; } \
  void badapt_adaptive_arc_to_sink_fallback( const badapt_adaptive* o, bcore_sink* sink ); \
  static inline f3_t badapt_adaptive_p_infer_f3( const badapt_adaptive_s* __p, const badapt_adaptive* o, const bmath_vf3_s* in ) { return __p->infer_f3( o, in ); } \
  static inline f3_t badapt_adaptive_a_infer_f3( const badapt_adaptive* o, const bmath_vf3_s* in ) { return badapt_adaptive_s_get_aware( o )->infer_f3( o, in ); } \
  static inline f3_t badapt_adaptive_r_infer_f3( const sr_s* o, const bmath_vf3_s* in ) { return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->infer_f3( o->o, in ); } \
  static inline bl_t badapt_adaptive_p_defines_infer_f3( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_infer_f3( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_infer_f3( const sr_s* o ) { return true; } \
  f3_t badapt_adaptive_infer_f3_fallback( const badapt_adaptive* o, const bmath_vf3_s* in ); \
  static inline void badapt_adaptive_p_adapt_l2( const badapt_adaptive_s* __p, badapt_adaptive* o, const bmath_vf3_s* in, const bmath_vf3_s* target, bmath_vf3_s* out ) { __p->adapt_l2( o, in, target, out ); } \
  static inline void badapt_adaptive_a_adapt_l2( badapt_adaptive* o, const bmath_vf3_s* in, const bmath_vf3_s* target, bmath_vf3_s* out ) { badapt_adaptive_s_get_aware( o )->adapt_l2( o, in, target, out ); } \
  static inline void badapt_adaptive_r_adapt_l2( const sr_s* o, const bmath_vf3_s* in, const bmath_vf3_s* target, bmath_vf3_s* out ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->adapt_l2( o->o, in, target, out ); } \
  static inline bl_t badapt_adaptive_p_defines_adapt_l2( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_adapt_l2( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_adapt_l2( const sr_s* o ) { return true; } \
  void badapt_adaptive_adapt_l2_fallback( badapt_adaptive* o, const bmath_vf3_s* in, const bmath_vf3_s* target, bmath_vf3_s* out ); \
  static inline f3_t badapt_adaptive_p_adapt_l2_f3( const badapt_adaptive_s* __p, badapt_adaptive* o, const bmath_vf3_s* in, f3_t target ) { return __p->adapt_l2_f3( o, in, target ); } \
  static inline f3_t badapt_adaptive_a_adapt_l2_f3( badapt_adaptive* o, const bmath_vf3_s* in, f3_t target ) { return badapt_adaptive_s_get_aware( o )->adapt_l2_f3( o, in, target ); } \
  static inline f3_t badapt_adaptive_r_adapt_l2_f3( const sr_s* o, const bmath_vf3_s* in, f3_t target ) { ASSERT( !sr_s_is_const( o ) ); return ( (badapt_adaptive_s*)ch_spect_p( o->p, TYPEOF_badapt_adaptive_s ) )->adapt_l2_f3( o->o, in, target ); } \
  static inline bl_t badapt_adaptive_p_defines_adapt_l2_f3( const badapt_adaptive_s* __p ) { return true; } \
  static inline bl_t badapt_adaptive_a_defines_adapt_l2_f3( const badapt_adaptive* o ) { return true; } \
  static inline bl_t badapt_adaptive_r_defines_adapt_l2_f3( const sr_s* o ) { return true; } \
  f3_t badapt_adaptive_adapt_l2_f3_fallback( badapt_adaptive* o, const bmath_vf3_s* in, f3_t target );

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_activation

#define TYPEOF_badapt_activation 1242735104
#define TYPEOF_badapt_activation_s 314872026
#define BETH_EXPAND_GROUP_badapt_activation \
  BCORE_FORWARD_OBJECT( badapt_activation ); \
  typedef f3_t (*badapt_activation_fx)( const badapt_activation* o, f3_t x ); \
  typedef f3_t (*badapt_activation_dy)( const badapt_activation* o, f3_t y ); \
  BCORE_DECLARE_SPECT( badapt_activation ) \
  { \
      bcore_spect_header_s header; \
      badapt_activation_fx fx; \
      badapt_activation_dy dy; \
  }; \
  static inline f3_t badapt_activation_p_fx( const badapt_activation_s* __p, const badapt_activation* o, f3_t x ) { return __p->fx( o, x ); } \
  static inline f3_t badapt_activation_a_fx( const badapt_activation* o, f3_t x ) { return badapt_activation_s_get_aware( o )->fx( o, x ); } \
  static inline f3_t badapt_activation_r_fx( const sr_s* o, f3_t x ) { return ( (badapt_activation_s*)ch_spect_p( o->p, TYPEOF_badapt_activation_s ) )->fx( o->o, x ); } \
  static inline bl_t badapt_activation_p_defines_fx( const badapt_activation_s* __p ) { return true; } \
  static inline bl_t badapt_activation_a_defines_fx( const badapt_activation* o ) { return true; } \
  static inline bl_t badapt_activation_r_defines_fx( const sr_s* o ) { return true; } \
  static inline f3_t badapt_activation_p_dy( const badapt_activation_s* __p, const badapt_activation* o, f3_t y ) { return __p->dy( o, y ); } \
  static inline f3_t badapt_activation_a_dy( const badapt_activation* o, f3_t y ) { return badapt_activation_s_get_aware( o )->dy( o, y ); } \
  static inline f3_t badapt_activation_r_dy( const sr_s* o, f3_t y ) { return ( (badapt_activation_s*)ch_spect_p( o->p, TYPEOF_badapt_activation_s ) )->dy( o->o, y ); } \
  static inline bl_t badapt_activation_p_defines_dy( const badapt_activation_s* __p ) { return true; } \
  static inline bl_t badapt_activation_a_defines_dy( const badapt_activation* o ) { return true; } \
  static inline bl_t badapt_activation_r_defines_dy( const sr_s* o ) { return true; }

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_activator

#define TYPEOF_badapt_activator 1765962851
#define TYPEOF_badapt_activator_s 991795461
#define BETH_EXPAND_GROUP_badapt_activator \
  BCORE_FORWARD_OBJECT( badapt_activator ); \
  typedef void (*badapt_activator_reset)( badapt_activator* o ); \
  typedef void (*badapt_activator_setup)( badapt_activator* o ); \
  typedef sz_t (*badapt_activator_get_size)( const badapt_activator* o ); \
  typedef void (*badapt_activator_set_size)( badapt_activator* o, sz_t size ); \
  typedef const sr_s* (*badapt_activator_get_activation)( const badapt_activator* o ); \
  typedef void (*badapt_activator_set_activation)( badapt_activator* o, sr_s activation ); \
  typedef void (*badapt_activator_infer)( const badapt_activator* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
  typedef void (*badapt_activator_bgrad)( const badapt_activator* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out ); \
  typedef void (*badapt_activator_adapt)( badapt_activator* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step ); \
  BCORE_DECLARE_SPECT( badapt_activator ) \
  { \
      bcore_spect_header_s header; \
      badapt_activator_reset reset; \
      badapt_activator_setup setup; \
      badapt_activator_get_size get_size; \
      badapt_activator_set_size set_size; \
      badapt_activator_get_activation get_activation; \
      badapt_activator_set_activation set_activation; \
      badapt_activator_infer infer; \
      badapt_activator_bgrad bgrad; \
      badapt_activator_adapt adapt; \
  }; \
  static inline void badapt_activator_p_reset( const badapt_activator_s* __p, badapt_activator* o ) { __p->reset( o ); } \
  static inline void badapt_activator_a_reset( badapt_activator* o ) { badapt_activator_s_get_aware( o )->reset( o ); } \
  static inline void badapt_activator_r_reset( const sr_s* o ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->reset( o->o ); } \
  static inline bl_t badapt_activator_p_defines_reset( const badapt_activator_s* __p ) { return true; } \
  static inline bl_t badapt_activator_a_defines_reset( const badapt_activator* o ) { return true; } \
  static inline bl_t badapt_activator_r_defines_reset( const sr_s* o ) { return true; } \
  static inline void badapt_activator_p_setup( const badapt_activator_s* __p, badapt_activator* o ) { __p->setup( o ); } \
  static inline void badapt_activator_a_setup( badapt_activator* o ) { badapt_activator_s_get_aware( o )->setup( o ); } \
  static inline void badapt_activator_r_setup( const sr_s* o ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->setup( o->o ); } \
  static inline bl_t badapt_activator_p_defines_setup( const badapt_activator_s* __p ) { return true; } \
  static inline bl_t badapt_activator_a_defines_setup( const badapt_activator* o ) { return true; } \
  static inline bl_t badapt_activator_r_defines_setup( const sr_s* o ) { return true; } \
  static inline sz_t badapt_activator_p_get_size( const badapt_activator_s* __p, const badapt_activator* o ) { return __p->get_size( o ); } \
  static inline sz_t badapt_activator_a_get_size( const badapt_activator* o ) { return badapt_activator_s_get_aware( o )->get_size( o ); } \
  static inline sz_t badapt_activator_r_get_size( const sr_s* o ) { return ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->get_size( o->o ); } \
  static inline bl_t badapt_activator_p_defines_get_size( const badapt_activator_s* __p ) { return __p->get_size != NULL; } \
  static inline bl_t badapt_activator_a_defines_get_size( const badapt_activator* o ) { return badapt_activator_s_get_aware( o )->get_size != NULL; } \
  static inline bl_t badapt_activator_r_defines_get_size( const sr_s* o ) { return ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->get_size != NULL; } \
  static inline void badapt_activator_p_set_size( const badapt_activator_s* __p, badapt_activator* o, sz_t size ) { __p->set_size( o, size ); } \
  static inline void badapt_activator_a_set_size( badapt_activator* o, sz_t size ) { badapt_activator_s_get_aware( o )->set_size( o, size ); } \
  static inline void badapt_activator_r_set_size( const sr_s* o, sz_t size ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->set_size( o->o, size ); } \
  static inline bl_t badapt_activator_p_defines_set_size( const badapt_activator_s* __p ) { return __p->set_size != NULL; } \
  static inline bl_t badapt_activator_a_defines_set_size( const badapt_activator* o ) { return badapt_activator_s_get_aware( o )->set_size != NULL; } \
  static inline bl_t badapt_activator_r_defines_set_size( const sr_s* o ) { return ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->set_size != NULL; } \
  static inline const sr_s* badapt_activator_p_get_activation( const badapt_activator_s* __p, const badapt_activator* o ) { return __p->get_activation( o ); } \
  static inline const sr_s* badapt_activator_a_get_activation( const badapt_activator* o ) { return badapt_activator_s_get_aware( o )->get_activation( o ); } \
  static inline const sr_s* badapt_activator_r_get_activation( const sr_s* o ) { return ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->get_activation( o->o ); } \
  static inline bl_t badapt_activator_p_defines_get_activation( const badapt_activator_s* __p ) { return __p->get_activation != NULL; } \
  static inline bl_t badapt_activator_a_defines_get_activation( const badapt_activator* o ) { return badapt_activator_s_get_aware( o )->get_activation != NULL; } \
  static inline bl_t badapt_activator_r_defines_get_activation( const sr_s* o ) { return ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->get_activation != NULL; } \
  static inline void badapt_activator_p_set_activation( const badapt_activator_s* __p, badapt_activator* o, sr_s activation ) { __p->set_activation( o, activation ); } \
  static inline void badapt_activator_a_set_activation( badapt_activator* o, sr_s activation ) { badapt_activator_s_get_aware( o )->set_activation( o, activation ); } \
  static inline void badapt_activator_r_set_activation( const sr_s* o, sr_s activation ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->set_activation( o->o, activation ); } \
  static inline bl_t badapt_activator_p_defines_set_activation( const badapt_activator_s* __p ) { return __p->set_activation != NULL; } \
  static inline bl_t badapt_activator_a_defines_set_activation( const badapt_activator* o ) { return badapt_activator_s_get_aware( o )->set_activation != NULL; } \
  static inline bl_t badapt_activator_r_defines_set_activation( const sr_s* o ) { return ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->set_activation != NULL; } \
  static inline void badapt_activator_p_infer( const badapt_activator_s* __p, const badapt_activator* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { __p->infer( o, in, out ); } \
  static inline void badapt_activator_a_infer( const badapt_activator* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { badapt_activator_s_get_aware( o )->infer( o, in, out ); } \
  static inline void badapt_activator_r_infer( const sr_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ) { ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->infer( o->o, in, out ); } \
  static inline bl_t badapt_activator_p_defines_infer( const badapt_activator_s* __p ) { return true; } \
  static inline bl_t badapt_activator_a_defines_infer( const badapt_activator* o ) { return true; } \
  static inline bl_t badapt_activator_r_defines_infer( const sr_s* o ) { return true; } \
  static inline void badapt_activator_p_bgrad( const badapt_activator_s* __p, const badapt_activator* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out ) { __p->bgrad( o, grad_in, grad_out, out ); } \
  static inline void badapt_activator_a_bgrad( const badapt_activator* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out ) { badapt_activator_s_get_aware( o )->bgrad( o, grad_in, grad_out, out ); } \
  static inline void badapt_activator_r_bgrad( const sr_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out ) { ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->bgrad( o->o, grad_in, grad_out, out ); } \
  static inline bl_t badapt_activator_p_defines_bgrad( const badapt_activator_s* __p ) { return true; } \
  static inline bl_t badapt_activator_a_defines_bgrad( const badapt_activator* o ) { return true; } \
  static inline bl_t badapt_activator_r_defines_bgrad( const sr_s* o ) { return true; } \
  static inline void badapt_activator_p_adapt( const badapt_activator_s* __p, badapt_activator* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step ) { __p->adapt( o, grad_in, grad_out, out, step ); } \
  static inline void badapt_activator_a_adapt( badapt_activator* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step ) { badapt_activator_s_get_aware( o )->adapt( o, grad_in, grad_out, out, step ); } \
  static inline void badapt_activator_r_adapt( const sr_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step ) { ASSERT( !sr_s_is_const( o ) ); ( (badapt_activator_s*)ch_spect_p( o->p, TYPEOF_badapt_activator_s ) )->adapt( o->o, grad_in, grad_out, out, step ); } \
  static inline bl_t badapt_activator_p_defines_adapt( const badapt_activator_s* __p ) { return true; } \
  static inline bl_t badapt_activator_a_defines_adapt( const badapt_activator* o ) { return true; } \
  static inline bl_t badapt_activator_r_defines_adapt( const sr_s* o ) { return true; }

/**********************************************************************************************************************/
// source: badapt_test

/**********************************************************************************************************************/
// source: badapt_activator

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_activation_objects

#define TYPEOF_badapt_activation_objects 802839491
  #define TYPEOF_badapt_activation_tanh_s 2100774626
  #define BETH_EXPAND_ITEM_badapt_activation_tanh_s \
    BCORE_DECLARE_OBJECT( badapt_activation_tanh_s ) \
      {aware_t _;}; \
    f3_t badapt_activation_tanh_s_fx( const badapt_activation_tanh_s* o, f3_t x ); \
    f3_t badapt_activation_tanh_s_dy( const badapt_activation_tanh_s* o, f3_t y );
  #define TYPEOF_badapt_activation_relu_s 708121501
  #define BETH_EXPAND_ITEM_badapt_activation_relu_s \
    BCORE_DECLARE_OBJECT( badapt_activation_relu_s ) \
      {aware_t _;}; \
    f3_t badapt_activation_relu_s_fx( const badapt_activation_relu_s* o, f3_t x ); \
    f3_t badapt_activation_relu_s_dy( const badapt_activation_relu_s* o, f3_t y );
  #define TYPEOF_badapt_activation_leaky_relu_s 841402970
  #define BETH_EXPAND_ITEM_badapt_activation_leaky_relu_s \
    BCORE_DECLARE_OBJECT( badapt_activation_leaky_relu_s ) \
      {aware_t _;}; \
    f3_t badapt_activation_leaky_relu_s_fx( const badapt_activation_leaky_relu_s* o, f3_t x ); \
    f3_t badapt_activation_leaky_relu_s_dy( const badapt_activation_leaky_relu_s* o, f3_t y );
  #define TYPEOF_badapt_activation_softplus_s 3728332191
  #define BETH_EXPAND_ITEM_badapt_activation_softplus_s \
    BCORE_DECLARE_OBJECT( badapt_activation_softplus_s ) \
      {aware_t _;}; \
    f3_t badapt_activation_softplus_s_fx( const badapt_activation_softplus_s* o, f3_t x ); \
    f3_t badapt_activation_softplus_s_dy( const badapt_activation_softplus_s* o, f3_t y );
#define BETH_EXPAND_GROUP_badapt_activation_objects \
  BETH_EXPAND_ITEM_badapt_activation_tanh_s \
  BETH_EXPAND_ITEM_badapt_activation_relu_s \
  BETH_EXPAND_ITEM_badapt_activation_leaky_relu_s \
  BETH_EXPAND_ITEM_badapt_activation_softplus_s

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_activator_objects

#define TYPEOF_badapt_activator_objects 987788816
  #define TYPEOF_badapt_activator_plain_s 3369734202
  #define BETH_EXPAND_ITEM_badapt_activator_plain_s \
    BCORE_DECLARE_OBJECT( badapt_activator_plain_s ) \
      {aware_t _;sr_s activation;}; \
    void badapt_activator_plain_s_setup( badapt_activator_plain_s* o ); \
    void badapt_activator_plain_s_reset( badapt_activator_plain_s* o ); \
    void badapt_activator_plain_s_infer( const badapt_activator_plain_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_activator_plain_s_bgrad( const badapt_activator_plain_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out ); \
    void badapt_activator_plain_s_adapt( badapt_activator_plain_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step ); \
    void badapt_activator_plain_s_set_activation( badapt_activator_plain_s* o, sr_s activation ); \
    const sr_s* badapt_activator_plain_s_get_activation( const badapt_activator_plain_s* o );
  #define TYPEOF_badapt_activator_offset_s 2607571033
  #define BETH_EXPAND_ITEM_badapt_activator_offset_s \
    BCORE_DECLARE_OBJECT( badapt_activator_offset_s ) \
      {aware_t _;sr_s activation;BCORE_ARRAY_DYN_SOLID_STATIC_S( f3_t, arr_offset_ );}; \
    void badapt_activator_offset_s_setup( badapt_activator_offset_s* o ); \
    void badapt_activator_offset_s_reset( badapt_activator_offset_s* o ); \
    void badapt_activator_offset_s_infer( const badapt_activator_offset_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_activator_offset_s_bgrad( const badapt_activator_offset_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out ); \
    void badapt_activator_offset_s_adapt( badapt_activator_offset_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step ); \
    void badapt_activator_offset_s_set_activation( badapt_activator_offset_s* o, sr_s activation ); \
    const sr_s* badapt_activator_offset_s_get_activation( const badapt_activator_offset_s* o );
#define BETH_EXPAND_GROUP_badapt_activator_objects \
  BETH_EXPAND_ITEM_badapt_activator_plain_s \
  BETH_EXPAND_ITEM_badapt_activator_offset_s

/**********************************************************************************************************************/
// source: badapt_mlp

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_mlp

#define TYPEOF_badapt_mlp 498425923
  #define TYPEOF_badapt_mlp_s 3664397861
  #define BETH_EXPAND_ITEM_badapt_mlp_s \
    BCORE_DECLARE_OBJECT( badapt_mlp_s ) \
      {aware_t _;sz_t input_size;sz_t input_kernels;sz_t output_kernels;sz_t layers;f3_t kernels_rate;f3_t adapt_step;f3_t regularization_l2;sr_s act_mid;sr_s act_out;u2_t random_state;sz_t max_buffer_size;bmath_arr_mf3_s arr_w;bcore_arr_sr_s arr_activator;bmath_arr_vf3_s arr_a;bmath_arr_vf3_s arr_b;bmath_vf3_s buf_ab;bmath_vf3_s in;bmath_vf3_s out;}; \
    void badapt_mlp_s_reset( badapt_mlp_s* o ); \
    void badapt_mlp_s_setup( badapt_mlp_s* o ); \
    sz_t badapt_mlp_s_get_in_size( const badapt_mlp_s* o ); \
    void badapt_mlp_s_set_in_size( badapt_mlp_s* o, sz_t size ); \
    sz_t badapt_mlp_s_get_out_size( const badapt_mlp_s* o ); \
    void badapt_mlp_s_set_out_size( badapt_mlp_s* o, sz_t size ); \
    f3_t badapt_mlp_s_get_step( const badapt_mlp_s* o ); \
    void badapt_mlp_s_set_step( badapt_mlp_s* o, f3_t val ); \
    f3_t badapt_mlp_s_get_regularization( const badapt_mlp_s* o, tp_t type ); \
    void badapt_mlp_s_set_regularization( badapt_mlp_s* o, tp_t type, f3_t val ); \
    void badapt_mlp_s_arc_to_sink( const badapt_mlp_s* o, bcore_sink* sink ); \
    void badapt_mlp_s_infer( const badapt_mlp_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_mlp_s_minfer( badapt_mlp_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_mlp_s_bgrad( const badapt_mlp_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out ); \
    void badapt_mlp_s_bgrad_adapt( badapt_mlp_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );
#define BETH_EXPAND_GROUP_badapt_mlp \
  BETH_EXPAND_ITEM_badapt_mlp_s

/**********************************************************************************************************************/

vd_t badapt_precoded_signal_handler( const bcore_signal_s* o );

#endif // BADAPT_PRECODED_H
