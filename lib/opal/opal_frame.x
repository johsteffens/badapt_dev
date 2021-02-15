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
/// groups, stamps

// ---------------------------------------------------------------------------------------------------------------------

/// holor indexing group
group :hidx =
{
    signature m @* clear( m @* o );
    signature m @* push(  m @* o, sz_t index );

    signature sz_t get_idx( c @* o, sz_t index );
    signature sz_t get_pclass_idx( c @* o, c bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );
    signature sz_t get_size( c @* o );

    signature m bhvm_holor_s*     get_holor( c @* o, c bhvm_mcode_hbase_s* hbase, sz_t index );
    signature m bhvm_mcode_hmeta* get_hmeta( c @* o, c bhvm_mcode_hbase_s* hbase, sz_t index );

    signature m bhvm_holor_s*     get_pclass_holor( c @* o, c bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );
    signature m bhvm_mcode_hmeta* get_pclass_hmeta( c @* o, c bhvm_mcode_hbase_s* hbase, tp_t pclass, sz_t index );

    signature m @* replace_index( m @* o, m bcore_arr_sz_s* index_map );

    stamp :s = aware :
    {
        bcore_arr_sz_s => arr;
        func :.clear     = { if( o.arr ) o.arr.clear(); return o; };
        func :.push      = { o.arr!.push( index ); return o; };

        func :.get_idx   = { assert( index >= 0 && index < o.arr.size ); return o.arr?.[ index ]; };
        func :.get_size  = { return o.arr ? o.arr.size : 0; };
        func :.get_holor = { return hbase.get_holor( o.get_idx( index ) ); };
        func :.get_hmeta = { return hbase.get_hmeta( o.get_idx( index ) ); };

        func :.get_pclass_idx =
        {
            c bhvm_mcode_hmeta* hmeta = o.get_hmeta( hbase, index );
            return ( hmeta ) ? hmeta.get_node().get_pclass_idx( pclass ) : -1;
        };

        func :.get_pclass_holor = { return hbase.get_holor( o.get_pclass_idx( hbase, pclass, index ) ); };
        func :.get_pclass_hmeta = { return hbase.get_hmeta( o.get_pclass_idx( hbase, pclass, index ) ); };

        func :.replace_index =
        {
            foreach( m sz_t* e in o.arr )
            {
                sz_t old_index = *e;
                assert( old_index >= 0 && old_index < index_map->size );
                sz_t new_index = index_map.[ old_index ];
                if( new_index >= 0 ) *e = new_index;
            }
            return o;
        };

    };

    stamp :ads_s = aware x_array
    {
        :s [];
        wrap x_array.push_c;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/// frame member functions

signature void reset( m @* o );
signature void setup( m @* o );
signature void check_integrity( c @* o );

signature o setup_from_source(      m @* o, m bcore_source* source, c bhvm_holor_s** en, sz_t size_en );
signature o setup_from_st(          m @* o,         c st_s* st,     c bhvm_holor_s** en, sz_t size_en );
signature o setup_from_sc(          m @* o,           sc_t  sc,     c bhvm_holor_s** en, sz_t size_en );
signature o setup_from_source_adl(  m @* o, m bcore_source* source, c bhvm_holor_adl_s* en );
signature o setup_from_st_adl(      m @* o,         c st_s* st,     c bhvm_holor_adl_s* en );
signature o setup_from_sc_adl(      m @* o,           sc_t  sc,     c bhvm_holor_adl_s* en );

signature d @* create_from_source(     m bcore_source* source, c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_st(                 c st_s* st,     c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_sc(                   sc_t  sc,     c bhvm_holor_s** en, sz_t size_en );
signature d @* create_from_source_adl( m bcore_source* source, c bhvm_holor_adl_s* en );
signature d @* create_from_st_adl(             c st_s* st,     c bhvm_holor_adl_s* en );
signature d @* create_from_sc_adl(               sc_t  sc,     c bhvm_holor_adl_s* en );

signature sz_t get_size_en( c @* o ); // number of entry channels
signature sz_t get_size_ex( c @* o ); // number of exit channels
signature sz_t get_size_ada( c @* o ); // number of adaptive channels

signature m bhvm_holor_s* get_ap_en(  m @* o, sz_t index );
signature m bhvm_holor_s* get_dp_en(  m @* o, sz_t index );
signature m bhvm_holor_s* get_ap_ex(  m @* o, sz_t index );
signature m bhvm_holor_s* get_dp_ex(  m @* o, sz_t index );
signature m bhvm_holor_s* get_ap_ada( m @* o, sz_t index );
signature m bhvm_holor_s* get_dp_ada( m @* o, sz_t index );

signature m @* run( m @* o, tp_t track);
signature m @* run_ap(     m @* o, c bhvm_holor_s** en, sz_t size_en, m bhvm_holor_s** ex, sz_t size_ex );
signature m @* run_dp(     m @* o, c bhvm_holor_s** ex, sz_t size_ex, m bhvm_holor_s** en, sz_t size_en );
signature m @* run_ap_adl( m @* o, c bhvm_holor_adl_s* en, m bhvm_holor_adl_s* ex ); // allocates out
signature m @* run_dp_adl( m @* o, c bhvm_holor_adl_s* ex, m bhvm_holor_adl_s* en ); // allocates out

signature void disassemble_to_sink( c @* o, m bcore_sink* sink );
signature void cyclic_reset( m @* o );


/** Explicitly re-binds holors (typically by running setup tracks).
 *  This can be necessary when certain holors have been externally reallocated.
 *  Use with care!
 */
signature m @* bind_holors( m @* o );

stamp :s = aware :
{
    /// pre-setup parameters
    aware bcore_sink -> log;

    /// In frames the context is part of the regular parameter set including serialization.
    aware opal_context -> context;

    /// post-setup data
    bhvm_mcode_frame_s => mcf;

    bl_t is_cyclic; // indicates that the underlying graph is cyclic

    /// frame has been setup
    bl_t is_setup;

    sz_t size_en; // number of entry holors (per ap/dp cycle)
    sz_t size_ex; // number of exit holors (per ap/dp cycle)

    :hidx_s hidx_en;  // entry index
    :hidx_s hidx_ex;  // exit index
    :hidx_s hidx_ada; // adaptive index

    func :.reset =
    {
        if( !o.is_setup ) return;
        if( !o.mcf ) return;
        o.mcf.track_run( TYPEOF_track_ap_shelve );
        o.mcf.track_run( TYPEOF_track_dp_shelve );
        o.is_setup = false;
    };

    func :.bind_holors =
    {
        o.mcf.track_run( TYPEOF_track_ap_setup );
        o.mcf.track_run( TYPEOF_track_dp_setup );
        return o;
    };

    func :.setup =
    {
        if( o.is_setup ) return;
        if( !o.mcf ) return;
        o.bind_holors();
        o.is_setup = true;
    };

    func :.check_integrity =
    {
        assert( o.context );
        assert( o.mcf );
        o.mcf.check_integrity();
    };

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t is_setup = o.is_setup; o.reset(); o.is_setup = is_setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o.is_setup ) { o.reset(); o.setup(); } o.check_integrity(); };
    func bcore_inst_call . copy_x  = { if( o.is_setup ) { o.reset(); o.setup(); } o.check_integrity(); };

    /// frame setup from string or source; 'in' can be NULL
    func :.setup_from_source;
    func :.setup_from_st = { return o.setup_from_source( bcore_source_string_s_create_from_string( st )^^, en, size_en ); };
    func :.setup_from_sc = { return o.setup_from_st( st_s_create_sc( sc )^^, en, size_en ); };
    func :.create_from_source     = { return @!.setup_from_source( source, en, size_en ); };
    func :.create_from_st         = { return @!.setup_from_st( st, en, size_en ); };
    func :.create_from_sc         = { return @!.setup_from_sc( sc, en, size_en ); };
    func :.setup_from_source_adl  = { return o.setup_from_source( source, en ? en.data.cast( c bhvm_holor_s** ) : NULL, en ? en.size : 0 ); };
    func :.setup_from_st_adl      = { return o.setup_from_st( st, en ? en.data.cast( c bhvm_holor_s** ) : NULL, en ? en.size : 0 ); };
    func :.setup_from_sc_adl      = { return o.setup_from_sc( sc, en ? en.data.cast( c bhvm_holor_s** ) : NULL, en ? en.size : 0 ); };
    func :.create_from_source_adl = { return @!.setup_from_source_adl( source, en ); };
    func :.create_from_st_adl     = { return @!.setup_from_st_adl( st, en ); };
    func :.create_from_sc_adl     = { return @!.setup_from_sc_adl( sc, en ); };

    func :.get_size_en  = { return o.hidx_en .get_size(); };
    func :.get_size_ex  = { return o.hidx_ex .get_size(); };
    func :.get_size_ada = { return o.hidx_ada.get_size(); };

    func :.get_ap_en  = { return o.hidx_en .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func :.get_dp_en  = { return o.hidx_en .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };
    func :.get_ap_ex  = { return o.hidx_ex .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func :.get_dp_ex  = { return o.hidx_ex .get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };
    func :.get_ap_ada = { return o.hidx_ada.get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ax0, index ); };
    func :.get_dp_ada = { return o.hidx_ada.get_pclass_holor( o.mcf.hbase, TYPEOF_pclass_ag0, index ); };

    func (m @* run( m @* o, tp_t track )) =
    {
        ASSERT( o->mcf );
        o.mcf.track_run( track );
        return o;
    };

    /// resets all cyclic values to the initialization value
    func :.cyclic_reset = { o.mcf.track_run( TYPEOF_track_ap_cyclic_reset ); };

    func :.run_ap;
    func :.run_dp;
    func :.run_ap_adl;
    func :.run_dp_adl;
    func :.disassemble_to_sink;
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :custom_hmeta_s = aware :
{
    sz_t ur_slot;
    sz_t ur_src;
};

// ---------------------------------------------------------------------------------------------------------------------

signature void setup_from_frame( m @* o, c opal_frame_s* frame, sz_t unroll_size );

/// resets cyclic values; runs track_ap for all slots assuming all input/output holors are provided in sequence
signature void run_ap_adl_flat( m @* o, c bhvm_holor_adl_s* en, m bhvm_holor_adl_s* ex );

/// runs track_dp for all slots assuming all input/output holors are provided in sequence
signature void run_dp_adl_flat( m @* o, c bhvm_holor_adl_s* ex, m bhvm_holor_adl_s* en );

/// frame specialized in unrolling cyclic networks
stamp :cyclic_s = aware :
{
    /// pre-setup parameters
    :s => frame;

    /// number of unrolled cycles
    sz_t unroll_size = 2;

    /// state data ...

    /// frame has been setup
    bl_t is_setup = false;

    /// current unroll process index
    sz_t unroll_index = 0;

    /// unrolled ap tracks
    bhvm_mcode_track_adl_s => track_adl_ap;
    bhvm_mcode_track_adl_s => track_adl_dp;
    bhvm_mcode_track_adl_s => track_adl_ap_setup;

    /// unrolled hindex
    :hidx_ads_s hidx_ads_en;  // entry index
    :hidx_ads_s hidx_ads_ex;  // exit index

    /// functions ...
    func :.bind_holors;
    func :.reset;
    func :.setup;

    /// shelving/reconstitution
    func bcore_via_call  . shelve  = { bl_t is_setup = o.is_setup; o.reset(); o.is_setup = is_setup; /* setup flag remembers o's setup state before shelving */ };
    func bcore_via_call  . mutated = { if( o.is_setup ) { o.reset(); o.setup(); } };
    func bcore_inst_call . copy_x  = { if( o.is_setup ) { o.reset(); o.setup(); } };

    func :.get_size_en  = { return o.frame.get_size_en(); };
    func :.get_size_ex  = { return o.frame.get_size_ex(); };
    func :.get_size_ada = { return o.frame.get_size_ada(); };

    func :.run_ap;
    func :.run_ap_adl;
    func :.run_ap_adl_flat;
    func :.run_dp_adl_flat;

    func :.setup_from_frame;

    func :.disassemble_to_sink;

    /// resets all cyclic values to the initialization value
    func :.cyclic_reset =
    {
        o.frame.mcf.track_run( TYPEOF_track_ap_cyclic_reset );
        o.unroll_index = 0;
    };

};

// ---------------------------------------------------------------------------------------------------------------------

func (void sc_run_ap( sc_t sc, c bhvm_holor_s** en, sz_t size_en, m bhvm_holor_s** ex, sz_t size_ex )) =
{
    opal_frame_s_create_from_sc( sc, en, size_en )^^.run_ap( en, size_en, ex, size_ex );
};

// ---------------------------------------------------------------------------------------------------------------------

func (void sc_run_dp( sc_t sc, c bhvm_holor_s** ex, sz_t size_ex, m bhvm_holor_s** en, sz_t size_en )) =
{
    opal_frame_s_create_from_sc( sc, ex, size_ex )^^.run_dp( ex, size_ex, en, size_en );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

func (m st_s* hmeta_get_global_name_st( c bhvm_mcode_hmeta* hmeta, c opal_context* context, m st_s* st )) =
{
    st.clear();
    if( hmeta && hmeta._ == TYPEOF_opal_holor_meta_s )
    {
        m $* holor_meta = hmeta.cast( m opal_holor_meta_s* );
        if( holor_meta.sem_id && holor_meta.sem_id._ == TYPEOF_opal_sem_id_s )
        {
            holor_meta.sem_id.cast( m opal_sem_id_s* ).to_string( context, st );
        }
    }
    return st;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) (void disassemble_hbase_to_sink( c @* o, c bhvm_mcode_hbase_s* hbase, sz_t indent, m bcore_sink* sink )) =
{
    m $* st_buf = st_s!^^;
    sz_t hname_length = 0;
    sz_t hbrief_length = 0;

    foreach( m bhvm_holor_s* h in hbase->holor_adl )
    {
        m bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ __i ];
        sc_t sc_name = opal_frame_hmeta_get_global_name_st( hmeta, o->context, st_buf )->sc;
        hname_length = sz_max( hname_length, bcore_strlen( sc_name ) );
        m st_s* st = st_s!^;
        h.compact_to_sink( 12, st );
        hbrief_length = sz_max( hbrief_length, st.size );
    }

    foreach( m bhvm_holor_s* h in hbase->holor_adl )
    {
        m bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.data[ __i ];
        tp_t pclass = hmeta.get_pclass();
        sc_t sc_name = opal_frame_hmeta_get_global_name_st( hmeta, o->context, st_buf ).sc;

        m $* msg = st_s!^;
        msg.push_fa( "#rn{ }#pl3 {#<sz_t>}", indent, __i );

        m bhvm_mcode_node_s* mnode = hmeta.get_node();
        ASSERT( mnode );

        if(      pclass == TYPEOF_pclass_ax0 ) msg.push_fa( " ax0 #pl5 {[#<sz_t>]}", mnode.ax0 );
        else if( pclass == TYPEOF_pclass_ax1 ) msg.push_fa( " ax1 #pl5 {[#<sz_t>]}", mnode.ax0 );
        else if( pclass == TYPEOF_pclass_ag0 ) msg.push_fa( " ag0 #pl5 {[#<sz_t>]}", mnode.ax0 );
        else if( pclass == TYPEOF_pclass_ag1 ) msg.push_fa( " ag1 #pl5 {[#<sz_t>]}", mnode.ax0 );

        msg.push_fa( " #pn'.'{#<sc_t> }", hname_length + 1, sc_name );
        if     ( mnode.adaptive  )   msg.push_fa( " adaptive" );
        else if( mnode.cyclic )      msg.push_fa( " cyclic  " );
        else if( mnode.param )       msg.push_fa( " param   " );
        else if( hmeta.is_active() ) msg.push_fa( " active  " );
        else                         msg.push_fa( " const   " );

        m $* st = st_s!^;
        h.compact_to_sink( 12, st );

        msg.push_fa( " #pn' '{#<st_s*>} ", hbrief_length, st );

        c x_inst* custom = hmeta.get_custom();
        if( custom && custom._ == TYPEOF_opal_frame_custom_hmeta_s )
        {
            msg.push_fa( " ur_slot #pl2 {#<sz_t>}", custom.cast( m opal_frame_custom_hmeta_s* ).ur_slot );
        }

        sink.push_fa( "#<st_s*>\n", msg );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) (void disassemble_hidx_to_sink( c @* o, c bhvm_mcode_hbase_s* hbase, c bcore_arr_sz_s* hidx, sz_t indent, m bcore_sink* sink ) ) =
{
    m $* st_buf = st_s!^^;
    sz_t hname_length = 0;

    foreach( sz_t idx_ap in hidx )
    {
        m bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.[ idx_ap ];
        hname_length = sz_max( hname_length, opal_frame_hmeta_get_global_name_st( hmeta, o.context, st_buf ).size );
    }

    foreach( sz_t idx_ap in hidx )
    {
        m bhvm_mcode_hmeta* hmeta = hbase->hmeta_adl.[ idx_ap ];
        assert( hmeta );
        sink.push_fa( "#rn{ }#pn'.'{#<sc_t> } :", indent, hname_length + 1, opal_frame_hmeta_get_global_name_st( hmeta, o.context, st_buf ).sc );
        if( idx_ap >= 0 ) sink.push_fa( " (ap)#<sz_t>", idx_ap );
        m bhvm_mcode_node_s* mnode = hmeta.get_node();
        if( mnode && mnode->ag0 >= 0 ) sink.push_fa( " (dp)#<sz_t>", mnode->ag0 );
        sink.push_fa( "\n" );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) (void disassemble_track_to_sink( c @* o, c bhvm_mcode_track_s* track, sz_t indent, m bcore_sink* sink )) =
{
    if( !track ) return;
    foreach( m $* vop in track..vop )
    {
        sink.push_fa( "#rn{ }", indent );
        vop.to_sink( sink );
        sink.push_fa( "\n" );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.disassemble_to_sink =
{
    m bhvm_mcode_frame_s* mcf = o->mcf;
    m bhvm_mcode_hbase_s* hbase = mcf->hbase;

    sink.push_fa( "Holorbase size: #<sz_t>\n", hbase ? bhvm_mcode_hbase_s_get_size( hbase ) : 0 );
    sink.push_fa( "Entry channels:\n" );
    o.disassemble_hidx_to_sink( hbase, o->hidx_en.arr, 2, sink );
    sink.push_fa( "\n" );

    sink.push_fa( "Exit channels:\n" );
    o.disassemble_hidx_to_sink( hbase, o->hidx_ex.arr, 2, sink );
    sink.push_fa( "\n" );

    if( o.hidx_ada.get_size() > 0 )
    {
        sink.push_fa( "Adaptive channels:\n" );
        o.disassemble_hidx_to_sink( hbase, o->hidx_ada.arr, 2, sink );
        sink.push_fa( "\n" );
    }
    sink.push_fa( "\n" );

    sink.push_fa( "Holorbase:\n" );
    o.disassemble_hbase_to_sink( hbase, 2, sink );
    sink.push_fa( "\n" );

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

    for( sz_t i = 0; i < sizeof( track_types ) / sizeof( tp_t ); i++ )
    {
        tp_t track_type = track_types[ i ];
        m bhvm_mcode_track_s* track = mcf.track_get( track_type );
        if( track )
        {
            sink.push_fa( "#<sc_t>:\n", ifnameof( track_type ) );
            o.disassemble_track_to_sink( track, 2, sink );
            sink.push_fa( "\n" );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.setup_from_source =
{
    m $* net_cell = opal_net_cell_s!^^;
    m $* net_builder = opal_net_builder_s!^^;

    net_builder.fork_log( o.log );
    net_builder.fork_input_holors( en, size_en );
    net_builder.build_from_source( net_cell, source );

    o.hidx_en.clear();
    o.hidx_ex.clear();
    o.hidx_ada.clear();

    o.context =< net_cell.context.fork();
    o.mcf =< bhvm_mcode_frame_s!;

    net_cell.mcode_push_ap( o.mcf );
    net_cell.mcode_push_dp( o.mcf, true );

    o.size_en = net_cell.encs.size;
    o.size_ex = net_cell.excs.size;

    foreach( m opal_net_node_s* node in net_cell.encs )
    {
        /** An entry node without mnode does not actively contribute to the output of the cell.
         *  We therefore construct an mnode formally to provide a holor for the input channel
         *  with the necessary setup and shelve routines.
         */
        if( !node.mnode ) node.isolated_mcode_push( o.mcf );
        ASSERT( node.mnode.ax0 >= 0 );
        o.hidx_en.push( node.mnode.ax0 );
    }

    foreach( m opal_net_node_s* node in net_cell.excs )
    {
        ASSERT( node.mnode?.ax0 >= 0 );
        opal_frame_hidx_s_push( &o->hidx_ex, node->mnode->ax0 );
    }

    foreach( m opal_net_node_s* node  in net_cell.body; node.nop )
    {
        c bhvm_mcode_node_s* mnode = node.mnode;
        if( mnode?.adaptive && node.mnode.ax0 >= 0 ) o.hidx_ada.push( node.mnode.ax0 );
        if( mnode?.cyclic ) o.is_cyclic = true;
    }

    o.is_setup = true;
    o.reset();
    o.setup();
    o.check_integrity();

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.run_ap =
{
    ASSERT( o.is_setup );

    m bhvm_mcode_hbase_s* hbase = o.mcf?.hbase;
    c opal_frame_hidx_s* hidx_en = o.hidx_en;
    c opal_frame_hidx_s* hidx_ex = o.hidx_ex;

    ASSERT( size_en >= o.size_en );
    for( sz_t i = 0; i < o.size_en; i++ )
    {
        m bhvm_holor_s* h_m = hidx_en.get_holor( hbase, i );
        c bhvm_holor_s* h_i = en[ i ];
        ASSERT( h_i && h_i._ == TYPEOF_bhvm_holor_s );
        if( !h_m.s.is_equal( h_i.s ) )
        {
            m st_s* st = st_s!^;
            st.push_fa( "Entry channel #<sz_t> size mismatch:", i );
            st.push_fa( "\nGiven holor:   " );
            h_i.brief_to_sink( st );
            st.push_fa( "\nChannel holor: " );
            h_m.brief_to_sink( st );
            ERR_fa( "#<sc_t>\n", st->sc );
        }
        h_i.v.cpy( h_m.v );
    }

    o.mcf.track_run( TYPEOF_track_ap_cyclic_update );
    o.mcf.track_run( TYPEOF_track_ap );

    if( ex )
    {
        ASSERT( size_ex >= o.size_ex );
        for( sz_t i = 0; i < o.size_ex; i++ )
        {
            m bhvm_holor_s* h_m = hidx_ex.get_holor( hbase, i );
            m bhvm_holor_s* h_o = ex[ i ];
            ASSERT( h_o && h_o._ == TYPEOF_bhvm_holor_s );
            if( !h_m.s.is_equal( h_o.s ) ) h_o.copy_shape_type( h_m );
            if( h_o.v.size == 0 )  h_o.fit_size();
            h_m.v.cpy( h_o.v );
        }
    }

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.run_dp =
{
    ASSERT( o.is_setup );
    ASSERT( !o.is_cyclic );

    m bhvm_mcode_hbase_s* hbase = o.mcf?.hbase;
    c opal_frame_hidx_s* hidx_en = o.hidx_en;
    c opal_frame_hidx_s* hidx_ex = o.hidx_ex;

    ASSERT( size_ex >= o.size_ex );
    for( sz_t i = 0; i < o.size_ex; i++ )
    {
        sz_t idx = hidx_ex.get_pclass_idx( hbase, TYPEOF_pclass_ag0, i );
        if( idx >= 0 )
        {
            m bhvm_holor_s* h_m = hbase.get_holor( idx );
            c bhvm_holor_s* h_i = ex[ i ];
            ASSERT( h_i && h_i->_ == TYPEOF_bhvm_holor_s );
            if( !h_m.s.is_equal( h_i.s ) )
            {
                m st_s* st = st_s!^;
                st.push_fa( "Exit channel #<sz_t> shape mismatch:", i );
                st.push_fa( "\nGiven holor:   " );
                h_i.brief_to_sink( st );
                st.push_fa( "\nChannel holor: " );
                h_m.brief_to_sink( st );
                ERR_fa( "#<sc_t>\n", st.sc );
            }
            h_i.v.cpy( h_m.v );
        }
    }

    o.mcf.track_run( TYPEOF_track_dp );

    if( en )
    {
        ASSERT( size_en >= o.size_en );
        for( sz_t i = 0; i < o.size_en; i++ )
        {
            sz_t idx = hidx_en.get_pclass_idx( hbase, TYPEOF_pclass_ag0, i );
            if( idx >= 0 )
            {
                m bhvm_holor_s* h_m = hbase.get_holor( idx );
                m bhvm_holor_s* h_o = en[ i ];
                ASSERT( h_o && h_o._ == TYPEOF_bhvm_holor_s );
                if( !h_m.s.is_equal( h_o.s ) ) h_o.copy_shape_type( h_m );
                if( h_o.v.size == 0 ) h_o.fit_size();
                h_m.v.cpy( h_o.v );
            }
        }
    }

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.run_ap_adl =
{
    if( ex && ex.size != o.get_size_ex() ) ex.set_size( o.get_size_ex() );
    foreach( m $.2 e in ex; !e.1 ) e.1 = bhvm_holor_s!;
    return o.run_ap
    (
        en ? en.data.cast( c bhvm_holor_s** ) : NULL,
        en ? en.size : 0,
        ex ? ex.data.cast( m bhvm_holor_s** ) : NULL,
        ex ? ex.size : 0
    );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.run_dp_adl =
{
    if( en && en.size != o.get_size_en() ) en.set_size( o.get_size_en() );
    foreach( m $.2 e in en; !e.1 ) e.1 = bhvm_holor_s!;
    return o.run_dp
    (
        ex ? ex.data.cast( c bhvm_holor_s** ) : NULL,
        ex ? ex.size : 0,
        en ? en.data.cast( m bhvm_holor_s** ) : NULL,
        en ? en.size : 0
    );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) :.reset =
{
    if( !o.is_setup ) return;
    if( !o.frame ) return;

    if( o.frame.mcf.hbase.copy_size_limit >= 0 )
    {
        o.frame.mcf.hbase.set_size( o.frame.mcf.hbase.copy_size_limit );
        o.frame.mcf.hbase.copy_size_limit = -1;
    }

    o.frame.reset();

    o.track_adl_ap =< NULL;
    o.track_adl_dp =< NULL;
    o.track_adl_ap_setup =< NULL;

    o.unroll_index = 0;
    o.is_setup = false;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) :.bind_holors =
{
    o.frame.bind_holors();
    m bhvm_mcode_hbase_s* hbase = o.frame.mcf.hbase;
    for( sz_t i = 1; i < o.unroll_size; i++ ) o.track_adl_ap_setup.[ i ].run( hbase.holor_adl.data );
    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) :.setup =
{
    if( o.is_setup ) return;
    if( !o.frame ) return;

    ASSERT( o.unroll_size >= 2 );

    m opal_frame_s* frame = o.frame;
    frame.reset();

    o.track_adl_ap =< bhvm_mcode_track_adl_s!;
    o.track_adl_dp =< bhvm_mcode_track_adl_s!;
    o.track_adl_ap_setup =< bhvm_mcode_track_adl_s!;

    m bhvm_mcode_track_s* track0_ap        = o.frame.mcf.track_get( TYPEOF_track_ap );
    m bhvm_mcode_track_s* track0_dp        = o.frame.mcf.track_get( TYPEOF_track_dp );
    m bhvm_mcode_track_s* track0_ap_setup  = o.frame.mcf.track_get( TYPEOF_track_ap_setup );
    m bhvm_mcode_hbase_s* hbase = o.frame.mcf.hbase;

    sz_t rolled_hbase_size = hbase.holor_adl.size;
    hbase.copy_size_limit = rolled_hbase_size;

    m bcore_arr_sz_s* idx_arr_track0_ap = bcore_arr_sz_s!^^;
    track0_ap.get_index_arr( idx_arr_track0_ap );

    /// unrollable indices
    m bcore_arr_sz_s* ur_idx_arr = bcore_arr_sz_s!^^;

    foreach( sz_t src_idx in idx_arr_track0_ap; !hbase.hmeta_adl.[ src_idx ].is_rollable() ) ur_idx_arr.push( src_idx );

    m opal_frame_custom_hmeta_s* custom = opal_frame_custom_hmeta_s!^^;

    m bhvm_mcode_track_s* track_ap_prev = NULL;

    for( sz_t i = 0; i < o.unroll_size; i++ )
    {
        custom->ur_slot = i;
        m bhvm_mcode_track_s* track_ap_curr   = o.track_adl_ap.push_c( track0_ap );
        m bhvm_mcode_track_s* track_dp        = o.track_adl_dp.push_c( track0_dp );
        m bhvm_mcode_track_s* track_ap_setup  = o.track_adl_ap_setup.push_c( track0_ap_setup );

        m opal_frame_hidx_s* hidx_en = o.hidx_ads_en.push_c( o.frame.hidx_en );
        m opal_frame_hidx_s* hidx_ex = o.hidx_ads_ex.push_c( o.frame.hidx_ex );

        if( i > 0 )
        {
            m bcore_arr_sz_s* ur_idx_map = bcore_arr_sz_s!^^.fill( rolled_hbase_size, -1 );
            m bcore_arr_sz_s* rc_idx_map = bcore_arr_sz_s!^^.fill( rolled_hbase_size, -1 );
            foreach( sz_t src_idx in ur_idx_arr )
            {
                sz_t dst_idx = hbase.push_copy_from_index( src_idx );
                ur_idx_map.[ src_idx ] = dst_idx;

                m bhvm_mcode_hmeta* src_hmeta = hbase->hmeta_adl.[ src_idx ];
                m bhvm_mcode_hmeta* dst_hmeta = hbase->hmeta_adl.[ dst_idx ];
                m bhvm_mcode_node_s* src_node = src_hmeta.get_node();
                if( src_node.cyclic ) rc_idx_map.data[ src_node.ax1 ] = dst_idx;

                dst_hmeta.set_custom( custom );
            }
            track_ap_curr.replace_index_via_map( ur_idx_map );
            track_ap_prev.replace_index_via_map( rc_idx_map );

            track_ap_setup.remove_unmapped_output( ur_idx_map );
            track_ap_setup.replace_index_via_map( ur_idx_map );
            track_dp.replace_index_via_map( ur_idx_map );

            hidx_en.replace_index( ur_idx_map );
            hidx_ex.replace_index( ur_idx_map );
        }

        track_ap_prev = track_ap_curr;
    }

    frame.setup();
    for( sz_t i = 1; i < o.unroll_size; i++ ) o.track_adl_ap_setup.[ i ].run( hbase.holor_adl.data );

    o.is_setup = true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) :.setup_from_frame =
{
    o.reset();
    o.frame =< frame.clone();
    o.frame.reset();
    o.unroll_size = unroll_size;
    o.setup();
};

// ---------------------------------------------------------------------------------------------------------------------

func( :cyclic_s) :.run_ap =
{
    ASSERT( o.frame );
    assert( o.is_setup );
    assert( o.unroll_index < o.unroll_size );

    m opal_frame_s* frame = o.frame;
    m bhvm_mcode_hbase_s* hbase = frame.mcf.hbase;
    c opal_frame_hidx_s* hidx_en = o.hidx_ads_en .[ o.unroll_index ];
    c opal_frame_hidx_s* hidx_ex = o.hidx_ads_ex .[ o.unroll_index ];
    c bhvm_mcode_track_s* track  = o.track_adl_ap.[ o.unroll_index ];

    ASSERT( size_en >= frame.size_en );

    for( sz_t i = 0; i < frame.size_en; i++ )
    {
        m bhvm_holor_s* h_m = hidx_en.get_holor( hbase, i );
        c bhvm_holor_s* h_i = en[ i ];
        ASSERT( h_i && h_i._ == TYPEOF_bhvm_holor_s );
        if( !h_m.s.is_equal( h_i.s ) ) ERR_fa( "Input shape mismatch" );
        h_i.v.cpy( h_m.v );
    }

    if( o.unroll_index == 0 ) frame.mcf.track_run( TYPEOF_track_ap_cyclic_update );
    track.run( hbase.holor_adl.data );

    if( ex )
    {
        ASSERT( size_ex >= frame.size_ex );
        for( sz_t i = 0; i < frame.size_ex; i++ )
        {
            m bhvm_holor_s* h_m = hidx_ex.get_holor( hbase, i );
            m bhvm_holor_s* h_o = ex[ i ];
            ASSERT( h_o && h_o._ == TYPEOF_bhvm_holor_s );
            if( !h_m.s.is_equal( h_o.s ) ) h_o.copy_shape_type( h_m );
            if( h_o.v.size == 0 ) h_o.fit_size();
            h_m.v.cpy( h_o.v );
        }
    }

    o.unroll_index = ( o.unroll_index + 1 ) % o.unroll_size;

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

func( :cyclic_s) :.run_ap_adl =
{
    if( ex && ex.size != o.get_size_ex() ) ex.set_size( o.get_size_ex() );
    foreach( m $.2 e in ex; !e.1 ) e.1 = bhvm_holor_s!;
    return o.run_ap
    (
        en ? en.data.cast( c bhvm_holor_s** ) : NULL,
        en ? en.size : 0,
        ex ? ex.data.cast( m bhvm_holor_s** ) : NULL,
        ex ? ex.size : 0
    );
};

// ---------------------------------------------------------------------------------------------------------------------

func( :cyclic_s) :.disassemble_to_sink =
{
    m opal_frame_s* frame = o.frame;
    m bhvm_mcode_frame_s* mcf = frame.mcf;
    m bhvm_mcode_hbase_s* hbase = mcf.hbase;

    sink.push_fa( "Holorbase:\n" );
    frame.disassemble_hbase_to_sink( hbase, 2, sink );
    sink.push_fa( "\n" );

    if( frame.hidx_ada.get_size() > 0 )
    {
        sink.push_fa( "Adaptive channels:\n" );
        frame.disassemble_hidx_to_sink( hbase, frame->hidx_ada.arr, 2, sink );
        sink.push_fa( "\n" );
    }

    sink.push_fa( "\n" );
    sink.push_fa( "Global Tracks:\n" );

    m bhvm_mcode_track_s* track = NULL;

    track = mcf.track_get( TYPEOF_track_dp_setup );
    if( track )
    {
        sink.push_fa( "#<sc_t>:\n", ifnameof( track->name ) );
        frame.disassemble_track_to_sink( track, 2, sink );
        sink.push_fa( "\n" );
    }

    track = mcf.track_get( TYPEOF_track_ap_cyclic_reset );
    if( track )
    {
        sink.push_fa( "#<sc_t>:\n", ifnameof( track->name ) );
        frame.disassemble_track_to_sink( track, 2, sink );
        sink.push_fa( "\n" );
    }

    track = mcf.track_get( TYPEOF_track_ap_cyclic_update );
    if( track )
    {
        sink.push_fa( "#<sc_t>:\n", ifnameof( track->name ) );
        frame.disassemble_track_to_sink( track, 2, sink );
        sink.push_fa( "\n" );
    }

    sink.push_fa( "\n" );
    sink.push_fa( "Unroll index: #<sz_t>\n", o.unroll_index );
    sink.push_fa( "Unroll slots: #<sz_t>\n", o.unroll_size );

    for( sz_t i = 0; i < o->unroll_size; i++ )
    {
        sink.push_fa( "  Roll slot: #<sz_t>", i );

        sink.push_fa( "\n  Entry channels:\n" );
        frame.disassemble_hidx_to_sink( hbase, o->hidx_ads_en.data[ i ].arr, 4, sink );

        sink.push_fa( "\n  Exit channels:\n" );
        frame.disassemble_hidx_to_sink( hbase, o->hidx_ads_ex.data[ i ].arr, 4, sink );

        track = o.track_adl_ap.[ i ];
        sink.push_fa( "\n  #<sc_t>:\n", ifnameof( track->name ) );
        frame.disassemble_track_to_sink( track, 4, sink );

        track = o.track_adl_dp.[ i ];
        sink.push_fa( "\n  #<sc_t>:\n", ifnameof( track->name ) );
        frame.disassemble_track_to_sink( track, 4, sink );

        track = o.track_adl_ap_setup.[ i ];
        sink.push_fa( "\n  #<sc_t>:\n", ifnameof( track->name ) );
        frame.disassemble_track_to_sink( track, 4, sink );

        sink.push_fa( "\n  #r32{-}\n" );
    }

    sink.push_fa( "\n" );
};

// ---------------------------------------------------------------------------------------------------------------------

func( :cyclic_s) :.run_ap_adl_flat =
{
    ASSERT( o.frame );
    o.cyclic_reset();
    sz_t size_en = o.frame.get_size_en();
    sz_t size_ex = o.frame.get_size_ex();

    if( ex && ex.size != size_ex * o.unroll_size ) ex.set_size( size_ex * o.unroll_size );
    foreach( m $.2 e in ex; !e.1 ) e.1 = bhvm_holor_s!;

    for( sz_t i = 0; i < o.unroll_size; i++ )
    {
        ASSERT( i * size_en < en.size );
        ASSERT( ex ? ( i * size_ex < ex.size ) : true );
        o.run_ap
        (
            ( const bhvm_holor_s** )( en.data + i * size_en ),
            size_en,
            ex ? ( ex.data + i * size_ex ) : NULL,
            size_ex
        );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func( :cyclic_s) :.run_dp_adl_flat =
{
    ASSERT( o.frame );
    ASSERT( o.is_setup );

    sz_t size_en = o.frame.get_size_en();
    sz_t size_ex = o.frame.get_size_ex();

    if( en && en.size != size_en * o.unroll_size ) en.set_size( size_en * o.unroll_size );
    foreach( m $.2 e in en; !e.1 ) e.1 = bhvm_holor_s!;

    m opal_frame_s* frame = o.frame;
    m bhvm_mcode_hbase_s* hbase = frame.mcf.hbase;

    frame.run( TYPEOF_track_dp_cyclic_zero_grad );

    for( sz_t i = 0; i < o.unroll_size; i++ )
    {
        sz_t unroll_index = ( o.unroll_size - i - 1 ) % o.unroll_size;
        c opal_frame_hidx_s*  hidx_en  = o.hidx_ads_en.[ unroll_index ];
        c opal_frame_hidx_s*  hidx_ex  = o.hidx_ads_ex.[ unroll_index ];
        c bhvm_mcode_track_s* track_dp = o.track_adl_dp.[ unroll_index ];

        ASSERT(        unroll_index * size_ex < ex.size          );
        ASSERT( en ? ( unroll_index * size_en < en.size ) : true );

        c bhvm_holor_s** p_ex = ( const bhvm_holor_s** )( ex->data + unroll_index * size_ex );
            m bhvm_holor_s** p_en = en ? (  bhvm_holor_s** )( en->data + unroll_index * size_en ) : NULL;

        for( sz_t i = 0; i < size_ex; i++ )
        {
            sz_t idx = hidx_ex.get_pclass_idx( hbase, TYPEOF_pclass_ag0, i );
            if( idx >= 0 )
            {
                m bhvm_holor_s* h_m = hbase.get_holor( idx );
                c bhvm_holor_s* h_i = p_ex[ i ];
                ASSERT( h_i && h_i._ == TYPEOF_bhvm_holor_s );
                if( !h_m.s.is_equal( h_i.s ) ) ERR_fa( "Input shape mismatch" );
                h_i.v.cpy( h_m.v );
            }
        }

        track_dp.run( hbase.holor_adl.data );

        if( p_en )
        {
            for( sz_t i = 0; i < size_en; i++ )
            {
                sz_t idx = hidx_en.get_pclass_idx( hbase, TYPEOF_pclass_ag0, i );
                if( idx >= 0 )
                {
                    m bhvm_holor_s* h_m = hbase.get_holor( idx );
                    m bhvm_holor_s* h_o = p_en[ i ];
                    ASSERT( h_o && h_o._ == TYPEOF_bhvm_holor_s );
                    if( !h_m.s.is_equal( h_o.s ) ) h_o.copy_shape_type( h_m );
                    if( h_o.v.size == 0 ) h_o.fit_size();
                    h_m.v.cpy( h_o.v );
                }
            }
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
