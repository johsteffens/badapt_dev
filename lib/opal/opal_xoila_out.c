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

#include "opal_xoila_out.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: opal_context.h
#include "opal_context.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_context

BCORE_DEFINE_SPECT( bcore_inst, opal_context )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_context : get_prsg = opal_context_get_prsg__;"
    "feature aware opal_context : nameof = opal_context_nameof__;"
    "feature aware opal_context : ifnameof = opal_context_ifnameof__;"
    "feature aware opal_context : typeof = opal_context_typeof__;"
    "feature aware opal_context : entypeof = opal_context_entypeof__;"
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
    "aware bcore_inst => sem_id;"
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

BCORE_DEFINE_OBJECT_INST_P( opal_nop_context_s )
"aware opal_context"
"{"
    "aware bcore_prsg => prsg = bcore_prsg_lcg_u3_00_s;"
    "func ^:get_prsg;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_nop_solve_result_s )
"aware bcore_inst"
"{"
    "opal_holor_s => h;"
    "st_s => msg;"
    "bl_t can_settle = false;"
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
    "feature aware opal_nop : solve_node = opal_nop_solve_node__;"
    "feature aware opal_nop : is_param = opal_nop_is_param__;"
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
    result->can_settle = true;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar0_param_s )
"aware opal_nop_ar0"
"{"
    "func opal_nop:arity;"
    "opal_holor_s -> h;"
    "func opal_nop:is_param;"
    "func opal_nop:solve;"
"}";

bl_t opal_nop_ar0_param_s_solve( const opal_nop_ar0_param_s* o, opal_context* context, opal_holor_s** a, opal_nop_solve_result_s* result )
{
    opal_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->can_settle = false;
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
    result->can_settle = false;
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
    result->can_settle = false;
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
    result->h->m.htp      =  a[0]->m.htp;
    result->h->m.active   =  a[0]->m.active;
    result->can_settle       = !a[0]->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_nop_ar1_param_s )
"aware opal_nop_ar1"
"{"
    "func opal_nop:arity;"
    "func opal_nop:reserved;"
    "func opal_nop:priority;"
    "func opal_nop:solve;"
    "func opal_nop:settle;"
"}";

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
    result->can_settle = ( result->h ) && !result->h->m.active;
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
    result->can_settle = ( result->h ) && !result->h->m.active;
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
        result->can_settle = true;
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
        result->can_settle = true;
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
        result->can_settle = true;
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
        result->can_settle = true;
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
        result->can_settle = true;
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
    "func opal_nop:solve_node;"
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
    "func opal_nop:solve_node;"
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

er_t opal_eval_nop_generator_s_main( opal_eval_nop_generator_s* o, bcore_main_frame_s* frame )
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

er_t opal_eval_nop_show_param_s_main( opal_eval_nop_show_param_s* o, bcore_main_frame_s* frame )
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

er_t opal_eval_nop_set_s_main( opal_eval_nop_set_s* o, bcore_main_frame_s* frame )
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
    "aware opal_context => context = opal_nop_context_s;"
"}";

er_t opal_eval_nop_ar1_s_main( opal_eval_nop_ar1_s* o, bcore_main_frame_s* frame )
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
    "aware opal_context => context = opal_nop_context_s;"
"}";

er_t opal_eval_nop_ar2_s_main( opal_eval_nop_ar2_s* o, bcore_main_frame_s* frame )
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
// source: opal_sem.h
#include "opal_sem.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem

BCORE_DEFINE_OBJECT_INST_P( opal_sem_link_s )
"aware opal_sem"
"{"
    "tp_t name;"
    "bl_t protected = false;"
    "bl_t visible = true;"
    "private opal_sem_link_s -> up;"
    "private opal_sem_link_s -> dn;"
    "private vd_t cell;"
    "bl_t exit;"
    "func ^:get_name;"
    "func ^:set_name_visible;"
    "func ^:set_name_invisible;"
    "func ^:is_visible;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_sem_links_s )
"aware bcore_array"
"{"
    "opal_sem_link_s => [];"
"}";

opal_sem_link_s* opal_sem_links_s_get_link_by_name( opal_sem_links_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return o->data[ i ];
    return NULL;
}

bl_t opal_sem_links_s_name_exists( const opal_sem_links_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return true;
    return false;
}

opal_sem_link_s* opal_sem_links_s_get_link_by_up( opal_sem_links_s* o, opal_sem_link_s* up )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->up == up ) return o->data[ i ];
    return NULL;
}

opal_sem_link_s* opal_sem_links_s_get_link_by_dn( opal_sem_links_s* o, opal_sem_link_s* dn )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->dn == dn ) return o->data[ i ];
    return NULL;
}

sz_t opal_sem_links_s_get_index_by_link( opal_sem_links_s* o, opal_sem_link_s* link )
{
    BFOR_EACH( i, o ) if( o->data[ i ] == link ) return i;
    return -1;
}

sz_t opal_sem_links_s_count_open( const opal_sem_links_s* o )
{
    sz_t count = 0;
    BFOR_EACH( i, o ) count += ( o->data[ i ]->up == NULL );
    return count;
}

BCORE_DEFINE_OBJECT_INST_P( opal_sem_body_s )
"aware bcore_array"
"{"
    "aware opal_sem=> [];"
"}";

bl_t opal_sem_body_s_name_exists( const opal_sem_body_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( opal_sem_a_get_name( o->data[ i ] ) == name ) return true;
    return false;
}

opal_sem* opal_sem_body_s_get_sem_by_name( opal_sem_body_s* o, tp_t name )
{
    BFOR_EACH( i, o )
    {
        if( opal_sem_a_get_name( o->data[ i ] ) == name )
        {
            if( opal_sem_a_is_visible( o->data[ i ] ) ) return o->data[ i ];
        }
    }
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( opal_sem_cell_s )
"aware opal_sem"
"{"
    "tp_t name;"
    "bl_t visible = true;"
    "opal_sem_links_s encs;"
    "opal_sem_links_s excs;"
    "opal_sem_body_s => body;"
    "private opal_sem_cell_s* parent;"
    "hidden opal_sem_context_s -> context;"
    "sz_t priority = 10;"
    "aware opal_nop -> nop;"
    "hidden bcore_source_point_s source_point;"
    "private opal_sem_cell_s -> wrapped_cell;"
    "func ^:get_name;"
    "func ^:set_name_visible;"
    "func ^:set_name_invisible;"
    "func ^:is_visible;"
"}";

opal_sem_cell_s* opal_sem_cell_s_get_cell_by_name( opal_sem_cell_s* o, tp_t name )
{
    opal_sem* sem = o->body ? opal_sem_body_s_get_sem_by_name( o->body, name ) : NULL;
    if( sem && sem->_ == TYPEOF_opal_sem_cell_s ) return ( opal_sem_cell_s* )sem;
    if( o->parent ) return opal_sem_cell_s_get_cell_by_name( o->parent, name );
    return NULL;
}

opal_sem_link_s* opal_sem_cell_s_get_link_by_name( opal_sem_cell_s* o, tp_t name )
{
    opal_sem* sem = o->body ? opal_sem_body_s_get_sem_by_name( o->body, name ) : NULL;
    if( sem && sem->_ == TYPEOF_opal_sem_link_s ) return ( opal_sem_link_s* )sem;
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( opal_sem_stack_flag_s )
"aware opal_sem"
"{"
"}";

BCORE_DEFINE_SPECT( bcore_inst, opal_sem )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_sem : get_name = opal_sem_get_name__;"
    "feature aware opal_sem : is_visible = opal_sem_is_visible__;"
    "feature aware opal_sem : set_name_visible;"
    "feature aware opal_sem : set_name_invisible;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_context

BCORE_DEFINE_OBJECT_INST_P( opal_sem_context_s )
"aware opal_sem_context"
"{"
    "opal_nop_context_s nop_context;"
    "func opal_context:get_prsg;"
    "bcore_hmap_name_s hmap_name;"
    "bcore_arr_st_s arr_symbol_op2;"
    "bcore_hmap_tp_s control_types;"
    "bcore_hmap_tp_s reserved_names;"
    "func opal_context:nameof;"
    "func opal_context:ifnameof;"
    "func opal_context:typeof;"
    "func opal_context:entypeof;"
"}";

opal_sem_cell_s* opal_sem_context_s_setup_cell( opal_sem_context_s* o, opal_sem_cell_s* cell )
{
    opal_sem_context_s_attach( &cell->context, bcore_fork( o ) );
    return cell;
}

opal_sem_cell_s* opal_sem_context_s_create_cell( opal_sem_context_s* o )
{
    return opal_sem_context_s_setup_cell( o, opal_sem_cell_s_create() );
}

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_id

BCORE_DEFINE_OBJECT_INST_P( opal_sem_id_s )
"aware opal_sem_id"
"{"
    "bcore_arr_tp_s arr_tp;"
"}";

void opal_sem_id_s_to_string( const opal_sem_id_s* o, const opal_context* context, st_s* s )
{
    st_s_clear( s );
    BFOR_EACH( i, &o->arr_tp )
    {
        if( i > 0 ) st_s_push_char( s, '.' );
        st_s_push_sc( s, opal_context_a_ifnameof( context, o->arr_tp.data[ i ] ) );
    }
}

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_builder

BCORE_DEFINE_OBJECT_INST_P( opal_sem_builder_s )
"aware opal_sem_builder"
"{"
    "opal_sem_context_s => context;"
    "opal_sem_cell_s => cell_context;"
    "opal_sem_cell_s => cell_frame;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: opal_sem_tree

BCORE_DEFINE_OBJECT_INST_P( opal_sem_tree_node_s )
"aware bcore_array"
"{"
    "sz_t id = -1;"
    "private opal_sem_cell_s -> cell;"
    "private opal_sem_tree_node_s -> parent;"
    "opal_sem_tree_node_s => [];"
"}";

void opal_sem_tree_node_s_push_parents_to_sem_id( const opal_sem_tree_node_s* o, opal_sem_id_s* sem_id )
{
    opal_sem_id_s_push_parent( sem_id, o->cell ? o->cell->name : 0 );
    if( o->parent ) opal_sem_tree_node_s_push_parents_to_sem_id( o->parent, sem_id );
}

void opal_sem_tree_node_s_get_sem_id( const opal_sem_tree_node_s* o, opal_sem_id_s* sem_id )
{
    opal_sem_id_s_set( sem_id, o->cell ? o->cell->name : 0 );
    if( o->parent ) opal_sem_tree_node_s_push_parents_to_sem_id( o->parent, sem_id );
}

BCORE_DEFINE_OBJECT_INST_P( opal_sem_tree_s )
"aware opal_sem_tree"
"{"
    "sz_t id_base = 0;"
    "opal_sem_tree_node_s => root;"
"}";

/**********************************************************************************************************************/
// source: opal_net.h
#include "opal_net.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_net

BCORE_DEFINE_OBJECT_INST_P( opal_net_link_s )
"aware opal_net"
"{"
    "hidden vd_t node;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_net_links_s )
"aware bcore_array"
"{"
    "opal_net_link_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_net_node_s )
"aware opal_net"
"{"
    "opal_net_links_s upls;"
    "opal_net_links_s dnls;"
    "tp_t name;"
    "opal_sem_id_s => sem_id;"
    "bl_t flag = false;"
    "bl_t probe = false;"
    "sz_t id;"
    "hidden bhvm_mcode_node_s -> mnode;"
    "aware opal_nop -> nop;"
    "opal_nop_solve_result_s => result;"
    "hidden aware opal_context -> context;"
    "hidden bcore_source_point_s -> source_point;"
    "func ^:is_cyclic;"
"}";

sz_t opal_net_node_s_up_index( const opal_net_node_s* o, const opal_net_node_s* node )
{
    BFOR_EACH( i, &o->upls ) if( o->upls.data[ i ]->node == node ) return i;
    return -1;
}

void opal_net_node_s_set_nop_d( opal_net_node_s* o, opal_nop* nop )
{
    ASSERT( o->result == NULL );
    opal_nop_a_attach( &o->nop, nop );
}

BCORE_DEFINE_OBJECT_INST_P( opal_net_node_adl_s )
"aware bcore_array"
"{"
    "opal_net_node_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_net_nodes_s )
"aware bcore_array"
"{"
    "opal_net_node_s => [];"
"}";

opal_net_node_s* opal_net_nodes_s_get_by_id( opal_net_nodes_s* o, sz_t id )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->id == id ) return o->data[ i ];
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( opal_net_cell_s )
"aware opal_net"
"{"
    "sz_t max_depth = 32768;"
    "opal_net_nodes_s body;"
    "opal_net_nodes_s encs;"
    "opal_net_nodes_s excs;"
    "hidden aware opal_context -> context;"
    "func bcore_inst_call:copy_x;"
    "func bcore_via_call:mutated;"
"}";

void opal_net_cell_s_clear_flags( opal_net_cell_s* o )
{
    BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
}

void opal_net_cell_s_clear_all_flags( opal_net_cell_s* o )
{
    BFOR_EACH( i, &o->body )
    {
        o->body.data[ i ]->flag = false;
        o->body.data[ i ]->probe = false;
    }
}

void opal_net_cell_s_clear_downlinks( opal_net_cell_s* o )
{
    BFOR_EACH( i, &o->body ) opal_net_links_s_clear( &o->body.data[ i ]->dnls );
}

BCORE_DEFINE_SPECT( bcore_inst, opal_net )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_net : is_cyclic = opal_net_is_cyclic__;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: opal_net_builder

BCORE_DEFINE_OBJECT_INST_P( opal_net_builder_s )
"aware opal_net_builder"
"{"
    "opal_sem_builder_s sem_builder;"
    "hidden bhvm_holor_adl_s input_holors;"
    "hidden aware bcore_sink -> log;"
"}";

void opal_net_builder_s_fork_input_holors( opal_net_builder_s* o, const bhvm_holor_s** input_holors, sz_t size_input_holors )
{
    bhvm_holor_adl_s_set_size( &o->input_holors, size_input_holors );
    BFOR_EACH( i, &o->input_holors )
    {
        ASSERT( input_holors[ i ] );
        bhvm_holor_s_attach( &o->input_holors.data[ i ], bcore_fork( ( bhvm_holor_s* )input_holors[ i ] ) );
    }
}

/**********************************************************************************************************************/
// source: opal_frame.h
#include "opal_frame.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_frame

BCORE_DEFINE_OBJECT_INST_P( opal_frame_s )
"aware opal_frame"
"{"
    "aware bcore_sink -> log;"
    "aware opal_context -> context;"
    "bhvm_mcode_frame_s => mcf;"
    "bl_t is_cyclic;"
    "bl_t setup;"
    "sz_t size_en;"
    "sz_t size_ex;"
    "opal_frame_hidx_s hidx_en;"
    "opal_frame_hidx_s hidx_ex;"
    "opal_frame_hidx_s hidx_ada;"
    "func bcore_via_call:shelve;"
    "func bcore_via_call:mutated;"
    "func bcore_inst_call:copy_x;"
"}";

void opal_frame_s_reset( opal_frame_s* o )
{
    if( !o->setup ) return;
    if( !o->mcf ) return;
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_shelve );
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp_shelve );
    o->setup = false;
}

opal_frame_s* opal_frame_s_bind_holors( opal_frame_s* o )
{
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_setup );
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp_setup );
    return o;
}

void opal_frame_s_setup( opal_frame_s* o )
{
    if( o->setup ) return;
    if( !o->mcf ) return;
    opal_frame_s_bind_holors( o );
    o->setup = true;
}

BCORE_DEFINE_OBJECT_INST_P( opal_frame_custom_hmeta_s )
"aware opal_frame"
"{"
    "sz_t ur_slot;"
    "sz_t ur_src;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_frame_cyclic_s )
"aware opal_frame"
"{"
    "opal_frame_s => frame;"
    "sz_t unroll_size = 2;"
    "bl_t setup = false;"
    "sz_t unroll_index = 0;"
    "bhvm_mcode_track_adl_s => track_adl_ap;"
    "bhvm_mcode_track_adl_s => track_adl_dp;"
    "bhvm_mcode_track_adl_s => track_adl_ap_setup;"
    "opal_frame_hidx_ads_s hidx_ads_en;"
    "opal_frame_hidx_ads_s hidx_ads_ex;"
    "func bcore_via_call:shelve;"
    "func bcore_via_call:mutated;"
    "func bcore_inst_call:copy_x;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: opal_frame_hidx

BCORE_DEFINE_OBJECT_INST_P( opal_frame_hidx_s )
"aware opal_frame_hidx"
"{"
    "bcore_arr_sz_s => arr;"
"}";

sz_t opal_frame_hidx_s_get_pclass_idx( const opal_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index )
{
    const bhvm_mcode_hmeta* hmeta = opal_frame_hidx_s_get_hmeta( o, hbase, index );
    if( hmeta ) return bhvm_mcode_node_s_get_pclass_idx( bhvm_mcode_hmeta_a_get_node( hmeta ), pclass );
    return -1;
}

opal_frame_hidx_s* opal_frame_hidx_s_replace_index( opal_frame_hidx_s* o, bcore_arr_sz_s* index_map )
{
    BFOR_EACH( i, o->arr )
    {
        sz_t old_index = o->arr->data[ i ];
        assert( old_index >= 0 && old_index < index_map->size );
        sz_t new_index = index_map->data[ old_index ];
        if( new_index >= 0 ) o->arr->data[ i ] = new_index;
    }
    return o;
}

BCORE_DEFINE_OBJECT_INST_P( opal_frame_hidx_ads_s )
"aware bcore_array"
"{"
    "opal_frame_hidx_s [];"
"}";

/**********************************************************************************************************************/
// source: opal_eval_frame.h
#include "opal_eval_frame.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_eval_frame

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_result_s )
"aware bcore_inst"
"{"
    "bl_t error = false;"
    "st_s msg;"
"}";

void opal_eval_frame_result_s_resolve( opal_eval_frame_result_s* o )
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
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_param_s )
"aware bcore_inst"
"{"
    "hidden aware bcore_sink -> log;"
    "sz_t verbosity = 1;"
    "u3_t rval = 1234;"
    "st_s name;"
    "aware => src;"
    "bhvm_holor_adl_s => in;"
    "bhvm_holor_adl_s => out;"
    "bl_t recovery_test = false;"
    "bl_t jacobian_test = false;"
    "f3_t max_dev = 1E-5;"
    "f3_t epsilon = 1E-5;"
    "func bcore_inst_call:init_x;"
"}";

void opal_eval_frame_param_s_set( opal_eval_frame_param_s* o, const opal_eval_frame_param_s* src )
{
    o->recovery_test = o->recovery_test || src->recovery_test;
    o->jacobian_test = o->jacobian_test || src->jacobian_test;
    
    o->verbosity = sz_max( o->verbosity, src->verbosity );
    o->rval      = bcore_lcg00_u3( o->rval + src->rval );
    bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
    
    if( o->name.size == 0 )
    {
        st_s_copy( &o->name, &src->name );
    }
    else if( src->name.size > 0 )
    {
        st_s* new_name = st_s_create_fa( "<sc_t>_<sc_t>", o->name.sc, src->name.sc );
        st_s_copy( &o->name, new_name );
        st_s_discard( new_name );
    }
    
    if( !o->src ) o->src = bcore_fork( src->src );
    if( !o->in  ) o->in  = bcore_fork( src->in );
    if( !o->out ) o->out = bcore_fork( src->out );
    
    o->max_dev = f3_max( o->max_dev, src->max_dev );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_show_param_s )
"aware opal_eval_frame"
"{"
    "opal_eval_frame_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

er_t opal_eval_frame_show_param_s_main( opal_eval_frame_show_param_s* o, bcore_main_frame_s* frame )
{
    BLM_INIT();
    opal_eval_frame_result_s_resolve( opal_eval_frame_show_param_s_run( o, BLM_CREATE( opal_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_arr_s )
"aware bcore_array"
"{"
    "aware opal_eval_frame* [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_set_s )
"aware opal_eval_frame"
"{"
    "opal_eval_frame_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "opal_eval_frame_arr_s arr;"
    "func ^:run;"
"}";

er_t opal_eval_frame_set_s_main( opal_eval_frame_set_s* o, bcore_main_frame_s* frame )
{
    BLM_INIT();
    opal_eval_frame_result_s_resolve( opal_eval_frame_set_s_run( o, BLM_CREATE( opal_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

opal_eval_frame_result_s* opal_eval_frame_set_s_run( const opal_eval_frame_set_s* o, opal_eval_frame_result_s* result )
{
    BFOR_EACH( i, &o->arr )
    {
        BLM_INIT();
        opal_eval_frame* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
        opal_eval_frame_a_set_param( eval, &o->param );
        opal_eval_frame_a_run( eval, result );
        if( result->error )
        {
            st_s_copy_fa( &result->msg, "At set entry #<sz_t>:\n#<st_s*>", i, BLM_CLONE( st_s, &result->msg ) );
            BLM_RETURNV( opal_eval_frame_result_s*, result );
        }
        BLM_DOWN();
    };
    return result;
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_plain_s )
"aware opal_eval_frame"
"{"
    "opal_eval_frame_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "sz_t ap_cycles = 1;"
"}";

er_t opal_eval_frame_plain_s_main( opal_eval_frame_plain_s* o, bcore_main_frame_s* frame )
{
    BLM_INIT();
    opal_eval_frame_result_s_resolve( opal_eval_frame_plain_s_run( o, BLM_CREATE( opal_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( opal_eval_frame_cyclic_s )
"aware opal_eval_frame"
"{"
    "opal_eval_frame_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

er_t opal_eval_frame_cyclic_s_main( opal_eval_frame_cyclic_s* o, bcore_main_frame_s* frame )
{
    BLM_INIT();
    opal_eval_frame_result_s_resolve( opal_eval_frame_cyclic_s_run( o, BLM_CREATE( opal_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_SPECT( bcore_inst, opal_eval_frame )
"{"
    "bcore_spect_header_s header;"
    "feature aware opal_eval_frame : run;"
    "feature aware opal_eval_frame : set_param;"
"}";

/**********************************************************************************************************************/
// source: opal_adaptive.h
#include "opal_adaptive.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_adaptive

BCORE_DEFINE_OBJECT_INST_P( opal_adaptive_s )
"aware bhpt_adaptive"
"{"
    "aware => src;"
    "opal_frame_s frame;"
    "bhvm_holor_s holor_frame_en;"
    "bhvm_holor_s holor_frame_ex;"
    "func ^:get_format_en;"
    "func ^:get_format_ex;"
    "func ^:axon_pass;"
    "func ^:dendrite_pass;"
    "func ^:cyclic_reset;"
    "func ^:get_adaptor_probe;"
    "func ^:rebind_holors;"
    "func ^:status_to_sink;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_adaptive_builder_s )
"aware bhpt_builder"
"{"
    "aware => src;"
    "bhvm_holor_s holor_frame_en;"
    "bhvm_holor_s holor_frame_ex;"
    "func ^:set_format_en;"
    "func ^:set_format_ex;"
    "func ^:create_adaptive;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_adaptive_cyclic_s )
"aware bhpt_adaptive"
"{"
    "aware => src;"
    "opal_frame_cyclic_s frame;"
    "bhvm_holor_s holor_frame_en;"
    "bhvm_holor_s holor_frame_ex;"
    "bhvm_holor_adl_s => dp_buffer;"
    "bl_t dp_value;"
    "func ^:get_format_en;"
    "func ^:get_format_ex;"
    "func ^:axon_pass;"
    "func ^:dendrite_pass;"
    "func ^:cyclic_reset;"
    "func ^:get_adaptor_probe;"
    "func ^:rebind_holors;"
    "func ^:status_to_sink;"
"}";

BCORE_DEFINE_OBJECT_INST_P( opal_adaptive_cyclic_builder_s )
"aware bhpt_builder"
"{"
    "aware => src;"
    "bhvm_holor_s holor_frame_en;"
    "bhvm_holor_s holor_frame_ex;"
    "sz_t unroll_size;"
    "func ^:set_format_en;"
    "func ^:set_format_ex;"
    "func ^:create_adaptive;"
"}";

/**********************************************************************************************************************/
// source: opal_adaptor.h
#include "opal_adaptor.h"

//----------------------------------------------------------------------------------------------------------------------
// group: opal_adaptor

BCORE_DEFINE_OBJECT_INST_P( opal_adaptor_frame_s )
"aware bhpt_adaptor"
"{"
    "aware => src;"
    "hidden opal_frame_s => frame;"
    "func ^:reset;"
    "func ^:adapt;"
"}";

/**********************************************************************************************************************/


vd_t opal_xoila_out_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "opal_xoila_out" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: opal_context.h

            // group: opal_context
            BCORE_REGISTER_FEATURE( opal_context_get_prsg );
            BCORE_REGISTER_FFUNC( opal_context_get_prsg, opal_context_get_prsg__ );
            BCORE_REGISTER_FEATURE( opal_context_nameof );
            BCORE_REGISTER_FFUNC( opal_context_nameof, opal_context_nameof__ );
            BCORE_REGISTER_FEATURE( opal_context_ifnameof );
            BCORE_REGISTER_FFUNC( opal_context_ifnameof, opal_context_ifnameof__ );
            BCORE_REGISTER_FEATURE( opal_context_typeof );
            BCORE_REGISTER_FFUNC( opal_context_typeof, opal_context_typeof__ );
            BCORE_REGISTER_FEATURE( opal_context_entypeof );
            BCORE_REGISTER_FFUNC( opal_context_entypeof, opal_context_entypeof__ );
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
            BCORE_REGISTER_FFUNC( opal_context_get_prsg, opal_nop_context_s_get_prsg );
            BCORE_REGISTER_OBJECT( opal_nop_context_s );
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
            BCORE_REGISTER_FFUNC( opal_nop_solve_node, opal_nop_solve_node__ );
            BCORE_REGISTER_FEATURE( opal_nop_is_param );
            BCORE_REGISTER_FFUNC( opal_nop_is_param, opal_nop_is_param__ );
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
            BCORE_REGISTER_FFUNC( opal_nop_is_param, opal_nop_ar0_param_s_is_param );
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
            BCORE_REGISTER_FFUNC( opal_nop_arity, opal_nop_ar1_param_s_arity );
            BCORE_REGISTER_FFUNC( opal_nop_reserved, opal_nop_ar1_param_s_reserved );
            BCORE_REGISTER_FFUNC( opal_nop_priority, opal_nop_ar1_param_s_priority );
            BCORE_REGISTER_FFUNC( opal_nop_solve, opal_nop_ar1_param_s_solve );
            BCORE_REGISTER_FFUNC( opal_nop_settle, opal_nop_ar1_param_s_settle );
            BCORE_REGISTER_OBJECT( opal_nop_ar1_param_s );
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
            bcore_inst_s_get_typed( TYPEOF_opal_nop_ar1_param_s );
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
            BCORE_REGISTER_FFUNC( opal_nop_solve_node, opal_nop_ar2_cyclic_s_solve_node );
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
            BCORE_REGISTER_FFUNC( opal_nop_solve_node, opal_nop_ar2_reshape_s_solve_node );
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

            // --------------------------------------------------------------------
            // source: opal_sem.h

            // group: opal_sem
            BCORE_REGISTER_NAME( cell );
            BCORE_REGISTER_FEATURE( opal_sem_get_name );
            BCORE_REGISTER_FFUNC( opal_sem_get_name, opal_sem_get_name__ );
            BCORE_REGISTER_FEATURE( opal_sem_is_visible );
            BCORE_REGISTER_FFUNC( opal_sem_is_visible, opal_sem_is_visible__ );
            BCORE_REGISTER_FEATURE( opal_sem_set_name_visible );
            BCORE_REGISTER_FEATURE( opal_sem_set_name_invisible );
            BCORE_REGISTER_FFUNC( opal_sem_get_name, opal_sem_link_s_get_name );
            BCORE_REGISTER_FFUNC( opal_sem_set_name_visible, opal_sem_link_s_set_name_visible );
            BCORE_REGISTER_FFUNC( opal_sem_set_name_invisible, opal_sem_link_s_set_name_invisible );
            BCORE_REGISTER_FFUNC( opal_sem_is_visible, opal_sem_link_s_is_visible );
            BCORE_REGISTER_OBJECT( opal_sem_link_s );
            BCORE_REGISTER_OBJECT( opal_sem_links_s );
            BCORE_REGISTER_OBJECT( opal_sem_body_s );
            BCORE_REGISTER_FFUNC( opal_sem_get_name, opal_sem_cell_s_get_name );
            BCORE_REGISTER_FFUNC( opal_sem_set_name_visible, opal_sem_cell_s_set_name_visible );
            BCORE_REGISTER_FFUNC( opal_sem_set_name_invisible, opal_sem_cell_s_set_name_invisible );
            BCORE_REGISTER_FFUNC( opal_sem_is_visible, opal_sem_cell_s_is_visible );
            BCORE_REGISTER_OBJECT( opal_sem_cell_s );
            BCORE_REGISTER_OBJECT( opal_sem_stack_flag_s );
            BCORE_REGISTER_SPECT( opal_sem );

            // group: opal_sem_context
            BCORE_REGISTER_FFUNC( opal_context_get_prsg, opal_sem_context_s_get_prsg );
            BCORE_REGISTER_FFUNC( opal_context_nameof, opal_sem_context_s_nameof );
            BCORE_REGISTER_FFUNC( opal_context_ifnameof, opal_sem_context_s_ifnameof );
            BCORE_REGISTER_FFUNC( opal_context_typeof, opal_sem_context_s_typeof );
            BCORE_REGISTER_FFUNC( opal_context_entypeof, opal_sem_context_s_entypeof );
            BCORE_REGISTER_OBJECT( opal_sem_context_s );
            BCORE_REGISTER_TRAIT( opal_sem_context, opal_context );

            // group: opal_sem_id
            BCORE_REGISTER_OBJECT( opal_sem_id_s );
            BCORE_REGISTER_TRAIT( opal_sem_id, opal_sem );

            // group: opal_sem_builder
            BCORE_REGISTER_OBJECT( opal_sem_builder_s );
            BCORE_REGISTER_TRAIT( opal_sem_builder, opal_sem );

            // group: opal_sem_tree
            BCORE_REGISTER_OBJECT( opal_sem_tree_node_s );
            BCORE_REGISTER_OBJECT( opal_sem_tree_s );
            BCORE_REGISTER_TRAIT( opal_sem_tree, opal_sem );

            // --------------------------------------------------------------------
            // source: opal_net.h

            // group: opal_net
            BCORE_REGISTER_OBJECT( opal_net_link_s );
            BCORE_REGISTER_OBJECT( opal_net_links_s );
            BCORE_REGISTER_FEATURE( opal_net_is_cyclic );
            BCORE_REGISTER_FFUNC( opal_net_is_cyclic, opal_net_is_cyclic__ );
            BCORE_REGISTER_FFUNC( opal_net_is_cyclic, opal_net_node_s_is_cyclic );
            BCORE_REGISTER_OBJECT( opal_net_node_s );
            BCORE_REGISTER_OBJECT( opal_net_node_adl_s );
            BCORE_REGISTER_OBJECT( opal_net_nodes_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, opal_net_cell_s_copy_x );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, opal_net_cell_s_mutated );
            BCORE_REGISTER_OBJECT( opal_net_cell_s );
            BCORE_REGISTER_SPECT( opal_net );

            // group: opal_net_builder
            BCORE_REGISTER_OBJECT( opal_net_builder_s );
            BCORE_REGISTER_TRAIT( opal_net_builder, opal_net );

            // --------------------------------------------------------------------
            // source: opal_frame.h

            // group: opal_frame
            BCORE_REGISTER_FFUNC( bcore_via_call_shelve, opal_frame_s_shelve );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, opal_frame_s_mutated );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, opal_frame_s_copy_x );
            BCORE_REGISTER_OBJECT( opal_frame_s );
            BCORE_REGISTER_OBJECT( opal_frame_custom_hmeta_s );
            BCORE_REGISTER_FFUNC( bcore_via_call_shelve, opal_frame_cyclic_s_shelve );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, opal_frame_cyclic_s_mutated );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, opal_frame_cyclic_s_copy_x );
            BCORE_REGISTER_OBJECT( opal_frame_cyclic_s );
            BCORE_REGISTER_TRAIT( opal_frame, bcore_inst );

            // group: opal_frame_hidx
            BCORE_REGISTER_OBJECT( opal_frame_hidx_s );
            BCORE_REGISTER_OBJECT( opal_frame_hidx_ads_s );
            BCORE_REGISTER_TRAIT( opal_frame_hidx, opal_frame );

            // --------------------------------------------------------------------
            // source: opal_eval_frame.h

            // group: opal_eval_frame
            BCORE_REGISTER_OBJECT( opal_eval_frame_result_s );
            BCORE_REGISTER_FEATURE( opal_eval_frame_run );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, opal_eval_frame_param_s_init_x );
            BCORE_REGISTER_OBJECT( opal_eval_frame_param_s );
            BCORE_REGISTER_FFUNC( opal_eval_frame_set_param, opal_eval_frame_show_param_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_frame_show_param_s_main );
            BCORE_REGISTER_FFUNC( opal_eval_frame_run, opal_eval_frame_show_param_s_run );
            BCORE_REGISTER_OBJECT( opal_eval_frame_show_param_s );
            BCORE_REGISTER_FEATURE( opal_eval_frame_set_param );
            BCORE_REGISTER_OBJECT( opal_eval_frame_arr_s );
            BCORE_REGISTER_FFUNC( opal_eval_frame_set_param, opal_eval_frame_set_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_frame_set_s_main );
            BCORE_REGISTER_FFUNC( opal_eval_frame_run, opal_eval_frame_set_s_run );
            BCORE_REGISTER_OBJECT( opal_eval_frame_set_s );
            BCORE_REGISTER_FFUNC( opal_eval_frame_run, opal_eval_frame_plain_s_run );
            BCORE_REGISTER_FFUNC( opal_eval_frame_set_param, opal_eval_frame_plain_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_frame_plain_s_main );
            BCORE_REGISTER_OBJECT( opal_eval_frame_plain_s );
            BCORE_REGISTER_FFUNC( opal_eval_frame_run, opal_eval_frame_cyclic_s_run );
            BCORE_REGISTER_FFUNC( opal_eval_frame_set_param, opal_eval_frame_cyclic_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, opal_eval_frame_cyclic_s_main );
            BCORE_REGISTER_OBJECT( opal_eval_frame_cyclic_s );
            BCORE_REGISTER_SPECT( opal_eval_frame );

            // --------------------------------------------------------------------
            // source: opal_adaptive.h

            // group: opal_adaptive
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_en, opal_adaptive_s_get_format_en );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_ex, opal_adaptive_s_get_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_axon_pass, opal_adaptive_s_axon_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_dendrite_pass, opal_adaptive_s_dendrite_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_cyclic_reset, opal_adaptive_s_cyclic_reset );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_adaptor_probe, opal_adaptive_s_get_adaptor_probe );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_rebind_holors, opal_adaptive_s_rebind_holors );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_status_to_sink, opal_adaptive_s_status_to_sink );
            BCORE_REGISTER_OBJECT( opal_adaptive_s );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_en, opal_adaptive_builder_s_set_format_en );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_ex, opal_adaptive_builder_s_set_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_builder_create_adaptive, opal_adaptive_builder_s_create_adaptive );
            BCORE_REGISTER_OBJECT( opal_adaptive_builder_s );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_en, opal_adaptive_cyclic_s_get_format_en );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_ex, opal_adaptive_cyclic_s_get_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_axon_pass, opal_adaptive_cyclic_s_axon_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_dendrite_pass, opal_adaptive_cyclic_s_dendrite_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_cyclic_reset, opal_adaptive_cyclic_s_cyclic_reset );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_adaptor_probe, opal_adaptive_cyclic_s_get_adaptor_probe );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_rebind_holors, opal_adaptive_cyclic_s_rebind_holors );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_status_to_sink, opal_adaptive_cyclic_s_status_to_sink );
            BCORE_REGISTER_OBJECT( opal_adaptive_cyclic_s );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_en, opal_adaptive_cyclic_builder_s_set_format_en );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_ex, opal_adaptive_cyclic_builder_s_set_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_builder_create_adaptive, opal_adaptive_cyclic_builder_s_create_adaptive );
            BCORE_REGISTER_OBJECT( opal_adaptive_cyclic_builder_s );
            BCORE_REGISTER_TRAIT( opal_adaptive, bcore_inst );

            // --------------------------------------------------------------------
            // source: opal_adaptor.h

            // group: opal_adaptor
            BCORE_REGISTER_FFUNC( bhpt_adaptor_reset, opal_adaptor_frame_s_reset );
            BCORE_REGISTER_FFUNC( bhpt_adaptor_adapt, opal_adaptor_frame_s_adapt );
            BCORE_REGISTER_OBJECT( opal_adaptor_frame_s );
            BCORE_REGISTER_TRAIT( opal_adaptor, bcore_inst );
        }
        break;
        default: break;
    }
    return NULL;
}
// BETH_PLANT_SIGNATURE 4178678366
