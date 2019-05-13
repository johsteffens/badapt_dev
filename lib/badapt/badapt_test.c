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

#include "badapt_test.h"
#include "badapt_loss.h"
#include "badapt_training.h"
#include "badapt_problem.h"

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

void badapt_adaptive_a_test_sine_random( const badapt_adaptive* const_o )
{
    BCORE_LIFE_INIT();

    BCORE_LIFE_CREATE( badapt_trainer_s, trainer );

    BCORE_LIFE_CREATE( badapt_trainer_state_s, state );
    badapt_adaptive_a_replicate( &state->adaptive, const_o );

    BCORE_LIFE_CREATE( badapt_problem_sine_random_s, problem );
    badapt_supplier_a_replicate( &state->supplier, ( badapt_supplier* ) problem );

    state->log = bcore_inst_a_clone( ( bcore_inst* )BCORE_STDOUT );

    badapt_trainer_s_run( trainer, state );

    BCORE_LIFE_RETURN();
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_adaptive_a_test_binary_add( const badapt_adaptive* const_o )
{
    BCORE_LIFE_INIT();

    BCORE_LIFE_CREATE( badapt_trainer_s, trainer );

    BCORE_LIFE_CREATE( badapt_trainer_state_s, state );
    badapt_adaptive_a_replicate( &state->adaptive, const_o );

    BCORE_LIFE_CREATE( badapt_problem_binary_add_s, problem );
    badapt_supplier_a_replicate( &state->supplier, ( badapt_supplier* ) problem );

    BCORE_LIFE_CREATE( badapt_training_guide_std_s, guide );
    guide->annealing_factor = 0.99;
    badapt_training_guide_a_replicate( &state->guide, ( badapt_training_guide* )guide );

    state->log = bcore_inst_a_clone( ( bcore_inst* )BCORE_STDOUT );

    badapt_trainer_s_run( trainer, state );

    BCORE_LIFE_RETURN();
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

vd_t badapt_test_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_test" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            return NULL;
        }
        break;

        case TYPEOF_precoder:
        {
            bcore_precoder_compile( "badapt_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

/**********************************************************************************************************************/

