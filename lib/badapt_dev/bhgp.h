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
name link;
name holor;
name cell;

/// operator scope
group :op =
{
    feature strict 'a' ::get_sz get_arity;
    feature        'a' ::get_sz get_priority = { return 10; };
    feature        'a' ::get_sc get_symbol = { return NULL; };

    /// nullary operator (arity 0)
    group :ar0 =
    {
        feature 'a' bl_t apply( const, bmath_hf3_s* r );

        stamp :holor = aware :
        {
            bmath_hf3_s h;
            func :: :get_arity = { return 0; };
            func  : :apply     =
            {
                bmath_hf3_s_copy_size( r, &o->h );
                if( o->h.v_size ) bmath_hf3_s_cpy( &o->h, r );
                return true;
            };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// unary operator (arity 1)
    group :ar1 = retrievable
    {
        feature 'a' bmath_hf3_vm_op* create_vm_op( const, const bmath_hf3_s* a, const bmath_hf3_s* r ) = { return NULL; };
        feature 'a' bl_t apply( const, const bmath_hf3_s* a, bmath_hf3_s* r );

        stamp :linear = aware :
        {
            func :: :get_symbol   = { return "linear"; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func  : :apply        =
            {
                bmath_hf3_s_copy_size( r, a );
                if( a->v_size ) bmath_hf3_s_cpy( a, r );
                return true;
            };
        };

        stamp :tanh = aware :
        {
            func :: :get_symbol   = { return "tanh"  ; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func  : :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_tanh_s_create(); };
            func  : :apply        =
            {
                bmath_hf3_s_copy_size( r, a );
                if( a->v_size ) bmath_hf3_s_tanh( a, r );
                return true;
            };
        };

        stamp :dimof = aware :
        {
            func :: :get_symbol   = { return "dimof" ; };
            func :: :get_arity    = { return 1; };
            func :: :get_priority = { return 8; };
            func  : :apply        =
            {
                bmath_hf3_s_set_scalar_f3( r, a->d_size ? a->d_data[ a->d_size - 1 ] : 1 );
                return true;
            };
        };

        //TODO stamp rand - randomizer
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// binary operator (arity 2)
    group :ar2 = retrievable
    {
        feature 'a' bmath_hf3_vm_op* create_vm_op( const, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r ) = { return NULL; };

        feature 'a' bl_t apply( const, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r );

        stamp :bmul = aware :
        {
            func :: :get_symbol   = { return "<*>"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :apply =
            {
                if( !bmath_hf3_s_set_d_bmul( a, b, r ) ) return false;
                if( a->v_data && b->v_data )
                {
                    bmath_hf3_s_fit_v_size( r );
                    bmath_hf3_s_bmul( a, b, r );
                }
                return true;
            };

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_bmul_s_create(); };
        };

        stamp :bmul_htp = aware :
        {
            func :: :get_symbol   = { return "<*t>"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };

            func :  :apply =
            {
                if( !bmath_hf3_s_set_d_bmul_htp( a, b, r ) ) return false;
                if( a->v_data && b->v_data )
                {
                    bmath_hf3_s_fit_v_size( r );
                    bmath_hf3_s_bmul_htp( a, b, r );
                }
                return true;
            };

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_bmul_htp_s_create(); };
        };

        stamp :htp_bmul = aware :
        {
            func :: :get_symbol   = { return "<t*>"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :apply =
            {
                if( !bmath_hf3_s_set_d_htp_bmul( a, b, r ) ) return false;
                if( a->v_data && b->v_data )
                {
                    bmath_hf3_s_fit_v_size( r );
                    bmath_hf3_s_htp_bmul( a, b, r );
                }
                return true;
            };

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_htp_bmul_s_create(); };
        };

        stamp :htp_bmul_htp = aware :
        {
            func :: :get_symbol   = { return "<t*t>"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :apply =
            {
                if( !bmath_hf3_s_set_d_htp_bmul_htp( a, b, r ) ) return false;
                if( a->v_data && b->v_data )
                {
                    bmath_hf3_s_fit_v_size( r );
                    bmath_hf3_s_htp_bmul_htp( a, b, r );
                }
                return true;
            };

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_htp_bmul_htp_s_create(); };
        };

        stamp :mul = aware :
        {
            func :: :get_symbol   = { return "*"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 9; };
            func :  :apply =
            {
                if( a->d_size == 0 )
                {
                    bmath_hf3_s_copy_d_data( r, b );
                    if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
                    {
                        bmath_hf3_s_fit_v_size( r );
                        bmath_hf3_s_mul_scl( b, a->v_data, r );
                    }
                }
                else if( b->d_size == 0 )
                {
                    bmath_hf3_s_copy_d_data( r, a );
                    if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
                    {
                        bmath_hf3_s_fit_v_size( r );
                        bmath_hf3_s_mul_scl( a, b->v_data, r );
                    }
                }
                else
                {
                    if( a->d_size != b->d_size ) return false;
                    if( bmath_hf3_s_d_product( a ) != bmath_hf3_s_d_product( b ) ) return false;
                    bmath_hf3_s_copy_d_data( r, a );
                    if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
                    {
                        bmath_hf3_s_fit_v_size( r );
                        bmath_hf3_s_hmul( a, b, r );
                    }
                }
                return true;
            };

            func :  :create_vm_op;
        };

        stamp :plus = aware :
        {
            func :: :get_symbol   = { return "+"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 8; };
            func :  :apply =
            {
                if( a->d_size != b->d_size ) return false;
                if( bmath_hf3_s_d_product( a ) != bmath_hf3_s_d_product( b ) ) return false;
                bmath_hf3_s_copy_d_data( r, a );
                if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
                {
                    bmath_hf3_s_fit_v_size( r );
                    bmath_hf3_s_add( a, b, r );
                }
                return true;
            };

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_add_s_create(); };
        };

        stamp :minus = aware :
        {
            func :: :get_symbol   = { return "-"; };
            func :: :get_arity    = { return 2; };
            func :: :get_priority = { return 8; };
            func :  :apply =
            {
                if( a->d_size != b->d_size ) return false;
                if( bmath_hf3_s_d_product( a ) != bmath_hf3_s_d_product( b ) ) return false;
                bmath_hf3_s_copy_d_data( r, a );
                if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
                {
                    bmath_hf3_s_fit_v_size( r );
                    bmath_hf3_s_sub( a, b, r );
                }
                return true;
            };

            func :  :create_vm_op = { return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_sub_s_create(); };
        };

        stamp :index = aware : // r-value is (scalar) index
        {
            func :: :get_arity    = { return  2; };
            func :: :get_priority = { return 20; };
            func :  :apply = // r->v_data will be weak
            {
                if( b->v_size != 1 ) return false;
                sz_t index = b->v_data[ 0 ];
                if( a->d_size == 0 ) return false;
                if( index < 0 || index >= a->d_data[ a->d_size - 1 ] ) return false;
                bmath_hf3_s_clear( r );
                bmath_hf3_s_set_d_data( r, a->d_data, a->d_size -1 );
                if( a->v_data )
                {
                    r->v_size = bmath_hf3_s_d_product( r );
                    r->v_data = a->v_data + index * r->v_size;
                    r->v_space = 0;
                }
                return true;
            };
        };

        stamp :inc_order = aware : // l-value is (scalar) increment
        {
            func :: :get_arity    = { return  2; };
            func :: :get_priority = { return 20; };
            func :  :apply =
            {
                if( a->v_size != 1 ) return false;
                sz_t dim = b->v_data[ 0 ];
                if( dim <= 0 ) return false;
                bmath_hf3_s_copy( r, b );
                bmath_hf3_s_inc_order( r, dim );
                return true;
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
    signature ::get_sz  count_open;

    stamp :links = aware bcore_array
    {
        :link_s => [];

        func : :name_exists =
        {
            for( sz_t i = 0; i < o->size; i++ ) if( o->data[ i ]->name == name ) return true;
            return false;
        };

        func : :get_link_by_name =
        {
            for( sz_t i = 0; i < o->size; i++ ) if( o->data[ i ]->name == name ) return o->data[ i ];
            return NULL;
        };

        func : :get_link_by_open =
        {
            for( sz_t i = 0; i < o->size; i++ ) if( o->data[ i ]->up == NULL ) return o->data[ i ];
            return NULL;
        };

        func : :count_open =
        {
            sz_t count = 0;
            for( sz_t i = 0; i < o->size; i++ ) count += ( o->data[ i ]->up == NULL );
            return count;
        };
    };

    stamp :body = aware bcore_array
    {
        aware : => [];

        func : :name_exists =
        {
            for( sz_t i = 0; i < o->size; i++ ) if( :a_get_name( o->data[ i ] ) == name ) return true;
            return false;
        };

        func : :get_sem_by_name =
        {
            for( sz_t i = 0; i < o->size; i++ ) if( :a_get_name( o->data[ i ] ) == name ) return o->data[ i ];
            return NULL;
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // cell

    signature :link_s* get_enc_by_name(  mutable, tp_t name );
    signature :link_s* get_enc_by_open(  mutable );
    signature :link_s* get_exc_by_name(  mutable, tp_t name );
    signature :cell_s* get_cell_by_name( mutable, tp_t name );

    stamp :cell = aware :
    {
                tp_t       name;
               :links_s    encs; // entry channels
               :links_s    excs; // exit channels
               :body_s  => body;
        aware ::op      -> op;   // cell holds either operator (cell is a node) or body (cell is a graph) or neither (cell is a wrapper)

        private :cell_s* parent; // lexical parent

        hidden bcore_source_point_s source_point;

        func : :get_name = :get_name_;
        func : :get_arity =       { return             :links_s_count_open(       &o->encs       ); };
        func : :get_enc_by_name = { return ( :link_s* ):links_s_get_link_by_name( &o->encs, name ); };
        func : :get_enc_by_open = { return ( :link_s* ):links_s_get_link_by_open( &o->encs       ); };
        func : :get_exc_by_name = { return ( :link_s* ):links_s_get_link_by_name( &o->excs, name ); };
        func : :get_priority    = { return ( o->op ) ? ::op_a_get_priority( o->op ) : 10 /* default cell priority */; };

        func : :get_cell_by_name =
        {
            ::sem* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
            if( sem && *(aware_t*)sem == TYPEOF_:cell_s ) return ( :cell_s* )sem;
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
    signature :node_s* cell_enter( mutable, ::sem_cell_s* cell );
    signature :node_s* cell_exit(  mutable, ::sem_cell_s* cell ); // returns NULL when exit fails
    stamp :node = aware bcore_array
    {
        sz_t id = -1;
        private ::sem_cell_s -> cell;
        private :node_s -> parent;
        :node_s => [];

        // returns the node which is currently being entered (the newly referenced node); id needs to be set
        func : :cell_enter =
        {
            for( sz_t i = 0; i < o->size; i++ ) if( o->data[ i ]->cell == cell ) return o->data[ i ];
            :node_s* node = :node_s_push_d( o, :node_s_create() );
            node->cell = cell;
            node->parent = o;
            return node;
        };

        // returns the node which is currently being exited (the newly referenced node would be its parent)
        func : :cell_exit =
        {
            :node_s* node = o;
            while( node && node->cell != cell ) node = o->parent;
            return node;
        };

    };

    stamp :tree = aware :
    {
        sz_t id_base = 0; // (incremented when adding nodes)
        :node_s => root;
        private :node_s -> node; // current node

        func : :cell_enter =
        {
            if( !o->root )
            {
                o->root = :node_s_create();
                o->root->id = o->id_base++;
                o->root->cell = cell;
                o->node = o->root;
            }
            else
            {
                o->node = :node_s_cell_enter( o->node ? o->node : o->root, cell );
                if( o->node->id < 0 ) o->node->id = o->id_base++;
            }
            return o->node;
        };

        func : :cell_exit =
        {
            if( !o->node ) return NULL;
            :node_s* node = :node_s_cell_exit( o->node, cell );
            if( node ) o->node = node->parent;
            return node;
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// network group
group :net =
{
    stamp :link = aware :
    {
        vd_t tg; // target is a node
    };

    stamp :links = aware bcore_array
    {
        :link_s => [];
    };

    stamp :node = aware :
    {
        :links_s upls; // uplinks
        :links_s dnls; // downlinks
        aware ::op -> op;
    };

    stamp :nodes = aware bcore_array
    {
        :node_s => [];
    };

    stamp :frame = aware :
    {
        ::ctr_tree_s tree;
        :nodes_s nodes;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// global context
stamp :context = aware :
{
    bcore_hmap_name_s hmap_name;
    bcore_arr_st_s    arr_symbol_op2;
    :sem_cell_s       cell; // frame of a cell structure
};

#endif // PLANT_SECTION
#endif // TYPEOF_bhgp

/**********************************************************************************************************************/

void bhgp_test( void );

/**********************************************************************************************************************/

vd_t bhgp_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BHGP_H
