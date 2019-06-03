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

static sc_t kjv_charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !.,";
//static sc_t kjv_charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 []!.,:;";
//static sc_t kjv_charset = "abcdefghijklmnopqrstuvwxyz ";

//----------------------------------------------------------------------------------------------------------------------

static void char_to_vec( const st_s* charset, const bcore_arr_sz_s* charmap, f3_t pos_tgt, f3_t neg_tgt, u0_t c, bmath_vf3_s* vec )
{
    bmath_vf3_s_set_size( vec, charset->size );
    sz_t idx = charmap->data[ c ];
    for( sz_t i = 0; i < vec->size; i++ ) vec->data[ i ] = ( i == idx ) ? pos_tgt : neg_tgt;
}

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

    char_to_vec( o->charset, o->charmap, o->pos_tgt, o->neg_tgt, o->t_last_char,  in );
    char_to_vec( o->charset, o->charmap, o->pos_tgt, o->neg_tgt,       cur_char, out );

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

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// badapt_guide_char_encode_s

bl_t badapt_guide_char_encode_s_callback( const badapt_guide_char_encode_s* o, badapt_training_state* state )
{
    BCORE_LIFE_INIT();
    badapt_adaptive* adaptive = BCORE_LIFE_A_PUSH( badapt_adaptive_a_clone( badapt_training_state_a_get_adaptive( state ) ) );
    sz_t vec_size = bcore_strlen( kjv_charset );
    BCORE_LIFE_CREATE( bmath_vf3_s, vin );
    BCORE_LIFE_CREATE( bmath_vf3_s, vout );
    bmath_vf3_s_set_size( vin, vec_size );
    bmath_vf3_s_set_size( vout, vec_size );

    u2_t rval = 1234;
    sz_t text_size = 92;

    bmath_vf3_s_set_random( vin, 1.0, -0.1, 0.1, &rval );

    f3_t exp = 4;

    for( sz_t i = 0; i < text_size; i++ )
    {
        badapt_adaptive_a_minfer( adaptive, vin, vout );
        bmath_vf3_s_add_scl_f3( vout, -bmath_vf3_s_min( vout ), vout );
        bmath_vf3_s_mul_f3( vout, 1.0 / bmath_vf3_s_max( vout ), vout );

        f3_t sum = 0;
        for( sz_t j = 0; j < vec_size; j++ )
        {
            sum += pow( vout->data[ j ], exp );
        }

        f3_t thr = f3_xsg2_pos( &rval ) * sum;

        sum = 0;
        sz_t idx = 0;
        for( sz_t j = 0; j < vec_size; j++ )
        {
            sum += pow( vout->data[ j ], exp );
            if( sum > thr )
            {
                idx = j;
                break;
            }
        }

        u0_t c = kjv_charset[ idx ];
        for( sz_t j = 0; j < vec_size; j++ ) vin->data[ j ] = ( j == idx ) ? 0.9 : -0.9;
        bcore_msg_fa( "#<char>", c );
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

