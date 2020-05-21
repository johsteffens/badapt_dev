/// Author & Copyright (C) 2020 Johannes Bernhard Steffens. All rights reserved.

#include <sys/time.h>

#include "badapt_std.h"
#include "bhvm_std.h"
#include "bhpt_std.h"
#include "badapt_dev_plant_config.h"
#include "lion_plant_config.h"
#include "badapt_dev_ern.h"
#include "badapt_dev_lstm.h"

int main( int argc, char** argv )
{
    BETH_PLANT_OPEN;
    BETH_PLANT_USE( bmath );
    BETH_PLANT_USE( bhvm );
    BETH_PLANT_USE( bhpt );
    BETH_PLANT_USE( badapt );
    BETH_PLANT_USE( badapt_dev );
    BETH_PLANT_USE( lion );

    // plant
    if( argc > 1 && sc_t_equal( argv[ 1 ], "-p" ) )
    {
        beth_plant_compile_all();
        if( beth_plant_update_required() )
        {
            beth_plant_update();
            BETH_PLANT_CLOSEV( true );
            return 0;
        }
        argc--;
        argv[ 1 ] = argv[ 0 ];
        argv++;

        /// testing flects and spects
        bcore_flect_parse_all_flects();
        bcore_inst_test_all_types();
    }

    BLM_INIT();

    bcore_main_frame_s* main_frame = BLM_CREATE( bcore_main_frame_s );
    main_frame->use_first_argument = true;
    s2_t retv = bcore_main_frame_s_main( main_frame, argc, argv );

    BLM_DOWN();

    BETH_PLANT_CLOSEV( true );

    return retv;
}
