/** This file was generated by the plant-compiler. Not suitable for manual editing.
 *
 *  Copyright and License:
 *    If a specification exists for the repository or folder in which the file is located,
 *    that specification shall apply. Otherwise, the Copyright and License of the associated
 *    source code files containing beth plant-code shall apply.
 */

#include "badapt_dev_planted.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: badapt_dev_problem
#include "badapt_dev_problem.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_problem_objects

BCORE_DEFINE_OBJECT_INST_P( badapt_problem_recurrent_abc_s )
"badapt_supplier"
"{"
    "aware_t _;"
    "sz_t index = 0;"
    "u2_t rval = 1234;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "aware badapt_loss* preferred_loss = badapt_loss_l2_s;"
    "func ^:preferred_loss;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:fetch_sample_tio;"
    "func ^:fetch_sample_vio;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_problem_recurrent_kjv_s )
"badapt_supplier"
"{"
    "aware_t _;"
    "aware bcore_source => source;"
    "bcore_arr_sz_s => charmap;"
    "st_s => charset;"
    "u0_t t_last_char = 0;"
    "u0_t v_last_char = 0;"
    "u2_t rval = 1234;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "aware badapt_loss* preferred_loss = badapt_loss_l2_s;"
    "func ^:preferred_loss;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:fetch_sample_tio;"
    "func ^:fetch_sample_vio;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_problem_recurrent_text_s )
"aware badapt_supplier"
"{"
    "st_s text_file;"
    "st_s ignore_line_char;"
    "aware bcore_source => source;"
    "bcore_arr_sz_s => charmap;"
    "st_s => charset;"
    "u0_t t_last_char = 0;"
    "u0_t v_last_char = 0;"
    "u2_t rval = 1234;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "aware badapt_loss* preferred_loss = badapt_loss_l2_s;"
    "func ^:preferred_loss;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:fetch_sample_tio;"
    "func ^:fetch_sample_vio;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_guide_char_encode_s )
"badapt_guide"
"{"
    "aware_t _;"
    "aware badapt_guide => guide_default = badapt_guide_std_s;"
    "bcore_arr_sz_s -> charmap;"
    "st_s -> charset;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "st_s txt_trigger;"
    "sz_t txt_size = 128;"
    "f3_t heat = 0.3;"
    "func ^:callback;"
"}";

/**********************************************************************************************************************/
// source: badapt_dev_ern
#include "badapt_dev_ern.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_ern

/**********************************************************************************************************************/
// source: badapt_dev_lstm
#include "badapt_dev_lstm.h"

/**********************************************************************************************************************/
// source: bsym
#include "bsym.h"

//----------------------------------------------------------------------------------------------------------------------
// group: bsym

BCORE_DEFINE_OBJECT_INST_P( bsym_source_info_s )
"aware bcore_inst"
"{"
    "aware bcore_source -> source;"
    "sz_t index;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op

BCORE_DEFINE_SPECT( bsym, bsym_op )
"{"
    "bcore_spect_header_s header;"
    "feature aware bsym_op : trace_to_sink = bsym_op_trace_to_sink__;"
    "feature strict aware bsym_op : get_arity;"
    "feature aware bsym_op : get_priority = bsym_op_get_priority__;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op_ar0

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar0_holor_s )
"aware bsym_op_ar0"
"{"
    "tp_t type;"
    "bmath_hf3_s hf3;"
    "func bsym_op:get_arity;"
    "func bsym_op:trace_to_sink;"
    "func ^:compute_hf3;"
    "func ^:get_hf3_type;"
"}";

void bsym_op_ar0_holor_s_trace_to_sink( const bsym_op_ar0_holor_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(#<sc_t>)", ifnameof( o->type ) );
    bmath_hf3_s_to_sink( &o->hf3, sink );
}

bl_t bsym_op_ar0_holor_s_compute_hf3( const bsym_op_ar0_holor_s* o, bmath_hf3_s* r )
{
    bmath_hf3_s_copy( r, &o->hf3 ); return true;
}

tp_t bsym_op_ar0_holor_s_get_hf3_type( const bsym_op_ar0_holor_s* o )
{
    return o->type;
}

BCORE_DEFINE_SPECT( bsym_op, bsym_op_ar0 )
"{"
    "bcore_spect_header_s header;"
    "feature strict aware bsym_op_ar0 : compute_hf3;"
    "feature aware bsym_op_ar0 : create_vm_operator = bsym_op_ar0_create_vm_operator__;"
    "feature aware bsym_op_ar0 : get_hf3_type;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op_ar1

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar1_linear_s )
"aware bsym_op_ar1"
"{"
    "func bsym_op:get_arity;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar1_tanh_s )
"aware bsym_op_ar1"
"{"
    "func bsym_op:get_arity;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

bl_t bsym_op_ar1_tanh_s_compute_hf3( const bsym_op_ar1_tanh_s* o, const bmath_hf3_s* a, bmath_hf3_s* r )
{
    bmath_hf3_s_copy_d_data( r, a );
    if( a->v_size > 0 )
    {
        bmath_hf3_s_fit_v_size( r );
        for( sz_t i = 0; i < a->v_size; i++ ) r->v_data[ i ] = tanh( a->v_data[ i ] );
    }
    return true;
}

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar1_dimof_s )
"aware bsym_op_ar1"
"{"
    "func bsym_op:get_arity;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
"}";

bl_t bsym_op_ar1_dimof_s_compute_hf3( const bsym_op_ar1_dimof_s* o, const bmath_hf3_s* a, bmath_hf3_s* r )
{
    if( bmath_hf3_s_d_product( a ) == 0 ) return false;
    bmath_hf3_s_set_d_size( r, 0 );
    bmath_hf3_s_fit_v_size( r );
    if( a->d_size > 0 )
    {
        r->v_data[ 0 ] = a->d_data[ a->d_size - 1 ];
    }
    else
    {
        r->v_data[ 0 ] = 1;
    }
    return true;
}

BCORE_DEFINE_SPECT( bsym_op, bsym_op_ar1 )
"{"
    "bcore_spect_header_s header;"
    "feature strict aware bsym_op_ar1 : get_symbol;"
    "feature aware bsym_op_ar1 : compute_hf3;"
    "feature aware bsym_op_ar1 : create_vm_operator = bsym_op_ar1_create_vm_operator__;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_op_ar2

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_bmul_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_bmul_htp_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_htp_bmul_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_htp_bmul_htp_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_mul_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_plus_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_op_ar2_minus_s )
"aware bsym_op_ar2"
"{"
    "func bsym_op:get_arity;"
    "func bsym_op:get_priority;"
    "func ^:get_symbol;"
    "func ^:compute_hf3;"
    "func ^:create_vm_operator;"
"}";

BCORE_DEFINE_SPECT( bsym_op, bsym_op_ar2 )
"{"
    "bcore_spect_header_s header;"
    "feature strict aware bsym_op_ar2 : get_symbol;"
    "feature aware bsym_op_ar2 : compute_hf3;"
    "feature aware bsym_op_ar2 : create_vm_operator = bsym_op_ar2_create_vm_operator__;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_net

BCORE_DEFINE_OBJECT_INST_P( bsym_net_hresult_s )
"aware bsym_net"
"{"
    "bmath_hf3_s => hf3;"
    "tp_t name;"
    "tp_t type;"
    "sz_t vm_index = -1;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_net_body_s )
"aware bcore_array"
"{"
    "aware bsym_net=> [];"
    "func bcore_inst_call:copy_x;"
"}";

void bsym_net_body_s_copy_x( bsym_net_body_s* o )
{
    for( sz_t i = 0; i < o->size; i++ ) bsym_net_a_set_body( o->data[ i ], o );
}

BCORE_DEFINE_OBJECT_INST_P( bsym_net_address_s )
"aware bcore_inst"
"{"
    "sz_t index;"
    "hidden vd_t body;"
    "func bsym_net:trace_get_node;"
    "func bsym_net:trace_to_sink;"
    "func bsym_net:trace_compute_hresult;"
    "func bsym_net:trace_clear_hresult;"
    "func bsym_net:trace_build_vm_proc;"
    "func bsym_net:get_net;"
"}";

bsym_net_node_s* bsym_net_address_s_trace_get_node( bsym_net_address_s* o )
{
    bsym_net* net = bsym_net_address_s_get_net( o );
    return net ? bsym_net_a_trace_get_node( net ) : NULL;
}

void bsym_net_address_s_trace_to_sink( const bsym_net_address_s* o, sz_t indent, bcore_sink* sink )
{
    bsym_net_node_s* node = bsym_net_address_s_trace_get_node( ( bsym_net_address_s* )o );
    if( node ) bsym_net_node_s_trace_to_sink( node, indent, sink );
}

bsym_net_hresult_s* bsym_net_address_s_trace_compute_hresult( bsym_net_address_s* o, bl_t force )
{
    bsym_net* net = bsym_net_address_s_get_net( o );
    return net ? bsym_net_a_trace_compute_hresult( net, force ) : NULL;
}

void bsym_net_address_s_trace_clear_hresult( bsym_net_address_s* o )
{
    bsym_net* net = bsym_net_address_s_get_net( o );
    if( net ) bsym_net_a_trace_clear_hresult( net );
}

void bsym_net_address_s_trace_build_vm_proc( bsym_net_address_s* o, bmath_hf3_vm_frame_s* vmf, tp_t proc_name )
{
    bsym_net* net = bsym_net_address_s_get_net( o );
    if( net ) bsym_net_a_trace_build_vm_proc( net, vmf, proc_name );
}

BCORE_DEFINE_OBJECT_INST_P( bsym_net_link_s )
"aware bsym_net"
"{"
    "tp_t name;"
    "bsym_net_address_s target;"
    "bsym_net_address_s root;"
    "bl_t flag;"
    "func ^:get_name;"
    "func ^:set_body;"
    "func ^:trace_get_node;"
    "func ^:trace_to_sink;"
    "func ^:trace_compute_hresult;"
    "func ^:trace_clear_hresult;"
    "func ^:trace_build_vm_proc;"
"}";

void bsym_net_link_s_set_body( bsym_net_link_s* o, bsym_net_body_s* body )
{
    if( o->target.body && o->target.body == o->root.body )
    {
        o->target.body = body;
    }
    o->root.body = body;
}

void bsym_net_link_s_trace_to_sink( const bsym_net_link_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(#<sc_t>) -> ", bsym_ifnameof( o->name ) );
    bsym_net_address_s_trace_to_sink( &o->target, indent, sink );
}

BCORE_DEFINE_OBJECT_INST_P( bsym_net_node_s )
"aware bcore_array"
"{"
    "tp_t name;"
    "bsym_net_address_s [] targets;"
    "bsym_net_address_s root;"
    "aware bsym_op* op;"
    "bsym_source_info_s source_info;"
    "bsym_net_hresult_s => hresult;"
    "private bsym_net_address_s -> new_root;"
    "func bsym_net:get_name;"
    "func bsym_net:set_body;"
    "func bsym_net:trace_get_node;"
    "func bsym_net:trace_to_sink;"
    "func bsym_net:trace_compute_hresult;"
    "func bsym_net:trace_clear_hresult;"
    "func bsym_net:trace_build_vm_proc;"
"}";

void bsym_net_node_s_set_body( bsym_net_node_s* o, bsym_net_body_s* body )
{
    for( sz_t i = 0; i < o->targets_size; i++ )
    {
        bsym_net_address_s* target = &o->targets_data[ i ];
        if( target->body && target->body == o->root.body )
        {
            target->body = body;
        }
    }
    o->root.body = body;
}

void bsym_net_node_s_trace_clear_hresult( bsym_net_node_s* o )
{
    bsym_net_hresult_s_detach( &o->hresult );
    for( sz_t i = 0; i < o->targets_size; i++ ) bsym_net_address_s_trace_clear_hresult( &o->targets_data[ i ] );
}

BCORE_DEFINE_SPECT( bsym, bsym_net )
"{"
    "bcore_spect_header_s header;"
    "feature aware bsym_net : trace_to_sink = bsym_net_trace_to_sink__;"
    "feature aware bsym_net : get_name = bsym_net_get_name__;"
    "feature aware bsym_net : set_body = bsym_net_set_body__;"
    "feature aware bsym_net : trace_get_node = bsym_net_trace_get_node__;"
    "feature aware bsym_net : trace_compute_hresult = bsym_net_trace_compute_hresult__;"
    "feature aware bsym_net : trace_clear_hresult = bsym_net_trace_clear_hresult__;"
    "feature aware bsym_net : trace_build_vm_proc = bsym_net_trace_build_vm_proc__;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_sem

BCORE_DEFINE_OBJECT_INST_P( bsym_sem_graph_s )
"aware bsym_sem"
"{"
    "tp_t name;"
    "sz_t args_in;"
    "sz_t args_out;"
    "bsym_net_body_s body;"
    "bsym_sem_graph_base_s => graph_base;"
    "hidden bcore_arr_st_s -> arr_symbol_op2;"
    "bsym_source_info_s source_info;"
    "sz_t priority = 10;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_sem_graph_base_s )
"aware bcore_array"
"{"
    "private bsym_sem_graph_base_s -> parent;"
    "aware bsym_sem=> [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_sem_stack_flag_s )
"aware bsym_sem"
"{"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: bsym_vm

BCORE_DEFINE_OBJECT_INST_P( bsym_vm_adaptive_s )
"aware badapt_adaptive"
"{"
    "st_s holograph_file;"
    "bmath_hf3_vm_frame_s vm;"
    "badapt_dynamics_std_s dynamics;"
    "sz_t in_size;"
    "sz_t out_size;"
    "sz_t in_index;"
    "sz_t out_index;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:get_dynamics_std;"
    "func ^:set_dynamics_std;"
    "func ^:minfer;"
    "func ^:bgrad_adapt;"
"}";

BCORE_DEFINE_OBJECT_INST_P( bsym_vm_builder_s )
"aware badapt_builder"
"{"
    "st_s holograph_file;"
    "st_s name_out_holor = \"output\";"
    "st_s name_out_size = \"out_size\";"
    "st_s name_in_holor = \"input\";"
    "sz_t in_size;"
    "sz_t out_size;"
    "u2_t rseed = 1234;"
    "badapt_dynamics_std_s dynamics;"
    "func ^:get_in_size;"
    "func ^:set_in_size;"
    "func ^:get_out_size;"
    "func ^:set_out_size;"
    "func ^:build;"
"}";

/**********************************************************************************************************************/

vd_t badapt_dev_planted_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_dev_planted" ) ) )
    {
        case TYPEOF_init1:
        {
            // Comment or remove line below to rebuild this target.
            bcore_const_x_set_d( typeof( "badapt_dev_planted_hash" ), sr_tp( 2702908698 ) );
            BCORE_REGISTER_FFUNC( badapt_supplier_preferred_loss, badapt_problem_recurrent_abc_s_preferred_loss );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_in_size, badapt_problem_recurrent_abc_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_out_size, badapt_problem_recurrent_abc_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_tio, badapt_problem_recurrent_abc_s_fetch_sample_tio );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_vio, badapt_problem_recurrent_abc_s_fetch_sample_vio );
            BCORE_REGISTER_OBJECT( badapt_problem_recurrent_abc_s );
            BCORE_REGISTER_FFUNC( badapt_supplier_preferred_loss, badapt_problem_recurrent_kjv_s_preferred_loss );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_in_size, badapt_problem_recurrent_kjv_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_out_size, badapt_problem_recurrent_kjv_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_tio, badapt_problem_recurrent_kjv_s_fetch_sample_tio );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_vio, badapt_problem_recurrent_kjv_s_fetch_sample_vio );
            BCORE_REGISTER_OBJECT( badapt_problem_recurrent_kjv_s );
            BCORE_REGISTER_FFUNC( badapt_supplier_preferred_loss, badapt_problem_recurrent_text_s_preferred_loss );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_in_size, badapt_problem_recurrent_text_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_out_size, badapt_problem_recurrent_text_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_tio, badapt_problem_recurrent_text_s_fetch_sample_tio );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_vio, badapt_problem_recurrent_text_s_fetch_sample_vio );
            BCORE_REGISTER_OBJECT( badapt_problem_recurrent_text_s );
            BCORE_REGISTER_FFUNC( badapt_guide_callback, badapt_guide_char_encode_s_callback );
            BCORE_REGISTER_OBJECT( badapt_guide_char_encode_s );
            BCORE_REGISTER_TRAIT( badapt_dev_problem_objects, bcore_inst );
            BCORE_REGISTER_TRAIT( badapt_dev_ern, bcore_inst );
            BCORE_REGISTER_NAME( link );
            BCORE_REGISTER_NAME( holor );
            BCORE_REGISTER_NAME( graph );
            BCORE_REGISTER_OBJECT( bsym_source_info_s );
            BCORE_REGISTER_TRAIT( bsym, bcore_inst );
            BCORE_REGISTER_FEATURE( bsym_op_trace_to_sink );
            BCORE_REGISTER_FFUNC( bsym_op_trace_to_sink, bsym_op_trace_to_sink__ );
            BCORE_REGISTER_FEATURE( bsym_op_get_arity );
            BCORE_REGISTER_FEATURE( bsym_op_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_get_priority__ );
            BCORE_REGISTER_SPECT( bsym_op );
            BCORE_REGISTER_NAME( adaptive );
            BCORE_REGISTER_NAME( buffer );
            BCORE_REGISTER_NAME( literal );
            BCORE_REGISTER_FEATURE( bsym_op_ar0_compute_hf3 );
            BCORE_REGISTER_FEATURE( bsym_op_ar0_create_vm_operator );
            BCORE_REGISTER_FFUNC( bsym_op_ar0_create_vm_operator, bsym_op_ar0_create_vm_operator__ );
            BCORE_REGISTER_FEATURE( bsym_op_ar0_get_hf3_type );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar0_holor_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_trace_to_sink, bsym_op_ar0_holor_s_trace_to_sink );
            BCORE_REGISTER_FFUNC( bsym_op_ar0_compute_hf3, bsym_op_ar0_holor_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar0_get_hf3_type, bsym_op_ar0_holor_s_get_hf3_type );
            BCORE_REGISTER_OBJECT( bsym_op_ar0_holor_s );
            BCORE_REGISTER_SPECT( bsym_op_ar0 );
            BCORE_REGISTER_FEATURE( bsym_op_ar1_get_symbol );
            BCORE_REGISTER_FEATURE( bsym_op_ar1_compute_hf3 );
            BCORE_REGISTER_FEATURE( bsym_op_ar1_create_vm_operator );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_create_vm_operator, bsym_op_ar1_create_vm_operator__ );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar1_linear_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_get_symbol, bsym_op_ar1_linear_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_compute_hf3, bsym_op_ar1_linear_s_compute_hf3 );
            BCORE_REGISTER_OBJECT( bsym_op_ar1_linear_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar1_tanh_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_get_symbol, bsym_op_ar1_tanh_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_compute_hf3, bsym_op_ar1_tanh_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_create_vm_operator, bsym_op_ar1_tanh_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar1_tanh_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar1_dimof_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_get_symbol, bsym_op_ar1_dimof_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar1_compute_hf3, bsym_op_ar1_dimof_s_compute_hf3 );
            BCORE_REGISTER_OBJECT( bsym_op_ar1_dimof_s );
            BCORE_REGISTER_SPECT( bsym_op_ar1 );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar1_linear_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar1_tanh_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar1_dimof_s );
            BCORE_REGISTER_FEATURE( bsym_op_ar2_get_symbol );
            BCORE_REGISTER_FEATURE( bsym_op_ar2_compute_hf3 );
            BCORE_REGISTER_FEATURE( bsym_op_ar2_create_vm_operator );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_create_vm_operator__ );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_bmul_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_bmul_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_bmul_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_bmul_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_bmul_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_bmul_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_bmul_htp_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_bmul_htp_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_bmul_htp_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_bmul_htp_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_bmul_htp_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_bmul_htp_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_htp_bmul_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_htp_bmul_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_htp_bmul_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_htp_bmul_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_htp_bmul_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_htp_bmul_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_htp_bmul_htp_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_htp_bmul_htp_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_htp_bmul_htp_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_htp_bmul_htp_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_htp_bmul_htp_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_htp_bmul_htp_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_mul_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_mul_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_mul_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_mul_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_mul_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_mul_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_plus_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_plus_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_plus_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_plus_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_plus_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_plus_s );
            BCORE_REGISTER_FFUNC( bsym_op_get_arity, bsym_op_ar2_minus_s_get_arity );
            BCORE_REGISTER_FFUNC( bsym_op_get_priority, bsym_op_ar2_minus_s_get_priority );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_get_symbol, bsym_op_ar2_minus_s_get_symbol );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_compute_hf3, bsym_op_ar2_minus_s_compute_hf3 );
            BCORE_REGISTER_FFUNC( bsym_op_ar2_create_vm_operator, bsym_op_ar2_minus_s_create_vm_operator );
            BCORE_REGISTER_OBJECT( bsym_op_ar2_minus_s );
            BCORE_REGISTER_SPECT( bsym_op_ar2 );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_bmul_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_bmul_htp_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_htp_bmul_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_htp_bmul_htp_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_mul_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_plus_s );
            bcore_inst_s_get_typed( TYPEOF_bsym_op_ar2_minus_s );
            BCORE_REGISTER_OBJECT( bsym_net_hresult_s );
            BCORE_REGISTER_FEATURE( bsym_net_trace_to_sink );
            BCORE_REGISTER_FFUNC( bsym_net_trace_to_sink, bsym_net_trace_to_sink__ );
            BCORE_REGISTER_FEATURE( bsym_net_get_name );
            BCORE_REGISTER_FFUNC( bsym_net_get_name, bsym_net_get_name__ );
            BCORE_REGISTER_FEATURE( bsym_net_set_body );
            BCORE_REGISTER_FFUNC( bsym_net_set_body, bsym_net_set_body__ );
            BCORE_REGISTER_FEATURE( bsym_net_trace_get_node );
            BCORE_REGISTER_FFUNC( bsym_net_trace_get_node, bsym_net_trace_get_node__ );
            BCORE_REGISTER_FEATURE( bsym_net_trace_compute_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_compute_hresult, bsym_net_trace_compute_hresult__ );
            BCORE_REGISTER_FEATURE( bsym_net_trace_clear_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_clear_hresult, bsym_net_trace_clear_hresult__ );
            BCORE_REGISTER_FEATURE( bsym_net_trace_build_vm_proc );
            BCORE_REGISTER_FFUNC( bsym_net_trace_build_vm_proc, bsym_net_trace_build_vm_proc__ );
            BCORE_REGISTER_FFUNC( bcore_inst_call_copy_x, bsym_net_body_s_copy_x );
            BCORE_REGISTER_OBJECT( bsym_net_body_s );
            BCORE_REGISTER_FFUNC( bsym_net_trace_get_node, bsym_net_address_s_trace_get_node );
            BCORE_REGISTER_FFUNC( bsym_net_trace_to_sink, bsym_net_address_s_trace_to_sink );
            BCORE_REGISTER_FFUNC( bsym_net_trace_compute_hresult, bsym_net_address_s_trace_compute_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_clear_hresult, bsym_net_address_s_trace_clear_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_build_vm_proc, bsym_net_address_s_trace_build_vm_proc );
            BCORE_REGISTER_FFUNC( bsym_net_get_net, bsym_net_address_s_get_net );
            BCORE_REGISTER_OBJECT( bsym_net_address_s );
            BCORE_REGISTER_FFUNC( bsym_net_get_name, bsym_net_link_s_get_name );
            BCORE_REGISTER_FFUNC( bsym_net_set_body, bsym_net_link_s_set_body );
            BCORE_REGISTER_FFUNC( bsym_net_trace_get_node, bsym_net_link_s_trace_get_node );
            BCORE_REGISTER_FFUNC( bsym_net_trace_to_sink, bsym_net_link_s_trace_to_sink );
            BCORE_REGISTER_FFUNC( bsym_net_trace_compute_hresult, bsym_net_link_s_trace_compute_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_clear_hresult, bsym_net_link_s_trace_clear_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_build_vm_proc, bsym_net_link_s_trace_build_vm_proc );
            BCORE_REGISTER_OBJECT( bsym_net_link_s );
            BCORE_REGISTER_NAME( infer );
            BCORE_REGISTER_FFUNC( bsym_net_get_name, bsym_net_node_s_get_name );
            BCORE_REGISTER_FFUNC( bsym_net_set_body, bsym_net_node_s_set_body );
            BCORE_REGISTER_FFUNC( bsym_net_trace_get_node, bsym_net_node_s_trace_get_node );
            BCORE_REGISTER_FFUNC( bsym_net_trace_to_sink, bsym_net_node_s_trace_to_sink );
            BCORE_REGISTER_FFUNC( bsym_net_trace_compute_hresult, bsym_net_node_s_trace_compute_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_clear_hresult, bsym_net_node_s_trace_clear_hresult );
            BCORE_REGISTER_FFUNC( bsym_net_trace_build_vm_proc, bsym_net_node_s_trace_build_vm_proc );
            BCORE_REGISTER_OBJECT( bsym_net_node_s );
            BCORE_REGISTER_SPECT( bsym_net );
            BCORE_REGISTER_OBJECT( bsym_sem_graph_s );
            BCORE_REGISTER_OBJECT( bsym_sem_graph_base_s );
            BCORE_REGISTER_OBJECT( bsym_sem_stack_flag_s );
            BCORE_REGISTER_TRAIT( bsym_sem, bsym );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_in_size, bsym_vm_adaptive_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_out_size, bsym_vm_adaptive_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_dynamics_std, bsym_vm_adaptive_s_get_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_set_dynamics_std, bsym_vm_adaptive_s_set_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_minfer, bsym_vm_adaptive_s_minfer );
            BCORE_REGISTER_FFUNC( badapt_adaptive_bgrad_adapt, bsym_vm_adaptive_s_bgrad_adapt );
            BCORE_REGISTER_OBJECT( bsym_vm_adaptive_s );
            BCORE_REGISTER_FFUNC( badapt_builder_get_in_size, bsym_vm_builder_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_in_size, bsym_vm_builder_s_set_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_get_out_size, bsym_vm_builder_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_out_size, bsym_vm_builder_s_set_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_build, bsym_vm_builder_s_build );
            BCORE_REGISTER_OBJECT( bsym_vm_builder_s );
            BCORE_REGISTER_TRAIT( bsym_vm, bsym );
        }
        break;
        default: break;
    }
    return NULL;
}
