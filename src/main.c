/// Author & Copyright (C) 2018 Johannes Bernhard Steffens. All rights reserved.

#include <sys/time.h>

#include "badapt_std.h"

void activator_test( void )
{
    BCORE_LIFE_INIT();

    BCORE_LIFE_CREATE( badapt_arr_activator_s, arr_a );
    BCORE_LIFE_CREATE( badapt_arr_layer_activator_s, arr_l );

    badapt_arr_layer_activator_s_push_c( arr_l, badapt_layer_activator_s_create_from_types(  0, TYPEOF_badapt_activator_plain_s, TYPEOF_badapt_activation_leaky_relu_s ) );
    badapt_arr_layer_activator_s_push_c( arr_l, badapt_layer_activator_s_create_from_types(  3, TYPEOF_badapt_activator_plain_s, TYPEOF_badapt_activation_softplus_s ) );
    badapt_arr_layer_activator_s_push_c( arr_l, badapt_layer_activator_s_create_from_types( -1, TYPEOF_badapt_activator_plain_s, TYPEOF_badapt_activation_tanh_s ) );
    badapt_arr_layer_activator_s_push_c( arr_l, badapt_layer_activator_s_create_from_types( -3, TYPEOF_badapt_activator_plain_s, TYPEOF_badapt_activation_relu_s ) );

    badapt_arr_activator_s_setup_from_arr_layer_activator( arr_a, arr_l, 10 );

    bcore_txt_ml_a_to_stdout( arr_l );
    bcore_txt_ml_a_to_stdout( arr_a );

    BCORE_LIFE_DOWN();
}

void virtual_test( void )
{
    badapt_activation* o1 = badapt_activation_t_create( TYPEOF_badapt_activation_leaky_relu_s );
    badapt_activation* o2 = badapt_activation_a_clone ( o1 );
    badapt_activation_a_replicate( &o2, o1 );

    bcore_txt_ml_a_to_stdout( o1 );
    bcore_txt_ml_a_to_stdout( o2 );

    badapt_activation_a_discard( o1 );
    badapt_activation_a_discard( o2 );
}

int main( void )
{
    bcore_register_signal_handler( bmath_signal_handler );
    bcore_register_signal_handler( badapt_signal_handler );
    if( bcore_precoder_run_globally() ) { bcore_down( true ); return 0; }

    //activator_test();
    //virtual_test();
    //return 0;

    CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "badapt_mlp" ), NULL ) );
    CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "bmath_adaptive_mlp" ), NULL ) );

    //snn_selftest2();
    bcore_down( true );
    return 0;
}
