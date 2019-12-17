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

#include "lion_nop.h"

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

static lion_nop_context_s* context_g = NULL;

lion_nop_context_s* lion_nop_get_context( void )
{
    return context_g;
}

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
        case TYPEOF_st_s:
        case TYPEOF_sc_t:
        {
            bhvm_holor_s_copy_typed( &o->h, type, src );
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

/**********************************************************************************************************************/
/// eval

// ---------------------------------------------------------------------------------------------------------------------

void lion_nop_eval_ar2_s_run( const lion_nop_eval_ar2_s* o )
{
    bcore_txt_ml_a_to_stdout( o );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// selftest

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_nop_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_nop" ) ) )
    {
        case TYPEOF_init1:
        {
//            bcore_flect_push_ns_func( TYPEOF_lion_holor_s, ( fp_t )lion_holor_s_copy_typed, "bcore_fp_copy_typed", "copy_typed" );
            lion_nop_context_s_attach( &context_g, lion_nop_context_s_create() );
        }
        break;

        case TYPEOF_down1:
        {
            lion_nop_context_s_detach( &context_g );
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


