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

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// context

static bhgp_context_s* context_g = NULL;

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_context_setup()
{
    if( context_g ) return;
    context_g = bhgp_context_s_create();

    BCORE_LIFE_INIT();
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

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_context_down()
{
    if( context_g ) bhgp_context_s_detach( &context_g );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t bhgp_ifnameof( tp_t name )
{
    if( !context_g ) bhgp_context_setup();
    sc_t sc = bcore_hmap_name_s_get_sc( &context_g->hmap_name, name );
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

/**********************************************************************************************************************/
/// bhgp_op_ar2

// ---------------------------------------------------------------------------------------------------------------------

bmath_hf3_vm_op* bhgp_op_ar2_mul_s_create_vm_op( const bhgp_op_ar2_mul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r )
{
    if( a->d_size == 0 )
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_scl_mul_s_create();
    }
    else if( b->d_size == 0 )
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_mul_scl_s_create();
    }
    else
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_hmul_s_create();
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

// Traces link to next cell (of which the link is part of the membrane); returns NULL in case trace ends in open link
bhgp_sem_link_s* bhgp_sem_link_s_trace_to_cell( bhgp_sem_link_s* o )
{
    if( !o || o->cell ) return o;
    return bhgp_sem_link_s_trace_to_cell( o->up );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// sem_cell

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_set_channels( bhgp_sem_cell_s* o, sz_t excs, sz_t encs )
{
    bhgp_sem_links_s_set_size( &o->excs, excs );
    bhgp_sem_links_s_set_size( &o->encs, encs );
    for( sz_t i = 0; i < excs; i++ ) o->excs.data[ i ] = bhgp_sem_link_s_create_setup( 0, NULL, NULL, o, true );
    for( sz_t i = 0; i < encs; i++ ) o->encs.data[ i ] = bhgp_sem_link_s_create_setup( 0, NULL, NULL, o, false );
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_wrap_cell( bhgp_sem_cell_s* o, bhgp_sem_cell_s* src )
{
    ASSERT( !o->body );
    ASSERT( !o->op   );
    bhgp_sem_links_s_set_size( &o->encs, bhgp_sem_cell_s_get_arity( src ) );
    bhgp_sem_links_s_set_size( &o->excs, src->excs.size );

    sz_t k = 0;
    for( sz_t i = 0; i < src->encs.size; i++ )
    {
        if( !src->encs.data[ i ]->up )
        {
            o->encs.data[ k++ ] = bhgp_sem_link_s_create_setup( 0, NULL, src->encs.data[ i ], o, false );
        }
    }

    assert( k == o->encs.size );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        o->excs.data[ i ] = bhgp_sem_link_s_create_setup( 0, src->excs.data[ i ], NULL, o, true );
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

bhgp_sem_cell_s* bhgp_sem_cell_s_push_cell_op_d( bhgp_sem_cell_s* o, bhgp_op* op )
{
    bhgp_sem_cell_s* cell = ( bhgp_sem_cell_s* )bhgp_sem_cell_s_push_cell( o );
    bhgp_sem_cell_s_set_channels( cell, 1, bhgp_op_a_get_arity( op ) );
    sc_t symbol = bhgp_op_a_get_symbol( op );
    if( symbol ) cell->name = bhgp_entypeof( symbol );
    cell->op = op;
    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

/// v can be NULL pushing an undetermined scalar
bhgp_sem_cell_s* bhgp_sem_cell_s_push_cell_scalar( bhgp_sem_cell_s* o, f3_t* v )
{
    bhgp_op_ar0_holor_s* holor = bhgp_op_ar0_holor_s_create();
    bmath_hf3_s_set_scalar_pf3( &holor->h, v );
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

void bhgp_sem_cell_s_parse_excs( bhgp_sem_cell_s* o, bcore_source* source )
{
    ASSERT( o->excs.size == 0 );
    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );
        bhgp_sem_link_s* link = bhgp_sem_link_s_create_setup( bhgp_parse_name( source ), NULL, NULL, o, true );
        bhgp_sem_links_s_push_d( &o->excs, link );
        first = false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_parse_encs( bhgp_sem_cell_s* o, bhgp_sem_cell_s* parent, bcore_source* source )
{
    ASSERT( o->encs.size == 0 );

    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );
        bhgp_sem_link_s* link = bhgp_sem_link_s_create_setup( bhgp_parse_name( source ), NULL, NULL, o, false );
        if( bcore_source_a_parse_bl_fa( source, " #?'->'" ) )
        {
            link->up = bhgp_sem_cell_s_evaluate_link( parent, source );
        }
        bhgp_sem_links_s_push_d( &o->encs, link );
        first = false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bhgp_sem_cell_s* bhgp_sem_cell_s_create_parse( bcore_source* source )
{
    if( !context_g ) bhgp_context_setup();
    bhgp_sem_cell_s* o = bhgp_sem_cell_s_create();
    o->parent = &context_g->cell;
    bhgp_sem_cell_s_parse( o, source );
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_parse( bhgp_sem_cell_s* o, bcore_source* source )
{
    // <name >
    tp_t tp_cell_name = bhgp_parse_name( source );
    bhgp_sem_cell_s* frame = o->parent;
    if( frame ) bhgp_sem_cell_s_assert_identifier_not_yet_defined( frame, tp_cell_name, source );
    o->name = tp_cell_name;

    bcore_source_point_s_set( &o->source_point, source );

    //  ( <args_out> ) => ( <args_in> ) { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        bhgp_sem_cell_s_parse_excs( o, source );
        bcore_source_a_parse_fa( source, " => " );
        bhgp_sem_cell_s_parse_encs( o, frame, source );
        bcore_source_a_parse_fa( source, " {" );
        bhgp_sem_cell_s_parse_body( o, source );
        bcore_source_a_parse_fa( source, " }" );
    }

    // = expression yielding a cell
    else
    {
        bcore_source_a_parse_fa( source, " = " );
        bhgp_sem_cell_s* cell = bhgp_sem_cell_s_evaluate_cell( frame, source );
        bhgp_sem_cell_s_wrap_cell( o, cell );
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
        else if( bcore_source_a_parse_bl_fa( source, " #?'link'" ) )
        {
            bhgp_sem_link_s* link = bhgp_sem_cell_s_push_link( o );
            tp_t name = bhgp_parse_name( source );
            bhgp_sem_cell_s_assert_identifier_not_yet_defined( o, name, source );
            link->name = name;
            bcore_source_a_parse_fa( source, " ->" );
            link->up = bhgp_sem_cell_s_evaluate_link( o, source );
        }

        //TODO: adaptive and buffer

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
                bcore_source_a_parse_fa( source, " ->" );
                link->up = bhgp_sem_cell_s_evaluate_link( o, source );
            }

            //TODO: adaptive and buffer

            else
            {
                bcore_source_a_parse_err_fa( source, "Unknown identifier '#<sc_t>'.", bhgp_ifnameof( tp_name ) );
            }

        }
        bcore_source_a_parse_fa( source, " ; " );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_evaluate_set_encs( bhgp_sem_cell_s* o, bhgp_sem_cell_s* parent, bcore_source* source )
{
    BCORE_LIFE_INIT();
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
            if( bcore_source_a_parse_bl_fa( source, " #?'->'" ) )
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

    for( sz_t i = 0; i < c2->encs.size; i++ )   c2->encs.data[ i ]->up = cell->encs.data[ i ];
    for( sz_t i = 0; i < c1->encs.size; i++ )   c1->encs.data[ i ]->up =   c2->excs.data[ i ];
    for( sz_t i = 0; i < c1->excs.size; i++ ) cell->excs.data[ i ]->up =   c1->excs.data[ i ];

    return cell;
}

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_sem_cell_s_evaluate_stack( bhgp_sem_cell_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( st_s, name );

    BCORE_LIFE_CREATE( bhgp_sem_stack_flag_s, flag_bin_op    );
    BCORE_LIFE_CREATE( bhgp_sem_stack_flag_s, flag_cell_cat  );
    BCORE_LIFE_CREATE( bhgp_sem_stack_flag_s, flag_inc_order );

    tp_t op2_symbol = 0;
    bmath_hf3_s* literal = NULL;

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

            /// disallowed identifiers inside evaluation
            if( tp_name == TYPEOF_cell || tp_name == TYPEOF_link  || tp_name == TYPEOF_holor )
            {
                bcore_source_a_parse_err_fa( source, "Unexpected keyword '#<sc_t>'. Forgot ';' on previous statement?", name->sc );
            }

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
                    if( bhgp_sem_cell_s_get_arity( cell ) > 0 )
                    {
                        cell = bhgp_sem_cell_s_push_wrap_cell( o, cell );
                        bcore_source_point_s_set( &cell->source_point, source );
                    }
                    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) ) bhgp_sem_cell_s_evaluate_set_encs( cell, o, source );
                    stack_push( stack, cell );
                }
                break;

                case TYPEOF_bhgp_sem_link_s: stack_push( stack, item ); break;
                default: bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' represents invalid object '#<sc_t>'.", name->sc, ifnameof( tp_item ) );
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

        // block
        else if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
        {
            stack_push( stack, bhgp_sem_cell_s_evaluate_sem( o, source ) );
            bcore_source_a_parse_fa( source, " )" );
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
        else if( bcore_source_a_parse_bl_fa( source, " #?'<'" ) )
        {
            bcore_source_a_parse_fa( source, "#until'>'>", name );
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

            if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_cell_s ) )
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

        // terminator
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

            if( *(aware_t*)arg1 == TYPEOF_bhgp_sem_cell_s )
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
                bhgp_sem_cell_s* cell2 = stack_pop_of_type( stack, TYPEOF_bhgp_sem_cell_s, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                bhgp_sem_cell_s* cell1 = stack_pop_of_type( stack, TYPEOF_bhgp_sem_cell_s, source );
                stack_push( stack, bhgp_sem_cell_s_cat_cell( o, cell1, cell2, source ) );
            }
            else if( stack_of_type( stack, 1, TYPEOF_bhgp_sem_link_s ) ) // cell : link
            {
                bhgp_sem_link_s* link = stack_pop_of_type( stack, TYPEOF_bhgp_sem_link_s, source );
                stack_pop_of_value( stack, flag_cell_cat, source );
                bhgp_sem_cell_s* cell = stack_pop_of_type( stack, TYPEOF_bhgp_sem_cell_s, source );
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
            bhgp_sem_link_s* link2 = stack_pop_of_type( stack, TYPEOF_bhgp_sem_link_s, source );
            stack_pop_of_value( stack, flag_inc_order, source );
            bhgp_sem_link_s* link1 = stack_pop_of_type( stack, TYPEOF_bhgp_sem_link_s, source );
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
        // <left address> <flag> <bin-operator> <output> <left address>
        if( stack->size >= 5 && stack_of_value( stack, 4, flag_bin_op ) )
        {
            bhgp_sem_link_s* link2 = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_link_s, source );
            bhgp_sem_link_s* out   = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_link_s, source );
            bhgp_sem_cell_s* cell  = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_cell_s, source );
                                     stack_pop_of_value( stack, flag_bin_op           , source );
            bhgp_sem_link_s* link1 = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_link_s, source );

            if( stack->size >= 4 && stack_of_value( stack, 3, flag_bin_op ) ) // merge with prior operation considering priority
            {
                bhgp_sem_link_s* prior_out   = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_link_s, source );
                bhgp_sem_cell_s* prior_cell  = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_cell_s, source );
                                               stack_pop_of_value( stack, flag_bin_op           , source );
                bhgp_sem_link_s* prior_link1 = stack_pop_of_type(  stack, TYPEOF_bhgp_sem_link_s, source );

                if( bhgp_sem_cell_s_get_priority( prior_cell ) >= bhgp_sem_cell_s_get_priority( cell ) )
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
    BCORE_LIFE_INIT();
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
    BCORE_LIFE_INIT();
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
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    bhgp_sem_cell_s* ret = bhgp_sem_cell_s_evaluate_cell_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// net_frame

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_net_frame_s_trace( bhgp_net_frame_s* o, bhgp_sem_link_s* link )
{
    tp_t name = link->name;
    link = bhgp_sem_link_s_trace_to_cell( link );
    if( !link ) ERR_fa( "Backtracing '#<sc_t>':\nTrace ends in open link.", bhgp_ifnameof( name ) );
    bhgp_sem_cell_s* cell = link->cell;

    if( link->exit )
    {
        // since we backtrace, a cell is entered through an 'exit' link
        bhgp_ctr_tree_s_cell_enter( &o->tree, cell );
    }
    else
    {
        if( !bhgp_ctr_tree_s_cell_exit( &o->tree, cell ) )
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting from untraced cell.", bhgp_ifnameof( name ) );
        }

        if( link->up )
        {
            bhgp_net_frame_s_trace( o, link->up );
        }
        else
        {

        }
    }

}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void bhgp_test( void )
{
    BCORE_LIFE_INIT();

    bcore_source* source  = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/bhgp_test.hgp" ) );
    bhgp_sem_cell_s* cell = BCORE_LIFE_A_PUSH( bhgp_sem_cell_s_create_parse( source ) );
    bcore_txt_ml_a_to_stdout( cell );

    BCORE_LIFE_DOWN();
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


