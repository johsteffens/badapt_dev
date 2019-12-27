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

#include "lion_planted.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: lion_nop.h
#include "lion_nop.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion

BCORE_DEFINE_OBJECT_INST_P( lion_hmeta_s )
"aware bhvm_mcode_hmeta"
"{"
    "tp_t name;"
    "tp_t class;"
    "bl_t htp;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_holor_s )
"aware lion"
"{"
    "lion_hmeta_s m;"
    "bhvm_holor_s h;"
    "func bcore_fp:copy_typed;"
"}";

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
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_context_s )
"aware bcore_inst"
"{"
    "private bcore_mutex_s* randomizer_mutex;"
    "bl_t randomizer_is_locked = false;"
    "u2_t randomizer_rval = 0;"
"}";

BCORE_DEFINE_SPECT( bcore_inst, lion_nop )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_nop : arity = lion_nop_arity__;"
    "feature aware lion_nop : class = lion_nop_class__;"
    "feature aware lion_nop : priority = lion_nop_priority__;"
    "feature aware lion_nop : symbol = lion_nop_symbol__;"
    "feature aware lion_nop : create_op_of_arn = lion_nop_create_op_of_arn__;"
    "feature aware lion_nop : solve = lion_nop_solve__;"
    "feature aware lion_nop : requires_solve_for_each_channel = lion_nop_requires_solve_for_each_channel__;"
    "feature aware lion_nop : create_final = lion_nop_create_final__;"
    "feature aware lion_nop : type_vop_ap;"
    "feature aware lion_nop : type_vop_dp_a;"
    "feature aware lion_nop : type_vop_dp_b;"
    "feature aware lion_nop : type_vop_dp_c;"
    "feature aware lion_nop : mcode_push_ap = lion_nop_mcode_push_ap__;"
    "feature aware lion_nop : mcode_push_dp = lion_nop_mcode_push_dp__;"
"}";


bl_t lion_nop_solve__( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( result );
    lion_holor_s** r = &result->h;
    lion_holor_s_detach( r );
    sz_t arity = lion_nop_a_arity( o );
    bl_t settled = ( arity > 0 );
    tp_t r_type = TYPEOF_f2_t;
    bl_t r_htp  = false;
    for( sz_t i = 0; i < arity; i++ )
    {
        if( !a[i] ) BLM_RETURNV( bl_t, false );
        bhvm_holor_s* h = &a[ i ]->h;
        if( h->v.type == TYPEOF_f3_t ) r_type = TYPEOF_f3_t;
        if( h->v.size == 0 ) settled = false;
        if( i > 0 )
        {
            lion_holor_s* lh0 = a[ 0 ];
            lion_holor_s* lh1 = a[ i ];
            if( !bhvm_shape_s_is_equal( &lh0->h.s, &lh1->h.s ) ) BLM_RETURNV( bl_t, false );
            if( lh0->m.htp != lh1->m.htp ) BLM_RETURNV( bl_t, false );
        }
        r_htp = a[ i ]->m.htp;
    }
    
    lion_holor_s_attach( r, lion_holor_s_create() );
    bhvm_holor_s* hr = &(*r)->h;
    (*r)->m.htp = r_htp;
    
    if( arity > 0 )
    {
        bhvm_holor_s* h0 = &a[ 0 ]->h;
        bhvm_shape_s_copy( &hr->s, &h0->s );
    }
    
    if( settled )
    {
        bhvm_holor_s_set_type( hr, r_type );
        bhvm_holor_s_fit_size( hr );
    
        // We setup a mini frame and run vop_ap on it.
        bhvm_mcode_hbase_s* hbase = BLM_CREATE( bhvm_mcode_hbase_s );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );
        bhvm_mcode_hbase_s_set_size( hbase, arity + 1 );
        bhvm_vop_arr_ci_s_set_size( arr_ci, arity + 1 );
        for( sz_t i = 0; i <= arity; i++ )
        {
            bhvm_holor_s_init_weak_from_holor( &hbase->holor_ads.data[ i ], ( i < arity ) ? &a[ i ]->h : hr );
            arr_ci->data[ i ].i = i;
            arr_ci->data[ i ].c = ( i < arity ) ? 'a' + i : 'y';
        }
    
        result->type_vop_ap = lion_nop_a_defines_type_vop_ap( o ) ? lion_nop_a_type_vop_ap( o ) : 0;
        assert( result->type_vop_ap );
        bhvm_vop* vop = BLM_A_PUSH( bhvm_vop_t_create( result->type_vop_ap ) );
        bhvm_vop_a_set_args( vop, arr_ci );
        bhvm_vop_a_run( vop, hbase->holor_ads.data );
    }
    
    result->settled = settled;
    BLM_RETURNV( bl_t, true );
}

lion_nop* lion_nop_create_final__( const lion_nop* o, lion_holor_s* h )
{
    lion_nop_ar0_literal_s* final = lion_nop_ar0_literal_s_create();
    final->h = lion_holor_s_clone( h );
    return (lion_nop*)final;
}

void lion_nop_mcode_push_ap__( const lion_nop* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    assert( result->type_vop_ap );
    tp_t type = ( lion_nop_a_defines_type_vop_ap( o ) ) ? lion_nop_a_type_vop_ap( o ) : result->type_vop_ap;
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap, bhvm_vop_t_create( type ), arr_ci );
}

void lion_nop_mcode_push_dp__( const lion_nop* o, const lion_nop_solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    if( ch_id < 'a' || ch_id > 'c' ) ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    if( ch_id >= lion_nop_a_arity( o ) + 'a' ) ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    tp_t type = 0;
    switch( ch_id )
    {
        case 'a': type = ( lion_nop_a_defines_type_vop_dp_a( o ) ) ? lion_nop_a_type_vop_dp_a( o ) : result->type_vop_dp_a; break;
        case 'b': type = ( lion_nop_a_defines_type_vop_dp_b( o ) ) ? lion_nop_a_type_vop_dp_b( o ) : result->type_vop_dp_b; break;
        case 'c': type = ( lion_nop_a_defines_type_vop_dp_c( o ) ) ? lion_nop_a_type_vop_dp_c( o ) : result->type_vop_dp_c; break;
        default: break;
    }
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_dp, bhvm_vop_t_create( type ), arr_ci );
}
//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar0

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_zro_s )
"aware lion_nop_ar0"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_zro_s_solve( const lion_nop_ar0_zro_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, lion_holor_s_create() );
    bhvm_holor_s_set_scalar_f3( &result->h->h, 0 );
    result->type_vop_ap = TYPEOF_bhvm_vop_ar0_zro_s;
    result->settled = true;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_one_s )
"aware lion_nop_ar0"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_one_s_solve( const lion_nop_ar0_one_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, lion_holor_s_create() );
    bhvm_holor_s_set_scalar_f3( &result->h->h, 1 );
    result->type_vop_ap = TYPEOF_bhvm_vop_ar0_one_s;
    result->settled = true;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_literal_s )
"aware lion_nop_ar0"
"{"
    "func lion_nop:arity;"
    "lion_holor_s -> h;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_literal_s_solve( const lion_nop_ar0_literal_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = true;
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_input_s )
"aware lion_nop_ar0"
"{"
    "func lion_nop:arity;"
    "lion_holor_s -> h;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_input_s_solve( const lion_nop_ar0_input_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = true;
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar0_adaptive_s )
"aware lion_nop_ar0"
"{"
    "func lion_nop:arity;"
    "lion_holor_s -> h;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar0_adaptive_s_solve( const lion_nop_ar0_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
    result->settled = false;
    result->codable = false;
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar1

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_identity_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_identity_s_solve( const lion_nop_ar1_identity_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, bcore_fork( a[0] ) );
    result->settled = (result->h) && result->h->h.v.size > 0;
    result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_identity_s;
    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_identity_dp_s;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_neg_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:create_op_of_arn;"
"}";

lion_nop* lion_nop_ar1_neg_s_create_op_of_arn( const lion_nop_ar1_neg_s* o, sz_t n )
{
    return ( n == 2 ) ? (lion_nop*)lion_nop_ar2_sub_s_create()
         : ( n == 1 ) ? (lion_nop*)lion_nop_ar1_neg_s_clone( o )
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_floor_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_ceil_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_exp_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_inv_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_lgst_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_lgst_hard_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_lgst_leaky_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_tanh_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_tanh_hard_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_tanh_leaky_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_softplus_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_relu_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_relu_leaky_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_output_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_output_s_solve( const lion_nop_ar1_output_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, bcore_fork( a[0] ) );
    result->settled = (result->h) && result->h->h.v.size > 0;
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_adaptive_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "tp_t name;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
    "func lion_nop:create_final;"
"}";

bl_t lion_nop_ar1_adaptive_s_solve( const lion_nop_ar1_adaptive_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, bcore_fork( a[0] ) );
    result->settled = ( result->h != NULL );
    result->reducible = false; // keep subsequent graph intact
    result->codable = false;
    return true;
}

lion_nop* lion_nop_ar1_adaptive_s_create_final( const lion_nop_ar1_adaptive_s* o, lion_holor_s* h )
{
    lion_nop_ar0_adaptive_s* final = lion_nop_ar0_adaptive_s_create();
    final->h = lion_holor_s_clone( h );
    final->h->m.name = o->name;
    return (lion_nop*)final;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_dimof_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_dimof_s_solve( const lion_nop_ar1_dimof_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, a[0] ? lion_holor_s_create() : NULL );
    if( result->h ) bhvm_holor_s_set_scalar_f3( &result->h->h, a[0]->h.s.size ? a[0]->h.s.data[ a[0]->h.s.size - 1 ] : 1 );
    result->type_vop_ap = TYPEOF_bhvm_vop_ar0_one_s;
    result->settled = result->h != NULL;
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_random_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "u2_t rseed = 1234;"
    "func lion_nop:symbol;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_random_s_solve( const lion_nop_ar1_random_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, a[0] ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        lion_nop_context_s* context = lion_nop_get_context();
        ASSERT( context->randomizer_is_locked );
        if( context->randomizer_rval == 0 ) context->randomizer_rval = o->rseed;
        lion_holor_s_copy( result->h, a[0] );
        if( !result->h->h.v.size ) bhvm_holor_s_fit_size( &result->h->h );
        bhvm_value_s_set_random( &result->h->h.v, 1.0, -0.5, 0.5, &context->randomizer_rval );
        result->settled = true;
    }
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar1_cast_htp_s )
"aware lion_nop_ar1"
"{"
    "func lion_nop:arity;"
    "func lion_nop:class;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar1_cast_htp_s_solve( const lion_nop_ar1_cast_htp_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, a[0] ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        bhvm_holor_s_init_fork_from_holor( &result->h->h, &a[0]->h );
        result->h->m.htp = !a[0]->m.htp;
    }
    result->settled = result->h && result->h->h.v.size > 0;
    result->codable = false;
    return true;
}

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar2

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_add_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_sub_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
    "func lion_nop:create_op_of_arn;"
"}";

lion_nop* lion_nop_ar2_sub_s_create_op_of_arn( const lion_nop_ar2_sub_s* o, sz_t n )
{
    return ( n == 2 ) ? (lion_nop*)lion_nop_ar2_sub_s_clone( o )
         : ( n == 1 ) ? (lion_nop*)lion_nop_ar1_neg_s_create()
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_div_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_mul_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_bmul_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:solve;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_equal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_larger_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_smaller_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_larger_equal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_smaller_equal_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_and_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_logic_or_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:symbol;"
    "func lion_nop:type_vop_ap;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_index_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar2_index_s_solve( const lion_nop_ar2_index_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_detach( &result->h );
    if( a[0] && a[0]->m.htp ) return false;
    lion_holor_s_attach( &result->h, a[0] && a[1] ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( hb->v.size != 1 ) return false;
        sz_t index = bhvm_holor_s_f3_get_scalar( hb );
        if( ha->s.size == 0 ) return false;
        if( index < 0 || index >= ha->s.data[ ha->s.size - 1 ] ) return false;
        bhvm_holor_s_clear( hr );
        bhvm_shape_s_set_data( &hr->s, ha->s.data, ha->s.size - 1 );
        if( ha->v.size ) bhvm_value_s_init_weak_from_value( &hr->v, &ha->v );
    }
    result->settled = ( result->h && result->h->h.v.size );
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_inc_order_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar2_inc_order_s_solve( const lion_nop_ar2_inc_order_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, a[0] && a[1] ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( ha->v.size != 1 ) return false;
        sz_t dim = bhvm_holor_s_f3_get_scalar( ha );
        if( dim <= 0 ) return false;
        bhvm_holor_s_copy( hr, hb );
        bhvm_holor_s_inc_order( hr, dim );
    }
    result->settled = ( result->h && result->h->h.v.size );
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_cat_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar2_cat_s_solve( const lion_nop_ar2_cat_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, a[0] && a[1] ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( !bhvm_holor_s_can_cat( ha, hb ) ) return false;
        bhvm_holor_s_cat_set( ha, hb, hr );
    }
    result->settled = ( result->h && result->h->h.v.size );
    result->codable = false;
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar2_recurrent_s )
"aware lion_nop_ar2"
"{"
    "func lion_nop:arity;"
    "tp_t name;"
    "func lion_nop:priority;"
    "func lion_nop:requires_solve_for_each_channel;"
    "func lion_nop:solve;"
    "func lion_nop:type_vop_dp_a;"
    "func lion_nop:type_vop_dp_b;"
    "func lion_nop:mcode_push_ap;"
"}";

bl_t lion_nop_ar2_recurrent_s_solve( const lion_nop_ar2_recurrent_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_create() );
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hr = &result->h->h;
        bhvm_shape_s_copy( &hr->s, &ha->s );
        if( a[1] )
        {
            bhvm_holor_s* hb = &a[1]->h;
            if( !bhvm_shape_s_is_equal( &ha->s, &hb->s ) ) return false;
            result->settled = ha->v.size > 0 && hb->v.size > 0;
            return true;
        }
        else
        {
            result->settled = false;
            return true;
        }
    }
    else
    {
        if( a[1] ) return false;
        lion_holor_s_attach( &result->h, NULL );
        result->settled = false;
        return true;
    }
}

void lion_nop_ar2_recurrent_s_mcode_push_ap( const lion_nop_ar2_recurrent_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_setup_ap, bhvm_vop_t_create( TYPEOF_bhvm_vop_ar1_cpy_ay_s ), arr_ci );
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap,       bhvm_vop_t_create( TYPEOF_bhvm_vop_ar1_cpy_by_s ), arr_ci );
}

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_ar3

BCORE_DEFINE_OBJECT_INST_P( lion_nop_ar3_branch_s )
"aware lion_nop_ar3"
"{"
    "func lion_nop:arity;"
    "func lion_nop:priority;"
    "func lion_nop:solve;"
"}";

bl_t lion_nop_ar3_branch_s_solve( const lion_nop_ar3_branch_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    if( a[0] )
    {
        bhvm_holor_s* ha = &a[0]->h;
        if( ha->v.size != 1 ) return false;
        f3_t cond = bhvm_holor_s_f3_get_scalar( ha );
        if( cond > 0 )
        {
            lion_holor_s_attach( &result->h, bcore_fork( a[1] ) );
        }
        else
        {
            lion_holor_s_attach( &result->h, bcore_fork( a[2] ) );
        }
    }
    result->settled = ( result->h && result->h->h.v.size );
    result->codable = false;
    return true;
}

/**********************************************************************************************************************/
// source: lion_nop_eval.h
#include "lion_nop_eval.h"

//----------------------------------------------------------------------------------------------------------------------
// group: lion_nop_eval

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_result_s )
"aware bcore_inst"
"{"
    "bl_t error = false;"
    "st_s msg;"
"}";

void lion_nop_eval_result_s_resolve( lion_nop_eval_result_s* o )
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
    lion_nop_eval_result_s_discard( o );
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_param_s )
"aware bcore_inst"
"{"
    "aware lion_nop => nop;"
    "lion_holor_s => ha;"
    "lion_holor_s => hb;"
    "lion_holor_s => hc;"
    "lion_holor_s => hr;"
    "hidden aware bcore_sink -> log;"
    "sz_t verbosity = 1;"
    "u2_t rval = 1234;"
    "func bcore_inst_call:init_x;"
"}";

void lion_nop_eval_param_s_set( lion_nop_eval_param_s* o, const lion_nop_eval_param_s* src )
{
    o->verbosity = sz_max( o->verbosity, src->verbosity );
    o->rval      = bcore_xsg3_u2( o->rval + src->rval );
    bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
    if( !o->ha  ) o->ha  = lion_holor_s_clone( src->ha );
    if( !o->hb  ) o->hb  = lion_holor_s_clone( src->hb );
    if( !o->hc  ) o->hc  = lion_holor_s_clone( src->hc );
    if( !o->hr  ) o->hr  = lion_holor_s_clone( src->hr );
    if( !o->nop ) o->nop = lion_nop_a_clone( src->nop );
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_generator_s )
"aware lion_nop_eval"
"{"
    "lion_nop_eval_param_s param;"
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
    "aware lion_nop_eval=> eval;"
    "func ^:set_param;"
    "func ^:run;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_show_param_s )
"aware lion_nop_eval"
"{"
    "lion_nop_eval_param_s param;"
    "func ^:set_param;"
    "func ^:run;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_arr_s )
"aware bcore_array"
"{"
    "aware lion_nop_eval* [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_set_s )
"aware lion_nop_eval"
"{"
    "lion_nop_eval_param_s param;"
    "lion_nop_eval_arr_s arr;"
    "func ^:set_param;"
    "func ^:run;"
    "func bcore_main:main;"
"}";

lion_nop_eval_result_s* lion_nop_eval_set_s_run( const lion_nop_eval_set_s* o )
{
    BFOR_EACH( i, &o->arr )
    {
        BLM_INIT();
        lion_nop_eval* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
        lion_nop_eval_a_set_param( eval, &o->param );
        lion_nop_eval_result_s* r = BLM_A_PUSH( lion_nop_eval_a_run( eval ) );
        if( r && r->error )
        {
            st_s* s = BLM_A_PUSH( st_s_clone( &r->msg ) );
            st_s_copy_fa( &r->msg, "At set entry #<sz_t>:\n#<st_s*>", i, s );
            BLM_RETURNV( lion_nop_eval_result_s*, lion_nop_eval_result_s_clone( r ) );
        }
        BLM_DOWN();
    };
    return NULL;
}

s2_t lion_nop_eval_set_s_main( lion_nop_eval_set_s* o, const bcore_arr_st_s* args )
{
    lion_nop_eval_result_s_resolve( lion_nop_eval_set_s_run( o ) ); return 0;
}

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_ar1_s )
"aware lion_nop_eval"
"{"
    "lion_nop_eval_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_OBJECT_INST_P( lion_nop_eval_ar2_s )
"aware lion_nop_eval"
"{"
    "lion_nop_eval_param_s param;"
    "func ^:run;"
    "func ^:set_param;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_SPECT( bcore_inst, lion_nop_eval )
"{"
    "bcore_spect_header_s header;"
    "feature aware lion_nop_eval : run;"
    "feature aware lion_nop_eval : set_param;"
"}";

/**********************************************************************************************************************/

vd_t lion_planted_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_planted" ) ) )
    {
        case TYPEOF_init1:
        {
            // Comment or remove line below to rebuild this target.
            bcore_const_x_set_d( typeof( "lion_planted_hash" ), sr_tp( 2003837385 ) );

            // --------------------------------------------------------------------
            // source: lion_nop.h

            // group: lion
            BCORE_REGISTER_OBJECT( lion_hmeta_s );
            BCORE_REGISTER_FFUNC( bcore_fp_copy_typed, lion_holor_s_copy_typed );
            BCORE_REGISTER_OBJECT( lion_holor_s );
            BCORE_REGISTER_TRAIT( lion, bcore_inst );

            // group: lion_nop
            BCORE_REGISTER_NAME( nop_class_regular );
            BCORE_REGISTER_NAME( nop_class_cast );
            BCORE_REGISTER_NAME( track_ap );
            BCORE_REGISTER_NAME( track_dp );
            BCORE_REGISTER_NAME( track_setup_ap );
            BCORE_REGISTER_NAME( track_setup_dp );
            BCORE_REGISTER_FEATURE( lion_nop_arity );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_arity__ );
            BCORE_REGISTER_FEATURE( lion_nop_class );
            BCORE_REGISTER_FFUNC( lion_nop_class, lion_nop_class__ );
            BCORE_REGISTER_FEATURE( lion_nop_priority );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_priority__ );
            BCORE_REGISTER_FEATURE( lion_nop_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_symbol__ );
            BCORE_REGISTER_FEATURE( lion_nop_create_op_of_arn );
            BCORE_REGISTER_FFUNC( lion_nop_create_op_of_arn, lion_nop_create_op_of_arn__ );
            BCORE_REGISTER_OBJECT( lion_nop_solve_result_s );
            BCORE_REGISTER_FEATURE( lion_nop_solve );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_solve__ );
            BCORE_REGISTER_FEATURE( lion_nop_requires_solve_for_each_channel );
            BCORE_REGISTER_FFUNC( lion_nop_requires_solve_for_each_channel, lion_nop_requires_solve_for_each_channel__ );
            BCORE_REGISTER_FEATURE( lion_nop_create_final );
            BCORE_REGISTER_FFUNC( lion_nop_create_final, lion_nop_create_final__ );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_ap );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_dp_a );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_dp_b );
            BCORE_REGISTER_FEATURE( lion_nop_type_vop_dp_c );
            BCORE_REGISTER_FEATURE( lion_nop_mcode_push_ap );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap, lion_nop_mcode_push_ap__ );
            BCORE_REGISTER_FEATURE( lion_nop_mcode_push_dp );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_dp, lion_nop_mcode_push_dp__ );
            BCORE_REGISTER_OBJECT( lion_nop_context_s );
            BCORE_REGISTER_SPECT( lion_nop );

            // group: lion_nop_ar0
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_zro_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar0_zro_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_zro_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_zro_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_one_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar0_one_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_one_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_one_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_literal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_literal_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_literal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_input_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_input_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_input_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar0_adaptive_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar0_adaptive_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar0_adaptive_s );
            BCORE_REGISTER_TRAIT( lion_nop_ar0, lion_nop );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_zro_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_one_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_literal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_input_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar0_adaptive_s );

            // group: lion_nop_ar1
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_identity_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_identity_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_identity_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_identity_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_neg_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_neg_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_neg_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_neg_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_neg_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_create_op_of_arn, lion_nop_ar1_neg_s_create_op_of_arn );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_neg_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_floor_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_floor_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_floor_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_floor_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_floor_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_floor_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_ceil_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_ceil_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_ceil_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_ceil_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_ceil_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_ceil_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_exp_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_exp_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_exp_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_exp_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_exp_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_exp_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_inv_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_inv_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_inv_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_inv_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_inv_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_inv_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_lgst_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_lgst_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_lgst_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_lgst_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_lgst_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_lgst_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_lgst_hard_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_lgst_hard_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_lgst_hard_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_lgst_hard_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_lgst_hard_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_lgst_hard_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_lgst_leaky_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_lgst_leaky_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_lgst_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_lgst_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_lgst_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_lgst_leaky_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_tanh_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_tanh_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_tanh_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_tanh_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_tanh_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_tanh_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_tanh_hard_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_tanh_hard_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_tanh_hard_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_tanh_hard_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_tanh_hard_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_tanh_hard_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_tanh_leaky_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_tanh_leaky_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_tanh_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_tanh_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_tanh_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_tanh_leaky_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_softplus_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_softplus_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_softplus_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_softplus_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_softplus_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_softplus_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_relu_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_relu_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_relu_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_relu_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_relu_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_relu_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_relu_leaky_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_relu_leaky_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_relu_leaky_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar1_relu_leaky_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar1_relu_leaky_s_type_vop_dp_a );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_relu_leaky_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_output_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_output_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_output_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_adaptive_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_adaptive_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_adaptive_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_create_final, lion_nop_ar1_adaptive_s_create_final );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_adaptive_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_dimof_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_dimof_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_dimof_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_dimof_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_dimof_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_random_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar1_random_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_random_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_random_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_random_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar1_cast_htp_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_class, lion_nop_ar1_cast_htp_s_class );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar1_cast_htp_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar1_cast_htp_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar1_cast_htp_s );
            BCORE_REGISTER_TRAIT( lion_nop_ar1, lion_nop );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_identity_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_neg_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_floor_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_ceil_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_exp_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_inv_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_lgst_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_lgst_hard_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_lgst_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_tanh_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_tanh_hard_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_tanh_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_softplus_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_relu_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_relu_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_output_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_adaptive_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_dimof_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_random_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar1_cast_htp_s );

            // group: lion_nop_ar2
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_add_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_add_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_add_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_add_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_add_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_add_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_add_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_sub_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_sub_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_sub_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_sub_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_sub_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_sub_s_type_vop_dp_b );
            BCORE_REGISTER_FFUNC( lion_nop_create_op_of_arn, lion_nop_ar2_sub_s_create_op_of_arn );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_sub_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_div_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_div_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_div_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_div_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_div_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_div_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_div_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_mul_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_mul_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_mul_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_mul_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_mul_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_bmul_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_bmul_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_bmul_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_bmul_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_bmul_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_equal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_equal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_equal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_equal_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_equal_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_equal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_larger_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_larger_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_larger_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_larger_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_larger_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_larger_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_larger_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_smaller_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_smaller_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_smaller_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_smaller_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_smaller_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_smaller_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_smaller_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_larger_equal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_larger_equal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_larger_equal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_larger_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_larger_equal_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_larger_equal_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_larger_equal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_smaller_equal_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_smaller_equal_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_smaller_equal_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_smaller_equal_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_smaller_equal_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_smaller_equal_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_smaller_equal_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_and_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_and_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_and_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_and_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_logic_and_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_logic_and_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_and_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_logic_or_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_logic_or_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_symbol, lion_nop_ar2_logic_or_s_symbol );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_ap, lion_nop_ar2_logic_or_s_type_vop_ap );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_logic_or_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_logic_or_s_type_vop_dp_b );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_logic_or_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_index_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_index_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_index_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_index_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_inc_order_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_inc_order_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_inc_order_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_inc_order_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_cat_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_cat_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_cat_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_cat_s );
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar2_recurrent_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar2_recurrent_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_requires_solve_for_each_channel, lion_nop_ar2_recurrent_s_requires_solve_for_each_channel );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar2_recurrent_s_solve );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_a, lion_nop_ar2_recurrent_s_type_vop_dp_a );
            BCORE_REGISTER_FFUNC( lion_nop_type_vop_dp_b, lion_nop_ar2_recurrent_s_type_vop_dp_b );
            BCORE_REGISTER_FFUNC( lion_nop_mcode_push_ap, lion_nop_ar2_recurrent_s_mcode_push_ap );
            BCORE_REGISTER_OBJECT( lion_nop_ar2_recurrent_s );
            BCORE_REGISTER_TRAIT( lion_nop_ar2, lion_nop );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_add_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_sub_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_div_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_mul_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_bmul_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_equal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_larger_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_smaller_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_larger_equal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_smaller_equal_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_and_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_logic_or_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_index_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_inc_order_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_cat_s );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar2_recurrent_s );

            // group: lion_nop_ar3
            BCORE_REGISTER_FFUNC( lion_nop_arity, lion_nop_ar3_branch_s_arity );
            BCORE_REGISTER_FFUNC( lion_nop_priority, lion_nop_ar3_branch_s_priority );
            BCORE_REGISTER_FFUNC( lion_nop_solve, lion_nop_ar3_branch_s_solve );
            BCORE_REGISTER_OBJECT( lion_nop_ar3_branch_s );
            BCORE_REGISTER_TRAIT( lion_nop_ar3, lion_nop );
            bcore_inst_s_get_typed( TYPEOF_lion_nop_ar3_branch_s );

            // --------------------------------------------------------------------
            // source: lion_nop_eval.h

            // group: lion_nop_eval
            BCORE_REGISTER_OBJECT( lion_nop_eval_result_s );
            BCORE_REGISTER_FEATURE( lion_nop_eval_run );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, lion_nop_eval_param_s_init_x );
            BCORE_REGISTER_OBJECT( lion_nop_eval_param_s );
            BCORE_REGISTER_FFUNC( lion_nop_eval_set_param, lion_nop_eval_generator_s_set_param );
            BCORE_REGISTER_FFUNC( lion_nop_eval_run, lion_nop_eval_generator_s_run );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_nop_eval_generator_s_main );
            BCORE_REGISTER_OBJECT( lion_nop_eval_generator_s );
            BCORE_REGISTER_FFUNC( lion_nop_eval_set_param, lion_nop_eval_show_param_s_set_param );
            BCORE_REGISTER_FFUNC( lion_nop_eval_run, lion_nop_eval_show_param_s_run );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_nop_eval_show_param_s_main );
            BCORE_REGISTER_OBJECT( lion_nop_eval_show_param_s );
            BCORE_REGISTER_FEATURE( lion_nop_eval_set_param );
            BCORE_REGISTER_OBJECT( lion_nop_eval_arr_s );
            BCORE_REGISTER_FFUNC( lion_nop_eval_set_param, lion_nop_eval_set_s_set_param );
            BCORE_REGISTER_FFUNC( lion_nop_eval_run, lion_nop_eval_set_s_run );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_nop_eval_set_s_main );
            BCORE_REGISTER_OBJECT( lion_nop_eval_set_s );
            BCORE_REGISTER_FFUNC( lion_nop_eval_run, lion_nop_eval_ar1_s_run );
            BCORE_REGISTER_FFUNC( lion_nop_eval_set_param, lion_nop_eval_ar1_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_nop_eval_ar1_s_main );
            BCORE_REGISTER_OBJECT( lion_nop_eval_ar1_s );
            BCORE_REGISTER_FFUNC( lion_nop_eval_run, lion_nop_eval_ar2_s_run );
            BCORE_REGISTER_FFUNC( lion_nop_eval_set_param, lion_nop_eval_ar2_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, lion_nop_eval_ar2_s_main );
            BCORE_REGISTER_OBJECT( lion_nop_eval_ar2_s );
            BCORE_REGISTER_SPECT( lion_nop_eval );
        }
        break;
        default: break;
    }
    return NULL;
}
