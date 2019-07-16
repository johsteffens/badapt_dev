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

/**
 *  Symbolic language to describe a graph of operators on holors.
 *
 *  Semantic Cell Concept:
 *  A semantic graph communicates with the objects outside its body through input an output channels.
 *  All links of a graph 'x' to outside objects the node must pass though an input channel of 'x'.
 *  Inside objects may not be referenced directly by outside objects.
 *  A graph adhering to this concept is called 'cell'
 *  An construction of a new graph must conclude with converting it to a cell.
 *  Cells can be used as objects for constricting new graphs.
 *
 *  Static Links:
 *  Defined links of an input channel of a semantic graph are never changed or freed again.
 *  Different use cases of a graph are achieved by creating graph-copies and assigning links of those copies differently.
 */

#ifndef BSYM_H
#define BSYM_H

#include "bmath_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym
PLANT_GROUP( bsym, bcore_inst )
#ifdef PLANT_SECTION

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :source_info = aware bcore_inst
{
    aware bcore_source -> source;
    sz_t index;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// operators
group :op =
{
    feature 'a' void trace_to_sink( const, sz_t indent, bcore_sink* sink ) = {};

    /// nullary operator (arity 0)
    group :ar0 =
    {
        /// holor types
        name adaptive;
        name buffer;
        name const;  // for literals

        feature strict 'a' bl_t compute_hf3( const, bmath_hf3_s* r );

        stamp :holor  = aware :
        {
            tp_t type;
            bmath_hf3_s hf3;

            func :: : trace_to_sink =
            {
                bcore_sink_a_push_fa( sink, "(#<sc_t>)", ifnameof( o->type ) );
                bmath_hf3_s_trace_to_sink( &o->hf3, indent, sink );
            };

            func : : compute_hf3 =
            {
                bmath_hf3_s_copy( r, &o->hf3 ); return true;
            };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// unary operator (arity 1)
    group :ar1 = retrievable
    {
        feature strict 'a' sc_t get_symbol( const );
        feature 'a' bl_t compute_hf3( const, const bmath_hf3_s* a, bmath_hf3_s* r );

        stamp :linear = aware :
        {
            func : :get_symbol = { return "linear"; };
            func : :compute_hf3 = { bmath_hf3_s_copy( r, a ); return true; };
        };

        stamp :tanh   = aware :
        {
            func : :get_symbol = { return "tanh"  ; };

            func : :compute_hf3 =
            {
                bmath_hf3_s_copy_d_data( r, a );
                if( a->v_size > 0 )
                {
                    bmath_hf3_s_fit_v_size( r );
                    for( sz_t i = 0; i < a->v_size; i++ ) r->v_data[ i ] = tanh( a->v_data[ i ] );
                }
                return true;
            };
        };

        stamp :dimof  = aware :
        {
            func : :get_symbol = { return "dimof" ; };

            func : :compute_hf3 =
            {
                if( bmath_hf3_s_d_product( a ) == 0 ) return false;
                bmath_hf3_s_set_d_size( r, 0 );
                bmath_hf3_s_fit_v_size( r );
                if( a->d_size > 0 )
                {
                    r->v_data[ 0 ] = a->d_data[ a->d_size - 1 ];
                }
                else
                {
                    r->v_data[ 0 ] = 1;
                }
                return true;
            };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// binary operator (arity 2)
    group :ar2 = retrievable
    {
        feature strict 'a' sc_t get_symbol( const );
        feature 'a' bl_t compute_hf3( const, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r );

        stamp :mul   = aware :
        {
            func : :get_symbol  = { return "*"; };
            func : :compute_hf3;
        };

        stamp :hmul   = aware :
        {
            func : :get_symbol  = { return "<*>"; };
            func : :compute_hf3;
        };

        stamp :plus   = aware :
        {
            func : :get_symbol  = { return "+"; };
            func : :compute_hf3;
        };

        stamp :minus   = aware :
        {
            func : :get_symbol  = { return "-"; };
            func : :compute_hf3;
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// graph objects
group :net =
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// Visualization / Debugging
    feature 'a' void trace_to_sink( const, sz_t indent, bcore_sink* sink ) = {};

    /// Name of link or node
    feature 'a' tp_t get_name( const ) = { return 0; };

    /// Used during cell construction
    feature 'a' void set_body( mutable, :body_s* body ) = {};

    /// (traceback) computes hf3 on nodes
    feature 'a' bmath_hf3_s* trace_compute_hf3( mutable ) = { return NULL; };

    /// (traceback) resets hf3 computation
    feature 'a' void trace_reset_hf3( mutable ) = {};

    /// (traceback) sets hf3 index; returns highest index specified so far; a new index value must be >= start_index
    feature 'a' sz_t trace_set_hf3_index( mutable, sz_t start_index ) = { return -1; };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :body = aware bcore_array
    {
        aware : => [];
        func bcore_inst_call : copy_x =
        {
            for( sz_t i = 0; i < o->size; i++ ) :a_set_body( o->data[ i ], o );
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /** This adress scheme is necessary to make sub-graphs copyable
     *  Direct addressing or owning is difficult because graphs are not necessarily trees
     *  they may even be cyclic.
     */
    stamp :address = aware bcore_inst
    {
        sz_t index; // index of this link in body (note that 0 may be a valid index)
        hidden vd_t body;  // pointer to :body_s; null indicates that the address is not set
        func : : trace_to_sink =
        {
            ::net* net = :address_s_get_net( o );
            if( net ) :a_trace_to_sink( net, indent, sink );
        };

        func : : trace_compute_hf3 =
        {
            ::net* net = :address_s_get_net( o );
            return net ? :a_trace_compute_hf3( net ) : NULL;
        };

        func : : trace_reset_hf3 =
        {
            ::net* net = :address_s_get_net( o );
            if( net ) :a_trace_reset_hf3( net );
        };

        func : : trace_set_hf3_index =
        {
            ::net* net = :address_s_get_net( o );
            return net ? :a_trace_set_hf3_index( net, start_index ) : -1;
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :link  = aware :
    {
        tp_t name;
        :address_s target;
        :address_s root;

        bl_t flag; // used during cell computing

        func : : get_name = { return o->name; };

        func : : set_body =
        {
            if( o->target.body && o->target.body == o->root.body )
            {
                o->target.body = body;
            }
            o->root.body = body;
        };

        func : : trace_to_sink =
        {
            bcore_sink_a_push_fa( sink, "(#<sc_t>) --> ", :link_s_get_name_sc( o ) );
            :address_s_trace_to_sink( &o->target, indent, sink );
        };

        func : : trace_compute_hf3   = { return :address_s_trace_compute_hf3(   &o->target ); };
        func : : trace_reset_hf3     = {        :address_s_trace_reset_hf3(     &o->target ); };
        func : : trace_set_hf3_index = { return :address_s_trace_set_hf3_index( &o->target, start_index ); };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :node = aware bcore_array
    {
        tp_t name;
        :address_s [] targets;
        :address_s root;

        aware ::op* op;

        ::source_info_s source_info;

        /// holor adata

        bmath_hf3_s => hf3;  // output holor (constructed during tracing)
        sz_t hf3_index = -1; // holor index (used for virtual machine construction)

        private :address_s -> new_root; // only used during embedding

        /// functions

        func : : get_name = { return o->name; };

        func : : set_body =
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

        func : : trace_to_sink;
        func : : trace_compute_hf3;
        func : : trace_reset_hf3 =
        {
            bmath_hf3_s_detach( &o->hf3 );
            for( sz_t i = 0; i < o->targets_size; i++ ) :address_s_trace_reset_hf3( &o->targets_data[ i ] );
        };

        func : : trace_set_hf3_index =
        {
            if( o->hf3_index >= 0 ) return o->hf3_index;
            sz_t last_index = start_index - 1;
            for( sz_t i = 0; i < o->targets_size; i++ )
            {
                last_index = sz_max( last_index, :address_s_trace_set_hf3_index( &o->targets_data[ i ], last_index + 1 ) );
            }
            o->hf3_index = last_index + 1;
            return o->hf3_index;
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// semantic objects
group :sem =
{
    stamp :graph = aware :
    {
        tp_t name;
        sz_t args_in;
        sz_t args_out;
        bsym_net_body_s body;
        :graph_base_s => graph_base;
        hidden bcore_arr_st_s -> arr_symbol_op2;
        ::source_info_s source_info;
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :graph_base = aware bcore_array
    {
        private :graph_base_s -> parent;
        aware : => [];
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// evaluation stack indicators
    stamp :stack_flag = aware : {};

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

#endif // PLANT_SECTION
#endif // TYPEOF_bsym

/**********************************************************************************************************************/

bsym_net* bsym_net_address_s_get_net( const bsym_net_address_s* o );
sc_t      bsym_net_link_s_get_name_sc( const bsym_net_link_s* o );
void      bmath_hf3_s_trace_to_sink( const bmath_hf3_s* o, sz_t indent, bcore_sink* sink );

void bsym_test( void );

/**********************************************************************************************************************/

vd_t bsym_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BSYM_H
