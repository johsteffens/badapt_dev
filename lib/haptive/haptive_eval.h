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

/** Description

*/

/**********************************************************************************************************************/

#ifndef HAPTIVE_EVAL_H
#define HAPTIVE_EVAL_H

#include "haptive_graph.h"

// ---------------------------------------------------------------------------------------------------------------------

#ifdef TYPEOF_haptive_eval
PLANT_GROUP( haptive_eval, bcore_inst )
#ifdef PLANT_SECTION

/// runs test, returns 0 on success.
feature 'a' s2_t run( const );

/** Tests gradient computation for adaptive holors.
 *  This is done by estimating the gradient for a
 *  given input and output using partial differentiation
 *  with given epsilon and comparing the result to the gradient
 *  obtained from reverse accumulating automatic differentiation.
 *  (Does not work for recurrent nets)
 */
stamp :grad = aware :
{
    f3_t epsilon = 1E-2;
    bhvm_hf3_vm_frame_s -> vmf; // virtual machine
    bhvm_hf3_adl_s      -> in;  // input
    bhvm_hf3_adl_s      -> out; // target output

    s2_t verbosity  = 1;           // verbosity;
    f3_t max_dev    = 1E-4;        // if grad deviation exceeds this value an error is generated
    hidden aware bcore_sink -> log;
    func bcore_inst_call : init_x = { o->log = bcore_fork( BCORE_STDOUT ); };
    func : : run;
    func bcore_main : main = { return @run( o ); };
};

/// single end to end test for a cell on a virtual machine
stamp :e2e = aware :
{
    st_s name;              // name of test (only for logging)
    st_s sig;               // frame signature
    aware => src;           // source (bcore_file_path_s or st_s with inline code)

    bhvm_hf3_adl_s => in;   // input holors
    bhvm_hf3_adl_s => out;  // expected output holors (if NULL, output is sent to log)
    sz_t infer_cycles = 1;  // multiple infer cycles tests reentrant behavior (e.g. recurrent networks generate different output for each cycle)
    s2_t verbosity = 1;    // verbosity;
    f3_t max_dev   = 1E-8; // if output deviation exceeds this value an error is generated
    hidden aware bcore_sink -> log;

    :grad_s => grad;        // gradient test (vacant parameters are set by e2e)

    // constructor
    func bcore_inst_call : init_x = { o->log = bcore_fork( BCORE_STDOUT ); };
    func :               : run;
    func bcore_main      : main = { return @run( o ); };
};

stamp :arr = aware bcore_array { aware :* []; };

/** Set of evaluations (elements can be sets or end to end tests).
 *  Parameters inside act as default values for sub-tests
 *  sub tests can override some of the defaults by explicitly defining them.
 */
stamp :set = aware :
{
    st_s set_name;         // name of this set (only for logging)
    st_s sig;              // frame signature
    bhvm_hf3_adl_s => in;  // input holors
    bhvm_hf3_adl_s => out; // expected output holors (if NULL, output is sent to log)
    s2_t verbosity = -1;   // >= 0 force overrides sub test verbosity
    f3_t max_dev   = -1;   // >= 0 force overrides sub test max_dev

    :arr_s arr;

    hidden aware bcore_sink -> log; // force overrides all sub-test logs

    // constructor
    func bcore_inst_call : init_x = { o->log = bcore_fork( BCORE_STDOUT ); };
    func :               : run;
    func bcore_main      : main = { return @run( o ); };
};

#endif // PLANT_SECTION

// ---------------------------------------------------------------------------------------------------------------------

#endif // TYPEOF_haptive_eval

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

vd_t haptive_eval_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // HAPTIVE_EVAL_H
