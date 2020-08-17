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

#ifndef LION_EVAL_NOP_H
#define LION_EVAL_NOP_H

#include "bmath_std.h"
#include "bhvm_mcode.h"
#include "lion_xoila_out.h"
#include "lion_nop.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_eval_nop

XOILA_DEFINE_GROUP( lion_eval_nop, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void resolve( const );

stamp :result = aware bcore_inst
{
    sz_t total_tests = 0;
    sz_t solvable_tests = 0;
    sz_t tolerated_errors = 0;

    bl_t error = false;
    st_s msg;

    func : :resolve =
    {
        if( !o ) return;
        if( o->error )
        {
            bcore_sink_a_push_fa( BCORE_STDERR, "#<sc_t>\n", o->msg.sc );
        }
        else if( o->msg.size > 0 )
        {
            bcore_sink_a_push_fa( BCORE_STDOUT, "#<sc_t>\n", o->msg.sc );
        }
        if( o->total_tests > 0 )
        {
            bcore_sink_a_push_fa( BCORE_STDOUT, "Total tests ...... #<sz_t>\n", o->total_tests );
            bcore_sink_a_push_fa( BCORE_STDOUT, "Solvable tests ... #<sz_t> (#<sz_t>%)\n", o->solvable_tests, ( o->solvable_tests * 100 ) / o->total_tests );
            bcore_sink_a_push_fa( BCORE_STDOUT, "Tolerated errors . #<sz_t>\n", o->tolerated_errors );
        }
    };
};

signature void set( mutable, const :param_s* src );
stamp :param = aware bcore_inst
{
    aware lion_nop => nop;
    lion_holor_s => ha;
    lion_holor_s => hb;
    lion_holor_s => hc;
    lion_holor_s => hr;
    hidden aware bcore_sink -> log;
    sz_t verbosity = 1;
    u3_t rval = 1234; // for random generators

    func bcore_inst_call : init_x = { o->log = bcore_fork( BCORE_STDOUT ); };

    func : :set =
    {
        o->verbosity = sz_max( o->verbosity, src->verbosity );
        o->rval      = bcore_lcg00_u3( o->rval + src->rval );
        bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
        if( !o->ha  ) o->ha  = lion_holor_s_clone( src->ha );
        if( !o->hb  ) o->hb  = lion_holor_s_clone( src->hb );
        if( !o->hc  ) o->hc  = lion_holor_s_clone( src->hc );
        if( !o->hr  ) o->hr  = lion_holor_s_clone( src->hr );
        if( !o->nop ) o->nop = lion_nop_a_clone( src->nop );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' void set_param( mutable, const :param_s* param );
feature 'a' :result_s* run( const, :result_s* result ); // creates result or returns NULL

/// template
stump :std = aware :
{
    :param_s param;
    func : :run;
    func : :set_param = { :param_s_set( &o->param, param ); };
    func bcore_main : main =
    {
        BLM_INIT();
        :result_s_resolve( @_run( o, BLM_CREATE( :result_s ) ) );
        BLM_RETURNV( s2_t, 0 );
    };
};

/// randomizes holors defined in param; undefined holors stay undefined
stamp :generator = extending :std
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

stamp :show_param = extending :std
{
    func : :run = { bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result; };
};

stamp :arr = aware bcore_array { aware :* []; };

stamp :set = extending :std
{
    :arr_s arr;

    func : :run =
    {
        BFOR_EACH( i, &o->arr )
        {
            BLM_INIT();
            :* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
            :a_set_param( eval, &o->param );
            :a_run( eval, result );
            if( result->error )
            {
                st_s* s = BLM_A_PUSH( st_s_clone( &result->msg ) );
                st_s_copy_fa( &result->msg, "At set entry #<sz_t>:\n#<st_s*>", i, s );
                BLM_RETURNV( :result_s*, result );
            }
            BLM_DOWN();
        }
        return result;
    };
};

stamp :ar1 = extending :std {};
stamp :ar2 = extending :std {};

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_eval_nop

/**********************************************************************************************************************/

vd_t lion_eval_nop_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_EVAL_NOP_H
