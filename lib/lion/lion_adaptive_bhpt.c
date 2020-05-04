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

#include "lion_adaptive_bhpt.h"

/**********************************************************************************************************************/
/// adaptive

// ---------------------------------------------------------------------------------------------------------------------

#ifdef TYPEOF_lion_adaptive_bhpt

void lion_adaptive_bhpt_s_axon_pass( lion_adaptive_bhpt_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex )
{
    lion_frame_s_run_ap( &o->frame, ( const bhvm_holor_s** )&ax_en, 1, &ax_ex, 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_dendrite_pass( lion_adaptive_bhpt_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en )
{
    lion_frame_s_run_dp( &o->frame, ( const bhvm_holor_s** )&ag_ex, 1, ( ag_en ) ? &ag_en : NULL, ( ag_en ) ? 1 : 0 );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_cyclic_reset( lion_adaptive_bhpt_s* o )
{
    lion_frame_s_cyclic_reset( &o->frame );
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptor_probe_s* lion_adaptive_bhpt_s_get_adaptor_probe( const lion_adaptive_bhpt_s* o, bhpt_adaptor_probe_s* probe )
{
    bhpt_adaptor_probe_s_set_size( probe, lion_frame_s_get_size_ada( &o->frame ) );
    lion_frame_s* frame = ( lion_frame_s* )&o->frame;
    ASSERT( frame->setup );
    BFOR_EACH( i, probe )
    {
        probe->data[ i ].axon = lion_frame_s_get_ap_ada( frame, i );
        probe->data[ i ].grad = lion_frame_s_get_dp_ada( frame, i );
    }
    return probe;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_status_to_sink( const lion_adaptive_bhpt_s* o, sz_t verbosity, bcore_sink* sink )
{
    if( verbosity >= 1 )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( o->_ ) );
    }

    if( verbosity >= 10 )
    {
        lion_frame_s_disassemble_to_sink( &o->frame, sink );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptive* lion_adaptive_bhpt_builder_s_create_adaptive( const lion_adaptive_bhpt_builder_s* o )
{
    BLM_INIT();
    lion_adaptive_bhpt_s* adaptive = lion_adaptive_bhpt_s_create();

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

    bhvm_holor_s_copy( &adaptive->holor_frame_en, &o->holor_frame_en );
    bhvm_holor_s_copy( &adaptive->holor_frame_ex, &o->holor_frame_ex );

    lion_frame_s* frame = &adaptive->frame;
    const bhvm_holor_s* holor_frame_en = &o->holor_frame_en;
    lion_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&holor_frame_en, 1 );

    ASSERT( lion_frame_s_get_size_en( frame ) == 1 );
    ASSERT( lion_frame_s_get_size_ex( frame ) == 1 );

    ASSERT( bhvm_shape_s_is_equal( &o->holor_frame_en.s, &lion_frame_s_get_ap_en( frame, 0 )->s ) );
    ASSERT( bhvm_shape_s_get_volume( &o->holor_frame_ex.s ) == bhvm_shape_s_get_volume( &lion_frame_s_get_ap_ex( frame, 0 )->s ) );

    adaptive->src = bcore_fork( o->src );

    BLM_RETURNV( bhpt_adaptive*, ( bhpt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive_bhpt_cyclic

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_bhpt_cyclic_s_dp_buffer_create( lion_adaptive_bhpt_cyclic_s* o )
{
    bhvm_holor_adl_s_attach( &o->dp_buffer, bhvm_holor_adl_s_create() );
    bhvm_holor_adl_s_set_size( o->dp_buffer, o->frame.unroll_size );
    BFOR_EACH( i, o->dp_buffer )
    {
        bhvm_holor_s* h = o->dp_buffer->data[ i ] = bhvm_holor_s_clone( &o->holor_frame_ex );
        bhvm_holor_s_fit_size( h );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_bhpt_cyclic_s_dp_buffer_reset( lion_adaptive_bhpt_cyclic_s* o )
{
    if( !o->dp_buffer ) lion_adaptive_bhpt_cyclic_s_dp_buffer_create( o );
    BFOR_EACH( i, o->dp_buffer ) bhvm_value_s_zro( &o->dp_buffer->data[ i ]->v );
    o->dp_value = false;
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_bhpt_cyclic_s_dp_buffer_apply( lion_adaptive_bhpt_cyclic_s* o )
{
    lion_frame_cyclic_s_run_dp_adl_flat( &o->frame, o->dp_buffer, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

static void lion_adaptive_bhpt_cyclic_s_dp_buffer_apply_reset( lion_adaptive_bhpt_cyclic_s* o )
{
    lion_adaptive_bhpt_cyclic_s_dp_buffer_apply( o );
    lion_adaptive_bhpt_cyclic_s_dp_buffer_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_cyclic_s_axon_pass( lion_adaptive_bhpt_cyclic_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex )
{
    lion_frame_cyclic_s_run_ap( &o->frame, ( const bhvm_holor_s** )&ax_en, 1, &ax_ex, 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_cyclic_s_dendrite_pass( lion_adaptive_bhpt_cyclic_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en )
{
    ASSERT( !ag_en );

    if( !o->dp_buffer ) lion_adaptive_bhpt_cyclic_s_dp_buffer_create( o );
    sz_t dp_index = ( o->frame.unroll_index == 0 ) ? o->frame.unroll_size - 1 : o->frame.unroll_index - 1;

    bhvm_holor_s* h = o->dp_buffer->data[ dp_index ];
    bhvm_value_s_cpy( &ag_ex->v, &h->v );
    o->dp_value = true;

    if( o->frame.unroll_index == 0 ) lion_adaptive_bhpt_cyclic_s_dp_buffer_apply_reset( o );

}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_cyclic_s_cyclic_reset( lion_adaptive_bhpt_cyclic_s* o )
{
    lion_frame_cyclic_s_cyclic_reset( &o->frame );
    if( o->dp_value ) lion_adaptive_bhpt_cyclic_s_dp_buffer_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptor_probe_s* lion_adaptive_bhpt_cyclic_s_get_adaptor_probe( const lion_adaptive_bhpt_cyclic_s* o, bhpt_adaptor_probe_s* probe )
{
    bhpt_adaptor_probe_s_set_size( probe, lion_frame_cyclic_s_get_size_ada( &o->frame ) );

    lion_frame_s* frame = o->frame.frame;

    ASSERT( frame->setup );
    BFOR_EACH( i, probe )
    {
        probe->data[ i ].axon = lion_frame_s_get_ap_ada( frame, i );
        probe->data[ i ].grad = lion_frame_s_get_dp_ada( frame, i );
    }
    return probe;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_cyclic_s_status_to_sink( const lion_adaptive_bhpt_cyclic_s* o, sz_t verbosity, bcore_sink* sink )
{
    if( verbosity >= 1 )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( o->_ ) );
    }

    if( verbosity >= 10 )
    {
        lion_frame_cyclic_s_disassemble_to_sink( &o->frame, sink );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptive* lion_adaptive_bhpt_cyclic_builder_s_create_adaptive( const lion_adaptive_bhpt_cyclic_builder_s* o )
{
    BLM_INIT();
    lion_adaptive_bhpt_cyclic_s* adaptive = lion_adaptive_bhpt_cyclic_s_create();

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

    bhvm_holor_s_copy( &adaptive->holor_frame_en, &o->holor_frame_en );
    bhvm_holor_s_copy( &adaptive->holor_frame_ex, &o->holor_frame_ex );

    lion_frame_s* frame = BLM_CREATE( lion_frame_s );
    const bhvm_holor_s* holor_frame_en = &o->holor_frame_en;
    lion_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&holor_frame_en, 1 );

    ASSERT( lion_frame_s_get_size_en( frame ) == 1 );
    ASSERT( lion_frame_s_get_size_ex( frame ) == 1 );

    ASSERT( bhvm_shape_s_is_equal( &o->holor_frame_en.s, &lion_frame_s_get_ap_en( frame, 0 )->s ) );
    ASSERT( bhvm_shape_s_get_volume( &o->holor_frame_ex.s ) == bhvm_shape_s_get_volume( &lion_frame_s_get_ap_ex( frame, 0 )->s ) );

    adaptive->src = bcore_fork( o->src );

    lion_frame_cyclic_s* frame_cyclic = &adaptive->frame;
    lion_frame_cyclic_s_setup_from_frame( frame_cyclic, frame, o->unroll_size );

    BLM_RETURNV( bhpt_adaptive*, ( bhpt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_lion_adaptive_bhpt

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_adaptive_bhpt_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_adaptive_bhpt" ) ) )
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


