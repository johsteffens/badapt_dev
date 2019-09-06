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
 *  <*>,
 *  <*t>,
 *  <t*>,
 *  <t*t>       9     holor-product for holors up to order 2; 'T' indicates which side is considered transposed

 *  <name>     10     Custom operator (defined by a graph with two free inputs and one output)
 *
 *  Possible name ?
 *     holocell
 *     holorcell  (unused)
 *     holograph
 *     holorgraph
 */

#ifndef BHGP_H
#define BHGP_H

#include "bmath_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_planted.h"

/**********************************************************************************************************************/
/// prototypes

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

/// operator scope
group :op =
{
    feature strict 'a' ::get_sz get_arity;
    feature        'a' ::get_sz get_priority = { return 10; };
    feature        'a' ::get_sc get_symbol   = { return NULL; };

    /** Solve computes the result 'r' from an array of arguments 'a'.
      * 'a' represents an array of pointers. The array size is equal to arity.
      * Solve can produced three valid states:
      *   Detached (NULL): E.g. when Arguments do not (yet) supply sufficient information (e.g. due to insufficient connectivity)
      *   Vacant (dimensions are fully determined)
      *   Determined - This represents a holor computed from literals and can itself be treated as literal.
      *
      * Return:
      *   0: A valid result could be computed
      *   1: output is settled for given operation
      *   Negative values indicate errors
      *   -1: Incorrect operands for the given operation (A valid result cannot be computed)
      */
    feature 'a' s2_t solve( const, bmath_hf3_s** r, bmath_hf3_s** a );

    /// nullary operator (arity 0)
    group :ar0 =
    {
        stamp :holor = aware :
        {
            bmath_hf3_s -> h;
            func :: :get_arity = { return 0; };
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
            func :: :get_arity = { return 0; };
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
        feature 'a' bmath_hf3_vm_op* create_vm_op( const, const bmath_hf3_s* a, const bmath_hf3_s* r ) = { return NULL; };

        stamp :linear = aware :
        {
            func :: :get_symbol   = { return "linear"; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :relu = aware :
        {
            func :: :get_symbol   = { return "relu"  ; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            //func  : :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_relu_s_create(); };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bmath_hf3_s_copy_size( *r, a[0] );
                    if( a[0]->v_size ) bmath_hf3_s_relu( a[0], *r );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :lrelu = aware :
        {
            func :: :get_symbol   = { return "lrelu"  ; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            //func  : :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_lrelu_s_create(); };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bmath_hf3_s_copy_size( *r, a[0] );
                    if( a[0]->v_size ) bmath_hf3_s_lrelu( a[0], *r );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :tanh = aware :
        {
            func :: :get_symbol   = { return "tanh"  ; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func  : :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_tanh_s_create(); };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bmath_hf3_s_copy_size( *r, a[0] );
                    if( a[0]->v_size ) bmath_hf3_s_tanh( a[0], *r );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :exp = aware :
        {
            func :: :get_symbol   = { return "exp"  ; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func  : :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_tanh_s_create(); };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bmath_hf3_s_copy_size( *r, a[0] );
                    if( a[0]->v_size ) bmath_hf3_s_exp( a[0], *r );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        /// marks a holor to be adaptive
        stamp :adapt = aware :
        {
            func :: :get_symbol   = { return "adapt"; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :identity = aware :
        {
            func :: :get_arity    = { return 1; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        /// formal output (used for resolving the network; not part of syntax)
        stamp :output = aware :
        {
            func :: :get_arity    = { return 1; };
            func :: :solve        =
            {
                bmath_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :dimof = aware :
        {
            func :: :get_symbol   = { return "dimof" ; };
            func :: :get_arity    = { return 1; };
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
            func :: :get_arity    = { return 1; };
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
        feature 'a' bmath_hf3_vm_op* create_vm_op( const, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r ) = { return NULL; };

        stamp :bmul = aware :
        {
            func :: :get_symbol   = { return "**"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_bmul_s_create(); };
        };

        stamp :bmul_htp = aware :
        {
            func :: :get_symbol   = { return "*^"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_bmul_htp_s_create(); };
        };

        stamp :htp_bmul = aware :
        {
            func :: :get_symbol   = { return "^*"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_htp_bmul_s_create(); };
        };

        stamp :htp_bmul_htp = aware :
        {
            func :: :get_symbol   = { return "^*^"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_htp_bmul_htp_s_create(); };
        };

        stamp :mul = aware :
        {
            func :: :get_symbol   = { return "*"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op;
        };

        stamp :plus = aware :
        {
            func :: :get_symbol   = { return "+"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_add_s_create(); };
        };

        stamp :minus = aware :
        {
            func :: :get_symbol   = { return "-"; };
            func :: :get_arity    = { return 2; };
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

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_sub_s_create(); };
        };

        stamp :equal = aware :
        {
            func :: :get_symbol   = { return "=="; };
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return 2; };
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
            func :: :get_arity    = { return  2; };
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
            func :: :get_arity    = { return  2; };
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
    };

    ///  tenary operator (arity 3)
    group :ar3 = retrievable
    {
        stamp :branch = aware : // arg[0] scalar condition, arg[1] ( cond > 0 ), arg[2] ( cond <= 0 )
        {
            func :: :get_arity    = { return  3; };
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
            BFOR_EACH( o, i ) if( o->data[ i ]->name == name ) return o->data[ i ];
            return NULL;
        };

        func : :name_exists =
        {
            BFOR_EACH( o, i ) if( o->data[ i ]->name == name ) return true;
            return false;
        };

        func : :get_link_by_up =
        {
            BFOR_EACH( o, i ) if( o->data[ i ]->up == up ) return o->data[ i ];
            return NULL;
        };

        func : :get_link_by_dn =
        {
            BFOR_EACH( o, i ) if( o->data[ i ]->dn == dn ) return o->data[ i ];
            return NULL;
        };

        func : :get_index_by_link =
        {
            BFOR_EACH( o, i ) if( o->data[ i ] == link ) return i;
            return -1;
        };

        func : :count_open =
        {
            sz_t count = 0;
            BFOR_EACH( o, i ) count += ( o->data[ i ]->up == NULL );
            return count;
        };
    };

    stamp :body = aware bcore_array
    {
        aware : => [];

        func : :name_exists =
        {
            BFOR_EACH( o, i ) if( :a_get_name( o->data[ i ] ) == name ) return true;
            return false;
        };

        func : :get_sem_by_name =
        {
            BFOR_EACH( o, i ) if( :a_get_name( o->data[ i ] ) == name ) return o->data[ i ];
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
        private vd_t /* :node_s* */ node; // (!) target is a node
    };

    stamp :links = aware bcore_array { :link_s => []; };

    signature :node_s* solve( mutable );

    stamp :node = aware :
    {
        :links_s upls; // uplinks
        :links_s dnls; // downlinks
        sz_t id;
        aware ::op -> op;
        bmath_hf3_s-> h; // holor after solving

        bcore_source_point_s -> source_point;

        func : :solve;
    };

    signature :node_s* get_by_id( mutable, sz_t id );
    stamp :nodes = aware bcore_array
    {
        :node_s => [];
        func : :get_by_id =
        {
            BFOR_EACH( o, i ) if( o->data[ i ]->id == id ) return o->data[ i ];
            return NULL;
        };
    };

    stamp :cell = aware :
    {
        sz_t max_depth = 65536; // maximum recursion depth for build_trace
        :nodes_s body;
        :nodes_s encs; // entry channels
        :nodes_s excs; // exit channels
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// global context
stamp :context = aware :
{
    bcore_hmap_name_s hmap_name;
    bcore_arr_st_s    arr_symbol_op2;
    :sem_cell_s       cell; // frame of a cell structure
    bcore_arr_tp_s    control_types; // types reserved for control and not suitable for identifiers
};

#endif // PLANT_SECTION
#endif // TYPEOF_bhgp

/**********************************************************************************************************************/

void bhgp_test( void );

/**********************************************************************************************************************/

vd_t bhgp_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BHGP_H
