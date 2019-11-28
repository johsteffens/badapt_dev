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

/** haptive-graph
    MLP

    cell layer( y => hidden_nodes, a )
    {
        w = adaptive : random : ( [ hidden_nodes ][ dimof( a ) ]# );
        b = adaptive : ( [ hidden_nodes ]0 );
        y = b + w ** a;
    };

    cell mlp( y => a )
    {
        l1 = layer( 10, a );
        l2 = layer( 20, relu( a ) );
        l3 = layer(  1, relu( a ) );
        y = tanh( l3.y );
    };

    ========================================
    LSTM

    cell layer( co, ho => dim_h, x, ci, hi )
    {
        // adaptive holors
        w_fx = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_fh = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_ix = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_ih = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_ox = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_oh = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_qx = adaptive : random( [ dim_h ][ dimof( x ) ]# );
        w_qh = adaptive : random( [ dim_h ][ dimof( x ) ]# );

        b_f = adaptive( [ dim_h ]0 );
        b_i = adaptive( [ dim_h ]0 );
        b_o = adaptive( [ dim_h ]0 );
        b_q = adaptive( [ dim_h ]0 );

        v_f = lgst( ( w_fx ** x ) + ( w_fh ** hi ) + b_f );
        v_i = lgst( ( w_ix ** x ) + ( w_ih ** hi ) + b_i );
        v_o = lgst( ( w_ox ** x ) + ( w_oh ** hi ) + b_o );
        v_q = tanh( ( w_qx ** x ) + ( w_qh ** hi ) + b_q );

        co  = ( v_f * ci ) + ( v_i * v_q );
        v_d = tanh( co );
        ho  = ( v_o * v_d );
    };

    cell lstm( y => dim_h, x )
    {
        adaptive w_r = random( [ dim_h ][ dimof( x ) ]# );
        adaptive b_r = [ dim_h ]#;

        recurrent c = [ dim_h ]0;
        recurrent h = [ dim_h ]0;

        l1 = layer( dim_h, x, ci = c, hi = h );

        h = l1.ho;
        c = l1.co;

        y = tanh( w_r * h + b_r );
    }

    g_out = lstm( dim_h = 200, x = g_in ).y;

    - parse into cell
    - cell: tree of cell
    - cell: inputs, outputs, body
    - definition: stand-alone node with identifier
    - operation: cell embedded in a cell
    - once a cell is complete, data types can be finalized

TODO:
   - (done) allow explicit output channel selection only on cells with no free input channels
   - virtual machine: overhaul differentiating between micro- and macrocode
   -                  add macro operations operating on the frame
   -                  add macro operations controlling program flow
   - recurrent: implement unrolled inference and bp_grad
   - allow elementwise operators mix with scalars (like mul)
   - look for generally accepted offline problems for neural networks
   - parameterize adaptive (e.g. adaptive( min, max, additional cost ))
   - index operator should be a cast-operator
   - add a cost operator or cost expression to generate specific costs like weight energy (producing weight decay)
*/

/**
 *  Symbolic language to describe a graph of operators on holors.
 *
 *  Semantic Cell Concept:
 *  A semantic graph communicates with the objects outside its body through input an output channels.
 *  All links of a graph 'x' to outside objects the node must pass though an input channel of 'x'.
 *  Inside objects may not be referenced directly by outside objects.
 *  A graph adhering to this concept is called 'cell'
 *  A construction of a new graph must conclude with converting it to a cell.
 *  Cells can be used as objects for constructing new graphs.
 *
 *  Static Links:
 *  Defined links of an input channel of a semantic graph are never changed or freed again.
 *  Different use cases of a graph are achieved by creating graph-copies and assigning links of those copies differently.
 *
 *  Binary operators:
 *  Binary operators have a priority-level. Higher priority is resolved before lower priority.
 *
 *  Available binary operators
 *  Symbol  Notation Priority  Type
 *   +      Infix    8     (elementwise) addition
 *   -      Infix    8     (elementwise) subtraction
 *   *      Infix    9     (elementwise) multiplication (hadamard product); multiplication of holor with scalar
 *  **,     Infix    9     holor-product for holors up to order 2; transposition state is considered
 *  ***     Infix    9     convolution?
 *
 *  Unary operators
 *   -          8     negates holor
 *  ^t,        10     toggles transposition state (represents a reinterpret cast) (priority must be above multiplication)
 *
 *  Possible name ?
 *     haptive (synonym to haptic) (no trademark (!) )
 *     holocell
 *     holorcell  (unused)
 *     holorframe (unused, term does not yet exist)
 *     holograph
 *     holorgraph
 *     holornova  (unused)
 *     helix   (mathematics, biology, earring, IT corporation)
 *     haptor  (biology: flatworm organ)
 *     hoptinet
 *     hoptivnet (unused)
 *     haptivnet (unused)
 *     adahonet  (unused)
 *     haptivscript (unused)
 *     haptivdown   // wordplay on markdown
 *
 *
 *  Dendpass-Algorithm:
 *  specific method to compute the local gradient via automatic differentiation
 *  using reverse accumulation to backpropagate gradients:
 *  - Each node holds a gradient holor of same shape as its output holor
 *  - The gradient holor represents the gradient with respect to the last input given the current state of the network.
 *  - The backpass algorithm for a specific node computes the gradient through a specific node-channel and adds it to (accumulates)
 *    the gradient of the node linked to the input channel. This step is done by s singe virtual operation.
 *  - The backpass procedure is compiled by recursively passing each node starting from the adaptive node downward through
 *    all downlinks.
 */

/**********************************************************************************************************************/

#ifndef HAPTIVE_GRAPH_H
#define HAPTIVE_GRAPH_H

#include "bmath_std.h"
#include "bhvm_std.h"
#include "badapt_std.h"

#include "haptive_planted.h"

/// In case unstable behavior is observed, try debugging by reducing optimization level.
#define HAPTIVE_GRAPH_OPTIMIZATION_LEVEL 1

/**********************************************************************************************************************/
/// prototypes

BCORE_FORWARD_OBJECT( haptive_context_s );

s2_t haptive_op_ar1_solve_unary( bhvm_hf3_s** r, bhvm_hf3_s** a, bmath_fp_f3_ar1 unary );

/// returns global context
haptive_context_s* haptive_get_context();

/**********************************************************************************************************************/

#ifdef TYPEOF_haptive
PLANT_GROUP( haptive, bcore_inst )
#ifdef PLANT_SECTION

// language control types
name cell;
name if;
name then;
name else;

/// operator class
name op_class_regular;

// A cast operator sets up a static relationship between the axon and dendrites (e.g. by referencing)
// It does not perform effective operations at runtime and can therefore be executed just once during setup.
// Its dendrite pass operators are also cast operators. These modify the axon gradient.
name op_class_cast;

// microcode names
name mcode_name_infer;
name mcode_name_bp_grad;
name mcode_name_setup;
name mcode_name_shelve;
name mcode_name_zero_adaptive_grad;

// subroutines copied to setup
name mcode_name_cast;          // contains cast operations to be copied to setup
name mcode_name_cast_reverse;  // contains cast operations to be copied to setup in reverse order
name mcode_name_ap_init;       // contains ap_init operations

// holor types
name holor_type_data;          // any type of data holder
name holor_type_depletable;    // holor can be set to vacant before shelving
name holor_type_adaptive;      // holor is adaptive
name holor_type_adaptive_grad; // holor represents the gradient of an adaptive holor
name holor_type_cast;          // holor is the result of a cast (such holors are setup by a cast operator and clear()-ed for shelving)

// basic signatures
signature sz_t get_sz( const );
signature sc_t get_sc( const );
signature tp_t get_tp( const );

/// operator group
group :op =
{
    feature strict 'a' ::get_sz get_arity;
    feature        'a' ::get_tp get_class    = { return TYPEOF_op_class_regular; };
    feature        'a' ::get_sz get_priority = { return 10; };
    feature        'a' ::get_sc get_symbol   = { return NULL; };

    /// converts an operator into a correspondent operator of arity n if possible; return NULL if conversion is not supported
    feature        'a' :* create_op_of_arn( const, sz_t n ) = { return ( :a_get_arity( o ) == n ) ? :a_clone( o ) : NULL; };

    /// signature prototype for axon-pass and dendrite-pass functions
    signature bhvm_hf3_vm_op* create_vm_op_pass( const, const bhvm_hf3_vm_frame_s* vmf, sc_t arr_sig, const bcore_arr_sz_s* arr_idx );

    /** Solve computes the result 'r' from an array of arguments 'a'.
      * 'a' represents an array of pointers. The array size is equal to arity.
      * Solve can produce three valid states:
      *   Detached (NULL): E.g. when arguments do not supply sufficient information (e.g. due to insufficient connectivity)
      *   Vacant (dimensions are fully determined)
      *   Determined - This represents a holor computed from literals and can itself be treated as literal.
      *
      *   Settled: The result is considered settled when the input was sufficient specific for computing a vm-operation
      *
      * Return:
      *   0: A valid result could be computed
      *   1: Output is settled. Triggers to finalize and discard graph spanned by operation.
      *   2: Situation of 1, additionally sets node-holor vacant (forces subsequent graph to remain intact).
      *      E.g. This is required for adaptive operands, which stay in the graph even though they might
      *           have a literal state at compile time.
      *
      *   Negative values indicate errors
      *   -1: Incorrect operands for the given operation (this triggers a syntax error by the parser)
      *       if( msg ) function can push a specific error text.
      */
    feature 'a' s2_t solve( const, bhvm_hf3_s** r, bhvm_hf3_s** a, st_s* msg );


    /** Normally the node solver calls above solve after all arguments have been obtained.
     *  Certain (potentially cyclic) operators require a solve for each input channel.
     **/
    feature 'a' bl_t solve_each_channel( const ) = { return false; };

    feature 'a' ::op* create_final( const, bhvm_hf3_s* h ) =
    {
        :ar0_literal_s* final = :ar0_literal_s_create();
        final->h = bhvm_hf3_s_clone( h );
        return (::op*)final;
    };

    /// virtual machine operation for forward initialization (towards axon).
    feature 'a' :create_vm_op_pass create_vm_op_ap_init         = { return NULL; };
    feature 'a' :create_vm_op_pass create_vm_op_ap_init_set_idx =
    {
        bhvm_hf3_vm_op* op = :a_create_vm_op_ap_init( o, vmf, arr_sig, arr_idx );
        if( op ) bhvm_hf3_vm_op_set_args( op, arr_sig, arr_idx );
        return op;
    };

    /// virtual machine operation for forward processing (towards axon).
    feature 'a' :create_vm_op_pass create_vm_op_ap         = { return NULL; };
    feature 'a' :create_vm_op_pass create_vm_op_ap_set_idx =
    {
        bhvm_hf3_vm_op* op = :a_create_vm_op_ap( o, vmf, arr_sig, arr_idx );
        if( op ) bhvm_hf3_vm_op_set_args( op, arr_sig, arr_idx );
        return op;
    };

    /// virtual machine operation backward gradient propagation (towards dendrite). (n = arity)
    feature 'a' :create_vm_op_pass create_vm_op_dp        ( char ch_id ) = { return NULL; };
    feature 'a' :create_vm_op_pass create_vm_op_dp_set_idx( char ch_id ) =
    {
        bhvm_hf3_vm_op* op = :a_create_vm_op_dp( o, vmf, arr_sig, arr_idx, ch_id );
        if( op ) bhvm_hf3_vm_op_set_args( op, arr_sig, arr_idx );
        return op;
    };

    /// nullary operator (arity 0)
    group :ar0 =
    {
        func :: :get_arity = { return 0; };

        stamp :literal = aware :
        {
            bhvm_hf3_s -> h;
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, bcore_fork( o->h ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

        };

        /// formal input (used for resolving the network; not part of syntax)
        stamp :input = aware :
        {
            bhvm_hf3_s -> h;
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, bcore_fork( o->h ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        /// nullary adaptive operator
        stamp :adaptive = aware :
        {
            bhvm_hf3_s -> h;
            tp_t name;

            func :: :solve =
            {
                if( o->h )
                {
                    bhvm_hf3_s_attach( r, bhvm_hf3_s_create() );
                    bhvm_hf3_s_copy_shape( *r, o->h );
                }
                else
                {
                    bhvm_hf3_s_detach( r );
                }

                return 0; // no need to settle
            };
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// unary operator (arity 1)
    group :ar1 = retrievable
    {
        func :: :get_arity        = { return 1; };

        /// ==== using unary functions =====

        stamp :identity = aware :
        {
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
            func :: :create_vm_op_ap =  { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_cpy_s_create(); };
        };

        stamp :neg = aware :
        {
            func :: :get_symbol       = { return "neg"; };
            func :: :get_priority     = { return 8; };
            func :: :solve            = { return :solve_unary( r, a, bmath_f3_op_ar1_neg_s_fx ); };
            func :: :create_vm_op_ap  = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_neg_s_create(); };
            func :: :create_vm_op_dp  = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_neg_s_create(); };
            func :: :create_op_of_arn =
            {
                return ( n == 2 ) ? (::*)::ar2_sub_s_create()
                     : ( n == 1 ) ? (::*)@clone( o )
                     : NULL;
            };
        };

        stamp :floor = aware :
        {
            func :: :get_symbol      = { return "floor"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_floor_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_floor_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar0_dp_ca_floor_s_create(); };
        };

        stamp :ceil = aware :
        {
            func :: :get_symbol      = { return "ceil"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_ceil_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_ceil_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar0_dp_ca_ceil_s_create(); };
        };

        stamp :exp = aware :
        {
            func :: :get_symbol      = { return "exp"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_exp_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_exp_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_exp_s_create(); };
        };

        /// ===== logistic =====

        stamp :lgst = aware :
        {
            func :: :get_symbol      = { return "lgst"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_lgst_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_lgst_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_lgst_s_create(); };
        };

        stamp :lgst_hard = aware :
        {
            func :: :get_symbol      = { return "lgst_hard"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_lgst_hard_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_lgst_hard_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_lgst_hard_s_create(); };
        };

        stamp :lgst_leaky = aware :
        {
            func :: :get_symbol      = { return "lgst_leaky"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_lgst_leaky_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_lgst_leaky_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_lgst_leaky_s_create(); };
        };

        /// ===== tanh =====

        stamp :tanh = aware :
        {
            func :: :get_symbol      = { return "tanh"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_tanh_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_tanh_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_tanh_s_create(); };
        };

        stamp :tanh_hard = aware :
        {
            func :: :get_symbol      = { return "tanh_hard"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_tanh_hard_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_tanh_hard_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_tanh_hard_s_create(); };
        };

        stamp :tanh_leaky = aware :
        {
            func :: :get_symbol      = { return "tanh_leaky"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_tanh_leaky_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_tanh_leaky_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_tanh_leaky_s_create(); };
        };

        /// ===== softplus =====

        stamp :softplus = aware :
        {
            func :: :get_symbol      = { return "softplus"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_softplus_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_softplus_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_softplus_s_create(); };
        };

        stamp :relu = aware :
        {
            func :: :get_symbol      = { return "relu"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_relu_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_relu_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_relu_s_create(); };
        };

        stamp :relu_leaky = aware :
        {
            func :: :get_symbol      = { return "relu_leaky"; };
            func :: :get_priority    = { return 8; };
            func :: :solve           = { return :solve_unary( r, a, bmath_f3_op_ar1_relu_leaky_s_fx ); };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_relu_leaky_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_relu_leaky_s_create(); };
        };

        stamp :htp = aware :
        {
            func :: :get_class       = { return TYPEOF_op_class_cast; };
            func :: :get_priority    = { return 8; };
            func :: :solve =
            {
                if( a[0] )
                {
                    #if ( HAPTIVE_GRAPH_OPTIMIZATION_LEVEL >= 1 )
                        // TODO: Watch this solution's stability.
                        bhvm_hf3_s_attach( r, bhvm_hf3_s_create() );
                        **r = bhvm_hf3_init_fork( a[0]->d_data, a[0]->d_size, a[0]->d_space, a[0]->v_data, a[0]->v_size, a[0]->v_space, !a[0]->htp );
                    #else
                        bhvm_hf3_s_attach( r, bhvm_hf3_s_clone( a[0] ) );
                        (*r)->htp = !(*r)->htp;
                    #endif
                }
                else
                {
                    bhvm_hf3_s_attach( r, NULL );
                }

                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cast_htp_s_create(); };
            func :: :create_vm_op_dp = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_cast_htp_s_create(); };
        };


        /// ===== other ... =====

        /// formal output (used for resolving the network; not part of syntax)
        stamp :output = aware :
        {
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
            func :: :create_vm_op_ap  = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_s_create(); };
            func :: :create_vm_op_dp  = { ASSERT( ch_id == 'a' ); return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_cpy_s_create(); };
        };

        /** marks a holor or expression to be adaptive
         *  Operation is settled when at least a vacant holor can be computed.
         *  If the holor is vacant, it is initialized in the virtual machine.
         */
        stamp :adaptive = aware :
        {
            tp_t name;

            func :: :get_symbol   = { return "adaptive"; };
            func :: :get_priority = { return 8; };

            func :: :solve =
            {
                bhvm_hf3_s_attach( r, bcore_fork( a[0] ) );
                return ( *r ) ? 2 : 0; // settle with value 2 to keep subsequent graph intact
            };

            func :: :create_final =
            {
                ::ar0_adaptive_s* final = ::ar0_adaptive_s_create();
                final->h    = bhvm_hf3_s_clone( h );
                final->name = o->name;
                return (:::op*)final;
            };
        };

        /// returns leading dimension
        stamp :dimof = aware :
        {
            func :: :get_symbol   = { return "dimof"; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bhvm_hf3_s_attach( r, a[0] ? bhvm_hf3_s_create() : NULL );
                if( a[0] )
                {
                    bhvm_hf3_s_set_scalar_f3( *r, a[0]->d_size ? a[0]->d_data[ a[0]->d_size - 1 ] : 1 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :random = aware :
        {
            u2_t rseed = 1234;
            func :: :get_symbol   = { return "random"; };
            func :: :get_priority = { return 8; };
            func :: :solve        =
            {
                bhvm_hf3_s_attach( r, a[0] ? bhvm_hf3_s_create() : NULL );
                if( a[0] )
                {
                    :::context_s* context = :::get_context();
                    ASSERT( context->randomizer_is_locked );
                    if( context->randomizer_rval == 0 )
                    {
                        context->randomizer_rval = o->rseed;
                    }
                    bhvm_hf3_s_copy( *r, a[0] );
                    if( !(*r)->v_size ) bhvm_hf3_s_fit_v_size( *r );
                    bhvm_hf3_s_set_random( *r, 1.0, -0.5, 0.5, &context->randomizer_rval );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// binary operator (arity 2)
    group :ar2 = retrievable
    {
        func :: :get_arity = { return 2; };

        stamp :bmul = aware :
        {
            func :: :get_symbol   = { return "**"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_set_shape_bmul( a[0], a[1], *r ) )
                    {
                        if( msg )
                        {
                            s2_t bhs_code = bhvm_hf3_s_bhs_code( a[0], a[1] );
                            if( !bhvm_hf3_s_bmul_bhs_code_allowed( bhs_code ) )
                            {
                                st_s_push_fa( msg, "Operation '");
                                bhvm_hf3_st_s_push_bhs_code( msg, bhs_code );
                                st_s_push_fa( msg, "' is not allowed.");
                            }
                        }
                        return -1;
                    }
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bhvm_hf3_s_fit_v_size( *r );
                        bhvm_hf3_s_bmul( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_bmul_s_create(); };
            func :: :create_vm_op_dp =
            {
                switch( ch_id )
                {
                    case 'a': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_ca_bmul_s_create();
                    case 'b': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_dp_cb_bmul_s_create();
                    default: ERR_fa( "Invalid channel id '#<char>'", ch_id ); break;
                }
                return NULL;
            };

        };

        stamp :mul = aware :
        {
            func :: :get_symbol   = { return "*"; };
            func :: :get_priority = { return 9; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->d_size == 0 )
                    {
                        bhvm_hf3_s_copy_d_data( *r, a[1] );
                        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                        {
                            bhvm_hf3_s_fit_v_size( *r );
                            bhvm_hf3_s_mul_scl( a[1], a[0]->v_data, *r );
                        }
                    }
                    else if( a[1]->d_size == 0 )
                    {
                        bhvm_hf3_s_copy_d_data( *r, a[0] );
                        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                        {
                            bhvm_hf3_s_fit_v_size( *r );
                            bhvm_hf3_s_mul_scl( a[0], a[1]->v_data, *r );
                        }
                    }
                    else
                    {
                        if( a[0]->d_size != a[1]->d_size ) return -1;
                        if( bhvm_hf3_s_d_product( a[0] ) != bhvm_hf3_s_d_product( a[1] ) ) return -1;
                        bhvm_hf3_s_copy_d_data( *r, a[0] );
                        if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                        {
                            bhvm_hf3_s_fit_v_size( *r );
                            bhvm_hf3_s_hmul( a[0], a[1], *r );
                        }
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :: :create_vm_op_ap;
            func :: :create_vm_op_dp;
        };

        stamp :add = aware :
        {
            func :: :get_symbol   = { return "+"; };
            func :: :get_priority = { return 8; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->d_size != a[1]->d_size ) return -1;
                    if( bhvm_hf3_s_d_product( a[0] ) != bhvm_hf3_s_d_product( a[1] ) ) return -1;
                    bhvm_hf3_s_copy_d_data( *r, a[0] );
                    if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                    {
                        bhvm_hf3_s_fit_v_size( *r );
                        bhvm_hf3_s_add( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_add_s_create(); };
            func :: :create_vm_op_dp =
            {
                switch( ch_id )
                {
                    case 'a': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_add_s_create();
                    case 'b': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_cb_add_s_create();
                    default: ERR_fa( "Invalid channel id '#<char>'", ch_id ); break;
                }
                return NULL;
            };
        };

        stamp :sub = aware :
        {
            func :: :get_symbol   = { return "-"; };
            func :: :get_priority = { return 8; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->d_size != a[1]->d_size ) return -1;
                    if( bhvm_hf3_s_d_product( a[0] ) != bhvm_hf3_s_d_product( a[1] ) ) return -1;
                    bhvm_hf3_s_copy_d_data( *r, a[0] );
                    if( ( a[0]->v_size > 0 ) && ( a[1]->v_size > 0 ) )
                    {
                        bhvm_hf3_s_fit_v_size( *r );
                        bhvm_hf3_s_sub( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };

            func :: :create_vm_op_ap = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar2_sub_s_create(); };
            func :: :create_vm_op_dp =
            {
                switch( ch_id )
                {
                    case 'a': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_ca_sub_s_create();
                    case 'b': return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_dp_cb_sub_s_create();
                    default: ERR_fa( "Invalid channel id '#<char>'", ch_id ); break;
                }
                return NULL;
            };

            func :: :create_op_of_arn =
            {
                return ( n == 2 ) ? (::*)@clone( o )
                     : ( n == 1 ) ? (::*)::ar1_neg_s_create()
                     : NULL;
            };
        };

        stamp :equal = aware :
        {
            func :: :get_symbol   = { return "=="; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r ) bhvm_hf3_s_set_scalar_f3( *r, bhvm_hf3_s_is_equal( a[0], a[1] ) ? 1 : 0 );
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :larger = aware :
        {
            func :: :get_symbol   = { return ">"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] > a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :smaller = aware :
        {
            func :: :get_symbol   = { return "<"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] < a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :larger_equal = aware :
        {
            func :: :get_symbol   = { return ">="; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] >= a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :smaller_equal = aware :
        {
            func :: :get_symbol   = { return "<="; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bhvm_hf3_s_set_scalar_f3( *r, a[0]->v_data[0] <= a[1]->v_data[0] ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :logic_and = aware :
        {
            func :: :get_symbol   = { return "&"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bhvm_hf3_s_set_scalar_f3( *r, ( a[0]->v_data[0] > 0 ) && ( a[1]->v_data[0] > 0 ) ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :logic_or = aware :
        {
            func :: :get_symbol   = { return "|"; };
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_is_scalar( a[0] ) || !a[0]->v_data ) return -1;
                    if( !bhvm_hf3_s_is_scalar( a[1] ) || !a[1]->v_data ) return -1;
                    bhvm_hf3_s_set_scalar_f3( *r, ( a[0]->v_data[0] > 0 ) || ( a[1]->v_data[0] > 0 ) ? 1 : 0 );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :index = aware : // r-value is (scalar) index
        {
            func :: :get_priority = { return 20; };
            func :: :solve = // r->v_data will be weak
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[1]->v_size != 1 ) return -1;
                    sz_t index = a[1]->v_data[ 0 ];
                    if( a[0]->d_size == 0 ) return -1;
                    if( index < 0 || index >= a[0]->d_data[ a[0]->d_size - 1 ] ) return -1;
                    bhvm_hf3_s_clear( *r );
                    bhvm_hf3_s_set_d_data( *r, a[0]->d_data, a[0]->d_size -1 );
                    if( a[0]->v_data )
                    {
                        (*r)->v_size = bhvm_hf3_s_d_product( *r );
                        (*r)->v_data = a[0]->v_data + index * (*r)->v_size;
                        (*r)->v_space = 0;
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :inc_order = aware : // l-value is (scalar) increment
        {
            func :: :get_priority = { return 20; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( a[0]->v_size != 1 ) return -1;
                    sz_t dim = a[0]->v_data[ 0 ];
                    if( dim <= 0 ) return -1;
                    bhvm_hf3_s_copy( *r, a[1] );
                    bhvm_hf3_s_inc_order( *r, dim );
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        stamp :cat = aware : // concatenates two holors according to cat-rule defined in bhvm_hf3_s_set_d_cat
        {
            func :: :get_priority = { return 6; };
            func :: :solve =
            {
                bhvm_hf3_s_attach( r, ( a[0] && a[1] ) ? bhvm_hf3_s_create() : NULL );
                if( *r )
                {
                    if( !bhvm_hf3_s_set_shape_cat( a[0], a[1], *r ) ) return -1;
                    if( a[0]->v_data && a[1]->v_data )
                    {
                        bhvm_hf3_s_fit_v_size( *r );
                        bhvm_hf3_s_cat( a[0], a[1], *r );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };

        /// first argument is initialization, second is normal input
        stamp :recurrent = aware :
        {
            tp_t name;

            //func :: :get_symbol   = { return "recurrent"; };
            func :: :get_priority = { return 8; };
            func :: :solve_each_channel = { return true; };

            func :: :solve =
            {
                if( a[0] )
                {
                    bhvm_hf3_s_attach( r, bhvm_hf3_s_create() );
                    bhvm_hf3_s_copy_shape( *r, a[0] );
                    if( a[1] )
                    {
                        if( !bhvm_hf3_s_shape_equal( a[0], a[1] ) ) return -1;
                        return ( a[0]->v_size > 0 && a[1]->v_size > 0 ) ? 1 : 0;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    if( a[1] ) return -1;
                    bhvm_hf3_s_attach( r, NULL );
                    return 0;
                }
            };

            // copies the l-value for initialization
            func :: :create_vm_op_ap_init = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_ay_s_create(); }; // copies a-channel for initialization
            func :: :create_vm_op_ap      = { return ( bhvm_hf3_vm_op* )bhvm_hf3_vm_op_ar1_cpy_by_s_create(); }; // copies b-channel for axon pass
        };
    };

    ///  ternary operator (arity 3)
    group :ar3 = retrievable
    {
        func :: :get_arity = { return  3; };

        stamp :branch = aware : // arg[0] scalar condition, arg[1] ( cond > 0 ), arg[2] ( cond <= 0 )
        {
            func :: :get_priority = { return  5; };
            func :: :solve =
            {
                if( a[0] )
                {
                    if( a[0]->v_size != 1 ) return -1;
                    f3_t cond = a[0]->v_data[ 0 ];
                    if( cond > 0 )
                    {
                        bhvm_hf3_s_attach( r, bcore_fork( a[1] ) );
                    }
                    else
                    {
                        bhvm_hf3_s_attach( r, bcore_fork( a[2] ) );
                    }
                }
                return ( *r && (*r)->v_size ) ? 1 : 0;
            };
        };
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// semantic group
group :sem =
{
    signature   ::get_sz get_arity;
    signature   ::get_sz get_priority;
    feature 'a' ::get_tp get_name  = { return 0; };
    body                 get_name_ = { return o->name; };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // bidirectional link
    stamp :link = aware :
    {
        tp_t name;
        private :link_s -> up;   // up link
        private :link_s -> dn;   // down link
        private  vd_t cell; // cell owning the link (only if link is part of membrane)
        bl_t     exit; // true: link is of cell's exit membrane. false: entry membrane
        func : : get_name = :get_name_;
    };

    signature   bl_t    name_exists(      const,   tp_t name );
    signature ::sem*    get_sem_by_name(  mutable, tp_t name );
    signature  :link_s* get_link_by_name( mutable, tp_t name );
    signature  :link_s* get_link_by_open( mutable );
    signature  :link_s* get_link_by_up(  mutable, :link_s* up );
    signature  :link_s* get_link_by_dn(  mutable, :link_s* dn );
    signature  sz_t     get_index_by_link( mutable, :link_s* link ); // returns -1 if not found
    signature ::get_sz  count_open;

    stamp :links = aware bcore_array
    {
        :link_s => [];

        func : :get_link_by_name =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return o->data[ i ];
            return NULL;
        };

        func : :name_exists =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->name == name ) return true;
            return false;
        };

        func : :get_link_by_up =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->up == up ) return o->data[ i ];
            return NULL;
        };

        func : :get_link_by_dn =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->dn == dn ) return o->data[ i ];
            return NULL;
        };

        func : :get_index_by_link =
        {
            BFOR_EACH( i, o ) if( o->data[ i ] == link ) return i;
            return -1;
        };

        func : :count_open =
        {
            sz_t count = 0;
            BFOR_EACH( i, o ) count += ( o->data[ i ]->up == NULL );
            return count;
        };
    };

    stamp :body = aware bcore_array
    {
        aware : => [];

        func : :name_exists =
        {
            BFOR_EACH( i, o ) if( :a_get_name( o->data[ i ] ) == name ) return true;
            return false;
        };

        func : :get_sem_by_name =
        {
            BFOR_EACH( i, o ) if( :a_get_name( o->data[ i ] ) == name ) return o->data[ i ];
            return NULL;
        };
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // cell

    signature :link_s* get_enc_by_name(  mutable, tp_t name );
    signature :link_s* get_enc_by_open(  mutable );
    signature :link_s* get_enc_by_dn(    mutable, :link_s* dn );
    signature :link_s* get_exc_by_name(  mutable, tp_t name );
    signature :cell_s* get_cell_by_name( mutable, tp_t name );

    stamp :cell = aware :
    {
                tp_t       name;
               :links_s    encs; // entry channels
               :links_s    excs; // exit channels
               :body_s  => body;
        aware ::op      -> op;   // cell holds either operator (cell is a node) or body (cell is a graph) or neither (cell is a wrapper)
                sz_t       priority = 10;

        private :cell_s* parent; // lexical parent

        hidden bcore_source_point_s source_point;

        func : :get_name = :get_name_;
        func : :get_arity =       { return :links_s_count_open(       &o->encs       ); };
        func : :get_enc_by_name = { return :links_s_get_link_by_name( &o->encs, name ); };
        func : :get_exc_by_name = { return :links_s_get_link_by_name( &o->excs, name ); };
        func : :get_enc_by_open = { return :links_s_get_link_by_up(   &o->encs, NULL ); };
        func : :get_enc_by_dn   = { return :links_s_get_link_by_dn(   &o->encs, dn   ); };
        func : :get_priority    = { return o->priority; };

        // search for a cell descends the tree
        func : :get_cell_by_name =
        {
            ::sem* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
            if( sem && sem->_ == TYPEOF_:cell_s ) return ( :cell_s* )sem;
            if( o->parent ) return :cell_s_get_cell_by_name( o->parent, name );
            return NULL;
        };

        // search for a link only looks up the body of this cell
        func : :get_link_by_name =
        {
            ::sem* sem = o->body ? :body_s_get_sem_by_name( o->body, name ) : NULL;
            if( sem && sem->_ == TYPEOF_:link_s ) return ( :link_s* )sem;
            return NULL;
        };

    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /// evaluation stack indicators
    stamp :stack_flag = aware : {};
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// tree group
group :ctr =
{
    stamp :node = aware bcore_array
    {
        sz_t id = -1;
        private ::sem_cell_s -> cell;
        private :node_s -> parent;
        :node_s => [];
    };

    stamp :tree = aware :
    {
        sz_t id_base = 0; // (incremented when adding nodes)
        :node_s => root;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// network group
group :net =
{
    stamp :link = aware :
    {
        hidden vd_t /* :node_s* */ node; // (!) target is a node
    };

    stamp :links = aware bcore_array { :link_s => []; };

    signature void solve( mutable );

    stamp :node = aware :
    {
        :links_s upls; // uplinks
        :links_s dnls; // downlinks

        /** Temporary flag used for various tracing routines.
          * It is typically used to ensure a node is visited only once.
          * Normalized state: false
          */
        bl_t flag = false;

        /** Node ID.
          * When the network cell is normalized, id is identical with the cell->body index.
          * id is also used to address the holor in the virtual machine.
          */
        sz_t id;

        /** Gradient ID.
          * Indicates the location of the gradient holor for the node.
          * -1 means: node needs no gradient.
          */
        sz_t gid = -1;

        tp_t name;
        aware ::op -> op;

        bhvm_hf3_s-> h; // holor after solving network

        bcore_source_point_s -> source_point;

        func : :solve;
    };

    signature :node_s* get_by_id( mutable, sz_t id );
    stamp :nodes = aware bcore_array
    {
        :node_s => [];
        func : :get_by_id =
        {
            BFOR_EACH( i, o ) if( o->data[ i ]->id == id ) return o->data[ i ];
            return NULL;
        };
    };

    signature void normalize( mutable );
    signature void clear_flags( mutable );
    signature bl_t is_consistent( const );
    signature void clear_downlinks( mutable );
    signature void set_downlinks( mutable );

    stamp :cell = aware :
    {
        sz_t max_depth = 32768; // maximum recursion depth
        :nodes_s body;
        :nodes_s encs; // entry channels
        :nodes_s excs; // exit channels

        func : :is_consistent;
        func : :normalize; // re-entrant

        func : :clear_flags =
        {
            BFOR_EACH( i, &o->body ) o->body.data[ i ]->flag = false;
        };

        func : :solve =
        {
            BFOR_EACH( i, &o->excs ) :node_s_solve( o->excs.data[ i ] );
        };

        func : :clear_downlinks =
        {
            BFOR_EACH( i, &o->body ) :links_s_clear( &o->body.data[ i ]->dnls );
        };

        func : :set_downlinks;

        func bcore_inst_call : copy_x; // cell is copyable
        func bcore_via_call  : mutated = { ERR_fa( "Cannot reconstitute." ); }; // cell is not transferable
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// virtual machine
group :vm =
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :adaptive = aware badapt_adaptive
    {

        // === architecture parameters ================================

        st_s                   sig;   // frame signature
        aware =>               src;   // source (bcore_file_path_s or st_s with inline code)  (just for reference)
        bhvm_hf3_vm_frame_s    vm;    // virtual machine
        badapt_dynamics_std_s  dynamics;
        sz_t             in_size;         // input vector size
        sz_t             out_size;        // output vector size
        sz_t             index_in;        // index into vm-holor array
        sz_t             index_out;       // index into vm-holor array
        sz_t             index_grad_out;  // index into vm-holor array
        bcore_arr_sz_s   index_arr_adaptive; // indices of all adaptives

        // ==============================================================

        // === adaptive functions =======================================
        func ^ : get_in_size  = { return o->in_size;  };
        func ^ : get_out_size = { return o->out_size; };
        func ^ : get_dynamics_std = { badapt_dynamics_std_s_copy( dynamics, &o->dynamics ); };
        func ^ : set_dynamics_std = { badapt_dynamics_std_s_copy( &o->dynamics, dynamics ); };

        func ^ : arc_to_sink;
        func ^ : minfer;

//        func ^ : bgrad;
        func ^ : bgrad_adapt;
        // ==============================================================
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    stamp :builder = aware badapt_builder
    {
        st_s sig = "( y => dim_y, a )"; // frame signature
        aware => src; // source (bcore_file_path_s or st_s with inline code)

        sz_t in_size;  // input vector size
        sz_t out_size; // output vector size
        badapt_dynamics_std_s dynamics;

        u2_t rseed = 1234; /* seed for adaptive randomizer */

        // === builder functions =======================================

        /// input vector size
        func ^ : get_in_size = { return o->in_size; };
        func ^ : set_in_size = { o->in_size = size; };

        /// output vector size
        func ^ : get_out_size = { return o->out_size; };
        func ^ : set_out_size = { o->out_size = size; };

        /// builds adaptive ready to be trained; passes ownership
        func ^ : build;

        // ==============================================================
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// global context
stamp :context = aware :
{
    bcore_hmap_name_s hmap_name;
    bcore_arr_st_s    arr_symbol_op2;
    :sem_cell_s       cell; // frame of a cell structure
    bcore_arr_tp_s    control_types; // types reserved for control and not allowed for identifiers

    /** The randomizer is supposed to produce different values on repeated calls but
     *  always the same sequence of random values for building a network.
     *  Therefore randomizer_mutex is locked during a build.
     */
    private bcore_mutex_s* randomizer_mutex;
    bl_t                   randomizer_is_locked;
    u2_t                   randomizer_rval;

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION

// ---------------------------------------------------------------------------------------------------------------------
// Interface functions

/// creates a frame-cell
haptive_sem_cell_s* haptive_sem_cell_s_create_frame();

/// frame-cell parsing from text source
void haptive_sem_cell_s_parse_signature( haptive_sem_cell_s* o, bcore_source* source );
void haptive_sem_cell_s_parse_body(      haptive_sem_cell_s* o, bcore_source* source );

/** Builds a net cell from a semantic cell
 *  This function locks and initializes the randomizer to ensure a deterministic sequence of random values.
 */
void haptive_net_cell_s_from_sem_cell
(
    haptive_net_cell_s* o,
    haptive_sem_cell_s* sem_cell,
    haptive_op* (*input_op_create)( vd_t arg, sz_t in_idx, tp_t in_name ),
    vd_t arg,
    bcore_sink* log
);

/// outputs graph to sink
void haptive_net_cell_s_graph_to_sink( haptive_net_cell_s* o, bcore_sink* sink );

/// builds vm procedure infer
void haptive_cell_s_vm_build_infer( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf );

/// builds vm procedure bp_grad
void haptive_cell_s_vm_build_bp_grad( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf );

/// sets adaptive gradients to zero
void haptive_net_cell_s_vm_build_zero_adaptive_grad( haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf );

/// builds vm procedure setup
void haptive_vm_build_setup( bhvm_hf3_vm_frame_s* o, u2_t rseed );

/// builds vm procedure shelve
void haptive_vm_build_shelve( bhvm_hf3_vm_frame_s* o );

/// specifies input holors on virtual machine
void haptive_net_cell_s_vm_set_input(  const haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf );

/// specifies output holors on virtual machine
void haptive_net_cell_s_vm_set_output( const haptive_net_cell_s* o, bhvm_hf3_vm_frame_s* vmf );

/// pulls all relevant names into frame's name map
void haptive_bhvm_hf3_vm_frame_s_pull_names( bhvm_hf3_vm_frame_s* o );

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_haptive

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

vd_t haptive_graph_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // HAPTIVE_GRAPH_H
