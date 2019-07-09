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

static sc_t encode_charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !.,";
//static sc_t encode_charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 []!.,:;";
//static sc_t encode_charset = "abcdefghijklmnopqrstuvwxyz ";

//----------------------------------------------------------------------------------------------------------------------


/**********************************************************************************************************************/
/// badapt_problem_recurrent_abc_s

sz_t badapt_problem_recurrent_abc_s_get_in_size(  const badapt_problem_recurrent_abc_s* o )
{
    return bcore_strlen( encode_charset );
}

//----------------------------------------------------------------------------------------------------------------------

sz_t badapt_problem_recurrent_abc_s_get_out_size( const badapt_problem_recurrent_abc_s* o )
{
    return bcore_strlen( encode_charset );
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_abc_s_fetch_sample_tio( badapt_problem_recurrent_abc_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    if(  in->size == 0 ) bmath_vf3_s_set_size( in,  badapt_problem_recurrent_abc_s_get_in_size( o ) );
    if( out->size == 0 ) bmath_vf3_s_set_size( out, badapt_problem_recurrent_abc_s_get_out_size( o ) );
    sz_t size    = in->size;
    sz_t in_idx  = o->index;
    sz_t out_idx = ( o->index + 1 ) % out->size;
    o->index = out_idx;
    for( sz_t i = 0; i < size; i++ )
    {
        in ->data[ i ] = ( i ==  in_idx ) ? o->pos_tgt : o->neg_tgt;
        out->data[ i ] = ( i == out_idx ) ? o->pos_tgt : o->neg_tgt;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_abc_s_fetch_sample_vio( badapt_problem_recurrent_abc_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    badapt_problem_recurrent_abc_s_fetch_sample_tio( o, in, out );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// badapt_problem_recurrent_kjv_s

static void char_to_vec( const st_s* charset, const bcore_arr_sz_s* charmap, f3_t pos_tgt, f3_t neg_tgt, u0_t c, bmath_vf3_s* vec )
{
    bmath_vf3_s_set_size( vec, charset->size );
    sz_t idx = charmap->data[ c ];
    for( sz_t i = 0; i < vec->size; i++ ) vec->data[ i ] = ( i == idx ) ? pos_tgt : neg_tgt;
}

//----------------------------------------------------------------------------------------------------------------------

sz_t badapt_problem_recurrent_kjv_s_get_in_size(  const badapt_problem_recurrent_kjv_s* o )
{
    return o->charset ? o->charset->size : bcore_strlen( encode_charset );
}

//----------------------------------------------------------------------------------------------------------------------

sz_t badapt_problem_recurrent_kjv_s_get_out_size( const badapt_problem_recurrent_kjv_s* o )
{
    return o->charset ? o->charset->size : bcore_strlen( encode_charset );
}

//----------------------------------------------------------------------------------------------------------------------

static void badapt_problem_recurrent_kjv_s_create_charmap( badapt_problem_recurrent_kjv_s* o )
{
    if( !o->charmap )
    {
        o->charmap = bcore_arr_sz_s_create();
        bcore_arr_sz_s_fill( o->charmap, 256, -1 );
        o->charset = st_s_create_sc( encode_charset );
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

    char_to_vec( o->charset, o->charmap, o->pos_tgt, o->neg_tgt, o->t_last_char,  in );
    char_to_vec( o->charset, o->charmap, o->pos_tgt, o->neg_tgt,       cur_char, out );

//    bcore_msg_fa( "#<char>", cur_char );

    o->t_last_char = cur_char;
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_kjv_s_fetch_sample_vio( badapt_problem_recurrent_kjv_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    badapt_problem_recurrent_kjv_s_fetch_sample_tio( o, in, out );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// badapt_problem_recurrent_text_s

sz_t badapt_problem_recurrent_text_s_get_in_size(  const badapt_problem_recurrent_text_s* o )
{
    return o->charset ? o->charset->size : bcore_strlen( encode_charset );
}

//----------------------------------------------------------------------------------------------------------------------

sz_t badapt_problem_recurrent_text_s_get_out_size( const badapt_problem_recurrent_text_s* o )
{
    return o->charset ? o->charset->size : bcore_strlen( encode_charset );
}

//----------------------------------------------------------------------------------------------------------------------

static void badapt_problem_recurrent_text_s_create_charmap( badapt_problem_recurrent_text_s* o )
{
    if( !o->charmap )
    {
        o->charmap = bcore_arr_sz_s_create();
        bcore_arr_sz_s_fill( o->charmap, 256, -1 );
        o->charset = st_s_create_sc( encode_charset );
        for( sz_t i = 0; i < o->charset->size; i++ ) o->charmap->data[ ( u0_t )o->charset->data[ i ] ] = i;
    }
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_text_s_fetch_sample_tio( badapt_problem_recurrent_text_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    if( !o->source )
    {
        if( o->text_file.size == 0 ) ERR_fa( "Source file not specified" );
        o->source = bcore_file_open_source( o->text_file.sc );
    }
    if( !o->charmap ) badapt_problem_recurrent_text_s_create_charmap( o );

    if( o->t_last_char == 0 ) o->t_last_char = bcore_source_a_get_u0( o->source );

    u0_t c;

    if( o->ignore_line_char.size > 0 )
    {
        while( bcore_source_a_inspect_u0( o->source ) == o->ignore_line_char.sc[ 0 ] )
        {
            while( bcore_source_a_get_u0( o->source ) != '\n' )
            {
                if( bcore_source_a_eos( o->source ) )
                {
                    bcore_source_a_set_index( o->source, 0 );
                    break;
                }
            }
        }
    }

    while( o->charmap->data[ ( c = bcore_source_a_get_u0( o->source ) ) ] == -1 )
    {
        if( bcore_source_a_eos( o->source ) ) bcore_source_a_set_index( o->source, 0 );
    }

    u0_t cur_char = c;

    char_to_vec( o->charset, o->charmap, o->pos_tgt, o->neg_tgt, o->t_last_char,  in );
    char_to_vec( o->charset, o->charmap, o->pos_tgt, o->neg_tgt,       cur_char, out );

//    bcore_msg_fa( "#<char>", cur_char );

    o->t_last_char = cur_char;
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_problem_recurrent_text_s_fetch_sample_vio( badapt_problem_recurrent_text_s* o, bmath_vf3_s* in, bmath_vf3_s* out )
{
    badapt_problem_recurrent_text_s_fetch_sample_tio( o, in, out );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// badapt_guide_char_encode_s

bl_t badapt_guide_char_encode_s_callback( const badapt_guide_char_encode_s* o, badapt_training_state* state )
{
    BCORE_LIFE_INIT();
    badapt_adaptive* adaptive = BCORE_LIFE_A_PUSH( badapt_adaptive_a_clone( badapt_training_state_a_get_adaptive( state ) ) );
    if( badapt_adaptive_a_defines_reset( adaptive ) ) badapt_adaptive_a_reset( adaptive );
    sz_t vec_size = bcore_strlen( encode_charset );
    BCORE_LIFE_CREATE( bmath_vf3_s, vin );
    BCORE_LIFE_CREATE( bmath_vf3_s, vout );
    bmath_vf3_s_set_size( vin, vec_size );
    bmath_vf3_s_set_size( vout, vec_size );

    bmath_vf3_s_zro( vin );

    sc_t txt0 = o->txt_trigger.sc;

    for( sz_t i = 0; txt0[ i ] != 0; i++ )
    {
        u0_t c = txt0[ i ];
        for( sz_t j = 0; j < vec_size; j++ ) vin->data[ j ] = ( j == i ) ? o->pos_tgt : o->neg_tgt;
        bcore_msg_fa( "#<char>", c );
        badapt_adaptive_a_minfer( adaptive, vin, vout );
    }

    for( sz_t i = 0; i < o->txt_size; i++ )
    {
        u2_t rval = 12341234 * bmath_vf3_s_f3_sum( vout );

        for( sz_t j = 0; j < vout->size; j++ ) vout->data[ j ] += f3_rnd_pos( &rval ) * o->heat;

        sz_t idx = bmath_vf3_s_idx_max( vout );
        u0_t c = encode_charset[ idx ];
        for( sz_t j = 0; j < vec_size; j++ ) vin->data[ j ] = ( j == idx ) ? o->pos_tgt : o->neg_tgt;
        bcore_msg_fa( "#<char>", c );
        badapt_adaptive_a_minfer( adaptive, vin, vout );
    }
    bcore_msg_fa( ";  " );

    BCORE_LIFE_DOWN();

    return badapt_guide_a_callback( o->guide_default, state );
}

//----------------------------------------------------------------------------------------------------------------------

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

        case TYPEOF_plant:
        {
            bcore_plant_compile( "badapt_dev_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

/**********************************************************************************************************************/

