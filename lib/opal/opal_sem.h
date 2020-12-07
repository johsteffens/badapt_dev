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

#ifndef OPAL_SEM_H
#define OPAL_SEM_H

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
 *  More details: See opal_design.txt
 */

/**********************************************************************************************************************/

#include "bmath_std.h"
#include "opal_nop.h"
#include "opal.xo.h"

/**********************************************************************************************************************/

BCORE_FORWARD_OBJECT( opal_sem_context_s );

/// returns global context
opal_sem_context_s* opal_sem_get_context( void );

XOILA_DEFINE_GROUP( opal_sem, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// semantic context
group :context = opal_context
{
    signature void setup( mutable, opal_sem_cell_s* frame );
    signature opal_sem_cell_s* setup_cell( mutable, opal_sem_cell_s* cell ); // returns cell
    signature opal_sem_cell_s* create_cell( mutable ); // creates and setups cell

    stamp :s = aware :
    {
        opal_nop_context_s nop_context;
        func opal_context .get_prsg = { return o->nop_context.get_prsg(); };

        bcore_hmap_name_s hmap_name;
        bcore_arr_st_s    arr_symbol_op2;

        bcore_hmap_tp_s control_types; // types reserved for control
        bcore_hmap_tp_s reserved_names; // reserved keywords (not allowed for variables)

        func :.setup;

        func opal_context .nameof   = { return o.hmap_name.get_sc( name ); };
        func opal_context .ifnameof = { sc_t sc = o.nameof( name ); return sc ? sc : ""; };
        func opal_context .typeof   = { return btypeof( name ); };
        func opal_context .entypeof = { return o.hmap_name.set_sc( name ); };

        func :.setup_cell =
        {
            cell.context =< bcore_fork( o );
            return cell;
        };

        func :.create_cell =
        {
            return o.setup_cell( ::cell_s! );
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Semantic Identifier.
 *  Identifies objects in a semantic tree by storing the tree elements
 *  from root to leaf in form of hashed names in a tp_t-array.
 */
group :id = :
{
    signature void clear(       mutable );
    signature void set(         mutable, tp_t tp );
    signature void push_child(  mutable, tp_t tp );
    signature void push_parent( mutable, tp_t tp );
    signature void to_string(   const, const opal_context* context, st_s* s );

    stamp :s = aware :
    {
        bcore_arr_tp_s arr_tp;
        func :.clear       = { o.arr_tp.clear(); };
        func :.set         = { o.arr_tp.clear(); o.arr_tp.push( tp ); };
        func :.push_child  = { o.arr_tp.push( tp ); };
        func :.push_parent = { o.arr_tp.push_left( tp ); };
        func :.to_string   =
        {
            s.clear();
            foreach( tp_t t in o.arr_tp )
            {
                if( __i > 0 ) s.push_char( '.' );
                s.push_sc( context.ifnameof( t ) );
            }
        };
    };

    /// for use in other objects
    signature void get_sem_id( const, :s* sem_id );
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// language control types
name cell;

signature   sz_t get_arity( const );
signature   sz_t get_priority( const );
feature tp_t get_name( const ) = { return 0; };
feature bl_t is_visible( const ) = { return true; }; // invisible objects are not searchable via get_by_name functions
feature void set_name_visible(   mutable, tp_t name );
feature void set_name_invisible( mutable, tp_t name );

body             get_name_ = { return o->name; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// bidirectional link
stamp :link_s = aware :
{
    tp_t name;
    bl_t protected = false; // a protected link may not be used (used for cyclic syntax error detection)
    bl_t visible   = true;

    private :link_s -> up;   // up link
    private :link_s -> dn;   // down link
    private  vd_t cell; // cell owning the link (only if link is part of membrane)
    bl_t     exit; // true: link is of cell's exit membrane. false: entry membrane
    func :. get_name = :get_name_;
    func :.set_name_visible   = { o->name = name; o->visible = true; };
    func :.set_name_invisible = { o->name = name; o->visible = false; };
    func :.is_visible = { return o->visible; };
};

signature bl_t     name_exists(       const,   tp_t name );
signature :*       get_sem_by_name(   mutable, tp_t name );
signature :link_s* get_link_by_name(  mutable, tp_t name );
signature :link_s* get_link_by_open(  mutable );
signature :link_s* get_link_by_up(    mutable, :link_s* up );
signature :link_s* get_link_by_dn(    mutable, :link_s* dn );
signature sz_t     get_index_by_link( mutable, :link_s* link ); // returns -1 if not found
signature sz_t     count_open( const );

stamp :links_s = aware bcore_array
{
    :link_s => [];

    func :.get_link_by_name =
    {
        foreach( $* e in o ) if( e.name == name ) return e;
        return NULL;
    };

    func :.name_exists =
    {
        foreach( const $* e in o ) if( e.name == name ) return true;
        return false;
    };

    func :.get_link_by_up =
    {
        foreach( $* e in o ) if( e.up == up ) return e;
        return NULL;
    };

    func :.get_link_by_dn =
    {
        foreach( $* e in o ) if( e.dn == dn ) return e;
        return NULL;
    };

    func :.get_index_by_link =
    {
        foreach( $* e in o ) if( e == link ) return __i;
        return -1;
    };

    func :.count_open =
    {
        sz_t count = 0;
        foreach( $* e in o ) count += ( e.up == NULL );
        return count;
    };
};

stamp :body_s = aware bcore_array
{
    aware : => [];

    func :.name_exists =
    {
        foreach( $* e in o ) if( e.get_name() == name ) return true;
        return false;
    };

    func :.get_sem_by_name =
    {
        foreach( $* e in o )
        {
            if( e.get_name() == name )
            {
                if( e.is_visible() ) return e;
            }
        }
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

signature bl_t is_wrapper( const );

stamp :cell_s = aware :
{
             tp_t         name;
             bl_t visible = true;  // an invisible cell cannot be retrieved in get_cell_by_name
            :links_s      encs;    // entry channels
            :links_s      excs;    // exit channels
            :body_s    => body;
    private :cell_s*      parent;  // lexical parent
    hidden  :context_s -> context; // context for given cell structure
             sz_t         priority = 10;

    aware    opal_nop  -> nop;     // cell holds either operator (cell is a node) or body (cell is a graph) or neither (cell is a wrapper)
    hidden bcore_source_point_s source_point;

    // if cell is a wrapper, wrapped_cell is the cell being wrapped
    private :cell_s    -> wrapped_cell;

    func :.get_name = :get_name_;

    func :.set_name_visible   = { o->name = name; o->visible = true; };
    func :.set_name_invisible = { o->name = name; o->visible = false; };
    func :.is_visible      = { return o->visible; };
    func :.get_arity       = { return o.encs.count_open(); };
    func :.get_enc_by_name = { return o.encs.get_link_by_name( name ); };
    func :.get_exc_by_name = { return o.excs.get_link_by_name( name ); };
    func :.get_enc_by_open = { return o.encs.get_link_by_up( NULL ); };
    func :.get_enc_by_dn   = { return o.encs.get_link_by_dn( dn   ); };
    func :.get_priority    = { return o->priority; };
    func :.is_wrapper      = { return o->wrapped_cell != NULL && o->nop == NULL && o->body == NULL; };

    // search for a cell descends the tree
    func :.get_cell_by_name =
    {
        :* sem = o.body ? o.body.get_sem_by_name( name ) : NULL;
        if( sem && sem._ == TYPEOF_:cell_s ) return sem.cast( :cell_s* );
        if( o.parent ) return o.parent.get_cell_by_name( name );
        return NULL;
    };

    // search for a link only looks up the body of this cell
    func :.get_link_by_name =
    {
        :* sem = o.body ? o.body.get_sem_by_name( name ) : NULL;
        if( sem && sem._ == TYPEOF_:link_s ) return sem.cast( :link_s* );
        return NULL;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// evaluation stack indicators
stamp :stack_flag_s = aware : {};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// semantic builder
group :builder = :
{
    signature er_t build_from_source( mutable, opal_sem_cell_s* cell, bcore_source* source );

    stamp :s = aware :
    {
        opal_sem_context_s => context;
        opal_sem_cell_s => cell_context;
        opal_sem_cell_s => cell_frame;

        func :.build_from_source;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Semantic tree
 *  The semantic tree is an intermediate and temporary representation
 *  of a partial semantic cell structure expressed as physical tree.
 *  It is used in functions net ... from_sem ... (in opal_net.c).
 *  This structure is necessary because the semantic cell structure
 *  only presents a logical tree. E.g. existing cells can be reused at
 *  different semantic places where the semantic parent is from the lexical
 *  parent.
 *
 *  In order to proper navigate inside the semantic tree, we build this
 *  physical tree during network conversion.
 *  This method is more economic than representing the cell structure as
 *  physical tree.
 *
 *  This solution permits describing the logical tree semantically in form
 *  of recursions. It also allows wrapper cells.
 */
group :tree = :
{
    signature void push_parents_to_sem_id( const, ::id_s* sem_id );
    signature void get_sem_id(             const, ::id_s* sem_id );

    stamp :node_s = aware bcore_array
    {
        sz_t id = -1;
        private opal_sem_cell_s -> cell;
        private :node_s -> parent; // semantic parent of cell (note that cell.parent is a lexical parent)
        :node_s => [];

        func :.push_parents_to_sem_id =
        {
            sem_id.push_parent( o.cell ? o.cell.name : 0 );
            if( o.parent ) o.parent.push_parents_to_sem_id( sem_id );
        };

        func :.get_sem_id =
        {
            sem_id.set( o.cell ? o.cell.name : 0 );
            if( o.parent ) o.parent.push_parents_to_sem_id( sem_id );
        };
    };

    signature er_t enter( mutable, ::cell_s* cell,                        :node_s* node_in, :node_s** node_out );
    signature er_t exit ( mutable, ::cell_s* cell, bl_t test_for_wrapper, :node_s* node_in, :node_s** node_out );

    stamp :s = aware :
    {
        sz_t id_base = 0; // (incremented when adding nodes)
        :node_s => root;

        func :.enter;
        func :.exit;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sc_t opal_sem_cell_s_nameof(      const opal_sem_cell_s* o, tp_t name );
sc_t opal_sem_cell_s_ifnameof(    const opal_sem_cell_s* o, tp_t name );
tp_t opal_sem_cell_s_entypeof(    const opal_sem_cell_s* o, sc_t name );
tp_t opal_sem_cell_s_entypeof_fv( const opal_sem_cell_s* o, sc_t format, va_list args );
tp_t opal_sem_cell_s_entypeof_fa( const opal_sem_cell_s* o, sc_t format, ... );

opal_sem_link_s* opal_sem_link_s_trace_to_cell_membrane( opal_sem_link_s* o );

void opal_sem_cell_s_parse( opal_sem_cell_s* o, bcore_source* source );
void opal_sem_cell_s_parse_signature( opal_sem_cell_s* o, bcore_source* source );
void opal_sem_cell_s_parse_body( opal_sem_cell_s* o, bcore_source* source );

bcore_source_point_s* opal_sem_tree_node_s_get_nearest_source_point( opal_sem_tree_node_s* o );

/**********************************************************************************************************************/

#endif // OPAL_SEM_H
