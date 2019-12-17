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

/// node operator

/**********************************************************************************************************************/

#ifndef LION_NOP_H
#define LION_NOP_H

#include "bmath_std.h"
#include "bhvm_mcode.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion

PLANT_GROUP( lion, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :hmeta = bhvm_mcode_hmeta
{
    tp_t name;
    tp_t class;
    bl_t htp;  // holor is transposed
};

stamp :holor = aware :
{
    :hmeta_s     m;
    bhvm_holor_s h;
    func bcore_fp : copy_typed;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_nop

BCORE_FORWARD_OBJECT( lion_nop_context_s );

/// returns global context
lion_nop_context_s* lion_nop_get_context( void );

PLANT_GROUP( lion_nop, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// operator class
name nop_class_regular;
name nop_class_cast;

/// tracks
name track_ap;
name track_dp;
name track_setup_ap;
name track_setup_dp;

feature 'a' sz_t arity( const ) = { ERR_fa( "Not implemented in '#<sc_t>'.", ifnameof( o->_ ) ); return -1; };
feature 'a' tp_t class( const ) = { return TYPEOF_nop_class_regular; };
feature 'a' sz_t priority( const ) = { return 10; };
feature 'a' sc_t symbol( const )   = { return NULL; };

/// converts an operator into a correspondent operator of arity n if possible; return NULL if conversion is not supported
feature        'a' :* create_op_of_arn( const, sz_t n ) = { return ( :a_arity( o ) == n ) ? :a_clone( o ) : NULL; };

/** Solve computes the result 'r' from an array of arguments 'a'.
  * 'a' represents an array of pointers. The array size is equal to arity.
  * Solve can produce three valid states:
  *   Detached (NULL): E.g. when arguments do not supply sufficient information (e.g. due to insufficient connectivity)
  *   Vacant (dimensions are fully determined)
  *   Determined - This represents a holor computed from literals and can itself be treated as literal.
  *
  *   Settled: The result is considered settled when the input was sufficient specific for computing a vm-operation
  *
  * Return: (deprecated)
  *   0: A valid result could be computed
  *   1: Output is settled. Triggers to finalize and discard graph spanned by operation.
  *   2: Situation of 1, additionally sets node-holor vacant (forces top-spanning graph to remain intact).
  *      E.g. This is required for adaptive operands, which stay in the graph even though they might
  *           have a literal state at compile time.
  *
  *   Negative values indicate errors
  *   -1: Incorrect operands for the given operation (this triggers a syntax error by the parser)
  *       if( msg ) function can push a specific error text.
  */

stamp :solve_result = bcore_inst
{
    /// optional message in case of failure
    st_s => msg;

    /// Output is settled: Triggers finalization and discards graph spanned by operation if reducible.
    bl_t settled = false;

    /// Operation provides mcode generation
    bl_t codable = true;

    /// If settled 'reducible' discards top-spanning graph
    bl_t reducible = true;

    /// preferred axon-pass vop type (0: not set)
    tp_t type_vop_ap;

    /// preferred dendrite-pass vop type for channels a...c (0: not set or inert dendrite pass)
    tp_t type_vop_dp_a;
    tp_t type_vop_dp_b;
    tp_t type_vop_dp_c;
};

/** Returns 'true' in case of success, otherwise check result->msg
  * The default implementation solves all elementary operators
  */
feature 'a' bl_t solve( const, lion_holor_s** r, lion_holor_s** a, :solve_result_s* result ) =
{
    BLM_INIT();
    if( !result ) result = BLM_CREATE( :solve_result_s );
    lion_holor_s_detach( r );
    sz_t arity = :a_arity( o );
    bl_t settled = ( arity > 0 );
    for( sz_t i = 0; i < arity; i++ )
    {
        if( !a[i] ) BLM_RETURNV( bl_t, false );
        bhvm_holor_s* h = &a[ i ]->h;
        if( h->v.size == 0 ) settled = false;
        if( i > 0 )
        {
            bhvm_holor_s* h0 = &a[ 0 ]->h;
            if( bhvm_shape_s_get_volume( &h->s ) != bhvm_shape_s_get_volume( &h0->s ) ) BLM_RETURNV( bl_t, false );
        }
    }

    lion_holor_s_attach( r, lion_holor_s_create() );
    bhvm_holor_s* hr = &(*r)->h;

    if( arity > 0 )
    {
        bhvm_holor_s* h0 = &a[ 0 ]->h;
        bhvm_shape_s_copy( &hr->s, &h0->s );
    }

    if( settled )
    {
        bhvm_holor_s_fit_size( hr );

        // We setup a mini frame and run vop_ap on it.
        bhvm_mcode_hbase_s* hbase = BLM_CREATE( bhvm_mcode_hbase_s );
        bhvm_vop_arr_ci_s* arr_ci = BLM_CREATE( bhvm_vop_arr_ci_s );
        bhvm_mcode_hbase_s_set_size( hbase, arity + 1 );
        bhvm_vop_arr_ci_s_set_size( arr_ci, arity + 1 );
        for( sz_t i = 0; i < arity; i++ )
        {
            bhvm_holor_s_init_weak_from_holor( &hbase->holor_ads.data[ i ], &a[ i ]->h );
            arr_ci->data[ i ].i = i;
            arr_ci->data[ i ].c = 'a' + i;
        }
        bhvm_holor_s_init_weak_from_holor( &hbase->holor_ads.data[ arity ], hr );
        arr_ci->data[ arity ].i = arity;
        arr_ci->data[ arity ].c = 'a' + arity;

        result->type_vop_ap = :a_defines_type_vop_ap( o ) ? :a_type_vop_ap( o ) : 0;
        assert( result->type_vop_ap );
        bhvm_vop* vop = BLM_A_PUSH( bhvm_vop_t_create( result->type_vop_ap ) );
        bhvm_vop_a_set_args( vop, arr_ci );
        bhvm_vop_a_run( vop, hbase->holor_ads.data );
    }

    result->settled = settled;
    BLM_RETURNV( bl_t, true );
};

/** Normally, the node solver calls solve after all arguments have been obtained.
 *  Certain (potentially cyclic) operators require a solve for each input channel.
 **/
feature 'a' bl_t requires_solve_for_each_channel( const ) = { return false; };

/** Finalizes holor.
 *  Default implementation turns it into a literal.
 **/
feature 'a' :* create_final( const, lion_holor_s* h ) =
{
    :ar0_literal_s* final = :ar0_literal_s_create();
    final->h = lion_holor_s_clone( h );
    return (:*)final;
};

/// preferred vop type (optional, when the type does not depend on holor parameters)
feature 'a' tp_t type_vop_ap( const );
feature 'a' tp_t type_vop_dp_a( const );
feature 'a' tp_t type_vop_dp_b( const );
feature 'a' tp_t type_vop_dp_c( const );

feature 'a' void mcode_push_ap( const, const :solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) =
{
    assert( result->type_vop_ap );
    tp_t type = ( :a_defines_type_vop_ap( o ) ) ? :a_type_vop_ap( o ) : result->type_vop_ap;
    bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap, bhvm_vop_t_create( type ), arr_ci );
};

feature 'a' void mcode_push_dp( const, const :solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) =
{
    if( ch_id >= :a_arity( o ) ) ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    tp_t type = 0;
    switch( ch_id )
    {
        case 'a': type = ( :a_defines_type_vop_dp_a( o ) ) ? :a_type_vop_dp_a( o ) : result->type_vop_dp_a; break;
        case 'b': type = ( :a_defines_type_vop_dp_b( o ) ) ? :a_type_vop_dp_b( o ) : result->type_vop_dp_b; break;
        case 'c': type = ( :a_defines_type_vop_dp_c( o ) ) ? :a_type_vop_dp_c( o ) : result->type_vop_dp_c; break;
        default: break;
    }
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_dp, bhvm_vop_t_create( type ), arr_ci );
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// global context
stamp :context = aware bcore_inst
{
    /** The randomizer is supposed to produce different values on repeated calls but
     *  always the same sequence of random values for building a network.
     *  Therefore randomizer_mutex is locked during a build.
     */
    private bcore_mutex_s* randomizer_mutex;
    bl_t                   randomizer_is_locked = false;
    u2_t                   randomizer_rval = 0;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group :ar0 = retrievable
{
    extending stump verbatim :_ = aware :
    {
        func :: :arity = { return 0; };
    };

    stamp :zro =
    {
        func :: :priority = { return 8; };
        func :: :solve =
        {
            lion_holor_s_attach( r, lion_holor_s_create() );
            bhvm_holor_s_set_scalar_f3( &(*r)->h, 0 );
            result->type_vop_ap = TYPEOF_bhvm_vop_ar0_zro_s;
            result->settled = true;
            return true;
        };
    };

    stamp :one =
    {
        func :: :priority = { return 8; };
        func :: :solve =
        {
            lion_holor_s_attach( r, lion_holor_s_create() );
            bhvm_holor_s_set_scalar_f3( &(*r)->h, 1 );
            result->type_vop_ap = TYPEOF_bhvm_vop_ar0_one_s;
            result->settled = true;
            return true;
        };
    };

    stamp :literal =
    {
        lion_holor_s -> h;
        func :: :solve =
        {
            lion_holor_s_attach( r, bcore_fork( o->h ) );
            result->settled = true;
            result->codable = false;
            return true;
        };
    };

    /// formal input (used for resolving the network; not part of language syntax)
    stamp :input =
    {
        lion_holor_s -> h;
        func :: :solve =
        {
            lion_holor_s_attach( r, bcore_fork( o->h ) );
            result->settled = true;
            result->codable = false;
            return true;
        };
    };

    /// nullary adaptive operator
    stamp :adaptive =
    {
        lion_holor_s -> h;
        func :: :solve =
        {
            lion_holor_s_attach( r, bcore_fork( o->h ) );
            result->settled = false;
            result->codable = false;
            return true;
        };
    };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group :ar1 = retrievable
{
    extending stump verbatim :_ = aware :
    {
        func :: :arity = { return 1; };
    };

    stamp :identity =
    {
        func :: :priority = { return 8; };
        func :: :solve =
        {
            lion_holor_s_attach( r, bcore_fork( a[0] ) );
            result->settled = (*r) && (*r)->h.v.size > 0;
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_identity_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_identity_dp_s;
            return true;
        };
    };

    stamp :neg =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "neg"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_neg_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar1_neg_dp_s; };
        func :: :create_op_of_arn =
        {
            return ( n == 2 ) ? (::*)::ar2_sub_s_create()
                 : ( n == 1 ) ? (::*)@_clone( o )
                 : NULL;
        };
    };

    stamp :floor =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "floor"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_floor_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar0_nul_dp_s; };
    };

    stamp :ceil =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "ceil"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_ceil_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar0_nul_dp_s; };
    };

    stamp :exp =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "exp"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_exp_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_exp_dp_s; };
    };

    stamp :inv =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "inv"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_inv_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_inv_dp_s; };
    };

    stamp :lgst =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "lgst"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_lgst_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_lgst_dp_s; };
    };

    stamp :lgst_hard =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "lgst_hard"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_lgst_hard_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_lgst_hard_dp_s; };
    };

    stamp :lgst_leaky =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "lgst_leaky"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_lgst_leaky_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_lgst_leaky_dp_s; };
    };

    stamp :tanh =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "tanh"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_tanh_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_tanh_dp_s; };
    };

    stamp :tanh_hard =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "tanh_hard"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_tanh_hard_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_tanh_hard_dp_s; };
    };

    stamp :tanh_leaky =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "tanh_leaky"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_tanh_leaky_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_tanh_leaky_dp_s; };
    };

    stamp :softplus =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "softplus"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_softplus_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_softplus_dp_s; };
    };

    stamp :relu =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "relu"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_relu_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_relu_dp_s; };
    };

    stamp :relu_leaky =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "relu_leaky"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_relu_leaky_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_relu_leaky_dp_s; };
    };

    /// formal output (used for resolving the network; not part of syntax)
    stamp :output =
    {
        func :: :solve =
        {
            lion_holor_s_attach( r, bcore_fork( a[0] ) );
            result->settled = (*r) && (*r)->h.v.size > 0;
            result->codable = false;
            return true;
        };
    };

    /** marks a holor or expression to be adaptive
     *  Operation is settled when at least a vacant holor can be computed.
     *  If the holor is vacant, it is initialized in the virtual machine.
     */
    stamp :adaptive =
    {
        tp_t name;

        func :: :symbol   = { return "adaptive"; };
        func :: :priority = { return 8; };

        func :: :solve =
        {
            lion_holor_s_attach( r, bcore_fork( a[0] ) );
            result->settled = ( *r != NULL );
            result->reducible = false; // keep subsequent graph intact
            result->codable = false;
            return true;
        };

        func :: :create_final =
        {
            ::ar0_adaptive_s* final = ::ar0_adaptive_s_create();
            final->h = lion_holor_s_clone( h );
            final->h->m.name = o->name;
            return (::*)final;
        };
    };

    /// returns leading dimension
    stamp :dimof =
    {
        func :: :symbol   = { return "dimof"; };
        func :: :priority = { return 8; };
        func :: :solve  =
        {
            lion_holor_s_attach( r, a[0] ? lion_holor_s_create() : NULL );
            if( *r ) bhvm_holor_s_set_scalar_f3( &(*r)->h, a[0]->h.s.size ? a[0]->h.s.data[ a[0]->h.s.size - 1 ] : 1 );
            result->type_vop_ap = TYPEOF_bhvm_vop_ar0_one_s;
            result->settled = *r != NULL;
            result->codable = false;
            return true;
        };
    };

    stamp :random =
    {
        u2_t rseed = 1234;
        func :: :symbol   = { return "random"; };
        func :: :priority = { return 8; };
        func :: :solve    =
        {
            lion_holor_s_attach( r, a[0] ? lion_holor_s_create() : NULL );
            if( *r )
            {
                ::context_s* context = ::get_context();
                ASSERT( context->randomizer_is_locked );
                if( context->randomizer_rval == 0 ) context->randomizer_rval = o->rseed;
                lion_holor_s_copy( *r, a[0] );
                if( !(*r)->h.v.size ) bhvm_holor_s_fit_size( &(*r)->h );
                bhvm_value_s_set_random( &(*r)->h.v, 1.0, -0.5, 0.5, &context->randomizer_rval );
                result->settled = true;
            }
            result->codable = false;
            return true;
        };
    };

    /// cast -------------------------------------------------------------------

    // Cast operators make the target weakly reference source data.
    // Value data is always referenced; shape might be referenced.
    // Cast operators are inert as far as actual vm-processing is concerned.
    // They are not intended to actually execute in ap of dp tracks.
    // They are typically placed in the setup track.

    stamp :cast_htp =
    {
        func :: :class     = { return TYPEOF_nop_class_cast; };
        func :: :priority  = { return 8; };
        func :: :solve =
        {
            lion_holor_s_attach( r, a[0] ? lion_holor_s_create() : NULL );
            if( *r )
            {
                bhvm_holor_s_init_fork_from_holor( &(*r)->h, &a[0]->h );
                (*r)->m.htp = !a[0]->m.htp;
            }
            result->settled = (*r) && (*r)->h.v.size > 0;
            result->codable = false;
            return true;
        };
    };

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group :ar2 = retrievable
{
    extending stump verbatim :_ = aware :
    {
        func :: :arity = { return 2; };
    };

    stamp :add =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "+"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_add_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar1_add_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar1_add_dp_b_s; };
    };

    stamp :sub =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "-"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_sub_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar1_sub_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar1_sub_dp_b_s; };
        func :: :create_op_of_arn =
        {
            return ( n == 2 ) ? (::*)@_clone( o )
                 : ( n == 1 ) ? (::*)::ar1_neg_s_create()
                 : NULL;
        };
    };

    stamp :div =
    {
        func :: :priority      = { return 10; };
        func :: :symbol        = { return "/"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_div_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_div_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar3_div_dp_b_s; };
    };

    stamp :mul =
    {
        func :: :priority = { return 10; };
        func :: :symbol   = { return "*"; };
        func :: :solve    =
        {
            BLM_INIT();
            if( !result ) result = BLM_CREATE( ::solve_result_s );
            lion_holor_s_attach( r, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );

            void (*f)( const bhvm_holor_s* a, const bhvm_holor_s* b, bhvm_holor_s* r );
            f = NULL;

            if( *r )
            {
                bhvm_holor_s* ha = &a[0]->h;
                bhvm_holor_s* hb = &a[1]->h;
                bhvm_holor_s* hr = &(*r)->h;
                if( bhvm_shape_s_is_equal( &ha->s, &hb->s ) )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_b_s;
                    f = bhvm_hop_ar2_mul_vvv_s_f;
                    bhvm_shape_s_copy( &hr->s, &ha->s );
                }
                else if( hb->s.size == 0 )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vsv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vsv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vsv_dp_b_s;
                    f = bhvm_hop_ar2_mul_vsv_s_f;
                    bhvm_shape_s_copy( &hr->s, &ha->s );
                }
                else if( ha->s.size == 0 )
                {
                    result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_svv_s;
                    result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_svv_dp_a_s;
                    result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_svv_dp_b_s;
                    f = bhvm_hop_ar2_mul_svv_s_f;
                    bhvm_shape_s_copy( &hr->s, &hb->s );
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
        };
    };

    stamp :bmul =
    {
        func :: :priority = { return 10; };
        func :: :symbol   = { return "**"; };
        func :: :solve    =
        {
            BLM_INIT();
            if( !result ) result = BLM_CREATE( ::solve_result_s );
            lion_holor_s_attach( r, ( a[0] && a[1] ) ? lion_holor_s_create() : NULL );

            void (*f)( const bhvm_holor_s* a, const bhvm_holor_s* b, bhvm_holor_s* r );
            f = NULL;

            if( *r )
            {
                bhvm_holor_s* ha = &a[0]->h;
                bhvm_holor_s* hb = &a[1]->h;
                bhvm_holor_s* hr = &(*r)->h;

                bl_t a_htp = a[0]->m.htp;
                bl_t b_htp = a[1]->m.htp;

                if( ha->s.size == 0 )
                {
                    if( hb->s.size == 0 )
                    {
                        result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvv_s;
                        result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_a_s;
                        result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvv_dp_b_s;
                                            f =        bhvm_hop_ar2_mul_vvv_s_f;
                        bhvm_shape_s_set_data_na( &hr->s, false, 0 );
                    }
                    else if( hb->s.size == 1 )
                    {
                        if( b_htp )
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_svv_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_svv_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_svv_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_svv_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, true, 1, &hb->s.data[ 0 ] );
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
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
                            bhvm_shape_s_set_data_na( &hr->s, false, 1, &ha->s.data[ 0 ] );
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else if( hb->s.size == 1 )
                    {
                        if( a_htp && !b_htp )  // dot product
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvs_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvs_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvs_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_vvs_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, false, 0 );
                        }
                        else if( !a_htp && b_htp )  // outer product
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vvm_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vvm_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_vvm_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, false, 2, hb->s.data[ 0 ], ha->s.data[ 0 ] );
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else if( hb->s.size == 2 )
                    {
                        if( !a_htp ) return false;
                        if( b_htp )
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vtv_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vtv_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_vtv_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, true, 1, hb->s.data[ 1 ] );
                        }
                        else
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_vmv_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_vmv_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_vmv_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, true, 1, hb->s.data[ 0 ] );
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else if( ha->s.size == 2 )
                {
                    if( hb->s.size == 0 )
                    {
                        return false;
                    }
                    else if( hb->s.size == 1 )
                    {
                        if( b_htp ) return false;
                        if( a_htp )
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tvv_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tvv_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_tvv_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, false, 1, ha->s.data[ 0 ] );
                        }
                        else
                        {
                            result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mvv_s;
                            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_a_s;
                            result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mvv_dp_b_s;
                                                f =        bhvm_hop_ar2_mul_mvv_s_f;
                            bhvm_shape_s_set_data_na( &hr->s, false, 1, ha->s.data[ 1 ] );
                        }
                    }
                    else if( hb->s.size == 2 )
                    {
                        if( a_htp )
                        {
                            if( b_htp )
                            {
                                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_ttm_s;
                                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_a_s;
                                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_ttm_dp_b_s;
                                                    f =        bhvm_hop_ar2_mul_ttm_s_f;
                                bhvm_shape_s_set_data_na( &hr->s, false, 2, hb->s.data[ 1 ], ha->s.data[ 0 ] );
                            }
                            else
                            {
                                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_tmm_s;
                                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_a_s;
                                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_tmm_dp_b_s;
                                                    f =        bhvm_hop_ar2_mul_tmm_s_f;
                                bhvm_shape_s_set_data_na( &hr->s, false, 2, hb->s.data[ 0 ], ha->s.data[ 0 ] );
                            }
                        }
                        else
                        {
                            if( b_htp )
                            {
                                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mtm_s;
                                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_a_s;
                                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mtm_dp_b_s;
                                                    f =        bhvm_hop_ar2_mul_mtm_s_f;
                                bhvm_shape_s_set_data_na( &hr->s, false, 2, hb->s.data[ 1 ], ha->s.data[ 1 ] );
                            }
                            else
                            {
                                result->type_vop_ap   = TYPEOF_bhvm_vop_ar2_mul_mmm_s;
                                result->type_vop_dp_a = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_a_s;
                                result->type_vop_dp_b = TYPEOF_bhvm_vop_ar2_mul_mmm_dp_b_s;
                                                    f =        bhvm_hop_ar2_mul_mmm_s_f;
                                bhvm_shape_s_set_data_na( &hr->s, false, 2, hb->s.data[ 0 ], ha->s.data[ 1 ] );
                            }
                        }
                    }
                    else
                    {
                        return false;
                    }
                }

                if( ( ha->v.size > 0 ) && ( hb->v.size > 0 ) )
                {
                    bhvm_holor_s_fit_size( hr );
                    f( ha, hb, hr );
                }
            }

            result->settled = ( *r && (*r)->h.v.size );
            BLM_RETURNV( bl_t, true );
        };
    };

    /// logic ------------------------------------------------------------------

    stamp :equal =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return "=="; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    stamp :larger =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return ">"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    stamp :smaller =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return "<"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    stamp :larger_equal =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return ">="; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    stamp :smaller_equal =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return "<="; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    stamp :logic_and =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return "&"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    stamp :logic_or =
    {
        func :: :priority      = { return 6; };
        func :: :symbol        = { return "|"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_$R_s; };
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };
    };

    /// special operators ------------------------------------------------------

    // r-value is (scalar) index
    stamp :index =
    {
        func :: :priority = { return 20; };
        func :: :solve = // r->v_data will be weak
        {
            if( a[0] && a[0]->m.htp ) return false;
            lion_holor_s_attach( r, a[0] && a[1] ? lion_holor_s_create() : NULL );
            if( *r )
            {
                bhvm_holor_s* ha = &a[0]->h;
                bhvm_holor_s* hb = &a[1]->h;
                bhvm_holor_s* hr = &(*r)->h;
                if( hb->v.size != 1 ) return false;
                sz_t index = bhvm_holor_s_f3_get_scalar( hb );
                if( ha->s.size == 0 ) return false;
                if( index < 0 || index >= ha->s.data[ ha->s.size - 1 ] ) return false;
                bhvm_holor_s_clear( hr );
                bhvm_shape_s_set_data( &hr->s, ha->s.data, ha->s.size - 1 );
                if( ha->v.size ) bhvm_value_s_init_weak_from_value( &hr->v, &ha->v );
            }
            result->settled = ( *r && (*r)->h.v.size );
            result->codable = false;
            return true;
        };
    };

    // l-value is (scalar) increment
    stamp :inc_order =
    {
        func :: :priority = { return 20; };
        func :: :solve =
        {
            lion_holor_s_attach( r, a[0] && a[1] ? lion_holor_s_create() : NULL );
            if( *r )
            {
                bhvm_holor_s* ha = &a[0]->h;
                bhvm_holor_s* hb = &a[1]->h;
                bhvm_holor_s* hr = &(*r)->h;
                if( ha->v.size != 1 ) return false;
                sz_t dim = bhvm_holor_s_f3_get_scalar( ha );
                if( dim <= 0 ) return false;
                bhvm_holor_s_copy( hr, hb );
                bhvm_holor_s_inc_order( hr, dim );
            }
            result->settled = ( *r && (*r)->h.v.size );
            result->codable = false;
            return true;
        };
    };

    // concatenates two holors according to cat-rule defined in bhvm_holor_s_cat_set
    stamp :cat =
    {
        func :: :priority = { return 6; };
        func :: :solve =
        {
            lion_holor_s_attach( r, a[0] && a[1] ? lion_holor_s_create() : NULL );
            if( *r )
            {
                bhvm_holor_s* ha = &a[0]->h;
                bhvm_holor_s* hb = &a[1]->h;
                bhvm_holor_s* hr = &(*r)->h;
                if( !bhvm_holor_s_can_cat( ha, hb ) ) return false;
                bhvm_holor_s_cat_set( ha, hb, hr );
            }
            result->settled = ( *r && (*r)->h.v.size );
            result->codable = false;
            return true;
        };
    };

    // first argument is initialization, second is normal input
    stamp :recurrent =
    {
        tp_t name;

        func :: :priority = { return 8; };
        func :: :requires_solve_for_each_channel = { return true; };

        func :: :solve =
        {
            if( a[0] )
            {
                lion_holor_s_attach( r, lion_holor_s_create() );
                bhvm_holor_s* ha = &a[0]->h;
                bhvm_holor_s* hr = &(*r)->h;
                bhvm_shape_s_copy( &hr->s, &ha->s );
                if( a[1] )
                {
                    bhvm_holor_s* hb = &a[1]->h;
                    if( !bhvm_shape_s_is_equal( &ha->s, &hb->s ) ) return false;
                    result->settled = ha->v.size > 0 && hb->v.size > 0;
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
                lion_holor_s_attach( r, NULL );
                result->settled = false;
                return true;
            }
        };

        // TODO: implement dendrite pass
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return 0; };

        func :: :mcode_push_ap =
        {
            bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_setup_ap, bhvm_vop_t_create( TYPEOF_bhvm_vop_ar1_cpy_ay_s ), arr_ci );
            bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap,       bhvm_vop_t_create( TYPEOF_bhvm_vop_ar1_cpy_by_s ), arr_ci );
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group :ar3 = retrievable
{
    extending stump verbatim :_ = aware :
    {
        func :: :arity = { return 3; };
    };

    // arg[0] scalar condition, arg[1] ( cond > 0 ), arg[2] ( cond <= 0 )
    stamp :branch =
    {
        func :: :priority = { return  5; };
        func :: :solve =
        {
            if( a[0] )
            {
                bhvm_holor_s* ha = &a[0]->h;
                if( ha->v.size != 1 ) return false;
                f3_t cond = bhvm_holor_s_f3_get_scalar( ha );
                if( cond > 0 )
                {
                    lion_holor_s_attach( r, bcore_fork( a[1] ) );
                }
                else
                {
                    lion_holor_s_attach( r, bcore_fork( a[2] ) );
                }
            }
            result->settled = ( *r && (*r)->h.v.size );
            result->codable = false;
            return true;
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// evaluation
group :eval =
{
    feature 'a' void run( const );
    stamp :ar2 = aware :
    {
        lion_holor_s => ha;
        lion_holor_s => hb;
        lion_holor_s => hr;
        aware ::ar2  => nop;
        func : :run;
        func bcore_main :main = { @_run( o ); return 0; };
    };
};

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_nop

/**********************************************************************************************************************/

vd_t lion_nop_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_NOP_H
