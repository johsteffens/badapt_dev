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

#include "opal_adaptive.h"

/**********************************************************************************************************************/
/// adaptive

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_s_axon_pass( opal_adaptive_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex )
{
    opal_frame_s_run_ap( &o->frame, ( const bhvm_holor_s** )&ax_en, 1, &ax_ex, 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_s_dendrite_pass( opal_adaptive_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en )
{
    opal_frame_s_run_dp( &o->frame, ( const bhvm_holor_s** )&ag_ex, 1, ( ag_en ) ? &ag_en : NULL, ( ag_en ) ? 1 : 0 );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_s_cyclic_reset( opal_adaptive_s* o )
{
    opal_frame_s_cyclic_reset( &o->frame );
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptor_probe_s* opal_adaptive_s_get_adaptor_probe( const opal_adaptive_s* o, bhpt_adaptor_probe_s* probe )
{
    bhpt_adaptor_probe_s_set_size( probe, opal_frame_s_get_size_ada( &o->frame ) );
    opal_frame_s* frame = ( opal_frame_s* )&o->frame;
    ASSERT( frame->is_setup );
    BFOR_EACH( i, probe )
    {
        probe->data[ i ].axon = opal_frame_s_get_ap_ada( frame, i );
        probe->data[ i ].grad = opal_frame_s_get_dp_ada( frame, i );
    }
    return probe;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_s_status_to_sink( const opal_adaptive_s* o, sz_t verbosity, bcore_sink* sink )
{
    if( verbosity >= 1 )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( o->_ ) );
    }

    if( verbosity >= 10 )
    {
        opal_frame_s_disassemble_to_sink( &o->frame, sink );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptive* opal_adaptive_builder_s_create_adaptive( const opal_adaptive_builder_s* o )
{
    BLM_INIT();
    opal_adaptive_s* adaptive = opal_adaptive_s_create();

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

    opal_frame_s* frame = &adaptive->frame;
    const bhvm_holor_s* holor_frame_en = &o->holor_frame_en;
    opal_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&holor_frame_en, 1 );

    ASSERT( opal_frame_s_get_size_en( frame ) == 1 );
    ASSERT( opal_frame_s_get_size_ex( frame ) == 1 );

    ASSERT( bhvm_shape_s_is_equal( &o->holor_frame_en.s, &opal_frame_s_get_ap_en( frame, 0 )->s ) );
    ASSERT( bhvm_shape_s_get_volume( &o->holor_frame_ex.s ) == bhvm_shape_s_get_volume( &opal_frame_s_get_ap_ex( frame, 0 )->s ) );

    adaptive->src = bcore_fork( o->src );

    BLM_RETURNV( bhpt_adaptive*, ( bhpt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive_cyclic

// ---------------------------------------------------------------------------------------------------------------------

static void opal_adaptive_cyclic_s_dp_buffer_create( opal_adaptive_cyclic_s* o )
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

static void opal_adaptive_cyclic_s_dp_buffer_reset( opal_adaptive_cyclic_s* o )
{
    if( !o->dp_buffer ) opal_adaptive_cyclic_s_dp_buffer_create( o );
    BFOR_EACH( i, o->dp_buffer ) bhvm_value_s_zro( &o->dp_buffer->data[ i ]->v );
    o->dp_value = false;
}

// ---------------------------------------------------------------------------------------------------------------------

static void opal_adaptive_cyclic_s_dp_buffer_apply( opal_adaptive_cyclic_s* o )
{
    opal_frame_cyclic_s_run_dp_adl_flat( &o->frame, o->dp_buffer, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

static void opal_adaptive_cyclic_s_dp_buffer_apply_reset( opal_adaptive_cyclic_s* o )
{
    opal_adaptive_cyclic_s_dp_buffer_apply( o );
    opal_adaptive_cyclic_s_dp_buffer_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_cyclic_s_axon_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ax_en, bhvm_holor_s* ax_ex )
{
    opal_frame_cyclic_s_run_ap( &o->frame, ( const bhvm_holor_s** )&ax_en, 1, &ax_ex, 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_cyclic_s_dendrite_pass( opal_adaptive_cyclic_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en )
{
    ASSERT( !ag_en );

    if( !o->dp_buffer ) opal_adaptive_cyclic_s_dp_buffer_create( o );
    sz_t dp_index = ( o->frame.unroll_index == 0 ) ? o->frame.unroll_size - 1 : o->frame.unroll_index - 1;

    bhvm_holor_s* h = o->dp_buffer->data[ dp_index ];
    bhvm_value_s_cpy( &ag_ex->v, &h->v );
    o->dp_value = true;

    if( o->frame.unroll_index == 0 ) opal_adaptive_cyclic_s_dp_buffer_apply_reset( o );

}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_cyclic_s_cyclic_reset( opal_adaptive_cyclic_s* o )
{
    opal_frame_cyclic_s_cyclic_reset( &o->frame );
    if( o->dp_value ) opal_adaptive_cyclic_s_dp_buffer_reset( o );
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptor_probe_s* opal_adaptive_cyclic_s_get_adaptor_probe( const opal_adaptive_cyclic_s* o, bhpt_adaptor_probe_s* probe )
{
    bhpt_adaptor_probe_s_set_size( probe, opal_frame_cyclic_s_get_size_ada( &o->frame ) );

    opal_frame_s* frame = o->frame.frame;

    ASSERT( frame->is_setup );
    BFOR_EACH( i, probe )
    {
        probe->data[ i ].axon = opal_frame_s_get_ap_ada( frame, i );
        probe->data[ i ].grad = opal_frame_s_get_dp_ada( frame, i );
    }
    return probe;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_adaptive_cyclic_s_status_to_sink( const opal_adaptive_cyclic_s* o, sz_t verbosity, bcore_sink* sink )
{
    if( verbosity >= 1 )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( o->_ ) );
    }

    if( verbosity >= 10 )
    {
        opal_frame_cyclic_s_disassemble_to_sink( &o->frame, sink );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bhpt_adaptive* opal_adaptive_cyclic_builder_s_create_adaptive( const opal_adaptive_cyclic_builder_s* o )
{
    BLM_INIT();
    opal_adaptive_cyclic_s* adaptive = opal_adaptive_cyclic_s_create();

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

    opal_frame_s* frame = BLM_CREATE( opal_frame_s );
    const bhvm_holor_s* holor_frame_en = &o->holor_frame_en;
    opal_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&holor_frame_en, 1 );

    ASSERT( opal_frame_s_get_size_en( frame ) == 1 );
    ASSERT( opal_frame_s_get_size_ex( frame ) == 1 );

    ASSERT( bhvm_shape_s_is_equal( &o->holor_frame_en.s, &opal_frame_s_get_ap_en( frame, 0 )->s ) );
    ASSERT( bhvm_shape_s_get_volume( &o->holor_frame_ex.s ) == bhvm_shape_s_get_volume( &opal_frame_s_get_ap_ex( frame, 0 )->s ) );

    adaptive->src = bcore_fork( o->src );

    opal_frame_cyclic_s* frame_cyclic = &adaptive->frame;
    opal_frame_cyclic_s_setup_from_frame( frame_cyclic, frame, o->unroll_size );

    BLM_RETURNV( bhpt_adaptive*, ( bhpt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

