/** Author and Copyright 2019 Johannes Bernhard Steffens
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

#include "haptive_graph.h"

// ---------------------------------------------------------------------------------------------------------------------

#ifdef TYPEOF_haptive

/**********************************************************************************************************************/
/// Prototypes


// ---------------------------------------------------------------------------------------------------------------------
// sem_cell

void haptive_sem_cell_s_create_args_out( haptive_sem_cell_s* o, bcore_source* source );
void haptive_sem_cell_s_create_args_in(  haptive_sem_cell_s* o, haptive_sem_cell_s* frame, bcore_source* source );
void haptive_sem_cell_s_wrap_cell(       haptive_sem_cell_s* o, haptive_sem_cell_s* cell );

void             haptive_sem_cell_s_parse(               haptive_sem_cell_s* o,                        bcore_source* source );
haptive_sem*        haptive_sem_cell_s_evaluate_sem(        haptive_sem_cell_s* o,                        bcore_source* source );
haptive_sem*        haptive_sem_cell_s_evaluate_sem_stack(  haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
haptive_sem_cell_s* haptive_sem_cell_s_evaluate_cell(       haptive_sem_cell_s* o,                        bcore_source* source );
haptive_sem_cell_s* haptive_sem_cell_s_evaluate_cell_stack( haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
haptive_sem_link_s* haptive_sem_cell_s_evaluate_link(       haptive_sem_cell_s* o,                        bcore_source* source );
haptive_sem_link_s* haptive_sem_cell_s_evaluate_link_stack( haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source );
haptive_sem_cell_s* haptive_sem_cell_s_push_cell_op_d(      haptive_sem_cell_s* o, haptive_op* op );
haptive_sem_cell_s* haptive_sem_cell_s_push_cell_op_d_reset_name( haptive_sem_cell_s* o, haptive_op* op );
void             haptive_sem_cell_s_set_channels(        haptive_sem_cell_s* o, sz_t excs, sz_t encs );

haptive_net_cell_s* haptive_net_cell_s_create_from_sem_link( haptive_sem_link_s* sem_link );

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// context

static haptive_context_s* context_g = NULL;

// ---------------------------------------------------------------------------------------------------------------------

haptive_context_s* haptive_get_context()
{
    return context_g;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t haptive_entypeof( sc_t name );

// ---------------------------------------------------------------------------------------------------------------------

void haptive_context_setup()
{
    if( context_g ) return;
    context_g = haptive_context_s_create();

    BLM_INIT();
    bcore_arr_tp_s* arr_tp = BLM_CREATE( bcore_arr_tp_s );

    bcore_push_traits_of_ancestor( TYPEOF_haptive_op_ar1, arr_tp );
    bcore_push_traits_of_ancestor( TYPEOF_haptive_op_ar2, arr_tp );

    context_g->randomizer_mutex = bcore_mutex_s_create();

    for( sz_t i = 0; i < arr_tp->size; i++ )
    {
        haptive_op* op = haptive_op_t_create( arr_tp->data[ i ] );
        sc_t symbol = haptive_op_a_get_symbol( op );
        // bcore_msg_fa( "#<sc_t>\n", symbol );
        if( symbol )
        {
            sz_t arity = haptive_op_a_get_arity( op );
            bcore_hmap_name_s_set_sc( &context_g->hmap_name, symbol );
            switch( arity )
            {
                case 2: bcore_arr_st_s_push_sc( &context_g->arr_symbol_op2, symbol ); break;
                default: break;
            }
            haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d( &context_g->cell, op );
            cell->name = typeof( symbol );
        }
        else
        {
            haptive_op_a_detach( &op );
        }
    }

    /** We sort the array in descending manner; this ensures that short symbols
     *  which patterns match the beginning of a longer symbol can not occlude the longer one.
     */
    bcore_array_a_sort( (bcore_array*)&context_g->arr_symbol_op2, 0, -1, -1 );

    /// register control types
    bcore_arr_tp_s_push( &context_g->control_types, haptive_entypeof( "cell" ) );
    bcore_arr_tp_s_push( &context_g->control_types, haptive_entypeof( "if" ) );
    bcore_arr_tp_s_push( &context_g->control_types, haptive_entypeof( "then" ) );
    bcore_arr_tp_s_push( &context_g->control_types, haptive_entypeof( "else" ) );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_context_down()
{
    if( context_g )
    {
        bcore_mutex_s_discard( context_g->randomizer_mutex );
        context_g->randomizer_mutex = NULL;
        haptive_context_s_detach( &context_g );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t haptive_nameof( tp_t name )
{
    if( !context_g ) haptive_context_setup();
    return bcore_hmap_name_s_get_sc( &context_g->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t haptive_ifnameof( tp_t name )
{
    sc_t sc = haptive_nameof( name );
    return sc ? sc : "";
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t haptive_entypeof( sc_t name )
{
    if( !context_g ) haptive_context_setup();
    return bcore_hmap_name_s_set_sc( &context_g->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t haptive_entypeof_fv( sc_t format, va_list args )
{
    st_s* s = st_s_create_fv( format, args );
    tp_t tp = haptive_entypeof( s->sc );
    st_s_discard( s );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t haptive_entypeof_fa( sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    tp_t tp = haptive_entypeof_fv( format, args );
    va_end( args );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t haptive_parse_name( bcore_source* source )
{
    st_s* name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", name );
    if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
    tp_t tp_name = haptive_entypeof( name->sc );
    st_s_discard( name );
    return tp_name;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t haptive_parse_op2_symbol( bcore_source* source )
{
    if( !context_g ) haptive_context_setup();
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

tp_t haptive_is_control_type( tp_t name )
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

static haptive_sem_link_s* stack_pop_link( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_haptive_sem_link_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static haptive_sem_cell_s* stack_pop_cell( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_haptive_sem_cell_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static haptive_sem_link_s* stack_pop_link_or_exit( bcore_arr_vd_s* o, bcore_source* source )
{
    vd_t v = stack_pop( o );
    tp_t t = *(aware_t*)v;
    if( t == TYPEOF_haptive_sem_link_s ) return v;
    if( t == TYPEOF_haptive_sem_cell_s )
    {
        haptive_sem_cell_s* cell = v;
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
/// haptive_op_ar1

s2_t haptive_op_ar1_solve_unary( bhvm_hf3_s** r, bhvm_hf3_s** a, bmath_fp_f3_ar1 unary )
{
    bhvm_hf3_s_attach( r, a[0] ? bhvm_hf3_s_create() : NULL );
    if( a[0] )
    {
        bhvm_hf3_s_copy_size( *r, a[0] );
        if( a[0]->v_size ) bhvm_hf3_s_fp_f3_ar1( a[0], unary, *r );
    }
    return ( *r && (*r)->v_size ) ? 1 : 0;
}


/**********************************************************************************************************************/
/// haptive_op_ar2

// ---------------------------------------------------------------------------------------------------------------------

bhvm_hf3_vm_op* haptive_op_ar2_mul_s_create_vm_op_ap( const haptive_op_ar2_mul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx )
{
    ASSERT( arr_idx->size >= 2 );
    const bhvm_hf3_s* a = &bhvm_hf3_vm_frame_s_holors_get_by_index( ( bhvm_hf3_vm_frame_s* )vmf, arr_idx->data[ 0 ] )->h;
    const bhvm_hf3_s* b = &bhvm_hf3_vm_frame_s_holors_get_by_index( ( bhvm_hf3_vm_frame_s* )vmf, arr_idx->data[ 1 ] )->h;
    if( a->d_size == 0 )
    {
        return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_scl_mul_s_create();
    }
    else if( b->d_size == 0 )
    {
        return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_mul_scl_s_create();
    }
    else
    {
        return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_hmul_s_create();
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bhvm_hf3_vm_op* haptive_op_ar2_mul_s_create_vm_op_dp( const haptive_op_ar2_mul_s* o, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx, char ch_id )
{
    ASSERT( arr_idx->size >= 2 );
    const bhvm_hf3_s* a = &bhvm_hf3_vm_frame_s_holors_get_by_index( ( bhvm_hf3_vm_frame_s* )vmf, arr_idx->data[ 0 ] )->h;
    const bhvm_hf3_s* b = &bhvm_hf3_vm_frame_s_holors_get_by_index( ( bhvm_hf3_vm_frame_s* )vmf, arr_idx->data[ 1 ] )->h;

    if( a->d_size == 0 )
    {
        if( ch_id == 'a' ) return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_scl_mul_s_create();
        if( ch_id == 'b' ) return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_cb_scl_mul_s_create();
    }
    else if( b->d_size == 0 )
    {
        if( ch_id == 'a' ) return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_mul_scl_s_create();
        if( ch_id == 'b' ) return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_cb_mul_scl_s_create();
    }
    else
    {
        if( ch_id == 'a' ) return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_hmul_s_create();
        if( ch_id == 'b' ) return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_cb_hmul_s_create();
    }

    ERR_fa( "Invalid channel id '#<char>'", ch_id );

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// sem_link

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_link_s* haptive_sem_link_s_create_setup( tp_t name, haptive_sem_link_s* up, haptive_sem_link_s* dn, haptive_sem_cell_s* cell, bl_t exit )
{
    haptive_sem_link_s* o = haptive_sem_link_s_create();
    o->name = name;
    o->up = up;
    o->dn = dn;
    o->cell = cell;
    o->exit = exit;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next membrane; returns NULL in case trace ends in open link
haptive_sem_link_s* haptive_sem_link_s_trace_to_cell_membrane( haptive_sem_link_s* o )
{
    if( !o || o->cell ) return o;
    return haptive_sem_link_s_trace_to_cell_membrane( o->up );
}

// ---------------------------------------------------------------------------------------------------------------------

// Traces link to next cell; returns NULL in case trace ends in open link
haptive_sem_cell_s* haptive_sem_link_s_trace_to_cell( haptive_sem_link_s* o )
{
    haptive_sem_link_s* link = haptive_sem_link_s_trace_to_cell_membrane( o );
    if( link )
    {
        if( link->cell ) assert( *(aware_t*)link->cell == TYPEOF_haptive_sem_cell_s );
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

void haptive_sem_cell_s_set_channels( haptive_sem_cell_s* o, sz_t excs, sz_t encs )
{
    haptive_sem_links_s_set_size( &o->excs, excs );
    haptive_sem_links_s_set_size( &o->encs, encs );
    for( sz_t i = 0; i < excs; i++ )
    {
        o->excs.data[ i ] = haptive_sem_link_s_create_setup( 0, NULL, NULL, o, true );
    }
    for( sz_t i = 0; i < encs; i++ )
    {
        o->encs.data[ i ] = haptive_sem_link_s_create_setup( 0, NULL, NULL, o, false );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_sem_cell_s_wrap_cell( haptive_sem_cell_s* o, haptive_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->op   );
    o->priority = src->priority;
    haptive_sem_links_s_set_size( &o->encs, haptive_sem_cell_s_get_arity( src ) );
    haptive_sem_links_s_set_size( &o->excs, src->excs.size );

    sz_t k = 0;
    for( sz_t i = 0; i < src->encs.size; i++ )
    {
        if( !src->encs.data[ i ]->up )
        {
            o->encs.data[ k++ ] = haptive_sem_link_s_create_setup( src->encs.data[ i ]->name, NULL, src->encs.data[ i ], o, false );
        }
    }

    assert( k == o->encs.size );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        o->excs.data[ i ] = haptive_sem_link_s_create_setup( src->excs.data[ i ]->name, src->excs.data[ i ], NULL, o, true );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem* haptive_sem_cell_s_push_sem( haptive_sem_cell_s* o, tp_t type )
{
    if( !o->body ) o->body = haptive_sem_body_s_create();
    return haptive_sem_body_s_push_t( o->body, type );
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_push_cell( haptive_sem_cell_s* o )
{
    haptive_sem_cell_s* cell = ( haptive_sem_cell_s* )haptive_sem_cell_s_push_sem( o, TYPEOF_haptive_sem_cell_s );
    cell->parent = o;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_link_s* haptive_sem_cell_s_push_link( haptive_sem_cell_s* o )
{
    haptive_sem_link_s* link = ( haptive_sem_link_s* )haptive_sem_cell_s_push_sem( o, TYPEOF_haptive_sem_link_s );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 * Channel naming:
 * Output channel has name 'y'
 * Input channels are named in order 'a', 'b' ...
 * If ever more than 24 input channels are used, excess channels carry no name.
 */
haptive_sem_cell_s* haptive_sem_cell_s_push_cell_op_d( haptive_sem_cell_s* o, haptive_op* op )
{
    haptive_sem_cell_s* cell = ( haptive_sem_cell_s* )haptive_sem_cell_s_push_cell( o );
    haptive_sem_cell_s_set_channels( cell, 1, haptive_op_a_get_arity( op ) );
    sc_t symbol = haptive_op_a_get_symbol( op );
    if( symbol ) cell->name = haptive_entypeof( symbol );
    cell->op = op;

    cell->priority = haptive_op_a_get_priority( op );
    cell->excs.data[ 0 ]->name = haptive_entypeof( "y" );

    for( sz_t i = 0; i < cell->encs.size; i++ )
    {
        if( i < 'y' - 'a' )
        {
            cell->encs.data[ 0 ]->name = haptive_entypeof_fa( "#<char>", 'a' + i );
        }
    }

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_push_cell_op_d_reset_name( haptive_sem_cell_s* o, haptive_op* op )
{
    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d( o, op );
    cell->name = 0;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_push_cell_op_d_set_source( haptive_sem_cell_s* o, haptive_op* op, bcore_source* source )
{
    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d( o, op );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( haptive_sem_cell_s* o, haptive_op* op, bcore_source* source )
{
    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name( o, op );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

/// v can be NULL pushing an undetermined scalar
haptive_sem_cell_s* haptive_sem_cell_s_push_cell_scalar( haptive_sem_cell_s* o, f3_t* v )
{
    haptive_op_ar0_literal_s* literal = haptive_op_ar0_literal_s_create();
    literal->h = bhvm_hf3_s_create();
    bhvm_hf3_s_set_scalar_pf3( literal->h, v );
    return haptive_sem_cell_s_push_cell_op_d_reset_name( o, ( haptive_op* )literal );
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_push_wrap_cell( haptive_sem_cell_s* o, haptive_sem_cell_s* src )
{
    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell( o );
    haptive_sem_cell_s_wrap_cell( cell, src );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_push_wrap_cell_set_source( haptive_sem_cell_s* o, haptive_sem_cell_s* src, bcore_source* source )
{
    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_wrap_cell( o, src );
    bcore_source_point_s_set( &cell->source_point, source );
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_sem_cell_s_assert_identifier_not_yet_defined( const haptive_sem_cell_s* o, tp_t name, bcore_source* source )
{
    if
    (
        haptive_sem_links_s_name_exists( &o->encs, name ) ||
        ( o->body && haptive_sem_body_s_name_exists( o->body, name ) )
    )
    {
        bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' already exists.", haptive_ifnameof( name ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_create_frame()
{
    if( !context_g ) haptive_context_setup();
    haptive_sem_cell_s* o = haptive_sem_cell_s_create();
    o->parent = &context_g->cell;
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

/// parses ( ... => ... )
void haptive_sem_cell_s_parse_signature( haptive_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );

    // parse excs
    {
        ASSERT( o->excs.size == 0 );
        bl_t first = true;
        while( !bcore_source_a_parse_bl_fa( source, " #?'=>'" ) )
        {
            if( !first ) bcore_source_a_parse_fa( source, " ," );
            haptive_sem_link_s* link = haptive_sem_link_s_create_setup( haptive_parse_name( source ), NULL, NULL, o, true );
            haptive_sem_links_s_push_d( &o->excs, link );
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
            haptive_sem_link_s* link = haptive_sem_link_s_create_setup( haptive_parse_name( source ), NULL, NULL, o, false );
            if( bcore_source_a_parse_bl_fa( source, " #?'='" ) )
            {
                link->up = haptive_sem_cell_s_evaluate_link( o->parent, source );
            }
            haptive_sem_links_s_push_d( &o->encs, link );
            first = false;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_sem_cell_s_parse( haptive_sem_cell_s* o, bcore_source* source )
{
    haptive_sem_cell_s* frame = o->parent;

    // cell signature without name is allowed
    if( !bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        tp_t tp_cell_name = haptive_parse_name( source );
        if( frame ) haptive_sem_cell_s_assert_identifier_not_yet_defined( frame, tp_cell_name, source );
        o->name = tp_cell_name;
    }

    bcore_source_point_s_set( &o->source_point, source );

    //  ( <args_out> => <args_in> ) { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        haptive_sem_cell_s_parse_signature( o, source );
        bcore_source_a_parse_fa( source, " {" );
        haptive_sem_cell_s_parse_body( o, source );
        bcore_source_a_parse_fa( source, " }" );
    }
    else // = 'expression yielding a cell'
    {
        bcore_source_a_parse_fa( source, " = " );
        haptive_sem_cell_s* cell = haptive_sem_cell_s_evaluate_cell( frame, source );
        haptive_sem_cell_s_wrap_cell( o, cell );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

st_s* haptive_sem_cell_s_create_signature( const haptive_sem_cell_s* o )
{
    st_s* s = st_s_create();
    st_s_push_fa( s, "(" );
    BFOR_EACH( i, &o->excs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", haptive_ifnameof( o->excs.data[ i ]->name ) );
    st_s_push_fa( s, "=>" );
    BFOR_EACH( i, &o->encs ) st_s_push_fa( s, "#<sc_t>#<sc_t>", i > 0 ? "," : "", haptive_ifnameof( o->encs.data[ i ]->name ) );
    st_s_push_fa( s, ")" );
    return s;
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_sem_cell_s_parse_verify_signature( const haptive_sem_cell_s* o, bcore_source* source )
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
            tp_t name = haptive_parse_name( source );
            if( !err ) err = ( index >= o->excs.size );
            if( !err ) err = o->excs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->excs.size;
        if( err )
        {
            st_s* sig = haptive_sem_cell_s_create_signature( o );
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
            tp_t name = haptive_parse_name( source );
            if( !err ) err = ( index >= o->encs.size );
            if( !err ) err = o->encs.data[ index ]->name != name;
            first = false;
            index++;
        }
        if( !err ) err = index != o->encs.size;
        if( err )
        {
            st_s* sig = haptive_sem_cell_s_create_signature( o );
            bcore_source_a_parse_err_fa( source, "Cell signature is '#<sc_t>'", sig->sc );
            st_s_discard( sig );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_sem_cell_s_parse_body( haptive_sem_cell_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " " );
    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #=?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'cell'" ) ) // definition of a cell
        {
            haptive_sem_cell_s_parse( haptive_sem_cell_s_push_cell( o ), source );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'verify_signature'" ) ) // verifies signature of wrapping cell
        {
            haptive_sem_cell_s_parse_verify_signature( o, source );
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'adaptive'" ) ) // defining a link to an adaptive operator
        {
            tp_t tp_name = haptive_parse_name( source );
            haptive_sem_link_s* link = haptive_sem_cell_s_push_link( o );
            haptive_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
            link->name = tp_name;
            haptive_op_ar1_adaptive_s* op_adaptive = haptive_op_ar1_adaptive_s_create();
            op_adaptive->name = tp_name;

            haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )op_adaptive, source );

            bcore_source_a_parse_fa( source, " =" );
            cell->encs.data[ 0 ]->up = haptive_sem_cell_s_evaluate_link( o, source );
            link->up = cell->excs.data[ 0 ];
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'recurrent'" ) ) // A link is defined as recurrent by attaching recurrent operator with open input channel
        {
            tp_t tp_name = haptive_parse_name( source );
            haptive_sem_link_s* link = haptive_sem_cell_s_push_link( o );
            haptive_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
            link->name = tp_name;
            haptive_op_ar2_recurrent_s* op_recurrent = haptive_op_ar2_recurrent_s_create();
            op_recurrent->name = tp_name;
            haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )op_recurrent, source );

            bcore_source_a_parse_fa( source, " =" );
            cell->encs.data[ 0 ]->up = haptive_sem_cell_s_evaluate_link( o, source );
            link->up = cell->excs.data[ 0 ];
        }
        else // identifier
        {
            tp_t tp_name = haptive_parse_name( source );

            vd_t item = NULL;

            if( ( item = haptive_sem_cell_s_get_exc_by_name( o, tp_name ) ) ) // identifier is exit channel of o
            {
                haptive_sem_link_s* link = item;
                if( link->up )
                {
                    bcore_source_a_parse_err_fa( source, "Channel '#<sc_t>' of cell '#<sc_t>' has already been defined.", haptive_ifnameof( tp_name ), haptive_ifnameof( o->name ) );
                }
                bcore_source_a_parse_fa( source, " =" );
                link->up = haptive_sem_cell_s_evaluate_link( o, source );
            }
            else if( ( item = haptive_sem_cell_s_get_link_by_name( o, tp_name ) ) ) // identifier is a link defined in o's body
            {
                haptive_sem_link_s* link = ( haptive_sem_link_s* )item;

                // Idle links should never occur. If they do, there is probably a bug in the haptive-compiler.
                if( !link->up       ) bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' is idle.", haptive_ifnameof( tp_name ) );
                if( !link->up->cell ) bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' has already been defined.", haptive_ifnameof( tp_name ) );
                haptive_sem_cell_s* cell = link->up->cell;
                if( cell->op && cell->op->_ == TYPEOF_haptive_op_ar2_recurrent_s )
                {
                    if( !cell->encs.data[ 1 ]->up )
                    {
                        bcore_source_a_parse_fa( source, " =" );
                        cell->encs.data[ 1 ]->up = haptive_sem_cell_s_evaluate_link( o, source );
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "Redefining a recurrent link '#<sc_t>'.", haptive_ifnameof( tp_name ) );
                    }
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' has already been defined.", haptive_ifnameof( tp_name ) );
                }
            }
            else // unknown identifier --> creates a link
            {
                haptive_sem_link_s* link = haptive_sem_cell_s_push_link( o );
                haptive_sem_cell_s_assert_identifier_not_yet_defined( o, tp_name, source );
                link->name = tp_name;
                bcore_source_a_parse_fa( source, " =" );
                link->up = haptive_sem_cell_s_evaluate_link( o, source );
            }

        }
        bcore_source_a_parse_fa( source, " ; " );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_sem_cell_s_evaluate_set_encs( haptive_sem_cell_s* o, haptive_sem_cell_s* parent, bcore_source* source )
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
                haptive_sem_link_s* link = haptive_sem_cell_s_get_enc_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' specifies no entry channel of cell '#<sc_t>'.", name->sc, haptive_ifnameof( o->name ) );
                }

                if( link->up )
                {
                    bcore_source_a_parse_err_fa( source, "Entry channel '#<sc_t>' of cell '#<sc_t>' has already been set.", name->sc, haptive_ifnameof( o->name ) );
                }

                link->up = haptive_sem_cell_s_evaluate_link( parent, source );
                done = true;
            }
            else
            {
                stack_push( stack, name );
            }
        }

        if( !done )
        {
            haptive_sem_link_s* link = haptive_sem_cell_s_get_enc_by_open( o );
            if( !link ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>': Number of free entry channels exceeded.", haptive_ifnameof( o->name ) );
            link->up = haptive_sem_cell_s_evaluate_link_stack( parent, stack, source );
        }

        first = false;
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/// in body of o: creates new cell wrapping the catenated cells: cell = { c1 : c2 }
haptive_sem_cell_s* haptive_sem_cell_s_cat_cell( haptive_sem_cell_s* o, haptive_sem_cell_s* c1, haptive_sem_cell_s* c2, bcore_source* source )
{
    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell( o );
    bcore_source_point_s_set( &cell->source_point, source );

    c1 = haptive_sem_cell_s_push_wrap_cell( cell, c1 );
    c2 = haptive_sem_cell_s_push_wrap_cell( cell, c2 );

    // only free input channels get wrapped (code below must change in case wrapping scheme changes)
    assert( c1->encs.size == haptive_sem_cell_s_get_arity( c1 ) );
    assert( c2->encs.size == haptive_sem_cell_s_get_arity( c2 ) );

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
    haptive_sem_cell_s_set_channels( cell, c1->excs.size, c2->encs.size );

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

void haptive_sem_cell_s_evaluate_stack( haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BLM_INIT();
    st_s* name = BLM_CREATE( st_s );

    haptive_sem_stack_flag_s* flag_bin_op    = BLM_CREATE( haptive_sem_stack_flag_s );
    haptive_sem_stack_flag_s* flag_una_op    = BLM_CREATE( haptive_sem_stack_flag_s );
    haptive_sem_stack_flag_s* flag_cell_cat  = BLM_CREATE( haptive_sem_stack_flag_s );
    haptive_sem_stack_flag_s* flag_inc_order = BLM_CREATE( haptive_sem_stack_flag_s );

    tp_t op2_symbol = 0;
    bhvm_hf3_s* literal = NULL;

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

            if( haptive_is_control_type( tp_name ) )
            {
                if( tp_name == TYPEOF_cell ) // inline cell definition
                {
                    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell( o );
                    haptive_sem_cell_s_parse( cell, source );
                    stack_push( stack, cell );
                }
                else if( tp_name == TYPEOF_if )
                {
                    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )haptive_op_ar3_branch_s_create(), source );
                    cell->encs.data[ 0 ]->up = haptive_sem_cell_s_evaluate_link( o, source );
                    bcore_source_a_parse_fa( source, " #skip';' then" );
                    cell->encs.data[ 1 ]->up = haptive_sem_cell_s_evaluate_link( o, source );
                    bcore_source_a_parse_fa( source, " #skip';' else" );
                    cell->encs.data[ 2 ]->up = haptive_sem_cell_s_evaluate_link( o, source );
                    stack_push( stack, cell->excs.data[ 0 ] );
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Unexpected keyword '#<sc_t>'. Did you miss ';' after previous statement?", name->sc );
                }
            }
            else
            {
                vd_t item = haptive_sem_cell_s_get_enc_by_name( o, tp_name );
                if( !item && o->body   ) item = haptive_sem_body_s_get_sem_by_name( o->body, tp_name );
                if( !item && o->parent ) item = haptive_sem_cell_s_get_cell_by_name( o->parent, tp_name );
                if( !item ) bcore_source_a_parse_err_fa( source, "Cannot evaluate identifier '#<sc_t>'.", name->sc );
                tp_t tp_item = *(aware_t*)item;

                switch( tp_item )
                {
                    case TYPEOF_haptive_sem_cell_s:
                    {
                        haptive_sem_cell_s* cell = item;
                        stack_push( stack, cell );
                    }
                    break;

                    case TYPEOF_haptive_sem_link_s: stack_push( stack, item ); break;
                    default: bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name->sc, ifnameof( tp_item ) );
                }
            }
        }

        // literal scalar (negative numbers are created via neg operator)
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]>='0'&&[0]<='9')" ) )
        {
            f3_t val = 0;
            bcore_source_a_parse_fa( source, " #<f3_t*>", &val );
            haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_scalar( o, &val );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // undetermined scalar
        else if( bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
        {
            haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_scalar( o, NULL );
            bcore_source_point_s_set( &cell->source_point, source );
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        // block or input channel selection in case l-value is a cell
        else if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
        {
            if( stack_of_type( stack, 1, TYPEOF_haptive_sem_cell_s ) )
            {
                haptive_sem_cell_s* cell = haptive_sem_cell_s_push_wrap_cell_set_source( o, stack_pop( stack ), source );
                haptive_sem_cell_s_evaluate_set_encs( cell, o, source );
                stack_push( stack, cell );
            }
            else
            {
                bcore_source_a_parse_fa( source, " (" );
                stack_push( stack, haptive_sem_cell_s_evaluate_sem( o, source ) );
                bcore_source_a_parse_fa( source, " )" );
            }
        }

        // binary operator from predefined symbols
        else if( ( op2_symbol = haptive_parse_op2_symbol( source ) ) )
        {
            if
            (
                stack->size == 0 ||
               ( stack->size >= 1 && stack_of_value( stack, 1, flag_una_op ) ) ||
               ( stack->size >= 3 && stack_of_value( stack, 3, flag_bin_op ) )
            )
            {
                // binary op not applicable, try unary
                haptive_sem_cell_s* cell = haptive_sem_cell_s_get_cell_by_name( o, op2_symbol );
                haptive_op* op_unary = haptive_op_a_create_op_of_arn( cell->op, 1 );
                if( op_unary )
                {
                    haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, op_unary, source );
                    stack_push( stack, cell );
                    stack_push( stack, flag_una_op ); // flag after cell to avoid incorrect stack evaluation
                }
                else
                {
                    if( stack->size == 0 )
                    {
                        bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", haptive_ifnameof( op2_symbol ) );
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Successive binary operator. Right operand expected.", haptive_ifnameof( op2_symbol ) );
                    }
                }
            }
            else
            {
                haptive_sem_cell_s* cell = haptive_sem_cell_s_get_cell_by_name( o, op2_symbol );
                if( !cell ) bcore_source_a_parse_err_fa( source, "Syntax error." );
                cell = haptive_sem_cell_s_push_wrap_cell_set_source( o, cell, source );
                stack_push( stack, flag_bin_op );
                stack_push( stack, cell );
            }
        }

        // custom binary operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'<<'" ) )
        {
            bcore_source_a_parse_fa( source, "#until'>'>>", name );
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", name->sc );
            haptive_sem_cell_s* cell = haptive_sem_cell_s_get_cell_by_name( o, typeof( name->sc ) );
            if( !cell ) bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>' not found.", name->sc );
            cell = haptive_sem_cell_s_push_wrap_cell_set_source( o, cell, source );
            stack_push( stack, flag_bin_op );
            stack_push( stack, cell );
        }

        // output channel selection
        else if( bcore_source_a_parse_bl_fa( source, " #?'.'" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );

            if( !stack_of_type( stack, 1, TYPEOF_haptive_sem_cell_s ) )
            {
                bcore_source_a_parse_err_fa( source, "Output channel selection on non-cell." );
            }

            haptive_sem_cell_s* cell = stack_pop( stack );
            haptive_sem_link_s* link = haptive_sem_cell_s_get_exc_by_name( cell, typeof( name->sc ) );

            if( haptive_sem_cell_s_get_arity( cell ) > 0 )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Output channel selection on cell '#<sc_t>' with #<sz_t> open input channels.",
                    haptive_ifnameof( cell->name ),
                    haptive_sem_cell_s_get_arity( cell )
                );
            }

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Cell '#<sc_t>': Invalid channel '#<sc_t>'.", haptive_ifnameof( cell->name ), name->sc );
            }
            stack_push( stack, link );
        }

        // array operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'['" ) )
        {
            haptive_sem_link_s* link = haptive_sem_cell_s_evaluate_link( o, source );
            bcore_source_a_parse_bl_fa( source, " ]" );

            if( stack_of_type( stack, 1, TYPEOF_haptive_sem_link_s ) )
            {
                haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )haptive_op_ar2_index_s_create(), source );
                cell->encs.data[ 0 ]->up = stack_pop_of_type( stack, TYPEOF_haptive_sem_link_s, source );
                cell->encs.data[ 1 ]->up = link;
                stack_push( stack, cell->excs.data[ 0 ] );
            }
            else
            {
                haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )haptive_op_ar2_inc_order_s_create(), source );
                cell->encs.data[ 0 ]->up = link;
                stack_push( stack, cell );
                stack_push( stack, flag_inc_order );
            }
        }

        // postfix htp
        else if( bcore_source_a_parse_bl_fa( source, " #?'^t'" ) )
        {
            haptive_sem_cell_s* htp_cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )haptive_op_ar1_htp_s_create(), source );
            if( stack_of_type( stack, 1, TYPEOF_haptive_sem_link_s ) )
            {
                htp_cell->encs.data[ 0 ]->up = stack_pop_of_type( stack, TYPEOF_haptive_sem_link_s, source );
                stack_push( stack, htp_cell->excs.data[ 0 ] );
            }
            else if( stack_of_type( stack, 1, TYPEOF_haptive_sem_cell_s ) )
            {
                haptive_sem_cell_s* r_cell = stack_pop_of_type( stack, TYPEOF_haptive_sem_cell_s, source );
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
            if( stack_of_type( stack, 1, TYPEOF_haptive_sem_cell_s ) )
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
        while( stack->size >= 3 && stack_of_value( stack, 2, flag_una_op ) && stack_of_type( stack, 1, TYPEOF_haptive_sem_link_s ) )
        {
            haptive_sem_link_s* link = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_una_op, source );
            haptive_sem_cell_s* cell = stack_pop_cell( stack, source );
            ASSERT( cell->encs.size == 1 );
            cell->encs.data[ 0 ]->up = link;
            stack_push( stack, cell->excs.data[ 0 ] );
        }

        if( stack->size >= 3 && stack_of_value( stack, 2, flag_bin_op ) )
        {
            haptive_sem_cell_s* cell = stack_pop_of_type( stack, TYPEOF_haptive_sem_cell_s, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            haptive_sem* arg1 = stack_pop( stack );

            if( arg1->_ == TYPEOF_haptive_sem_cell_s )
            {
                haptive_sem_cell_s* cell1 = ( haptive_sem_cell_s* )arg1;
                if( cell1->excs.size != 1 )
                {
                    bcore_source_point_s_parse_err_fa
                    (
                        &cell1->source_point,
                        "Binary operator '#<sc_t>': Left operant '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                        haptive_ifnameof( cell->name ),
                        haptive_ifnameof( cell1->name ),
                        cell1->excs.size
                    );
                }
                arg1 = ( haptive_sem* )cell1->excs.data[ 0 ];
            }

            if( haptive_sem_cell_s_get_arity( cell ) != 2 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has arity '#<sz_t>'. Expected: '2'.",
                    haptive_ifnameof( cell->name ),
                    haptive_sem_cell_s_get_arity( cell )
                );
            }

            if( cell->excs.size != 1 )
            {
                bcore_source_point_s_parse_err_fa
                (
                    &cell->source_point,
                    "Binary operator '#<sc_t>' has #<sz_t> output channels. Expected: 1.",
                    haptive_ifnameof( cell->name ),
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
            if( stack_of_type( stack, 1, TYPEOF_haptive_sem_cell_s ) )  // cell1 : cell2
            {
                haptive_sem_cell_s* cell2 = stack_pop_cell( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                haptive_sem_cell_s* cell1 = stack_pop_cell( stack, source );
                stack_push( stack, haptive_sem_cell_s_cat_cell( o, cell1, cell2, source ) );
            }
            else if( stack_of_type( stack, 1, TYPEOF_haptive_sem_link_s ) ) // cell : link
            {
                haptive_sem_link_s* link = stack_pop_link( stack, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                haptive_sem_cell_s* cell = stack_pop_cell( stack, source );
                cell = haptive_sem_cell_s_push_wrap_cell( o, cell );
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
        while( stack_of_value( stack, 2, flag_inc_order ) && stack_of_type( stack, 1, TYPEOF_haptive_sem_link_s ) )
        {
            haptive_sem_link_s* link2 = stack_pop_link( stack, source );
            stack_pop_of_value( stack, flag_inc_order, source );
            haptive_sem_cell_s* cell  = stack_pop_cell( stack, source );
            ASSERT( cell->encs.data[ 0 ]->up ); // was set at cell creation
            cell->encs.data[ 1 ]->up = link2;
            stack_push( stack, cell->excs.data[ 0 ] );
        }
    }

    /// remaining stack processing ...

    /// Binary operators
    while( stack->size >= 5 && stack_of_value( stack, 4, flag_bin_op ) ) // <left arg> <flag> <bin-operator> <output> <right arg>
    {
        haptive_sem_link_s* link2 = stack_pop_link_or_exit( stack, source );
        haptive_sem_link_s* out   = stack_pop_link( stack, source );
        haptive_sem_cell_s* cell  = stack_pop_cell( stack, source );
        stack_pop_of_value( stack, flag_bin_op, source );
        haptive_sem_link_s* link1 = stack_pop_link_or_exit( stack, source );

        if( stack->size >= 4 && stack_of_value( stack, 3, flag_bin_op ) ) // merge with prior operation considering priority
        {
            haptive_sem_link_s* prior_out   = stack_pop_link( stack, source );
            haptive_sem_cell_s* prior_cell  = stack_pop_cell( stack, source );
            stack_pop_of_value( stack, flag_bin_op, source );
            haptive_sem_link_s* prior_link1 = stack_pop_link_or_exit( stack, source );

            sz_t prior_priority = haptive_sem_cell_s_get_priority( prior_cell );
            sz_t cell_priority  = haptive_sem_cell_s_get_priority( cell );

            if( prior_priority >= cell_priority  )
            {
                haptive_sem_cell_s_get_enc_by_open( cell )->up = prior_out;
                haptive_sem_cell_s_get_enc_by_open( cell )->up = link2;

                stack_push( stack, prior_link1 );
                stack_push( stack, flag_bin_op );
                stack_push( stack, prior_cell );
                stack_push( stack, out );
                stack_push( stack, link1 );
            }
            else
            {
                haptive_sem_cell_s_get_enc_by_open( cell )->up = link1;
                haptive_sem_cell_s_get_enc_by_open( cell )->up = link2;

                stack_push( stack, prior_link1 );
                stack_push( stack, flag_bin_op );
                stack_push( stack, prior_cell );
                stack_push( stack, prior_out );
                stack_push( stack, out );           // out becomes right argument for prior_cell
            }
        }
        else // fully resolve operation
        {
            haptive_sem_cell_s_get_enc_by_open( cell )->up = link1;
            haptive_sem_cell_s_get_enc_by_open( cell )->up = link2;
            stack_push( stack, out );
        }
    }

    /// Adjacent holors
    while( stack->size >= 2 && stack_of_type( stack, 1, TYPEOF_haptive_sem_link_s ) && stack_of_type( stack, 2, TYPEOF_haptive_sem_link_s ) )
    {
        haptive_sem_link_s* link2 = stack_pop_link( stack, source );
        haptive_sem_link_s* link1 = stack_pop_link( stack, source );
        haptive_sem_cell_s* cell = haptive_sem_cell_s_push_cell_op_d_reset_name_set_source( o, ( haptive_op* )haptive_op_ar2_cat_s_create(), source );
        cell->encs.data[ 0 ]->up = link1;
        cell->encs.data[ 1 ]->up = link2;
        stack_push( stack, cell->excs.data[ 0 ] );
    }

    bhvm_hf3_s_detach( &literal );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem* haptive_sem_cell_s_evaluate_sem_stack( haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    haptive_sem_cell_s_evaluate_stack( o, stack, source );
    if( stack->size != 1 ) bcore_source_a_parse_err_fa( source, "Expression syntax error." );
    return stack_pop( stack );
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem* haptive_sem_cell_s_evaluate_sem( haptive_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    vd_t ret = haptive_sem_cell_s_evaluate_sem_stack( o, stack, source );
    BLM_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_link_s* haptive_sem_cell_s_evaluate_link_stack( haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    haptive_sem* ret = haptive_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret == TYPEOF_haptive_sem_cell_s )
    {
        haptive_sem_cell_s* cell = ( haptive_sem_cell_s* )ret;
        if( haptive_sem_cell_s_get_arity( cell ) > 0 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> open entry channels.", haptive_sem_cell_s_get_arity( cell ) );
        }

        if( cell->excs.size != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic exit channel selection on cell with #<sz_t> exit channels.", cell->excs.size );
        }

        ret = ( haptive_sem* )cell->excs.data[ 0 ];
    }

    if( *( aware_t* )ret != TYPEOF_haptive_sem_link_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Link expected.", ifnameof( *( aware_t* )ret ) );
    }

    return ( haptive_sem_link_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_link_s* haptive_sem_cell_s_evaluate_link( haptive_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    haptive_sem_link_s* ret = haptive_sem_cell_s_evaluate_link_stack( o, stack, source );
    BLM_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_evaluate_cell_stack( haptive_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    haptive_sem* ret = haptive_sem_cell_s_evaluate_sem_stack( o, stack, source );
    if( *( aware_t* )ret != TYPEOF_haptive_sem_cell_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Cell Expected.", ifnameof( *( aware_t* )ret ) );
    }
    return ( haptive_sem_cell_s* )ret;
}

// ---------------------------------------------------------------------------------------------------------------------

haptive_sem_cell_s* haptive_sem_cell_s_evaluate_cell( haptive_sem_cell_s* o, bcore_source* source )
{
    BLM_INIT();
    bcore_arr_vd_s* stack = BLM_CREATE( bcore_arr_vd_s );
    haptive_sem_cell_s* ret = haptive_sem_cell_s_evaluate_cell_stack( o, stack, source );
    BLM_RETURNV( haptive_sem_cell_s*, ret );
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
s2_t haptive_ctr_node_s_node_process( haptive_ctr_node_s* o, haptive_sem_cell_s* cell, bl_t enter, haptive_ctr_node_s** node_out )
{
    haptive_ctr_node_s* node = NULL;
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
            node = haptive_ctr_node_s_push_d( o, haptive_ctr_node_s_create() );
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

s2_t haptive_ctr_tree_s_tree_process( haptive_ctr_tree_s* o, haptive_sem_cell_s* cell, bl_t enter, haptive_ctr_node_s* node_in, haptive_ctr_node_s** node_out )
{
    if( enter )
    {
        haptive_ctr_node_s* node = NULL;
        if( !o->root )
        {
            o->root = haptive_ctr_node_s_create();
            o->root->id = o->id_base++;
            o->root->cell = cell;
            node = o->root;
            *node_out = node;
            return 0;
        }
        else if( !node_in ) // we just entered the tree frame
        {
            *node_out = o->root;
            return 0;
        }
        else
        {
            s2_t ret = haptive_ctr_node_s_node_process( node_in, cell, enter, &node );
            if( ret ) return ret;
            if( node->id < 0 ) node->id = o->id_base++;
            *node_out = node;
            return 0;
        }
    }
    else
    {
        return haptive_ctr_node_s_node_process( node_in, cell, enter, node_out );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bcore_source_point_s* haptive_ctr_node_s_get_nearest_source_point( haptive_ctr_node_s* o )
{
    if( !o ) return NULL;
    if( !o->cell ) return NULL;
    if( o->cell->source_point.source ) return &o->cell->source_point;
    return haptive_ctr_node_s_get_nearest_source_point( o->parent );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// net_node

/// recursive trace; exits when the enter membrane of the root cell is reached
void haptive_net_node_s_trace_to_sink( haptive_net_node_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o )
    {
        bcore_sink_a_push_fa( sink, "(NULL)" );
        return;
    }

    bl_t recurring = o->flag;

    if( recurring ) bcore_sink_a_push_fa( sink, "(recurring)" );

    o->flag = true;

    if( o->h )
    {
        bhvm_hf3_s_brief_to_sink( o->h, sink );
    }

    sc_t symbol = "";
    if( o->op )
    {
        sc_t symbol = haptive_op_a_get_symbol( o->op );
        if( !symbol ) symbol = ifnameof( o->op->_ );
        bcore_sink_a_push_fa( sink, "(#<sc_t>)", symbol );
    }
    else
    {
        bcore_sink_a_push_fa( sink, "(noop)", symbol );
    }

    if( !recurring )
    {
        for( sz_t i = 0; i < o->upls.size; i++ )
        {
            sz_t incr = 4;
            bcore_sink_a_push_fa( sink, "\n#rn{ }#rn{-}", indent, incr );
            haptive_net_node_s* node = o->upls.data[ i ]->node;
            haptive_net_node_s_trace_to_sink( node, indent + incr, sink );
        }
    }

    o->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_net_node_s_err_fa( haptive_net_node_s* o, sc_t format, ... )
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

/// calls op-solve and sets node-holor
static sz_t net_node_s_op_solve( haptive_net_node_s* o, bhvm_hf3_s** arg_h )
{
    st_s* err_msg = st_s_create();
    sz_t result = haptive_op_a_solve( o->op, &o->h, arg_h, err_msg );

    if( result < 0 )
    {
        sz_t arity = haptive_op_a_get_arity( o->op );
        sc_t name = haptive_op_a_get_symbol( o->op );
        if( !name ) name = ifnameof( o->op->_ );
        st_s* msg = st_s_create();
        st_s_push_fa( msg, "Operator '#<sc_t>' failed:", name );
        if( err_msg->size > 0 ) st_s_push_fa( msg, " #<sc_t>", err_msg->sc );
        st_s_push_fa( msg, "\n" );
        for( sz_t i = 0; i < arity; i++ )
        {
            st_s_push_fa( msg, "arg[#<sz_t>]: ", i );
            if( arg_h[ i ] )
            {
                bhvm_hf3_s_brief_to_sink( arg_h[ i ], (bcore_sink*)msg );
            }
            else
            {
                st_s_push_fa( msg, "null" );
            }
            st_s_push_fa( msg, "\n" );
        }
        haptive_net_node_s_err_fa( o, "#<sc_t>", msg->sc );
        st_s_discard( msg );
    }
    st_s_discard( err_msg );
    return result;
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 *  Function 'solve' executes operator->solve to compute a holor.
 *  If a holor can be computed (vacant or determined), the solve-route is considered finished
 *  and will not be processed again. A detached result (o->h == NULL) causes a route to be reentered.
 *  If operator->solve returns 1, the operation is considered settled, in which case all uplinks
 *  are removed and the operator is switched to a final arity0 version via haptive_op_a_create_final.
 *  After settling, the graph can be run through an optimizer minimizing its structure.
 */
void haptive_net_node_s_solve( haptive_net_node_s* o )
{
    if( o->flag ) return; // cyclic link

    o->flag = true;

    if( o->h ) return;

    if( o->op )
    {
        sz_t arity = haptive_op_a_get_arity( o->op );
        if( arity != o->upls.size )
        {
            haptive_net_node_s_err_fa( o, "Operator arity #<sz_t> differs from node arity #<sz_t>", arity, o->upls.size );
        }

        #define haptive_MAX_ARITY 4 /* increase this number when assertion below fails */
        ASSERT( arity <= haptive_MAX_ARITY );
        bhvm_hf3_s* arg_h[ haptive_MAX_ARITY ] = { NULL };

        sz_t result = -1;

        bl_t solve_each_channel = haptive_op_a_solve_each_channel( o->op );

        for( sz_t i = 0; i < arity; i++ )
        {
            haptive_net_node_s* arg_n = o->upls.data[ i ]->node;
            if( arg_n )
            {
                haptive_net_node_s_solve( arg_n );
                arg_h[ i ] = arg_n->h;
            }
            if( solve_each_channel ) result = net_node_s_op_solve( o, arg_h );
        }

        if( result < 0 ) result = net_node_s_op_solve( o, arg_h );

        // operation is settled and can be removed
        if( result >= 1 )
        {
            haptive_op_a_attach( &o->op, haptive_op_a_create_final( o->op, o->h ) );
            haptive_net_links_s_clear( &o->upls );
            if( result == 2 && o->h ) bhvm_hf3_s_set_vacant( o->h );
        }
    }

    o->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

/// Outputs the graph structure in text form to sink
void haptive_net_node_s_graph_to_sink( haptive_net_node_s* o, bcore_sink* sink )
{
    haptive_net_node_s_trace_to_sink( o, 0, sink );
    bcore_sink_a_push_fa( sink, "\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively sets downlinks for all non-flagged uplinks.
 *  Assumes initial state was normal.
 */
void haptive_net_node_s_set_downlinks( haptive_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( i, &o->upls )
    {
        haptive_net_node_s* node = o->upls.data[ i ]->node;
        haptive_net_links_s_push( &node->dnls )->node = o;
        haptive_net_node_s_set_downlinks( node );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively skips identities.
 *  Assumes initial state was normal and downlinks not set
 */
void haptive_net_node_s_skip_identities( haptive_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( i, &o->upls )
    {
        haptive_net_node_s* node = o->upls.data[ i ]->node;
        while( node && node->op && node->op->_ == TYPEOF_haptive_op_ar1_identity_s ) node = node->upls.data[ i ]->node;
        ASSERT( node );
        o->upls.data[ i ]->node = node;
        haptive_net_node_s_skip_identities( node );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively sets flags for all nodes reachable via uplink.
 *  Assumes initial state was normal.
 */
void haptive_net_node_s_set_flags( haptive_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( i, &o->upls ) haptive_net_node_s_set_flags( o->upls.data[ i ]->node );
}

// ---------------------------------------------------------------------------------------------------------------------

static void net_node_s_vm_build_infer( haptive_net_node_s* o, bhvm_hf3_vm_frame_s* vm_frame )
{
    ASSERT( o );
    if( o->flag ) return;
    o->flag = true;
    if( !o->h ) ERR_fa( "Holor is missing." );

    BLM_INIT();
    bcore_arr_sz_s* arr_index = BLM_CREATE( bcore_arr_sz_s );
    st_s* arr_sig             = BLM_CREATE( st_s );
    BFOR_EACH( i, &o->upls )
    {
        haptive_net_node_s* node = o->upls.data[ i ]->node;
        net_node_s_vm_build_infer( node, vm_frame );
        bcore_arr_sz_s_push( arr_index, node->id );
        st_s_push_char( arr_sig, 'a' + i );
    }
    bcore_arr_sz_s_push( arr_index, o->id );
    st_s_push_char( arr_sig, 'y' );

    ASSERT( o->id >= 0 && o->id < vm_frame->arr_holor.size );
    bhvm_hf3_vm_holor_s* vm_holor = &vm_frame->arr_holor.data[ o->id ];
    vm_holor->name = o->name;
    bhvm_hf3_s_copy( &vm_holor->h, o->h );
    if( o->op && o->op->_ == TYPEOF_haptive_op_ar0_adaptive_s )
    {
        haptive_op_ar0_adaptive_s* op_ar0_adapt = ( haptive_op_ar0_adaptive_s* )o->op;
        vm_holor->type = TYPEOF_holor_type_adaptive;
        vm_holor->name = op_ar0_adapt->name;
        bhvm_hf3_s_copy( &vm_holor->h, op_ar0_adapt->h );
    }
    else
    {
        vm_holor->type = ( o->h->v_size == 0 ) ? TYPEOF_holor_type_depletable : TYPEOF_holor_type_data;
    }

    if( o->op )
    {
        ASSERT( haptive_op_a_get_arity( o->op ) == o->upls.size );

        // axon-initialization
        bhvm_hf3_vm_op* vm_op = haptive_op_a_create_vm_op_ap_init_set_idx( o->op, vm_frame, arr_sig->sc, arr_index );
        if( vm_op )
        {
            bhvm_hf3_vm_frame_s_mcode_op_push_d( vm_frame, TYPEOF_mcode_name_ap_init, vm_op );
        }

        vm_op = haptive_op_a_create_vm_op_ap_set_idx( o->op, vm_frame, arr_sig->sc, arr_index );

        // axon-pass
        if( vm_op )
        {
            switch( haptive_op_a_get_class( o->op ) )
            {
                case TYPEOF_op_class_regular:
                {
                    bhvm_hf3_vm_frame_s_mcode_op_push_d( vm_frame, TYPEOF_mcode_name_infer, vm_op );
                }
                break;

                case TYPEOF_op_class_cast:
                {
                    vm_holor->type = TYPEOF_holor_type_cast;
                    bhvm_hf3_vm_frame_s_mcode_op_push_d( vm_frame, TYPEOF_mcode_name_cast, vm_op );
                }
                break;

                default: ERR_fa( "Invalid operator class" );
            }
        }
        else
        {
            if( o->upls.size > 0 )
            {
                ERR_fa( "Could not create axon-pass from #<sc_t>.", ifnameof( o->op->_ ) );
            }
        }
    }
    else
    {
        if( o->upls.size > 0 )
        {
            ERR_fa( "Node has uplinks but no operator." );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static void node_s_vm_build_bp_grad( haptive_net_node_s* o, sz_t up_index, bhvm_hf3_vm_frame_s* vm_frame )
{
    ASSERT( o );
    if( !o->h ) ERR_fa( "Holor is missing." );

    BLM_INIT();

    if( !o->flag ) // build gradient computation for this node
    {
        o->gid = vm_frame->arr_holor.size;

        bhvm_hf3_vm_holor_s* vm_holor = bhvm_hf3_vm_frame_s_holors_push( vm_frame );
        vm_holor->name = o->name;
        bhvm_hf3_s_copy_shape( &vm_holor->h, o->h );

        if( o->op && o->op->_ == TYPEOF_haptive_op_ar0_adaptive_s )
        {
            haptive_op_ar0_adaptive_s* op_adapt = ( haptive_op_ar0_adaptive_s* )o->op;
            vm_holor->name = op_adapt->name;
            vm_holor->type = TYPEOF_holor_type_adaptive_grad;
        }
        else
        {
            vm_holor->type = TYPEOF_holor_type_depletable;

            /// zero gradient for non-casts
            if( o->dnls.size > 0 && ( haptive_op_a_get_class( o->op ) != TYPEOF_op_class_cast ) )
            {
                bhvm_hf3_vm_frame_s_mcode_op_push_d( vm_frame, TYPEOF_mcode_name_bp_grad, bhvm_hf3_vm_op_ar0_zro_s_csetup( NULL, o->gid ) );
            }
        }

        bhvm_hf3_vm_frame_s_holors_get_by_index( vm_frame, o->id  )->idx_paired = o->gid;
        bhvm_hf3_vm_frame_s_holors_get_by_index( vm_frame, o->gid )->idx_paired = o->id;

        // build this gradient from all downlinks ...
        BFOR_EACH( i, &o->dnls )
        {
            haptive_net_node_s* node = o->dnls.data[ i ]->node;
            ASSERT( node->h );
            sz_t node_up_index = -1;
            BFOR_EACH( j, &node->upls )
            {
                if( node->upls.data[ j ]->node == o )
                {
                    node_up_index = j;
                    break;
                }
            }
            ASSERT( node_up_index >= 0 );
            node_s_vm_build_bp_grad( node, node_up_index, vm_frame );
        }

        o->flag = true;
    }

    // update uplink gradient ...
    if( up_index >= 0 )
    {
        bcore_arr_sz_s* arr_index = BLM_CREATE( bcore_arr_sz_s );
        st_s* arr_sig             = BLM_CREATE( st_s );

        sz_t up_gid = -1;

        BFOR_EACH( i, &o->upls )
        {
            haptive_net_node_s* node = o->upls.data[ i ]->node;
            ASSERT( node->h );
            bcore_arr_sz_s_push( arr_index, node->id );
            st_s_push_char( arr_sig, 'a' + i );
            if( i == up_index ) up_gid = node->gid;
        }

        ASSERT( up_gid >= 0 );

        bcore_arr_sz_s_push( arr_index, o->id );
        st_s_push_char( arr_sig, 'y' );

        bcore_arr_sz_s_push( arr_index, up_gid );
        st_s_push_char( arr_sig, 'u' );

        bcore_arr_sz_s_push( arr_index, o->gid );
        st_s_push_char( arr_sig, 'v' );

        ASSERT( o->op );
        bhvm_hf3_vm_op* vm_op = haptive_op_a_create_vm_op_dp_set_idx( o->op, vm_frame, arr_sig->sc, arr_index, 'a' + up_index );

        if( vm_op )
        {
            switch( haptive_op_a_get_class( o->op ) )
            {
                case TYPEOF_op_class_regular:
                {
                    bhvm_hf3_vm_frame_s_mcode_op_push_d( vm_frame, TYPEOF_mcode_name_bp_grad, vm_op );
                }
                break;

                case TYPEOF_op_class_cast:
                {
                    bhvm_hf3_vm_holor_s* up_vm_holor = bhvm_hf3_vm_frame_s_holors_get_by_index( vm_frame, o->gid );
                    up_vm_holor->type = TYPEOF_holor_type_cast;

                    /** Note: dendrite pass casts must be added in reverse order.
                     *  This ensures that subsequent casts all refer to the correct target.
                     */
                    bhvm_hf3_vm_frame_s_mcode_op_push_d( vm_frame, TYPEOF_mcode_name_cast_reverse, vm_op );
                }
                break;

                default: ERR_fa( "Invalid operator class" );
            }

        }
        else
        {
            ERR_fa( "Could not create dendrite-pass from #<sc_t>.", ifnameof( o->op->_ ) );
        }
    }

    BLM_DOWN();
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
void haptive_net_cell_s_normalize( haptive_net_cell_s* o )
{
    bcore_arr_vd_s* arr = bcore_arr_vd_s_create();
    BFOR_EACH( i, &o->body ) bcore_arr_vd_s_push( arr, o->body.data[ i ] );
    BFOR_EACH( i, &o->encs ) bcore_arr_vd_s_push( arr, o->encs.data[ i ] );
    BFOR_EACH( i, &o->excs ) bcore_arr_vd_s_push( arr, o->excs.data[ i ] );

    // sort references descending (to move zeros to the end)
    bcore_array_a_sort_f( ( bcore_array* )arr, 0, -1, ( bcore_cmp_f ){ .f = cmp_vd, .o = NULL }, -1 );

    // remove zeros
    if( arr->size > 0 )
    {
        BFOR_EACH( i, arr )
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
    BFOR_EACH( i, arr ) arr->data[ i ] = bcore_fork( arr->data[ i ] );

    // new body
    haptive_net_nodes_s_set_size( &o->body, 0 );
    for( sz_t i = 0; i < arr->size; i++ )
    {
        haptive_net_node_s* node = haptive_net_nodes_s_push_d( &o->body, arr->data[ i ] );
        assert( node == arr->data[ i ] );
        node->id = i;
        node->flag = false;
    }

    bcore_arr_vd_s_discard( arr );
}

// ---------------------------------------------------------------------------------------------------------------------

/// Checks consistency of a normalized cell
bl_t haptive_net_cell_s_is_consistent( const haptive_net_cell_s* o )
{
    BFOR_EACH( i, &o->body )
    {
        const haptive_net_node_s* node = o->body.data[ i ];
        if( node->flag ) return false;
        if( node->id != i ) return false;
        BFOR_EACH( i, &node->upls )
        {
            const haptive_net_node_s* node2 = node->upls.data[ i ]->node;
            if( node2->id < 0 ) return false;
            if( node2->id >= o->body.size ) return false;
            if( node2 != o->body.data[ node2->id ] ) return false;
        }

        BFOR_EACH( i, &node->dnls )
        {
            const haptive_net_node_s* node2 = node->dnls.data[ i ]->node;
            if( node2->id < 0 ) return false;
            if( node2->id >= o->body.size ) return false;
            if( node2 != o->body.data[ node2->id ] ) return false;
        }
        if( node->h && !bhvm_hf3_s_is_consistent( node->h ) ) return false;
    }

    BFOR_EACH( i, &o->encs )
    {
        const haptive_net_node_s* node2 = o->encs.data[ i ];
        if( node2->id < 0 ) return false;
        if( node2->id >= o->body.size ) return false;
        if( node2 != o->body.data[ node2->id ] ) return false;
        if( node2->h && !bhvm_hf3_s_is_consistent( node2->h ) ) return false;
    }

    BFOR_EACH( i, &o->excs )
    {
        const haptive_net_node_s* node2 = o->excs.data[ i ];
        if( node2->id < 0 ) return false;
        if( node2->id >= o->body.size ) return false;
        if( node2 != o->body.data[ node2->id ] ) return false;
        if( node2->h && !bhvm_hf3_s_is_consistent( node2->h ) ) return false;
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_net_cell_s_copy_x( haptive_net_cell_s* o )
{
    BFOR_EACH( i, &o->body )
    {
        const haptive_net_node_s* node = o->body.data[ i ];
        ASSERT( node->id == i );
        BFOR_EACH( i, &node->upls )
        {
            const haptive_net_node_s* node2 = node->upls.data[ i ]->node;
            ASSERT( node2->id >= 0 );
            ASSERT( node2->id < o->body.size );
            node->upls.data[ i ]->node = o->body.data[ node2->id ];
        }
        BFOR_EACH( i, &node->dnls )
        {
            const haptive_net_node_s* node2 = node->dnls.data[ i ]->node;
            ASSERT( node2->id >= 0 );
            ASSERT( node2->id < o->body.size );
            node->dnls.data[ i ]->node = o->body.data[ node2->id ];
        }
    }

    BFOR_EACH( i, &o->encs )
    {
        sz_t id = o->encs.data[ i ]->id;
        ASSERT( id >= 0 );
        ASSERT( id < o->body.size );
        haptive_net_node_s_detach( &o->encs.data[ i ] );
        o->encs.data[ i ] = bcore_fork( o->body.data[ id ] );
    }

    BFOR_EACH( i, &o->excs )
    {
        sz_t id = o->excs.data[ i ]->id;
        ASSERT( id >= 0 );
        ASSERT( id < o->body.size );
        haptive_net_node_s_detach( &o->excs.data[ i ] );
        o->excs.data[ i ] = bcore_fork( o->body.data[ id ] );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_net_cell_s_set_downlinks( haptive_net_cell_s* o )
{
    haptive_net_cell_s_clear_flags( o );
    haptive_net_cell_s_clear_downlinks( o );
    BFOR_EACH( i, &o->excs ) haptive_net_node_s_set_downlinks( o->excs.data[ i ] );
    haptive_net_cell_s_clear_flags( o );
    assert( haptive_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes not reachable via uplink from exit channels
 *  Creates an warning in case an entry channel is unreachable.
 */
void haptive_net_cell_s_remove_unreachable_nodes( haptive_net_cell_s* o )
{
    haptive_net_cell_s_clear_flags( o );
    BFOR_EACH( i, &o->excs ) haptive_net_node_s_set_flags( o->excs.data[ i ] );
    BFOR_EACH( i, &o->encs )
    {
        haptive_net_node_s* node = o->encs.data[ i ];
        if( !node->flag && ( !( node->h && node->h->v_size > 0 ) ) )
        {
            bcore_source_point_s_parse_msg_to_sink_fa( node->source_point, BCORE_STDERR, "Warning: Entry channel [#<sz_t>] '#<sc_t>' has no effect.", i, haptive_ifnameof( node->name ) );
        }
        node->flag = true;
    }

    BFOR_EACH( i, &o->body ) if( !o->body.data[ i ]->flag ) haptive_net_node_s_detach( &o->body.data[ i ] );
    haptive_net_cell_s_normalize( o );

    assert( haptive_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes containing an identity operator and relinks remaining nodes accordingly
 *  Clears all downlinks;
 */
void haptive_net_cell_s_remove_identities( haptive_net_cell_s* o )
{
    haptive_net_cell_s_clear_downlinks( o );
    haptive_net_cell_s_clear_flags( o );
    BFOR_EACH( i, &o->excs ) haptive_net_node_s_skip_identities( o->excs.data[ i ] );
    haptive_net_cell_s_clear_flags( o );
    haptive_net_cell_s_remove_unreachable_nodes( o );
    assert( haptive_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively building a network cell from a semantic cell using membrane-technique.
 *  Exits when the enter membrane of the root cell is reached.
 *  This function does not set downlinks.
 */
static void net_cell_s_from_sem_recursive
(
    haptive_net_cell_s* o,
    haptive_sem_link_s* link,
    haptive_ctr_tree_s* ctr_tree,
    haptive_ctr_node_s* ctr_node,
    haptive_net_node_s* net_node_dn,
    sz_t             depth,
    bcore_sink*      log  // optional
)
{
    depth++;
    tp_t name = link->name;
    if( log ) bcore_sink_a_push_fa( log, "Tracing link '#<sc_t>' at depth #<sz_t>\n", haptive_ifnameof( name ), depth );
    link = haptive_sem_link_s_trace_to_cell_membrane( link );
    if( !link ) ERR_fa( "Backtracing '#<sc_t>':\nTrace ends in open link.", haptive_ifnameof( name ) );
    haptive_sem_cell_s* cell = link->cell;
    haptive_sem_link_s* next_link = NULL;

    if( depth > o->max_depth )
    {
        bcore_source_point_s_parse_err_fa( &cell->source_point, "Maximum depth '#<sz_t>' exceeded: This problem might be the result of an indefinite recursion.\n", o->max_depth );
    }

    if( link->exit )
    {
        bcore_source_point_s_parse_msg_to_sink_fa( &cell->source_point, log, "entering cell: '#<sc_t>' \n", haptive_nameof( cell->name ) );

        // since we backtrace, a cell is entered through an 'exit' link
        s2_t err = haptive_ctr_tree_s_tree_process( ctr_tree, cell, true, ctr_node, &ctr_node );
        if( err )
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nEntering cell failed.", haptive_ifnameof( name ) );
        }

        if( cell->op )
        {
            if( log ) bcore_sink_a_push_fa( log, "cell op: #<sc_t>\n", ifnameof( cell->op->_ ) );

            bl_t trace_up = false;
            haptive_net_node_s* net_node_up = haptive_net_nodes_s_get_by_id( &o->body, ctr_node->id );
            if( !net_node_up )
            {
                net_node_up = haptive_net_nodes_s_push( &o->body );
                net_node_up->id = ctr_node->id;
                net_node_up->op = bcore_fork( cell->op );

                bcore_source_point_s_attach( &net_node_up->source_point, bcore_fork( haptive_ctr_node_s_get_nearest_source_point( ctr_node ) ) );

                trace_up = haptive_op_a_get_arity( net_node_up->op ) > 0;
                if( log ) bcore_sink_a_push_fa( log, "new node id: '#<sz_t>'\n", net_node_up->id );
            }

            if( trace_up )
            {
                sz_t arity = haptive_op_a_get_arity( net_node_up->op );
                ASSERT( arity == cell->encs.size );

                if( net_node_up->op->_ == TYPEOF_haptive_op_ar3_branch_s )
                {
                    if( log ) bcore_sink_a_push_fa( log, "Branch channel 0:\n" );
                    net_cell_s_from_sem_recursive( o, cell->encs.data[ 0 ], ctr_tree, ctr_node, net_node_up, depth, log );
                    haptive_net_node_s* arg0 = net_node_up->upls.data[ 0 ]->node;
                    haptive_net_node_s_solve( arg0 );
                    if( arg0->h->v_data ) // determined holor
                    {
                        haptive_net_links_s_clear( &net_node_up->upls );
                        haptive_op_a_attach( &net_node_up->op, ( haptive_op* )haptive_op_ar1_identity_s_create() );
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

            haptive_net_links_s_push( &net_node_dn->upls )->node = net_node_up;
        }
        else if( link->up )
        {
            next_link = link->up;
        }
        else
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nOpen exit link '#<sc_t>'.", haptive_ifnameof( name ), haptive_ifnameof( link->name ) );
        }
    }
    else
    {
        if( log ) bcore_sink_a_push_fa( log, "exiting cell: '#<sc_t>' \n", haptive_ifnameof( cell->name ) );

        s2_t err = haptive_ctr_tree_s_tree_process( ctr_tree, cell, false, ctr_node, &ctr_node );
        if( err )
        {
            if( err == 1 )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting from untraced cell.", haptive_ifnameof( name ) );
            }
            else
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting cell failed.", haptive_ifnameof( name ) );
            }
        }

        if( !ctr_node ) // root membrane reached (trace ended)
        {
            sz_t index = haptive_sem_links_s_get_index_by_link( &cell->encs, link );
            if( index == -1 )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nEnding trace: No matching input channel.", haptive_ifnameof( name ) );
            }
            if( index >= o->encs.size )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nInput channel boundary exceeded.", haptive_ifnameof( name ) );
            }

            haptive_net_node_s* net_node_up = o->encs.data[ index ];
            haptive_net_links_s_push( &net_node_dn->upls )->node = net_node_up;

            next_link = NULL;
        }

        else if( link->up )
        {
            next_link = link->up;
        }
        else
        {
            next_link = haptive_sem_cell_s_get_enc_by_dn( ctr_node->cell, link );
            if( !next_link )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nTrace ends in open link.", haptive_ifnameof( name ) );
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

/// Finalization steps: Solves graph and optimizes it
void haptive_net_cell_s_finalize( haptive_net_cell_s* o )
{
    haptive_net_cell_s_solve( o );
    haptive_net_cell_s_remove_identities( o );
    haptive_net_cell_s_set_downlinks( o );
    ASSERT( haptive_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Builds a net cell from a semantic cell
 *  This function locks and initializes the randomizer to ensure a deterministic sequence of random values.
 */
void haptive_net_cell_s_from_sem_cell
(
    haptive_net_cell_s* o,
    haptive_sem_cell_s* sem_cell,
    haptive_op* (*input_op_create)( vd_t arg, sz_t in_idx, tp_t in_name ),
    vd_t arg,
    bcore_sink* log
)
{
    ASSERT( sem_cell );
    bcore_mutex_s_lock( context_g->randomizer_mutex );
    ASSERT( !context_g->randomizer_is_locked );
    context_g->randomizer_is_locked = true;
    context_g->randomizer_rval = 0; // rval == 0 causes randomizer to be seeded by functions using it.

    haptive_ctr_tree_s* tree = haptive_ctr_tree_s_create();
    for( sz_t i = 0; i < sem_cell->encs.size; i++ )
    {
        haptive_sem_link_s* sem_link = sem_cell->encs.data[ i ];
        haptive_net_node_s* net_node = haptive_net_nodes_s_push( &o->encs );
        net_node->name = sem_link->name;
        net_node->id   = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        net_node->op = input_op_create ? input_op_create( arg, i, sem_link->name ) : NULL;
    }

    for( sz_t i = 0; i < sem_cell->excs.size; i++ )
    {
        haptive_sem_link_s* sem_link = sem_cell->excs.data[ i ];
        haptive_net_node_s* net_node = haptive_net_nodes_s_push( &o->excs );
        net_node->name = sem_link->name;
        net_node->id = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        haptive_op_ar1_output_s* op_ar1_output = haptive_op_ar1_output_s_create();
        net_node->op = ( haptive_op* )op_ar1_output;
        net_cell_s_from_sem_recursive( o, sem_link, tree, NULL, net_node, 0, log );
    }

    haptive_ctr_tree_s_discard( tree );

    haptive_net_cell_s_normalize( o );
    assert( haptive_net_cell_s_is_consistent( o ) );

    ASSERT( haptive_net_cell_s_is_consistent( o ) );
    haptive_net_cell_s_finalize( o );

    context_g->randomizer_is_locked = false;
    bcore_mutex_s_unlock( context_g->randomizer_mutex );
}

// ---------------------------------------------------------------------------------------------------------------------

/// outputs graph to sink
void haptive_net_cell_s_graph_to_sink( haptive_net_cell_s* o, bcore_sink* sink )
{
    BFOR_EACH( i, &o->excs ) haptive_net_node_s_graph_to_sink( o->excs.data[ i ], sink );
}

// ---------------------------------------------------------------------------------------------------------------------

// builds main vm procedure
void haptive_cell_s_vm_build_infer( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
{
    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_infer );
    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_setup );
    ASSERT( haptive_net_cell_s_is_consistent( o ) );

    bhvm_hf3_vm_arr_holor_s_set_size( &vmf->arr_holor, o->body.size );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        haptive_net_node_s* node = o->excs.data[ i ];
        if( !node->h ) ERR_fa( "Unsolved node '#<sc_t>'\n", haptive_ifnameof( node->name ) );
        net_node_s_vm_build_infer( node, vmf );
    }

    haptive_net_cell_s_clear_flags( o );
}

// ---------------------------------------------------------------------------------------------------------------------

// builds bp_grad vm procedure
void haptive_cell_s_vm_build_bp_grad( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
{
    if( !bhvm_hf3_vm_frame_s_mcode_exists( vmf, TYPEOF_mcode_name_infer ) )
    {
        ERR_fa( "Procedure 'infer' missing. Call 'build_infer' first." );
    }

    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_bp_grad );
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        haptive_net_node_s* node = o->body.data[ i ];
        if( !node->op ) continue;
        if( node->op->_ != TYPEOF_haptive_op_ar0_adaptive_s ) continue;
        node_s_vm_build_bp_grad( node, -1, vmf );
    }
    haptive_net_cell_s_clear_flags( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_vm_build_setup( bhvm_hf3_vm_frame_s* o, u2_t rseed )
{
    const bhvm_hf3_vm_arr_holor_s* arr_holor = &o->arr_holor;
    for( sz_t i = 0; i < arr_holor->size; i++ )
    {
        const bhvm_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
        switch( holor->type )
        {
            case TYPEOF_holor_type_depletable:
            case TYPEOF_holor_type_adaptive_grad:
            {
                bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_setup, bhvm_hf3_vm_op_ar0_determine_s_csetup( NULL, i ) );
            }
            break;

            case TYPEOF_holor_type_adaptive:
            {
                if( holor->h.v_size == 0 )
                {
                    bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_setup, bhvm_hf3_vm_op_ar0_determine_s_csetup( NULL, i ) );
                    bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_setup, bhvm_hf3_vm_op_ar0_randomize_s_csetup_randomize( NULL, i, rseed, 1.0, -0.5, 0.5 ) );
                }
            }
            break;

            default: break;
        }
    }

    // moving init subroutines to setup ...

    if( bhvm_hf3_vm_frame_s_mcode_exists( o, TYPEOF_mcode_name_cast ) )
    {
        bhvm_hf3_vm_frame_s_mcode_push( o, TYPEOF_mcode_name_setup, TYPEOF_mcode_name_cast );
        bhvm_hf3_vm_frame_s_mcode_remove( o, TYPEOF_mcode_name_cast );
    }

    if( bhvm_hf3_vm_frame_s_mcode_exists( o, TYPEOF_mcode_name_cast_reverse ) )
    {
        bhvm_hf3_vm_frame_s_mcode_push_reverse( o, TYPEOF_mcode_name_setup, TYPEOF_mcode_name_cast_reverse );
        bhvm_hf3_vm_frame_s_mcode_remove( o, TYPEOF_mcode_name_cast_reverse );
    }

    if( bhvm_hf3_vm_frame_s_mcode_exists( o, TYPEOF_mcode_name_ap_init ) )
    {
        bhvm_hf3_vm_frame_s_mcode_push( o, TYPEOF_mcode_name_setup, TYPEOF_mcode_name_ap_init );
        bhvm_hf3_vm_frame_s_mcode_remove( o, TYPEOF_mcode_name_ap_init );
    }

    o->mcode_setup = TYPEOF_mcode_name_setup;
}

// ---------------------------------------------------------------------------------------------------------------------

// builds vm procedure shelve for all holors
void haptive_vm_build_shelve( bhvm_hf3_vm_frame_s* o )
{
    bhvm_hf3_vm_frame_s_mcode_reset( o, TYPEOF_mcode_name_shelve );

    const bhvm_hf3_vm_arr_holor_s* arr_holor = &o->arr_holor;
    for( sz_t i = 0; i < arr_holor->size; i++ )
    {
        const bhvm_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
        switch( holor->type )
        {
            case TYPEOF_holor_type_depletable:
            {
                bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_shelve, bhvm_hf3_vm_op_ar0_vacate_s_csetup( NULL, i ) );
            }
            break;

            case TYPEOF_holor_type_cast:
            {
                bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_shelve, bhvm_hf3_vm_op_ar0_clear_s_csetup( NULL, i ) );
            }
            break;

            default: break;
        }
    }
    o->mcode_shelve = TYPEOF_mcode_name_shelve;
}

// ---------------------------------------------------------------------------------------------------------------------

// sets adaptive gradients to zero
void haptive_net_cell_s_vm_build_zero_adaptive_grad( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
{
    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_zero_adaptive_grad );

    const bhvm_hf3_vm_arr_holor_s* arr_holor = &vmf->arr_holor;
    for( sz_t i = 0; i < arr_holor->size; i++ )
    {
        const bhvm_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
        switch( holor->type )
        {
            case TYPEOF_holor_type_adaptive_grad:
            {
                bhvm_hf3_vm_frame_s_mcode_op_push_d( vmf, TYPEOF_mcode_name_zero_adaptive_grad, bhvm_hf3_vm_op_ar0_zro_s_csetup( NULL, i ) );
            }
            break;

            default: break;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_net_cell_s_vm_set_input( const haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
{
    bcore_arr_sz_s_clear( &vmf->input );
    for( sz_t i = 0; i < o->encs.size; i++ )
    {
        const haptive_net_node_s* node = o->encs.data[ i ];
        bhvm_hf3_vm_frame_s_input_push( vmf, node->id );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_net_cell_s_vm_set_output( const haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
{
    bcore_arr_sz_s_clear( &vmf->output );
    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        const haptive_net_node_s* node = o->excs.data[ i ];
        bhvm_hf3_vm_frame_s_output_push( vmf, node->id );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// VIRTUAL MACHINE
/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void haptive_vm_adaptive_s_arc_to_sink( const haptive_vm_adaptive_s* o, bcore_sink* sink )
{
    bcore_txt_ml_a_to_sink( o->src, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_vm_adaptive_s_minfer( haptive_vm_adaptive_s* o, const bmath_vf3_s* v_in, bmath_vf3_s* v_out )
{
    ASSERT( o->index_in  < o->vm.arr_holor.size );
    ASSERT( o->index_out < o->vm.arr_holor.size );
    bhvm_hf3_s* h_in  = &o->vm.arr_holor.data[ o->index_in  ].h;
    bhvm_hf3_s* h_out = &o->vm.arr_holor.data[ o->index_out ].h;

    ASSERT( v_in ->size == h_in ->v_size );
    ASSERT( v_out->size == h_out->v_size );

    bhvm_hf3_s_copy_v_data_from_vf3( h_in, v_in );
    bhvm_hf3_vm_frame_s_mcode_run( &o->vm, TYPEOF_mcode_name_infer );
    bhvm_hf3_s_copy_v_data_to_vf3( h_out, v_out );
}

// ---------------------------------------------------------------------------------------------------------------------

void haptive_vm_adaptive_s_bgrad_adapt( haptive_vm_adaptive_s* o, bmath_vf3_s* v_grad_in, const bmath_vf3_s* v_grad_out )
{
    ASSERT( o->index_grad_out < o->vm.arr_holor.size );

    bhvm_hf3_s* h_grad_out = &o->vm.arr_holor.data[ o->index_grad_out ].h;

    ASSERT( v_grad_out->size == h_grad_out->v_size );
    bhvm_hf3_s_copy_v_data_from_vf3( h_grad_out, v_grad_out );
    bhvm_hf3_vm_frame_s_mcode_run( &o->vm, TYPEOF_mcode_name_bp_grad );

    f3_t l2_reg_factor = ( 1.0 - o->dynamics.lambda_l2  * o->dynamics.epsilon );
    f3_t l1_reg_offset = o->dynamics.lambda_l1 * o->dynamics.epsilon;

    BFOR_EACH( i, &o->index_arr_adaptive )
    {
        bhvm_hf3_vm_holor_s* vh = bhvm_hf3_vm_frame_s_holors_get_by_index( &o->vm, o->index_arr_adaptive.data[ i ] );
        bhvm_hf3_vm_holor_s* vg = bhvm_hf3_vm_frame_s_holors_get_by_index( &o->vm, vh->idx_paired );
        bhvm_hf3_s* h = &vh->h;
        bhvm_hf3_s* g = &vg->h;
        bhvm_hf3_s_mul_scl_add( g, &o->dynamics.epsilon, h, h );
        if( l2_reg_factor < 1.0 ) bhvm_hf3_s_mul_scl( h, &l2_reg_factor, h );
        if( l1_reg_offset > 0 )
        {
            for( sz_t j = 0; j < h->v_size; j++ )
            {
                h->v_data[ j ] += ( h->v_data[ j ] > 0 ) ? -l1_reg_offset : l1_reg_offset;
            }
        }
        bhvm_hf3_s_zro( g );
    }
}
// ---------------------------------------------------------------------------------------------------------------------

haptive_op* haptive_vm_builder_s_build_input_op_create( vd_t vd_o, sz_t in_idx, tp_t in_name )
{
    const haptive_vm_builder_s* o = vd_o;
    haptive_op_ar0_input_s* input = haptive_op_ar0_input_s_create();
    input->h = bhvm_hf3_s_create();

    switch( in_idx )
    {
        case 0:
        {
            bhvm_hf3_s_set_scalar_f3( input->h, o->out_size );
        }
        break;

        case 1:
        {
            bhvm_hf3_s_set_d_data_na( input->h, 1, o->in_size );
        }
        break;

        default:
        {
            ERR_fa( "Invalid index '#<sz_t>',", in_idx );
        }
        break;
    }

    return ( haptive_op* )input;
}

// ---------------------------------------------------------------------------------------------------------------------

// Pulls all relevant names into frame's name map
void haptive_bhvm_hf3_vm_frame_s_pull_names( bhvm_hf3_vm_frame_s* o )
{
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_infer ) );
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_bp_grad ) );
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_setup ) );
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_shelve ) );
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_cast ) );
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_cast_reverse ) );
    bhvm_hf3_vm_frame_s_entypeof( o, nameof( TYPEOF_mcode_name_zero_adaptive_grad ) );
    BFOR_EACH( i, &o->arr_holor )
    {
        tp_t tp_name = o->arr_holor.data[ i ].name;
        if( tp_name )
        {
            sc_t sc_name = haptive_nameof( tp_name );
            if( sc_name ) bhvm_hf3_vm_frame_s_entypeof( o, sc_name );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* haptive_vm_builder_s_build( const haptive_vm_builder_s* o )
{
    haptive_vm_adaptive_s* adaptive = haptive_vm_adaptive_s_create();
    st_s_copy( &adaptive->sig, &o->sig );
    bcore_inst_a_replicate( ( bcore_inst** )&adaptive->src, ( const bcore_inst* )o->src );

    adaptive->in_size  = o->in_size;
    adaptive->out_size = o->out_size;
    badapt_dynamics_std_s_copy( &adaptive->dynamics, &o->dynamics );

    BLM_INIT();

    bcore_source* source = NULL;
    if( !o->src ) ERR_fa( "Source missing." );
    switch( *(aware_t*)o->src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = BLM_A_PUSH( bcore_file_open_source_path( ( const bcore_file_path_s* )o->src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = BLM_A_PUSH( bcore_source_string_s_create_from_string( ( const st_s* )o->src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->src ) );
        }
        break;
    }

    // semantic cell
    haptive_sem_cell_s* sem_frame = BLM_A_PUSH( haptive_sem_cell_s_create_frame() );
    haptive_sem_cell_s_parse_signature( sem_frame, BLM_A_PUSH( bcore_source_string_s_create_sc( o->sig.sc ) ) );
    bcore_source_point_s_set( &sem_frame->source_point, source );
    haptive_sem_cell_s_parse_body( sem_frame, source );

    // network cell
    haptive_net_cell_s* net_frame = BLM_A_PUSH( haptive_net_cell_s_create() );
    haptive_net_cell_s_from_sem_cell( net_frame, sem_frame, haptive_vm_builder_s_build_input_op_create, ( vd_t )o, NULL );

    bhvm_hf3_vm_frame_s* vmf = &adaptive->vm;

    haptive_cell_s_vm_build_infer(   net_frame, vmf );
    haptive_cell_s_vm_build_bp_grad( net_frame, vmf );
    haptive_vm_build_setup(  vmf, o->rseed );
    haptive_vm_build_shelve( vmf );
    haptive_net_cell_s_vm_set_input(  net_frame, vmf );
    haptive_net_cell_s_vm_set_output( net_frame, vmf );

    haptive_bhvm_hf3_vm_frame_s_pull_names( vmf );

    ASSERT( vmf->input.size  == 2 );
    ASSERT( vmf->output.size == 1 );

    adaptive->index_in       = vmf->input.data [ 1 ];
    adaptive->index_out      = vmf->output.data[ 0 ];
    adaptive->index_grad_out = vmf->arr_holor.data[ adaptive->index_out ].idx_paired;

    // adaptive holors
    BFOR_EACH( i, &vmf->arr_holor )
    {
        if( vmf->arr_holor.data[ i ].type == TYPEOF_holor_type_adaptive )
        {
            bcore_arr_sz_s_push( &adaptive->index_arr_adaptive, i );
        }
    }

    /// test input and output holors
    {
        ASSERT( adaptive->index_in  >= 0 );
        ASSERT( adaptive->index_out >= 0 );
        ASSERT( adaptive->index_in  < vmf->arr_holor.size );
        ASSERT( adaptive->index_out < vmf->arr_holor.size );

        bhvm_hf3_s* h_in  = &vmf->arr_holor.data[ adaptive->index_in  ].h;
        bhvm_hf3_s* h_out = &vmf->arr_holor.data[ adaptive->index_out ].h;

        if( h_in->d_size != 1 || h_in->d_data[ 0 ] != adaptive->in_size )
        {
            st_s* s = BLM_CREATE( st_s );
            bhvm_hf3_s_to_sink( h_in, ( bcore_sink* )s );
            ERR_fa( "Virtual machine has input holor '#<sc_t>', which is of incorrect size.", s->sc );
        }

        if( h_out->d_size != 1 || h_out->d_data[ 0 ] != adaptive->out_size )
        {
            st_s* s = BLM_CREATE( st_s );
            bhvm_hf3_s_to_sink( h_out, ( bcore_sink* )s );
            ERR_fa( "Virtual machine has output holor '#<sc_t>', which is of incorrect size.", s->sc );
        }
    }

    bhvm_hf3_vm_frame_s_check_integrity( vmf );

    /// run setup
    bhvm_hf3_vm_frame_s_mcode_run( vmf, TYPEOF_mcode_name_setup );

    bhvm_hf3_vm_frame_s_check_integrity( vmf );

    BLM_RETURNV( badapt_adaptive*, ( badapt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_haptive

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t haptive_graph_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "haptive_graph" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
#ifdef TYPEOF_haptive
            haptive_context_down();
#endif // TYPEOF_bhcl
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "haptive_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


