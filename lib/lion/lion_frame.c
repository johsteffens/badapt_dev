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
/// frame

// ---------------------------------------------------------------------------------------------------------------------

static lion_nop* input_op_create( vd_t arg, sz_t in_idx, tp_t in_name, const lion_nop* current_nop )
{
    BLM_INIT();
    const bhvm_holor_s** in = arg;

    if( in ) ASSERT( in[ in_idx ] != NULL && *(aware_t*)in[ in_idx ] == TYPEOF_bhvm_holor_s );

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

static void disassemble_hbase_to_sink( const bhvm_mcode_hbase_s* hbase, sz_t indent, bcore_sink* sink )
{
    sz_t hname_length = 0;
    sz_t hbrief_length = 0;

    BFOR_EACH( i, &hbase->holor_ads )
    {
        BLM_INIT();
        bhvm_holor_s* h = &hbase->holor_ads.data[ i ];
        bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ i ];
        hname_length = sz_max( hname_length, bcore_strlen( lion_ifnameof( bhvm_mcode_hmeta_a_get_name( hmeta ) ) ) );

        st_s* st = BLM_CREATE( st_s );
        bhvm_holor_s_compact_to_sink( h, 12, ( bcore_sink* )st );
        hbrief_length = sz_max( hbrief_length, st->size );

        BLM_DOWN();
    }

    BFOR_EACH( i, &hbase->holor_ads )
    {
        BLM_INIT();
        st_s* msg = BLM_CREATE( st_s );
        bhvm_holor_s* h = &hbase->holor_ads.data[ i ];
        bhvm_mcode_hmeta* hmeta  = hbase->hmeta_adl.data[ i ];

        tp_t pclass = bhvm_mcode_hmeta_a_get_pclass( hmeta );
        sc_t sc_name = lion_ifnameof( bhvm_mcode_hmeta_a_get_name( hmeta ) );

        st_s_push_fa( msg, "#rn{ }#pl3 {#<sz_t>}", indent, i );

        bhvm_mcode_node_s* mnode = bhvm_mcode_hmeta_a_get_node( hmeta );
        ASSERT( mnode );

        if(      pclass == TYPEOF_pclass_ax0 ) st_s_push_fa( msg, " ax0 #pl5 {[#<sz_t>]}", mnode->ax0 );
        else if( pclass == TYPEOF_pclass_ax1 ) st_s_push_fa( msg, " ax1 #pl5 {[#<sz_t>]}", mnode->ax0 );
        else if( pclass == TYPEOF_pclass_ag0 ) st_s_push_fa( msg, " ag0 #pl5 {[#<sz_t>]}", mnode->ax0 );
        else if( pclass == TYPEOF_pclass_ag1 ) st_s_push_fa( msg, " ag1 #pl5 {[#<sz_t>]}", mnode->ax0 );

        st_s_push_fa( msg, " #rn{.} ", sz_max( 0, 22 - msg->size ) );

        st_s_push_fa( msg, " #pln' '{#<sc_t>}", hname_length, sc_name );
        if     ( mnode->adaptive  )                      st_s_push_fa( msg, " adaptive" );
        else if( mnode->cyclic )                         st_s_push_fa( msg, " cyclic  " );
        else if( bhvm_mcode_hmeta_a_is_active( hmeta ) ) st_s_push_fa( msg, " active  " );
        else                                             st_s_push_fa( msg, " const   " );

        st_s* st = BLM_CREATE( st_s );
        bhvm_holor_s_compact_to_sink( h, 12, ( bcore_sink* )st );

        st_s_push_fa( msg, " #pn' '{#<st_s*>} ", hbrief_length, st );

        const bcore_inst* custom = bhvm_mcode_hmeta_a_get_custom( hmeta );
        if( custom && *(aware_t*)custom == TYPEOF_lion_frame_custom_hmeta_s )
        {
            lion_frame_custom_hmeta_s* custom_hmeta = ( lion_frame_custom_hmeta_s* )custom;
            st_s_push_fa( msg, " ur_slot #pl2 {#<sz_t>}", custom_hmeta->ur_slot );
        }

        bcore_sink_a_push_fa( sink, "#<st_s*>\n", msg );


        BLM_DOWN();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void disassemble_hidx_to_sink( const bhvm_mcode_hbase_s* hbase, const bcore_arr_sz_s* hidx, sz_t indent, bcore_sink* sink )
{
    BFOR_EACH( i, hidx )
    {
        sz_t idx_ap = hidx->data[ i ];
        bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ idx_ap ];
        assert( hmeta );
        bcore_sink_a_push_fa( sink, "#rn{ }#pl3 {#<sc_t>}:", indent, lion_ifnameof( bhvm_mcode_hmeta_a_get_name( hmeta ) ) );
        if( idx_ap >= 0 ) bcore_sink_a_push_fa( sink, " (ap)#<sz_t>", idx_ap );

        bhvm_mcode_node_s* mnode = bhvm_mcode_hmeta_a_get_node( hmeta );
        if( mnode )
        {
            sz_t idx_dp = mnode->ag0;
            if( idx_dp >= 0 ) bcore_sink_a_push_fa( sink, " (dp)#<sz_t>", idx_dp );
        }

        bcore_sink_a_push_fa( sink, "\n" );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

static void disassemble_track_to_sink( const bhvm_mcode_track_s* track, sz_t indent, bcore_sink* sink )
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

void lion_frame_s_disassemble_to_sink( const lion_frame_s* o, bcore_sink* sink )
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
    disassemble_hidx_to_sink( hbase, o->hidx_en.arr, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "Exit channels:\n" );
    disassemble_hidx_to_sink( hbase, o->hidx_ex.arr, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    if( lion_frame_hidx_s_get_size( &o->hidx_ada ) > 0 )
    {
        bcore_sink_a_push_fa( sink, "Adaptive channels:\n" );
        disassemble_hidx_to_sink( hbase, o->hidx_ada.arr, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }
    bcore_sink_a_push_fa( sink, "\n" );

    bcore_sink_a_push_fa( sink, "Holorbase:\n" );
    disassemble_hbase_to_sink( hbase, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    for( sz_t i = 0; i < sizeof( track_types ) / sizeof( tp_t ); i++ )
    {
        tp_t track_type = track_types[ i ];
        bhvm_mcode_track_s* track = bhvm_mcode_frame_s_track_get( mcf, track_type );
        if( track )
        {
            bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track_type ) );
            disassemble_track_to_sink( track, 2, sink );
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

void lion_frame_s_check_integrity( const lion_frame_s* o )
{
    assert( o->mcf );
    bhvm_mcode_frame_s_check_integrity( o->mcf );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_setup_from_source( lion_frame_s* o, bcore_source* source, const bhvm_holor_s** en, sz_t size_en )
{
    BLM_INIT();

    lion_frame_hidx_s_clear( &o->hidx_en );
    lion_frame_hidx_s_clear( &o->hidx_ex );
    lion_frame_hidx_s_clear( &o->hidx_ada );

    lion_net_cell_s* cell = BLM_CREATE( lion_net_cell_s );

    bhvm_mcode_frame_s_attach( &o->mcf, bhvm_mcode_frame_s_create() );

    /// We use a double-nested frame because the body of sem_cell->parent could be used
    lion_sem_cell_s* sem_cell = BLM_CREATE( lion_sem_cell_s );
    sem_cell->parent = BLM_A_PUSH( lion_sem_cell_s_create_frame() ); // double nested

    bcore_source_point_s_set( &sem_cell->source_point, source );

    bcore_source_a_parse_fa( source, " #-?'cell'" ); // leading 'cell' keyword is optional
    lion_sem_cell_s_parse( sem_cell, source );

    if( en ) ASSERT( size_en >= sem_cell->encs.size );

    /// network cell
    lion_net_cell_s_from_sem_cell( cell, sem_cell, input_op_create, ( vd_t )en, o->log );

    lion_net_cell_s_mcode_push_ap( cell, o->mcf );
    lion_net_cell_s_mcode_push_dp( cell, o->mcf, true );

    o->size_en = cell->encs.size;
    o->size_ex = cell->excs.size;

    BFOR_EACH( i, &cell->encs )
    {
        lion_net_node_s* node = cell->encs.data[ i ];

        /** An entry node without mnode does not actively contribute to the output of the cell.
         *  We therefore construct an mnode formally to provide a holor for the input channel
         *  with the necessary setup and shelve routines.
         */
        if( !node->mnode ) lion_net_node_s_isolated_mcode_push( node, o->mcf );

        ASSERT( node->mnode->ax0 >= 0 );
        lion_frame_hidx_s_push( &o->hidx_en, node->mnode->ax0 );
    }

    BFOR_EACH( i, &cell->excs )
    {
        lion_net_node_s* node = cell->excs.data[ i ];
        ASSERT( node->mnode );
        ASSERT( node->mnode->ax0 >= 0 ) ;
        lion_frame_hidx_s_push( &o->hidx_ex, node->mnode->ax0 );
    }

    BFOR_EACH( i, &cell->body )
    {
        lion_net_node_s* node = cell->body.data[ i ];
        if( node->nop )
        {
            ASSERT( node->mnode );
            const bhvm_mcode_node_s* mnode = node->mnode;
            if( mnode->adaptive ) if( node->mnode->ax0 >= 0 ) lion_frame_hidx_s_push( &o->hidx_ada, node->mnode->ax0 );
            if( mnode->cyclic ) o->is_cyclic = true;
        }
    }

    o->setup = true;
    lion_frame_s_reset( o );
    lion_frame_s_setup( o );

    lion_frame_s_check_integrity( o );

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

lion_frame_s* lion_frame_s_run_ap( lion_frame_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex )
{
    ASSERT( o->mcf );
    ASSERT( o->setup );

    bhvm_mcode_hbase_s* hbase = o->mcf->hbase;
    const lion_frame_hidx_s* hidx_en = &o->hidx_en;
    const lion_frame_hidx_s* hidx_ex = &o->hidx_ex;

    ASSERT( size_en >= o->size_en );
    for( sz_t i = 0; i < o->size_en; i++ )
    {
        bhvm_holor_s* h_m = lion_frame_hidx_s_get_holor( hidx_en, hbase, i );
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
            bhvm_holor_s* h_m = lion_frame_hidx_s_get_holor( hidx_ex, hbase, i );
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

lion_frame_s* lion_frame_s_run_dp( lion_frame_s* o, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en )
{
    ASSERT( o->setup );
    ASSERT( o->mcf );
    ASSERT( !o->is_cyclic );

    bhvm_mcode_hbase_s* hbase = o->mcf->hbase;
    const lion_frame_hidx_s* hidx_en = &o->hidx_en;
    const lion_frame_hidx_s* hidx_ex = &o->hidx_ex;

    ASSERT( size_ex >= o->size_ex );
    BFOR_SIZE( i, o->size_ex )
    {
        sz_t idx = lion_frame_hidx_s_get_pclass_idx( hidx_ex, hbase, TYPEOF_pclass_ag0, i );
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
            sz_t idx = lion_frame_hidx_s_get_pclass_idx( hidx_en, hbase, TYPEOF_pclass_ag0, i );
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

lion_frame_s* lion_frame_s_run_ap_adl( lion_frame_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex )
{
    if( ex && ex->size != lion_frame_s_get_size_ex( o ) ) bhvm_holor_adl_s_set_size( ex, lion_frame_s_get_size_ex( o ) );
    BFOR_EACH( i, ex ) if( !ex->data[ i ] ) ex->data[ i ] = bhvm_holor_s_create();
    return lion_frame_s_run_ap
    (
        o,
        en ? ( const bhvm_holor_s** )en->data : NULL,
        en ? en->size : 0,
        ex ? (       bhvm_holor_s** )ex->data : NULL,
        ex ? ex->size : 0
    );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_s* lion_frame_s_run_dp_adl( lion_frame_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en )
{
    if( en && en->size != lion_frame_s_get_size_en( o ) ) bhvm_holor_adl_s_set_size( en, lion_frame_s_get_size_en( o ) );
    BFOR_EACH( i, en ) if( !en->data[ i ] ) en->data[ i ] = bhvm_holor_s_create();
    return lion_frame_s_run_dp
    (
        o,
        ex ? ( const bhvm_holor_s** )ex->data : NULL,
        ex ? ex->size : 0,
        en ? (       bhvm_holor_s** )en->data : NULL,
        en ? en->size : 0
    );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_sc_run_ap( sc_t sc, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex )
{
    BLM_INIT();
    lion_frame_s_run_ap( BLM_A_PUSH( lion_frame_s_create_from_sc( sc, en, size_en ) ), en, size_en, ex, size_ex );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_sc_run_dp( sc_t sc, const bhvm_holor_s** ex, sz_t size_ex, bhvm_holor_s** en, sz_t size_en )
{
    BLM_INIT();
    lion_frame_s_run_dp( BLM_A_PUSH( lion_frame_s_create_from_sc( sc, ex, size_ex ) ), ex, size_ex, en, size_en );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_s_cyclic_reset( lion_frame_s* o )
{
    bhvm_mcode_frame_s_track_run( o->mcf, TYPEOF_track_ap_cyclic_reset );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// frame_cyclic

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_cyclic_s_reset( lion_frame_cyclic_s* o )
{
    if( !o->setup ) return;
    if( !o->frame ) return;

    if( o->frame->mcf->hbase->copy_size_limit >= 0 )
    {
        bhvm_mcode_hbase_s_set_size( o->frame->mcf->hbase, o->frame->mcf->hbase->copy_size_limit );
        o->frame->mcf->hbase->copy_size_limit = -1;
    }

    lion_frame_s_reset( o->frame );

    bhvm_mcode_track_adl_s_detach( &o->track_adl_ap );
    bhvm_mcode_track_adl_s_detach( &o->track_adl_dp );
    bhvm_mcode_track_adl_s_detach( &o->track_adl_ap_setup );

    o->unroll_index = 0;
    o->setup = false;
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_cyclic_s* lion_frame_cyclic_s_bind_holors( lion_frame_cyclic_s* o )
{
    lion_frame_s_bind_holors( o->frame );
    bhvm_mcode_hbase_s* hbase = o->frame->mcf->hbase;
    for( sz_t i = 1; i < o->unroll_size; i++ ) bhvm_mcode_track_s_run( o->track_adl_ap_setup->data[ i ], hbase->holor_ads.data );
    return o;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_cyclic_s_setup( lion_frame_cyclic_s* o )
{
    if( o->setup ) return;
    if( !o->frame ) return;

    ASSERT( o->unroll_size >= 2 );

    BLM_INIT();

    lion_frame_s* frame = o->frame;
    lion_frame_s_reset( frame );

    bhvm_mcode_track_adl_s_attach( &o->track_adl_ap        , bhvm_mcode_track_adl_s_create() );
    bhvm_mcode_track_adl_s_attach( &o->track_adl_dp        , bhvm_mcode_track_adl_s_create() );
    bhvm_mcode_track_adl_s_attach( &o->track_adl_ap_setup  , bhvm_mcode_track_adl_s_create() );

    bhvm_mcode_track_s* track0_ap        = bhvm_mcode_frame_s_track_get( o->frame->mcf, TYPEOF_track_ap );
    bhvm_mcode_track_s* track0_dp        = bhvm_mcode_frame_s_track_get( o->frame->mcf, TYPEOF_track_dp );
    bhvm_mcode_track_s* track0_ap_setup  = bhvm_mcode_frame_s_track_get( o->frame->mcf, TYPEOF_track_ap_setup );
    bhvm_mcode_hbase_s* hbase = o->frame->mcf->hbase;

    sz_t rolled_hbase_size = hbase->holor_ads.size;
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

    lion_frame_custom_hmeta_s* custom = BLM_CREATE( lion_frame_custom_hmeta_s );

    bhvm_mcode_track_s* track_ap_prev = NULL;

    for( sz_t i = 0; i < o->unroll_size; i++ )
    {
        BLM_INIT();
        custom->ur_slot = i;
        bhvm_mcode_track_s* track_ap_curr   = bhvm_mcode_track_adl_s_push_c( o->track_adl_ap, track0_ap );
        bhvm_mcode_track_s* track_dp        = bhvm_mcode_track_adl_s_push_c( o->track_adl_dp, track0_dp );
        bhvm_mcode_track_s* track_ap_setup  = bhvm_mcode_track_adl_s_push_c( o->track_adl_ap_setup,  track0_ap_setup );

        lion_frame_hidx_s* hidx_en = lion_frame_hidx_ads_s_push_c( &o->hidx_ads_en, &o->frame->hidx_en );
        lion_frame_hidx_s* hidx_ex = lion_frame_hidx_ads_s_push_c( &o->hidx_ads_ex, &o->frame->hidx_ex );

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

            lion_frame_hidx_s_replace_index( hidx_en, ur_idx_map );
            lion_frame_hidx_s_replace_index( hidx_ex, ur_idx_map );
        }

        track_ap_prev = track_ap_curr;
        BLM_DOWN();
    }

    lion_frame_s_setup( frame );
    for( sz_t i = 1; i < o->unroll_size; i++ ) bhvm_mcode_track_s_run( o->track_adl_ap_setup->data[ i ], hbase->holor_ads.data );

    o->setup = true;
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_cyclic_s_setup_from_frame( lion_frame_cyclic_s* o, const lion_frame_s* frame, sz_t unroll_size )
{
    lion_frame_cyclic_s_reset( o );
    lion_frame_s_attach( &o->frame, lion_frame_s_clone( frame ) );
    lion_frame_s_reset( o->frame );
    o->unroll_size = unroll_size;
    lion_frame_cyclic_s_setup( o );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_frame_cyclic_s* lion_frame_cyclic_s_run_ap( lion_frame_cyclic_s* o, const bhvm_holor_s** en, sz_t size_en, bhvm_holor_s** ex, sz_t size_ex )
{
    ASSERT( o->frame );
    assert( o->setup );
    assert( o->unroll_index < o->unroll_size );

    lion_frame_s* frame = o->frame;
    bhvm_mcode_hbase_s* hbase = frame->mcf->hbase;
    const lion_frame_hidx_s* hidx_en = &o->hidx_ads_en.data[  o->unroll_index ];
    const lion_frame_hidx_s* hidx_ex = &o->hidx_ads_ex.data[  o->unroll_index ];
    const bhvm_mcode_track_s* track  = o->track_adl_ap->data[ o->unroll_index ];

    ASSERT( size_en >= frame->size_en );

    for( sz_t i = 0; i < frame->size_en; i++ )
    {
        bhvm_holor_s* h_m = lion_frame_hidx_s_get_holor( hidx_en, hbase, i );
        const bhvm_holor_s* h_i = en[ i ];
        ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
        if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
        bhvm_value_s_cpy( &h_i->v, &h_m->v );
    }

    if( o->unroll_index == 0 ) bhvm_mcode_frame_s_track_run( frame->mcf, TYPEOF_track_ap_cyclic_update );
    bhvm_mcode_track_s_run( track, hbase->holor_ads.data );

    if( ex )
    {
        ASSERT( size_ex >= frame->size_ex );
        for( sz_t i = 0; i < frame->size_ex; i++ )
        {
            bhvm_holor_s* h_m = lion_frame_hidx_s_get_holor( hidx_ex, hbase, i );
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

lion_frame_cyclic_s* lion_frame_cyclic_s_run_ap_adl( lion_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex )
{
    if( ex && ex->size != lion_frame_cyclic_s_get_size_ex( o ) ) bhvm_holor_adl_s_set_size( ex, lion_frame_cyclic_s_get_size_ex( o ) );
    BFOR_EACH( i, ex ) if( !ex->data[ i ] ) ex->data[ i ] = bhvm_holor_s_create();
    return lion_frame_cyclic_s_run_ap
    (
        o,
        en ? ( const bhvm_holor_s** )en->data : NULL,
        en ? en->size : 0,
        ex ? ( bhvm_holor_s** ) ex->data : NULL,
        ex ? ex->size : 0
    );
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_cyclic_s_disassemble_to_sink( const lion_frame_cyclic_s* o, bcore_sink* sink )
{
    BLM_INIT();

    lion_frame_s* frame = o->frame;
    bhvm_mcode_frame_s* mcf = frame->mcf;
    bhvm_mcode_hbase_s* hbase = mcf->hbase;

    bcore_sink_a_push_fa( sink, "Holorbase:\n" );
    disassemble_hbase_to_sink( hbase, 2, sink );
    bcore_sink_a_push_fa( sink, "\n" );

    if( lion_frame_hidx_s_get_size( &frame->hidx_ada ) > 0 )
    {
        bcore_sink_a_push_fa( sink, "Adaptive channels:\n" );
        disassemble_hidx_to_sink( hbase, frame->hidx_ada.arr, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Global Tracks:\n" );

    bhvm_mcode_track_s* track = NULL;

    track = bhvm_mcode_frame_s_track_get( mcf, TYPEOF_track_dp_setup );
    if( track )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track->name ) );
        disassemble_track_to_sink( track, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    track = bhvm_mcode_frame_s_track_get( mcf, TYPEOF_track_ap_cyclic_reset );
    if( track )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track->name ) );
        disassemble_track_to_sink( track, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    track = bhvm_mcode_frame_s_track_get( mcf, TYPEOF_track_ap_cyclic_update );
    if( track )
    {
        bcore_sink_a_push_fa( sink, "#<sc_t>:\n", ifnameof( track->name ) );
        disassemble_track_to_sink( track, 2, sink );
        bcore_sink_a_push_fa( sink, "\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    bcore_sink_a_push_fa( sink, "Unroll index: #<sz_t>\n", o->unroll_index );
    bcore_sink_a_push_fa( sink, "Unroll slots: #<sz_t>\n", o->unroll_size );

    BFOR_SIZE( i, o->unroll_size )
    {
        bcore_sink_a_push_fa( sink, "  Roll slot: #<sz_t>", i );

        bcore_sink_a_push_fa( sink, "\n  Entry channels:\n" );
        disassemble_hidx_to_sink( hbase, o->hidx_ads_en.data[ i ].arr, 4, sink );

        bcore_sink_a_push_fa( sink, "\n  Exit channels:\n" );
        disassemble_hidx_to_sink( hbase, o->hidx_ads_ex.data[ i ].arr, 4, sink );

        track = o->track_adl_ap->data[ i ];
        bcore_sink_a_push_fa( sink, "\n  #<sc_t>:\n", ifnameof( track->name ) );
        disassemble_track_to_sink( track, 4, sink );

        track = o->track_adl_dp->data[ i ];
        bcore_sink_a_push_fa( sink, "\n  #<sc_t>:\n", ifnameof( track->name ) );
        disassemble_track_to_sink( track, 4, sink );

        track = o->track_adl_ap_setup->data[ i ];
        bcore_sink_a_push_fa( sink, "\n  #<sc_t>:\n", ifnameof( track->name ) );
        disassemble_track_to_sink( track, 4, sink );

        bcore_sink_a_push_fa( sink, "\n  #r32{-}\n" );
    }

    bcore_sink_a_push_fa( sink, "\n" );
    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_cyclic_s_cyclic_reset( lion_frame_cyclic_s* o )
{
    bhvm_mcode_frame_s_track_run( o->frame->mcf, TYPEOF_track_ap_cyclic_reset );
    o->unroll_index = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_frame_cyclic_s_run_ap_adl_flat( lion_frame_cyclic_s* o, const bhvm_holor_adl_s* en, bhvm_holor_adl_s* ex )
{
    ASSERT( o->frame );
    lion_frame_cyclic_s_cyclic_reset( o );
    sz_t size_en = lion_frame_s_get_size_en( o->frame );
    sz_t size_ex = lion_frame_s_get_size_ex( o->frame );

    if( ex && ex->size != size_ex * o->unroll_size ) bhvm_holor_adl_s_set_size( ex, size_ex * o->unroll_size );
    BFOR_EACH( i, ex ) if( !ex->data[ i ] ) ex->data[ i ] = bhvm_holor_s_create();

    BFOR_SIZE( i, o->unroll_size )
    {
        ASSERT( i * size_en < en->size );
        ASSERT( ex ? ( i * size_ex < ex->size ) : true);
        lion_frame_cyclic_s_run_ap
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

void lion_frame_cyclic_s_run_dp_adl_flat( lion_frame_cyclic_s* o, const bhvm_holor_adl_s* ex, bhvm_holor_adl_s* en )
{
    ASSERT( o->frame );
    assert( o->setup );

    sz_t size_en = lion_frame_s_get_size_en( o->frame );
    sz_t size_ex = lion_frame_s_get_size_ex( o->frame );

    if( en && en->size != size_en * o->unroll_size ) bhvm_holor_adl_s_set_size( en, size_en * o->unroll_size );
    BFOR_EACH( i, en ) if( !en->data[ i ] ) en->data[ i ] = bhvm_holor_s_create();

    lion_frame_s* frame = o->frame;
    bhvm_mcode_hbase_s* hbase = frame->mcf->hbase;

    lion_frame_s_run( frame, TYPEOF_track_dp_cyclic_zero_grad );

    BFOR_SIZE( i, o->unroll_size )
    {
        sz_t unroll_index = ( o->unroll_size - i - 1 ) % o->unroll_size;
        const lion_frame_hidx_s*  hidx_en  = &o->hidx_ads_en.data[  unroll_index ];
        const lion_frame_hidx_s*  hidx_ex  = &o->hidx_ads_ex.data[  unroll_index ];
        const bhvm_mcode_track_s* track_dp = o->track_adl_dp->data[ unroll_index ];

        ASSERT(        unroll_index * size_ex < ex->size          );
        ASSERT( en ? ( unroll_index * size_en < en->size ) : true );

        const bhvm_holor_s** p_ex = ( const bhvm_holor_s** )( ex->data + unroll_index * size_ex );
              bhvm_holor_s** p_en = en ? (  bhvm_holor_s** )( en->data + unroll_index * size_en ) : NULL;

        BFOR_SIZE( i, size_ex )
        {
            sz_t idx = lion_frame_hidx_s_get_pclass_idx( hidx_ex, hbase, TYPEOF_pclass_ag0, i );
            if( idx < 0 ) continue;
            bhvm_holor_s* h_m = bhvm_mcode_hbase_s_get_holor( hbase, idx );
            const bhvm_holor_s* h_i = p_ex[ i ];
            ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
            if( !bhvm_shape_s_is_equal( &h_m->s, &h_i->s ) ) ERR_fa( "Input shape mismatch" );
            bhvm_value_s_cpy( &h_i->v, &h_m->v );
        }

        bhvm_mcode_track_s_run( track_dp, hbase->holor_ads.data );

        if( p_en )
        {
            BFOR_SIZE( i, size_en )
            {
                sz_t idx = lion_frame_hidx_s_get_pclass_idx( hidx_en, hbase, TYPEOF_pclass_ag0, i );
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

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


