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

group :ar0 =
{
    feature o run( @* o, mutable opal_frame_s* r );
    stamp :log_s =
    {
        ::selector_s selector;

        func :.run =
        {
            $* hidx = o.selector.get_hidx( r, opal_frame_hidx_s!^ );
            foreach( sz_t idx in hidx )
            {
                $* h = r.mcf.hbase.holor_adl.[ idx ];
                $* m = r.mcf.hbase.hmeta_adl.[ idx ].cast( opal_holor_meta_s* );
            }
            return o;
        };
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
