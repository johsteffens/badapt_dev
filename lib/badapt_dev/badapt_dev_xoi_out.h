/** This file was generated from beth-plant source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-08-05T17:38:00Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  badapt_dev_problem.h
 *  badapt_dev_ern.h
 *  badapt_dev_lstm.h
 *
 */

#ifndef BADAPT_DEV_XOI_OUT_H
#define BADAPT_DEV_XOI_OUT_H

#include "bcore_control.h"

//To force a rebuild of this target by the plant-compiler, reset the hash key value below to 0.
#define HKEYOF_badapt_dev_xoila_out 1344491091

#define TYPEOF_badapt_dev_xoila_out 2337873987

/**********************************************************************************************************************/
// source: badapt_dev_problem.h

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_problem_objects

#define TYPEOF_badapt_dev_problem_objects 483428364
#define TYPEOF_badapt_dev_problem_objects_s 3324364078
#define TYPEOF_badapt_problem_recurrent_abc_s 3613882751
#define BETH_EXPAND_ITEM_badapt_problem_recurrent_abc_s \
  BCORE_DECLARE_OBJECT( badapt_problem_recurrent_abc_s ) \
    {aware_t _;sz_t index;u3_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
  static inline const badapt_loss* badapt_problem_recurrent_abc_s_preferred_loss( const badapt_problem_recurrent_abc_s* o ){return o->preferred_loss;} \
  sz_t badapt_problem_recurrent_abc_s_get_in_size( const badapt_problem_recurrent_abc_s* o ); \
  sz_t badapt_problem_recurrent_abc_s_get_out_size( const badapt_problem_recurrent_abc_s* o ); \
  void badapt_problem_recurrent_abc_s_fetch_sample_tio( badapt_problem_recurrent_abc_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
  void badapt_problem_recurrent_abc_s_fetch_sample_vio( badapt_problem_recurrent_abc_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
#define TYPEOF_badapt_problem_recurrent_text_s 1449347910
#define BETH_EXPAND_ITEM_badapt_problem_recurrent_text_s \
  BCORE_DECLARE_OBJECT( badapt_problem_recurrent_text_s ) \
    {aware_t _;st_s text_file;st_s ignore_line_char;bcore_source* source;bcore_arr_sz_s* charmap;st_s* charset;u0_t t_last_char;u0_t v_last_char;u3_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
  static inline const badapt_loss* badapt_problem_recurrent_text_s_preferred_loss( const badapt_problem_recurrent_text_s* o ){return o->preferred_loss;} \
  sz_t badapt_problem_recurrent_text_s_get_in_size( const badapt_problem_recurrent_text_s* o ); \
  sz_t badapt_problem_recurrent_text_s_get_out_size( const badapt_problem_recurrent_text_s* o ); \
  void badapt_problem_recurrent_text_s_fetch_sample_tio( badapt_problem_recurrent_text_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
  void badapt_problem_recurrent_text_s_fetch_sample_vio( badapt_problem_recurrent_text_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
#define TYPEOF_badapt_guide_char_encode_s 2263969302
#define BETH_EXPAND_ITEM_badapt_guide_char_encode_s \
  BCORE_DECLARE_OBJECT( badapt_guide_char_encode_s ) \
    {aware_t _;badapt_guide* guide_default;bcore_arr_sz_s* charmap;st_s* charset;bcore_sink* sink;f3_t pos_tgt;f3_t neg_tgt;st_s prefix;st_s postfix;st_s txt_trigger;sz_t txt_size;sz_t line_size;f3_t heat;}; \
  static inline void badapt_guide_char_encode_s_init_x( badapt_guide_char_encode_s* o ){o->sink = bcore_fork( BCORE_STDOUT );} \
  bl_t badapt_guide_char_encode_s_callback( const badapt_guide_char_encode_s* o, badapt_training_state* state );
#define TYPEOF_badapt_problem_recurrent_utf8_s 3187411278
#define BETH_EXPAND_ITEM_badapt_problem_recurrent_utf8_s \
  BCORE_DECLARE_OBJECT( badapt_problem_recurrent_utf8_s ) \
    {aware_t _;st_s text_file;bcore_source* source;u0_t t_last_char;u0_t v_last_char;u3_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
  static inline const badapt_loss* badapt_problem_recurrent_utf8_s_preferred_loss( const badapt_problem_recurrent_utf8_s* o ){return o->preferred_loss;} \
  static inline sz_t badapt_problem_recurrent_utf8_s_get_in_size( const badapt_problem_recurrent_utf8_s* o ){return 256;} \
  static inline sz_t badapt_problem_recurrent_utf8_s_get_out_size( const badapt_problem_recurrent_utf8_s* o ){return 256;} \
  void badapt_problem_recurrent_utf8_s_fetch_sample_tio( badapt_problem_recurrent_utf8_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
  void badapt_problem_recurrent_utf8_s_fetch_sample_vio( badapt_problem_recurrent_utf8_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
#define TYPEOF_badapt_guide_utf8_encode_s 3478673599
#define BETH_EXPAND_ITEM_badapt_guide_utf8_encode_s \
  BCORE_DECLARE_OBJECT( badapt_guide_utf8_encode_s ) \
    {aware_t _;badapt_guide* guide_default;bcore_sink* sink;f3_t pos_tgt;f3_t neg_tgt;st_s txt_trigger;sz_t txt_size;sz_t line_size;f3_t heat;}; \
  static inline void badapt_guide_utf8_encode_s_init_x( badapt_guide_utf8_encode_s* o ){o->sink = bcore_fork( BCORE_STDOUT );} \
  bl_t badapt_guide_utf8_encode_s_callback( const badapt_guide_utf8_encode_s* o, badapt_training_state* state );
#define BETH_EXPAND_GROUP_badapt_dev_problem_objects \
  BCORE_FORWARD_OBJECT( badapt_dev_problem_objects ); \
  BCORE_FORWARD_OBJECT( badapt_problem_recurrent_abc_s ); \
  BCORE_FORWARD_OBJECT( badapt_problem_recurrent_text_s ); \
  BCORE_FORWARD_OBJECT( badapt_guide_char_encode_s ); \
  BCORE_FORWARD_OBJECT( badapt_problem_recurrent_utf8_s ); \
  BCORE_FORWARD_OBJECT( badapt_guide_utf8_encode_s ); \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_abc_s \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_text_s \
  BETH_EXPAND_ITEM_badapt_guide_char_encode_s \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_utf8_s \
  BETH_EXPAND_ITEM_badapt_guide_utf8_encode_s

/**********************************************************************************************************************/
// source: badapt_dev_ern.h

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_ern

#define TYPEOF_badapt_dev_ern 3818246179
#define TYPEOF_badapt_dev_ern_s 3653613765
#define BETH_EXPAND_GROUP_badapt_dev_ern \
  BCORE_FORWARD_OBJECT( badapt_dev_ern );

/**********************************************************************************************************************/
// source: badapt_dev_lstm.h

/**********************************************************************************************************************/

vd_t badapt_dev_xoila_out_signal_handler( const bcore_signal_s* o );

#endif // BADAPT_DEV_XOI_OUT_H
// BETH_PLANT_SIGNATURE 3703214962