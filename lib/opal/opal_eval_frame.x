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
/// opal_frame_s

// ---------------------------------------------------------------------------------------------------------------------

/** Estimates jacobians for entry and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [in-channels][out-channels]
 */

func (opal_frame) (void mutable_estimate_jacobian_en( mutable, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )) =
{
    ASSERT( o.is_setup );

    bhvm_holor_adl_s* adl_en = scope( en.clone(), scope_func );
    bhvm_holor_adl_s* adl_ex = scope( bhvm_holor_adl_s!, scope_func );
    bhvm_holor_adl_s* adl_rf = scope( bhvm_holor_adl_s!, scope_func );
    o.run_ap_adl( adl_en, adl_ex );
    adl_rf.copy( adl_ex );

    jac_mdl.clear();
    jac_mdl.set_size( adl_en.size );

    for( sz_t i = 0; i < adl_en.size; i++ )
    {
        bhvm_holor_s* h_en = adl_en.[ i ];
        bhvm_holor_adl_s* jac_adl = jac_mdl.[ i ] = bhvm_holor_adl_s!;
        jac_adl.set_size( adl_ex.size );

        for( sz_t j = 0; j < h_en.v.size; j++ )
        {
            f3_t v_en = h_en.v.get_f3( j );
            h_en.v.set_f3( j, v_en + epsilon );
            o.run_ap_adl( adl_en, adl_ex );
            for( sz_t k = 0; k < adl_ex.size; k++ )
            {
                bhvm_holor_s* h_ex = adl_ex.[ k ];
                bhvm_holor_s* h_rf = adl_rf.[ k ];

                if( !jac_adl.[ k ] ) jac_adl.[ k ] = bhvm_holor_s!;
                bhvm_holor_s* h_jc = jac_adl.[ k ];
                if( h_jc.v.size == 0 )
                {
                    h_jc.s.set_data_na( 2, h_ex.v.size, h_en.v.size );
                    h_jc.set_type( TYPEOF_f3_t );
                    h_jc.fit_size();
                }

                for( sz_t l = 0; l < h_ex.v.size; l++ )
                {
                    f3_t v_ex = h_ex.v.get_f3( l );
                    f3_t v_rf = h_rf.v.get_f3( l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    h_jc.v.set_f3( j * h_jc.s.[ 0 ] + l, v_gr );
                }
            }
            h_en.v.set_f3( j, v_en );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (opal_frame) (void estimate_jacobian_en( const, const bhvm_holor_adl_s* en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )) =
{
    scope( o.clone() ).mutable_estimate_jacobian_en( en, epsilon, jac_mdl );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Estimates jacobians for adaptive and exit channels of last axon pass, given epsilon.
 *  jac_mdl stores jacobians in the form [ada-channels][out-channels]
 */
func (opal_frame) (void mutable_estimate_jacobian_ada( mutable, const bhvm_holor_adl_s* adl_en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )) =
{
    ASSERT( o.is_setup );

    bhvm_holor_adl_s* adl_ex = scope( bhvm_holor_adl_s!, scope_func );
    o.run_ap_adl( adl_en, adl_ex );

    sz_t size_ada = o.hidx_ada.get_size();

    jac_mdl.clear();
    jac_mdl.set_size( size_ada );

    for( sz_t i = 0; i < size_ada; i++ )
    {
        bhvm_holor_s* h_ada = o.get_ap_ada( i );
        bhvm_holor_adl_s* jac_adl = jac_mdl.[ i ] = bhvm_holor_adl_s!;
        jac_adl.set_size( o.size_ex );

        for( sz_t j = 0; j < h_ada.v.size; j++ )
        {
            f3_t v_ada = h_ada.v.get_f3( j );
            h_ada.v.set_f3( j, v_ada + epsilon );
            o.mcf.track_run( TYPEOF_track_ap );
            for( sz_t k = 0; k < o.size_ex; k++ )
            {
                bhvm_holor_s* h_ex = o.get_ap_ex( k );
                bhvm_holor_s* h_rf = adl_ex.[ k ];

                if( !jac_adl.[ k ] ) jac_adl.[ k ] = bhvm_holor_s!;
                bhvm_holor_s* h_jc = jac_adl.[ k ];
                if( h_jc.v.size == 0 )
                {
                    h_jc.s.set_data_na( 2, h_ex.v.size, h_ada.v.size );
                    h_jc.set_type( TYPEOF_f3_t );
                    h_jc.fit_size();
                }

                for( sz_t l = 0; l < h_ex.v.size; l++ )
                {
                    f3_t v_ex = h_ex.v.get_f3( l );
                    f3_t v_rf = h_rf.v.get_f3( l );
                    f3_t v_gr = ( v_ex - v_rf ) / epsilon;
                    h_jc.v.set_f3( j * h_jc.s.[ 0 ] + l, v_gr );
                }
            }
            h_ada.v.set_f3( j, v_ada );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (opal_frame) (void estimate_jacobian_ada( const, const bhvm_holor_adl_s* adl_en, f3_t epsilon, bhvm_holor_mdl_s* jac_mdl )) =
{
    scope( o.clone(), scope_func ).mutable_estimate_jacobian_ada( adl_en, epsilon, jac_mdl );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:plain) :.run =
{
    if( o.param.name.size > 0 && o.param.verbosity >= 2 ) o.param.log.push_fa( "#<sc_t>:\n", o.param.name.sc );
    if( !o.param.src ) ERR_fa( "Source missing." );

    bcore_source* source = NULL;
    bcore_sink* log = o.param.log;
    sz_t verbosity = o.param.verbosity;

    switch( *(aware_t*)o.param.src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = scope( cast( bcore_file_open_source_path( cast( o.param.src, const bcore_file_path_s* ) ), bcore_source* ), source );
        }
        break;

        case TYPEOF_st_s:
        {
            source = scope( cast( bcore_source_string_s_create_from_string( cast( o.param.src, const st_s* ) ), bcore_source* ), source );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o.param.src ) );
        }
        break;
    }

    const bhvm_holor_adl_s* adl_ap_en = o.param.in;
          bhvm_holor_adl_s* adl_ap_ex = scope( bhvm_holor_adl_s!, scope_func );

    opal_frame_s* frame0 = scope( opal_frame_s!, scope_func );
    if( verbosity >= 20 ) frame0.log = fork( log );

    frame0.setup_from_source_adl( source, adl_ap_en );

    /// test frame recovery/copying
    if( o.param.recovery_test )
    {
        opal_frame_s* frame1 = scope( opal_frame_s!, scope_func );
        bcore_bin_ml_a_copy( frame1, frame0 );
        frame0 = frame1;
    }

    /// test copying
    opal_frame_s* frame = scope( frame0.clone(), scope_func );

    if( frame.size_en > 0 )
    {
        if( !adl_ap_en )
        {
            WRN_fa( "Entry holors were not defined." );
        }
        else if( adl_ap_en.size != frame.size_en )
        {
            WRN_fa( "Number of expected entry holors (#<sz_t>) differs from number of provided entry holors (#<sz_t>).", frame.size_en, adl_ap_en.size );
        }
    }

    for( sz_t i = 0; i < o.ap_cycles; i++ )
    {
        frame.run_ap_adl( adl_ap_en, adl_ap_ex );

        if( verbosity >= 2 )
        {
            log.push_fa( "Output (cycle #pl3 {#<sz_t>}): ", i );
            foreach( $* e in adl_ap_ex )
            {
                e.brief_to_sink( log );
                log.push_fa( "#<sc_t>", __i + 1 < adl_ap_ex.size ? ", " : "\n" );
            }
        }
    }

    for( sz_t i = 0; i < adl_ap_ex.size; i++ )
    {
        bhvm_holor_s* h_hbo = adl_ap_ex.[ i ];
        if( o.param.out && o.param.out.size > i )
        {
            bhvm_holor_s* h_out = o.param.out.[ i ];
            bl_t shape_dev = !h_out.s.is_equal( &h_hbo.s );
            bl_t value_dev = shape_dev || ( h_out.v.fdev_equ( &h_hbo.v ) > o.param.max_dev );
            if( shape_dev || value_dev )
            {
                st_s* msg = scope( st_s!, msg );
                bcore_sink* sink = cast( msg, bcore_sink* );
                sink.push_fa( "#<sc_t> deviation at output holor '#<sz_t>':", shape_dev ? "Shape" : "Value", i );
                sink.push_fa( "\n#p20.{Frame output} " );
                h_hbo.brief_to_sink( sink );
                sink.push_fa( "\n#p20.{Expected output} " );
                h_out.brief_to_sink( sink );
                ERR_fa( "#<st_s*>\n", msg );
            }
        }
        else
        {
            if( verbosity >= 0 )
            {
                log.push_fa( "Frame out channel '#<sz_t>':\n", i );
                h_hbo.to_sink_nl( o.param.log );
            }
        }
    }

    if( o.param.verbosity >= 10 )
    {
        log.push_fa( "\nBegin microcode disassembly\n\n" );
        frame.disassemble_to_sink( log );
        log.push_fa( "End microcode disassembly\n\n" );
    }

    if( o.param.jacobian_test )
    {
        u3_t rval = 1234;

        if( verbosity >= 10 ) log.push_fa( "\nJacobian DP Test:\n" );

        bhvm_holor_adl_s* adl_dp_en = scope( adl_ap_en.clone(), scope_local );
        bhvm_holor_adl_s* adl_dp_ex = scope( adl_ap_ex.clone(), scope_local );
        foreach( $* e in adl_dp_en ) e.zro();

        foreach( $* e in adl_dp_ex )
        {
            e.v.set_random_u3( 1.0, -1, 1, &rval );
            if( verbosity >= 10 )
            {
                log.push_fa( "Gradient exc #<sz_t>: ", __i );
                e.to_sink_nl( log );
            }
        }

        frame.run_dp_adl( adl_dp_ex, adl_dp_en );

        sz_t size_ex = frame.get_size_ex();
        bhvm_holor_mdl_s* mdl_jc = scope( bhvm_holor_mdl_s!, scope_local );

        /// testing entry channels
        if( frame.get_size_en() )
        {
            if( verbosity >= 10 ) log.push_fa( "\nTesting #<sz_t> entry channels:\n", frame.get_size_en() );
            frame.estimate_jacobian_en( adl_ap_en, o.param.epsilon, mdl_jc );

            for( sz_t i = 0; i < frame.get_size_en(); i++ )
            {
                if( verbosity >= 10 ) log.push_fa( "enc #<sz_t>:\n", i );

                bhvm_holor_s* dp_en1 = adl_dp_en.[ i ];
                bhvm_holor_s* dp_en2 = scope( bhvm_holor_s!, scope_local ).copy_vector_isovol( dp_en1 );
                dp_en2.v.zro();

                for( sz_t j = 0; j < size_ex; j++ )
                {
                    if( verbosity >= 10 ) log.push_fa( "exc #<sz_t>:\n", j );

                    bhvm_holor_s* h_jc = mdl_jc.[ i ].[ j ];
                    if( verbosity >= 10 )
                    {
                        log.push_fa( "Jacobian: " );
                        h_jc.to_sink_nl( log );
                    }

                    bhvm_holor_s* dp_ex1 = adl_dp_ex.[ j ];
                    bhvm_holor_s* dp_ex2 = scope( bhvm_holor_s!, scope_local ).fork_vector_isovol( dp_ex1 );

                    opal_frame_sc_run_ap
                    (
                        "( y <- a, b, c ) { y = a + b ** c; }",
                        verbatim_C{ ( const bhvm_holor_s*[] ) { dp_en2, h_jc, dp_ex2 } },
                        3,
                        &dp_en2,
                        1
                    );
                }

                f3_t dev = dp_en1.v.fdev_equ( &dp_en2.v );

                bl_t error = dev > o.param.max_dev;

                if( error || verbosity >= 10 )
                {
                    st_s* st = scope( st_s!, scope_local );
                    st.push_fa( "dp-channel: #<sz_t>", i );
                    st.push_fa( ", dev: #<f3_t>", dev );
                    st.push_fa( "\ngradient (dp)          : " );
                    dp_en1.to_sink( cast( st, bcore_sink* ) );
                    st.push_fa( "\ngradient (via jacobian): " );
                    dp_en2.to_sink( cast( st, bcore_sink* ) );
                    st.push_fa( "\n" );
                    if( error )
                    {
                        result.msg.push_fa( "\n#<sc_t>:", o.param.name.sc );
                        result.msg.push_fa( "\nJacobian test failure:\n#<sc_t>\n", st.sc );
                        result.error = true;
                        return result;
                    }
                    else
                    {
                        log.push_fa( "#<sc_t>", st.sc );
                    }
                }
            }
        }

        /// testing adaptive channels
        if( frame.get_size_ada() )
        {
            if( verbosity >= 10 ) log.push_fa( "\nTesting #<sz_t> adaptive  channels:\n", frame.get_size_ada() );

            frame.estimate_jacobian_ada( adl_ap_en, o.param.epsilon, mdl_jc );

            for( sz_t i = 0; i < frame.get_size_ada(); i++ )
            {
                if( verbosity >= 10 ) log.push_fa( "adc #<sz_t>:\n", i );

                const bhvm_holor_s* dp_ada1 = frame.get_dp_ada( i );
                bhvm_holor_s* dp_ada2 = scope( bhvm_holor_s!, scope_local ).copy_vector_isovol( dp_ada1 );
                dp_ada2.v.zro();

                for( sz_t j = 0; j < size_ex; j++ )
                {
                    if( verbosity >= 10 ) log.push_fa( "exc #<sz_t>:\n", j );

                    bhvm_holor_s* h_jc = mdl_jc.[ i ].[ j ];
                    if( verbosity >= 10 )
                    {
                        log.push_fa( "Jacobian: " );
                        h_jc.to_sink_nl( log );
                    }

                    bhvm_holor_s* dp_ex1 = adl_dp_ex.[ j ];
                    bhvm_holor_s* dp_ex2 = scope( bhvm_holor_s!, scope_local ).fork_vector_isovol( dp_ex1 );

                    opal_frame_sc_run_ap
                    (
                        "( y <- a, b, c ) { y = a + b ** c; }",
                        verbatim_C{( const bhvm_holor_s*[] ) { dp_ada2, h_jc, dp_ex2 }},
                        3,
                        &dp_ada2,
                        1
                    );
                }

                f3_t dev = dp_ada1.v.fdev_equ( &dp_ada2.v );

                bl_t error = dev > o.param.max_dev;

                if( error || verbosity >= 10 )
                {
                    st_s* st = scope( st_s!, scope_local );
                    st.push_fa( "dp-channel: #<sz_t>", i );
                    st.push_fa( ", dev: #<f3_t>", dev );
                    st.push_fa( "\ngradient (dp)          : " );
                    dp_ada1.to_sink( cast( st, bcore_sink* ) );
                    st.push_fa( "\ngradient (via jacobian): " );
                    dp_ada2.to_sink( cast( st, bcore_sink* ) );
                    st.push_fa( "\n" );
                    if( error )
                    {
                        result.msg.push_fa( "\nJacobian test failure:\n#<sc_t>\n", st.sc );
                        result.error = true;
                        return result;
                    }
                    else
                    {
                        log.push_fa( "#<sc_t>", st.sc );
                    }
                }
            }
        }
    }

    return result;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
