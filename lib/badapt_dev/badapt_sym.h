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

#ifdef TYPEOF_badapt_sym
BETH_PRECODE( badapt_sym )
#ifdef BETH_PRECODE_SECTION

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' tp_t get_name( const );
feature 'a' void parse( mutable, :frame_s* frame, const :node_s* node, bcore_source* source );
feature 'a' void to_sink( const, const :frame_s* frame, bcore_sink* sink );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :items = aware bcore_array
{
    aware badapt_sym => [];
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :link = aware :
{
    tp_t name;
    aware badapt_sym -> target;

    func : get_name = { return o->name; };
    func : parse;
    func : to_sink;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :args = aware bcore_array
{
    :link_s [];

    func badapt_sym : parse;
    func badapt_sym : to_sink;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :dim = aware :
{
    :link_s link;  // to be resolved via link
    sz_t literal = -1; // literal dim
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :dims = aware bcore_array
{
    :dim_s [];
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :mutor = aware :
{
    tp_t name;
    tp_t type; // adaptive, recurrent, etc
    :dims_s dims;

    func : get_name = { return o->name; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node = aware :
{
    /// certain names refer to predefined binary and unary operators
    tp_t name;
    :args_s  args_in;
    :args_s  args_out;
    :items_s body;
    func : get_name = { return o->name; };
    func bcore_inst_call : init_x =
    {
        :items_s_clear( &o->body );
        :args_s_clear( &o->args_in );
        :args_s_clear( &o->args_out );
    };

    func bcore_inst_call : discard_e =
    {
        :items_s_clear( &o->body );
        :args_s_clear( &o->args_in );
        :args_s_clear( &o->args_out );
    };
    func : parse;
    func : to_sink;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :frame = aware :
{
    bcore_hmap_name_s hmap_name;
    :node_s root;
    func bcore_inst_call : discard_e = { :node_s_discard_e( &o->root ); };
    func : parse;
    func : to_sink;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // BETH_PRECODE_SECTION
#endif // TYPEOF_badapt_sym

void badapt_sym_test( void );

/**********************************************************************************************************************/

vd_t badapt_sym_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_SYM_H
