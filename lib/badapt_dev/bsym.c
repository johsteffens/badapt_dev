/** Copyright 2019 Johannes Bernhard Steffens
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

#include "bcore_std.h"
#include "bmath_std.h"
#include "bmath_plot.h"
#include "bsym.h"

/**********************************************************************************************************************/
//bsym

/// prototypes

bsym_net_link_s*    bsym_sem_graph_s_get_arg_out( bsym_sem_graph_s* o, sz_t index );
void                bsym_sem_graph_s_check_consistency( const bsym_sem_graph_s* o );
void                bsym_sem_graph_s_embed( bsym_sem_graph_s* o, bcore_source* source );
bsym_net*           bsym_sem_graph_s_evaluate_net(           bsym_sem_graph_s* o,                        bcore_source* source );
bsym_net*           bsym_sem_graph_s_evaluate_net_stack(     bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source );
bsym_net_address_s* bsym_sem_graph_s_evaluate_address(       bsym_sem_graph_s* o,                        bcore_source* source );
bsym_net_address_s* bsym_sem_graph_s_evaluate_address_stack( bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source );
bsym_sem_graph_s*   bsym_sem_graph_s_evaluate_graph(         bsym_sem_graph_s* o,                        bcore_source* source );
bsym_sem_graph_s*   bsym_sem_graph_s_evaluate_graph_stack(   bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source );
bsym_net_node_s*    bsym_sem_graph_s_evaluate_node(          bsym_sem_graph_s* o, bcore_source* source );
bsym_net_hresult_s* bsym_sem_graph_s_evaluate_hresult(       bsym_sem_graph_s* o, bcore_source* source );
bmath_hf3_s*        bsym_sem_graph_s_evaluate_hf3(           bsym_sem_graph_s* o, bcore_source* source );
f3_t                bsym_sem_graph_s_evaluate_f3(            bsym_sem_graph_s* o, bcore_source* source );

void bsym_sem_graph_s_parse( bsym_sem_graph_s* o, bsym_sem_graph_s* parent, bcore_source* source );

/// globals
static bcore_hmap_name_s* hmap_name_g = NULL;

// ---------------------------------------------------------------------------------------------------------------------

sc_t bsym_ifnameof( tp_t name )
{
    sc_t sc = bcore_hmap_name_s_get_sc( hmap_name_g, name );
    return sc ? sc : "";
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bsym_entypeof( sc_t name )
{
    return bcore_hmap_name_s_set_sc( hmap_name_g, name );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bsym_entypeof_fv( sc_t format, va_list args )
{
    st_s* s = st_s_create_fv( format, args );
    tp_t tp = bsym_entypeof( s->sc );
    st_s_discard( s );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bsym_entypeof_fa( sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    tp_t tp = bsym_entypeof_fv( format, args );
    va_end( args );
    return tp;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_source_info_s

// ---------------------------------------------------------------------------------------------------------------------

void bsym_source_info_s_set( bsym_source_info_s* o, bcore_source* source )
{
    bcore_source_a_attach( &o->source, bcore_fork( source ) );
    o->index = bcore_source_a_get_index( source );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_source_info_s_parse_err_fv( bsym_source_info_s* o, sc_t format, va_list args )
{
    if( o->source )
    {
        bcore_source_a_set_index( o->source, o->index );
        bcore_source_a_parse_err_fv( o->source, format, args );
    }
    else
    {
        bcore_err_fv( format, args );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_source_info_s_parse_err_fa( bsym_source_info_s* o, sc_t format, ... )
{
    va_list args;
    va_start( args, format );
    bsym_source_info_s_parse_err_fv( o, format, args );
    va_end( args );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_op_ar2[_htp]_mul[_htp]_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_bmul_s_compute_hf3( const bsym_op_ar2_bmul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( !bmath_hf3_s_set_d_bmul( a, b, r ) ) return false;
    if( a->v_data && b->v_data )
    {
        bmath_hf3_s_fit_v_size( r );
        bmath_hf3_s_bmul( a, b, r );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_bmul_htp_s_compute_hf3( const bsym_op_ar2_bmul_htp_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( !bmath_hf3_s_set_d_bmul_htp( a, b, r ) ) return false;
    if( a->v_data && b->v_data )
    {
        bmath_hf3_s_fit_v_size( r );
        bmath_hf3_s_bmul_htp( a, b, r );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_htp_bmul_s_compute_hf3( const bsym_op_ar2_htp_bmul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( !bmath_hf3_s_set_d_htp_bmul( a, b, r ) ) return false;
    if( a->v_data && b->v_data )
    {
        bmath_hf3_s_fit_v_size( r );
        bmath_hf3_s_htp_bmul( a, b, r );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_htp_bmul_htp_s_compute_hf3( const bsym_op_ar2_htp_bmul_htp_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( !bmath_hf3_s_set_d_htp_bmul_htp( a, b, r ) ) return false;
    if( a->v_data && b->v_data )
    {
        bmath_hf3_s_fit_v_size( r );
        bmath_hf3_s_htp_bmul_htp( a, b, r );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_op_ar2_mul_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_mul_s_compute_hf3( const bsym_op_ar2_mul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( a->d_size == 0 )
    {
        bmath_hf3_s_copy_d_data( r, b );
        if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
        {
            bmath_hf3_s_fit_v_size( r );
            bmath_hf3_s_mul_scl( b, a->v_data, r );
        }
    }
    else if( b->d_size == 0 )
    {
        bmath_hf3_s_copy_d_data( r, a );
        if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
        {
            bmath_hf3_s_fit_v_size( r );
            bmath_hf3_s_mul_scl( a, b->v_data, r );
        }
    }
    else
    {
        if( a->d_size != b->d_size ) return false;
        if( bmath_hf3_s_d_product( a ) != bmath_hf3_s_d_product( b ) ) return false;
        bmath_hf3_s_copy_d_data( r, a );
        if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
        {
            bmath_hf3_s_fit_v_size( r );
            bmath_hf3_s_hmul( a, b, r );
        }
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bmath_hf3_vm_op* bsym_op_ar2_mul_s_create_vm_operator( const bsym_op_ar2_mul_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, const bmath_hf3_s* r )
{
    if( a->d_size == 0 )
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_scl_mul_s_create();
    }
    else if( b->d_size == 0 )
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_mul_scl_s_create();
    }
    else
    {
        return ( bmath_hf3_vm_op* )bmath_hf3_vm_op_hmul_s_create();
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_op_ar2_plus_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_plus_s_compute_hf3( const bsym_op_ar2_plus_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( a->d_size != b->d_size ) return false;
    if( bmath_hf3_s_d_product( a ) != bmath_hf3_s_d_product( b ) ) return false;
    bmath_hf3_s_copy_d_data( r, a );
    if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
    {
        bmath_hf3_s_fit_v_size( r );
        bmath_hf3_s_add( a, b, r );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_op_ar2_minus_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_op_ar2_minus_s_compute_hf3( const bsym_op_ar2_minus_s* o, const bmath_hf3_s* a, const bmath_hf3_s* b, bmath_hf3_s* r )
{
    if( a->d_size != b->d_size ) return false;
    if( bmath_hf3_s_d_product( a ) != bmath_hf3_s_d_product( b ) ) return false;

    bmath_hf3_s_copy_d_data( r, a );
    if( ( a->v_size > 0 ) && ( b->v_size > 0 ) )
    {
        bmath_hf3_s_fit_v_size( r );
        bmath_hf3_s_sub( a, b, r );
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_body_s

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_net_body_s_push_link( bsym_net_body_s* o )
{
    bsym_net_link_s* link = ( bsym_net_link_s* )bsym_net_body_s_push_t( o, TYPEOF_bsym_net_link_s );
    link->root.body = o;
    link->root.index = o->size - 1;
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_push_node( bsym_net_body_s* o )
{
    bsym_net_node_s* node = ( bsym_net_node_s* )bsym_net_body_s_push_t( o, TYPEOF_bsym_net_node_s );
    node->root.body = o;
    node->root.index = o->size - 1;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_clone_node( bsym_net_body_s* o, const bsym_net_node_s* src )
{
    bsym_net_node_s* node = bsym_net_body_s_push_node( o );
    for( sz_t i = 0; i < src->targets_size; i++ )
    {
        bsym_net_address_s_copy( bsym_net_node_s_push( node ), &src->targets_data[ i ] );
    }
    node->name = src->name;
    node->op = bsym_op_a_clone( src->op );
    node->hresult = bsym_net_hresult_s_clone( src->hresult );
    bsym_source_info_s_copy( &node->source_info, &src->source_info );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_push_literal_scalar( bsym_net_body_s* o, f3_t val )
{
    bsym_net_node_s* node = bsym_net_body_s_push_node( o );
    bsym_op_ar0_holor_s* holor = bsym_op_ar0_holor_s_create();
    holor->type = TYPEOF_literal;
    bmath_hf3_s_fit_v_size( &holor->hf3 );
    holor->hf3.v_data[ 0 ] = val;
    node->op = ( bsym_op* )holor;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_net_body_s_push_literal_holor( bsym_net_body_s* o, const bmath_hf3_s* hf3 )
{
    bsym_net_node_s* node = bsym_net_body_s_push_node( o );
    bsym_op_ar0_holor_s* holor = bsym_op_ar0_holor_s_create();
    holor->type = TYPEOF_literal;
    bmath_hf3_s_copy( &holor->hf3, hf3 );
    node->op = ( bsym_op* )holor;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_body_s_set_source_info( bsym_net_body_s* o, bcore_source* source )
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        if( *(aware_t*)o->data[ i ] == TYPEOF_bsym_net_node_s )
        {
            bsym_net_node_s* node = ( bsym_net_node_s* )o->data[ i ];
            bsym_source_info_s_set( &node->source_info, source );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_address_s

void bsym_net_address_s_clear( bsym_net_address_s* o )
{
    o->body = 0;
    o->index = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net* bsym_net_address_s_get_net( const bsym_net_address_s* o )
{
    if( o->body )
    {
        const bsym_net_body_s* body = o->body;
        assert( o->index >= 0 && o->index < body->size );
        assert( body->data );
        return body->data[ o->index ];
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_link_s

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_net_node_s

// ---------------------------------------------------------------------------------------------------------------------

bsym_net* bsym_net_node_s_get_target_net( const bsym_net_node_s* o, sz_t index )
{
    assert( index < o->targets_size );
    return bsym_net_address_s_get_net( &o->targets_data[ index ] );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_node_s_trace_to_sink( const bsym_net_node_s* o, sz_t indent, bcore_sink* sink )
{
    bl_t details = true;

    if( o->hresult )
    {
        if( o->hresult->hf3->v_size > 0 )
        {
            bmath_hf3_s_to_sink( o->hresult->hf3, sink );
            details = false;
        }
    }

    if( details )
    {
        if( o->hresult )
        {
            bmath_hf3_s_to_sink( o->hresult->hf3, sink );
            if( o->hresult->vm_index >= 0 ) bcore_sink_a_push_fa( sink, "(i#pl3'0'{#<sz_t>})", o->hresult->vm_index );
            if( o->hresult->type != TYPEOF_buffer ) bcore_sink_a_push_fa( sink, "(#<sc_t>)", ifnameof( o->hresult->type ) );
        }
        else
        {
            bsym_op_a_trace_to_sink( o->op, indent, sink );
        }
        bcore_sink_a_push_fa( sink, "<#<sc_t>>", bsym_ifnameof( o->name ) );
        if( o->op )
        {
            indent += 4;
            for( sz_t i = 0; i < o->targets_size; i++ )
            {
                bcore_sink_a_push_fa( sink, "\n#rn{ } |-> ", indent );
                bsym_net_address_s_trace_to_sink( &o->targets_data[ i ], indent, sink );
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_hresult_s* bsym_net_node_s_trace_compute_hresult( bsym_net_node_s* o, bl_t force )
{
    if( o->hresult ) return o->hresult;

    bmath_hf3_s* hf3 = NULL;
    tp_t type = TYPEOF_buffer;

    if( o->op )
    {
        if( bsym_op_ar0_a_is_trait_of( o->op ) )
        {
            bsym_op_ar0* op0 = ( bsym_op_ar0* )o->op;
            hf3 = bmath_hf3_s_create();
            type = bsym_op_ar0_a_get_hf3_type( op0 );
            if( bsym_op_ar0_a_compute_hf3( op0, hf3 ) )
            {
                if( bmath_hf3_s_d_product( hf3 ) == 0 )
                {
                    ASSERT( o->targets_size == hf3->d_size );
                    for( sz_t i = 0; i < hf3->d_size; i++ )
                    {
                        if( hf3->d_data[ i ] == 0 )
                        {
                            bsym_net_address_s* address = &o->targets_data[ hf3->d_size - i - 1 ];
                            bsym_net_hresult_s* hresult = bsym_net_address_s_trace_compute_hresult( address, force );
                            if( hresult && hresult->hf3->v_size == 1 )
                            {
                                hf3->d_data[ i ] = hresult->hf3->v_data[ 0 ];
                            }
                            else
                            {
                                if( force )
                                {
                                    bsym_source_info_s_parse_err_fa( &o->source_info, "Scalar type needed for dimension assignment." );
                                }
                                hf3->d_data[ i ] = 0;
                            }
                        }
                    }

                    if( hf3 && bmath_hf3_s_d_product( hf3 ) > 0 ) bsym_net_node_s_clear( o ); // remove all input addresses
                }
                if( bmath_hf3_s_d_product( hf3 ) == 0 )
                {
                    if( force )
                    {
                        bsym_source_info_s_parse_err_fa( &o->source_info, "Holor dimensions assignment cannot be fully traced to scalar literals." );
                    }
                    else
                    {
                        bmath_hf3_s_detach( &hf3 );
                    }
                }
            }
            else
            {
                if( force )
                {
                    bsym_source_info_s_parse_err_fa( &o->source_info, "Nullary operator did not yield a holor." );
                }
                else
                {
                    bmath_hf3_s_detach( &hf3 );
                }
            }
        }
        else if( bsym_op_ar1_a_is_trait_of( o->op ) )
        {
            ASSERT( o->targets_size == 1 );
            const bsym_net_hresult_s* hresult = bsym_net_address_s_trace_compute_hresult( &o->targets_data[ 0 ], force );
            if( hresult )
            {
                bsym_op_ar1* op1 = ( bsym_op_ar1* )o->op;
                hf3 = bmath_hf3_s_create();
                if( !bsym_op_ar1_a_compute_hf3( op1, hresult->hf3, hf3 ) )
                {
                    bsym_source_info_s_parse_err_fa( &o->source_info, "Could not resolve operation '<#sc_t>'.", bsym_op_ar1_a_get_symbol( op1 ) );
                }
            }
        }
        else if( bsym_op_ar2_a_is_trait_of( o->op ) )
        {
            ASSERT( o->targets_size == 2 );
            const bsym_net_hresult_s* hresult1 = bsym_net_address_s_trace_compute_hresult( &o->targets_data[ 0 ], force );
            const bsym_net_hresult_s* hresult2 = bsym_net_address_s_trace_compute_hresult( &o->targets_data[ 1 ], force );
            if( hresult1 && hresult2 )
            {
                bsym_op_ar2* op2 = ( bsym_op_ar2* )o->op;
                hf3 = bmath_hf3_s_create();
                if( !bsym_op_ar2_a_compute_hf3( op2, hresult1->hf3, hresult2->hf3, hf3 ) )
                {
                    st_s* st_src1 = st_s_create();
                    st_s* st_src2 = st_s_create();
                    bmath_hf3_s_to_sink( hresult1->hf3, ( bcore_sink* )st_src1 );
                    bmath_hf3_s_to_sink( hresult2->hf3, ( bcore_sink* )st_src2 );
                    bsym_source_info_s_parse_err_fa( &o->source_info, "Could not resolve operation '#<sc_t> #<sc_t> #<sc_t>'.", st_src1->sc, bsym_op_ar2_a_get_symbol( op2 ), st_src2->sc );
                }
            }
        }
        else
        {
            bsym_source_info_s_parse_err_fa( &o->source_info, "Invalid operator." );
        }
    }

    if( hf3 )
    {
        o->hresult = bsym_net_hresult_s_create();
        o->hresult->hf3 = hf3;
        o->hresult->type = type;
    }
    else
    {
        if( force )
        {
            bsym_source_info_s_parse_err_fa( &o->source_info, "Solving operation failed." );
        }
    }

    return o->hresult;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_net_node_s_trace_build_vm_proc( bsym_net_node_s* o, bmath_hf3_vm_frame_s* vmf, tp_t proc_name )
{
    if( proc_name == TYPEOF_infer )
    {
        if( !o->hresult ) ERR_fa( "hresult missing." );
        if( o->hresult->vm_index >= 0 ) return; // vm_holor exists; nothing to do
        if( !o->op ) ERR_fa( "operator missing." );

        sz_t arity = bsym_op_a_get_arity( o->op );

        // early recursion into branches makes holor order feed-forward-ascending
        if( arity == 1 )
        {
            ASSERT( o->targets_size == 1 );
            bsym_net_address_s_trace_build_vm_proc( &o->targets_data[ 0 ], vmf, proc_name );
        }
        else if( arity == 2 )
        {
            ASSERT( o->targets_size == 2 );
            bsym_net_address_s_trace_build_vm_proc( &o->targets_data[ 0 ], vmf, proc_name );
            bsym_net_address_s_trace_build_vm_proc( &o->targets_data[ 1 ], vmf, proc_name );
        }

        // computing holor of this node ...

        bmath_hf3_vm_holor_s* vm_holor = bmath_hf3_vm_arr_holor_s_push( &vmf->arr_holor );
        o->hresult->vm_index = vmf->arr_holor.size - 1;

        if( !bcore_hmap_tpuz_s_exists( &vmf->map_proc, proc_name ) )
        {
            bmath_hf3_vm_library_s_push( &vmf->library );
            bcore_hmap_tpuz_s_set( &vmf->map_proc, proc_name, vmf->library.size - 1 );
        }

        bmath_hf3_vm_proc_s* vm_proc = &vmf->library.data[ *bcore_hmap_tpuz_s_get( &vmf->map_proc, proc_name ) ];
        vm_holor->name = o->hresult->name;
        vm_holor->type = o->hresult->type;
        bmath_hf3_s_copy( &vm_holor->hf3, o->hresult->hf3 );

        if( vm_holor->name )
        {
            bcore_hmap_name_s_set_sc( &vmf->map_name, bsym_ifnameof( vm_holor->name ) );
            bcore_hmap_tpuz_s_set( &vmf->map_holor, vm_holor->name, vmf->arr_holor.size -1 );
        }

        if( arity == 0 )
        {
            bsym_op_ar0* op_ar0 = ( bsym_op_ar0* )o->op;
            bmath_hf3_vm_op* vm_op = bsym_op_ar0_a_create_vm_operator( op_ar0, &vm_holor->hf3 );

            if( vm_op )
            {
                bmath_hf3_vm_op_ar0_a_set_args( (vd_t)vm_op, o->hresult->vm_index );
                bmath_hf3_vm_proc_s_push_op_d( vm_proc, vm_op );
            }
            // else: arity 0 nodes represent a constant and only need a vm-operator in case the constant is computed on the fly.
        }
        else if( arity == 1 )
        {
            ASSERT( o->targets_size == 1 );
            bsym_op_ar1* op_ar1 = ( bsym_op_ar1* )o->op;
            bsym_net_address_s* arg1 = &o->targets_data[ 0 ];
            bsym_net_node_s* node1 = bsym_net_address_s_trace_get_node( arg1 );
            ASSERT( node1 && node1->hresult && node1->hresult->vm_index >= 0 );
            sz_t idx1 = node1->hresult->vm_index;
            ASSERT( idx1 >= 0 && idx1 < vmf->arr_holor.size );
            bmath_hf3_vm_op* vm_op = bsym_op_ar1_a_create_vm_operator( op_ar1, node1->hresult->hf3, &vm_holor->hf3 );
            if( vm_op )
            {
                bmath_hf3_vm_op_ar1_a_set_args( (vd_t)vm_op, idx1, o->hresult->vm_index );
                bmath_hf3_vm_proc_s_push_op_d( vm_proc, vm_op );
            }
            else
            {
                bsym_source_info_s_parse_err_fa( &o->source_info, "Node has no operator." );
            }
        }
        else // arity == 2
        {
            ASSERT( o->targets_size == 2 );
            bsym_op_ar2* op_ar2 = ( bsym_op_ar2* )o->op;
            bsym_net_address_s* arg1 = &o->targets_data[ 0 ];
            bsym_net_address_s* arg2 = &o->targets_data[ 1 ];
            bsym_net_node_s* node1 = bsym_net_address_s_trace_get_node( arg1 );
            bsym_net_node_s* node2 = bsym_net_address_s_trace_get_node( arg2 );
            ASSERT( node1 && node1->hresult && node1->hresult->vm_index >= 0 );
            ASSERT( node2 && node2->hresult && node2->hresult->vm_index >= 0 );
            sz_t idx1 = node1->hresult->vm_index;
            sz_t idx2 = node2->hresult->vm_index;
            ASSERT( idx1 >= 0 && idx1 < vmf->arr_holor.size );
            ASSERT( idx2 >= 0 && idx2 < vmf->arr_holor.size );
            bmath_hf3_vm_op* vm_op = bsym_op_ar2_a_create_vm_operator( op_ar2, node1->hresult->hf3, node2->hresult->hf3, &vm_holor->hf3 );
            if( vm_op )
            {
                bmath_hf3_vm_op_ar2_a_set_args( (vd_t)vm_op, idx1, idx2, o->hresult->vm_index );
                bmath_hf3_vm_proc_s_push_op_d( vm_proc, vm_op );
            }
            else
            {
                bsym_source_info_s_parse_err_fa( &o->source_info, "Node has no operator." );
            }
        }
    }
    else
    {
        ERR_fa( "Unknown procedure name '#<sc_t>'.", ifnameof( proc_name ) );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
//bsym_sem_graph_s

bsym_sem_graph_s* bsym_sem_graph_s_push_graph( bsym_sem_graph_s* o )
{
    bsym_sem_graph_s* node = ( bsym_sem_graph_s* )bsym_sem_graph_base_s_push_t( o->graph_base, TYPEOF_bsym_sem_graph_s );
    node->arr_symbol_op2   = bcore_fork( o->arr_symbol_op2 );
    node->graph_base = bsym_sem_graph_base_s_create();
    node->graph_base->parent = o->graph_base;
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_copy_graph( bsym_sem_graph_s* o, const bsym_sem_graph_s* src )
{
    o->name = src->name;
    o->args_in  = src->args_in;
    o->args_out = src->args_out;
    bsym_source_info_s_copy( &o->source_info, &src->source_info );
    bsym_net_body_s_copy( &o->body, &src->body );
    o->priority = src->priority;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_graph_s* bsym_sem_graph_s_clone_graph( bsym_sem_graph_s* o, const bsym_sem_graph_s* src )
{
    bsym_sem_graph_s* graph = bsym_sem_graph_s_push_graph( o );
    bsym_sem_graph_s_copy_graph( graph, src );
    graph->name = 0; // we have to reset the name to avoid this graph to be re-selected on another expression
    return graph;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_set_args( bsym_sem_graph_s* o, sz_t args_out, sz_t args_in )
{
    o->args_out = args_out;
    o->args_in  = args_in;
    bsym_net_body_s_clear( &o->body );
    for( sz_t i = 0; i < args_out; i++ ) bsym_net_body_s_push_link( &o->body );
    for( sz_t i = 0; i < args_in;  i++ ) bsym_net_body_s_push_link( &o->body );
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_get_arg_in( bsym_sem_graph_s* o, sz_t index )
{
    ASSERT( index < o->args_in );
    return ( bsym_net_link_s* )o->body.data[ o->args_out + index ];
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_get_arg_out( bsym_sem_graph_s* o, sz_t index )
{
    ASSERT( index < o->args_out );
    return ( bsym_net_link_s* )o->body.data[ index ];
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_get_arg_in_by_name( bsym_sem_graph_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->args_in; i++ )
    {
        if( bsym_sem_graph_s_get_arg_in( o, i )->name == name ) return bsym_sem_graph_s_get_arg_in( o, i );
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t bsym_sem_graph_s_get_free_args_in( bsym_sem_graph_s* o )
{
    sz_t count = 0;
    for( sz_t i = 0; i < o->args_in; i++ )
    {
        bsym_net_link_s* link = bsym_sem_graph_s_get_arg_in( o, i );
        count += ( link->target.body == NULL );
    }
    return count;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_get_next_free_arg_in( bsym_sem_graph_s* o )
{
    for( sz_t i = 0; i < o->args_in; i++ )
    {
        bsym_net_link_s* link = bsym_sem_graph_s_get_arg_in( o, i );
        if( link->target.body == NULL ) return link;
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_get_arg_out_by_name( bsym_sem_graph_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->args_out; i++ )
    {
        if( bsym_sem_graph_s_get_arg_out( o, i )->name == name ) return bsym_sem_graph_s_get_arg_out( o, i );
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_get_link_from_body_by_name( bsym_sem_graph_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        vd_t item = o->body.data[ i ];
        if( *(aware_t*)item == TYPEOF_bsym_net_link_s )
        {
            bsym_net_link_s* link = item;
            if( link->name == name ) return link;
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_sem_graph_s_get_node_by_name( bsym_sem_graph_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        vd_t item = o->body.data[ i ];
        if( *(aware_t*)item == TYPEOF_bsym_net_node_s )
        {
            bsym_net_node_s* node = item;
            if( node->name == name ) return node;
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_graph_s* bsym_sem_graph_base_s_get_graph_by_name( bsym_sem_graph_base_s* o, tp_t name )
{
    for( sz_t i = 0; i < o->size; i++ )
    {
        bsym_sem* item = o->data[ i ];
        assert( *( aware_t* )item == TYPEOF_bsym_sem_graph_s );
        bsym_sem_graph_s* node = ( bsym_sem_graph_s* )item;
        if( node->name == name ) return node;
    }
    if( o->parent ) return bsym_sem_graph_base_s_get_graph_by_name( o->parent, name );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_graph_s* bsym_sem_graph_s_get_graph_by_name( bsym_sem_graph_s* o, tp_t name )
{
    return bsym_sem_graph_base_s_get_graph_by_name( o->graph_base, name );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_trace_out_to_sink( const bsym_sem_graph_s* o, sz_t out_index, bcore_sink* sink )
{
    ASSERT( out_index < o->args_out );

    bsym_net_link_s* link = bsym_sem_graph_s_get_arg_out( ( bsym_sem_graph_s* )o, out_index );

    ASSERT( link->target.body == &o->body );

    bcore_sink_a_push_fa( sink, "Tracing node '#<sc_t>.#<sc_t>':\n", bsym_ifnameof( o->name ), bsym_ifnameof( link->name ) );
    bsym_net_link_s_trace_to_sink( bsym_sem_graph_s_get_arg_out( ( bsym_sem_graph_s* )o, out_index ), 0, sink );
    bcore_sink_a_push_fa( sink, "\n" );
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_push_link( bsym_sem_graph_s* o )
{
    return bsym_net_body_s_push_link( &o->body );
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_push_literal_scalar( bsym_sem_graph_s* o, f3_t val )
{
    bsym_net_node_s* node = bsym_net_body_s_push_literal_scalar( &o->body, val );
    node->name = bsym_entypeof( "literal" );
    bsym_net_link_s* link = bsym_sem_graph_s_push_link( o );
    bsym_net_address_s_copy( &link->target, &node->root );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_link_s* bsym_sem_graph_s_push_literal_holor( bsym_sem_graph_s* o, const bmath_hf3_s* holor )
{
    bsym_net_node_s* node = bsym_net_body_s_push_literal_holor( &o->body, holor );
    node->name = bsym_entypeof( "literal" );
    bsym_net_link_s* link = bsym_sem_graph_s_push_link( o );
    bsym_net_address_s_copy( &link->target, &node->root );
    return link;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_sem_graph_s_push_node( bsym_sem_graph_s* o, sz_t args )
{
    bsym_net_node_s* node = bsym_net_body_s_push_node( &o->body );
    bsym_net_node_s_set_size( node, args );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t bsym_sem_graph_s_trace_build_cell( bsym_sem_graph_s* o, bsym_net_address_s* addr, st_s* err_msg )
{
    if( !addr->body )
    {
        if( err_msg ) st_s_push_fa( err_msg, "Node #<sc_t>: Trace ends in open link.", bsym_ifnameof( o->name ) );
        return false;
    }

    bsym_net* net = bsym_net_address_s_get_net( addr );

    if( *( aware_t* )net == TYPEOF_bsym_net_link_s )
    {
        bsym_net_link_s* link = ( bsym_net_link_s* )net;
        if( link->flag ) return true;
        bsym_net_address_s_copy( addr, &link->target );
        return bsym_sem_graph_s_trace_build_cell( o, addr, err_msg );
    }

    if( *( aware_t* )net == TYPEOF_bsym_net_node_s )
    {
        bsym_net_node_s* node = ( bsym_net_node_s* )net;
        if( node->root.body != &o->body )
        {
            if( !node->new_root )
            {
                bsym_net_node_s* new_node = bsym_net_body_s_clone_node( &o->body, node );
                node->new_root = &new_node->root;
            }

            bsym_net_address_s_copy( addr, node->new_root );
            node = ( bsym_net_node_s* )bsym_net_address_s_get_net( addr );
        }
        for( sz_t i = 0; i < node->targets_size; i++ )
        {
            if( !bsym_sem_graph_s_trace_build_cell( o, &node->targets_data[ i ], err_msg ) ) return false;
        }
        return true;
    }

    if( err_msg ) st_s_push_fa( err_msg, "Trace ends in invalid object '#<sc_t>'.", ifnameof( *( aware_t* )net ) );

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

/// converts all sub-nodes into a graph held by o->body
bl_t bsym_sem_graph_s_build_cell( bsym_sem_graph_s* o, st_s* err_msg )
{
    sc_t sc_name = bsym_ifnameof( o->name );

    // set flag
    for( sz_t i = 0; i < o->args_in;  i++ ) bsym_sem_graph_s_get_arg_in( o, i )->flag = true;

    for( sz_t i = 0; i < o->args_out; i++ )
    {
        bsym_net_link_s* link = bsym_sem_graph_s_get_arg_out( o, i );
        if( !bsym_sem_graph_s_trace_build_cell( o, &link->target, err_msg ) )
        {
            if( err_msg )
            {
                st_s* msg = st_s_create();
                st_s_push_fa( msg, "Backtracing output channel #<sc_t>.#<sc_t>:\n", sc_name, bsym_ifnameof( link->name ) );
                st_s_push_fa( msg, "#<sc_t>\n", err_msg->sc );
                st_s_copy( err_msg, msg );
                st_s_discard( msg );
            }
            return false;
        }
    }

    // reset flag
    for( sz_t i = 0; i < o->args_in;  i++ ) bsym_sem_graph_s_get_arg_in( o, i )->flag = false;

    // remove local nodes
    bsym_sem_graph_base_s_discard( o->graph_base );
    o->graph_base = NULL;

    // try resolve holors as possible
    for( sz_t i = 0; i < o->args_out; i++ )
    {
        bsym_net_link_s* link = bsym_sem_graph_s_get_arg_out( o, i );
        bsym_net_link_s_trace_compute_hresult( link, false );
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_build_cell_check( bsym_sem_graph_s* o )
{
    st_s* err_msg = st_s_create();
    if( !bsym_sem_graph_s_build_cell( o, err_msg ) )
    {
        ERR_fa( "#<sc_t>\n", err_msg->sc );
    }
    st_s_discard( err_msg );
}

// ---------------------------------------------------------------------------------------------------------------------

/// in body of o: creates new graph which is catenated version of n1 : n2
bsym_sem_graph_s* bsym_sem_graph_s_cat_graph( bsym_sem_graph_s* o, bsym_sem_graph_s* graph1, bsym_sem_graph_s* graph2, bcore_source* source )
{
    bsym_sem_graph_s* gc = bsym_sem_graph_s_push_graph( o );
    bsym_source_info_s_set( &gc->source_info, source );
    bsym_sem_graph_s* g1 = bsym_sem_graph_s_clone_graph( gc, graph1 );
    bsym_sem_graph_s* g2 = bsym_sem_graph_s_clone_graph( gc, graph2 );

    sz_t free_args_in1 = bsym_sem_graph_s_get_free_args_in( g1 );

    /// free input channels of n1 must match output channels of n2
    if( free_args_in1 != g2->args_out )
    {
        bsym_source_info_s_parse_err_fa
        (
            &gc->source_info,
            "Catenating graphs: Left graph's free input channels (#<sz_t>) differs from right graphs's output channels (#<sz_t>).",
            free_args_in1,
            g2->args_out
        );
    }

    sz_t args_in_c = g2->args_in + g1->args_in - free_args_in1;
    bsym_sem_graph_s_set_args( gc, g1->args_out, args_in_c );

    sz_t k = 0; // arg_in_c index

    // all args-in of n2
    for( sz_t i = 0; i < g2->args_in; i++ )
    {
        bsym_net_link_s* arg_in_g = bsym_sem_graph_s_get_arg_in( g2, i   );
        bsym_net_link_s* arg_in_c = bsym_sem_graph_s_get_arg_in( gc, k++ );
        ASSERT( arg_in_c );
        bsym_net_address_s_copy( &arg_in_c->target, &arg_in_g->target );
        bsym_net_address_s_copy( &arg_in_g->target, &arg_in_c->root   );
    }

    // used args-in of n1
    for( sz_t i = 0; i < g1->args_in; i++ )
    {
        bsym_net_link_s* arg_in_g = bsym_sem_graph_s_get_arg_in( g1, i );
        if( arg_in_g->target.body )
        {
            bsym_net_link_s* arg_in_c = bsym_sem_graph_s_get_arg_in( gc, k++ );
            ASSERT( arg_in_c );
            bsym_net_address_s_copy( &arg_in_c->target, &arg_in_g->target );
            bsym_net_address_s_copy( &arg_in_g->target, &arg_in_c->root   );
        }
    }

    // channels between n1 : n2
    for( sz_t i = 0; i < free_args_in1; i++ )
    {
        bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( g1 )->target, &bsym_sem_graph_s_get_arg_out( g2, i )->root );
    }

    // output channels
    for( sz_t i = 0; i < gc->args_out; i++ )
    {
        bsym_net_address_s_copy( &bsym_sem_graph_s_get_arg_out( gc, i )->target, &bsym_sem_graph_s_get_arg_out( g1, i )->root );
    }

    bsym_sem_graph_s_build_cell_check( gc );
    return gc;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_sem_graph_s_push_op( bsym_sem_graph_s* o, sz_t args, sz_t priority, tp_t name )
{
    bsym_sem_graph_s* graph = bsym_sem_graph_s_push_graph( o );
    graph->name = name;
    graph->priority = priority < 0 ? graph->priority : priority;
    bsym_sem_graph_s_set_args( graph, 1, args );
    bsym_net_node_s* node = bsym_sem_graph_s_push_node( graph, args );
    node->name = name;
    for( sz_t i = 0; i < args; i++ )
    {
        bsym_net_address_s_copy( &node->targets_data[ i ], &bsym_sem_graph_s_get_arg_in( graph, i )->root );
    }
    bsym_net_address_s_copy( &bsym_sem_graph_s_get_arg_out( graph, 0 )->target, &node->root );

    bsym_sem_graph_s_build_cell_check( graph );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_push_op1_d( bsym_sem_graph_s* o, bsym_op_ar1* op )
{
    sc_t symbol = bsym_op_ar1_a_get_symbol( op );
    sz_t priority = bsym_op_a_get_priority( ( bsym_op* )op );
    tp_t tp_name = bsym_entypeof( symbol );
    bsym_net_node_s* node = bsym_sem_graph_s_push_op( o, 1, priority, tp_name );
    node->op = ( bsym_op* )op;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_push_op2_d( bsym_sem_graph_s* o, bsym_op_ar2* op )
{
    sc_t symbol = bsym_op_ar2_a_get_symbol( op );
    sz_t priority = bsym_op_a_get_priority( ( bsym_op* )op );
    tp_t tp_name = bsym_entypeof( symbol );
    bsym_net_node_s* node = bsym_sem_graph_s_push_op( o, 2, priority, tp_name );
    node->op = ( bsym_op* )op;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_set_source_info( bsym_sem_graph_s* o, bcore_source* source )
{
    bsym_net_body_s_set_source_info( &o->body, source );
}

// ---------------------------------------------------------------------------------------------------------------------

tp_t bsym_sem_graph_s_parse_name( bsym_sem_graph_s* o, bcore_source* source )
{
    st_s* name = st_s_create();
    bcore_source_a_parse_fa( source, " #name", name );
    if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Name expected." );
    tp_t tp_name = bsym_entypeof( name->sc );
    st_s_discard( name );
    return tp_name;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_assert_identifier_not_defined( const bsym_sem_graph_s* o, tp_t name, bcore_source* source )
{
    for( sz_t i = 0; i < o->body.size; i++ )
    {
        if( bsym_net_a_get_name( o->body.data[ i ] ) == name )
        {
            bcore_source_a_parse_err_fa( source, "Identifier '#<sc_t>' already exists.", bsym_ifnameof( name ) );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_create_args_out( bsym_sem_graph_s* o, bcore_source* source )
{
    ASSERT( o->args_in == 0 );
    ASSERT( o->args_out == 0 );
    ASSERT( o->body.size == 0 );

    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );
        bsym_net_link_s* link = bsym_net_body_s_push_link( &o->body );
        link->name = bsym_sem_graph_s_parse_name( o, source );
        o->args_out++;
        first = false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_create_args_in( bsym_sem_graph_s* o, bsym_sem_graph_s* parent, bcore_source* source )
{
    ASSERT( o->args_in == 0 );
    ASSERT( o->body.size == o->args_out );

    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );
        bsym_net_link_s* link = bsym_net_body_s_push_link( &o->body );
        link->name = bsym_sem_graph_s_parse_name( o, source );
        o->args_in++;

        if( bcore_source_a_parse_bl_fa( source, " #?'->'" ) )
        {
            bsym_net_address_s_copy( &link->target, bsym_sem_graph_s_evaluate_address( parent, source ) );
        }

        first = false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_evaluate_set_args_in( bsym_sem_graph_s* o, bsym_sem_graph_s* parent, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    BCORE_LIFE_CREATE( st_s, name );

    bcore_source_a_parse_fa( source, " (" );
    bl_t first = true;
    while( !bcore_source_a_parse_bl_fa( source, " #?')'" ) )
    {
        if( !first ) bcore_source_a_parse_fa( source, " ," );

        bl_t done = false;

        if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( bcore_source_a_parse_bl_fa( source, " #?'->'" ) )
            {
                bsym_net_link_s* link = bsym_sem_graph_s_get_arg_in_by_name( o, typeof( name->sc ) );
                if( !link )
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' specifies no input channel of graph '#<sc_t>'.", name->sc, bsym_ifnameof( o->name ) );
                }

                if( link->target.body )
                {
                    bcore_source_a_parse_err_fa( source, "Channel '#<sc_t>' of graph '#<sc_t>' has already been set.", name->sc, bsym_ifnameof( o->name ) );
                }

                bsym_net_address_s_copy( &link->target, bsym_sem_graph_s_evaluate_address( parent, source ) );
                done = true;
            }
            else
            {
                bcore_arr_vd_s_push( stack, name );
            }
        }

        if( !done )
        {
            bsym_net_link_s* link = bsym_sem_graph_s_get_next_free_arg_in( o );

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Node '#<sc_t>': Assigning more links than available.", bsym_ifnameof( o->name ) );
            }

            bsym_net_address_s* addr = bsym_sem_graph_s_evaluate_address_stack( parent, stack, source );
            bsym_net_address_s_copy( &link->target, addr );
        }

        first = false;
    }

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

static vd_t cast_a( tp_t type, vd_t o, bcore_source* source )
{
    if( *( aware_t* )o == type ) return o;
    bcore_source_a_parse_err_fa( source, "Type error: '#<sc_t>' present but '#<sc_t>' expected.", ifnameof( *( aware_t* )o ), ifnameof( type ) );
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

sc_t bsym_sem_graph_s_parse_op2_symbol( bsym_sem_graph_s* o, bcore_source* source )
{
    bcore_arr_st_s* arr = o->arr_symbol_op2;
    if( !arr ) return 0;

    st_s* format = st_s_create();
    sc_t ret = NULL;

    for( sz_t i = 0; i < arr->size; i++ )
    {
        st_s_copy_fa( format, " ##?'#<sc_t>'", arr->data[ i ]->sc );
        if( bcore_source_a_parse_bl_fa( source, format->sc ) )
        {
            ret = arr->data[ i ]->sc;
            break;
        }
    }

    st_s_discard( format );

    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

// returns false in case expression does not yield a literal, otherwise the result is attached to r
bl_t bsym_sem_graph_s_evaluate_literal( bsym_sem_graph_s* o, bcore_source* source, bmath_hf3_s** ret )
{
    // literal scalar
    if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='0'&&[0]<='9')||([0]=='-'&&([1]>='0'&&[1]<='9')))" ) )
    {
        f3_t val = 0;
        bcore_source_a_parse_fa( source, " #<f3_t*>", &val );

        bmath_hf3_s* hf3 = bmath_hf3_s_create();
        bmath_hf3_s_fit_v_size( hf3 );
        hf3->v_data[ 0 ] = val;

        bmath_hf3_s_attach( ret, hf3 );
        return true;
    }

    // undetermined scalar
    if( bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
    {
        bmath_hf3_s* hf3 = bmath_hf3_s_create();
        bmath_hf3_s_attach( ret, hf3 );
        return true;
    }

    // literal holor
    if( bcore_source_a_parse_bl_fa( source, " #?'{'" ) )
    {
        bmath_hf3_s* hf3 = bmath_hf3_s_create();
        bmath_hf3_s* sub_hf3 = NULL;
        while( !bcore_source_a_eos( source ) )
        {
            if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
            {
                sub_hf3 = bsym_sem_graph_s_evaluate_hf3( o, source );
                bcore_source_a_parse_fa( source, " )" );
            }
            else
            {
                if( !bsym_sem_graph_s_evaluate_literal( o, source, &sub_hf3 ) ) bcore_source_a_parse_err_fa( source, "Literal expected." );
            }

            if( hf3->d_size > 0 || hf3->v_size > 0 )
            {
                if( hf3->d_size > sub_hf3->d_size + 1 || hf3->d_size < sub_hf3->d_size )
                {
                    bcore_source_a_parse_err_fa( source, "Jagged arrays are not supported." );
                }

                for( sz_t i = 0; i < sub_hf3->d_size; i++ )
                {
                    if( hf3->d_data[ i ] != sub_hf3->d_data[ i ] ) bcore_source_a_parse_err_fa( source, "Jagged arrays are not supported." );
                }

                if( hf3->v_data && !sub_hf3->v_data )
                {
                    bcore_source_a_parse_err_fa( source, "Appending undetermined holor to determined holor." );
                }

                if( !hf3->v_data && sub_hf3->v_data )
                {
                    bcore_source_a_parse_err_fa( source, "Appending determined holor to undetermined holor." );
                }
            }


            bmath_hf3_s_push( hf3, sub_hf3 );
            if( bcore_source_a_parse_bl_fa( source, " #?'}'" ) ) break;
        }
        bmath_hf3_s_detach( &sub_hf3 );
        bmath_hf3_s_attach( ret, hf3 );
        return true;
    }

    // (n+1)-holor of n-holor
    if( bcore_source_a_parse_bl_fa( source, " #?'['" ) )
    {
        sz_t dim = bsym_sem_graph_s_evaluate_f3( o, source );
        if( dim <= 0 ) bcore_source_a_parse_err_fa( source, "Holor dimension > 0 expected." );
        bcore_source_a_parse_bl_fa( source, " ]" );
        bmath_hf3_s* hf3 = NULL;
        bmath_hf3_s_replicate( &hf3, bsym_sem_graph_s_evaluate_hf3( o, source ) );
        bmath_hf3_s_inc_order( hf3, dim );
        bmath_hf3_s_attach( ret, hf3 );
        return true;
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_evaluate_stack( bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( st_s, name );
    BCORE_LIFE_CREATE( bsym_sem_stack_flag_s, bin_op_flag );
    BCORE_LIFE_CREATE( bsym_sem_stack_flag_s, catenation );

    sc_t op2_symbol = NULL;
    bmath_hf3_s* literal = NULL;

    while( !bcore_source_a_eos( source ) )
    {
        bl_t identifier = false;

        // identifier
        if( stack->size > 0 && *(aware_t*)stack->data[ 0 ] == TYPEOF_st_s )
        {
            st_s_copy( name, bcore_arr_vd_s_pop( stack ) );
            identifier = true;
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?(([0]>='A'&&[0]<='Z')||([0]>='a'&&[0]<='z'))" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            identifier = true;
        }

        if( identifier )
        {
            tp_t tp_name = typeof( name->sc );

            /// disallowed identifiers inside evaluation
            if
            (
                tp_name == TYPEOF_graph ||
                tp_name == TYPEOF_link  ||
                tp_name == TYPEOF_holor
            )
            {
                bcore_source_a_parse_err_fa( source, "Unexpected keyword '#<sc_t>'. Forgot ';' on previous statement?", name->sc );
            }

            vd_t item = NULL;

            // input channel
            if( ( item = bsym_sem_graph_s_get_arg_in_by_name( o, tp_name ) ) )
            {
                bsym_net_link_s* link = item;
                bcore_arr_vd_s_push( stack, &link->root );
            }

            // link on body
            else if( ( item = bsym_sem_graph_s_get_link_from_body_by_name( o, tp_name ) ) )
            {
                bsym_net_link_s* link = item;
                bcore_arr_vd_s_push( stack, &link->root );
            }

            // graph
            else if( ( item = bsym_sem_graph_s_get_graph_by_name( o, tp_name ) ) )
            {
                bsym_sem_graph_s* graph = item;

                if( bsym_sem_graph_s_get_free_args_in( graph ) > 0 )
                {
                    graph = bsym_sem_graph_s_clone_graph( o, graph );
                    bsym_source_info_s_set( &graph->source_info, source );
                }

                if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
                {
                    bsym_sem_graph_s_evaluate_set_args_in( graph, o, source );
                }
                bcore_arr_vd_s_push( stack, graph );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cannot evaluate identifier '#<sc_t>'.", name->sc );
            }
        }

        // literal or array element from literal
        else if( bcore_source_a_parse_bl_fa( source, " #=?'['" ) )
        {
            // array element from literal
            if( stack->size > 0 && ( *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_net_address_s ) )
            {
                bcore_source_a_parse_fa( source, " [" );
                sz_t index = bsym_sem_graph_s_evaluate_f3( o, source );
                bcore_source_a_parse_fa( source, " ]" );

                bsym_net_address_s* address = bcore_arr_vd_s_pop( stack );
                bsym_net_hresult_s* hresult = bsym_net_a_trace_compute_hresult( ( bsym_net* )address, true );
                const bmath_hf3_s* hf3 = hresult->hf3;

                if( hf3->d_size == 0 ) bcore_source_a_parse_err_fa( source, "Cannot index a scalar literal." );
                if( index < 0 || index >= hf3->d_data[ hf3->d_size -1 ] ) bcore_source_a_parse_err_fa( source, "Index '#<sz_t>' is out of range.", index );
                if( hf3->v_size == 0 ) bcore_source_a_parse_err_fa( source, "Cannot index an undetermined holor." );

                bmath_hf3_s* sub_hf3 = bmath_hf3_s_create();
                bmath_hf3_s_set_d_data( sub_hf3, hf3->d_data, hf3->d_size -1 );
                sub_hf3->v_size = bmath_hf3_s_d_product( sub_hf3 );
                sub_hf3->v_data = hf3->v_data + index * sub_hf3->v_size;
                sub_hf3->v_space = 0;
                bcore_arr_vd_s_push( stack, &bsym_sem_graph_s_push_literal_holor( o, sub_hf3 )->root );
                bmath_hf3_s_detach( &sub_hf3 );
            }
            // literal
            else if( bsym_sem_graph_s_evaluate_literal( o, source, &literal ) )
            {
                bcore_arr_vd_s_push( stack, &bsym_sem_graph_s_push_literal_holor( o, literal )->root );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Syntax error.", name->sc );
            }
        }

        // literal (including undetermined holors)
        else if( bsym_sem_graph_s_evaluate_literal( o, source, &literal ) )
        {
            bcore_arr_vd_s_push( stack, &bsym_sem_graph_s_push_literal_holor( o, literal )->root );
        }

        // block
        else if( bcore_source_a_parse_bl_fa( source, " #?'('" ) )
        {
            bcore_arr_vd_s_push( stack, bsym_sem_graph_s_evaluate_net( o, source ) );
            bcore_source_a_parse_fa( source, " )" );
        }

        // binary operator from predefined symbols
        else if( ( op2_symbol = bsym_sem_graph_s_parse_op2_symbol( o, source ) ) )
        {
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", op2_symbol );
            bsym_sem_graph_s* graph = bsym_sem_graph_s_get_graph_by_name( o, typeof( op2_symbol ) );
            if( !graph ) bcore_source_a_parse_err_fa( source, "Syntax error." );
            graph = bsym_sem_graph_s_clone_graph( o, graph );
            bsym_sem_graph_s_set_source_info( graph, source );
            bcore_arr_vd_s_push( stack, bin_op_flag );
            bcore_arr_vd_s_push( stack, graph );
        }

        // custom binary operator
        else if( bcore_source_a_parse_bl_fa( source, " #?'<'" ) )
        {
            bcore_source_a_parse_fa( source, "#until'>'>", name );
            if( stack->size == 0 ) bcore_source_a_parse_err_fa( source, "Operator '#<sc_t>': Left operand missing.", name->sc );
            bsym_sem_graph_s* graph = bsym_sem_graph_s_get_graph_by_name( o, typeof( name->sc ) );
            if( !graph ) bcore_source_a_parse_err_fa( source, "Graph '#<sc_t>' not found.", name->sc );
            graph = bsym_sem_graph_s_clone_graph( o, graph );
            bsym_sem_graph_s_set_source_info( graph, source );
            bcore_arr_vd_s_push( stack, bin_op_flag );
            bcore_arr_vd_s_push( stack, graph );
        }

        // output channel selection
        else if( bcore_source_a_parse_bl_fa( source, " #?'.'" ) )
        {
            bcore_source_a_parse_fa( source, "#name", name );
            if( name->size == 0 ) bcore_source_a_parse_err_fa( source, "Identifier expected." );

            if( *(aware_t*)stack->data[ stack->size - 1 ] != TYPEOF_bsym_sem_graph_s )
            {
                bcore_source_a_parse_err_fa( source, "Output channel selection on non-graph." );
            }

            bsym_sem_graph_s* graph = bcore_arr_vd_s_pop( stack );
            sz_t free_args = bsym_sem_graph_s_get_free_args_in( graph );
            sc_t sc_node_name = bsym_ifnameof( graph->name );

            if( free_args > 0 )
            {
                bcore_source_a_parse_err_fa( source, "Channel selection '.': Node #<sz_t> has #<sz_t> free input channels.", sc_node_name, free_args );
            }

            bsym_net_link_s* link = bsym_sem_graph_s_get_arg_out_by_name( graph, typeof( name->sc ) );

            if( !link )
            {
                bcore_source_a_parse_err_fa( source, "Node '#<sc_t>':Invalid channel '#<sc_t>'.", sc_node_name, name->sc );
            }
            bcore_arr_vd_s_push( stack, &link->root );
        }

        // graph catenation
        else if( bcore_source_a_parse_bl_fa( source, " #?':'" ) )
        {
            if( stack->size >= 1 && *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_sem_graph_s )
            {
                bcore_arr_vd_s_push( stack, catenation );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Node catenation ':': l-value is not a graph." );
            }
        }

        // compute holors
        else if( bcore_source_a_parse_bl_fa( source, " #?'!'" ) )
        {
            bsym_net* net = bsym_sem_graph_s_evaluate_net( o, source );
            bsym_net_a_trace_compute_hresult( net, true );
            bcore_arr_vd_s_push( stack, net );
        }

        // terminator
        else if( bcore_source_a_parse_bl_fa( source, " #?([0]==')'||[0]==']'||[0]==','||[0]==';')" ) )
        {
            break;
        }

        else
        {
            bcore_source_a_parse_err_fa( source, "Syntax error." );
        }

        /// priority stack processing ...

        // <left arg> <flag> <bin-operator>  error checks, left operand conversion, output generation
        if( stack->size >= 3 && stack->data[ stack->size - 2 ] == bin_op_flag )
        {
            bsym_sem_graph_s* graph = cast_a( TYPEOF_bsym_sem_graph_s, bcore_arr_vd_s_pop( stack ), source );
            ASSERT( bin_op_flag == bcore_arr_vd_s_pop( stack ) );
            bsym_net* arg1 = bcore_arr_vd_s_pop( stack );

            if( *(aware_t*)arg1 == TYPEOF_bsym_sem_graph_s )
            {
                bsym_sem_graph_s* graph1 = ( bsym_sem_graph_s* )arg1;
                if( graph1->args_out != 1 )
                {
                    bsym_source_info_s_parse_err_fa
                    (
                        &graph1->source_info,
                        "Binary operator '#<sc_t>': Left operant '#<sc_t>' has #<sz_t> output channels. Expected exactly one.",
                        bsym_ifnameof( graph->name ),
                        bsym_ifnameof( graph1->name ),
                        graph->args_out
                    );
                }
                arg1 = ( bsym_net* )&bsym_sem_graph_s_get_arg_out( graph1, 0 )->root;
            }

            sz_t free_args = bsym_sem_graph_s_get_free_args_in( graph );
            if( free_args != 2 )
            {
                bsym_source_info_s_parse_err_fa
                (
                    &graph->source_info,
                    "Binary operator '#<sc_t>' has #<sz_t> free input channels. Expected exactly two.",
                    bsym_ifnameof( graph->name ),
                    free_args
                );
            }

            if( graph->args_out != 1 )
            {
                bsym_source_info_s_parse_err_fa
                (
                    &graph->source_info,
                    "Binary operator '#<sc_t>' has #<sz_t> output channels. Expected exactly one.",
                    bsym_ifnameof( graph->name ),
                    graph->args_out
                );
            }

            bcore_arr_vd_s_push( stack, arg1 );
            bcore_arr_vd_s_push( stack, bin_op_flag );
            bcore_arr_vd_s_push( stack, graph );
            bcore_arr_vd_s_push( stack, &bsym_sem_graph_s_get_arg_out( graph, 0 )->root );
        }

        // graph-catenation
        if( stack->size >= 3 && stack->data[ stack->size - 2 ] == catenation )
        {
            if( *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_sem_graph_s )
            {
                bsym_sem_graph_s* graph2 = cast_a( TYPEOF_bsym_sem_graph_s, bcore_arr_vd_s_pop( stack ), source );
                ASSERT( bcore_arr_vd_s_pop( stack ) == catenation );
                bsym_sem_graph_s* graph1 = cast_a( TYPEOF_bsym_sem_graph_s, bcore_arr_vd_s_pop( stack ), source );
                sz_t free_args1 = bsym_sem_graph_s_get_free_args_in( graph1 );
                if( free_args1 != graph2->args_out )
                {
                    bcore_source_a_parse_err_fa( source, "Graph catenation 'G1 : G2': G1 has #<sz_t> free input arguments; G2 has #<sz_t> output arguments.", free_args1, graph2->args_out );
                }

                bsym_sem_graph_s* graph = bsym_sem_graph_s_cat_graph( o, graph1, graph2, source );

                bcore_arr_vd_s_push( stack, graph );
            }
            else if( *(aware_t*)stack->data[ stack->size - 1 ] == TYPEOF_bsym_net_address_s )
            {
                bsym_net_address_s* addr = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );
                ASSERT( bcore_arr_vd_s_pop( stack ) == catenation );
                bsym_sem_graph_s* graph2 = cast_a( TYPEOF_bsym_sem_graph_s, bcore_arr_vd_s_pop( stack ), source );
                sz_t free_args2 = bsym_sem_graph_s_get_free_args_in( graph2 );
                if( free_args2 != 1 )
                {
                    bcore_source_a_parse_err_fa( source, "Catenation 'N1 : Link': N1 has #<sz_t> free input arguments; required is 1", free_args2 );
                }

                bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph2 )->target, addr );
                bcore_arr_vd_s_push( stack, graph2 );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "Cannot resolve catenation." );
            }
        }
    }

    /// remaining stack processing ...
    bl_t resolve_stack = true;
    while( resolve_stack )
    {
        // <left address> <flag> <bin-operator> <output> <left address>
        if( stack->size >= 5 && stack->data[ stack->size - 4 ] == bin_op_flag )
        {
            bsym_net_address_s* addr2 = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );
            bsym_net_address_s* out   = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );
            bsym_sem_graph_s*  graph  = cast_a( TYPEOF_bsym_sem_graph_s,   bcore_arr_vd_s_pop( stack ), source );
            ASSERT( bin_op_flag == bcore_arr_vd_s_pop( stack ) );
            bsym_net_address_s* addr1 = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );

            if( stack->size >= 4 && stack->data[ stack->size - 3 ] == bin_op_flag ) // merge with prior operation considering priority
            {
                bsym_net_address_s* prior_out   = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );
                bsym_sem_graph_s*  prior_graph  = cast_a( TYPEOF_bsym_sem_graph_s,   bcore_arr_vd_s_pop( stack ), source );
                ASSERT( bin_op_flag == bcore_arr_vd_s_pop( stack ) );
                bsym_net_address_s* prior_addr1 = cast_a( TYPEOF_bsym_net_address_s, bcore_arr_vd_s_pop( stack ), source );

                if( prior_graph->priority >= graph->priority )
                {
                    bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph )->target, prior_out );
                    bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph )->target, addr2 );

                    bcore_arr_vd_s_push( stack, prior_addr1 );
                    bcore_arr_vd_s_push( stack, bin_op_flag );
                    bcore_arr_vd_s_push( stack, prior_graph );
                    bcore_arr_vd_s_push( stack, out );
                    bcore_arr_vd_s_push( stack, addr1 );
                }
                else
                {
                    bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph )->target, addr1 );
                    bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph )->target, addr2 );

                    bcore_arr_vd_s_push( stack, prior_addr1 );
                    bcore_arr_vd_s_push( stack, bin_op_flag );
                    bcore_arr_vd_s_push( stack, prior_graph );
                    bcore_arr_vd_s_push( stack, prior_out );
                    bcore_arr_vd_s_push( stack, out );           // out becomes right argument for prior_graph
                }
            }
            else // fully resolve operation
            {
                bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph )->target, addr1 );
                bsym_net_address_s_copy( &bsym_sem_graph_s_get_next_free_arg_in( graph )->target, addr2 );
                bcore_arr_vd_s_push( stack, out );
            }
        }
        else
        {
            resolve_stack = false;
        }
    }

    bmath_hf3_s_detach( &literal );
    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net* bsym_sem_graph_s_evaluate_net_stack( bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    bsym_sem_graph_s_evaluate_stack( o, stack, source );
    if( stack->size != 1 ) bcore_source_a_parse_err_fa( source, "Expression syntax error." );
    vd_t ret = bcore_arr_vd_s_pop( stack );
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_address_s* bsym_sem_graph_s_evaluate_address_stack( bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    vd_t ret = bsym_sem_graph_s_evaluate_net_stack( o, stack, source );
    if( *( aware_t* )ret == TYPEOF_bsym_sem_graph_s )
    {
        bsym_sem_graph_s* graph = ret;
        sz_t free_args = bsym_sem_graph_s_get_free_args_in( graph );
        if( free_args > 0 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic output channel selection on graph with #<sz_t> free input channels.", free_args );
        }

        if( graph->args_out != 1 )
        {
            bcore_source_a_parse_err_fa( source, "Automatic output channel selection on graph with #<sz_t> output channels.", graph->args_out );
        }

        ret = &bsym_sem_graph_s_get_arg_out( graph, 0 )->root;
    }

    if( *( aware_t* )ret != TYPEOF_bsym_net_address_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Address expected.", ifnameof( *( aware_t* )ret ) );
    }
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_graph_s* bsym_sem_graph_s_evaluate_graph_stack( bsym_sem_graph_s* o, bcore_arr_vd_s* stack, bcore_source* source )
{
    vd_t ret = bsym_sem_graph_s_evaluate_net_stack( o, stack, source );
    if( *( aware_t* )ret != TYPEOF_bsym_sem_graph_s )
    {
        bcore_source_a_parse_err_fa( source, "Expression yields #<sc_t>. Graph Expected.", ifnameof( *( aware_t* )ret ) );
    }
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net* bsym_sem_graph_s_evaluate_net( bsym_sem_graph_s* o, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    vd_t ret = bsym_sem_graph_s_evaluate_net_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_address_s* bsym_sem_graph_s_evaluate_address( bsym_sem_graph_s* o, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    vd_t ret = bsym_sem_graph_s_evaluate_address_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_node_s* bsym_sem_graph_s_evaluate_node( bsym_sem_graph_s* o, bcore_source* source )
{
    vd_t address = bsym_sem_graph_s_evaluate_address( o, source );
    bsym_net_node_s* node = bsym_net_a_trace_get_node( address );
    if( !node ) bcore_source_a_parse_err_fa( source, "Expression does not yield a node." );
    return node;
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_net_hresult_s* bsym_sem_graph_s_evaluate_hresult( bsym_sem_graph_s* o, bcore_source* source )
{
    bsym_net_hresult_s* hresult = bsym_net_a_trace_compute_hresult( ( bsym_net* )bsym_sem_graph_s_evaluate_node( o, source ), true );
    return hresult;
}

// ---------------------------------------------------------------------------------------------------------------------

bmath_hf3_s* bsym_sem_graph_s_evaluate_hf3( bsym_sem_graph_s* o, bcore_source* source )
{
    bsym_net_hresult_s* hresult = bsym_sem_graph_s_evaluate_hresult( o, source );
    if( !hresult ) bcore_source_a_parse_err_fa( source, "Expression does not yield a holor." );
    return hresult->hf3;
}

// ---------------------------------------------------------------------------------------------------------------------

f3_t bsym_sem_graph_s_evaluate_f3( bsym_sem_graph_s* o, bcore_source* source )
{
    bmath_hf3_s* hf3 = bsym_sem_graph_s_evaluate_hf3( o, source );
    if( hf3->d_size  > 0 ) bcore_source_a_parse_err_fa( source, "Expression does not yield a scalar." );
    if( hf3->v_size == 0 ) bcore_source_a_parse_err_fa( source, "Expression yields a vacant scalar." );
    return hf3->v_data[ 0 ];
}

// ---------------------------------------------------------------------------------------------------------------------

bsym_sem_graph_s* bsym_sem_graph_s_evaluate_graph( bsym_sem_graph_s* o, bcore_source* source )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bcore_arr_vd_s, stack );
    vd_t ret = bsym_sem_graph_s_evaluate_graph_stack( o, stack, source );
    BCORE_LIFE_DOWN();
    return ret;
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_parse_body( bsym_sem_graph_s* o, bcore_source* source )
{
    bcore_source_a_parse_fa( source, " " );
    while( !bcore_source_a_eos( source ) && !bcore_source_a_parse_bl_fa( source, " #=?'}'" ) )
    {
        if( bcore_source_a_parse_bl_fa( source, " #?'graph'" ) )
        {
            bl_t first = true;
            while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
            {
                if( !first ) bcore_source_a_parse_fa( source, " ," );
                bsym_sem_graph_s* graph = bsym_sem_graph_s_push_graph( o );
                bsym_sem_graph_s_parse( graph, o, source );
                first = false;
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'link'" ) )
        {
            bl_t first = true;
            while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
            {
                if( !first ) bcore_source_a_parse_fa( source, " ," );
                bsym_net_link_s* link = bsym_sem_graph_s_push_link( o );
                tp_t name = bsym_sem_graph_s_parse_name( o, source );
                bsym_sem_graph_s_assert_identifier_not_defined( o, name, source );
                link->name = name;
                bcore_source_a_parse_fa( source, " -> " );
                bsym_net_address_s_copy( &link->target, bsym_sem_graph_s_evaluate_address( o, source ) );
                first = false;
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'holor'" ) )
        {
            tp_t holor_type = bsym_sem_graph_s_parse_name( o, source );
            if
            (
                holor_type != TYPEOF_adaptive &&
                holor_type != TYPEOF_buffer
            )
            {
                bcore_source_a_parse_err_fa( source, "Define holor type: 'adaptive | buffer'" );
            }

            bl_t first = true;
            while( !bcore_source_a_parse_bl_fa( source, " #?';'" ) )
            {
                if( !first ) bcore_source_a_parse_fa( source, " ," );
                bsym_net_node_s* net_node = bsym_sem_graph_s_push_node( o, 0 );
                bsym_source_info_s_set( &net_node->source_info, source );

                bsym_net_link_s* link = bsym_sem_graph_s_push_link( o );
                tp_t name = bsym_sem_graph_s_parse_name( o, source );
                bsym_sem_graph_s_assert_identifier_not_defined( o, name, source );
                link->name = name;
                bsym_net_address_s_copy( &link->target, &net_node->root );

                bcore_source_a_parse_fa( source, " = " );
                net_node->op = bsym_op_t_create( TYPEOF_bsym_op_ar0_holor_s );
                net_node->name = link->name;
                bsym_op_ar0_holor_s* holor = ( bsym_op_ar0_holor_s* )net_node->op;
                holor->type = holor_type;

                bcore_arr_sz_s* arr_sz = bcore_arr_sz_s_create();

                while( !bcore_source_a_parse_bl_fa( source, " #?'#'" ) )
                {
                    bcore_source_a_parse_fa( source, " [" );
                    bsym_net_address_s* address = bsym_net_node_s_push( net_node );
                    bsym_net_address_s_copy( address, bsym_sem_graph_s_evaluate_address( o, source ) );
                    bsym_net_hresult_s* hresult = bsym_net_address_s_trace_compute_hresult( address, false );
                    if( hresult && hresult->hf3->v_size == 1 )
                    {
                        bcore_arr_sz_s_push( arr_sz, *hresult->hf3->v_data );
                        bsym_net_address_s_clear( address );
                    }
                    else
                    {
                        bcore_arr_sz_s_push( arr_sz, 0 );
                    }
                    bcore_source_a_parse_fa( source, " ]" );
                }

                bmath_hf3_s_set_d_size( &holor->hf3, arr_sz->size );

                // fill in sizes in reverse order
                for( sz_t i = 0; i < arr_sz->size; i++ ) holor->hf3.d_data[ arr_sz->size - i - 1 ] = arr_sz->data[ i ];

                if( bmath_hf3_s_d_product( &holor->hf3 ) > 0 )
                {
                    bsym_net_node_s_clear( net_node );
                }

                first = false;
                bcore_arr_sz_s_discard( arr_sz );
            }
        }
        else if( bcore_source_a_parse_bl_fa( source, " #?'?'" ) )
        {
            bl_t just_holor = bcore_source_a_parse_bl_fa( source, "#?'?'" );

            bsym_net_address_s* address = bsym_sem_graph_s_evaluate_address( o, source );

            if( just_holor )
            {
                bsym_net_node_s* node = bsym_net_address_s_trace_get_node( address );
                if( node && node->hresult && node->hresult->hf3 )
                {
                    bmath_hf3_s_formatted_to_stdout( node->hresult->hf3 );
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "Expression does not evaluate to a literal." );
                }
            }
            else
            {
                bsym_net_address_s_trace_to_sink( address, 0, BCORE_STDOUT );
                bcore_sink_a_push_fa( BCORE_STDOUT, "\n" );
            }

            bcore_source_a_parse_fa( source, " ;" );
        }
        else
        {
            st_s* name = st_s_create();
            bcore_source_a_parse_fa( source, " #name", name );
            if( !name->size ) bcore_source_a_parse_err_fa( source, "Identifier expected." );
            tp_t tp_name = typeof( name->sc );

            bsym_net_node_s* node;
            bsym_net_link_s* link;

            if( ( node = bsym_sem_graph_s_get_node_by_name( o, tp_name ) ) )
            {
                if( *(aware_t*)node->op == TYPEOF_bsym_op_ar0_holor_s )
                {
                    bsym_op_ar0_holor_s* holor = ( bsym_op_ar0_holor_s* )node->op;
                    if( holor->type == TYPEOF_buffer )
                    {
                        //TODO: implement this for recurrent holors
//                        holor->backfeed =
                    }
                    else
                    {
                        bcore_source_a_parse_err_fa( source, "holor '#<sc_t>' if of type '#<sc_t>'. Feeding is only possible for type 'buffer'.", name->sc, ifnameof( holor->type ) );
                    }
                }
                else
                {
                    bcore_source_a_parse_err_fa( source, "'#<sc_t>' should be holor or output channel.", name->sc );
                }
            }
            else if( ( link = bsym_sem_graph_s_get_arg_out_by_name( o, tp_name ) ) )
            {
                if( link->target.body )
                {
                    bcore_source_a_parse_err_fa( source, "Link '#<sc_t>' of graph '#<sc_t>' has already been set.", name->sc, bsym_ifnameof( o->name ) );
                }

                bcore_source_a_parse_fa( source, " ->" );

                bsym_net_address_s_copy( &link->target, bsym_sem_graph_s_evaluate_address( o, source ) );
            }
            else
            {
                bcore_source_a_parse_err_fa( source, "'#<sc_t>' should be holor or output channel.", name->sc );
            }

            bcore_source_a_parse_fa( source, " ;" );

            st_s_discard( name );
        }

        bcore_source_a_parse_fa( source, " " );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_parse( bsym_sem_graph_s* o, bsym_sem_graph_s* parent, bcore_source* source )
{
    // <name >
    tp_t tp_graph_name = bsym_sem_graph_s_parse_name( o, source );
    if( parent ) bsym_sem_graph_s_assert_identifier_not_defined( parent, tp_graph_name, source );

    //  ( <args_out> ) => ( <args_in> )  { <body> }
    if( bcore_source_a_parse_bl_fa( source, " #=?'('" ) )
    {
        bsym_sem_graph_s_create_args_out( o, source );
        bcore_source_a_parse_fa( source, " => " );
        bsym_sem_graph_s_create_args_in( o, parent, source );
        bcore_source_a_parse_fa( source, " {" );
        bsym_sem_graph_s_parse_body( o, source );
        bcore_source_a_parse_fa( source, " }" );
        o->name = tp_graph_name;
    }

    // = expression yielding a graph
    else
    {
        bcore_source_a_parse_fa( source, " = " );
        bsym_sem_graph_s* graph = bsym_sem_graph_s_evaluate_graph( parent, source );
        bsym_sem_graph_s_copy_graph( o, graph );
        o->name = tp_graph_name;
    }

    // build graph
    bsym_sem_graph_s_build_cell_check( o );
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_frame_setup( bsym_sem_graph_s* o )
{
    BCORE_LIFE_INIT();
    o->graph_base = bsym_sem_graph_base_s_create();
    o->arr_symbol_op2 = bcore_arr_st_s_create();

    BCORE_LIFE_CREATE( bcore_arr_tp_s, arr_tp );

    bcore_get_traits_of_ancestor( TYPEOF_bsym_op_ar1, arr_tp );
    for( sz_t i = 0; i < arr_tp->size; i++ )
    {
        bsym_sem_graph_s_push_op1_d( o, bsym_op_ar1_t_create( arr_tp->data[ i ] ) );
    }

    bcore_get_traits_of_ancestor( TYPEOF_bsym_op_ar2, arr_tp );
    for( sz_t i = 0; i < arr_tp->size; i++ )
    {
        bsym_op_ar2* op2 = bsym_op_ar2_t_create( arr_tp->data[ i ] );
        bsym_sem_graph_s_push_op2_d( o, op2 );
        bcore_arr_st_s_push_sc( o->arr_symbol_op2, bsym_op_ar2_a_get_symbol( op2 ) );
    }

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_frame_compile( bsym_sem_graph_s* o, bcore_source* source )
{
    bsym_sem_graph_s_parse_body( o, source );
    bsym_sem_graph_s* root = bsym_sem_graph_s_get_graph_by_name( o, typeof( "root" ) );
    if( root )
    {
        for( sz_t i = 0; i < root->args_out; i++ )
        {
            bsym_net_link_s* link = bsym_sem_graph_s_get_arg_out( root, i );
            if( link->name == 0 )
            {
                bsym_source_info_s_parse_err_fa( &o->source_info, "Output link without name." );
            }
            bsym_net_hresult_s* hresult = bsym_net_link_s_trace_compute_hresult( link, true );
            if( !hresult )
            {
                bsym_source_info_s_parse_err_fa( &o->source_info, "Cannot resolve output channel '#<sc_t>'.", bsym_ifnameof( link->name ) );
            }
            hresult->name = link->name;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void bsym_sem_graph_s_build_vm( bsym_sem_graph_s* o, bmath_hf3_vm_frame_s* vm_frame )
{
    bsym_sem_graph_s* root = bsym_sem_graph_s_get_graph_by_name( o, typeof( "root" ) );
    if( root )
    {
        for( sz_t i = 0; i < root->args_in; i++ )
        {
            bsym_net_link_s* link = bsym_sem_graph_s_get_arg_in( root, i );
            bsym_net_hresult_s* hresult = bsym_net_link_s_trace_compute_hresult( link, true );
            hresult->name = bsym_entypeof_fa( "root_in#<sz_t>", i );
        }

        for( sz_t i = 0; i < root->args_out; i++ )
        {
            bsym_net_link_s* link = bsym_sem_graph_s_get_arg_out( root, i );
            bsym_net_hresult_s* hresult = bsym_net_link_s_trace_compute_hresult( link, true );
            hresult->name = bsym_entypeof_fa( "root_out#<sz_t>", i );
            bsym_net_link_s_trace_build_vm_proc( link, vm_frame, TYPEOF_infer );
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// VIRTUAL MACHINE
/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void bsym_vm_adaptive_s_minfer( bsym_vm_adaptive_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    ASSERT( o->vm.arr_holor.size < o->in_index );
    ASSERT( o->vm.arr_holor.size < o->out_index );
    bmath_hf3_s* h_in  = &o->vm.arr_holor.data[ o->in_index  ].hf3;
    bmath_hf3_s* h_out = &o->vm.arr_holor.data[ o->out_index ].hf3;
}

// ---------------------------------------------------------------------------------------------------------------------

badapt_adaptive* bsym_vm_builder_s_build( const bsym_vm_builder_s* o )
{
    bsym_vm_adaptive_s* adaptive = bsym_vm_adaptive_s_create();
    st_s_copy( &adaptive->holograph_file, &o->holograph_file );
    adaptive->in_size = o->in_size;
    adaptive->out_size = o->out_size;
    badapt_dynamics_std_s_copy( &adaptive->dynamics, &o->dynamics );

    tp_t tp_name_out_size  = bsym_entypeof( o->name_out_size.sc  );
    tp_t tp_name_in_holor  = bsym_entypeof( o->name_in_holor.sc  );
    tp_t tp_name_out_holor = bsym_entypeof( o->name_out_holor.sc );

    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bsym_sem_graph_s, graph );
    BCORE_LIFE_CREATE( bmath_hf3_s, h_in_holor );
    BCORE_LIFE_CREATE( bmath_hf3_s, h_out_size );
    bmath_hf3_s_set_scalar_f3( h_out_size, o->out_size );
    bmath_hf3_s_set_d_data_na( h_in_holor, 1, o->in_size );

    bsym_sem_graph_s_frame_setup( graph );
    bsym_sem_graph_s_set_args( graph, 1, 2 );

    {
        bsym_net_link_s* link_h_out_size = bsym_sem_graph_s_push_literal_holor( graph, h_out_size );
        bsym_net_link_s* link_h_in_holor = bsym_sem_graph_s_push_literal_holor( graph, h_in_holor );
        bsym_net_link_s* link_g_out_size = bsym_sem_graph_s_get_arg_in( graph, 0 );
        bsym_net_link_s* link_g_in_holor = bsym_sem_graph_s_get_arg_in( graph, 1 );
        bsym_net_link_s* link_g_out_holor = bsym_sem_graph_s_get_arg_out( graph, 0 );
        link_h_out_size->name  = tp_name_out_size;
        link_g_out_size->name  = tp_name_out_size;
        link_h_in_holor->name  = tp_name_in_holor;
        link_g_in_holor->name  = tp_name_in_holor;
        link_g_out_holor->name = tp_name_out_holor;
        bsym_net_address_s_copy( &link_g_out_size->target, &link_h_out_size->root );
        bsym_net_address_s_copy( &link_g_in_holor->target, &link_h_in_holor->root );
        bsym_net_hresult_s* hresult = bsym_net_link_s_trace_compute_hresult( link_g_in_holor, true );
        hresult->name = tp_name_in_holor;
    }

    {
        bcore_source* source = bcore_file_open_source( o->holograph_file.sc );
        bsym_sem_graph_s_parse_body( graph, source );
        bsym_net_link_s* link_g_out_holor = bsym_sem_graph_s_get_arg_out( graph, 0 );
        bsym_net_hresult_s* hresult = bsym_net_link_s_trace_compute_hresult( link_g_out_holor, true );
        hresult->name = tp_name_out_holor;

        if( bmath_hf3_s_d_product( hresult->hf3 ) != o->out_size )
        {
            bcore_source_a_parse_err_fa
            (
                source,
                "Output channel size is '#<sz_t>' but '#<sz_t>' was required.",
                bmath_hf3_s_d_product( hresult->hf3 ),
                o->out_size
            );
        }

        bsym_net_link_s_trace_build_vm_proc( link_g_out_holor, &adaptive->vm, TYPEOF_infer );

        adaptive->in_index  = bmath_hf3_vm_frame_s_get_holor_index( &adaptive->vm, tp_name_in_holor );
        adaptive->out_index = bmath_hf3_vm_frame_s_get_holor_index( &adaptive->vm, tp_name_out_holor );

        bcore_source_a_detach( &source );
    }

    BCORE_LIFE_RETURN( ( badapt_adaptive* )adaptive );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

void bsym_test( void )
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( bsym_vm_builder_s, builder );
    st_s_copy_sc( &builder->holograph_file, "models/bsym_mlp.hgp" );
    builder->in_size = 8;
    builder->out_size = 2;

    badapt_adaptive* adaptive = bsym_vm_builder_s_build( builder );

    badapt_adaptive_a_arc_to_sink( adaptive, BCORE_STDOUT );

    badapt_adaptive_a_discard( adaptive );

/*

    BCORE_LIFE_CREATE( bsym_sem_graph_s,    sem_frame );
    BCORE_LIFE_CREATE( bmath_hf3_vm_frame_s, vm_frame );
    bsym_sem_graph_s_frame_setup( sem_frame );

//    bcore_source* source = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/bsym_mlp.hgp" ) );
//    bcore_source* source = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/bsym_test.hgp" ) );
//    bcore_source* source = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/bsym_mul_test.hgp" ) );
//    bcore_source* source = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/syntax01.hog" ) );
    bcore_source* source = BCORE_LIFE_A_PUSH( bcore_file_open_source( "models/syntax02.hog" ) );


    bsym_sem_graph_s_frame_compile( sem_frame, source );
    bsym_sem_graph_s_build_vm( sem_frame, vm_frame );

//    bcore_txt_ml_a_to_stdout( vm_frame );
*/

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t bsym_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "bsym" ) ) )
    {
        case TYPEOF_init1:
        {
            hmap_name_g = bcore_hmap_name_s_create();
        }
        break;

        case TYPEOF_down1:
        {
            if( hmap_name_g ) bcore_hmap_name_s_detach( &hmap_name_g );
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "badapt_dev_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


