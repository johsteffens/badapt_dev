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

#include "lion_net.h"

/**********************************************************************************************************************/
/// Prototypes

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// ctr

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
s2_t lion_ctr_node_s_node_process( lion_ctr_node_s* o, lion_sem_cell_s* cell, bl_t enter, lion_ctr_node_s** node_out )
{
    lion_ctr_node_s* node = NULL;
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
            node = lion_ctr_node_s_push_d( o, lion_ctr_node_s_create() );
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

s2_t lion_ctr_tree_s_tree_process( lion_ctr_tree_s* o, lion_sem_cell_s* cell, bl_t enter, lion_ctr_node_s* node_in, lion_ctr_node_s** node_out )
{
    if( enter )
    {
        lion_ctr_node_s* node = NULL;
        if( !o->root )
        {
            o->root = lion_ctr_node_s_create();
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
            s2_t ret = lion_ctr_node_s_node_process( node_in, cell, enter, &node );
            if( ret ) return ret;
            if( node->id < 0 ) node->id = o->id_base++;
            *node_out = node;
            return 0;
        }
    }
    else
    {
        return lion_ctr_node_s_node_process( node_in, cell, enter, node_out );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bcore_source_point_s* lion_ctr_node_s_get_nearest_source_point( lion_ctr_node_s* o )
{
    if( !o ) return NULL;
    if( !o->cell ) return NULL;
    if( o->cell->source_point.source ) return &o->cell->source_point;
    return lion_ctr_node_s_get_nearest_source_point( o->parent );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// net_node

/// recursive trace; exits when the enter membrane of the root cell is reached
void lion_net_node_s_trace_to_sink( lion_net_node_s* o, sz_t indent, bcore_sink* sink )
{
    if( !o )
    {
        bcore_sink_a_push_fa( sink, "(NULL)" );
        return;
    }

    bl_t recurring = o->flag;

    if( recurring ) bcore_sink_a_push_fa( sink, "(recurring)" );

    o->flag = true;

    if( o->result )
    {
        lion_holor_s_brief_to_sink( o->result->h, sink );
    }

    sc_t symbol = "";
    if( o->nop )
    {
        sc_t symbol = lion_nop_a_symbol( o->nop );
        if( !symbol ) symbol = ifnameof( o->nop->_ );
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
            lion_net_node_s* node = o->upls.data[ i ]->node;
            lion_net_node_s_trace_to_sink( node, indent + incr, sink );
        }
    }

    o->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_node_s_err_fa( lion_net_node_s* o, sc_t format, ... )
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
static void net_node_s_nop_solve( lion_net_node_s* o, lion_holor_s** arg_h )
{
    lion_nop_solve_result_s_attach( &o->result, lion_nop_solve_result_s_create() );

    if( !lion_nop_a_solve( o->nop, arg_h, o->result ) )
    {
        sz_t arity = lion_nop_a_arity( o->nop );
        sc_t name = lion_nop_a_symbol( o->nop );
        if( !name ) name = ifnameof( o->nop->_ );
        st_s* msg = st_s_create();
        st_s_push_fa( msg, "Operator '#<sc_t>' failed:", name );
        if( o->result->msg ) st_s_push_fa( msg, " #<sc_t>", o->result->msg->sc );
        st_s_push_fa( msg, "\n" );
        for( sz_t i = 0; i < arity; i++ )
        {
            st_s_push_fa( msg, "arg[#<sz_t>]: ", i );
            if( arg_h[ i ] )
            {
                lion_holor_s_brief_to_sink( arg_h[ i ], (bcore_sink*)msg );
            }
            else
            {
                st_s_push_fa( msg, "null" );
            }
            st_s_push_fa( msg, "\n" );
        }
        lion_net_node_s_err_fa( o, "#<sc_t>", msg->sc );
        st_s_discard( msg );
    }

    if( !o->result->h )
    {
        lion_nop_solve_result_s_detach( &o->result );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**
 *  Function 'solve' executes operator->solve to compute a holor.
 *  If a holor can be computed (vacant or determined), the solve-route is considered finished
 *  and will not be processed again. A detached result (o->h == NULL) causes a route to be reentered.
 *  If operator->solve returns 1, the operation is considered settled, in which case all uplinks
 *  are removed and the operator is switched to a final arity0 version via lion_op_a_settle.
 *  After settling, the graph can be run through an optimizer minimizing its structure.
 */
void lion_net_node_s_solve( lion_net_node_s* o )
{
    if( o->flag ) return; // cyclic link

    o->flag = true;

    if( o->result ) return;

    if( !o->nop ) lion_net_node_s_err_fa( o, "Node has no operator." );

    sz_t arity = lion_nop_a_arity( o->nop );
    if( arity != o->upls.size )
    {
        lion_net_node_s_err_fa( o, "Operator arity #<sz_t> differs from node arity #<sz_t>", arity, o->upls.size );
    }

    #define lion_MAX_ARITY 4 /* increase this number when assertion below fails */
    ASSERT( arity <= lion_MAX_ARITY );
    lion_holor_s* arg_h[ lion_MAX_ARITY ] = { NULL };

    bl_t solve_each_channel = lion_nop_a_requires_solve_for_each_channel( o->nop );

    for( sz_t i = 0; i < arity; i++ )
    {
        lion_net_node_s* arg_n = o->upls.data[ i ]->node;
        if( arg_n )
        {
            lion_net_node_s_solve( arg_n );
            arg_h[ i ] = arg_n->result->h;
        }
        if( solve_each_channel ) net_node_s_nop_solve( o, arg_h );
    }

    if( !solve_each_channel ) net_node_s_nop_solve( o, arg_h );

    if( o->result->settled )
    {
        lion_nop_a_settle( o->nop, o->result, &o->nop, &o->result );
        lion_net_links_s_clear( &o->upls );
        if( !o->result->reducible )
        {
            if( o->result->h ) bhvm_value_s_clear( &o->result->h->h.v );
        }
    }

    o->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

/// Outputs the graph structure in text form to sink
void lion_net_node_s_graph_to_sink( lion_net_node_s* o, bcore_sink* sink )
{
    lion_net_node_s_trace_to_sink( o, 0, sink );
    bcore_sink_a_push_fa( sink, "\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively sets downlinks for all non-flagged uplinks.
 *  Assumes initial state was normal.
 */
void lion_net_node_s_set_downlinks( lion_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( i, &o->upls )
    {
        lion_net_node_s* node = o->upls.data[ i ]->node;
        lion_net_links_s_push( &node->dnls )->node = o;
        lion_net_node_s_set_downlinks( node );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively skips identities.
 *  Assumes initial state was normal and downlinks not set
 */
void lion_net_node_s_skip_identities( lion_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( i, &o->upls )
    {
        lion_net_node_s* node = o->upls.data[ i ]->node;
        while( node && node->nop && node->nop->_ == TYPEOF_lion_nop_ar1_identity_s ) node = node->upls.data[ i ]->node;
        ASSERT( node );
        o->upls.data[ i ]->node = node;
        lion_net_node_s_skip_identities( node );
    }
    o->flag = false;
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively sets flags for all nodes reachable via uplink.
 *  Assumes initial state was normal.
 */
void lion_net_node_s_set_flags( lion_net_node_s* o )
{
    if( o->flag ) return;
    o->flag = true;
    BFOR_EACH( i, &o->upls ) lion_net_node_s_set_flags( o->upls.data[ i ]->node );
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
void lion_net_cell_s_normalize( lion_net_cell_s* o )
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
    lion_net_nodes_s_set_size( &o->body, 0 );
    for( sz_t i = 0; i < arr->size; i++ )
    {
        lion_net_node_s* node = lion_net_nodes_s_push_d( &o->body, arr->data[ i ] );
        assert( node == arr->data[ i ] );
        node->id = i;
        node->flag = false;
    }

    bcore_arr_vd_s_discard( arr );
}

// ---------------------------------------------------------------------------------------------------------------------

/// Checks consistency of a normalized cell
bl_t lion_net_cell_s_is_consistent( const lion_net_cell_s* o )
{
    BFOR_EACH( i, &o->body )
    {
        const lion_net_node_s* node = o->body.data[ i ];
        if( node->flag ) return false;
        if( node->id != i ) return false;
        BFOR_EACH( i, &node->upls )
        {
            const lion_net_node_s* node2 = node->upls.data[ i ]->node;
            if( node2->id < 0 ) return false;
            if( node2->id >= o->body.size ) return false;
            if( node2 != o->body.data[ node2->id ] ) return false;
        }

        BFOR_EACH( i, &node->dnls )
        {
            const lion_net_node_s* node2 = node->dnls.data[ i ]->node;
            if( node2->id < 0 ) return false;
            if( node2->id >= o->body.size ) return false;
            if( node2 != o->body.data[ node2->id ] ) return false;
        }
        if( node->result && !bhvm_holor_s_is_consistent( &node->result->h->h ) ) return false;
    }

    BFOR_EACH( i, &o->encs )
    {
        const lion_net_node_s* node2 = o->encs.data[ i ];
        if( node2->id < 0 ) return false;
        if( node2->id >= o->body.size ) return false;
        if( node2 != o->body.data[ node2->id ] ) return false;
        if( node2->result && !bhvm_holor_s_is_consistent( &node2->result->h->h ) ) return false;
    }

    BFOR_EACH( i, &o->excs )
    {
        const lion_net_node_s* node2 = o->excs.data[ i ];
        if( node2->id < 0 ) return false;
        if( node2->id >= o->body.size ) return false;
        if( node2 != o->body.data[ node2->id ] ) return false;
        if( node2->result && !bhvm_holor_s_is_consistent( &node2->result->h->h ) ) return false;
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_cell_s_copy_x( lion_net_cell_s* o )
{
    BFOR_EACH( i, &o->body )
    {
        const lion_net_node_s* node = o->body.data[ i ];
        ASSERT( node->id == i );
        BFOR_EACH( i, &node->upls )
        {
            const lion_net_node_s* node2 = node->upls.data[ i ]->node;
            ASSERT( node2->id >= 0 );
            ASSERT( node2->id < o->body.size );
            node->upls.data[ i ]->node = o->body.data[ node2->id ];
        }
        BFOR_EACH( i, &node->dnls )
        {
            const lion_net_node_s* node2 = node->dnls.data[ i ]->node;
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
        lion_net_node_s_detach( &o->encs.data[ i ] );
        o->encs.data[ i ] = bcore_fork( o->body.data[ id ] );
    }

    BFOR_EACH( i, &o->excs )
    {
        sz_t id = o->excs.data[ i ]->id;
        ASSERT( id >= 0 );
        ASSERT( id < o->body.size );
        lion_net_node_s_detach( &o->excs.data[ i ] );
        o->excs.data[ i ] = bcore_fork( o->body.data[ id ] );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_cell_s_set_downlinks( lion_net_cell_s* o )
{
    lion_net_cell_s_clear_flags( o );
    lion_net_cell_s_clear_downlinks( o );
    BFOR_EACH( i, &o->excs ) lion_net_node_s_set_downlinks( o->excs.data[ i ] );
    lion_net_cell_s_clear_flags( o );
    assert( lion_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes not reachable via uplink from exit channels
 *  Creates an warning in case an entry channel is unreachable.
 */
void lion_net_cell_s_remove_unreachable_nodes( lion_net_cell_s* o )
{
    lion_net_cell_s_clear_flags( o );
    BFOR_EACH( i, &o->excs ) lion_net_node_s_set_flags( o->excs.data[ i ] );
    BFOR_EACH( i, &o->encs )
    {
        lion_net_node_s* node = o->encs.data[ i ];
        if( !node->flag && ( !( node->result && node->result->h->h.v.size > 0 ) ) )
        {
            bcore_source_point_s_parse_msg_to_sink_fa( node->source_point, BCORE_STDERR, "Warning: Entry channel [#<sz_t>] '#<sc_t>' has no effect.", i, lion_ifnameof( node->name ) );
        }
        node->flag = true;
    }

    BFOR_EACH( i, &o->body ) if( !o->body.data[ i ]->flag ) lion_net_node_s_detach( &o->body.data[ i ] );
    lion_net_cell_s_normalize( o );

    ASSERT( lion_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes containing an identity operator and relinks remaining nodes accordingly
 *  Clears all downlinks;
 */
void lion_net_cell_s_remove_identities( lion_net_cell_s* o )
{
    lion_net_cell_s_clear_downlinks( o );
    lion_net_cell_s_clear_flags( o );
    BFOR_EACH( i, &o->excs ) lion_net_node_s_skip_identities( o->excs.data[ i ] );
    lion_net_cell_s_clear_flags( o );
    lion_net_cell_s_remove_unreachable_nodes( o );
    assert( lion_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively building a network cell from a semantic cell using membrane-technique.
 *  Exits when the enter membrane of the root cell is reached.
 *  This function does not set downlinks.
 */
static void net_cell_s_from_sem_recursive
(
    lion_net_cell_s* o,
    lion_sem_link_s* link,
    lion_ctr_tree_s* ctr_tree,
    lion_ctr_node_s* ctr_node,
    lion_net_node_s* net_node_dn,
    sz_t             depth,
    bcore_sink*      log  // optional
)
{
    depth++;
    tp_t name = link->name;
    if( log ) bcore_sink_a_push_fa( log, "Tracing link '#<sc_t>' at depth #<sz_t>\n", lion_ifnameof( name ), depth );
    link = lion_sem_link_s_trace_to_cell_membrane( link );
    if( !link ) ERR_fa( "Backtracing '#<sc_t>':\nTrace ends in open link.", lion_ifnameof( name ) );
    lion_sem_cell_s* cell = link->cell;
    lion_sem_link_s* next_link = NULL;

    if( depth > o->max_depth )
    {
        bcore_source_point_s_parse_err_fa( &cell->source_point, "Maximum depth '#<sz_t>' exceeded: This problem might be the result of an indefinite recursion.\n", o->max_depth );
    }

    if( link->exit )
    {
        bcore_source_point_s_parse_msg_to_sink_fa( &cell->source_point, log, "entering cell: '#<sc_t>' \n", lion_nameof( cell->name ) );

        // since we backtrace, a cell is entered through an 'exit' link
        s2_t err = lion_ctr_tree_s_tree_process( ctr_tree, cell, true, ctr_node, &ctr_node );
        if( err )
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nEntering cell failed.", lion_ifnameof( name ) );
        }

        if( cell->nop )
        {
            if( log ) bcore_sink_a_push_fa( log, "cell nop: #<sc_t>\n", ifnameof( cell->nop->_ ) );

            bl_t trace_up = false;
            lion_net_node_s* net_node_up = lion_net_nodes_s_get_by_id( &o->body, ctr_node->id );
            if( !net_node_up )
            {
                net_node_up = lion_net_nodes_s_push( &o->body );
                net_node_up->id = ctr_node->id;
                lion_net_node_s_set_nop_d( net_node_up, bcore_fork( cell->nop ) );

                bcore_source_point_s_attach( &net_node_up->source_point, bcore_fork( lion_ctr_node_s_get_nearest_source_point( ctr_node ) ) );

                trace_up = lion_nop_a_arity( net_node_up->nop ) > 0;
                if( log ) bcore_sink_a_push_fa( log, "new node id: '#<sz_t>'\n", net_node_up->id );
            }

            if( trace_up )
            {
                sz_t arity = lion_nop_a_arity( net_node_up->nop );
                ASSERT( arity == cell->encs.size );

                if( net_node_up->nop->_ == TYPEOF_lion_nop_ar3_branch_s )
                {
                    if( log ) bcore_sink_a_push_fa( log, "Branch channel 0:\n" );
                    net_cell_s_from_sem_recursive( o, cell->encs.data[ 0 ], ctr_tree, ctr_node, net_node_up, depth, log );
                    lion_net_node_s* arg0 = net_node_up->upls.data[ 0 ]->node;
                    lion_net_node_s_solve( arg0 );
                    if( arg0->result->h->h.v.size > 0 ) // determined holor
                    {
                        lion_net_links_s_clear( &net_node_up->upls );
                        lion_net_node_s_set_nop_d( net_node_up, ( lion_nop* )lion_nop_ar1_identity_s_create() );
                        if( log ) bcore_sink_a_push_fa( log, "Condition check result: #<f3_t>. Identity to channel ", bhvm_value_s_get_f3( &arg0->result->h->h.v, 0 ) );
                        if( bhvm_value_s_get_f3( &arg0->result->h->h.v, 0 ) > 0 )
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

            lion_net_links_s_push( &net_node_dn->upls )->node = net_node_up;
        }
        else if( link->up )
        {
            next_link = link->up;
        }
        else
        {
            bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nOpen exit link '#<sc_t>'.", lion_ifnameof( name ), lion_ifnameof( link->name ) );
        }
    }
    else
    {
        if( log ) bcore_sink_a_push_fa( log, "exiting cell: '#<sc_t>' \n", lion_ifnameof( cell->name ) );

        s2_t err = lion_ctr_tree_s_tree_process( ctr_tree, cell, false, ctr_node, &ctr_node );
        if( err )
        {
            if( err == 1 )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting from untraced cell.", lion_ifnameof( name ) );
            }
            else
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nExiting cell failed.", lion_ifnameof( name ) );
            }
        }

        if( !ctr_node ) // root membrane reached (trace ended)
        {
            sz_t index = lion_sem_links_s_get_index_by_link( &cell->encs, link );
            if( index == -1 )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nEnding trace: No matching input channel.", lion_ifnameof( name ) );
            }
            if( index >= o->encs.size )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nInput channel boundary exceeded.", lion_ifnameof( name ) );
            }

            lion_net_node_s* net_node_up = o->encs.data[ index ];
            lion_net_links_s_push( &net_node_dn->upls )->node = net_node_up;

            next_link = NULL;
        }

        else if( link->up )
        {
            next_link = link->up;
        }
        else
        {
            next_link = lion_sem_cell_s_get_enc_by_dn( ctr_node->cell, link );
            if( !next_link )
            {
                bcore_source_point_s_parse_err_fa( &cell->source_point, "Backtracing '#<sc_t>':\nTrace ends in open link.", lion_ifnameof( name ) );
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
void lion_net_cell_s_finalize( lion_net_cell_s* o )
{
    lion_net_cell_s_solve( o );
    lion_net_cell_s_remove_identities( o );
    lion_net_cell_s_set_downlinks( o );
    ASSERT( lion_net_cell_s_is_consistent( o ) );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_holor_s_from_sem_link( lion_holor_s* o, lion_sem_link_s* link, lion_sem_cell_s* root, bcore_sink* log )
{
    BLM_INIT();
    ASSERT( link->up );
    ASSERT( link->cell );
    ASSERT( root );
    if( !root->parent ) ERR_fa( "(root->parent == NULL) Root is not nested. Using semantic context as root is discouraged. Preferably use a double-nested semantic frame." );
    lion_sem_cell_s* cell = link->cell;
    lion_ctr_tree_s* tree = BLM_CREATE( lion_ctr_tree_s );
    lion_ctr_node_s* ctr_node = NULL;
    lion_ctr_tree_s_tree_process( tree, root, true, ctr_node, &ctr_node );
    lion_net_cell_s* net_frame = BLM_CREATE( lion_net_cell_s );
    lion_net_node_s* up_node = BLM_CREATE( lion_net_node_s );
    up_node->name = link->name;
    up_node->id = tree->id_base++;
    up_node->source_point = bcore_fork( &cell->source_point );
    lion_net_node_s_set_nop_d( up_node, ( lion_nop* )lion_nop_ar1_output_s_create() );
    net_cell_s_from_sem_recursive( net_frame, link->up, tree, ctr_node, up_node, 0, log );
    lion_net_node_s_solve( up_node );

    if( !up_node->result ) bcore_source_point_s_parse_err_fa( up_node->source_point, "Could not solve expression." );
    if( !up_node->result->h ) bcore_source_point_s_parse_err_fa( up_node->source_point, "Expression does not yield a holor." );

    lion_holor_s_copy( o, up_node->result->h );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/** Builds a net cell from a semantic cell
 *  This function locks and initializes the randomizer to ensure a deterministic sequence of random values.
 */
void lion_net_cell_s_from_sem_cell
(
    lion_net_cell_s* o,
    lion_sem_cell_s* sem_cell,
    lion_nop* (*input_nop_create)( vd_t arg, sz_t in_idx, tp_t in_name, const lion_nop* cur_nop ),
    vd_t arg,
    bcore_sink* log
)
{
    ASSERT( sem_cell );

    lion_ctr_tree_s* tree = lion_ctr_tree_s_create();
    for( sz_t i = 0; i < sem_cell->encs.size; i++ )
    {
        lion_sem_link_s* sem_link = sem_cell->encs.data[ i ];
        lion_net_node_s* net_node = lion_net_nodes_s_push( &o->encs );
        net_node->name = sem_link->name;
        net_node->id   = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );

        if( sem_link->up )
        {
            if( log ) bcore_sink_a_push_fa( log, "Evaluating literal in root entry channel '#<sz_t>' ... \n", i );
            lion_nop_ar0_param_s* param = lion_nop_ar0_param_s_create();
            param->h = lion_holor_s_create();

            lion_holor_s_from_sem_link( param->h, sem_link, sem_cell->parent, log );
            lion_net_node_s_set_nop_d( net_node, (lion_nop*)param );
            if( log )
            {
                bcore_sink_a_push_fa( log, "Evaluating literal in root entry channel '#<sz_t>' finished. Resulting Holor: ", i );
                lion_holor_s_brief_to_sink( param->h, log );
                bcore_sink_a_push_fa( log, "\n" );
            }
        }

        lion_nop* new_nop = input_nop_create ? input_nop_create( arg, i, sem_link->name, net_node->nop ) : NULL;
        if( new_nop ) lion_net_node_s_set_nop_d( net_node, new_nop );
    }

    lion_nop_context_s* nop_context = lion_nop_get_context();
    bcore_mutex_s_lock( nop_context->randomizer_mutex );
    ASSERT( !nop_context->randomizer_is_locked );
    nop_context->randomizer_is_locked = true;
    nop_context->randomizer_rval = 0; // rval == 0 causes randomizer to be seeded by functions using it.

    for( sz_t i = 0; i < sem_cell->excs.size; i++ )
    {
        lion_sem_link_s* sem_link = sem_cell->excs.data[ i ];
        lion_net_node_s* net_node = lion_net_nodes_s_push( &o->excs );
        net_node->name = sem_link->name;
        net_node->id = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        lion_net_node_s_set_nop_d( net_node, ( lion_nop* )lion_nop_ar1_output_s_create() );
        net_cell_s_from_sem_recursive( o, sem_link, tree, NULL, net_node, 0, log );
    }

    lion_ctr_tree_s_discard( tree );

    lion_net_cell_s_normalize( o );

    ASSERT( lion_net_cell_s_is_consistent( o ) );
    lion_net_cell_s_finalize( o );

    nop_context->randomizer_is_locked = false;
    bcore_mutex_s_unlock( nop_context->randomizer_mutex );
}

// ---------------------------------------------------------------------------------------------------------------------

/// outputs graph to sink
void lion_net_cell_s_graph_to_sink( lion_net_cell_s* o, bcore_sink* sink )
{
    BFOR_EACH( i, &o->excs ) lion_net_node_s_graph_to_sink( o->excs.data[ i ], sink );
}

// -------------------------------------------------------------------------------net_-------------------------------------

/**********************************************************************************************************************/
// node, cell: building mcode tracks

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_node_s_mcode_push_ap( lion_net_node_s* o, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    ASSERT( o );

    if( o->flag ) BLM_RETURN();
    o->flag = true;
    if( !o->nop ) ERR_fa( "Operator is missing." );
    if( !o->result ) ERR_fa( "Result is missing." );

    if( !o->result->codable )
    {
        bcore_source_point_s_parse_err_fa( o->source_point, "Operator '#<sc_t>': Not codable.", ifnameof( o->nop->_ ) );
    }

    bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

    BFOR_EACH( i, &o->upls )
    {
        lion_net_node_s* node = o->upls.data[ i ]->node;
        lion_net_node_s_mcode_push_ap( node, mcf );
        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'a' + i, node->hidx );
    }

    o->hidx = lion_nop_a_mcode_push_ap_holor( o->nop, o->result, arr_ci, mcf );
    bhvm_vop_arr_ci_s_push_ci( arr_ci, 'y', o->hidx );

    lion_nop_a_mcode_push_ap_track( o->nop, o->result, arr_ci, mcf );

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_node_s_mcode_push_dp( lion_net_node_s* o, sz_t up_index, bhvm_mcode_frame_s* mcf )
{
    ASSERT( o );
    if( !o->nop ) ERR_fa( "Operator is missing." );
    if( !o->result ) ERR_fa( "Result is missing." );

    BLM_INIT();

    bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

    sz_t up_gidx = -1;
    BFOR_EACH( i, &o->upls )
    {
        lion_net_node_s* node = o->upls.data[ i ]->node;
        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'a' + i, node->hidx );
        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'f' + i, node->gidx );
        if( i == up_index ) up_gidx = node->gidx;
    }
    bhvm_vop_arr_ci_s_push_ci( arr_ci, 'y', o->hidx );

    if( !o->flag ) // build gradient computation for this node
    {
        o->gidx = lion_nop_a_mcode_push_dp_holor( o->nop, o->result, arr_ci, mcf );

        // build this gradient from all downlinks ...
        BFOR_EACH( i, &o->dnls )
        {
            lion_net_node_s* node = o->dnls.data[ i ]->node;
            sz_t node_up_index = lion_net_node_s_up_index( node, o );
            ASSERT( node_up_index >= 0 );
            lion_net_node_s_mcode_push_dp( node, node_up_index, mcf );
        }

        o->flag = true;
    }

    bhvm_vop_arr_ci_s_push_ci( arr_ci, 'z', o->gidx );

    // update uplink gradient ... (up_index == -1 means no uplink present)
    if( up_index >= 0 )
    {
        ASSERT( up_gidx >= 0 );
        lion_nop_a_mcode_push_dp_track( o->nop, o->result, 'a' + up_index, arr_ci, mcf );
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_cell_s_mcode_push_ap( lion_net_cell_s* o, bhvm_mcode_frame_s* mcf )
{
    ASSERT( lion_net_cell_s_is_consistent( o ) );

    for( sz_t i = 0; i < o->excs.size; i++ )
    {
        lion_net_node_s* node = o->excs.data[ i ];
        if( !node->result ) ERR_fa( "Unsolved node '#<sc_t>'\n", lion_ifnameof( node->name ) );
        lion_net_node_s_mcode_push_ap( node, mcf );
    }

    lion_net_cell_s_clear_flags( o );

    bhvm_mcode_frame_s_check_integrity( mcf );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_cell_s_mcode_push_dp( lion_net_cell_s* o, bhvm_mcode_frame_s* mcf, bl_t entry_channels )
{
    ASSERT( lion_net_cell_s_is_consistent( o ) );

    if( entry_channels )
    {
        BFOR_EACH( i, &o->encs )
        {
            lion_net_node_s* node = o->encs.data[ i ];
            if( !node->nop ) continue;
            lion_net_node_s_mcode_push_dp( node, -1, mcf );
        }
    }

    BFOR_EACH( i, &o->body )
    {
        lion_net_node_s* node = o->body.data[ i ];
        if( !node->nop ) continue;
        if( node->nop->_ != TYPEOF_lion_nop_ar0_adaptive_s ) continue;
        lion_net_node_s_mcode_push_dp( node, -1, mcf );
    }

    lion_net_cell_s_clear_flags( o );

    bhvm_mcode_frame_s_check_integrity( mcf );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// frame

// ---------------------------------------------------------------------------------------------------------------------

static lion_nop* input_op_create( vd_t arg, sz_t in_idx, tp_t in_name, const lion_nop* current_nop )
{
    BLM_INIT();
    const bhvm_holor_s** in = arg;

    if( in ) ASSERT( *(aware_t*)in[ in_idx ] == TYPEOF_bhvm_holor_s );

    const bhvm_holor_s* h_in = in ? in[ in_idx ] : NULL;

    if( current_nop && current_nop->_ == TYPEOF_lion_nop_ar0_param_s )
    {
        const bhvm_holor_s* h_cur = &( ( lion_nop_ar0_param_s* )current_nop )->h->h;
        if( !h_in )
        {
            h_in = h_cur;
        }
        else if( !bhvm_shape_s_is_equal( &h_cur->s, &h_in->s ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            bcore_sink_a_push_fa( (bcore_sink*)msg, "Shape deviation at input holor '#<sz_t>':", in_idx );
            bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Passed input} " );
            bhvm_holor_s_brief_to_sink( h_in, (bcore_sink*)msg );
            bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Expected shape} " );
            bhvm_holor_s_brief_to_sink( h_cur, (bcore_sink*)msg );
            ERR_fa( "#<st_s*>\n", msg );
        }
    }

    if( h_in )
    {
        lion_nop_ar0_param_s* param = lion_nop_ar0_param_s_create();
        param->h = lion_holor_s_create();
        bhvm_holor_s_copy( &param->h->h, h_in );
        BLM_RETURNV( lion_nop*, ( lion_nop* )param );
    }
    else
    {
        BLM_RETURNV( lion_nop*, NULL );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_frame_s_disassemble_to_sink( const lion_net_frame_s* o, const lion_net_cell_s* cell, bcore_sink* sink )
{
    BLM_INIT();
    tp_t track_types [] =
    {
        TYPEOF_track_ap,
        TYPEOF_track_dp,
        TYPEOF_track_setup_ap,
        TYPEOF_track_setup_dp,
        TYPEOF_track_shelve_ap,
        TYPEOF_track_shelve_dp,
        TYPEOF_track_reset_dp
    };

    bhvm_mcode_frame_s* mcf = o->mcf;
    bcore_arr_st_s* info_holors = BLM_CREATE( bcore_arr_st_s );
    bcore_arr_st_s_set_size( info_holors, mcf->hbase->holor_ads.size );
    BFOR_EACH( i, info_holors ) info_holors->data[ i ] = st_s_create();

    bcore_sink_a_push_fa( sink, "Holorbase size: #<sz_t>\n", mcf->hbase ? bhvm_mcode_hbase_s_get_size( mcf->hbase ) : 0 );
    bcore_sink_a_push_fa( sink, "Entry channels:\n" );
    BFOR_EACH( i, &cell->encs )
    {
        lion_net_node_s* node = cell->encs.data[ i ];
        bcore_sink_a_push_fa( sink, "  #pl3 {#<sz_t>} (#<sc_t>):", i, lion_ifnameof( node->name ) );
        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap enc #<sz_t>", i );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp enc #<sz_t>", i );
        }

        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Exit channels:\n" );
    BFOR_EACH( i, &cell->excs )
    {
        lion_net_node_s* node = cell->excs.data[ i ];
        bcore_sink_a_push_fa( sink, "  #pl3 {#<sz_t>} (#<sc_t>):", i, lion_ifnameof( node->name ) );
        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap exc #<sz_t>", i );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp exc #<sz_t>", i );
        }
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Adaptive channels:\n" );
    BFOR_EACH( i, &cell->body )
    {
        lion_net_node_s* node = cell->body.data[ i ];
        if( !node->nop || node->nop->_ != TYPEOF_lion_nop_ar0_adaptive_s ) continue;
        lion_nop_ar0_adaptive_s* ar0_adaptive = ( lion_nop_ar0_adaptive_s* )node->nop;

        bcore_sink_a_push_fa( sink, "  #pl3 {#<sz_t>} (#<sc_t>):", i, lion_ifnameof( ar0_adaptive->h->m.name ) );
        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap adc #<sz_t>", i );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp adc #<sz_t>", i );
        }
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "Holorbase:\n" );
    BFOR_EACH( i, &mcf->hbase->holor_ads )
    {
        BLM_INIT();
        st_s* msg = BLM_CREATE( st_s );
        bhvm_holor_s* h = &mcf->hbase->holor_ads.data[ i ];
        st_s_push_fa( msg, "  #pl3 {#<sz_t>}: ", i );
        bhvm_holor_s_brief_to_sink( h, ( bcore_sink* )msg );
        if( info_holors->data[ i ]->size > 0 )
        {
            st_s_push_char_n( msg, ' ', 1 );
            st_s_push_char_n( msg, '.', uz_max( 0, 48 - msg->size ) );
            st_s_push_fa( msg, " #<st_s*>", info_holors->data[ i ] );
        }
        bcore_sink_a_push_fa( sink, "#<st_s*>\n", msg );
        BLM_DOWN();
    }
    bcore_sink_a_push_fa( sink, "\n" );

    for( sz_t i = 0; i < sizeof( track_types ) / sizeof( tp_t ); i++ )
    {
        tp_t track_type = track_types[ i ];
        bhvm_mcode_track_s* track = bhvm_mcode_frame_s_track_get( mcf, track_type );
        if( track )
        {
            bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track_type ) );
            BFOR_EACH( i, track )
            {
                bcore_sink_a_push_fa( sink, "  " );
                bhvm_vop* vop = track->data[ i ].vop;
                bhvm_vop_a_to_sink( vop, sink );
                bcore_sink_a_push_fa( sink, "\n" );
            }
            bcore_sink_a_push_fa( sink, "\n" );
        }
    }
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

bcore_arr_sz_s* lion_net_frame_push_idx( bcore_arr_sz_s** o, sz_t idx )
{
    if( !*o ) bcore_arr_sz_s_attach( o, bcore_arr_sz_s_create() );
    bcore_arr_sz_s_push( *o, idx );
    return *o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_frame_s* lion_net_frame_s_setup_from_source( lion_net_frame_s* o, bcore_source* source, const bhvm_holor_s** in )
{
    BLM_INIT();
    bcore_arr_sz_s_detach( &o->idx_ap_en );
    bcore_arr_sz_s_detach( &o->idx_dp_en );
    bcore_arr_sz_s_detach( &o->idx_ap_ex );
    bcore_arr_sz_s_detach( &o->idx_dp_ex );
    bcore_arr_sz_s_detach( &o->idx_ap_ada );
    bcore_arr_sz_s_detach( &o->idx_dp_ada );

    lion_net_cell_s* cell = BLM_CREATE( lion_net_cell_s );

    bhvm_mcode_frame_s_attach( &o->mcf, bhvm_mcode_frame_s_create() );

    /// We use a double-nested frame because the body of sem_frame->parent could be used
    lion_sem_cell_s* sem_frame = BLM_CREATE( lion_sem_cell_s );
    sem_frame->parent = BLM_A_PUSH( lion_sem_cell_s_create_frame() ); // double nested

    bcore_source_point_s_set( &sem_frame->source_point, source );
    lion_sem_cell_s_parse( sem_frame, source );

    /// network cell
    lion_net_cell_s_from_sem_cell( cell, sem_frame, input_op_create, ( vd_t )in, NULL );

    lion_net_cell_s_mcode_push_ap( cell, o->mcf );
    lion_net_cell_s_mcode_push_dp( cell, o->mcf, true );

    BFOR_EACH( i, &cell->encs )
    {
        lion_net_node_s* node = cell->encs.data[ i ];
        if( node->hidx >= 0 ) lion_net_frame_push_idx( &o->idx_ap_en, node->hidx );
        if( node->gidx >= 0 ) lion_net_frame_push_idx( &o->idx_dp_en, node->gidx );
    }

    BFOR_EACH( i, &cell->excs )
    {
        lion_net_node_s* node = cell->excs.data[ i ];
        if( node->hidx >= 0 ) lion_net_frame_push_idx( &o->idx_ap_ex, node->hidx );
        if( node->gidx >= 0 ) lion_net_frame_push_idx( &o->idx_dp_ex, node->gidx );
    }

    BFOR_EACH( i, &cell->body )
    {
        lion_net_node_s* node = cell->body.data[ i ];
        if( node->nop && node->nop->_ == TYPEOF_lion_nop_ar0_adaptive_s )
        {
            if( node->hidx >= 0 ) lion_net_frame_push_idx( &o->idx_ap_ada, node->hidx );
            if( node->gidx >= 0 ) lion_net_frame_push_idx( &o->idx_dp_ada, node->gidx );
        }
    }

    if( o->mcode_log ) lion_net_frame_s_disassemble_to_sink( o, cell, o->mcode_log );

    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_setup_ap );
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_setup_dp );

    BLM_RETURNV( lion_net_frame_s*, o );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_frame_s* lion_net_frame_s_run_ap( lion_net_frame_s* o, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    ASSERT( o->mcf );

    BFOR_EACH( i, o->idx_ap_en )
    {
        bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_ap_en->data[ i ] ];
        const bhvm_holor_s* h_i = in[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );

    BFOR_EACH( i, o->idx_ap_ex )
    {
        bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_ap_ex->data[ i ] ];
        bhvm_holor_s* h_o = out[ i ];
        ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
        if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
        bhvm_value_s_cpy( &h_m->v, &h_o->v );
    }

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_frame_s* lion_net_frame_s_run_dp( lion_net_frame_s* o, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    ASSERT( o->mcf );

    BFOR_EACH( i, o->idx_dp_ex )
    {
        bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_dp_ex->data[ i ] ];
        const bhvm_holor_s* h_i = in[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp );

    BFOR_EACH( i, o->idx_dp_en )
    {
        bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_dp_en->data[ i ] ];
        bhvm_holor_s* h_o = out[ i ];
        ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
        if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
        bhvm_value_s_cpy( &h_m->v, &h_o->v );
    }

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_frame_s* lion_net_frame_s_run_ap_adl( lion_net_frame_s* o, const bhvm_holor_adl_s* in, bhvm_holor_adl_s* out )
{
    if( out && out->size != lion_net_frame_s_get_size_ex( o ) ) bhvm_holor_adl_s_set_size( out, lion_net_frame_s_get_size_ex( o ) );
    BFOR_EACH( i, out ) if( !out->data[ i ] ) out->data[ i ] = bhvm_holor_s_create();
    return lion_net_frame_s_run_ap( o, in ? ( const bhvm_holor_s** )in->data : NULL, out ? ( bhvm_holor_s** ) out->data : NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_frame_s* lion_net_frame_s_run_dp_adl( lion_net_frame_s* o, const bhvm_holor_adl_s* in, bhvm_holor_adl_s* out )
{
    if( out && out->size != lion_net_frame_s_get_size_en( o ) ) bhvm_holor_adl_s_set_size( out, lion_net_frame_s_get_size_en( o ) );
    BFOR_EACH( i, out ) if( !out->data[ i ] ) out->data[ i ] = bhvm_holor_s_create();
    return lion_net_frame_s_run_dp( o, in ? ( const bhvm_holor_s** )in->data : NULL, out ? ( bhvm_holor_s** ) out->data : NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    BLM_INIT();
    lion_net_frame_s_run_ap( BLM_A_PUSH( lion_net_frame_s_create_from_sc( sc, in ) ), in, out );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    BLM_INIT();
    lion_net_frame_s_run_dp( BLM_A_PUSH( lion_net_frame_s_create_from_sc( sc, in ) ), in, out );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_frame_s_estimate_jacobian_en( const lion_net_frame_s* const_o, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();
    lion_net_frame_s* o = BLM_CLONE( lion_net_frame_s, const_o );

    bhvm_holor_adl_s* ref = BLM_CREATE( bhvm_holor_adl_s );
    bhvm_holor_adl_s_set_size( ref, o->idx_ap_ex->size );
    BFOR_EACH( k, o->idx_ap_ex ) ref->data[ k ] = bhvm_holor_s_clone( lion_net_frame_s_get_ap_ex( o, k ) );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, o->idx_ap_en->size );

    BFOR_EACH( i, o->idx_ap_en )
    {
        bhvm_holor_s* h_en = lion_net_frame_s_get_ap_en( o, i );

        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, o->idx_ap_ex->size );

        BFOR_EACH( j, &h_en->v )
        {
            f3_t v_en = bhvm_value_s_get_f3( &h_en->v, j );
            bhvm_value_s_set_f3( &h_en->v, j, v_en + epsilon );
            bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );
            BFOR_EACH( k, o->idx_ap_ex )
            {
                bhvm_holor_s* h_ex = lion_net_frame_s_get_ap_ex( o, k );
                bhvm_holor_s* h_rf = ref->data[ k ];

                if( !jac_adl->data[ k ] ) jac_adl->data[ k ] = bhvm_holor_s_create();
                bhvm_holor_s* h_jc = jac_adl->data[ k ];
                if( h_jc->v.size == 0 )
                {
                    bhvm_shape_s_set_data_na( &h_jc->s, 2, h_ex->v.size, h_en->v.size );
                    bhvm_holor_s_set_type( h_jc, TYPEOF_f3_t );
                    bhvm_holor_s_fit_size( h_jc );
                }

                BFOR_EACH( l, &h_ex->v )
                {
                    f3_t v_ex = bhvm_value_s_get_f3( &h_ex->v, l );
                    f3_t v_rf = bhvm_value_s_get_f3( &h_rf->v, l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    bhvm_value_s_set_f3( &h_jc->v, j * h_jc->s.data[ 0 ] + l, v_gr );
                }
            }
            bhvm_value_s_set_f3( &h_en->v, j, v_en );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_net_frame_s_estimate_jacobian_ada( const lion_net_frame_s* const_o, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )
{
    BLM_INIT();
    lion_net_frame_s* o = BLM_CLONE( lion_net_frame_s, const_o );

    bhvm_holor_adl_s* ref = BLM_CREATE( bhvm_holor_adl_s );
    bhvm_holor_adl_s_set_size( ref, o->idx_ap_ex->size );
    BFOR_EACH( k, o->idx_ap_ex ) ref->data[ k ] = bhvm_holor_s_clone( lion_net_frame_s_get_ap_ex( o, k ) );

    bhvm_holor_mdl_s_clear( jac_mdl );
    bhvm_holor_mdl_s_set_size( jac_mdl, o->idx_ap_ada->size );

    BFOR_EACH( i, o->idx_ap_ada )
    {
        bhvm_holor_s* h_ada = lion_net_frame_s_get_ap_ada( o, i );

        bhvm_holor_adl_s* jac_adl = jac_mdl->data[ i ] = bhvm_holor_adl_s_create();
        bhvm_holor_adl_s_set_size( jac_adl, o->idx_ap_ex->size );

        BFOR_EACH( j, &h_ada->v )
        {
            f3_t v_ada = bhvm_value_s_get_f3( &h_ada->v, j );
            bhvm_value_s_set_f3( &h_ada->v, j, v_ada + epsilon );
            bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );
            BFOR_EACH( k, o->idx_ap_ex )
            {
                bhvm_holor_s* h_ex = lion_net_frame_s_get_ap_ex( o, k );
                bhvm_holor_s* h_rf = ref->data[ k ];

                if( !jac_adl->data[ k ] ) jac_adl->data[ k ] = bhvm_holor_s_create();
                bhvm_holor_s* h_jc = jac_adl->data[ k ];
                if( h_jc->v.size == 0 )
                {
                    bhvm_shape_s_set_data_na( &h_jc->s, 2, h_ex->v.size, h_ada->v.size );
                    bhvm_holor_s_set_type( h_jc, TYPEOF_f3_t );
                    bhvm_holor_s_fit_size( h_jc );
                }

                BFOR_EACH( l, &h_ex->v )
                {
                    f3_t v_ex = bhvm_value_s_get_f3( &h_ex->v, l );
                    f3_t v_rf = bhvm_value_s_get_f3( &h_rf->v, l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    bhvm_value_s_set_f3( &h_jc->v, j * h_jc->s.data[ 0 ] + l, v_gr );
                }
            }
            bhvm_value_s_set_f3( &h_ada->v, j, v_ada );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_net_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_net" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_down1:
        {
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

