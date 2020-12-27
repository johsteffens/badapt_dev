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

/// Network Frame Evaluation

/**********************************************************************************************************************/

#ifndef OPAL_EVAL_FRAME_H
#define OPAL_EVAL_FRAME_H

#include "opal_net.h"
#include "opal_frame.h"
#include "opal.xo.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_opal_eval_frame

XOILA_DEFINE_GROUP( opal_eval_frame, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void resolve( mutable );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :result_s = aware bcore_inst
{
    bl_t error = false;
    st_s msg;

    func : .resolve =
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
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature :result_s* run( const, :result_s* result ); // returns result

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void set( mutable, const :param_s* src );
stamp :param_s = aware bcore_inst
{
    hidden aware bcore_sink -> log;
    sz_t verbosity = 1;
    u3_t rval = 1234; // for random generators

    st_s name;               // name of test (only for logging)
    aware x_inst => src; // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_adl_s => in;  // input holors
    bhvm_holor_adl_s => out; // expected output holors (if NULL, output is sent to log)

    bl_t recovery_test = false; // transfers the frame though stream-io
    bl_t jacobian_test = false;

    f3_t max_dev = 1E-5;   // if output deviation exceeds this value, an error is generated
    f3_t epsilon = 1E-5;   // for Jacobian estimation

    func bcore_inst_call . init_x = { o.log = bcore_fork( BCORE_STDOUT ); };

    func :.set =
    {
        o.recovery_test = o.recovery_test || src.recovery_test;
        o.jacobian_test = o.jacobian_test || src.jacobian_test;

        o.verbosity = sz_max( o.verbosity, src.verbosity );
        o.rval      = bcore_lcg00_u3( o.rval + src.rval );
        o.log       =< src.log.fork();

        if( o.name.size == 0 )
        {
            o.name.copy( src.name );
        }
        else if( src.name.size > 0 )
        {
            o.name.push_fa( "_<sc_t>", src.name.sc );
        }

        if( !o.src ) o.src = src.src.fork();
        if( !o.in  ) o.in  = src.in.fork();
        if( !o.out ) o.out = src.out.fork();

        o.max_dev = f3_max( o.max_dev, src.max_dev );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stump :std_s = aware :
{
    :param_s param;
    func :.run;
    func :.set_param = { o.param.set( param ); };
    func bcore_main .main =
    {
        o.run( :result_s!^^ ).resolve();
        return 0;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :show_param_s = extending :std_s
{
    func : .run = { bcore_txt_ml_a_to_sink( &o.param, o.param.log ); return result; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature void set_param( mutable, const :param_s* param );

stamp :arr_s = aware x_array { aware : => []; };

stamp :set_s = extending :std_s
{
    :arr_s arr;
    func :.run =
    {
        foreach( const :* e in o.arr )
        {
            :* eval = e.clone().scope( eval );
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :plain_s = extending :std_s
{
    sz_t ap_cycles = 1; // for testing
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :cyclic_s = extending :std_s
{
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

embed "opal_eval_frame.x";

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_opal_eval_frame

/**********************************************************************************************************************/

#endif // OPAL_EVAL_FRAME_H
