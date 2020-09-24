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

#include "opal_frame.h"

/**********************************************************************************************************************/
/// frame

// ---------------------------------------------------------------------------------------------------------------------

static st_s* hmeta_get_global_name_st( bhvm_mcode_hmeta* hmeta, const opal_context* context, st_s* st )
{
    st_s_clear( st );
    if( hmeta && hmeta->_ == TYPEOF_opal_holor_meta_s )
    {
        opal_holor_meta_s* holor_meta = ( opal_holor_meta_s* )hmeta;
        if( holor_meta->sem_id && *( aware_t* )holor_meta->sem_id == TYPEOF_opal_sem_id_s )
        {
            opal_sem_id_s_to_string( ( opal_sem_id_s* )holor_meta->sem_id, context, st );
        }
    }
    return st;
}

// ---------------------------------------------------------------------------------------------------------------------

static void opal_frame_s_disassemble_hbase_to_sink( const opal_frame_s* o, const bhvm_mcode_hbase_s* hbase, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    st_s* st_buf = BLM_CREATE( st_s );
    sz_t hname_length = 0;
    sz_t hbrief_length = 0;

    BFOR_EACH( i, &hbase->holor_adl )
    {
        BLM_INIT();
        bhvm_holor_s* h = hbase->holor_adl.data[ i ];
        bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ i ];
        //sc_t sc_name = opal_context_a_ifnameof( o->context, bhvm_mcode_hmeta_a_get_name( hmeta ) );
        sc_t sc_name = hmeta_get_global_name_st( hmeta, o->context, st_buf )->sc;
        hname_length = sz_max( hname_length, bcore_strlen( sc_name ) );

        st_s* st = BLM_CREATE( st_s );
        bhvm_holor_s_compact_to_sink( h, 12, ( bcore_sink* )st );
        hbrief_length = sz_max( hbrief_length, st->size );

        BLM_DOWN();
    }

    BFOR_EACH( i, &hbase->holor_adl )
    {
        BLM_INIT();
        st_s* msg = BLM_CREATE( st_s );
        bhvm_holor_s* h = hbase->holor_adl.data[ i ];
        bhvm_mcode_hmeta* hmeta  = hbase->hmeta_adl.data[ i ];

        tp_t pclass = bhvm_mcode_hmeta_a_get_pclass( hmeta );
        //sc_t sc_name = opal_context_a_ifnameof( o->context, bhvm_mcode_hmeta_a_get_name( hmeta ) );
        sc_t sc_name = hmeta_get_global_name_st( hmeta, o->context, st_buf )->sc;

        st_s_push_fa( msg, "#rn{ }#pl3 {#<sz_t>}", indent, i );

        bhvm_mcode_node_s* mnode = bhvm_mcode_hmeta_a_get_node( hmeta );
        ASSERT( mnode );

        if(      pclass == TYPEOF_pclass_ax0 ) st_s_push_fa( msg, " ax0 #pl5 {[#<sz_t>]}", mnode->ax0 );
        else if( pclass == TYPEOF_pclass_ax1 ) st_s_push_fa( msg, " ax1 #pl5 {[#<sz_t>]}", mnode->ax0 );
        else if( pclass == TYPEOF_pclass_ag0 ) st_s_push_fa( msg, " ag0 #pl5 {[#<sz_t>]}", mnode->ax0 );
        else if( pclass == TYPEOF_pclass_ag1 ) st_s_push_fa( msg, " ag1 #pl5 {[#<sz_t>]}", mnode->ax0 );

        //st_s_push_fa( msg, " #rn{.} ", sz_max( 0, 22 - msg->size ) );

        st_s_push_fa( msg, " #pn'.'{#<sc_t> }", hname_length + 1, sc_name );
        if     ( mnode->adaptive  )                      st_s_push_fa( msg, " adaptive" );
        else if( mnode->cyclic )                         st_s_push_fa( msg, " cyclic  " );
        else if( mnode->param )                          st_s_push_fa( msg, " param   " );
        else if( bhvm_mcode_hmeta_a_is_active( hmeta ) ) st_s_push_fa( msg, " active  " );
        else                                             st_s_push_fa( msg, " const   " );

        st_s* st = BLM_CREATE( st_s );
        bhvm_holor_s_compact_to_sink( h, 12, ( bcore_sink* )st );

        st_s_push_fa( msg, " #pn' '{#<st_s*>} ", hbrief_length, st );

        const bcore_inst* custom = bhvm_mcode_hmeta_a_get_custom( hmeta );
        if( custom && *(aware_t*)custom == TYPEOF_opal_frame_custom_hmeta_s )
        {
            opal_frame_custom_hmeta_s* custom_hmeta = ( opal_frame_custom_hmeta_s* )custom;
            st_s_push_fa( msg, " ur_slot #pl2 {#<sz_t>}", custom_hmeta->ur_slot );
        }

        bcore_sink_a_push_fa( sink, "#<st_s*>\n", msg );


        BLM_DOWN();
    }
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static void opal_frame_s_disassemble_hidx_to_sink( const opal_frame_s* o, const bhvm_mcode_hbase_s* hbase, const bcore_arr_sz_s* hidx, sz_t indent, bcore_sink* sink )
{
    BLM_INIT();
    st_s* st_buf = BLM_CREATE( st_s );
    sz_t hname_length = 0;

    BFOR_EACH( i, hidx )
    {
        BLM_INIT();
        sz_t idx_ap = hidx->data[ i ];
        bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ idx_ap ];
        hname_length = sz_max( hname_length, hmeta_get_global_name_st( hmeta, o->context, st_buf )->size );
        BLM_DOWN();
    }

    BFOR_EACH( i, hidx )
    {
        sz_t idx_ap = hidx->data[ i ];
        bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ idx_ap ];
        assert( hmeta );
        bcore_sink_a_push_fa( sink, "#rn{ }#pn'.'{#<sc_t> } :", indent, hname_length + 1, hmeta_get_global_name_st( hmeta, o->context, st_buf )->sc );

        if( idx_ap >= 0 ) bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", idx_ap );

        bhvm_mcode_node_s* mnode = bhvm_mcode_hmeta_a_get_node( hmeta );
        if( mnode )
        {
            sz_t idx_dp = mnode->ag0;
            if( idx_dp >= 0 ) bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", idx_dp );
        }

        bcore_sink_a_push_fa( sink, "\n" );
    }
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static void opal_frame_s_disassemble_track_to_sink( const opal_frame_s* o, const bhvm_mcode_track_s* track, sz_t indent, bcore_sink* sink )
{
    if( !track ) return;
    BFOR_EACH( i, track )
    {
        bcore_sink_a_push_fa( sink, "#rn{ }", indent );
        bhvm_vop* vop = track->data[ i ].vop;
        bhvm_vop_a_to_sink( vop, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_s_disassemble_to_sink( const opal_frame_s* o, bcore_sink* sink )
{
    BLM_INIT();
    tp_t track_types [] =
    {
        TYPEOF_track_ap,
        TYPEOF_track_ap_cyclic_update,
        TYPEOF_track_dp,
        TYPEOF_track_dp_cyclic_zero_grad,
        TYPEOF_track_ap_setup,
        TYPEOF_track_dp_setup,
        TYPEOF_track_ap_shelve,
        TYPEOF_track_dp_shelve,
        TYPEOF_track_dp_adaptive_zero_grad
    };

    bhvm_mcode_frame_s* mcf = o->mcf;
    bhvm_mcode_hbase_s* hbase = mcf->hbase;

    bcore_sink_a_push_fa( sink, "Holorbase size: #<sz_t>\n", hbase ? bhvm_mcode_hbase_s_get_size( hbase ) : 0 );
    bcore_sink_a_push_fa( sink, "Entry channels:\n" );
    opal_frame_s_disassemble_hidx_to_sink( o, hbase, o->hidx_en.arr, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "Exit channels:\n" );
    opal_frame_s_disassemble_hidx_to_sink( o, hbase, o->hidx_ex.arr, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    if( opal_frame_hidx_s_get_size( &o->hidx_ada ) > 0 )
    {
        bcore_sink_a_push_fa( sink, "Adaptive channels:\n" );
        opal_frame_s_disassemble_hidx_to_sink( o, hbase, o->hidx_ada.arr, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }
    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "Holorbase:\n" );
    opal_frame_s_disassemble_hbase_to_sink( o, hbase, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    for( sz_t i = 0; i < sizeof( track_types ) / sizeof( tp_t ); i++ )
    {
        tp_t track_type = track_types[ i ];
        bhvm_mcode_track_s* track = bhvm_mcode_frame_s_track_get( mcf, track_type );
        if( track )
        {
            bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track_type ) );
            opal_frame_s_disassemble_track_to_sink( o, track, 2, sink );
            bcore_sink_a_push_fa( sink, "\n" );
        }
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

bcore_arr_sz_s* opal_frame_push_idx( bcore_arr_sz_s** o, sz_t idx )
{
    if( !*o ) bcore_arr_sz_s_attach( o, bcore_arr_sz_s_create() );
    bcore_arr_sz_s_push( *o, idx );
    return *o;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_s_check_integrity( const opal_frame_s* o )
{
    assert( o->context );
    assert( o->mcf );
    bhvm_mcode_frame_s_check_integrity( o->mcf );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_s* opal_frame_s_setup_from_source( opal_frame_s* o, bcore_source* source, const bhvm_holor_s** en, sz_t size_en )
{
    BLM_INIT();

    opal_net_cell_s* net_cell = BLM_CREATE( opal_net_cell_s );
    opal_net_builder_s* net_builder = BLM_CREATE( opal_net_builder_s );

    opal_net_builder_s_fork_log( net_builder, o->log );
    opal_net_builder_s_fork_input_holors( net_builder, en, size_en );
    opal_net_builder_s_build_from_source( net_builder, net_cell, source );

    opal_frame_hidx_s_clear( &o->hidx_en );
    opal_frame_hidx_s_clear( &o->hidx_ex );
    opal_frame_hidx_s_clear( &o->hidx_ada );

    opal_context_a_attach( &o->context, bcore_fork( net_cell->context ) );
    bhvm_mcode_frame_s_attach( &o->mcf, bhvm_mcode_frame_s_create() );

    opal_net_cell_s_mcode_push_ap( net_cell, o->mcf );
    opal_net_cell_s_mcode_push_dp( net_cell, o->mcf, true );

    o->size_en = net_cell->encs.size;
    o->size_ex = net_cell->excs.size;

    BFOR_EACH( i, &net_cell->encs )
    {
        opal_net_node_s* node = net_cell->encs.data[ i ];

        /** An entry node without mnode does not actively contribute to the output of the cell.
         *  We therefore construct an mnode formally to provide a holor for the input channel
         *  with the necessary setup and shelve routines.
         */
        if( !node->mnode ) opal_net_node_s_isolated_mcode_push( node, o->mcf );

        ASSERT( node->mnode->ax0 >= 0 );
        opal_frame_hidx_s_push( &o->hidx_en, node->mnode->ax0 );
    }

    BFOR_EACH( i, &net_cell->excs )
    {
        opal_net_node_s* node = net_cell->excs.data[ i ];
        ASSERT( node->mnode );
        ASSERT( node->mnode->ax0 >= 0 ) ;
        opal_frame_hidx_s_push( &o->hidx_ex, node->mnode->ax0 );
    }

    BFOR_EACH( i, &net_cell->body )
    {
        opal_net_node_s* node = net_cell->body.data[ i ];
        if( node->nop )
        {
            ASSERT( node->mnode );
            const bhvm_mcode_node_s* mnode = node->mnode;
            if( mnode->adaptive ) if( node->mnode->ax0 >= 0 ) opal_frame_hidx_s_push( &o->hidx_ada, node->mnode->ax0 );
            if( mnode->cyclic ) o->is_cyclic = true;
        }
    }

    o->is_setup = true;
    opal_frame_s_reset( o );
    opal_frame_s_setup( o );

    opal_frame_s_check_integrity( o );

    BLM_RETURNV( opal_frame_s*, o );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_s* opal_frame_s_run( opal_frame_s* o, tp_t track )
{
    ASSERT( o->mcf );
    bhvm_mcode_frame_s_track_run( o->mcf, track );
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_s* opal_frame_s_run_ap( opal_frame_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex )
{
    ASSERT( o->mcf );
    ASSERT( o->is_setup );

    bhvm_mcode_hbase_s* hbase = o->mcf->hbase;
    const opal_frame_hidx_s* hidx_en = &o->hidx_en;
    const opal_frame_hidx_s* hidx_ex = &o->hidx_ex;

    ASSERT( size_en >= o->size_en );
    for( sz_t i = 0; i < o->size_en; i++ )
    {
        bhvm_holor_s* h_m = opal_frame_hidx_s_get_holor( hidx_en, hbase, i );
        const bhvm_holor_s* h_i = en[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) )
        {
            BLM_INIT();
            st_s* st = BLM_CREATE( st_s );
            st_s_push_fa( st, "Entry channel #<sz_t> size mismatch:", i );
            st_s_push_fa( st, "\nGiven holor:   " );
            bhvm_holor_s_brief_to_sink( h_i, (bcore_sink*)st );
            st_s_push_fa( st, "\nChannel holor: " );
            bhvm_holor_s_brief_to_sink( h_m, (bcore_sink*)st );
            ERR_fa( "#<sc_t>\n", st->sc );
            BLM_DOWN();
        }
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_cyclic_update );
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap );

    if( ex )
    {
        ASSERT( size_ex >= o->size_ex );
        for( sz_t i = 0; i < o->size_ex; i++ )
        {
            bhvm_holor_s* h_m = opal_frame_hidx_s_get_holor( hidx_ex, hbase, i );
            bhvm_holor_s* h_o = ex[ i ];
            ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
            if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
            bhvm_value_s_cpy( &h_m->v, &h_o->v );
        }
    }

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_s* opal_frame_s_run_dp( opal_frame_s* o, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en )
{
    ASSERT( o->is_setup );
    ASSERT( o->mcf );
    ASSERT( !o->is_cyclic );

    bhvm_mcode_hbase_s* hbase = o->mcf->hbase;
    const opal_frame_hidx_s* hidx_en = &o->hidx_en;
    const opal_frame_hidx_s* hidx_ex = &o->hidx_ex;

    ASSERT( size_ex >= o->size_ex );
    BFOR_SIZE( i, o->size_ex )
    {
        sz_t idx = opal_frame_hidx_s_get_pclass_idx( hidx_ex, hbase, TYPEOF_pclass_ag0, i );
        if( idx < 0 ) continue;
        bhvm_holor_s* h_m = bhvm_mcode_hbase_s_get_holor( hbase, idx );
        const bhvm_holor_s* h_i = ex[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) )
        {
            BLM_INIT();
            st_s* st = BLM_CREATE( st_s );
            st_s_push_fa( st, "Exit channel #<sz_t> shape mismatch:", i );
            st_s_push_fa( st, "\nGiven holor:   " );
            bhvm_holor_s_brief_to_sink( h_i, (bcore_sink*)st );
            st_s_push_fa( st, "\nChannel holor: " );
            bhvm_holor_s_brief_to_sink( h_m, (bcore_sink*)st );
            ERR_fa( "#<sc_t>\n", st->sc );
            BLM_DOWN();
        }
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_dp );

    if( en )
    {
        ASSERT( size_en >= o->size_en );
        BFOR_SIZE( i, o->size_en )
        {
            sz_t idx = opal_frame_hidx_s_get_pclass_idx( hidx_en, hbase, TYPEOF_pclass_ag0, i );
            if( idx < 0 ) continue;
            bhvm_holor_s* h_m = bhvm_mcode_hbase_s_get_holor( hbase, idx );
            bhvm_holor_s* h_o = en[ i ];
            ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
            if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
            bhvm_value_s_cpy( &h_m->v, &h_o->v );
        }
    }

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_s* opal_frame_s_run_ap_adl( opal_frame_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex )
{
    if( ex && ex->size != opal_frame_s_get_size_ex( o ) ) bhvm_holor_adl_s_set_size( ex, opal_frame_s_get_size_ex( o ) );
    BFOR_EACH( i, ex ) if( !ex->data[ i ] ) ex->data[ i ] = bhvm_holor_s_create();
    return opal_frame_s_run_ap
    (
        o,
        en ? ( const bhvm_holor_s** )en->data : NULL,
        en ? en->size : 0,
        ex ? (       bhvm_holor_s** )ex->data : NULL,
        ex ? ex->size : 0
    );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_s* opal_frame_s_run_dp_adl( opal_frame_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en )
{
    if( en && en->size != opal_frame_s_get_size_en( o ) ) bhvm_holor_adl_s_set_size( en, opal_frame_s_get_size_en( o ) );
    BFOR_EACH( i, en ) if( !en->data[ i ] ) en->data[ i ] = bhvm_holor_s_create();
    return opal_frame_s_run_dp
    (
        o,
        ex ? ( const bhvm_holor_s** )ex->data : NULL,
        ex ? ex->size : 0,
        en ? (       bhvm_holor_s** )en->data : NULL,
        en ? en->size : 0
    );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex )
{
    BLM_INIT();
    opal_frame_s_run_ap( BLM_A_PUSH( opal_frame_s_create_from_sc( sc, en, size_en ) ), en, size_en, ex, size_ex );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en )
{
    BLM_INIT();
    opal_frame_s_run_dp( BLM_A_PUSH( opal_frame_s_create_from_sc( sc, ex, size_ex ) ), ex, size_ex, en, size_en );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_s_cyclic_reset( opal_frame_s* o )
{
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_cyclic_reset );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// frame_cyclic

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_reset( opal_frame_cyclic_s* o )
{
    if( !o->is_setup ) return;
    if( !o->frame ) return;

    if( o->frame->mcf->hbase->copy_size_limit >= 0 )
    {
        bhvm_mcode_hbase_s_set_size( o->frame->mcf->hbase, o->frame->mcf->hbase->copy_size_limit );
        o->frame->mcf->hbase->copy_size_limit = -1;
    }

    opal_frame_s_reset( o->frame );

    bhvm_mcode_track_adl_s_detach( &o->track_adl_ap );
    bhvm_mcode_track_adl_s_detach( &o->track_adl_dp );
    bhvm_mcode_track_adl_s_detach( &o->track_adl_ap_setup );

    o->unroll_index = 0;
    o->is_setup = false;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_cyclic_s* opal_frame_cyclic_s_bind_holors( opal_frame_cyclic_s* o )
{
    opal_frame_s_bind_holors( o->frame );
    bhvm_mcode_hbase_s* hbase = o->frame->mcf->hbase;
    for( sz_t i = 1; i < o->unroll_size; i++ ) bhvm_mcode_track_s_run( o->track_adl_ap_setup->data[ i ], hbase->holor_adl.data );
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_setup( opal_frame_cyclic_s* o )
{
    if( o->is_setup ) return;
    if( !o->frame ) return;

    ASSERT( o->unroll_size >= 2 );

    BLM_INIT();

    opal_frame_s* frame = o->frame;
    opal_frame_s_reset( frame );

    bhvm_mcode_track_adl_s_attach( &o->track_adl_ap      , bhvm_mcode_track_adl_s_create() );
    bhvm_mcode_track_adl_s_attach( &o->track_adl_dp      , bhvm_mcode_track_adl_s_create() );
    bhvm_mcode_track_adl_s_attach( &o->track_adl_ap_setup, bhvm_mcode_track_adl_s_create() );

    bhvm_mcode_track_s* track0_ap        = bhvm_mcode_frame_s_track_get( o->frame->mcf, TYPEOF_track_ap );
    bhvm_mcode_track_s* track0_dp        = bhvm_mcode_frame_s_track_get( o->frame->mcf, TYPEOF_track_dp );
    bhvm_mcode_track_s* track0_ap_setup  = bhvm_mcode_frame_s_track_get( o->frame->mcf, TYPEOF_track_ap_setup );
    bhvm_mcode_hbase_s* hbase = o->frame->mcf->hbase;

    sz_t rolled_hbase_size = hbase->holor_adl.size;
    hbase->copy_size_limit = rolled_hbase_size;

    bcore_arr_sz_s* idx_arr_track0_ap = BLM_CREATE( bcore_arr_sz_s );
    bhvm_mcode_track_s_get_index_arr( track0_ap, idx_arr_track0_ap );

    /// unrollable indices
    bcore_arr_sz_s* ur_idx_arr = BLM_CREATE( bcore_arr_sz_s );

    BFOR_EACH( i, idx_arr_track0_ap )
    {
        sz_t src_idx = idx_arr_track0_ap->data[ i ];
        if( !bhvm_mcode_hmeta_a_is_rollable( hbase->hmeta_adl.data[ src_idx ] ) ) bcore_arr_sz_s_push( ur_idx_arr, src_idx );
    }

    opal_frame_custom_hmeta_s* custom = BLM_CREATE( opal_frame_custom_hmeta_s );

    bhvm_mcode_track_s* track_ap_prev = NULL;

    for( sz_t i = 0; i < o->unroll_size; i++ )
    {
        BLM_INIT();
        custom->ur_slot = i;
        bhvm_mcode_track_s* track_ap_curr   = bhvm_mcode_track_adl_s_push_c( o->track_adl_ap, track0_ap );
        bhvm_mcode_track_s* track_dp        = bhvm_mcode_track_adl_s_push_c( o->track_adl_dp, track0_dp );
        bhvm_mcode_track_s* track_ap_setup  = bhvm_mcode_track_adl_s_push_c( o->track_adl_ap_setup,  track0_ap_setup );

        opal_frame_hidx_s* hidx_en = opal_frame_hidx_ads_s_push_c( &o->hidx_ads_en, &o->frame->hidx_en );
        opal_frame_hidx_s* hidx_ex = opal_frame_hidx_ads_s_push_c( &o->hidx_ads_ex, &o->frame->hidx_ex );

        if( i > 0 )
        {
            bcore_arr_sz_s* ur_idx_map = BLM_CREATEC( bcore_arr_sz_s, fill, rolled_hbase_size, -1 );
            bcore_arr_sz_s* rc_idx_map = BLM_CREATEC( bcore_arr_sz_s, fill, rolled_hbase_size, -1 );
            BFOR_EACH( j, ur_idx_arr )
            {
                sz_t src_idx = ur_idx_arr->data[ j ];
                sz_t dst_idx = bhvm_mcode_hbase_s_push_copy_from_index( hbase, src_idx );
                ur_idx_map->data[ src_idx ] = dst_idx;

                bhvm_mcode_hmeta* src_hmeta = hbase->hmeta_adl.data[ src_idx ];
                bhvm_mcode_hmeta* dst_hmeta = hbase->hmeta_adl.data[ dst_idx ];
                bhvm_mcode_node_s* src_node = bhvm_mcode_hmeta_a_get_node( src_hmeta );
                if( src_node->cyclic ) rc_idx_map->data[ src_node->ax1 ] = dst_idx;

                bhvm_mcode_hmeta_a_set_custom( dst_hmeta, ( bcore_inst* )custom );
            }
            bhvm_mcode_track_s_replace_index_via_map( track_ap_curr, ur_idx_map );
            bhvm_mcode_track_s_replace_index_via_map( track_ap_prev, rc_idx_map );

            bhvm_mcode_track_s_remove_unmapped_output( track_ap_setup,  ur_idx_map );
            bhvm_mcode_track_s_replace_index_via_map(  track_ap_setup,  ur_idx_map );
            bhvm_mcode_track_s_replace_index_via_map(  track_dp,        ur_idx_map );

            opal_frame_hidx_s_replace_index( hidx_en, ur_idx_map );
            opal_frame_hidx_s_replace_index( hidx_ex, ur_idx_map );
        }

        track_ap_prev = track_ap_curr;
        BLM_DOWN();
    }

    opal_frame_s_setup( frame );
    for( sz_t i = 1; i < o->unroll_size; i++ ) bhvm_mcode_track_s_run( o->track_adl_ap_setup->data[ i ], hbase->holor_adl.data );

    o->is_setup = true;
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_setup_from_frame( opal_frame_cyclic_s* o, const opal_frame_s* frame, sz_t unroll_size )
{
    opal_frame_cyclic_s_reset( o );
    opal_frame_s_attach( &o->frame, opal_frame_s_clone( frame ) );
    opal_frame_s_reset( o->frame );
    o->unroll_size = unroll_size;
    opal_frame_cyclic_s_setup( o );
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_cyclic_s* opal_frame_cyclic_s_run_ap( opal_frame_cyclic_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex )
{
    ASSERT( o->frame );
    assert( o->setup );
    assert( o->unroll_index < o->unroll_size );

    opal_frame_s* frame = o->frame;
    bhvm_mcode_hbase_s* hbase = frame->mcf->hbase;
    const opal_frame_hidx_s* hidx_en = &o->hidx_ads_en.data[  o->unroll_index ];
    const opal_frame_hidx_s* hidx_ex = &o->hidx_ads_ex.data[  o->unroll_index ];
    const bhvm_mcode_track_s* track  = o->track_adl_ap->data[ o->unroll_index ];

    ASSERT( size_en >= frame->size_en );

    for( sz_t i = 0; i < frame->size_en; i++ )
    {
        bhvm_holor_s* h_m = opal_frame_hidx_s_get_holor( hidx_en, hbase, i );
        const bhvm_holor_s* h_i = en[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    if( o->unroll_index == 0 ) bhvm_mcode_frame_s_track_run( frame->mcf, TYPEOF_track_ap_cyclic_update );
    bhvm_mcode_track_s_run( track, hbase->holor_adl.data );

    if( ex )
    {
        ASSERT( size_ex >= frame->size_ex );
        for( sz_t i = 0; i < frame->size_ex; i++ )
        {
            bhvm_holor_s* h_m = opal_frame_hidx_s_get_holor( hidx_ex, hbase, i );
            bhvm_holor_s* h_o = ex[ i ];
            ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
            if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
            bhvm_value_s_cpy( &h_m->v, &h_o->v );
        }
    }

    o->unroll_index = ( o->unroll_index + 1 ) % o->unroll_size;

    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

opal_frame_cyclic_s* opal_frame_cyclic_s_run_ap_adl( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex )
{
    if( ex && ex->size != opal_frame_cyclic_s_get_size_ex( o ) ) bhvm_holor_adl_s_set_size( ex, opal_frame_cyclic_s_get_size_ex( o ) );
    BFOR_EACH( i, ex ) if( !ex->data[ i ] ) ex->data[ i ] = bhvm_holor_s_create();
    return opal_frame_cyclic_s_run_ap
    (
        o,
        en ? ( const bhvm_holor_s** )en->data : NULL,
        en ? en->size : 0,
        ex ? ( bhvm_holor_s** ) ex->data : NULL,
        ex ? ex->size : 0
    );
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_disassemble_to_sink( const opal_frame_cyclic_s* o, bcore_sink* sink )
{
    BLM_INIT();

    opal_frame_s* frame = o->frame;
    bhvm_mcode_frame_s* mcf = frame->mcf;
    bhvm_mcode_hbase_s* hbase = mcf->hbase;

    bcore_sink_a_push_fa( sink, "Holorbase:\n" );
    opal_frame_s_disassemble_hbase_to_sink( frame, hbase, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    if( opal_frame_hidx_s_get_size( &frame->hidx_ada ) > 0 )
    {
        bcore_sink_a_push_fa( sink, "Adaptive channels:\n" );
        opal_frame_s_disassemble_hidx_to_sink( frame, hbase, frame->hidx_ada.arr, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Global Tracks:\n" );

    bhvm_mcode_track_s* track = NULL;

    track = bhvm_mcode_frame_s_track_get( mcf, TYPEOF_track_dp_setup );
    if( track )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track->name ) );
        opal_frame_s_disassemble_track_to_sink( frame, track, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    track = bhvm_mcode_frame_s_track_get( mcf, TYPEOF_track_ap_cyclic_reset );
    if( track )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track->name ) );
        opal_frame_s_disassemble_track_to_sink( frame, track, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    track = bhvm_mcode_frame_s_track_get( mcf, TYPEOF_track_ap_cyclic_update );
    if( track )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track->name ) );
        opal_frame_s_disassemble_track_to_sink( frame, track, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Unroll index: #<sz_t>\n", o->unroll_index );
    bcore_sink_a_push_fa( sink, "Unroll slots: #<sz_t>\n", o->unroll_size );

    BFOR_SIZE( i, o->unroll_size )
    {
        bcore_sink_a_push_fa( sink, "  Roll slot: #<sz_t>", i );

        bcore_sink_a_push_fa( sink, "\n  Entry channels:\n" );
        opal_frame_s_disassemble_hidx_to_sink( frame, hbase, o->hidx_ads_en.data[ i ].arr, 4, sink );

        bcore_sink_a_push_fa( sink, "\n  Exit channels:\n" );
        opal_frame_s_disassemble_hidx_to_sink( frame, hbase, o->hidx_ads_ex.data[ i ].arr, 4, sink );

        track = o->track_adl_ap->data[ i ];
        bcore_sink_a_push_fa( sink, "\n  #<sc_t>:\n", ifnameof( track->name ) );
        opal_frame_s_disassemble_track_to_sink( frame, track, 4, sink );

        track = o->track_adl_dp->data[ i ];
        bcore_sink_a_push_fa( sink, "\n  #<sc_t>:\n", ifnameof( track->name ) );
        opal_frame_s_disassemble_track_to_sink( frame, track, 4, sink );

        track = o->track_adl_ap_setup->data[ i ];
        bcore_sink_a_push_fa( sink, "\n  #<sc_t>:\n", ifnameof( track->name ) );
        opal_frame_s_disassemble_track_to_sink( frame, track, 4, sink );

        bcore_sink_a_push_fa( sink, "\n  #r32{-}\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_cyclic_reset( opal_frame_cyclic_s* o )
{
    bhvm_mcode_frame_s_track_run( o->frame->mcf, TYPEOF_track_ap_cyclic_reset );
    o->unroll_index = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_run_ap_adl_flat( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex )
{
    ASSERT( o->frame );
    opal_frame_cyclic_s_cyclic_reset( o );
    sz_t size_en = opal_frame_s_get_size_en( o->frame );
    sz_t size_ex = opal_frame_s_get_size_ex( o->frame );

    if( ex && ex->size != size_ex * o->unroll_size ) bhvm_holor_adl_s_set_size( ex, size_ex * o->unroll_size );
    BFOR_EACH( i, ex ) if( !ex->data[ i ] ) ex->data[ i ] = bhvm_holor_s_create();

    BFOR_SIZE( i, o->unroll_size )
    {
        ASSERT( i * size_en < en->size );
        ASSERT( ex ? ( i * size_ex < ex->size ) : true);
        opal_frame_cyclic_s_run_ap
        (
            o,
            ( const bhvm_holor_s** )( en->data + i * size_en ),
            size_en,
            ex ? ( ex->data + i * size_ex ) : NULL,
            size_ex
        );
    }

}

// ---------------------------------------------------------------------------------------------------------------------

void opal_frame_cyclic_s_run_dp_adl_flat( opal_frame_cyclic_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en )
{
    ASSERT( o->frame );
    ASSERT( o->is_setup );

    sz_t size_en = opal_frame_s_get_size_en( o->frame );
    sz_t size_ex = opal_frame_s_get_size_ex( o->frame );

    if( en && en->size != size_en * o->unroll_size ) bhvm_holor_adl_s_set_size( en, size_en * o->unroll_size );
    BFOR_EACH( i, en ) if( !en->data[ i ] ) en->data[ i ] = bhvm_holor_s_create();

    opal_frame_s* frame = o->frame;
    bhvm_mcode_hbase_s* hbase = frame->mcf->hbase;

    opal_frame_s_run( frame, TYPEOF_track_dp_cyclic_zero_grad );

    BFOR_SIZE( i, o->unroll_size )
    {
        sz_t unroll_index = ( o->unroll_size - i - 1 ) % o->unroll_size;
        const opal_frame_hidx_s*  hidx_en  = &o->hidx_ads_en.data[  unroll_index ];
        const opal_frame_hidx_s*  hidx_ex  = &o->hidx_ads_ex.data[  unroll_index ];
        const bhvm_mcode_track_s* track_dp = o->track_adl_dp->data[ unroll_index ];

        ASSERT(        unroll_index * size_ex < ex->size          );
        ASSERT( en ? ( unroll_index * size_en < en->size ) : true );

        const bhvm_holor_s** p_ex = ( const bhvm_holor_s** )( ex->data + unroll_index * size_ex );
              bhvm_holor_s** p_en = en ? (  bhvm_holor_s** )( en->data + unroll_index * size_en ) : NULL;

        BFOR_SIZE( i, size_ex )
        {
            sz_t idx = opal_frame_hidx_s_get_pclass_idx( hidx_ex, hbase, TYPEOF_pclass_ag0, i );
            if( idx < 0 ) continue;
            bhvm_holor_s* h_m = bhvm_mcode_hbase_s_get_holor( hbase, idx );
            const bhvm_holor_s* h_i = p_ex[ i ];
            ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
            bhvm_value_s_cpy( &h_i->v, &h_m->v );
        }

        bhvm_mcode_track_s_run( track_dp, hbase->holor_adl.data );

        if( p_en )
        {
            BFOR_SIZE( i, size_en )
            {
                sz_t idx = opal_frame_hidx_s_get_pclass_idx( hidx_en, hbase, TYPEOF_pclass_ag0, i );
                if( idx < 0 ) continue;
                bhvm_holor_s* h_m = bhvm_mcode_hbase_s_get_holor( hbase, idx );
                bhvm_holor_s* h_o = p_en[ i ];
                ASSERT( h_o && h_o->_ == TYPEOF_bhvm_holor_s );
                if( !bhvm_shape_s_is_equal( &h_m->s, &h_o->s ) ) bhvm_holor_s_copy_shape_type( h_o, h_m );
                if( h_o->v.size == 0 ) bhvm_holor_s_fit_size( h_o );
                bhvm_value_s_cpy( &h_m->v, &h_o->v );
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

