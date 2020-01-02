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
// nop

// ---------------------------------------------------------------------------------------------------------------------

bl_t lion_nop_ar2_mul_s_solve( const lion_nop_ar2_mul_s* o, lion_holor_s** a, lion_nop_solve_result_s* result )
{
    BLM_INIT();
    ASSERT( result );
    lion_holor_s** r = &result->h;
    lion_holor_s_attach( r, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );

    void (*f)( const bhvm_holor_s* a, const bhvm_holor_s* b, bhvm_holor_s* r );
    f = NULL;

    if( *r )
    {
        lion_holor_s* lha = a[0];
        lion_holor_s* lhb = a[1];
        lion_holor_s* lhr = (*r);
        bhvm_holor_s* ha = &lha->h;
        bhvm_holor_s* hb = &lhb->h;
        bhvm_holor_s* hr = &lhr->h;
        bhvm_holor_s_set_type( hr, ha->v.type == TYPEOF_f2_t && hb->v.type == TYPEOF_f2_t ? TYPEOF_f2_t : TYPEOF_f3_t );

        if( hb->s.size == 0 )
        {
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vsv_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vsv_dp_a_s;
            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vsv_dp_b_s;
            f = bhvm_hop_ar2_mul_vsv_s_f;
            bhvm_shape_s_copy( &hr->s, &ha->s );
            lhr->m.htp = ( ha->s.size > 0 ) ? lha->m.htp : false;
        }
        else if( ha->s.size == 0 )
        {
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_svv_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_svv_dp_a_s;
            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_svv_dp_b_s;
            f = bhvm_hop_ar2_mul_svv_s_f;
            bhvm_shape_s_copy( &hr->s, &hb->s );
            lhr->m.htp = ( hb->s.size > 0 ) ? lhb->m.htp : false;
        }
        else if( bhvm_shape_s_is_equal( &ha->s, &hb->s ) )
        {
            if( lha->m.htp != lhb->m.htp ) BLM_RETURNV( bl_t, false );
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvv_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_a_s;
            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_b_s;
            f = bhvm_hop_ar2_mul_vvv_s_f;
            bhvm_shape_s_copy( &hr->s, &ha->s );
            lhr->m.htp = lha->m.htp;
        }
        else
        {
            BLM_RETURNV( bl_t, false );
        }

        if( ( ha->v.size > 0 ) && ( hb->v.size > 0 ) )
        {
            bhvm_holor_s_fit_size( hr );
            f( ha, hb, hr );
        }
    }

    result->settled = ( *r && (*r)->h.v.size );
    BLM_RETURNV( bl_t, true );
}

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
                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvv_s;
                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_a_s;
                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_b_s;
                                    f =        bhvm_hop_ar2_mul_vvv_s_f;
                bhvm_shape_s_set_data_na( &hr->s, 0 );
                r_htp = false;
            }
            else if( hb->s.size == 1 )
            {
                if( b_htp )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_svv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_svv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_svv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_svv_s_f;
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
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vsv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vsv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vsv_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vsv_s_f;
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
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvs_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvs_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvs_dp_b_s;
                                        f =        bhvm_hop_ar2_mul_vvs_s_f;
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

    result->settled = ( *r && (*r)->h.v.size );
    BLM_RETURNV( bl_t, true );
}

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


