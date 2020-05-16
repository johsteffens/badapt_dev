/// Author & Copyright (C) 2020 Johannes Bernhard Steffens. All rights reserved.

#include <sys/time.h>

#include "badapt_std.h"
#include "bhvm_std.h"
#include "bhpt_std.h"
#include "badapt_dev_signal.h"
#include "lion_signal.h"
#include "badapt_dev_ern.h"
#include "badapt_dev_lstm.h"

int main( int argc, char** argv )
{
    bcore_register_signal_handler( bmath_signal_handler );
    bcore_register_signal_handler( bhvm_signal_handler );
    bcore_register_signal_handler( bhpt_signal_handler );
    bcore_register_signal_handler( badapt_signal_handler );
    bcore_register_signal_handler( badapt_dev_signal_handler );
    bcore_register_signal_handler( lion_signal_handler );

    // bmath_quicktypes_to_stdout( NULL ); return 0;

    // plant
    if( argc > 1 && sc_t_equal( argv[ 1 ], "-p" ) )
    {
        if( bcore_plant_run_globally() )
        {
            bcore_down( true );
            return 0;
        }
        argc--;
        argv++;
    }

    /// testing flects and spects
    bcore_flect_parse_all_flects();
    bcore_inst_test_all_types();

    BLM_INIT();

    s2_t ret = -1;
    bcore_main_frame_s* main_frame = BLM_CREATE( bcore_main_frame_s );
    main_frame->use_first_argument = true;
    ret = bcore_main_frame_s_main( main_frame, argc, argv );
    if( ret >= 0 )
    {
        BLM_DOWN();
        bcore_down( true );
        return ret;
    }

    BLM_DOWN();

    bcore_down( true );

    return ret;
}
