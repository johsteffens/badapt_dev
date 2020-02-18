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

#include "lion_nop.h"

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

static lion_nop_context_s* context_g = NULL;

lion_nop_context_s* lion_nop_get_context( void )
{
    return context_g;
}

/**********************************************************************************************************************/
// lion_nop

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_solve__( const lion_nop* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( result );
    lion_holor_s** r = &result->h;
    lion_holor_s_detach( r );
    sz_t arity = lion_nop_a_arity( o );
    bl_t settled = ( arity > 0 );
    bl_t vacant = ( arity == 0 );
    tp_t r_type = TYPEOF_f2_t;
    bl_t r_htp  = false;
    bl_t active = false;

    bhvm_shape_s* base_shape = BLM_CREATE( bhvm_shape_s );

    for( sz_t i = 0; i < arity; i++ )
    {
        if( !a[i] ) BLM_RETURNV( bl_t, false );
        if( a[i]->h.v.type == TYPEOF_f3_t ) r_type = TYPEOF_f3_t;
        if( i == 0 )
        {
            bhvm_shape_s_copy( base_shape, &a[i]->h.s );
        }
        else
        {
            if( lion_nop_a_eci( o ) )
            {
                if( a[i]->h.s.size > base_shape->size )
                {
                    if( !bhvm_shape_s_is_sub( &a[i]->h.s, base_shape ) ) BLM_RETURNV( bl_t, false );
                    bhvm_shape_s_copy( base_shape, &a[i]->h.s );
                }
                else
                {
                    if( !bhvm_shape_s_is_sub( base_shape, &a[i]->h.s ) ) BLM_RETURNV( bl_t, false );
                }
            }
            else
            {
                if( !bhvm_shape_s_is_equal( base_shape, &a[i]->h.s ) ) BLM_RETURNV( bl_t, false );
            }
            //if( ( a[0]->m.htp != a[i]->m.htp ) ) BLM_RETURNV( bl_t, false );
            if( ( a[0]->m.htp != a[i]->m.htp ) && a[0]->h.s.size > 0 && a[i]->h.s.size > 0 ) BLM_RETURNV( bl_t, false );
        }

        r_htp = a[ i ]->m.htp;
        active = active || a[i]->m.active;
        vacant = vacant || ( a[i]->h.v.size == 0 );
    }

    settled = !active;

    lion_holor_s_attach( r, lion_holor_s_create() );
    bhvm_holor_s* hr = &(*r)->h;
    (*r)->m.htp = r_htp;
    (*r)->m.active = active;

    if( arity > 0 ) bhvm_shape_s_copy( &hr->s, base_shape );

    bhvm_holor_s_set_type( hr, r_type );

    if( !vacant )
    {
        bhvm_holor_s_fit_size( hr );

        // We setup a mini frame and run vop_ap on it.
        bhvm_mcode_hbase_s* hbase = BLM_CREATEC( bhvm_mcode_hbase_s, set_size, arity + 1 );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATEC( bhvm_vop_arr_ci_s,  set_size, arity + 1 );

        for( sz_t i = 0; i <= arity; i++ )
        {
            bhvm_holor_s_init_weak_from_holor( &hbase->holor_ads.data[ i ], ( i < arity ) ? &a[ i ]->h : hr );
            arr_ci->data[ i ].i = i;
            arr_ci->data[ i ].c = ( i < arity ) ? 'a' + i : 'y';
        }

        result->type_vop_ap = lion_nop_a_defines_type_vop_ap( o ) ? lion_nop_a_type_vop_ap( o ) : 0;
        assert( result->type_vop_ap );

        bhvm_vop_a_run( bhvm_vop_a_set_args( BLM_A_PUSH( bhvm_vop_t_create( result->type_vop_ap ) ), arr_ci ), hbase->holor_ads.data );
    }

    result->settled = settled;
    BLM_RETURNV( bl_t, true );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar1_output_s

// ---------------------------------------------------------------------------------------------------------------------

sz_t lion_nop_ar1_output_s_mcode_push_dp_holor( const lion_nop_ar1_output_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();

    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );

    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_dp,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_dp, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );

    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar1_cast_htp_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar1_cast_htp_s_solve( const lion_nop_ar1_cast_htp_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_create() );
        bhvm_holor_s_init_fork_from_holor( &result->h->h, &a[0]->h );
        lion_hmeta_s_copy( &result->h->m, &a[0]->m );
        result->h->m.htp = !a[0]->m.htp;
    }
    result->settled = result->h && !result->h->m.active;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t lion_nop_ar1_cast_htp_s_mcode_push_ap_holor
(
    const lion_nop_ar1_cast_htp_s* o,
    const lion_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    BLM_INIT();
    bhvm_holor_s* h = &result->h->h;
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'y', idx );

    bhvm_vop_ar1_fork_s* fork = bhvm_vop_ar1_fork_s_create();
    fork->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'a' );
    fork->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'y' );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_ap, ( bhvm_vop* )fork );

    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_shelve_ap, ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create(), arr_ci_l );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t lion_nop_ar1_cast_htp_s_mcode_push_dp_holor
(
    const lion_nop_ar1_cast_htp_s* o,
    const lion_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    BLM_INIT();

    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'z', idx );

    bhvm_vop_ar1_fork_s* fork = bhvm_vop_ar1_fork_s_create();
    fork->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'f' );
    fork->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    ASSERT( fork->i.v[ 0 ] >= 0 );
    ASSERT( fork->i.v[ 1 ] >= 0 );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_dp, ( bhvm_vop* )fork );

    bhvm_vop_ar0_vacate_s* vacate = bhvm_vop_ar0_vacate_s_create();
    vacate->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    ASSERT( vacate->i.v[ 0 ] >= 0 );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_dp, ( bhvm_vop* )vacate );

    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar2_mul_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_bmul_s_solve( const lion_nop_ar2_bmul_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( result );
    lion_holor_s** r = &result->h;
    lion_holor_s_attach( r, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );

    void (*f)( const bhvm_holor_s* a, const bhvm_holor_s* b, bhvm_holor_s* r );
    f = NULL;

    if( *r )
    {
        result->h->m.active = a[0]->m.active || a[1]->m.active;

        lion_holor_s* lha = a[0];
        lion_holor_s* lhb = a[1];
        lion_holor_s* lhr = (*r);
        bhvm_holor_s* ha = &lha->h;
        bhvm_holor_s* hb = &lhb->h;
        bhvm_holor_s* hr = &lhr->h;
        bhvm_holor_s_set_type( hr, ha->v.type == TYPEOF_f2_t && hb->v.type == TYPEOF_f2_t ? TYPEOF_f2_t : TYPEOF_f3_t );

        bl_t a_htp = lha->m.htp;
        bl_t b_htp = lhb->m.htp;
        bl_t r_htp = false;

        if( ha->s.size == 0 )
        {
            if( hb->s.size == 0 )
            {
                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                    f =        bhvm_hop_ar2_eci_mul_s_f;
                bhvm_shape_s_set_data_na( &hr->s, 0 );
                r_htp = false;
            }
            else if( hb->s.size == 1 )
            {
                if( b_htp )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                        f =        bhvm_hop_ar2_eci_mul_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, hb->s.data[ 0 ] );
                    r_htp = true;
                }
                else
                {
                    BLM_RETURNV( bl_t, false );
                }
            }
            else
            {
                BLM_RETURNV( bl_t, false );
            }
        }
        else if( ha->s.size == 1 )
        {
            if( hb->s.size == 0 )
            {
                if( !a_htp )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                        f =        bhvm_hop_ar2_eci_mul_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, ha->s.data[ 0 ] );
                    r_htp = false;
                }
                else
                {
                    BLM_RETURNV( bl_t, false );
                }
            }
            else if( hb->s.size == 1 )
            {
                if( a_htp && !b_htp )  // dot product
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_dp_b_s;
                                        f =        bhvm_hop_ar2_eci_mul_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 0 );
                    r_htp = false;
                }
                else if( !a_htp && b_htp )  // outer product
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvm_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vvm_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 0 ], ha->s.data[ 0 ] );
                    r_htp = false;
                }
                else
                {
                    BLM_RETURNV( bl_t, false );
                }
            }
            else if( hb->s.size == 2 )
            {
                if( !a_htp ) BLM_RETURNV( bl_t, false );
                if( b_htp )
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vtv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vtv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, hb->s.data[ 1 ] );
                }
                else
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 1 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vmv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vmv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, hb->s.data[ 0 ] );
                }
                r_htp = true;
            }
            else
            {
                BLM_RETURNV( bl_t, false );
            }
        }
        else if( ha->s.size == 2 )
        {
            if( hb->s.size == 0 )
            {
                BLM_RETURNV( bl_t, false );
            }
            else if( hb->s.size == 1 )
            {
                if( b_htp ) BLM_RETURNV( bl_t, false );
                if( a_htp )
                {
                    if( ha->s.data[ 1 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tvv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_tvv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, ha->s.data[ 0 ] );
                }
                else
                {
                    if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mvv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_mvv_s_f;
                    bhvm_shape_s_set_data_na( &hr->s, 1, ha->s.data[ 1 ] );
                }
                r_htp = false;
            }
            else if( hb->s.size == 2 )
            {
                if( a_htp )
                {
                    if( b_htp )
                    {
                        if( ha->s.data[ 1 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_ttm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_ttm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 1 ], ha->s.data[ 0 ] );
                    }
                    else
                    {
                        if( ha->s.data[ 1 ] != hb->s.data[ 1 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tmm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_tmm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 0 ], ha->s.data[ 0 ] );
                    }
                    r_htp = false;
                }
                else
                {
                    if( b_htp )
                    {
                        if( ha->s.data[ 0 ] != hb->s.data[ 0 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mtm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_mtm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 1 ], ha->s.data[ 1 ] );
                    }
                    else
                    {
                        if( ha->s.data[ 0 ] != hb->s.data[ 1 ] ) BLM_RETURNV( bl_t, false );
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mmm_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_mmm_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, 2, hb->s.data[ 0 ], ha->s.data[ 1 ] );
                    }
                    r_htp = false;
                }
            }
            else
            {
                BLM_RETURNV( bl_t, false );
            }
        }
        else
        {
            BLM_RETURNV( bl_t, false );
        }

        lhr->m.htp = r_htp;

        if( ( ha->v.size > 0 ) && ( hb->v.size > 0 ) )
        {
            ASSERT( f );
            bhvm_holor_s_fit_size( hr );
            f( ha, hb, hr );
        }
    }

    result->settled = ( result->h && !result->h->m.active );
    BLM_RETURNV( bl_t, true );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar2_(c)cat_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_cat_s_solve( const lion_nop_ar2_cat_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        result->h->m.active = a[0]->m.active || a[1]->m.active;
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( !bhvm_holor_s_cat_can( ha, hb ) ) return false;
        bhvm_holor_s_cat_set( ha, hb, hr );
    }
    result->settled = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_ccat_s_solve( const lion_nop_ar2_ccat_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        result->h->m.active = a[0]->m.active || a[1]->m.active;
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( !bhvm_holor_s_ccat_can( ha, hb ) ) return false;
        bhvm_holor_s_ccat_set( ha, hb, hr );
    }
    result->settled = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar2_order_inc_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_order_inc_s_solve( const lion_nop_ar2_order_inc_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_attach( &result->h, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        lion_hmeta_s_copy( &result->h->m, &a[1]->m );

        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( ha->v.size != 1 ) return false;
        sz_t dim = bhvm_holor_s_f3_get_scalar( ha );
        if( dim <= 0 ) return false;
        bhvm_holor_s_order_inc_set( hb, dim, hr );

        bhvm_vop_ar1_order_inc_s* order_inc = bhvm_vop_ar1_order_inc_s_create();
        order_inc->dim = dim;
        bhvm_vop_arr_s* vop_arr = bhvm_vop_arr_s_create();
        bhvm_vop_arr_s_push_d( vop_arr, ( bhvm_vop* )order_inc );
        bcore_inst_a_attach( (bcore_inst**)&result->attached, (bcore_inst*)vop_arr );
    }
    result->settled = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_nop_ar2_order_inc_s_mcode_push_ap_track( const lion_nop_ar2_order_inc_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    bhvm_vop* vop = bhvm_vop_a_clone( ( ( bhvm_vop_arr_s* )result->attached )->data[ 0 ] );
    bhvm_vop_a_set_index( vop, 0, bhvm_vop_arr_ci_s_i_of_c( arr_ci, 'b' ) );  // default signature 'ay' would be incorrect in this case
    bhvm_vop_a_set_index( vop, 1, bhvm_vop_arr_ci_s_i_of_c( arr_ci, 'y' ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_ap, vop );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar2_order_dec_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_order_dec_s_solve( const lion_nop_ar2_order_dec_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    lion_holor_s_detach( &result->h );
    if( a[0] && a[0]->m.htp ) return false;
    lion_holor_s_attach( &result->h, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );
    if( result->h )
    {
        lion_hmeta_s_copy( &result->h->m, &a[0]->m );

        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hb = &a[1]->h;
        bhvm_holor_s* hr = &result->h->h;
        if( hb->v.size != 1 ) return false;
        sz_t index = bhvm_holor_s_f3_get_scalar( hb );
        if( ha->s.size == 0 ) return false;
        if( index < 0 || index >= ha->s.data[ ha->s.size - 1 ] ) return false;
        bhvm_holor_s_order_dec_fork( ha, index, hr );

        bhvm_vop_ar1_order_dec_fork_s* order_dec_fork = bhvm_vop_ar1_order_dec_fork_s_create();
        order_dec_fork->idx = index;
        bhvm_vop_arr_s* vop_arr = bhvm_vop_arr_s_create();
        bhvm_vop_arr_s_push_d( vop_arr, ( bhvm_vop* )order_dec_fork );
        bcore_inst_a_attach( (bcore_inst**)&result->attached, (bcore_inst*)vop_arr );
    }
    result->settled = ( result->h && !result->h->m.active );
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t lion_nop_ar2_order_dec_s_mcode_push_ap_holor( const lion_nop_ar2_order_dec_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    bhvm_holor_s* h = &result->h->h;
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'y', idx );

    bhvm_vop_ar1_order_dec_fork_s* fork = bhvm_vop_ar1_order_dec_fork_s_clone( ( bhvm_vop_ar1_order_dec_fork_s* )( ( bhvm_vop_arr_s* )result->attached )->data[ 0 ] );
    fork->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'a' );
    fork->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'y' );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_ap, ( bhvm_vop* )fork );

    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_shelve_ap, ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create(), arr_ci_l );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t lion_nop_ar2_order_dec_s_mcode_push_dp_holor( const lion_nop_ar2_order_dec_s* o, const lion_nop_solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf )
{
    BLM_INIT();
    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );

    bhvm_vop_arr_ci_s* arr_ci_l = BLM_CLONE( bhvm_vop_arr_ci_s, arr_ci );
    bhvm_vop_arr_ci_s_push_ci( arr_ci_l, 'z', idx );

    bhvm_vop_ar1_order_dec_fork_s* fork = bhvm_vop_ar1_order_dec_fork_s_clone( ( bhvm_vop_ar1_order_dec_fork_s* )( ( bhvm_vop_arr_s* )result->attached )->data[ 0 ] );
    fork->i.v[ 0 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'f' );
    fork->i.v[ 1 ] = bhvm_vop_arr_ci_s_i_of_c( arr_ci_l, 'z' );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_dp, ( bhvm_vop* )fork );

    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_dp, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    BLM_RETURNV( sz_t, idx );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar2_recurrent_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_recurrent_s_solve( const lion_nop_ar2_recurrent_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    if( a[0] )
    {
        lion_holor_s_attach( &result->h, lion_holor_s_create() );
        result->h->m.active = true;
        bhvm_holor_s* ha = &a[0]->h;
        bhvm_holor_s* hr = &result->h->h;
        bhvm_shape_s_copy( &hr->s, &ha->s );

        if( a[1] )
        {
            bhvm_holor_s* hb = &a[1]->h;
            if( !bhvm_shape_s_is_equal( &ha->s, &hb->s ) ) return false;
            result->settled = ( !a[0]->m.active ) && ( !a[1]->m.active );
            return true;
        }
        else
        {
            result->settled = false;
            return true;
        }
    }
    else
    {
        if( a[1] ) return false;
        lion_holor_s_attach( &result->h, NULL );
        result->settled = false;
        return true;
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void lion_nop_ar2_recurrent_s_mcode_push_ap_track
(
    const lion_nop_ar2_recurrent_s* o,
    const lion_nop_solve_result_s* result,
    const bhvm_vop_arr_ci_s* arr_ci,
    bhvm_mcode_frame_s* mcf
)
{
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_setup_ap, bhvm_vop_t_create( TYPEOF_bhvm_vop_ar1_cpy_ay_s ), arr_ci );
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap,       bhvm_vop_t_create( TYPEOF_bhvm_vop_ar1_cpy_by_s ), arr_ci );
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
// lion_nop_ar3_branch_s

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar3_branch_s_solve( const lion_nop_ar3_branch_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    if( a[0] )
    {
        bhvm_holor_s* ha = &a[0]->h;
        if( ha->v.size != 1 ) return false;
        f3_t cond = bhvm_holor_s_f3_get_scalar( ha );
        if( cond > 0 )
        {
            lion_holor_s_attach( &result->h, bcore_fork( a[1] ) );
        }
        else
        {
            lion_holor_s_attach( &result->h, bcore_fork( a[2] ) );
        }

        if( result->h ) result->h->m.active = false;
    }
    result->settled = ( result->h && !result->h->m.active );
    result->codable = false;
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t lion_nop_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "lion_nop" ) ) )
    {
        case TYPEOF_init1:
        {
            lion_nop_context_s_attach( &context_g, lion_nop_context_s_create() );
        }
        break;

        case TYPEOF_down1:
        {
            lion_nop_context_s_detach( &context_g );
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "lion_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


