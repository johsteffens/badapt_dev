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

// ---------------------------------------------------------------------------------------------------------------------

int main( void )
{
    bcore_register_signal_handler( bmath_signal_handler );
    bcore_register_signal_handler( badapt_signal_handler );
    if( bcore_precoder_run_globally() ) { bcore_down( true ); return 0; }

    //activator_test();
    //virtual_test();
    //return 0;

    badapt_mlp_s_test_sine_random();
//    badapt_mlp_s_test_binary_add();
//    badapt_mlp_s_test_binary_mul();
//    badapt_mlp_s_test_binary_xsg3();
//    badapt_mlp_s_test_binary_hash();
//    badapt_mlp_s_test_polynom();

    badapt_c1d_s_test_sine_random();
//    badapt_c1d_s_test_binary_add();
//    badapt_c1d_s_test_binary_mul();
//    badapt_c1d_s_test_binary_xsg3();
//    badapt_c1d_s_test_binary_hash();
//    badapt_c1d_s_test_polynom();

    //CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "badapt_mlp" ), NULL ) );
    //CPU_TIME_TO_STDOUT( bcore_run_signal_selftest( typeof( "bmath_adaptive_mlp" ), NULL ) );

    //snn_selftest2();
    bcore_down( true );
    return 0;
}
