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


// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// stack

/*
 * Index values are in reverse array order from the stack-end;
 * idx == 1 means last array entry or top of stack.
 */

// ---------------------------------------------------------------------------------------------------------------------

void stack_push( bcore_arr_vd_s* o, vd_t value )
{
    bcore_arr_vd_s_push( o, value );
}

// ---------------------------------------------------------------------------------------------------------------------

vd_t stack_pop( bcore_arr_vd_s* o )
{
    return bcore_arr_vd_s_pop( o );
}

// ---------------------------------------------------------------------------------------------------------------------

vd_t stack_pop_of_type( bcore_arr_vd_s* o, tp_t type, bcore_source* source )
{
    vd_t v = stack_pop( o );
    if( *( aware_t* )v == type ) return v;
    bcore_source_a_parse_err_fa( source, "Type error: '#<sc_t>' present but '#<sc_t>' expected.", ifnameof( *( aware_t* )v ), ifnameof( type ) );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

vd_t stack_pop_of_value( bcore_arr_vd_s* o, vd_t value, bcore_source* source )
{
    vd_t v = stack_pop( o );
    if( v == value ) return v;
    bcore_source_a_parse_err_fa( source, "Internal error: Stack holds invalid value." );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t stack_of_type( bcore_arr_vd_s* o, sz_t idx, tp_t type )
{
    if( idx <= 0 || idx > o->size ) return false;
    return *(aware_t*)o->data[ o->size - idx ] == type;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t stack_of_value( bcore_arr_vd_s* o, sz_t idx, vd_t value )
{
    if( idx <= 0 || idx > o->size ) return false;
    return o->data[ o->size - idx ] == value;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_link_s* stack_pop_link( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_opal_sem_link_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_cell_s* stack_pop_cell( bcore_arr_vd_s* o, bcore_source* source )
{
    return stack_pop_of_type( o, TYPEOF_opal_sem_cell_s, source );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_sem_link_s* stack_pop_link_or_exit( bcore_arr_vd_s* o, bcore_source* source )
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

/**********************************************************************************************************************/
/// Cell

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// builder

// ---------------------------------------------------------------------------------------------------------------------

er_t opal_sem_builder_s_build_from_source( opal_sem_builder_s* o, opal_sem_cell_s* cell, bcore_source* source )
{
    BLM_INIT();

    opal_sem_context_s_attach( &o->context, opal_sem_context_s_create() );

    /** Triple-nested semantic cell-frame:
     *  Level 0: context level: contains all global operators
     *  Level 1: frame level  : holds operators defined outside the root cell
     *  Level 2: root level   : represents the root cell defined in source
     */

    opal_sem_cell_s_attach( &o->cell_context, opal_sem_context_s_create_cell( o->context ) );
    opal_sem_cell_s_attach( &o->cell_frame,   opal_sem_context_s_create_cell( o->context ) );
    opal_sem_context_s_setup_cell( o->context, cell );
    opal_sem_context_s_setup( o->context, o->cell_context );

    opal_sem_cell_s_set_name_invisible( o->cell_context, opal_sem_context_s_entypeof( o->context, "$CX" ) );
    opal_sem_cell_s_set_name_invisible( o->cell_frame,   opal_sem_context_s_entypeof( o->context, "$CF" ) );

    o->cell_frame->parent = o->cell_context;
       cell      ->parent = o->cell_frame;

    bcore_source_point_s_set( &o->cell_frame->source_point, source );
    bcore_source_point_s_set( &cell->source_point, source );

    bcore_source_a_parse_fa( source, " #-?'cell'" ); // leading 'cell' keyword is optional
    opal_sem_cell_s_parse( cell, source );

    BLM_RETURNV( er_t, 0 );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// ctr

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

er_t opal_sem_tree_node_s_enter
(
    opal_sem_tree_node_s* o,
    opal_sem_cell_s* cell,
    opal_sem_tree_node_s** node_out
)
{
    opal_sem_tree_node_s* node = NULL;
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( o->data[ i ]->cell == cell )
        {
            node = o->data[ i ];
        }
    }
    if( !node )
    {
        node = opal_sem_tree_node_s_push_d( o, opal_sem_tree_node_s_create() );
        node->cell = cell;
        node->parent = o;
    }
    *node_out = node;
    return 0;
}

// ---------------------------------------------------------------------------------------------------------------------

er_t opal_sem_tree_node_s_exit
(
    opal_sem_tree_node_s* o,
    opal_sem_cell_s* cell,
    bl_t test_for_wrapper,
    opal_sem_tree_node_s** node_out
)
{
    opal_sem_tree_node_s* node = NULL;
    node = o;

    /** Descend tree until node->cell == cell.
      * This part covers specific (rare) situations in which a link exits a cell without passing through its membrane
      * It is unclear if this handling is sensitive. Probably all relevant cases are covered using test_for_wrapper
      * scheme.
      */
    while( node && node->cell != cell )
    {
        //bcore_msg_fa( "descending...\n" );
        node = node->parent;
    }

    if( node && node->cell == cell )
    {
        node = node->parent;

        if( test_for_wrapper && node && opal_sem_cell_s_is_wrapper( node->cell ) )
        {
            while( node && opal_sem_cell_s_is_wrapper( node->cell ) ) node = node->parent;
        }

        *node_out = node;
        return 0;
    }
    else
    {
        return TYPEOF_general_error; // exiting from untraced cell
    }
}

// ---------------------------------------------------------------------------------------------------------------------

er_t opal_sem_tree_s_enter
(
    opal_sem_tree_s* o,
    opal_sem_cell_s* cell,
    opal_sem_tree_node_s* node_in,
    opal_sem_tree_node_s** node_out
)
{
    opal_sem_tree_node_s* node = NULL;
    if( !o->root )
    {
        o->root = opal_sem_tree_node_s_create();
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
        er_t ret = opal_sem_tree_node_s_enter( node_in, cell, &node );
        if( ret ) return ret;
        if( node->id < 0 ) node->id = o->id_base++;
        *node_out = node;
        return 0;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

er_t opal_sem_tree_s_exit
(
    opal_sem_tree_s* o,
    opal_sem_cell_s* cell,
    bl_t test_for_wrapper,
    opal_sem_tree_node_s* node_in,
    opal_sem_tree_node_s** node_out
)
{
    return opal_sem_tree_node_s_exit( node_in, cell, test_for_wrapper, node_out );
}

// ---------------------------------------------------------------------------------------------------------------------

bcore_source_point_s* opal_sem_tree_node_s_get_nearest_source_point( opal_sem_tree_node_s* o )
{
    if( !o ) return NULL;
    if( !o->cell ) return NULL;
    if( o->cell->source_point.source ) return &o->cell->source_point;
    return opal_sem_tree_node_s_get_nearest_source_point( o->parent );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
