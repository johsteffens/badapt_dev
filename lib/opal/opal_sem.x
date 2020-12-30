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
/// :context_s

// ---------------------------------------------------------------------------------------------------------------------

func (:context_s) (tp_t parse_op2_symbol( const, bcore_source* source )) =
{
    const bcore_arr_st_s* arr = o.arr_symbol_op2;

    st_s* format = st_s!^;
    tp_t ret = 0;

    source.parse_fa( " " );
    for( sz_t i = 0; i < arr.size; i++ )
    {
        format.copy_fa( "##?'#<sc_t>'", arr.[ i ].sc );
        if( source.parse_bl( format.sc ) )
        {
            ret = typeof( arr.[ i ].sc );
            break;
        }
    }

    return ret;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:context_s) :.setup =
{
    bcore_arr_tp_s* arr_tp = bcore_arr_tp_s!^;

    bcore_push_traits_of_ancestor( TYPEOF_opal_nop_ar1, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_opal_nop_ar2, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_opal_nop_ar3, arr_tp );

    for( sz_t i = 0; i < arr_tp.size; i++ )
    {
        opal_nop* nop = opal_nop_t_create( arr_tp.[ i ] );
        sc_t symbol   = nop.symbol();

        // bcore_msg_fa( "#<sc_t>\n", symbol );
        if( symbol )
        {
            sz_t arity = nop.arity();
            o.hmap_name.set_sc( symbol );
            if( arity == 2 ) o.arr_symbol_op2.push_sc( symbol );
            ::cell_s* cell = frame.push_cell_nop_d( nop );
            cell.set_name_visible( typeof( symbol ) );

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

func (:link_s* link_s_create_setup( tp_t name, :link_s* up, :link_s* dn, :cell_s* cell, bl_t exit )) =
{
    :link_s* o = :link_s!;
    o.set_name_visible( name );
    o.up = up;
    o.dn = dn;
    o.cell = cell;
    o.exit = exit;
    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next membrane; returns NULL in case trace ends in open link
func (:link_s) (@* trace_to_cell_membrane( mutable )) =
{
    if( !o || o.cell ) return o;
    return o.up.trace_to_cell_membrane();
};

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next cell; returns NULL in case trace ends in open link
func (:link_s) (:cell_s* trace_to_cell( mutable )) =
{
    :link_s* link = o.trace_to_cell_membrane();
    if( link )
    {
        if( link.cell ) assert( link.cell._ == TYPEOF_:cell_s );
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

func (:cell_s) (void set_channels( mutable, sz_t excs, sz_t encs )) =
{
    o.excs.set_size( excs );
    o.encs.set_size( encs );
    foreach( :link_s.2 link in o.excs ) link.1 = :link_s_create_setup( 0, NULL, NULL, o, true );
    foreach( :link_s.2 link in o.encs ) link.1 = :link_s_create_setup( 0, NULL, NULL, o, false );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Adds a wrapping membrane only exposing unspecified entry links.
  * links of src are not modified; returns o
  */
func (:cell_s) (@* wrap_cell_soft( mutable, @* src )) =
{
    ASSERT( !o.body );
    ASSERT( !o.nop  );
    ASSERT( !o.wrapped_cell );

    o.wrapped_cell = src;
    o.priority = src.priority;
    o.encs.set_size( src.get_arity() );
    o.excs.set_size( src.excs.size );

    sz_t k = 0;

    foreach( :link_s* link in src.encs )
    {
        if( !link.up ) o.encs.[ k++ ] = :link_s_create_setup( link.name, NULL, link, o, false );
    }

    assert( k == o.encs.size );

    foreach( :link_s* link in src.excs )
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
func (:cell_s) (@* wrap_cell_hard( mutable, :cell_s* src )) =
{
    ASSERT( !o.body );
    ASSERT( !o.nop  );
    ASSERT( !o.wrapped_cell );

    o.wrapped_cell = src;
    o.priority = src.priority;
    o.encs.set_size( src.encs.size );
    o.excs.set_size( src.excs.size );

    foreach( :link_s.2 link in src.encs )
    {
        o.encs.[ __i ] = :link_s_create_setup( link.1.name, link.1.up, link.1, o, false );
        link.1.up = NULL;
    }

    foreach( :link_s.2 link in src.excs )
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
func (:cell_s) (@* rewrap_cell_soft( mutable, :cell_s* src )) =
{
    ASSERT( !o.body );
    ASSERT( !o.nop  );
    ASSERT( !o.wrapped_cell );

    :cell_s* root = src;
    while( root.wrapped_cell ) root = root.wrapped_cell;
    o.wrap_cell_soft( root );

    :cell_s* wrap = src;
    while( wrap.wrapped_cell )
    {
        foreach( :link_s* wrap_link in wrap.encs ) if( wrap_link.up )
        {
            :link_s* root_link = wrap_link;
            while( root_link.cell != root && root_link.dn ) root_link = root_link.dn;
            ASSERT( root_link.cell == root );

            foreach( :link_s* link in o.encs ) if( link.dn == root_link )
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
func (:cell_s) (@* push_cell_nop_d( mutable, opal_nop* nop )) =
{
    @* cell = o.push_cell();
    cell.set_channels( 1, nop.arity() );
    sc_t symbol = nop.symbol();
    if( symbol ) cell.set_name_visible( o.entypeof( symbol ) );
    cell.nop = nop;
    cell.priority = nop.priority();
    cell.excs.[ 0 ].set_name_visible( o.entypeof( "y" ) );
    foreach( :link_s* link in cell.encs ) if( __i < 'y' - 'a' ) link.set_name_visible( o.entypeof_fa( "#<char>", 'a' + __i ) );
    return cell;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (@* push_cell_const_scalar( mutable, tp_t type, f3_t v )) =
{
    opal_nop_ar0_literal_s* literal = opal_nop_ar0_literal_s!;
    literal.h = opal_holor_s!;
    literal.h.h.set_type_scalar( type, v );
    literal.h.m.active = false;
    return o.push_cell_nop_d_invisible( literal );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void assert_identifier_not_yet_defined( const, tp_t name, bcore_source* source )) =
{
    if( o.encs.name_exists( name ) || ( o.body && o.body.name_exists( name ) ) )
    {
        source.parse_err_fa( "Identifier '#<sc_t>' already exists.", o.ifnameof( name ) );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/// parses ( ... <- ... )
func (:cell_s) (void parse_signature( mutable, bcore_source* source )) =
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
            :link_s* link = :link_s_create_setup( o.parse_var_name( source ), NULL, NULL, o, false );
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

func (:cell_s) (void parse( mutable, bcore_source* source )) =
{
    :cell_s* frame = o.parent;

    // cell signature without name is allowed
    if( !source.parse_bl( " #=?'('" ) )
    {
        tp_t tp_cell_name = o.parse_var_name( source );
        if( frame ) frame.assert_identifier_not_yet_defined( tp_cell_name, source );
        o.set_name_visible( tp_cell_name );
    }

    o.source_point.set( source );

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

func (:cell_s) (st_s* create_signature( const )) =
{
    st_s* s = st_s!;
    s.push_fa( "(" );
    foreach( :link_s* link in o.excs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", __i > 0 ? "," : "", o.ifnameof( link.name ) );
    s.push_fa( "<-" );
    foreach( :link_s* link in o.encs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", __i > 0 ? "," : "", o.ifnameof( link.name ) );
    s.push_fa( ")" );
    return s;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void parse_verify_signature( const, bcore_source* source )) =
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
            st_s* sig =  o.create_signature().scope( scope_local );
            source.parse_err_fa( "Cell signature is '#<sc_t>'", sig.sc );
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
            st_s* sig = o.create_signature().scope( scope_local );
            source.parse_err_fa( "Cell signature is '#<sc_t>'", sig.sc );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void parse_body( mutable, bcore_source* source )) =
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
            :link_s* link = o.push_link();
            o.assert_identifier_not_yet_defined( tp_name, source );
            link.set_name_visible( tp_name );
            :cell_s* cell = o.push_cell_nop_d_invisible_set_source( opal_nop_ar1_param_s!, source );
            cell.set_name_invisible( tp_name );
            source.parse_fa( " =" );
            cell.encs.[ 0 ].up = o.evaluate_link( source );
            link.up = cell.excs.[ 0 ];
        }
        else if( source.parse_bl( " #?'adaptive'" ) ) // defining a link to an adaptive operator
        {
            tp_t tp_name = o.parse_var_name( source );
            :link_s* link = o.push_link();
            o.assert_identifier_not_yet_defined( tp_name, source );
            link.set_name_visible( tp_name );
            opal_nop_ar1_adaptive_s* nop_adaptive = opal_nop_ar1_adaptive_s!;
            nop_adaptive.name = tp_name;
            :cell_s* cell = o.push_cell_nop_d_invisible_set_source( nop_adaptive, source );
            cell.set_name_invisible( tp_name );
            source.parse_fa( " =" );
            cell.encs.[ 0 ].up = o.evaluate_link( source );
            link.up = cell.excs.[ 0 ];
        }
        else if( source.parse_bl( " #?'cyclic'" ) ) // A link is defined as cyclic by attaching cyclic operator with open input channel
        {
            tp_t tp_name = o.parse_var_name( source );
            :link_s* link = o.push_link();
            o.assert_identifier_not_yet_defined( tp_name, source );
            link.set_name_visible( tp_name );
            opal_nop_ar2_cyclic_s* nop_cyclic = opal_nop_ar2_cyclic_s!;
            nop_cyclic.name = tp_name;
            :cell_s* cell = o.push_cell_nop_d_invisible_set_source( nop_cyclic, source );
            cell.set_name_invisible( tp_name );
            source.parse_fa( " =" );
            cell.encs.[ 0 ].up = o.evaluate_link( source );
            link.up = cell.excs.[ 0 ];
        }
        else // identifier
        {
            tp_t tp_name = o.parse_var_name( source );
            :* item = NULL;

            if( ( item = o.get_exc_by_name( tp_name ) ) ) // identifier is exit channel of o
            {
                :link_s* link = item.cast( :link_s* );
                if( link.up )
                {
                    source.parse_err_fa
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
                :link_s* link = item.cast( :link_s* );

                // Idle links should never occur. If they do, there is probably a bug in the opal-compiler.
                if( !link.up      ) source.parse_err_fa( "Link '#<sc_t>' is idle.", o.ifnameof( tp_name ) );
                if( !link.up.cell ) source.parse_err_fa( "Link '#<sc_t>' has already been defined.", o.ifnameof( tp_name ) );
                :cell_s* cell = link.up.cell;

                if( cell.nop && cell.nop._ == TYPEOF_opal_nop_ar2_cyclic_s )
                {
                    if( !cell.encs.[ 1 ].up )
                    {
                        source.parse_fa( " =" );
                        cell.encs.[ 1 ].up = o.evaluate_link( source );
                        link.protected = true;
                    }
                    else
                    {
                        source.parse_err_fa( "Redefining a cyclic link '#<sc_t>'.", o.ifnameof( tp_name ) );
                    }
                }
                else
                {
                    source.parse_err_fa( "Link '#<sc_t>' has already been defined.", o.ifnameof( tp_name ) );
                }
            }
            else // unknown identifier -. creates a link
            {
                :link_s* link = o.push_link();
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

func (:cell_s) (void evaluate_set_encs( mutable, :cell_s* parent, bcore_source* source )) =
{
    :stack_s* stack = :stack_s!^;
    st_s* name = st_s!^;

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
                :link_s* link = o.get_enc_by_name( typeof( name.sc ) );
                if( !link )
                {
                    source.parse_err_fa
                    (
                        "'#<sc_t>' specifies no entry channel of cell '#<sc_t>'.",
                        name.sc,
                        o.ifnameof( o.name )
                    );
                }

                if( link.up )
                {
                    source.parse_err_fa
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
            :link_s* link =  o.get_enc_by_open();
            if( !link )
            {
                source.parse_err_fa
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
func (:cell_s) (:cell_s* recat_cell( mutable, :cell_s* c1, :cell_s* c2, bcore_source* source )) =
{
    :cell_s* cell = o.push_cell();
    cell.source_point.set( source );

    c1 = cell.push_rewrap_cell_soft( c1 );
    c2 = cell.push_rewrap_cell_soft( c2 );

    c1.set_name_invisible( o.entypeof( "$CAT1" ) );
    c2.set_name_invisible( o.entypeof( "$CAT2" ) );

    sz_t arity_c1 = c1.get_arity();

    /// free input channels of n1 must match output channels of n2
    if( arity_c1 != c2.excs.size )
    {
        cell.source_point.parse_err_fa
        (
            "Catenating cells: Number of left cell's open entry channels (#<sz_t>) differs from right cells's exit channels (#<sz_t>).",
            arity_c1,
            c2.excs.size
        );
    }

    /// channels of wrapping cell
    cell.set_channels( c1.excs.size, c2.encs.size + c1.encs.size - arity_c1 );

    foreach( :link_s* c2_link in c2.encs )
    {
        :link_s* c0_link = cell.encs.[ __i ];
        c0_link.set_name_visible( c2_link.name );
        c0_link.up = c2_link.up;
        c2_link.up = c0_link;
    }



    sz_t l = 0;
    sz_t k = c2.encs.size;
    foreach( :link_s* c1_link in c1.encs )
    {
        if( c1_link.up )
        {
            assert( k < cell.encs.size );
            :link_s* c0_link = cell.encs.[ k++ ];
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

    foreach( :link_s* c1_link in c1.excs )
    {
        :link_s* c0_link = cell.excs.[ __i ];
        c0_link.up = c1_link;
        c0_link.set_name_visible( c1_link.name );
    }

    /// the last soft-wrap is convenience (consider changing dependent code using arity rather then encs.size to determine open links)
    return o.push_wrap_cell_soft( o.push_wrap_cell_hard( cell ) );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void evaluate_stack( mutable, :stack_s* stack, bcore_source* source )) =
{
    st_s* name = st_s!^;

    $* flag_bin_op    = :stack_flag_s!^;
    $* flag_una_op    = :stack_flag_s!^;
    $* flag_cell_cat  = :stack_flag_s!^;
    $* flag_inc_order = :stack_flag_s!^;

    tp_t op2_symbol = 0;

    while( !source.eos() )
    {
        bl_t identifier = false;

        // identifier
        if( stack.is_of_type( 1, TYPEOF_st_s ) )
        {
            name.copy( stack.pop().cast( st_s* ) );
            identifier = true;
        }
        else if( source.parse_bl( " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            source.parse_fa( "#name", name );
            identifier = true;
        }

        if( identifier )
        {
            tp_t tp_name = typeof( name.sc );

            if( o.is_control_type( tp_name ) )
            {
                if( tp_name == TYPEOF_cell ) // inline cell definition
                {
                    :cell_s* cell = o.push_cell();
                    cell.parse( source );
                    stack.push( cell );
                }
                else
                {
                    source.parse_err_fa( "Unexpected keyword '#<sc_t>'. Did you miss ';' after previous statement?", name.sc );
                }
            }
            else
            {
                :* item = o.get_enc_by_name( tp_name );
                if( !item && o.body   ) item = o.body.get_sem_by_name( tp_name );
                if( !item && o.parent ) item = o.parent.get_cell_by_name( tp_name );
                if( !item )
                {
                    item = o.get_exc_by_name( tp_name );
                    if( item )
                    {
                        assert( item._ == TYPEOF_:link_s );
                        :link_s* link = item.cast( :link_s* );
                        if( !link.up )
                        {
                            source.parse_err_fa( "Use of exit channel '#<sc_t>' before it was defined.", name.sc );
                        }
                        item = link.up;
                    }
                    else
                    {
                        source.parse_err_fa( "Cannot evaluate identifier '#<sc_t>'.", name.sc );
                    }
                }

                tp_t tp_item = item._;

                switch( tp_item )
                {
                    case TYPEOF_:cell_s:
                    {
                        stack.push( item.cast( :cell_s* ) );
                    }
                    break;

                    case TYPEOF_:link_s:
                    {
                        :link_s* link = item.cast( :link_s* );
                        if( link.protected )
                        {
                            if( link.up && link.up.cell )
                            {
                                :cell_s* cell = link.up.cell;
                                if( cell.nop && cell.nop._ == TYPEOF_opal_nop_ar2_cyclic_s )
                                {
                                    source.parse_err_fa( "Recurrent node '#<sc_t>' must not be used after updating.", name.sc );
                                }
                            }
                            else
                            {
                                source.parse_err_fa( "Identifier '#<sc_t>' is protected (unusable) at this point.", name.sc );
                            }
                        }
                        stack.push( item );
                    }
                    break;

                    default:
                    {
                        source.parse_err_fa( "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name.sc, ifnameof( tp_item ) );
                    }
                    break;
                }
            }
        }

        // literal scalar (negative numbers are created via neg operator)
        else if( source.parse_bl( " #?([0]>='0'&&[0]<='9')" ) )
        {
            f3_t val = 0;
            tp_t type = TYPEOF_f3_t;
            source.parse_fa( " #<f3_t*>", &val );
            if(      source.parse_bl( "#?'f2'" ) ) type = TYPEOF_f2_t;
            else if( source.parse_bl( "#?'f3'" ) ) type = TYPEOF_f3_t;
            :cell_s* cell = o.push_cell_const_scalar( type, val );
            cell.source_point.set( source );
            stack.push( cell.excs.data[ 0 ] );
        }

        // undetermined scalar (falls back to 0)
        else if( source.parse_bl( " #?'#'" ) )
        {
            tp_t type = TYPEOF_f3_t;
            if(      source.parse_bl( "#?'f2'" ) ) type = TYPEOF_f2_t;
            else if( source.parse_bl( "#?'f3'" ) ) type = TYPEOF_f3_t;
            :cell_s* cell = o.push_cell_const_scalar( type, 0 );
            cell.source_point.set( source );
            stack.push( cell.excs.data[ 0 ] );
        }

        // block or input channel selection in case l-value is a cell
        else if( source.parse_bl( " #=?'('" ) )
        {
            if( stack.is_of_type( 1, TYPEOF_:cell_s ) )
            {
                :cell_s* cell = o.push_wrap_cell_set_source( stack.pop().cast( :cell_s* ), source );
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
            if( stack.is_of_type( 1, TYPEOF_:cell_s ) )
            {
                stack.push( flag_cell_cat );
            }
            else
            {
                source.parse_err_fa( "Cell catenation '<:': l-value is not a cell." );
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
                :cell_s* cell = o.get_cell_by_name( op2_symbol );
                opal_nop* nop_unary = cell.nop.create_op_of_arn( 1 );
                if( nop_unary )
                {
                    :cell_s* cell = o.push_cell_nop_d_invisible_set_source( nop_unary, source );
                    stack.push( cell );
                    stack.push( flag_una_op ); // flag after cell to avoid incorrect stack evaluation
                }
                else
                {
                    if( stack.size() == 0 )
                    {
                        source.parse_err_fa
                        (
                            "Operator '#<sc_t>': Left operand missing.",
                            o.ifnameof( op2_symbol )
                        );
                    }
                    else
                    {
                        source.parse_err_fa
                        (
                            "Operator '#<sc_t>': This is a successive binary operator. Right operand expected instead.",
                            o.ifnameof( op2_symbol )
                        );
                    }
                }
            }
            else // else of: if( binary op not applicable):
            {
                :cell_s* cell = o.get_cell_by_name( op2_symbol );
                if( !cell ) source.parse_err_fa( "Syntax error." );

                cell = o.push_wrap_cell_set_source( cell, source );

                stack.push( flag_bin_op );
                stack.push( cell );
            }
        }

        // custom binary operator
        else if( source.parse_bl( " #?'<<'" ) )
        {
            source.parse_fa( "#until'>'>>", name );
            if( stack.size() == 0 ) source.parse_err_fa( "Operator '#<sc_t>': Left operand missing.", name.sc );
            :cell_s* cell = o.get_cell_by_name( typeof( name.sc ) );
            if( !cell ) source.parse_err_fa( "Cell '#<sc_t>' not found.", name.sc );
            cell = o.push_wrap_cell_set_source( cell, source );
            stack.push( flag_bin_op );
            stack.push( cell );
        }

        // output channel selection
        else if( source.parse_bl( " #?'.'" ) )
        {
            source.parse_fa( "#name", name );
            if( name.size == 0 ) source.parse_err_fa( "Identifier expected." );

            if( !stack.is_of_type( 1, TYPEOF_:cell_s ) )
            {
                source.parse_err_fa( "Output channel selection on non-cell." );
            }

            :cell_s* cell = stack.pop().cast( :cell_s* );
            :link_s* link = cell.get_exc_by_name( typeof( name.sc ) );

            if( cell.get_arity() > 0 )
            {
                source.parse_err_fa
                (
                    "Output channel selection on cell '#<sc_t>' with #<sz_t> open input channels.",
                    o.ifnameof( cell.name ),
                    cell.get_arity()
                );
            }

            if( !link )
            {
                source.parse_err_fa
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
            :cell_s* htp_cell = o.push_cell_nop_d_invisible_set_source( opal_nop_ar1_cast_htp_s!, source );
            if( stack.is_of_type( 1, TYPEOF_:link_s ) )
            {
                htp_cell.encs.[ 0 ].up = stack.pop_link( source );
                stack.push( htp_cell.excs.[ 0 ] );
            }
            else if( stack.is_of_type( 1, TYPEOF_:cell_s ) )
            {
                :cell_s* r_cell = stack.pop_cell( source );
                stack.push( htp_cell );
                stack.push( flag_cell_cat );
                stack.push( r_cell );
            }
            else
            {
                source.parse_err_fa( "transposition '~': invalid l-value." );
            }
        }

        // single char terminator
        else if( source.parse_bl( " #?([0]==')'||[0]==']'||[0]==','||[0]==';')" ) )
        {
            break;
        }

        else
        {
            source.parse_err_fa( "Syntax error." );
        }

        /// priority stack processing ...

        // unary operator: right operand
        while( stack.size() >= 3 && stack.is_of_value( 2, flag_una_op ) && stack.is_of_type( 1, TYPEOF_:link_s ) )
        {
            :link_s* link = stack.pop_link( source );
            stack.pop_of_value( flag_una_op, source );
            :cell_s* cell = stack.pop_cell( source );
            ASSERT( cell.encs.size == 1 );
            cell.encs.[ 0 ].up = link;
            stack.push( cell.excs.[ 0 ] );
        }

        if( stack.size() >= 3 && stack.is_of_value( 2, flag_bin_op ) )
        {
            :cell_s* cell = stack.pop_cell( source );
            stack.pop_of_value( flag_bin_op, source );
            opal_sem* arg1 = stack.pop();

            if( arg1._ == TYPEOF_:cell_s )
            {
                :cell_s* cell1 = arg1.cast( :cell_s* );
                if( cell1.excs.size != 1 )
                {
                    cell1.source_point.parse_err_fa
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
                cell.source_point.parse_err_fa
                (
                    "Binary operator '#<sc_t>' has arity '#<sz_t>'. Expected: '2'.",
                    o.ifnameof( cell.name ),
                    cell.get_arity()
                );
            }

            if( cell.excs.size != 1 )
            {
                cell.source_point.parse_err_fa
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
            if( stack.is_of_type( 1, TYPEOF_:cell_s ) )  // cell1 : cell2
            {
                :cell_s* cell2 = stack.pop_cell( source );
                stack.pop_of_value( flag_cell_cat, source );
                :cell_s* cell1 = stack.pop_cell( source );
                stack.push( o.recat_cell( cell1, cell2, source ) );
            }
            else if( stack.is_of_type( 1, TYPEOF_:link_s ) ) // cell : link
            {
                :link_s* link = stack.pop_link( source );
                stack.pop_of_value( flag_cell_cat, source );
                :cell_s* cell = stack.pop_cell( source );
                cell = o.push_wrap_cell_soft( cell );
                if( cell.encs.size != 1 ) source.parse_err_fa( "Catenation 'Cell : Link': Cell has #<sz_t> free entry channels; required is 1", cell.encs.size );
                cell.encs.[ 0 ].up = link;
                stack.push( cell );
            }
            else
            {
                source.parse_err_fa( "Cannot resolve catenation." );
            }
        }

        // order incrementations (loop because multiple [] can be next to each other)
        while( stack.is_of_value( 2, flag_inc_order ) && stack.is_of_type( 1, TYPEOF_:link_s ) )
        {
            :link_s* link2 = stack.pop_link( source );
            stack.pop_of_value( flag_inc_order, source );
            :cell_s* cell  = stack.pop_cell( source );
            ASSERT( cell.encs.[ 0 ].up ); // was set at cell creation
            cell.encs.[ 1 ].up = link2;
            stack.push( cell.excs.[ 0 ] );
        }
    }

    /// remaining stack processing ...

    /// Binary operators
    while( stack.size() >= 5 && stack.is_of_value( 4, flag_bin_op ) ) // <left arg> <flag> <bin-operator> <output> <right arg>
    {
        :link_s* link2 = stack.pop_link_or_exit( source );
        :link_s* out   = stack.pop_link( source );
        :cell_s* cell  = stack.pop_cell( source );
        stack.pop_of_value( flag_bin_op, source );
        :link_s* link1 = stack.pop_link_or_exit( source );

        if( stack.size() >= 4 && stack.is_of_value( 3, flag_bin_op ) ) // merge with prior operation considering priority
        {
            :link_s* prior_out   = stack.pop_link( source );
            :cell_s* prior_cell  = stack.pop_cell( source );
            stack.pop_of_value( flag_bin_op, source );
            :link_s* prior_link1 = stack.pop_link_or_exit( source );

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

func (:cell_s) (:* evaluate_sem_stack( mutable, :stack_s* stack, bcore_source* source )) =
{
    o.evaluate_stack( stack, source );
    if( stack.size() != 1 ) source.parse_err_fa( "Expression syntax error." );
    return stack.pop();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (:* evaluate_sem( mutable, bcore_source* source )) =
{
    return o.evaluate_sem_stack( :stack_s!^, source );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (:link_s* evaluate_link_stack( mutable, :stack_s* stack, bcore_source* source )) =
{
    :* ret = o.evaluate_sem_stack( stack, source );
    if( ret._ == TYPEOF_:cell_s )
    {
        :cell_s* cell = ret.cast( :cell_s* );
        if( cell.get_arity() > 0 ) source.parse_err_fa( "Automatic exit channel selection on cell with #<sz_t> open entry channels.", cell.get_arity() );
        if( cell.excs.size != 1 ) source.parse_err_fa( "Automatic exit channel selection on cell with #<sz_t> exit channels.", cell.excs.size );
        ret = cell.excs.[ 0 ];
    }

    if( ret._ != TYPEOF_:link_s ) source.parse_err_fa( "Expression yields #<sc_t>. Link expected.", ifnameof( ret._ ) );
    return ret.cast( :link_s* );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (:link_s* evaluate_link( mutable, bcore_source* source )) =
{
    return o.evaluate_link_stack( :stack_s!^, source );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (:cell_s* evaluate_cell_stack( mutable, :stack_s* stack, bcore_source* source )) =
{
    :* ret = o.evaluate_sem_stack( stack, source );
    if( ret._ != TYPEOF_:cell_s )
    {
        source.parse_err_fa( "Expression yields #<sc_t>. Cell Expected.", ifnameof( ret._ ) );
    }
    return ret.cast( :cell_s* );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (:cell_s* evaluate_cell( mutable, bcore_source* source )) =
{
    return o.evaluate_cell_stack( :stack_s!^, source );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :builder_s

// ---------------------------------------------------------------------------------------------------------------------

func (:builder_s) :.build_from_source =
{
    ::cell_s* root_cell = cell;
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

    o.frame_cell.source_point.set( source );
       root_cell.source_point.set( source );

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

func (:tree_node_s) (er_t enter( mutable, ::cell_s* cell, :node_s.2 node_out )) =
{
    :node_s* node = NULL;
    foreach( :node_s* e in o ) node = ( e.cell == cell ) ? e : node;

    if( !node )
    {
        node = o.push_d( :node_s! );
        node.cell = cell;
        node.parent = o;
    }
    node_out.1 = node;
    return 0;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_node_s) (er_t exit( mutable, ::cell_s* cell, bl_t test_for_wrapper, :node_s.2 node_out )) =
{
    :node_s* node = o;

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
        return TYPEOF_general_error; // exiting from untraced cell
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_node_s) (bcore_source_point_s* get_nearest_source_point( mutable )) =
{
    if( !o || !o.cell ) return NULL;
    return ( o.cell.source_point.source ) ? o.cell.source_point.1 : o.parent.get_nearest_source_point();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:tree_s) :.enter =
{
    if( !o.root )
    {
        o.root = :node_s!;
        o.root.id = o.id_base++;
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

