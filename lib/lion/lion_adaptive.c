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
/// adaptive

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_s_arc_to_sink( const lion_adaptive_s* o, bcore_sink* sink )
{
    lion_frame_s_disassemble_to_sink( &o->frame, sink );
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

    lion_frame_s_run_ap( &o->frame, ( const bhvm_holor_s** )&h_in, &h_out );

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

    lion_frame_s* frame = &o->frame;
    lion_frame_s_run_dp( frame, ( const bhvm_holor_s** )&h_grad_out, ( h_grad_in ) ? &h_grad_in : NULL );

    f3_t l2_reg_factor = ( 1.0 - o->dynamics.lambda_l2 * o->dynamics.epsilon );
    f3_t l1_reg_offset = o->dynamics.lambda_l1 * o->dynamics.epsilon;

    BFOR_SIZE( i, lion_frame_s_get_size_ada( frame ) )
    {
        bhvm_value_s* v_ap_ada = &lion_frame_s_get_ap_ada( frame, i )->v;
        bhvm_value_s* v_dp_ada = &lion_frame_s_get_dp_ada( frame, i )->v;
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

    lion_frame_s* frame = &adaptive->frame;

    lion_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&h_in );

    ASSERT( lion_frame_s_get_size_en( frame ) == 1 );
    ASSERT( lion_frame_s_get_size_ex( frame ) == 1 );

    adaptive->in_size  = bhvm_shape_s_get_volume( &lion_frame_s_get_ap_en( frame, 0 )->s );
    adaptive->out_size = bhvm_shape_s_get_volume( &lion_frame_s_get_ap_ex( frame, 0 )->s );

    badapt_dynamics_std_s_copy( &adaptive->dynamics, &o->dynamics );

    adaptive->src = bcore_fork( o->src );

    BLM_RETURNV( badapt_adaptive*, ( badapt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive_cyclic

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_cyclic_s_arc_to_sink( const lion_adaptive_cyclic_s* o, bcore_sink* sink )
{
    lion_frame_cyclic_s_disassemble_to_sink( &o->frame, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_cyclic_s_dp_buffer_create( lion_adaptive_cyclic_s* o )
{
    bhvm_holor_adl_s_attach( &o->dp_buffer, bhvm_holor_adl_s_create() );
    bhvm_holor_adl_s_set_size( o->dp_buffer, o->frame.unroll_size );
    BFOR_EACH( i, o->dp_buffer )
    {
        bhvm_holor_s* h = o->dp_buffer->data[ i ] = bhvm_holor_s_create();
        bhvm_shape_s_set_data_na( &h->s, 1, o->out_size );
        bhvm_value_s_set_type_size( &h->v, TYPEOF_f3_t, o->out_size );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_cyclic_s_dp_buffer_reset( lion_adaptive_cyclic_s* o )
{
    if( !o->dp_buffer ) lion_adaptive_cyclic_s_dp_buffer_create( o );
    BFOR_EACH( i, o->dp_buffer )
    {
        bhvm_holor_s* h = o->dp_buffer->data[ i ] = bhvm_holor_s_create();
        bhvm_value_s_zro( &h->v );
    }
    o->dp_value = false;
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_cyclic_s_dp_buffer_apply( lion_adaptive_cyclic_s* o )
{
    lion_frame_cyclic_s* frame_cyclic = &o->frame;
    lion_frame_cyclic_s_run_dp_adl_flat( frame_cyclic, o->dp_buffer, NULL );

    lion_frame_s* frame = frame_cyclic->frame;

    f3_t l2_reg_factor = ( 1.0 - o->dynamics.lambda_l2 * o->dynamics.epsilon );
    f3_t l1_reg_offset = o->dynamics.lambda_l1 * o->dynamics.epsilon;

    BFOR_SIZE( i, lion_frame_s_get_size_ada( frame ) )
    {
        bhvm_value_s* v_ap_ada = &lion_frame_s_get_ap_ada( frame, i )->v;
        bhvm_value_s* v_dp_ada = &lion_frame_s_get_dp_ada( frame, i )->v;
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
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_cyclic_s_dp_buffer_apply_reset( lion_adaptive_cyclic_s* o )
{
    lion_adaptive_cyclic_s_dp_buffer_apply( o );
    lion_adaptive_cyclic_s_dp_buffer_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_cyclic_s_minfer( lion_adaptive_cyclic_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    BLM_INIT();
    if( o->dp_value && o->frame.unroll_index == 0 ) lion_adaptive_cyclic_s_dp_buffer_apply_reset( o );

    bhvm_holor_s* h_in  = BLM_CREATE( bhvm_holor_s );
    bhvm_holor_s* h_out = BLM_CREATE( bhvm_holor_s );

    bhvm_shape_s_set_data( &h_in->s, ( sz_t* )&in->size, 1 );
    bhvm_shape_s_set_data( &h_out->s, ( sz_t* )&out->size, 1 );

    if( out->size != o->out_size ) bmath_vf3_s_set_size( out, o->out_size );

    bhvm_value_s_fork_data( &h_in->v,  TYPEOF_f3_t, in->data,  in->size );
    bhvm_value_s_fork_data( &h_out->v, TYPEOF_f3_t, out->data, out->size );

    lion_frame_cyclic_s_run_ap( &o->frame, ( const bhvm_holor_s** )&h_in, &h_out );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_cyclic_s_bgrad_adapt( lion_adaptive_cyclic_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    ASSERT( !grad_in );

    if( !o->dp_buffer ) lion_adaptive_cyclic_s_dp_buffer_create( o );
    sz_t dp_index = ( o->frame.unroll_index == 0 ) ? o->frame.unroll_size - 1 : o->frame.unroll_index - 1;

    bhvm_holor_s* h = o->dp_buffer->data[ dp_index ];
    bhvm_value_s_cpy_data( &h->v, TYPEOF_f3_t, grad_out->data, grad_out->size );

    o->dp_value = true;

    if( o->frame.unroll_index == 0 ) lion_adaptive_cyclic_s_dp_buffer_apply_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_cyclic_s_reset( lion_adaptive_cyclic_s* o )
{
    lion_frame_cyclic_s_cyclic_reset( &o->frame );
    if( o->dp_value ) lion_adaptive_cyclic_s_dp_buffer_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_cyclic_s_get_weights_min_max( const lion_adaptive_cyclic_s* o, f3_t* arg_min, f3_t* arg_max )
{
    lion_frame_s* frame = o->frame.frame;
    f3_t max = 0;
    f3_t min = 0;

    BFOR_SIZE( i, lion_frame_s_get_size_ada( frame ) )
    {
        const bhvm_value_s* v = &lion_frame_s_get_ap_ada( frame, i )->v;
        f3_t v_max = bhvm_value_s_get_max_f3( v );
        f3_t v_min = bhvm_value_s_get_min_f3( v );
        max = ( i == 0 ) ? v_max : f3_max( max, v_max );
        min = ( i == 0 ) ? v_min : f3_min( min, v_min );
    }

    if( arg_max ) *arg_max = max;
    if( arg_min ) *arg_min = min;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* lion_adaptive_cyclic_builder_s_build( const lion_adaptive_cyclic_builder_s* o )
{
    BLM_INIT();
    lion_adaptive_cyclic_s* adaptive = lion_adaptive_cyclic_s_create();

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

    lion_frame_s* frame = BLM_CREATE( lion_frame_s );

    lion_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&h_in );

    ASSERT( lion_frame_s_get_size_en( frame ) == 1 );
    ASSERT( lion_frame_s_get_size_ex( frame ) == 1 );

    adaptive->in_size  = bhvm_shape_s_get_volume( &lion_frame_s_get_ap_en( frame, 0 )->s );
    adaptive->out_size = bhvm_shape_s_get_volume( &lion_frame_s_get_ap_ex( frame, 0 )->s );

    badapt_dynamics_std_s_copy( &adaptive->dynamics, &o->dynamics );

    adaptive->src = bcore_fork( o->src );

    lion_frame_cyclic_s* frame_cyclic = &adaptive->frame;
    lion_frame_cyclic_s_setup_from_frame( frame_cyclic, frame, o->unroll_size );

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


