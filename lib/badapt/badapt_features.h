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

BETH_PRECODE( badapt_adaptive )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// resets trainable components with given seed
    feature strict 'par' void reset( mutable, u2_t rseed );

    /// should be called once before use
    feature strict 'par' void setup( mutable );

    /// input vector size
    feature strict 'par' sz_t get_in_size( const );
    feature strict 'par' void set_in_size( mutable, sz_t size );

    /// output vector size
    feature strict 'par' sz_t get_out_size( const );
    feature strict 'par' void set_out_size( mutable, sz_t size );

    /// fast concurrent inference
    feature strict 'par' void infer( const, const bmath_vf3_s* in, bmath_vf3_s* out );

    /// mutable inference (used for training)
    feature strict 'par' void minfer( mutable, const bmath_vf3_s* in, bmath_vf3_s* out );

    /// fast concurrent gradient backpropagation (no changing of state)
    feature strict 'par' void bgrad( const, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );

    /// gradient backpropagation with adaptation; relates to after last call to minfer for given gradient; grad_in can be NULL
    feature strict 'par' void bgrad_adapt( mutable, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out );

    // ===== optional features =====

    /// adaption step
    feature        'par' f3_t get_step( const );
    feature        'par' void set_step( mutable, f3_t val );

    /// adaption regularization
    feature        'par' f3_t get_regularization( const,   tp_t type );
    feature        'par' void set_regularization( mutable, tp_t type, f3_t val );

    /// outputs architecture to text sink (for easy inspection)
    feature        'par' void arc_to_sink( const, bcore_sink* sink ) = arc_to_sink_fallback;

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

/// activation function
BETH_PRECODE( badapt_activation )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    feature strict 'par' f3_t fx( const, f3_t x ); // y  = f( x )
    feature strict 'par' f3_t dy( const, f3_t y ); // dy = d( y ) (derivative applied on y)
#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

/// activator: (adaptive) activation applied to a vector
BETH_PRECODE( badapt_activator )
#ifdef BETH_PRECODE_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// resets trainable components with given seed
    feature strict 'par' void reset( mutable, u2_t rseed );

    /// should be called once before use
    feature strict 'par' void setup( mutable );

    /// vector size
    feature        'par' sz_t get_size( const );
    feature        'par' void set_size( mutable, sz_t size );

    /// fast concurrent inference
    feature strict 'par' void infer( const, const bmath_vf3_s* in, bmath_vf3_s* out );

    /// fast concurrent gradient backpropagation (no changing of state)
    /// grad_in and grad_out may refer to the same object
    feature strict 'par' void bgrad( const, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out );

    /// adaptation step after last minfer for given gradient; grad_in can be NULL
    /// grad_in and grad_out may refer to the same object
    feature strict 'par' void adapt( mutable, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out, const bmath_vf3_s* out );

#endif // BETH_PRECODE_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

vd_t badapt_features_signal_handler( const bcore_signal_s* o );

#endif  // BADAPT_FEATURES_H

