/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019 J.B.Steffens
 *  Last File Update: 2019-11-28T17:18:23Z
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

#include "haptive_planted.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: haptive_graph.h
#include "haptive_graph.h"

//----------------------------------------------------------------------------------------------------------------------
// group: haptive

BCORE_DEFINE_OBJECT_INST_P( haptive_context_s )
"aware haptive"
"{"
    "bcore_hmap_name_s hmap_name;"
    "bcore_arr_st_s arr_symbol_op2;"
    "haptive_sem_cell_s cell;"
    "bcore_arr_tp_s control_types;"
    "private bcore_mutex_s* randomizer_mutex;"
    "bl_t randomizer_is_locked;"
    "u2_t randomizer_rval;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op

BCORE_DEFINE_SPECT( haptive, haptive_op )
"{"
    "bcore_spect_header_s header;"
    "feature strict aware haptive_op : get_arity;"
    "feature aware haptive_op : get_class = haptive_op_get_class__;"
    "feature aware haptive_op : get_priority = haptive_op_get_priority__;"
    "feature aware haptive_op : get_symbol = haptive_op_get_symbol__;"
    "feature aware haptive_op : create_op_of_arn = haptive_op_create_op_of_arn__;"
    "feature aware haptive_op : solve;"
    "feature aware haptive_op : solve_each_channel = haptive_op_solve_each_channel__;"
    "feature aware haptive_op : create_final = haptive_op_create_final__;"
    "feature aware haptive_op : create_vm_op_ap_init = haptive_op_create_vm_op_ap_init__;"
    "feature aware haptive_op : create_vm_op_ap_init_set_idx = haptive_op_create_vm_op_ap_init_set_idx__;"
    "feature aware haptive_op : create_vm_op_ap = haptive_op_create_vm_op_ap__;"
    "feature aware haptive_op : create_vm_op_ap_set_idx = haptive_op_create_vm_op_ap_set_idx__;"
    "feature aware haptive_op : create_vm_op_dp = haptive_op_create_vm_op_dp__;"
    "feature aware haptive_op : create_vm_op_dp_set_idx = haptive_op_create_vm_op_dp_set_idx__;"
"}";


haptive_op* haptive_op_create_final__( const haptive_op* o, bhvm_hf3_s* h )
{
    haptive_op_ar0_literal_s* final = haptive_op_ar0_literal_s_create();
    final->h = bhvm_hf3_s_clone( h );
    return (haptive_op*)final;
}

bhvm_hf3_vm_op* haptive_op_create_vm_op_ap_init_set_idx__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx )
{
    bhvm_hf3_vm_op* op = haptive_op_a_create_vm_op_ap_init( o, vmf, arr_sig, arr_idx );
    if( op ) bhvm_hf3_vm_op_set_args( op, arr_sig, arr_idx );
    return op;
}

bhvm_hf3_vm_op* haptive_op_create_vm_op_ap_set_idx__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx )
{
    bhvm_hf3_vm_op* op = haptive_op_a_create_vm_op_ap( o, vmf, arr_sig, arr_idx );
    if( op ) bhvm_hf3_vm_op_set_args( op, arr_sig, arr_idx );
    return op;
}

bhvm_hf3_vm_op* haptive_op_create_vm_op_dp_set_idx__( const haptive_op* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id )
{
    bhvm_hf3_vm_op* op = haptive_op_a_create_vm_op_dp( o, vmf, arr_sig, arr_idx, ch_id );
    if( op ) bhvm_hf3_vm_op_set_args( op, arr_sig, arr_idx );
    return op;
}
//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar0

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar0_literal_s )
"aware haptive_op_ar0"
"{"
    "bhvm_hf3_s -> h;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar0_literal_s_solve( const haptive_op_ar0_literal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, bcore_fork( o->h ) );
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar0_input_s )
"aware haptive_op_ar0"
"{"
    "bhvm_hf3_s -> h;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar0_input_s_solve( const haptive_op_ar0_input_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, bcore_fork( o->h ) );
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar0_adaptive_s )
"aware haptive_op_ar0"
"{"
    "bhvm_hf3_s -> h;"
    "tp_t name;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar0_adaptive_s_solve( const haptive_op_ar0_adaptive_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    if( o->h )
    {
        bhvm_hf3_s_attach( r, bhvm_hf3_s_create() );
        bhvm_hf3_s_copy_shape( *r, o->h );
    }
    else
    {
        bhvm_hf3_s_detach( r );
    }

    return 0; // no need to settle
}

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar1

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_identity_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar1_identity_s_solve( const haptive_op_ar1_identity_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, bcore_fork( a[0] ) );
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_neg_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:create_op_of_arn;"
    "func haptive_op:get_arity;"
"}";

haptive_op* haptive_op_ar1_neg_s_create_op_of_arn( const haptive_op_ar1_neg_s* o, sz_t n )
{
    return ( n == 2 ) ? (haptive_op*)haptive_op_ar2_sub_s_create()
         : ( n == 1 ) ? (haptive_op*)haptive_op_ar1_neg_s_clone( o )
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_floor_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_ceil_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_exp_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_lgst_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_lgst_hard_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_lgst_leaky_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_tanh_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_tanh_hard_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_tanh_leaky_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_softplus_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_relu_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_relu_leaky_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_htp_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_class;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar1_htp_s_solve( const haptive_op_ar1_htp_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    if( a[0] )
    {
        #if ( HAPTIVE_GRAPH_OPTIMIZATION_LEVEL >= 1 )
            // TODO: Watch this solution's stability.
            bhvm_hf3_s_attach( r, bhvm_hf3_s_create() );
            **r = bhvm_hf3_init_fork( a[0]->d_data, a[0]->d_size, a[0]->d_space, a[0]->v_data, a[0]->v_size, a[0]->v_space, !a[0]->htp );
        #else
            bhvm_hf3_s_attach( r, bhvm_hf3_s_clone( a[0] ) );
            (*r)->htp = !(*r)->htp;
        #endif
    }
    else
    {
        bhvm_hf3_s_attach( r, NULL );
    }

    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_output_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar1_output_s_solve( const haptive_op_ar1_output_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, bcore_fork( a[0] ) );
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_adaptive_s )
"aware haptive_op_ar1"
"{"
    "tp_t name;"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_final;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar1_adaptive_s_solve( const haptive_op_ar1_adaptive_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, bcore_fork( a[0] ) );
    return ( *r ) ? 2 : 0; // settle with value 2 to keep subsequent graph intact
}

haptive_op* haptive_op_ar1_adaptive_s_create_final( const haptive_op_ar1_adaptive_s* o, bhvm_hf3_s* h )
{
    haptive_op_ar0_adaptive_s* final = haptive_op_ar0_adaptive_s_create();
    final->h    = bhvm_hf3_s_clone( h );
    final->name = o->name;
    return (haptive_op*)final;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_dimof_s )
"aware haptive_op_ar1"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar1_dimof_s_solve( const haptive_op_ar1_dimof_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, a[0] ? bhvm_hf3_s_create() : NULL );
    if( a[0] )
    {
        bhvm_hf3_s_set_scalar_f3( *r, a[0]->d_size ? a[0]->d_data[ a[0]->d_size - 1 ] : 1 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar1_random_s )
"aware haptive_op_ar1"
"{"
    "u2_t rseed = 1234;"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar1_random_s_solve( const haptive_op_ar1_random_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, a[0] ? bhvm_hf3_s_create() : NULL );
    if( a[0] )
    {
        haptive_context_s* context = haptive_get_context();
        ASSERT( context->randomizer_is_locked );
        if( context->randomizer_rval == 0 )
        {
            context->randomizer_rval = o->rseed;
        }
        bhvm_hf3_s_copy( *r, a[0] );
        if( !(*r)->v_size ) bhvm_hf3_s_fit_v_size( *r );
        bhvm_hf3_s_set_random( *r, 1.0, -0.5, 0.5, &context->randomizer_rval );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar2

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_bmul_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_bmul_s_solve( const haptive_op_ar2_bmul_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_set_shape_bmul( a[0], a[1], *r ) )
        {
            if( msg )
            {
                s2_t bhs_code = bhvm_hf3_s_bhs_code( a[0], a[1] );
                if( !bhvm_hf3_s_bmul_bhs_code_allowed( bhs_code ) )
                {
                    st_s_push_fa( msg, "Operation '");
                    bhvm_hf3_st_s_push_bhs_code( msg, bhs_code );
                    st_s_push_fa( msg, "' is not allowed.");
                }
            }
            return -1;
        }
        if( a[0]->v_data && a[1]->v_data )
        {
            bhvm_hf3_s_fit_v_size( *r );
            bhvm_hf3_s_bmul( a[0], a[1], *r );
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

bhvm_hf3_vm_op* haptive_op_ar2_bmul_s_create_vm_op_dp( const haptive_op_ar2_bmul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id )
{
    switch( ch_id )
    {
        case 'a': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_bmul_s_create();
        case 'b': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_cb_bmul_s_create();
        default: ERR_fa( "Invalid channel id '#<char>'", ch_id ); break;
    }
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_mul_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_mul_s_solve( const haptive_op_ar2_mul_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( a[0]->d_size == 0 )
        {
            bhvm_hf3_s_copy_d_data( *r, a[1] );
            if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
            {
                bhvm_hf3_s_fit_v_size( *r );
                bhvm_hf3_s_mul_scl( a[1], a[0]->v_data, *r );
            }
        }
        else if( a[1]->d_size == 0 )
        {
            bhvm_hf3_s_copy_d_data( *r, a[0] );
            if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
            {
                bhvm_hf3_s_fit_v_size( *r );
                bhvm_hf3_s_mul_scl( a[0], a[1]->v_data, *r );
            }
        }
        else
        {
            if( a[0]->d_size != a[1]->d_size ) return -1;
            if( bhvm_hf3_s_d_product( a[0] ) != bhvm_hf3_s_d_product( a[1] ) ) return -1;
            bhvm_hf3_s_copy_d_data( *r, a[0] );
            if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
            {
                bhvm_hf3_s_fit_v_size( *r );
                bhvm_hf3_s_hmul( a[0], a[1], *r );
            }
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_add_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_add_s_solve( const haptive_op_ar2_add_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( a[0]->d_size != a[1]->d_size ) return -1;
        if( bhvm_hf3_s_d_product( a[0] ) != bhvm_hf3_s_d_product( a[1] ) ) return -1;
        bhvm_hf3_s_copy_d_data( *r, a[0] );
        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
        {
            bhvm_hf3_s_fit_v_size( *r );
            bhvm_hf3_s_add( a[0], a[1], *r );
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

bhvm_hf3_vm_op* haptive_op_ar2_add_s_create_vm_op_dp( const haptive_op_ar2_add_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id )
{
    switch( ch_id )
    {
        case 'a': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_add_s_create();
        case 'b': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_cb_add_s_create();
        default: ERR_fa( "Invalid channel id '#<char>'", ch_id ); break;
    }
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_sub_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:create_vm_op_dp;"
    "func haptive_op:create_op_of_arn;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_sub_s_solve( const haptive_op_ar2_sub_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( a[0]->d_size != a[1]->d_size ) return -1;
        if( bhvm_hf3_s_d_product( a[0] ) != bhvm_hf3_s_d_product( a[1] ) ) return -1;
        bhvm_hf3_s_copy_d_data( *r, a[0] );
        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
        {
            bhvm_hf3_s_fit_v_size( *r );
            bhvm_hf3_s_sub( a[0], a[1], *r );
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

bhvm_hf3_vm_op* haptive_op_ar2_sub_s_create_vm_op_dp( const haptive_op_ar2_sub_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id )
{
    switch( ch_id )
    {
        case 'a': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_sub_s_create();
        case 'b': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_cb_sub_s_create();
        default: ERR_fa( "Invalid channel id '#<char>'", ch_id ); break;
    }
    return NULL;
}

haptive_op* haptive_op_ar2_sub_s_create_op_of_arn( const haptive_op_ar2_sub_s* o, sz_t n )
{
    return ( n == 2 ) ? (haptive_op*)haptive_op_ar2_sub_s_clone( o )
         : ( n == 1 ) ? (haptive_op*)haptive_op_ar1_neg_s_create()
         : NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_equal_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_equal_s_solve( const haptive_op_ar2_equal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r ) bhvm_hf3_s_set_scalar_f3( *r, bhvm_hf3_s_is_equal( a[0], a[1] ) ? 1 : 0 );
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_larger_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_larger_s_solve( const haptive_op_ar2_larger_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
        if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
        bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] > a[1]->v_data[0] ? 1 : 0 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_smaller_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_smaller_s_solve( const haptive_op_ar2_smaller_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
        if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
        bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] < a[1]->v_data[0] ? 1 : 0 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_larger_equal_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_larger_equal_s_solve( const haptive_op_ar2_larger_equal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
        if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
        bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] >= a[1]->v_data[0] ? 1 : 0 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_smaller_equal_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_smaller_equal_s_solve( const haptive_op_ar2_smaller_equal_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
        if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
        bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] <= a[1]->v_data[0] ? 1 : 0 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_logic_and_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_logic_and_s_solve( const haptive_op_ar2_logic_and_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
        if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
        bhvm_hf3_s_set_scalar_f3( *r, ( a[0]->v_data[0] > 0 ) && ( a[1]->v_data[0] > 0 ) ? 1 : 0 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_logic_or_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_symbol;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_logic_or_s_solve( const haptive_op_ar2_logic_or_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
        if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
        bhvm_hf3_s_set_scalar_f3( *r, ( a[0]->v_data[0] > 0 ) || ( a[1]->v_data[0] > 0 ) ? 1 : 0 );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_index_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_index_s_solve( const haptive_op_ar2_index_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( a[1]->v_size != 1 ) return -1;
        sz_t index = a[1]->v_data[ 0 ];
        if( a[0]->d_size == 0 ) return -1;
        if( index < 0 || index >= a[0]->d_data[ a[0]->d_size - 1 ] ) return -1;
        bhvm_hf3_s_clear( *r );
        bhvm_hf3_s_set_d_data( *r, a[0]->d_data, a[0]->d_size -1 );
        if( a[0]->v_data )
        {
            (*r)->v_size = bhvm_hf3_s_d_product( *r );
            (*r)->v_data = a[0]->v_data + index * (*r)->v_size;
            (*r)->v_space = 0;
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_inc_order_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_inc_order_s_solve( const haptive_op_ar2_inc_order_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( a[0]->v_size != 1 ) return -1;
        sz_t dim = a[0]->v_data[ 0 ];
        if( dim <= 0 ) return -1;
        bhvm_hf3_s_copy( *r, a[1] );
        bhvm_hf3_s_inc_order( *r, dim );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_cat_s )
"aware haptive_op_ar2"
"{"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_cat_s_solve( const haptive_op_ar2_cat_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
    if( *r )
    {
        if( !bhvm_hf3_s_set_shape_cat( a[0], a[1], *r ) ) return -1;
        if( a[0]->v_data && a[1]->v_data )
        {
            bhvm_hf3_s_fit_v_size( *r );
            bhvm_hf3_s_cat( a[0], a[1], *r );
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar2_recurrent_s )
"aware haptive_op_ar2"
"{"
    "tp_t name;"
    "func haptive_op:get_priority;"
    "func haptive_op:solve_each_channel;"
    "func haptive_op:solve;"
    "func haptive_op:create_vm_op_ap_init;"
    "func haptive_op:create_vm_op_ap;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar2_recurrent_s_solve( const haptive_op_ar2_recurrent_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    if( a[0] )
    {
        bhvm_hf3_s_attach( r, bhvm_hf3_s_create() );
        bhvm_hf3_s_copy_shape( *r, a[0] );
        if( a[1] )
        {
            if( !bhvm_hf3_s_shape_equal( a[0], a[1] ) ) return -1;
            return ( a[0]->v_size > 0 && a[1]->v_size > 0 ) ? 1 : 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if( a[1] ) return -1;
        bhvm_hf3_s_attach( r, NULL );
        return 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_op_ar3

BCORE_DEFINE_OBJECT_INST_P( haptive_op_ar3_branch_s )
"aware haptive_op_ar3"
"{"
    "func haptive_op:get_priority;"
    "func haptive_op:solve;"
    "func haptive_op:get_arity;"
"}";

s2_t haptive_op_ar3_branch_s_solve( const haptive_op_ar3_branch_s* o, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg )
{
    if( a[0] )
    {
        if( a[0]->v_size != 1 ) return -1;
        f3_t cond = a[0]->v_data[ 0 ];
        if( cond > 0 )
        {
            bhvm_hf3_s_attach( r, bcore_fork( a[1] ) );
        }
        else
        {
            bhvm_hf3_s_attach( r, bcore_fork( a[2] ) );
        }
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_sem

BCORE_DEFINE_OBJECT_INST_P( haptive_sem_link_s )
"aware haptive_sem"
"{"
    "tp_t name;"
    "private haptive_sem_link_s -> up;"
    "private haptive_sem_link_s -> dn;"
    "private vd_t cell;"
    "bl_t exit;"
    "func ^:get_name;"
"}";

tp_t haptive_sem_link_s_get_name( const haptive_sem_link_s* o )
{ return o->name; }

BCORE_DEFINE_OBJECT_INST_P( haptive_sem_links_s )
"aware bcore_array"
"{"
    "haptive_sem_link_s => [];"
    "func haptive_sem:get_link_by_name;"
    "func haptive_sem:name_exists;"
    "func haptive_sem:get_link_by_up;"
    "func haptive_sem:get_link_by_dn;"
    "func haptive_sem:get_index_by_link;"
    "func haptive_sem:count_open;"
"}";

haptive_sem_link_s* haptive_sem_links_s_get_link_by_name( haptive_sem_links_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return o->data[ i ];
    return NULL;
}

bl_t haptive_sem_links_s_name_exists( const haptive_sem_links_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return true;
    return false;
}

haptive_sem_link_s* haptive_sem_links_s_get_link_by_up( haptive_sem_links_s* o, haptive_sem_link_s* up )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->up == up ) return o->data[ i ];
    return NULL;
}

haptive_sem_link_s* haptive_sem_links_s_get_link_by_dn( haptive_sem_links_s* o, haptive_sem_link_s* dn )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->dn == dn ) return o->data[ i ];
    return NULL;
}

sz_t haptive_sem_links_s_get_index_by_link( haptive_sem_links_s* o, haptive_sem_link_s* link )
{
    BFOR_EACH( i, o ) if( o->data[ i ] == link ) return i;
    return -1;
}

sz_t haptive_sem_links_s_count_open( const haptive_sem_links_s* o )
{
    sz_t count = 0;
    BFOR_EACH( i, o ) count += ( o->data[ i ]->up == NULL );
    return count;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_sem_body_s )
"aware bcore_array"
"{"
    "aware haptive_sem=> [];"
    "func haptive_sem:name_exists;"
    "func haptive_sem:get_sem_by_name;"
"}";

bl_t haptive_sem_body_s_name_exists( const haptive_sem_body_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( haptive_sem_a_get_name( o->data[ i ] ) == name ) return true;
    return false;
}

haptive_sem* haptive_sem_body_s_get_sem_by_name( haptive_sem_body_s* o, tp_t name )
{
    BFOR_EACH( i, o ) if( haptive_sem_a_get_name( o->data[ i ] ) == name ) return o->data[ i ];
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_sem_cell_s )
"aware haptive_sem"
"{"
    "tp_t name;"
    "haptive_sem_links_s encs;"
    "haptive_sem_links_s excs;"
    "haptive_sem_body_s => body;"
    "aware haptive_op -> op;"
    "sz_t priority = 10;"
    "private haptive_sem_cell_s* parent;"
    "hidden bcore_source_point_s source_point;"
    "func ^:get_name;"
    "func ^:get_arity;"
    "func ^:get_enc_by_name;"
    "func ^:get_exc_by_name;"
    "func ^:get_enc_by_open;"
    "func ^:get_enc_by_dn;"
    "func ^:get_priority;"
    "func ^:get_cell_by_name;"
    "func ^:get_link_by_name;"
"}";

tp_t haptive_sem_cell_s_get_name( const haptive_sem_cell_s* o )
{ return o->name; }

haptive_sem_cell_s* haptive_sem_cell_s_get_cell_by_name( haptive_sem_cell_s* o, tp_t name )
{
    haptive_sem* sem = o->body ? haptive_sem_body_s_get_sem_by_name( o->body, name ) : NULL;
    if( sem && sem->_ == TYPEOF_haptive_sem_cell_s ) return ( haptive_sem_cell_s* )sem;
    if( o->parent ) return haptive_sem_cell_s_get_cell_by_name( o->parent, name );
    return NULL;
}

haptive_sem_link_s* haptive_sem_cell_s_get_link_by_name( haptive_sem_cell_s* o, tp_t name )
{
    haptive_sem* sem = o->body ? haptive_sem_body_s_get_sem_by_name( o->body, name ) : NULL;
    if( sem && sem->_ == TYPEOF_haptive_sem_link_s ) return ( haptive_sem_link_s* )sem;
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_sem_stack_flag_s )
"aware haptive_sem"
"{"
"}";

BCORE_DEFINE_SPECT( haptive, haptive_sem )
"{"
    "bcore_spect_header_s header;"
    "feature aware haptive_sem : get_name = haptive_sem_get_name__;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_ctr

BCORE_DEFINE_OBJECT_INST_P( haptive_ctr_node_s )
"aware bcore_array"
"{"
    "sz_t id = -1;"
    "private haptive_sem_cell_s -> cell;"
    "private haptive_ctr_node_s -> parent;"
    "haptive_ctr_node_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_ctr_tree_s )
"aware haptive_ctr"
"{"
    "sz_t id_base = 0;"
    "haptive_ctr_node_s => root;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_net

BCORE_DEFINE_OBJECT_INST_P( haptive_net_link_s )
"aware haptive_net"
"{"
    "hidden vd_t node;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_net_links_s )
"aware bcore_array"
"{"
    "haptive_net_link_s => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_net_node_s )
"aware haptive_net"
"{"
    "haptive_net_links_s upls;"
    "haptive_net_links_s dnls;"
    "bl_t flag = false;"
    "sz_t id;"
    "sz_t gid = -1;"
    "tp_t name;"
    "aware haptive_op -> op;"
    "bhvm_hf3_s-> h;"
    "bcore_source_point_s -> source_point;"
    "func ^:solve;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_net_nodes_s )
"aware bcore_array"
"{"
    "haptive_net_node_s => [];"
    "func haptive_net:get_by_id;"
"}";

haptive_net_node_s* haptive_net_nodes_s_get_by_id( haptive_net_nodes_s* o, sz_t id )
{
    BFOR_EACH( i, o ) if( o->data[ i ]->id == id ) return o->data[ i ];
    return NULL;
}

BCORE_DEFINE_OBJECT_INST_P( haptive_net_cell_s )
"aware haptive_net"
"{"
    "sz_t max_depth = 32768;"
    "haptive_net_nodes_s body;"
    "haptive_net_nodes_s encs;"
    "haptive_net_nodes_s excs;"
    "func ^:is_consistent;"
    "func ^:normalize;"
    "func ^:clear_flags;"
    "func ^:solve;"
    "func ^:clear_downlinks;"
    "func ^:set_downlinks;"
    "func bcore_inst_call:copy_x;"
    "func bcore_via_call:mutated;"
"}";

void haptive_net_cell_s_clear_flags( haptive_net_cell_s* o )
{
    BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
}

void haptive_net_cell_s_solve( haptive_net_cell_s* o )
{
    BFOR_EACH( i, &o->excs ) haptive_net_node_s_solve( o->excs.data[ i ] );
}

void haptive_net_cell_s_clear_downlinks( haptive_net_cell_s* o )
{
    BFOR_EACH( i, &o->body ) haptive_net_links_s_clear( &o->body.data[ i ]->dnls );
}

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_vm

BCORE_DEFINE_OBJECT_INST_P( haptive_vm_adaptive_s )
"aware badapt_adaptive"
"{"
    "st_s sig;"
    "aware => src;"
    "bhvm_hf3_vm_frame_s vm;"
    "badapt_dynamics_std_s dynamics;"
    "sz_t in_size;"
    "sz_t out_size;"
    "sz_t index_in;"
    "sz_t index_out;"
    "sz_t index_grad_out;"
    "bcore_arr_sz_s index_arr_adaptive;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:get_dynamics_std;"
    "func ^:set_dynamics_std;"
    "func ^:arc_to_sink;"
    "func ^:minfer;"
    "func ^:bgrad_adapt;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_vm_builder_s )
"aware badapt_builder"
"{"
    "st_s sig = \"( y => dim_y, a )\";"
    "aware => src;"
    "sz_t in_size;"
    "sz_t out_size;"
    "badapt_dynamics_std_s dynamics;"
    "u2_t rseed = 1234;"
    "func ^:get_in_size;"
    "func ^:set_in_size;"
    "func ^:get_out_size;"
    "func ^:set_out_size;"
    "func ^:build;"
"}";

/**********************************************************************************************************************/
// source: haptive_eval.h
#include "haptive_eval.h"

//----------------------------------------------------------------------------------------------------------------------
// group: haptive_eval

BCORE_DEFINE_OBJECT_INST_P( haptive_eval_grad_s )
"aware haptive_eval"
"{"
    "f3_t epsilon = 1E-2;"
    "bhvm_hf3_vm_frame_s -> vmf;"
    "bhvm_hf3_adl_s -> in;"
    "bhvm_hf3_adl_s -> out;"
    "s2_t verbosity = 1;"
    "f3_t max_dev = 1E-4;"
    "hidden aware bcore_sink -> log;"
    "func bcore_inst_call:init_x;"
    "func ^:run;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_eval_e2e_s )
"aware haptive_eval"
"{"
    "st_s name;"
    "st_s sig;"
    "aware => src;"
    "bhvm_hf3_adl_s => in;"
    "bhvm_hf3_adl_s => out;"
    "sz_t infer_cycles = 1;"
    "s2_t verbosity = 1;"
    "f3_t max_dev = 1E-8;"
    "hidden aware bcore_sink -> log;"
    "haptive_eval_grad_s => grad;"
    "func bcore_inst_call:init_x;"
    "func ^:run;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_eval_arr_s )
"aware bcore_array"
"{"
    "aware haptive_eval* [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( haptive_eval_set_s )
"aware haptive_eval"
"{"
    "st_s set_name;"
    "st_s sig;"
    "bhvm_hf3_adl_s => in;"
    "bhvm_hf3_adl_s => out;"
    "s2_t verbosity = -1;"
    "f3_t max_dev = -1;"
    "haptive_eval_arr_s arr;"
    "hidden aware bcore_sink -> log;"
    "func bcore_inst_call:init_x;"
    "func ^:run;"
    "func bcore_main:main;"
"}";

BCORE_DEFINE_SPECT( bcore_inst, haptive_eval )
"{"
    "bcore_spect_header_s header;"
    "feature aware haptive_eval : run;"
"}";

/**********************************************************************************************************************/

vd_t haptive_planted_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "haptive_planted" ) ) )
    {
        case TYPEOF_init1:
        {
            // Comment or remove line below to rebuild this target.
            bcore_const_x_set_d( typeof( "haptive_planted_hash" ), sr_tp( 2215593221 ) );

            // --------------------------------------------------------------------
            // source: haptive_graph.h

            // group: haptive
            BCORE_REGISTER_NAME( cell );
            BCORE_REGISTER_NAME( if );
            BCORE_REGISTER_NAME( then );
            BCORE_REGISTER_NAME( else );
            BCORE_REGISTER_NAME( op_class_regular );
            BCORE_REGISTER_NAME( op_class_cast );
            BCORE_REGISTER_NAME( mcode_name_infer );
            BCORE_REGISTER_NAME( mcode_name_bp_grad );
            BCORE_REGISTER_NAME( mcode_name_setup );
            BCORE_REGISTER_NAME( mcode_name_shelve );
            BCORE_REGISTER_NAME( mcode_name_zero_adaptive_grad );
            BCORE_REGISTER_NAME( mcode_name_cast );
            BCORE_REGISTER_NAME( mcode_name_cast_reverse );
            BCORE_REGISTER_NAME( mcode_name_ap_init );
            BCORE_REGISTER_NAME( holor_type_data );
            BCORE_REGISTER_NAME( holor_type_depletable );
            BCORE_REGISTER_NAME( holor_type_adaptive );
            BCORE_REGISTER_NAME( holor_type_adaptive_grad );
            BCORE_REGISTER_NAME( holor_type_cast );
            BCORE_REGISTER_OBJECT( haptive_context_s );
            BCORE_REGISTER_TRAIT( haptive, bcore_inst );

            // group: haptive_op
            BCORE_REGISTER_FEATURE( haptive_op_get_arity );
            BCORE_REGISTER_FEATURE( haptive_op_get_class );
            BCORE_REGISTER_FFUNC( haptive_op_get_class, haptive_op_get_class__ );
            BCORE_REGISTER_FEATURE( haptive_op_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_get_priority__ );
            BCORE_REGISTER_FEATURE( haptive_op_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_get_symbol__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_op_of_arn );
            BCORE_REGISTER_FFUNC( haptive_op_create_op_of_arn, haptive_op_create_op_of_arn__ );
            BCORE_REGISTER_FEATURE( haptive_op_solve );
            BCORE_REGISTER_FEATURE( haptive_op_solve_each_channel );
            BCORE_REGISTER_FFUNC( haptive_op_solve_each_channel, haptive_op_solve_each_channel__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_final );
            BCORE_REGISTER_FFUNC( haptive_op_create_final, haptive_op_create_final__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_vm_op_ap_init );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap_init, haptive_op_create_vm_op_ap_init__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_vm_op_ap_init_set_idx );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap_init_set_idx, haptive_op_create_vm_op_ap_init_set_idx__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_create_vm_op_ap__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_vm_op_ap_set_idx );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap_set_idx, haptive_op_create_vm_op_ap_set_idx__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_create_vm_op_dp__ );
            BCORE_REGISTER_FEATURE( haptive_op_create_vm_op_dp_set_idx );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp_set_idx, haptive_op_create_vm_op_dp_set_idx__ );
            BCORE_REGISTER_SPECT( haptive_op );

            // group: haptive_op_ar0
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar0_literal_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar0_literal_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar0_literal_s );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar0_input_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar0_input_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar0_input_s );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar0_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar0_adaptive_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar0_adaptive_s );
            BCORE_REGISTER_TRAIT( haptive_op_ar0, haptive_op );

            // group: haptive_op_ar1
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_identity_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_identity_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_identity_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_identity_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_identity_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_neg_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_neg_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_neg_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_neg_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_neg_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_create_op_of_arn, haptive_op_ar1_neg_s_create_op_of_arn );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_neg_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_neg_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_floor_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_floor_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_floor_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_floor_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_floor_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_floor_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_floor_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_ceil_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_ceil_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_ceil_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_ceil_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_ceil_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_ceil_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_ceil_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_exp_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_exp_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_exp_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_exp_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_exp_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_exp_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_exp_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_lgst_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_lgst_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_lgst_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_lgst_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_lgst_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_lgst_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_lgst_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_lgst_hard_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_lgst_hard_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_lgst_hard_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_lgst_hard_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_lgst_hard_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_lgst_hard_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_lgst_hard_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_lgst_leaky_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_lgst_leaky_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_lgst_leaky_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_lgst_leaky_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_lgst_leaky_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_lgst_leaky_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_lgst_leaky_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_tanh_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_tanh_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_tanh_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_tanh_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_tanh_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_tanh_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_tanh_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_tanh_hard_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_tanh_hard_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_tanh_hard_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_tanh_hard_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_tanh_hard_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_tanh_hard_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_tanh_hard_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_tanh_leaky_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_tanh_leaky_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_tanh_leaky_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_tanh_leaky_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_tanh_leaky_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_tanh_leaky_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_tanh_leaky_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_softplus_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_softplus_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_softplus_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_softplus_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_softplus_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_softplus_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_softplus_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_relu_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_relu_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_relu_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_relu_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_relu_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_relu_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_relu_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_relu_leaky_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_relu_leaky_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_relu_leaky_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_relu_leaky_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_relu_leaky_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_relu_leaky_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_relu_leaky_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_class, haptive_op_ar1_htp_s_get_class );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_htp_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_htp_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_htp_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_htp_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_htp_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_htp_s );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_output_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar1_output_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar1_output_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_output_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_output_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_adaptive_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_adaptive_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_adaptive_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_final, haptive_op_ar1_adaptive_s_create_final );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_adaptive_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_adaptive_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_dimof_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_dimof_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_dimof_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_dimof_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_dimof_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar1_random_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar1_random_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar1_random_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar1_random_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar1_random_s );
            BCORE_REGISTER_TRAIT( haptive_op_ar1, haptive_op );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_identity_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_neg_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_floor_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_ceil_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_exp_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_lgst_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_lgst_hard_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_lgst_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_tanh_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_tanh_hard_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_tanh_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_softplus_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_relu_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_relu_leaky_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_htp_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_output_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_adaptive_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_dimof_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar1_random_s );

            // group: haptive_op_ar2
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_bmul_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_bmul_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_bmul_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar2_bmul_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar2_bmul_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_bmul_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_bmul_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_mul_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_mul_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_mul_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar2_mul_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar2_mul_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_mul_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_mul_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_add_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_add_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_add_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar2_add_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar2_add_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_add_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_add_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_sub_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_sub_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_sub_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar2_sub_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_dp, haptive_op_ar2_sub_s_create_vm_op_dp );
            BCORE_REGISTER_FFUNC( haptive_op_create_op_of_arn, haptive_op_ar2_sub_s_create_op_of_arn );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_sub_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_sub_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_equal_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_equal_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_equal_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_equal_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_equal_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_larger_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_larger_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_larger_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_larger_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_larger_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_smaller_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_smaller_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_smaller_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_smaller_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_smaller_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_larger_equal_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_larger_equal_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_larger_equal_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_larger_equal_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_larger_equal_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_smaller_equal_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_smaller_equal_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_smaller_equal_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_smaller_equal_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_smaller_equal_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_logic_and_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_logic_and_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_logic_and_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_logic_and_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_logic_and_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_symbol, haptive_op_ar2_logic_or_s_get_symbol );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_logic_or_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_logic_or_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_logic_or_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_logic_or_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_index_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_index_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_index_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_index_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_inc_order_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_inc_order_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_inc_order_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_inc_order_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_cat_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_cat_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_cat_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_cat_s );
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar2_recurrent_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve_each_channel, haptive_op_ar2_recurrent_s_solve_each_channel );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar2_recurrent_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap_init, haptive_op_ar2_recurrent_s_create_vm_op_ap_init );
            BCORE_REGISTER_FFUNC( haptive_op_create_vm_op_ap, haptive_op_ar2_recurrent_s_create_vm_op_ap );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar2_recurrent_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar2_recurrent_s );
            BCORE_REGISTER_TRAIT( haptive_op_ar2, haptive_op );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_bmul_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_mul_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_add_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_sub_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_equal_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_larger_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_smaller_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_larger_equal_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_smaller_equal_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_logic_and_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_logic_or_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_index_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_inc_order_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_cat_s );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar2_recurrent_s );

            // group: haptive_op_ar3
            BCORE_REGISTER_FFUNC( haptive_op_get_priority, haptive_op_ar3_branch_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_op_solve, haptive_op_ar3_branch_s_solve );
            BCORE_REGISTER_FFUNC( haptive_op_get_arity, haptive_op_ar3_branch_s_get_arity );
            BCORE_REGISTER_OBJECT( haptive_op_ar3_branch_s );
            BCORE_REGISTER_TRAIT( haptive_op_ar3, haptive_op );
            bcore_inst_s_get_typed( TYPEOF_haptive_op_ar3_branch_s );

            // group: haptive_sem
            BCORE_REGISTER_FEATURE( haptive_sem_get_name );
            BCORE_REGISTER_FFUNC( haptive_sem_get_name, haptive_sem_get_name__ );
            BCORE_REGISTER_FFUNC( haptive_sem_get_name, haptive_sem_link_s_get_name );
            BCORE_REGISTER_OBJECT( haptive_sem_link_s );
            BCORE_REGISTER_FFUNC( haptive_sem_get_link_by_name, haptive_sem_links_s_get_link_by_name );
            BCORE_REGISTER_FFUNC( haptive_sem_name_exists, haptive_sem_links_s_name_exists );
            BCORE_REGISTER_FFUNC( haptive_sem_get_link_by_up, haptive_sem_links_s_get_link_by_up );
            BCORE_REGISTER_FFUNC( haptive_sem_get_link_by_dn, haptive_sem_links_s_get_link_by_dn );
            BCORE_REGISTER_FFUNC( haptive_sem_get_index_by_link, haptive_sem_links_s_get_index_by_link );
            BCORE_REGISTER_FFUNC( haptive_sem_count_open, haptive_sem_links_s_count_open );
            BCORE_REGISTER_OBJECT( haptive_sem_links_s );
            BCORE_REGISTER_FFUNC( haptive_sem_name_exists, haptive_sem_body_s_name_exists );
            BCORE_REGISTER_FFUNC( haptive_sem_get_sem_by_name, haptive_sem_body_s_get_sem_by_name );
            BCORE_REGISTER_OBJECT( haptive_sem_body_s );
            BCORE_REGISTER_FFUNC( haptive_sem_get_name, haptive_sem_cell_s_get_name );
            BCORE_REGISTER_FFUNC( haptive_sem_get_arity, haptive_sem_cell_s_get_arity );
            BCORE_REGISTER_FFUNC( haptive_sem_get_enc_by_name, haptive_sem_cell_s_get_enc_by_name );
            BCORE_REGISTER_FFUNC( haptive_sem_get_exc_by_name, haptive_sem_cell_s_get_exc_by_name );
            BCORE_REGISTER_FFUNC( haptive_sem_get_enc_by_open, haptive_sem_cell_s_get_enc_by_open );
            BCORE_REGISTER_FFUNC( haptive_sem_get_enc_by_dn, haptive_sem_cell_s_get_enc_by_dn );
            BCORE_REGISTER_FFUNC( haptive_sem_get_priority, haptive_sem_cell_s_get_priority );
            BCORE_REGISTER_FFUNC( haptive_sem_get_cell_by_name, haptive_sem_cell_s_get_cell_by_name );
            BCORE_REGISTER_FFUNC( haptive_sem_get_link_by_name, haptive_sem_cell_s_get_link_by_name );
            BCORE_REGISTER_OBJECT( haptive_sem_cell_s );
            BCORE_REGISTER_OBJECT( haptive_sem_stack_flag_s );
            BCORE_REGISTER_SPECT( haptive_sem );

            // group: haptive_ctr
            BCORE_REGISTER_OBJECT( haptive_ctr_node_s );
            BCORE_REGISTER_OBJECT( haptive_ctr_tree_s );
            BCORE_REGISTER_TRAIT( haptive_ctr, haptive );

            // group: haptive_net
            BCORE_REGISTER_OBJECT( haptive_net_link_s );
            BCORE_REGISTER_OBJECT( haptive_net_links_s );
            BCORE_REGISTER_FFUNC( haptive_net_solve, haptive_net_node_s_solve );
            BCORE_REGISTER_OBJECT( haptive_net_node_s );
            BCORE_REGISTER_FFUNC( haptive_net_get_by_id, haptive_net_nodes_s_get_by_id );
            BCORE_REGISTER_OBJECT( haptive_net_nodes_s );
            BCORE_REGISTER_FFUNC( haptive_net_is_consistent, haptive_net_cell_s_is_consistent );
            BCORE_REGISTER_FFUNC( haptive_net_normalize, haptive_net_cell_s_normalize );
            BCORE_REGISTER_FFUNC( haptive_net_clear_flags, haptive_net_cell_s_clear_flags );
            BCORE_REGISTER_FFUNC( haptive_net_solve, haptive_net_cell_s_solve );
            BCORE_REGISTER_FFUNC( haptive_net_clear_downlinks, haptive_net_cell_s_clear_downlinks );
            BCORE_REGISTER_FFUNC( haptive_net_set_downlinks, haptive_net_cell_s_set_downlinks );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, haptive_net_cell_s_copy_x );
            BCORE_REGISTER_FFUNC( bcore_via_call_mutated, haptive_net_cell_s_mutated );
            BCORE_REGISTER_OBJECT( haptive_net_cell_s );
            BCORE_REGISTER_TRAIT( haptive_net, haptive );

            // group: haptive_vm
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_in_size, haptive_vm_adaptive_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_out_size, haptive_vm_adaptive_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_dynamics_std, haptive_vm_adaptive_s_get_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_set_dynamics_std, haptive_vm_adaptive_s_set_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_arc_to_sink, haptive_vm_adaptive_s_arc_to_sink );
            BCORE_REGISTER_FFUNC( badapt_adaptive_minfer, haptive_vm_adaptive_s_minfer );
            BCORE_REGISTER_FFUNC( badapt_adaptive_bgrad_adapt, haptive_vm_adaptive_s_bgrad_adapt );
            BCORE_REGISTER_OBJECT( haptive_vm_adaptive_s );
            BCORE_REGISTER_FFUNC( badapt_builder_get_in_size, haptive_vm_builder_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_in_size, haptive_vm_builder_s_set_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_get_out_size, haptive_vm_builder_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_out_size, haptive_vm_builder_s_set_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_build, haptive_vm_builder_s_build );
            BCORE_REGISTER_OBJECT( haptive_vm_builder_s );
            BCORE_REGISTER_TRAIT( haptive_vm, haptive );

            // --------------------------------------------------------------------
            // source: haptive_eval.h

            // group: haptive_eval
            BCORE_REGISTER_FEATURE( haptive_eval_run );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, haptive_eval_grad_s_init_x );
            BCORE_REGISTER_FFUNC( haptive_eval_run, haptive_eval_grad_s_run );
            BCORE_REGISTER_FFUNC( bcore_main_main, haptive_eval_grad_s_main );
            BCORE_REGISTER_OBJECT( haptive_eval_grad_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, haptive_eval_e2e_s_init_x );
            BCORE_REGISTER_FFUNC( haptive_eval_run, haptive_eval_e2e_s_run );
            BCORE_REGISTER_FFUNC( bcore_main_main, haptive_eval_e2e_s_main );
            BCORE_REGISTER_OBJECT( haptive_eval_e2e_s );
            BCORE_REGISTER_OBJECT( haptive_eval_arr_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, haptive_eval_set_s_init_x );
            BCORE_REGISTER_FFUNC( haptive_eval_run, haptive_eval_set_s_run );
            BCORE_REGISTER_FFUNC( bcore_main_main, haptive_eval_set_s_main );
            BCORE_REGISTER_OBJECT( haptive_eval_set_s );
            BCORE_REGISTER_SPECT( haptive_eval );
        }
        break;
        default: break;
    }
    return NULL;
}
