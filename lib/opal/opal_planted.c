/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019, 2020 J.B.Steffens
 *  Last File Update: 2020-07-11T12:39:16Z
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
 *
 */

#include "opal_planted.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: opal_context.h
#include "opal_context.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_context

BCORE_DEFINE_OBJECT_INST_P( opal_context_std_s )
"aware opal_context"
"{"
    "aware bcore_prsg => prsg = bcore_prsg_lcg_u3_00_s;"
    "func ^:get_prsg;"
"}";

BCORE_DEFINE_SPECT( bcore_inst, opal_context )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_context : get_prsg;"
"}";

/**********************************************************************************************************************/
// source: opal_holor.h
#include "opal_holor.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_holor

BCORE_DEFINE_OBJECT_INST_P( opal_holor_meta_s )
"aware bhvm_mcode_hmeta"
"{"
    "aware bcore_inst => custom;"
    "hidden bhvm_mcode_node_s -> mnode;"
    "tp_t name;"
    "tp_t pclass;"
    "bl_t htp;"
    "bl_t active = true;"
    "func ^:get_name;"
    "func ^:get_pclass;"
    "func ^:is_rollable;"
    "func ^:is_active;"
    "func ^:get_custom;"
    "func ^:set_custom;"
    "func ^:get_node;"
    "func ^:set_node;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_holor_s )
"aware opal_holor"
"{"
    "opal_holor_meta_s m;"
    "bhvm_holor_s h;"
    "func bcore_fp:copy_typed;"
"}";

/**********************************************************************************************************************/
// source: opal_nop.h
#include "opal_nop.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop

BCORE_DEFINE_OBJECT_INST_P( opal_nop_solve_result_s )
"aware bcore_inst"
"{"
    "opal_holor_s => h;"
    "st_s => msg;"
    "bl_t settled = false;"
    "bl_t codable = true;"
    "bl_t reducible = true;"
    "tp_t type_vop_ap;"
    "tp_t type_vop_dp_a;"
    "tp_t type_vop_dp_b;"
    "tp_t type_vop_dp_c;"
    "aware => attached;"
"}";

BCORE_DEFINE_SPECT( bcore_inst, opal_nop )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_nop : arity = opal_nop_arity__;"
    "feature aware opal_nop : priority = opal_nop_priority__;"
    "feature aware opal_nop : symbol = opal_nop_symbol__;"
    "feature aware opal_nop : reserved = opal_nop_reserved__;"
    "feature aware opal_nop : create_op_of_arn = opal_nop_create_op_of_arn__;"
    "feature aware opal_nop : eci = opal_nop_eci__;"
    "feature aware opal_nop : solve = opal_nop_solve__;"
    "feature aware opal_nop : solve_node;"
    "feature aware opal_nop : is_cyclic = opal_nop_is_cyclic__;"
    "feature aware opal_nop : is_adaptive = opal_nop_is_adaptive__;"
    "feature aware opal_nop : settle = opal_nop_settle__;"
    "feature aware opal_nop : type_vop_ap;"
    "feature aware opal_nop : type_vop_dp_a;"
    "feature aware opal_nop : type_vop_dp_b;"
    "feature aware opal_nop : type_vop_dp_c;"
    "feature aware opal_nop : mcode_push_ap_holor = opal_nop_mcode_push_ap_holor__;"
    "feature aware opal_nop : mcode_push_dp_holor = opal_nop_mcode_push_dp_holor__;"
    "feature aware opal_nop : mcode_push_ap_track = opal_nop_mcode_push_ap_track__;"
    "feature aware opal_nop : mcode_push_dp_track = opal_nop_mcode_push_dp_track__;"
"}";


void opal_nop_settle__( const opal_nop* o, opal_context* context, const opal_nop_solve_result_s* result, opal_nop** out_nop, opal_nop_solve_result_s** out_result )
{
    opal_nop_ar0_literal_s* literal = opal_nop_ar0_literal_s_create();
    literal->h = opal_holor_s_clone( result->h );
    opal_nop_solve_result_s* r = opal_nop_solve_result_s_create();
    r->h = bcore_fork( literal->h );
    opal_nop_solve_result_s_attach( out_result, r );
    opal_nop_a_attach( out_nop, (opal_nop*)literal );
}

sz_t opal_nop_mcode_push_ap_holor__( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    bhvm_holor_s* h = &result->h->h;
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    if( m->active )
    {
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    }
    return idx;
}

sz_t opal_nop_mcode_push_dp_holor__( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    
    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp,        bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ),       0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    
    BLM_RETURNV( sz_t, idx );
}

void opal_nop_mcode_push_ap_track__( const opal_nop* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    tp_t type = ( opal_nop_a_defines_type_vop_ap( o ) ) ? opal_nop_a_type_vop_ap( o ) : result->type_vop_ap;
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap, bhvm_vop_t_create( type ), arr_ci );
}

void opal_nop_mcode_push_dp_track__( const opal_nop* o, const opal_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    if( ch_id >= opal_nop_a_arity( o ) + 'a' ) ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    tp_t type = 0;
    switch( ch_id )
    {
        case 'a': type = ( opal_nop_a_defines_type_vop_dp_a( o ) ) ? opal_nop_a_type_vop_dp_a( o ) : result->type_vop_dp_a; break;
        case 'b': type = ( opal_nop_a_defines_type_vop_dp_b( o ) ) ? opal_nop_a_type_vop_dp_b( o ) : result->type_vop_dp_b; break;
        case 'c': type = ( opal_nop_a_defines_type_vop_dp_c( o ) ) ? opal_nop_a_type_vop_dp_c( o ) : result->type_vop_dp_c; break;
        default: ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    }
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_dp, bhvm_vop_t_create( type ), arr_ci );
}
//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar0

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar0_literal_s )
"aware opal_nop_ar0"
"{"
    "func opal_nop:arity;"
    "opal_holor_s -> h;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar0_literal_s_solve( const opal_nop_ar0_literal_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = true;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar0_param_s )
"aware opal_nop_ar0"
"{"
    "func opal_nop:arity;"
    "opal_holor_s -> h;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar0_param_s_solve( const opal_nop_ar0_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar0_adaptive_s )
"aware opal_nop_ar0"
"{"
    "func opal_nop:arity;"
    "opal_holor_s -> h;"
    "func opal_nop:is_adaptive;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_holor;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

bl_t opal_nop_ar0_adaptive_s_solve( const opal_nop_ar0_adaptive_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    return true;
}

sz_t opal_nop_ar0_adaptive_s_mcode_push_ap_holor( const opal_nop_ar0_adaptive_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    bhvm_holor_s* h = &result->h->h;
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    if( result->h->h.v.size == 0 ) // randomize holor if result is vacant
    {
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_randomize_s_create() ), 0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    }
    return idx;
}

sz_t opal_nop_ar0_adaptive_s_mcode_push_dp_holor( const opal_nop_ar0_adaptive_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp_adaptive_zero_grad,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ), 0, idx ) );
    BLM_RETURNV( sz_t, idx );
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar0_rand_s )
"aware opal_nop_ar0"
"{"
    "func opal_nop:arity;"
    "opal_holor_s -> h;"
    "aware bcore_prsg => prsg;"
    "f3_t min = -0.5;"
    "f3_t max = 0.5;"
    "f3_t density = 1.0;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_holor;"
"}";

bl_t opal_nop_ar0_rand_s_solve( const opal_nop_ar0_rand_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    return true;
}

sz_t opal_nop_ar0_rand_s_mcode_push_ap_holor( const opal_nop_ar0_rand_s* o, const opal_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    bhvm_holor_s* h = &result->h->h;
    opal_holor_meta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    
    bhvm_vop_ar0_rand_s* vop_rand = bhvm_vop_ar0_rand_s_create();
    vop_rand->prsg = bcore_prsg_a_clone( o->prsg );
    vop_rand->min = o->min;
    vop_rand->max = o->max;
    vop_rand->density = o->density;
    
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap,        bhvm_vop_a_set_index( ( ( bhvm_vop* )vop_rand ),                          0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    
    return idx;
}

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar1

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_identity_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_identity_s_solve( const opal_nop_ar1_identity_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, opal_holor_s_create() );
    bhvm_holor_s_fork( &result->h->h, &a[0]->h );
    result->h->m.htp = a[0]->m.htp;
    result->h->m.active = a[0]->m.active;
    result->settled = (result->h) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_f3_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_f3_s_solve( const opal_nop_ar1_f3_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, opal_holor_s_clone( a[0] ) );
    bhvm_holor_s_set_type( &result->h->h, TYPEOF_f3_t );
    result->settled = ( result->h ) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_f2_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_f2_s_solve( const opal_nop_ar1_f2_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, opal_holor_s_clone( a[0] ) );
    bhvm_holor_s_set_type( &result->h->h, TYPEOF_f2_t );
    result->settled = ( result->h ) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_neg_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:create_op_of_arn;"
"}";

opal_nop* opal_nop_ar1_neg_s_create_op_of_arn( const opal_nop_ar1_neg_s* o, sz_t n )
{
    return ( n == 2 ) ? (opal_nop*)opal_nop_ar2_sub_s_create()
         : ( n == 1 ) ? (opal_nop*)opal_nop_ar1_neg_s_clone( o )
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_floor_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_ceil_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_abs_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_exp_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_log_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_inv_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_sqr_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_srt_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_sigm_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_sigm_hard_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_sigm_leaky_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_tanh_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_tanh_hard_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_tanh_leaky_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_softplus_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_softmax_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_relu_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_relu_leaky_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_output_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_adaptive_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "tp_t name;"
    "func opal_nop:priority;"
    "func opal_nop:is_adaptive;"
    "func opal_nop:solve;"
    "func opal_nop:settle;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_dimof_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_dimof_s_solve( const opal_nop_ar1_dimof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_create() );
        bhvm_holor_s_set_scalar_f3( &result->h->h, a[0]->h.s.size ? a[0]->h.s.data[ a[0]->h.s.size - 1 ] : 1 );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_volof_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_volof_s_solve( const opal_nop_ar1_volof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_create() );
        bhvm_holor_s_set_scalar_f3( &result->h->h, bhvm_shape_s_get_volume( &a[0]->h.s ) );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_constof_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_constof_s_solve( const opal_nop_ar1_constof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_clone( a[0] ) );
        if( result->h->h.v.size == 0 ) bhvm_holor_s_fit_size( &result->h->h );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_zeroof_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_zeroof_s_solve( const opal_nop_ar1_zeroof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_clone( a[0] ) );
        if( result->h->h.v.size == 0 ) bhvm_holor_s_fit_size( &result->h->h );
        bhvm_value_s_zro( &result->h->h.v );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_shapeof_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar1_shapeof_s_solve( const opal_nop_ar1_shapeof_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    if( a[0] )
    {
        opal_holor_s_attach( &result->h, opal_holor_s_create() );
        bhvm_shape_s_copy( &result->h->h.s, &a[0]->h.s );
        bhvm_value_s_set_type( &result->h->h.v, a[0]->h.v.type );
        result->h->m.htp = &a[0]->m.htp;
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_rand_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
    "func opal_nop:settle;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_cast_htp_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_holor;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_reshape_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "bhvm_shape_s shape;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_holor;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar2

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_add_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_sub_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
    "func opal_nop:create_op_of_arn;"
"}";

opal_nop* opal_nop_ar2_sub_s_create_op_of_arn( const opal_nop_ar2_sub_s* o, sz_t n )
{
    return ( n == 2 ) ? (opal_nop*)opal_nop_ar2_sub_s_clone( o )
         : ( n == 1 ) ? (opal_nop*)opal_nop_ar1_neg_s_create()
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_mul_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_div_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_pow_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_bmul_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_equal_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_unequal_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_larger_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_smaller_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_larger_equal_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_smaller_equal_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_and_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_logic_or_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_cat_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_ccat_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_order_inc_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_track;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_order_dec_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:symbol;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_holor;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_cyclic_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "tp_t name;"
    "func opal_nop:priority;"
    "func opal_nop:is_cyclic;"
    "func opal_nop:solve;"
    "func opal_nop:mcode_push_ap_track;"
    "func opal_nop:mcode_push_dp_track;"
    "func opal_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_rands_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
    "func opal_nop:settle;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar2_reshape_s )
"aware opal_nop_ar2"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:symbol;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar2_reshape_s_solve( const opal_nop_ar2_reshape_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    ERR_fa( "This function should never be called from feature 'solve_node'." );
    return false;
}

//----------------------------------------------------------------------------------------------------------------------
// group: opal_nop_ar3

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar3_iff_s )
"aware opal_nop_ar3"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:eci;"
    "func opal_nop:symbol;"
    "func opal_nop:type_vop_ap;"
    "func opal_nop:type_vop_dp_a;"
    "func opal_nop:type_vop_dp_b;"
    "func opal_nop:type_vop_dp_c;"
"}";

/**********************************************************************************************************************/
// source: opal_eval_nop.h
#include "opal_eval_nop.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_eval_nop

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_result_s )
"aware bcore_inst"
"{"
    "sz_t total_tests = 0;"
    "sz_t solvable_tests = 0;"
    "sz_t tolerated_errors = 0;"
    "bl_t error = false;"
    "st_s msg;"
"}";

void opal_eval_nop_result_s_resolve( const opal_eval_nop_result_s* o )
{
    if( !o ) return;
    if( o->error )
    {
        bcore_sink_a_push_fa( BCORE_STDERR, "#<sc_t>\n", o->msg.sc );
    }
    else if( o->msg.size > 0 )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<sc_t>\n", o->msg.sc );
    }
    if( o->total_tests > 0 )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "Total tests ...... #<sz_t>\n", o->total_tests );
        bcore_sink_a_push_fa( BCORE_STDOUT, "Solvable tests ... #<sz_t> (#<sz_t>%)\n", o->solvable_tests, ( o->solvable_tests * 100 ) / o->total_tests );
        bcore_sink_a_push_fa( BCORE_STDOUT, "Tolerated errors . #<sz_t>\n", o->tolerated_errors );
    }
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_param_s )
"aware bcore_inst"
"{"
    "aware opal_nop => nop;"
    "opal_holor_s => ha;"
    "opal_holor_s => hb;"
    "opal_holor_s => hc;"
    "opal_holor_s => hr;"
    "hidden aware bcore_sink -> log;"
    "sz_t verbosity = 1;"
    "aware bcore_prsg => prsg = bcore_prsg_lcg_u3_00_s;"
    "func bcore_inst_call:init_x;"
"}";

void opal_eval_nop_param_s_set( opal_eval_nop_param_s* o, const opal_eval_nop_param_s* src )
{
    o->verbosity = sz_max( o->verbosity, src->verbosity );
    bcore_prsg_a_set_state_mix( o->prsg, o->prsg, src->prsg );
    bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
    if( !o->ha  ) o->ha  = opal_holor_s_clone( src->ha );
    if( !o->hb  ) o->hb  = opal_holor_s_clone( src->hb );
    if( !o->hc  ) o->hc  = opal_holor_s_clone( src->hc );
    if( !o->hr  ) o->hr  = opal_holor_s_clone( src->hr );
    if( !o->nop ) o->nop = opal_nop_a_clone( src->nop );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_generator_s )
"aware opal_eval_nop"
"{"
    "opal_eval_nop_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "bl_t set_htp = false;"
    "bl_t set_value = false;"
    "bl_t set_shape = false;"
    "bl_t set_dim = false;"
    "bl_t set_v_type = false;"
    "sz_t max_shape_size = 3;"
    "sz_t max_dim = 3;"
    "f3_t v_min = -1;"
    "f3_t v_max = 1;"
    "sz_t cycles = 0;"
    "bcore_arr_uz_s tolerated_cycles;"
    "aware opal_eval_nop=> eval;"
"}";

s2_t opal_eval_nop_generator_s_main( opal_eval_nop_generator_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    opal_eval_nop_result_s_resolve( opal_eval_nop_generator_s_run( o, BLM_CREATE( opal_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_show_param_s )
"aware opal_eval_nop"
"{"
    "opal_eval_nop_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

s2_t opal_eval_nop_show_param_s_main( opal_eval_nop_show_param_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    opal_eval_nop_result_s_resolve( opal_eval_nop_show_param_s_run( o, BLM_CREATE( opal_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_arr_s )
"aware bcore_array"
"{"
    "aware opal_eval_nop* [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_set_s )
"aware opal_eval_nop"
"{"
    "opal_eval_nop_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "opal_eval_nop_arr_s arr;"
    "func ^:run;"
"}";

s2_t opal_eval_nop_set_s_main( opal_eval_nop_set_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    opal_eval_nop_result_s_resolve( opal_eval_nop_set_s_run( o, BLM_CREATE( opal_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

opal_eval_nop_result_s* opal_eval_nop_set_s_run( const opal_eval_nop_set_s* o, opal_eval_nop_result_s* result )
{
    BFOR_EACH( i, &o->arr )
    {
        BLM_INIT();
        opal_eval_nop* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
        opal_eval_nop_a_set_param( eval, &o->param );
        opal_eval_nop_a_run( eval, result );
        if( result->error )
        {
            st_s* s = BLM_A_PUSH( st_s_clone( &result->msg ) );
            st_s_copy_fa( &result->msg, "At set entry #<sz_t>:\n#<st_s*>", i, s );
            BLM_RETURNV( opal_eval_nop_result_s*, result );
        }
        BLM_DOWN();
    };
    return result;
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_ar1_s )
"aware opal_eval_nop"
"{"
    "opal_eval_nop_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "aware opal_context => context = opal_context_std_s;"
"}";

s2_t opal_eval_nop_ar1_s_main( opal_eval_nop_ar1_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    opal_eval_nop_result_s_resolve( opal_eval_nop_ar1_s_run( o, BLM_CREATE( opal_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_nop_ar2_s )
"aware opal_eval_nop"
"{"
    "opal_eval_nop_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "aware opal_context => context = opal_context_std_s;"
"}";

s2_t opal_eval_nop_ar2_s_main( opal_eval_nop_ar2_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    opal_eval_nop_result_s_resolve( opal_eval_nop_ar2_s_run( o, BLM_CREATE( opal_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_SPECT( bcore_inst, opal_eval_nop )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_eval_nop : set_param;"
    "feature aware opal_eval_nop : run;"
"}";

/**********************************************************************************************************************/


vd_t opal_planted_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "opal_planted" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: opal_context.h

            // group: opal_context
            BCORE_REGISTER_FEATURE( opal_context_get_prsg );
            BCORE_REGISTER_FFUNC( opal_context_get_prsg, opal_context_std_s_get_prsg );
            BCORE_REGISTER_OBJECT( opal_context_std_s );
            BCORE_REGISTER_SPECT( opal_context );

            // --------------------------------------------------------------------
            // source: opal_holor.h

            // group: opal_holor
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_name, opal_holor_meta_s_get_name );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_pclass, opal_holor_meta_s_get_pclass );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_is_rollable, opal_holor_meta_s_is_rollable );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_is_active, opal_holor_meta_s_is_active );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_custom, opal_holor_meta_s_get_custom );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_set_custom, opal_holor_meta_s_set_custom );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_node, opal_holor_meta_s_get_node );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_set_node, opal_holor_meta_s_set_node );
            BCORE_REGISTER_OBJECT( opal_holor_meta_s );
            BCORE_REGISTER_FFUNC( bcore_fp_copy_typed, opal_holor_s_copy_typed );
            BCORE_REGISTER_OBJECT( opal_holor_s );
            BCORE_REGISTER_TRAIT( opal_holor, bcore_inst );

            // --------------------------------------------------------------------
            // source: opal_nop.h

            // group: opal_nop
            BCORE_REGISTER_NAME( track_ap );
            BCORE_REGISTER_NAME( track_dp );
            BCORE_REGISTER_NAME( track_ap_setup );
            BCORE_REGISTER_NAME( track_dp_setup );
            BCORE_REGISTER_NAME( track_ap_shelve );
            BCORE_REGISTER_NAME( track_dp_shelve );
            BCORE_REGISTER_NAME( track_dp_cyclic_zero_grad );
            BCORE_REGISTER_NAME( track_ap_cyclic_reset );
            BCORE_REGISTER_NAME( track_ap_cyclic_update );
            BCORE_REGISTER_NAME( track_dp_adaptive_zero_grad );
            BCORE_REGISTER_FEATURE( opal_nop_arity );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_arity__ );
            BCORE_REGISTER_FEATURE( opal_nop_priority );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_priority__ );
            BCORE_REGISTER_FEATURE( opal_nop_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_symbol__ );
            BCORE_REGISTER_FEATURE( opal_nop_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_reserved__ );
            BCORE_REGISTER_FEATURE( opal_nop_create_op_of_arn );
            BCORE_REGISTER_FFUNC( opal_nop_create_op_of_arn, opal_nop_create_op_of_arn__ );
            BCORE_REGISTER_OBJECT( opal_nop_solve_result_s );
            BCORE_REGISTER_FEATURE( opal_nop_eci );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_eci__ );
            BCORE_REGISTER_FEATURE( opal_nop_solve );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_solve__ );
            BCORE_REGISTER_FEATURE( opal_nop_solve_node );
            BCORE_REGISTER_FEATURE( opal_nop_is_cyclic );
            BCORE_REGISTER_FFUNC( opal_nop_is_cyclic, opal_nop_is_cyclic__ );
            BCORE_REGISTER_FEATURE( opal_nop_is_adaptive );
            BCORE_REGISTER_FFUNC( opal_nop_is_adaptive, opal_nop_is_adaptive__ );
            BCORE_REGISTER_FEATURE( opal_nop_settle );
            BCORE_REGISTER_FFUNC( opal_nop_settle, opal_nop_settle__ );
            BCORE_REGISTER_FEATURE( opal_nop_type_vop_ap );
            BCORE_REGISTER_FEATURE( opal_nop_type_vop_dp_a );
            BCORE_REGISTER_FEATURE( opal_nop_type_vop_dp_b );
            BCORE_REGISTER_FEATURE( opal_nop_type_vop_dp_c );
            BCORE_REGISTER_FEATURE( opal_nop_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_holor, opal_nop_mcode_push_ap_holor__ );
            BCORE_REGISTER_FEATURE( opal_nop_mcode_push_dp_holor );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_mcode_push_dp_holor__ );
            BCORE_REGISTER_FEATURE( opal_nop_mcode_push_ap_track );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_track, opal_nop_mcode_push_ap_track__ );
            BCORE_REGISTER_FEATURE( opal_nop_mcode_push_dp_track );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_track, opal_nop_mcode_push_dp_track__ );
            BCORE_REGISTER_SPECT( opal_nop );

            // group: opal_nop_ar0
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar0_literal_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar0_literal_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar0_literal_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar0_param_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar0_param_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar0_param_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar0_adaptive_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_is_adaptive, opal_nop_ar0_adaptive_s_is_adaptive );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar0_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_holor, opal_nop_ar0_adaptive_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar0_adaptive_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar0_adaptive_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar0_rand_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar0_rand_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_holor, opal_nop_ar0_rand_s_mcode_push_ap_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar0_rand_s );
            BCORE_REGISTER_TRAIT( opal_nop_ar0, opal_nop );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar0_literal_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar0_param_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar0_adaptive_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar0_rand_s );

            // group: opal_nop_ar1
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_identity_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_identity_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_identity_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_identity_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_identity_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_f3_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_f3_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_f3_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_f3_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_f3_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_f3_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_f2_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_f2_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_f2_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_f2_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_f2_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_f2_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_neg_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_neg_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_neg_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_neg_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_neg_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_neg_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_create_op_of_arn, opal_nop_ar1_neg_s_create_op_of_arn );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_neg_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_floor_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_floor_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_floor_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_floor_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_floor_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar1_floor_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_floor_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_ceil_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_ceil_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_ceil_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_ceil_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_ceil_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar1_ceil_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_ceil_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_abs_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_abs_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_abs_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_abs_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_abs_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_abs_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_abs_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_exp_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_exp_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_exp_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_exp_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_exp_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_exp_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_exp_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_log_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_log_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_log_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_log_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_log_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_log_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_log_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_inv_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_inv_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_inv_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_inv_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_inv_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_inv_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_inv_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_sqr_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_sqr_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_sqr_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_sqr_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_sqr_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_sqr_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_sqr_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_srt_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_srt_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_srt_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_srt_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_srt_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_srt_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_srt_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_sigm_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_sigm_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_sigm_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_sigm_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_sigm_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_sigm_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_sigm_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_sigm_hard_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_sigm_hard_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_sigm_hard_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_sigm_hard_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_sigm_hard_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_sigm_hard_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_sigm_hard_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_sigm_leaky_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_sigm_leaky_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_sigm_leaky_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_sigm_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_sigm_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_sigm_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_sigm_leaky_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_tanh_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_tanh_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_tanh_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_tanh_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_tanh_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_tanh_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_tanh_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_tanh_hard_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_tanh_hard_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_tanh_hard_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_tanh_hard_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_tanh_hard_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_tanh_hard_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_tanh_hard_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_tanh_leaky_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_tanh_leaky_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_tanh_leaky_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_tanh_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_tanh_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_tanh_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_tanh_leaky_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_softplus_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_softplus_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_softplus_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_softplus_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_softplus_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_softplus_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_softplus_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_softmax_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_softmax_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_softmax_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_softmax_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_softmax_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_softmax_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_softmax_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_relu_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_relu_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_relu_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_relu_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_relu_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_relu_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_relu_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_relu_leaky_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_relu_leaky_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_relu_leaky_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_relu_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar1_relu_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar1_relu_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_relu_leaky_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_output_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_output_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_output_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar1_output_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_output_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_adaptive_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_adaptive_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_adaptive_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_is_adaptive, opal_nop_ar1_adaptive_s_is_adaptive );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_settle, opal_nop_ar1_adaptive_s_settle );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_adaptive_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_dimof_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_dimof_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_dimof_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_dimof_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_dimof_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_dimof_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_volof_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_volof_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_volof_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_volof_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_volof_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_volof_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_constof_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_constof_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_constof_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_constof_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_constof_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_constof_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_zeroof_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_zeroof_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_zeroof_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_zeroof_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_zeroof_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_zeroof_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_shapeof_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_shapeof_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_shapeof_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_shapeof_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_shapeof_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_shapeof_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_rand_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_rand_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_rand_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_rand_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_rand_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_settle, opal_nop_ar1_rand_s_settle );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_rand_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_cast_htp_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_cast_htp_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_cast_htp_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar1_cast_htp_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_cast_htp_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_holor, opal_nop_ar1_cast_htp_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar1_cast_htp_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_cast_htp_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_reshape_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_reshape_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_reshape_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_reshape_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_holor, opal_nop_ar1_reshape_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar1_reshape_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_reshape_s );
            BCORE_REGISTER_TRAIT( opal_nop_ar1, opal_nop );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_identity_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_f3_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_f2_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_neg_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_floor_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_ceil_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_abs_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_exp_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_log_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_inv_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_sqr_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_srt_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_sigm_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_sigm_hard_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_sigm_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_tanh_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_tanh_hard_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_tanh_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_softplus_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_softmax_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_relu_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_relu_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_output_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_adaptive_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_dimof_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_volof_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_constof_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_zeroof_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_shapeof_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_rand_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_cast_htp_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_reshape_s );

            // group: opal_nop_ar2
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_add_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_add_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_add_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_add_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_add_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_add_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_add_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_add_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_add_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_sub_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_sub_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_sub_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_sub_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_sub_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_sub_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_sub_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_sub_s_type_vop_dp_b );
            BCORE_REGISTER_FFUNC( opal_nop_create_op_of_arn, opal_nop_ar2_sub_s_create_op_of_arn );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_sub_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_mul_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_mul_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_mul_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_mul_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_mul_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_mul_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_mul_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_mul_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_mul_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_div_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_div_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_div_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_div_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_div_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_div_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_div_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_div_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_div_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_pow_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_pow_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_pow_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_pow_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_pow_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_pow_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_pow_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_pow_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_pow_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_bmul_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_bmul_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_bmul_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_bmul_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_bmul_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_bmul_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_equal_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_equal_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_equal_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_equal_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_equal_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_equal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_equal_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_unequal_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_unequal_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_unequal_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_unequal_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_unequal_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_unequal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_unequal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_unequal_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_larger_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_larger_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_larger_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_larger_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_larger_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_larger_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_larger_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_larger_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_smaller_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_smaller_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_smaller_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_smaller_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_smaller_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_smaller_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_smaller_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_smaller_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_larger_equal_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_larger_equal_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_larger_equal_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_larger_equal_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_larger_equal_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_larger_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_larger_equal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_larger_equal_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_smaller_equal_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_smaller_equal_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_smaller_equal_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_smaller_equal_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_smaller_equal_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_smaller_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_smaller_equal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_smaller_equal_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_and_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_and_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_and_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_and_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_and_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_and_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_and_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_and_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_logic_or_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_logic_or_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_logic_or_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar2_logic_or_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_logic_or_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_logic_or_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_logic_or_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_logic_or_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_cat_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_cat_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_cat_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_cat_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_cat_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_cat_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_cat_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_cat_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_cat_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_ccat_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_ccat_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_ccat_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_ccat_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_ccat_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar2_ccat_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_ccat_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_ccat_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_ccat_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_order_inc_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_order_inc_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_order_inc_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_order_inc_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_order_inc_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_track, opal_nop_ar2_order_inc_s_mcode_push_ap_track );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar2_order_inc_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar2_order_inc_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_order_inc_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_order_dec_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_order_dec_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_order_dec_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_order_dec_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_order_dec_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_holor, opal_nop_ar2_order_dec_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_order_dec_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_order_dec_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_cyclic_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_cyclic_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_cyclic_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_is_cyclic, opal_nop_ar2_cyclic_s_is_cyclic );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_cyclic_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_ap_track, opal_nop_ar2_cyclic_s_mcode_push_ap_track );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_track, opal_nop_ar2_cyclic_s_mcode_push_dp_track );
            BCORE_REGISTER_FFUNC( opal_nop_mcode_push_dp_holor, opal_nop_ar2_cyclic_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_cyclic_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_rands_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_rands_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_rands_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_rands_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_rands_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_settle, opal_nop_ar2_rands_s_settle );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_rands_s );
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar2_reshape_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar2_reshape_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar2_reshape_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar2_reshape_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar2_reshape_s_solve );
            BCORE_REGISTER_OBJECT( opal_nop_ar2_reshape_s );
            BCORE_REGISTER_TRAIT( opal_nop_ar2, opal_nop );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_add_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_sub_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_mul_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_div_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_pow_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_bmul_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_equal_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_unequal_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_larger_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_smaller_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_larger_equal_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_smaller_equal_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_and_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_logic_or_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_cat_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_ccat_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_order_inc_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_order_dec_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_cyclic_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_rands_s );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar2_reshape_s );

            // group: opal_nop_ar3
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar3_iff_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar3_iff_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar3_iff_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_eci, opal_nop_ar3_iff_s_eci );
            BCORE_REGISTER_FFUNC( opal_nop_symbol, opal_nop_ar3_iff_s_symbol );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_ap, opal_nop_ar3_iff_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_a, opal_nop_ar3_iff_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_b, opal_nop_ar3_iff_s_type_vop_dp_b );
            BCORE_REGISTER_FFUNC( opal_nop_type_vop_dp_c, opal_nop_ar3_iff_s_type_vop_dp_c );
            BCORE_REGISTER_OBJECT( opal_nop_ar3_iff_s );
            BCORE_REGISTER_TRAIT( opal_nop_ar3, opal_nop );
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar3_iff_s );

            // --------------------------------------------------------------------
            // source: opal_eval_nop.h

            // group: opal_eval_nop
            BCORE_REGISTER_OBJECT( opal_eval_nop_result_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, opal_eval_nop_param_s_init_x );
            BCORE_REGISTER_OBJECT( opal_eval_nop_param_s );
            BCORE_REGISTER_FEATURE( opal_eval_nop_set_param );
            BCORE_REGISTER_FEATURE( opal_eval_nop_run );
            BCORE_REGISTER_FFUNC( opal_eval_nop_run, opal_eval_nop_generator_s_run );
            BCORE_REGISTER_FFUNC( opal_eval_nop_set_param, opal_eval_nop_generator_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_nop_generator_s_main );
            BCORE_REGISTER_OBJECT( opal_eval_nop_generator_s );
            BCORE_REGISTER_FFUNC( opal_eval_nop_set_param, opal_eval_nop_show_param_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_nop_show_param_s_main );
            BCORE_REGISTER_FFUNC( opal_eval_nop_run, opal_eval_nop_show_param_s_run );
            BCORE_REGISTER_OBJECT( opal_eval_nop_show_param_s );
            BCORE_REGISTER_OBJECT( opal_eval_nop_arr_s );
            BCORE_REGISTER_FFUNC( opal_eval_nop_set_param, opal_eval_nop_set_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_nop_set_s_main );
            BCORE_REGISTER_FFUNC( opal_eval_nop_run, opal_eval_nop_set_s_run );
            BCORE_REGISTER_OBJECT( opal_eval_nop_set_s );
            BCORE_REGISTER_FFUNC( opal_eval_nop_run, opal_eval_nop_ar1_s_run );
            BCORE_REGISTER_FFUNC( opal_eval_nop_set_param, opal_eval_nop_ar1_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_nop_ar1_s_main );
            BCORE_REGISTER_OBJECT( opal_eval_nop_ar1_s );
            BCORE_REGISTER_FFUNC( opal_eval_nop_run, opal_eval_nop_ar2_s_run );
            BCORE_REGISTER_FFUNC( opal_eval_nop_set_param, opal_eval_nop_ar2_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_nop_ar2_s_main );
            BCORE_REGISTER_OBJECT( opal_eval_nop_ar2_s );
            BCORE_REGISTER_SPECT( opal_eval_nop );
        }
        break;
        default: break;
    }
    return NULL;
}
// BETH_PLANT_SIGNATURE     842945
