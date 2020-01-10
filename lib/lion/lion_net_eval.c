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

#include "lion_net_eval.h"

/**********************************************************************************************************************/

static lion_nop* input_op_create( vd_t arg, sz_t in_idx, tp_t in_name, const lion_nop* current_nop )
{
    BLM_INIT();
    assert( *(aware_t*)arg == TYPEOF_lion_net_eval_e2e_s );
    lion_net_eval_e2e_s* o = arg;
    if( !o->param.in ) return NULL;
    if( in_idx < 0 && in_idx >= o->param.in->size ) return NULL;

    const bhvm_holor_s* h_in = o->param.in->data[ in_idx ];

    lion_nop_ar0_param_s* param = lion_nop_ar0_param_s_create();
    param->h = lion_holor_s_create();

    if( current_nop && current_nop->_ == TYPEOF_lion_nop_ar0_param_s )
    {
        const bhvm_holor_s* h_cur = &( ( lion_nop_ar0_param_s* )current_nop )->h->h;
        if( !bhvm_shape_s_is_equal( &h_cur->s, &h_in->s ) )
        {
            st_s* msg = BLM_CREATE( st_s );
            bcore_sink_a_push_fa( (bcore_sink*)msg, "Shape deviation at input holor '#<sz_t>':", in_idx );
            bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Passed input} " );
            bhvm_holor_s_brief_to_sink( h_in, (bcore_sink*)msg );
            bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Expected shape} " );
            bhvm_holor_s_brief_to_sink( h_cur, (bcore_sink*)msg );
            ERR_fa( "#<st_s*>\n", msg );
        }
        bhvm_holor_s_copy_shape_type( &param->h->h, h_cur );
    }
    else
    {
        bhvm_holor_s_copy_shape_type( &param->h->h, h_in );
    }

    BLM_RETURNV( lion_nop*, ( lion_nop* )param );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_eval_result_s* lion_net_eval_e2e_s_run( const lion_net_eval_e2e_s* o )
{
    BLM_INIT();

    bcore_sink* log = o->param.log;
    sz_t verbosity  = o->param.verbosity;
    const st_s* name = &o->param.name;
    bhvm_holor_adl_s* in = o->param.in;
    bhvm_holor_adl_s* out = o->param.out;
    f3_t max_dev = o->param.max_dev;

    if( name->size > 0 && verbosity >= 2 )
    {
        bcore_sink_a_push_fa( log, "#<sc_t>:\n", name->sc );
    }

    bcore_source* source = NULL;
    if( !o->param.src ) ERR_fa( "Source missing." );
    switch( *(aware_t*)o->param.src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = BLM_A_PUSH( bcore_file_open_source_path( ( const bcore_file_path_s* )o->param.src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = BLM_A_PUSH( bcore_source_string_s_create_from_string( ( const st_s* )o->param.src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->param.src ) );
        }
        break;
    }

    f3_t time_build_sem = 0;
    f3_t time_build_net = 0;

    /// semantic cell
    bcore_source_a_parse_fa( source, "cell " );

    /// We use a double-nested frame because the body of sem_frame->parent could be used
    lion_sem_cell_s* sem_frame = BLM_CREATE( lion_sem_cell_s );
    sem_frame->parent = BLM_A_PUSH( lion_sem_cell_s_create_frame() );

    bcore_source_point_s_set( &sem_frame->source_point, source );
    CPU_TIME_OF( lion_sem_cell_s_parse( sem_frame, source ), time_build_sem );

    /// check input channels and turn them to parameters

    /// network cell
    lion_net_cell_s* net_frame = BLM_CREATE( lion_net_cell_s );
    CPU_TIME_OF( lion_net_cell_s_from_sem_cell( net_frame, sem_frame, input_op_create, ( vd_t )o, verbosity > 5 ? log : NULL ), time_build_net );

    BFOR_EACH( i, &net_frame->excs )
    {
        lion_net_node_s* node = net_frame->excs.data[ i ];
        if( node->result )
        {
            lion_holor_s* h = node->result->h;
            if( h && h->m.htp ) bcore_sink_a_push_fa( log, "\nWARNING: Output holor '#<sz_t>' is transposed.\n", i );
        }
    }

    if( log && verbosity >= 3 )
    {
        bcore_sink_a_push_fa( log, "Cell:\n" );
        bcore_sink_a_push_fa( log, "  Entry channels . #<sz_t>\n", net_frame->encs.size );
        bcore_sink_a_push_fa( log, "  Body size ...... #<sz_t>\n", net_frame->body.size );
        bcore_sink_a_push_fa( log, "  Exit channels .. #<sz_t>\n", net_frame->excs.size );
        bcore_sink_a_push_fa( log, "\n" );

        if( verbosity >= 2 && net_frame->body.size < 1000 )
        {
            bcore_sink_a_push_fa( log, "Network Graph Structure:\n" );
            lion_net_cell_s_graph_to_sink( net_frame, log );
            bcore_sink_a_push_fa( log, "\n" );
        }
    }

    /// test copying of net_cell
    {
        lion_net_cell_s* cloned_cell = BLM_A_PUSH( lion_net_cell_s_clone( net_frame ) );
        ASSERT( lion_net_cell_s_is_consistent( cloned_cell ) );
    }

    f3_t time_push_ap = 0;
    f3_t time_push_dp = 0;

    bhvm_mcode_frame_s* mcf = BLM_CREATE( bhvm_mcode_frame_s );
    CPU_TIME_OF( lion_net_cell_s_mcode_push_ap( net_frame, mcf ), time_push_ap );
    CPU_TIME_OF( lion_net_cell_s_mcode_push_dp( net_frame, mcf ), time_push_dp );

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

    if( log && verbosity >= 5 )
    {
        bcore_sink_a_push_fa( log, "Timing (ms):\n" );
        bcore_sink_a_push_fa( log, "  Parsing ........... #<f3_t>\n", 1000 * time_build_sem );
        bcore_sink_a_push_fa( log, "  Building network .. #<f3_t>\n", 1000 * time_build_net );
        bcore_sink_a_push_fa( log, "  VM: Building 'ap' . #<f3_t>\n", 1000 * time_push_ap );
        bcore_sink_a_push_fa( log, "  VM: Building 'dp' . #<f3_t>\n", 1000 * time_push_dp );
        bcore_sink_a_push_fa( log, "\n" );

        bcore_sink_a_push_fa( log, "Tracks size:\n" );
        for( sz_t i = 0; i < sizeof( track_types ) / sizeof( tp_t ); i++ )
        {
            tp_t track_type = track_types[ i ];
            bhvm_mcode_track_s* track = bhvm_mcode_frame_s_track_get( mcf, track_type );
            if( track ) bcore_sink_a_push_fa( log, "#p20.{#<sc_t> } #<sz_t>\n", ifnameof( track_type ), track->size );
        }
        bcore_sink_a_push_fa( log, "\n" );
    }

    if( log && verbosity >= 10 )
    {
        bcore_sink_a_push_fa( log, "Microcode:\n" );
        bcore_sink_a_push_fa( log, "\n" );

        bcore_sink_a_push_fa( log, "  hbase size: #<sz_t>\n", mcf->hbase ? bhvm_mcode_hbase_s_get_size( mcf->hbase ) : 0 );
        bcore_sink_a_push_fa( log, "  Input : " );
        BFOR_EACH( i, &net_frame->encs )
        {
            lion_net_node_s* node = net_frame->encs.data[ i ];
            bcore_sink_a_push_fa( log, "#<sc_t>#<sz_t> (#<sc_t>)", ( i > 0 ) ? ", " : "", node->hidx, lion_ifnameof( node->name ) );
        }
        bcore_sink_a_push_fa( log, "\n" );

        bcore_sink_a_push_fa( log, "  Output: " );
        BFOR_EACH( i, &net_frame->excs )
        {
            lion_net_node_s* node = net_frame->excs.data[ i ];
            bcore_sink_a_push_fa( log, "#<sc_t>#<sz_t> (#<sc_t>)", ( i > 0 ) ? ", " : "", node->hidx, lion_ifnameof( node->name ) );
        }
        bcore_sink_a_push_fa( log, "\n" );
        bcore_sink_a_push_fa( log, "\n" );

        for( sz_t i = 0; i < sizeof( track_types ) / sizeof( tp_t ); i++ )
        {
            tp_t track_type = track_types[ i ];
            bhvm_mcode_track_s* track = bhvm_mcode_frame_s_track_get( mcf, track_type );
            if( track )
            {
                bcore_sink_a_push_fa( log, "#<sc_t>:\n", ifnameof( track_type ) );
                BFOR_EACH( i, track )
                {
                    bcore_sink_a_push_fa( log, "  " );
                    bhvm_vop_a_to_sink( track->data[ i ].vop, log );
                    bcore_sink_a_push_fa( log, "\n" );
                }
                bcore_sink_a_push_fa( log, "\n" );
            }
        }
        bcore_sink_a_push_fa( log, "\n" );
    }

    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_setup_ap );

    if( in )
    {
        if( in->size != net_frame->encs.size )
        {
            ERR_fa( "Number of input holors '#<sz_t>' differs from frame's entry channels '#<sz_t>'.", in->size, net_frame->encs.size );
        }
        BFOR_EACH( i, &net_frame->encs )
        {
            lion_net_node_s* node = net_frame->encs.data[ i ];
            if( node->hidx >= 0 )
            {
                bhvm_holor_s* h_in = in->data[ i ];
                bhvm_holor_s* h_hb = &mcf->hbase->holor_ads.data[ node->hidx ];
                ASSERT( bhvm_shape_s_is_equal( &h_in->s, &h_hb->s ) );
                bhvm_hop_ar1_cpy_s_f( h_in, h_hb );
            }
        }
    }

    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_ap );

    if( out )
    {
        if( out->size != net_frame->excs.size )
        {
            ERR_fa( "Number of output holors '#<sz_t>' differs from frame's exit channels '#<sz_t>'.", out->size, net_frame->excs.size );
        }
    }

    BFOR_EACH( i, &net_frame->excs )
    {
        lion_net_node_s* node = net_frame->excs.data[ i ];
        ASSERT( node->hidx >= 0 );
        bhvm_holor_s* h_hbo = &mcf->hbase->holor_ads.data[ node->hidx ];

        if( out )
        {
            bhvm_holor_s* h_out = out->data[ i ];
            bl_t shape_dev = !bhvm_shape_s_is_equal( &h_out->s, &h_hbo->s );
            bl_t value_dev = shape_dev || ( bhvm_value_s_fdev_equ( &h_out->v, &h_hbo->v ) > max_dev );
            if( shape_dev || value_dev )
            {
                st_s* msg = BLM_CREATE( st_s );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "#<sc_t> deviation at output holor '#<sz_t>':", shape_dev ? "Shape" : "Value", i );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Cell output} " );
                bhvm_holor_s_brief_to_sink( h_hbo, (bcore_sink*)msg );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Expected output} " );
                bhvm_holor_s_brief_to_sink( h_out, (bcore_sink*)msg );
                ERR_fa( "#<st_s*>\n", msg );
            }
        }
        else
        {
            bcore_sink_a_push_fa( log, "Cell out channel '#<sz_t>':\n", i );
            bhvm_holor_s_to_sink_nl( h_hbo, log );
        }
    }

    BLM_RETURNV( lion_net_eval_result_s*, NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_net_eval_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_net_eval" ) ) )
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


