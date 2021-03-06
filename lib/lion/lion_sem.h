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
 *   :      Infix      6     Constructive Concatenation
 *  ::      Infix      8     Conservative Concatenation
 *  <:      Infix            Cell Catenation
 *   [      Infix     21     order-increment bin operator (l-value: dim). (Yielding) Example: 2[# = (#:#), 2[2[# = (#:#):(#:#)
 *   ]      Infix     20     order-decrement bin operator (r-value: idx). Example: (1:2:3)]1 = 2
 *   +      Infix      8     (ECI) addition
 *   -      Infix      8     (ECI) subtraction
 *   *      Infix     10     (ECI) multiplication
 *   /      Infix     10     (ECI) division
 *   ^      Infix     12     (ECI) power
 *  **,     Infix     10     holor-product for holors up to order 2; transposition state is considered
 *  *~      Infix     10     convolution?
 *
 *  Unary operators
 *  -     Prefix       8     negates holor
 *  ~     Postfix     12     toggles transposition state (represents a reinterpret cast) (priority must be above multiplication)
 *
 *  Holors
 *    #   Vacant scalar
 *    7   Determined Scalar
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
 *
 *  More details: See lion_design.txt
 */

/**********************************************************************************************************************/

#include "bmath_std.h"
#include "lion_nop.h"
#include "lion.xo.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_sem

BCORE_FORWARD_OBJECT( lion_sem_context_s );

/// returns global context
lion_sem_context_s* lion_sem_get_context( void );

XOILA_DEFINE_GROUP( lion_sem, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ---------------------------------------------------------------------------------------------------------------------

// global context
stamp :context_s = aware bcore_inst
{
    bcore_hmap_name_s hmap_name;
    bcore_arr_st_s    arr_symbol_op2;
    :cell_s        => cell; // frame of a cell structure

    bcore_hmap_tp_s control_types; // types reserved for control
    bcore_hmap_tp_s reserved_names; // reserved keywords (not allowed for variables)
};

// ---------------------------------------------------------------------------------------------------------------------

// language control types
name cell;

signature   sz_t get_arity( c @* o );
signature   sz_t get_priority( c @* o );
feature tp_t get_name( c @* o ) = { return 0; };
feature bl_t is_visible( c @* o ) = { return true; }; // an object can be made syntactically invisible
body             get_name_ = { return o->name; };

// ---------------------------------------------------------------------------------------------------------------------

// bidirectional link
stamp :link_s = aware :
{
    tp_t name;
    bl_t visible = true;
    private :link_s -> up;   // up link
    private :link_s -> dn;   // down link
    private  vd_t cell; // cell owning the link (only if link is part of membrane)
    bl_t     exit; // true: link is of cell's exit membrane. false: entry membrane
    func : . get_name = :get_name_;
    func : . is_visible = { return o->visible; };
};

signature bl_t name_exists(       c @* o, tp_t name );
signature m :* get_sem_by_name(   m @* o, tp_t name );
signature m :link_s* get_link_by_name( m @* o, tp_t name );
signature m :link_s* get_link_by_open( m @* o );
signature m :link_s* get_link_by_up(   m @* o, m :link_s* up );
signature m :link_s* get_link_by_dn(   m @* o, m :link_s* dn );
signature sz_t get_index_by_link( m @* o, m :link_s* link ); // returns -1 if not found
signature sz_t count_open( c @* o );

stamp :links_s = aware x_array
{
    :link_s => [];

    wrap x_array.set_size;
    wrap x_array.push_d;

    func : .get_link_by_name =
    {
        BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return o->data[ i ];
        return NULL;
    };

    func : .name_exists =
    {
        BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return true;
        return false;
    };

    func : .get_link_by_up =
    {
        BFOR_EACH( i, o ) if( o->data[ i ]->up == up ) return o->data[ i ];
        return NULL;
    };

    func : .get_link_by_dn =
    {
        BFOR_EACH( i, o ) if( o->data[ i ]->dn == dn ) return o->data[ i ];
        return NULL;
    };

    func : .get_index_by_link =
    {
        BFOR_EACH( i, o ) if( o->data[ i ] == link ) return i;
        return -1;
    };

    func : .count_open =
    {
        sz_t count = 0;
        BFOR_EACH( i, o ) count += ( o->data[ i ]->up == NULL );
        return count;
    };
};

stamp :body_s = aware x_array
{
    aware : => [];
    wrap x_array.push_t;

    func : .name_exists =
    {
        BFOR_EACH( i, o ) if( :a_get_name( o->data[ i ] ) == name ) return true;
        return false;
    };

    func : .get_sem_by_name =
    {
        BFOR_EACH( i, o )
        {
            if( :a_get_name( o->data[ i ] ) == name ) return o->data[ i ];
        }
        return NULL;
    };
};

// ---------------------------------------------------------------------------------------------------------------------
// cell

signature m :link_s* get_enc_by_name(  m @* o, tp_t name );
signature m :link_s* get_enc_by_open(  m @* o );
signature m :link_s* get_enc_by_dn(    m @* o, m :link_s* dn );
signature m :link_s* get_exc_by_name(  m @* o, tp_t name );
signature m :cell_s* get_cell_by_name( m @* o, tp_t name );

signature bl_t is_wrapper( c @* o );

stamp :cell_s = aware :
{
            tp_t       name;
           :links_s    encs; // entry channels
           :links_s    excs; // exit channels
           :body_s  => body;
    aware lion_nop  -> nop;          // cell holds either operator (cell is a node) or body (cell is a graph) or neither (cell is a wrapper)
    private :cell_s -> wrapped_cell; // if cell is a wrapper, wrapped_cell is the cell being wrapped

            sz_t       priority = 10;

    private :cell_s* parent; // lexical parent

    hidden bcore_source_point_s source_point;

    func : .get_name = :get_name_;
    func : .get_arity       = { return :links_s_count_open(       &o->encs       ); };
    func : .get_enc_by_name = { return :links_s_get_link_by_name( &o->encs, name ); };
    func : .get_exc_by_name = { return :links_s_get_link_by_name( &o->excs, name ); };
    func : .get_enc_by_open = { return :links_s_get_link_by_up(   &o->encs, NULL ); };
    func : .get_enc_by_dn   = { return :links_s_get_link_by_dn(   &o->encs, dn   ); };
    func : .get_priority    = { return o->priority; };
    func : .is_wrapper      = { return o->wrapped_cell != NULL && o->nop == NULL && o->body == NULL; };

    // search for a cell descends the tree
    func : .get_cell_by_name =
    {
        m :* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
        if( sem && sem->_ == TYPEOF_:cell_s ) return ( :cell_s* )sem;
        if( o->parent ) return :cell_s_get_cell_by_name( o->parent, name );
        return NULL;
    };

    // search for a link only looks up the body of this cell
    func : .get_link_by_name =
    {
        m :* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
        if( sem && sem->_ == TYPEOF_:link_s ) return ( :link_s* )sem;
        return NULL;
    };

};

// ---------------------------------------------------------------------------------------------------------------------

/// evaluation stack indicators
stamp :stack_flag_s = aware : {};

// ---------------------------------------------------------------------------------------------------------------------

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sc_t lion_nameof(   tp_t name );
sc_t lion_ifnameof( tp_t name );
tp_t lion_entypeof( sc_t name );
tp_t lion_entypeof_fv( sc_t format, va_list args );
tp_t lion_entypeof_fa( sc_t format, ... );

lion_sem_link_s* lion_sem_link_s_trace_to_cell_membrane( lion_sem_link_s* o );

void lion_sem_cell_s_parse( lion_sem_cell_s* o, bcore_source* source );
void lion_sem_cell_s_parse_signature( lion_sem_cell_s* o, bcore_source* source );
void lion_sem_cell_s_parse_body( lion_sem_cell_s* o, bcore_source* source );
lion_sem_cell_s* lion_sem_cell_s_create_frame( void );

#endif // TYPEOF_lion_sem

/**********************************************************************************************************************/

vd_t lion_sem_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_SEM_H
