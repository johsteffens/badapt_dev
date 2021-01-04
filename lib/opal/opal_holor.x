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

func (:s) bcore_fp.copy_typed =
{
    m x_inst* inst = ( x_inst* )src;
    switch( type )
    {
        case TYPEOF_opal_holor_s:
        {
            assert( inst._ == TYPEOF_opal_holor_s );
            o.copy( inst.cast( m opal_holor_s* ) );
        }
        break;

        case TYPEOF_bhvm_holor_s:
        case TYPEOF_bmath_mf2_s:
        case TYPEOF_bmath_mf3_s:
        case TYPEOF_bmath_vf2_s:
        case TYPEOF_bmath_vf3_s:
        case TYPEOF_f2_t:
        case TYPEOF_f3_t:
        case TYPEOF_sc_t:
        {
            o.h.copy_typed( type, inst );
        }
        break;

        case TYPEOF_st_s:
        {
            assert( inst._ == TYPEOF_st_s );
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

include deferred "opal_net.h";

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

