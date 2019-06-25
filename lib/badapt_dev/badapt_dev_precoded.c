/** This file was generated by the beth-precode-compiler. Not suitable for manual editing.
 *
 *  Copyright and License:
 *    If a specification exists for the repository or folder in which the file is located,
 *    that specification shall apply. Otherwise, the Copyright and License of the associated
 *    source code files containing beth-precode shall apply.
 */

#include "badapt_dev_precoded.h"
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
    "func badapt_supplier:preferred_loss;"
    "func badapt_supplier:get_in_size;"
    "func badapt_supplier:get_out_size;"
    "func badapt_supplier:fetch_sample_tio;"
    "func badapt_supplier:fetch_sample_vio;"
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
    "func badapt_supplier:preferred_loss;"
    "func badapt_supplier:get_in_size;"
    "func badapt_supplier:get_out_size;"
    "func badapt_supplier:fetch_sample_tio;"
    "func badapt_supplier:fetch_sample_vio;"
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
    "func badapt_supplier:preferred_loss;"
    "func badapt_supplier:get_in_size;"
    "func badapt_supplier:get_out_size;"
    "func badapt_supplier:fetch_sample_tio;"
    "func badapt_supplier:fetch_sample_vio;"
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
    "func badapt_guide:callback;"
"}";

/**********************************************************************************************************************/
// source: badapt_dev_ern
#include "badapt_dev_ern.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_ern

/**********************************************************************************************************************/
// source: badapt_dev_lstm
#include "badapt_dev_lstm.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_lstm

BCORE_DEFINE_OBJECT_INST_P( badapt_dev_lstm_layer_s )
"bcore_inst"
"{"
    "bmath_vf3_s v_x;"
    "bmath_vf3_s v_f;"
    "bmath_vf3_s v_i;"
    "bmath_vf3_s v_o;"
    "bmath_vf3_s v_q;"
    "bmath_vf3_s v_c;"
    "bmath_vf3_s v_d;"
    "bmath_vf3_s v_h;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_dev_lstm_arr_layer_s )
"aware bcore_array"
"{"
    "badapt_dev_lstm_layer_s => [] arr;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_dev_lstm_s )
"aware badapt_adaptive"
"{"
    "sz_t size_input;"
    "sz_t size_hidden;"
    "sz_t size_output;"
    "sz_t size_unfolded;"
    "badapt_dynamics_std_s dynamics;"
    "bmath_mf3_s w_fx;"
    "bmath_mf3_s w_fh;"
    "bmath_mf3_s w_ix;"
    "bmath_mf3_s w_ih;"
    "bmath_mf3_s w_ox;"
    "bmath_mf3_s w_oh;"
    "bmath_mf3_s w_qx;"
    "bmath_mf3_s w_qh;"
    "bmath_mf3_s w_rh;"
    "bmath_vf3_s b_f;"
    "bmath_vf3_s b_i;"
    "bmath_vf3_s b_o;"
    "bmath_vf3_s b_q;"
    "bmath_vf3_s b_r;"
    "aware badapt_activator => a_f;"
    "aware badapt_activator => a_i;"
    "aware badapt_activator => a_o;"
    "aware badapt_activator => a_q;"
    "aware badapt_activator => a_d;"
    "aware badapt_activator => a_r;"
    "hidden bmath_vf3_s v_r;"
    "hidden bmath_vf3_s d_v_r;"
    "hidden bmath_vf3_s d_v_f;"
    "hidden bmath_vf3_s d_v_i;"
    "hidden bmath_vf3_s d_v_o;"
    "hidden bmath_vf3_s d_v_q;"
    "hidden bmath_vf3_s d_v_c;"
    "hidden bmath_vf3_s d_v_d;"
    "hidden bmath_vf3_s d_v_h;"
    "hidden bmath_mf3_s d_w_fx;"
    "hidden bmath_mf3_s d_w_fh;"
    "hidden bmath_mf3_s d_w_ix;"
    "hidden bmath_mf3_s d_w_ih;"
    "hidden bmath_mf3_s d_w_ox;"
    "hidden bmath_mf3_s d_w_oh;"
    "hidden bmath_mf3_s d_w_qx;"
    "hidden bmath_mf3_s d_w_qh;"
    "hidden bmath_vf3_s d_b_f;"
    "hidden bmath_vf3_s d_b_i;"
    "hidden bmath_vf3_s d_b_o;"
    "hidden bmath_vf3_s d_b_q;"
    "hidden badapt_dev_lstm_arr_layer_s arr_layer;"
    "func :get_in_size;"
    "func :get_out_size;"
    "func :get_dynamics_std;"
    "func :set_dynamics_std;"
    "func :arc_to_sink;"
    "func :minfer;"
    "func :bgrad_adapt;"
    "func :reset;"
    "func :get_weights_min_max;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_dev_lstm_builder_s )
"aware badapt_builder"
"{"
    "sz_t size_input;"
    "sz_t size_hidden = 8;"
    "sz_t size_output = 1;"
    "sz_t size_unfolded = 2;"
    "badapt_dynamics_std_s dynamics;"
    "u2_t random_seed = 1234;"
    "f3_t random_range = 0.5;"
    "aware badapt_activator => a_f;"
    "aware badapt_activator => a_i;"
    "aware badapt_activator => a_o;"
    "aware badapt_activator => a_q;"
    "aware badapt_activator => a_d;"
    "aware badapt_activator => a_r;"
    "func bcore_inst_call:init_x;"
    "func :get_in_size;"
    "func :set_in_size;"
    "func :get_out_size;"
    "func :set_out_size;"
    "func :build;"
"}";

/**********************************************************************************************************************/
// source: badapt_sym
#include "badapt_sym.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_sym

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_items_s )
"aware bcore_array"
"{"
    "aware badapt_sym => [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_link_s )
"aware badapt_sym"
"{"
    "tp_t name;"
    "aware badapt_sym -> target;"
    "func :get_name;"
    "func :parse;"
    "func :to_sink;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_args_s )
"aware bcore_array"
"{"
    "badapt_sym_link_s [];"
    "func badapt_sym:parse;"
    "func badapt_sym:to_sink;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_dim_s )
"aware badapt_sym"
"{"
    "badapt_sym_link_s link;"
    "sz_t literal = -1;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_dims_s )
"aware bcore_array"
"{"
    "badapt_sym_dim_s [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_mutor_s )
"aware badapt_sym"
"{"
    "tp_t name;"
    "tp_t type;"
    "badapt_sym_dims_s dims;"
    "func :get_name;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_node_s )
"aware badapt_sym"
"{"
    "tp_t name;"
    "badapt_sym_args_s args_in;"
    "badapt_sym_args_s args_out;"
    "badapt_sym_items_s body;"
    "func :get_name;"
    "func bcore_inst_call:init_x;"
    "func bcore_inst_call:discard_e;"
    "func :parse;"
    "func :to_sink;"
"}";

void badapt_sym_node_s_init_x( badapt_sym_node_s* o )
{
    badapt_sym_items_s_clear( &o->body );
    badapt_sym_args_s_clear( &o->args_in );
    badapt_sym_args_s_clear( &o->args_out );
}

void badapt_sym_node_s_discard_e( badapt_sym_node_s* o )
{
    badapt_sym_items_s_clear( &o->body );
    badapt_sym_args_s_clear( &o->args_in );
    badapt_sym_args_s_clear( &o->args_out );
}

BCORE_DEFINE_OBJECT_INST_P( badapt_sym_frame_s )
"aware badapt_sym"
"{"
    "bcore_hmap_name_s hmap_name;"
    "badapt_sym_node_s root;"
    "func bcore_inst_call:discard_e;"
    "func :parse;"
    "func :to_sink;"
"}";

BCORE_DEFINE_SPECT( bcore_inst, badapt_sym )
"{"
    "bcore_spect_header_s header;"
    "feature aware badapt_sym : get_name;"
    "feature aware badapt_sym : parse;"
    "feature aware badapt_sym : to_sink;"
"}";

/**********************************************************************************************************************/

vd_t badapt_dev_precoded_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_dev_precoded" ) ) )
    {
        case TYPEOF_init1:
        {
            // Comment or remove line below to rebuild this target.
            bcore_const_x_set_d( typeof( "badapt_dev_precoded_hash" ), sr_tp( 158103379 ) );
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
            BCORE_REGISTER_OBJECT( badapt_dev_lstm_layer_s );
            BCORE_REGISTER_OBJECT( badapt_dev_lstm_arr_layer_s );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_in_size, badapt_dev_lstm_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_out_size, badapt_dev_lstm_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_dynamics_std, badapt_dev_lstm_s_get_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_set_dynamics_std, badapt_dev_lstm_s_set_dynamics_std );
            BCORE_REGISTER_FFUNC( badapt_adaptive_arc_to_sink, badapt_dev_lstm_s_arc_to_sink );
            BCORE_REGISTER_FFUNC( badapt_adaptive_minfer, badapt_dev_lstm_s_minfer );
            BCORE_REGISTER_FFUNC( badapt_adaptive_bgrad_adapt, badapt_dev_lstm_s_bgrad_adapt );
            BCORE_REGISTER_FFUNC( badapt_adaptive_reset, badapt_dev_lstm_s_reset );
            BCORE_REGISTER_FFUNC( badapt_adaptive_get_weights_min_max, badapt_dev_lstm_s_get_weights_min_max );
            BCORE_REGISTER_OBJECT( badapt_dev_lstm_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, badapt_dev_lstm_builder_s_init_x );
            BCORE_REGISTER_FFUNC( badapt_builder_get_in_size, badapt_dev_lstm_builder_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_in_size, badapt_dev_lstm_builder_s_set_in_size );
            BCORE_REGISTER_FFUNC( badapt_builder_get_out_size, badapt_dev_lstm_builder_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_set_out_size, badapt_dev_lstm_builder_s_set_out_size );
            BCORE_REGISTER_FFUNC( badapt_builder_build, badapt_dev_lstm_builder_s_build );
            BCORE_REGISTER_OBJECT( badapt_dev_lstm_builder_s );
            BCORE_REGISTER_FEATURE( badapt_sym_get_name );
            BCORE_REGISTER_FEATURE( badapt_sym_parse );
            BCORE_REGISTER_FEATURE( badapt_sym_to_sink );
            BCORE_REGISTER_OBJECT( badapt_sym_items_s );
            BCORE_REGISTER_FFUNC( badapt_sym_get_name, badapt_sym_link_s_get_name );
            BCORE_REGISTER_FFUNC( badapt_sym_parse, badapt_sym_link_s_parse );
            BCORE_REGISTER_FFUNC( badapt_sym_to_sink, badapt_sym_link_s_to_sink );
            BCORE_REGISTER_OBJECT( badapt_sym_link_s );
            BCORE_REGISTER_FFUNC( badapt_sym_parse, badapt_sym_args_s_parse );
            BCORE_REGISTER_FFUNC( badapt_sym_to_sink, badapt_sym_args_s_to_sink );
            BCORE_REGISTER_OBJECT( badapt_sym_args_s );
            BCORE_REGISTER_OBJECT( badapt_sym_dim_s );
            BCORE_REGISTER_OBJECT( badapt_sym_dims_s );
            BCORE_REGISTER_FFUNC( badapt_sym_get_name, badapt_sym_mutor_s_get_name );
            BCORE_REGISTER_OBJECT( badapt_sym_mutor_s );
            BCORE_REGISTER_FFUNC( badapt_sym_get_name, badapt_sym_node_s_get_name );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, badapt_sym_node_s_init_x );
            BCORE_REGISTER_FFUNC( bcore_inst_call_discard_e, badapt_sym_node_s_discard_e );
            BCORE_REGISTER_FFUNC( badapt_sym_parse, badapt_sym_node_s_parse );
            BCORE_REGISTER_FFUNC( badapt_sym_to_sink, badapt_sym_node_s_to_sink );
            BCORE_REGISTER_OBJECT( badapt_sym_node_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_discard_e, badapt_sym_frame_s_discard_e );
            BCORE_REGISTER_FFUNC( badapt_sym_parse, badapt_sym_frame_s_parse );
            BCORE_REGISTER_FFUNC( badapt_sym_to_sink, badapt_sym_frame_s_to_sink );
            BCORE_REGISTER_OBJECT( badapt_sym_frame_s );
            BCORE_REGISTER_SPECT( badapt_sym );
        }
        break;
        default: break;
    }
    return NULL;
}
