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

/*
    ========================================

    MLP

    graph layer( y ) => ( dim_y, x )
    {
        holor adaptive w = [ dim_y ][ dimof( x ) ]#, b = [ dim_y ]#;
        y -> ( w * x ) + b;
    };

    graph mlp( y ) => ( x )
    {
        graph l1 = layer( dim -> 10, x -> x    );
        graph l2 = layer( dim -> 20, x -> act_relu( l1.y ) );
        graph l3 = layer( dim ->  1, x -> act_relu( l2.y ) );
        y -> act_tanh( l3.y );
    };

    g_out -> mlp( g_in );

    ========================================
    LSTM

    graph layer( co, ho ) => ( dim_h, x, ci, hi )
    {
        // = type def
        holor w_fx = [ dim_h ][ dimof( x ) ]#, w_fh = [ dim_h ][ dimof( x ) ]#, b_f = [ dim_h ]#;
        holor w_ix = [ dim_h ][ dimof( x ) ]#, w_ih = [ dim_h ][ dimof( x ) ]#, b_i = [ dim_h ]#;
        holor w_ox = [ dim_h ][ dimof( x ) ]#, w_oh = [ dim_h ][ dimof( x ) ]#, b_o = [ dim_h ]#;
        holor w_qx = [ dim_h ][ dimof( x ) ]#, w_qh = [ dim_h ][ dimof( x ) ]#, b_q = [ dim_h ]#;

        link v_f -> act_sig ( ( w_fx * x ) + ( w_fh * hi ) + b_f );
        link v_i -> act_sig ( ( w_ix * x ) + ( w_ih * hi ) + b_i );
        link v_o -> act_sig ( ( w_ox * x ) + ( w_oh * hi ) + b_o );
        link v_q -> act_tanh( ( w_qx * x ) + ( w_qh * hi ) + b_q );

        co  -> ( v_f <*> ci ) + ( v_i <*> v_q );
        link v_d -> act_tanh( co );
        ho  -> ( v_o <*> v_d );
    };

    graph lstm( y ) => ( dim_h, x )
    {
        holor adaptive w_r = [ dim_h ][ dimof( x ) ]#, b_r = [ dim_h ]#;
        holor recurrent c = [ dim_h ]#, h = [ dim_h ]#;

        graph l1 = layer( dim_h -> dim_h, x -> x, ci -> c, hi -> h );

        h -> l1.ho;
        c -> l1.co;

        y -> act_tanh( w_r * h + b_r );
    }

    g_out -> lstm( dim_h -> 200, x -> g_in ).y;

    - parse into graph
    - graph: mesh of graph
    - graph: inputs, outputs, body
    - definition: stand-alone node with identifier
    - operation: graph embedded in a graph
    - once a graph is complete, data types can be finalized

*/

/**
 *  Symbolic language to describe a graph of operators on holors.
 *
 *  Semantic Cell Concept:
 *  A semantic graph communicates with the objects outside its body through input an output channels.
 *  All links of a graph 'x' to outside objects the node must pass though an input channel of 'x'.
 *  Inside objects may not be referenced directly by outside objects.
 *  A graph adhering to this concept is called 'cell'
 *  An construction of a new graph must conclude with converting it to a cell.
 *  Cells can be used as objects for constructing new graphs.
 *
 *  Static Links:
 *  Defined links of an input channel of a semantic graph are never changed or freed again.
 *  Different use cases of a graph are achieved by creating graph-copies and assigning links of those copies differently.
 *
 *  Binary operators:
 *  Binary operators have a priority-level. Higher priority is resolved before lower priority.
 *
 *  Available binary operators
 *  Symbol  Priority  Type
 *   +          8     (elementwise) addition
 *   -          8     (elementwise) subtraction
 *   *          9     (elementwise) multiplication (hadamard product); multiplication of holor with scalar
 *  **,
 *  *^,
 *  ^*,
 *  ^*^         9     holor-product for holors up to order 2; '^' indicates which side is considered transposed
 *  ***         9     convolution?
 *
 *
 *  Possible name ?
 *     holocell
 *     holorcell  (unused)
 *     holorframe (unused, term does not yet exist)
 *     holograph
 *     holorgraph
 *     holornova
 *
 *  Dendpass-Algorithm:
 *  specific method to compute the local gradient via automatic differentiation
 *  using reverse accumulation to backpropagate gradients:
 *  - Each node holds a gradient holor of same shape as its output holor
 *  - The gradient holor represents the gradient with respect to the last input given the current state of the network.
 *  - The backpass algorithm for a specific node computes the gradient through a specific node-channel and adds it to (accumulates)
 *    the gradient of the node linked to the input channel. This step is done by s singe virtual operation.
 *  - The backpass procedure is compiled by recursively passing each node starting from the adaptive node downward through
 *    all downlinks.
 */

#ifndef BHGP_H
#define BHGP_H

#include "bmath_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_planted.h"

/**********************************************************************************************************************/
/// f3-operators

/**********************************************************************************************************************/
/// prototypes

s2_t bhgp_op_ar1_solve_unary( bmath_hf3_s** r, bmath_hf3_s** a, bmath_fp_f3_ar1 unary );

/**********************************************************************************************************************/

#ifdef TYPEOF_bhgp
PLANT_GROUP( bhgp, bcore_inst )
#ifdef PLANT_SECTION

signature sz_t get_sz( const );
signature sc_t get_sc( const );
signature tp_t get_tp( const );

/// control types
name cell;
name if;
name then;
name else;

/// operator group
group :op =
{
    feature strict 'a' ::get_sz get_arity;
    feature        'a' ::get_sz get_priority = { return 10; };
    feature        'a' ::get_sc get_symbol   = { return NULL; };

    /// converts an operator into a correspondent operator of arity n if possible; return NULL if conversion is not supported
    feature        'a' :* create_op_of_arn( const, sz_t n ) = { return ( :a_get_arity( o ) == n ) ? :a_clone( o ) : NULL; };

    signature bmath_hf3_vm_op* create_vm_op_pass( const, const bmath_hf3_vm_frame_s* vmf, const bcore_arr_sz_s* arr_idx );

    /** Solve computes the result 'r' from an array of arguments 'a'.
      * 'a' represents an array of pointers. The array size is equal to arity.
      * Solve can produced three valid states:
      *   Detached (NULL): E.g. when Arguments do not (yet) supply sufficient information (e.g. due to insufficient connectivity)
      *   Vacant (dimensions are fully determined)
      *   Determined - This represents a holor computed from literals and can itself be treated as literal.
      *
      * Return:
      *   0: A valid result could be computed
      *   1: Output is settled for given operation (graph spanned by operation can be discarded)
      *   Negative values indicate errors
      *   -1: Incorrect operands for the given operation (syntax error)
      */
    feature 'a' s2_t solve( const, bmath_hf3_s** r, bmath_hf3_s** a );

    feature 'a' ::op* create_final( const, bmath_hf3_s* h ) =
    {
        :ar0_holor_s* final = :ar0_holor_s_create();
        final->h = bcore_fork( h );
        return (::op*)final;
    };

    /// virtual machine operation for forward processing
    feature 'a' bmath_hf3_vm_op* create_vm_op( const, const bmath_hf3_s** a, const bmath_hf3_s* r ) = { return NULL; };

    /** virtual machine operation for forward processing (towards axon).
      * Index array: (channel 0, ..., n-1), output channel
      * (n == arity)
      */
    feature 'a' :create_vm_op_pass create_axonpass = { return NULL; };

    /** virtual machine operation backward gradient propagation (towards dendrite). (n = arity)
      * Index array: channel [0, ...,n-1], output channel, grad-input-channel, grad-output-channel
      * ch_idx: index of input channel for gradient propagation [0, ...,n-1]
      * (n == arity)
      */
    feature 'a' :create_vm_op_pass create_dendpass( sz_t ch_idx ) = { return NULL; };

    /// nullary operator (arity 0)
    group :ar0 =
    {
        feature 'a' bmath_hf3_vm_op* create_vm_op_ar0( const, const bmath_hf3_s* r ) = { return NULL; };

        func :: :get_arity = { return 0; };
        func  : :create_vm_op_ar0 = { return NULL; };
        func :: :create_vm_op     = { return @create_vm_op_ar0( o, r ); };

        /// used for literals
        stamp :holor = aware :
        {
            bmath_hf3_s -> h;
            func :: :solve    =
            {
                bmath_hf3_s_attach( r, bcore_fork( o->h ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

        };

        /// formal input (used for resolving the network; not part of syntax)
        stamp :input = aware :
        {
            bmath_hf3_s -> h;
            func :: :solve    =
            {
                bmath_hf3_s_attach( r, bcore_fork( o->h ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        /// nullary adaptive operator
        stamp :adapt = aware :
        {
            bmath_hf3_s -> h;
            func :: :solve    =
            {
                bmath_hf3_s_attach( r, bcore_fork( o->h ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// unary operator (arity 1)
    group :ar1 = retrievable
    {
        feature 'a' bmath_hf3_vm_op* create_vm_op_ar1( const, const bmath_hf3_s* a, const bmath_hf3_s* r ) = { return NULL; };
        func :: :get_arity        = { return 1; };
        func  : :create_vm_op_ar1 = { return NULL; };
        func :: :create_vm_op     = { return @create_vm_op_ar1( o, a[0], r ); };

        /// ==== using unary functions =====

        stamp :neg = aware :
        {
            func :: :get_symbol       = { return "neg"; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_neg_s_fx ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( bmath_f3_op_ar1_neg_s_fx ); };

            func :: :create_axonpass =
            {
                ASSERT( arr_idx->size == 2 );
                bmath_hf3_vm_op_ar1_unary_s* op = bmath_hf3_vm_op_ar1_unary_s_create_unary( bmath_f3_op_ar1_neg_s_fx );
                op->a = arr_idx->data[ 0 ];
                op->b = arr_idx->data[ 1 ];
                return ( bmath_hf3_vm_op* )op;
            };

            // subtracts gradient
            func :: :create_dendpass =
            {
                ASSERT( arr_idx->size == 4 );
                ASSERT( ch_idx        == 0 );
                bmath_hf3_vm_op_ar2_sub_s* op = bmath_hf3_vm_op_ar2_sub_s_create();
                op->a = arr_idx->data[ 2 ];
                op->b = arr_idx->data[ 3 ];
                op->c = arr_idx->data[ 2 ];
                return ( bmath_hf3_vm_op* )op;
            };

            func :: :create_op_of_arn =
            {
                return ( n == 2 ) ? (::*)::ar2_minus_s_create()
                     : ( n == 1 ) ? (::*)@clone( o )
                     : NULL;
            };
        };

        stamp :floor = aware :
        {
            func :: :get_symbol       = { return "floor"; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, floor ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( floor ); };

            func :: :create_axonpass =
            {
                ASSERT( arr_idx->size == 2 );
                bmath_hf3_vm_op_ar1_unary_s* op = bmath_hf3_vm_op_ar1_unary_s_create_unary( floor );
                op->a = arr_idx->data[ 0 ];
                op->b = arr_idx->data[ 1 ];
                return ( bmath_hf3_vm_op* )op;
            };

            // gradient is zero -> nothing to do
            func :: :create_dendpass =
            {
                ASSERT( arr_idx->size == 4 );
                ASSERT( ch_idx        == 0 );
                bmath_hf3_vm_op_ar0_nul_s* op = bmath_hf3_vm_op_ar0_nul_s_create();
                op->a = arr_idx->data[ 2 ];
                return ( bmath_hf3_vm_op* )op;
            };
        };

        stamp :ceil = aware :
        {
            func :: :get_symbol       = { return "ceil"; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, ceil ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( ceil ); };

            func :: :create_axonpass =
            {
                ASSERT( arr_idx->size == 2 );
                bmath_hf3_vm_op_ar1_unary_s* op = bmath_hf3_vm_op_ar1_unary_s_create_unary( ceil );
                op->a = arr_idx->data[ 0 ];
                op->b = arr_idx->data[ 1 ];
                return ( bmath_hf3_vm_op* )op;
            };

            // gradient is zero -> nothing to do
            func :: :create_dendpass =
            {
                ASSERT( arr_idx->size == 4 );
                ASSERT( ch_idx        == 0 );
                bmath_hf3_vm_op_ar0_nul_s* op = bmath_hf3_vm_op_ar0_nul_s_create();
                op->a = arr_idx->data[ 2 ];
                return ( bmath_hf3_vm_op* )op;
            };
        };

        stamp :tanh = aware :
        {
            func :: :get_symbol       = { return "tanh"; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, tanh ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( tanh ); };

            func :: :create_axonpass =
            {
                ASSERT( arr_idx->size == 2 );
                bmath_hf3_vm_op_ar1_unary_s* op = bmath_hf3_vm_op_ar1_unary_s_create_unary( bmath_f3_op_ar1_tanh_s_fx );
                op->a = arr_idx->data[ 0 ];
                op->b = arr_idx->data[ 1 ];
                return ( bmath_hf3_vm_op* )op;
            };

        };

        stamp :exp = aware :
        {
            func :: :get_symbol       = { return "exp"; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, exp ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( exp ); };
        };

        stamp :relu = aware :
        {
            func :: :get_symbol       = { return "relu"  ; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_relu_s_fx ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( bmath_f3_op_ar1_relu_s_fx ); };
        };

        stamp :lrelu = aware :
        {
            func :: :get_symbol   = { return "lrelu"  ; };
            func :: :get_priority = { return 8; };
            func :: :solve            = { return bhgp_op_ar1_solve_unary( r, a, bmath_f3_op_ar1_relu_leaky_s_fx ); };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_unary_s_create_unary( bmath_f3_op_ar1_relu_leaky_s_fx ); };
        };

        /** marks a holor to be adaptive
         *  Operation is settled when at least a vacant holor can be computed.
         *  If the holor is vacant, it is initialized in the virtual machine.
         */
        stamp :adapt = aware :
        {
            func :: :get_symbol   = { return "adapt"; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r ) ? 1 : 0; // (!) settles on vacant
            };

            func :: :create_final =
            {
                ::ar0_adapt_s* final = ::ar0_adapt_s_create();
                final->h = bcore_fork( h );
                return (:::op*)final;
            };
        };

        stamp :identity = aware :
        {
            func :: :solve =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_cpy_s_create(); };
        };

        /// formal output (used for resolving the network; not part of syntax)
        stamp :output = aware :
        {
            func :: :solve =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
            func  : :create_vm_op_ar1 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar1_cpy_s_create(); };
        };

        stamp :dimof = aware :
        {
            func :: :get_symbol   = { return "dimof" ; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bmath_hf3_s_set_scalar_f3( *r, a[0]->d_size ? a[0]->d_data[ a[0]->d_size - 1 ] : 1 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :rand = aware :
        {
            func :: :get_symbol   = { return "rand" ; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bmath_hf3_s_copy( *r, a[0] );
                    if( !(*r)->v_size ) bmath_hf3_s_fit_v_size( *r );
                    f3_t sum = f3_abs( bmath_hf3_s_f3_sum( *r ) );
                    f3_t max = f3_abs( bmath_hf3_s_f3_max( *r ) );
                    f3_t rbase = ( max > 0 ) ? ( sum / max ) : 0;
                    u2_t rval = rbase * 21036284023;
                    rval += (*r)->v_size;
                    if( rval == 0 ) rval = 1;
                    bmath_hf3_s_set_random( *r, 1.0, -1.0, 1.0, &rval );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// binary operator (arity 2)
    group :ar2 = retrievable
    {
        feature 'a' bmath_hf3_vm_op* create_vm_op_ar2( const, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r ) = { return NULL; };
        func :: :get_arity = { return 2; };

        func  : :create_vm_op_ar2 = { return NULL; };
        func :: :create_vm_op     = { return @create_vm_op_ar2( o, a[0], a[1], r ); };

        stamp :bmul = aware :
        {
            func :: :get_symbol   = { return "**"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_set_d_bmul( a[0], a[1], *r ) ) return -1;
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_bmul( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_bmul_s_create(); };
        };

        stamp :bmul_htp = aware :
        {
            func :: :get_symbol   = { return "*^"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_set_d_bmul_htp( a[0], a[1], *r ) ) return -1;
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_bmul_htp( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_bmul_htp_s_create(); };
        };

        stamp :htp_bmul = aware :
        {
            func :: :get_symbol   = { return "^*"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_set_d_htp_bmul( a[0], a[1], *r ) ) return -1;
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_htp_bmul( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_htp_bmul_s_create(); };
        };

        stamp :htp_bmul_htp = aware :
        {
            func :: :get_symbol   = { return "^*^"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_set_d_htp_bmul_htp( a[0], a[1], *r ) ) return -1;
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_htp_bmul_htp( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_htp_bmul_htp_s_create(); };
        };

        stamp :mul = aware :
        {
            func :: :get_symbol   = { return "*"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->d_size == 0 )
                    {
                        bmath_hf3_s_copy_d_data( *r, a[1] );
                        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                        {
                            bmath_hf3_s_fit_v_size( *r );
                            bmath_hf3_s_mul_scl( a[1], a[0]->v_data, *r );
                        }
                    }
                    else if( a[1]->d_size == 0 )
                    {
                        bmath_hf3_s_copy_d_data( *r, a[0] );
                        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                        {
                            bmath_hf3_s_fit_v_size( *r );
                            bmath_hf3_s_mul_scl( a[0], a[1]->v_data, *r );
                        }
                    }
                    else
                    {
                        if( a[0]->d_size != a[1]->d_size ) return -1;
                        if( bmath_hf3_s_d_product( a[0] ) != bmath_hf3_s_d_product( a[1] ) ) return -1;
                        bmath_hf3_s_copy_d_data( *r, a[0] );
                        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                        {
                            bmath_hf3_s_fit_v_size( *r );
                            bmath_hf3_s_hmul( a[0], a[1], *r );
                        }
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2;
        };

        stamp :plus = aware :
        {
            func :: :get_symbol   = { return "+"; };
            func :: :get_priority = { return 8; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->d_size != a[1]->d_size ) return -1;
                    if( bmath_hf3_s_d_product( a[0] ) != bmath_hf3_s_d_product( a[1] ) ) return -1;
                    bmath_hf3_s_copy_d_data( *r, a[0] );
                    if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_add( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_add_s_create(); };
        };

        stamp :minus = aware :
        {
            func :: :get_symbol   = { return "-"; };
            func :: :get_priority = { return 8; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->d_size != a[1]->d_size ) return -1;
                    if( bmath_hf3_s_d_product( a[0] ) != bmath_hf3_s_d_product( a[1] ) ) return -1;
                    bmath_hf3_s_copy_d_data( *r, a[0] );
                    if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_sub( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :  :create_vm_op_ar2 = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_sub_s_create(); };

            func :: :create_op_of_arn =
            {
                return ( n == 2 ) ? (::*)@clone( o )
                     : ( n == 1 ) ? (::*)::ar1_neg_s_create()
                     : NULL;
            };
        };

        stamp :equal = aware :
        {
            func :: :get_symbol   = { return "=="; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r ) bmath_hf3_s_set_scalar_f3( *r, bmath_hf3_s_is_equal( a[0], a[1] ) ? 1 : 0 );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :larger = aware :
        {
            func :: :get_symbol   = { return ">"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bmath_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bmath_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] > a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :smaller = aware :
        {
            func :: :get_symbol   = { return "<"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bmath_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bmath_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] < a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :larger_equal = aware :
        {
            func :: :get_symbol   = { return ">="; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bmath_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bmath_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] >= a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :smaller_equal = aware :
        {
            func :: :get_symbol   = { return "<="; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bmath_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bmath_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] <= a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :logic_and = aware :
        {
            func :: :get_symbol   = { return "&"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bmath_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bmath_hf3_s_set_scalar_f3( *r, ( a[0]->v_data[0] > 0 ) && ( a[1]->v_data[0] > 0 ) ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :logic_or = aware :
        {
            func :: :get_symbol   = { return "|"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bmath_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bmath_hf3_s_set_scalar_f3( *r, ( a[0]->v_data[0] > 0 ) || ( a[1]->v_data[0] > 0 ) ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :index = aware : // r-value is (scalar) index
        {
            func :: :get_priority = { return 20; };
            func :: :solve = // r->v_data will be weak
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[1]->v_size != 1 ) return -1;
                    sz_t index = a[1]->v_data[ 0 ];
                    if( a[0]->d_size == 0 ) return -1;
                    if( index < 0 || index >= a[0]->d_data[ a[0]->d_size - 1 ] ) return -1;
                    bmath_hf3_s_clear( *r );
                    bmath_hf3_s_set_d_data( *r, a[0]->d_data, a[0]->d_size -1 );
                    if( a[0]->v_data )
                    {
                        (*r)->v_size = bmath_hf3_s_d_product( *r );
                        (*r)->v_data = a[0]->v_data + index * (*r)->v_size;
                        (*r)->v_space = 0;
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :inc_order = aware : // l-value is (scalar) increment
        {
            func :: :get_priority = { return 20; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->v_size != 1 ) return -1;
                    sz_t dim = a[0]->v_data[ 0 ];
                    if( dim <= 0 ) return -1;
                    bmath_hf3_s_copy( *r, a[1] );
                    bmath_hf3_s_inc_order( *r, dim );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :cat = aware : // catenates two holors according to catenation rule defined in bmath_hf3_s_set_d_cat
        {
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bmath_hf3_s_attach( r, ( a[0] && a[1] ) ? bmath_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bmath_hf3_s_set_d_cat( a[0], a[1], *r ) ) return -1;
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bmath_hf3_s_fit_v_size( *r );
                        bmath_hf3_s_cat( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };
    };

    ///  ternary operator (arity 3)
    group :ar3 = retrievable
    {
        feature 'a' bmath_hf3_vm_op* create_vm_op_ar3( const, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* c, const bmath_hf3_s* r ) = { return NULL; };
        func :: :get_arity = { return  3; };
        func  : :create_vm_op_ar3 = { return NULL; };
        func :: :create_vm_op     = { return @create_vm_op_ar3( o, a[0], a[1], a[2], r ); };

        stamp :branch = aware : // arg[0] scalar condition, arg[1] ( cond > 0 ), arg[2] ( cond <= 0 )
        {
            func :: :get_priority = { return  5; };
            func :: :solve =
            {
                if( a[0] )
                {
                    if( a[0]->v_size != 1 ) return -1;
                    f3_t cond = a[0]->v_data[ 0 ];
                    if( cond > 0 )
                    {
                        bmath_hf3_s_attach( r, bcore_fork( a[1] ) );
                    }
                    else
                    {
                        bmath_hf3_s_attach( r, bcore_fork( a[2] ) );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// semantic group
group :sem =
{
    signature   ::get_sz get_arity;
    signature   ::get_sz get_priority;
    feature 'a' ::get_tp get_name  = { return 0; };
    body                 get_name_ = { return o->name; };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // bidirectional link
    stamp :link = aware :
    {
        tp_t name;
        private :link_s -> up;   // up link
        private :link_s -> dn;   // down link
        private  vd_t cell; // cell owning the link (only if link is part of membrane)
        bl_t     exit; // true: link is of cell's exit membrane. false: entry membrane
        func : : get_name = :get_name_;
    };

    signature   bl_t    name_exists(      const,   tp_t name );
    signature ::sem*    get_sem_by_name(  mutable, tp_t name );
    signature  :link_s* get_link_by_name( mutable, tp_t name );
    signature  :link_s* get_link_by_open( mutable );
    signature  :link_s* get_link_by_up(  mutable, :link_s* up );
    signature  :link_s* get_link_by_dn(  mutable, :link_s* dn );
    signature  sz_t     get_index_by_link( mutable, :link_s* link ); // returns -1 if not found
    signature ::get_sz  count_open;

    stamp :links = aware bcore_array
    {
        :link_s => [];

        func : :get_link_by_name =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return o->data[ i ];
            return NULL;
        };

        func : :name_exists =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return true;
            return false;
        };

        func : :get_link_by_up =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->up == up ) return o->data[ i ];
            return NULL;
        };

        func : :get_link_by_dn =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->dn == dn ) return o->data[ i ];
            return NULL;
        };

        func : :get_index_by_link =
        {
            BFOR_EACH( i, o ) if( o->data[ i ] == link ) return i;
            return -1;
        };

        func : :count_open =
        {
            sz_t count = 0;
            BFOR_EACH( i, o ) count += ( o->data[ i ]->up == NULL );
            return count;
        };
    };

    stamp :body = aware bcore_array
    {
        aware : => [];

        func : :name_exists =
        {
            BFOR_EACH( i, o ) if( :a_get_name( o->data[ i ] ) == name ) return true;
            return false;
        };

        func : :get_sem_by_name =
        {
            BFOR_EACH( i, o ) if( :a_get_name( o->data[ i ] ) == name ) return o->data[ i ];
            return NULL;
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // cell

    signature :link_s* get_enc_by_name(  mutable, tp_t name );
    signature :link_s* get_enc_by_open(  mutable );
    signature :link_s* get_enc_by_dn(    mutable, :link_s* dn );
    signature :link_s* get_exc_by_name(  mutable, tp_t name );
    signature :cell_s* get_cell_by_name( mutable, tp_t name );

    stamp :cell = aware :
    {
                tp_t       name;
               :links_s    encs; // entry channels
               :links_s    excs; // exit channels
               :body_s  => body;
        aware ::op      -> op;   // cell holds either operator (cell is a node) or body (cell is a graph) or neither (cell is a wrapper)
                sz_t       priority = 10;

        private :cell_s* parent; // lexical parent

        hidden bcore_source_point_s source_point;

        func : :get_name = :get_name_;
        func : :get_arity =       { return :links_s_count_open(       &o->encs       ); };
        func : :get_enc_by_name = { return :links_s_get_link_by_name( &o->encs, name ); };
        func : :get_exc_by_name = { return :links_s_get_link_by_name( &o->excs, name ); };
        func : :get_enc_by_open = { return :links_s_get_link_by_up(   &o->encs, NULL ); };
        func : :get_enc_by_dn   = { return :links_s_get_link_by_dn(   &o->encs, dn   ); };
        func : :get_priority    = { return o->priority; };

        func : :get_cell_by_name =
        {
            ::sem* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
            if( sem && sem->_ == TYPEOF_:cell_s ) return ( :cell_s* )sem;
            if( o->parent ) return :cell_s_get_cell_by_name( o->parent, name );
            return NULL;
        };

    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// evaluation stack indicators
    stamp :stack_flag = aware : {};
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// tree group
group :ctr =
{
    stamp :node = aware bcore_array
    {
        sz_t id = -1;
        private ::sem_cell_s -> cell;
        private :node_s -> parent;
        :node_s => [];
    };

    stamp :tree = aware :
    {
        sz_t id_base = 0; // (incremented when adding nodes)
        :node_s => root;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// network group
group :net =
{
    stamp :link = aware :
    {
        hidden vd_t /* :node_s* */ node; // (!) target is a node
    };

    stamp :links = aware bcore_array { :link_s => []; };

    signature void solve( mutable );

    stamp :node = aware :
    {
        :links_s upls; // uplinks
        :links_s dnls; // downlinks

        /** Temporary flag used for various tracing routines.
          * It is typically used to ensure a node is visited only once.
          * Normalized state: false
          */
        bl_t flag = false;

        /** Node ID.
          * When the network cell is normalized, id is identical with the cell->body index.
          * id is also used to address the holor in the virtual machine.
          */
        sz_t id;

        /** Gradient ID.
          * Indicates the location of the gradient holor for the node.
          * -1 means: node needs no gradient.
          */
        sz_t gid = -1;

        tp_t name;
        aware ::op -> op;

        bmath_hf3_s-> h; // holor after solving network

        bcore_source_point_s -> source_point;

        func : :solve;
    };

    signature :node_s* get_by_id( mutable, sz_t id );
    stamp :nodes = aware bcore_array
    {
        :node_s => [];
        func : :get_by_id =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->id == id ) return o->data[ i ];
            return NULL;
        };
    };

    signature void normalize( mutable );
    signature void clear_flags( mutable );
    signature bl_t is_consistent( const );
    signature void clear_downlinks( mutable );
    signature void set_downlinks( mutable );

    stamp :cell = aware :
    {
        sz_t max_depth = 32768; // maximum recursion depth
        :nodes_s body;
        :nodes_s encs; // entry channels
        :nodes_s excs; // exit channels

        func : :is_consistent;
        func : :normalize; // re-entrant

        func : :clear_flags =
        {
            BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
        };

        func : :solve =
        {
            BFOR_EACH( i, &o->excs ) bhgp_net_node_s_solve( o->excs.data[ i ] );
        };

        func : :clear_downlinks =
        {
            BFOR_EACH( i, &o->body ) bhgp_net_links_s_clear( &o->body.data[ i ]->dnls );
        };

        func : :set_downlinks;

        func bcore_inst_call : copy_x; // cell is copyable
        func bcore_via_call  : mutated = { ERR_fa( "Cannot reconstitute." ); }; // cell is not transferable
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// virtual machine
group :vm =
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // procedure names
    name infer;

    // holor types
    name data;       // any type of data holder
    name adaptive;
    name depletable; // holor can be set to vacant before shelving

    stamp :adaptive = aware badapt_adaptive
    {

        // === architecture parameters ================================

        st_s                   frame; // frame signature
        st_s                   src;   // path to holograph used by builder (here just for reference)
        bmath_hf3_vm_frame_s   vm;    // virtual machine
        badapt_dynamics_std_s  dynamics;
        sz_t                   in_size;  // input vector size
        sz_t                   out_size; // output vector size
        sz_t                   in_index; // index into vm-holor array
        sz_t                  out_index; // index into vm-holor array

        // ==============================================================

        // === adaptive functions =======================================
        func ^ : get_in_size  = { return o->in_size;  };
        func ^ : get_out_size = { return o->out_size; };
        func ^ : get_dynamics_std = { badapt_dynamics_std_s_copy( dynamics, &o->dynamics ); };
        func ^ : set_dynamics_std = { badapt_dynamics_std_s_copy( &o->dynamics, dynamics ); };

//        func ^ : arc_to_sink;
        func ^ : minfer;

//        func ^ : bgrad;
        func ^ : bgrad_adapt = {};
        // ==============================================================
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :builder = aware badapt_builder
    {
        st_s frame = "( y => dim_y, a )"; // frame signature
        st_s src; // path to source file

        sz_t in_size;  // input vector size
        sz_t out_size; // output vector size
        badapt_dynamics_std_s dynamics;

        u2_t rseed = 1234; /* seed for adaptive randomizer */

        // === builder functions =======================================

        /// input vector size
        func ^ : get_in_size = { return o->in_size; };
        func ^ : set_in_size = { o->in_size = size; };

        /// output vector size
        func ^ : get_out_size = { return o->out_size; };
        func ^ : set_out_size = { o->out_size = size; };

        /// builds adaptive ready to be trained; passes ownership
        func ^ : build;

        // ==============================================================
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// evaluation
group :eval =
{
    /// runs test, returns 0 on success.
    feature 'a' s2_t run( const );
    func bcore_main : main = { return @run( o ); };

    /// end to end test for a cell on a virtual machine
    stamp :e2e = aware :
    {
        st_s sig = "(y=>a)";    // frame signature
        bcore_file_path_s src;  // source file
        bmath_hf3_adl_s => in;  // input holors
        bmath_hf3_adl_s => out; // expected output holors (if NULL, output is sent to log)
        s2_t verbosity  = 10;   // verbosity
        f3_t max_dev    = 1E-8; // if output deviation exceeds this value an error is generated
        hidden aware bcore_sink -> log;

        // constructor
        func bcore_inst_call : init_x = { o->log = bcore_fork( BCORE_STDOUT ); };
        func               : : run;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// global context
stamp :context = aware :
{
    bcore_hmap_name_s hmap_name;
    bcore_arr_st_s    arr_symbol_op2;
    :sem_cell_s       cell; // frame of a cell structure
    bcore_arr_tp_s    control_types; // types reserved for control and not allowed for identifiers
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION
#endif // TYPEOF_bhgp

/**********************************************************************************************************************/

void bhgp_simple_test( void );
void bhgp_simple_eval( void );
void bhgp_adaptive_test( void );

/**********************************************************************************************************************/

vd_t bhgp_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BHGP_H
