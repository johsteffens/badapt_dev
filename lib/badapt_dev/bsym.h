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
 */

#ifndef BSYM_H
#define BSYM_H

#include "bmath_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_planted.h"

/**********************************************************************************************************************/
/// prototypes

void bmath_hf3_s_trace_to_sink( const bmath_hf3_s* o, sz_t indent, bcore_sink* sink );

/// name manager
sc_t bsym_ifnameof( tp_t name );
tp_t bsym_entypeof( sc_t name );

/**********************************************************************************************************************/

#ifdef TYPEOF_bsym
PLANT_GROUP( bsym, bcore_inst )
#ifdef PLANT_SECTION

/// control types
name link;
name holor;
name graph;

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

    /// operator arity (number of input channels)
    feature strict 'a' sz_t get_arity( const );

    /// operator priority; -1 means: use default priority of node
    feature 'a' sz_t get_priority( const ) = { return -1; };

    /// nullary operator (arity 0)
    group :ar0 =
    {
        /// holor types
        name adaptive;
        name buffer;
        name literal;

        feature strict 'a' bl_t compute_hf3( const,  bmath_hf3_s* r );
        feature 'a' bmath_hf3_vm_op* create_vm_operator( const, const bmath_hf3_s* r ) = { return NULL; };

        feature 'a' tp_t get_hf3_type( const );

        stamp :holor = aware :
        {
            tp_t type;
            bmath_hf3_s hf3;

            func :: :get_arity = { return 0; };

            func :: :trace_to_sink =
            {
                bcore_sink_a_push_fa( sink, "(#<sc_t>)", ifnameof( o->type ) );
                bmath_hf3_s_to_sink( &o->hf3, sink );
            };

            func : :compute_hf3 =
            {
                bmath_hf3_s_copy( r, &o->hf3 ); return true;
            };

            func : :get_hf3_type =
            {
                return o->type;
            };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// unary operator (arity 1)
    group :ar1 = retrievable
    {
        feature strict 'a' sc_t get_symbol( const );
        feature 'a' bl_t             compute_hf3(        const, const bmath_hf3_s* a,       bmath_hf3_s* r );
        feature 'a' bmath_hf3_vm_op* create_vm_operator( const, const bmath_hf3_s* a, const bmath_hf3_s* r ) = { return NULL; };

        stamp :linear = aware :
        {
            func :: :get_arity  = { return 1; };
            func  : :get_symbol = { return "linear"; };
            func  : :compute_hf3 = { bmath_hf3_s_copy( r, a ); return true; };
        };

        stamp :tanh = aware :
        {
            func :: :get_arity  = { return 1; };
            func  : :get_symbol = { return "tanh"  ; };

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

            func : : create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_tanh_s_create(); };
        };

        stamp :dimof = aware :
        {
            func :: :get_arity  = { return 1; };
            func  : :get_symbol = { return "dimof" ; };

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
        feature 'a' bl_t                    compute_hf3( const, const bmath_hf3_s* a, const bmath_hf3_s* b,       bmath_hf3_s* r );
        feature 'a' bmath_hf3_vm_op* create_vm_operator( const, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r ) = { return NULL; };

        stamp :bmul = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :get_symbol   = { return "<*>"; };
            func :  :compute_hf3;
            func :  :create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_bmul_s_create(); };
        };

        stamp :bmul_htp = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :get_symbol   = { return "<*t>"; };
            func :  :compute_hf3;
            func :  :create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_bmul_htp_s_create(); };
        };

        stamp :htp_bmul = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :get_symbol   = { return "<t*>"; };
            func :  :compute_hf3;
            func :  :create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_htp_bmul_s_create(); };
        };

        stamp :htp_bmul_htp = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :get_symbol   = { return "<t*t>"; };
            func :  :compute_hf3;
            func :  :create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_htp_bmul_htp_s_create(); };
        };

        stamp :mul = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :get_symbol   = { return "*"; };
            func :  :compute_hf3;
            func :  :create_vm_operator;
        };

        stamp :plus = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 8; };
            func :  :get_symbol   = { return "+"; };
            func :  :compute_hf3;
            func :  :create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_add_s_create(); };
        };

        stamp :minus = aware :
        {
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 8; };
            func :  :get_symbol   = { return "-"; };
            func :  :compute_hf3;
            func :  :create_vm_operator = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_sub_s_create(); };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// graph objects
group :net =
{
    /** hresult represents the holor result after the analysis of a sub-graph terminated by a node
     *  It represents a holor with at at least all dimensions determined.
     *  It may also represent holor data.
     *  It contains information to build a virtual machine
     */
    stamp :hresult = aware :
    {
        bmath_hf3_s => hf3; // final holor
        tp_t name;
        tp_t type;          // type of holor
        sz_t vm_index = -1; // holor index (used for virtual machine construction)
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    signature bsym_net* get_net( const );

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// Visualization / Debugging
    feature 'a' void trace_to_sink( const, sz_t indent, bcore_sink* sink ) = {};

    /// Name of link or node
    feature 'a' tp_t get_name( const ) = { return 0; };

    /// Used during cell construction
    feature 'a' void set_body( mutable, :body_s* body ) = {};

    /// returns next node in trace-line; returns NULL if trace-line is open
    feature 'a' :node_s* trace_get_node( mutable ) = { return NULL; };

    /// (traceback) computes hresult and returns reference; returns NULL in case it could not be computed
    feature 'a' :hresult_s* trace_compute_hresult( mutable, bl_t force ) = { return NULL; };

    /// (traceback) removes hresult
    feature 'a' void trace_clear_hresult( mutable ) = {};

    /// (traceback) builds virtual machine
    feature 'a' void trace_build_vm_proc( mutable, bmath_hf3_vm_frame_s* vmf, tp_t proc_name ) = {};

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

        func : : trace_get_node =
        {
            ::net* net = :address_s_get_net( o );
            return net ? :a_trace_get_node( net ) : NULL;
        };

        func : : trace_to_sink =
        {
            :node_s* node = :address_s_trace_get_node( ( :address_s* )o );
            if( node ) :node_s_trace_to_sink( node, indent, sink );
        };

        func : : trace_compute_hresult =
        {
            ::net* net = :address_s_get_net( o );
            return net ? :a_trace_compute_hresult( net, force ) : NULL;
        };

        func : : trace_clear_hresult =
        {
            ::net* net = :address_s_get_net( o );
            if( net ) :a_trace_clear_hresult( net );
        };

        func : : trace_build_vm_proc =
        {
            ::net* net = :address_s_get_net( o );
            if( net ) :a_trace_build_vm_proc( net, vmf, proc_name );
        };

        func : : get_net;
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

        func : : trace_get_node = { return :address_s_trace_get_node( &o->target ); };

        func : : trace_to_sink =
        {
            bcore_sink_a_push_fa( sink, "(#<sc_t>) -> ", ::ifnameof( o->name ) );
            :address_s_trace_to_sink( &o->target, indent, sink );
        };

        func : : trace_compute_hresult = { return :address_s_trace_compute_hresult( &o->target, force ); };
        func : : trace_clear_hresult   = {        :address_s_trace_clear_hresult(   &o->target ); };
        func : : trace_build_vm_proc   = {        :address_s_trace_build_vm_proc(   &o->target, vmf, proc_name ); };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// Procedure names
    name infer;

    stamp :node = aware bcore_array
    {
        tp_t name;
        :address_s [] targets;
        :address_s root;

        /// (operator) payload of node
        aware ::op* op;

        ::source_info_s source_info;

        :hresult_s => hresult;

        private :address_s -> new_root; // only used during embedding

        // .....................................................................

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

        func : : trace_get_node = { return o; };

        func : : trace_to_sink;
        func : : trace_compute_hresult;
        func : : trace_clear_hresult =
        {
            bsym_net_hresult_s_detach( &o->hresult );
            for( sz_t i = 0; i < o->targets_size; i++ ) :address_s_trace_clear_hresult( &o->targets_data[ i ] );
        };

        func : : trace_build_vm_proc;
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// semantic objects
group :sem =
{
//    signature void :build(      mutable, bcore_source* source );
//    signature void :compile_vm( mutable, )

    stamp :graph = aware :
    {
        tp_t name;
        sz_t args_in;
        sz_t args_out;
        bsym_net_body_s body;
        :graph_base_s => graph_base;
        hidden bcore_arr_st_s -> arr_symbol_op2;
        ::source_info_s source_info;

        /// operator-priority (higher value means earlier evaluation; e.g. binary evaluation)
        sz_t priority = 10;
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

/// virtual machine
group :vm =
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :adaptive = aware badapt_adaptive
    {

        // === architecture parameters ================================

        st_s                   holograph_file; // path to holograph used by builder (here just for reference)
        bmath_hf3_vm_frame_s   vm; // virtual machine
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
        /**
         *  Holograph's frame is
         *  ( <name_out_holor> ) => ( <name_out_size>, <name_in_holor> )
         *  using settings below.
         */
        st_s holograph_file; // path to holograph

        st_s name_out_holor = "output";
        st_s name_out_size  = "out_size";
        st_s name_in_holor  = "input";

        sz_t in_size;        // input vector size
        sz_t out_size;       // output vector size
        u2_t rseed = 1234;   // randomizer seed
        badapt_dynamics_std_s dynamics;

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

#endif // PLANT_SECTION
#endif // TYPEOF_bsym

/**********************************************************************************************************************/


void bsym_test( void );

/**********************************************************************************************************************/

vd_t bsym_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BSYM_H
