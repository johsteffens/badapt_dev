/// Author & Copyright (C) 2018 Johannes Bernhard Steffens. All rights reserved.

#include <sys/time.h>

#include "badapt_std.h"

int main( void )
{
    bcore_register_signal_handler( bmath_signal_handler );
    bcore_register_signal_handler( badapt_signal_handler );
    if( bcore_precoder_run_globally() ) { bcore_down( true ); return 0; }

    bcore_spect_get_typed( typeof( "badapt_activator_s" ), typeof( "badapt_activator_plain_s" ) );

    bcore_inst_a_discard( bcore_inst_t_create( typeof( "badapt_trainer_s" ) ) );

    CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "badapt_mlp" ), NULL ) );
    CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "bmath_adaptive_mlp" ), NULL ) );

    //snn_selftest2();
    bcore_down( true );
    return 0;
}
