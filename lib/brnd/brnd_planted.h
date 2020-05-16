/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019, 2020 J.B.Steffens
 *  Last File Update: 2020-05-16T10:15:38Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  brnd_sketch.h
 *  brnd_eval.h
 *  brnd_gen.h
 *  brnd_test.h
 *
 */

#ifndef BRND_PLANTED_H
#define BRND_PLANTED_H

#include "bcore_control.h"


/**********************************************************************************************************************/
// source: brnd_sketch.h

//----------------------------------------------------------------------------------------------------------------------
// group: brnd

#define TYPEOF_brnd 1148841919
#define TYPEOF_brnd_s 2232709929
#define BETH_EXPAND_GROUP_brnd \
  BCORE_FORWARD_OBJECT( brnd ); \
  BCORE_FORWARD_OBJECT( brnd_gen ); \
  BCORE_FORWARD_OBJECT( brnd_test ); \
  BETH_EXPAND_GROUP_brnd_gen \
  BETH_EXPAND_GROUP_brnd_test

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen

#define TYPEOF_brnd_gen 2372545546
#define TYPEOF_brnd_gen_s 2102825716
#define BETH_EXPAND_GROUP_brnd_gen \
  BCORE_FORWARD_OBJECT( brnd_gen ); \
  typedef u3_t (*brnd_gen_max_u3)( const brnd_gen* o ); \
  typedef u3_t (*brnd_gen_min_u3)( const brnd_gen* o ); \
  typedef u3_t (*brnd_gen_gen_u3)( brnd_gen* o ); \
  typedef f3_t (*brnd_gen_gen_f3)( brnd_gen* o, f3_t min, f3_t max ); \
  typedef void (*brnd_gen_reseed)( brnd_gen* o, u3_t seed ); \
  BCORE_DECLARE_SPECT( brnd_gen ) \
  { \
      bcore_spect_header_s header; \
      brnd_gen_max_u3 max_u3; \
      brnd_gen_min_u3 min_u3; \
      brnd_gen_gen_u3 gen_u3; \
      brnd_gen_gen_f3 gen_f3; \
      brnd_gen_reseed reseed; \
  }; \
  static inline brnd_gen* brnd_gen_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_brnd_gen, t ); return ( brnd_gen* )bcore_inst_t_create( t ); } \
  static inline bl_t brnd_gen_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_brnd_gen ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( brnd_gen ) \
  static inline bl_t brnd_gen_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_brnd_gen ); } \
  static inline u3_t brnd_gen_a_max_u3( const brnd_gen* o ) { const brnd_gen_s* p = brnd_gen_s_get_aware( o ); assert( p->max_u3 ); return p->max_u3( o ); } \
  static inline bl_t brnd_gen_a_defines_max_u3( const brnd_gen* o ) { return brnd_gen_s_get_aware( o )->max_u3 != NULL; } \
  static inline u3_t brnd_gen_a_min_u3( const brnd_gen* o ) { const brnd_gen_s* p = brnd_gen_s_get_aware( o ); assert( p->min_u3 ); return p->min_u3( o ); } \
  static inline bl_t brnd_gen_a_defines_min_u3( const brnd_gen* o ) { return brnd_gen_s_get_aware( o )->min_u3 != NULL; } \
  static inline u3_t brnd_gen_a_gen_u3( brnd_gen* o ) { const brnd_gen_s* p = brnd_gen_s_get_aware( o ); assert( p->gen_u3 ); return p->gen_u3( o ); } \
  static inline bl_t brnd_gen_a_defines_gen_u3( const brnd_gen* o ) { return brnd_gen_s_get_aware( o )->gen_u3 != NULL; } \
  static inline f3_t brnd_gen_a_gen_f3( brnd_gen* o, f3_t min, f3_t max ) { const brnd_gen_s* p = brnd_gen_s_get_aware( o ); assert( p->gen_f3 ); return p->gen_f3( o, min, max ); } \
  static inline bl_t brnd_gen_a_defines_gen_f3( const brnd_gen* o ) { return brnd_gen_s_get_aware( o )->gen_f3 != NULL; } \
  static inline void brnd_gen_a_reseed( brnd_gen* o, u3_t seed ) { const brnd_gen_s* p = brnd_gen_s_get_aware( o ); assert( p->reseed ); p->reseed( o, seed ); } \
  static inline bl_t brnd_gen_a_defines_reseed( const brnd_gen* o ) { return brnd_gen_s_get_aware( o )->reseed != NULL; }

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_test

#define TYPEOF_brnd_test 2707875748
#define TYPEOF_brnd_test_s 2159612182
#define BETH_EXPAND_GROUP_brnd_test \
  BCORE_FORWARD_OBJECT( brnd_test ); \
  typedef f3_t (*brnd_test_run)( const brnd_test* o, const brnd_gen* gen ); \
  BCORE_DECLARE_SPECT( brnd_test ) \
  { \
      bcore_spect_header_s header; \
      brnd_test_run run; \
  }; \
  static inline brnd_test* brnd_test_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_brnd_test, t ); return ( brnd_test* )bcore_inst_t_create( t ); } \
  static inline bl_t brnd_test_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_brnd_test ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( brnd_test ) \
  static inline bl_t brnd_test_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_brnd_test ); } \
  static inline f3_t brnd_test_a_run( const brnd_test* o, const brnd_gen* gen ) { const brnd_test_s* p = brnd_test_s_get_aware( o ); assert( p->run ); return p->run( o, gen ); } \
  static inline bl_t brnd_test_a_defines_run( const brnd_test* o ) { return brnd_test_s_get_aware( o )->run != NULL; }

/**********************************************************************************************************************/
// source: brnd_eval.h

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_eval

#define TYPEOF_brnd_eval 3897329014
#define TYPEOF_brnd_eval_s 1277875048
#define TYPEOF_brnd_eval_result_s 3469820380
#define BETH_EXPAND_ITEM_brnd_eval_result_s \
  BCORE_DECLARE_OBJECT( brnd_eval_result_s ) \
    {aware_t _;bl_t error;st_s msg;}; \
  void brnd_eval_result_s_resolve( brnd_eval_result_s* o );
#define TYPEOF_brnd_eval_param_s 2379732274
#define BETH_EXPAND_ITEM_brnd_eval_param_s \
  BCORE_DECLARE_OBJECT( brnd_eval_param_s ) \
    {aware_t _;bcore_sink* log;st_s name;sz_t verbosity;u3_t* seed;brnd_gen* gen;brnd_test* test;}; \
  static inline void brnd_eval_param_s_init_x( brnd_eval_param_s* o ){o->log = bcore_fork( BCORE_STDOUT );} \
  void brnd_eval_param_s_set( brnd_eval_param_s* o, const brnd_eval_param_s* src );
#define TYPEOF_brnd_eval_arr_s 2822215292
#define BETH_EXPAND_ITEM_brnd_eval_arr_s \
  BCORE_DECLARE_OBJECT( brnd_eval_arr_s ) \
    {aware_t _;BCORE_ARRAY_DYN_LINK_STATIC_S( brnd_eval, );}; \
  static inline brnd_eval_arr_s* brnd_eval_arr_s_set_space( brnd_eval_arr_s* o, sz_t size ) { bcore_array_t_set_space( TYPEOF_brnd_eval_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline brnd_eval_arr_s* brnd_eval_arr_s_set_size( brnd_eval_arr_s* o, sz_t size ) { bcore_array_t_set_size( TYPEOF_brnd_eval_arr_s, ( bcore_array* )o, size ); return o; } \
  static inline brnd_eval_arr_s* brnd_eval_arr_s_clear( brnd_eval_arr_s* o ) { bcore_array_t_set_space( TYPEOF_brnd_eval_arr_s, ( bcore_array* )o, 0 ); return o; } \
  static inline brnd_eval* brnd_eval_arr_s_push_c( brnd_eval_arr_s* o, const brnd_eval* v ) { bcore_array_t_push( TYPEOF_brnd_eval_arr_s, ( bcore_array* )o, sr_awc( v ) ); return o->data[ o->size - 1 ]; } \
  static inline brnd_eval* brnd_eval_arr_s_push_d( brnd_eval_arr_s* o,       brnd_eval* v ) { bcore_array_t_push( TYPEOF_brnd_eval_arr_s, ( bcore_array* )o, sr_asd( v ) ); return o->data[ o->size - 1 ]; } \
  static inline brnd_eval* brnd_eval_arr_s_push_t( brnd_eval_arr_s* o, tp_t t ) \
  { \
      bcore_trait_assert_satisfied_type( TYPEOF_brnd_eval, t ); \
      bcore_array_t_push( TYPEOF_brnd_eval_arr_s, ( bcore_array* )o, sr_t_create( t ) ); \
      return o->data[ o->size - 1 ]; \
  }
#define TYPEOF_brnd_eval_set_s 1810561459
#define BETH_EXPAND_ITEM_brnd_eval_set_s \
  BCORE_DECLARE_OBJECT( brnd_eval_set_s ) \
    {aware_t _;brnd_eval_param_s param;brnd_eval_arr_s arr;}; \
  static inline void brnd_eval_set_s_set_param( brnd_eval_set_s* o, const brnd_eval_param_s* param ){brnd_eval_param_s_set( &o->param, param );} \
  s2_t brnd_eval_set_s_main( brnd_eval_set_s* o, const bcore_arr_st_s* args ); \
  brnd_eval_result_s* brnd_eval_set_s_run( const brnd_eval_set_s* o, brnd_eval_result_s* result );
#define TYPEOF_brnd_eval_show_param_s 2117831306
#define BETH_EXPAND_ITEM_brnd_eval_show_param_s \
  BCORE_DECLARE_OBJECT( brnd_eval_show_param_s ) \
    {aware_t _;brnd_eval_param_s param;}; \
  static inline void brnd_eval_show_param_s_set_param( brnd_eval_show_param_s* o, const brnd_eval_param_s* param ){brnd_eval_param_s_set( &o->param, param );} \
  s2_t brnd_eval_show_param_s_main( brnd_eval_show_param_s* o, const bcore_arr_st_s* args ); \
  static inline brnd_eval_result_s* brnd_eval_show_param_s_run( const brnd_eval_show_param_s* o, brnd_eval_result_s* result ){bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result;}
#define TYPEOF_brnd_eval_errf_s 286259682
#define BETH_EXPAND_ITEM_brnd_eval_errf_s \
  BCORE_DECLARE_OBJECT( brnd_eval_errf_s ) \
    {aware_t _;brnd_eval_param_s param;}; \
  static inline void brnd_eval_errf_s_set_param( brnd_eval_errf_s* o, const brnd_eval_param_s* param ){brnd_eval_param_s_set( &o->param, param );} \
  s2_t brnd_eval_errf_s_main( brnd_eval_errf_s* o, const bcore_arr_st_s* args ); \
  brnd_eval_result_s* brnd_eval_errf_s_run( const brnd_eval_errf_s* o, brnd_eval_result_s* result );
#define TYPEOF_brnd_eval_plain_s 2778308831
#define BETH_EXPAND_ITEM_brnd_eval_plain_s \
  BCORE_DECLARE_OBJECT( brnd_eval_plain_s ) \
    {aware_t _;brnd_eval_param_s param;}; \
  static inline void brnd_eval_plain_s_set_param( brnd_eval_plain_s* o, const brnd_eval_param_s* param ){brnd_eval_param_s_set( &o->param, param );} \
  s2_t brnd_eval_plain_s_main( brnd_eval_plain_s* o, const bcore_arr_st_s* args ); \
  brnd_eval_result_s* brnd_eval_plain_s_run( const brnd_eval_plain_s* o, brnd_eval_result_s* result );
#define BETH_EXPAND_GROUP_brnd_eval \
  BCORE_FORWARD_OBJECT( brnd_eval ); \
  BCORE_FORWARD_OBJECT( brnd_eval_result_s ); \
  BCORE_FORWARD_OBJECT( brnd_eval_param_s ); \
  BCORE_FORWARD_OBJECT( brnd_eval_arr_s ); \
  BCORE_FORWARD_OBJECT( brnd_eval_set_s ); \
  BCORE_FORWARD_OBJECT( brnd_eval_show_param_s ); \
  BCORE_FORWARD_OBJECT( brnd_eval_errf_s ); \
  BCORE_FORWARD_OBJECT( brnd_eval_plain_s ); \
  typedef brnd_eval_result_s* (*brnd_eval_run)( const brnd_eval* o, brnd_eval_result_s* result ); \
  typedef void (*brnd_eval_set_param)( brnd_eval* o, const brnd_eval_param_s* param ); \
  BCORE_DECLARE_SPECT( brnd_eval ) \
  { \
      bcore_spect_header_s header; \
      brnd_eval_run run; \
      brnd_eval_set_param set_param; \
  }; \
  static inline brnd_eval* brnd_eval_t_create( tp_t t ) { bcore_trait_assert_satisfied_type( TYPEOF_brnd_eval, t ); return ( brnd_eval* )bcore_inst_t_create( t ); } \
  static inline bl_t brnd_eval_t_is_trait_of( tp_t t ) { return bcore_trait_is_of( t, TYPEOF_brnd_eval ); } \
  BCORE_DECLARE_VIRTUAL_AWARE_OBJECT( brnd_eval ) \
  static inline bl_t brnd_eval_a_is_trait_of( vc_t o ) { return bcore_trait_is_of( o ? *(aware_t*)o : 0, TYPEOF_brnd_eval ); } \
  BETH_EXPAND_ITEM_brnd_eval_result_s \
  static inline brnd_eval_result_s* brnd_eval_a_run( const brnd_eval* o, brnd_eval_result_s* result ) { const brnd_eval_s* p = brnd_eval_s_get_aware( o ); assert( p->run ); return p->run( o, result ); } \
  static inline bl_t brnd_eval_a_defines_run( const brnd_eval* o ) { return brnd_eval_s_get_aware( o )->run != NULL; } \
  BETH_EXPAND_ITEM_brnd_eval_param_s \
  static inline void brnd_eval_a_set_param( brnd_eval* o, const brnd_eval_param_s* param ) { const brnd_eval_s* p = brnd_eval_s_get_aware( o ); assert( p->set_param ); p->set_param( o, param ); } \
  static inline bl_t brnd_eval_a_defines_set_param( const brnd_eval* o ) { return brnd_eval_s_get_aware( o )->set_param != NULL; } \
  BETH_EXPAND_ITEM_brnd_eval_arr_s \
  BETH_EXPAND_ITEM_brnd_eval_set_s \
  BETH_EXPAND_ITEM_brnd_eval_show_param_s \
  BETH_EXPAND_ITEM_brnd_eval_errf_s \
  BETH_EXPAND_ITEM_brnd_eval_plain_s

/**********************************************************************************************************************/
// source: brnd_gen.h

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen_stamp

#define TYPEOF_brnd_gen_stamp 2527136062
#define TYPEOF_brnd_gen_stamp_s 205989696
#define TYPEOF_brnd_gen_count_s 1158093480
#define BETH_EXPAND_ITEM_brnd_gen_count_s \
  BCORE_DECLARE_OBJECT( brnd_gen_count_s ) \
    {aware_t _;u2_t state;}; \
  static inline u3_t brnd_gen_count_s_max_u3( const brnd_gen_count_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_count_s_min_u3( const brnd_gen_count_s* o ){return 0;} \
  static inline u3_t brnd_gen_count_s_gen_u3( brnd_gen_count_s* o ){return ++o->state;} \
  static inline f3_t brnd_gen_count_s_gen_f3( brnd_gen_count_s* o, f3_t min, f3_t max ){return min + ( f3_t )brnd_gen_count_s_gen_u3( o ) / ( ( max - min ) * brnd_gen_count_s_max_u3( o ) );} \
  static inline void brnd_gen_count_s_reseed( brnd_gen_count_s* o, u3_t seed ){o->state = seed ^ ( seed >> 32 );}
#define BETH_EXPAND_GROUP_brnd_gen_stamp \
  BCORE_FORWARD_OBJECT( brnd_gen_stamp ); \
  BCORE_FORWARD_OBJECT( brnd_gen_lcg ); \
  BCORE_FORWARD_OBJECT( brnd_gen_xsg ); \
  BCORE_FORWARD_OBJECT( brnd_gen_count_s ); \
  BETH_EXPAND_GROUP_brnd_gen_lcg \
  BETH_EXPAND_GROUP_brnd_gen_xsg \
  BETH_EXPAND_ITEM_brnd_gen_count_s

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen_lcg

#define TYPEOF_brnd_gen_lcg 2782657739
#define TYPEOF_brnd_gen_lcg_s 1640002845
#define TYPEOF_brnd_gen_lcg_v00_s 1269826832
#define BETH_EXPAND_ITEM_brnd_gen_lcg_v00_s \
  BCORE_DECLARE_OBJECT( brnd_gen_lcg_v00_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_lcg_v00_s_gen_f3( brnd_gen_lcg_v00_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_lcg_v00_s_max_u3( const brnd_gen_lcg_v00_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_lcg_v00_s_min_u3( const brnd_gen_lcg_v00_s* o ){return 0;} \
  static inline void brnd_gen_lcg_v00_s_reseed( brnd_gen_lcg_v00_s* o, u3_t seed ){o->state = seed ^ ( seed >> 32 );} \
  static inline u3_t brnd_gen_lcg_v00_s_gen_u3( brnd_gen_lcg_v00_s* o ){return ( o->state = bcore_lcg_u2(  o->state ) );}
#define TYPEOF_brnd_gen_lcg_v01_s 3369582923
#define BETH_EXPAND_ITEM_brnd_gen_lcg_v01_s \
  BCORE_DECLARE_OBJECT( brnd_gen_lcg_v01_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_lcg_v01_s_gen_f3( brnd_gen_lcg_v01_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_lcg_v01_s_max_u3( const brnd_gen_lcg_v01_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_lcg_v01_s_min_u3( const brnd_gen_lcg_v01_s* o ){return 0;} \
  static inline void brnd_gen_lcg_v01_s_reseed( brnd_gen_lcg_v01_s* o, u3_t seed ){o->state = seed ^ ( seed >> 32 );} \
  static inline u3_t brnd_gen_lcg_v01_s_gen_u3( brnd_gen_lcg_v01_s* o ){return ( o->state = bcore_lcg1_u2( o->state ) );}
#define TYPEOF_brnd_gen_lcg_v02_s 2067620818
#define BETH_EXPAND_ITEM_brnd_gen_lcg_v02_s \
  BCORE_DECLARE_OBJECT( brnd_gen_lcg_v02_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_lcg_v02_s_gen_f3( brnd_gen_lcg_v02_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_lcg_v02_s_max_u3( const brnd_gen_lcg_v02_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_lcg_v02_s_min_u3( const brnd_gen_lcg_v02_s* o ){return 0;} \
  static inline void brnd_gen_lcg_v02_s_reseed( brnd_gen_lcg_v02_s* o, u3_t seed ){o->state = seed ^ ( seed >> 32 );} \
  static inline u3_t brnd_gen_lcg_v02_s_gen_u3( brnd_gen_lcg_v02_s* o ){return ( o->state = bcore_lcg2_u2( o->state ) );}
#define TYPEOF_brnd_gen_lcg_v03_s 4156931149
#define BETH_EXPAND_ITEM_brnd_gen_lcg_v03_s \
  BCORE_DECLARE_OBJECT( brnd_gen_lcg_v03_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_lcg_v03_s_gen_f3( brnd_gen_lcg_v03_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_lcg_v03_s_max_u3( const brnd_gen_lcg_v03_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_lcg_v03_s_min_u3( const brnd_gen_lcg_v03_s* o ){return 0;} \
  static inline void brnd_gen_lcg_v03_s_reseed( brnd_gen_lcg_v03_s* o, u3_t seed ){o->state = seed ^ ( seed >> 32 );} \
  static inline u3_t brnd_gen_lcg_v03_s_gen_u3( brnd_gen_lcg_v03_s* o ){return ( o->state = bcore_lcg3_u2( o->state ) );}
#define BETH_EXPAND_GROUP_brnd_gen_lcg \
  BCORE_FORWARD_OBJECT( brnd_gen_lcg ); \
  BCORE_FORWARD_OBJECT( brnd_gen_lcg_v00_s ); \
  BCORE_FORWARD_OBJECT( brnd_gen_lcg_v01_s ); \
  BCORE_FORWARD_OBJECT( brnd_gen_lcg_v02_s ); \
  BCORE_FORWARD_OBJECT( brnd_gen_lcg_v03_s ); \
  BETH_EXPAND_ITEM_brnd_gen_lcg_v00_s \
  BETH_EXPAND_ITEM_brnd_gen_lcg_v01_s \
  BETH_EXPAND_ITEM_brnd_gen_lcg_v02_s \
  BETH_EXPAND_ITEM_brnd_gen_lcg_v03_s

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen_xsg

#define TYPEOF_brnd_gen_xsg 934962351
#define TYPEOF_brnd_gen_xsg_s 3966599065
#define TYPEOF_brnd_gen_xsg_v00_s 3029867580
#define BETH_EXPAND_ITEM_brnd_gen_xsg_v00_s \
  BCORE_DECLARE_OBJECT( brnd_gen_xsg_v00_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_xsg_v00_s_gen_f3( brnd_gen_xsg_v00_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_xsg_v00_s_max_u3( const brnd_gen_xsg_v00_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_xsg_v00_s_min_u3( const brnd_gen_xsg_v00_s* o ){return 1;} \
  static inline void brnd_gen_xsg_v00_s_reseed( brnd_gen_xsg_v00_s* o, u3_t seed ){o->state = u2_max( 1, seed ^ ( seed >> 32 ) );} \
  static inline u3_t brnd_gen_xsg_v00_s_gen_u3( brnd_gen_xsg_v00_s* o ){return ( o->state = bcore_xsg_u2(  o->state ) );}
#define TYPEOF_brnd_gen_xsg_v01_s 824210615
#define BETH_EXPAND_ITEM_brnd_gen_xsg_v01_s \
  BCORE_DECLARE_OBJECT( brnd_gen_xsg_v01_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_xsg_v01_s_gen_f3( brnd_gen_xsg_v01_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_xsg_v01_s_max_u3( const brnd_gen_xsg_v01_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_xsg_v01_s_min_u3( const brnd_gen_xsg_v01_s* o ){return 1;} \
  static inline void brnd_gen_xsg_v01_s_reseed( brnd_gen_xsg_v01_s* o, u3_t seed ){o->state = u2_max( 1, seed ^ ( seed >> 32 ) );} \
  static inline u3_t brnd_gen_xsg_v01_s_gen_u3( brnd_gen_xsg_v01_s* o ){return ( o->state = bcore_xsg1_u2( o->state ) );}
#define TYPEOF_brnd_gen_xsg_v02_s 3817215806
#define BETH_EXPAND_ITEM_brnd_gen_xsg_v02_s \
  BCORE_DECLARE_OBJECT( brnd_gen_xsg_v02_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_xsg_v02_s_gen_f3( brnd_gen_xsg_v02_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_xsg_v02_s_max_u3( const brnd_gen_xsg_v02_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_xsg_v02_s_min_u3( const brnd_gen_xsg_v02_s* o ){return 1;} \
  static inline void brnd_gen_xsg_v02_s_reseed( brnd_gen_xsg_v02_s* o, u3_t seed ){o->state = u2_max( 1, seed ^ ( seed >> 32 ) );} \
  static inline u3_t brnd_gen_xsg_v02_s_gen_u3( brnd_gen_xsg_v02_s* o ){return ( o->state = bcore_xsg2_u2( o->state ) );}
#define TYPEOF_brnd_gen_xsg_v03_s 1085120793
#define BETH_EXPAND_ITEM_brnd_gen_xsg_v03_s \
  BCORE_DECLARE_OBJECT( brnd_gen_xsg_v03_s ) \
    {aware_t _;u2_t state;}; \
  f3_t brnd_gen_xsg_v03_s_gen_f3( brnd_gen_xsg_v03_s* o, f3_t min, f3_t max ); \
  static inline u3_t brnd_gen_xsg_v03_s_max_u3( const brnd_gen_xsg_v03_s* o ){return 0xFFFFFFFFu;} \
  static inline u3_t brnd_gen_xsg_v03_s_min_u3( const brnd_gen_xsg_v03_s* o ){return 1;} \
  static inline void brnd_gen_xsg_v03_s_reseed( brnd_gen_xsg_v03_s* o, u3_t seed ){o->state = u2_max( 1, seed ^ ( seed >> 32 ) );} \
  static inline u3_t brnd_gen_xsg_v03_s_gen_u3( brnd_gen_xsg_v03_s* o ){return ( o->state = bcore_xsg3_u2( o->state ) );}
#define BETH_EXPAND_GROUP_brnd_gen_xsg \
  BCORE_FORWARD_OBJECT( brnd_gen_xsg ); \
  BCORE_FORWARD_OBJECT( brnd_gen_xsg_v00_s ); \
  BCORE_FORWARD_OBJECT( brnd_gen_xsg_v01_s ); \
  BCORE_FORWARD_OBJECT( brnd_gen_xsg_v02_s ); \
  BCORE_FORWARD_OBJECT( brnd_gen_xsg_v03_s ); \
  BETH_EXPAND_ITEM_brnd_gen_xsg_v00_s \
  BETH_EXPAND_ITEM_brnd_gen_xsg_v01_s \
  BETH_EXPAND_ITEM_brnd_gen_xsg_v02_s \
  BETH_EXPAND_ITEM_brnd_gen_xsg_v03_s

/**********************************************************************************************************************/
// source: brnd_test.h

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_test_stamp

#define TYPEOF_brnd_test_stamp 2543031608
#define TYPEOF_brnd_test_stamp_s 646556258
#define TYPEOF_brnd_test_uniform_dist_s 3383636058
#define BETH_EXPAND_ITEM_brnd_test_uniform_dist_s \
  BCORE_DECLARE_OBJECT( brnd_test_uniform_dist_s ) \
    {aware_t _;sz_t samples;sz_t slots;}; \
  f3_t brnd_test_uniform_dist_s_run( const brnd_test_uniform_dist_s* o, const brnd_gen* gen );
#define BETH_EXPAND_GROUP_brnd_test_stamp \
  BCORE_FORWARD_OBJECT( brnd_test_stamp ); \
  BCORE_FORWARD_OBJECT( brnd_test_uniform_dist_s ); \
  BETH_EXPAND_ITEM_brnd_test_uniform_dist_s

/**********************************************************************************************************************/

vd_t brnd_planted_signal_handler( const bcore_signal_s* o );

#endif // BRND_PLANTED_H
