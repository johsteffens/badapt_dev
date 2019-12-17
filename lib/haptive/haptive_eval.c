/** Author and Copyright 2019 Johannes Bernhard Steffens
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

#include "haptive_eval.h"

// ---------------------------------------------------------------------------------------------------------------------

haptive_op* haptive_eval_e2e_s_input_op_create( vd_t arg, sz_t in_idx, tp_t in_name )
{
    assert( *(aware_t*)arg == TYPEOF_haptive_eval_e2e_s );
    haptive_eval_e2e_s* o = arg;
    if( in_idx < 0 && in_idx >= o->in->size ) return NULL;
    haptive_op_ar0_input_s* input = haptive_op_ar0_input_s_create();
    input->h = bhvm_hf3_s_create();
    bhvm_hf3_s_copy_shape( input->h, o->in->data[ in_idx ] );
    return ( haptive_op* )input;
}

// ---------------------------------------------------------------------------------------------------------------------

s2_t haptive_eval_grad_s_run( const haptive_eval_grad_s* o )
{
    if( o->verbosity >= 2 ) bcore_sink_a_push_fa( o->log, "Gradient test:\n" );
    BLM_INIT();
    bhvm_hf3_vm_frame_s* vmf = o->vmf;

    bhvm_hf3_adl_s* tgt  = BLM_CREATE( bhvm_hf3_adl_s );
    bhvm_hf3_adl_s* out0 = BLM_CREATE( bhvm_hf3_adl_s ); // default output
    bhvm_hf3_adl_s* out1 = BLM_CREATE( bhvm_hf3_adl_s ); // varied output
    bhvm_hf3_adl_s* grad = BLM_CREATE( bhvm_hf3_adl_s );

    ASSERT( o->in );
    ASSERT( o->out );
    bhvm_hf3_adl_s_copy( tgt, o->out );

    // compute out0, e0
    bhvm_hf3_vm_frame_s_input_set_all( vmf, o->in );
    bhvm_hf3_vm_frame_s_mcode_run( vmf, TYPEOF_mcode_name_infer );
    bhvm_hf3_vm_frame_s_output_get_all( vmf, out0 );

    ASSERT( tgt->size == out0->size );

    // verify shapes
    BFOR_EACH( i, tgt )
    {
        const bhvm_hf3_s* ht = tgt->data[ i ];
        const bhvm_hf3_s* ho = out0->data[ i ];
        if( !bhvm_hf3_s_shape_equal( ht, ho ) )
        {
            st_s* msg = st_s_create();
            bcore_sink* sink = (bcore_sink*)msg;
            bcore_sink_a_push_fa( sink, "Exit channel #<sz_t>: Output has different shape than target.\n", i );
            bcore_sink_a_push_fa( sink, "Output: " );
            bhvm_hf3_s_brief_to_sink( ho, sink );
            bcore_sink_a_push_fa( sink, "\n" );
            bcore_sink_a_push_fa( sink, "Target: " );
            bhvm_hf3_s_brief_to_sink( ht, sink );
            bcore_sink_a_push_fa( sink, "\n" );
            ERR_fa( "#<sc_t>", msg->sc );
            st_s_discard( msg );
        }
    }

    f3_t e0 = bhvm_hf3_adl_s_f3_sub_sqr( tgt, out0 );

    // compute gradients
    bhvm_hf3_adl_s_copy( grad, out0 );
    bhvm_hf3_adl_s_sub(  grad, tgt, grad );
    bhvm_hf3_adl_s_mul_scl_f3(  grad, 2.0, grad );
    bhvm_hf3_vm_frame_s_mcode_run( vmf, TYPEOF_mcode_name_zero_adaptive_grad );
    bhvm_hf3_vm_frame_s_output_set_paired_all( vmf, grad );
    bhvm_hf3_vm_frame_s_mcode_run( vmf, TYPEOF_mcode_name_bp_grad );
    bhvm_hf3_vm_frame_s_check_integrity( vmf );

    f3_t g_dev_sum = 0;
    f3_t g_dev_wgt = 0;

    ASSERT( o->max_dev > 0 );

    /* Significance is the relative change of energy for a given variance.
     * Tests below min_significance are not accurate enough to produce
     * testable results
     * If significance * max_dev < 1E-15 then the energy gradient cannot be resolved
     * in f3_t. Such results are not counted as gradient deviation.
     */
    f3_t min_significance = 1E-15 / o->max_dev;

    BFOR_EACH( i, &vmf->arr_holor )
    {
        if( vmf->arr_holor.data[ i ].p.type != TYPEOF_holor_type_adaptive ) continue;

        bhvm_hf3_vm_holor_s* vm_ha = bhvm_hf3_vm_frame_s_holors_get_by_index( vmf, i );
        bhvm_hf3_vm_holor_s* vm_hg = bhvm_hf3_vm_frame_s_holors_get_by_index( vmf, vm_ha->p.idx_paired );

        sc_t name = bhvm_hf3_vm_frame_s_ifnameof( vmf, vm_ha->p.name );

        if( o->verbosity >= 5 )
        {
            bcore_sink_a_push_fa( o->log, "Adaptive holor '#<sc_t>' (address #<sz_t>): ", name, i );
            bhvm_hf3_s_brief_to_sink( &vm_ha->h, o->log );
            bcore_sink_a_push_fa( o->log, "':\n", i );
        }

        bhvm_hf3_s* ha = &vm_ha->h;
        bhvm_hf3_s* hg = &vm_hg->h;

        ASSERT( ha->v_size == hg->v_size );

        for( sz_t i = 0; i < ha->v_size; i++ )
        {
            f3_t v0 = ha->v_data[ i ];

            // set variation
            ha->v_data[ i ] = v0 + o->epsilon;
            bhvm_hf3_vm_frame_s_mcode_run( vmf, TYPEOF_mcode_name_infer );
            bhvm_hf3_vm_frame_s_output_get_all( vmf, out1 );
            f3_t e1 = bhvm_hf3_adl_s_f3_sub_sqr( tgt, out1 );

            f3_t d1 = e1 - e0;

            f3_t max_e = f3_max( f3_abs( e0 ), f3_abs( e1 ) );
            f3_t significance = f3_abs( d1 ) * ( ( max_e > 0 ) ? 1.0 / max_e : 0 );

            f3_t g0 = hg->v_data[ i ];
            f3_t g1 = d1 / o->epsilon;

            f3_t g_dev = f3_abs( g1 - g0 );
            f3_t g_max = f3_max( f3_abs( g1 ), f3_abs( g0 ) );
            f3_t inv_g_max = ( g_max > 0 ) ? 1.0 / g_max : 0;
            g_dev *= inv_g_max;

            bl_t counted = ( significance >= min_significance );

            if( counted )
            {
                g_dev_sum += g_dev;
                g_dev_wgt += 1;
            }

            // reset variation
            ha->v_data[ i ] = v0;

            if( o->verbosity >= 5 )
            {
                sz_t n = 14;
                if( i == 0 )
                {
                    bcore_sink_a_push_fa( o->log, "  " );
                    bcore_sink_a_push_fa( o->log, "|#pn {index}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn { v0}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn { e1}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn { d1}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn { g0}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn { g1}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn { g_dev}", n );
                    bcore_sink_a_push_fa( o->log, "|#pn {significance}", n );
                    bcore_sink_a_push_fa( o->log, "\n" );
                }
                bcore_sink_a_push_fa( o->log, "  " );
                bcore_sink_a_push_fa( o->log, "|#pn {#<sz_t>}", n, i );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, v0 );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, e1 );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, d1 );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, g0 );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, g1 );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, g_dev );
                bcore_sink_a_push_fa( o->log, "|#pn {#<f3_t>}", n, significance );
                bcore_sink_a_push_fa( o->log, "|#pn {#<sc_t>}", n, counted ? "" : "(not counted)" );
                bcore_sink_a_push_fa( o->log, "\n" );
            }
        }
    }

    f3_t g_dev = ( g_dev_wgt > 0 ) ? ( g_dev_sum / g_dev_wgt ) : 0;
    bl_t success = ( g_dev <= o->max_dev );
    if( !success || o->verbosity >= 2 ) bcore_sink_a_push_fa( o->log, "Gradient deviation: #<f3_t>.\n", g_dev );

    BLM_RETURNV( s2_t, success ? 0 : 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

s2_t haptive_eval_e2e_s_run( const haptive_eval_e2e_s* o )
{
    BLM_INIT();

    if( o->name.size > 0 && o->verbosity >= 2 )
    {
        bcore_sink_a_push_fa( o->log, "#<sc_t>:\n", o->name.sc );
    }

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

    f3_t time_parse_sem = 0;
    f3_t time_build_net = 0;

    /// semantic cell
    haptive_sem_cell_s* sem_frame = BLM_A_PUSH( haptive_sem_cell_s_create_frame() );
    haptive_sem_cell_s_parse_signature( sem_frame, BLM_A_PUSH( bcore_source_string_s_create_from_string( &o->sig ) ) );
    bcore_source_point_s_set( &sem_frame->source_point, source );
    CPU_TIME_OF( haptive_sem_cell_s_parse_body( sem_frame, source ), time_parse_sem );

    /// network cell
    haptive_net_cell_s* net_frame = BLM_CREATE( haptive_net_cell_s );
    CPU_TIME_OF( haptive_net_cell_s_from_sem_cell( net_frame, sem_frame, haptive_eval_e2e_s_input_op_create, ( vd_t )o, o->verbosity > 5 ? o->log : NULL ), time_build_net );

    if( o->log && o->verbosity >= 3 )
    {
        bcore_sink_a_push_fa( o->log, "Network Cell:\n" );
        bcore_sink_a_push_fa( o->log, "  Entry channels . #<sz_t>\n", net_frame->encs.size );
        bcore_sink_a_push_fa( o->log, "  Body size ...... #<sz_t>\n", net_frame->body.size );
        bcore_sink_a_push_fa( o->log, "  Exit channels .. #<sz_t>\n", net_frame->excs.size );

        if( o->verbosity >= 2 && net_frame->body.size < 1000 )
        {
            bcore_sink_a_push_fa( o->log, "Network Graph Structure:\n" );
            haptive_net_cell_s_graph_to_sink( net_frame, o->log );
        }
    }

    /// test copying of net_cell
    {
        haptive_net_cell_s* cloned_cell = BLM_A_PUSH( haptive_net_cell_s_clone( net_frame ) );
        ASSERT( haptive_net_cell_s_is_consistent( cloned_cell ) );
    }

    f3_t time_vm_build_infer   = 0;
    f3_t time_vm_build_bp_grad = 0;
    f3_t time_vm_run_setup     = 0;
    f3_t time_vm_run_infer     = 0;

    bhvm_hf3_vm_frame_s* vm_frame = BLM_CREATE( bhvm_hf3_vm_frame_s );

    CPU_TIME_OF( haptive_cell_s_vm_build_infer(   net_frame, vm_frame ), time_vm_build_infer );
    CPU_TIME_OF( haptive_cell_s_vm_build_bp_grad( net_frame, vm_frame ), time_vm_build_bp_grad );

    haptive_net_cell_s_vm_build_zero_adaptive_grad( net_frame, vm_frame );
    haptive_vm_build_setup(  vm_frame, 1234 );
    haptive_vm_build_shelve( vm_frame );

    haptive_net_cell_s_vm_set_input(  net_frame, vm_frame );
    haptive_net_cell_s_vm_set_output( net_frame, vm_frame );
    haptive_bhvm_hf3_vm_frame_s_pull_names( vm_frame );

    CPU_TIME_OF( bhvm_hf3_vm_frame_s_mcode_run( vm_frame, TYPEOF_mcode_name_setup ), time_vm_run_setup );

    if( o->in ) bhvm_hf3_vm_frame_s_input_set_all( vm_frame, o->in );
    bhvm_hf3_vm_frame_s_check_integrity( vm_frame );

    CPU_TIME_OF( bhvm_hf3_vm_frame_s_mcode_run( vm_frame, TYPEOF_mcode_name_infer ), time_vm_run_infer );

    for( sz_t i = 1; i < o->infer_cycles; i++ )
    {
        bhvm_hf3_vm_frame_s_mcode_run( vm_frame, TYPEOF_mcode_name_infer );
    }

    bhvm_hf3_vm_frame_s_check_integrity( vm_frame );

    bl_t success = true;

    if( o->verbosity >= 5 )
    {
        bcore_sink_a_push_fa( o->log, "Timing (ms):\n" );
        bcore_sink_a_push_fa( o->log, "  Parsing ................ #<f3_t>\n", 1000 * time_parse_sem );
        bcore_sink_a_push_fa( o->log, "  Building network ....... #<f3_t>\n", 1000 * time_build_net );
        bcore_sink_a_push_fa( o->log, "  VM: Building 'infer' ... #<f3_t>\n", 1000 * time_vm_build_infer );
        bcore_sink_a_push_fa( o->log, "  VM: Building 'bp_grad' . #<f3_t>\n", 1000 * time_vm_build_bp_grad );
        bcore_sink_a_push_fa( o->log, "  VM: Running  'setup' ... #<f3_t>\n", 1000 * time_vm_run_setup );
        bcore_sink_a_push_fa( o->log, "  VM: Running  'infer' ... #<f3_t>\n", 1000 * time_vm_run_infer );
        if( o->infer_cycles > 1 )
        {
            bcore_sink_a_push_fa( o->log, "  VM: Infer-cycles ....... #<sz_t>\n", o->infer_cycles );
        }

        bcore_sink_a_push_fa( o->log, "VM Microcode:\n" );

        BFOR_EACH( i, &vm_frame->lib_mcode.arr )
        {
            const bhvm_hf3_vm_mcode_s* mcode = vm_frame->lib_mcode.arr.data[ i ];
            sc_t name = bhvm_hf3_vm_frame_s_ifnameof( vm_frame, mcode->name );
            bcore_sink_a_push_fa( o->log, "  #p20.{#<sc_t> } #<sz_t>\n", name, mcode->size );
        }

        if( o->verbosity >= 10 )
        {
            BFOR_EACH( i, &vm_frame->lib_mcode.arr )
            {
                const bhvm_hf3_vm_mcode_s* mcode = vm_frame->lib_mcode.arr.data[ i ];
                bhvm_hf3_vm_frame_s_mcode_to_sink( vm_frame, mcode->name, o->log );
            }
        }
    }

    for( sz_t i = 0; i < net_frame->excs.size; i++ )
    {
        tp_t name = net_frame->excs.data[ i ]->name;
        bhvm_hf3_s* h_vm = &bhvm_hf3_vm_frame_s_output_get_holor( vm_frame, i )->h;
        if( o->out && i < o->out->size )
        {
            bhvm_hf3_s* h_out = o->out->data[ i ];

            if( !bhvm_hf3_s_shape_equal( h_vm, h_out ) )
            {
                bcore_sink_a_push_fa( o->log, "Output '#<sc_t>': Shape mismatch.\n", bhvm_hf3_vm_frame_s_ifnameof( vm_frame, name ) );
                bcore_sink_a_push_fa( o->log, "Returned: ");
                bhvm_hf3_s_brief_to_sink( h_vm, o->log );
                bcore_sink_a_push_fa( o->log, "\n");
                bcore_sink_a_push_fa( o->log, "Expected: ");
                bhvm_hf3_s_brief_to_sink( h_out, o->log );
                bcore_sink_a_push_fa( o->log, "\n");
                success = false;
            }
            else
            {
                f3_t dev = bhvm_hf3_s_fdev_equ( h_vm, h_out );
                if( dev > o->max_dev )
                {
                    bcore_sink_a_push_fa( o->log, "Output '#<sc_t>':\n", bhvm_hf3_vm_frame_s_ifnameof( vm_frame, name ) );
                    bhvm_hf3_s_to_sink_nl( h_vm, o->log );
                    bcore_sink_a_push_fa( o->log, "Deviation: #<f3_t>.\n", dev );
                    success = false;
                }
            }
        }
        else
        {
            if( o->log && o->verbosity >= 2 )
            {
                bcore_sink_a_push_fa( o->log, "Output '#<sc_t>':\n", bhvm_hf3_vm_frame_s_ifnameof( vm_frame, name ) );
                bhvm_hf3_s_to_sink_nl( h_vm, o->log );
            }
        }
    }

    if( o->grad )
    {
        haptive_eval_grad_s* grad = BLM_A_PUSH( haptive_eval_grad_s_clone( o->grad ) );
        if( !grad->in  ) grad->in = bcore_fork( o->in );
        if( !grad->out ) grad->in = bcore_fork( o->out );
        bhvm_hf3_vm_frame_s_attach( &grad->vmf, bcore_fork( vm_frame ) );
        bcore_sink_a_attach( &grad->log, bcore_fork( o->log ) );
        grad->verbosity = 0;
        haptive_eval_grad_s_run( grad ); // run quietly
        grad->verbosity = o->verbosity;
        s2_t grad_result = haptive_eval_grad_s_run( grad ); // second run to test reentrance
        if( grad_result > 0 ) success = false;
    }

    if( o->verbosity >= 1 )
    {
        if( o->name.size > 0 ) bcore_sink_a_push_fa( o->log, "#p20 {#<sc_t>} : ", o->name.sc );
        bcore_sink_a_push_fa( o->log, success ? "OK" : "FAIL" );
        bcore_sink_a_push_fa( o->log, "\n" );
    }

    BLM_RETURNV( s2_t, success ? 0 : 1 );
}

// ---------------------------------------------------------------------------------------------------------------------

s2_t haptive_eval_set_s_run( const haptive_eval_set_s* o )
{
    BLM_INIT();

    if( o->set_name.size > 0 && o->verbosity > 0 )
    {
        bcore_sink_a_push_fa( o->log, "#<sc_t>:\n", o->set_name.sc );
    }
    s2_t ret_val = 0;
    for( sz_t i = 0; i < o->arr.size; i++ )
    {
        haptive_eval* eval = o->arr.data[ i ];
        if( !eval ) continue;
        if( eval->_ == TYPEOF_haptive_eval_e2e_s )
        {
            haptive_eval_e2e_s* e2e = haptive_eval_e2e_s_clone( ( haptive_eval_e2e_s* )eval );
            if( e2e->sig.size == 0 ) st_s_copy( &e2e->sig, &o->sig );
            if( !e2e->in  ) e2e->in  = bcore_fork( o->in  );
            if( !e2e->out ) e2e->out = bcore_fork( o->out );
            if( o->verbosity >= 0 ) e2e->verbosity = o->verbosity;
            if( o->max_dev   >= 0 ) e2e->max_dev   = o->max_dev;

            bcore_sink_a_attach( &e2e->log, bcore_fork( o->log ) );

            s2_t err_val = haptive_eval_e2e_s_run( e2e );
            ret_val = s2_max( err_val, ret_val );

            haptive_eval_e2e_s_discard( e2e );
        }
        else if( eval->_ == TYPEOF_haptive_eval_set_s )
        {
            haptive_eval_set_s* set = haptive_eval_set_s_clone( ( haptive_eval_set_s* )eval );
            if( set->sig.size == 0 ) st_s_copy( &set->sig, &o->sig );
            if( !set->in  ) set->in  = bcore_fork( o->in  );
            if( !set->out ) set->out = bcore_fork( o->out );
            if( o->verbosity >= 0 ) set->verbosity = o->verbosity;
            if( o->max_dev   >= 0 ) set->max_dev   = o->max_dev;

            bcore_sink_a_attach( &set->log, bcore_fork( o->log ) );

            s2_t err_val = haptive_eval_set_s_run( set );
            ret_val = s2_max( err_val, ret_val );

            haptive_eval_set_s_discard( set );
        }
        else
        {
            ERR_fa( "Unsupported evaluation object '<#sc_t>'.", ifnameof( eval->_ ) );
        }
    }

    BLM_RETURNV( s2_t, ret_val );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t haptive_eval_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "haptive_eval" ) ) )
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
            bcore_plant_compile( "haptive_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


