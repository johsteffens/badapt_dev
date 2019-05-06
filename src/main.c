/// Author & Copyright (C) 2018 Johannes Bernhard Steffens. All rights reserved.

#include <sys/time.h>

#include "badapt_std.h"

int main( void )
{
    bcore_register_signal_handler( bmath_signal_handler );
    bcore_register_signal_handler( badapt_signal_handler );
    if( bcore_precoder_run_globally() ) { bcore_down( true ); return 0; }

//    bcore_run_signal_selftest( typeof( "bmath_simd" ), NULL );

    //snn_selftest2();
    bcore_down( true );
    return 0;
}
