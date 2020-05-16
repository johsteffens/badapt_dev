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

/** Sketch for a dev framework of (pseudo-)random generators.
 *  The principal purpose of these generators are
 *  random initialization, noise generation and Monte-Carlo-Testing.
 *  Random generators studied and developed here are neither intended
 *  nor deemed suitable for any cryptographic use case.
 */

/**********************************************************************************************************************/

#ifndef BRND_EVAL_H
#define BRND_EVAL_H

#include "bmath_std.h"
#include "brnd_sketch.h"
#include "brnd_planted.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_brnd_eval

PLANT_GROUP( brnd_eval, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void resolve( mutable );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :result = aware bcore_inst
{
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
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' :result_s* run( const, :result_s* result ); // returns result

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void set( mutable, const :param_s* src );

stamp :param = aware bcore_inst
{
    hidden aware bcore_sink -> log;
    st_s name; // name of test (only for logging)
    sz_t verbosity = 1;
    u3_t => seed;

    aware brnd_gen  => gen;
    aware brnd_test => test;

    func bcore_inst_call : init_x = { o->log = bcore_fork( BCORE_STDOUT ); };

    func : :set =
    {
        o->verbosity = sz_max( o->verbosity, src->verbosity );
        bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
        if( o->name.size == 0 )
        {
            st_s_copy( &o->name, &src->name );
        }
        else if( src->name.size > 0 )
        {
            st_s* new_name = st_s_create_fa( "<sc_t>_<sc_t>", o->name.sc, src->name.sc );
            st_s_copy( &o->name, new_name );
            st_s_discard( new_name );
        }

        if( !o->gen ) o->gen  = brnd_gen_a_clone(  src->gen );
        if( !o->test ) o->test = brnd_test_a_clone( src->test );
        if( !o->seed && src->seed ) o->seed = ( u3_t* )bcore_inst_t_clone( TYPEOF_u3_t, ( bcore_inst* )&src->seed );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stump :std = aware :
{
    :param_s param;
    func : :run;
    func : :set_param = { :param_s_set( &o->param, param ); };
    func bcore_main :main =
    {
        BLM_INIT();
        :result_s_resolve( @_run( o, BLM_CREATE( :result_s ) ) );
        BLM_RETURNV( s2_t, 0 );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' void set_param( mutable, const :param_s* param );

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
                st_s_copy_fa( &result->msg, "At set entry #<sz_t>:\n#<st_s*>", i, BLM_CLONE( st_s, &result->msg ) );
                BLM_RETURNV( :result_s*, result );
            }
            BLM_DOWN();
        };
        return result;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :show_param = extending :std
{
    func : :run = { bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// testing error functions
stamp :errf = extending :std { func : :run; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// runs a plain test
stamp :plain = extending :std
{
    func : :run =
    {
        ASSERT( o->param.gen  );
        ASSERT( o->param.test );
        if( o->param.seed ) brnd_gen_a_reseed( o->param.gen, *o->param.seed );
        f3_t score = brnd_test_a_run( o->param.test, o->param.gen );
        if( o->param.verbosity > 0 )
        {
            bcore_sink_a_push_fa( o->param.log, "#<sc_t>( #<sc_t> ): ", ifnameof( o->param.test->_ ), ifnameof( o->param.gen->_ ) );
        }
        bcore_sink_a_push_fa( o->param.log, "score = #f3_t\n", score );
        return result;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_brnd_eval

/**********************************************************************************************************************/

vd_t brnd_eval_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BRND_EVAL_H
