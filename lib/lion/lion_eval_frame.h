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

#ifndef LION_EVAL_FRAME_H
#define LION_EVAL_FRAME_H

#include "lion_net.h"
#include "lion_frame.h"
#include "lion_xoila_out.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_lion_eval_frame

XOILA_DEFINE_GROUP( lion_eval_frame, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void resolve( mutable );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :result = aware bcore_inst
{
    bl_t error = false;
    st_s msg;

    func : .resolve =
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

feature :result_s* run( const, :result_s* result ); // returns result

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void set( mutable, const :param_s* src );
stamp :param = aware bcore_inst
{
    hidden aware bcore_sink -> log;
    sz_t verbosity = 1;
    u3_t rval = 1234; // for random generators

    st_s name;              // name of test (only for logging)
    aware => src;           // source (bcore_file_path_s or st_s with inline code)

    bhvm_holor_adl_s => in;  // input holors
    bhvm_holor_adl_s => out; // expected output holors (if NULL, output is sent to log)

    bl_t recovery_test = false; // transfers the frame though stream-io
    bl_t jacobian_test = false;

    f3_t max_dev = 1E-5;   // if output deviation exceeds this value, an error is generated
    f3_t epsilon = 1E-5;   // for Jacobian estimation

    func bcore_inst_call . init_x = { o->log = bcore_fork( BCORE_STDOUT ); };

    func : .set =
    {
        o->recovery_test = o->recovery_test || src->recovery_test;
        o->jacobian_test = o->jacobian_test || src->jacobian_test;

        o->verbosity = sz_max( o->verbosity, src->verbosity );
        o->rval      = bcore_lcg00_u3( o->rval + src->rval );
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

        if( !o->src ) o->src = bcore_fork( src->src );
        if( !o->in  ) o->in  = bcore_fork( src->in );
        if( !o->out ) o->out = bcore_fork( src->out );

        o->max_dev = f3_max( o->max_dev, src->max_dev );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stump :std = aware :
{
    :param_s param;
    func : .run;
    func : .set_param = { :param_s_set( &o->param, param ); };
    func bcore_main .main =
    {
        BLM_INIT();
        :result_s_resolve( @_run( o, BLM_CREATE( :result_s ) ) );
        BLM_RETURNV( s2_t, 0 );
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :show_param = extending :std
{
    func : .run = { bcore_txt_ml_a_to_sink( &o->param, o->param.log ); return result; };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature void set_param( mutable, const :param_s* param );

stamp :arr = aware bcore_array { aware :=> []; };

stamp :set = extending :std
{
    :arr_s arr;
    func : .run =
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
        }
        return result;
    };
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :plain  = extending :std
{
    sz_t ap_cycles = 1; // for testing
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

stamp :cyclic  = extending :std
{
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//stamp :timing = extending :std {};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // TYPEOF_lion_eval_frame

/**********************************************************************************************************************/

vd_t lion_eval_frame_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // LION_EVAL_FRAME_H
