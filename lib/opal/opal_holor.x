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

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

signature void clear( m @* o );
signature void parse( m @* o, m bcore_source* source );

stamp :meta_s = aware bhvm_mcode_hmeta
{
    aware bcore_inst => custom; // custom params

    /// associated mnode
    hidden bhvm_mcode_node_s -> mnode;

    /// name obtained from the corresponding node (TODO: consider moving it to mnode)
    tp_t name;

    /// pass-class (see bhvm_mcode_hmeta)
    tp_t pclass;

    // holor is transposed
    bl_t htp;

    /** Holor is a active (mutable, not constant).
     *  Active holors typically represent a variable in the virtual machine.
     *  They are normally depleted during shelving and actively initialized during setup.
     *  The opposite (passive) are holors carrying an immutable value (e.g a constant)
     *  In a network a holor is active if it depends on at least one active holor in
     *  such a manner that its change affects the resulting holor.
     *  Computations among passive holors are generally solved in the network and not converted into microcode.
     */
    bl_t active = true;

    func :.clear = { o.name = 0; o.htp = false; };

    func bhvm_mcode_hmeta.get_name    = { return o.name; };
    func bhvm_mcode_hmeta.get_pclass  = { return o.pclass; };
    func bhvm_mcode_hmeta.is_rollable = { return !o.active || o.mnode.adaptive || ( o.mnode.cyclic && o.pclass == pclass_ax1~ ); };
    func bhvm_mcode_hmeta.is_active   = { return  o.active; };

    func bhvm_mcode_hmeta.get_custom = { return o.custom; };
    func bhvm_mcode_hmeta.set_custom = { return o.custom =< custom.clone(); };

    func bhvm_mcode_hmeta.get_sem_id = { return o.mnode?.sem_id; };

    func bhvm_mcode_hmeta.get_node = { return o.mnode; };
    func bhvm_mcode_hmeta.set_node = { o.mnode =< node.fork(); };
};

stamp :meta_adl_s = x_array { :meta_s => []; };

stamp :s = aware :
{
    :meta_s      m;
    bhvm_holor_s h;
    func bcore_fp.copy_typed;

    func (void to_sink( c @* o, m bcore_sink* sink )) =
    {
        if( !o.m.active ) sink.push_fa( "<const>" );
        if( o.m.htp ) sink.push_fa( "<htp>" );
        o.h.to_sink( sink );
    };

    // appends newline
    func (void to_sink_nl( c @* o, m bcore_sink* sink )) =
    {
        o.to_sink( sink );
        sink.push_fa( "\n" );
    };

    func (void to_stdout( c @* o )) = { o.to_sink( x_sink_stdout() ); };

    // appends newline
    func (void to_stdout_nl( c @* o )) = { o.to_sink_nl( x_sink_stdout() ); };

    /** compacted version, single line */
    func (void brief_to_sink( c @* o, m bcore_sink* sink )) =
    {
        sink.push_fa( o.m.active ? "<active>" : "<const>" );
        if( o.m.htp ) sink.push_fa( "<htp>" );
        o.h.brief_to_sink( sink );
    };

    func (void brief_to_stdout( c @* o )) = { o.brief_to_sink( x_sink_stdout() ); };

    /** multiline version */
    func (void formatted_to_sink( c @* o, m bcore_sink* sink )) =
    {
        sink.push_fa( o.m.active ? "<active>" : "<const>" );
        if( o.m.htp ) sink.push_fa( "<htp>(" );
        o.h.formatted_to_sink( sink );
        if( o.m.htp ) sink.push_fa( ")" );
    };

    func (void formatted_to_stdout( c @* o )) = { o.formatted_to_sink( x_sink_stdout() ); };

    /// sets holor from text source
    func :.parse;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

func (:s) bcore_fp.copy_typed =
{
    m x_inst* inst = ( x_inst* )src;
    switch( type )
    {
        case opal_holor_s~:
        {
            assert( inst._ == opal_holor_s~ );
            o.copy( inst.cast( m opal_holor_s* ) );
        }
        break;

        case bhvm_holor_s~:
        case bmath_mf2_s~:
        case bmath_mf3_s~:
        case bmath_vf2_s~:
        case bmath_vf3_s~:
        case f2_t~:
        case f3_t~:
        case sc_t~:
        {
            o.h.copy_typed( type, inst );
        }
        break;

        case st_s~:
        {
            assert( inst._ == st_s~ );
            o.parse( bcore_source_string_s!^^.setup_from_string( inst.cast( m st_s* ) ) );
        }
        break;

        default:
        {
            ERR_fa( "Cannot convert '#<sc_t>' to 'opal_holor_s'", ifnameof( type ) );
        }
        break;
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:s) :.parse =
{
    o.m.clear();

    if( source.parse_bl( " #?'<const>'" ) )
    {
        o.parse( source );
        o.m.active = false;
    }
    else
    {
        o.h.parse( source );
    }

    // postfix
    while( source.parse_bl( " #?'~'" ) )
    {
        o->m.htp = !o->m.htp;
    }
};

// ---------------------------------------------------------------------------------------------------------------------

forward opal_sem_link_s;
forward opal_sem_cell_s;

func (:s) (void from_sem_link( m @* o, m opal_sem_link_s* link, m opal_sem_cell_s* root, m bcore_sink* log )) =
{
    ASSERT( link.up );
    ASSERT( link.cell );
    ASSERT( root );
    if( !root.parent ) ERR_fa( "(root->parent == NULL) Root is not nested. Using semantic context as root is discouraged. Preferably use a double-nested semantic frame." );
    m opal_sem_cell_s* cell = link.cell;
    m opal_sem_tree_s* tree = opal_sem_tree_s!^^;
    m opal_sem_tree_node_s* sem_tree_node = NULL;
    tree.enter( root, sem_tree_node, &sem_tree_node );
    m opal_net_cell_s* net_frame = opal_net_cell_s!^^;
    m opal_net_node_s* up_node   = opal_net_node_s!^^;
    net_frame.context = root.context.fork();
    up_node.context   = root.context.fork();

    up_node.name = link.name;
    up_node.id = tree.id_base++;
    up_node.source_point = cell.source_point.1.fork();
    up_node.set_nop_d( opal_nop_ar1_output_s! );
    net_frame.from_sem_recursive( link.up, tree, sem_tree_node, up_node, 0, log );
    up_node.solve( NULL );

    if( !up_node.result ) up_node.source_point.parse_err_fa( "Could not solve expression." );
    if( !up_node.result.h ) up_node.source_point.parse_err_fa( "Expression does not yield a holor." );

    o.copy( up_node.result.h );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

