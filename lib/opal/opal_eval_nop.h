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

/// Node Operator Evaluation

/**********************************************************************************************************************/

#ifndef OPAL_EVAL_NOP_H
#define OPAL_EVAL_NOP_H

#include "bmath_std.h"
#include "bhvm_mcode.h"
#include "opal.xo.h"
#include "opal_nop.h"

/**********************************************************************************************************************/

XOILA_DEFINE_GROUP( opal_eval_nop, bcore_inst )
#ifdef XOILA_SECTION

// ---------------------------------------------------------------------------------------------------------------------

signature void resolve( const );

stamp :result_s = aware bcore_inst
{
    sz_t total_tests = 0;
    sz_t solvable_tests = 0;
    sz_t tolerated_errors = 0;

    bl_t error = false;
    st_s msg;

    func :.resolve =
    {
        if( !o ) return;
        if( o.error )
        {
            bcore_sink_a_push_fa( BCORE_STDERR, "#<sc_t>\n", o.msg.sc );
        }
        else if( o.msg.size > 0 )
        {
            bcore_sink_a_push_fa( BCORE_STDOUT, "#<sc_t>\n", o.msg.sc );
        }
        if( o.total_tests > 0 )
        {
            bcore_sink_a_push_fa( BCORE_STDOUT, "Total tests ...... #<sz_t>\n", o.total_tests );
            bcore_sink_a_push_fa( BCORE_STDOUT, "Solvable tests ... #<sz_t> (#<sz_t>%)\n", o.solvable_tests, ( o.solvable_tests * 100 ) / o.total_tests );
            bcore_sink_a_push_fa( BCORE_STDOUT, "Tolerated errors . #<sz_t>\n", o.tolerated_errors );
        }
    };
};

// ---------------------------------------------------------------------------------------------------------------------

signature void set( mutable, const :param_s* src );

stamp :param_s = aware bcore_inst
{
    aware opal_nop => nop;
    opal_holor_s => ha;
    opal_holor_s => hb;
    opal_holor_s => hc;
    opal_holor_s => hr;
    hidden aware bcore_sink -> log;
    sz_t verbosity = 1;
    aware bcore_prsg => prsg = bcore_prsg_lcg_u3_00_s;

    func bcore_inst_call . init_x = { o.log = bcore_fork( BCORE_STDOUT ); };

    func :.set =
    {
        o.verbosity = sz_max( o.verbosity, src.verbosity );
        o.prsg.set_state_mix( o.prsg, src.prsg );
        o.log =< bcore_fork( src.log );
        if( !o.ha  ) o.ha  = src.ha.clone();
        if( !o.hb  ) o.hb  = src.hb.clone();
        if( !o.hc  ) o.hc  = src.hc.clone();
        if( !o.hr  ) o.hr  = src.hr.clone();
        if( !o.nop ) o.nop = src.nop.clone();
    };
};

// ---------------------------------------------------------------------------------------------------------------------

feature void set_param( mutable, const :param_s* param );
feature :result_s* run( const, :result_s* result ); // creates result or returns NULL

/// template
stump :std_s = aware :
{
    :param_s param;
    func :.run;
    func :.set_param = { o.param.set( param ); };
    func bcore_main . main =
    {
        o.run( :result_s!.scope() ).resolve();
        return 0;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

/// randomizes holors defined in param; undefined holors stay undefined
stamp :generator_s = extending :std_s
{
    bl_t set_htp    = false;  // changes htp-state
    bl_t set_value  = false;  // sets/changes values
    bl_t set_shape  = false;  // sets/changes shape
    bl_t set_dim    = false;  // sets/changes dimensions
    bl_t set_v_type = false;  // sets/changes value type

    sz_t max_shape_size =  3;
    sz_t max_dim        =  3;
    f3_t v_min          = -1;
    f3_t v_max          =  1;
    sz_t cycles         =  0;

    // Cycles with borderline conditions producing an error despite being mathematically correct
    // are not marked as error if listed in tolerated_cycles.
    bcore_arr_uz_s tolerated_cycles;
    aware : => eval;
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :show_param_s = extending :std_s
{
    func :.run = { bcore_txt_ml_a_to_sink( &o.param, o.param.log ); return result; };
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :arr_s = aware x_array { aware :=> []; };

stamp :set_s = extending :std_s
{
    :arr_s arr;

    func :.run =
    {
        foreach( :* e in o.arr )
        {
            :* eval = e.clone().scope( scope_local );
            eval.set_param( &o.param );
            eval.run( result );
            if( result.error )
            {
                result.msg.copy_fa( "At set entry #<sz_t>:\n#<st_s*>", __i, result.msg.clone().scope( scope_local ) );
                return result;
            }
        }
        return result;
    };
};

// ---------------------------------------------------------------------------------------------------------------------

stamp :ar1_s = extending :std_s { aware opal_context => context = opal_nop_context_s; };

// ---------------------------------------------------------------------------------------------------------------------

stamp :ar2_s = extending :std_s { aware opal_context => context = opal_nop_context_s; };

// ---------------------------------------------------------------------------------------------------------------------

embed "opal_eval_nop.x";

#endif

/**********************************************************************************************************************/

#endif // OPAL_EVAL_NOP_H
