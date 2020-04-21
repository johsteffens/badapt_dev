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
    lion_frame_s_run_ap( &o->frame, ( const bhvm_holor_s** )&ax_en, &ax_ex );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_dendrite_pass( lion_adaptive_bhpt_s* o, const bhvm_holor_s* ag_ex, bhvm_holor_s* ag_en )
{
    lion_frame_s_run_dp( &o->frame, ( const bhvm_holor_s** )&ag_ex, ( ag_en ) ? &ag_en : NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_cyclic_reset( lion_adaptive_bhpt_s* o )
{
    lion_frame_s_cyclic_reset( &o->frame );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_get_hprobe_accugrad( const lion_adaptive_bhpt_s* o, bhpt_hprobe_s* hprobe )
{
    bhpt_hprobe_s_set_size( hprobe, lion_frame_s_get_size_ada( &o->frame ) );
    lion_frame_s* frame = ( lion_frame_s* )&o->frame;
    BFOR_EACH( i, hprobe )
    {
        bhvm_holor_s_attach( &hprobe->data[ i ], bcore_fork( lion_frame_s_get_dp_ada( frame, i ) ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_get_hprobe_adaptive( const lion_adaptive_bhpt_s* o, bhpt_hprobe_s* hprobe )
{
    bhpt_hprobe_s_set_size( hprobe, lion_frame_s_get_size_ada( &o->frame ) );
    lion_frame_s* frame = ( lion_frame_s* )&o->frame;
    BFOR_EACH( i, hprobe )
    {
        bhvm_holor_s_attach( &hprobe->data[ i ], bcore_fork( lion_frame_s_get_ap_ada( frame, i ) ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptive_bhpt_s_status_to_sink( const lion_adaptive_bhpt_s* o, sz_t verbosity, bcore_sink* sink )
{
    if( verbosity > 0 )
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
    lion_frame_s_setup_from_source( frame, source, ( const bhvm_holor_s** )&holor_frame_en );

    ASSERT( lion_frame_s_get_size_en( frame ) == 1 );
    ASSERT( lion_frame_s_get_size_ex( frame ) == 1 );

    ASSERT( bhvm_shape_s_is_equal( &o->holor_frame_en.s, &lion_frame_s_get_ap_en( frame, 0 )->s ) );
    ASSERT( bhvm_shape_s_get_volume( &o->holor_frame_ex.s ) == bhvm_shape_s_get_volume( &lion_frame_s_get_ap_ex( frame, 0 )->s ) );

    adaptive->src = bcore_fork( o->src );

    BLM_RETURNV( bhpt_adaptive*, ( bhpt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive_cyclic

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


