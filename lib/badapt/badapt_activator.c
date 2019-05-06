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

#include "badapt_activator.h"

/**********************************************************************************************************************/

f3_t badapt_activation_tanh_s_fx( const badapt_activation_tanh_s* o, f3_t x ) { return 1.0 - ( 2.0 / ( exp( 2.0 * x ) + 1.0 ) ); }
f3_t badapt_activation_tanh_s_dy( const badapt_activation_tanh_s* o, f3_t y ) { return 1.0 - f3_sqr( y ); }

f3_t badapt_activation_relu_s_fx( const badapt_activation_relu_s* o, f3_t x ) { return x > 0 ? x : 0; }
f3_t badapt_activation_relu_s_dy( const badapt_activation_relu_s* o, f3_t y ) { return y > 0 ? 1 : 0; }

f3_t badapt_activation_leaky_relu_s_fx( const badapt_activation_leaky_relu_s* o, f3_t x ) { return x > 0 ? x : x * 0.01; }
f3_t badapt_activation_leaky_relu_s_dy( const badapt_activation_leaky_relu_s* o, f3_t y ) { return y > 0 ? 1 : 0.01; }

f3_t badapt_activation_softplus_s_fx( const badapt_activation_softplus_s* o, f3_t x ) { return log( 1.0 + exp( x ) ); }
f3_t badapt_activation_softplus_s_dy( const badapt_activation_softplus_s* o, f3_t y ) { f3_t u = exp( y ); return ( u - 1.0 ) / u; }

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

void badapt_activator_plain_s_setup( badapt_activator_plain_s* o )
{
    if( sr_s_p_type( &o->activation ) != TYPEOF_badapt_activation )
    {
        o->activation.p = ch_spect_p( o->activation.p, TYPEOF_badapt_activation );
    }
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_activator_plain_s_reset( badapt_activator_plain_s* o, u2_t rseed )
{
   // nothing to do
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_activator_plain_s_infer( const badapt_activator_plain_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    assert( in->size == out->size );
    assert( sr_s_p_type( &o->activation ) == TYPEOF_badapt_activation );
    const badapt_activation_s* activation_p = o->activation.p;
    const badapt_activation  * activation_o = o->activation.o;
    for( sz_t i = 0; i < out->size; i++ ) out->data[ i ] = badapt_activation_p_fx( activation_p, activation_o, in->data[ i ] );
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_activator_plain_s_bgrad( const badapt_activator_plain_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out )
{
    assert( grad_in->size == grad_out->size );
    assert( grad_in->size ==      out->size );
    assert( sr_s_p_type( &o->activation ) == TYPEOF_badapt_activation );
    const badapt_activation_s* activation_p = o->activation.p;
    const badapt_activation  * activation_o = o->activation.o;
    for( sz_t i = 0; i < out->size; i++ ) grad_in->data[ i ] = badapt_activation_p_dy( activation_p, activation_o, out->data[ i ] ) * grad_out->data[ i ];
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_activator_plain_s_adapt( badapt_activator_plain_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out )
{
    badapt_activator_plain_s_bgrad( o, grad_in, grad_out, out );
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

vd_t badapt_activator_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_activator" ) ) )
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
            bcore_precoder_compile( "badapt_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

/**********************************************************************************************************************/

