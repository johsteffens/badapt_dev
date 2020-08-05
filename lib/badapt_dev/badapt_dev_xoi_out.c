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

#include "badapt_dev_xoi_out.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: badapt_dev_problem.h
#include "badapt_dev_problem.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_problem_objects

BCORE_DEFINE_OBJECT_INST_P( badapt_problem_recurrent_abc_s )
"badapt_supplier"
"{"
    "aware_t _;"
    "sz_t index = 0;"
    "u3_t rval = 1234;"
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
    "u3_t rval = 1234;"
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
    "hidden aware bcore_sink -> sink;"
    "func bcore_inst_call:init_x;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "st_s prefix = \"\";"
    "st_s postfix = \"\n\";"
    "st_s txt_trigger;"
    "sz_t txt_size = 128;"
    "sz_t line_size = 256;"
    "f3_t heat = 0.3;"
    "func ^:callback;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_problem_recurrent_utf8_s )
"aware badapt_supplier"
"{"
    "st_s text_file;"
    "aware bcore_source => source;"
    "u0_t t_last_char = 0;"
    "u0_t v_last_char = 0;"
    "u3_t rval = 1234;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "aware badapt_loss* preferred_loss = badapt_loss_l2_s;"
    "func ^:preferred_loss;"
    "func ^:get_in_size;"
    "func ^:get_out_size;"
    "func ^:fetch_sample_tio;"
    "func ^:fetch_sample_vio;"
"}";

BCORE_DEFINE_OBJECT_INST_P( badapt_guide_utf8_encode_s )
"badapt_guide"
"{"
    "aware_t _;"
    "aware badapt_guide => guide_default = badapt_guide_std_s;"
    "hidden aware bcore_sink -> sink;"
    "func bcore_inst_call:init_x;"
    "f3_t pos_tgt = 1.0;"
    "f3_t neg_tgt = 0.0;"
    "st_s txt_trigger;"
    "sz_t txt_size = 128;"
    "sz_t line_size = 256;"
    "f3_t heat = 0.3;"
    "func ^:callback;"
"}";

/**********************************************************************************************************************/
// source: badapt_dev_ern.h
#include "badapt_dev_ern.h"

//----------------------------------------------------------------------------------------------------------------------
// group: badapt_dev_ern

/**********************************************************************************************************************/
// source: badapt_dev_lstm.h
#include "badapt_dev_lstm.h"

/**********************************************************************************************************************/

vd_t badapt_general_signal_handler( const bcore_signal_s* o );

vd_t badapt_dev_xoi_out_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_dev_xoi_out" ) ) )
    {
        case TYPEOF_init1:
        {

            // --------------------------------------------------------------------
            // source: badapt_dev_problem.h

            // group: badapt_dev_problem_objects
            BCORE_REGISTER_FFUNC( badapt_supplier_preferred_loss, badapt_problem_recurrent_abc_s_preferred_loss );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_in_size, badapt_problem_recurrent_abc_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_out_size, badapt_problem_recurrent_abc_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_tio, badapt_problem_recurrent_abc_s_fetch_sample_tio );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_vio, badapt_problem_recurrent_abc_s_fetch_sample_vio );
            BCORE_REGISTER_OBJECT( badapt_problem_recurrent_abc_s );
            BCORE_REGISTER_FFUNC( badapt_supplier_preferred_loss, badapt_problem_recurrent_text_s_preferred_loss );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_in_size, badapt_problem_recurrent_text_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_out_size, badapt_problem_recurrent_text_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_tio, badapt_problem_recurrent_text_s_fetch_sample_tio );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_vio, badapt_problem_recurrent_text_s_fetch_sample_vio );
            BCORE_REGISTER_OBJECT( badapt_problem_recurrent_text_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, badapt_guide_char_encode_s_init_x );
            BCORE_REGISTER_FFUNC( badapt_guide_callback, badapt_guide_char_encode_s_callback );
            BCORE_REGISTER_OBJECT( badapt_guide_char_encode_s );
            BCORE_REGISTER_FFUNC( badapt_supplier_preferred_loss, badapt_problem_recurrent_utf8_s_preferred_loss );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_in_size, badapt_problem_recurrent_utf8_s_get_in_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_get_out_size, badapt_problem_recurrent_utf8_s_get_out_size );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_tio, badapt_problem_recurrent_utf8_s_fetch_sample_tio );
            BCORE_REGISTER_FFUNC( badapt_supplier_fetch_sample_vio, badapt_problem_recurrent_utf8_s_fetch_sample_vio );
            BCORE_REGISTER_OBJECT( badapt_problem_recurrent_utf8_s );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, badapt_guide_utf8_encode_s_init_x );
            BCORE_REGISTER_FFUNC( badapt_guide_callback, badapt_guide_utf8_encode_s_callback );
            BCORE_REGISTER_OBJECT( badapt_guide_utf8_encode_s );
            BCORE_REGISTER_TRAIT( badapt_dev_problem_objects, bcore_inst );

            // --------------------------------------------------------------------
            // source: badapt_dev_ern.h

            // group: badapt_dev_ern
            BCORE_REGISTER_TRAIT( badapt_dev_ern, bcore_inst );

            // --------------------------------------------------------------------
            // source: badapt_dev_lstm.h
        }
        break;
        case TYPEOF_push_dependencies:
        {
            ASSERT( o->object && ( *( aware_t* )o->object ) == TYPEOF_bcore_arr_fp_s );
            bcore_arr_fp_s* arr_fp = o->object;
            bcore_arr_fp_s_push( arr_fp, ( fp_t )badapt_general_signal_handler );
        }
        break;
        default: break;
    }
    return NULL;
}
// BETH_PLANT_SIGNATURE   21624527
