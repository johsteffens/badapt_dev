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

    node layer = ( y ) => ( dim_y, x )
    {
        mutor adaptive w = [ dim_y ][ dimof( x ) ]#, b = [ dim_y ]#;
        y -> ( w * x ) + b;
    };

    node mlp = ( y ) => ( x )
    {
        node l1 = layer( dim -> 10, x -> x    );
        node l2 = layer( dim -> 20, x -> act_relu( l1.y ) );
        node l3 = layer( dim ->  1, x -> act_relu( l2.y ) );
        y -> act_tanh( l3.y );
    };

    g_out -> mlp( g_in );

    ========================================
    LSTM

    node layer =  ( co, ho ) => ( dim_h, x, ci, hi )
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

    node lstm = ( y ) => ( dim_h, x )
    {
        holor adaptive w_r = [ dim_h ][ dimof( x ) ]#, b_r = [ dim_h ]#;
        holor recurrent c = [ dim_h ]#, h = [ dim_h ]#;

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

#ifndef BSYM_H
#define BSYM_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym_op0
PLANT_GROUP( bsym_op0, bcore_inst )
#ifdef PLANT_SECTION

stamp :holor  = aware bcore_array { sz_t []; }; // fully size determined holor
stamp :number = aware :           { f3_t v;  }; // used as const scalar

#endif // PLANT_SECTION
#endif // TYPEOF_bsym_op0

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym_op1
PLANT_GROUP( bsym_op1, bcore_inst )
#ifdef PLANT_SECTION

stamp :linear = aware : { };
stamp :tanh   = aware : { };
stamp :dimof  = aware : { }; // dimension of input

#endif // PLANT_SECTION
#endif // TYPEOF_bsym_op1

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym_op2
PLANT_GROUP( bsym_op2, bcore_inst )
#ifdef PLANT_SECTION

set enroll;

/// we prepend '__' when operators are not meant to be used by name but by an associated symbol
stamp :__mul   = aware : { }; // symbol '*'
stamp :__hmul  = aware : { }; // symbol '<*>' (hadamard product)
stamp :__plus  = aware : { }; // symbol '+'
stamp :__minus = aware : { }; // symbol '-'

#endif // PLANT_SECTION
#endif // TYPEOF_bsym_op2

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym_net
PLANT_GROUP( bsym_net, bcore_inst )
#ifdef PLANT_SECTION

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' void set_body( mutable, :body_s* body ) = {};
feature 'a' void trace_to_sink( const, sz_t indent, bcore_sink* sink ) = { /*ERR_fa( "Cannot trace #<sc_t>", ifnameof( *(aware_t*)o ) );*/ };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :body  = aware bcore_array
{
    aware : => [];
    bcore_hmap_name_s -> hmap_name;
    func bcore_inst_call : copy_x =
    {
        for( sz_t i = 0; i < o->size; i++ ) bsym_net_a_set_body( o->data[ i ], o );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** This adress scheme is necessary to make sub-networks copyable
 *  Direct addressing or owning is difficult because networks are not necessarily trees
 *  and may even be cyclic.
 */
stamp :address = aware bcore_inst
{
    sz_t index; // index of this link in body (note that 0 may be a valid index)
    hidden vd_t body;  // pointer to :body_s; null indicates that the address is not set
    func bsym_net : trace_to_sink;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :link  = aware :
{
    tp_t name;
    :address_s target;
    :address_s root;

    bl_t flag; // used during embedding

    func bsym_net : set_body =
    {
        if( o->target.body && o->target.body == o->root.body )
        {
            o->target.body = body;
        }
        o->root.body = body;
    };

    func bsym_net : trace_to_sink;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node  = aware bcore_array
{
    tp_t name;
    :address_s [] targets;
    :address_s root;
    private :address_s -> new_root; // only used during embedding
    sr_s load;
    private :body_s -> body;
    func bsym_net : set_body =
    {
        for( sz_t i = 0; i < o->targets_size; i++ )
        {
            :address_s* target = &o->targets_data[ i ];
            if( target->body && target->body == o->root.body )
            {
                target->body = body;
            }
        }
        o->root.body = body;
    };

    func bsym_net : trace_to_sink;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// holor types
name adaptive;
name buffer;

stamp :holor = aware :
{
    tp_t type;
    sz_t dims;
    func bsym_net : trace_to_sink;
}; // dim determined holor

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION
#endif // TYPEOF_bsym_net

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym_sem
PLANT_GROUP( bsym_sem, bcore_inst )
#ifdef PLANT_SECTION

stamp :links = aware bcore_array { bsym_net_link_s []; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node = aware :
{
    tp_t name;
    sz_t args_in;
    sz_t args_out;
    bsym_net_body_s body;
    :node_base_s => node_base;
    hidden bcore_hmap_name_s -> hmap_name;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :node_base = aware bcore_array
{
    private :node_base_s -> parent;
    aware : => [];
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// evaluation stack indicators
stamp :stack_flag = aware : {};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION
#endif // TYPEOF_bsym_sem

/**********************************************************************************************************************/

void bsym_test( void );

/**********************************************************************************************************************/

vd_t bsym_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BSYM_H
