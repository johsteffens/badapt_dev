/** Author and Copyright 2020 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**********************************************************************************************************************/

#include "lion_adaptive.h"

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_s_arc_to_sink( const lion_adaptive_s* o, bcore_sink* sink )
{
    if( o->frame.mcode_log && *( aware_t* )o->frame.mcode_log == TYPEOF_st_s )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>\n", ( ( st_s* )o->frame.mcode_log )->sc );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_s_minfer( lion_adaptive_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    BLM_INIT();
    bhvm_holor_s* h_in  = BLM_CREATE( bhvm_holor_s );
    bhvm_holor_s* h_out = BLM_CREATE( bhvm_holor_s );

    bhvm_shape_s_set_data( &h_in->s, ( sz_t* )&in->size, 1 );
    bhvm_shape_s_set_data( &h_out->s, ( sz_t* )&out->size, 1 );

    if( out->size != o->out_size ) bmath_vf3_s_set_size( out, o->out_size );

    bhvm_value_s_fork_data( &h_in->v,  TYPEOF_f3_t, in->data,  in->size );
    bhvm_value_s_fork_data( &h_out->v, TYPEOF_f3_t, out->data, out->size );

    lion_net_frame_s_run_ap( &o->frame, ( const bhvm_holor_s** )&h_in, &h_out );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_s_bgrad_adapt( lion_adaptive_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    BLM_INIT();

    bhvm_holor_s* h_grad_in  = ( grad_in ) ? BLM_CREATE( bhvm_holor_s ) : NULL;
    bhvm_holor_s* h_grad_out = BLM_CREATE( bhvm_holor_s );

    if( grad_in ) bhvm_shape_s_set_data( &h_grad_in->s, ( sz_t* )&grad_in->size, 1 );
    bhvm_shape_s_set_data( &h_grad_out->s, ( sz_t* )&grad_out->size, 1 );

    if( h_grad_in ) bhvm_value_s_fork_data( &h_grad_in->v, TYPEOF_f3_t, grad_in->data, grad_in->size );
    bhvm_value_s_fork_data( &h_grad_out->v, TYPEOF_f3_t, grad_out->data, grad_out->size );

    lion_net_frame_s* frame = &o->frame;
    lion_net_frame_s_run_dp( frame, ( const bhvm_holor_s** )&h_grad_out, ( h_grad_in ) ? &h_grad_in : NULL );

    f3_t l2_reg_factor = ( 1.0 - o->dynamics.lambda_l2 * o->dynamics.epsilon );
    f3_t l1_reg_offset = o->dynamics.lambda_l1 * o->dynamics.epsilon;

    BFOR_SIZE( i, lion_net_frame_s_get_size_ada( frame ) )
    {
        bhvm_value_s* v_ap_ada = &lion_net_frame_s_get_ap_ada( frame, i )->v;
        bhvm_value_s* v_dp_ada = &lion_net_frame_s_get_dp_ada( frame, i )->v;
        bhvm_value_s_mul_scl_f3_acc( v_dp_ada, o->dynamics.epsilon, v_ap_ada );
        if( l2_reg_factor < 1.0 ) bhvm_value_s_mul_scl_f3( v_ap_ada, l2_reg_factor, v_ap_ada );
        if( l1_reg_offset > 0 )
        {
            sz_t size = v_ap_ada->size;
            vd_t data = v_ap_ada->data;
            switch( BKNIT_FA1( v_ap_ada->type ) )
            {
                case BKNIT_F2: for( sz_t j = 0; j < size; j++ ) { f2_t* dp = data; dp[ j ] += ( dp[ j ] > 0 ) ? -l1_reg_offset : l1_reg_offset; } break;
                case BKNIT_F3: for( sz_t j = 0; j < size; j++ ) { f3_t* dp = data; dp[ j ] += ( dp[ j ] > 0 ) ? -l1_reg_offset : l1_reg_offset; } break;
                default: BKNIT_FA1_ERR( v_ap_ada->type ); break;
            }
        }
        bhvm_value_s_zro( v_dp_ada );
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* lion_adaptive_builder_s_build( const lion_adaptive_builder_s* o )
{
    BLM_INIT();
    lion_adaptive_s* adaptive = lion_adaptive_s_create();

    bhvm_holor_s* h_in  = BLM_CREATE( bhvm_holor_s );

    bhvm_holor_s_set_type( h_in, TYPEOF_f3_t );
    bhvm_shape_s_set_data_na( &h_in->s, 1, o->in_size );

    bcore_source* source = NULL;

    switch( *(aware_t*)o->src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = BLM_A_PUSH( bcore_file_open_source_path( ( const bcore_file_path_s* )o->src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = BLM_A_PUSH( bcore_source_string_s_create_from_string( ( const st_s* )o->src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->src ) );
        }
        break;
    }

    lion_net_frame_s* frame = &adaptive->frame;

    bcore_sink_a_attach( &frame->mcode_log, ( bcore_sink* )st_s_create() );

    lion_net_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&h_in );

    ASSERT( lion_net_frame_s_get_size_en( frame ) == 1 );
    ASSERT( lion_net_frame_s_get_size_ex( frame ) == 1 );

    adaptive->in_size  = bhvm_shape_s_get_volume( &lion_net_frame_s_get_ap_en( frame, 0 )->s );
    adaptive->out_size = bhvm_shape_s_get_volume( &lion_net_frame_s_get_ap_ex( frame, 0 )->s );

    badapt_dynamics_std_s_copy( &adaptive->dynamics, &o->dynamics );

    adaptive->src = bcore_fork( o->src );

    BLM_RETURNV( badapt_adaptive*, ( badapt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_adaptive_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_adaptive" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "lion_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


