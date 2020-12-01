/** This file was generated from xoila source code.
 *  Compiling Agent : xoico_compiler (C) 2020 J.B.Steffens
 *  Last File Update: 2020-12-01T10:47:49Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying xoila source code.
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

#include "lion.xo.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: lion_root.h
#include "lion_root.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion

BCORE_DEFINE_OBJECT_INST_P( lion_hmeta_s )
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

BCORE_DEFINE_OBJECT_INST_P( lion_holor_s )
"aware lion"
"{"
    "lion_hmeta_s m;"
    "bhvm_holor_s h;"
    "func bcore_fp:copy_typed;"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: lion_nop.h
#include "lion_nop.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop

BCORE_DEFINE_OBJECT_INST_P( lion_nop_solve_result_s )
"aware bcore_inst"
"{"
    "lion_holor_s => h;"
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

BCORE_DEFINE_OBJECT_INST_P( lion_nop_context_s )
"aware bcore_inst"
"{"
    "hidden bcore_mutex_s randomizer_mutex;"
    "bl_t randomizer_is_locked = false;"
    "u3_t randomizer_rval = 0;"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion_nop )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_nop : arity = lion_nop_arity_default;"
    "feature aware lion_nop : priority = lion_nop_priority_default;"
    "feature aware lion_nop : symbol = lion_nop_symbol_default;"
    "feature aware lion_nop : reserved = lion_nop_reserved_default;"
    "feature aware lion_nop : create_op_of_arn = lion_nop_create_op_of_arn_default;"
    "feature aware lion_nop : eci = lion_nop_eci_default;"
    "feature aware lion_nop : solve = lion_nop_solve__;"
    "feature aware lion_nop : solve_node = lion_nop_solve_node__;"
    "feature aware lion_nop : is_cyclic = lion_nop_is_cyclic_default;"
    "feature aware lion_nop : is_adaptive = lion_nop_is_adaptive_default;"
    "feature aware lion_nop : settle = lion_nop_settle_default;"
    "feature aware lion_nop : type_vop_ap;"
    "feature aware lion_nop : type_vop_dp_a;"
    "feature aware lion_nop : type_vop_dp_b;"
    "feature aware lion_nop : type_vop_dp_c;"
    "feature aware lion_nop : mcode_push_ap_holor = lion_nop_mcode_push_ap_holor_default;"
    "feature aware lion_nop : mcode_push_dp_holor = lion_nop_mcode_push_dp_holor_default;"
    "feature aware lion_nop : mcode_push_ap_track = lion_nop_mcode_push_ap_track_default;"
    "feature aware lion_nop : mcode_push_dp_track = lion_nop_mcode_push_dp_track_default;"
"}";

void lion_nop_settle_default( const lion_nop* o, const lion_nop_solve_result_s* result, lion_nop** out_nop, lion_nop_solve_result_s** out_result )
{
    // lion_nop.h:164:1
    
    lion_nop_ar0_literal_s* literal = lion_nop_ar0_literal_s_create();
    literal->h = lion_holor_s_clone( result->h );
    lion_nop_solve_result_s* r = lion_nop_solve_result_s_create();
    r->h = bcore_fork( literal->h );
    lion_nop_solve_result_s_attach( out_result, r );
    lion_nop_a_attach( out_nop, (lion_nop*)literal );
}

sz_t lion_nop_mcode_push_ap_holor_default( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:185:1
    
    bhvm_holor_s* h = &result->h->h;
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf,h, ( bhvm_mcode_hmeta* )m );
    if( m->active )
    {
        bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ),0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),0, idx ) );
    }
    return  idx;
}

sz_t lion_nop_mcode_push_dp_holor_default( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:206:1
    
    BLM_INIT();
    
    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf,h, ( bhvm_mcode_hmeta* )m );
    
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_dp_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ),0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_dp,        bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ),0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_dp_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),0, idx ) );
    
    BLM_RETURNV( sz_t, idx );
}

void lion_nop_mcode_push_ap_track_default( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:223:1
    
    tp_t type = ( lion_nop_a_defines_type_vop_ap( o ) ) ? lion_nop_a_type_vop_ap( o ) : result->type_vop_ap;
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf,TYPEOF_track_ap, bhvm_vop_t_create( type ), arr_ci );
}

void lion_nop_mcode_push_dp_track_default( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:231:1
    
    if( ch_id >= lion_nop_a_arity( o ) + 'a' ) ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    tp_t type = 0;
    switch( ch_id )
    {
        case 'a': type = ( lion_nop_a_defines_type_vop_dp_a( o ) ) ? lion_nop_a_type_vop_dp_a( o ) : result->type_vop_dp_a; break;
        case 'b': type = ( lion_nop_a_defines_type_vop_dp_b( o ) ) ? lion_nop_a_type_vop_dp_b( o ) : result->type_vop_dp_b; break;
        case 'c': type = ( lion_nop_a_defines_type_vop_dp_c( o ) ) ? lion_nop_a_type_vop_dp_c( o ) : result->type_vop_dp_c; break;
        default: ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    }
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf,TYPEOF_track_dp, bhvm_vop_t_create( type ), arr_ci );
}

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar0

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_literal_s )
"aware lion_nop_ar0"
"{"
    "lion_holor_s -> h;"
    "func lion_nop:arity;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_literal_s_solve( const lion_nop_ar0_literal_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:271:9
    
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = true;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_param_s )
"aware lion_nop_ar0"
"{"
    "lion_holor_s -> h;"
    "func lion_nop:arity;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_param_s_solve( const lion_nop_ar0_param_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:283:9
    
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_adaptive_s )
"aware lion_nop_ar0"
"{"
    "lion_holor_s -> h;"
    "func lion_nop:arity;"
    "func lion_nop:is_adaptive;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_ap_holor;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

bl_t lion_nop_ar0_adaptive_s_solve( const lion_nop_ar0_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:298:9
    
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    return  true;
}

sz_t lion_nop_ar0_adaptive_s_mcode_push_ap_holor( const lion_nop_ar0_adaptive_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:305:9
    
    bhvm_holor_s* h = &result->h->h;
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf,h, ( bhvm_mcode_hmeta* )m );
    if( result->h->h.v.size == 0 ) // randomize holor if result is vacant
    {
        bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ),0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_randomize_s_create() ),0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),0, idx ) );
    }
    return  idx;
}

sz_t lion_nop_ar0_adaptive_s_mcode_push_dp_holor( const lion_nop_ar0_adaptive_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:319:9
    
    BLM_INIT();
    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf,h, ( bhvm_mcode_hmeta* )m );
    
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_dp_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ),0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_dp_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_dp_adaptive_zero_grad,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ),0, idx ) );
    BLM_RETURNV( sz_t, idx );
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_rand_s )
"aware lion_nop_ar0"
"{"
    "lion_holor_s -> h;"
    "f3_t min = -0.5;"
    "f3_t max = 0.5;"
    "f3_t density = 1.0;"
    "u3_t rval = 7384;"
    "func lion_nop:arity;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_ap_holor;"
"}";

bl_t lion_nop_ar0_rand_s_solve( const lion_nop_ar0_rand_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:343:9
    
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    return  true;
}

sz_t lion_nop_ar0_rand_s_mcode_push_ap_holor( const lion_nop_ar0_rand_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    // lion_nop.h:350:9
    
    bhvm_holor_s* h = &result->h->h;
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf,h, ( bhvm_mcode_hmeta* )m );
    
    bhvm_vop_ar0_rand_s* vop_rand = bhvm_vop_ar0_rand_s_create();
    vop_rand->rval = o->rval;
    vop_rand->min = o->min;
    vop_rand->max = o->max;
    vop_rand->density = o->density;
    
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap,        bhvm_vop_a_set_index( ( ( bhvm_vop* )vop_rand ),0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_setup,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ),0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf,TYPEOF_track_ap_shelve, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),0, idx ) );
    
    return  idx;
}

XOILA_DEFINE_SPECT( lion_nop, lion_nop_ar0 )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar1

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_identity_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_identity_s_solve( const lion_nop_ar1_identity_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:384:9
    
    lion_holor_s_attach( &result->h, lion_holor_s_create() );
    bhvm_holor_s_fork_from( &result->h->h, &a[0]->h );
    result->h->m.htp = a[0]->m.htp;
    result->h->m.active = a[0]->m.active;
    result->settled = (result->h) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_f3_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_f3_s_solve( const lion_nop_ar1_f3_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:401:9
    
    lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
    bhvm_holor_s_set_type( &result->h->h, TYPEOF_f3_t );
    result->settled = ( result->h ) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_f2_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_f2_s_solve( const lion_nop_ar1_f2_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:416:9
    
    lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
    bhvm_holor_s_set_type( &result->h->h, TYPEOF_f2_t );
    result->settled = ( result->h ) && !result->h->m.active;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_cpy_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_acc_s;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_neg_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:create_op_of_arn;"
"}";

lion_nop* lion_nop_ar1_neg_s_create_op_of_arn( const lion_nop_ar1_neg_s* o, sz_t n )
{
    // lion_nop.h:433:9
    
    return  ( n == 2 ) ? (lion_nop*)lion_nop_ar2_sub_s_create()
         : ( n == 1 ) ? (lion_nop*)lion_nop_ar1_neg_s_clone( o )
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_floor_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_ceil_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_abs_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_exp_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_log_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_inv_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_sqr_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_srt_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_sigm_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_sigm_hard_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_sigm_leaky_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_tanh_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_tanh_hard_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_tanh_leaky_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_softplus_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_softmax_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_relu_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_relu_leaky_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_output_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_adaptive_s )
"aware lion_nop_ar1"
"{"
    "tp_t name;"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:is_adaptive;"
    "func lion_nop:solve;"
    "func lion_nop:settle;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_dimof_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_dimof_s_solve( const lion_nop_ar1_dimof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:612:9
    
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_create() );
        bhvm_holor_s_set_scalar_f3( &result->h->h, a[0]->h.s.size ? a[0]->h.s.data[ a[0]->h.s.size - 1 ] : 1 );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_volof_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_volof_s_solve( const lion_nop_ar1_volof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:631:9
    
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_create() );
        bhvm_holor_s_set_scalar_f3( &result->h->h, bhvm_shape_s_get_volume( &a[0]->h.s ) );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_constof_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_constof_s_solve( const lion_nop_ar1_constof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:653:9
    
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
        if( result->h->h.v.size == 0 ) bhvm_holor_s_fit_size( &result->h->h );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_zeroof_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_zeroof_s_solve( const lion_nop_ar1_zeroof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:672:9
    
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
        if( result->h->h.v.size == 0 ) bhvm_holor_s_fit_size( &result->h->h );
        bhvm_value_s_zro( &result->h->h.v );
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_shapeof_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_shapeof_s_solve( const lion_nop_ar1_shapeof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:692:9
    
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_create() );
        bhvm_shape_s_copy( &result->h->h.s,&a[0]->h.s );
        bhvm_value_s_set_type( &result->h->h.v, a[0]->h.v.type );
        result->h->m.htp = &a[0]->m.htp;
        result->h->m.active = false;
        result->settled = true;
    }
    result->codable = false;
    return  true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_rand_s )
"aware lion_nop_ar1"
"{"
    "u3_t rseed = 1234;"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
    "func lion_nop:settle;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_cast_htp_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_ap_holor;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_reshape_s )
"aware lion_nop_ar1"
"{"
    "bhvm_shape_s shape;"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_ap_holor;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

XOILA_DEFINE_SPECT( lion_nop, lion_nop_ar1 )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar2

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_add_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_sub_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
    "func lion_nop:create_op_of_arn;"
"}";

lion_nop* lion_nop_ar2_sub_s_create_op_of_arn( const lion_nop_ar2_sub_s* o, sz_t n )
{
    // lion_nop.h:775:9
    
    return  ( n == 2 ) ? (lion_nop*)lion_nop_ar2_sub_s_clone( o )
         : ( n == 1 ) ? (lion_nop*)lion_nop_ar1_neg_s_create()
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_mul_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_div_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_pow_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_bmul_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_equal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_unequal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_larger_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_smaller_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_larger_equal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_smaller_equal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_and_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_or_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_cat_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_ccat_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_order_inc_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_ap_track;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_order_dec_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
    "func lion_nop:mcode_push_ap_holor;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_cyclic_s )
"aware lion_nop_ar2"
"{"
    "tp_t name;"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:is_cyclic;"
    "func lion_nop:solve;"
    "func lion_nop:solve_node;"
    "func lion_nop:mcode_push_ap_track;"
    "func lion_nop:mcode_push_dp_track;"
    "func lion_nop:mcode_push_dp_holor;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_rands_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
    "func lion_nop:settle;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_reshape_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
    "func lion_nop:solve_node;"
"}";

bl_t lion_nop_ar2_reshape_s_solve( const lion_nop_ar2_reshape_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    // lion_nop.h:974:9
    
    ERR_fa( "This function should never be called from feature 'solve_node'." );
    return  false;
}

XOILA_DEFINE_SPECT( lion_nop, lion_nop_ar2 )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar3

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar3_iff_s )
"aware lion_nop_ar3"
"{"
    "func lion_nop:arity;"
    "func lion_nop:reserved;"
    "func lion_nop:priority;"
    "func lion_nop:eci;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
    "func lion_nop:type_vop_dp_c;"
"}";

XOILA_DEFINE_SPECT( lion_nop, lion_nop_ar3 )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: lion_eval_nop.h
#include "lion_eval_nop.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_eval_nop

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_result_s )
"aware bcore_inst"
"{"
    "sz_t total_tests = 0;"
    "sz_t solvable_tests = 0;"
    "sz_t tolerated_errors = 0;"
    "bl_t error = false;"
    "st_s msg;"
"}";

void lion_eval_nop_result_s_resolve( const lion_eval_nop_result_s* o )
{
    // lion_eval_nop.h:49:5
    
    if( !o ) return ;
    if( o->error )
    {
        bcore_sink_a_push_fa( BCORE_STDERR,"#<sc_t>\n", o->msg.sc );
    }
    else if( o->msg.size > 0 )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT,"#<sc_t>\n", o->msg.sc );
    }
    if( o->total_tests > 0 )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT,"Total tests ...... #<sz_t>\n", o->total_tests );
        bcore_sink_a_push_fa( BCORE_STDOUT,"Solvable tests ... #<sz_t> (#<sz_t>%)\n", o->solvable_tests, ( o->solvable_tests * 100 ) / o->total_tests );
        bcore_sink_a_push_fa( BCORE_STDOUT,"Tolerated errors . #<sz_t>\n", o->tolerated_errors );
    }
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_param_s )
"aware bcore_inst"
"{"
    "aware lion_nop => nop;"
    "lion_holor_s => ha;"
    "lion_holor_s => hb;"
    "lion_holor_s => hc;"
    "lion_holor_s => hr;"
    "hidden aware bcore_sink -> log;"
    "sz_t verbosity = 1;"
    "u3_t rval = 1234;"
    "func bcore_inst_call:init_x;"
"}";

void lion_eval_nop_param_s_set( lion_eval_nop_param_s* o, const lion_eval_nop_param_s* src )
{
    // lion_eval_nop.h:83:5
    
    o->verbosity = sz_max( o->verbosity, src->verbosity );
    o->rval      = bcore_lcg00_u3( o->rval + src->rval );
    bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
    if( !o->ha  ) o->ha  = lion_holor_s_clone( src->ha );
    if( !o->hb  ) o->hb  = lion_holor_s_clone( src->hb );
    if( !o->hc  ) o->hc  = lion_holor_s_clone( src->hc );
    if( !o->hr  ) o->hr  = lion_holor_s_clone( src->hr );
    if( !o->nop ) o->nop = lion_nop_a_clone( src->nop );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_generator_s )
"aware lion_eval_nop"
"{"
    "lion_eval_nop_param_s param;"
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
    "aware lion_eval_nop=> eval;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

er_t lion_eval_nop_generator_s_main( lion_eval_nop_generator_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_nop.h:107:5
    
    BLM_INIT();
    lion_eval_nop_result_s_resolve( lion_eval_nop_generator_s_run( o,BLM_CREATE( lion_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_show_param_s )
"aware lion_eval_nop"
"{"
    "lion_eval_nop_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

er_t lion_eval_nop_show_param_s_main( lion_eval_nop_show_param_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_nop.h:107:5
    
    BLM_INIT();
    lion_eval_nop_result_s_resolve( lion_eval_nop_show_param_s_run( o,BLM_CREATE( lion_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_arr_s )
"aware bcore_array"
"{"
    "aware lion_eval_nop=> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_set_s )
"aware lion_eval_nop"
"{"
    "lion_eval_nop_param_s param;"
    "lion_eval_nop_arr_s arr;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

er_t lion_eval_nop_set_s_main( lion_eval_nop_set_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_nop.h:107:5
    
    BLM_INIT();
    lion_eval_nop_result_s_resolve( lion_eval_nop_set_s_run( o,BLM_CREATE( lion_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

lion_eval_nop_result_s* lion_eval_nop_set_s_run( const lion_eval_nop_set_s* o, lion_eval_nop_result_s* result )
{
    // lion_eval_nop.h:147:5
    
    BFOR_EACH( i, &o->arr )
    {
        BLM_INIT();
        lion_eval_nop* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
        lion_eval_nop_a_set_param( eval,&o->param );
        lion_eval_nop_a_run( eval,result );
        if( result->error )
        {
            st_s* s = BLM_A_PUSH( st_s_clone( &result->msg ) );
            st_s_copy_fa( &result->msg,"At set entry #<sz_t>:\n#<st_s*>", i, s );
            BLM_RETURNV( lion_eval_nop_result_s*, result );
        }
        BLM_DOWN();
    }
    return  result;
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_ar1_s )
"aware lion_eval_nop"
"{"
    "lion_eval_nop_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

er_t lion_eval_nop_ar1_s_main( lion_eval_nop_ar1_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_nop.h:107:5
    
    BLM_INIT();
    lion_eval_nop_result_s_resolve( lion_eval_nop_ar1_s_run( o,BLM_CREATE( lion_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_nop_ar2_s )
"aware lion_eval_nop"
"{"
    "lion_eval_nop_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

er_t lion_eval_nop_ar2_s_main( lion_eval_nop_ar2_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_nop.h:107:5
    
    BLM_INIT();
    lion_eval_nop_result_s_resolve( lion_eval_nop_ar2_s_run( o,BLM_CREATE( lion_eval_nop_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

XOILA_DEFINE_SPECT( bcore_inst, lion_eval_nop )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_eval_nop : set_param;"
    "feature aware lion_eval_nop : run;"
"}";

/**********************************************************************************************************************/
// source: lion_sem.h
#include "lion_sem.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_sem

BCORE_DEFINE_OBJECT_INST_P( lion_sem_context_s )
"aware bcore_inst"
"{"
    "bcore_hmap_name_s hmap_name;"
    "bcore_arr_st_s arr_symbol_op2;"
    "lion_sem_cell_s => cell;"
    "bcore_hmap_tp_s control_types;"
    "bcore_hmap_tp_s reserved_names;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_sem_link_s )
"aware lion_sem"
"{"
    "tp_t name;"
    "bl_t visible = true;"
    "private lion_sem_link_s -> up;"
    "private lion_sem_link_s -> dn;"
    "private vd_t cell;"
    "bl_t exit;"
    "func ^:get_name;"
    "func ^:is_visible;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_sem_links_s )
"aware bcore_array"
"{"
    "lion_sem_link_s => [];"
"}";

lion_sem_link_s* lion_sem_links_s_get_link_by_name( lion_sem_links_s* o, tp_t name )
{
    // lion_sem.h:150:5
    
    BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return  o->data[ i ];
    return  NULL;
}

bl_t lion_sem_links_s_name_exists( const lion_sem_links_s* o, tp_t name )
{
    // lion_sem.h:156:5
    
    BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return  true;
    return  false;
}

lion_sem_link_s* lion_sem_links_s_get_link_by_up( lion_sem_links_s* o, lion_sem_link_s* up )
{
    // lion_sem.h:162:5
    
    BFOR_EACH( i, o ) if( o->data[ i ]->up == up ) return  o->data[ i ];
    return  NULL;
}

lion_sem_link_s* lion_sem_links_s_get_link_by_dn( lion_sem_links_s* o, lion_sem_link_s* dn )
{
    // lion_sem.h:168:5
    
    BFOR_EACH( i, o ) if( o->data[ i ]->dn == dn ) return  o->data[ i ];
    return  NULL;
}

sz_t lion_sem_links_s_get_index_by_link( lion_sem_links_s* o, lion_sem_link_s* link )
{
    // lion_sem.h:174:5
    
    BFOR_EACH( i, o ) if( o->data[ i ] == link ) return  i;
    return  -1;
}

sz_t lion_sem_links_s_count_open( const lion_sem_links_s* o )
{
    // lion_sem.h:180:5
    
    sz_t count = 0;
    BFOR_EACH( i, o ) count += ( o->data[ i ]->up == NULL );
    return  count;
}

BCORE_DEFINE_OBJECT_INST_P( lion_sem_body_s )
"aware bcore_array"
"{"
    "aware lion_sem=> [];"
"}";

bl_t lion_sem_body_s_name_exists( const lion_sem_body_s* o, tp_t name )
{
    // lion_sem.h:192:5
    
    BFOR_EACH( i, o ) if( lion_sem_a_get_name( o->data[ i ] ) == name ) return  true;
    return  false;
}

lion_sem* lion_sem_body_s_get_sem_by_name( lion_sem_body_s* o, tp_t name )
{
    // lion_sem.h:198:5
    
    BFOR_EACH( i, o )
    {
        if( lion_sem_a_get_name( o->data[ i ] ) == name ) return  o->data[ i ];
    }
    return  NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_sem_cell_s )
"aware lion_sem"
"{"
    "tp_t name;"
    "lion_sem_links_s encs;"
    "lion_sem_links_s excs;"
    "lion_sem_body_s => body;"
    "aware lion_nop -> nop;"
    "private lion_sem_cell_s -> wrapped_cell;"
    "sz_t priority = 10;"
    "private lion_sem_cell_s* parent;"
    "hidden bcore_source_point_s source_point;"
    "func ^:get_name;"
"}";

lion_sem_cell_s* lion_sem_cell_s_get_cell_by_name( lion_sem_cell_s* o, tp_t name )
{
    // lion_sem.h:244:5
    
    lion_sem* sem = o->body ? lion_sem_body_s_get_sem_by_name( o->body,name ) : NULL;
    if( sem && sem->_ == TYPEOF_lion_sem_cell_s ) return  ( lion_sem_cell_s* )sem;
    if( o->parent ) return  lion_sem_cell_s_get_cell_by_name( o->parent,name );
    return  NULL;
}

lion_sem_link_s* lion_sem_cell_s_get_link_by_name( lion_sem_cell_s* o, tp_t name )
{
    // lion_sem.h:253:5
    
    lion_sem* sem = o->body ? lion_sem_body_s_get_sem_by_name( o->body,name ) : NULL;
    if( sem && sem->_ == TYPEOF_lion_sem_link_s ) return  ( lion_sem_link_s* )sem;
    return  NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_sem_stack_flag_s )
"aware lion_sem"
"{"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion_sem )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_sem : get_name = lion_sem_get_name_default;"
    "feature aware lion_sem : is_visible = lion_sem_is_visible_default;"
"}";

/**********************************************************************************************************************/
// source: lion_net.h
#include "lion_net.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_ctr

BCORE_DEFINE_OBJECT_INST_P( lion_ctr_node_s )
"aware bcore_array"
"{"
    "sz_t id = -1;"
    "private lion_sem_cell_s -> cell;"
    "private lion_ctr_node_s -> parent;"
    "lion_ctr_node_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_ctr_tree_s )
"aware lion_ctr"
"{"
    "sz_t id_base = 0;"
    "lion_ctr_node_s => root;"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion_ctr )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: lion_net

BCORE_DEFINE_OBJECT_INST_P( lion_net_link_s )
"aware lion_net"
"{"
    "hidden vd_t node;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_net_links_s )
"aware bcore_array"
"{"
    "lion_net_link_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_net_node_s )
"aware lion_net"
"{"
    "lion_net_links_s upls;"
    "lion_net_links_s dnls;"
    "tp_t name;"
    "bl_t flag = false;"
    "bl_t probe = false;"
    "sz_t id;"
    "hidden bhvm_mcode_node_s -> mnode;"
    "aware lion_nop -> nop;"
    "lion_nop_solve_result_s => result;"
    "hidden bcore_source_point_s -> source_point;"
    "func ^:is_cyclic;"
"}";

sz_t lion_net_node_s_up_index( const lion_net_node_s* o, const lion_net_node_s* node )
{
    // lion_net.h:140:5
    
    BFOR_EACH( i, &o->upls ) if( o->upls.data[ i ]->node == node ) return  i;
    return  -1;
}

void lion_net_node_s_set_nop_d( lion_net_node_s* o, lion_nop* nop )
{
    // lion_net.h:146:5
    
    ASSERT( o->result == NULL );
    lion_nop_a_attach( &o->nop, nop );
}

BCORE_DEFINE_OBJECT_INST_P( lion_net_node_adl_s )
"aware bcore_array"
"{"
    "lion_net_node_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_net_nodes_s )
"aware bcore_array"
"{"
    "lion_net_node_s => [];"
"}";

lion_net_node_s* lion_net_nodes_s_get_by_id( lion_net_nodes_s* o, sz_t id )
{
    // lion_net.h:162:5
    
    BFOR_EACH( i, o ) if( o->data[ i ]->id == id ) return  o->data[ i ];
    return  NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_net_cell_s )
"aware lion_net"
"{"
    "sz_t max_depth = 32768;"
    "lion_net_nodes_s body;"
    "lion_net_nodes_s encs;"
    "lion_net_nodes_s excs;"
    "func bcore_inst_call:copy_x;"
    "func bcore_via_call:mutated;"
"}";

void lion_net_cell_s_clear_flags( lion_net_cell_s* o )
{
    // lion_net.h:188:5
    
    BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
}

void lion_net_cell_s_clear_all_flags( lion_net_cell_s* o )
{
    // lion_net.h:193:5
    
    BFOR_EACH( i, &o->body )
    {
        o->body.data[ i ]->flag = false;
        o->body.data[ i ]->probe = false;
    }
}

void lion_net_cell_s_clear_downlinks( lion_net_cell_s* o )
{
    // lion_net.h:204:5
    
    BFOR_EACH( i, &o->body ) lion_net_links_s_clear( &o->body.data[ i ]->dnls );
}

XOILA_DEFINE_SPECT( bcore_inst, lion_net )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_net : is_cyclic = lion_net_is_cyclic_default;"
"}";

/**********************************************************************************************************************/
// source: lion_frame.h
#include "lion_frame.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_frame

BCORE_DEFINE_OBJECT_INST_P( lion_frame_s )
"aware lion_frame"
"{"
    "aware bcore_sink -> log;"
    "bhvm_mcode_frame_s => mcf;"
    "bl_t is_cyclic;"
    "bl_t setup;"
    "sz_t size_en;"
    "sz_t size_ex;"
    "lion_frame_hidx_s hidx_en;"
    "lion_frame_hidx_s hidx_ex;"
    "lion_frame_hidx_s hidx_ada;"
    "func bcore_via_call:shelve;"
    "func bcore_via_call:mutated;"
    "func bcore_inst_call:copy_x;"
"}";

void lion_frame_s_reset( lion_frame_s* o )
{
    // lion_frame.h:158:5
    
    if( !o->setup ) return ;
    if( !o->mcf ) return ;
    bhvm_mcode_frame_s_track_run( o->mcf,TYPEOF_track_ap_shelve );
    bhvm_mcode_frame_s_track_run( o->mcf,TYPEOF_track_dp_shelve );
    o->setup = false;
}

lion_frame_s* lion_frame_s_bind_holors( lion_frame_s* o )
{
    // lion_frame.h:167:5
    
    bhvm_mcode_frame_s_track_run( o->mcf,TYPEOF_track_ap_setup );
    bhvm_mcode_frame_s_track_run( o->mcf,TYPEOF_track_dp_setup );
    return  o;
}

void lion_frame_s_setup( lion_frame_s* o )
{
    // lion_frame.h:174:5
    
    if( o->setup ) return ;
    if( !o->mcf ) return ;
    lion_frame_s_bind_holors( o );
    o->setup = true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_frame_custom_hmeta_s )
"aware lion_frame"
"{"
    "sz_t ur_slot;"
    "sz_t ur_src;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_frame_cyclic_s )
"aware lion_frame"
"{"
    "lion_frame_s => frame;"
    "sz_t unroll_size = 2;"
    "bl_t setup = false;"
    "sz_t unroll_index = 0;"
    "bhvm_mcode_track_adl_s => track_adl_ap;"
    "bhvm_mcode_track_adl_s => track_adl_dp;"
    "bhvm_mcode_track_adl_s => track_adl_ap_setup;"
    "lion_frame_hidx_ads_s hidx_ads_en;"
    "lion_frame_hidx_ads_s hidx_ads_ex;"
    "func bcore_via_call:shelve;"
    "func bcore_via_call:mutated;"
    "func bcore_inst_call:copy_x;"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion_frame )
"{"
    "bcore_spect_header_s header;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: lion_frame_hidx

BCORE_DEFINE_OBJECT_INST_P( lion_frame_hidx_s )
"aware lion_frame_hidx"
"{"
    "bcore_arr_sz_s => arr;"
"}";

sz_t lion_frame_hidx_s_get_pclass_idx( const lion_frame_hidx_s* o, const bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index )
{
    // lion_frame.h:69:9
    
    const bhvm_mcode_hmeta* hmeta = lion_frame_hidx_s_get_hmeta( o,hbase, index );
    if( hmeta ) return  bhvm_mcode_node_s_get_pclass_idx( bhvm_mcode_hmeta_a_get_node( hmeta ),pclass );
    return  -1;
}

lion_frame_hidx_s* lion_frame_hidx_s_replace_index( lion_frame_hidx_s* o, bcore_arr_sz_s* index_map )
{
    // lion_frame.h:79:9
    
    BFOR_EACH( i, o->arr )
    {
        sz_t old_index = o->arr->data[ i ];
        assert( old_index >= 0 && old_index < index_map->size );
        sz_t new_index = index_map->data[ old_index ];
        if( new_index >= 0 ) o->arr->data[ i ] = new_index;
    }
    return  o;
}

BCORE_DEFINE_OBJECT_INST_P( lion_frame_hidx_ads_s )
"aware bcore_array"
"{"
    "lion_frame_hidx_s [];"
"}";

XOILA_DEFINE_SPECT( lion_frame, lion_frame_hidx )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: lion_eval_frame.h
#include "lion_eval_frame.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_eval_frame

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_result_s )
"aware bcore_inst"
"{"
    "bl_t error = false;"
    "st_s msg;"
"}";

void lion_eval_frame_result_s_resolve( lion_eval_frame_result_s* o )
{
    // lion_eval_frame.h:46:5
    
    if( !o ) return ;
    if( o->error )
    {
        bcore_sink_a_push_fa( BCORE_STDERR,"#<sc_t>\n", o->msg.sc );
    }
    else if( o->msg.size > 0 )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT,"#<sc_t>\n", o->msg.sc );
    }
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_param_s )
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

void lion_eval_frame_param_s_set( lion_eval_frame_param_s* o, const lion_eval_frame_param_s* src )
{
    // lion_eval_frame.h:87:5
    
    o->recovery_test = o->recovery_test || src->recovery_test;
    o->jacobian_test = o->jacobian_test || src->jacobian_test;
    
    o->verbosity = sz_max( o->verbosity, src->verbosity );
    o->rval      = bcore_lcg00_u3( o->rval + src->rval );
    bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
    
    if( o->name.size == 0 )
    {
        st_s_copy( &o->name,&src->name );
    }
    else if( src->name.size > 0 )
    {
        st_s* new_name = st_s_create_fa("<sc_t>_<sc_t>", o->name.sc, src->name.sc );
        st_s_copy( &o->name,new_name );
        st_s_discard( new_name );
    }
    
    if( !o->src ) o->src = bcore_fork( src->src );
    if( !o->in  ) o->in  = bcore_fork( src->in );
    if( !o->out ) o->out = bcore_fork( src->out );
    
    o->max_dev = f3_max( o->max_dev, src->max_dev );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_show_param_s )
"aware lion_eval_frame"
"{"
    "lion_eval_frame_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

er_t lion_eval_frame_show_param_s_main( lion_eval_frame_show_param_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_frame.h:122:5
    
    BLM_INIT();
    lion_eval_frame_result_s_resolve( lion_eval_frame_show_param_s_run( o,BLM_CREATE( lion_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_arr_s )
"aware bcore_array"
"{"
    "aware lion_eval_frame=> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_set_s )
"aware lion_eval_frame"
"{"
    "lion_eval_frame_param_s param;"
    "lion_eval_frame_arr_s arr;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

er_t lion_eval_frame_set_s_main( lion_eval_frame_set_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_frame.h:122:5
    
    BLM_INIT();
    lion_eval_frame_result_s_resolve( lion_eval_frame_set_s_run( o,BLM_CREATE( lion_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

lion_eval_frame_result_s* lion_eval_frame_set_s_run( const lion_eval_frame_set_s* o, lion_eval_frame_result_s* result )
{
    // lion_eval_frame.h:146:5
    
    BFOR_EACH( i, &o->arr )
    {
        BLM_INIT();
        lion_eval_frame* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
        lion_eval_frame_a_set_param( eval,&o->param );
        lion_eval_frame_a_run( eval,result );
        if( result->error )
        {
            st_s_copy_fa( &result->msg,"At set entry #<sz_t>:\n#<st_s*>", i, BLM_CLONE( st_s, &result->msg ) );
            BLM_RETURNV( lion_eval_frame_result_s*, result );
        }
        BLM_DOWN();
    }
    return  result;
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_plain_s )
"aware lion_eval_frame"
"{"
    "lion_eval_frame_param_s param;"
    "sz_t ap_cycles = 1;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

er_t lion_eval_frame_plain_s_main( lion_eval_frame_plain_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_frame.h:122:5
    
    BLM_INIT();
    lion_eval_frame_result_s_resolve( lion_eval_frame_plain_s_run( o,BLM_CREATE( lion_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( lion_eval_frame_cyclic_s )
"aware lion_eval_frame"
"{"
    "lion_eval_frame_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

er_t lion_eval_frame_cyclic_s_main( lion_eval_frame_cyclic_s* o, bcore_main_frame_s* frame )
{
    // lion_eval_frame.h:122:5
    
    BLM_INIT();
    lion_eval_frame_result_s_resolve( lion_eval_frame_cyclic_s_run( o,BLM_CREATE( lion_eval_frame_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

XOILA_DEFINE_SPECT( bcore_inst, lion_eval_frame )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_eval_frame : run;"
    "feature aware lion_eval_frame : set_param;"
"}";

/**********************************************************************************************************************/
// source: lion_adaptive.h
#include "lion_adaptive.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_adaptive

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_s )
"aware badapt_adaptive"
"{"
    "aware => src;"
    "lion_frame_s frame;"
    "badapt_dynamics_std_s dynamics;"
    "sz_t in_size;"
    "sz_t out_size;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:get_dynamics_std;"
    "func ^:set_dynamics_std;"
    "func ^:arc_to_sink;"
    "func ^:minfer;"
    "func ^:bgrad_adapt;"
    "func ^:get_weights_min_max;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_builder_s )
"aware badapt_builder"
"{"
    "aware => src;"
    "sz_t in_size;"
    "sz_t out_size;"
    "badapt_dynamics_std_s dynamics;"
    "func ^:get_in_size;"
    "func ^:set_in_size;"
    "func ^:get_out_size;"
    "func ^:set_out_size;"
    "func ^:build;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_cyclic_s )
"aware badapt_adaptive"
"{"
    "aware => src;"
    "lion_frame_cyclic_s frame;"
    "badapt_dynamics_std_s dynamics;"
    "sz_t in_size;"
    "sz_t out_size;"
    "bhvm_holor_adl_s => dp_buffer;"
    "bl_t dp_value;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:get_dynamics_std;"
    "func ^:set_dynamics_std;"
    "func ^:arc_to_sink;"
    "func ^:minfer;"
    "func ^:bgrad_adapt;"
    "func ^:get_weights_min_max;"
    "func ^:reset;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_cyclic_builder_s )
"aware badapt_builder"
"{"
    "aware => src;"
    "sz_t in_size;"
    "sz_t out_size;"
    "sz_t unroll_size;"
    "badapt_dynamics_std_s dynamics;"
    "func ^:get_in_size;"
    "func ^:set_in_size;"
    "func ^:get_out_size;"
    "func ^:set_out_size;"
    "func ^:build;"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion_adaptive )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: lion_adaptor.h
#include "lion_adaptor.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_adaptor

BCORE_DEFINE_OBJECT_INST_P( lion_adaptor_frame_s )
"aware bhpt_adaptor"
"{"
    "aware => src;"
    "hidden lion_frame_s => frame;"
    "func ^:reset;"
    "func ^:adapt;"
"}";

XOILA_DEFINE_SPECT( bcore_inst, lion_adaptor )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/
// source: lion_adaptive_bhpt.h
#include "lion_adaptive_bhpt.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_adaptive_bhpt

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_bhpt_s )
"aware bhpt_adaptive"
"{"
    "aware => src;"
    "lion_frame_s frame;"
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

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_bhpt_builder_s )
"aware bhpt_builder"
"{"
    "aware => src;"
    "bhvm_holor_s holor_frame_en;"
    "bhvm_holor_s holor_frame_ex;"
    "func ^:set_format_en;"
    "func ^:set_format_ex;"
    "func ^:create_adaptive;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_bhpt_cyclic_s )
"aware bhpt_adaptive"
"{"
    "aware => src;"
    "lion_frame_cyclic_s frame;"
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

BCORE_DEFINE_OBJECT_INST_P( lion_adaptive_bhpt_cyclic_builder_s )
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

XOILA_DEFINE_SPECT( bcore_inst, lion_adaptive_bhpt )
"{"
    "bcore_spect_header_s header;"
"}";

/**********************************************************************************************************************/

vd_t bmath_general_signal_handler( const bcore_signal_s* o );
vd_t bhvm_general_signal_handler( const bcore_signal_s* o );
vd_t bhpt_general_signal_handler( const bcore_signal_s* o );

vd_t lion_xo_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_xo" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: lion_root.h

            // group: lion
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_name, lion_hmeta_s_get_name );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_pclass, lion_hmeta_s_get_pclass );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_is_rollable, lion_hmeta_s_is_rollable );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_is_active, lion_hmeta_s_is_active );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_custom, lion_hmeta_s_get_custom );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_set_custom, lion_hmeta_s_set_custom );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_get_node, lion_hmeta_s_get_node );
            BCORE_REGISTER_FFUNC( bhvm_mcode_hmeta_set_node, lion_hmeta_s_set_node );
            BCORE_REGISTER_OBJECT( lion_hmeta_s );
            BCORE_REGISTER_FFUNC( bcore_fp_copy_typed, lion_holor_s_copy_typed );
            BCORE_REGISTER_OBJECT( lion_holor_s );
            XOILA_REGISTER_SPECT( lion );

            // --------------------------------------------------------------------
            // source: lion_nop.h

            // group: lion_nop
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
            BCORE_REGISTER_FEATURE( lion_nop_arity );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_arity_default );
            BCORE_REGISTER_FEATURE( lion_nop_priority );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_priority_default );
            BCORE_REGISTER_FEATURE( lion_nop_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_symbol_default );
            BCORE_REGISTER_FEATURE( lion_nop_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_reserved_default );
            BCORE_REGISTER_FEATURE( lion_nop_create_op_of_arn );
            BCORE_REGISTER_FFUNC( lion_nop_create_op_of_arn, lion_nop_create_op_of_arn_default );
            BCORE_REGISTER_OBJECT( lion_nop_solve_result_s );
            BCORE_REGISTER_FEATURE( lion_nop_eci );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_eci_default );
            BCORE_REGISTER_FEATURE( lion_nop_solve );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_solve__ );
            BCORE_REGISTER_FEATURE( lion_nop_solve_node );
            BCORE_REGISTER_FFUNC( lion_nop_solve_node, lion_nop_solve_node__ );
            BCORE_REGISTER_FEATURE( lion_nop_is_cyclic );
            BCORE_REGISTER_FFUNC( lion_nop_is_cyclic, lion_nop_is_cyclic_default );
            BCORE_REGISTER_FEATURE( lion_nop_is_adaptive );
            BCORE_REGISTER_FFUNC( lion_nop_is_adaptive, lion_nop_is_adaptive_default );
            BCORE_REGISTER_FEATURE( lion_nop_settle );
            BCORE_REGISTER_FFUNC( lion_nop_settle, lion_nop_settle_default );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_ap );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_dp_a );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_dp_b );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_dp_c );
            BCORE_REGISTER_FEATURE( lion_nop_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_holor, lion_nop_mcode_push_ap_holor_default );
            BCORE_REGISTER_FEATURE( lion_nop_mcode_push_dp_holor );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_mcode_push_dp_holor_default );
            BCORE_REGISTER_FEATURE( lion_nop_mcode_push_ap_track );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_track, lion_nop_mcode_push_ap_track_default );
            BCORE_REGISTER_FEATURE( lion_nop_mcode_push_dp_track );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_track, lion_nop_mcode_push_dp_track_default );
            BCORE_REGISTER_OBJECT( lion_nop_context_s );
            XOILA_REGISTER_SPECT( lion_nop );

            // group: lion_nop_ar0
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_literal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_literal_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_literal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_param_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_param_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_param_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_adaptive_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_is_adaptive, lion_nop_ar0_adaptive_s_is_adaptive );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_holor, lion_nop_ar0_adaptive_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar0_adaptive_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_adaptive_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_rand_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_rand_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_holor, lion_nop_ar0_rand_s_mcode_push_ap_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_rand_s );
            XOILA_REGISTER_SPECT( lion_nop_ar0 );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_literal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_param_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_adaptive_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_rand_s );

            // group: lion_nop_ar1
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_identity_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_identity_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_identity_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_identity_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_identity_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_f3_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_f3_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_f3_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_f3_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_f3_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_f3_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_f2_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_f2_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_f2_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_f2_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_f2_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_f2_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_neg_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_neg_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_neg_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_neg_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_neg_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_neg_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_create_op_of_arn, lion_nop_ar1_neg_s_create_op_of_arn );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_neg_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_floor_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_floor_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_floor_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_floor_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_floor_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar1_floor_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_floor_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_ceil_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_ceil_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_ceil_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_ceil_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_ceil_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar1_ceil_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_ceil_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_abs_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_abs_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_abs_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_abs_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_abs_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_abs_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_abs_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_exp_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_exp_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_exp_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_exp_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_exp_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_exp_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_exp_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_log_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_log_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_log_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_log_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_log_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_log_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_log_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_inv_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_inv_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_inv_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_inv_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_inv_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_inv_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_inv_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_sqr_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_sqr_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_sqr_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_sqr_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_sqr_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_sqr_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_sqr_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_srt_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_srt_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_srt_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_srt_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_srt_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_srt_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_srt_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_sigm_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_sigm_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_sigm_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_sigm_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_sigm_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_sigm_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_sigm_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_sigm_hard_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_sigm_hard_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_sigm_hard_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_sigm_hard_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_sigm_hard_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_sigm_hard_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_sigm_hard_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_sigm_leaky_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_sigm_leaky_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_sigm_leaky_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_sigm_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_sigm_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_sigm_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_sigm_leaky_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_tanh_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_tanh_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_tanh_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_tanh_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_tanh_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_tanh_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_tanh_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_tanh_hard_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_tanh_hard_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_tanh_hard_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_tanh_hard_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_tanh_hard_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_tanh_hard_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_tanh_hard_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_tanh_leaky_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_tanh_leaky_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_tanh_leaky_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_tanh_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_tanh_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_tanh_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_tanh_leaky_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_softplus_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_softplus_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_softplus_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_softplus_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_softplus_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_softplus_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_softplus_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_softmax_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_softmax_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_softmax_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_softmax_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_softmax_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_softmax_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_softmax_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_relu_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_relu_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_relu_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_relu_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_relu_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_relu_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_relu_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_relu_leaky_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_relu_leaky_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_relu_leaky_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_relu_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_relu_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_relu_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_relu_leaky_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_output_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_output_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_output_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar1_output_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_output_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_adaptive_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_adaptive_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_adaptive_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_is_adaptive, lion_nop_ar1_adaptive_s_is_adaptive );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_settle, lion_nop_ar1_adaptive_s_settle );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_adaptive_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_dimof_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_dimof_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_dimof_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_dimof_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_dimof_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_dimof_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_volof_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_volof_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_volof_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_volof_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_volof_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_volof_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_constof_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_constof_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_constof_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_constof_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_constof_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_constof_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_zeroof_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_zeroof_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_zeroof_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_zeroof_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_zeroof_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_zeroof_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_shapeof_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_shapeof_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_shapeof_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_shapeof_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_shapeof_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_shapeof_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_rand_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_rand_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_rand_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_rand_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_rand_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_settle, lion_nop_ar1_rand_s_settle );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_rand_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_cast_htp_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_cast_htp_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_cast_htp_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_cast_htp_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_cast_htp_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_holor, lion_nop_ar1_cast_htp_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar1_cast_htp_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_cast_htp_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_reshape_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar1_reshape_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_reshape_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_reshape_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_holor, lion_nop_ar1_reshape_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar1_reshape_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_reshape_s );
            XOILA_REGISTER_SPECT( lion_nop_ar1 );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_identity_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_f3_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_f2_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_neg_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_floor_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_ceil_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_abs_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_exp_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_log_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_inv_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_sqr_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_srt_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_sigm_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_sigm_hard_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_sigm_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_tanh_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_tanh_hard_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_tanh_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_softplus_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_softmax_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_relu_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_relu_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_output_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_adaptive_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_dimof_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_volof_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_constof_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_zeroof_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_shapeof_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_rand_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_cast_htp_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_reshape_s );

            // group: lion_nop_ar2
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_add_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_add_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_add_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_add_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_add_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_add_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_add_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_add_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_add_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_sub_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_sub_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_sub_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_sub_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_sub_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_sub_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_sub_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_sub_s_type_vop_dp_b );
            BCORE_REGISTER_FFUNC( lion_nop_create_op_of_arn, lion_nop_ar2_sub_s_create_op_of_arn );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_sub_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_mul_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_mul_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_mul_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_mul_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_mul_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_mul_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_mul_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_mul_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_mul_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_div_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_div_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_div_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_div_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_div_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_div_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_div_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_div_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_div_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_pow_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_pow_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_pow_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_pow_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_pow_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_pow_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_pow_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_pow_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_pow_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_bmul_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_bmul_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_bmul_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_bmul_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_bmul_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_bmul_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_equal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_equal_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_equal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_equal_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_equal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_equal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_equal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_unequal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_unequal_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_unequal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_unequal_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_unequal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_unequal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_unequal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_unequal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_larger_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_larger_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_larger_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_larger_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_larger_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_larger_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_larger_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_larger_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_smaller_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_smaller_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_smaller_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_smaller_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_smaller_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_smaller_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_smaller_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_smaller_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_larger_equal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_larger_equal_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_larger_equal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_larger_equal_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_larger_equal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_larger_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_larger_equal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_larger_equal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_smaller_equal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_smaller_equal_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_smaller_equal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_smaller_equal_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_smaller_equal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_smaller_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_smaller_equal_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_smaller_equal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_and_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_and_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_and_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_and_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_and_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_and_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_and_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_and_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_or_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_logic_or_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_or_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar2_logic_or_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_or_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_or_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_logic_or_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_or_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_cat_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_cat_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_cat_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_cat_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_cat_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_cat_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_cat_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_cat_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_cat_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_ccat_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_ccat_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_ccat_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_ccat_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_ccat_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_ccat_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_ccat_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_ccat_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_ccat_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_order_inc_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_order_inc_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_order_inc_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_order_inc_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_order_inc_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_track, lion_nop_ar2_order_inc_s_mcode_push_ap_track );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_order_inc_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_order_inc_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_order_inc_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_order_dec_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_order_dec_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_order_dec_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_order_dec_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_order_dec_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_holor, lion_nop_ar2_order_dec_s_mcode_push_ap_holor );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_order_dec_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_order_dec_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_cyclic_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_cyclic_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_cyclic_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_is_cyclic, lion_nop_ar2_cyclic_s_is_cyclic );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_cyclic_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_solve_node, lion_nop_ar2_cyclic_s_solve_node );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap_track, lion_nop_ar2_cyclic_s_mcode_push_ap_track );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_track, lion_nop_ar2_cyclic_s_mcode_push_dp_track );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp_holor, lion_nop_ar2_cyclic_s_mcode_push_dp_holor );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_cyclic_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_rands_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_rands_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_rands_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_rands_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_rands_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_settle, lion_nop_ar2_rands_s_settle );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_rands_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_reshape_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar2_reshape_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_reshape_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_reshape_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_reshape_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_solve_node, lion_nop_ar2_reshape_s_solve_node );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_reshape_s );
            XOILA_REGISTER_SPECT( lion_nop_ar2 );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_add_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_sub_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_mul_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_div_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_pow_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_bmul_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_equal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_unequal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_larger_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_smaller_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_larger_equal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_smaller_equal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_and_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_or_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_cat_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_ccat_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_order_inc_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_order_dec_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_cyclic_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_rands_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_reshape_s );

            // group: lion_nop_ar3
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar3_iff_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_reserved, lion_nop_ar3_iff_s_reserved );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar3_iff_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_eci, lion_nop_ar3_iff_s_eci );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar3_iff_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar3_iff_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar3_iff_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar3_iff_s_type_vop_dp_b );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_c, lion_nop_ar3_iff_s_type_vop_dp_c );
            BCORE_REGISTER_OBJECT( lion_nop_ar3_iff_s );
            XOILA_REGISTER_SPECT( lion_nop_ar3 );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar3_iff_s );

            // --------------------------------------------------------------------
            // source: lion_eval_nop.h

            // group: lion_eval_nop
            BCORE_REGISTER_OBJECT( lion_eval_nop_result_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, lion_eval_nop_param_s_init_x );
            BCORE_REGISTER_OBJECT( lion_eval_nop_param_s );
            BCORE_REGISTER_FEATURE( lion_eval_nop_set_param );
            BCORE_REGISTER_FEATURE( lion_eval_nop_run );
            BCORE_REGISTER_FFUNC( lion_eval_nop_run, lion_eval_nop_generator_s_run );
            BCORE_REGISTER_FFUNC( lion_eval_nop_set_param, lion_eval_nop_generator_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_nop_generator_s_main );
            BCORE_REGISTER_OBJECT( lion_eval_nop_generator_s );
            BCORE_REGISTER_FFUNC( lion_eval_nop_set_param, lion_eval_nop_show_param_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_nop_show_param_s_main );
            BCORE_REGISTER_FFUNC( lion_eval_nop_run, lion_eval_nop_show_param_s_run );
            BCORE_REGISTER_OBJECT( lion_eval_nop_show_param_s );
            BCORE_REGISTER_OBJECT( lion_eval_nop_arr_s );
            BCORE_REGISTER_FFUNC( lion_eval_nop_set_param, lion_eval_nop_set_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_nop_set_s_main );
            BCORE_REGISTER_FFUNC( lion_eval_nop_run, lion_eval_nop_set_s_run );
            BCORE_REGISTER_OBJECT( lion_eval_nop_set_s );
            BCORE_REGISTER_FFUNC( lion_eval_nop_run, lion_eval_nop_ar1_s_run );
            BCORE_REGISTER_FFUNC( lion_eval_nop_set_param, lion_eval_nop_ar1_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_nop_ar1_s_main );
            BCORE_REGISTER_OBJECT( lion_eval_nop_ar1_s );
            BCORE_REGISTER_FFUNC( lion_eval_nop_run, lion_eval_nop_ar2_s_run );
            BCORE_REGISTER_FFUNC( lion_eval_nop_set_param, lion_eval_nop_ar2_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_nop_ar2_s_main );
            BCORE_REGISTER_OBJECT( lion_eval_nop_ar2_s );
            XOILA_REGISTER_SPECT( lion_eval_nop );

            // --------------------------------------------------------------------
            // source: lion_sem.h

            // group: lion_sem
            BCORE_REGISTER_OBJECT( lion_sem_context_s );
            BCORE_REGISTER_NAME( cell );
            BCORE_REGISTER_FEATURE( lion_sem_get_name );
            BCORE_REGISTER_FFUNC( lion_sem_get_name, lion_sem_get_name_default );
            BCORE_REGISTER_FEATURE( lion_sem_is_visible );
            BCORE_REGISTER_FFUNC( lion_sem_is_visible, lion_sem_is_visible_default );
            BCORE_REGISTER_FFUNC( lion_sem_get_name, lion_sem_link_s_get_name );
            BCORE_REGISTER_FFUNC( lion_sem_is_visible, lion_sem_link_s_is_visible );
            BCORE_REGISTER_OBJECT( lion_sem_link_s );
            BCORE_REGISTER_OBJECT( lion_sem_links_s );
            BCORE_REGISTER_OBJECT( lion_sem_body_s );
            BCORE_REGISTER_FFUNC( lion_sem_get_name, lion_sem_cell_s_get_name );
            BCORE_REGISTER_OBJECT( lion_sem_cell_s );
            BCORE_REGISTER_OBJECT( lion_sem_stack_flag_s );
            XOILA_REGISTER_SPECT( lion_sem );

            // --------------------------------------------------------------------
            // source: lion_net.h

            // group: lion_ctr
            BCORE_REGISTER_OBJECT( lion_ctr_node_s );
            BCORE_REGISTER_OBJECT( lion_ctr_tree_s );
            XOILA_REGISTER_SPECT( lion_ctr );

            // group: lion_net
            BCORE_REGISTER_OBJECT( lion_net_link_s );
            BCORE_REGISTER_OBJECT( lion_net_links_s );
            BCORE_REGISTER_FEATURE( lion_net_is_cyclic );
            BCORE_REGISTER_FFUNC( lion_net_is_cyclic, lion_net_is_cyclic_default );
            BCORE_REGISTER_FFUNC( lion_net_is_cyclic, lion_net_node_s_is_cyclic );
            BCORE_REGISTER_OBJECT( lion_net_node_s );
            BCORE_REGISTER_OBJECT( lion_net_node_adl_s );
            BCORE_REGISTER_OBJECT( lion_net_nodes_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, lion_net_cell_s_copy_x );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, lion_net_cell_s_mutated );
            BCORE_REGISTER_OBJECT( lion_net_cell_s );
            XOILA_REGISTER_SPECT( lion_net );

            // --------------------------------------------------------------------
            // source: lion_frame.h

            // group: lion_frame
            BCORE_REGISTER_FFUNC( bcore_via_call_shelve, lion_frame_s_shelve );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, lion_frame_s_mutated );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, lion_frame_s_copy_x );
            BCORE_REGISTER_OBJECT( lion_frame_s );
            BCORE_REGISTER_OBJECT( lion_frame_custom_hmeta_s );
            BCORE_REGISTER_FFUNC( bcore_via_call_shelve, lion_frame_cyclic_s_shelve );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, lion_frame_cyclic_s_mutated );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, lion_frame_cyclic_s_copy_x );
            BCORE_REGISTER_OBJECT( lion_frame_cyclic_s );
            XOILA_REGISTER_SPECT( lion_frame );

            // group: lion_frame_hidx
            BCORE_REGISTER_OBJECT( lion_frame_hidx_s );
            BCORE_REGISTER_OBJECT( lion_frame_hidx_ads_s );
            XOILA_REGISTER_SPECT( lion_frame_hidx );

            // --------------------------------------------------------------------
            // source: lion_eval_frame.h

            // group: lion_eval_frame
            BCORE_REGISTER_OBJECT( lion_eval_frame_result_s );
            BCORE_REGISTER_FEATURE( lion_eval_frame_run );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, lion_eval_frame_param_s_init_x );
            BCORE_REGISTER_OBJECT( lion_eval_frame_param_s );
            BCORE_REGISTER_FFUNC( lion_eval_frame_set_param, lion_eval_frame_show_param_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_frame_show_param_s_main );
            BCORE_REGISTER_FFUNC( lion_eval_frame_run, lion_eval_frame_show_param_s_run );
            BCORE_REGISTER_OBJECT( lion_eval_frame_show_param_s );
            BCORE_REGISTER_FEATURE( lion_eval_frame_set_param );
            BCORE_REGISTER_OBJECT( lion_eval_frame_arr_s );
            BCORE_REGISTER_FFUNC( lion_eval_frame_set_param, lion_eval_frame_set_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_frame_set_s_main );
            BCORE_REGISTER_FFUNC( lion_eval_frame_run, lion_eval_frame_set_s_run );
            BCORE_REGISTER_OBJECT( lion_eval_frame_set_s );
            BCORE_REGISTER_FFUNC( lion_eval_frame_run, lion_eval_frame_plain_s_run );
            BCORE_REGISTER_FFUNC( lion_eval_frame_set_param, lion_eval_frame_plain_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_frame_plain_s_main );
            BCORE_REGISTER_OBJECT( lion_eval_frame_plain_s );
            BCORE_REGISTER_FFUNC( lion_eval_frame_run, lion_eval_frame_cyclic_s_run );
            BCORE_REGISTER_FFUNC( lion_eval_frame_set_param, lion_eval_frame_cyclic_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_eval_frame_cyclic_s_main );
            BCORE_REGISTER_OBJECT( lion_eval_frame_cyclic_s );
            XOILA_REGISTER_SPECT( lion_eval_frame );

            // --------------------------------------------------------------------
            // source: lion_adaptive.h

            // group: lion_adaptive
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_in_size, lion_adaptive_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_out_size, lion_adaptive_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_dynamics_std, lion_adaptive_s_get_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_set_dynamics_std, lion_adaptive_s_set_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_arc_to_sink, lion_adaptive_s_arc_to_sink );
            BCORE_REGISTER_FFUNC( badapt_adaptive_minfer, lion_adaptive_s_minfer );
            BCORE_REGISTER_FFUNC( badapt_adaptive_bgrad_adapt, lion_adaptive_s_bgrad_adapt );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_weights_min_max, lion_adaptive_s_get_weights_min_max );
            BCORE_REGISTER_OBJECT( lion_adaptive_s );
            BCORE_REGISTER_FFUNC( badapt_builder_get_in_size, lion_adaptive_builder_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_in_size, lion_adaptive_builder_s_set_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_get_out_size, lion_adaptive_builder_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_out_size, lion_adaptive_builder_s_set_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_build, lion_adaptive_builder_s_build );
            BCORE_REGISTER_OBJECT( lion_adaptive_builder_s );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_in_size, lion_adaptive_cyclic_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_out_size, lion_adaptive_cyclic_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_dynamics_std, lion_adaptive_cyclic_s_get_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_set_dynamics_std, lion_adaptive_cyclic_s_set_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_arc_to_sink, lion_adaptive_cyclic_s_arc_to_sink );
            BCORE_REGISTER_FFUNC( badapt_adaptive_minfer, lion_adaptive_cyclic_s_minfer );
            BCORE_REGISTER_FFUNC( badapt_adaptive_bgrad_adapt, lion_adaptive_cyclic_s_bgrad_adapt );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_weights_min_max, lion_adaptive_cyclic_s_get_weights_min_max );
            BCORE_REGISTER_FFUNC( badapt_adaptive_reset, lion_adaptive_cyclic_s_reset );
            BCORE_REGISTER_OBJECT( lion_adaptive_cyclic_s );
            BCORE_REGISTER_FFUNC( badapt_builder_get_in_size, lion_adaptive_cyclic_builder_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_in_size, lion_adaptive_cyclic_builder_s_set_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_get_out_size, lion_adaptive_cyclic_builder_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_out_size, lion_adaptive_cyclic_builder_s_set_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_build, lion_adaptive_cyclic_builder_s_build );
            BCORE_REGISTER_OBJECT( lion_adaptive_cyclic_builder_s );
            XOILA_REGISTER_SPECT( lion_adaptive );

            // --------------------------------------------------------------------
            // source: lion_adaptor.h

            // group: lion_adaptor
            BCORE_REGISTER_FFUNC( bhpt_adaptor_reset, lion_adaptor_frame_s_reset );
            BCORE_REGISTER_FFUNC( bhpt_adaptor_adapt, lion_adaptor_frame_s_adapt );
            BCORE_REGISTER_OBJECT( lion_adaptor_frame_s );
            XOILA_REGISTER_SPECT( lion_adaptor );

            // --------------------------------------------------------------------
            // source: lion_adaptive_bhpt.h

            // group: lion_adaptive_bhpt
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_en, lion_adaptive_bhpt_s_get_format_en );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_ex, lion_adaptive_bhpt_s_get_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_axon_pass, lion_adaptive_bhpt_s_axon_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_dendrite_pass, lion_adaptive_bhpt_s_dendrite_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_cyclic_reset, lion_adaptive_bhpt_s_cyclic_reset );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_adaptor_probe, lion_adaptive_bhpt_s_get_adaptor_probe );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_rebind_holors, lion_adaptive_bhpt_s_rebind_holors );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_status_to_sink, lion_adaptive_bhpt_s_status_to_sink );
            BCORE_REGISTER_OBJECT( lion_adaptive_bhpt_s );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_en, lion_adaptive_bhpt_builder_s_set_format_en );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_ex, lion_adaptive_bhpt_builder_s_set_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_builder_create_adaptive, lion_adaptive_bhpt_builder_s_create_adaptive );
            BCORE_REGISTER_OBJECT( lion_adaptive_bhpt_builder_s );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_en, lion_adaptive_bhpt_cyclic_s_get_format_en );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_format_ex, lion_adaptive_bhpt_cyclic_s_get_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_axon_pass, lion_adaptive_bhpt_cyclic_s_axon_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_dendrite_pass, lion_adaptive_bhpt_cyclic_s_dendrite_pass );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_cyclic_reset, lion_adaptive_bhpt_cyclic_s_cyclic_reset );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_get_adaptor_probe, lion_adaptive_bhpt_cyclic_s_get_adaptor_probe );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_rebind_holors, lion_adaptive_bhpt_cyclic_s_rebind_holors );
            BCORE_REGISTER_FFUNC( bhpt_adaptive_status_to_sink, lion_adaptive_bhpt_cyclic_s_status_to_sink );
            BCORE_REGISTER_OBJECT( lion_adaptive_bhpt_cyclic_s );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_en, lion_adaptive_bhpt_cyclic_builder_s_set_format_en );
            BCORE_REGISTER_FFUNC( bhpt_builder_set_format_ex, lion_adaptive_bhpt_cyclic_builder_s_set_format_ex );
            BCORE_REGISTER_FFUNC( bhpt_builder_create_adaptive, lion_adaptive_bhpt_cyclic_builder_s_create_adaptive );
            BCORE_REGISTER_OBJECT( lion_adaptive_bhpt_cyclic_builder_s );
            XOILA_REGISTER_SPECT( lion_adaptive_bhpt );
        }
        break;
        case TYPEOF_push_dependencies:
        {
            ASSERT( o->object && ( *( aware_t* )o->object ) == TYPEOF_bcore_arr_fp_s );
            bcore_arr_fp_s* arr_fp = o->object;
            bcore_arr_fp_s_push( arr_fp, ( fp_t )bmath_general_signal_handler );
            bcore_arr_fp_s_push( arr_fp, ( fp_t )bhvm_general_signal_handler );
            bcore_arr_fp_s_push( arr_fp, ( fp_t )bhpt_general_signal_handler );
        }
        break;
        default: break;
    }
    return NULL;
}
// XOILA_OUT_SIGNATURE 0xD05388C5ED9582CBull
