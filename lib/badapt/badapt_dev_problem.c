/** Copyright 2019 Johannes Bernhard Steffens
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

#include "badapt_dev_problem.h"
#include "badapt_loss.h"

/**********************************************************************************************************************/
#ifdef TYPEOF_badapt_problem_recurrent_kjv_s

//static sc_t kjv_charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 []!.,:;\"\n";
static sc_t kjv_charset = "abcdefghijklmnopqrstuvwxyz ";

//----------------------------------------------------------------------------------------------------------------------

sz_t badapt_problem_recurrent_kjv_s_get_in_size(  const badapt_problem_recurrent_kjv_s* o )
{
    return o->charset ? o->charset->size : bcore_strlen( kjv_charset );
}

//----------------------------------------------------------------------------------------------------------------------

sz_t badapt_problem_recurrent_kjv_s_get_out_size( const badapt_problem_recurrent_kjv_s* o )
{
    return o->charset ? o->charset->size : bcore_strlen( kjv_charset );
}

const badapt_loss* badapt_problem_recurrent_kjv_s_preferred_loss( const badapt_problem_recurrent_kjv_s* o ) { return o->preferred_loss; }

//----------------------------------------------------------------------------------------------------------------------

static void badapt_problem_recurrent_kjv_s_char_to_vec( badapt_problem_recurrent_kjv_s* o, u0_t c, bmath_vf3_s* vec )
{
    bmath_vf3_s_set_size( vec, o->charset->size );
    sz_t idx = o->charmap->data[ c ];
    for( sz_t i = 0; i < vec->size; i++ ) vec->data[ i ] = ( i == idx ) ? o->pos_tgt : o->neg_tgt;
}

//----------------------------------------------------------------------------------------------------------------------

static void badapt_problem_recurrent_kjv_s_create_charmap( badapt_problem_recurrent_kjv_s* o )
{
    if( !o->charmap )
    {
        o->charmap = bcore_arr_sz_s_create();
        bcore_arr_sz_s_fill( o->charmap, 256, -1 );
        o->charset = st_s_create_sc( kjv_charset );
        for( sz_t i = 0; i < o->charset->size; i++ ) o->charmap->data[ ( u0_t )o->charset->data[ i ] ] = i;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_kjv_s_fetch_sample_tio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    if( !o->source ) o->source = bcore_file_open_source( "../data/bible/KJV.txt" );
    if( !o->charmap ) badapt_problem_recurrent_kjv_s_create_charmap( o );

    if( o->t_last_char == 0 ) o->t_last_char = bcore_source_a_get_u0( o->source );

    u0_t c;

    while( o->charmap->data[ ( c = bcore_source_a_get_u0( o->source ) ) ] == -1 )
    {
        if( bcore_source_a_eos( o->source ) ) bcore_source_a_set_index( o->source, 0 );
    }

    u0_t cur_char = c;

    badapt_problem_recurrent_kjv_s_char_to_vec( o, o->t_last_char,  in );
    badapt_problem_recurrent_kjv_s_char_to_vec( o,       cur_char, out );

//    bcore_msg_fa( "#<char>", cur_char );

    o->t_last_char = cur_char;
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_kjv_s_fetch_sample_vio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    /// TODO: separate between batch and valid
    badapt_problem_recurrent_kjv_s_fetch_sample_tio( o, in, out );
}

//----------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_badapt_problem_recurrent_kjv_s

/**********************************************************************************************************************/

vd_t badapt_dev_problem_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_dev_problem" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            return NULL;
        }
        break;

        case TYPEOF_precoder:
        {
            bcore_precoder_compile( "badapt_dev_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

/**********************************************************************************************************************/

