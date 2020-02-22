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
#include "lion_root.h"
#include "lion_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_nop

BCORE_FORWARD_OBJECT( lion_nop_context_s );

/// returns global context
lion_nop_context_s* lion_nop_get_context( void );

PLANT_GROUP( lion_nop, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// tracks
name track_ap;
name track_dp;
name track_setup_ap;
name track_setup_dp;
name track_shelve_ap;
name track_shelve_dp;
name track_reset_dp; // zeros gradients on adaptive nodes

feature 'a' sz_t arity( const ) = { ERR_fa( "Not implemented in '#<sc_t>'.", ifnameof( o->_ ) ); return -1; };
feature 'a' sz_t priority( const ) = { return 10; };
feature 'a' sc_t symbol( const )   = { return NULL; };

/// converts an operator into a correspondent operator of arity n if possible; return NULL if conversion is not supported
feature 'a' :* create_op_of_arn( const, sz_t n ) = { return ( :a_arity( o ) == n ) ? :a_clone( o ) : NULL; };

/** Solve computes the result 'r' from an array of arguments 'a'.
  * 'a' represents an array of pointers. The array size is equal to arity.
  * Solve can produce three valid states:
  *   Detached (NULL): E.g. when arguments do not supply sufficient information (e.g. due to insufficient connectivity)
  *   Vacant (dimensions are fully determined)
  *   Determined - This represents a holor computed from literals and can itself be treated as literal.
  *
  *   Settled:
  *     The result is considered settled when the top-spanning graph of the result is not relevant for
  *     the virtual machine. This is generally (not always) the case when the result is not active (e.g. a constant).
  *     If the result is settled, the top-spanning graph is removed, which turn the node into and arity-0 node.
  *     The feature 'settle' is triggered, which switches the operator to an arity0 operator. By default this is a literal.
  */

stamp :solve_result = aware bcore_inst
{
    /// result holor
    lion_holor_s => h;

    /// optional message in case of failure
    st_s => msg;

    /// Output is settled: Triggers operator settling and removes top-spanning graph.
    bl_t settled = false;

    /// Non-codabe operators should not enter code generation.
    bl_t codable = true;

    /// If settled 'reducible' allows subsequent graph to be disconnected (solution needs not retain a reference to this node)
    bl_t reducible = true;

    /// preferred axon-pass vop type (0: not set)
    tp_t type_vop_ap;

    /// preferred dendrite-pass vop type for channels a...c (0: not set or inert dendrite pass)
    tp_t type_vop_dp_a;
    tp_t type_vop_dp_b;
    tp_t type_vop_dp_c;

    /// attachment (only used by specific operators)
    aware => attached;
};

/// returns true when the operator supports 'elementary cyclic indexing'
feature 'a' bl_t eci( const ) = { return false; };

/** Returns 'true' in case of success, otherwise check result->msg
  * The default implementation solves all elementary operators
  */
feature 'a' bl_t solve( const, lion_holor_s** a, :solve_result_s* result ) = solve__;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Indicates a cyclic operator (e.g. recurrent)
 *
 *  Normally, the node solver calls nop_solve and associates resulting holor
 *  after all arguments have been obtained.
 *
 *  Cyclic operators need to provide an output before all arguments have been evaluated.
 *  Therefore nop_solve is called once for each channel and mcode_push_ap_holor before
 *  processing all channels.
 *
 **/
feature 'a' bl_t cyclic( const ) = { return false; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/** Settles operator. (Creates an arity-0 operator)
 *  Default implementation turns it into a literal.
 **/
feature 'a' void settle( const, const :solve_result_s* result, :** out_nop, :solve_result_s** out_result ) =
{
    :ar0_literal_s* literal = :ar0_literal_s_create();
    literal->h = lion_holor_s_clone( result->h );
    :solve_result_s* r = :solve_result_s_create();
    r->h = bcore_fork( literal->h );
    :solve_result_s_attach( out_result, r );
    :a_attach( out_nop, (:*)literal );
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// preferred vop type (optional, when the type does not depend on holor parameters)
feature 'a' tp_t type_vop_ap( const );
feature 'a' tp_t type_vop_dp_a( const );
feature 'a' tp_t type_vop_dp_b( const );
feature 'a' tp_t type_vop_dp_c( const );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// axon pass (output) holor + initialization code
feature 'a' sz_t mcode_push_ap_holor( const, const :solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) =
{
    bhvm_holor_s* h = &result->h->h;
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
    if( m->active )
    {
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_ap,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
        bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_ap, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
    }
    return idx;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// dendrite pass (input) gradient holor + initialization code
feature 'a' sz_t mcode_push_dp_holor( const, const :solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) =
{
    BLM_INIT();

    bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
    lion_hmeta_s* m = &result->h->m;
    sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );

    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_dp,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_dp,        bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ),       0, idx ) );
    bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_dp, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );

    BLM_RETURNV( sz_t, idx );
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' void mcode_push_ap_track( const, const :solve_result_s* result, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) =
{
    tp_t type = ( :a_defines_type_vop_ap( o ) ) ? :a_type_vop_ap( o ) : result->type_vop_ap;
    if( type ) bhvm_mcode_frame_s_track_vop_set_args_push_d( mcf, TYPEOF_track_ap, bhvm_vop_t_create( type ), arr_ci );
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' void mcode_push_dp_track( const, const :solve_result_s* result, u0_t ch_id, const bhvm_vop_arr_ci_s* arr_ci, bhvm_mcode_frame_s* mcf ) =
{
    if( ch_id >= :a_arity( o ) + 'a' ) ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
    tp_t type = 0;
    switch( ch_id )
    {
        case 'a': type = ( :a_defines_type_vop_dp_a( o ) ) ? :a_type_vop_dp_a( o ) : result->type_vop_dp_a; break;
        case 'b': type = ( :a_defines_type_vop_dp_b( o ) ) ? :a_type_vop_dp_b( o ) : result->type_vop_dp_b; break;
        case 'c': type = ( :a_defines_type_vop_dp_c( o ) ) ? :a_type_vop_dp_c( o ) : result->type_vop_dp_c; break;
        default: ERR_fa( "Invalid channel id '#<char>'", ( char )ch_id );
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

    func bcore_inst_call : init_x = { o->randomizer_mutex = bcore_mutex_s_create(); };
    func bcore_inst_call : down_e = { bcore_mutex_s_discard( o->randomizer_mutex ); };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

group :ar0 = retrievable
{
    extending stump verbatim :_ = aware :
    {
        func :: :arity = { return 0; };
    };

    stamp :literal =
    {
        lion_holor_s -> h;
        func :: :solve =
        {
            lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
            result->settled = true;
            return true;
        };
    };

    /// parameter/variable (does not settle); used for cell-frame input and system accessible parameters
    stamp :param =
    {
        lion_holor_s -> h;
        func :: :solve =
        {
            lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
            result->settled = false;
            return true;
        };
    };

    /// nullary adaptive operator
    stamp :adaptive =
    {
        lion_holor_s -> h;
        func :: :solve =
        {
            lion_holor_s_attach( &result->h, bcore_fork( o->h ) );
            result->h->m.adaptive = true;
            result->settled = false;
            return true;
        };

        func :: :mcode_push_ap_holor =
        {
            bhvm_holor_s* h = &result->h->h;
            lion_hmeta_s* m = &result->h->m;
            sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );
            if( result->h->h.v.size == 0 ) // randomize holor if result is vacant
            {
                bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_ap,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
                bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_ap,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_randomize_s_create() ), 0, idx ) );
                bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_ap, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
            }
            return idx;
        };

        func :: :mcode_push_dp_holor =
        {
//            sz_t idx = ::mcode_push_dp_holor__( ( lion_nop* )o, result, arr_ci, mcf );
//            bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_reset_dp, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ), 0, idx ) );
//            return idx;

            BLM_INIT();
            bhvm_holor_s* h = BLM_CREATEC( bhvm_holor_s, copy_shape_type, &result->h->h );
            lion_hmeta_s* m = &result->h->m;
            sz_t idx = bhvm_mcode_frame_s_push_hm( mcf, h, ( bhvm_mcode_hmeta* )m );

            bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_setup_dp,  bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_determine_s_create() ), 0, idx ) );
            bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_shelve_dp, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_vacate_s_create() ),    0, idx ) );
            bhvm_mcode_frame_s_track_vop_push_d( mcf, TYPEOF_track_reset_dp, bhvm_vop_a_set_index( ( ( bhvm_vop* )bhvm_vop_ar0_zro_s_create() ), 0, idx ) );
            BLM_RETURNV( sz_t, idx );
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
            lion_holor_s_attach( &result->h, bcore_fork( a[0] ) );
            result->settled = (result->h) && !result->h->m.active;
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_identity_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_identity_dp_s;
            return true;
        };
    };

    stamp :f3 =
    {
        func :: :priority = { return 8; };
        func :: :symbol   = { return "f3_t"; };
        func :: :solve =
        {
            lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
            bhvm_holor_s_set_type( &result->h->h, TYPEOF_f3_t );
            result->settled = ( result->h ) && !result->h->m.active;
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_identity_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_identity_dp_s;
            return true;
        };
    };

    stamp :f2 =
    {
        func :: :priority = { return 8; };
        func :: :symbol   = { return "f2_t"; };
        func :: :solve =
        {
            lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
            bhvm_holor_s_set_type( &result->h->h, TYPEOF_f2_t );
            result->settled = ( result->h ) && !result->h->m.active;
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

    stamp :abs =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "abs"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_abs_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_abs_dp_s; };
    };

    stamp :exp =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "exp"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_exp_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_exp_dp_s; };
    };

    stamp :log =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "log"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_log_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_log_dp_s; };
    };

    stamp :inv =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "inv"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_inv_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_inv_dp_s; };
    };

    stamp :sqr =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "sqr"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_sqr_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_sqr_dp_s; };
    };

    stamp :srt =
    {
        func :: :priority      = { return 8; };
        func :: :symbol        = { return "srt"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar1_srt_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_srt_dp_s; };
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
            lion_holor_s_attach( &result->h, bcore_fork( a[0] ) );
            result->settled = (result->h) && !result->h->m.active;
            result->type_vop_ap   = TYPEOF_bhvm_vop_ar1_identity_s;
            result->type_vop_dp_a = TYPEOF_bhvm_vop_ar1_identity_dp_s;
            return true;
        };
        func :: :mcode_push_dp_holor;
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
            lion_holor_s_attach( &result->h, bcore_fork( a[0] ) );
            if( result->h ) result->h->m.active = true;
            result->settled = ( result->h != NULL );
            result->reducible = false; // keep subsequent graph intact
            result->codable = false;
            return true;
        };

        func :: :settle =
        {
            ::ar0_adaptive_s* adaptive = ::ar0_adaptive_s_create();
            adaptive->h = lion_holor_s_clone( result->h );
            adaptive->h->m.name = o->name;
            ::solve_result_s* r = ::solve_result_s_create();
            r->h = bcore_fork( adaptive->h );
            ::solve_result_s_attach( out_result, r );
            ::a_attach( out_nop, (::*)adaptive );
        };

    };

    /// special operators ------------------------------------------------------

    /// returns leading dimension
    stamp :dimof =
    {
        func :: :symbol   = { return "dimof"; };
        func :: :priority = { return 8; };
        func :: :solve  =
        {
            if( a[0] )
            {
                lion_holor_s_attach( &result->h, lion_holor_s_create() );
                bhvm_holor_s_set_scalar_f3( &result->h->h, a[0]->h.s.size ? a[0]->h.s.data[ a[0]->h.s.size - 1 ] : 1 );
                result->h->m.active = false;
            }
            result->settled = result->h != NULL;
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
            if( a[0] )
            {
                lion_holor_s_attach( &result->h, lion_holor_s_clone( a[0] ) );
                ::context_s* context = ::get_context();
                ASSERT( context->randomizer_is_locked );
                if( context->randomizer_rval == 0 ) context->randomizer_rval = o->rseed;
                if( !result->h->h.v.size ) bhvm_holor_s_fit_size( &result->h->h );
                bhvm_value_s_set_random( &result->h->h.v, 1.0, -0.5, 0.5, &context->randomizer_rval );
                result->h->m.active = false;
                result->settled = true;
            }
            result->codable = false;
            return true;
        };
    };

    stamp :cast_htp =
    {
        func :: :priority  = { return 12; };
        func :: :solve;
        func :: :mcode_push_ap_holor;
        func :: :mcode_push_dp_holor;
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
        func :: :eci           = { return true; };
        func :: :symbol        = { return "+"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_add_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar1_add_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar1_add_dp_b_s; };
    };

    stamp :sub =
    {
        func :: :priority      = { return 8; };
        func :: :eci           = { return true; };
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

    stamp :mul =
    {
        func :: :priority      = { return 10; };
        func :: :eci           = { return true; };
        func :: :symbol        = { return "*"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_mul_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_mul_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar2_mul_dp_b_s; };
    };

    stamp :div =
    {
        func :: :priority      = { return 10; };
        func :: :eci           = { return true; };
        func :: :symbol        = { return "/"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_div_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar2_div_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar3_div_dp_b_s; };
    };

    stamp :pow =
    {
        func :: :priority      = { return 12; };
        func :: :eci           = { return true; };
        func :: :symbol        = { return "^"; };
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_pow_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar3_pow_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar3_pow_dp_b_s; };
    };

    stamp :bmul =
    {
        func :: :priority = { return 10; };
        func :: :symbol   = { return "**"; };
        func :: :solve;
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

    // constructive concatenation defined in bhvm_holor_s_cat_set
    stamp :cat =
    {
        func :: :priority = { return 6; };
        func :: :symbol   = { return ":"; };
        func :: :solve;
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_cat_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar1_cat_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar1_cat_dp_b_s; };
    };

    // conservative concatenation defined in bhvm_holor_s_ccat_set
    stamp :ccat =
    {
        func :: :priority = { return 8; };
        func :: :symbol   = { return "::"; };
        func :: :solve;
        func :: :type_vop_ap   = { return TYPEOF_bhvm_vop_ar2_ccat_s; };
        func :: :type_vop_dp_a = { return TYPEOF_bhvm_vop_ar1_ccat_dp_a_s; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar1_ccat_dp_b_s; };
    };

    stamp :order_inc =
    {
        func :: :priority = { return 21; };
        func :: :symbol   = { return "["; };
        func :: :solve;
        func :: :mcode_push_ap_track;
        func :: :type_vop_dp_a = { return 0; };
        func :: :type_vop_dp_b = { return TYPEOF_bhvm_vop_ar1_add_dp_b_s; };
    };

    // r-value is (scalar) index
    stamp :order_dec =
    {
        func :: :priority = { return 20; };
        func :: :symbol   = { return "]"; };
        func :: :solve;
        func :: :mcode_push_ap_holor;
        func :: :mcode_push_dp_holor;
    };

    // first argument is initialization, second is normal input
    stamp :recurrent =
    {
        tp_t name;

        func :: :priority = { return 8; };
        func :: :cyclic = { return true; };
        func :: :solve;
        func :: :mcode_push_ap_track;
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
        func :: :priority = { return 4; };
        func :: :solve;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_nop

/**********************************************************************************************************************/

vd_t lion_nop_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_NOP_H
