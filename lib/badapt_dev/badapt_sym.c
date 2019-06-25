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
tp_t badapt_sym_frame_s_parse_name( badapt_sym_frame_s* o, bcore_source* source );
sc_t badapt_sym_frame_s_get_name_sc( const badapt_sym_frame_s* o, tp_t name );
badapt_sym* badapt_sym_evaluate( badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source );

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// link

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_link_s_parse( badapt_sym_link_s* o, badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source )
{
    o->name = badapt_sym_frame_s_parse_name( frame, source );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_link_s_to_sink( const badapt_sym_link_s* o, const badapt_sym_frame_s* frame, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "#<sc_t>", badapt_sym_frame_s_get_name_sc( frame, o->name ) );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// args

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_args_s_parse( badapt_sym_args_s* o, badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " (" );
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( o->size > 0 ) bcore_source_a_parse_fa( source, " ," );
        badapt_sym_link_s* link = badapt_sym_args_s_push( o );
        badapt_sym_link_s_parse( link, frame, node, source );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_args_s_to_sink( const badapt_sym_args_s* o, const badapt_sym_frame_s* frame, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "( " );
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( i > 0 ) bcore_sink_a_push_fa( sink, ", " );
        badapt_sym_link_s_to_sink( &o->data[ i ], frame, sink );
    }
    bcore_sink_a_push_fa( sink, " )" );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// node

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_node_s_parse( badapt_sym_node_s* o, badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source )
{
    // <name > = ( <args_in> ) => ( <args_out> ) { <body> }
    o->name = badapt_sym_frame_s_parse_name( frame, source );
    bcore_source_a_parse_fa( source, " = " );
    badapt_sym_args_s_parse( &o->args_in, frame, node, source );
    bcore_source_a_parse_fa( source, " => " );
    badapt_sym_args_s_parse( &o->args_out, frame, node, source );
    bcore_source_a_parse_fa( source, " {" );
    if( bcore_source_a_parse_bl_fa( source, " #?'mutor'" ) )
    {
        tp_t mutor_type = badapt_sym_frame_s_parse_name( frame, source );

        while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
        {
            badapt_sym_mutor_s* mutor = ( badapt_sym_mutor_s* )badapt_sym_items_s_push_t( &o->body, TYPEOF_badapt_sym_mutor_s );
            mutor->name = badapt_sym_frame_s_parse_name( frame, source );
            mutor->type = mutor_type;
            bcore_source_a_parse_fa( source, " = " );
            while( !bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
            {
                badapt_sym_dim_s* dim = badapt_sym_dims_s_push( &mutor->dims );
                bcore_source_a_parse_fa( source, " [" );
                dim->link.target = bcore_fork( badapt_sym_evaluate( frame, o, source ) );
                bcore_source_a_parse_fa( source, " ]" );
            }
        }
    }
    bcore_source_a_parse_fa( source, " }" );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t badapt_sym_frame_s_parse_name( badapt_sym_frame_s* o, bcore_source* source )
{
    st_s* st_name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", st_name );
    if( st_name->size == 0 ) bcore_source_a_parse_err_fa( source, "name expected" );
    return bcore_hmap_name_s_set_st_d( &o->hmap_name, st_name );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_node_s_to_sink( const badapt_sym_node_s* o, const badapt_sym_frame_s* frame, bcore_sink* sink )
{
    bcore_sink_a_push_fa( sink, "node #<sc_t> = ", badapt_sym_frame_s_get_name_sc( frame, o->name ) );
    badapt_sym_args_s_to_sink( &o->args_in, frame, sink );
    bcore_sink_a_push_fa( sink, " => " );
    badapt_sym_args_s_to_sink( &o->args_out, frame, sink );
    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "{\n" );
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        badapt_sym_a_to_sink( o->body.data[ i ], frame, sink );
    }
    bcore_sink_a_push_fa( sink, "}\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// frame

// ---------------------------------------------------------------------------------------------------------------------

sc_t badapt_sym_frame_s_get_name_sc( const badapt_sym_frame_s* o, tp_t name )
{
    st_s* st = bcore_hmap_name_s_get( &o->hmap_name, name );
    return st ? st->sc : NULL;
}

// ---------------------------------------------------------------------------------------------------------------------


void badapt_sym_frame_s_parse( badapt_sym_frame_s* o, badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source )
{
    if( bcore_source_a_parse_bl_fa( source, " #?'node'" ) )
    {
        badapt_sym_node_s_parse( &o->root, o, NULL, source );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_frame_s_to_sink( const badapt_sym_frame_s* o, const badapt_sym_frame_s* frame, bcore_sink* sink )
{
    badapt_sym_node_s_to_sink( &o->root, o, sink );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//badapt_sym

// ---------------------------------------------------------------------------------------------------------------------

badapt_sym* badapt_sym_evaluate( badapt_sym_frame_s* frame, const badapt_sym_node_s* node, bcore_source* source )
{

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void badapt_sym_test( void )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_sym_frame_s, frame );

    st_s text = st_weak_sc
    (
        "node layer = ( dim_y, x ) => ( y )"
        "{"
            "mutor adaptive w = [ dim_y ][ dimof( x ) ]#, b = [ dim_y ]#;"
            "y -> ( w * x ) + b;"
        "};"
    );

    badapt_sym_frame_s_parse( frame, frame, NULL, ( bcore_source* )&text );

    badapt_sym_frame_s_to_sink( frame, NULL, BCORE_STDOUT );

//    bcore_txt_ml_a_to_stdout( frame );

    bcore_txt_ml_transfer_test( sr_awc( frame ) );
    bcore_bin_ml_transfer_test( sr_awc( frame ) );

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


