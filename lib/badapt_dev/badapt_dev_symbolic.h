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

/** Symbolic representation of an adaptive
 */

/*
    ========================================

    given globals:
    variables: g_in, g_out
    various literals (numbers, activation functions, operators)

    ========================================
    MLP

    l = ( dim, act, x ) -> ( y )
    {
        w = [ dim ][];
        b = [];
        y = act( ( x * w ) + b );
    }

    lr = l( act = act_relu );
    lt = l( act = act_tanh );

    mlp = ( x ) -> ( y )
    {
        x >>
        lr( dim = 10 ) >>
        lr( dim = 20 ) >>
        lr( dim = 10 ) >> ... >>
        lt( dim =  1 ) >> y
    }

    g_out = mlp( g_in );

    ========================================
    LSTM

    l = ( dim_h, x, ci = [dim_h], hi = [dim_h] ) -> ( co, ho )
    {
        w_fx = [ dim_h ][]; w_fh = [ dim_h ][]; b_f = [ dim_h ];
        w_ix = [ dim_h ][]; w_ih = [ dim_h ][]; b_i = [ dim_h ];
        w_ox = [ dim_h ][]; w_oh = [ dim_h ][]; b_o = [ dim_h ];
        w_qx = [ dim_h ][]; w_qh = [ dim_h ][]; b_q = [ dim_h ];

        v_f = act_sig ( ( w_fx * x ) + ( w_fh * hi ) + b_f );
        v_i = act_sig ( ( w_ix * x ) + ( w_ih * hi ) + b_i );
        v_o = act_sig ( ( w_ox * x ) + ( w_oh * hi ) + b_o );
        v_q = act_tanh( ( w_qx * x ) + ( w_qh * hi ) + b_q );

        co  = v_f <o> ci + v_i <o> v_q;
        v_d = act_tanh( co );
        ho  = v_o <o> v_d;
    }

    lstm = ( dim_h, x ) -> ( y )
    {
        c = [ dim_h ]; // recurrent var
        h = [ dim_h ]; // recurrent var
        w_r = [ dim_h ][]; b_r = [ dim_h ];
        l( dim_h = dim_h, x = x, ci = c, hi = h ) -> ( h = ho, c = co );
        y = act_tanh( w_r * h + b_r );
    }

    g_out = lstm( dim_h = 200, x = g_in );

*/

#ifndef BADAPT_DEV_SYMBOLIC_H
#define BADAPT_DEV_SYMBOLIC_H

#include "bcore_std.h"
#include "badapt_activator.h"
#include "badapt_adaptive.h"
#include "badapt_dev_precoded.h"

/**********************************************************************************************************************/

#ifdef TYPEOF_badapt_dev_symbolic
BETH_PRECODE( badapt_dev_symbolic )
#ifdef BETH_PRECODE_SECTION

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#endif // BETH_PRECODE_SECTION
#endif // TYPEOF_badapt_dev_symbolic


/**********************************************************************************************************************/

vd_t badapt_dev_symbolic_signal_handler( const bcore_signal_s* o );

/**********************************************************************************************************************/

#endif // BADAPT_DEV_SYMBOLIC_H
