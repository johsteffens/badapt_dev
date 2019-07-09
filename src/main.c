/// Author & Copyright (C) 2018 Johannes Bernhard Steffens. All rights reserved.

#include <sys/time.h>

#include "badapt_std.h"
#include "badapt_dev_signal.h"
#include "badapt_dev_ern.h"
#include "badapt_dev_lstm.h"
#include "bsym.h"

int main( int argc, char** argv )
{
    bcore_register_signal_handler( bmath_signal_handler );
    bcore_register_signal_handler( badapt_signal_handler );
    bcore_register_signal_handler( badapt_dev_signal_handler );

    // plant
    if( argc > 1 && sc_t_equal( argv[ 1 ], "-p" ) )
    {
        if( bcore_plant_run_globally() )
        {
            bcore_down( true );
            return 0;
        }
    }

    BCORE_LIFE_INIT();

    s2_t ret = 0;
    BCORE_LIFE_CREATE( bcore_main_frame_s, main_frame );
    ret = bcore_main_frame_s_main( main_frame, argc, argv );
    if( ret >= 0 )
    {
        BCORE_LIFE_DOWN();
        bcore_down( true );
        return ret;
    }

    bsym_test();

//    bcore_quicktypes_to_stdout( NULL );
//    return 0;



    //activator_test();
    //virtual_test();
    //return 0;

//    badapt_mlp_s_test_sine_random();
//    badapt_mlp_s_test_binary_add();
//    badapt_mlp_s_test_binary_mul();
//    badapt_mlp_s_test_binary_xsg3();
//    badapt_mlp_s_test_binary_hash();
//    badapt_mlp_s_test_polynom();

//    badapt_c1d_s_test_sine_random();
//    badapt_c1d_s_test_binary_add();
//    badapt_c1d_s_test_binary_mul();
//    badapt_c1d_s_test_binary_xsg3();
//    badapt_c1d_s_test_binary_hash();
//    badapt_c1d_s_test_polynom();

//    CPU_TIME_TO_STDOUT( badapt_dev_lstm_test_recurrent_abc() );
//    CPU_TIME_TO_STDOUT( badapt_lstm_test_recurrent_abc() );
//    CPU_TIME_TO_STDOUT( badapt_ern_test_recurrent_abc() );

//      CPU_TIME_TO_STDOUT( badapt_dev_lstm_test_recurrent_kjv() );

    //CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "badapt_mlp" ), NULL ) );
    //CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "bmath_adaptive_mlp" ), NULL ) );

    //snn_selftest2();
    BCORE_LIFE_DOWN();

    bcore_down( true );

    return ret;
}
