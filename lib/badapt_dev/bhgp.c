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

#include "bcore_std.h"
#include "bmath_std.h"
#include "bmath_plot.h"
#include "bhgp.h"

#define DEV_CODE_SECTION

/**********************************************************************************************************************/
/// Prototypes


// ---------------------------------------------------------------------------------------------------------------------
// sem_cell

void bhgp_sem_cell_s_create_args_out( bhgp_sem_cell_s* o, bcore_source* source );
void bhgp_sem_cell_s_create_args_in(  bhgp_sem_cell_s* o, bhgp_sem_cell_s* frame, bcore_source* source );
void bhgp_sem_cell_s_parse_body(      bhgp_sem_cell_s* o, bcore_source* source );
void bhgp_sem_cell_s_wrap_cell(       bhgp_sem_cell_s* o, bhgp_sem_cell_s* cell );

void             bhgp_sem_cell_s_parse(               bhgp_sem_cell_s* o,                        bcore_source* source );
bhgp_sem*        bhgp_sem_cell_s_evaluate_sem(        bhgp_sem_cell_s* o,                        bcore_source* source );
bhgp_sem*        bhgp_sem_cell_s_evaluate_sem_stack(  bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
bhgp_sem_cell_s* bhgp_sem_cell_s_evaluate_cell(       bhgp_sem_cell_s* o,                        bcore_source* source );
bhgp_sem_cell_s* bhgp_sem_cell_s_evaluate_cell_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
bhgp_sem_link_s* bhgp_sem_cell_s_evaluate_link(       bhgp_sem_cell_s* o,                        bcore_source* source );
bhgp_sem_link_s* bhgp_sem_cell_s_evaluate_link_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
bhgp_sem_cell_s* bhgp_sem_cell_s_push_cell_op_d(      bhgp_sem_cell_s* o, bhgp_op* op );
void             bhgp_sem_cell_s_set_channels(        bhgp_sem_cell_s* o, sz_t excs, sz_t encs );

bhgp_net_cell_s* bhgp_net_cell_s_create_from_sem_link( bhgp_sem_link_s* sem_link );

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// context

static bhgp_context_s* context_g = NULL;

// ---------------------------------------------------------------------------------------------------------------------

tp_t bhgp_entypeof( sc_t name );

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_context_setup()
{
    if( context_g ) return;
    context_g = bhgp_context_s_create();

    BLM_INIT();
    BCORE_LIFE_CREATE( bcore_arr_tp_s, arr_tp );

    bcore_push_traits_of_ancestor( TYPEOF_bhgp_op_ar1, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_bhgp_op_ar2, arr_tp );

    for( sz_t i = 0; i < arr_tp->size; i++ )
    {
        bhgp_op* op = bhgp_op_t_create( arr_tp->data[ i ] );
        sc_t symbol = bhgp_op_a_get_symbol( op );
        if( symbol )
        {
            sz_t arity = bhgp_op_a_get_arity( op );
            bcore_hmap_name_s_set_sc( &context_g->hmap_name, symbol );
            switch( arity )
            {
                case 2: bcore_arr_st_s_push_sc( &context_g->arr_symbol_op2, symbol ); break;
                default: break;
            }
            bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell_op_d( &context_g->cell, op );
            cell->name = typeof( symbol );
        }
        else
        {
            bhgp_op_a_detach( &op );
        }
    }

    /** We sort the array in descending manner; this ensures that short symbols
     *  which patterns match the beginning of a longer symbol can not occlude the longer one.
     */
    bcore_array_a_sort( (bcore_array*)&context_g->arr_symbol_op2, 0, -1, -1 );

    /// register control types
    bcore_arr_tp_s_push( &context_g->control_types, bhgp_entypeof( "cell" ) );
    bcore_arr_tp_s_push( &context_g->control_types, bhgp_entypeof( "if" ) );
    bcore_arr_tp_s_push( &context_g->control_types, bhgp_entypeof( "then" ) );
    bcore_arr_tp_s_push( &context_g->control_types, bhgp_entypeof( "else" ) );

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_context_down()
{
    if( context_g ) bhgp_context_s_detach( &context_g );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t bhgp_nameof( tp_t name )
{
    if( !context_g ) bhgp_context_setup();
    return bcore_hmap_name_s_get_sc( &context_g->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t bhgp_ifnameof( tp_t name )
{
    sc_t sc = bhgp_nameof( name );
    return sc ? sc : "";
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bhgp_entypeof( sc_t name )
{
    if( !context_g ) bhgp_context_setup();
    return bcore_hmap_name_s_set_sc( &context_g->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bhgp_entypeof_fv( sc_t format, va_list args )
{
    st_s* s = st_s_create_fv( format, args );
    tp_t tp = bhgp_entypeof( s->sc );
    st_s_discard( s );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bhgp_entypeof_fa( sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    tp_t tp = bhgp_entypeof_fv( format, args );
    va_end( args );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bhgp_parse_name( bcore_source* source )
{
    st_s* name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", name );
    if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
    tp_t tp_name = bhgp_entypeof( name->sc );
    st_s_discard( name );
    return tp_name;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bhgp_parse_op2_symbol( bcore_source* source )
{
    if( !context_g ) bhgp_context_setup();
    bcore_arr_st_s* arr = &context_g->arr_symbol_op2;

    st_s* format = st_s_create();
    tp_t ret = 0;

    for( sz_t i = 0; i < arr->size; i++ )
    {
        st_s_copy_fa( format, " ##?'#<sc_t>'", arr->data[ i ]->sc );
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

tp_t bhgp_is_control_type( tp_t name )
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

static bhgp_sem_link_s* stack_pop_link( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_bhgp_sem_link_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static bhgp_sem_cell_s* stack_pop_cell( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_bhgp_sem_cell_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static bhgp_sem_link_s* stack_pop_link_or_exit( bcore_arr_vd_s* o, bcore_source* source )
{
    vd_t v = stack_pop( o );
    tp_t t = *(aware_t*)v;
    if( t == TYPEOF_bhgp_sem_link_s ) return v;
    if( t == TYPEOF_bhgp_sem_cell_s )
    {
        bhgp_sem_cell_s* cell = v;
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
/// bhgp_op_ar2

s2_t bhgp_op_ar1_solve_unary( bmath_hf3_s** r, bmath_hf3_s** a, bmath_fp_f3_ar1 unary )
{
    bmath_hf3_s_attach( r, a[0] ? bmath_hf3_s_create() : NULL );
    if( a[0] )
    {
        bmath_hf3_s_copy_size( *r, a[0] );
        if( a[0]->v_size ) bmath_hf3_s_fp_f3_ar1( a[0], unary, *r );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}


/**********************************************************************************************************************/
/// bhgp_op_ar2

// ---------------------------------------------------------------------------------------------------------------------

bmath_hf3_vm_op* bhgp_op_ar2_mul_s_create_vm_op_ar2( const bhgp_op_ar2_mul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r )
{
    if( a->d_size == 0 )
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_scl_mul_s_create();
    }
    else if( b->d_size == 0 )
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_mul_scl_s_create();
    }
    else
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_ar2_hmul_s_create();
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// sem_link

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_link_s* bhgp_sem_link_s_create_setup( tp_t name, bhgp_sem_link_s* up, bhgp_sem_link_s* dn, bhgp_sem_cell_s* cell, bl_t exit )
{
    bhgp_sem_link_s* o = bhgp_sem_link_s_create();
    o->name = name;
    o->up = up;
    o->dn = dn;
    o->cell = cell;
    o->exit = exit;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next membrane; returns NULL in case trace ends in open link
bhgp_sem_link_s* bhgp_sem_link_s_trace_to_cell_membrane( bhgp_sem_link_s* o )
{
    if( !o || o->cell ) return o;
    return bhgp_sem_link_s_trace_to_cell_membrane( o->up );
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next cell; returns NULL in case trace ends in open link
bhgp_sem_cell_s* bhgp_sem_link_s_trace_to_cell( bhgp_sem_link_s* o )
{
    bhgp_sem_link_s* link = bhgp_sem_link_s_trace_to_cell_membrane( o );
    if( link )
    {
        if( link->cell ) assert( *(aware_t*)link->cell == TYPEOF_bhgp_sem_cell_s );
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

void bhgp_sem_cell_s_set_channels( bhgp_sem_cell_s* o, sz_t excs, sz_t encs )
{
    bhgp_sem_links_s_set_size( &o->excs, excs );
    bhgp_sem_links_s_set_size( &o->encs, encs );
    for( sz_t i = 0; i < excs; i++ )
    {
        o->excs.data[ i ] = bhgp_sem_link_s_create_setup( 0, NULL, NULL, o, true );
    }
    for( sz_t i = 0; i < encs; i++ )
    {
        o->encs.data[ i ] = bhgp_sem_link_s_create_setup( 0, NULL, NULL, o, false );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_wrap_cell( bhgp_sem_cell_s* o, bhgp_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->op   );
    o->priority = src->priority;
    bhgp_sem_links_s_set_size( &o->encs, bhgp_sem_cell_s_get_arity( src ) );
    bhgp_sem_links_s_set_size( &o->excs, src->excs.size );

    sz_t k = 0;
    for( sz_t i = 0; i < src->encs.size; i++ )
    {
        if( !src->encs.data[ i ]->up )
        {
            o->encs.data[ k++ ] = bhgp_sem_link_s_create_setup( src->encs.data[ i ]->name, NULL, src->encs.data[ i ], o, false );
        }
    }

    assert( k == o->encs.size );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        o->excs.data[ i ] = bhgp_sem_link_s_create_setup( src->excs.data[ i ]->name, src->excs.data[ i ], NULL, o, true );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem* bhgp_sem_cell_s_push_sem( bhgp_sem_cell_s* o, tp_t type )
{
    if( !o->body ) o->body = bhgp_sem_body_s_create();
    return bhgp_sem_body_s_push_t( o->body, type );
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_cell_s* bhgp_sem_cell_s_push_cell( bhgp_sem_cell_s* o )
{
    bhgp_sem_cell_s* cell = ( bhgp_sem_cell_s* )bhgp_sem_cell_s_push_sem( o, TYPEOF_bhgp_sem_cell_s );
    cell->parent = o;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_link_s* bhgp_sem_cell_s_push_link( bhgp_sem_cell_s* o )
{
    bhgp_sem_link_s* link = ( bhgp_sem_link_s* )bhgp_sem_cell_s_push_sem( o, TYPEOF_bhgp_sem_link_s );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * Channel naming:
 * Output channel has name 'y'
 * Input channels are named in order 'a', 'b' ...
 * If ever more than 24 input channels are used, excess channels carry no name.
 */
bhgp_sem_cell_s* bhgp_sem_cell_s_push_cell_op_d( bhgp_sem_cell_s* o, bhgp_op* op )
{
    bhgp_sem_cell_s* cell = ( bhgp_sem_cell_s* )bhgp_sem_cell_s_push_cell( o );
    bhgp_sem_cell_s_set_channels( cell, 1, bhgp_op_a_get_arity( op ) );
    sc_t symbol = bhgp_op_a_get_symbol( op );
    if( symbol ) cell->name = bhgp_entypeof( symbol );
    cell->op = op;
    cell->priority = bhgp_op_a_get_priority( op );

    cell->excs.data[ 0 ]->name = bhgp_entypeof( "y" );

    for( sz_t i = 0; i < cell->encs.size; i++ )
    {
        if( i < 'y' - 'a' )
        {
            cell->encs.data[ 0 ]->name = bhgp_entypeof_fa( "#<char>", 'a' + i );
        }
    }

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

/// v can be NULL pushing an undetermined scalar
bhgp_sem_cell_s* bhgp_sem_cell_s_push_cell_scalar( bhgp_sem_cell_s* o, f3_t* v )
{
    bhgp_op_ar0_holor_s* holor = bhgp_op_ar0_holor_s_create();
    holor->h = bmath_hf3_s_create();
    bmath_hf3_s_set_scalar_pf3( holor->h, v );
    return bhgp_sem_cell_s_push_cell_op_d( o, ( bhgp_op* )holor );
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_cell_s* bhgp_sem_cell_s_push_wrap_cell( bhgp_sem_cell_s* o, bhgp_sem_cell_s* src )
{
    bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell( o );
    bhgp_sem_cell_s_wrap_cell( cell, src );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_assert_identifier_not_yet_defined( const bhgp_sem_cell_s* o, tp_t name, bcore_source* source )
{
    if
    (
        bhgp_sem_links_s_name_exists( &o->encs, name ) ||
        ( o->body && bhgp_sem_body_s_name_exists( o->body, name ) )
    )
    {
        bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' already exists.", bhgp_ifnameof( name ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static bhgp_sem_cell_s* sem_cell_s_create_frame()
{
    if( !context_g ) bhgp_context_setup();
    bhgp_sem_cell_s* o = bhgp_sem_cell_s_create();
    o->parent = &context_g->cell;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------
/*
static bhgp_sem_cell_s* sem_cell_s_create_frame_parse( bcore_source* source )
{
    bhgp_sem_cell_s* o = sem_cell_s_create_root();
    bcore_source_point_s_set( &o->source_point, source );
    bhgp_sem_cell_s_parse( o, source );
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

static bhgp_sem_cell_s* sem_cell_s_create_frame_parse_body( bcore_source* source )
{
    bhgp_sem_cell_s* o = sem_cell_s_create_frame();
    bcore_source_point_s_set( &o->source_point, source );
    bhgp_sem_cell_s_parse_body( o, source );
    return o;
}
*/

// ---------------------------------------------------------------------------------------------------------------------

/// parses ( ... => ... )
void bhgp_sem_cell_s_parse_signature( bhgp_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );

    // parse excs
    {
        ASSERT( o->excs.size == 0 );
        bl_t first = true;
        while( !bcore_source_a_parse_bl_fa( source, " #?'=>'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            bhgp_sem_link_s* link = bhgp_sem_link_s_create_setup( bhgp_parse_name( source ), NULL, NULL, o, true );
            bhgp_sem_links_s_push_d( &o->excs, link );
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
            bhgp_sem_link_s* link = bhgp_sem_link_s_create_setup( bhgp_parse_name( source ), NULL, NULL, o, false );
            if( bcore_source_a_parse_bl_fa( source, " #?'='" ) )
            {
                link->up = bhgp_sem_cell_s_evaluate_link( o->parent, source );
            }
            bhgp_sem_links_s_push_d( &o->encs, link );
            first = false;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_parse( bhgp_sem_cell_s* o, bcore_source* source )
{
    bhgp_sem_cell_s* frame = o->parent;

    // cell signature without name is allowed
    if( !bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        tp_t tp_cell_name = bhgp_parse_name( source );
        if( frame ) bhgp_sem_cell_s_assert_identifier_not_yet_defined( frame, tp_cell_name, source );
        o->name = tp_cell_name;
    }

    bcore_source_point_s_set( &o->source_point, source );

    //  ( <args_out> => <args_in> ) { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        bhgp_sem_cell_s_parse_signature( o, source );
        bcore_source_a_parse_fa( source, " {" );
        bhgp_sem_cell_s_parse_body( o, source );
        bcore_source_a_parse_fa( source, " }" );
    }
    else // = 'expression yielding a cell'
    {
        bcore_source_a_parse_fa( source, " = " );
        bhgp_sem_cell_s* cell = bhgp_sem_cell_s_evaluate_cell( frame, source );
        bhgp_sem_cell_s_wrap_cell( o, cell );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

st_s* bhgp_sem_cell_s_create_signature( const bhgp_sem_cell_s* o )
{
    st_s* s = st_s_create();
    st_s_push_fa( s, "(" );
    BFOR_EACH( &o->excs, i ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", bhgp_ifnameof( o->excs.data[ i ]->name ) );
    st_s_push_fa( s, "=>" );
    BFOR_EACH( &o->encs, i ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", bhgp_ifnameof( o->encs.data[ i ]->name ) );
    st_s_push_fa( s, ")" );
    return s;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_parse_verify_signature( const bhgp_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );

    // parse excs
    {
        bl_t first = true;
        sz_t index= 0;
        bl_t err = false;
        while( !err && !bcore_source_a_parse_bl_fa( source, " #?'=>'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            tp_t name = bhgp_parse_name( source );
            if( !err ) err = ( index >= o->excs.size );
            if( !err ) err = o->excs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->excs.size;
        if( err )
        {
            st_s* sig = bhgp_sem_cell_s_create_signature( o );
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
            tp_t name = bhgp_parse_name( source );
            if( !err ) err = ( index >= o->encs.size );
            if( !err ) err = o->encs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->encs.size;
        if( err )
        {
            st_s* sig = bhgp_sem_cell_s_create_signature( o );
            bcore_source_a_parse_err_fa( source, "Cell signature is '#<sc_t>'", sig->sc );
            st_s_discard( sig );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_parse_body( bhgp_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " " );
    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #=?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'cell'" ) )
        {
            bhgp_sem_cell_s_parse( bhgp_sem_cell_s_push_cell( o ), source );
        }
        if( bcore_source_a_parse_bl_fa( source, " #?'verify_signature'" ) )
        {
            bhgp_sem_cell_s_parse_verify_signature( o, source );
        }
        else
        {
            tp_t tp_name = bhgp_parse_name( source );

            vd_t item = NULL;
            if( ( item = bhgp_sem_cell_s_get_exc_by_name( o, tp_name ) ) )
            {
                bhgp_sem_link_s* link = item;
                if( link->up )
                {
                    bcore_source_a_parse_err_fa( source, "Channel '#<sc_t>' of cell '#<sc_t>' has already been defined.", bhgp_ifnameof( tp_name ), bhgp_ifnameof( o->name ) );
                }
                bcore_source_a_parse_fa( source, " =" );
                link->up = bhgp_sem_cell_s_evaluate_link( o, source );
            }
            else // unknown identifier --> creates a link
            {
                bhgp_sem_link_s* link = bhgp_sem_cell_s_push_link( o );
                bhgp_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
                link->name = tp_name;
                bcore_source_a_parse_fa( source, " =" );
                link->up = bhgp_sem_cell_s_evaluate_link( o, source );
            }

        }
        bcore_source_a_parse_fa( source, " ; " );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_evaluate_set_encs( bhgp_sem_cell_s* o, bhgp_sem_cell_s* parent, bcore_source* source )
{
    BLM_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    BCORE_LIFE_CREATE( st_s, name );

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
                bhgp_sem_link_s* link = bhgp_sem_cell_s_get_enc_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' specifies no entry channel of cell '#<sc_t>'.", name->sc, bhgp_ifnameof( o->name ) );
                }

                if( link->up )
                {
                    bcore_source_a_parse_err_fa( source, "Entry channel '#<sc_t>' of cell '#<sc_t>' has already been set.", name->sc, bhgp_ifnameof( o->name ) );
                }

                link->up = bhgp_sem_cell_s_evaluate_link( parent, source );
                done = true;
            }
            else
            {
                stack_push( stack, name );
            }
        }

        if( !done )
        {
            bhgp_sem_link_s* link = bhgp_sem_cell_s_get_enc_by_open( o );
            if( !link ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>': Number of free entry channels exceeded.", bhgp_ifnameof( o->name ) );
            link->up = bhgp_sem_cell_s_evaluate_link_stack( parent, stack, source );
        }

        first = false;
    }

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/// in body of o: creates new cell wrapping the catenated cells: cell = { c1 : c2 }
bhgp_sem_cell_s* bhgp_sem_cell_s_cat_cell( bhgp_sem_cell_s* o, bhgp_sem_cell_s* c1, bhgp_sem_cell_s* c2, bcore_source* source )
{
    bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell( o );
    bcore_source_point_s_set( &cell->source_point, source );

    c1 = bhgp_sem_cell_s_push_wrap_cell( cell, c1 );
    c2 = bhgp_sem_cell_s_push_wrap_cell( cell, c2 );

    // only free input channels get wrapped (code below must change in case wrapping scheme changes)
    assert( c1->encs.size == bhgp_sem_cell_s_get_arity( c1 ) );
    assert( c2->encs.size == bhgp_sem_cell_s_get_arity( c2 ) );

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
    bhgp_sem_cell_s_set_channels( cell, c1->excs.size, c2->encs.size );

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
        cell->excs.data[ i ]->up = c1->excs.data[ i ];
        cell->excs.data[ i ]->name = c1->excs.data[ i ]->name;
    }

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_evaluate_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BLM_INIT();
    BCORE_LIFE_CREATE( st_s, name );

    BCORE_LIFE_CREATE( bhgp_sem_stack_flag_s, flag_bin_op    );
    BCORE_LIFE_CREATE( bhgp_sem_stack_flag_s, flag_cell_cat  );
    BCORE_LIFE_CREATE( bhgp_sem_stack_flag_s, flag_inc_order );

    tp_t op2_symbol = 0;
    bmath_hf3_s* literal = NULL;

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

            if( bhgp_is_control_type( tp_name ) )
            {
                if( tp_name == TYPEOF_cell ) // inline cell definition
                {
                    bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell( o );
                    bhgp_sem_cell_s_parse( cell, source );
                    stack_push( stack, cell );
                }
                else if( tp_name == TYPEOF_if )
                {
                    bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell_op_d( o, ( bhgp_op* )bhgp_op_ar3_branch_s_create() );
                    bcore_source_point_s_set( &cell->source_point, source );
                    cell->encs.data[ 0 ]->up = bhgp_sem_cell_s_evaluate_link( o, source );
                    bcore_source_a_parse_fa( source, " #skip';' then" );
                    cell->encs.data[ 1 ]->up = bhgp_sem_cell_s_evaluate_link( o, source );
                    bcore_source_a_parse_fa( source, " #skip';' else" );
                    cell->encs.data[ 2 ]->up = bhgp_sem_cell_s_evaluate_link( o, source );
                    stack_push( stack, cell->excs.data[ 0 ] );
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Unexpected keyword '#<sc_t>'. Forgot ';' on previous statement?", name->sc );
                }
            }
            else
            {
                vd_t item = bhgp_sem_cell_s_get_enc_by_name( o, tp_name );
                if( !item && o->body   ) item = bhgp_sem_body_s_get_sem_by_name( o->body, tp_name );
                if( !item && o->parent ) item = bhgp_sem_cell_s_get_cell_by_name( o->parent, tp_name );
                if( !item ) bcore_source_a_parse_err_fa( source, "Cannot evaluate identifier '#<sc_t>'.", name->sc );
                tp_t tp_item = *(aware_t*)item;

                switch( tp_item )
                {
                    case TYPEOF_bhgp_sem_cell_s:
                    {
                        bhgp_sem_cell_s* cell = item;
                        stack_push( stack, cell );
                    }
                    break;

                    case TYPEOF_bhgp_sem_link_s: stack_push( stack, item ); break;
                    default: bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name->sc, ifnameof( tp_item ) );
                }
            }
        }

        // literal scalar
        else if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='0'&&[0]<='9')||([0]=='-'&&([1]>='0'&&[1]<='9')))" ) )
        {
            f3_t val = 0;
            bcore_source_a_parse_fa( source, " #<f3_t*>", &val );
            bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell_scalar( o, &val );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // undetermined scalar
        else if( bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
        {
            bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell_scalar( o, NULL );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // block or input channel selection in case l-value is a cell
        else if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_cell_s ) )
            {
                bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_wrap_cell( o, stack_pop( stack ) );
                bcore_source_point_s_set( &cell->source_point, source );
                bhgp_sem_cell_s_evaluate_set_encs( cell, o, source );
                stack_push( stack, cell );
            }
            else
            {
                bcore_source_a_parse_fa( source, " (" );
                stack_push( stack, bhgp_sem_cell_s_evaluate_sem( o, source ) );
                bcore_source_a_parse_fa( source, " )" );
            }

        }

        // binary operator from predefined symbols
        else if( ( op2_symbol = bhgp_parse_op2_symbol( source ) ) )
        {
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", op2_symbol );
            bhgp_sem_cell_s* cell = bhgp_sem_cell_s_get_cell_by_name( o, op2_symbol );
            if( !cell ) bcore_source_a_parse_err_fa( source, "Syntax error." );
            cell = bhgp_sem_cell_s_push_wrap_cell( o, cell );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, flag_bin_op );
            stack_push( stack, cell );
        }

        // custom binary operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'<<'" ) )
        {
            bcore_source_a_parse_fa( source, "#until'>'>>", name );
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", name->sc );
            bhgp_sem_cell_s* cell = bhgp_sem_cell_s_get_cell_by_name( o, typeof( name->sc ) );
            if( !cell ) bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>' not found.", name->sc );
            cell = bhgp_sem_cell_s_push_wrap_cell( o, cell );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, flag_bin_op );
            stack_push( stack, cell );
        }

        // output channel selection
        else if( bcore_source_a_parse_bl_fa( source, " #?'.'" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );

            if( !stack_of_type( stack, 1, TYPEOF_bhgp_sem_cell_s ) )
            {
                bcore_source_a_parse_err_fa( source, "Output channel selection on non-cell." );
            }

            bhgp_sem_cell_s* cell = stack_pop( stack );
            bhgp_sem_link_s* link = bhgp_sem_cell_s_get_exc_by_name( cell, typeof( name->sc ) );

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>':Invalid channel '#<sc_t>'.", bhgp_ifnameof( cell->name ), name->sc );
            }
            stack_push( stack, link );
        }

        // array operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'['" ) )
        {
            bhgp_sem_link_s* link = bhgp_sem_cell_s_evaluate_link( o, source );
            bcore_source_a_parse_bl_fa( source, " ]" );

            if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_link_s ) )
            {
                bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell_op_d( o, ( bhgp_op* )bhgp_op_ar2_index_s_create() );
                bcore_source_point_s_set( &cell->source_point, source );
                cell->encs.data[ 0 ]->up = stack_pop_of_type( stack, TYPEOF_bhgp_sem_link_s, source );
                cell->encs.data[ 1 ]->up = link;
                stack_push( stack, cell->excs.data[ 0 ] );
            }
            else
            {
                stack_push( stack, link );
                stack_push( stack, flag_inc_order );
            }
        }

        // cell catenation
        else if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_cell_s ) )
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

        // <left arg> <flag> <bin-operator>  error checks, left operand conversion, output generation
        if( stack->size >= 3 && stack_of_value( stack, 2, flag_bin_op ) )
        {
            bhgp_sem_cell_s* cell = stack_pop_of_type( stack, TYPEOF_bhgp_sem_cell_s, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            bhgp_sem* arg1 = stack_pop( stack );

            if( arg1->_ == TYPEOF_bhgp_sem_cell_s )
            {
                bhgp_sem_cell_s* cell1 = ( bhgp_sem_cell_s* )arg1;
                if( cell1->excs.size != 1 )
                {
                    bcore_source_point_s_parse_err_fa
                    (
                        &cell1->source_point,
                        "Binary operator '#<sc_t>': Left operant '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                        bhgp_ifnameof( cell->name ),
                        bhgp_ifnameof( cell1->name ),
                        cell1->excs.size
                    );
                }
                arg1 = ( bhgp_sem* )cell1->excs.data[ 0 ];
            }

            if( bhgp_sem_cell_s_get_arity( cell ) != 2 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has arity '#<sz_t>'. Expected: '2'.",
                    bhgp_ifnameof( cell->name ),
                    bhgp_sem_cell_s_get_arity( cell )
                );
            }

            if( cell->excs.size != 1 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                    bhgp_ifnameof( cell->name ),
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
            if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_cell_s ) )  // cell1 : cell2
            {
                bhgp_sem_cell_s* cell2 = stack_pop_cell( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                bhgp_sem_cell_s* cell1 = stack_pop_cell( stack, source );
                stack_push( stack, bhgp_sem_cell_s_cat_cell( o, cell1, cell2, source ) );
            }
            else if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_link_s ) ) // cell : link
            {
                bhgp_sem_link_s* link = stack_pop_link( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                bhgp_sem_cell_s* cell = stack_pop_cell( stack, source );
                cell = bhgp_sem_cell_s_push_wrap_cell( o, cell );
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
        while( stack_of_value( stack, 2, flag_inc_order ) && stack_of_type( stack, 1, TYPEOF_bhgp_sem_link_s ) )
        {
            bhgp_sem_link_s* link2 = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_inc_order, source );
            bhgp_sem_link_s* link1 = stack_pop_link( stack, source );
            bhgp_sem_cell_s* cell = bhgp_sem_cell_s_push_cell_op_d( o, ( bhgp_op* )bhgp_op_ar2_inc_order_s_create() );
            bcore_source_point_s_set( &cell->source_point, source );
            cell->encs.data[ 0 ]->up = link1;
            cell->encs.data[ 1 ]->up = link2;
            stack_push( stack, cell->excs.data[ 0 ] );
        }
    }

    /// remaining stack processing ...
    bl_t resolve_stack = true;
    while( resolve_stack )
    {
        // <left arg> <flag> <bin-operator> <output> <right arg>
        if( stack->size >= 5 && stack_of_value( stack, 4, flag_bin_op ) )
        {
            bhgp_sem_link_s* link2 = stack_pop_link_or_exit( stack, source );
            bhgp_sem_link_s* out   = stack_pop_link( stack, source );
            bhgp_sem_cell_s* cell  = stack_pop_cell( stack, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            bhgp_sem_link_s* link1 = stack_pop_link_or_exit( stack, source );

            if( stack->size >= 4 && stack_of_value( stack, 3, flag_bin_op ) ) // merge with prior operation considering priority
            {
                bhgp_sem_link_s* prior_out   = stack_pop_link( stack, source );
                bhgp_sem_cell_s* prior_cell  = stack_pop_cell( stack, source );
                stack_pop_of_value( stack, flag_bin_op, source );
                bhgp_sem_link_s* prior_link1 = stack_pop_link_or_exit( stack, source );

                sz_t prior_priority = bhgp_sem_cell_s_get_priority( prior_cell );
                sz_t cell_priority  = bhgp_sem_cell_s_get_priority( cell );

                if( prior_priority >= cell_priority  )
                {
                    bhgp_sem_cell_s_get_enc_by_open( cell )->up = prior_out;
                    bhgp_sem_cell_s_get_enc_by_open( cell )->up = link2;

                    stack_push( stack, prior_link1 );
                    stack_push( stack, flag_bin_op );
                    stack_push( stack, prior_cell );
                    stack_push( stack, out );
                    stack_push( stack, link1 );
                }
                else
                {
                    bhgp_sem_cell_s_get_enc_by_open( cell )->up = link1;
                    bhgp_sem_cell_s_get_enc_by_open( cell )->up = link2;

                    stack_push( stack, prior_link1 );
                    stack_push( stack, flag_bin_op );
                    stack_push( stack, prior_cell );
                    stack_push( stack, prior_out );
                    stack_push( stack, out );           // out becomes right argument for prior_cell
                }
            }
            else // fully resolve operation
            {
                bhgp_sem_cell_s_get_enc_by_open( cell )->up = link1;
                bhgp_sem_cell_s_get_enc_by_open( cell )->up = link2;
                stack_push( stack, out );
            }
        }
        else
        {
            resolve_stack = false;
        }
    }

    bmath_hf3_s_detach( &literal );
    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem* bhgp_sem_cell_s_evaluate_sem_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    bhgp_sem_cell_s_evaluate_stack( o, stack, source );
    if( stack->size != 1 ) bcore_source_a_parse_err_fa( source, "Expression syntax error." );
    return stack_pop( stack );
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem* bhgp_sem_cell_s_evaluate_sem( bhgp_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    vd_t ret = bhgp_sem_cell_s_evaluate_sem_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_link_s* bhgp_sem_cell_s_evaluate_link_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    bhgp_sem* ret = bhgp_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret == TYPEOF_bhgp_sem_cell_s )
    {
        bhgp_sem_cell_s* cell = ( bhgp_sem_cell_s* )ret;
        if( bhgp_sem_cell_s_get_arity( cell ) > 0 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> open entry channels.", bhgp_sem_cell_s_get_arity( cell ) );
        }

        if( cell->excs.size != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> exit channels.", cell->excs.size );
        }

        ret = ( bhgp_sem* )cell->excs.data[ 0 ];
    }

    if( *( aware_t* )ret != TYPEOF_bhgp_sem_link_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Link expected.", ifnameof( *( aware_t* )ret ) );
    }

    return ( bhgp_sem_link_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_link_s* bhgp_sem_cell_s_evaluate_link( bhgp_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    bhgp_sem_link_s* ret = bhgp_sem_cell_s_evaluate_link_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_cell_s* bhgp_sem_cell_s_evaluate_cell_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    bhgp_sem* ret = bhgp_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret != TYPEOF_bhgp_sem_cell_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Cell Expected.", ifnameof( *( aware_t* )ret ) );
    }
    return ( bhgp_sem_cell_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_cell_s* bhgp_sem_cell_s_evaluate_cell( bhgp_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    bhgp_sem_cell_s* ret = bhgp_sem_cell_s_evaluate_cell_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// ctr

// ---------------------------------------------------------------------------------------------------------------------

/** Node process for a semantic cell.
 *  Entering a cell:
 *    Ascend the tree if matching or add a new node to the tree.
 *    node_out is set to the node referencing the cell
 *  Exiting a cell:
 *     Descend the tree until a matching node is found.
 *     node_out is set to the parent of the node referencing the cell.
 *     Returns 1 in case no match is found.
 *
 *  Returns 0 in case of success.
 */
s2_t bhgp_ctr_node_s_node_process( bhgp_ctr_node_s* o, bhgp_sem_cell_s* cell, bl_t enter, bhgp_ctr_node_s** node_out )
{
    bhgp_ctr_node_s* node = NULL;
    if( enter )
    {
        for( sz_t i = 0; i < o->size; i++ )
        {
            if( o->data[ i ]->cell == cell )
            {
                node = o->data[ i ];
            }
        }
        if( !node )
        {
            node = bhgp_ctr_node_s_push_d( o, bhgp_ctr_node_s_create() );
            node->cell = cell;
            node->parent = o;
        }
        *node_out = node;
        return 0;
    }
    else
    {
        node = o;
        while( node && node->cell != cell ) node = node->parent;
        if( node && node->cell == cell )
        {
            node = node->parent;
            *node_out = node;
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

s2_t bhgp_ctr_tree_s_tree_process( bhgp_ctr_tree_s* o, bhgp_sem_cell_s* cell, bl_t enter, bhgp_ctr_node_s* node_in, bhgp_ctr_node_s** node_out )
{
    if( enter )
    {
        bhgp_ctr_node_s* node = NULL;
        if( !o->root )
        {
            o->root = bhgp_ctr_node_s_create();
            o->root->id = o->id_base++;
            o->root->cell = cell;
            node = o->root;
            *node_out = node;
            return 0;
        }
        else if( node_in )
        {
            s2_t ret = bhgp_ctr_node_s_node_process( node_in, cell, enter, &node );
            if( ret ) return ret;
            if( node->id < 0 ) node->id = o->id_base++;
            *node_out = node;
            return 0;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return bhgp_ctr_node_s_node_process( node_in, cell, enter, node_out );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bcore_source_point_s* bhgp_ctr_node_s_get_nearest_source_point( bhgp_ctr_node_s* o )
{
    if( !o ) return NULL;
    if( !o->cell ) return NULL;
    if( o->cell->source_point.source ) return &o->cell->source_point;
    return bhgp_ctr_node_s_get_nearest_source_point( o->parent );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// net_node

/// recursive trace; exits when the enter membrane of the root cell is reached
void bhgp_net_node_s_trace_to_sink( bhgp_net_node_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o )
    {
        bcore_sink_a_push_fa( sink, "(NULL)" );
        return;
    }

    if( o->h )
    {
        bmath_hf3_s_brief_to_sink( o->h, sink );
    }

    sc_t symbol = "";
    if( o->op )
    {
        sc_t symbol = bhgp_op_a_get_symbol( o->op );
        if( !symbol ) symbol = ifnameof( o->op->_ );
        bcore_sink_a_push_fa( sink, "(#<sc_t>)", symbol );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "(noop)", symbol );
    }

    for( sz_t i = 0; i < o->upls.size; i++ )
    {
        sz_t incr = 4;
        bcore_sink_a_push_fa( sink, "\n#rn{ }#rn{-}", indent, incr );
        bhgp_net_node_s* node = o->upls.data[ i ]->node;
        bhgp_net_node_s_trace_to_sink( node, indent + incr, sink );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_net_node_s_err_fa( bhgp_net_node_s* o, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    if( o->source_point )
    {
        bcore_source_point_s_parse_err_fv( o->source_point, format, args );
    }
    else
    {
        bcore_err_fv( format, args );
    }
    va_end( args );
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 *  solve executes operator->solve to compute a holor.
 *  If a holor can be computed (vacant or determined), the solve-route is considered finished
 *  and will not be processed again. A detached result (o->h == NULL) causes a route to be reentered.
 *  If operator->solve returns 1, the operation is considered settled, in which case all uplinks
 *  are removed and the operator is switched to a final arity0 version via bhgp_op_a_create_final.
 *  After settling, the graph can be run through an optimizer minimizing its structure.
 */
void bhgp_net_node_s_solve( bhgp_net_node_s* o )
{
    if( o->h ) return;

    if( o->op )
    {
        sz_t arity = bhgp_op_a_get_arity( o->op );
        if( arity != o->upls.size )
        {
            bhgp_net_node_s_err_fa( o, "Operator arity #<sz_t> differs from node arity #<sz_t>", arity, o->upls.size );
        }

        #define bhgp_MAX_ARITY 4 /* increase this number when assertion below fails */
        ASSERT( arity <= bhgp_MAX_ARITY );
        bmath_hf3_s* arg_h[ bhgp_MAX_ARITY ];

        for( sz_t i = 0; i < arity; i++ )
        {
            bhgp_net_node_s* arg_n = o->upls.data[ i ]->node;
            if( arg_n )
            {
                bhgp_net_node_s_solve( arg_n );
                arg_h[ i ] = arg_n->h;
            }
        }

        sz_t result = bhgp_op_a_solve( o->op, &o->h, arg_h );

        if( result < 0 )
        {
            sc_t name = bhgp_op_a_get_symbol( o->op );
            if( !name ) name = ifnameof( o->op->_ );
            st_s* msg = st_s_create();
            st_s_push_fa( msg, "Operator '#<sc_t>' failed.\n", name );
            for( sz_t i = 0; i < arity; i++ )
            {
                st_s_push_fa( msg, "arg[#<sz_t>]: ", i );
                if( arg_h[ i ] )
                {
                    bmath_hf3_s_brief_to_sink( arg_h[ i ], (bcore_sink*)msg );
                }
                else
                {
                    st_s_push_fa( msg, "null" );
                }
                st_s_push_fa( msg, "\n" );
            }
            bhgp_net_node_s_err_fa( o, "#<sc_t>", msg->sc );
            st_s_discard( msg );
        }

        // operation is settled and can be removed
        if( result == 1 )
        {
//            bhgp_op_a_detach( &o->op );
            bhgp_op_a_attach( &o->op, bhgp_op_a_create_final( o->op, o->h ) );
            bhgp_net_links_s_clear( &o->upls );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/// Outputs the graph structure in text form to sink
void bhgp_net_node_s_graph_to_sink( bhgp_net_node_s* o, bcore_sink* sink )
{
    bhgp_net_node_s_trace_to_sink( o, 0, sink );
    bcore_sink_a_push_fa( sink, "\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively sets downlinks for all non-flagged uplinks.
 *  Assumes initial state was normal.
 */
void bhgp_net_node_s_set_downlinks( bhgp_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( &o->upls, i )
    {
        bhgp_net_node_s* node = o->upls.data[ i ]->node;
        bhgp_net_links_s_push( &node->dnls )->node = o;
        bhgp_net_node_s_set_downlinks( node );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively skips identities.
 *  Assumes initial state was normal and downlinks not set
 */
void bhgp_net_node_s_skip_identities( bhgp_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( &o->upls, i )
    {
        bhgp_net_node_s* node = o->upls.data[ i ]->node;
        while( node && node->op && node->op->_ == TYPEOF_bhgp_op_ar1_identity_s ) node = node->upls.data[ i ]->node;
        ASSERT( node );
        o->upls.data[ i ]->node = node;
        bhgp_net_node_s_skip_identities( node );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively sets flags for all nodes reachable via uplink.
 *  Assumes initial state was normal.
 */
void bhgp_net_node_s_set_flags( bhgp_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( &o->upls, i ) bhgp_net_node_s_set_flags( o->upls.data[ i ]->node );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// net_cell

// ---------------------------------------------------------------------------------------------------------------------

/** Normalizes network structure to the following result:
 *  Body references all nodes (including entry and exit nodes)
 *  Entry and exit references are forked accordingly.
 *  Node id is identical to body-index.
 */
static s2_t cmp_vd( vc_t o, vc_t v1, vc_t v2 ) { return ( *( vd_t* )v2 > *( vd_t* )v1 ) ? 1 : ( *( vd_t* )v2 < *( vd_t* )v1 ) ? -1 : 0; }
void bhgp_net_cell_s_normalize( bhgp_net_cell_s* o )
{
    bcore_arr_vd_s* arr = bcore_arr_vd_s_create();
    BFOR_EACH( &o->body, i ) bcore_arr_vd_s_push( arr, o->body.data[ i ] );
    BFOR_EACH( &o->encs, i ) bcore_arr_vd_s_push( arr, o->encs.data[ i ] );
    BFOR_EACH( &o->excs, i ) bcore_arr_vd_s_push( arr, o->excs.data[ i ] );

    // sort references descending (to move zeros to the end)
    bcore_array_a_sort_f( ( bcore_array* )arr, 0, -1, ( bcore_cmp_f ){ .f = cmp_vd, .o = NULL }, -1 );

    // remove zeros
    if( arr->size > 0 )
    {
        BFOR_EACH( arr, i )
        {
            if( arr->data[ i ] == NULL )
            {
                for( sz_t j = i + 1; j < arr->size; j++ ) ASSERT( arr->data[ j ] == NULL );
                arr->size = i;
                break;
            }
        }
    }

    // remove duplicates
    if( arr->size > 1 )
    {
        sz_t d = 1;
        for( sz_t i = 1; i < arr->size; i++ ) if( arr->data[ i - 1 ] != arr->data[ i ] ) arr->data[ d++ ] = arr->data[ i ];
        arr->size = d;
    }

    // fork references
    BFOR_EACH( arr, i ) arr->data[ i ] = bcore_fork( arr->data[ i ] );

    // new body
    bhgp_net_nodes_s_set_size( &o->body, 0 );
    for( sz_t i = 0; i < arr->size; i++ )
    {
        bhgp_net_node_s* node = bhgp_net_nodes_s_push_d( &o->body, arr->data[ i ] );
        assert( node == arr->data[ i ] );
        node->id = i;
        node->flag = false;
    }

    bcore_arr_vd_s_discard( arr );
}

// ---------------------------------------------------------------------------------------------------------------------

/// Checks consistency of a normalized cell
bl_t bhgp_net_cell_s_is_consistent( const bhgp_net_cell_s* o )
{
    BFOR_EACH( &o->body, i )
    {
        const bhgp_net_node_s* node = o->body.data[ i ];
        if( node->flag ) return false;
        if( node->id != i ) return false;
        BFOR_EACH( &node->upls, i )
        {
            const bhgp_net_node_s* node2 = node->upls.data[ i ]->node;
            if( node2->id < 0 ) return false;
            if( node2->id >= o->body.size ) return false;
            if( node2 != o->body.data[ node2->id ] ) return false;
        }

        BFOR_EACH( &node->dnls, i )
        {
            const bhgp_net_node_s* node2 = node->dnls.data[ i ]->node;
            if( node2->id < 0 ) return false;
            if( node2->id >= o->body.size ) return false;
            if( node2 != o->body.data[ node2->id ] ) return false;
        }
    }

    BFOR_EACH( &o->encs, i )
    {
        const bhgp_net_node_s* node2 = o->encs.data[ i ];
        if( node2->id < 0 ) return false;
        if( node2->id >= o->body.size ) return false;
        if( node2 != o->body.data[ node2->id ] ) return false;
    }

    BFOR_EACH( &o->excs, i )
    {
        const bhgp_net_node_s* node2 = o->excs.data[ i ];
        if( node2->id < 0 ) return false;
        if( node2->id >= o->body.size ) return false;
        if( node2 != o->body.data[ node2->id ] ) return false;
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_net_cell_s_copy_x( bhgp_net_cell_s* o )
{
    BFOR_EACH( &o->body, i )
    {
        const bhgp_net_node_s* node = o->body.data[ i ];
        ASSERT( node->id == i );
        BFOR_EACH( &node->upls, i )
        {
            const bhgp_net_node_s* node2 = node->upls.data[ i ]->node;
            ASSERT( node2->id >= 0 );
            ASSERT( node2->id < o->body.size );
            node->upls.data[ i ]->node = o->body.data[ node2->id ];
        }
        BFOR_EACH( &node->dnls, i )
        {
            const bhgp_net_node_s* node2 = node->dnls.data[ i ]->node;
            ASSERT( node2->id >= 0 );
            ASSERT( node2->id < o->body.size );
            node->dnls.data[ i ]->node = o->body.data[ node2->id ];
        }
    }

    BFOR_EACH( &o->encs, i )
    {
        sz_t id = o->encs.data[ i ]->id;
        ASSERT( id >= 0 );
        ASSERT( id < o->body.size );
        bhgp_net_node_s_detach( &o->encs.data[ i ] );
        o->encs.data[ i ] = bcore_fork( o->body.data[ id ] );
    }

    BFOR_EACH( &o->excs, i )
    {
        sz_t id = o->excs.data[ i ]->id;
        ASSERT( id >= 0 );
        ASSERT( id < o->body.size );
        bhgp_net_node_s_detach( &o->excs.data[ i ] );
        o->excs.data[ i ] = bcore_fork( o->body.data[ id ] );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_net_cell_s_set_downlinks( bhgp_net_cell_s* o )
{
    bhgp_net_cell_s_clear_flags( o );
    bhgp_net_cell_s_clear_downlinks( o );
    BFOR_EACH( &o->excs, i ) bhgp_net_node_s_set_downlinks( o->excs.data[ i ] );
    bhgp_net_cell_s_clear_flags( o );
    assert( bhgp_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes not reachable via uplink from exit channels
 *  Creates an warning in case an entry channel is unreachable.
 */
void bhgp_net_cell_s_remove_unreachable_nodes( bhgp_net_cell_s* o )
{
    bhgp_net_cell_s_clear_flags( o );
    BFOR_EACH( &o->excs, i ) bhgp_net_node_s_set_flags( o->excs.data[ i ] );
    BFOR_EACH( &o->encs, i )
    {
        bhgp_net_node_s* node = o->encs.data[ i ];
        if( !node->flag ) bcore_source_point_s_parse_msg_to_sink_fa( node->source_point, BCORE_STDERR, "Warning: Entry channel has no effect." );
        node->flag = true;
    }

    BFOR_EACH( &o->body, i ) if( !o->body.data[ i ]->flag ) bhgp_net_node_s_detach( &o->body.data[ i ] );
    bhgp_net_cell_s_normalize( o );

    assert( bhgp_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes containing an identity operator and relinks remaining nodes accordingly
 *  Clears all downlinks;
 */
void bhgp_net_cell_s_remove_identities( bhgp_net_cell_s* o )
{
    bhgp_net_cell_s_clear_downlinks( o );
    bhgp_net_cell_s_clear_flags( o );
    BFOR_EACH( &o->excs, i ) bhgp_net_node_s_skip_identities( o->excs.data[ i ] );
    bhgp_net_cell_s_clear_flags( o );
    bhgp_net_cell_s_remove_unreachable_nodes( o );
    assert( bhgp_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively building a network cell from a semantic cell using membrane-technique.
 *  Exits when the enter membrane of the root cell is reached.
 *  This function does not set downlinks.
 */
static void net_cell_s_from_sem_recursive
(
    bhgp_net_cell_s* o,
    bhgp_sem_link_s* link,
    bhgp_ctr_tree_s* ctr_tree,
    bhgp_ctr_node_s* ctr_node,
    bhgp_net_node_s* net_node_dn,
    sz_t             depth,
    bcore_sink*      log  // optional
)
{
    depth++;
    tp_t name = link->name;
    if( log ) bcore_sink_a_push_fa( log, "Tracing link '#<sc_t>' at depth #<sz_t>\n", bhgp_ifnameof( name ), depth );
    link = bhgp_sem_link_s_trace_to_cell_membrane( link );
    if( !link ) ERR_fa( "Backtracing '#<sc_t>':\nTrace ends in open link.", bhgp_ifnameof( name ) );
    bhgp_sem_cell_s* cell = link->cell;
    bhgp_sem_link_s* next_link = NULL;

    if( depth > o->max_depth )
    {
        bcore_source_point_s_parse_err_fa( &cell->source_point, "Maximum depth '#<sz_t>' exceeded: This problem might be the result of an indefinite recursion.\n", o->max_depth );
    }

    if( link->exit )
    {
        bcore_source_point_s_parse_msg_to_sink_fa( &cell->source_point, log, "entering cell: '#<sc_t>' \n", bhgp_nameof( cell->name ) );

        // since we backtrace, a cell is entered through an 'exit' link
        s2_t err = bhgp_ctr_tree_s_tree_process( ctr_tree, cell, true, ctr_node, &ctr_node );
        if( err )
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nEntering cell failed.", bhgp_ifnameof( name ) );
        }

        if( cell->op )
        {
            if( log ) bcore_sink_a_push_fa( log, "cell op: #<sc_t>\n", ifnameof( cell->op->_ ) );

            bl_t trace_up = false;
            bhgp_net_node_s* net_node_up = bhgp_net_nodes_s_get_by_id( &o->body, ctr_node->id );
            if( !net_node_up )
            {
                net_node_up = bhgp_net_nodes_s_push( &o->body );
                net_node_up->id = ctr_node->id;
                net_node_up->op = bcore_fork( cell->op );

                bcore_source_point_s_attach( &net_node_up->source_point, bcore_fork( bhgp_ctr_node_s_get_nearest_source_point( ctr_node ) ) );

                trace_up = bhgp_op_a_get_arity( net_node_up->op ) > 0;
                if( log ) bcore_sink_a_push_fa( log, "new node id: '#<sz_t>'\n", net_node_up->id );
            }

            if( trace_up )
            {
                sz_t arity = bhgp_op_a_get_arity( net_node_up->op );
                ASSERT( arity == cell->encs.size );

                if( net_node_up->op->_ == TYPEOF_bhgp_op_ar3_branch_s )
                {
                    if( log ) bcore_sink_a_push_fa( log, "Branch channel 0:\n" );
                    net_cell_s_from_sem_recursive( o, cell->encs.data[ 0 ], ctr_tree, ctr_node, net_node_up, depth, log );
                    bhgp_net_node_s* arg0 = net_node_up->upls.data[ 0 ]->node;
                    bhgp_net_node_s_solve( arg0 );
                    if( arg0->h->v_data ) // determined holor
                    {
                        bhgp_net_links_s_clear( &net_node_up->upls );
                        bhgp_op_a_attach( &net_node_up->op, ( bhgp_op* )bhgp_op_ar1_identity_s_create() );
                        if( log ) bcore_sink_a_push_fa( log, "Condition check result: #<f3_t>. Identity to channel ", arg0->h->v_data[ 0 ] );
                        if( arg0->h->v_data[ 0 ] > 0 )
                        {
                            if( log ) bcore_sink_a_push_fa( log, "'TRUE'\n" );
                            net_cell_s_from_sem_recursive( o, cell->encs.data[ 1 ], ctr_tree, ctr_node, net_node_up, depth, log );
                        }
                        else
                        {
                            if( log ) bcore_sink_a_push_fa( log, "'FALSE'\n" );
                            net_cell_s_from_sem_recursive( o, cell->encs.data[ 2 ], ctr_tree, ctr_node, net_node_up, depth, log );
                        }
                    }
                    else
                    {
                        if( log ) bcore_sink_a_push_fa( log, "Branching to channel " );
                        if( log ) bcore_sink_a_push_fa( log, "'TRUE'\n" );
                        net_cell_s_from_sem_recursive( o, cell->encs.data[ 1 ], ctr_tree, ctr_node, net_node_up, depth, log );
                        if( log ) bcore_sink_a_push_fa( log, "'FALSE'\n" );
                        net_cell_s_from_sem_recursive( o, cell->encs.data[ 2 ], ctr_tree, ctr_node, net_node_up, depth, log );
                    }
                }
                else
                {
                    for( sz_t i = 0; i < arity; i++ )
                    {
                        if( log ) bcore_sink_a_push_fa( log, "node id #<sz_t>: up channel #<sz_t> of #<sz_t>:\n", net_node_up->id, i, arity );
                        net_cell_s_from_sem_recursive( o, cell->encs.data[ i ], ctr_tree, ctr_node, net_node_up, depth, log );
                    }
                }
            }

            bhgp_net_links_s_push( &net_node_dn->upls )->node = net_node_up;
        }
        else if( link->up )
        {
            next_link = link->up;
        }
        else
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nOpen exit link '#<sc_t>'.", bhgp_ifnameof( name ), bhgp_ifnameof( link->name ) );
        }
    }
    else
    {
        if( log ) bcore_sink_a_push_fa( log, "exiting cell: '#<sc_t>' \n", bhgp_ifnameof( cell->name ) );

        s2_t err = bhgp_ctr_tree_s_tree_process( ctr_tree, cell, false, ctr_node, &ctr_node );
        if( err )
        {
            if( err == 1 )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting from untraced cell.", bhgp_ifnameof( name ) );
            }
            else
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting cell failed.", bhgp_ifnameof( name ) );
            }
        }

        if( !ctr_node ) // root membrane reached (trace ended)
        {
            sz_t index = bhgp_sem_links_s_get_index_by_link( &cell->encs, link );
            if( index == -1 )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nEnding trace: No matching input channel.", bhgp_ifnameof( name ) );
            }
            if( index >= o->encs.size )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nInput channel boundary exceeded.", bhgp_ifnameof( name ) );
            }

            bhgp_net_node_s* net_node_up = o->encs.data[ index ];
            bhgp_net_links_s_push( &net_node_dn->upls )->node = net_node_up;

            next_link = NULL;
        }

        else if( link->up )
        {
            next_link = link->up;
        }
        else
        {
            next_link = bhgp_sem_cell_s_get_enc_by_dn( ctr_node->cell, link );
            if( !next_link )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nTrace ends in open link.", bhgp_ifnameof( name ) );
            }
        }
    }

    if( next_link )
    {
        net_cell_s_from_sem_recursive( o, next_link, ctr_tree, ctr_node, net_node_dn, depth, log );
    }
    else
    {
        if( log ) bcore_sink_a_push_fa( log, "Trace ended.\n" );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/// builds a net cell from a semantic cell
void bhgp_net_cell_s_from_sem_cell
(
    bhgp_net_cell_s* o,
    bhgp_sem_cell_s* sem_cell,
    bhgp_op* (*input_op_create)( vd_t arg, sz_t in_idx, tp_t in_name ),
    vd_t arg
)
{
    ASSERT( sem_cell );
    bhgp_ctr_tree_s* tree = bhgp_ctr_tree_s_create();
    for( sz_t i = 0; i < sem_cell->encs.size; i++ )
    {
        bhgp_sem_link_s* sem_link = sem_cell->encs.data[ i ];
        bhgp_net_node_s* net_node = bhgp_net_nodes_s_push( &o->encs );
        net_node->name = sem_link->name;
        net_node->id   = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        net_node->op = input_op_create ? input_op_create( arg, i, sem_link->name ) : NULL;
    }

    for( sz_t i = 0; i < sem_cell->excs.size; i++ )
    {
        bhgp_sem_link_s* sem_link = sem_cell->excs.data[ i ];
        bhgp_net_node_s* net_node = bhgp_net_nodes_s_push( &o->excs );
        net_node->name = sem_link->name;
        net_node->id = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        bhgp_op_ar1_output_s* op_ar1_output = bhgp_op_ar1_output_s_create();
        net_node->op = ( bhgp_op* )op_ar1_output;
        net_cell_s_from_sem_recursive( o, sem_link, tree, NULL, net_node, 0, BCORE_STDOUT );
    }

    bhgp_ctr_tree_s_discard( tree );

    bhgp_net_cell_s_normalize( o );
    assert( bhgp_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/// outputs graph to sink
static void bhgp_net_cell_s_graph_to_sink( bhgp_net_cell_s* o, bcore_sink* sink )
{
    BFOR_EACH( &o->excs, i ) bhgp_net_node_s_graph_to_sink( o->excs.data[ i ], sink );
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_net_node_s_build_vm_frame_proc( bhgp_net_node_s* o, bmath_hf3_vm_frame_s* vm_frame, tp_t proc_name )
{
    ASSERT( o );
    if( o->flag ) return;
    o->flag = true;
    if( !o->h ) ERR_fa( "Holor is missing." );

    BLM_INIT();
    bcore_arr_vd_s* arr_holor = BLM_CREATE( bcore_arr_vd_s );
    bcore_arr_sz_s* arr_index = BLM_CREATE( bcore_arr_sz_s );
    BFOR_EACH( &o->upls, i )
    {
        bhgp_net_node_s* node = o->upls.data[ i ]->node;
        bhgp_net_node_s_build_vm_frame_proc( node, vm_frame, proc_name );
        bcore_arr_vd_s_push( arr_holor, node->h );
        bcore_arr_sz_s_push( arr_index, node->id );
    }

    ASSERT( o->id >= 0 && o->id < vm_frame->arr_holor.size );
    bmath_hf3_vm_holor_s* vm_holor = &vm_frame->arr_holor.data[ o->id ];
    vm_holor->name = o->name;
    bmath_hf3_s_copy( &vm_holor->hf3, o->h );

    vm_holor->type = ( o->h->v_size == 0 ) ? TYPEOF_depletable : TYPEOF_data;
    if( o->op && o->op->_ == TYPEOF_bhgp_op_ar0_adapt_s ) vm_holor->type = TYPEOF_adaptive;

    bmath_hf3_vm_op* vm_op = bhgp_op_a_create_vm_op( o->op, ( const bmath_hf3_s** )arr_holor->data, &vm_holor->hf3 );

    ASSERT( bmath_hf3_vm_op_a_get_arity( vm_op ) == arr_index->size );
    bmath_hf3_vm_op_a_set_indices( vm_op, arr_index->data );
    bmath_hf3_vm_proc_s* vm_proc = bmath_hf3_vm_frame_s_proc_get_or_push( vm_frame, proc_name );
    bmath_hf3_vm_proc_s_push_op_d( vm_proc, vm_op );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_net_cell_s_build_vm_frame( bhgp_net_cell_s* o, bmath_hf3_vm_frame_s* vm_frame )
{
    bmath_hf3_vm_frame_s_clear( vm_frame );
    ASSERT( bhgp_net_cell_s_is_consistent( o ) );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        bhgp_net_node_s* node = o->encs.data[ i ];
        if( !node->h ) ERR_fa( "Unsolved node '#<sc_t>'\n", bhgp_ifnameof( node->name ) );
        bhgp_net_node_s_build_vm_frame_proc( node, vm_frame, TYPEOF_infer );
    }

    bhgp_net_cell_s_clear_flags( o );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// VIRTUAL MACHINE
/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_vm_adaptive_s_minfer( bhgp_vm_adaptive_s* o, const bmath_vf3_s* v_in, bmath_vf3_s* v_out )
{
    ASSERT( o->in_index  < o->vm.arr_holor.size );
    ASSERT( o->out_index < o->vm.arr_holor.size );
    bmath_hf3_s* h_in  = &o->vm.arr_holor.data[ o->in_index  ].hf3;
    bmath_hf3_s* h_out = &o->vm.arr_holor.data[ o->out_index ].hf3;

    ASSERT( v_in ->size == h_in ->v_size );
    ASSERT( v_out->size == h_out->v_size );

    bmath_hf3_s_copy_v_data_from_vf3( h_in, v_in );
    bmath_hf3_vm_frame_s_proc_run( &o->vm, TYPEOF_infer );
    bmath_hf3_s_copy_v_data_to_vf3( h_out, v_out );
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_op* bhgp_vm_builder_s_build_input_op_create( vd_t vd_o, sz_t in_idx, tp_t in_name )
{
    const bhgp_vm_builder_s* o = vd_o;
    bhgp_op_ar0_input_s* input = bhgp_op_ar0_input_s_create();
    input->h = bmath_hf3_s_create();

    switch( in_idx )
    {
        case 0:
        {
            bmath_hf3_s_set_f3( input->h, o->in_size );
        }
        break;

        case 1:
        {
            bmath_hf3_s_set_d_data_na( input->h, 1, o->in_size );
        }
        break;

        default:
        {
            ERR_fa( "Invalid index '#<sz_t>',", in_idx );
        }
        break;
    }

    return ( bhgp_op* )input;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* bhgp_vm_builder_s_build( const bhgp_vm_builder_s* o )
{
    bhgp_vm_adaptive_s* adaptive = bhgp_vm_adaptive_s_create();
    st_s_copy( &adaptive->src, &o->src );
    adaptive->in_size = o->in_size;
    adaptive->out_size = o->out_size;
    badapt_dynamics_std_s_copy( &adaptive->dynamics, &o->dynamics );

    BLM_INIT();

    bcore_source* source  = BCORE_LIFE_A_PUSH( bcore_file_open_source( o->src.sc ) );
    bhgp_sem_cell_s* sem_frame = BCORE_LIFE_A_PUSH( sem_cell_s_create_frame() );

    bhgp_sem_cell_s_parse_signature( sem_frame, BLM_A_PUSH( bcore_source_string_s_create_sc( o->frame.sc ) ) );
    bcore_source_point_s_set( &sem_frame->source_point, source );
    bhgp_sem_cell_s_parse_body( sem_frame, source );

    bhgp_net_cell_s* net_frame = BCORE_LIFE_A_PUSH( bhgp_net_cell_s_create() );
    bhgp_net_cell_s_from_sem_cell( net_frame, sem_frame, bhgp_vm_builder_s_build_input_op_create, ( vd_t )o );

    bhgp_net_cell_s_solve( net_frame );
    bhgp_net_cell_s_remove_identities( net_frame );
    bhgp_net_cell_s_set_downlinks( net_frame );
    ASSERT( bhgp_net_cell_s_is_consistent( net_frame ) );

    bhgp_net_cell_s_graph_to_sink( net_frame, BCORE_STDOUT );

    bcore_msg_fa( "net_cell encs size = #<sz_t>\n", net_frame->encs.size );
    bcore_msg_fa( "net_cell body size = #<sz_t>\n", net_frame->body.size );
    bcore_msg_fa( "net_cell excs size = #<sz_t>\n", net_frame->excs.size );

    bhgp_net_cell_s_build_vm_frame( net_frame, &adaptive->vm );

    ASSERT( net_frame->encs.size == 2 );
    ASSERT( net_frame->excs.size == 1 );

    adaptive->in_index  = bmath_hf3_vm_frame_s_get_holor_index( &adaptive->vm, net_frame->encs.data[ 1 ]->name );
    adaptive->out_index = bmath_hf3_vm_frame_s_get_holor_index( &adaptive->vm, net_frame->excs.data[ 0 ]->name );

    bmath_hf3_vm_frame_s* vmf = &adaptive->vm;

    // procedure 'setup'
    {
        tp_t tp_setup = bmath_hf3_vm_frame_s_entypeof( vmf, "setup" );
        const bmath_hf3_vm_arr_holor_s* arr_holor = &vmf->arr_holor;
        for( sz_t i = 0; i < arr_holor->size; i++ )
        {
            const bmath_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
            switch( holor->type )
            {
                case TYPEOF_depletable:
                {
                    bmath_hf3_vm_frame_s_push_op_d( vmf, tp_setup, bmath_hf3_vm_op_ar0_determine_s_csetup( NULL, i ) );
                }
                break;

                case TYPEOF_adaptive:
                {
                    if( holor->hf3.v_size == 0 )
                    {
                        bmath_hf3_vm_frame_s_push_op_d( vmf, tp_setup, bmath_hf3_vm_op_ar0_determine_s_csetup( NULL, i ) );
                        bmath_hf3_vm_frame_s_push_op_d( vmf, tp_setup, bmath_hf3_vm_op_ar0_randomize_s_csetup_randomize( NULL, i, 1234 /*o->rseed*/ ) );
                    }
                }
                break;

                default: break;
            }
        }
        vmf->proc_setup = tp_setup;
    }

    // procedure 'shelve'
    {
        tp_t tp_shelve = bmath_hf3_vm_frame_s_entypeof( vmf, "shelve" );
        const bmath_hf3_vm_arr_holor_s* arr_holor = &vmf->arr_holor;
        for( sz_t i = 0; i < arr_holor->size; i++ )
        {
            const bmath_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
            switch( holor->type )
            {
                case TYPEOF_buffer: bmath_hf3_vm_frame_s_push_op_d( vmf, tp_shelve, bmath_hf3_vm_op_ar0_vacate_s_csetup( NULL, i ) ); break;
                default:              break;
            }
        }
        vmf->proc_shelve = tp_shelve;
    }
    /// run setup
    bmath_hf3_vm_frame_s_proc_run( vmf, typeof( "setup" ) );

    BLM_RETURNV( badapt_adaptive*, ( badapt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

bhgp_op* bhgp_test_input_op_create( vd_t arg, sz_t in_idx, tp_t in_name )
{
    bhgp_op_ar0_input_s* input = bhgp_op_ar0_input_s_create();
    input->h = bmath_hf3_s_create();
    bmath_hf3_s_set_d_data_na( input->h, 1, 100 );
    return ( bhgp_op* )input;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_test( void )
{
    BLM_INIT();

//    bcore_source* source  = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/bhgp_test.hgp" ) );
    bcore_source* source  = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/bhgp_mlp.hgp" ) );
//    bcore_source* source  = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/syntax02.hgp" ) );

    bhgp_sem_cell_s* sem_frame = BCORE_LIFE_A_PUSH( sem_cell_s_create_frame() );

    bhgp_sem_cell_s_parse_signature( sem_frame, BLM_A_PUSH( bcore_source_string_s_create_sc( "( y => a )" ) ) );
    bcore_source_point_s_set( &sem_frame->source_point, source );
    bhgp_sem_cell_s_parse_body( sem_frame, source );

    bhgp_net_cell_s* net_frame = BCORE_LIFE_A_PUSH( bhgp_net_cell_s_create() );
    bhgp_net_cell_s_from_sem_cell( net_frame, sem_frame, bhgp_test_input_op_create, NULL );

    bhgp_net_cell_s_solve( net_frame );
    bhgp_net_cell_s_remove_identities( net_frame );
    bhgp_net_cell_s_set_downlinks( net_frame );
    ASSERT( bhgp_net_cell_s_is_consistent( net_frame ) );

    bhgp_net_cell_s_graph_to_sink( net_frame, BCORE_STDOUT );

    bcore_msg_fa( "net_cell encs size = #<sz_t>\n", net_frame->encs.size );
    bcore_msg_fa( "net_cell body size = #<sz_t>\n", net_frame->body.size );
    bcore_msg_fa( "net_cell excs size = #<sz_t>\n", net_frame->excs.size );

    // test copying of net_cell
    {
        bhgp_net_cell_s* cloned_cell = BCORE_LIFE_A_PUSH( bhgp_net_cell_s_clone( net_frame ) );
        ASSERT( bhgp_net_cell_s_is_consistent( cloned_cell ) );
    }

//    bcore_txt_ml_a_to_stdout( net_cell );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t bhgp_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "bhgp" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
            bhgp_context_down();
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "badapt_dev_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


