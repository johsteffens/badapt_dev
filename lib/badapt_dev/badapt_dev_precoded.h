/** This file was generated by the beth-precode-compiler. Not suitable for manual editing.
 *
 *  Copyright and License:
 *    If a specification exists for the repository or folder in which the file is located,
 *    that specification shall apply. Otherwise, the Copyright and License of the associated
 *    source code files containing beth-precode shall apply.
 */

#ifndef BADAPT_DEV_PRECODED_H
#define BADAPT_DEV_PRECODED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: badapt_dev_problem

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_problem_objects

#define TYPEOF_badapt_dev_problem_objects 483428364
  #define TYPEOF_badapt_problem_recurrent_kjv_s 1636314442
  #define BETH_EXPAND_ITEM_badapt_problem_recurrent_kjv_s \
    BCORE_DECLARE_OBJECT( badapt_problem_recurrent_kjv_s ) \
      {aware_t _;bcore_source* source;bcore_arr_sz_s* charmap;st_s* charset;u0_t t_last_char;u0_t v_last_char;u2_t rval;f3_t pos_tgt;f3_t neg_tgt;badapt_loss* preferred_loss;}; \
    const badapt_loss* badapt_problem_recurrent_kjv_s_preferred_loss( const badapt_problem_recurrent_kjv_s* o ); \
    sz_t badapt_problem_recurrent_kjv_s_get_in_size( const badapt_problem_recurrent_kjv_s* o ); \
    sz_t badapt_problem_recurrent_kjv_s_get_out_size( const badapt_problem_recurrent_kjv_s* o ); \
    void badapt_problem_recurrent_kjv_s_fetch_sample_tio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_problem_recurrent_kjv_s_fetch_sample_vio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out );
  #define TYPEOF_badapt_guide_char_encode_s 2263969302
  #define BETH_EXPAND_ITEM_badapt_guide_char_encode_s \
    BCORE_DECLARE_OBJECT( badapt_guide_char_encode_s ) \
      {aware_t _;badapt_guide* guide_default;bcore_arr_sz_s* charmap;st_s* charset;f3_t pos_tgt;f3_t neg_tgt;}; \
    bl_t badapt_guide_char_encode_s_callback( const badapt_guide_char_encode_s* o, badapt_training_state* state );
#define BETH_EXPAND_GROUP_badapt_dev_problem_objects \
  BETH_EXPAND_ITEM_badapt_problem_recurrent_kjv_s \
  BETH_EXPAND_ITEM_badapt_guide_char_encode_s

/**********************************************************************************************************************/
// source: badapt_dev_ern

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_ern

#define TYPEOF_badapt_dev_ern 3818246179
  #define TYPEOF_badapt_dev_ern_layer_s 1185116011
  #define BETH_EXPAND_ITEM_badapt_dev_ern_layer_s \
    BCORE_DECLARE_OBJECT( badapt_dev_ern_layer_s ) \
      {bmath_vf3_s v_x;bmath_vf3_s v_c;bmath_vf3_s v_h;};
  #define TYPEOF_badapt_dev_ern_arr_layer_s 2587644503
  #define BETH_EXPAND_ITEM_badapt_dev_ern_arr_layer_s \
    BCORE_DECLARE_OBJECT( badapt_dev_ern_arr_layer_s ) \
      {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( badapt_dev_ern_layer_s, arr_ );}; \
    static inline void badapt_dev_ern_arr_layer_s_set_space( badapt_dev_ern_arr_layer_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o, size ); } \
    static inline void badapt_dev_ern_arr_layer_s_set_size( badapt_dev_ern_arr_layer_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o, size ); } \
    static inline void badapt_dev_ern_arr_layer_s_clear( badapt_dev_ern_arr_layer_s* o ) { bcore_array_t_set_space( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o, 0 ); } \
    static inline void badapt_dev_ern_arr_layer_s_push_c( badapt_dev_ern_arr_layer_s* o, const badapt_dev_ern_layer_s* v ) { bcore_array_t_push( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o, sr_twc( TYPEOF_badapt_dev_ern_layer_s, v ) ); } \
    static inline void badapt_dev_ern_arr_layer_s_push_d( badapt_dev_ern_arr_layer_s* o,       badapt_dev_ern_layer_s* v ) { bcore_array_t_push( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o, sr_tsd( TYPEOF_badapt_dev_ern_layer_s, v ) ); } \
    static inline badapt_dev_ern_layer_s* badapt_dev_ern_arr_layer_s_push( badapt_dev_ern_arr_layer_s* o ) \
    { \
        bcore_array_t_push( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o, sr_t_create( TYPEOF_badapt_dev_ern_layer_s ) ); \
        return bcore_array_t_get_last( TYPEOF_badapt_dev_ern_arr_layer_s, ( bcore_array* )o ).o; \
    }
  #define TYPEOF_badapt_dev_ern_s 3653613765
  #define BETH_EXPAND_ITEM_badapt_dev_ern_s \
    BCORE_DECLARE_OBJECT( badapt_dev_ern_s ) \
      {aware_t _;sz_t size_input;sz_t size_hidden;sz_t size_output;sz_t size_unfolded;badapt_dynamics_std_s dynamics;bmath_mf3_s w_hx;bmath_mf3_s w_hc;bmath_mf3_s w_o;badapt_activator* a_h;badapt_activator* a_o;bmath_vf3_s v_o;bmath_vf3_s v_go;bmath_vf3_s v_gc;bmath_vf3_s v_gh;bmath_mf3_s gw_hx;bmath_mf3_s gw_hc;badapt_dev_ern_arr_layer_s arr_layer;}; \
    sz_t badapt_dev_ern_s_get_in_size( const badapt_dev_ern_s* o ); \
    sz_t badapt_dev_ern_s_get_out_size( const badapt_dev_ern_s* o ); \
    void badapt_dev_ern_s_get_dynamics_std( const badapt_dev_ern_s* o, badapt_dynamics_std_s* dynamics ); \
    void badapt_dev_ern_s_set_dynamics_std( badapt_dev_ern_s* o, const badapt_dynamics_std_s* dynamics ); \
    void badapt_dev_ern_s_arc_to_sink( const badapt_dev_ern_s* o, bcore_sink* sink ); \
    void badapt_dev_ern_s_minfer( badapt_dev_ern_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_dev_ern_s_bgrad_adapt( badapt_dev_ern_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );
  #define TYPEOF_badapt_dev_ern_builder_s 550737685
  #define BETH_EXPAND_ITEM_badapt_dev_ern_builder_s \
    BCORE_DECLARE_OBJECT( badapt_dev_ern_builder_s ) \
      {aware_t _;sz_t size_input;sz_t size_hidden;sz_t size_output;sz_t size_unfolded;badapt_dynamics_std_s dynamics;u2_t random_seed;badapt_activator* a_h;badapt_activator* a_o;}; \
    sz_t badapt_dev_ern_builder_s_get_in_size( const badapt_dev_ern_builder_s* o ); \
    void badapt_dev_ern_builder_s_set_in_size( badapt_dev_ern_builder_s* o, sz_t size ); \
    sz_t badapt_dev_ern_builder_s_get_out_size( const badapt_dev_ern_builder_s* o ); \
    void badapt_dev_ern_builder_s_set_out_size( badapt_dev_ern_builder_s* o, sz_t size ); \
    badapt_adaptive* badapt_dev_ern_builder_s_build( const badapt_dev_ern_builder_s* o );
#define BETH_EXPAND_GROUP_badapt_dev_ern \
  BETH_EXPAND_ITEM_badapt_dev_ern_layer_s \
  BETH_EXPAND_ITEM_badapt_dev_ern_arr_layer_s \
  BETH_EXPAND_ITEM_badapt_dev_ern_s \
  BETH_EXPAND_ITEM_badapt_dev_ern_builder_s

/**********************************************************************************************************************/
// source: badapt_dev_jrn

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_jrn

#define TYPEOF_badapt_dev_jrn 892930198
  #define TYPEOF_badapt_dev_jrn_layer_s 549553782
  #define BETH_EXPAND_ITEM_badapt_dev_jrn_layer_s \
    BCORE_DECLARE_OBJECT( badapt_dev_jrn_layer_s ) \
      {bmath_vf3_s v_x;bmath_vf3_s v_c;bmath_vf3_s v_h;bmath_vf3_s v_o;};
  #define TYPEOF_badapt_dev_jrn_arr_layer_s 3101882642
  #define BETH_EXPAND_ITEM_badapt_dev_jrn_arr_layer_s \
    BCORE_DECLARE_OBJECT( badapt_dev_jrn_arr_layer_s ) \
      {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( badapt_dev_jrn_layer_s, arr_ );}; \
    static inline void badapt_dev_jrn_arr_layer_s_set_space( badapt_dev_jrn_arr_layer_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o, size ); } \
    static inline void badapt_dev_jrn_arr_layer_s_set_size( badapt_dev_jrn_arr_layer_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o, size ); } \
    static inline void badapt_dev_jrn_arr_layer_s_clear( badapt_dev_jrn_arr_layer_s* o ) { bcore_array_t_set_space( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o, 0 ); } \
    static inline void badapt_dev_jrn_arr_layer_s_push_c( badapt_dev_jrn_arr_layer_s* o, const badapt_dev_jrn_layer_s* v ) { bcore_array_t_push( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o, sr_twc( TYPEOF_badapt_dev_jrn_layer_s, v ) ); } \
    static inline void badapt_dev_jrn_arr_layer_s_push_d( badapt_dev_jrn_arr_layer_s* o,       badapt_dev_jrn_layer_s* v ) { bcore_array_t_push( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o, sr_tsd( TYPEOF_badapt_dev_jrn_layer_s, v ) ); } \
    static inline badapt_dev_jrn_layer_s* badapt_dev_jrn_arr_layer_s_push( badapt_dev_jrn_arr_layer_s* o ) \
    { \
        bcore_array_t_push( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o, sr_t_create( TYPEOF_badapt_dev_jrn_layer_s ) ); \
        return bcore_array_t_get_last( TYPEOF_badapt_dev_jrn_arr_layer_s, ( bcore_array* )o ).o; \
    }
  #define TYPEOF_badapt_dev_jrn_s 2535842248
  #define BETH_EXPAND_ITEM_badapt_dev_jrn_s \
    BCORE_DECLARE_OBJECT( badapt_dev_jrn_s ) \
      {aware_t _;sz_t size_input;sz_t size_hidden;sz_t size_output;sz_t size_unfolded;badapt_dynamics_std_s dynamics;bmath_mf3_s w_hx;bmath_mf3_s w_hc;bmath_mf3_s w_oh;badapt_activator* a_h;badapt_activator* a_o;bmath_vf3_s v_go;bmath_vf3_s v_gc;bmath_vf3_s v_gh;bmath_mf3_s gw_hx;bmath_mf3_s gw_hc;bmath_mf3_s gw_oh;badapt_dev_jrn_arr_layer_s arr_layer;}; \
    sz_t badapt_dev_jrn_s_get_in_size( const badapt_dev_jrn_s* o ); \
    sz_t badapt_dev_jrn_s_get_out_size( const badapt_dev_jrn_s* o ); \
    void badapt_dev_jrn_s_get_dynamics_std( const badapt_dev_jrn_s* o, badapt_dynamics_std_s* dynamics ); \
    void badapt_dev_jrn_s_set_dynamics_std( badapt_dev_jrn_s* o, const badapt_dynamics_std_s* dynamics ); \
    void badapt_dev_jrn_s_arc_to_sink( const badapt_dev_jrn_s* o, bcore_sink* sink ); \
    void badapt_dev_jrn_s_minfer( badapt_dev_jrn_s* o, const bmath_vf3_s* in, bmath_vf3_s* out ); \
    void badapt_dev_jrn_s_bgrad_adapt( badapt_dev_jrn_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );
  #define TYPEOF_badapt_dev_jrn_builder_s 4124896260
  #define BETH_EXPAND_ITEM_badapt_dev_jrn_builder_s \
    BCORE_DECLARE_OBJECT( badapt_dev_jrn_builder_s ) \
      {aware_t _;sz_t size_input;sz_t size_hidden;sz_t size_output;sz_t size_unfolded;badapt_dynamics_std_s dynamics;u2_t random_seed;badapt_activator* a_h;badapt_activator* a_o;}; \
    sz_t badapt_dev_jrn_builder_s_get_in_size( const badapt_dev_jrn_builder_s* o ); \
    void badapt_dev_jrn_builder_s_set_in_size( badapt_dev_jrn_builder_s* o, sz_t size ); \
    sz_t badapt_dev_jrn_builder_s_get_out_size( const badapt_dev_jrn_builder_s* o ); \
    void badapt_dev_jrn_builder_s_set_out_size( badapt_dev_jrn_builder_s* o, sz_t size ); \
    badapt_adaptive* badapt_dev_jrn_builder_s_build( const badapt_dev_jrn_builder_s* o );
#define BETH_EXPAND_GROUP_badapt_dev_jrn \
  BETH_EXPAND_ITEM_badapt_dev_jrn_layer_s \
  BETH_EXPAND_ITEM_badapt_dev_jrn_arr_layer_s \
  BETH_EXPAND_ITEM_badapt_dev_jrn_s \
  BETH_EXPAND_ITEM_badapt_dev_jrn_builder_s

/**********************************************************************************************************************/
// source: badapt_dev_lstm

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_lstm

#define TYPEOF_badapt_dev_lstm 523027522
  #define TYPEOF_badapt_dev_lstm_s 571246780
  #define BETH_EXPAND_ITEM_badapt_dev_lstm_s \
    BCORE_DECLARE_OBJECT( badapt_dev_lstm_s ) \
      {aware_t _;bmath_mf3_s w_k;bmath_mf3_s w_i;bmath_mf3_s w_c;bmath_mf3_s w_o;badapt_activator* sig_k;badapt_activator* sig_i;badapt_activator* sig_o;badapt_activator* act_c;badapt_activator* act_q;bmath_vf3_s v_x;bmath_vf3_s v_h;bmath_vf3_s v_c;bmath_vf3_s v_o;bmath_vf3_s v_q;bmath_vf3_s v_xh;};
#define BETH_EXPAND_GROUP_badapt_dev_lstm \
  BETH_EXPAND_ITEM_badapt_dev_lstm_s

/**********************************************************************************************************************/

vd_t badapt_dev_precoded_signal_handler( const bcore_signal_s* o );

#endif // BADAPT_DEV_PRECODED_H
