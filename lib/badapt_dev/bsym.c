/** Copyright 2019 Johannes Bsymbolichard Steffens
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
#include "bsym.h"

/// prototypes
bsym_net_link_s* bsym_sem_node_s_get_arg_out( bsym_sem_node_s* o, sz_t index );
void bsym_sem_node_s_check_consistency( const bsym_sem_node_s* o );
void bsym_sem_node_s_embed( bsym_sem_node_s* o, bcore_source* source );
bsym_net_address_s* bsym_sem_node_s_evaluate( bsym_sem_node_s* o, bcore_source* source );
void bsym_sem_node_s_stack_evaluate( bsym_sem_node_s* o, bcore_arr_vd_s* stack, bcore_source* source );

/**********************************************************************************************************************/
//bsym

/**********************************************************************************************************************/
//bsym_net_body_s

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_net_body_s_push_link( bsym_net_body_s* o )
{
    bsym_net_link_s* link = ( bsym_net_link_s* )bsym_net_body_s_push_t( o, TYPEOF_bsym_net_link_s );
    link->root.body = o;
    link->root.index = o->size - 1;
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_push_node( bsym_net_body_s* o )
{
    bsym_net_node_s* node = ( bsym_net_node_s* )bsym_net_body_s_push_t( o, TYPEOF_bsym_net_node_s );
    node->root.body = o;
    node->root.index = o->size - 1;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_copy_node( bsym_net_body_s* o, const bsym_net_node_s* src )
{
    bsym_net_node_s* node = bsym_net_body_s_push_node( o );
    for( sz_t i = 0; i < src->targets_size; i++ )
    {
        bsym_net_address_s_copy( bsym_net_node_s_push( node ), &src->targets_data[ i ] );
    }
    node->name = src->name;
    node->load = sr_clone( sr_cw( src->load ) );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_push_number( bsym_net_body_s* o, f3_t val )
{
    bsym_net_node_s* node = bsym_net_body_s_push_node( o );
    bsym_op0_number_s* number = bsym_op0_number_s_create();
    number->v = val;
    node->load = sr_asd( number );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_address_s

// ---------------------------------------------------------------------------------------------------------------------

vd_t bsym_net_address_s_get_vd( const bsym_net_address_s* o )
{
    if( o->body )
    {
        const bsym_net_body_s* body = o->body;
        assert( o->index >= 0 && o->index < body->size );
        return body->data[ o->index ];
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_address_s_trace_to_sink( const bsym_net_address_s* addr, sz_t indent, bcore_sink* sink )
{
    vd_t vd_target = bsym_net_address_s_get_vd( addr );
    if( vd_target ) bsym_net_a_trace_to_sink( vd_target, indent, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_link_s

// ---------------------------------------------------------------------------------------------------------------------

sc_t bsym_net_link_s_get_name_sc( const bsym_net_link_s* link )
{
    if( link->root.body )
    {
        const bsym_net_body_s* body = link->root.body;
        if( body->hmap_name )
        {
            st_s* s = bcore_hmap_name_s_get( body->hmap_name, link->name );
            return s ? s->sc : "";
        }
    }
    return "";
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_link_s_trace_to_sink( const bsym_net_link_s* link, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(#<sc_t>) --> ", bsym_net_link_s_get_name_sc( link ) );
    bsym_net_address_s_trace_to_sink( &link->target, indent, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_node_s

// ---------------------------------------------------------------------------------------------------------------------

sc_t bsym_net_node_s_get_name_sc( const bsym_net_node_s* o )
{
    if( o->root.body )
    {
        const bsym_net_body_s* body = o->root.body;
        if( body->hmap_name )
        {
            st_s* s = bcore_hmap_name_s_get( body->hmap_name, o->name );
            return s ? s->sc : "";
        }
    }
    return "";
}

// ---------------------------------------------------------------------------------------------------------------------

vd_t bsym_net_node_s_get_target_vd( const bsym_net_node_s* o, sz_t index )
{
    assert( index < o->targets_size );
    return bsym_net_address_s_get_vd( &o->targets_data[ index ] );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_node_s_trace_to_sink( const bsym_net_node_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "<#<sc_t>>", bsym_net_node_s_get_name_sc( o ) );
    if( o->load.o )
    {
        if( sr_s_type( &o->load ) == TYPEOF_bsym_op0_number_s )
        {
            bcore_sink_a_push_fa( sink, "#<f3_t>", ( ( bsym_op0_number_s* )o->load.o )->v );
        }
        else
        {
            bsym_net_a_trace_to_sink( o->load.o, indent, sink );
        }
    }
    indent += 4;
    for( sz_t i = 0; i < o->targets_size; i++ )
    {
        bcore_sink_a_push_fa( sink, "\n#rn{ } |-> ", indent );
        bsym_net_address_s_trace_to_sink( &o->targets_data[ i ], indent, sink );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// bsym_net_holor_s

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_holor_s_trace_to_sink( const bsym_net_holor_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, " #<sz_t>-holor", o->dims );
}

// ---------------------------------------------------------------------------------------------------------------------


/**********************************************************************************************************************/
//bsym_sem_node_s

bsym_sem_node_s* bsym_sem_node_s_push_node( bsym_sem_node_s* o )
{
    bsym_sem_node_s* node = ( bsym_sem_node_s* )bsym_sem_frame_s_push_t( o->frame, TYPEOF_bsym_sem_node_s );
    node->frame = bsym_sem_frame_s_create();
    node->frame->parent = o->frame;
    node->frame->hmap_name = bcore_fork( o->frame->hmap_name );
    node->body.hmap_name   = bcore_fork( o->frame->hmap_name );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_node_s* bsym_sem_node_s_copy_node( bsym_sem_node_s* o, const bsym_sem_node_s* src )
{
    bsym_sem_node_s* node = bsym_sem_node_s_push_node( o );
    node->name = src->name;
    node->args_in  = src->args_in;
    node->args_out = src->args_out;
    bsym_net_body_s_copy( &node->body, &src->body );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bsym_sem_node_s_entypeof( const bsym_sem_node_s* o, sc_t name )
{
    assert( o->frame );
    assert( o->frame->hmap_name );
    return bcore_hmap_name_s_set_sc( o->frame->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t bsym_sem_node_s_get_name_sc( const bsym_sem_node_s* o, tp_t tp_name )
{
    st_s* name = bcore_hmap_name_s_get( o->frame->hmap_name, tp_name );
    return name ? name->sc : NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_set_args( bsym_sem_node_s* o, sz_t args_in, sz_t args_out )
{
    o->args_in = args_in;
    o->args_out = args_out;
    bsym_net_body_s_clear( &o->body );
    for( sz_t i = 0; i < args_in; i++ )  bsym_net_body_s_push_link( &o->body );
    for( sz_t i = 0; i < args_out; i++ ) bsym_net_body_s_push_link( &o->body );
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_get_arg_in( bsym_sem_node_s* o, sz_t index )
{
    ASSERT( index < o->args_in );
    return ( bsym_net_link_s* )o->body.data[ index ];
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_get_arg_out( bsym_sem_node_s* o, sz_t index )
{
    ASSERT( index < o->args_out );
    return ( bsym_net_link_s* )o->body.data[ o->args_in + index ];
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_get_arg_in_by_name( bsym_sem_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->args_in; i++ )
    {
        if( bsym_sem_node_s_get_arg_in( o, i )->name == name ) return bsym_sem_node_s_get_arg_in( o, i );
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t bsym_sem_node_s_get_free_args_in( bsym_sem_node_s* o )
{
    sz_t count = 0;
    for( sz_t i = 0; i < o->args_in; i++ )
    {
        bsym_net_link_s* link = bsym_sem_node_s_get_arg_in( o, i );
        count += ( link->target.body == NULL );
    }
    return count;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_get_next_free_arg_in( bsym_sem_node_s* o )
{
    for( sz_t i = 0; i < o->args_in; i++ )
    {
        bsym_net_link_s* link = bsym_sem_node_s_get_arg_in( o, i );
        if( link->target.body == NULL ) return link;
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_get_arg_out_by_name( bsym_sem_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->args_out; i++ )
    {
        if( bsym_sem_node_s_get_arg_out( o, i )->name == name ) return bsym_sem_node_s_get_arg_out( o, i );
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_get_link_from_body_by_name( bsym_sem_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        vd_t item = o->body.data[ i ];
        if( *(aware_t*)item == TYPEOF_bsym_net_link_s )
        {
            bsym_net_link_s* link = item;
            if( link->name == name ) return link;
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_node_s* bsym_sem_frame_s_get_node_by_name( bsym_sem_frame_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        bsym_sem* item = o->data[ i ];
        assert( *( aware_t* )item == TYPEOF_bsym_sem_node_s );
        bsym_sem_node_s* node = ( bsym_sem_node_s* )item;
        if( node->name == name ) return node;
    }
    if( o->parent ) return bsym_sem_frame_s_get_node_by_name( o->parent, name );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_node_s* bsym_sem_node_s_get_node_by_name( bsym_sem_node_s* o, tp_t name )
{
    return bsym_sem_frame_s_get_node_by_name( o->frame, name );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_trace_out_to_sink( const bsym_sem_node_s* o, sz_t out_index, bcore_sink* sink )
{
    ASSERT( out_index < o->args_out );

    bsym_net_link_s* link = bsym_sem_node_s_get_arg_out( ( bsym_sem_node_s* )o, out_index );

    ASSERT( link->target.body == &o->body );

    bcore_sink_a_push_fa( sink, "Tracing node '#<sc_t>.#<sc_t>':\n", bsym_sem_node_s_get_name_sc( o, o->name ), bsym_net_link_s_get_name_sc( link ) );
    bsym_net_link_s_trace_to_sink( bsym_sem_node_s_get_arg_out( ( bsym_sem_node_s* )o, out_index ), 0, sink );
    bcore_sink_a_push_fa( sink, "\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_push_link( bsym_sem_node_s* o )
{
    return bsym_net_body_s_push_link( &o->body );
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_node_s_push_number( bsym_sem_node_s* o, f3_t val )
{
    bsym_net_node_s* node = bsym_net_body_s_push_number( &o->body, val );
    node->name = bsym_sem_node_s_entypeof( o, "number" );
    bsym_net_link_s* link = bsym_sem_node_s_push_link( o );
    bsym_net_address_s_copy( &link->target, &node->root );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_sem_node_s_push_net_node( bsym_sem_node_s* o, sz_t args )
{
    bsym_net_node_s* net_node = bsym_net_body_s_push_node( &o->body );
    bsym_net_node_s_set_size( net_node, args );
    return net_node;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_sem_node_s_trace_build_graph( bsym_sem_node_s* o, bsym_net_address_s* addr, st_s* err_msg )
{
    if( !addr->body )
    {
        if( err_msg ) st_s_push_fa( err_msg, "Trace ends in open link." );
        return false;
    }

    vd_t vd = bsym_net_address_s_get_vd( addr );

    if( *( aware_t* )vd == TYPEOF_bsym_net_link_s )
    {
        bsym_net_link_s* link = vd;
        if( link->flag ) return true;
        bsym_net_address_s_copy( addr, &link->target );
        return bsym_sem_node_s_trace_build_graph( o, addr, err_msg );
    }

    if( *( aware_t* )vd == TYPEOF_bsym_net_node_s )
    {
        bsym_net_node_s* node = vd;
        if( node->root.body != &o->body )
        {
            if( !node->new_root )
            {
                bsym_net_node_s* new_node = bsym_net_body_s_copy_node( &o->body, node );
                node->new_root = &new_node->root;
            }

            bsym_net_address_s_copy( addr, node->new_root );
            node = bsym_net_address_s_get_vd( addr );
        }
        for( sz_t i = 0; i < node->targets_size; i++ )
        {
            if( !bsym_sem_node_s_trace_build_graph( o, &node->targets_data[ i ], err_msg ) ) return false;
        }
        return true;
    }

    if( err_msg ) st_s_push_fa( err_msg, "Trace ends in invalid object '#<sc_t>'.", ifnameof( *( aware_t* )vd ) );

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

/// converts all sub-nodes into a graph held by o->body
bl_t bsym_sem_node_s_build_graph( bsym_sem_node_s* o, st_s* err_msg )
{
    sc_t sc_name = bsym_sem_node_s_get_name_sc( o, o->name );
    // set flag
    for( sz_t i = 0; i < o->args_in;  i++ ) bsym_sem_node_s_get_arg_in( o, i )->flag = true;

    for( sz_t i = 0; i < o->args_out; i++ )
    {
        bsym_net_link_s* link = bsym_sem_node_s_get_arg_out( o, i );
        if( !bsym_sem_node_s_trace_build_graph( o, &link->target, err_msg ) )
        {
            if( err_msg )
            {
                st_s* msg = st_s_create();
                st_s_push_fa( msg, "Backtracing output channel #<sc_t>.#<sc_t>:\n", sc_name, bsym_sem_node_s_get_name_sc( o, link->name ) );
                st_s_push_fa( msg, "#<sc_t>\n", err_msg->sc );
                st_s_copy( err_msg, msg );
                st_s_discard( msg );
            }
            return false;
        }
    }

    // reset flag
    for( sz_t i = 0; i < o->args_in;  i++ ) bsym_sem_node_s_get_arg_in( o, i )->flag = false;

    // remove local nodes
    bsym_sem_frame_s_clear( o->frame );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_check_build_graph( bsym_sem_node_s* o )
{
    st_s* err_msg = st_s_create();
    if( !bsym_sem_node_s_build_graph( o, err_msg ) )
    {
        ERR_fa( "#<sc_t>\n", err_msg->sc );
    }
    st_s_discard( err_msg );
}

// ---------------------------------------------------------------------------------------------------------------------

/// in body of o: creates new node which is catenated version of n1 : n2
bsym_sem_node_s* bsym_sem_node_s_cat_node( bsym_sem_node_s* o, bsym_sem_node_s* n1, bsym_sem_node_s* n2 )
{
    bsym_sem_node_s* node = bsym_sem_node_s_push_node( o );
    n1 = bsym_sem_node_s_copy_node( node, n1 );
    n2 = bsym_sem_node_s_copy_node( node, n2 );
    sz_t free_args_in1 = bsym_sem_node_s_get_free_args_in( n1 );
    sz_t free_args_in2 = bsym_sem_node_s_get_free_args_in( n2 );

    for( sz_t i = 0; i < sz_min( free_args_in1, n2->args_out ); i++ )
    {
        bsym_net_address_s_copy( &bsym_sem_node_s_get_next_free_arg_in( n1 )->target, &bsym_sem_node_s_get_arg_out( n2, i )->root );
    }

    bsym_sem_node_s_set_args( node, free_args_in2, n1->args_out );

    for( sz_t i = 0; i < free_args_in2; i++ )
    {
        bsym_net_address_s_copy( &bsym_sem_node_s_get_next_free_arg_in( n2 )->target, &bsym_sem_node_s_get_arg_in( node, i )->root );
    }

    for( sz_t i = 0; i < node->args_out; i++ )
    {
        bsym_net_address_s_copy( &bsym_sem_node_s_get_arg_out( node, i )->target, &bsym_sem_node_s_get_arg_out( n1, i )->root );
    }

    bsym_sem_node_s_check_build_graph( node );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_sem_node_s_push_op( bsym_sem_node_s* o, sz_t args, tp_t name )
{
    bsym_sem_node_s* sem_node = bsym_sem_node_s_push_node( o );
    sem_node->name = name;
    bsym_sem_node_s_set_args( sem_node, args, 1 );
    bsym_net_node_s* net_node = bsym_sem_node_s_push_net_node( sem_node, args );
    net_node->name = name;
    for( sz_t i = 0; i < args; i++ )
    {
        bsym_net_address_s_copy( &net_node->targets_data[ i ], &bsym_sem_node_s_get_arg_in( sem_node, i )->root );
    }
    bsym_net_address_s_copy( &bsym_sem_node_s_get_arg_out( sem_node, 0 )->target, &net_node->root );

    bsym_sem_node_s_check_build_graph( sem_node );
    return net_node;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_push_op1_sc( bsym_sem_node_s* o, sc_t name )
{
    tp_t tp_name = bsym_sem_node_s_entypeof( o, name );
    bsym_net_node_s* node = bsym_sem_node_s_push_op( o, 1, tp_name );
    tp_t type = entypeof_fa( "bsym_op1_#<sc_t>_s", name );
    node->load = sr_create( type );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_push_op2_sc( bsym_sem_node_s* o, sc_t name )
{
    tp_t tp_name = bsym_sem_node_s_entypeof( o, name );
    bsym_net_node_s* node = bsym_sem_node_s_push_op( o, 2, tp_name );
    tp_t type = entypeof_fa( "bsym_op2_#<sc_t>_s", name );
    node->load = sr_create( type );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bsym_sem_node_s_parse_name( bsym_sem_node_s* o, bcore_source* source )
{
    st_s* name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", name );
    if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Name expected." );
    tp_t tp_name = bsym_sem_node_s_entypeof( o, name->sc );
    st_s_discard( name );
    return tp_name;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t bsym_sem_node_s_parse_args( bsym_sem_node_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    sz_t count = 0;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );
        bsym_net_link_s* link = bsym_net_body_s_push_link( &o->body );
        link->name = bsym_sem_node_s_parse_name( o, source );
        count++;
        first = false;
    }
    return count;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_evaluate_set_args( bsym_sem_node_s* o, bsym_sem_node_s* parent, bcore_source* source )
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
                bsym_net_link_s* link = bsym_sem_node_s_get_arg_in_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' specifies no input link of node '#<sc_t>'.", name->sc, bsym_sem_node_s_get_name_sc( o, o->name ) );
                }

                if( link->target.body )
                {
                    bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' of node '#<sc_t>' has already been set.", name->sc, bsym_sem_node_s_get_name_sc( o, o->name ) );
                }

                bsym_net_address_s_copy( &link->target, bsym_sem_node_s_evaluate( parent, source ) );
                done = true;
            }
            else
            {
                bcore_arr_vd_s_push( stack, name );
            }
        }

        if( !done )
        {
            bsym_net_link_s* link = bsym_sem_node_s_get_next_free_arg_in( o );

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Node '#<sc_t>': Assigning more links than available.", bsym_sem_node_s_get_name_sc( o, o->name ) );
            }

            bsym_sem_node_s_stack_evaluate( parent, stack, source );
            ASSERT( stack->size == 1 );
            ASSERT( *(aware_t*)stack->data[ 0 ] == TYPEOF_bsym_net_address_s );
            bsym_net_address_s* addr = bcore_arr_vd_s_pop( stack );
            bsym_net_address_s_copy( &link->target, addr );
        }

        first = false;
    }

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static vd_t cast_a( tp_t type, vd_t o, bcore_source* source )
{
    if( *( aware_t* )o == type ) return o;
    bcore_source_a_parse_err_fa( source, "Type error: '#<sc_t>' present but '#<sc_t>' expected.", ifnameof( *( aware_t* )o ), ifnameof( type ) );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_stack_evaluate( bsym_sem_node_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( st_s, name );
    BCORE_LIFE_CREATE( bsym_sem_stack_flag_s, bin_op_completion );
    BCORE_LIFE_CREATE( bsym_sem_stack_flag_s, catenation );

    while( !bcore_source_a_eos( source ) )
    {
        bl_t identifier = false;

        // identifier
        if( stack->size > 0 && *(aware_t*)stack->data[ 0 ] == TYPEOF_st_s )
        {
            st_s_copy( name, bcore_arr_vd_s_pop( stack ) );
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
            vd_t item = NULL;

            // input channel
            if( ( item = bsym_sem_node_s_get_arg_in_by_name( o, tp_name ) ) )
            {
                bsym_net_link_s* link = item;
                bcore_arr_vd_s_push( stack, &link->root );
            }

            // link on body
            else if( ( item = bsym_sem_node_s_get_link_from_body_by_name( o, tp_name ) ) )
            {
                bsym_net_link_s* link = item;
                bcore_arr_vd_s_push( stack, &link->root );
            }

            // node
            else if( ( item = bsym_sem_node_s_get_node_by_name( o, tp_name ) ) )
            {
                bsym_sem_node_s* node = item;

                if( bsym_sem_node_s_get_free_args_in( node ) > 0 )
                {
                    node = bsym_sem_node_s_copy_node( o, node );
                }

                if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
                {
                    bsym_sem_node_s_evaluate_set_args( node, o, source );
                }
                bcore_arr_vd_s_push( stack, node );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cannot evaluate identifier '#<sc_t>'.", name->sc );
            }
        }

        // scalar literal
        else if( bcore_source_a_parse_bl_fa( source, "#?(([0]>='0'&&[0]<='9')||([0]=='-'&&([1]>='0'&&[1]<='9')))" ) )
        {
            f3_t val = 0;
            bcore_source_a_parse_fa( source, " #<f3_t*>", &val );
            bsym_net_link_s* link = bsym_sem_node_s_push_number( o, val );
            bcore_arr_vd_s_push( stack, &link->root );
        }

        // block
        else if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
        {
            bcore_arr_vd_s_push( stack, bsym_sem_node_s_evaluate( o, source ) );
            bcore_source_a_parse_fa( source, " )" );
        }

        // binary operator
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]=='*'||[0]=='+'||[0]=='-'||[0]=='<')" ) )
        {
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<char>': Left operand missing.", bcore_source_a_get_u0( source ) );

            bsym_sem_node_s* node = NULL;

            if( bcore_source_a_parse_bl_fa( source, "#?'+'" ) )
            {
                node = bsym_sem_node_s_get_node_by_name( o, typeof( "__plus" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'-'" ) )
            {
                node = bsym_sem_node_s_get_node_by_name( o, typeof( "__minus" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'*'" ) )
            {
                node = bsym_sem_node_s_get_node_by_name( o, typeof( "__mul" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'<*>'" ) )
            {
                node = bsym_sem_node_s_get_node_by_name( o, typeof( "__hmul" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'<'" ) )
            {
                bcore_source_a_parse_fa( source, "#until'>'>", name );
                node = bsym_sem_node_s_get_node_by_name( o, typeof( name->sc ) );
                if( !node ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>' not found.", name->sc );
            }

            if( !node ) bcore_source_a_parse_err_fa( source, "Syntax error." );

            sz_t free_args = bsym_sem_node_s_get_free_args_in( node );
            sc_t sc_node_name = bsym_sem_node_s_get_name_sc( o, node->name );

            if( free_args != 2 )      bcore_source_a_parse_err_fa( source, "Node '#<sc_t>' has #<sz_t> free input channels.", sc_node_name, free_args );
            if( node->args_out != 1 ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>' has #<sz_t> output channels.", sc_node_name, node->args_out );

            node = bsym_sem_node_s_copy_node( o, node );
            bsym_net_link_s* op_link = bsym_sem_node_s_get_next_free_arg_in( node );

            vd_t l_item = bcore_arr_vd_s_pop( stack );
            if( *(aware_t*)l_item == TYPEOF_bsym_sem_node_s )
            {
                bsym_sem_node_s* l_node = l_item;
                if( l_node->args_out != 1 ) bcore_source_a_parse_err_fa( source, "Left operand needs exactly one output channel." );
                bsym_net_link_s* l_out_link = bsym_sem_node_s_get_arg_out( l_node, 0 );
                bsym_net_address_s_copy( &op_link->target, &l_out_link->root );
            }
            else if( *(aware_t*)l_item == TYPEOF_bsym_net_address_s )
            {
                bsym_net_address_s* l_address = l_item;
                bsym_net_address_s_copy( &op_link->target, l_address );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Invalid left operand '#<sc_t>'.", ifnameof( *(aware_t*)l_item ) );
            }

            bcore_arr_vd_s_push( stack, bin_op_completion );
            bcore_arr_vd_s_push( stack, node );
        }

        // output channel selection
        else if( bcore_source_a_parse_bl_fa( source, " #?'.'" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );

            if( *(aware_t*)stack->data[ stack->size - 1 ] != TYPEOF_bsym_sem_node_s )
            {
                bcore_source_a_parse_err_fa( source, "Output channel selection on non-node." );
            }

            bsym_sem_node_s* node = bcore_arr_vd_s_pop( stack );
            sz_t free_args = bsym_sem_node_s_get_free_args_in( node );
            sc_t sc_node_name = bsym_sem_node_s_get_name_sc( node, node->name );

            if( free_args > 0 )
            {
                bcore_source_a_parse_err_fa( source, "Channel selection '.': Node #<sz_t> has #<sz_t> free input channels.", sc_node_name, free_args );
            }

            bsym_net_link_s* link = bsym_sem_node_s_get_arg_out_by_name( node, typeof( name->sc ) );

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Node '#<sc_t>':Invalid channel '#<sc_t>'.", sc_node_name, name->sc );
            }
            bcore_arr_vd_s_push( stack, &link->root );
        }

        // node catenation
        else if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
        {
            if( stack->size >= 1 && *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_sem_node_s )
            {
                bcore_arr_vd_s_push( stack, catenation );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Node catenation ':': l-value is not a node." );
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

        /// resolving stack...

        // bin_op_completion
        if( stack->size >= 3 && stack->data[ stack->size - 3 ] == bin_op_completion )
        {
            bsym_net_address_s* addr = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );
            bsym_sem_node_s*    node = cast_a( TYPEOF_bsym_sem_node_s,    bcore_arr_vd_s_pop( stack ), source );
            ASSERT( bcore_arr_vd_s_pop( stack ) == bin_op_completion );

            sz_t free_args = bsym_sem_node_s_get_free_args_in( node );
            ASSERT( free_args == 1 );

            bsym_net_link_s* l_link = bsym_sem_node_s_get_next_free_arg_in( node );
            bsym_net_address_s_copy( &l_link->target, addr );

            ASSERT( node->args_out == 1 );
            bcore_arr_vd_s_push( stack, &bsym_sem_node_s_get_arg_out( node, 0 )->root );
        }

        // node-catenation
        if( stack->size >= 3 && stack->data[ stack->size - 2 ] == catenation )
        {
            if( *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_sem_node_s )
            {
                bsym_sem_node_s* node2 = cast_a( TYPEOF_bsym_sem_node_s, bcore_arr_vd_s_pop( stack ), source );
                ASSERT( bcore_arr_vd_s_pop( stack ) == catenation );
                bsym_sem_node_s* node1 = cast_a( TYPEOF_bsym_sem_node_s, bcore_arr_vd_s_pop( stack ), source );
                sz_t free_args1 = bsym_sem_node_s_get_free_args_in( node1 );
                if( free_args1 != node2->args_out )
                {
                    bcore_source_a_parse_err_fa( source, "Node catenation 'N1 : N2': N1 has #<sz_t> free input arguments; N2 has #<sz_t> output arguments.", free_args1, node2->args_out );
                }

                bsym_sem_node_s* node = bsym_sem_node_s_cat_node( o, node1, node2 );
                bcore_arr_vd_s_push( stack, node );
            }
            else if( *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_net_address_s )
            {
                bsym_net_address_s* addr = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );
                ASSERT( bcore_arr_vd_s_pop( stack ) == catenation );
                bsym_sem_node_s* node2   = cast_a( TYPEOF_bsym_sem_node_s, bcore_arr_vd_s_pop( stack ), source );
                sz_t free_args2 = bsym_sem_node_s_get_free_args_in( node2 );
                if( free_args2 != 1 )
                {
                    bcore_source_a_parse_err_fa( source, "Catenation 'N1 : Link': N1 has #<sz_t> free input arguments; required is 1", free_args2 );
                }

                bsym_net_address_s_copy( &bsym_sem_node_s_get_next_free_arg_in( node2 )->target, addr );
                bcore_arr_vd_s_push( stack, node2 );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cannot resolve catenation." );
            }
        }
    }

    ASSERT( stack->size == 1 );
    vd_t ret = bcore_arr_vd_s_pop( stack );

    if( *( aware_t* )ret == TYPEOF_bsym_sem_node_s )
    {
        bsym_sem_node_s* node = ret;
        sz_t free_args = bsym_sem_node_s_get_free_args_in( node );
        if( free_args > 0 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic output channel selection on node with #<sz_t> free input channels.", free_args );
        }

        if( node->args_out != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic output channel selection on node with #<sz_t> output channels.", node->args_out );
        }

        ret = &bsym_sem_node_s_get_arg_out( node, 0 )->root;
    }

    if( *( aware_t* )ret != TYPEOF_bsym_net_address_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Address expected.", ifnameof( *( aware_t* )ret ) );
    }

    bcore_arr_vd_s_push( stack, ret );

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_address_s* bsym_sem_node_s_evaluate( bsym_sem_node_s* o, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    bsym_sem_node_s_stack_evaluate( o, stack, source );
    vd_t ret = bcore_arr_vd_s_pop( stack );
    ASSERT( *( aware_t* )ret == TYPEOF_bsym_net_address_s );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_parse( bsym_sem_node_s* o, bcore_source* source )
{

    o->name = bsym_sem_node_s_parse_name( o, source );
    bcore_source_a_parse_fa( source, " = " );

    //    <name > = ( <args_in> ) => ( <args_out> ) { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        o->args_in = bsym_sem_node_s_parse_args( o, source );
        bcore_source_a_parse_fa( source, " => " );
        o->args_out = bsym_sem_node_s_parse_args( o, source );

        bcore_source_a_parse_fa( source, " {" );
        while( !bcore_source_a_parse_bl_fa( source, " #?'}'" ) )
        {
            if( bcore_source_a_parse_bl_fa( source, " #?'node'" ) )
            {
                bl_t first = true;
                while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
                {
                    if( !first ) bcore_source_a_parse_fa( source, " ," );
                    bsym_sem_node_s* node = bsym_sem_node_s_push_node( o );
                    bsym_sem_node_s_parse( node, source );
                    first = false;
                }
            }
            else if( bcore_source_a_parse_bl_fa( source, " #?'link'" ) )
            {
                bl_t first = true;
                while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
                {
                    if( !first ) bcore_source_a_parse_fa( source, " ," );
                    bsym_net_link_s* link = bsym_sem_node_s_push_link( o );
                    link->name = bsym_sem_node_s_parse_name( o, source );
                    bcore_source_a_parse_fa( source, " -> " );
                    bsym_net_address_s_copy( &link->target, bsym_sem_node_s_evaluate( o, source ) );
                    first = false;
                }
            }
            else if( bcore_source_a_parse_bl_fa( source, " #?'holor'" ) )
            {
                bl_t first = true;
                while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
                {
                    if( !first ) bcore_source_a_parse_fa( source, " ," );
                    bsym_net_node_s* net_node = bsym_sem_node_s_push_net_node( o, 0 );
                    bsym_net_link_s* link = bsym_sem_node_s_push_link( o );
                    link->name = bsym_sem_node_s_parse_name( o, source );
                    bsym_net_address_s_copy( &link->target, &net_node->root );

                    bcore_source_a_parse_fa( source, " = " );
                    net_node->load = sr_create( TYPEOF_bsym_net_holor_s );
                    net_node->name = link->name;
                    bsym_net_holor_s* holor = net_node->load.o;
                    while( !bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
                    {
                        bcore_source_a_parse_fa( source, " [" );
                        bsym_net_address_s* address = bsym_net_node_s_push( net_node );
                        bsym_net_address_s_copy( address, bsym_sem_node_s_evaluate( o, source ) );
                        bcore_source_a_parse_fa( source, " ]" );
                        holor->dims++;
                    }

                    first = false;
                }
            }
            else
            {
                st_s* name = st_s_create();
                bcore_source_a_parse_fa( source, " #name", name );
                if( !name->size ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
                bsym_net_link_s* link = bsym_sem_node_s_get_arg_out_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' specifies no output link of node '#<sc_t>'.", name->sc, bsym_sem_node_s_get_name_sc( o, o->name ) );
                }

                if( link->target.body )
                {
                    bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' of node '#<sc_t>' has already been set.", name->sc, bsym_sem_node_s_get_name_sc( o, o->name ) );
                }

                bcore_source_a_parse_fa( source, " ->" );

                bsym_net_address_s_copy( &link->target, bsym_sem_node_s_evaluate( o, source ) );

                bcore_source_a_parse_fa( source, " ;" );

                st_s_discard( name );
            }
        }
    }

    // <name > = <node_name>( <argname> = link, ... )
    else
    {
        st_s* name = st_s_create();
        bcore_source_a_parse_fa( source, " #name", name );
        if( !name->size ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
        bsym_sem_node_s* node = bsym_sem_node_s_get_node_by_name( o, typeof( name->sc ) );
        if( !node ) bcore_source_a_parse_err_fa( source, "'#<sc_t>' unknown.", name->sc );
        node = bsym_sem_node_s_copy_node( o, node );
        bsym_sem_node_s_evaluate_set_args( node, o, source );
        st_s_discard( name );
    }

    {
        st_s* err_msg = st_s_create();
        if( !bsym_sem_node_s_build_graph( o, err_msg ) )
        {
            bcore_source_a_parse_err_fa( source, "#<sc_t>\n", err_msg->sc );
        }
        st_s_discard( err_msg );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_node_s_setup_root( bsym_sem_node_s* o )
{
    o->frame = bsym_sem_frame_s_create();
    o->frame->hmap_name = bcore_hmap_name_s_create();
    o->body.hmap_name = bcore_fork( o->frame->hmap_name );

    bsym_sem_node_s_push_op1_sc( o, "linear" );
    bsym_sem_node_s_push_op1_sc( o, "tanh"   );
    bsym_sem_node_s_push_op1_sc( o, "dimof"  );

    bsym_sem_node_s_push_op2_sc( o, "__mul" );
    bsym_sem_node_s_push_op2_sc( o, "__hmul" );
    bsym_sem_node_s_push_op2_sc( o, "__plus" );
    bsym_sem_node_s_push_op2_sc( o, "__minus" );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void bsym_test( void )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bsym_sem_node_s, node );
    bsym_sem_node_s_setup_root( node );

    st_s text = st_weak_sc
    (
        "root = ( root_x ) => ( root_y )"
        "{"
            "node layer = ( dim_y, x ) => ( y )"
            "{"
                "holor w = [ dim_y ][ dimof( x ) ]#, b = [ dim_y ]#;"
                "y -> ( w * x ) + b;"
            "};"

            "root_y -> tanh : layer( 1 ) : tanh : layer( 10 ) : tanh : layer( 100 ) : tanh : layer( 1000 ) : root_x;"

//            "root_y -> tanh : layer( 1 ) : root_x;"
//            "root_y -> layer( 1, root_x );"
//            "root_y -> root_x;"
        "};"
    );

    bsym_sem_node_s_parse( node, ( bcore_source* )&text );

    bsym_net_link_s_trace_to_sink( bsym_sem_node_s_get_arg_out( node, 0 ), 0, BCORE_STDOUT );

    //bcore_txt_ml_a_to_stdout( node );
    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t bsym_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "bsym" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_precoder:
        {
            bcore_precoder_compile( "badapt_dev_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


