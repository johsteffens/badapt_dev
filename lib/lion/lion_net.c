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
 *  are removed and the operator is switched to a final arity0 version via lion_op_a_create_final.
 *  After settling, the graph can be run through an optimizer minimizing its structure.
 */
void lion_net_node_s_solve( lion_net_node_s* o )
{
    if( o->flag ) return; // cyclic link

    o->flag = true;

    if( o->result ) return;

    if( o->nop )
    {
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
            lion_nop_a_attach( &o->nop, lion_nop_a_create_final( o->nop, o->result->h ) );
            lion_net_links_s_clear( &o->upls );
            if( !o->result->reducible )
            {
                if( o->result->h ) bhvm_value_s_clear( &o->result->h->h.v );
            }
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

void lion_net_node_s_mcode_push_ap( lion_net_node_s* o, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    ASSERT( o );

    if( o->flag ) BLM_RETURN();
    o->flag = true;
    if( !o->nop ) ERR_fa( "Operator is missing." );
    if( !o->result ) ERR_fa( "Result is missing." );

    bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

    BFOR_EACH( i, &o->upls )
    {
        lion_net_node_s* node = o->upls.data[ i ]->node;
        lion_net_node_s_mcode_push_ap( node, mcf );
        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'a' + i, node->hidx );
    }

    o->hidx = lion_nop_a_mcode_push_ap_holor( o->nop, o->result, mcf );
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

    if( !o->flag ) // build gradient computation for this node
    {
        o->gidx = lion_nop_a_mcode_push_dp_holor( o->nop, o->result, mcf );

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

    // update uplink gradient ...
    if( up_index >= 0 )
    {
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );

        sz_t up_gidx = -1;
        BFOR_EACH( i, &o->upls )
        {
            lion_net_node_s* node = o->upls.data[ i ]->node;
            bhvm_vop_arr_ci_s_push_ci( arr_ci, 'a' + i, node->hidx );
            if( i == up_index ) up_gidx = node->gidx;
        }

        ASSERT( up_gidx >= 0 );

        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'y', o->hidx );
        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'z', o->gidx );
        bhvm_vop_arr_ci_s_push_ci( arr_ci, 'f' + up_index, up_gidx );

        lion_nop_a_mcode_push_dp_track( o->nop, o->result, 'a' + up_index, arr_ci, mcf );
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

    assert( lion_net_cell_s_is_consistent( o ) );
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
                net_node_up->nop = bcore_fork( cell->nop );

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
                        lion_nop_a_attach( &net_node_up->nop, ( lion_nop* )lion_nop_ar1_identity_s_create() );
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

/** Builds a net cell from a semantic cell
 *  This function locks and initializes the randomizer to ensure a deterministic sequence of random values.
 */
void lion_net_cell_s_from_sem_cell
(
    lion_net_cell_s* o,
    lion_sem_cell_s* sem_cell,
    lion_nop* (*input_nop_create)( vd_t arg, sz_t in_idx, tp_t in_name ),
    vd_t arg,
    bcore_sink* log
)
{
    ASSERT( sem_cell );
    lion_nop_context_s* nop_context = lion_nop_get_context();
    bcore_mutex_s_lock( nop_context->randomizer_mutex );
    ASSERT( !nop_context->randomizer_is_locked );
    nop_context->randomizer_is_locked = true;
    nop_context->randomizer_rval = 0; // rval == 0 causes randomizer to be seeded by functions using it.

    lion_ctr_tree_s* tree = lion_ctr_tree_s_create();
    for( sz_t i = 0; i < sem_cell->encs.size; i++ )
    {
        lion_sem_link_s* sem_link = sem_cell->encs.data[ i ];
        lion_net_node_s* net_node = lion_net_nodes_s_push( &o->encs );
        net_node->name = sem_link->name;
        net_node->id   = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        net_node->nop = input_nop_create ? input_nop_create( arg, i, sem_link->name ) : NULL;
    }

    for( sz_t i = 0; i < sem_cell->excs.size; i++ )
    {
        lion_sem_link_s* sem_link = sem_cell->excs.data[ i ];
        lion_net_node_s* net_node = lion_net_nodes_s_push( &o->excs );
        net_node->name = sem_link->name;
        net_node->id = tree->id_base++;
        net_node->source_point = bcore_fork( &sem_cell->source_point );
        lion_nop_ar1_output_s* nop_ar1_output = lion_nop_ar1_output_s_create();
        net_node->nop = ( lion_nop* )nop_ar1_output;
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

// ---------------------------------------------------------------------------------------------------------------------

// builds main vm procedure
//void haptive_cell_s_vm_build_infer( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
//{
//    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_infer );
//    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_setup );
//    ASSERT( haptive_net_cell_s_is_consistent( o ) );
//
//    bhvm_hf3_vm_arr_holor_s_set_size( &vmf->arr_holor, o->body.size );
//
//    for( sz_t i = 0; i < o->excs.size; i++ )
//    {
//        haptive_net_node_s* node = o->excs.data[ i ];
//        if( !node->h ) ERR_fa( "Unsolved node '#<sc_t>'\n", haptive_ifnameof( node->name ) );
//        net_node_s_vm_build_infer( node, vmf );
//    }
//
//    haptive_net_cell_s_clear_flags( o );
//}
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//// builds bp_grad vm procedure
//void haptive_cell_s_vm_build_bp_grad( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
//{
//    if( !bhvm_hf3_vm_frame_s_mcode_exists( vmf, TYPEOF_mcode_name_infer ) )
//    {
//        ERR_fa( "Procedure 'infer' missing. Call 'build_infer' first." );
//    }
//
//    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_bp_grad );
//    for( sz_t i = 0; i < o->body.size; i++ )
//    {
//        haptive_net_node_s* node = o->body.data[ i ];
//        if( !node->op ) continue;
//        if( node->op->_ != TYPEOF_haptive_op_ar0_adaptive_s ) continue;
//        node_s_vm_build_bp_grad( node, -1, vmf );
//    }
//    haptive_net_cell_s_clear_flags( o );
//}
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//void haptive_vm_build_setup( bhvm_hf3_vm_frame_s* o, u2_t rseed )
//{
//    const bhvm_hf3_vm_arr_holor_s* arr_holor = &o->arr_holor;
//    for( sz_t i = 0; i < arr_holor->size; i++ )
//    {
//        const bhvm_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
//        switch( holor->p.type )
//        {
//            case TYPEOF_holor_type_depletable:
//            case TYPEOF_holor_type_adaptive_grad:
//            {
//                bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_setup, bhvm_hf3_vm_op_ar0_determine_s_csetup( NULL, i ) );
//            }
//            break;
//
//            case TYPEOF_holor_type_adaptive:
//            {
//                if( holor->h.v_size == 0 )
//                {
//                    bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_setup, bhvm_hf3_vm_op_ar0_determine_s_csetup( NULL, i ) );
//                    bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_setup, bhvm_hf3_vm_op_ar0_randomize_s_csetup_randomize( NULL, i, rseed, 1.0, -0.5, 0.5 ) );
//                }
//            }
//            break;
//
//            default: break;
//        }
//    }
//
//    // moving init subroutines to setup ...
//
//    if( bhvm_hf3_vm_frame_s_mcode_exists( o, TYPEOF_mcode_name_cast ) )
//    {
//        bhvm_hf3_vm_frame_s_mcode_push( o, TYPEOF_mcode_name_setup, TYPEOF_mcode_name_cast );
//        bhvm_hf3_vm_frame_s_mcode_remove( o, TYPEOF_mcode_name_cast );
//    }
//
//    if( bhvm_hf3_vm_frame_s_mcode_exists( o, TYPEOF_mcode_name_cast_reverse ) )
//    {
//        bhvm_hf3_vm_frame_s_mcode_push_reverse( o, TYPEOF_mcode_name_setup, TYPEOF_mcode_name_cast_reverse );
//        bhvm_hf3_vm_frame_s_mcode_remove( o, TYPEOF_mcode_name_cast_reverse );
//    }
//
//    if( bhvm_hf3_vm_frame_s_mcode_exists( o, TYPEOF_mcode_name_ap_init ) )
//    {
//        bhvm_hf3_vm_frame_s_mcode_push( o, TYPEOF_mcode_name_setup, TYPEOF_mcode_name_ap_init );
//        bhvm_hf3_vm_frame_s_mcode_remove( o, TYPEOF_mcode_name_ap_init );
//    }
//
//    o->mcode_setup = TYPEOF_mcode_name_setup;
//}
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//// builds vm procedure shelve for all holors
//void haptive_vm_build_shelve( bhvm_hf3_vm_frame_s* o )
//{
//    bhvm_hf3_vm_frame_s_mcode_reset( o, TYPEOF_mcode_name_shelve );
//
//    const bhvm_hf3_vm_arr_holor_s* arr_holor = &o->arr_holor;
//    for( sz_t i = 0; i < arr_holor->size; i++ )
//    {
//        const bhvm_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
//        switch( holor->p.type )
//        {
//            case TYPEOF_holor_type_depletable:
//            {
//                bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_shelve, bhvm_hf3_vm_op_ar0_vacate_s_csetup( NULL, i ) );
//            }
//            break;
//
//            case TYPEOF_holor_type_cast:
//            {
//                bhvm_hf3_vm_frame_s_mcode_op_push_d( o, TYPEOF_mcode_name_shelve, bhvm_hf3_vm_op_ar0_clear_s_csetup( NULL, i ) );
//            }
//            break;
//
//            default: break;
//        }
//    }
//    o->mcode_shelve = TYPEOF_mcode_name_shelve;
//}
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//// sets adaptive gradients to zero
//void haptive_net_cell_s_vm_build_zero_adaptive_grad( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
//{
//    bhvm_hf3_vm_frame_s_mcode_reset( vmf, TYPEOF_mcode_name_zero_adaptive_grad );
//
//    const bhvm_hf3_vm_arr_holor_s* arr_holor = &vmf->arr_holor;
//    for( sz_t i = 0; i < arr_holor->size; i++ )
//    {
//        const bhvm_hf3_vm_holor_s* holor = &arr_holor->data[ i ];
//        switch( holor->p.type )
//        {
//            case TYPEOF_holor_type_adaptive_grad:
//            {
//                bhvm_hf3_vm_frame_s_mcode_op_push_d( vmf, TYPEOF_mcode_name_zero_adaptive_grad, bhvm_hf3_vm_op_ar0_zro_s_csetup( NULL, i ) );
//            }
//            break;
//
//            default: break;
//        }
//    }
//}
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//void haptive_net_cell_s_vm_set_input( const haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
//{
//    bcore_arr_sz_s_clear( &vmf->input );
//    for( sz_t i = 0; i < o->encs.size; i++ )
//    {
//        const haptive_net_node_s* node = o->encs.data[ i ];
//        bhvm_hf3_vm_frame_s_input_push( vmf, node->id );
//    }
//}
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//void haptive_net_cell_s_vm_set_output( const haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf )
//{
//    bcore_arr_sz_s_clear( &vmf->output );
//    for( sz_t i = 0; i < o->excs.size; i++ )
//    {
//        const haptive_net_node_s* node = o->excs.data[ i ];
//        bhvm_hf3_vm_frame_s_output_push( vmf, node->id );
//    }
//}
//
//// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

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


