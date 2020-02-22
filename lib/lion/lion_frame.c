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

#include "lion_frame.h"

/**********************************************************************************************************************/

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

void lion_frame_s_disassemble_to_sink( const lion_frame_s* o, const lion_net_cell_s* cell, bcore_sink* sink )
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
        bcore_sink_a_push_fa( sink, "  #pl3 {#<sc_t>}:", lion_ifnameof( node->name ) );
        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap enc (#<sc_t>)", lion_ifnameof( node->name ) );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp enc (#<sc_t>)", lion_ifnameof( node->name ) );
        }

        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Exit channels:\n" );
    BFOR_EACH( i, &cell->excs )
    {
        lion_net_node_s* node = cell->excs.data[ i ];
        bcore_sink_a_push_fa( sink, "  #pl3 {#<sc_t>}:", lion_ifnameof( node->name ) );
        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap exc (#<sc_t>)", lion_ifnameof( node->name ) );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp exc (#<sc_t>)", lion_ifnameof( node->name ) );
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

        bcore_sink_a_push_fa( sink, "  #pl3 {#<sc_t>}:", lion_ifnameof( ar0_adaptive->h->m.name ) );
        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap adc (#<sc_t>)", lion_ifnameof( ar0_adaptive->h->m.name ) );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp adc (#<sc_t>)", lion_ifnameof( ar0_adaptive->h->m.name ) );
        }
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Recurrent channels:\n" );
    BFOR_EACH( i, &cell->body )
    {
        lion_net_node_s* node = cell->body.data[ i ];
        if( !node->nop || node->nop->_ != TYPEOF_lion_nop_ar2_recurrent_s ) continue;
        lion_nop_ar2_recurrent_s* ar2_recurrent = ( lion_nop_ar2_recurrent_s* )node->nop;

        bcore_sink_a_push_fa( sink, "  #pl3 {#<sc_t>}:", lion_ifnameof( ar2_recurrent->name ) );

        if( node->hidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", node->hidx );
            st_s_push_fa( info_holors->data[ node->hidx ], "ap rcc (#<sc_t>)", lion_ifnameof( ar2_recurrent->name ) );
        }

        if( node->gidx >= 0 )
        {
            bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", node->gidx );
            st_s_push_fa( info_holors->data[ node->gidx ], "dp rcc (#<sc_t>)", lion_ifnameof( ar2_recurrent->name ) );
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
            st_s_push_char_n( msg, '.', sz_max( 0, 48 - msg->size ) );
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

bcore_arr_sz_s* lion_frame_push_idx( bcore_arr_sz_s** o, sz_t idx )
{
    if( !*o ) bcore_arr_sz_s_attach( o, bcore_arr_sz_s_create() );
    bcore_arr_sz_s_push( *o, idx );
    return *o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_setup_from_source( lion_frame_s* o, bcore_source* source, const bhvm_holor_s** in )
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

    o->size_en = cell->encs.size;
    o->size_ex = cell->excs.size;

    BFOR_EACH( i, &cell->encs )
    {
        lion_net_node_s* node = cell->encs.data[ i ];
        if( node->hidx >= 0 ) lion_frame_push_idx( &o->idx_ap_en, node->hidx );
        if( node->gidx >= 0 ) lion_frame_push_idx( &o->idx_dp_en, node->gidx );
    }

    BFOR_EACH( i, &cell->excs )
    {
        lion_net_node_s* node = cell->excs.data[ i ];
        if( node->hidx >= 0 ) lion_frame_push_idx( &o->idx_ap_ex, node->hidx );
        if( node->gidx >= 0 ) lion_frame_push_idx( &o->idx_dp_ex, node->gidx );
    }

    BFOR_EACH( i, &cell->body )
    {
        lion_net_node_s* node = cell->body.data[ i ];
        if( node->nop && node->nop->_ == TYPEOF_lion_nop_ar0_adaptive_s )
        {
            if( node->hidx >= 0 ) lion_frame_push_idx( &o->idx_ap_ada, node->hidx );
            if( node->gidx >= 0 ) lion_frame_push_idx( &o->idx_dp_ada, node->gidx );
        }
    }

    /// unrolling
    if( o->unrolled_cycles > 1 )
    {
        BLM_INIT();
        bhvm_mcode_track_s* ap_track = bhvm_mcode_frame_s_track_get( o->mcf, TYPEOF_track_ap );
        bhvm_mcode_sub_ads_s* sub_arr = ( ap_track->sub_arr = bhvm_mcode_sub_ads_s_create() );
        bhvm_mcode_sub_s* sub0 = bhvm_mcode_sub_ads_s_push( sub_arr );
        sub0->start = 0;
        sub0->size  = ap_track->size;

        bcore_arr_bl_s* ap_flags = BLM_CREATE( bcore_arr_bl_s );
        bcore_arr_bl_s_fill( ap_flags, o->mcf->hbase->holor_ads.size, false );

        BFOR_EACH( i, ap_track )
        {
            bhvm_vop* vop = ap_track->data[ i ].vop;
            sz_t arity = bhvm_vop_a_arity( vop );
            sz_t* index_arr = bhvm_vop_a_get_index_arr( vop );

            BFOR_SIZE( i, arity + 1 )
            {
                sz_t h_index = index_arr[ i ];
                if( !ap_flags->data[ h_index ] )
                {
                    lion_hmeta_s* hmeta = ( lion_hmeta_s* )o->mcf->hbase->hmeta_adl.data[ h_index ];
                    assert( hmeta );
                    ap_flags->data[ h_index ] = ( hmeta->active && !hmeta->adaptive );
                }
            }
        }

        bcore_arr_sz_s* ap_holors = BLM_CREATE( bcore_arr_sz_s );
        BFOR_EACH( i, ap_flags ) if( ap_flags->data[ i ] ) bcore_arr_sz_s_push( ap_holors, i );

        for( sz_t i = 1; i < o->unrolled_cycles; i++ )
        {
            BLM_INIT();

            bcore_arr_sz_s* ap_map = BLM_CREATE( bcore_arr_sz_s );
            bcore_arr_sz_s_fill( ap_map, o->mcf->hbase->holor_ads.size, -1 );

            BFOR_EACH( i, ap_holors )
            {
                sz_t index0 = ap_holors->data[ i ];
                sz_t index1 = bhvm_mcode_hbase_s_push_copy_from_index( o->mcf->hbase, index0 );
                ap_map->data[ index0 ] = index1;
            }

            bhvm_mcode_sub_s* sub = bhvm_mcode_sub_ads_s_push( sub_arr );
            sub->start = ap_track->size;
            sub->size  = sub0->size;

            BFOR_SIZE( i, sub0->size )
            {
                sz_t index = bhvm_mcode_track_s_push_copy_from_index( ap_track, i );
                bhvm_vop* vop = ap_track->data[ index ].vop;
                sz_t arity = bhvm_vop_a_arity( vop );
                sz_t* index_arr = bhvm_vop_a_get_index_arr( vop );
                BFOR_SIZE( i, arity + 1 ) if( ap_map->data[ index_arr[ i ] ] != -1 ) index_arr[ i ] = ap_map->data[ index_arr[ i ] ];
            }

            BLM_DOWN();
        }

        BLM_DOWN();
    }

    if( o->mcode_log ) lion_frame_s_disassemble_to_sink( o, cell, o->mcode_log );

    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_setup_ap );
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_setup_dp );

    BLM_RETURNV( lion_frame_s*, o );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_run( lion_frame_s* o, tp_t track )
{
    ASSERT( o->mcf );
    bhvm_mcode_frame_s_track_run( o->mcf, track );
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_run_ap( lion_frame_s* o, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    ASSERT( o->mcf );

    for( sz_t i = 0; i < o->size_en; i++ )
    {
        bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_ap_en->data[ i + o->unroll_cycle * o->size_en ] ];
        const bhvm_holor_s* h_i = in[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    if( o->unrolled_cycles == 1 )
    {
        bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );
    }
    else
    {
        bhvm_mcode_frame_s_track_run_isub( o->mcf, TYPEOF_track_ap, o->unroll_cycle );
    }

    if( out )
    {
        for( sz_t i = 0; i < o->size_ex; i++ )
        {
            bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_ap_ex->data[ i + o->unroll_cycle * o->size_ex ] ];
            bhvm_holor_s* h_o = out[ i ];
            ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
            if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
            bhvm_value_s_cpy( &h_m->v, &h_o->v );
        }
    }

    o->unroll_cycle = ( o->unroll_cycle + 1 ) % o->unrolled_cycles;

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_run_dp( lion_frame_s* o, const bhvm_holor_s** in, bhvm_holor_s** out )
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

    if( out )
    {
        BFOR_EACH( i, o->idx_dp_en )
        {
            bhvm_holor_s* h_m = &o->mcf->hbase->holor_ads.data[ o->idx_dp_en->data[ i ] ];
            bhvm_holor_s* h_o = out[ i ];
            ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
            if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
            bhvm_value_s_cpy( &h_m->v, &h_o->v );
        }
    }

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_run_ap_adl( lion_frame_s* o, const bhvm_holor_adl_s* in, bhvm_holor_adl_s* out )
{
    if( out && out->size != lion_frame_s_get_size_ex( o ) ) bhvm_holor_adl_s_set_size( out, lion_frame_s_get_size_ex( o ) );
    BFOR_EACH( i, out ) if( !out->data[ i ] ) out->data[ i ] = bhvm_holor_s_create();
    return lion_frame_s_run_ap( o, in ? ( const bhvm_holor_s** )in->data : NULL, out ? ( bhvm_holor_s** ) out->data : NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_run_dp_adl( lion_frame_s* o, const bhvm_holor_adl_s* in, bhvm_holor_adl_s* out )
{
    if( out && out->size != lion_frame_s_get_size_en( o ) ) bhvm_holor_adl_s_set_size( out, lion_frame_s_get_size_en( o ) );
    BFOR_EACH( i, out ) if( !out->data[ i ] ) out->data[ i ] = bhvm_holor_s_create();
    return lion_frame_s_run_dp( o, in ? ( const bhvm_holor_s** )in->data : NULL, out ? ( bhvm_holor_s** ) out->data : NULL );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    BLM_INIT();
    lion_frame_s_run_ap( BLM_A_PUSH( lion_frame_s_create_from_sc( sc, in ) ), in, out );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** in, bhvm_holor_s** out )
{
    BLM_INIT();
    lion_frame_s_run_dp( BLM_A_PUSH( lion_frame_s_create_from_sc( sc, in ) ), in, out );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_frame_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_frame" ) ) )
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


