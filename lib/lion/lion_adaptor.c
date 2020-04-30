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

#include "lion_adaptor.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_adaptor

// ---------------------------------------------------------------------------------------------------------------------

void lion_adaptor_frame_s_adapt( lion_adaptor_frame_s* o, const bhpt_adaptor_node_s* node )
{
    if( !o->frame )
    {
        BLM_INIT();
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

        o->frame = lion_frame_s_create();
        lion_frame_s_setup_from_source( o->frame, source, ( const bhvm_holor_s*[] ){ node->axon, node->grad } );

        ASSERT( lion_frame_s_get_size_en( frame ) == 2 );
        ASSERT( lion_frame_s_get_size_ex( frame ) == 2 );

        BLM_DOWN();
    }

    lion_frame_s_run_ap( o->frame, ( const bhvm_holor_s*[] ){ node->axon, node->grad }, ( bhvm_holor_s*[] ){ node->axon, node->grad } );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_lion_adaptor

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_adaptor_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_adaptor" ) ) )
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


