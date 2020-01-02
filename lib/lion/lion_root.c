/** Author and Copyright 2019 Johannes Bernhard Steffens
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

#include "lion_root.h"

/**********************************************************************************************************************/
/// holor

void lion_holor_s_copy_typed( lion_holor_s* o, tp_t type, vc_t src )
{
    switch( type )
    {
        case TYPEOF_lion_holor_s:
        {
            assert( *(aware_t*)src == TYPEOF_lion_holor_s );
            lion_holor_s_copy( o, src );
        }
        break;

        case TYPEOF_bhvm_holor_s:
        case TYPEOF_bmath_mf2_s:
        case TYPEOF_bmath_mf3_s:
        case TYPEOF_bmath_vf2_s:
        case TYPEOF_bmath_vf3_s:
        case TYPEOF_f2_t:
        case TYPEOF_f3_t:
        case TYPEOF_sc_t:
        {
            bhvm_holor_s_copy_typed( &o->h, type, src );
        }
        break;

        case TYPEOF_st_s:
        {
            assert( *(aware_t*)src == TYPEOF_st_s );
            bcore_source* source = ( bcore_source* )bcore_source_string_s_create_from_string( src );
            lion_holor_s_parse( o, source );
            bcore_source_a_discard( source );
        }
        break;

        default:
        {
            ERR_fa( "Cannot convert '#<sc_t>' to 'lion_holor_s'", ifnameof( type ) );
        }
        break;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_to_sink( const lion_holor_s* o, bcore_sink* sink )
{
    if( o->m.htp ) bcore_sink_a_push_fa( sink, "<htp>" );
    bhvm_holor_s_to_sink( &o->h, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_to_sink_nl( const lion_holor_s* o, bcore_sink* sink )
{
    lion_holor_s_to_sink( o, sink );
    bcore_sink_a_push_fa( sink, "\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_to_stdout( const lion_holor_s* o )
{
    lion_holor_s_to_sink( o, BCORE_STDOUT );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_to_stdout_nl( const lion_holor_s* o )
{
    lion_holor_s_to_sink_nl( o, BCORE_STDOUT );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_brief_to_sink( const lion_holor_s* o, bcore_sink* sink )
{
    if( o->m.htp ) bcore_sink_a_push_fa( sink, "<htp>" );
    bhvm_holor_s_brief_to_sink( &o->h, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_brief_to_stdout( const lion_holor_s* o )
{
    lion_holor_s_brief_to_sink( o, BCORE_STDOUT );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_formatted_to_sink( const lion_holor_s* o, bcore_sink* sink )
{
    if( o->m.htp ) bcore_sink_a_push_fa( sink, "<htp>" );
    bhvm_holor_s_formatted_to_sink( &o->h, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_formatted_to_stdout( const lion_holor_s* o )
{
    lion_holor_s_formatted_to_sink( o, BCORE_STDOUT );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_parse( lion_holor_s* o, bcore_source* source )
{
    lion_hmeta_s_clear( &o->m );

    if( bcore_source_a_parse_bl_fa( source, " #?'<htp>'" ) )
    {
        lion_holor_s_parse( o, source );
        o->m.htp = !o->m.htp;
    }
    else
    {
        bhvm_holor_s_parse( &o->h, source );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_root_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_root" ) ) )
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


