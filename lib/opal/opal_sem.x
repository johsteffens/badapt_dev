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

/**********************************************************************************************************************/
/// groups, stamps

// ---------------------------------------------------------------------------------------------------------------------

// semantic context
group :context = opal_context
{
    signature void setup( m @* o, m opal_sem_cell_s* frame );
    signature cell setup_cell( m @* o, m opal_sem_cell_s* cell ); // returns cell
    signature d opal_sem_cell_s* create_cell( m @* o ); // creates and setups cell

    stamp :s = aware :
    {
        opal_nop_context_s nop_context;
        func opal_context .get_prsg { return o->nop_context.get_prsg(); };

        bcore_hmap_name_s hmap_name;
        bcore_arr_st_s    arr_symbol_op2;

        bcore_hmap_tp_s control_types; // types reserved for control
        bcore_hmap_tp_s reserved_names; // reserved keywords (not allowed for variables)

        func :.setup;

        func opal_context .nameof   { return o.hmap_name.get_sc( name ); };
        func opal_context .ifnameof { sc_t sc = o.nameof( name ); return sc ? sc : ""; };
        func opal_context .typeof   { return btypeof( name ); };
        func opal_context .entypeof { return o.hmap_name.set_sc( name ); };

        func :.setup_cell
        {
            cell.context =< o.fork();
            return cell;
        };

        func :.create_cell
        {
            return o.setup_cell( ::cell_s! );
        };

        func (tp_t entypeof_fv( m @* o, sc_t format, va_list args ))
        {
            return o.entypeof( st_s_create_fv( format, args )^.sc );
        };

        func (tp_t entypeof_fa( m @* o, sc_t format, ... ))
        {
            va_list args; va_start( args, format );
            tp_t tp = o.entypeof_fv( format, args );
            va_end( args );
            return tp;
        };

        func (tp_t parse_name( m @* o, m x_source* source ))
        {
            m st_s* name = st_s!^;
            source.parse_fa( " #name", name );
            if( name.size == 0 ) source.parse_error_fa( "Identifier expected." );
            return o.entypeof( name.sc );
        };

        func (bl_t is_control_type(  c @* o, tp_t name )) { return o.control_types.exists( name ); };
        func (bl_t is_reserved_name( c @* o, tp_t name )) { return o.reserved_names.exists( name ); };

        func (tp_t parse_var_name( m @* o, m x_source* source ))
        {
            tp_t name = o.parse_name( source );
            if( o.is_reserved_name( name ) )
            {
                source.parse_error_fa( "'#<sc_t>' is a reserved keyword. It may not be used as identifier at this point.", o.ifnameof( name ) );
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
        func (sz_t size( c @* o )) { return o.arr.size; };
        func (m x_inst* push( m @* o, m x_inst* value )) { o.arr.push( value ); return value; };
        func (m x_inst* pop(  m @* o )) { return (x_inst*)o.arr.pop(); };
        func (m x_inst* pop_of_type(  m @* o, tp_t type, m x_source* source ))
        {
            m x_inst* v = o.pop();
            if( v._ == type ) return v;
            source.parse_error_fa( "Type error: '#<sc_t>' present but '#<sc_t>' expected.", ifnameof( v._ ), ifnameof( type ) );
            return NULL;
        };

        func (m x_inst* pop_of_value( m @* o, m x_inst* value, m x_source* source ))
        {
            m x_inst* v = o.pop();
            if( v == value ) return v;
            source.parse_error_fa( "Internal error: Stack holds invalid value." );
            return NULL;
        };

        func (bl_t is_of_type( m @* o, sz_t idx, tp_t type ))
        {
            if( idx <= 0 || idx > o.arr.size ) return false;
            return *(aware_t*)o.arr.[ o.arr.size - idx ] == type;
        };

        func (bl_t is_of_value( m @* o, sz_t idx, m x_inst* value ))
        {
            if( idx <= 0 || idx > o.arr.size ) return false;
            return ( o.arr.[ o.arr.size - idx ].cast( m x_inst* ) == value );
        };

        func (m ::link_s* pop_link( m @* o, m x_source* source )) { return o.pop_of_type( ::link_s~, source ).cast(m ::link_s*); };
        func (m ::cell_s* pop_cell( m @* o, m x_source* source )) { return o.pop_of_type( ::cell_s~, source ).cast(m ::cell_s*); };

        func (m ::link_s* pop_link_or_exit( m @* o, m x_source* source ))
        {
            m x_inst* v = o.pop();
            if     ( v._ == ::link_s~ )
            {
                return v.cast(m ::link_s*);
            }
            else if( v._ == ::cell_s~ )
            {
                m ::cell_s* cell = v.cast(m ::cell_s*);
                if( cell.excs.size != 1 )
                {
                    source.parse_error_fa( "Cell has #<sz_t> exit channels. Require is 1.", cell.excs.size );
                }
                return cell.excs.[ 0 ];
            }
            else
            {
                source.parse_error_fa( "Incorrect object on stack '#<sc_t>.", ifnameof( v._ ) );
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
    signature void push_tp(     m @* o, tp_t tp );
    signature void push_child(  m @* o, tp_t tp );
    signature void push_parent( m @* o, tp_t tp );
    signature void to_string(   c @* o, c opal_context* context, m st_s* s );
    signature er_t parse( m @* o, mutable x_source* source );
    signature er_t parse_sc( m @* o, sc_t sc );

    /// for use in other objects
    signature void get_sem_id( c @* o, m :s* sem_id );

    stamp :s = aware :
    {
        bcore_arr_tp_s arr;
        func :.clear       { o.arr.clear(); };
        func :.set         { o.arr.clear(); o.arr.push( tp ); };
        func :.push_tp     { o.arr.push( tp ); };
        func :.push_child  { o.arr.push( tp ); };
        func :.push_parent { o.arr.push_left( tp ); };
        func :.to_string
        {
            s.clear();
            foreach( tp_t t in o.arr )
            {
                if( __i > 0 ) s.push_char( '.' );
                s.push_sc( context.ifnameof( t ) );
            }
        };

        func :.parse
        {
            o.clear();
            while( source.parse_bl( "#?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z')||([0]>='0'&&[0]<='9')||([0]=='.'))" ) )
            {
                if( o.arr.size > 0 ) source.parse_fa( "." );
                st_s^ name;
                source.parse_fa( "#name", name.1 );
                o.push_tp( btypeof( name.sc ) );
            }
            return 0;
        };

        func :.parse_sc { return o.parse( x_source_create_from_sc( sc )^ ); };

        func (s2_t cmp(           @* o, @* b )) { return o.arr.cmp( b.arr ); };
        func (bl_t is_equal(      @* o, @* b )) { return o.cmp( b ) == 0; };
        func (bl_t matches_front( @* o, @* b )) { s2_t v = o.cmp( b ); return v == 0 || v == 1; };
        func (bl_t matches_tail(  @* o, @* b ))
        {
            if( o.arr.size > b.arr.size ) return false;
            foreach( tp_t t in o.arr ) if( t != b.arr.[ b.arr.size - o.arr.size + __i ] ) return false;
            return true;
        };

        func (tp_t get_front_hash( @* o, sz_t size ))
        {
            size = sz_max( size, o.arr.size );
            tp_t hash = bcore_tp_init();
            for( sz_t i = 0; i < size; i++ ) hash = bcore_tp_fold_tp( hash, o.arr.[ i ] );
            return hash;
        };

        func (tp_t get_tail_hash( @* o, sz_t size ))
        {
            size = sz_max( size, o.arr.size );
            sz_t start = o.arr.size - size;
            tp_t hash = bcore_tp_init();
            for( sz_t i = 0; i < size; i++ ) hash = bcore_tp_fold_tp( hash, o.arr.[ i + start ] );
            return hash;
        };

        func (tp_t get_tail_hash_after_sub_id( @* o, @* sub_id ))
        {
            sz_t index = o.find( sub_id );
            index = ( index < 0 ) ? 0 : index + sub_id.arr.size;
            return o.get_tail_hash( o.arr.size - index );
        };

        func (tp_t get_hash( @* o )) { return o.get_front_hash( o.arr.size ); };

        func (o copy_front( mutable @* o, @* b, sz_t size ))
        {
            sz_t min_size = sz_min( size, b.arr.size );
            o.arr.set_size( min_size );
            for( sz_t i = 0; i < min_size; i++ ) o.arr.[ i ] = b.arr.[ i ];
            return o;
        };

        func (o copy_tail( mutable @* o, @* b, sz_t size ))
        {
            sz_t min_size = sz_min( size, b.arr.size );
            o.arr.set_size( min_size );
            for( sz_t i = 0; i < min_size; i++ ) o.arr.[ i ] = b.arr.[ b.arr.size - min_size + i ];
            return o;
        };

        func (d @* create_front( @* o, sz_t size )) { return @!.copy_front( o, size ); };
        func (d @* create_tail ( @* o, sz_t size )) { return @!.copy_tail ( o, size ); };

        /// returns index of first match or -1 if not found;
        func (sz_t find( @* o, @* b ))
        {
            if( b.arr.size > o.arr.size ) return -1;
            for( sz_t i = 0; i < o.arr.size; i++ )
            {
                bl_t match = true;
                for( sz_t j = 0; j < b.arr.size; j++ )
                {
                    if( o.arr.[ i + j ] != b.arr.[ j ] )
                    {
                        match = false;
                        break;
                    }
                }
                if( match ) return i;
            }
            return -1;
        };
    };

};

// ---------------------------------------------------------------------------------------------------------------------

// language control types
name cell;

signature   sz_t get_arity( c @* o );
signature   sz_t get_priority( c @* o );
feature tp_t get_name( c @* o ) { return 0; };
feature bl_t is_visible( c @* o ) { return true; }; // invisible objects are not searchable via get_by_name functions
feature void set_name_visible(   m @* o, tp_t name );
feature void set_name_invisible( m @* o, tp_t name );

body             get_name_ { return o->name; };

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
    func :. get_name :get_name_;
    func :.set_name_visible   { o->name = name; o->visible = true; };
    func :.set_name_invisible { o->name = name; o->visible = false; };
    func :.is_visible { return o->visible; };
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

    func :.get_link_by_name
    {
        foreach( m $* e in o ) if( e.name == name ) return e;
        return NULL;
    };

    func :.name_exists
    {
        foreach( c $* e in o ) if( e.name == name ) return true;
        return false;
    };

    func :.get_link_by_up
    {
        foreach( m $* e in o ) if( e.up == up ) return e;
        return NULL;
    };

    func :.get_link_by_dn
    {
        foreach( m $* e in o ) if( e.dn == dn ) return e;
        return NULL;
    };

    func :.get_index_by_link
    {
        foreach( m $* e in o ) if( e == link ) return __i;
        return -1;
    };

    func :.count_open
    {
        sz_t count = 0;
        foreach( m $* e in o ) count += ( e.up == NULL );
        return count;
    };

    func (m @* trace_to_cell_membrane( m @* o ));

};

stamp :body_s = aware x_array
{
    aware : => [];

    wrap x_array.push_t;

    func :.name_exists
    {
        foreach( m $* e in o ) if( e.get_name() == name ) return true;
        return false;
    };

    func :.get_sem_by_name
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
    hidden x_source_point_s source_point;

    // if cell is a wrapper, wrapped_cell is the cell being wrapped
    private :cell_s    -> wrapped_cell;

    func :.get_name :get_name_;

    func :.set_name_visible   { o->name = name; o->visible = true; };
    func :.set_name_invisible { o->name = name; o->visible = false; };
    func :.is_visible      { return o->visible; };
    func :.get_arity       { return o.encs.count_open(); };
    func :.get_enc_by_name { return o.encs.get_link_by_name( name ); };
    func :.get_exc_by_name { return o.excs.get_link_by_name( name ); };
    func :.get_enc_by_open { return o.encs.get_link_by_up( NULL ); };
    func :.get_enc_by_dn   { return o.encs.get_link_by_dn( dn   ); };
    func :.get_priority    { return o->priority; };
    func :.is_wrapper      { return o->wrapped_cell != NULL && o->nop == NULL && o->body == NULL; };

    // search for a cell descends the tree
    func :.get_cell_by_name
    {
        m :* sem = o.body ? o.body.get_sem_by_name( name ) : NULL;
        if( sem && sem._ == :cell_s~ ) return sem.cast( m :cell_s* );
        if( o.parent ) return o.parent.get_cell_by_name( name );
        return NULL;
    };

    // search for a link only looks up the body of this cell
    func :.get_link_by_name
    {
        m :* sem = o.body ? o.body.get_sem_by_name( name ) : NULL;
        if( sem && sem._ == :link_s~ ) return sem.cast( m :link_s* );
        return NULL;
    };

    // push semantic item to cell's body ...
    func (m :* push_sem( m @* o, tp_t type )) { return o.body!.push_t( type ); };
    func (m :link_s* push_link( m @* o )) { return o.push_sem( :link_s~ ).cast( m :link_s* ); };
    func (m @* push_cell( m @* o ))
    {
        m @* cell = o.push_sem( @~ ).cast( m @* );
        cell->parent = o;
        cell->context = o->context.fork();
        cell.set_name_invisible( o.entypeof_fa( "$#<sz_t>", o.body.size - 1 ) );
        return cell;
    };

    func (m @* push_cell_nop_d_invisible( m @* o, d opal_nop* nop )) { m @* cell = o.push_cell_nop_d( nop ); cell.visible = false; return cell; };
    func (m @* set_source( m @* o, m x_source* source )) { o.source_point.setup_from_source( source ); return o; };
    func (m @* push_cell_nop_d_set_source( m @* o, d opal_nop* nop, m x_source* source )) { return o.push_cell_nop_d( nop ).set_source( source ); };
    func (m @* push_cell_nop_d(                      m @* o, d opal_nop* nop ));
    func (m @* push_cell_nop_d_invisible_set_source( m @* o, d opal_nop* nop, m x_source* source )) { return o.push_cell_nop_d_invisible( nop ).set_source( source ); };
    func (m @* push_wrap_cell_hard( m @* o, m @* src )) { return o.push_cell().wrap_cell_hard( src ); };
    func (m @* push_wrap_cell_soft( m @* o, m @* src )) { return o.push_cell().wrap_cell_soft( src ); };
    func (m @* push_rewrap_cell_soft(     m @* o, m @* src )) { return o.push_cell().rewrap_cell_soft( src ); };
    func (m @* push_wrap_cell_set_source( m @* o, m @* src, m x_source* source )) { return o.push_wrap_cell_soft( src ).set_source( source ); };

    func (void create_args_out( m @* o, m x_source* source ));
    func (void create_args_in(  m @* o, m :cell_s* frame, m x_source* source ));
    func (void wrap_cell(       m @* o, m :cell_s* cell ));
    func (void             parse(               m @* o,                      m x_source* source ));
    func (void             parse_body(          m @* o,                      m x_source* source ));
    func (m opal_sem*        evaluate_sem(        m @* o,                    m x_source* source ));
    func (m opal_sem*        evaluate_sem_stack(  m @* o, m :stack_s* stack, m x_source* source ));
    func (m opal_sem_cell_s* evaluate_cell(       m @* o,                    m x_source* source ));
    func (m opal_sem_cell_s* evaluate_cell_stack( m @* o, m :stack_s* stack, m x_source* source ));
    func (m opal_sem_link_s* evaluate_link(       m @* o,                    m x_source* source ));
    func (m opal_sem_link_s* evaluate_link_stack( m @* o, m :stack_s* stack, m x_source* source ));
    func (void             set_channels(        m @* o, sz_t excs, sz_t encs ));

    /// Context wrappers
    func (sc_t nameof(   c @* o, tp_t name )) { return o.context.nameof( name ); };
    func (sc_t ifnameof( c @* o, tp_t name )) { return o.context.ifnameof( name ); };
    func (tp_t entypeof( c @* o, sc_t name )) { return o.context.entypeof( name ); };
    func (tp_t entypeof_fv( c @* o, sc_t format, va_list args )) { return o.context.entypeof( st_s_create_fv( format, args )^->sc ); };
    func (tp_t entypeof_fa( c @* o, sc_t format, ... ))
    {
        va_list args; va_start( args, format );
        tp_t tp = o.entypeof_fv( format, args );
        va_end( args );
        return tp;
    };

    func (tp_t parse_name(       c @* o, m x_source* source )) { return o.context.parse_name( source ); };
    func (tp_t parse_op2_symbol( c @* o, m x_source* source )) { return o.context.parse_op2_symbol( source ); };
    func (bl_t is_control_type(  c @* o, tp_t name )) { return o.context.is_control_type( name ); };
    func (bl_t is_reserved_name( c @* o, tp_t name )) { return o.context.is_reserved_name( name ); };
    func (tp_t parse_var_name(   c @* o, m x_source* source )) { return o.context.parse_var_name( source ); };

};

// ---------------------------------------------------------------------------------------------------------------------

/// evaluation stack indicators
stamp :stack_flag_s = aware : {};

// ---------------------------------------------------------------------------------------------------------------------

// semantic builder
group :builder = :
{
    signature er_t build_from_source( m @* o, m opal_sem_cell_s* cell, m x_source* source );

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

        func :.push_parents_to_sem_id
        {
            sem_id.push_parent( o.cell ? o.cell.name : 0 );
            if( o.parent ) o.parent.push_parents_to_sem_id( sem_id );
        };

        func :.get_sem_id
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
        func :.exit { return node_in.exit( cell, test_for_wrapper, node_out ); };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :context_s

// ---------------------------------------------------------------------------------------------------------------------

func (:context_s) (tp_t parse_op2_symbol( c @* o, m x_source* source ))
{
    c bcore_arr_st_s* arr = o.arr_symbol_op2;

    m st_s* format = st_s!^;
    tp_t ret = 0;

    source.parse_fa( " " );
    for( sz_t i = 0; i < arr.size; i++ )
    {
        format.copy_fa( "##?'#<sc_t>'", arr.[ i ].sc );
        if( source.parse_bl( format.sc ) )
        {
            ret = btypeof( arr.[ i ].sc );
            break;
        }
    }

    return ret;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:context_s) :.setup
{
    m bcore_arr_tp_s* arr_tp = bcore_arr_tp_s!^;

    arr_tp.push_arr( x_group_get_arr_traitline_stamps( opal_nop_ar1~ ) );
    arr_tp.push_arr( x_group_get_arr_traitline_stamps( opal_nop_ar2~ ) );
    arr_tp.push_arr( x_group_get_arr_traitline_stamps( opal_nop_ar3~ ) );

//    bcore_push_traits_of_ancestor( opal_nop_ar1~, arr_tp );
//    bcore_push_traits_of_ancestor( opal_nop_ar2~, arr_tp );
//    bcore_push_traits_of_ancestor( opal_nop_ar3~, arr_tp );

    for( sz_t i = 0; i < arr_tp.size; i++ )
    {
        d opal_nop* nop = opal_nop_t_create( arr_tp.[ i ] );
        sc_t symbol   = nop.symbol();

        // bcore_msg_fa( "#<sc_t>\n", symbol );
        if( symbol )
        {
            sz_t arity = nop.arity();
            o.hmap_name.set_sc( symbol );
            if( arity == 2 ) o.arr_symbol_op2.push_sc( symbol );
            m ::cell_s* cell = frame.push_cell_nop_d( nop );
            cell.set_name_visible( btypeof( symbol ) );

            if( nop.reserved() ) o.reserved_names.set( o.entypeof( symbol ) );
        }
        else
        {
            nop =< NULL;
        }
    }

    /** We sort the array in descending manner; this ensures that short symbols
     *  which patterns match the beginning of a longer symbol can not occlude the longer one.
     */
    o.arr_symbol_op2.sort( -1 );

    /// register control types
    o.control_types.set( o.entypeof( "cell" ) );

    /// register reserved keywords
    o.reserved_names.set( o.entypeof( "cell"     ) );
    o.reserved_names.set( o.entypeof( "cyclic"   ) );
    o.reserved_names.set( o.entypeof( "adaptive" ) );
    o.reserved_names.set( o.entypeof( "param"    ) );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :link_s

// ---------------------------------------------------------------------------------------------------------------------

func (d :link_s* link_s_create_setup( tp_t name, m :link_s* up, m :link_s* dn, m :cell_s* cell, bl_t exit ))
{
    d :link_s* o = :link_s!;
    o.set_name_visible( name );
    o.up = up;
    o.dn = dn;
    o.cell = cell;
    o.exit = exit;
    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next membrane; returns NULL in case trace ends in open link
func (:link_s) (m @* trace_to_cell_membrane( m @* o ))
{
    if( !o || o.cell ) return o;
    return o.up.trace_to_cell_membrane();
};

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next cell; returns NULL in case trace ends in open link
func (:link_s) (m :cell_s* trace_to_cell( m @* o ))
{
    m :link_s* link = o.trace_to_cell_membrane();
    if( link )
    {
        if( link.cell ) assert( link.cell._ == :cell_s~ );
        return link.cell;
    }
    else
    {
        return NULL;
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :cell_s

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) set_channels
{
    o.excs.set_size( excs );
    o.encs.set_size( encs );
    foreach( m :link_s.2 link in o.excs ) link.1 = :link_s_create_setup( 0, NULL, NULL, o, true );
    foreach( m :link_s.2 link in o.encs ) link.1 = :link_s_create_setup( 0, NULL, NULL, o, false );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Adds a wrapping membrane only exposing unspecified entry links.
  * links of src are not modified; returns o
  */
func (:cell_s) (m @* wrap_cell_soft( m @* o, m @* src ))
{
    ASSERT( !o.body );
    ASSERT( !o.nop  );
    ASSERT( !o.wrapped_cell );

    o.wrapped_cell = src;
    o.priority = src.priority;
    o.encs.set_size( src.get_arity() );
    o.excs.set_size( src.excs.size );

    sz_t k = 0;

    foreach( m :link_s* link in src.encs; !link.up )
    {
        o.encs.[ k++ ] = :link_s_create_setup( link.name, NULL, link, o, false );
    }

    assert( k == o.encs.size );

    foreach( m :link_s* link in src.excs )
    {
        o.excs.data[ __i ] = :link_s_create_setup( link.name, link, NULL, o, true );
    }

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

/** Adds a wrapping membrane exposing all links of src.
  * Explicitly moves entry links of src to the wrapping membrane
  * Returns o.
  */
func (:cell_s) (m @* wrap_cell_hard( m @* o, m :cell_s* src ))
{
    ASSERT( !o.body );
    ASSERT( !o.nop  );
    ASSERT( !o.wrapped_cell );

    o.wrapped_cell = src;
    o.priority = src.priority;
    o.encs.set_size( src.encs.size );
    o.excs.set_size( src.excs.size );

    foreach( m :link_s.2 link in src.encs )
    {
        o.encs.[ __i ] = :link_s_create_setup( link.1.name, link.1.up, link.1, o, false );
        link.1.up = NULL;
    }

    foreach( m :link_s.2 link in src.excs )
    {
        o.excs.[ __i ] = :link_s_create_setup( link.1.name, link.1, NULL, o, true );
    }

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

/** Passes through all wrapping membranes of src to find first non-wrapper (root).
 *  Wraps root by moving all specified entries of intermediate wrappers to the outermost membrane.
 *  Does not (!) move specified links of the root cell.
 *  Returns o.
 */
func (:cell_s) (m @* rewrap_cell_soft( m @* o, m :cell_s* src ))
{
    ASSERT( !o.body );
    ASSERT( !o.nop  );
    ASSERT( !o.wrapped_cell );

    m :cell_s* root = src;
    while( root.wrapped_cell ) root = root.wrapped_cell;
    o.wrap_cell_soft( root );

    m :cell_s* wrap = src;
    while( wrap.wrapped_cell )
    {
        foreach( m :link_s* wrap_link in wrap.encs; wrap_link.up )
        {
            m :link_s* root_link = wrap_link;
            while( root_link.cell != root && root_link.dn ) root_link = root_link.dn;
            ASSERT( root_link.cell == root );

            foreach( m :link_s* link in o.encs; link.dn == root_link )
            {
                link.up = wrap_link.up;
                break;
            }
        }
        wrap = wrap.wrapped_cell;
    }
    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

/**
 * Channel naming:
 * Output channel has name 'y'
 * Input channels are named in order 'a', 'b' ...
 * If ever more than 24 input channels are used, excess channels carry no name.
 */
func (:cell_s) push_cell_nop_d
{
    m @* cell = o.push_cell();
    cell.set_channels( 1, nop.arity() );
    sc_t symbol = nop.symbol();
    if( symbol ) cell.set_name_visible( o.entypeof( symbol ) );
    cell.nop = nop;
    cell.priority = nop.priority();
    cell.excs.[ 0 ].set_name_visible( o.entypeof( "y" ) );
    foreach( m :link_s* link in cell.encs ) if( __i < 'y' - 'a' ) link.set_name_visible( o.entypeof_fa( "#<char>", 'a' + __i ) );
    return cell;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (m @* push_cell_const_scalar( m @* o, tp_t type, f3_t v ))
{
    d opal_nop_ar0_literal_s* literal = opal_nop_ar0_literal_s!;
    literal.h = opal_holor_s!;
    literal.h.h.set_type_scalar( type, v );
    literal.h.m.active = false;
    return o.push_cell_nop_d_invisible( literal );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void assert_identifier_not_yet_defined( c @* o, tp_t name, m x_source* source ))
{
    if( o.encs.name_exists( name ) || ( o.body && o.body.name_exists( name ) ) )
    {
        source.parse_error_fa( "Identifier '#<sc_t>' already exists.", o.ifnameof( name ) );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/// parses ( ... <- ... )
func (:cell_s) (void parse_signature( m @* o, m x_source* source ))
{
    source.parse_fa( " (" );

    // parse excs
    {
        ASSERT( o.excs.size == 0 );
        bl_t first = true;
        while( !source.parse_bl( " #?'<-'" ) )
        {
            if( !first ) source.parse_fa( " ," );
            o.excs.push_d( :link_s_create_setup( o.parse_var_name( source ), NULL, NULL, o, true ) );
            first = false;
        }
    }

    // parse encs
    {
        ASSERT( o.encs.size == 0 );
        bl_t first = true;
        while( !source.parse_bl( " #?')'" ) )
        {
            if( !first ) source.parse_fa( " ," );
            d :link_s* link = :link_s_create_setup( o.parse_var_name( source ), NULL, NULL, o, false );
            if( source.parse_bl( " #?([0]=='='&&[1]!='=')" ) )
            {
                source.parse_fa( "=" );
                link.up = o.parent.evaluate_link( source );
            }
            o.encs.push_d( link );
            first = false;
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) parse
{
    m :cell_s* frame = o.parent;

    // cell signature without name is allowed
    if( !source.parse_bl( " #=?'('" ) )
    {
        tp_t tp_cell_name = o.parse_var_name( source );
        if( frame ) frame.assert_identifier_not_yet_defined( tp_cell_name, source );
        o.set_name_visible( tp_cell_name );
    }

    o.source_point.setup_from_source( source );

    //  ( <args_out> <- <args_in> ) { <body> }
    if( source.parse_bl( " #=?'('" ) )
    {
        o.parse_signature( source );
        source.parse_fa( " {" );
        o.parse_body( source );
        source.parse_fa( " }" );
    }
    else // = 'expression yielding a cell'
    {
        source.parse_fa( " = " );
        o.wrap_cell_soft( frame.evaluate_cell( source ) );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (d st_s* create_signature( c @* o ))
{
    d st_s* s = st_s!;
    s.push_fa( "(" );
    foreach( m :link_s* link in o.excs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", __i > 0 ? "," : "", o.ifnameof( link.name ) );
    s.push_fa( "<-" );
    foreach( m :link_s* link in o.encs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", __i > 0 ? "," : "", o.ifnameof( link.name ) );
    s.push_fa( ")" );
    return s;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void parse_verify_signature( c @* o, m x_source* source ))
{
    source.parse_fa( " (" );

    // parse excs
    {
        bl_t first = true;
        sz_t index = 0;
        bl_t err = false;
        while( !err && !source.parse_bl( " #?'<-'" ) )
        {
            if( !first ) source.parse_fa( " ," );
            tp_t name = o.parse_var_name( source );
            if( !err ) err = ( index >= o.excs.size );
            if( !err ) err = o.excs.[ index ].name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o.excs.size;
        if( err )
        {
            m st_s* sig =  o.create_signature()^;
            source.parse_error_fa( "Cell signature is '#<sc_t>'", sig.sc );
        }
    }

    // parse encs
    {
        bl_t first = true;
        sz_t index= 0;
        bl_t err = false;
        while( !err && !source.parse_bl( " #?')'" ) )
        {
            if( !first ) source.parse_fa( " ," );
            tp_t name = o.parse_var_name( source );
            if( !err ) err = ( index >= o.encs.size );
            if( !err ) err = o.encs.[ index ].name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o.encs.size;
        if( err )
        {
            m st_s* sig = o.create_signature()^;
            source.parse_error_fa( "Cell signature is '#<sc_t>'", sig.sc );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) parse_body
{
    source.parse_fa( " " );
    while( !source.eos() && !source.parse_bl( " #=?'}'" ) )
    {
        if( source.parse_bl( " #?'cell'" ) ) // definition of a cell
        {
            o.push_cell().parse( source );
        }
        else if( source.parse_bl( " #?'verify_signature'" ) ) // verifies signature of wrapping cell
        {
            o.parse_verify_signature( source );
        }
        else if( source.parse_bl( " #?'param'" ) ) // defining a link to a parameter operator
        {
            tp_t tp_name = o.parse_var_name( source );
            m :link_s* link = o.push_link();
            o.assert_identifier_not_yet_defined( tp_name, source );
            link.set_name_visible( tp_name );
            m :cell_s* cell = o.push_cell_nop_d_invisible_set_source( opal_nop_ar1_param_s!, source );
            cell.set_name_invisible( tp_name );
            source.parse_fa( " =" );
            cell.encs.[ 0 ].up = o.evaluate_link( source );
            link.up = cell.excs.[ 0 ];
        }
        else if( source.parse_bl( " #?'adaptive'" ) ) // defining a link to an adaptive operator
        {
            tp_t tp_name = o.parse_var_name( source );
            m :link_s* link = o.push_link();
            o.assert_identifier_not_yet_defined( tp_name, source );
            link.set_name_visible( tp_name );
            d opal_nop_ar1_adaptive_s* nop_adaptive = opal_nop_ar1_adaptive_s!;
            nop_adaptive.name = tp_name;
            m :cell_s* cell = o.push_cell_nop_d_invisible_set_source( nop_adaptive, source );
            cell.set_name_invisible( tp_name );
            source.parse_fa( " =" );
            cell.encs.[ 0 ].up = o.evaluate_link( source );
            link.up = cell.excs.[ 0 ];
        }
        else if( source.parse_bl( " #?'cyclic'" ) ) // A link is defined as cyclic by attaching cyclic operator with open input channel
        {
            tp_t tp_name = o.parse_var_name( source );
            m :link_s* link = o.push_link();
            o.assert_identifier_not_yet_defined( tp_name, source );
            link.set_name_visible( tp_name );
            d opal_nop_ar2_cyclic_s* nop_cyclic = opal_nop_ar2_cyclic_s!;
            nop_cyclic.name = tp_name;
            m :cell_s* cell = o.push_cell_nop_d_invisible_set_source( nop_cyclic, source );
            cell.set_name_invisible( tp_name );
            source.parse_fa( " =" );
            cell.encs.[ 0 ].up = o.evaluate_link( source );
            link.up = cell.excs.[ 0 ];
        }
        else // identifier
        {
            tp_t tp_name = o.parse_var_name( source );
            m :* item = NULL;

            if( ( item = o.get_exc_by_name( tp_name ) ) ) // identifier is exit channel of o
            {
                m :link_s* link = item.cast( m :link_s* );
                if( link.up )
                {
                    source.parse_error_fa
                    (
                        "Channel '#<sc_t>' of cell '#<sc_t>' has already been defined.",
                        o.ifnameof( tp_name ),
                        o.ifnameof( o.name )
                    );
                }
                source.parse_fa( " =" );
                link.up = o.evaluate_link( source );
            }
            else if( ( item = o.get_link_by_name( tp_name ) ) ) // identifier is a link defined in o's body
            {
                m :link_s* link = item.cast( m :link_s* );

                // Idle links should never occur. If they do, there is probably a bug in the opal-compiler.
                if( !link.up      ) source.parse_error_fa( "Link '#<sc_t>' is idle.", o.ifnameof( tp_name ) );
                if( !link.up.cell ) source.parse_error_fa( "Link '#<sc_t>' has already been defined.", o.ifnameof( tp_name ) );
                m :cell_s* cell = link.up.cell;

                if( cell.nop && cell.nop._ == opal_nop_ar2_cyclic_s~ )
                {
                    if( !cell.encs.[ 1 ].up )
                    {
                        source.parse_fa( " =" );
                        cell.encs.[ 1 ].up = o.evaluate_link( source );
                        link.protected = true;
                    }
                    else
                    {
                        source.parse_error_fa( "Redefining a cyclic link '#<sc_t>'.", o.ifnameof( tp_name ) );
                    }
                }
                else
                {
                    source.parse_error_fa( "Link '#<sc_t>' has already been defined.", o.ifnameof( tp_name ) );
                }
            }
            else // unknown identifier -. creates a link
            {
                m :link_s* link = o.push_link();
                o.assert_identifier_not_yet_defined( tp_name, source );
                link.set_name_visible( tp_name );
                source.parse_fa( " =" );
                link.up = o.evaluate_link( source );
            }
        }
        source.parse_fa( " ; " );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void evaluate_set_encs( m @* o, m :cell_s* parent, m x_source* source ))
{
    m :stack_s* stack = :stack_s!^;
    m st_s* name = st_s!^;

    source.parse_fa( " (" );
    bl_t first = true;
    while( !source.parse_bl( " #?')'" ) )
    {
        if( !first ) source.parse_fa( " ," );

        bl_t done = false;

        if( source.parse_bl( " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            source.parse_fa( "#name", name );
            if( source.parse_bl( " #?([0]=='='&&[1]!='=')" ) )
            {
                source.parse_fa( "=" );
                m :link_s* link = o.get_enc_by_name( btypeof( name.sc ) );
                if( !link )
                {
                    source.parse_error_fa
                    (
                        "'#<sc_t>' specifies no entry channel of cell '#<sc_t>'.",
                        name.sc,
                        o.ifnameof( o.name )
                    );
                }

                if( link.up )
                {
                    source.parse_error_fa
                    (
                        "Entry channel '#<sc_t>' of cell '#<sc_t>' has already been set.",
                        name.sc,
                        o.ifnameof( o.name )
                    );
                }

                link.up = parent.evaluate_link( source );
                done = true;
            }
            else
            {
                stack.push( name );
            }
        }

        if( !done )
        {
            m :link_s* link =  o.get_enc_by_open();
            if( !link )
            {
                source.parse_error_fa
                (
                    "Node '#<sc_t>': Number of free entry channels exceeded.",
                    o.ifnameof( o.name )
                );
            }
            link.up = parent.evaluate_link_stack( stack, source );
        }

        first = false;
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/** In body of o: creates new cell rewrapping the catenated cells: cell = { c1 <: c2 }
 *  This function rewraps c1, c2 making sure that all defined uplinks are moved to the outermost membrane.
 *  The catenated cell is then wrapped again to leave only undefined input links exposed.
 *  The last soft-wrapping is done for convenience because some code using this function assumes arity == encs.size.
 */
func (:cell_s) (m :cell_s* recat_cell( m @* o, m :cell_s* c1, m :cell_s* c2, m x_source* source ))
{
    m :cell_s* cell = o.push_cell();
    cell.source_point.setup_from_source( source );

    c1 = cell.push_rewrap_cell_soft( c1 );
    c2 = cell.push_rewrap_cell_soft( c2 );

    c1.set_name_invisible( o.entypeof( "$CAT1" ) );
    c2.set_name_invisible( o.entypeof( "$CAT2" ) );

    sz_t arity_c1 = c1.get_arity();

    /// free input channels of n1 must match output channels of n2
    if( arity_c1 != c2.excs.size )
    {
        cell.source_point.parse_error_fa
        (
            "Catenating cells: Number of left cell's open entry channels (#<sz_t>) differs from right cells's exit channels (#<sz_t>).",
            arity_c1,
            c2.excs.size
        );
    }

    /// channels of wrapping cell
    cell.set_channels( c1.excs.size, c2.encs.size + c1.encs.size - arity_c1 );

    foreach( m :link_s* c2_link in c2.encs )
    {
        m :link_s* c0_link = cell.encs.[ __i ];
        c0_link.set_name_visible( c2_link.name );
        c0_link.up = c2_link.up;
        c2_link.up = c0_link;
    }

    sz_t l = 0;
    sz_t k = c2.encs.size;
    foreach( m :link_s* c1_link in c1.encs )
    {
        if( c1_link.up )
        {
            assert( k < cell.encs.size );
            m :link_s* c0_link = cell.encs.[ k++ ];
            c0_link.set_name_visible( c1_link.name );
            c0_link.up = c1_link.up;
            c1_link.up = c0_link;
        }
        else
        {
            assert( l < c2.excs.size );
            c1_link.up = c2.excs.[ l++ ];
        }
    }

    ASSERT( k == cell.encs.size );
    ASSERT( l ==   c2.excs.size );

    foreach( m :link_s* c1_link in c1.excs )
    {
        m :link_s* c0_link = cell.excs.[ __i ];
        c0_link.up = c1_link;
        c0_link.set_name_visible( c1_link.name );
    }

    /// the last soft-wrap is convenience (consider changing dependent code using arity rather then encs.size to determine open links)
    return o.push_wrap_cell_soft( o.push_wrap_cell_hard( cell ) );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void evaluate_stack( m @* o, m :stack_s* stack, m x_source* source ))
{
    m st_s* name = st_s!^;

    m $* flag_bin_op    = :stack_flag_s!^;
    m $* flag_una_op    = :stack_flag_s!^;
    m $* flag_cell_cat  = :stack_flag_s!^;
    m $* flag_inc_order = :stack_flag_s!^;

    tp_t op2_symbol = 0;

    while( !source.eos() )
    {
        bl_t identifier = false;

        // identifier
        if( stack.is_of_type( 1, st_s~ ) )
        {
            name.copy( stack.pop().cast( m st_s* ) );
            identifier = true;
        }
        else if( source.parse_bl( " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            source.parse_fa( "#name", name );
            identifier = true;
        }

        if( identifier )
        {
            tp_t tp_name = btypeof( name.sc );

            if( o.is_control_type( tp_name ) )
            {
                if( tp_name == cell~ ) // inline cell definition
                {
                    m :cell_s* cell = o.push_cell();
                    cell.parse( source );
                    stack.push( cell );
                }
                else
                {
                    source.parse_error_fa( "Unexpected keyword '#<sc_t>'. Did you miss ';' after previous statement?", name.sc );
                }
            }
            else
            {
                m :* item = o.get_enc_by_name( tp_name );
                if( !item && o.body   ) item = o.body.get_sem_by_name( tp_name );
                if( !item && o.parent ) item = o.parent.get_cell_by_name( tp_name );
                if( !item )
                {
                    item = o.get_exc_by_name( tp_name );
                    if( item )
                    {
                        assert( item._ == :link_s~ );
                        m :link_s* link = item.cast( m :link_s* );
                        if( !link.up )
                        {
                            source.parse_error_fa( "Use of exit channel '#<sc_t>' before it was defined.", name.sc );
                        }
                        item = link.up;
                    }
                    else
                    {
                        source.parse_error_fa( "Cannot evaluate identifier '#<sc_t>'.", name.sc );
                    }
                }

                tp_t tp_item = item._;

                switch( tp_item )
                {
                    case :cell_s~:
                    {
                        stack.push( item.cast( m :cell_s* ) );
                    }
                    break;

                    case :link_s~:
                    {
                        m :link_s* link = item.cast( m :link_s* );
                        if( link.protected )
                        {
                            if( link.up && link.up.cell )
                            {
                                m :cell_s* cell = link.up.cell;
                                if( cell.nop && cell.nop._ == opal_nop_ar2_cyclic_s~ )
                                {
                                    source.parse_error_fa( "Recurrent node '#<sc_t>' must not be used after updating.", name.sc );
                                }
                            }
                            else
                            {
                                source.parse_error_fa( "Identifier '#<sc_t>' is protected (unusable) at this point.", name.sc );
                            }
                        }
                        stack.push( item );
                    }
                    break;

                    default:
                    {
                        source.parse_error_fa( "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name.sc, ifnameof( tp_item ) );
                    }
                    break;
                }
            }
        }

        // literal scalar (negative numbers are created via neg operator)
        else if( source.parse_bl( " #?([0]>='0'&&[0]<='9')" ) )
        {
            f3_t val = 0;
            tp_t type = f3_t~;
            source.parse_fa( " #<f3_t*>", &val );
            if(      source.parse_bl( "#?'f2'" ) ) type = f2_t~;
            else if( source.parse_bl( "#?'f3'" ) ) type = f3_t~;
            m :cell_s* cell = o.push_cell_const_scalar( type, val );
            cell.source_point.setup_from_source( source );
            stack.push( cell.excs.data[ 0 ] );
        }

        // undetermined scalar (falls back to 0)
        else if( source.parse_bl( " #?'#'" ) )
        {
            tp_t type = f3_t~;
            if(      source.parse_bl( "#?'f2'" ) ) type = f2_t~;
            else if( source.parse_bl( "#?'f3'" ) ) type = f3_t~;
            m :cell_s* cell = o.push_cell_const_scalar( type, 0 );
            cell.source_point.setup_from_source( source );
            stack.push( cell.excs.data[ 0 ] );
        }

        // block or input channel selection in case l-value is a cell
        else if( source.parse_bl( " #=?'('" ) )
        {
            if( stack.is_of_type( 1, :cell_s~ ) )
            {
                m :cell_s* cell = o.push_wrap_cell_set_source( stack.pop().cast( m :cell_s* ), source );
                cell.evaluate_set_encs( o, source );
                stack.push( cell );
            }
            else
            {
                source.parse_fa( " (" );
                stack.push( o.evaluate_sem( source ) );
                source.parse_fa( " )" );
            }
        }

        // cell catenation
        else if( source.parse_bl( " #?'<:'" ) )
        {
            if( stack.is_of_type( 1, :cell_s~ ) )
            {
                stack.push( flag_cell_cat );
            }
            else
            {
                source.parse_error_fa( "Cell catenation '<:': l-value is not a cell." );
            }
        }

        // binary operator from predefined symbols
        else if( ( op2_symbol = o.parse_op2_symbol( source ) ) )
        {
            if // if( binary op not applicable):
            (
                 stack.size() == 0 ||
               ( stack.size() >= 1 && stack.is_of_value( 1, flag_una_op ) ) ||
               ( stack.size() >= 3 && stack.is_of_value( 3, flag_bin_op ) )
            )
            {
                m :cell_s* cell = o.get_cell_by_name( op2_symbol );
                d opal_nop* nop_unary = cell.nop.create_op_of_arn( 1 );
                if( nop_unary )
                {
                    m :cell_s* cell = o.push_cell_nop_d_invisible_set_source( nop_unary, source );
                    stack.push( cell );
                    stack.push( flag_una_op ); // flag after cell to avoid incorrect stack evaluation
                }
                else
                {
                    if( stack.size() == 0 )
                    {
                        source.parse_error_fa
                        (
                            "Operator '#<sc_t>': Left operand missing.",
                            o.ifnameof( op2_symbol )
                        );
                    }
                    else
                    {
                        source.parse_error_fa
                        (
                            "Operator '#<sc_t>': This is a successive binary operator. Right operand expected instead.",
                            o.ifnameof( op2_symbol )
                        );
                    }
                }
            }
            else // else of: if( binary op not applicable):
            {
                m :cell_s* cell = o.get_cell_by_name( op2_symbol );
                if( !cell ) source.parse_error_fa( "Syntax error." );

                cell = o.push_wrap_cell_set_source( cell, source );

                stack.push( flag_bin_op );
                stack.push( cell );
            }
        }

        // custom binary operator
        else if( source.parse_bl( " #?'<<'" ) )
        {
            source.parse_fa( "#until'>'>>", name );
            if( stack.size() == 0 ) source.parse_error_fa( "Operator '#<sc_t>': Left operand missing.", name.sc );
            m :cell_s* cell = o.get_cell_by_name( btypeof( name.sc ) );
            if( !cell ) source.parse_error_fa( "Cell '#<sc_t>' not found.", name.sc );
            cell = o.push_wrap_cell_set_source( cell, source );
            stack.push( flag_bin_op );
            stack.push( cell );
        }

        // output channel selection
        else if( source.parse_bl( " #?'.'" ) )
        {
            source.parse_fa( "#name", name );
            if( name.size == 0 ) source.parse_error_fa( "Identifier expected." );

            if( !stack.is_of_type( 1, :cell_s~ ) )
            {
                source.parse_error_fa( "Output channel selection on non-cell." );
            }

            m :cell_s* cell = stack.pop().cast( m :cell_s* );
            m :link_s* link = cell.get_exc_by_name( btypeof( name.sc ) );

            if( cell.get_arity() > 0 )
            {
                source.parse_error_fa
                (
                    "Output channel selection on cell '#<sc_t>' with #<sz_t> open input channels.",
                    o.ifnameof( cell.name ),
                    cell.get_arity()
                );
            }

            if( !link )
            {
                source.parse_error_fa
                (
                    "Cell '#<sc_t>': Invalid channel '#<sc_t>'.",
                    o.ifnameof( cell.name ), name.sc
                );
            }
            stack.push( link );
        }

        // postfix htp
        else if( source.parse_bl( " #?'~'" ) )
        {
            m :cell_s* htp_cell = o.push_cell_nop_d_invisible_set_source( opal_nop_ar1_cast_htp_s!, source );
            if( stack.is_of_type( 1, :link_s~ ) )
            {
                htp_cell.encs.[ 0 ].up = stack.pop_link( source );
                stack.push( htp_cell.excs.[ 0 ] );
            }
            else if( stack.is_of_type( 1, :cell_s~ ) )
            {
                m :cell_s* r_cell = stack.pop_cell( source );
                stack.push( htp_cell );
                stack.push( flag_cell_cat );
                stack.push( r_cell );
            }
            else
            {
                source.parse_error_fa( "transposition '~': invalid l-value." );
            }
        }

        // single char terminator
        else if( source.parse_bl( " #?([0]==')'||[0]==']'||[0]==','||[0]==';')" ) )
        {
            break;
        }

        else
        {
            source.parse_error_fa( "Syntax error." );
        }

        /// priority stack processing ...

        // unary operator: right operand
        while( stack.size() >= 3 && stack.is_of_value( 2, flag_una_op ) && stack.is_of_type( 1, :link_s~ ) )
        {
            m :link_s* link = stack.pop_link( source );
            stack.pop_of_value( flag_una_op, source );
            m :cell_s* cell = stack.pop_cell( source );
            ASSERT( cell.encs.size == 1 );
            cell.encs.[ 0 ].up = link;
            stack.push( cell.excs.[ 0 ] );
        }

        if( stack.size() >= 3 && stack.is_of_value( 2, flag_bin_op ) )
        {
            m :cell_s* cell = stack.pop_cell( source );
            stack.pop_of_value( flag_bin_op, source );
            m opal_sem* arg1 = stack.pop();

            if( arg1._ == :cell_s~ )
            {
                m :cell_s* cell1 = arg1.cast( m :cell_s* );
                if( cell1.excs.size != 1 )
                {
                    cell1.source_point.parse_error_fa
                    (
                        "Binary operator '#<sc_t>': Left operant '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                        o.ifnameof( cell.name ),
                        o.ifnameof( cell1.name ),
                        cell1.excs.size
                    );
                }
                arg1 = cell1.excs.[ 0 ];
            }

            if( cell.get_arity() != 2 )
            {
                cell.source_point.parse_error_fa
                (
                    "Binary operator '#<sc_t>' has arity '#<sz_t>'. Expected: '2'.",
                    o.ifnameof( cell.name ),
                    cell.get_arity()
                );
            }

            if( cell.excs.size != 1 )
            {
                cell.source_point.parse_error_fa
                (
                    "Binary operator '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                    o.ifnameof( cell.name ),
                    cell.excs.size
                );
            }

            stack.push( arg1 );
            stack.push( flag_bin_op );
            stack.push( cell );
            stack.push( cell.excs.[ 0 ] );
        }

        // cell-catenation
        if( stack.size() >= 3 && stack.is_of_value( 2, flag_cell_cat ) )
        {
            if( stack.is_of_type( 1, :cell_s~ ) )  // cell1 : cell2
            {
                m :cell_s* cell2 = stack.pop_cell( source );
                stack.pop_of_value( flag_cell_cat, source );
                m :cell_s* cell1 = stack.pop_cell( source );
                stack.push( o.recat_cell( cell1, cell2, source ) );
            }
            else if( stack.is_of_type( 1, :link_s~ ) ) // cell : link
            {
                m :link_s* link = stack.pop_link( source );
                stack.pop_of_value( flag_cell_cat, source );
                m :cell_s* cell = stack.pop_cell( source );
                cell = o.push_wrap_cell_soft( cell );
                if( cell.encs.size != 1 ) source.parse_error_fa( "Catenation 'Cell : Link': Cell has #<sz_t> free entry channels; required is 1", cell.encs.size );
                cell.encs.[ 0 ].up = link;
                stack.push( cell );
            }
            else
            {
                source.parse_error_fa( "Cannot resolve catenation." );
            }
        }

        // order incrementations (loop because multiple [] can be next to each other)
        while( stack.is_of_value( 2, flag_inc_order ) && stack.is_of_type( 1, :link_s~ ) )
        {
            m :link_s* link2 = stack.pop_link( source );
            stack.pop_of_value( flag_inc_order, source );
            m :cell_s* cell  = stack.pop_cell( source );
            ASSERT( cell.encs.[ 0 ].up ); // was set at cell creation
            cell.encs.[ 1 ].up = link2;
            stack.push( cell.excs.[ 0 ] );
        }
    }

    /// remaining stack processing ...

    /// Binary operators
    while( stack.size() >= 5 && stack.is_of_value( 4, flag_bin_op ) ) // <left arg> <flag> <bin-operator> <output> <right arg>
    {
        m :link_s* link2 = stack.pop_link_or_exit( source );
        m :link_s* out   = stack.pop_link( source );
        m :cell_s* cell  = stack.pop_cell( source );
        stack.pop_of_value( flag_bin_op, source );
        m :link_s* link1 = stack.pop_link_or_exit( source );

        if( stack.size() >= 4 && stack.is_of_value( 3, flag_bin_op ) ) // merge with prior operation considering priority
        {
            m :link_s* prior_out   = stack.pop_link( source );
            m :cell_s* prior_cell  = stack.pop_cell( source );
            stack.pop_of_value( flag_bin_op, source );
            m :link_s* prior_link1 = stack.pop_link_or_exit( source );

            sz_t prior_priority = prior_cell.get_priority();
            sz_t cell_priority  = cell.get_priority();

            /// on equality: odd priority yields
            bl_t yield = ( prior_priority < cell_priority )
                           || ( ( prior_priority == cell_priority ) && ( ( prior_priority & 1 ) == 1 ) );

            if( yield )
            {
                cell.get_enc_by_open().up = link1;
                cell.get_enc_by_open().up = link2;

                stack.push( prior_link1 );
                stack.push( flag_bin_op );
                stack.push( prior_cell );
                stack.push( prior_out );
                stack.push( out );           // out becomes right argument for prior_cell
            }
            else
            {
                cell.get_enc_by_open().up = prior_out;
                cell.get_enc_by_open().up = link2;

                stack.push( prior_link1 );
                stack.push( flag_bin_op );
                stack.push( prior_cell );
                stack.push( out );
                stack.push( link1 );
            }
        }
        else // fully resolve operation
        {
            cell.get_enc_by_open().up = link1;
            cell.get_enc_by_open().up = link2;
            stack.push( out );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) evaluate_sem_stack
{
    o.evaluate_stack( stack, source );
    if( stack.size() != 1 ) source.parse_error_fa( "Expression syntax error." );
    return stack.pop();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) evaluate_sem
{
    return o.evaluate_sem_stack( :stack_s!^, source );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) evaluate_link_stack
{
    m :* ret = o.evaluate_sem_stack( stack, source );
    if( ret._ == :cell_s~ )
    {
        m :cell_s* cell = ret.cast( m :cell_s* );
        if( cell.get_arity() > 0 ) source.parse_error_fa( "Automatic exit channel selection on cell with #<sz_t> open entry channels.", cell.get_arity() );
        if( cell.excs.size != 1 ) source.parse_error_fa( "Automatic exit channel selection on cell with #<sz_t> exit channels.", cell.excs.size );
        ret = cell.excs.[ 0 ];
    }

    if( ret._ != :link_s~ ) source.parse_error_fa( "Expression yields #<sc_t>. Link expected.", ifnameof( ret._ ) );
    return ret.cast( m :link_s* );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) evaluate_link
{
    return o.evaluate_link_stack( :stack_s!^, source );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) evaluate_cell_stack
{
    m :* ret = o.evaluate_sem_stack( stack, source );
    if( ret._ != :cell_s~ )
    {
        source.parse_error_fa( "Expression yields #<sc_t>. Cell Expected.", ifnameof( ret._ ) );
    }
    return ret.cast( m :cell_s* );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) evaluate_cell
{
    return o.evaluate_cell_stack( :stack_s!^, source );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :builder_s

// ---------------------------------------------------------------------------------------------------------------------

func (:builder_s) :.build_from_source
{
    m ::cell_s* root_cell = cell;
    o.context =< ::context_s!;

    /** Triple-nested semantic cell-frame:
     *  Level 0: context level: contains all global operators
     *  Level 1: frame level  : holds operators defined outside the root cell
     *  Level 2: root level   : represents the root cell defined in source
     */

    o.context_cell =< ::context_s_create_cell( o.context );
    o.frame_cell   =< ::context_s_create_cell( o.context );

    o.context.setup_cell( root_cell );
    o.context.setup( o.context_cell );

    o.context_cell.set_name_invisible( o.context.entypeof( "$CX" ) );
    o.frame_cell  .set_name_invisible( o.context.entypeof( "$CF" ) );

    o.frame_cell.parent = o.context_cell;
      root_cell .parent = o.frame_cell;

    o.frame_cell.source_point.setup_from_source( source );
       root_cell.source_point.setup_from_source( source );

    source.parse_fa( " #-?'cell'" ); // leading 'cell' keyword is optional
    root_cell.parse( source );

    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :tree

// ---------------------------------------------------------------------------------------------------------------------

/** Node process for a semantic cell.
 *
 *  Entering a cell:
 *    Ascend the tree if matching or add a new node to the tree.
 *    node_out is set to the node referencing the cell
 *
 *  Exiting a cell:
 *     Descend the tree until a matching node is found.
 *     node_out is set to the parent of the node referencing the cell.
 *     Returns 1 in case no match is found.
 *
 *  Enter/Exit functions return 0 in case of success. !=0 is considered an error
 */

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_node_s) (er_t enter( m @* o, m ::cell_s* cell, m :node_s.2 node_out ))
{
    m :node_s* node = NULL;
    foreach( m :node_s* e in o ) node = ( e.cell == cell ) ? e : node;

    if( !node )
    {
        node = o.push();
        node.cell = cell;
        node.parent = o;
    }
    node_out.1 = node;
    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_node_s) (er_t exit( m @* o, m ::cell_s* cell, bl_t test_for_wrapper, m :node_s.2 node_out ))
{
    m :node_s* node = o;

    /** Descend tree until node.cell == cell.
      * This part covers specific (rare) situations in which a link exits a cell without passing through its membrane
      * It is unclear if this handling is sensitive. Probably all relevant cases are covered using test_for_wrapper
      * scheme.
      */
    while( node && node.cell != cell ) node = node.parent;

    if( node && node.cell == cell )
    {
        node = node.parent;
        while( test_for_wrapper && node && node.cell.is_wrapper() ) node = node.parent;
        node_out.1 = node;
        return 0;
    }
    else
    {
        return general_error~; // exiting from untraced cell
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_node_s) (m x_source_point_s* get_nearest_source_point( m @* o ))
{
    if( !o || !o.cell ) return NULL;
    return o.cell.source_point.ifd( o.cell.source_point.source, o.parent.get_nearest_source_point() );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_s) :.enter
{
    if( !o.root )
    {
        o.root!.id = o.id_base++;
        o.root.cell = cell;
        node_out.1 = o.root;
    }
    else if( node_in )
    {
        node_in.enter( cell, node_out ).try();
        if( node_out.1.id < 0 ) node_out.1.id = o.id_base++;
    }
    else // we just entered the tree frame
    {
        node_out.1 = o.root;
    }
    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

