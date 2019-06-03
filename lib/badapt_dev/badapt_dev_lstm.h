/** Copyright 2019 Johannes Bernhard Steffens
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

/** Long Short Term Memory Recurrent Network
 *
 *    recurrent inference:
 *    q = sig_k( W_k * x:h ) * c + sig_i( W_i * x:h ) * act_c( W_c * x:h )
 *    p = sig_p( W_p * x:h ) * act_q( q )
 *
 *    iterate:
 *    c <- q; // cell state
 *    h <- p; // hidden becomes output
 *
 *    x: input
 *    h: hidden (fed back from p)
 *    c: cell state
 *    p: recurrent output (passed on to output layer)
 *    q: new cell state
 *
 *    k: keep-gate, i: input-gate, o: output-gate
 *
 *    sig: sigmoid activator
 *    act: regular activator (typ tanh)
 *
 *    output infererence:
 *    act_o( W_p * p )
 */

#ifndef BADAPT_DEV_LSTM_H
#define BADAPT_DEV_LSTM_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_precoded.h"

/**********************************************************************************************************************/

BETH_PRECODE( badapt_dev_lstm )
#ifdef BETH_PRECODE_SECTION


stamp :s = aware badapt_adaptive
{
    // === architecture parameters ================================

    bmath_mf3_s w_k;
    bmath_mf3_s w_i;
    bmath_mf3_s w_c;
    bmath_mf3_s w_o;

    aware badapt_activator => sig_k;
    aware badapt_activator => sig_i;
    aware badapt_activator => sig_o;

    aware badapt_activator => act_c;
    aware badapt_activator => act_q;

    // === runtime data =============================================

    bmath_vf3_s v_x;
    bmath_vf3_s v_h;
    bmath_vf3_s v_c;
    bmath_vf3_s v_o;
    bmath_vf3_s v_q;

    bmath_vf3_s v_xh;

    // ==============================================================

    // === adaptive functions =======================================

    /*
    func : get_in_size;
    func : get_out_size;

    func : get_dynamics_std;
    func : set_dynamics_std;

    func : arc_to_sink;
    func : minfer;

    func : bgrad;
    func : bgrad_adapt;
    */

    // ==============================================================
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // BETH_PRECODE_SECTION

/**********************************************************************************************************************/
// tests

void badapt_dev_lstm_s_test_recurrent_kjv();

/**********************************************************************************************************************/

vd_t badapt_dev_lstm_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_DEV_LSTM_H
