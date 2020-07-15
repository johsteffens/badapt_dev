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

#include "opal_sem.h"

/**********************************************************************************************************************/
/// Prototypes

// ---------------------------------------------------------------------------------------------------------------------
// sem_cell

void opal_sem_cell_s_create_args_out( opal_sem_cell_s* o, bcore_source* source );
void opal_sem_cell_s_create_args_in(  opal_sem_cell_s* o, opal_sem_cell_s* frame, bcore_source* source );
void opal_sem_cell_s_wrap_cell(       opal_sem_cell_s* o, opal_sem_cell_s* cell );

void             opal_sem_cell_s_parse(               opal_sem_cell_s* o,                        bcore_source* source );
void             opal_sem_cell_s_parse_body(          opal_sem_cell_s* o,                        bcore_source* source );
opal_sem*        opal_sem_cell_s_evaluate_sem(        opal_sem_cell_s* o,                        bcore_source* source );
opal_sem*        opal_sem_cell_s_evaluate_sem_stack(  opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
opal_sem_cell_s* opal_sem_cell_s_evaluate_cell(       opal_sem_cell_s* o,                        bcore_source* source );
opal_sem_cell_s* opal_sem_cell_s_evaluate_cell_stack( opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
opal_sem_link_s* opal_sem_cell_s_evaluate_link(       opal_sem_cell_s* o,                        bcore_source* source );
opal_sem_link_s* opal_sem_cell_s_evaluate_link_stack( opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
opal_sem_cell_s* opal_sem_cell_s_push_cell_nop_d(     opal_sem_cell_s* o,       opal_nop* nop );
opal_sem_cell_s* opal_sem_cell_s_push_cell_nop_d_reset_name( opal_sem_cell_s* o, opal_nop* nop );
void             opal_sem_cell_s_set_channels(        opal_sem_cell_s* o, sz_t excs, sz_t encs );

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// Context

// ---------------------------------------------------------------------------------------------------------------------

sc_t opal_sem_context_s_nameof( const opal_sem_context_s* o, tp_t name )
{
    return bcore_hmap_name_s_get_sc( &o->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t opal_sem_context_s_ifnameof( const opal_sem_context_s* o, tp_t name )
{
    sc_t sc = opal_sem_context_s_nameof( o, name );
    return sc ? sc : "";
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_typeof( const opal_sem_context_s* o, sc_t name )
{
    return btypeof( name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_entypeof( opal_sem_context_s* o, sc_t name )
{
    return bcore_hmap_name_s_set_sc( &o->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_entypeof_fv( opal_sem_context_s* o, sc_t format, va_list args )
{
    st_s* s = st_s_create_fv( format, args );
    tp_t tp = opal_sem_context_s_entypeof( o, s->sc );
    st_s_discard( s );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_entypeof_fa( opal_sem_context_s* o, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    tp_t tp = opal_sem_context_s_entypeof_fv( o, format, args );
    va_end( args );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_parse_name( opal_sem_context_s* o, bcore_source* source )
{
    st_s* name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", name );
    if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
    tp_t tp_name = opal_sem_context_s_entypeof( o, name->sc );
    st_s_discard( name );
    return tp_name;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_parse_op2_symbol( const opal_sem_context_s* o, bcore_source* source )
{
    const bcore_arr_st_s* arr = &o->arr_symbol_op2;

    st_s* format = st_s_create();
    tp_t ret = 0;

    bcore_source_a_parse_fa( source, " " );
    for( sz_t i = 0; i < arr->size; i++ )
    {
        st_s_copy_fa( format, "##?'#<sc_t>'", arr->data[ i ]->sc );
        if( bcore_source_a_parse_bl_fa( source, format->sc ) )
        {
            ret = typeof( arr->data[ i ]->sc );
            break;
        }
    }

    st_s_discard( format );

    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_sem_context_s_is_control_type( const opal_sem_context_s* o, tp_t name )
{
    return bcore_hmap_tp_s_exists( &o->control_types, name );
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_sem_context_s_is_reserved_name( const opal_sem_context_s* o, tp_t name )
{
    return bcore_hmap_tp_s_exists( &o->reserved_names, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_context_s_parse_var_name( opal_sem_context_s* o, bcore_source* source )
{
    tp_t name = opal_sem_context_s_parse_name( o, source );
    if( opal_sem_context_s_is_reserved_name( o, name ) )
    {
        bcore_source_a_parse_err_fa( source, "'#<sc_t>' is a reserved keyword. It may not be used as identifier at this point.", opal_sem_context_s_ifnameof( o, name ) );
    }

    return name;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_context_s_setup( opal_sem_context_s* o, opal_sem_cell_s* frame )
{
    BLM_INIT();
    bcore_arr_tp_s* arr_tp = BLM_CREATE( bcore_arr_tp_s );

    bcore_push_traits_of_ancestor( TYPEOF_opal_nop_ar1, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_opal_nop_ar2, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_opal_nop_ar3, arr_tp );

    for( sz_t i = 0; i < arr_tp->size; i++ )
    {
        opal_nop* nop = opal_nop_t_create( arr_tp->data[ i ] );
        sc_t symbol   = opal_nop_a_symbol( nop );

        // bcore_msg_fa( "#<sc_t>\n", symbol );
        if( symbol )
        {
            sz_t arity = opal_nop_a_arity( nop );
            bcore_hmap_name_s_set_sc( &o->hmap_name, symbol );
            switch( arity )
            {
                case 2: bcore_arr_st_s_push_sc( &o->arr_symbol_op2, symbol ); break;
                default: break;
            }
            opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d( frame, nop );
            cell->name = typeof( symbol );

            if( opal_nop_a_reserved( nop ) ) bcore_hmap_tp_s_set( &o->reserved_names, opal_sem_context_s_entypeof( o, symbol ) );
        }
        else
        {
            opal_nop_a_detach( &nop );
        }
    }

    /** We sort the array in descending manner; this ensures that short symbols
     *  which patterns match the beginning of a longer symbol can not occlude the longer one.
     */
    bcore_array_a_sort( (bcore_array*)&o->arr_symbol_op2, 0, -1, -1 );

    /// register control types
    bcore_hmap_tp_s_set( &o->control_types, opal_sem_context_s_entypeof( o, "cell" ) );

    /// register reserved keywords
    bcore_hmap_tp_s_set( &o->reserved_names, opal_sem_context_s_entypeof( o, "cell"     ) );
    bcore_hmap_tp_s_set( &o->reserved_names, opal_sem_context_s_entypeof( o, "cyclic"   ) );
    bcore_hmap_tp_s_set( &o->reserved_names, opal_sem_context_s_entypeof( o, "adaptive" ) );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// Cell-Context functions

// ---------------------------------------------------------------------------------------------------------------------

sc_t opal_sem_cell_s_nameof( const opal_sem_cell_s* o, tp_t name )
{
    return opal_sem_context_s_nameof( o->context, name );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t opal_sem_cell_s_ifnameof( const opal_sem_cell_s* o, tp_t name )
{
    return opal_sem_context_s_ifnameof( o->context, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_cell_s_entypeof( const opal_sem_cell_s* o, sc_t name )
{
     return opal_sem_context_s_entypeof( o->context, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_cell_s_entypeof_fv( const opal_sem_cell_s* o, sc_t format, va_list args )
{
    st_s* s = st_s_create_fv( format, args );
    tp_t tp = opal_sem_context_s_entypeof( o->context, s->sc );
    st_s_discard( s );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_cell_s_entypeof_fa( const opal_sem_cell_s* o, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    tp_t tp = opal_sem_cell_s_entypeof_fv( o, format, args );
    va_end( args );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_cell_s_parse_name( const opal_sem_cell_s* o, bcore_source* source )
{
    return opal_sem_context_s_parse_name( o->context, source );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_cell_s_parse_op2_symbol( const opal_sem_cell_s* o, bcore_source* source )
{
    return opal_sem_context_s_parse_op2_symbol( o->context, source );
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_sem_cell_s_is_control_type( const opal_sem_cell_s* o, tp_t name )
{
    return opal_sem_context_s_is_control_type( o->context, name );
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t opal_sem_cell_s_is_reserved_name( const opal_sem_cell_s* o, tp_t name )
{
    return opal_sem_context_s_is_reserved_name( o->context, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t opal_sem_cell_s_parse_var_name( const opal_sem_cell_s* o, bcore_source* source )
{
    return opal_sem_context_s_parse_var_name( o->context, source );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// stack

/*
 * Index values are in reverse array order from the stack-end;
 * idx == 1 means last array entry or top of stack.
 */

// ---------------------------------------------------------------------------------------------------------------------

static void stack_push( bcore_arr_vd_s* o, vd_t value )
{
    bcore_arr_vd_s_push( o, value );
}

// ---------------------------------------------------------------------------------------------------------------------

static vd_t stack_pop( bcore_arr_vd_s* o )
{
    return bcore_arr_vd_s_pop( o );
}

// ---------------------------------------------------------------------------------------------------------------------

static vd_t stack_pop_of_type( bcore_arr_vd_s* o, tp_t type, bcore_source* source )
{
    vd_t v = stack_pop( o );
    if( *( aware_t* )v == type ) return v;
    bcore_source_a_parse_err_fa( source, "Type error: '#<sc_t>' present but '#<sc_t>' expected.", ifnameof( *( aware_t* )v ), ifnameof( type ) );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

static vd_t stack_pop_of_value( bcore_arr_vd_s* o, vd_t value, bcore_source* source )
{
    vd_t v = stack_pop( o );
    if( v == value ) return v;
    bcore_source_a_parse_err_fa( source, "Internal error: Stack holds invalid value." );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

static bl_t stack_of_type( bcore_arr_vd_s* o, sz_t idx, tp_t type )
{
    if( idx <= 0 || idx > o->size ) return false;
    return *(aware_t*)o->data[ o->size - idx ] == type;
}

// ---------------------------------------------------------------------------------------------------------------------

static bl_t stack_of_value( bcore_arr_vd_s* o, sz_t idx, vd_t value )
{
    if( idx <= 0 || idx > o->size ) return false;
    return o->data[ o->size - idx ] == value;
}

// ---------------------------------------------------------------------------------------------------------------------

static opal_sem_link_s* stack_pop_link( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_opal_sem_link_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static opal_sem_cell_s* stack_pop_cell( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_opal_sem_cell_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static opal_sem_link_s* stack_pop_link_or_exit( bcore_arr_vd_s* o, bcore_source* source )
{
    vd_t v = stack_pop( o );
    tp_t t = *(aware_t*)v;
    if( t == TYPEOF_opal_sem_link_s ) return v;
    if( t == TYPEOF_opal_sem_cell_s )
    {
        opal_sem_cell_s* cell = v;
        if( cell->excs.size != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Cell has #<sz_t> exit channels. Require is 1.", cell->excs.size );
        }
        return cell->excs.data[ 0 ];
    }
    else
    {
        bcore_source_a_parse_err_fa( source, "Incorrect object on stack '#<sc_t>.", ifnameof( t ) );
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// Link

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_link_s* opal_sem_link_s_create_setup( tp_t name, opal_sem_link_s* up, opal_sem_link_s* dn, opal_sem_cell_s* cell, bl_t exit )
{
    opal_sem_link_s* o = opal_sem_link_s_create();
    o->name = name;
    o->up = up;
    o->dn = dn;
    o->cell = cell;
    o->exit = exit;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next membrane; returns NULL in case trace ends in open link
opal_sem_link_s* opal_sem_link_s_trace_to_cell_membrane( opal_sem_link_s* o )
{
    if( !o || o->cell ) return o;
    return opal_sem_link_s_trace_to_cell_membrane( o->up );
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next cell; returns NULL in case trace ends in open link
opal_sem_cell_s* opal_sem_link_s_trace_to_cell( opal_sem_link_s* o )
{
    opal_sem_link_s* link = opal_sem_link_s_trace_to_cell_membrane( o );
    if( link )
    {
        if( link->cell ) assert( *(aware_t*)link->cell == TYPEOF_opal_sem_cell_s );
        return link->cell;
    }
    else
    {
        return NULL;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// Cell

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_set_channels( opal_sem_cell_s* o, sz_t excs, sz_t encs )
{
    opal_sem_links_s_set_size( &o->excs, excs );
    opal_sem_links_s_set_size( &o->encs, encs );
    for( sz_t i = 0; i < excs; i++ )
    {
        o->excs.data[ i ] = opal_sem_link_s_create_setup( 0, NULL, NULL, o, true );
    }
    for( sz_t i = 0; i < encs; i++ )
    {
        o->encs.data[ i ] = opal_sem_link_s_create_setup( 0, NULL, NULL, o, false );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Adds a wrapping membrane only exposing unspecified entry links.
  * links of src are not modified
  */
void opal_sem_cell_s_wrap_cell_soft( opal_sem_cell_s* o, opal_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->nop  );
    ASSERT( !o->wrapped_cell );

    o->wrapped_cell = src;
    o->priority = src->priority;
    opal_sem_links_s_set_size( &o->encs, opal_sem_cell_s_get_arity( src ) );
    opal_sem_links_s_set_size( &o->excs, src->excs.size );

    sz_t k = 0;

    BFOR_EACH( i, &src->encs )
    {
        if( !src->encs.data[ i ]->up )
        {
            o->encs.data[ k++ ] = opal_sem_link_s_create_setup( src->encs.data[ i ]->name, NULL, src->encs.data[ i ], o, false );
        }
    }

    assert( k == o->encs.size );

    BFOR_EACH( i, &src->excs )
    {
        o->excs.data[ i ] = opal_sem_link_s_create_setup( src->excs.data[ i ]->name, src->excs.data[ i ], NULL, o, true );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Adds a wrapping membrane exposing all links of src.
  * Explicitly moves entry links of src to the wrapping membrane
  */
void opal_sem_cell_s_wrap_cell_hard( opal_sem_cell_s* o, opal_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->nop  );
    ASSERT( !o->wrapped_cell );

    o->wrapped_cell = src;
    o->priority = src->priority;
    opal_sem_links_s_set_size( &o->encs, src->encs.size );
    opal_sem_links_s_set_size( &o->excs, src->excs.size );

    BFOR_EACH( i, &o->encs )
    {
        o->encs.data[ i ] = opal_sem_link_s_create_setup( src->encs.data[ i ]->name, src->encs.data[ i ]->up, src->encs.data[ i ], o, false );
        src->encs.data[ i ]->up = NULL;
    }

    BFOR_EACH( i, &o->excs )
    {
        o->excs.data[ i ] = opal_sem_link_s_create_setup( src->excs.data[ i ]->name, src->excs.data[ i ], NULL, o, true );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Passes through all wrapping membranes of src to find first non-wrapper (root).
 *  Wraps root by moving all specified entries of intermediate wrappers to the outermost membrane.
 *  Does not (!) move specified links of the root cell.
 */
void opal_sem_cell_s_rewrap_cell_soft( opal_sem_cell_s* o, opal_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->nop  );
    ASSERT( !o->wrapped_cell );

    opal_sem_cell_s* root = src;
    while( root->wrapped_cell ) root = root->wrapped_cell;
    opal_sem_cell_s_wrap_cell_soft( o, root );

    opal_sem_cell_s* wrap = src;
    while( wrap->wrapped_cell )
    {
        BFOR_EACH( i, &wrap->encs )
        {
            opal_sem_link_s* wrap_link = wrap->encs.data[ i ];
            if( wrap_link->up )
            {
                opal_sem_link_s* root_link = wrap_link;
                while( root_link->cell != root && root_link->dn ) root_link = root_link->dn;
                ASSERT( root_link->cell == root );

                BFOR_EACH( i, &o->encs )
                {
                    if( o->encs.data[ i ]->dn == root_link )
                    {
                        o->encs.data[ i ]->up = wrap_link->up;
                        break;
                    }
                }
            }
        }
        wrap = wrap->wrapped_cell;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem* opal_sem_cell_s_push_sem( opal_sem_cell_s* o, tp_t type )
{
    if( !o->body ) o->body = opal_sem_body_s_create();
    return opal_sem_body_s_push_t( o->body, type );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_cell( opal_sem_cell_s* o )
{
    opal_sem_cell_s* cell = ( opal_sem_cell_s* )opal_sem_cell_s_push_sem( o, TYPEOF_opal_sem_cell_s );
    cell->parent = o;
    cell->context = bcore_fork( o->context );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_link_s* opal_sem_cell_s_push_link( opal_sem_cell_s* o )
{
    opal_sem_link_s* link = ( opal_sem_link_s* )opal_sem_cell_s_push_sem( o, TYPEOF_opal_sem_link_s );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * Channel naming:
 * Output channel has name 'y'
 * Input channels are named in order 'a', 'b' ...
 * If ever more than 24 input channels are used, excess channels carry no name.
 */
opal_sem_cell_s* opal_sem_cell_s_push_cell_nop_d( opal_sem_cell_s* o, opal_nop* nop )
{
    opal_sem_cell_s* cell = ( opal_sem_cell_s* )opal_sem_cell_s_push_cell( o );
    opal_sem_cell_s_set_channels( cell, 1, opal_nop_a_arity( nop ) );
    sc_t symbol = opal_nop_a_symbol( nop );
    if( symbol ) cell->name = opal_sem_cell_s_entypeof( o, symbol );
    cell->nop = nop;

    cell->priority = opal_nop_a_priority( nop );
    cell->excs.data[ 0 ]->name = opal_sem_cell_s_entypeof( o, "y" );

    for( sz_t i = 0; i < cell->encs.size; i++ )
    {
        if( i < 'y' - 'a' )
        {
            cell->encs.data[ 0 ]->name = opal_sem_cell_s_entypeof_fa( o, "#<char>", 'a' + i );
        }
    }

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_cell_nop_d_reset_name( opal_sem_cell_s* o, opal_nop* nop )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d( o, nop );
    cell->name = 0;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_cell_nop_d_set_source( opal_sem_cell_s* o, opal_nop* nop, bcore_source* source )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d( o, nop );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_cell_nop_d_reset_name_set_source( opal_sem_cell_s* o, opal_nop* nop, bcore_source* source )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d_reset_name( o, nop );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_cell_const_scalar( opal_sem_cell_s* o, tp_t type, f3_t v )
{
    opal_nop_ar0_literal_s* literal = opal_nop_ar0_literal_s_create();
    literal->h = opal_holor_s_create();
    bhvm_holor_s_set_type_scalar( &literal->h->h, type, v );
    literal->h->m.active = false;
    return opal_sem_cell_s_push_cell_nop_d_reset_name( o, ( opal_nop* )literal );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_wrap_cell_soft( opal_sem_cell_s* o, opal_sem_cell_s* src )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell( o );
    opal_sem_cell_s_wrap_cell_soft( cell, src );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_wrap_cell_hard( opal_sem_cell_s* o, opal_sem_cell_s* src )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell( o );
    opal_sem_cell_s_wrap_cell_hard( cell, src );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_rewrap_cell_soft( opal_sem_cell_s* o, opal_sem_cell_s* src )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell( o );
    opal_sem_cell_s_rewrap_cell_soft( cell, src );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_push_wrap_cell_set_source( opal_sem_cell_s* o, opal_sem_cell_s* src, bcore_source* source )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_wrap_cell_soft( o, src );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_assert_identifier_not_yet_defined( const opal_sem_cell_s* o, tp_t name, bcore_source* source )
{
    if
    (
        opal_sem_links_s_name_exists( &o->encs, name ) ||
        ( o->body && opal_sem_body_s_name_exists( o->body, name ) )
    )
    {
        bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' already exists.", opal_sem_cell_s_ifnameof( o, name ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

// TODO: will be part of builder
//opal_sem_cell_s* opal_sem_cell_s_create_frame( void )
//{
//    if( !context_g ) opal_sem_context_setup();
//    opal_sem_cell_s* o = opal_sem_cell_s_create();
//    o->parent = context_g->cell;
//    return o;
//}

// ---------------------------------------------------------------------------------------------------------------------

/// parses ( ... <- ... )
void opal_sem_cell_s_parse_signature( opal_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );

    // parse excs
    {
        ASSERT( o->excs.size == 0 );
        bl_t first = true;
        while( !bcore_source_a_parse_bl_fa( source, " #?'<-'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            opal_sem_link_s* link = opal_sem_link_s_create_setup( opal_sem_cell_s_parse_var_name( o, source ), NULL, NULL, o, true );
            opal_sem_links_s_push_d( &o->excs, link );
            first = false;
        }
    }

    // parse encs
    {
        ASSERT( o->encs.size == 0 );
        bl_t first = true;
        while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            opal_sem_link_s* link = opal_sem_link_s_create_setup( opal_sem_cell_s_parse_var_name( o, source ), NULL, NULL, o, false );
            if( bcore_source_a_parse_bl_fa( source, " #?([0]=='='&&[1]!='=')" ) )
            {
                bcore_source_a_parse_fa( source, "=" );
                link->up = opal_sem_cell_s_evaluate_link( o->parent, source );
            }
            opal_sem_links_s_push_d( &o->encs, link );
            first = false;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_parse( opal_sem_cell_s* o, bcore_source* source )
{
    opal_sem_cell_s* frame = o->parent;

    // cell signature without name is allowed
    if( !bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        tp_t tp_cell_name = opal_sem_cell_s_parse_var_name( o, source );
        if( frame ) opal_sem_cell_s_assert_identifier_not_yet_defined( frame, tp_cell_name, source );
        o->name = tp_cell_name;
    }

    bcore_source_point_s_set( &o->source_point, source );

    //  ( <args_out> <- <args_in> ) { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        opal_sem_cell_s_parse_signature( o, source );
        bcore_source_a_parse_fa( source, " {" );
        opal_sem_cell_s_parse_body( o, source );
        bcore_source_a_parse_fa( source, " }" );
    }
    else // = 'expression yielding a cell'
    {
        bcore_source_a_parse_fa( source, " = " );
        opal_sem_cell_s* cell = opal_sem_cell_s_evaluate_cell( frame, source );
        opal_sem_cell_s_wrap_cell_soft( o, cell );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

st_s* opal_sem_cell_s_create_signature( const opal_sem_cell_s* o )
{
    st_s* s = st_s_create();
    st_s_push_fa( s, "(" );
    BFOR_EACH( i, &o->excs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", opal_sem_cell_s_ifnameof( o, o->excs.data[ i ]->name ) );
    st_s_push_fa( s, "<-" );
    BFOR_EACH( i, &o->encs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", opal_sem_cell_s_ifnameof( o, o->encs.data[ i ]->name ) );
    st_s_push_fa( s, ")" );
    return s;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_parse_verify_signature( const opal_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );

    // parse excs
    {
        bl_t first = true;
        sz_t index = 0;
        bl_t err = false;
        while( !err && !bcore_source_a_parse_bl_fa( source, " #?'<-'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            tp_t name = opal_sem_cell_s_parse_var_name( o, source );
            if( !err ) err = ( index >= o->excs.size );
            if( !err ) err = o->excs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->excs.size;
        if( err )
        {
            st_s* sig = opal_sem_cell_s_create_signature( o );
            bcore_source_a_parse_err_fa( source, "Cell signature is '#<sc_t>'", sig->sc );
            st_s_discard( sig );
        }
    }

    // parse encs
    {
        bl_t first = true;
        sz_t index= 0;
        bl_t err = false;
        while( !err && !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            tp_t name = opal_sem_cell_s_parse_var_name( o, source );
            if( !err ) err = ( index >= o->encs.size );
            if( !err ) err = o->encs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->encs.size;
        if( err )
        {
            st_s* sig = opal_sem_cell_s_create_signature( o );
            bcore_source_a_parse_err_fa( source, "Cell signature is '#<sc_t>'", sig->sc );
            st_s_discard( sig );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_parse_body( opal_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " " );
    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #=?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'cell'" ) ) // definition of a cell
        {
            opal_sem_cell_s_parse( opal_sem_cell_s_push_cell( o ), source );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'verify_signature'" ) ) // verifies signature of wrapping cell
        {
            opal_sem_cell_s_parse_verify_signature( o, source );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'adaptive'" ) ) // defining a link to an adaptive operator
        {
            tp_t tp_name = opal_sem_cell_s_parse_var_name( o, source );
            opal_sem_link_s* link = opal_sem_cell_s_push_link( o );
            opal_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
            link->name = tp_name;
            opal_nop_ar1_adaptive_s* nop_adaptive = opal_nop_ar1_adaptive_s_create();
            nop_adaptive->name = tp_name;

            opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( opal_nop* )nop_adaptive, source );

            bcore_source_a_parse_fa( source, " =" );
            cell->encs.data[ 0 ]->up = opal_sem_cell_s_evaluate_link( o, source );
            link->up = cell->excs.data[ 0 ];
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'cyclic'" ) ) // A link is defined as cyclic by attaching cyclic operator with open input channel
        {
            tp_t tp_name = opal_sem_cell_s_parse_var_name( o, source );
            opal_sem_link_s* link = opal_sem_cell_s_push_link( o );
            opal_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
            link->name = tp_name;
            opal_nop_ar2_cyclic_s* nop_cyclic = opal_nop_ar2_cyclic_s_create();
            nop_cyclic->name = tp_name;
            opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( opal_nop* )nop_cyclic, source );

            bcore_source_a_parse_fa( source, " =" );
            cell->encs.data[ 0 ]->up = opal_sem_cell_s_evaluate_link( o, source );
            link->up = cell->excs.data[ 0 ];
        }
        else // identifier
        {
            tp_t tp_name = opal_sem_cell_s_parse_var_name( o, source );

            vd_t item = NULL;

            if( ( item = opal_sem_cell_s_get_exc_by_name( o, tp_name ) ) ) // identifier is exit channel of o
            {
                opal_sem_link_s* link = item;
                if( link->up )
                {
                    bcore_source_a_parse_err_fa
                    (
                        source,
                        "Channel '#<sc_t>' of cell '#<sc_t>' has already been defined.",
                        opal_sem_cell_s_ifnameof( o, tp_name ),
                        opal_sem_cell_s_ifnameof( o, o->name )
                    );
                }
                bcore_source_a_parse_fa( source, " =" );
                link->up = opal_sem_cell_s_evaluate_link( o, source );
            }
            else if( ( item = opal_sem_cell_s_get_link_by_name( o, tp_name ) ) ) // identifier is a link defined in o's body
            {
                opal_sem_link_s* link = ( opal_sem_link_s* )item;

                // Idle links should never occur. If they do, there is probably a bug in the opal-compiler.
                if( !link->up       ) bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' is idle.", opal_sem_cell_s_ifnameof( o, tp_name ) );
                if( !link->up->cell ) bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' has already been defined.", opal_sem_cell_s_ifnameof( o, tp_name ) );
                opal_sem_cell_s* cell = link->up->cell;

                if( cell->nop && cell->nop->_ == TYPEOF_opal_nop_ar2_cyclic_s )
                {
                    if( !cell->encs.data[ 1 ]->up )
                    {
                        bcore_source_a_parse_fa( source, " =" );
                        cell->encs.data[ 1 ]->up = opal_sem_cell_s_evaluate_link( o, source );
                        link->visible = false;
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "Redefining a cyclic link '#<sc_t>'.", opal_sem_cell_s_ifnameof( o, tp_name ) );
                    }
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' has already been defined.", opal_sem_cell_s_ifnameof( o, tp_name ) );
                }
            }
            else // unknown identifier --> creates a link
            {
                opal_sem_link_s* link = opal_sem_cell_s_push_link( o );
                opal_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
                link->name = tp_name;
                bcore_source_a_parse_fa( source, " =" );
                link->up = opal_sem_cell_s_evaluate_link( o, source );
            }

        }
        bcore_source_a_parse_fa( source, " ; " );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_evaluate_set_encs( opal_sem_cell_s* o, opal_sem_cell_s* parent, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    st_s* name = BLM_CREATE( st_s );

    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );

        bl_t done = false;

        if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( bcore_source_a_parse_bl_fa( source, " #?([0]=='='&&[1]!='=')" ) )
            //if( bcore_source_a_parse_bl_fa( source, " #?'='" ) )
            {
                bcore_source_a_parse_fa( source, "=" );
                opal_sem_link_s* link = opal_sem_cell_s_get_enc_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa
                    (
                        source,
                        "'#<sc_t>' specifies no entry channel of cell '#<sc_t>'.",
                        name->sc,
                        opal_sem_cell_s_ifnameof( o, o->name )
                    );
                }

                if( link->up )
                {
                    bcore_source_a_parse_err_fa
                    (
                        source,
                        "Entry channel '#<sc_t>' of cell '#<sc_t>' has already been set.",
                        name->sc,
                        opal_sem_cell_s_ifnameof( o, o->name )
                    );
                }

                link->up = opal_sem_cell_s_evaluate_link( parent, source );
                done = true;
            }
            else
            {
                stack_push( stack, name );
            }
        }

        if( !done )
        {
            opal_sem_link_s* link = opal_sem_cell_s_get_enc_by_open( o );
            if( !link )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Node '#<sc_t>': Number of free entry channels exceeded.",
                    opal_sem_cell_s_ifnameof( o, o->name )
                );
            }
            link->up = opal_sem_cell_s_evaluate_link_stack( parent, stack, source );
        }

        first = false;
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/** In body of o: creates new cell wrapping the catenated cells: cell = { c1 <: c2 }
 *  Deprecated approach. Prefer opal_sem_cell_s_recat_cell below.
 */
opal_sem_cell_s* opal_sem_cell_s_cat_cell( opal_sem_cell_s* o, opal_sem_cell_s* c1, opal_sem_cell_s* c2, bcore_source* source )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell( o );
    bcore_source_point_s_set( &cell->source_point, source );

    c1 = opal_sem_cell_s_push_wrap_cell_soft( cell, c1 );
    c2 = opal_sem_cell_s_push_wrap_cell_soft( cell, c2 );

    // only free input channels get wrapped (code below must change in case wrapping scheme changes)
    assert( c1->encs.size == opal_sem_cell_s_get_arity( c1 ) );
    assert( c2->encs.size == opal_sem_cell_s_get_arity( c2 ) );

    /// free input channels of n1 must match output channels of n2
    if( c1->encs.size != c2->excs.size )
    {
        bcore_source_point_s_parse_err_fa
        (
            &cell->source_point,
            "Catenating cells: Number of left cell's open entry channels (#<sz_t>) differs from right cells's exit channels (#<sz_t>).",
            c1->encs.size,
            c2->excs.size
        );
    }

    /// channels of wrapping cell
    opal_sem_cell_s_set_channels( cell, c1->excs.size, c2->encs.size );

    for( sz_t i = 0; i < c2->encs.size; i++ )
    {
        c2->encs.data[ i ]->up = cell->encs.data[ i ];
        cell->encs.data[ i ]->name = c2->encs.data[ i ]->name;
    }

    for( sz_t i = 0; i < c1->encs.size; i++ )
    {
        c1->encs.data[ i ]->up = c2->excs.data[ i ];
    }

    for( sz_t i = 0; i < c1->excs.size; i++ )
    {
        cell->excs.data[ i ]->up   = c1->excs.data[ i ];
        cell->excs.data[ i ]->name = c1->excs.data[ i ]->name;
    }

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

/** In body of o: creates new cell rewrapping the catenated cells: cell = { c1 <: c2 }
 *  This function rewraps c1, c2 making sure that all defined uplinks are moved to the outermost membrane.
 *  The catenated cell is then wrapped again to leave only undefined input links exposed.
 *  The last soft-wrapping is done for convenience because some code using this function assumes arity == encs.size.
 */
opal_sem_cell_s* opal_sem_cell_s_recat_cell( opal_sem_cell_s* o, opal_sem_cell_s* c1, opal_sem_cell_s* c2, bcore_source* source )
{
    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell( o );
    bcore_source_point_s_set( &cell->source_point, source );

    c1 = opal_sem_cell_s_push_rewrap_cell_soft( cell, c1 );
    c2 = opal_sem_cell_s_push_rewrap_cell_soft( cell, c2 );

    sz_t arity_c1 = opal_sem_cell_s_get_arity( c1 );

    /// free input channels of n1 must match output channels of n2
    if( arity_c1 != c2->excs.size )
    {
        bcore_source_point_s_parse_err_fa
        (
            &cell->source_point,
            "Catenating cells: Number of left cell's open entry channels (#<sz_t>) differs from right cells's exit channels (#<sz_t>).",
            arity_c1,
            c2->excs.size
        );
    }

    /// channels of wrapping cell
    opal_sem_cell_s_set_channels( cell, c1->excs.size, c2->encs.size + c1->encs.size - arity_c1 );

    sz_t k = 0;
    for( sz_t i = 0; i < c2->encs.size; i++ )
    {
        cell->encs.data[ k ]->name =   c2->encs.data[ i ]->name;
        cell->encs.data[ k ]->up   =   c2->encs.data[ i ]->up;
          c2->encs.data[ i ]->up   = cell->encs.data[ k ];
        k++;
    }

    sz_t l = 0;
    for( sz_t i = 0; i < c1->encs.size; i++ )
    {
        if( c1->encs.data[ i ]->up )
        {
            assert( k < cell->encs.size );
            cell->encs.data[ k ]->name =   c1->encs.data[ i ]->name;
            cell->encs.data[ k ]->up   =   c1->encs.data[ i ]->up;
              c1->encs.data[ i ]->up   = cell->encs.data[ k ];
            k++;
        }
        else
        {
            assert( l < c2->excs.size );
            c1->encs.data[ i ]->up = c2->excs.data[ l ];
            l++;
        }
    }

    ASSERT( k == cell->encs.size );
    ASSERT( l ==   c2->excs.size );

    for( sz_t i = 0; i < c1->excs.size; i++ )
    {
        cell->excs.data[ i ]->up   = c1->excs.data[ i ];
        cell->excs.data[ i ]->name = c1->excs.data[ i ]->name;
    }

    /// the last soft-wrap is convenience (consider changing dependent code using arity rather then encs.size to determine open links)
    return opal_sem_cell_s_push_wrap_cell_soft( o, opal_sem_cell_s_push_wrap_cell_hard( o, cell ) );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_sem_cell_s_evaluate_stack( opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BLM_INIT();
    st_s* name = BLM_CREATE( st_s );

    opal_sem_stack_flag_s* flag_bin_op    = BLM_CREATE( opal_sem_stack_flag_s );
    opal_sem_stack_flag_s* flag_una_op    = BLM_CREATE( opal_sem_stack_flag_s );
    opal_sem_stack_flag_s* flag_cell_cat  = BLM_CREATE( opal_sem_stack_flag_s );
    opal_sem_stack_flag_s* flag_inc_order = BLM_CREATE( opal_sem_stack_flag_s );

    tp_t op2_symbol = 0;

    while( !bcore_source_a_eos( source ) )
    {
        bl_t identifier = false;

        // identifier
        if( stack_of_type( stack, 1, TYPEOF_st_s ) )
        {
            st_s_copy( name, stack_pop( stack ) );
            identifier = true;
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            identifier = true;
        }

        if( identifier )
        {
            tp_t tp_name = typeof( name->sc );

            if( opal_sem_cell_s_is_control_type( o, tp_name ) )
            {
                if( tp_name == TYPEOF_cell ) // inline cell definition
                {
                    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell( o );
                    opal_sem_cell_s_parse( cell, source );
                    stack_push( stack, cell );
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Unexpected keyword '#<sc_t>'. Did you miss ';' after previous statement?", name->sc );
                }
            }
            else
            {
                vd_t item = opal_sem_cell_s_get_enc_by_name( o, tp_name );
                if( !item && o->body   ) item = opal_sem_body_s_get_sem_by_name( o->body, tp_name );
                if( !item && o->parent ) item = opal_sem_cell_s_get_cell_by_name( o->parent, tp_name );
                if( !item )
                {
                    item = opal_sem_cell_s_get_exc_by_name( o, tp_name );
                    if( item )
                    {
                        assert( *(aware_t*)item == TYPEOF_opal_sem_link_s );
                        opal_sem_link_s* link = item;
                        if( !link->up )
                        {
                            bcore_source_a_parse_err_fa( source, "Use of exit channel '#<sc_t>' before it was defined.", name->sc );
                        }
                        item = link->up;
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "Cannot evaluate identifier '#<sc_t>'.", name->sc );
                    }
                }

                tp_t tp_item = *(aware_t*)item;

                switch( tp_item )
                {
                    case TYPEOF_opal_sem_cell_s:
                    {
                        if( !opal_sem_a_is_visible( item ) ) bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' is not visible at this point.", name->sc );
                        opal_sem_cell_s* cell = item;
                        stack_push( stack, cell );
                    }
                    break;

                    case TYPEOF_opal_sem_link_s:
                    {
                        if( !opal_sem_a_is_visible( item ) )
                        {
                            opal_sem_link_s* link = item;
                            if( link->up && link->up->cell )
                            {
                                opal_sem_cell_s* cell = link->up->cell;
                                if( cell->nop && cell->nop->_ == TYPEOF_opal_nop_ar2_cyclic_s )
                                {
                                    bcore_source_a_parse_err_fa( source, "Recurrent node '#<sc_t>' must not be used after updating.", name->sc );
                                }
                            }
                            else
                            {
                                bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' is not visible at this point.", name->sc );
                            }
                        }
                        stack_push( stack, item );
                    }
                    break;

                    default:
                    {
                        bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name->sc, ifnameof( tp_item ) );
                    }
                    break;
                }
            }
        }

        // literal scalar (negative numbers are created via neg operator)
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]>='0'&&[0]<='9')" ) )
        {
            f3_t val = 0;
            tp_t type = TYPEOF_f3_t;
            bcore_source_a_parse_fa( source, " #<f3_t*>", &val );
            if(      bcore_source_a_parse_bl_fa( source, "#?'f2'" ) ) type = TYPEOF_f2_t;
            else if( bcore_source_a_parse_bl_fa( source, "#?'f3'" ) ) type = TYPEOF_f3_t;
            opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_const_scalar( o, type, val );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // undetermined scalar (falls back to 0)
        else if( bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
        {
            tp_t type = TYPEOF_f3_t;
            if(      bcore_source_a_parse_bl_fa( source, "#?'f2'" ) ) type = TYPEOF_f2_t;
            else if( bcore_source_a_parse_bl_fa( source, "#?'f3'" ) ) type = TYPEOF_f3_t;
            opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_const_scalar( o, type, 0 );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // block or input channel selection in case l-value is a cell
        else if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_opal_sem_cell_s ) )
            {
                opal_sem_cell_s* cell = opal_sem_cell_s_push_wrap_cell_set_source( o, stack_pop( stack ), source );
                opal_sem_cell_s_evaluate_set_encs( cell, o, source );
                stack_push( stack, cell );
            }
            else
            {
                bcore_source_a_parse_fa( source, " (" );
                stack_push( stack, opal_sem_cell_s_evaluate_sem( o, source ) );
                bcore_source_a_parse_fa( source, " )" );
            }
        }

        // cell catenation
        else if( bcore_source_a_parse_bl_fa( source, " #?'<:'" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_opal_sem_cell_s ) )
            {
                stack_push( stack, flag_cell_cat );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cell catenation '<:': l-value is not a cell." );
            }
        }

        // binary operator from predefined symbols
        else if( ( op2_symbol = opal_sem_cell_s_parse_op2_symbol( o, source ) ) )
        {
            if
            (
                 stack->size == 0 ||
               ( stack->size >= 1 && stack_of_value( stack, 1, flag_una_op ) ) ||
               ( stack->size >= 3 && stack_of_value( stack, 3, flag_bin_op ) )
            )
            {
                // binary op not applicable, try unary
                opal_sem_cell_s* cell = opal_sem_cell_s_get_cell_by_name( o, op2_symbol );
                opal_nop* nop_unary = opal_nop_a_create_op_of_arn( cell->nop, 1 );
                if( nop_unary )
                {
                    opal_sem_cell_s* cell = opal_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, nop_unary, source );
                    stack_push( stack, cell );
                    stack_push( stack, flag_una_op ); // flag after cell to avoid incorrect stack evaluation
                }
                else
                {
                    if( stack->size == 0 )
                    {
                        bcore_source_a_parse_err_fa
                        (
                            source,
                            "Operator '#<sc_t>': Left operand missing.",
                            opal_sem_cell_s_ifnameof( o, op2_symbol )
                        );
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa
                        (
                            source,
                            "Operator '#<sc_t>': This is a successive binary operator. Right operand expected instead.",
                            opal_sem_cell_s_ifnameof( o, op2_symbol )
                        );
                    }
                }
            }
            else
            {
                opal_sem_cell_s* cell = opal_sem_cell_s_get_cell_by_name( o, op2_symbol );
                if( !cell ) bcore_source_a_parse_err_fa( source, "Syntax error." );
                cell = opal_sem_cell_s_push_wrap_cell_set_source( o, cell, source );
                stack_push( stack, flag_bin_op );
                stack_push( stack, cell );
            }
        }

        // custom binary operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'<<'" ) )
        {
            bcore_source_a_parse_fa( source, "#until'>'>>", name );
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", name->sc );
            opal_sem_cell_s* cell = opal_sem_cell_s_get_cell_by_name( o, typeof( name->sc ) );
            if( !cell ) bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>' not found.", name->sc );
            cell = opal_sem_cell_s_push_wrap_cell_set_source( o, cell, source );
            stack_push( stack, flag_bin_op );
            stack_push( stack, cell );
        }

        // output channel selection
        else if( bcore_source_a_parse_bl_fa( source, " #?'.'" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );

            if( !stack_of_type( stack, 1, TYPEOF_opal_sem_cell_s ) )
            {
                bcore_source_a_parse_err_fa( source, "Output channel selection on non-cell." );
            }

            opal_sem_cell_s* cell = stack_pop( stack );
            opal_sem_link_s* link = opal_sem_cell_s_get_exc_by_name( cell, typeof( name->sc ) );

            if( opal_sem_cell_s_get_arity( cell ) > 0 )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Output channel selection on cell '#<sc_t>' with #<sz_t> open input channels.",
                    opal_sem_cell_s_ifnameof( o, cell->name ),
                    opal_sem_cell_s_get_arity( cell )
                );
            }

            if( !link )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Cell '#<sc_t>': Invalid channel '#<sc_t>'.",
                    opal_sem_cell_s_ifnameof( o, cell->name ), name->sc
                );
            }
            stack_push( stack, link );
        }

        // postfix htp
        else if( bcore_source_a_parse_bl_fa( source, " #?'~'" ) )
        {
            opal_sem_cell_s* htp_cell = opal_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( opal_nop* )opal_nop_ar1_cast_htp_s_create(), source );
            if( stack_of_type( stack, 1, TYPEOF_opal_sem_link_s ) )
            {
                htp_cell->encs.data[ 0 ]->up = stack_pop_of_type( stack, TYPEOF_opal_sem_link_s, source );
                stack_push( stack, htp_cell->excs.data[ 0 ] );
            }
            else if( stack_of_type( stack, 1, TYPEOF_opal_sem_cell_s ) )
            {
                opal_sem_cell_s* r_cell = stack_pop_of_type( stack, TYPEOF_opal_sem_cell_s, source );
                stack_push( stack, htp_cell );
                stack_push( stack, flag_cell_cat );
                stack_push( stack, r_cell );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "transposition '~': invalid l-value." );
            }
        }

        // single char terminator
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]==')'||[0]==']'||[0]==','||[0]==';')" ) )
        {
            break;
        }

        else
        {
            bcore_source_a_parse_err_fa( source, "Syntax error." );
        }

        /// priority stack processing ...

        // unary operator: right operand
        while( stack->size >= 3 && stack_of_value( stack, 2, flag_una_op ) && stack_of_type( stack, 1, TYPEOF_opal_sem_link_s ) )
        {
            opal_sem_link_s* link = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_una_op, source );
            opal_sem_cell_s* cell = stack_pop_cell( stack, source );
            ASSERT( cell->encs.size == 1 );
            cell->encs.data[ 0 ]->up = link;
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        if( stack->size >= 3 && stack_of_value( stack, 2, flag_bin_op ) )
        {
            opal_sem_cell_s* cell = stack_pop_of_type( stack, TYPEOF_opal_sem_cell_s, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            opal_sem* arg1 = stack_pop( stack );

            if( arg1->_ == TYPEOF_opal_sem_cell_s )
            {
                opal_sem_cell_s* cell1 = ( opal_sem_cell_s* )arg1;
                if( cell1->excs.size != 1 )
                {
                    bcore_source_point_s_parse_err_fa
                    (
                        &cell1->source_point,
                        "Binary operator '#<sc_t>': Left operant '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                        opal_sem_cell_s_ifnameof( o, cell->name ),
                        opal_sem_cell_s_ifnameof( o, cell1->name ),
                        cell1->excs.size
                    );
                }
                arg1 = ( opal_sem* )cell1->excs.data[ 0 ];
            }

            if( opal_sem_cell_s_get_arity( cell ) != 2 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has arity '#<sz_t>'. Expected: '2'.",
                    opal_sem_cell_s_ifnameof( o, cell->name ),
                    opal_sem_cell_s_get_arity( cell )
                );
            }

            if( cell->excs.size != 1 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                    opal_sem_cell_s_ifnameof( o, cell->name ),
                    cell->excs.size
                );
            }

            stack_push( stack, arg1 );
            stack_push( stack, flag_bin_op );
            stack_push( stack, cell );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // cell-catenation
        if( stack->size >= 3 && stack_of_value( stack, 2, flag_cell_cat ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_opal_sem_cell_s ) )  // cell1 : cell2
            {
                opal_sem_cell_s* cell2 = stack_pop_cell( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                opal_sem_cell_s* cell1 = stack_pop_cell( stack, source );
                stack_push( stack, opal_sem_cell_s_recat_cell( o, cell1, cell2, source ) );
            }
            else if( stack_of_type( stack, 1, TYPEOF_opal_sem_link_s ) ) // cell : link
            {
                opal_sem_link_s* link = stack_pop_link( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                opal_sem_cell_s* cell = stack_pop_cell( stack, source );
                cell = opal_sem_cell_s_push_wrap_cell_soft( o, cell );
                if( cell->encs.size != 1 ) bcore_source_a_parse_err_fa( source, "Catenation 'Cell : Link': Cell has #<sz_t> free entry channels; required is 1", cell->encs.size );
                cell->encs.data[ 0 ]->up = link;
                stack_push( stack, cell );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cannot resolve catenation." );
            }
        }

        // order incrementations (loop because multiple [] can be next to each other)
        while( stack_of_value( stack, 2, flag_inc_order ) && stack_of_type( stack, 1, TYPEOF_opal_sem_link_s ) )
        {
            opal_sem_link_s* link2 = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_inc_order, source );
            opal_sem_cell_s* cell  = stack_pop_cell( stack, source );
            ASSERT( cell->encs.data[ 0 ]->up ); // was set at cell creation
            cell->encs.data[ 1 ]->up = link2;
            stack_push( stack, cell->excs.data[ 0 ] );
        }
    }

    /// remaining stack processing ...

    /// Binary operators
    while( stack->size >= 5 && stack_of_value( stack, 4, flag_bin_op ) ) // <left arg> <flag> <bin-operator> <output> <right arg>
    {
        opal_sem_link_s* link2 = stack_pop_link_or_exit( stack, source );
        opal_sem_link_s* out   = stack_pop_link( stack, source );
        opal_sem_cell_s* cell  = stack_pop_cell( stack, source );
        stack_pop_of_value( stack, flag_bin_op, source );
        opal_sem_link_s* link1 = stack_pop_link_or_exit( stack, source );

        if( stack->size >= 4 && stack_of_value( stack, 3, flag_bin_op ) ) // merge with prior operation considering priority
        {
            opal_sem_link_s* prior_out   = stack_pop_link( stack, source );
            opal_sem_cell_s* prior_cell  = stack_pop_cell( stack, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            opal_sem_link_s* prior_link1 = stack_pop_link_or_exit( stack, source );

            sz_t prior_priority = opal_sem_cell_s_get_priority( prior_cell );
            sz_t cell_priority  = opal_sem_cell_s_get_priority( cell );

            /// on equality: odd priority yields
            bl_t yield = ( prior_priority < cell_priority )
                           || ( ( prior_priority == cell_priority ) && ( ( prior_priority & 1 ) == 1 ) );

            if( yield )
            {
                opal_sem_cell_s_get_enc_by_open( cell )->up = link1;
                opal_sem_cell_s_get_enc_by_open( cell )->up = link2;

                stack_push( stack, prior_link1 );
                stack_push( stack, flag_bin_op );
                stack_push( stack, prior_cell );
                stack_push( stack, prior_out );
                stack_push( stack, out );           // out becomes right argument for prior_cell
            }
            else
            {
                opal_sem_cell_s_get_enc_by_open( cell )->up = prior_out;
                opal_sem_cell_s_get_enc_by_open( cell )->up = link2;

                stack_push( stack, prior_link1 );
                stack_push( stack, flag_bin_op );
                stack_push( stack, prior_cell );
                stack_push( stack, out );
                stack_push( stack, link1 );
            }
        }
        else // fully resolve operation
        {
            opal_sem_cell_s_get_enc_by_open( cell )->up = link1;
            opal_sem_cell_s_get_enc_by_open( cell )->up = link2;
            stack_push( stack, out );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem* opal_sem_cell_s_evaluate_sem_stack( opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    opal_sem_cell_s_evaluate_stack( o, stack, source );
    if( stack->size != 1 ) bcore_source_a_parse_err_fa( source, "Expression syntax error." );
    return stack_pop( stack );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem* opal_sem_cell_s_evaluate_sem( opal_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    vd_t ret = opal_sem_cell_s_evaluate_sem_stack( o, stack, source );
    BLM_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_link_s* opal_sem_cell_s_evaluate_link_stack( opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    opal_sem* ret = opal_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret == TYPEOF_opal_sem_cell_s )
    {
        opal_sem_cell_s* cell = ( opal_sem_cell_s* )ret;
        if( opal_sem_cell_s_get_arity( cell ) > 0 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> open entry channels.", opal_sem_cell_s_get_arity( cell ) );
        }

        if( cell->excs.size != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> exit channels.", cell->excs.size );
        }

        ret = ( opal_sem* )cell->excs.data[ 0 ];
    }

    if( *( aware_t* )ret != TYPEOF_opal_sem_link_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Link expected.", ifnameof( *( aware_t* )ret ) );
    }

    return ( opal_sem_link_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_link_s* opal_sem_cell_s_evaluate_link( opal_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    opal_sem_link_s* ret = opal_sem_cell_s_evaluate_link_stack( o, stack, source );
    BLM_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_evaluate_cell_stack( opal_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    opal_sem* ret = opal_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret != TYPEOF_opal_sem_cell_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Cell Expected.", ifnameof( *( aware_t* )ret ) );
    }
    return ( opal_sem_cell_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* opal_sem_cell_s_evaluate_cell( opal_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    opal_sem_cell_s* ret = opal_sem_cell_s_evaluate_cell_stack( o, stack, source );
    BLM_RETURNV( opal_sem_cell_s*, ret );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

