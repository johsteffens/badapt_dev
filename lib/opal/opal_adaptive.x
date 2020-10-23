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
/// adaptive

// ---------------------------------------------------------------------------------------------------------------------

func (:) bhpt_adaptive.get_adaptor_probe =
{
    probe.set_size( o.frame.get_size_ada() );
    opal_frame_s* frame = cast( opal_frame_s*, o->frame );
    ASSERT( frame.is_setup );
    BFOR_EACH( i, probe )
    {
        probe.[ i ].axon = frame.get_ap_ada( i );
        probe.[ i ].grad = frame.get_dp_ada( i );
    }
    return probe;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:) bhpt_adaptive.status_to_sink =
{
    if( verbosity >=  1 ) sink.push_fa( "#<sc_t>", ifnameof( o->_ ) );
    if( verbosity >= 10 ) o.frame.disassemble_to_sink( sink );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:builder) bhpt_builder.create_adaptive =
{
    opal_adaptive_s* adaptive = opal_adaptive_s_create();

    bcore_source* source = NULL;

    switch( *cast( aware_t*, o.src ) )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = bcore_file_open_source_path( cast( const bcore_file_path_s*, o->src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = ( bcore_source* )bcore_source_string_s_create_from_string( cast( const st_s*, o->src ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->src ) );
        }
        break;
    }

    keep( source );

    adaptive.holor_frame_en.copy( o.holor_frame_en );
    adaptive.holor_frame_ex.copy( o.holor_frame_ex );

    opal_frame_s* frame = adaptive.frame;
    const bhvm_holor_s* holor_frame_en = o.holor_frame_en;
    frame.setup_from_source( source, ( const bhvm_holor_s** )&holor_frame_en, 1 );

    ASSERT( frame.get_size_en() == 1 );
    ASSERT( frame.get_size_ex() == 1 );

    ASSERT( o.holor_frame_en.s.is_equal( &frame.get_ap_en(0).s ) );
    ASSERT( o.holor_frame_ex.s.get_volume() == frame.get_ap_ex(0).s.get_volume() );

    adaptive->src = bcore_fork( o->src );

    return (bhpt_adaptive*)adaptive;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// adaptive_cyclic

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) (void dp_buffer_create( mutable )) =
{
    o.dp_buffer =< bhvm_holor_adl_s!;
    o.dp_buffer.set_size( o.frame.unroll_size );
    foreach( $** e in o->dp_buffer )
    {
        bhvm_holor_s* h = ( *e = o.holor_frame_ex.clone() );
        h.fit_size();
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) (void dp_buffer_reset( mutable )) =
{
    if( !o->dp_buffer ) opal_adaptive_cyclic_s_dp_buffer_create( o );
    foreach( $* e in o->dp_buffer ) e.v.zro();
    o.dp_value = false;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) (void dp_buffer_apply( mutable )) =
{
    o.frame.run_dp_adl_flat( o.dp_buffer, NULL );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) (void dp_buffer_apply_reset( mutable )) =
{
    o.dp_buffer_apply();
    o.dp_buffer_reset();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) bhpt_adaptive.dendrite_pass =
{
    ASSERT( !ag_en );

    if( !o.dp_buffer ) o.dp_buffer_create();
    sz_t dp_index = ( o->frame.unroll_index == 0 ) ? o->frame.unroll_size - 1 : o->frame.unroll_index - 1;

    bhvm_holor_s* h = o.dp_buffer.[ dp_index ];
    ag_ex.v.cpy( &h.v );
    o.dp_value = true;

    if( o->frame.unroll_index == 0 ) o.dp_buffer_apply_reset();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) bhpt_adaptive.cyclic_reset =
{
    o.frame.cyclic_reset();
    if( o.dp_value ) o.dp_buffer_reset();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) bhpt_adaptive.get_adaptor_probe =
{
    bhpt_adaptor_probe_s_set_size( probe, o.frame.get_size_ada() );
    opal_frame_s* frame = o.frame.frame;
    ASSERT( frame.is_setup );
    BFOR_EACH( i, probe )
    {
        probe->data[ i ].axon = frame.get_ap_ada( i );
        probe->data[ i ].grad = frame.get_dp_ada( i );
    }
    return probe;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic) bhpt_adaptive.status_to_sink =
{
    if( verbosity >= 1 ) sink.push_fa( "#<sc_t>", ifnameof( o->_ ) );
    if( verbosity >= 10 ) o.frame.disassemble_to_sink( sink );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cyclic_builder) bhpt_builder.create_adaptive =
{
    opal_adaptive_cyclic_s* adaptive = opal_adaptive_cyclic_s_create();

    bcore_source* source = NULL;

    switch( *(aware_t*)o->src )
    {
        case TYPEOF_bcore_file_path_s:
        {
            source = bcore_file_open_source_path( cast( const bcore_file_path_s*, o->src ) );
        }
        break;

        case TYPEOF_st_s:
        {
            source = cast( bcore_source*, bcore_source_string_s_create_from_string( cast( const st_s*, o->src ) ) );
        }
        break;

        default:
        {
            ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o->src ) );
        }
        break;
    }

    keep( source );

    adaptive.holor_frame_en.copy( o->holor_frame_en );
    adaptive.holor_frame_ex.copy( o->holor_frame_ex );

    opal_frame_s* frame = keep( opal_frame_s! );
    const bhvm_holor_s* holor_frame_en = o->holor_frame_en;
    frame.setup_from_source( source, cast( const bhvm_holor_s** , holor_frame_en ), 1 );

    ASSERT( frame.get_size_en() == 1 );
    ASSERT( frame.get_size_ex() == 1 );

    ASSERT( o.holor_frame_en.s.is_equal( &frame.get_ap_en(0).s ) );
    ASSERT( o.holor_frame_ex.s.get_volume() == frame.get_ap_ex(0).s.get_volume() );

    adaptive->src = bcore_fork( o->src );

    opal_frame_cyclic_s* frame_cyclic = adaptive->frame;
    frame_cyclic.setup_from_frame( frame, o->unroll_size );

    return ( bhpt_adaptive* )adaptive;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/