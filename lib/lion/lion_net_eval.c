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
    assert( *(aware_t*)arg == TYPEOF_lion_net_eval_param_s );
    lion_net_eval_param_s* o = arg;

    if( !o->in )
    {
        if( current_nop ) return NULL;
        ERR_fa( "No input holor specified." );
    }
    if( in_idx < 0 || in_idx >= o->in->size )
    {
        if( current_nop ) return NULL;
        ERR_fa( "Insufficient input holors specified." );
    }
    const bhvm_holor_s* h_in = o->in->data[ in_idx ];

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

void lion_net_eval_build( const lion_net_eval_param_s* o, lion_net_cell_s* ntf, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();

    bcore_sink* log = o->log;
    sz_t verbosity  = o->verbosity;

    bcore_source* source = NULL;
    if( !o->src ) ERR_fa( "Source missing." );
    switch( *(aware_t*)o->src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = BLM_A_PUSH( bcore_file_open_source_path( ( const bcore_file_path_s* )o->src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = BLM_A_PUSH( bcore_source_string_s_create_from_string( ( const st_s* )o->src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->src ) );
        }
        break;
    }

    f3_t time_build_sem = 0;
    f3_t time_build_net = 0;

    /// semantic cell
    bcore_source_a_parse_fa( source, " cell" );

    /// We use a double-nested frame because the body of sem_frame->parent could be used
    lion_sem_cell_s* sem_frame = BLM_CREATE( lion_sem_cell_s );
    sem_frame->parent = BLM_A_PUSH( lion_sem_cell_s_create_frame() );

    bcore_source_point_s_set( &sem_frame->source_point, source );
    CPU_TIME_OF( lion_sem_cell_s_parse( sem_frame, source ), time_build_sem );

    /// check input channels and turn them to parameters

    /// network cell
    CPU_TIME_OF( lion_net_cell_s_from_sem_cell( ntf, sem_frame, input_op_create, ( vd_t )o, verbosity > 5 ? log : NULL ), time_build_net );

    BFOR_EACH( i, &ntf->excs )
    {
        lion_net_node_s* node = ntf->excs.data[ i ];
        if( node->result )
        {
            lion_holor_s* h = node->result->h;
            if( h && h->m.htp ) bcore_sink_a_push_fa( log, "\nWARNING: Output holor '#<sz_t>' is transposed.\n", i );
        }
    }

    if( log && verbosity >= 3 )
    {
        bcore_sink_a_push_fa( log, "Cell:\n" );
        bcore_sink_a_push_fa( log, "  Entry channels . #<sz_t>\n", ntf->encs.size );
        bcore_sink_a_push_fa( log, "  Body size ...... #<sz_t>\n", ntf->body.size );
        bcore_sink_a_push_fa( log, "  Exit channels .. #<sz_t>\n", ntf->excs.size );
        bcore_sink_a_push_fa( log, "\n" );

        if( verbosity >= 2 && ntf->body.size < 1000 )
        {
            bcore_sink_a_push_fa( log, "Network Graph Structure:\n" );
            lion_net_cell_s_graph_to_sink( ntf, log );
            bcore_sink_a_push_fa( log, "\n" );
        }
    }

    /// test copying of net_cell
    {
        lion_net_cell_s* cloned_cell = BLM_A_PUSH( lion_net_cell_s_clone( ntf ) );
        ASSERT( lion_net_cell_s_is_consistent( cloned_cell ) );
    }

    f3_t time_push_ap = 0;
    f3_t time_push_dp = 0;

    CPU_TIME_OF( lion_net_cell_s_mcode_push_ap( ntf, mcf        ), time_push_ap );
    CPU_TIME_OF( lion_net_cell_s_mcode_push_dp( ntf, mcf, false ), time_push_dp );

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
        BFOR_EACH( i, &ntf->encs )
        {
            lion_net_node_s* node = ntf->encs.data[ i ];
            bcore_sink_a_push_fa( log, "#<sc_t>#<sz_t> (#<sc_t>)", ( i > 0 ) ? ", " : "", node->hidx, lion_ifnameof( node->name ) );
        }
        bcore_sink_a_push_fa( log, "\n" );

        bcore_sink_a_push_fa( log, "  Output: " );
        BFOR_EACH( i, &ntf->excs )
        {
            lion_net_node_s* node = ntf->excs.data[ i ];
            bcore_sink_a_push_fa( log, "#<sc_t>#<sz_t> (#<sc_t>)", ( i > 0 ) ? ", " : "", node->hidx, lion_ifnameof( node->name ) );
        }
        bcore_sink_a_push_fa( log, "\n" );
        bcore_sink_a_push_fa( log, "\n" );

        bcore_sink_a_push_fa( log, "  Holors:\n" );
        BFOR_EACH( i, &mcf->hbase->holor_ads )
        {
            bhvm_holor_s* h = &mcf->hbase->holor_ads.data[ i ];
            bcore_sink_a_push_fa( log, "    #pl3 {#<sz_t>}: ", i );
            bhvm_holor_s_brief_to_sink( h, log );
            bcore_sink_a_push_fa( log, "\n" );
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
                    bhvm_vop* vop = track->data[ i ].vop;
                    bhvm_vop_a_to_sink( vop, log );
                    bcore_sink_a_push_fa( log, "\n" );
                }
                bcore_sink_a_push_fa( log, "\n" );
            }
        }
        bcore_sink_a_push_fa( log, "\n" );
    }

    BLM_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_eval_result_s* lion_net_eval_ap_s_run( const lion_net_eval_ap_s* o, lion_net_eval_result_s* result )
{
    BLM_INIT();

    bcore_sink* log = o->param.log;
    sz_t verbosity  = o->param.verbosity;
    const st_s* name = &o->param.name;
    bhvm_holor_adl_s* in = o->param.in;
    bhvm_holor_adl_s* out = o->param.out;
    f3_t max_dev = o->param.max_dev;

    if( name->size > 0 && verbosity >= 2 ) bcore_sink_a_push_fa( log, "#<sc_t>:\n", name->sc );

    lion_net_cell_s*    ntf = BLM_CREATE( lion_net_cell_s    );
    bhvm_mcode_frame_s* mcf = BLM_CREATE( bhvm_mcode_frame_s );
    lion_net_eval_build( &o->param, ntf, mcf );

    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_shelve_ap );
    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_setup_ap );

    if( in )
    {
        if( in->size != ntf->encs.size )
        {
            ERR_fa( "Number of input holors '#<sz_t>' differs from frame's entry channels '#<sz_t>'.", in->size, ntf->encs.size );
        }
        BFOR_EACH( i, &ntf->encs )
        {
            lion_net_node_s* node = ntf->encs.data[ i ];
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
        if( out->size != ntf->excs.size )
        {
            ERR_fa( "Number of output holors '#<sz_t>' differs from frame's exit channels '#<sz_t>'.", out->size, ntf->excs.size );
        }
    }

    BFOR_EACH( i, &ntf->excs )
    {
        lion_net_node_s* node = ntf->excs.data[ i ];
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

    BLM_RETURNV( lion_net_eval_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_eval_result_s* lion_net_eval_dp_s_run( const lion_net_eval_dp_s* o, lion_net_eval_result_s* result )
{
    BLM_INIT();

    bcore_sink* log = o->param.log;
    sz_t verbosity  = o->param.verbosity;
    const st_s* name = &o->param.name;
//    bhvm_holor_adl_s* in  = o->param.in;
//    bhvm_holor_adl_s* out = o->param.out;
//    f3_t max_dev = o->param.max_dev;

    if( name->size > 0 && verbosity >= 2 ) bcore_sink_a_push_fa( log, "#<sc_t>:\n", name->sc );

    lion_net_cell_s*    ntf = BLM_CREATE( lion_net_cell_s    );
    bhvm_mcode_frame_s* mcf = BLM_CREATE( bhvm_mcode_frame_s );
    lion_net_eval_build( &o->param, ntf, mcf );

    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_shelve_ap );
    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_shelve_dp );
    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_setup_ap );
    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_setup_dp );

    bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_ap );

    u2_t rval = 1234;   //o->param.rval;
//    f3_t in_eps = 1e-4; // input epsilon
//    f3_t gr_dev = 2e-1; // max relative gradient deviation
//    f3_t en_min_dev = 1e-6; // significant energy deviation (tests with less deviations do not generate an error)
//    f3_t en_max_dev = 0.1;  // too high energy deviation
//    f3_t o0_max     = 1E1;  // max out energy

    BFOR_EACH( i, &ntf->excs )
    {
        BLM_INIT();
        lion_net_node_s* node = ntf->excs.data[ i ];
        ASSERT( node->hidx >= 0 );
        bhvm_holor_s* h_hbo = &mcf->hbase->holor_ads.data[ node->hidx ];
        bhvm_holor_s* h_hbg = &mcf->hbase->holor_ads.data[ node->gidx ];

        bhvm_holor_s* h_fin = BLM_A_PUSH( bhvm_holor_s_clone( h_hbo ) );
        bhvm_holor_s* h_scl = BLM_CREATE( bhvm_holor_s );
        bhvm_holor_s_set_scalar_f3( h_scl, 1.0 );

        ASSERT( bhvm_shape_s_is_equal( &h_hbo->s, &h_hbg->s ) );

        /// choose fin such that channel-energy is 1.0
        bhvm_value_s_set_random( &h_fin->v, 1.0, -1.0, 1.0, &rval );

        bhvm_hop_ar1_sqr_s_f(       h_fin, h_scl );
        bhvm_holor_s_set_scalar_f3( h_scl, f3_srt( 1.0 / bhvm_value_s_get_f3( &h_scl->v, 0 ) ) );
        bhvm_hop_ar2_eci_mul_s_f(   h_fin, h_scl, h_fin );
        bhvm_hop_ar2_eci_add_s_f(   h_hbo, h_fin, h_fin );

        /// compute out gradient
        bhvm_hop_ar2_eci_sub_s_f( h_hbo, h_fin, h_hbg );
        bhvm_holor_s_set_scalar_f3( h_scl, 2.0 );
        bhvm_hop_ar2_eci_mul_s_f( h_hbg, h_scl, h_hbg );

        /// dendrite pass
        bhvm_mcode_frame_s_track_run( mcf, TYPEOF_track_dp );

        BLM_DOWN();
    }


    BLM_RETURNV( lion_net_eval_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_eval_result_s* lion_net_eval_frame_s_run( const lion_net_eval_frame_s* o, lion_net_eval_result_s* result )
{
    BLM_INIT();

    if( !o->param.src ) ERR_fa( "Source missing." );

    lion_net_frame_s* frame = BLM_CREATE( lion_net_frame_s );

    if( o->param.log && o->param.verbosity >= 10 ) bcore_sink_a_attach( &frame->mcode_log, bcore_fork( o->param.log ) );

    bcore_source* source = NULL;

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

    ASSERT( o->param.in );
    const bhvm_holor_adl_s* adl_ap_en = o->param.in;
          bhvm_holor_adl_s* adl_ap_ex = BLM_CREATE( bhvm_holor_adl_s );

    lion_net_frame_s_setup_from_source_adl( frame, source, adl_ap_en );
    lion_net_frame_s_run_ap_adl( frame, adl_ap_en, adl_ap_ex );

    BFOR_EACH( i, adl_ap_ex )
    {
        bhvm_holor_s* h_hbo = adl_ap_ex->data[ i ];
        if( o->param.out )
        {
            bhvm_holor_s* h_out = o->param.out->data[ i ];
            bl_t shape_dev = !bhvm_shape_s_is_equal( &h_out->s, &h_hbo->s );
            bl_t value_dev = shape_dev || ( bhvm_value_s_fdev_equ( &h_out->v, &h_hbo->v ) > o->param.max_dev );
            if( shape_dev || value_dev )
            {
                st_s* msg = BLM_CREATE( st_s );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "#<sc_t> deviation at output holor '#<sz_t>':", shape_dev ? "Shape" : "Value", i );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Frame output} " );
                bhvm_holor_s_brief_to_sink( h_hbo, (bcore_sink*)msg );
                bcore_sink_a_push_fa( (bcore_sink*)msg, "\n#p20.{Expected output} " );
                bhvm_holor_s_brief_to_sink( h_out, (bcore_sink*)msg );
                ERR_fa( "#<st_s*>\n", msg );
            }
        }
        else
        {
            bcore_sink_a_push_fa( o->param.log, "Frame out channel '#<sz_t>':\n", i );
            bhvm_holor_s_to_sink_nl( h_hbo, o->param.log );
        }
    }

    u2_t rval = 1234;

    if( o->jacobian_test )
    {
        bhvm_holor_mdl_s* mdl_jc = BLM_CREATE( bhvm_holor_mdl_s );
        lion_net_frame_s_estimate_jacobian( frame, o->param.epsilon, mdl_jc );

        if( o->param.verbosity >= 10 )
        {
            bcore_sink_a_push_fa( o->param.log, "Jacobian DP Test:\n" );
        }

        sz_t size_en = lion_net_frame_s_get_size_en( frame );
        sz_t size_ex = lion_net_frame_s_get_size_ex( frame );

        bhvm_holor_adl_s* adl_dp_en = BLM_CLONE( bhvm_holor_adl_s, adl_ap_en );
        bhvm_holor_adl_s* adl_dp_ex = BLM_CLONE( bhvm_holor_adl_s, adl_ap_ex );

        BFOR_EACH( i, adl_dp_ex )
        {
            bhvm_value_s_set_random( &adl_dp_ex->data[ i ]->v, 1.0, -1, 1, &rval );
            if( o->param.verbosity >= 10 )
            {
                bcore_sink_a_push_fa( o->param.log, "Gradient exc #<sz_t>: ", i );
                bhvm_holor_s_to_sink_nl( adl_dp_ex->data[ i ], o->param.log );
            }
        }

        lion_net_frame_s_run_dp_adl( frame, adl_dp_ex, adl_dp_en );

        BFOR_SIZE( i, size_en )
        {
            BLM_INIT();
            if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "enc #<sz_t>:\n", i );

            bhvm_holor_s* dp_en1 = adl_dp_en->data[ i ];
            bhvm_holor_s* dp_en2 = bhvm_holor_s_copy_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_en1 );
            bhvm_value_s_zro( &dp_en2->v );

            BFOR_SIZE( j, size_ex )
            {
                BLM_INIT();
                if( o->param.verbosity >= 10 ) bcore_sink_a_push_fa( o->param.log, "exc #<sz_t>:\n", j );

                bhvm_holor_s* h_jc = mdl_jc->data[ i ]->data[ j ];
                if( o->param.verbosity >= 10 )
                {
                    bcore_sink_a_push_fa( o->param.log, "Jacobian: " );
                    bhvm_holor_s_to_sink_nl( h_jc, o->param.log );
                }

                bhvm_holor_s* dp_ex1 = adl_dp_ex->data[ j ];
                bhvm_holor_s* dp_ex2 = bhvm_holor_s_fork_vector_isovol( BLM_CREATE( bhvm_holor_s ), dp_ex1 );
                lion_net_frame_sc_run_ap( "( y <- a, b, c ) { y = a + b ** c; }", ( const bhvm_holor_s*[] ) { dp_en2, h_jc, dp_ex2 }, &dp_en2 );
                BLM_DOWN();
            }

            f3_t dev = bhvm_value_s_fdev_equ( &dp_en1->v, &dp_en2->v );

            bl_t error = dev > o->param.max_dev;

            if( error || o->param.verbosity >= 10 )
            {
                st_s* st = BLM_CREATE( st_s );
                st_s_push_fa( st, "dp-channel: #<sz_t>", i );
                st_s_push_fa( st, ", dev: #<f3_t>", dev );
                st_s_push_fa( st, "\ngradient (dp)          : " );
                bhvm_holor_s_to_sink( dp_en1, ( bcore_sink* )st );
                st_s_push_fa( st, "\ngradient (via jacobian): " );
                bhvm_holor_s_to_sink( dp_en2, ( bcore_sink* )st );
                st_s_push_fa( st, "\n" );
                if( error )
                {
                    st_s_push_fa( &result->msg, "\nJacobian test failure:\n#<sc_t>\n", st->sc );
                    result->error = true;
                    BLM_RETURNV( lion_net_eval_result_s*, result );
                }
                else
                {
                    bcore_sink_a_push_fa( o->param.log, "#<sc_t>", st->sc );
                }
            }

            BLM_DOWN();
        }
    }

    BLM_RETURNV( lion_net_eval_result_s*, result );
}

// ---------------------------------------------------------------------------------------------------------------------

lion_net_eval_result_s* lion_net_eval_timing_s_run( const lion_net_eval_timing_s* o, lion_net_eval_result_s* result )
{
    BLM_INIT();


    BLM_RETURNV( lion_net_eval_result_s*, result );
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


