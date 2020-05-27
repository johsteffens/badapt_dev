/// Author & Copyright (C) 2020 Johannes Bernhard Steffens. All rights reserved.

#include "bcore_std.h"

int main( int argc, char** argv )
{
    BETH_PLANT_USE( badapt_dev );
    BETH_PLANT_USE( lion );

    // plant
    if( argc > 1 && sc_t_equal( argv[ 1 ], "-p" ) )
    {
        BETH_PLANT_BUILD_FROM_DEFAULT();
        if( beth_plant_update_required() )
        {
            beth_plant_update();
            BETH_PLANT_CLOSEV( 1 );
            return 0;
        }
        argc--;
        argv[ 1 ] = argv[ 0 ];
        argv++;
    }

    /// testing flects and spects
    bcore_flect_parse_all_flects();
    bcore_inst_test_all_types();

    BLM_INIT();
    bcore_main_frame_s* main_frame = BLM_CREATE( bcore_main_frame_s );
    main_frame->use_first_argument = true;
    s2_t retv = bcore_main_frame_s_main( main_frame, argc, argv );
    BLM_DOWN();

    BETH_PLANT_CLOSEV( 1 );
    return retv;
}
