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

/// Frame operators

/**********************************************************************************************************************/
/// groups, stamps

feature er_t parse( mutable @* o, mutable x_source* source );
feature o run( mutable @* o );

stamp :selector_s =
{
    opal_sem_id_s sem_id;
    bl_t ax0; // main axon
    bl_t ag0; // main axon gradient
    bl_t ax1; // auxiliary axon
    bl_t ag1; // auxiliary axon gradient
    bl_t param;    // node is a parameter
    bl_t adaptive; // node is adaptive
    bl_t cyclic;   // node is cyclic

    /// syntax: sem_id ([param|adaptive|cyclic]) ([a{x|g}{0|1}][ws ...])
    func :.parse =
    {
        o.sem_id.parse( source );
        source.parse_fa( " " );
        if( source.parse_bl( "#?'(' " ) )
        {
            while( !source.parse_bl( " #=?')'" ) )
            {
                if( source.parse_bl( " #?w'param'"    ) ) o.param = true;
                if( source.parse_bl( " #?w'adaptive'" ) ) o.adaptive = true;
                if( source.parse_bl( " #?w'cyclic'"   ) ) o.cyclic = true;
                if( source.eos() ) break;
            }
            source.parse_fa( ") " );
        }

        if( source.parse_bl( "#?'(' " ) )
        {
            while( !source.parse_bl( " #=?')'" ) )
            {
                if( source.parse_bl( " #?w'ax0'"    ) ) o.ax0 = true;
                if( source.parse_bl( " #?w'ax1'"    ) ) o.ax1 = true;
                if( source.parse_bl( " #?w'ag0'"    ) ) o.ag0 = true;
                if( source.parse_bl( " #?w'ag1'"    ) ) o.ag1 = true;
                if( source.eos() ) break;
            }
            source.parse_fa( ") " );
        }
        return 0;
    };

    func( hidx get_hidx( @* o, opal_frame_s* frame, m opal_frame_hidx_s* hidx ) ) =
    {
        hidx.clear();

        foreach( bhvm_mcode_node_s* node in frame.mcf.nbase )
        {
            if
            (
                ( o.param    && node.param ) ||
                ( o.adaptive && node.adaptive ) ||
                ( o.cyclic   && node.cyclic )
            )
            {
                if( node.sem_id.cast( opal_sem_id_s* ).find( o.sem_id ) >= 0 )
                {
                    if( o.ax0 && node.ax0 >= 0 ) hidx.push( node.ax0 );
                    if( o.ax1 && node.ax1 >= 0 ) hidx.push( node.ax1 );
                    if( o.ag0 && node.ag0 >= 0 ) hidx.push( node.ag0 );
                    if( o.ag1 && node.ag1 >= 0 ) hidx.push( node.ag1 );
                }
            }
        };

        return hidx;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

group :ar0 =
{
    feature o setup( mutable @* o, mutable opal_frame_s* r );
    stamp :log_s =
    {
        aware x_sink -> log;

        /// setup-params
        ::selector_s selector;

        /// run-params

        opal_frame_s -> r;
        bhvm_holor_adl_s      holor_adl;
        opal_holor_meta_adl_s hmeta_adl;

        /// functions
        func :.setup =
        {
            $* hidx = o.selector.get_hidx( r, opal_frame_hidx_s!^ );
            o.holor_adl.set_size( 0 );
            o.hmeta_adl.set_size( 0 );
            foreach( sz_t idx in hidx )
            {
                o.holor_adl.push_d( r.mcf.hbase.holor_adl.[ idx ].fork() );
                o.hmeta_adl.push_d( r.mcf.hbase.hmeta_adl.[ idx ].cast( mutable opal_holor_meta_s* ).fork() );
            }
            return o;
        };

        func ::.run =
        {
            for( sz_t i = 0; i < o.holor_adl.size; i++ )
            {
                o.log.push_fa( "Hello world!\n" );
            }
            return o;
        };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
