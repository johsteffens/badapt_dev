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
#include "badapt_sym.h"

/**********************************************************************************************************************/
/// badapt_sym

// forwards
static tp_t frame_s_parse_name(            badapt_sym_frame_s* o, bcore_source* source );
static tp_t frame_s_set_name_sc(           badapt_sym_frame_s* o, sc_t name );
static sc_t frame_s_get_name_sc(     const badapt_sym_frame_s* o, tp_t name );
static badapt_sym_link_s* node_s_evaluate( badapt_sym_node_s*  o, bcore_source* source );


/**********************************************************************************************************************/
/// trace_to_sink

static void link_s_trace_to_sink(      const badapt_sym_link_s* o,      sz_t indent, bcore_sink* sink );
static void operator0_s_trace_to_sink( const badapt_sym_operator0_s* o, sz_t indent, bcore_sink* sink );
static void operator1_s_trace_to_sink( const badapt_sym_operator1_s* o, sz_t indent, bcore_sink* sink );
static void operator2_s_trace_to_sink( const badapt_sym_operator2_s* o, sz_t indent, bcore_sink* sink );
static void mutor_s_trace_to_sink(     const badapt_sym_mutor_s* o,     sz_t indent, bcore_sink* sink );

// ---------------------------------------------------------------------------------------------------------------------

static void link_s_trace_to_sink( const badapt_sym_link_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(l)" );
    if( o->name ) bcore_sink_a_push_fa( sink, "#<sc_t>", frame_s_get_name_sc( o->frame, o->name ) );
    if( o->target )
    {
        bcore_sink_a_push_fa( sink, "->" );
        switch( *(aware_t*)o->target )
        {
            case TYPEOF_badapt_sym_link_s:      link_s_trace_to_sink( ( badapt_sym_link_s* )o->target,           indent, sink ); break;
            case TYPEOF_badapt_sym_operator0_s: operator0_s_trace_to_sink( ( badapt_sym_operator0_s* )o->target, indent, sink ); break;
            case TYPEOF_badapt_sym_operator1_s: operator1_s_trace_to_sink( ( badapt_sym_operator1_s* )o->target, indent, sink ); break;
            case TYPEOF_badapt_sym_operator2_s: operator2_s_trace_to_sink( ( badapt_sym_operator2_s* )o->target, indent, sink ); break;
            case TYPEOF_badapt_sym_mutor_s:     mutor_s_trace_to_sink( ( badapt_sym_mutor_s* )o->target,         indent, sink ); break;
            default: bcore_sink_a_push_fa( sink, "(#<sc_t>)", ifnameof( *(aware_t*)o->target ) ); break;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void operator0_s_trace_to_sink( const badapt_sym_operator0_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(op0)" );
    if( o->operator )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( *(aware_t*)o->operator ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void operator1_s_trace_to_sink( const badapt_sym_operator1_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(op1)" );
    if( o->operator )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( *(aware_t*)o->operator ) );
    }

    indent += 4;
    bcore_sink_a_push_fa( sink, "\n#rn{ }", indent );
    link_s_trace_to_sink( &o->link, indent, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

static void operator2_s_trace_to_sink( const badapt_sym_operator2_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(op2)" );
    if( o->operator )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>", ifnameof( *(aware_t*)o->operator ) );
    }

    indent += 4;
    bcore_sink_a_push_fa( sink, "\n#rn{ }(1)->", indent );
    link_s_trace_to_sink( &o->link1, indent, sink );
    bcore_sink_a_push_fa( sink, "\n#rn{ }(2)->", indent );
    link_s_trace_to_sink( &o->link2, indent, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

static void mutor_s_trace_to_sink( const badapt_sym_mutor_s* o, sz_t indent, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "(mutor)#<sc_t>", frame_s_get_name_sc( o->frame, o->name ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// link

// ---------------------------------------------------------------------------------------------------------------------

static void link_s_parse( badapt_sym_link_s* o, bcore_source* source )
{
    o->name = frame_s_parse_name( o->frame, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static void link_s_to_sink( const badapt_sym_link_s* o, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#<sc_t>", frame_s_get_name_sc( o->frame, o->name ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// args

// ---------------------------------------------------------------------------------------------------------------------

static void args_s_parse( badapt_sym_args_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( o->size > 0 ) bcore_source_a_parse_fa( source, " ," );
        badapt_sym_link_s* link = badapt_sym_args_s_push( o );
        link->frame = o->frame;
        link_s_parse( link, source );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void args_s_to_sink( const badapt_sym_args_s* o, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "( " );
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( i > 0 ) bcore_sink_a_push_fa( sink, ", " );
        link_s_to_sink( &o->data[ i ], sink );
    }
    bcore_sink_a_push_fa( sink, " )" );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// node

// ---------------------------------------------------------------------------------------------------------------------

static tp_t frame_s_parse_name( badapt_sym_frame_s* o, bcore_source* source );

// ---------------------------------------------------------------------------------------------------------------------

static void node_s_to_sink( const badapt_sym_node_s* o, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "node #<sc_t> = ", frame_s_get_name_sc( o->frame, o->name ) );
    args_s_to_sink( &o->args_in, sink );
    bcore_sink_a_push_fa( sink, " => " );
    args_s_to_sink( &o->args_out, sink );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "{\n" );
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        if( *(aware_t*)o->body.data[ i ] == TYPEOF_badapt_sym_link_s )
        {
            link_s_to_sink( ( badapt_sym_link_s* )o->body.data[ i ], sink );
        }
        else if( *(aware_t*)o->body.data[ i ] == TYPEOF_badapt_sym_node_s )
        {
            node_s_to_sink( ( badapt_sym_node_s* )o->body.data[ i ], sink );
        }
    }
    bcore_sink_a_push_fa( sink, "}\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

static badapt_sym_link_s* node_s_get_arg_in( const badapt_sym_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->args_in.size; i++ )
    {
        if( o->args_in.data[ i ].name == name ) return &o->args_in.data[ i ];
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

static badapt_sym_link_s* node_s_get_arg_out( const badapt_sym_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->args_out.size; i++ )
    {
        if( o->args_out.data[ i ].name == name ) return &o->args_out.data[ i ];
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

static badapt_sym_node_s* node_s_get_node( const badapt_sym_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        if( *(aware_t*)o->body.data[ i ] == TYPEOF_badapt_sym_node_s )
        {
            badapt_sym_node_s* node = ( badapt_sym_node_s* )o->body.data[ i ];
            if( node->name == name ) return node;
        }
    }
    if( o->parent_node ) return node_s_get_node( o->parent_node, name );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

static badapt_sym_link_s* node_s_get_link_from_body( const badapt_sym_node_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        if( *(aware_t*)o->body.data[ i ] == TYPEOF_badapt_sym_link_s )
        {
            badapt_sym_link_s* link = ( badapt_sym_link_s* )o->body.data[ i ];
            if( link->name == name ) return link;
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

static sz_t node_s_free_args_in( const badapt_sym_node_s* o )
{
    sz_t count = 0;
    for( sz_t i = 0; i < o->args_in.size; i++ ) count += ( o->args_in.data[ i ].target == NULL );
    return count;
}

// ---------------------------------------------------------------------------------------------------------------------

static badapt_sym_link_s* node_s_get_first_free_arg_in( const badapt_sym_node_s* o )
{
    for( sz_t i = 0; i < o->args_in.size; i++ )
    {
        if( o->args_in.data[ i ].target == NULL ) return &o->args_in.data[ i ];
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_create_node( badapt_sym_node_s* o )
{
    badapt_sym_node_s* node = ( badapt_sym_node_s* )badapt_sym_items_s_push_t( &o->body, TYPEOF_badapt_sym_node_s );
    node->frame = o->frame;
    node->parent_node = o;
    node->args_in.frame = o->frame;
    node->args_out.frame = o->frame;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_link_s* node_s_create_link_on_body( badapt_sym_node_s* o )
{
    badapt_sym_link_s* link = ( badapt_sym_link_s* )badapt_sym_items_s_push_t( &o->body, TYPEOF_badapt_sym_link_s );
    link->frame = o->frame;
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_link_s* node_s_push_link_on_args_in( badapt_sym_node_s* o )
{
    badapt_sym_link_s* link = badapt_sym_args_s_push( &o->args_in );
    link->frame = o->frame;
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_link_s* node_s_push_link_on_args_out( badapt_sym_node_s* o )
{
    badapt_sym_link_s* link = badapt_sym_args_s_push( &o->args_out );
    link->frame = o->frame;
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_mutor_s* node_s_create_mutor( badapt_sym_node_s* o )
{
    badapt_sym_mutor_s* mutor = ( badapt_sym_mutor_s* )badapt_sym_items_s_push_t( &o->body, TYPEOF_badapt_sym_mutor_s );
    mutor->frame = o->frame;
    return mutor;
}


// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_create_scalar_literal( badapt_sym_node_s* o, f3_t val )
{
    badapt_sym_node_s* node = node_s_create_node( o );
    badapt_sym_link_s* link = node_s_push_link_on_args_out( node );
    link->name = frame_s_set_name_sc( o->frame, "scalar-out" );
    badapt_operator0_scalar_s* scalar = badapt_operator0_scalar_s_create();
    scalar->value = val;
    badapt_sym_operator0_s* sym_operator = badapt_sym_operator0_s_create();
    sym_operator->operator = ( badapt_operator0* )scalar;
    link->target = ( badapt_sym* )sym_operator; // no fork here
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_create_unary( badapt_sym_node_s* o, tp_t type )
{
    badapt_sym_node_s* node = node_s_create_node( o );
    badapt_sym_link_s* node_link_in  = node_s_push_link_on_args_in(  node );
    badapt_sym_link_s* node_link_out = node_s_push_link_on_args_out( node );

    node_link_in ->name = frame_s_set_name_sc( o->frame, "unary-in" );
    node_link_out->name = frame_s_set_name_sc( o->frame, "unary-out" );

    badapt_sym_operator1_s* sym_operator = badapt_sym_operator1_s_create();
    sym_operator->link.target = bcore_fork( node_link_in );
    sym_operator->operator = badapt_operator1_t_create( type );
    node_link_out->target = ( badapt_sym* )sym_operator; // no fork here
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_create_unary_sc( badapt_sym_node_s* o, sc_t name )
{
    st_s* operator_name = st_s_create_fa( "badapt_operator1_#<sc_t>_s", name );
    tp_t type = entypeof( operator_name->sc );
    st_s_discard( operator_name );
    badapt_sym_node_s* node = node_s_create_unary( o, type );
    node->name = frame_s_set_name_sc( o->frame, name );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_create_binary( badapt_sym_node_s* o, tp_t type )
{
    badapt_sym_node_s* node = node_s_create_node( o );
    badapt_sym_link_s* node_link_in1 = node_s_push_link_on_args_in(  node );
    badapt_sym_link_s* node_link_in2 = node_s_push_link_on_args_in(  node );
    badapt_sym_link_s* node_link_out = node_s_push_link_on_args_out( node );

    node_link_in1->name = frame_s_set_name_sc( o->frame, "binary-in1" );
    node_link_in1->name = frame_s_set_name_sc( o->frame, "binary-in2" );
    node_link_out->name = frame_s_set_name_sc( o->frame, "binary-out" );

    badapt_sym_operator2_s* sym_operator = badapt_sym_operator2_s_create();
    sym_operator->link1.target = bcore_fork( node_link_in1 );
    sym_operator->link2.target = bcore_fork( node_link_in2 );
    sym_operator->operator = badapt_operator2_t_create( type );

    node_link_out->target = ( badapt_sym* )sym_operator; // no fork here
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_create_binary_sc( badapt_sym_node_s* o, sc_t name )
{
    st_s* operator_name = st_s_create_fa( "badapt_operator2_#<sc_t>_s", name );
    tp_t type = entypeof( operator_name->sc );
    st_s_discard( operator_name );
    badapt_sym_node_s* node = node_s_create_binary( o, type );
    node->name = frame_s_set_name_sc( o->frame, name );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

static void node_s_parse(      badapt_sym_node_s* o, bcore_source* source );
static void node_s_parse_body( badapt_sym_node_s* o, bcore_source* source )
{
    BCORE_LIFE_INIT();
    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #=?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'node'" ) )
        {
            bl_t first = true;
            while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
            {
                if( !first ) bcore_source_a_parse_fa( source, " ," );
                badapt_sym_node_s* node = node_s_create_node( o );
                node_s_parse( node, source );
                first = false;
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'mutor'" ) )
        {
            tp_t mutor_type = frame_s_parse_name( o->frame, source );
            bl_t first = true;
            while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
            {
                if( !first ) bcore_source_a_parse_fa( source, " ," );
                badapt_sym_mutor_s* mutor = node_s_create_mutor( o );
                mutor->name = frame_s_parse_name( o->frame, source );
                mutor->type = mutor_type;
                bcore_source_a_parse_fa( source, " = " );
                while( !bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
                {
                    badapt_sym_dim_s* dim = badapt_sym_dims_s_push( &mutor->dims );
                    bcore_source_a_parse_fa( source, " [" );
                    dim->link.target = bcore_fork( node_s_evaluate( o, source ) );
                    bcore_source_a_parse_fa( source, " ]" );
                }

                badapt_sym_link_s* link = node_s_create_link_on_body( o );
                link->name = mutor->name;
                link->target = bcore_fork( mutor );

                first = false;
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'link'" ) )
        {
            bl_t first = true;
            while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
            {
                if( !first ) bcore_source_a_parse_fa( source, " ," );
                badapt_sym_link_s* link = node_s_create_link_on_body( o );
                link->name = frame_s_parse_name( o->frame, source );
                bcore_source_a_parse_fa( source, " -> " );
                link->target = bcore_fork( node_s_evaluate( o, source ) );
                first = false;
            }
        }
        else
        {
            BCORE_LIFE_CREATE( st_s, name );
            bcore_source_a_parse_fa( source, " #name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
            tp_t tp_name = typeof( name->sc );
            badapt_sym_link_s* link = NULL;
            if( ( link = node_s_get_arg_out( o, tp_name ) ) )
            {
                bcore_source_a_parse_fa( source, " -> " );
                link->target = bcore_fork( node_s_evaluate( o, source ) );
                bcore_source_a_parse_fa( source, ";" );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' not found or not assignable.", name->sc );
            }
        }
    }
    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static void node_s_parse( badapt_sym_node_s* o, bcore_source* source )
{
    // <name > = ( <args_in> ) => ( <args_out> ) { <body> }
    o->name = frame_s_parse_name( o->frame, source );
    bcore_source_a_parse_fa( source, " = " );
    args_s_parse( &o->args_in, source );
    bcore_source_a_parse_fa( source, " => " );
    args_s_parse( &o->args_out, source );

    bcore_source_a_parse_fa( source, " {" );
    node_s_parse_body( o, source );
    bcore_source_a_parse_fa( source, " }" );
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym_node_s* node_s_copy_node( badapt_sym_node_s* o, badapt_sym_node_s* node )
{
    badapt_sym_items_s_push_c( &o->body, ( badapt_sym* )node );
    badapt_sym_node_s* ret = ( badapt_sym_node_s* )o->body.data[ o->body.size - 1 ];
    ret->parent_node = o;
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t node_s_is_unary_operator( const badapt_sym_node_s* o )
{
    return ( node_s_free_args_in( o ) == 2 ) && ( o->args_out.size == 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t node_s_is_binary_operator( const badapt_sym_node_s* o )
{
    return ( node_s_free_args_in( o ) == 2 ) && ( o->args_out.size == 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

void node_s_stack_evaluate( badapt_sym_node_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( st_s, name );

    badapt_sym_frame_s* frame = o->frame;

    while( !bcore_source_a_eos( source ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?([0]==')'||[0]==']'||[0]==','||[0]==';')" ) ) break;

        // identifier
        if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            tp_t tp_name = typeof( name->sc );
            vd_t item = NULL;
            if( ( item = node_s_get_arg_in( o, tp_name ) ) )
            {
                bcore_msg_fa( "got in link '#<sc_t>'\n", frame_s_get_name_sc( o->frame, ( ( badapt_sym_link_s* )item )->name ) );
                bcore_arr_vd_s_push( stack, item );
            }
            else if( ( item = node_s_get_link_from_body( o, tp_name ) ) )
            {
                bcore_msg_fa( "got body link '#<sc_t>'\n", frame_s_get_name_sc( o->frame, ( ( badapt_sym_link_s* )item )->name ) );
                bcore_arr_vd_s_push( stack, item );
            }
            else if( ( item = node_s_get_node( o, tp_name ) ) )
            {
                bcore_msg_fa( "got node '#<sc_t>'\n", frame_s_get_name_sc( o->frame, ( ( badapt_sym_node_s* )item )->name ) );
                badapt_sym_node_s* node = node_s_copy_node( o, item );

                // arguments
                bcore_source_a_parse_fa( source, " (" );
                bl_t first = true;
                while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
                {
                    if( !first ) bcore_source_a_parse_fa( source, " ," );

                    // input arguments
                    badapt_sym_link_s* link = node_s_get_first_free_arg_in( node );
                    if( !link ) bcore_source_a_parse_err_fa( source, "node '#<sc_t>': All arguments have been assigned.", name->sc, frame_s_get_name_sc( frame, node->name ) );
                    link->target = bcore_fork( node_s_evaluate( o, source ) );
                    first = false;
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
            badapt_sym_node_s* node = node_s_create_scalar_literal( o, val );
            bcore_arr_vd_s_push( stack, node );
        }

        // block
        else if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
        {
            bcore_arr_vd_s_push( stack, node_s_evaluate( o, source ) );
            bcore_source_a_parse_fa( source, " )" );
        }

        // binary operators
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]=='*'||[0]=='+'||[0]=='-'||[0]=='<')" ) )
        {
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Left operand missing." );

            vd_t l_item = bcore_arr_vd_s_pop( stack );

            badapt_sym_node_s* node = NULL;

            if( bcore_source_a_parse_bl_fa( source, "#?'+'" ) )
            {
                node = node_s_get_node( o, typeof( "__plus" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'-'" ) )
            {
                node = node_s_get_node( o, typeof( "__minus" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'*'" ) )
            {
                node = node_s_get_node( o, typeof( "__mul" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'<*>'" ) )
            {
                node = node_s_get_node( o, typeof( "__hmul" ) );
            }
            else if( bcore_source_a_parse_bl_fa( source, "#?'<'" ) )
            {
                bcore_source_a_parse_fa( source, "#until'>'>", name );
                node = node_s_get_node( o, typeof( name->sc ) );
                if( !node ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>' not found.", name->sc );
            }

            if( !node ) bcore_source_a_parse_err_fa( source, "Syntax error." );
            if( !node_s_is_binary_operator( node ) ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>' cannot be used as binary operator.", frame_s_get_name_sc( frame, node->name ) );

            node = node_s_copy_node( o, node );

            if( badapt_sym_a_is_node( l_item ) )
            {
                badapt_sym_node_s* l_node = l_item;
                if( l_node->args_out.size != 1 ) bcore_source_a_parse_err_fa( source, "Left operand needs exactly one output channel." );
                node_s_get_first_free_arg_in( node )->target = bcore_fork( &l_node->args_out.data[ 0 ] );
                bcore_msg_fa( "left node '#<sc_t>'\n", frame_s_get_name_sc( o->frame, l_node->name ) );
            }
            else if( badapt_sym_a_is_link( l_item ) )
            {
                link_s_trace_to_sink( l_item, 0, BCORE_STDOUT );
                node_s_get_first_free_arg_in( node )->target = bcore_fork( l_item );
                bcore_msg_fa( "left link '#<sc_t>'\n", frame_s_get_name_sc( o->frame, ( ( badapt_sym_link_s* )l_item )->name ) );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Invalid left operand '#<sc_t>'.", ifnameof( *(aware_t*)l_item ) );
            }

            bcore_arr_vd_s_push( stack, node );
//            link_s_trace_to_sink( &node->args_in.data[ 0 ], 0, BCORE_STDOUT );
//            bcore_msg_fa( "\n" );
            link_s_trace_to_sink( &node->args_out.data[ 0 ], 0, BCORE_STDOUT );
            bcore_msg_fa( "\npushed bin operator '#<sc_t>'\n", frame_s_get_name_sc( o->frame, node->name ) );
        }

        // output channel
        else if( bcore_source_a_parse_bl_fa( source, "#?'.'" ) )
        {
            if( stack->size == 0 )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Misplaced channel selector."
                );
            }

            vd_t l_item = bcore_arr_vd_s_pop( stack );
            if( *(aware_t*)l_item != TYPEOF_badapt_sym_node_s )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Channel selector can only be applied to a node."
                );
            }

            badapt_sym_node_s* node = ( badapt_sym_node_s* )l_item;

            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 )
            {
                bcore_source_a_parse_err_fa
                (
                    source,
                    "Identifier expected."
                );
            }
            tp_t tp_name = typeof( name->sc );

            badapt_sym_link_s* link = node_s_get_arg_out( node, tp_name );

            if( !link ) bcore_source_a_parse_err_fa( source, "Invalid channel '#<sc_t>'.", name->sc );

            bcore_arr_vd_s_push( stack, link );
        }

        /// resolve node with r_value
        if( stack->size >= 2 )
        {
            if( badapt_sym_a_is_node( stack->data[ stack->size - 2 ] ) )
            {
                vd_t r_item             = bcore_arr_vd_s_pop( stack );
                badapt_sym_node_s* node = bcore_arr_vd_s_pop( stack );

                if( node_s_free_args_in( node ) != 1 ) bcore_source_a_parse_err_fa( source, "Node '#<sc_t>' cannot be used as operator. Incorrect number of free arguments.", frame_s_get_name_sc( frame, node->name ) );

                if( badapt_sym_a_is_node( r_item ) )
                {
                    badapt_sym_node_s* r_node = r_item;
                    if( r_node->args_out.size != 1 ) bcore_source_a_parse_err_fa( source, "Right operand needs exactly one output channel." );
                    node_s_get_first_free_arg_in( node )->target = bcore_fork( &r_node->args_out.data[ 0 ] );
                }
                else if( badapt_sym_a_is_link( r_item ) )
                {
                    node_s_get_first_free_arg_in( node )->target = bcore_fork( r_item );
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Invalid right operand (#<sc_t>).", ifnameof( *(aware_t*)r_item ) );
                }

                bcore_arr_vd_s_push( stack, &node->args_out.data[ 0 ] );
            }
        }
    }

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static badapt_sym_link_s* node_s_evaluate( badapt_sym_node_s* o, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    node_s_stack_evaluate( o, stack, source );

    if( stack->size != 1 ) bcore_source_a_parse_err_fa( source, "Syntax error. (Stack size)" );

    vd_t ret = bcore_arr_vd_s_pop( stack );

    if( badapt_sym_a_is_node( ret ) )
    {
        badapt_sym_node_s* node = ret;
        if( node->args_out.size != 1 ) bcore_source_a_parse_err_fa( source, "Expression yields a node with no or more than one output channels." );
        ret = &node->args_out.data[ 0 ];
    }

    if( !badapt_sym_a_is_link( ret ) )  bcore_source_a_parse_err_fa( source, "Syntax error. (Stack object is '#<sc_t>'. Link expected.)", ifnameof( *(aware_t*)ret ) );

//    bcore_msg_fa( "\n" );
//    link_s_trace_to_sink( ret, 0, BCORE_STDOUT );
//    bcore_msg_fa( "\n-----------------------------\n" );
    BCORE_LIFE_RETURN( ret );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// frame

// ---------------------------------------------------------------------------------------------------------------------

static tp_t frame_s_parse_name( badapt_sym_frame_s* o, bcore_source* source )
{
    st_s* st_name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", st_name );
    if( st_name->size == 0 ) bcore_source_a_parse_err_fa( source, "name expected" );
    return bcore_hmap_name_s_set_st_d( &o->hmap_name, st_name );
}

// ---------------------------------------------------------------------------------------------------------------------

static tp_t frame_s_set_name_sc( badapt_sym_frame_s* o, sc_t name )
{
    return bcore_hmap_name_s_set_sc( &o->hmap_name, name );
}

// ---------------------------------------------------------------------------------------------------------------------

static sc_t frame_s_get_name_sc( const badapt_sym_frame_s* o, tp_t name )
{
    st_s* st = bcore_hmap_name_s_get( &o->hmap_name, name );
    return st ? st->sc : NULL;
}

// ---------------------------------------------------------------------------------------------------------------------


static void frame_s_parse( badapt_sym_frame_s* o, badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source )
{
    bcore_source_a_parse_fa( source, "node " );
    node_s_parse( &o->root, source );
}

// ---------------------------------------------------------------------------------------------------------------------

static void frame_s_to_sink( const badapt_sym_frame_s* o, const badapt_sym_frame_s* frame, bcore_sink* sink )
{
    node_s_to_sink( &o->root, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_frame_s_setup( badapt_sym_frame_s* o )
{
    o->root.frame          = o;
    o->root.args_in.frame  = o;
    o->root.args_out.frame = o;

    node_s_create_unary_sc( &o->root, "dimof" );
    node_s_create_unary_sc( &o->root, "linear" );
    node_s_create_unary_sc( &o->root, "tanh" );
    node_s_create_binary_sc( &o->root, "__mul" );
    node_s_create_binary_sc( &o->root, "__hmul" );
    node_s_create_binary_sc( &o->root, "__plus" );
    node_s_create_binary_sc( &o->root, "__minus" );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//badapt_sym

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_test( void )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_sym_frame_s, frame );

    st_s text = st_weak_sc
    (
        "node root = ( root_x ) => ( root_y )"
        "{"
            "node layer = ( dim_y, x ) => ( y )"
            "{"
                "mutor adaptive w = [ dim_y ][ dimof( x ) ]#, b = [ dim_y ]#;"
                "y -> ( w * x ) + b;"
            "};"

            "root_y -> layer( 10, root_x );"
        "};"
    );

    frame_s_parse( frame, frame, NULL, ( bcore_source* )&text );
    frame_s_to_sink( frame, NULL, BCORE_STDOUT );

    link_s_trace_to_sink( &frame->root.args_out.data[ 0 ], 0, BCORE_STDOUT );

//    bcore_txt_ml_a_to_stdout( frame );

//    bcore_txt_ml_transfer_test( sr_awc( frame ) );
//    bcore_bin_ml_transfer_test( sr_awc( frame ) );

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t badapt_sym_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_sym" ) ) )
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


