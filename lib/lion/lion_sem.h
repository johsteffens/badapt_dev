/** Author and Copyright 2020 Johannes Bernhard Steffens
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

#ifndef LION_SEM_H
#define LION_SEM_H

/**********************************************************************************************************************/

/// Syntax & Semantic

/**********************************************************************************************************************/

/** Syntax
    MLP

    cell layer( y => hidden_nodes, a )
    {
        w = adaptive : random : ( [ hidden_nodes ][ dimof( a ) ]# );
        b = adaptive : ( [ hidden_nodes ]0 );
        y = b + w ** a;
    };

    cell mlp( y => a )
    {
        l1 = layer( 10, a );
        l2 = layer( 20, relu( a ) );
        l3 = layer(  1, relu( a ) );
        y = tanh( l3.y );
    };

    ========================================
    LSTM

    cell layer( co, ho => dim_h, x, ci, hi )
    {
        // adaptive holors
        w_fx = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_fh = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_ix = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_ih = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_ox = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_oh = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_qx = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_qh = adaptive : random( [ dim_h ][ dimof( x ) ]# );

        b_f = adaptive( [ dim_h ]0 );
        b_i = adaptive( [ dim_h ]0 );
        b_o = adaptive( [ dim_h ]0 );
        b_q = adaptive( [ dim_h ]0 );

        v_f = lgst( ( w_fx ** x ) + ( w_fh ** hi ) + b_f );
        v_i = lgst( ( w_ix ** x ) + ( w_ih ** hi ) + b_i );
        v_o = lgst( ( w_ox ** x ) + ( w_oh ** hi ) + b_o );
        v_q = tanh( ( w_qx ** x ) + ( w_qh ** hi ) + b_q );

        co  = ( v_f * ci ) + ( v_i * v_q );
        v_d = tanh( co );
        ho  = ( v_o * v_d );
    };

    cell lstm( y => dim_h, x )
    {
        adaptive w_r = random( [ dim_h ][ dimof( x ) ]# );
        adaptive b_r = [ dim_h ]#;

        recurrent c = [ dim_h ]0;
        recurrent h = [ dim_h ]0;

        l1 = layer( dim_h, x, ci = c, hi = h );

        h = l1.ho;
        c = l1.co;

        y = tanh( w_r * h + b_r );
    }

    g_out = lstm( dim_h = 200, x = g_in ).y;

    - parse into cell
    - cell: tree of cell
    - cell: inputs, outputs, body
    - definition: stand-alone node with identifier
    - operation: cell embedded in a cell
    - once a cell is complete, data types can be finalized

TODO:
   - (done) allow explicit output channel selection only on cells with no free input channels
   - virtual machine: overhaul differentiating between micro- and macrocode
   -                  add macro operations operating on the frame
   -                  add macro operations controlling program flow
   - recurrent: implement unrolled inference and bp_grad
   - allow elementwise operators mix with scalars (like mul)
   - look for generally accepted offline problems for neural networks
   - parameterize adaptive (e.g. adaptive( min, max, additional cost ))
   - index operator should be a cast-operator
   - add a cost operator or cost expression to generate specific costs like weight energy (producing weight decay)
*/

/**
 *  Symbolic language to describe a graph of operators on holors.
 *
 *  Semantic Cell Concept:
 *  A semantic graph communicates with the objects outside its body through input an output channels.
 *  All links of a graph 'x' to outside objects the node must pass though an input channel of 'x'.
 *  Inside objects may not be referenced directly by outside objects.
 *  A graph adhering to this concept is called 'cell'
 *  A construction of a new graph must conclude with converting it to a cell.
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
 *  Symbol  Notation Priority  Type
 *   +      Infix    8     (elementwise) addition
 *   -      Infix    8     (elementwise) subtraction
 *   *      Infix    9     (elementwise) multiplication (hadamard product); multiplication of holor with scalar
 *  **,     Infix    9     holor-product for holors up to order 2; transposition state is considered
 *  ***     Infix    9     convolution?
 *
 *  Unary operators
 *   -          8     negates holor
 *  ^t,        10     toggles transposition state (represents a reinterpret cast) (priority must be above multiplication)
 *
 *  Possible name ?
 *     haptive (synonym to haptic) (no trademark (!) )
 *     holocell
 *     holorcell  (unused)
 *     holorframe (unused, term does not yet exist)
 *     holograph
 *     holorgraph
 *     holornova  (unused)
 *     helix   (mathematics, biology, earring, IT corporation)
 *     haptor  (biology: flatworm organ)
 *     hoptinet
 *     hoptivnet (unused)
 *     haptivnet (unused)
 *     adahonet  (unused)
 *     haptivscript (unused)
 *     haptivdown   // wordplay on markdown
 *
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

/**********************************************************************************************************************/

#include "bmath_std.h"
#include "lion_nop.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_sem

BCORE_FORWARD_OBJECT( lion_sem_context_s );

/// returns global context
lion_sem_context_s* lion_sem_get_context( void );

PLANT_GROUP( lion_sem, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// global context
stamp :context = aware bcore_inst
{
    bcore_hmap_name_s hmap_name;
    bcore_arr_st_s    arr_symbol_op2;
    :cell_s        => cell; // frame of a cell structure
    bcore_arr_tp_s    control_types; // types reserved for control and not allowed for identifiers
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// language control types
name cell;
name if;
name then;
name else;

signature   sz_t get_arity( const );
signature   sz_t get_priority( const );
feature 'a' tp_t get_name( const ) = { return 0; };
body             get_name_ = { return o->name; };

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

signature bl_t     name_exists(       const,   tp_t name );
signature :*       get_sem_by_name(   mutable, tp_t name );
signature :link_s* get_link_by_name(  mutable, tp_t name );
signature :link_s* get_link_by_open(  mutable );
signature :link_s* get_link_by_up(    mutable, :link_s* up );
signature :link_s* get_link_by_dn(    mutable, :link_s* dn );
signature sz_t     get_index_by_link( mutable, :link_s* link ); // returns -1 if not found
signature sz_t     count_open( const );

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
    aware lion_nop  -> nop;   // cell holds either operator (cell is a node) or body (cell is a graph) or neither (cell is a wrapper)
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

    // search for a cell descends the tree
    func : :get_cell_by_name =
    {
        :* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
        if( sem && sem->_ == TYPEOF_:cell_s ) return ( :cell_s* )sem;
        if( o->parent ) return :cell_s_get_cell_by_name( o->parent, name );
        return NULL;
    };

    // search for a link only looks up the body of this cell
    func : :get_link_by_name =
    {
        :* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
        if( sem && sem->_ == TYPEOF_:link_s ) return ( :link_s* )sem;
        return NULL;
    };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// evaluation stack indicators
stamp :stack_flag = aware : {};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sc_t lion_nameof(   tp_t name );
sc_t lion_ifnameof( tp_t name );
tp_t lion_entypeof( sc_t name );
tp_t lion_entypeof_fv( sc_t format, va_list args );
tp_t lion_entypeof_fa( sc_t format, ... );

lion_sem_link_s* lion_sem_link_s_trace_to_cell_membrane( lion_sem_link_s* o );

#endif // TYPEOF_lion_sem

/**********************************************************************************************************************/

vd_t lion_sem_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_SEM_H
