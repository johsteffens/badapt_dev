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

/** Symbolic representation of an adaptive
 */

/*
    ========================================

    given globals:
    variables: g_in, g_out
    various literals (numbers, activation functions, operators)

    ========================================
    MLP

    node layer = ( dim_y, x ) => ( y )
    {
        mutor adaptive w = [ dim_y ][ dimof( x ) ]#, b = [ dim_y ]#;
        y -> ( w * x ) + b;
    };

    node mlp = ( x ) => ( y )
    {
        node l1 = layer( dim -> 10, x -> x    );
        node l2 = layer( dim -> 20, x -> act_relu( l1.y ) );
        node l3 = layer( dim ->  1, x -> act_relu( l2.y ) );
        y -> act_tanh( l3.y );
    };

    g_out -> mlp( g_in );

    ========================================
    LSTM

    node layer = ( dim_h, x, ci, hi ) => ( co, ho )
    {
        // = type def
        mutor adaptive w_fx = [ dim_h ][ dimof( x ) ]#, w_fh = [ dim_h ][ dimof( x ) ]#, b_f = [ dim_h ]#;
        mutor adaptive w_ix = [ dim_h ][ dimof( x ) ]#, w_ih = [ dim_h ][ dimof( x ) ]#, b_i = [ dim_h ]#;
        mutor adaptive w_ox = [ dim_h ][ dimof( x ) ]#, w_oh = [ dim_h ][ dimof( x ) ]#, b_o = [ dim_h ]#;
        mutor adaptive w_qx = [ dim_h ][ dimof( x ) ]#, w_qh = [ dim_h ][ dimof( x ) ]#, b_q = [ dim_h ]#;

        link v_f -> act_sig ( ( w_fx * x ) + ( w_fh * hi ) + b_f );
        link v_i -> act_sig ( ( w_ix * x ) + ( w_ih * hi ) + b_i );
        link v_o -> act_sig ( ( w_ox * x ) + ( w_oh * hi ) + b_o );
        link v_q -> act_tanh( ( w_qx * x ) + ( w_qh * hi ) + b_q );

        co  -> ( v_f <o> ci ) + ( v_i <o> v_q );
        link v_d -> act_tanh( co );
        ho  -> ( v_o <o> v_d );
    };

    node lstm = ( dim_h, x ) => ( y )
    {
        mutor adaptive w_r = [ dim_h ][ dimof( x ) ]#, b_r = [ dim_h ]#;
        mutor recurrent c = [ dim_h ]#, h = [ dim_h ]#;

        node l1 = layer( dim_h -> dim_h, x -> x, ci -> c, hi -> h );

        h -> l1.ho;
        c -> l1.co;

        y -> act_tanh( w_r * h + b_r );
    }

    g_out -> lstm( dim_h -> 200, x -> g_in ).y;

    - parse into graph (parse into node)
    - graph: mesh of nodes
    - node: inputs, outputs, body
    - a graph is also a node
    - definition: stand-alone node with identifier
    - operation: node embedded in a graph
    - once a graph is complete, data types can be finalized

*/

#ifndef BADAPT_SYM_H
#define BADAPT_SYM_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_precoded.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_badapt_operator0
BETH_PRECODE( badapt_operator0 )
#ifdef BETH_PRECODE_SECTION

feature 'a' sr_s forward( const ) = { ERR_fa( "Not implemented." ); return sr_null(); };

stamp :scalar = aware :
{
    f3_t value;
    func :forward = { return sr_f3( o->value ); };
}; // scalar constant

#endif // BETH_PRECODE_SECTION
#endif // TYPEOF_badapt_operator0

/**********************************************************************************************************************/

#ifdef TYPEOF_badapt_operator1
BETH_PRECODE( badapt_operator1 )
#ifdef BETH_PRECODE_SECTION

feature 'a' sr_s forward( const, sr_s arg ) = { ERR_fa( "Not implemented." ); return sr_null(); };

stamp :linear = aware : { };
stamp :tanh   = aware : { };
stamp :dimof  = aware : { }; // dimension of input

#endif // BETH_PRECODE_SECTION
#endif // TYPEOF_badapt_operator1

/**********************************************************************************************************************/

#ifdef TYPEOF_badapt_operator2
BETH_PRECODE( badapt_operator2 )
#ifdef BETH_PRECODE_SECTION

feature 'a' sr_s forward( const, sr_s arg1, sr_s arg2 ) = { ERR_fa( "Not implemented." ); return sr_null(); };

/// we prepend '__' when operators are not meant to be used by name but by an associated symbol
stamp :__mul   = aware : { }; // symbol '*'
stamp :__hmul  = aware : { }; // symbol '<*>' (hadamard product)
stamp :__plus  = aware : { }; // symbol '+'
stamp :__minus = aware : { }; // symbol '-'

#endif // BETH_PRECODE_SECTION
#endif // TYPEOF_badapt_operator2

/**********************************************************************************************************************/

#ifdef TYPEOF_badapt_sym
BETH_PRECODE( badapt_sym )
#ifdef BETH_PRECODE_SECTION

feature 'a' bl_t is_operator( const ) = { return false; }; // item is operator
feature 'a' bl_t is_node(     const ) = { return false; }; // item is node
feature 'a' bl_t is_link(     const ) = { return false; }; // item is link

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :items = aware bcore_array
{
    aware badapt_sym => [];
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// The target of a link can be null, another link or an operator
stamp :link = aware :
{
    tp_t name;
    aware badapt_sym -> target;
    hidden vd_t frame;
    func : is_link = { return true; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :args = aware bcore_array
{
    :link_s [];

    hidden vd_t frame;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :dim  = aware bcore_inst  { :link_s link; };
stamp :dims = aware bcore_array { :dim_s []; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :mutor = aware :
{
    tp_t name;
    tp_t type; // adaptive, recurrent, etc
    :dims_s dims;

    hidden vd_t frame;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node = aware :
{
    /// certain names refer to predefined binary and unary operators
    tp_t name;
    :args_s  args_in;
    :args_s  args_out;
    :items_s body;

    /* we want to copy the pointer but not treat it as link */
    hidden vd_t parent_node;
    hidden vd_t frame;

    /// optional data load (e.g. const value)
    sr_s load;

    func : is_node = { return true; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// const-operator
stamp :operator0 = aware :
{
    aware badapt_operator0 => operator;
    func : is_operator = { return true; };
};

// unary-operator
stamp :operator1 = aware :
{
    :link_s link;
    aware badapt_operator1 => operator;
    func : is_operator = { return true; };
};

// binary-operator
stamp :operator2 = aware :
{
    :link_s link1;
    :link_s link2;
    aware badapt_operator2 => operator;
    func : is_operator = { return true; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :frame = aware bcore_inst
{
    bcore_hmap_name_s hmap_name;
    :node_s root;

    func bcore_inst_call : init_x =
    {
        badapt_sym_frame_s_setup( o );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // BETH_PRECODE_SECTION
#endif // TYPEOF_badapt_sym

void badapt_sym_frame_s_setup( badapt_sym_frame_s* o );

void badapt_sym_test( void );

/**********************************************************************************************************************/

vd_t badapt_sym_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_SYM_H
