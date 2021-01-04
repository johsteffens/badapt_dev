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

XOILA_DEFINE_GROUP( opal_sem, x_inst )
#ifdef XOILA_SECTION

// ---------------------------------------------------------------------------------------------------------------------

// semantic context
group :context = opal_context
{
    signature void setup( m @* o, m opal_sem_cell_s* frame );
    signature m opal_sem_cell_s* setup_cell( m @* o, m opal_sem_cell_s* cell ); // returns cell
    signature d opal_sem_cell_s* create_cell( m @* o ); // creates and setups cell

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

        func (tp_t entypeof_fv( m @* o, sc_t format, va_list args )) =
        {
            return o.entypeof( st_s_create_fv( format, args ).scope().sc );
        };

        func (tp_t entypeof_fa( m @* o, sc_t format, ... )) =
        {
            va_list args; va_start( args, format );
            tp_t tp = o.entypeof_fv( format, args );
            va_end( args );
            return tp;
        };

        func (tp_t parse_name( m @* o, m bcore_source* source )) =
        {
            m st_s* name = st_s!^;
            source.parse_fa( " #name", name );
            if( name.size == 0 ) source.parse_err_fa( "Identifier expected." );
            return o.entypeof( name.sc );
        };

        func (bl_t is_control_type(  c @* o, tp_t name )) = { return o.control_types.exists( name ); };
        func (bl_t is_reserved_name( c @* o, tp_t name )) = { return o.reserved_names.exists( name ); };

        func (tp_t parse_var_name( m @* o, m bcore_source* source )) =
        {
            tp_t name = o.parse_name( source );
            if( o.is_reserved_name( name ) )
            {
                source.parse_err_fa( "'#<sc_t>' is a reserved keyword. It may not be used as identifier at this point.", o.ifnameof( name ) );
            }
            return name;
        };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

group :stack =
{
    stamp :s = aware :
    {
        bcore_arr_vd_s arr;
        func (sz_t size( c @* o )) = { return o.arr.size; };
        func (m x_inst* push( m @* o, m x_inst* value )) = { o.arr.push( value ); return value; };
        func (m x_inst* pop(  m @* o )) = { return (x_inst*)o.arr.pop(); };
        func (m x_inst* pop_of_type(  m @* o, tp_t type, m bcore_source* source )) =
        {
            m x_inst* v = o.pop();
            if( v._ == type ) return v;
            source.parse_err_fa( "Type error: '#<sc_t>' present but '#<sc_t>' expected.", ifnameof( v._ ), ifnameof( type ) );
            return NULL;
        };

        func (m x_inst* pop_of_value( m @* o, m x_inst* value, m bcore_source* source )) =
        {
            m x_inst* v = o.pop();
            if( v == value ) return v;
            source.parse_err_fa( "Internal error: Stack holds invalid value." );
            return NULL;
        };

        func (bl_t is_of_type( m @* o, sz_t idx, tp_t type )) =
        {
            if( idx <= 0 || idx > o.arr.size ) return false;
            return *(aware_t*)o.arr.[ o.arr.size - idx ] == type;
        };

        func (bl_t is_of_value( m @* o, sz_t idx, m x_inst* value )) =
        {
            if( idx <= 0 || idx > o.arr.size ) return false;
            return ( o.arr.[ o.arr.size - idx ].cast( m x_inst* ) == value );
        };

        func (m ::link_s* pop_link( m @* o, m bcore_source* source )) = { return o.pop_of_type( TYPEOF_::link_s, source ).cast(m ::link_s*); };
        func (m ::cell_s* pop_cell( m @* o, m bcore_source* source )) = { return o.pop_of_type( TYPEOF_::cell_s, source ).cast(m ::cell_s*); };

        func (m ::link_s* pop_link_or_exit( m @* o, m bcore_source* source )) =
        {
            m x_inst* v = o.pop();
            if     ( v._ == TYPEOF_::link_s )
            {
                return v.cast(m ::link_s*);
            }
            else if( v._ == TYPEOF_::cell_s )
            {
                m ::cell_s* cell = v.cast(m ::cell_s*);
                if( cell.excs.size != 1 )
                {
                    source.parse_err_fa( "Cell has #<sz_t> exit channels. Require is 1.", cell.excs.size );
                }
                return cell.excs.[ 0 ];
            }
            else
            {
                source.parse_err_fa( "Incorrect object on stack '#<sc_t>.", ifnameof( v._ ) );
            }
            return NULL;
        };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/** Semantic Identifier.
 *  Identifies objects in a semantic tree by storing the tree elements
 *  from root to leaf in form of hashed names in a tp_t-array.
 */
group :id = :
{
    signature void clear(       m @* o );
    signature void set(         m @* o, tp_t tp );
    signature void push_child(  m @* o, tp_t tp );
    signature void push_parent( m @* o, tp_t tp );
    signature void to_string(   c @* o, c opal_context* context, m st_s* s );

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
    signature void get_sem_id( c @* o, m :s* sem_id );
};

// ---------------------------------------------------------------------------------------------------------------------

// language control types
name cell;

signature   sz_t get_arity( c @* o );
signature   sz_t get_priority( c @* o );
feature tp_t get_name( c @* o ) = { return 0; };
feature bl_t is_visible( c @* o ) = { return true; }; // invisible objects are not searchable via get_by_name functions
feature void set_name_visible(   m @* o, tp_t name );
feature void set_name_invisible( m @* o, tp_t name );

body             get_name_ = { return o->name; };

// ---------------------------------------------------------------------------------------------------------------------

// bidirectional link
stamp :link_s = aware :
{
    tp_t name;
    bl_t protected = false; // a protected link may not be used (used for cyclic syntax error detection)
    bl_t visible   = true;

    private :link_s -> up;   // up link
    private :link_s -> dn;   // down link
    private :cell_s* cell; // cell owning the link (only if link is part of membrane)
    bl_t     exit; // true: link is of cell's exit membrane. false: entry membrane
    func :. get_name = :get_name_;
    func :.set_name_visible   = { o->name = name; o->visible = true; };
    func :.set_name_invisible = { o->name = name; o->visible = false; };
    func :.is_visible = { return o->visible; };
};

signature bl_t       name_exists(       c @* o, tp_t name );
signature m :*       get_sem_by_name(   m @* o, tp_t name );
signature m :link_s* get_link_by_name(  m @* o, tp_t name );
signature m :link_s* get_link_by_open(  m @* o );
signature m :link_s* get_link_by_up(    m @* o, c :link_s* up );
signature m :link_s* get_link_by_dn(    m @* o, c :link_s* dn );
signature sz_t       get_index_by_link( m @* o, c :link_s* link ); // returns -1 if not found
signature sz_t       count_open( c @* o );

stamp :links_s = aware x_array
{
    :link_s => [];

    wrap x_array.set_size;
    wrap x_array.push_d;

    func :.get_link_by_name =
    {
        foreach( m $* e in o ) if( e.name == name ) return e;
        return NULL;
    };

    func :.name_exists =
    {
        foreach( const $* e in o ) if( e.name == name ) return true;
        return false;
    };

    func :.get_link_by_up =
    {
        foreach( m $* e in o ) if( e.up == up ) return e;
        return NULL;
    };

    func :.get_link_by_dn =
    {
        foreach( m $* e in o ) if( e.dn == dn ) return e;
        return NULL;
    };

    func :.get_index_by_link =
    {
        foreach( m $* e in o ) if( e == link ) return __i;
        return -1;
    };

    func :.count_open =
    {
        sz_t count = 0;
        foreach( m $* e in o ) count += ( e.up == NULL );
        return count;
    };
};

stamp :body_s = aware x_array
{
    aware : => [];

    wrap x_array.push_t;

    func :.name_exists =
    {
        foreach( m $* e in o ) if( e.get_name() == name ) return true;
        return false;
    };

    func :.get_sem_by_name =
    {
        foreach( m $* e in o )
        {
            if( e.get_name() == name )
            {
                if( e.is_visible() ) return e;
            }
        }
        return NULL;
    };
};

// ---------------------------------------------------------------------------------------------------------------------
// cell

signature m :link_s* get_enc_by_name(  m @* o, tp_t name );
signature m :link_s* get_enc_by_open(  m @* o );
signature m :link_s* get_enc_by_dn(    m @* o, c :link_s* dn );
signature m :link_s* get_exc_by_name(  m @* o, tp_t name );
signature m :cell_s* get_cell_by_name( m @* o, tp_t name );

signature bl_t is_wrapper( c @* o );

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
        m :* sem = o.body ? o.body.get_sem_by_name( name ) : NULL;
        if( sem && sem._ == TYPEOF_:cell_s ) return sem.cast( m :cell_s* );
        if( o.parent ) return o.parent.get_cell_by_name( name );
        return NULL;
    };

    // search for a link only looks up the body of this cell
    func :.get_link_by_name =
    {
        m :* sem = o.body ? o.body.get_sem_by_name( name ) : NULL;
        if( sem && sem._ == TYPEOF_:link_s ) return sem.cast( m :link_s* );
        return NULL;
    };

    // push semantic item to cell's body ...
    func (m :* push_sem( m @* o, tp_t type )) = { return o.body!.push_t( type ); };
    func (m :link_s* push_link( m @* o )) = { return o.push_sem( TYPEOF_:link_s ).cast( m :link_s* ); };
    func (m @* push_cell( m @* o )) =
    {
        m @* cell = o.push_sem( TYPEOF_@ ).cast( m @* );
        cell->parent = o;
        cell->context = o->context.fork();
        cell.set_name_invisible( o.entypeof_fa( "$#<sz_t>", o.body.size - 1 ) );
        return cell;
    };

    func (m @* push_cell_nop_d_invisible( m @* o, d opal_nop* nop )) = { m @* cell = o.push_cell_nop_d( nop ); cell.visible = false; return cell; };
    func (m @* set_source( m @* o, m bcore_source* source )) = { o.source_point.set( source ); return o; };
    func (m @* push_cell_nop_d_set_source( m @* o, d opal_nop* nop, m bcore_source* source )) = { return o.push_cell_nop_d( nop ).set_source( source ); };
    func (m @* push_cell_nop_d(                      m @* o, d opal_nop* nop ));
    func (m @* push_cell_nop_d_invisible_set_source( m @* o, d opal_nop* nop, m bcore_source* source )) = { return o.push_cell_nop_d_invisible( nop ).set_source( source ); };
    func (m @* push_wrap_cell_hard( m @* o, m @* src )) = { return o.push_cell().wrap_cell_hard( src ); };
    func (m @* push_wrap_cell_soft( m @* o, m @* src )) = { return o.push_cell().wrap_cell_soft( src ); };
    func (m @* push_rewrap_cell_soft(     m @* o, m @* src )) = { return o.push_cell().rewrap_cell_soft( src ); };
    func (m @* push_wrap_cell_set_source( m @* o, m @* src, m bcore_source* source )) = { return o.push_wrap_cell_soft( src ).set_source( source ); };

    func (void create_args_out( m @* o, m bcore_source* source ));
    func (void create_args_in(  m @* o, m :cell_s* frame, m bcore_source* source ));
    func (void wrap_cell(       m @* o, m :cell_s* cell ));
    func (void             parse(               m @* o,                          m bcore_source* source ));
    func (void             parse_body(          m @* o,                          m bcore_source* source ));
    func (m opal_sem*        evaluate_sem(        m @* o,                          m bcore_source* source ));
    func (m opal_sem*        evaluate_sem_stack(  m @* o, m bcore_arr_vd_s* stack, m bcore_source* source ));
    func (m opal_sem_cell_s* evaluate_cell(       m @* o,                          m bcore_source* source ));
    func (m opal_sem_cell_s* evaluate_cell_stack( m @* o, m bcore_arr_vd_s* stack, m bcore_source* source ));
    func (m opal_sem_link_s* evaluate_link(       m @* o,                          m bcore_source* source ));
    func (m opal_sem_link_s* evaluate_link_stack( m @* o, m bcore_arr_vd_s* stack, m bcore_source* source ));
    func (void             set_channels(        m @* o, sz_t excs, sz_t encs ));

    /// Context wrappers
    func (sc_t nameof(   c @* o, tp_t name )) = { return o.context.nameof( name ); };
    func (sc_t ifnameof( c @* o, tp_t name )) = { return o.context.ifnameof( name ); };
    func (tp_t entypeof( c @* o, sc_t name )) = { return o.context.entypeof( name ); };
    func (tp_t entypeof_fv( c @* o, sc_t format, va_list args )) = { return o.context.entypeof( st_s_create_fv( format, args ).scope()->sc ); };
    func (tp_t entypeof_fa( c @* o, sc_t format, ... )) =
    {
        va_list args; va_start( args, format );
        tp_t tp = o.entypeof_fv( format, args );
        va_end( args );
        return tp;
    };

    func (tp_t parse_name(       c @* o, m bcore_source* source )) = { return o.context.parse_name( source ); };
    func (tp_t parse_op2_symbol( c @* o, m bcore_source* source )) = { return o.context.parse_op2_symbol( source ); };
    func (bl_t is_control_type(  c @* o, tp_t name )) = { return o.context.is_control_type( name ); };
    func (bl_t is_reserved_name( c @* o, tp_t name )) = { return o.context.is_reserved_name( name ); };
    func (tp_t parse_var_name(   c @* o, m bcore_source* source )) = { return o.context.parse_var_name( source ); };

};

// ---------------------------------------------------------------------------------------------------------------------

/// evaluation stack indicators
stamp :stack_flag_s = aware : {};

// ---------------------------------------------------------------------------------------------------------------------

// semantic builder
group :builder = :
{
    signature er_t build_from_source( m @* o, m opal_sem_cell_s* cell, m bcore_source* source );

    stamp :s = aware :
    {
        ::context_s => context;
        ::cell_s => context_cell;
        ::cell_s => frame_cell;
        func :.build_from_source;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

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
    signature void push_parents_to_sem_id( c @* o, m ::id_s* sem_id );
    signature void get_sem_id(             c @* o, m ::id_s* sem_id );

    stamp :node_s = aware x_array
    {
        sz_t id = -1;
        private opal_sem_cell_s -> cell;
        private :node_s -> parent; // semantic parent of cell (note that cell.parent is a lexical parent)
        :node_s => [];

        wrap x_array.push_d;

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

    signature er_t enter( m @* o, m ::cell_s* cell,                        m :node_s* node_in, m :node_s** node_out );
    signature er_t exit ( m @* o, m ::cell_s* cell, bl_t test_for_wrapper, m :node_s* node_in, m :node_s** node_out );

    stamp :s = aware :
    {
        sz_t id_base = 0; // (incremented when adding nodes)
        :node_s => root;

        func :.enter;
        func :.exit = { return node_in.exit( cell, test_for_wrapper, node_out ); };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

func (:link_s) (m @* trace_to_cell_membrane( m @* o ));

func (:tree_node_s) (m bcore_source_point_s* get_nearest_source_point( m @* o ));

embed "opal_sem.x";

#endif // XOILA_SECTION

/**********************************************************************************************************************/

void stack_push( bcore_arr_vd_s* o, vd_t value );
vd_t stack_pop( bcore_arr_vd_s* o );
vd_t stack_pop_of_type( bcore_arr_vd_s* o, tp_t type, bcore_source* source );
vd_t stack_pop_of_value( bcore_arr_vd_s* o, vd_t value, bcore_source* source );
bl_t stack_of_type( bcore_arr_vd_s* o, sz_t idx, tp_t type );
bl_t stack_of_value( bcore_arr_vd_s* o, sz_t idx, vd_t value );
opal_sem_link_s* stack_pop_link( bcore_arr_vd_s* o, bcore_source* source );
opal_sem_cell_s* stack_pop_cell( bcore_arr_vd_s* o, bcore_source* source );
opal_sem_link_s* stack_pop_link_or_exit( bcore_arr_vd_s* o, bcore_source* source );


#endif // OPAL_SEM_H
