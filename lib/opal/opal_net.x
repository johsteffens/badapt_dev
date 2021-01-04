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
/// :node_s

// ---------------------------------------------------------------------------------------------------------------------

/// recursive trace; exits when the enter membrane of the root cell is reached
func (:node_s) (void trace_to_sink( c @* o, sz_t indent, m bcore_sink* sink )) =
{
    if( !o )
    {
        sink.push_fa( "(NULL)" );
        return;
    }

    bl_t recurring = o.flag;

    if( recurring ) sink.push_fa( "(recurring)" );

    o.cast(m $*).flag = true;

    if( o.result ) o.result.h.brief_to_sink( sink );

    sc_t symbol = "";
    if( o.nop )
    {
        sc_t symbol = o.nop.symbol();
        if( !symbol ) symbol = ifnameof( o.nop._ );
        sink.push_fa( "(#<sc_t>)", symbol );
    }
    else
    {
        sink.push_fa( "(noop)", symbol );
    }

    if( !recurring )
    {
        for( sz_t i = 0; i < o.upls.size; i++ )
        {
            sz_t incr = 4;
            sink.push_fa( "\n#rn{ }#rn{-}", indent, incr );
            m opal_net_node_s* node = o.upls.[ i ].node;
            node.trace_to_sink( indent + incr, sink );
        }
    }

    o.cast(m $*).flag = false;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:node_s) (void err_fa( m @* o, sc_t format, ... )) =
{
    va_list args;
    va_start( args, format );
    if( o.source_point )
    {
        o.source_point.parse_err_fv( format, args );
    }
    else
    {
        bcore_err_fv( format, args );
    }
    va_end( args );
};

// ---------------------------------------------------------------------------------------------------------------------

/// calls op-solve and sets node-holor
func(:node_s) (void nop_solve( m @* o, m opal_holor_s** arg_h )) =
{
    o.result =< opal_nop_solve_result_s!;

    if( !o.nop.solve( o.context, arg_h, o.result ) )
    {
        sc_t name = o.nop.symbol();
        if( !name ) name = ifnameof( o.nop._ );
        m st_s* msg = st_s!^^;
        msg.push_fa( "Operator '#<sc_t>' failed:", name );
        if( o.result.msg ) msg.push_fa( " #<sc_t>", o.result.msg.sc );
        msg.push_fa( "\n" );
        sz_t arity = o.nop.arity();
        for( sz_t i = 0; i < arity; i++ )
        {
            msg.push_fa( "arg[#<sz_t>]: ", i );
            if( arg_h[ i ] )
            {
                arg_h[ i ].brief_to_sink( msg );
            }
            else
            {
                msg.push_fa( "null" );
            }
            msg.push_fa( "\n" );
        }
        o.err_fa( "#<sc_t>", msg.sc );
    }

    if( !o.result.h ) o.result =< NULL;
};

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively skips identities.
 *  Assumes initial state was normal and downlinks not set
 */
func( :node_s) (void skip_identities( m @* o )) =
{
    if( o.flag ) return;
    o.flag = true;
    foreach( m $* e in o.upls )
    {
        m $* node = e.node;
        while( node && node.nop && node.nop._ == TYPEOF_opal_nop_ar1_identity_s ) node = node.upls.[ 0 ].node;
        ASSERT( e.node = node );
        node.skip_identities();
    }
    o.flag = false;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :cell_s

// ---------------------------------------------------------------------------------------------------------------------

/** Normalizes network structure to the following result:
 *  Body references all nodes (including entry and exit nodes)
 *  Entry and exit references are forked accordingly.
 *  Node id is identical to body-index.
 */
func (s2_t cmp_vd( vc_t o, vc_t v1, vc_t v2 )) =
{
    return ( *( vd_t* )v2 > *( vd_t* )v1 ) ? 1 : ( *( vd_t* )v2 < *( vd_t* )v1 ) ? -1 : 0;
};

func (:cell_s) :.normalize =
{
    m bcore_arr_vd_s* arr = bcore_arr_vd_s!^^;
    foreach( m $* e in o.body ) arr.push( e );
    foreach( m $* e in o.encs ) arr.push( e );
    foreach( m $* e in o.excs ) arr.push( e );

    // sort references descending (to move zeros to the end)
    verbatim_C
    {
        bcore_array_a_sort_f( ( bcore_array* )arr, 0, -1, ( bcore_cmp_f ){ .f = opal_net_cmp_vd, .o = NULL }, -1 );
    }

    // remove zeros
    if( arr.size > 0 )
    {
        for( sz_t i = 0; i < arr.size; i++ )
        {
            if( arr.[ i ] == NULL )
            {
                for( sz_t j = i + 1; j < arr.size; j++ ) ASSERT( arr.[ j ] == NULL );
                arr.size = i;
                break;
            }
        }
    }

    // remove duplicates
    if( arr.size > 1 )
    {
        sz_t d = 1;
        for( sz_t i = 1; i < arr.size; i++ ) if( arr.[ i - 1 ] != arr.[ i ] ) arr.[ d++ ] = arr.[ i ];
        arr.size = d;
    }

    // fork references
    for( sz_t i = 0; i < arr.size; i++ ) arr.[ i ] = bcore_fork( arr.[ i ] );

    // new body
    o.body.set_size( 0 );
    for( sz_t i = 0; i < arr.size; i++ )
    {
        m opal_net_node_s* node = o.body.push_d( ( opal_net_node_s* )arr.[ i ] );
        assert( node == arr.[ i ] );
        node.id = i;
        node.flag = false;
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/// Checks consistency of a normalized cell
func (:cell_s) :.is_consistent =
{
    foreach( const $* node in o.body )
    {
        if( node.flag ) return false;
        if( node.id != __i ) return false;
        foreach( const $* e in node.upls )
        {
            if( e.node.id < 0 ) return false;
            if( e.node.id >= o.body.size ) return false;
            if( e.node != o.body.[ e.node.id ] ) return false;
        }

        foreach( const $* e in node.dnls )
        {
            if( e.node.id < 0 ) return false;
            if( e.node.id >= o.body.size ) return false;
            if( e.node != o.body.[ e.node.id ] ) return false;
        }
        if( node.result && !node.result.h.h.is_consistent() ) return false;
    }

    foreach( const $* node in o.encs )
    {
        if( node.id < 0 ) return false;
        if( node.id >= o.body.size ) return false;
        if( node != o.body.[ node.id ] ) return false;
        if( node.result && !node.result.h.h.is_consistent() ) return false;
    }

    foreach( const $* node in o.excs )
    {
        if( node.id < 0 ) return false;
        if( node.id >= o.body.size ) return false;
        if( node != o.body.[ node.id ] ) return false;
        if( node.result && !node.result.h.h.is_consistent() ) return false;
    }

    return true;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) bcore_inst_call.copy_x =
{
    foreach( m :node_s* node in o.body )
    {
        ASSERT( node.id == __i );
        foreach( m :link_s* e in node.upls )
        {
            ASSERT( e.node.id >= 0 && e.node.id < o.body.size );
            e.node = o.body.data[ e.node.id ];
        }
        foreach( m :link_s* e in node.dnls )
        {
            ASSERT( e.node.id >= 0 && e.node.id < o.body.size );
            e.node = o.body.data[ e.node.id ];
        }
    }

    foreach( m :node_s.2 node in o.encs )
    {
        sz_t id = node.1.id;
        ASSERT( id >= 0 && id < o.body.size );
        node.1 =< o.body.[ id ].fork();
    }

    foreach( m :node_s.2 node in o.excs )
    {
        sz_t id = node.1.id;
        ASSERT( id >= 0 && id < o.body.size );
        node.1 =< o.body.[ id ].fork();
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) :.set_downlinks =
{
    o.clear_flags();
    o.clear_downlinks();
    foreach( m :node_s* node in o.excs ) node.set_downlinks();
    o.clear_flags();
    assert( o.is_consistent() );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes not reachable via uplink from exit channels
 *  Creates a warning in case an entry channel is unreachable.
 */
func (:cell_s) (void remove_unreachable_nodes( m @* o )) =
{
    o.clear_flags();
    foreach( m :node_s* node in o.excs ) node.set_flags();
    foreach( m :node_s* node in o.encs )
    {
        if( !node.flag && ( !( node.result && node.result.h.h.v.size > 0 ) ) )
        {
            node.source_point.parse_msg_to_sink_fa
            (
                BCORE_STDERR,
                "Warning: Entry channel [#<sz_t>] '#<sc_t>' has no effect.",
                __i,
                node.context.ifnameof( node.name )
            );
        }
        node.flag = true;
    }

    foreach( m :node_s.2 node in o.body ) if( !node.1.flag ) node.1 =< NULL;
    o.normalize();

    ASSERT( o.is_consistent() );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Removes all body-nodes containing an identity operator and relinks remaining nodes accordingly
 *  Clears all downlinks;
 */
func (:cell_s) (void remove_identities( m @* o )) =
{
    o.clear_downlinks();
    o.clear_flags();
    foreach( m :node_s* node in o.excs ) node.skip_identities();
    o.clear_flags();
    o.remove_unreachable_nodes();
    assert( o.is_consistent() );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Recursively building a network cell from a semantic cell using membrane-technique.
 *  Exits when the enter membrane of the root cell is reached.
 *  This function does not set downlinks.
 *  Note: This recursion reflects the network structure (not the semantic cell structure)
 */
func (:cell_s)
(
    void from_sem_recursive
    (
        m @* o,
        m opal_sem_link_s* link,
        m opal_sem_tree_s* sem_tree,
        m opal_sem_tree_node_s* sem_tree_node,
        m opal_net_node_s* net_node_dn,
        sz_t             depth,
        m bcore_sink*      log  // optional
    )
) =
{
    depth++;
    tp_t name = link.name;
    if( log ) log.push_fa( "Tracing link '#<sc_t>' at depth #<sz_t>\n", o.context.ifnameof( name ), depth );

    link = link.trace_to_cell_membrane();

    if( !link ) ERR_fa( "Backtracing '#<sc_t>':\nTrace terminates in an open link.", o.context.ifnameof( name ) );

    m opal_sem_cell_s* cell = link.cell;
    m opal_sem_link_s* next_link = NULL;

    sc_t cell_type = cell.nop ? "node" : cell.body ? "graph" : cell.is_wrapper() ? "wrapper" : "";

    if( depth > o.max_depth )
    {
        cell.source_point.parse_err_fa( "Maximum depth '#<sz_t>' exceeded: This problem might be the result of an indefinite recursion.\n", o.max_depth );
    }

    if( link.exit ) // we are backtracing: Thus entering a cell though an exit link
    {
        if( log )
        {
            cell.source_point.parse_msg_to_sink_fa
            (
                log,
                "entering #<sc_t>-cell: '#<sc_t>' \n",
                cell_type,
                o.context.ifnameof( name )
            );
        }

        // since we backtrace, a cell is entered through an 'exit' link
        er_t err = sem_tree.enter( cell, /*node_in*/ sem_tree_node, /*node_out*/ &sem_tree_node );
        if( err ) cell.source_point.parse_err_fa( "Backtracing '#<sc_t>':\nEntering cell failed.", o.context.ifnameof( name ) );

        if( cell.nop )
        {
            if( log ) log.push_fa( "cell nop: #<sc_t>\n", ifnameof( cell.nop._ ) );

            bl_t trace_up = false;
            m opal_net_node_s* net_node_up = o.body.get_by_id( sem_tree_node.id );
            if( !net_node_up )
            {
                net_node_up = o.body.push();

                if( !net_node_up.context ) net_node_up.context = cell.context.fork();
                net_node_up.set_nop_d( cell.nop.fork() );

                if( !net_node_up.sem_id ) net_node_up.sem_id = opal_sem_id_s!;
                sem_tree_node.get_sem_id( net_node_up.sem_id );

                net_node_up.id = sem_tree_node.id;
                net_node_up.source_point =< sem_tree_node.get_nearest_source_point().fork();

                trace_up = net_node_up.nop.arity() > 0;
                if( log ) log.push_fa( "new node id: '#<sz_t>'\n", net_node_up.id );
            }

            if( trace_up )
            {
                sz_t arity = net_node_up.nop.arity();
                ASSERT( arity == cell.encs.size );

                /// ==== BEGIN SPECIAL BRANCH HANDLING ====

                /** If there is an iff-branch and the condition (arg0) is a constant scalar,
                 *  then the branch code is replaced by an identity linking to the
                 *  branch target based on the condition value.
                 *  Otherwise the branch code is left intact.
                 */
                if( net_node_up.nop._ == TYPEOF_opal_nop_ar3_iff_s )
                {
                    if( log ) log.push_fa( "Branch channel 0:\n" );
                    o.from_sem_recursive( cell.encs.[ 0 ], sem_tree, sem_tree_node, net_node_up, depth, log );
                    m opal_net_node_s* arg0 = net_node_up.upls.[ 0 ].node;
                    arg0.solve( NULL );
                    m opal_holor_s* result_h = arg0.result.h;
                    if( result_h.h.v.size == 1 && !result_h.m.active ) // determined constant holor
                    {
                        net_node_up.upls.clear();
                        net_node_up.set_nop_d( opal_nop_ar1_identity_s! );
                        if( log ) log.push_fa( "Condition check result: #<f3_t>. Identity to channel ", result_h.h.v.get_f3( 0 ) );

                        if( result_h.h.v.get_f3( 0 ) > 0 )
                        {
                            if( log ) log.push_fa( "'TRUE'\n" );
                            o.from_sem_recursive( cell.encs.[ 1 ], sem_tree, sem_tree_node, net_node_up, depth, log );
                        }
                        else
                        {
                            if( log ) log.push_fa( "'FALSE'\n" );
                            o.from_sem_recursive( cell.encs.[ 2 ], sem_tree, sem_tree_node, net_node_up, depth, log );
                        }
                    }
                    else /// leaving the branch code intact
                    {
                        if( log ) log.push_fa( "Branching to channel " );
                        if( log ) log.push_fa( "'TRUE'\n" );
                        o.from_sem_recursive( cell.encs.[ 1 ], sem_tree, sem_tree_node, net_node_up, depth, log );
                        if( log ) log.push_fa( "'FALSE'\n" );
                        o.from_sem_recursive( cell.encs.[ 2 ], sem_tree, sem_tree_node, net_node_up, depth, log );
                    }
                }

                /// ==== END SPECIAL BRANCH HANDLING ====

                else // normal processing
                {
                    for( sz_t i = 0; i < arity; i++ )
                    {
                        if( log ) log.push_fa( "node id #<sz_t>: up channel #<sz_t> of #<sz_t>:\n", net_node_up.id, i, arity );
                        o.from_sem_recursive( cell.encs.[ i ], sem_tree, sem_tree_node, net_node_up, depth, log );
                    }
                }
            }

            net_node_dn.upls.push().node = net_node_up;
        }
        else if( link.up )
        {
            next_link = link.up;
        }
        else
        {
            cell.source_point.parse_err_fa( "Backtracing '#<sc_t>':\nOpen exit link '#<sc_t>'.", o.context.ifnameof( name ), o.context.ifnameof( link.name ) );
        }
    }
    else
    {
        if( log ) log.push_fa( "exiting #<sc_t>-cell: '#<sc_t>' \n", cell_type, o.context.ifnameof( cell.name ) );
        bl_t exit_through_wrapper = link.up != NULL;
        er_t err = sem_tree.exit( cell, exit_through_wrapper, /*node_in*/ sem_tree_node, /*node_out*/ &sem_tree_node );

        if( err )
        {
            if( err == 1 )
            {
                cell.source_point.parse_err_fa( "Backtracing '#<sc_t>':\nExiting from untraced cell.", o.context.ifnameof( name ) );
            }
            else
            {
                cell.source_point.parse_err_fa( "Backtracing '#<sc_t>':\nExiting cell failed.", o.context.ifnameof( name ) );
            }
        }

        if( !sem_tree_node ) // root membrane reached (trace ended)
        {
            sz_t index = cell.encs.get_index_by_link( link );
            if( index == -1 )
            {
                cell.source_point.parse_err_fa( "Backtracing '#<sc_t>':\nEnding trace: No matching input channel.", o.context.ifnameof( name ) );
            }
            if( index >= o.encs.size )
            {
                cell.source_point.parse_err_fa( "Backtracing '#<sc_t>':\nInput channel boundary exceeded.", o.context.ifnameof( name ) );
            }

            m opal_net_node_s* net_node_up = o.encs.[ index ];
            net_node_dn.upls.push().node = net_node_up;

            next_link = NULL;
        }

        else if( link.up )
        {
            next_link = link.up;
        }
        else
        {
            next_link = sem_tree_node.cell.get_enc_by_dn( link );
            if( !next_link )
            {
                cell.source_point.parse_err_fa
                (
                    "Backtracing '#<sc_t>': Trace terminates in an open link.\n"
                    "Possible Reasons:\n"
                    "   * Dangling input channel.\n"
                    "   * Cyclic node without update.\n"
                    ,
                    o.context.ifnameof( name )
                );
            }
        }
    }

    if( next_link )
    {
        o.from_sem_recursive( next_link, sem_tree, sem_tree_node, net_node_dn, depth, log );
    }
    else
    {
        if( log ) log.push_fa( "Trace ended.\n" );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/// Finalization steps: Solves graph and optimizes it
func (:cell_s) (void finalize( m @* o )) =
{
    o.solve();
    o.remove_identities();
    o.set_downlinks();
    ASSERT( o.is_consistent() );
};

// ---------------------------------------------------------------------------------------------------------------------

/** Builds a net cell from a semantic cell
 *  This function locks and initializes the randomizer to ensure a deterministic sequence of random values.
 */
func (:cell_s)
(
    m opal_net_cell_s* from_sem_cell
    (
        m @* o,
        m opal_sem_cell_s* sem_cell,
        c opal_net* input_nop_creator,
        m bcore_sink* log
    )
) =
{
    ASSERT( sem_cell );

    if( !o.context ) o.context = sem_cell.context.fork();

    m opal_sem_tree_s* tree = opal_sem_tree_s!^^;
    foreach( m opal_sem_link_s* sem_link in sem_cell.encs )
    {
        m opal_net_node_s* net_node =  o.encs.push();
        net_node.context = o.context.fork();
        net_node.name = sem_link.name;
        net_node.sem_id = opal_sem_id_s!;
        net_node.sem_id.set( net_node.name );
        net_node.id = tree.id_base++;
        net_node.source_point = sem_cell.source_point.1.fork();

        if( sem_link.up )
        {
            if( log ) log.push_fa( "Evaluating literal in root entry channel '#<sz_t>' ... \n", __i );
            m opal_nop_ar0_param_s* param = opal_nop_ar0_param_s!;
            param.h = opal_holor_s!;

            param.h.from_sem_link( sem_link, sem_cell.parent, log );
            net_node.set_nop_d( param );
            if( log )
            {
                log.push_fa( "Evaluating literal in root entry channel '#<sz_t>' finished. Resulting Holor: ", __i );
                param.h.brief_to_sink( log );
                log.push_fa( "\n" );
            }
        }

        m opal_nop* new_nop = input_nop_creator ? input_nop_creator.create_input_nop( __i, sem_link.name, net_node.nop ) : NULL;
        if( new_nop ) net_node.set_nop_d( new_nop );
    }

    foreach( m opal_sem_link_s* sem_link in sem_cell.excs )
    {
        m opal_net_node_s* net_node =  o.excs.push();
        net_node.context = o.context.fork();
        net_node.name = sem_link.name;

        net_node.sem_id = opal_sem_id_s!;
        net_node.sem_id.set( net_node.name );

        net_node.id = tree.id_base++;
        net_node.source_point = sem_cell.source_point.1.fork();
        net_node.set_nop_d( opal_nop_ar1_output_s! );
        o.from_sem_recursive( sem_link, tree, NULL, net_node, 0, log );
    }

    o.normalize();

    ASSERT( o.is_consistent() );
    o.finalize();

    return o;
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :node_s, :cell_s: building mcode tracks

// ---------------------------------------------------------------------------------------------------------------------

/// node occurs in the downtree of o
func (:node_s) (bl_t recurses_in_downtree( m @* o, const opal_net_node_s* node )) =
{
    if( o == node ) return true;
    if( o.probe ) return false;

    o.probe = true;
    foreach( m :link_s* link in o.dnls )
    {
        if( link.node.recurses_in_downtree( node ) )
        {
            o.probe = false;
            return true;
        }
    }
    o.probe = false;
    return false;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:node_s) :.mcode_push_ap =
{
    if( o.is_cyclic() )
    {
        o.cyclic_mcode_push_ap_phase0( mcf );
        return;
    }

    ASSERT( o );

    if( o.flag ) return;
    o.flag = true;
    if( !o.nop    ) ERR_fa( "Operator is missing." );
    if( !o.result ) ERR_fa( "Result is missing." );
    if( !o.result.codable ) o.source_point.parse_err_fa( "Operator '#<sc_t>': Not codable.", ifnameof( o.nop._ ) );

    m bhvm_vop_arr_ci_s* arr_ci = bhvm_vop_arr_ci_s!^^;

    if( !o.mnode )
    {
        o.mnode = mcf.push_node().fork();
        o.mnode.param    = o.nop.is_param();
        o.mnode.cyclic   = o.nop.is_cyclic();
        o.mnode.adaptive = o.nop.is_adaptive();
    }

    foreach( m :link_s* link in o.upls )
    {
        link.node.mcode_push_ap( mcf );
        arr_ci.push_ci( 'a' + __i, link.node.mnode.ax0 );
    }

    o.mnode.ax0 = o.nop.mcode_push_ap_holor( o.result, arr_ci, mcf );
    arr_ci.push_ci( 'y', o.mnode.ax0 );
    o.nop.mcode_push_ap_track( o.result, arr_ci, mcf );

    if( o.mnode.ax0 >= 0 )
    {
        m opal_holor_meta_s* hmeta = mcf.hbase.hmeta_adl.[ o.mnode.ax0 ].cast( m opal_holor_meta_s* );
        if( !hmeta.name   ) hmeta.name = o.name;
        if( !hmeta.sem_id ) hmeta.sem_id = o.sem_id.fork();

        hmeta.pclass = TYPEOF_pclass_ax0;
        hmeta.mnode =< o.mnode.fork();
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:node_s) :.isolated_mcode_push =
{
    if( !o.result ) o.solve( NULL );
    if( !o.result ) o.source_point.parse_err_fa( "Node '#<sc_t>' has no result.", o.context.ifnameof( o.name ) );

    if( !o.mnode )
    {
        o.mnode = mcf.push_node().fork();
        o.mnode.param    = o.nop.is_param();
        o.mnode.cyclic   = o.nop.is_cyclic();
        o.mnode.adaptive = o.nop.is_adaptive();
    }

    o.mnode.ax0 = o.nop.mcode_push_ap_holor( o.result, NULL, mcf );
    m opal_holor_meta_s* hmeta = mcf.hbase.hmeta_adl.[ o.mnode.ax0 ].cast( m opal_holor_meta_s* );
    if( !hmeta.name ) hmeta.name = o.name;
    if( !hmeta.sem_id ) hmeta.sem_id = o.sem_id.fork();
    hmeta.pclass = TYPEOF_pclass_ax0;
    hmeta.mnode =< o.mnode.fork();
};

// --------------------------------------------------------------------------------------------------------------------

/** Recurrent ap phase0:
 *  opal_net_node_s_mcode_push_ap for cyclic nodes.
 *  Processes only the non_cyclic (left) up-channel [0]
 */
func (:node_s) :.cyclic_mcode_push_ap_phase0 =
{
    ASSERT( o.is_cyclic() );

    if( !o.mnode )
    {
        o.mnode = mcf.push_node().fork();
        o.mnode.param    = o.nop.is_param();
        o.mnode.cyclic   = true;
        o.mnode.adaptive = o.nop.is_adaptive();
        o.mnode.ax0 = o.nop.mcode_push_ap_holor( o.result, NULL, mcf );
        o.mnode.ax1 = o.nop.mcode_push_ap_holor( o.result, NULL, mcf );

        m opal_holor_meta_s* hmeta0 = mcf.hbase.hmeta_adl.[ o.mnode.ax0 ].cast( m opal_holor_meta_s* );
        m opal_holor_meta_s* hmeta1 = mcf.hbase.hmeta_adl.[ o.mnode.ax1 ].cast( m opal_holor_meta_s* );

        if( !hmeta0.name   ) hmeta0.name = o.name;
        if( !hmeta0.sem_id ) hmeta0.sem_id = o.sem_id.fork();
        if( !hmeta1.name   ) hmeta1.name = o.name;
        if( !hmeta1.sem_id ) hmeta1.sem_id = o.sem_id.fork();

        hmeta0.pclass = TYPEOF_pclass_ax0;
        hmeta1.pclass = TYPEOF_pclass_ax1;
        hmeta0.mnode =< o.mnode.fork();
        hmeta1.mnode =< o.mnode.fork();

        m opal_net_node_s* node = o.upls.[ 0 ].node;
        node.mcode_push_ap( mcf );

        mcf.track_vop_push_d( TYPEOF_track_ap_setup,         bhvm_vop_ar1_cpy_s!.setup( node.mnode.ax0, o.mnode.ax1 ) );
        mcf.track_vop_push_d( TYPEOF_track_ap_cyclic_reset,  bhvm_vop_ar1_cpy_s!.setup( node.mnode.ax0, o.mnode.ax1 ) );
        mcf.track_vop_push_d( TYPEOF_track_ap_cyclic_update, bhvm_vop_ar1_cpy_s!.setup(    o.mnode.ax1, o.mnode.ax0 ) );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/** Recurrent ap phase1:
 *  This function is called for all cyclic nodes after mcode_push_ap is completed for the entire network.
 *  Processes the cyclic (right) up-channel [1].
 */
func (:node_s) :.cyclic_mcode_push_ap_phase1 =
{
    ASSERT( o.is_cyclic() );
    if( !o.mnode ) o.cyclic_mcode_push_ap_phase0( mcf );
    if( !o.flag )
    {
        o.flag = true;
        m opal_net_node_s* node = o.upls.[ 1 ].node;
        node.mcode_push_ap( mcf );
        mcf.track_vop_push_d( TYPEOF_track_ap, bhvm_vop_ar1_cpy_s!.setup( node.mnode.ax0, o.mnode.ax1 ) );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:node_s) :.mcode_push_dp =
{
    ASSERT( o );

    /// nodes without mnode have no active role in the axon pass and therefore do not generate dp-code
    if( !o.mnode ) return;
    if( !o.nop ) ERR_fa( "Operator is missing." );
    if( !o.result ) ERR_fa( "Result is missing." );

    if( o.is_cyclic() )
    {
        o.cyclic_mcode_push_dp_phase0( up_index, mcf );
        return;
    }

    m bhvm_vop_arr_ci_s* arr_ci = bhvm_vop_arr_ci_s!^^;

    bl_t up_index_is_valid = false;

    foreach( m :link_s* link in o.upls )
    {
        m opal_net_node_s* node = link.node;
        arr_ci.push_ci( 'a' + __i, node.mnode.ax0 );
        sz_t agx = node.mnode.ag1 >= 0 ? node.mnode.ag1 : node.mnode.ag0;
        arr_ci.push_ci( 'f' + __i, agx );
        if( __i == up_index ) up_index_is_valid = agx >= 0;
    }

    arr_ci.push_ci( 'y', o.mnode.ax0 );

    if( !o.flag ) // build gradient computation for this node
    {
        o.flag = true;
        o.mnode.ag0 = o.nop.mcode_push_dp_holor( o.result, arr_ci, mcf );

        if( o.mnode.ag0 >= 0 )
        {
            // build this gradient from all downlinks ...
            foreach( m :link_s* link in o.dnls )
            {
                m opal_net_node_s* node = link.node;

                /// we do not accumulate downtree recurrences at this point
                if( !o.nop.is_cyclic() || ! node.recurses_in_downtree( o ) )
                {
                    sz_t node_up_index = node.up_index( o );
                    ASSERT( node_up_index >= 0 );
                    node.mcode_push_dp( node_up_index, mcf );
                }
            }

            m opal_holor_meta_s* hmeta = mcf.hbase.hmeta_adl.[ o.mnode.ag0 ].cast( m opal_holor_meta_s* );
            if( !hmeta.name ) hmeta.name = o.name;
            if( !hmeta.sem_id ) hmeta.sem_id = o.sem_id.fork();
            hmeta.pclass = TYPEOF_pclass_ag0;
            hmeta.mnode =< o.mnode.fork();
        }
    }

    if( up_index_is_valid )
    {
        arr_ci.push_ci( 'z', o.mnode.ag0 );
        o.nop.mcode_push_dp_track( o.result, 'a' + up_index, arr_ci, mcf );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

/** Recurrent dp phase0:
 *  opal_net_node_s_mcode_push_dp for cyclic nodes.
 */
func (:node_s) :.cyclic_mcode_push_dp_phase0 =
{
    if( !o.flag ) // build gradient computation for this node
    {
        o.flag = true;

        m bhvm_holor_s* h = bhvm_holor_s!^^.copy_shape_type( o.result.h.h );
        m opal_holor_meta_s* m = o.result.h.m.clone().scope();
        if( !m.name ) m.name = o.name;
        if( !m.sem_id ) m.sem_id = o.sem_id.fork();

        m.pclass = TYPEOF_pclass_ag0;
        m.mnode =< o.mnode.fork();

        sz_t idx = mcf.push_hm( h, m );
        mcf.track_vop_push_d( TYPEOF_track_dp_setup,            bhvm_vop_ar0_determine_s!.setup( idx ) );
        mcf.track_vop_push_d( TYPEOF_track_dp_shelve,           bhvm_vop_ar0_vacate_s   !.setup( idx ) );
        mcf.track_vop_push_d( TYPEOF_track_dp_cyclic_zero_grad, bhvm_vop_ar0_zro_s      !.setup( idx ) );
        o.mnode.ag0 = idx;

        // build this gradient from all downlinks ...
        foreach( m :link_s* link in o.dnls )
        {
            m opal_net_node_s* node = link.node;

            /// we do not accumulate downtree recurrences at this point
            if( !node.recurses_in_downtree( o ) )
            {
                sz_t node_up_index = node.up_index( o );
                ASSERT( node_up_index >= 0 );
                node.mcode_push_dp( node_up_index, mcf );
            }
        }
    }

    if( up_index == 1 )
    {
        m opal_net_node_s* node1 = o.upls.[ 1 ].node;
        mcf.track_vop_push_d( TYPEOF_track_dp, bhvm_vop_ar1_acc_s!.setup( o.mnode.ag0, node1.mnode.ag1 >= 0 ? node1.mnode.ag1 : node1.mnode.ag0 ) );
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:node_s) :.cyclic_mcode_push_dp_phase1 =
{
    ASSERT( o );
    if( !o.nop ) ERR_fa( "Operator is missing." );
    if( !o.result ) ERR_fa( "Result is missing." );
    ASSERT( o.nop.is_cyclic() );

    {
        m bhvm_holor_s* h = bhvm_holor_s!^^.copy_shape_type( o.result.h.h );
        m opal_holor_meta_s* m = o.result.h.m.clone().scope();
        if( !m.name ) m.name = o.name;
        if( !m.sem_id ) m.sem_id = o.sem_id.fork();
        m.pclass = TYPEOF_pclass_ag1;
        m.mnode =< o.mnode.fork();
        sz_t idx = mcf.push_hm( h, m );
        mcf.track_vop_push_d( TYPEOF_track_dp_setup,  bhvm_vop_ar0_determine_s!.setup( idx ) );
        mcf.track_vop_push_d( TYPEOF_track_dp_shelve, bhvm_vop_ar0_vacate_s   !.setup( idx ) );
        mcf.track_vop_push_d( TYPEOF_track_dp,        bhvm_vop_ar0_zro_s      !.setup( idx ) );
        o.mnode.ag1 = idx;
    }

    foreach( m :link_s* link in o.dnls )
    {
        m opal_net_node_s* node = link.node;

        /// we only accumulate downtree recurrences at this point
        if( node.recurses_in_downtree( o ) )
        {
            sz_t node_up_index = node.up_index( o );
            ASSERT( node_up_index >= 0 );
            node.mcode_push_dp( node_up_index, mcf );
        }
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:node_s) :.cyclic_mcode_push_dp_phase2 =
{
    ASSERT( o );
    if( !o.nop ) ERR_fa( "Operator is missing." );
    if( !o.result ) ERR_fa( "Result is missing." );
    ASSERT( o.nop.is_cyclic() );
    mcf.track_vop_push_d( TYPEOF_track_dp, bhvm_vop_ar1_cpy_s!.setup( o.mnode.ag1, o.mnode.ag0 ) );
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) :.mcode_push_ap =
{
    ASSERT( o.is_consistent() );

    m opal_net_node_adl_s* cyclic_adl = opal_net_node_adl_s!^^;
    foreach( m :node_s* node in o.body ) if( node.nop && node.nop.is_cyclic() ) cyclic_adl.push_d( node.fork() );

    foreach( m :node_s* node in o.excs )
    {
        if( !node.result ) ERR_fa( "Unsolved node '#<sc_t>'\n", o.context.ifnameof( node.name ) );
        node.mcode_push_ap( mcf );
    }

    /// cyclic nodes phase 1, 2
    foreach( m :node_s* node in cyclic_adl ) node.cyclic_mcode_push_ap_phase1( mcf );

    o.clear_all_flags();
    mcf.check_integrity();
};

// ---------------------------------------------------------------------------------------------------------------------

func (:cell_s) (void mcode_push_dp( m @* o, m bhvm_mcode_frame_s* mcf, bl_t entry_channels )) =
{
    ASSERT( o.is_consistent() );
    m opal_net_node_adl_s* cyclic_adl   = opal_net_node_adl_s!^^;
    m opal_net_node_adl_s* adaptive_adl = opal_net_node_adl_s!^^;

    foreach( m :node_s* node in o.body ) if( node.nop )
    {
        if( node.nop.is_cyclic() ) cyclic_adl.push_d( node.fork() );
        if( node.nop.is_adaptive() ) adaptive_adl.push_d( node.fork() );
    }

    if( entry_channels )
    {
        foreach( m :node_s* node in o.encs ) if( node.nop ) node.mcode_push_dp( -1, mcf );
    }

    /// adaptive nodes
    foreach( m :node_s* node in adaptive_adl ) node.mcode_push_dp( -1, mcf );

    /// cyclic nodes phase 1, 2
    foreach( m :node_s* node in cyclic_adl ) node.cyclic_mcode_push_dp_phase1( mcf );
    foreach( m :node_s* node in cyclic_adl ) node.cyclic_mcode_push_dp_phase2( mcf );

    o.clear_all_flags();
    mcf.check_integrity();
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// :builder_s
// ---------------------------------------------------------------------------------------------------------------------

func (:builder_s) ::.create_input_nop =
{
    ASSERT( in_idx < o.input_holors.size );

    const bhvm_holor_s* h_in = o.input_holors.[ in_idx ];

    if( cur_nop && cur_nop._ == TYPEOF_opal_nop_ar0_param_s )
    {
        const bhvm_holor_s* h_cur = cur_nop.cast( m opal_nop_ar0_param_s* ).h.h;
        if( !h_in )
        {
            h_in = h_cur;
        }
        else if( !h_cur.s.is_equal( h_in.s ) )
        {
            m st_s* msg = st_s!^^;
            msg.push_fa( "Shape deviation at input holor '#<sz_t>':", in_idx );
            msg.push_fa( "\n#p20.{Passed input} " );
            h_in.brief_to_sink( msg );
            msg.push_fa( "\n#p20.{Expected shape} " );
            h_cur.brief_to_sink( msg );
            ERR_fa( "#<st_s*>\n", msg );
        }
    }

    if( h_in )
    {
        m opal_nop_ar0_param_s* param = opal_nop_ar0_param_s!;
        param.h = opal_holor_s!;
        param.h.h.copy( h_in );
        return param;
    }
    else
    {
        return NULL;
    }
};

// ---------------------------------------------------------------------------------------------------------------------

func (:builder_s) :.build_from_source =
{
    m opal_sem_cell_s* sem_cell = opal_sem_cell_s!^^;
    o.sem_builder.build_from_source( sem_cell, source );
    net_cell.from_sem_cell( sem_cell, o, o->log );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

