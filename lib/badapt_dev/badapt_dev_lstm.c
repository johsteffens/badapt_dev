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

#include "bcore_std.h"
#include "bmath_std.h"
#include "bmath_plot.h"
#include "badapt_dev_lstm.h"
#include "badapt_lstm.h"
#include "badapt_trainer.h"
#include "badapt_dev_problem.h"


/**********************************************************************************************************************/
/// tests

void badapt_dev_lstm_s_run_training
(
    badapt_supplier* problem,
    badapt_builder* builder,
    badapt_guide* guide,
    const badapt_trainer_batch_s* trainer
)
{
    BCORE_LIFE_INIT();
    badapt_training_state* state = BCORE_LIFE_A_PUSH( badapt_trainer_batch_s_create_state( trainer ) );
    badapt_supplier_a_setup_builder( problem, builder );
    badapt_training_state_a_set_adaptive( state, BCORE_LIFE_A_PUSH( badapt_builder_a_build( builder ) ) );
    badapt_training_state_a_set_supplier( state, problem );
    badapt_training_state_a_set_guide( state, guide );
    badapt_adaptive_a_arc_to_sink( badapt_training_state_a_get_adaptive( state ), BCORE_STDOUT );
    badapt_trainer_batch_s_run( trainer, ( badapt_training_state* )state );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_dev_lstm_test_recurrent_abc()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_recurrent_abc_s, problem );
    BCORE_LIFE_CREATE( badapt_lstm_builder_s,          builder );
    BCORE_LIFE_CREATE( badapt_trainer_batch_s,         trainer );
    BCORE_LIFE_CREATE( badapt_guide_char_encode_s,     guide );

    st_s_copy_sc( &guide->txt_trigger, "abc" );
    builder->random_seed        = 111;
    builder->size_unfolded      = 10;
    builder->size_hidden        = 20;
    builder->dynamics.epsilon   = 0.02;
    builder->dynamics.lambda_l2 = 0.00001;
    trainer->fetch_cycles_per_iteration = 10;
    trainer->max_iterations = 5;

    badapt_dev_lstm_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, ( badapt_guide* )guide, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_lstm_test_recurrent_abc()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_problem_recurrent_abc_s, problem );
    BCORE_LIFE_CREATE( badapt_lstm_builder_s,          builder );
    BCORE_LIFE_CREATE( badapt_trainer_batch_s,         trainer );
    BCORE_LIFE_CREATE( badapt_guide_char_encode_s,     guide );

    st_s_copy_sc( &guide->txt_trigger, "abc" );
    builder->random_seed        = 111;
    builder->size_unfolded      = 10;
    builder->size_hidden        = 20;
    builder->dynamics.epsilon   = 0.02;
    builder->dynamics.lambda_l2 = 0.00001;
    trainer->fetch_cycles_per_iteration = 10;
    trainer->max_iterations = 5;

    badapt_dev_lstm_s_run_training( ( badapt_supplier* )problem, ( badapt_builder* )builder, ( badapt_guide* )guide, trainer );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_dev_lstm_test_recurrent_kjv()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_trainer_main_s, trainer_main );
    bcore_txt_ml_a_from_file( trainer_main, "dev/kjv/v0.cfg" );
    badapt_trainer_main_s_main( trainer_main, NULL );
    BCORE_LIFE_RETURN();
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t badapt_dev_lstm_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_lstm" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
        }
        break;

        case TYPEOF_plant:
        {
            bcore_plant_compile( "badapt_dev_planted", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


