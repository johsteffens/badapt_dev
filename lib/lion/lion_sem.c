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

#include "lion_sem.h"

/**********************************************************************************************************************/
/// Prototypes

// ---------------------------------------------------------------------------------------------------------------------
// sem_cell

void lion_sem_cell_s_create_args_out( lion_sem_cell_s* o, bcore_source* source );
void lion_sem_cell_s_create_args_in(  lion_sem_cell_s* o, lion_sem_cell_s* frame, bcore_source* source );
void lion_sem_cell_s_wrap_cell(       lion_sem_cell_s* o, lion_sem_cell_s* cell );

void             lion_sem_cell_s_parse(               lion_sem_cell_s* o,                        bcore_source* source );
void             lion_sem_cell_s_parse_body(          lion_sem_cell_s* o,                        bcore_source* source );
lion_sem*        lion_sem_cell_s_evaluate_sem(        lion_sem_cell_s* o,                        bcore_source* source );
lion_sem*        lion_sem_cell_s_evaluate_sem_stack(  lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
lion_sem_cell_s* lion_sem_cell_s_evaluate_cell(       lion_sem_cell_s* o,                        bcore_source* source );
lion_sem_cell_s* lion_sem_cell_s_evaluate_cell_stack( lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
lion_sem_link_s* lion_sem_cell_s_evaluate_link(       lion_sem_cell_s* o,                        bcore_source* source );
lion_sem_link_s* lion_sem_cell_s_evaluate_link_stack( lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
lion_sem_cell_s* lion_sem_cell_s_push_cell_nop_d(     lion_sem_cell_s* o,       lion_nop* nop );
lion_sem_cell_s* lion_sem_cell_s_push_cell_nop_d_reset_name( lion_sem_cell_s* o, lion_nop* nop );
void             lion_sem_cell_s_set_channels(        lion_sem_cell_s* o, sz_t excs, sz_t encs );

// ---------------------------------------------------------------------------------------------------------------------
// context

tp_t lion_entypeof( sc_t name );

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// Context

// ---------------------------------------------------------------------------------------------------------------------

static lion_sem_context_s* context_g = NULL;

lion_sem_context_s* lion_sem_get_context( void )
{
    return context_g;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_context_setup()
{
    if( context_g ) return;
    context_g = lion_sem_context_s_create();

    BLM_INIT();
    bcore_arr_tp_s* arr_tp = BLM_CREATE( bcore_arr_tp_s );

    bcore_push_traits_of_ancestor( TYPEOF_lion_nop_ar1, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_lion_nop_ar2, arr_tp );

    context_g->cell = lion_sem_cell_s_create();

    for( sz_t i = 0; i < arr_tp->size; i++ )
    {
        lion_nop* nop = lion_nop_t_create( arr_tp->data[ i ] );
        sc_t symbol   = lion_nop_a_symbol( nop );
        // bcore_msg_fa( "#<sc_t>\n", symbol );
        if( symbol )
        {
            sz_t arity = lion_nop_a_arity( nop );
            bcore_hmap_name_s_set_sc( &context_g->hmap_name, symbol );
            switch( arity )
            {
                case 2: bcore_arr_st_s_push_sc( &context_g->arr_symbol_op2, symbol ); break;
                default: break;
            }
            lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d( context_g->cell, nop );
            cell->name = typeof( symbol );
        }
        else
        {
            lion_nop_a_detach( &nop );
        }
    }

    /** We sort the array in descending manner; this ensures that short symbols
     *  which patterns match the beginning of a longer symbol can not occlude the longer one.
     */
    bcore_array_a_sort( (bcore_array*)&context_g->arr_symbol_op2, 0, -1, -1 );

    /// register control types
    bcore_arr_tp_s_push( &context_g->control_types, lion_entypeof( "cell" ) );
    bcore_arr_tp_s_push( &context_g->control_types, lion_entypeof( "if" ) );
    bcore_arr_tp_s_push( &context_g->control_types, lion_entypeof( "then" ) );
    bcore_arr_tp_s_push( &context_g->control_types, lion_entypeof( "else" ) );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_context_down()
{
    if( context_g )
    {
        lion_sem_context_s_detach( &context_g );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t lion_nameof( tp_t name )
{
    if( !context_g ) lion_sem_context_setup();
    return bcore_hmap_name_s_get_sc( &context_g->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t lion_ifnameof( tp_t name )
{
    sc_t sc = lion_nameof( name );
    return sc ? sc : "";
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t lion_entypeof( sc_t name )
{
    if( !context_g ) lion_sem_context_setup();
    return bcore_hmap_name_s_set_sc( &context_g->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t lion_entypeof_fv( sc_t format, va_list args )
{
    st_s* s = st_s_create_fv( format, args );
    tp_t tp = lion_entypeof( s->sc );
    st_s_discard( s );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t lion_entypeof_fa( sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    tp_t tp = lion_entypeof_fv( format, args );
    va_end( args );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t lion_parse_name( bcore_source* source )
{
    st_s* name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", name );
    if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
    tp_t tp_name = lion_entypeof( name->sc );
    st_s_discard( name );
    return tp_name;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t lion_parse_op2_symbol( bcore_source* source )
{
    if( !context_g ) lion_sem_context_setup();
    bcore_arr_st_s* arr = &context_g->arr_symbol_op2;

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

tp_t lion_is_control_type( tp_t name )
{
    return ( bcore_arr_tp_s_find( &context_g->control_types, 0, -1, name ) < context_g->control_types.size );
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

static lion_sem_link_s* stack_pop_link( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_lion_sem_link_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static lion_sem_cell_s* stack_pop_cell( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_lion_sem_cell_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static lion_sem_link_s* stack_pop_link_or_exit( bcore_arr_vd_s* o, bcore_source* source )
{
    vd_t v = stack_pop( o );
    tp_t t = *(aware_t*)v;
    if( t == TYPEOF_lion_sem_link_s ) return v;
    if( t == TYPEOF_lion_sem_cell_s )
    {
        lion_sem_cell_s* cell = v;
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
/// link

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_link_s* lion_sem_link_s_create_setup( tp_t name, lion_sem_link_s* up, lion_sem_link_s* dn, lion_sem_cell_s* cell, bl_t exit )
{
    lion_sem_link_s* o = lion_sem_link_s_create();
    o->name = name;
    o->up = up;
    o->dn = dn;
    o->cell = cell;
    o->exit = exit;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next membrane; returns NULL in case trace ends in open link
lion_sem_link_s* lion_sem_link_s_trace_to_cell_membrane( lion_sem_link_s* o )
{
    if( !o || o->cell ) return o;
    return lion_sem_link_s_trace_to_cell_membrane( o->up );
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next cell; returns NULL in case trace ends in open link
lion_sem_cell_s* lion_sem_link_s_trace_to_cell( lion_sem_link_s* o )
{
    lion_sem_link_s* link = lion_sem_link_s_trace_to_cell_membrane( o );
    if( link )
    {
        if( link->cell ) assert( *(aware_t*)link->cell == TYPEOF_lion_sem_cell_s );
        return link->cell;
    }
    else
    {
        return NULL;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// sem_cell

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_set_channels( lion_sem_cell_s* o, sz_t excs, sz_t encs )
{
    lion_sem_links_s_set_size( &o->excs, excs );
    lion_sem_links_s_set_size( &o->encs, encs );
    for( sz_t i = 0; i < excs; i++ )
    {
        o->excs.data[ i ] = lion_sem_link_s_create_setup( 0, NULL, NULL, o, true );
    }
    for( sz_t i = 0; i < encs; i++ )
    {
        o->encs.data[ i ] = lion_sem_link_s_create_setup( 0, NULL, NULL, o, false );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_wrap_cell( lion_sem_cell_s* o, lion_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->nop  );
    o->priority = src->priority;
    lion_sem_links_s_set_size( &o->encs, lion_sem_cell_s_get_arity( src ) );
    lion_sem_links_s_set_size( &o->excs, src->excs.size );

    sz_t k = 0;
    for( sz_t i = 0; i < src->encs.size; i++ )
    {
        if( !src->encs.data[ i ]->up )
        {
            o->encs.data[ k++ ] = lion_sem_link_s_create_setup( src->encs.data[ i ]->name, NULL, src->encs.data[ i ], o, false );
        }
    }

    assert( k == o->encs.size );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        o->excs.data[ i ] = lion_sem_link_s_create_setup( src->excs.data[ i ]->name, src->excs.data[ i ], NULL, o, true );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem* lion_sem_cell_s_push_sem( lion_sem_cell_s* o, tp_t type )
{
    if( !o->body ) o->body = lion_sem_body_s_create();
    return lion_sem_body_s_push_t( o->body, type );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_push_cell( lion_sem_cell_s* o )
{
    lion_sem_cell_s* cell = ( lion_sem_cell_s* )lion_sem_cell_s_push_sem( o, TYPEOF_lion_sem_cell_s );
    cell->parent = o;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_link_s* lion_sem_cell_s_push_link( lion_sem_cell_s* o )
{
    lion_sem_link_s* link = ( lion_sem_link_s* )lion_sem_cell_s_push_sem( o, TYPEOF_lion_sem_link_s );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * Channel naming:
 * Output channel has name 'y'
 * Input channels are named in order 'a', 'b' ...
 * If ever more than 24 input channels are used, excess channels carry no name.
 */
lion_sem_cell_s* lion_sem_cell_s_push_cell_nop_d( lion_sem_cell_s* o, lion_nop* nop )
{
    lion_sem_cell_s* cell = ( lion_sem_cell_s* )lion_sem_cell_s_push_cell( o );
    lion_sem_cell_s_set_channels( cell, 1, lion_nop_a_arity( nop ) );
    sc_t symbol = lion_nop_a_symbol( nop );
    if( symbol ) cell->name = lion_entypeof( symbol );
    cell->nop = nop;

    cell->priority = lion_nop_a_priority( nop );
    cell->excs.data[ 0 ]->name = lion_entypeof( "y" );

    for( sz_t i = 0; i < cell->encs.size; i++ )
    {
        if( i < 'y' - 'a' )
        {
            cell->encs.data[ 0 ]->name = lion_entypeof_fa( "#<char>", 'a' + i );
        }
    }

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_push_cell_nop_d_reset_name( lion_sem_cell_s* o, lion_nop* nop )
{
    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d( o, nop );
    cell->name = 0;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_push_cell_nop_d_set_source( lion_sem_cell_s* o, lion_nop* nop, bcore_source* source )
{
    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d( o, nop );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( lion_sem_cell_s* o, lion_nop* nop, bcore_source* source )
{
    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name( o, nop );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

/// v can be NULL pushing an undetermined scalar
lion_sem_cell_s* lion_sem_cell_s_push_cell_scalar( lion_sem_cell_s* o, f3_t* v )
{
    lion_nop_ar0_literal_s* literal = lion_nop_ar0_literal_s_create();
    literal->h = lion_holor_s_create();
    if( v )
    {
        bhvm_holor_s_set_scalar_f3( &literal->h->h, *v );
    }
    else
    {
        bhvm_holor_s_set_scalar_pf( &literal->h->h, TYPEOF_f3_t, NULL );
    }
    return lion_sem_cell_s_push_cell_nop_d_reset_name( o, ( lion_nop* )literal );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_push_wrap_cell( lion_sem_cell_s* o, lion_sem_cell_s* src )
{
    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell( o );
    lion_sem_cell_s_wrap_cell( cell, src );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_push_wrap_cell_set_source( lion_sem_cell_s* o, lion_sem_cell_s* src, bcore_source* source )
{
    lion_sem_cell_s* cell = lion_sem_cell_s_push_wrap_cell( o, src );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_assert_identifier_not_yet_defined( const lion_sem_cell_s* o, tp_t name, bcore_source* source )
{
    if
    (
        lion_sem_links_s_name_exists( &o->encs, name ) ||
        ( o->body && lion_sem_body_s_name_exists( o->body, name ) )
    )
    {
        bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' already exists.", lion_ifnameof( name ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_create_frame( void )
{
    if( !context_g ) lion_sem_context_setup();
    lion_sem_cell_s* o = lion_sem_cell_s_create();
    o->parent = context_g->cell;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

/// parses ( ... <- ... )
void lion_sem_cell_s_parse_signature( lion_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );

    // parse excs
    {
        ASSERT( o->excs.size == 0 );
        bl_t first = true;
        while( !bcore_source_a_parse_bl_fa( source, " #?'<-'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            lion_sem_link_s* link = lion_sem_link_s_create_setup( lion_parse_name( source ), NULL, NULL, o, true );
            lion_sem_links_s_push_d( &o->excs, link );
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
            lion_sem_link_s* link = lion_sem_link_s_create_setup( lion_parse_name( source ), NULL, NULL, o, false );
            if( bcore_source_a_parse_bl_fa( source, " #?'='" ) )
            {
                link->up = lion_sem_cell_s_evaluate_link( o->parent, source );
            }
            lion_sem_links_s_push_d( &o->encs, link );
            first = false;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_parse( lion_sem_cell_s* o, bcore_source* source )
{
    lion_sem_cell_s* frame = o->parent;

    // cell signature without name is allowed
    if( !bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        tp_t tp_cell_name = lion_parse_name( source );
        if( frame ) lion_sem_cell_s_assert_identifier_not_yet_defined( frame, tp_cell_name, source );
        o->name = tp_cell_name;
    }

    bcore_source_point_s_set( &o->source_point, source );

    //  ( <args_out> <- <args_in> ) { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        lion_sem_cell_s_parse_signature( o, source );
        bcore_source_a_parse_fa( source, " {" );
        lion_sem_cell_s_parse_body( o, source );
        bcore_source_a_parse_fa( source, " }" );
    }
    else // = 'expression yielding a cell'
    {
        bcore_source_a_parse_fa( source, " = " );
        lion_sem_cell_s* cell = lion_sem_cell_s_evaluate_cell( frame, source );
        lion_sem_cell_s_wrap_cell( o, cell );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

st_s* lion_sem_cell_s_create_signature( const lion_sem_cell_s* o )
{
    st_s* s = st_s_create();
    st_s_push_fa( s, "(" );
    BFOR_EACH( i, &o->excs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", lion_ifnameof( o->excs.data[ i ]->name ) );
    st_s_push_fa( s, "<-" );
    BFOR_EACH( i, &o->encs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", lion_ifnameof( o->encs.data[ i ]->name ) );
    st_s_push_fa( s, ")" );
    return s;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_parse_verify_signature( const lion_sem_cell_s* o, bcore_source* source )
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
            tp_t name = lion_parse_name( source );
            if( !err ) err = ( index >= o->excs.size );
            if( !err ) err = o->excs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->excs.size;
        if( err )
        {
            st_s* sig = lion_sem_cell_s_create_signature( o );
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
            tp_t name = lion_parse_name( source );
            if( !err ) err = ( index >= o->encs.size );
            if( !err ) err = o->encs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->encs.size;
        if( err )
        {
            st_s* sig = lion_sem_cell_s_create_signature( o );
            bcore_source_a_parse_err_fa( source, "Cell signature is '#<sc_t>'", sig->sc );
            st_s_discard( sig );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_parse_body( lion_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " " );
    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #=?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'cell'" ) ) // definition of a cell
        {
            lion_sem_cell_s_parse( lion_sem_cell_s_push_cell( o ), source );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'verify_signature'" ) ) // verifies signature of wrapping cell
        {
            lion_sem_cell_s_parse_verify_signature( o, source );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'adaptive'" ) ) // defining a link to an adaptive operator
        {
            tp_t tp_name = lion_parse_name( source );
            lion_sem_link_s* link = lion_sem_cell_s_push_link( o );
            lion_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
            link->name = tp_name;
            lion_nop_ar1_adaptive_s* nop_adaptive = lion_nop_ar1_adaptive_s_create();
            nop_adaptive->name = tp_name;

            lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )nop_adaptive, source );

            bcore_source_a_parse_fa( source, " =" );
            cell->encs.data[ 0 ]->up = lion_sem_cell_s_evaluate_link( o, source );
            link->up = cell->excs.data[ 0 ];
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'recurrent'" ) ) // A link is defined as recurrent by attaching recurrent operator with open input channel
        {
            tp_t tp_name = lion_parse_name( source );
            lion_sem_link_s* link = lion_sem_cell_s_push_link( o );
            lion_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
            link->name = tp_name;
            lion_nop_ar2_recurrent_s* nop_recurrent = lion_nop_ar2_recurrent_s_create();
            nop_recurrent->name = tp_name;
            lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )nop_recurrent, source );

            bcore_source_a_parse_fa( source, " =" );
            cell->encs.data[ 0 ]->up = lion_sem_cell_s_evaluate_link( o, source );
            link->up = cell->excs.data[ 0 ];
        }
        else // identifier
        {
            tp_t tp_name = lion_parse_name( source );

            vd_t item = NULL;

            if( ( item = lion_sem_cell_s_get_exc_by_name( o, tp_name ) ) ) // identifier is exit channel of o
            {
                lion_sem_link_s* link = item;
                if( link->up )
                {
                    bcore_source_a_parse_err_fa( source, "Channel '#<sc_t>' of cell '#<sc_t>' has already been defined.", lion_ifnameof( tp_name ), lion_ifnameof( o->name ) );
                }
                bcore_source_a_parse_fa( source, " =" );
                link->up = lion_sem_cell_s_evaluate_link( o, source );
            }
            else if( ( item = lion_sem_cell_s_get_link_by_name( o, tp_name ) ) ) // identifier is a link defined in o's body
            {
                lion_sem_link_s* link = ( lion_sem_link_s* )item;

                // Idle links should never occur. If they do, there is probably a bug in the lion-compiler.
                if( !link->up       ) bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' is idle.", lion_ifnameof( tp_name ) );
                if( !link->up->cell ) bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' has already been defined.", lion_ifnameof( tp_name ) );
                lion_sem_cell_s* cell = link->up->cell;
                if( cell->nop && cell->nop->_ == TYPEOF_lion_nop_ar2_recurrent_s )
                {
                    if( !cell->encs.data[ 1 ]->up )
                    {
                        bcore_source_a_parse_fa( source, " =" );
                        cell->encs.data[ 1 ]->up = lion_sem_cell_s_evaluate_link( o, source );
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "Redefining a recurrent link '#<sc_t>'.", lion_ifnameof( tp_name ) );
                    }
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' has already been defined.", lion_ifnameof( tp_name ) );
                }
            }
            else // unknown identifier --> creates a link
            {
                lion_sem_link_s* link = lion_sem_cell_s_push_link( o );
                lion_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
                link->name = tp_name;
                bcore_source_a_parse_fa( source, " =" );
                link->up = lion_sem_cell_s_evaluate_link( o, source );
            }

        }
        bcore_source_a_parse_fa( source, " ; " );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_sem_cell_s_evaluate_set_encs( lion_sem_cell_s* o, lion_sem_cell_s* parent, bcore_source* source )
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
            if( bcore_source_a_parse_bl_fa( source, " #?'='" ) )
            {
                lion_sem_link_s* link = lion_sem_cell_s_get_enc_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' specifies no entry channel of cell '#<sc_t>'.", name->sc, lion_ifnameof( o->name ) );
                }

                if( link->up )
                {
                    bcore_source_a_parse_err_fa( source, "Entry channel '#<sc_t>' of cell '#<sc_t>' has already been set.", name->sc, lion_ifnameof( o->name ) );
                }

                link->up = lion_sem_cell_s_evaluate_link( parent, source );
                done = true;
            }
            else
            {
                stack_push( stack, name );
            }
        }

        if( !done )
        {
            lion_sem_link_s* link = lion_sem_cell_s_get_enc_by_open( o );
            if( !link ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>': Number of free entry channels exceeded.", lion_ifnameof( o->name ) );
            link->up = lion_sem_cell_s_evaluate_link_stack( parent, stack, source );
        }

        first = false;
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/// in body of o: creates new cell wrapping the catenated cells: cell = { c1 : c2 }
lion_sem_cell_s* lion_sem_cell_s_cat_cell( lion_sem_cell_s* o, lion_sem_cell_s* c1, lion_sem_cell_s* c2, bcore_source* source )
{
    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell( o );
    bcore_source_point_s_set( &cell->source_point, source );

    c1 = lion_sem_cell_s_push_wrap_cell( cell, c1 );
    c2 = lion_sem_cell_s_push_wrap_cell( cell, c2 );

    // only free input channels get wrapped (code below must change in case wrapping scheme changes)
    assert( c1->encs.size == lion_sem_cell_s_get_arity( c1 ) );
    assert( c2->encs.size == lion_sem_cell_s_get_arity( c2 ) );

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
    lion_sem_cell_s_set_channels( cell, c1->excs.size, c2->encs.size );

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

void lion_sem_cell_s_evaluate_stack( lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BLM_INIT();
    st_s* name = BLM_CREATE( st_s );

    lion_sem_stack_flag_s* flag_bin_op    = BLM_CREATE( lion_sem_stack_flag_s );
    lion_sem_stack_flag_s* flag_una_op    = BLM_CREATE( lion_sem_stack_flag_s );
    lion_sem_stack_flag_s* flag_cell_cat  = BLM_CREATE( lion_sem_stack_flag_s );
    lion_sem_stack_flag_s* flag_inc_order = BLM_CREATE( lion_sem_stack_flag_s );

    tp_t op2_symbol = 0;

    while( !bcore_source_a_eos( source ) )
    {
        bl_t identifier = false;

        // immediately terminating identifiers (not being removed from stream)
        if( bcore_source_a_parse_bl_fa( source, " #=?'then'" ) ) break;
        if( bcore_source_a_parse_bl_fa( source, " #=?'else'" ) ) break;

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

            if( lion_is_control_type( tp_name ) )
            {
                if( tp_name == TYPEOF_cell ) // inline cell definition
                {
                    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell( o );
                    lion_sem_cell_s_parse( cell, source );
                    stack_push( stack, cell );
                }
                else if( tp_name == TYPEOF_if )
                {
                    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )lion_nop_ar3_branch_s_create(), source );
                    cell->encs.data[ 0 ]->up = lion_sem_cell_s_evaluate_link( o, source );
                    bcore_source_a_parse_fa( source, " #skip';' then" );
                    cell->encs.data[ 1 ]->up = lion_sem_cell_s_evaluate_link( o, source );
                    bcore_source_a_parse_fa( source, " #skip';' else" );
                    cell->encs.data[ 2 ]->up = lion_sem_cell_s_evaluate_link( o, source );
                    stack_push( stack, cell->excs.data[ 0 ] );
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Unexpected keyword '#<sc_t>'. Did you miss ';' after previous statement?", name->sc );
                }
            }
            else
            {
                vd_t item = lion_sem_cell_s_get_enc_by_name( o, tp_name );
                if( !item && o->body   ) item = lion_sem_body_s_get_sem_by_name( o->body, tp_name );
                if( !item && o->parent ) item = lion_sem_cell_s_get_cell_by_name( o->parent, tp_name );
                if( !item ) bcore_source_a_parse_err_fa( source, "Cannot evaluate identifier '#<sc_t>'.", name->sc );
                tp_t tp_item = *(aware_t*)item;

                switch( tp_item )
                {
                    case TYPEOF_lion_sem_cell_s:
                    {
                        lion_sem_cell_s* cell = item;
                        stack_push( stack, cell );
                    }
                    break;

                    case TYPEOF_lion_sem_link_s: stack_push( stack, item ); break;
                    default: bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name->sc, ifnameof( tp_item ) );
                }
            }
        }

        // literal scalar (negative numbers are created via neg operator)
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]>='0'&&[0]<='9')" ) )
        {
            f3_t val = 0;
            bcore_source_a_parse_fa( source, " #<f3_t*>", &val );
            lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_scalar( o, &val );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // undetermined scalar
        else if( bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
        {
            lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_scalar( o, NULL );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // block or input channel selection in case l-value is a cell
        else if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_lion_sem_cell_s ) )
            {
                lion_sem_cell_s* cell = lion_sem_cell_s_push_wrap_cell_set_source( o, stack_pop( stack ), source );
                lion_sem_cell_s_evaluate_set_encs( cell, o, source );
                stack_push( stack, cell );
            }
            else
            {
                bcore_source_a_parse_fa( source, " (" );
                stack_push( stack, lion_sem_cell_s_evaluate_sem( o, source ) );
                bcore_source_a_parse_fa( source, " )" );
            }
        }

        // binary operator from predefined symbols
        else if( ( op2_symbol = lion_parse_op2_symbol( source ) ) )
        {
            if
            (
                stack->size == 0 ||
               ( stack->size >= 1 && stack_of_value( stack, 1, flag_una_op ) ) ||
               ( stack->size >= 3 && stack_of_value( stack, 3, flag_bin_op ) )
            )
            {
                // binary op not applicable, try unary
                lion_sem_cell_s* cell = lion_sem_cell_s_get_cell_by_name( o, op2_symbol );
                lion_nop* nop_unary = lion_nop_a_create_op_of_arn( cell->nop, 1 );
                if( nop_unary )
                {
                    lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, nop_unary, source );
                    stack_push( stack, cell );
                    stack_push( stack, flag_una_op ); // flag after cell to avoid incorrect stack evaluation
                }
                else
                {
                    if( stack->size == 0 )
                    {
                        bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", lion_ifnameof( op2_symbol ) );
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Successive binary operator. Right operand expected.", lion_ifnameof( op2_symbol ) );
                    }
                }
            }
            else
            {
                lion_sem_cell_s* cell = lion_sem_cell_s_get_cell_by_name( o, op2_symbol );
                if( !cell ) bcore_source_a_parse_err_fa( source, "Syntax error." );
                cell = lion_sem_cell_s_push_wrap_cell_set_source( o, cell, source );
                stack_push( stack, flag_bin_op );
                stack_push( stack, cell );
            }
        }

        // custom binary operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'<<'" ) )
        {
            bcore_source_a_parse_fa( source, "#until'>'>>", name );
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", name->sc );
            lion_sem_cell_s* cell = lion_sem_cell_s_get_cell_by_name( o, typeof( name->sc ) );
            if( !cell ) bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>' not found.", name->sc );
            cell = lion_sem_cell_s_push_wrap_cell_set_source( o, cell, source );
            stack_push( stack, flag_bin_op );
            stack_push( stack, cell );
        }

        // output channel selection
        else if( bcore_source_a_parse_bl_fa( source, " #?'.'" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );

            if( !stack_of_type( stack, 1, TYPEOF_lion_sem_cell_s ) )
            {
                bcore_source_a_parse_err_fa( source, "Output channel selection on non-cell." );
            }

            lion_sem_cell_s* cell = stack_pop( stack );
            lion_sem_link_s* link = lion_sem_cell_s_get_exc_by_name( cell, typeof( name->sc ) );

            if( lion_sem_cell_s_get_arity( cell ) > 0 )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Output channel selection on cell '#<sc_t>' with #<sz_t> open input channels.",
                    lion_ifnameof( cell->name ),
                    lion_sem_cell_s_get_arity( cell )
                );
            }

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>': Invalid channel '#<sc_t>'.", lion_ifnameof( cell->name ), name->sc );
            }
            stack_push( stack, link );
        }

        // array operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'['" ) )
        {
            lion_sem_link_s* link = lion_sem_cell_s_evaluate_link( o, source );
            bcore_source_a_parse_bl_fa( source, " ]" );

            if( stack_of_type( stack, 1, TYPEOF_lion_sem_link_s ) )
            {
                lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )lion_nop_ar2_index_s_create(), source );
                cell->encs.data[ 0 ]->up = stack_pop_of_type( stack, TYPEOF_lion_sem_link_s, source );
                cell->encs.data[ 1 ]->up = link;
                stack_push( stack, cell->excs.data[ 0 ] );
            }
            else
            {
                lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )lion_nop_ar2_inc_order_s_create(), source );
                cell->encs.data[ 0 ]->up = link;
                stack_push( stack, cell );
                stack_push( stack, flag_inc_order );
            }
        }

        // postfix htp
        else if( bcore_source_a_parse_bl_fa( source, " #?'^t'" ) )
        {
            lion_sem_cell_s* htp_cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )lion_nop_ar1_cast_htp_s_create(), source );
            if( stack_of_type( stack, 1, TYPEOF_lion_sem_link_s ) )
            {
                htp_cell->encs.data[ 0 ]->up = stack_pop_of_type( stack, TYPEOF_lion_sem_link_s, source );
                stack_push( stack, htp_cell->excs.data[ 0 ] );
            }
            else if( stack_of_type( stack, 1, TYPEOF_lion_sem_cell_s ) )
            {
                lion_sem_cell_s* r_cell = stack_pop_of_type( stack, TYPEOF_lion_sem_cell_s, source );
                stack_push( stack, htp_cell );
                stack_push( stack, flag_cell_cat );
                stack_push( stack, r_cell );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "transposition ':': invalid l-value." );
            }
        }

        // cell catenation
        else if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_lion_sem_cell_s ) )
            {
                stack_push( stack, flag_cell_cat );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cell catenation ':': l-value is not a cell." );
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
        while( stack->size >= 3 && stack_of_value( stack, 2, flag_una_op ) && stack_of_type( stack, 1, TYPEOF_lion_sem_link_s ) )
        {
            lion_sem_link_s* link = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_una_op, source );
            lion_sem_cell_s* cell = stack_pop_cell( stack, source );
            ASSERT( cell->encs.size == 1 );
            cell->encs.data[ 0 ]->up = link;
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        if( stack->size >= 3 && stack_of_value( stack, 2, flag_bin_op ) )
        {
            lion_sem_cell_s* cell = stack_pop_of_type( stack, TYPEOF_lion_sem_cell_s, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            lion_sem* arg1 = stack_pop( stack );

            if( arg1->_ == TYPEOF_lion_sem_cell_s )
            {
                lion_sem_cell_s* cell1 = ( lion_sem_cell_s* )arg1;
                if( cell1->excs.size != 1 )
                {
                    bcore_source_point_s_parse_err_fa
                    (
                        &cell1->source_point,
                        "Binary operator '#<sc_t>': Left operant '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                        lion_ifnameof( cell->name ),
                        lion_ifnameof( cell1->name ),
                        cell1->excs.size
                    );
                }
                arg1 = ( lion_sem* )cell1->excs.data[ 0 ];
            }

            if( lion_sem_cell_s_get_arity( cell ) != 2 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has arity '#<sz_t>'. Expected: '2'.",
                    lion_ifnameof( cell->name ),
                    lion_sem_cell_s_get_arity( cell )
                );
            }

            if( cell->excs.size != 1 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                    lion_ifnameof( cell->name ),
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
            if( stack_of_type( stack, 1, TYPEOF_lion_sem_cell_s ) )  // cell1 : cell2
            {
                lion_sem_cell_s* cell2 = stack_pop_cell( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                lion_sem_cell_s* cell1 = stack_pop_cell( stack, source );
                stack_push( stack, lion_sem_cell_s_cat_cell( o, cell1, cell2, source ) );
            }
            else if( stack_of_type( stack, 1, TYPEOF_lion_sem_link_s ) ) // cell : link
            {
                lion_sem_link_s* link = stack_pop_link( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                lion_sem_cell_s* cell = stack_pop_cell( stack, source );
                cell = lion_sem_cell_s_push_wrap_cell( o, cell );
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
        while( stack_of_value( stack, 2, flag_inc_order ) && stack_of_type( stack, 1, TYPEOF_lion_sem_link_s ) )
        {
            lion_sem_link_s* link2 = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_inc_order, source );
            lion_sem_cell_s* cell  = stack_pop_cell( stack, source );
            ASSERT( cell->encs.data[ 0 ]->up ); // was set at cell creation
            cell->encs.data[ 1 ]->up = link2;
            stack_push( stack, cell->excs.data[ 0 ] );
        }
    }

    /// remaining stack processing ...

    /// Binary operators
    while( stack->size >= 5 && stack_of_value( stack, 4, flag_bin_op ) ) // <left arg> <flag> <bin-operator> <output> <right arg>
    {
        lion_sem_link_s* link2 = stack_pop_link_or_exit( stack, source );
        lion_sem_link_s* out   = stack_pop_link( stack, source );
        lion_sem_cell_s* cell  = stack_pop_cell( stack, source );
        stack_pop_of_value( stack, flag_bin_op, source );
        lion_sem_link_s* link1 = stack_pop_link_or_exit( stack, source );

        if( stack->size >= 4 && stack_of_value( stack, 3, flag_bin_op ) ) // merge with prior operation considering priority
        {
            lion_sem_link_s* prior_out   = stack_pop_link( stack, source );
            lion_sem_cell_s* prior_cell  = stack_pop_cell( stack, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            lion_sem_link_s* prior_link1 = stack_pop_link_or_exit( stack, source );

            sz_t prior_priority = lion_sem_cell_s_get_priority( prior_cell );
            sz_t cell_priority  = lion_sem_cell_s_get_priority( cell );

            if( prior_priority >= cell_priority  )
            {
                lion_sem_cell_s_get_enc_by_open( cell )->up = prior_out;
                lion_sem_cell_s_get_enc_by_open( cell )->up = link2;

                stack_push( stack, prior_link1 );
                stack_push( stack, flag_bin_op );
                stack_push( stack, prior_cell );
                stack_push( stack, out );
                stack_push( stack, link1 );
            }
            else
            {
                lion_sem_cell_s_get_enc_by_open( cell )->up = link1;
                lion_sem_cell_s_get_enc_by_open( cell )->up = link2;

                stack_push( stack, prior_link1 );
                stack_push( stack, flag_bin_op );
                stack_push( stack, prior_cell );
                stack_push( stack, prior_out );
                stack_push( stack, out );           // out becomes right argument for prior_cell
            }
        }
        else // fully resolve operation
        {
            lion_sem_cell_s_get_enc_by_open( cell )->up = link1;
            lion_sem_cell_s_get_enc_by_open( cell )->up = link2;
            stack_push( stack, out );
        }
    }

    /// Adjacent holors
    while( stack->size >= 2 && stack_of_type( stack, 1, TYPEOF_lion_sem_link_s ) && stack_of_type( stack, 2, TYPEOF_lion_sem_link_s ) )
    {
        lion_sem_link_s* link2 = stack_pop_link( stack, source );
        lion_sem_link_s* link1 = stack_pop_link( stack, source );
        lion_sem_cell_s* cell = lion_sem_cell_s_push_cell_nop_d_reset_name_set_source( o, ( lion_nop* )lion_nop_ar2_cat_s_create(), source );
        cell->encs.data[ 0 ]->up = link1;
        cell->encs.data[ 1 ]->up = link2;
        stack_push( stack, cell->excs.data[ 0 ] );
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem* lion_sem_cell_s_evaluate_sem_stack( lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    lion_sem_cell_s_evaluate_stack( o, stack, source );
    if( stack->size != 1 ) bcore_source_a_parse_err_fa( source, "Expression syntax error." );
    return stack_pop( stack );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem* lion_sem_cell_s_evaluate_sem( lion_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    vd_t ret = lion_sem_cell_s_evaluate_sem_stack( o, stack, source );
    BLM_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_link_s* lion_sem_cell_s_evaluate_link_stack( lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    lion_sem* ret = lion_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret == TYPEOF_lion_sem_cell_s )
    {
        lion_sem_cell_s* cell = ( lion_sem_cell_s* )ret;
        if( lion_sem_cell_s_get_arity( cell ) > 0 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> open entry channels.", lion_sem_cell_s_get_arity( cell ) );
        }

        if( cell->excs.size != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> exit channels.", cell->excs.size );
        }

        ret = ( lion_sem* )cell->excs.data[ 0 ];
    }

    if( *( aware_t* )ret != TYPEOF_lion_sem_link_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Link expected.", ifnameof( *( aware_t* )ret ) );
    }

    return ( lion_sem_link_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_link_s* lion_sem_cell_s_evaluate_link( lion_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    lion_sem_link_s* ret = lion_sem_cell_s_evaluate_link_stack( o, stack, source );
    BLM_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_evaluate_cell_stack( lion_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    lion_sem* ret = lion_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret != TYPEOF_lion_sem_cell_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Cell Expected.", ifnameof( *( aware_t* )ret ) );
    }
    return ( lion_sem_cell_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_sem_cell_s* lion_sem_cell_s_evaluate_cell( lion_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    lion_sem_cell_s* ret = lion_sem_cell_s_evaluate_cell_stack( o, stack, source );
    BLM_RETURNV( lion_sem_cell_s*, ret );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_sem_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_sem" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
            lion_sem_context_s_detach( &context_g );
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "lion_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


