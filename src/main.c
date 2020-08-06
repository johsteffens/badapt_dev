/// Author & Copyright (C) 2020 Johannes Bernhard Steffens. All rights reserved.

#include "bcore_std.h"

int main( int argc, char** argv )
{
    BETH_USE( badapt_dev );
    BETH_USE( lion );
    BETH_USE( opal );

    /// testing flects and spects
    bcore_flect_parse_all_flects();
    bcore_inst_test_all_types();

    BLM_INIT();
    bcore_main_frame_s* main_frame = BLM_CREATE( bcore_main_frame_s );
    main_frame->use_first_argument = true;
    er_t retv = bcore_main_frame_s_main( main_frame, argc, argv );
    BLM_DOWN();

    BETH_CLOSEV( 1 );
    return retv;
}
