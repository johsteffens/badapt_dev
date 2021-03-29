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

stamp :s = aware bhpt_adaptive
{
    // === architecture parameters ================================

    aware x_inst => src;      // source (bcore_file_path_s or st_s with inline code)  (just for reference)
    opal_frame_s frame;

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // ==============================================================

    // === adaptive functions =======================================

    func bhpt_adaptive.get_format_en = { format.copy( o.holor_frame_en ); return format; };
    func bhpt_adaptive.get_format_ex = { format.copy( o.holor_frame_ex ); return format; };
    func bhpt_adaptive.axon_pass     = { o.frame.run_axon_pass( ax_en, 1, ax_ex, 1 ); };
    func bhpt_adaptive.dendrite_pass = { o.frame.run_dendrite_pass( ag_ex, 1, ( ag_en ) ? &ag_en : NULL, ( ag_en ) ? 1 : 0 ); };
    func bhpt_adaptive.cyclic_reset  = { o.frame.cyclic_reset(); };
    func bhpt_adaptive.rebind_holors = { o.frame.bind_holors(); };
    func bhpt_adaptive.get_adaptor_probe;
    func bhpt_adaptive.status_to_sink;

    // ==============================================================

    // === shell functions ==========================================

};

// ---------------------------------------------------------------------------------------------------------------------

stamp :builder_s = aware bhpt_builder
{
    aware x_inst => src; // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // === builder functions =======================================

    func bhpt_builder.set_format_en = { o.holor_frame_en.copy( format ); };
    func bhpt_builder.set_format_ex = { o.holor_frame_ex.copy( format ); };
    func bhpt_builder.create_adaptive;

    // ==============================================================
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :cyclic_s = aware bhpt_adaptive
{
    // === architecture parameters ================================

    aware x_inst => src;      // source (bcore_file_path_s or st_s with inline code)  (just for reference)
    opal_frame_cyclic_s frame;

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;

    // ==============================================================

    /// accumulated dp data
    bhvm_holor_adl_s => dp_buffer;
    bl_t dp_value; // true in case a value was stored

    // === adaptive functions =======================================

    func bhpt_adaptive.get_format_en = { format.copy( o.holor_frame_en ); return format; };
    func bhpt_adaptive.get_format_ex = { format.copy( o.holor_frame_ex ); return format; };

    func bhpt_adaptive.axon_pass = { o.frame.run_axon_pass( ax_en, 1, ax_ex, 1 ); };
    func bhpt_adaptive.dendrite_pass;
    func bhpt_adaptive.cyclic_reset;
    func bhpt_adaptive.get_adaptor_probe;
    func bhpt_adaptive.rebind_holors = { o.frame.bind_holors(); };
    func bhpt_adaptive.status_to_sink;

    // ==============================================================
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :cyclic_builder_s = aware bhpt_builder
{
    aware x_inst => src; // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_s holor_frame_en;
    bhvm_holor_s holor_frame_ex;
    sz_t unroll_size;

    // === builder functions =======================================

    func bhpt_builder.set_format_en = { o.holor_frame_en.copy( format ); };
    func bhpt_builder.set_format_ex = { o.holor_frame_ex.copy( format ); };
    func bhpt_builder.create_adaptive;

    // ==============================================================
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive

// ---------------------------------------------------------------------------------------------------------------------

func (:s) bhpt_adaptive.get_adaptor_probe =
{
    probe.set_size( o.frame.get_size_ada() );
    ASSERT( o.frame.is_setup );
    foreach( m $* e in probe )
    {
        e.axon = o.frame.cast(m $*).get_ap_ada(__i);
        e.grad = o.frame.cast(m $*).get_dp_ada(__i);
    }
    return probe;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) bhpt_adaptive.status_to_sink =
{
    if( verbosity >=  1 ) sink.push_fa( "#<sc_t>", ifnameof( o._ ) );

    if( verbosity >=  5 )
    {
        sink.push_fa( "\nSource Code:\n" );
        o.frame.source_code_to_sink( sink );
    }

    if( verbosity >= 10 )
    {
        o.frame.disassemble_to_sink( sink );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:builder_s) bhpt_builder.create_adaptive =
{
    d opal_adaptive_s* adaptive = opal_adaptive_s!;

    m bcore_source* source = NULL;

    switch( o.src._ )
    {
        case bcore_file_path_s~:
        {
            source = bcore_file_open_source_path( o.src.cast( c bcore_file_path_s* ) )^^;
        }
        break;

        case st_s~:
        {
            source = bcore_source_string_s_create_from_string( o.src.cast( c st_s* ) )^^.cast( m bcore_source* );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o.src ) );
        }
        break;
    }

    adaptive.holor_frame_en.copy( o.holor_frame_en );
    adaptive.holor_frame_ex.copy( o.holor_frame_ex );

    m opal_frame_s* frame = adaptive.frame;
    c bhvm_holor_s* holor_frame_en = o.holor_frame_en;

    frame.setup_from_source( source, holor_frame_en, 1 );

    ASSERT( frame.get_size_en() == 1 );
    ASSERT( frame.get_size_ex() == 1 );

    ASSERT( o.holor_frame_en.s.is_equal( &frame.get_ap_en(0).s ) );
    ASSERT( o.holor_frame_ex.s.get_volume() == frame.get_ap_ex(0).s.get_volume() );

    adaptive.src = o.src.fork();

    return adaptive;
};

// ---------------------------------------------------------------------------------------------------------------------
/// shell

func (:s) bcore_shell.op_group = { return :op~; };
group :op = retrievable
{
    stamp :status_s =
    {
        sz_t verbosity = 10;
        func bcore_shell_op.key = { return "status"; };
        func bcore_shell_op.info = { return "outputs status of current adaptive; verbosity: 0 ... 10"; };
        func bcore_shell_op.run = { obj.cast(::s*).status_to_sink( o.verbosity, sink ); };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive_cyclic

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) (void dp_buffer_create( m @* o )) =
{
    o.dp_buffer =< bhvm_holor_adl_s!;
    o.dp_buffer.set_size( o.frame.unroll_size );
    foreach( m $** e in o.dp_buffer )
    {
        m bhvm_holor_s* h = ( *e = o.holor_frame_ex.clone() );
        h.fit_size();
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) (void dp_buffer_reset( m @* o )) =
{
    if( !o.dp_buffer ) opal_adaptive_cyclic_s_dp_buffer_create( o );
    foreach( m $* e in o.dp_buffer ) e.v.zro();
    o.dp_value = false;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) (void dp_buffer_apply( m @* o )) =
{
    o.frame.run_dendrite_pass_adl_flat( o.dp_buffer, NULL );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) (void dp_buffer_apply_reset( m @* o )) =
{
    o.dp_buffer_apply();
    o.dp_buffer_reset();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) bhpt_adaptive.dendrite_pass =
{
    ASSERT( !ag_en );

    if( !o.dp_buffer ) o.dp_buffer_create();
    sz_t dp_index = ( o.frame.unroll_index == 0 ) ? o.frame.unroll_size - 1 : o.frame.unroll_index - 1;

    m bhvm_holor_s* h = o.dp_buffer.[ dp_index ];
    ag_ex.v.cpy( &h.v );
    o.dp_value = true;

    if( o.frame.unroll_index == 0 ) o.dp_buffer_apply_reset();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) bhpt_adaptive.cyclic_reset =
{
    o.frame.cyclic_reset();
    if( o.dp_value ) o.dp_buffer_reset();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) bhpt_adaptive.get_adaptor_probe =
{
    bhpt_adaptor_probe_s_set_size( probe, o.frame.get_size_ada() );
    m opal_frame_s* frame = o.frame.frame;
    ASSERT( frame.is_setup );
    foreach( m $* e in probe )
    {
        e.axon = frame.get_ap_ada(__i);
        e.grad = frame.get_dp_ada(__i);
    }
    return probe;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_s) bhpt_adaptive.status_to_sink =
{
    if( verbosity >=  1 ) sink.push_fa( "#<sc_t>", ifnameof( o._ ) );

    if( verbosity >=  5 )
    {
        sink.push_fa( "\nSource Code:\n" );
        o.frame.source_code_to_sink( sink );
    }

    if( verbosity >= 10 )
    {
        o.frame.disassemble_to_sink( sink );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_builder_s) bhpt_builder.create_adaptive =
{
    d opal_adaptive_cyclic_s* adaptive = opal_adaptive_cyclic_s!;

    m bcore_source* source = NULL;

    switch( o.src._ )
    {
        case bcore_file_path_s~:
        {
            source = bcore_file_open_source_path( o.src.cast( c bcore_file_path_s* ) )^^;
        }
        break;

        case st_s~:
        {
            source = bcore_source_string_s_create_from_string( o.src.cast( c st_s* ) )^^;
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o.src ) );
        }
        break;
    }

    adaptive.holor_frame_en.copy( o.holor_frame_en );
    adaptive.holor_frame_ex.copy( o.holor_frame_ex );

    m opal_frame_s* frame = opal_frame_s!^;
    c bhvm_holor_s* holor_frame_en = o.holor_frame_en;
    frame.setup_from_source( source, holor_frame_en, 1 );

    ASSERT( frame.get_size_en() == 1 );
    ASSERT( frame.get_size_ex() == 1 );

    ASSERT( o.holor_frame_en.s.is_equal( frame.get_ap_en(0).s.1 ) );
    ASSERT( o.holor_frame_ex.s.get_volume() == frame.get_ap_ex(0).s.get_volume() );

    adaptive.src = o.src.fork();

    adaptive.frame.setup_from_frame( frame, o.unroll_size );

    return adaptive;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
