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

#include "badapt_training.h"

/**********************************************************************************************************************/
/// badapt_arr_sample_s

/**********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------------

void badapt_supplier_fetch_batch_data_default( badapt_supplier* o, badapt_arr_sample_s* dst, sz_t size )
{
    for( sz_t i  = 0; i < size; i++ )
    {
        badapt_sample_s* sample = badapt_sample_s_create();
        badapt_supplier_a_fetch_batch_sample( o, sample );
        bcore_array_a_push( ( bcore_array* )dst, sr_tsd( TYPEOF_badapt_sample_s, sample ) );
    }
}

//----------------------------------------------------------------------------------------------------------------------

void badapt_supplier_fetch_valid_data_default( badapt_supplier* o, badapt_arr_sample_s* dst, sz_t size )
{
    for( sz_t i  = 0; i < size; i++ )
    {
        badapt_sample_s* sample = badapt_sample_s_create();
        badapt_supplier_a_fetch_valid_sample( o, sample );
        bcore_array_a_push( ( bcore_array* )dst, sr_tsd( TYPEOF_badapt_sample_s, sample ) );
    }
}

//----------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
/// badapt_trainer_s

void badapt_trainer_s_run( const badapt_trainer_s* o, badapt_adaptive* adaptive )
{
    ASSERT( o->supplier != NULL );
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_arr_sample_s, buffer_valid );
    BCORE_LIFE_CREATE( badapt_arr_sample_s, buffer_batch );

    badapt_adaptive_a_setup( adaptive );

    bcore_array_a_set_size( ( bcore_array* )buffer_valid, 0 );
    badapt_supplier_a_fetch_valid_data( o->supplier, buffer_valid, o->valid_size );

    for( sz_t iteration = 0; iteration < o->max_iterations; iteration++ )
    {
        for( sz_t fetch_cycle = 0; fetch_cycle < o->fetch_cycles_per_iteration; fetch_cycle++ )
        {
            bcore_array_a_set_size( ( bcore_array* )buffer_batch, 0 );
            badapt_supplier_a_fetch_valid_data( o->supplier, buffer_batch, o->batch_size );
            for( sz_t batch_cycle = 0; batch_cycle < o->batch_cycles_per_fetch; batch_cycle++ )
            {
                for( sz_t i = 0; i < o->batch_size; i++ )
                {
                    const badapt_sample_s* sample = &buffer_batch->arr_data[ i ];
                    badapt_adaptive_a_adapt_l2( adaptive, &sample->in, &sample->out, NULL );
                }
            }
        }
    }
    BCORE_LIFE_DOWN();
}

/**********************************************************************************************************************/

vd_t badapt_training_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_training" ) ) )
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

