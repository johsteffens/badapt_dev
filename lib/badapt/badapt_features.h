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

#ifndef BADAPT_FEATURES_H
#define BADAPT_FEATURES_H

#include "bmath_std.h"
#include "badapt_precoded.h"

/**********************************************************************************************************************/

/// loss function
BETH_PRECODE( badapt_loss )
#ifdef BETH_PRECODE_SECTION
    feature strict 'pa' f3_t loss(    const, const bmath_vf3_s* out, const bmath_vf3_s* target );                    // loss function
    feature strict 'pa' f3_t loss_f3( const, f3_t               out, f3_t               target );                    // loss function on scalars
    feature strict 'pa' void bgrad(   const, const bmath_vf3_s* out, const bmath_vf3_s* target, bmath_vf3_s* grad ); // computes loss minimizing backward gradient of x
#endif // BETH_PRECODE_SECTION

/**********************************************************************************************************************/

BETH_PRECODE( badapt_adaptive )
#ifdef BETH_PRECODE_SECTION

    // ===== required features =====

    /// resets trainable components with given seed
    feature strict 'a' void reset( mutable );

    /// should be called once before use
    feature strict 'a' void setup( mutable );

    /// input vector size
    feature strict 'a' sz_t get_in_size( const );
    feature strict 'a' void set_in_size( mutable, sz_t size );

    /// output vector size
    feature strict 'a' sz_t get_out_size( const );
    feature strict 'a' void set_out_size( mutable, sz_t size );

    /// fast concurrent inference
    feature strict 'a' void infer( const, const bmath_vf3_s* in, bmath_vf3_s* out );

    /// mutable inference (used for training)
    feature strict 'a' void minfer( mutable, const bmath_vf3_s* in, bmath_vf3_s* out );

    /// fast concurrent gradient backpropagation (no changing of state)
    feature strict 'a' void bgrad( const, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );

    /// gradient backpropagation with adaptation; relates to after last call to minfer for given gradient; grad_in can be NULL
    feature strict 'a' void bgrad_adapt( mutable, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );

    // ===== optional features =====

    /// adaption rate (1.0 means default rate for the network)
    feature 'a' f3_t get_rate( const );
    feature 'a' void set_rate( mutable, f3_t val );

    /// regularization (1.0 means default rate for the network)
    feature 'a' f3_t get_lambda_l1( const );
    feature 'a' void set_lambda_l1( mutable, f3_t val );
    feature 'a' f3_t get_lambda_l2( const );
    feature 'a' void set_lambda_l2( mutable, f3_t val );

    // ===== optional features with default implementation =====

    /// outputs architecture to text sink (for easy inspection)
    feature 'a' void arc_to_sink( const, bcore_sink* sink ) = arc_to_sink_fallback;

    /// inference for scalar output
    feature 'a' f3_t infer_f3( const, const bmath_vf3_s* in ) = infer_f3_fallback;

    /// full adaption cycle based on loss function; adapt_loss_f3 returns estimates result
    feature 'a' void adapt_loss(    mutable, const badapt_loss* loss, const bmath_vf3_s* in, const bmath_vf3_s* target, bmath_vf3_s* out ) = adapt_loss_fallback;
    feature 'a' f3_t adapt_loss_f3( mutable, const badapt_loss* loss, const bmath_vf3_s* in, f3_t target )                                 = adapt_loss_f3_fallback;

#endif // BETH_PRECODE_SECTION

/**********************************************************************************************************************/

/// activation function
BETH_PRECODE( badapt_activation )
#ifdef BETH_PRECODE_SECTION
    feature strict 'pa' f3_t fx( const, f3_t x ); // y  = f( x )
    feature strict 'pa' f3_t dy( const, f3_t y ); // dy = d( y ) (derivative applied on y)
#endif // BETH_PRECODE_SECTION

/**********************************************************************************************************************/

/// activator: (adaptive) activation applied to a vector
BETH_PRECODE( badapt_activator )
#ifdef BETH_PRECODE_SECTION

    /// resets trainable components with given seed
    feature strict 'a' void reset( mutable );

    /// should be called once before use
    feature strict 'a' void setup( mutable );

    /// vector size
    feature        'a' sz_t get_size( const );
    feature        'a' void set_size( mutable, sz_t size );

    /// activation function
    feature        'a' const badapt_activation* get_activation( const );
    feature        'a' void set_activation( mutable, const badapt_activation* activation );

    /// fast concurrent inference
    feature strict 'a' void infer( const, const bmath_vf3_s* in, bmath_vf3_s* out );

    /// fast concurrent gradient backpropagation (no changing of state)
    /// grad_in and grad_out may refer to the same object
    feature strict 'a' void bgrad( const, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out );

    /// adaptation step after last minfer for given gradient; grad_in can be NULL
    /// grad_in and grad_out may refer to the same object
    feature strict 'a' void adapt( mutable, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out, f3_t step );

#endif // BETH_PRECODE_SECTION

/**********************************************************************************************************************/

vd_t badapt_features_signal_handler( const bcore_signal_s* o );

#endif  // BADAPT_FEATURES_H

