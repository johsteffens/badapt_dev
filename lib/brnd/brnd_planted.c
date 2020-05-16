/** This file was generated from beth-plant source code.
 *  Compiling Agent : bcore_plant_compiler (C) 2019, 2020 J.B.Steffens
 *  Last File Update: 2020-05-16T10:15:38Z
 *
 *  Copyright and License of this File:
 *
 *  Generated code inherits the copyright and license of the underlying beth-plant source code.
 *  Source code defining this file is distributed across following files:
 *
 *  brnd_sketch.h
 *  brnd_eval.h
 *  brnd_gen.h
 *  brnd_test.h
 *
 */

#include "brnd_planted.h"
#include "bcore_spect.h"
#include "bcore_spect_inst.h"
#include "bcore_sr.h"
#include "bcore_const_manager.h"


/**********************************************************************************************************************/
// source: brnd_sketch.h
#include "brnd_sketch.h"

//----------------------------------------------------------------------------------------------------------------------
// group: brnd

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen

BCORE_DEFINE_SPECT( brnd, brnd_gen )
"{"
    "bcore_spect_header_s header;"
    "feature aware brnd_gen : max_u3;"
    "feature aware brnd_gen : min_u3;"
    "feature aware brnd_gen : gen_u3;"
    "feature aware brnd_gen : gen_f3;"
    "feature aware brnd_gen : reseed;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_test

BCORE_DEFINE_SPECT( brnd, brnd_test )
"{"
    "bcore_spect_header_s header;"
    "feature aware brnd_test : run;"
"}";

/**********************************************************************************************************************/
// source: brnd_eval.h
#include "brnd_eval.h"

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_eval

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_result_s )
"aware bcore_inst"
"{"
    "bl_t error = false;"
    "st_s msg;"
"}";

void brnd_eval_result_s_resolve( brnd_eval_result_s* o )
{
    if( !o ) return;
    if( o->error )
    {
        bcore_sink_a_push_fa( BCORE_STDERR, "#<sc_t>\n", o->msg.sc );
    }
    else if( o->msg.size > 0 )
    {
        bcore_sink_a_push_fa( BCORE_STDOUT, "#<sc_t>\n", o->msg.sc );
    }
}

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_param_s )
"aware bcore_inst"
"{"
    "hidden aware bcore_sink -> log;"
    "st_s name;"
    "sz_t verbosity = 1;"
    "u3_t => seed;"
    "aware brnd_gen => gen;"
    "aware brnd_test => test;"
    "func bcore_inst_call:init_x;"
"}";

void brnd_eval_param_s_set( brnd_eval_param_s* o, const brnd_eval_param_s* src )
{
    o->verbosity = sz_max( o->verbosity, src->verbosity );
    bcore_inst_a_attach( (bcore_inst**)&o->log, bcore_fork( src->log ) );
    if( o->name.size == 0 )
    {
        st_s_copy( &o->name, &src->name );
    }
    else if( src->name.size > 0 )
    {
        st_s* new_name = st_s_create_fa( "<sc_t>_<sc_t>", o->name.sc, src->name.sc );
        st_s_copy( &o->name, new_name );
        st_s_discard( new_name );
    }
    
    if( !o->gen ) o->gen  = brnd_gen_a_clone(  src->gen );
    if( !o->test ) o->test = brnd_test_a_clone( src->test );
    if( !o->seed && src->seed ) o->seed = ( u3_t* )bcore_inst_t_clone( TYPEOF_u3_t, ( bcore_inst* )&src->seed );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_arr_s )
"aware bcore_array"
"{"
    "aware brnd_eval* [];"
"}";

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_set_s )
"aware brnd_eval"
"{"
    "brnd_eval_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "brnd_eval_arr_s arr;"
    "func ^:run;"
"}";

s2_t brnd_eval_set_s_main( brnd_eval_set_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    brnd_eval_result_s_resolve( brnd_eval_set_s_run( o, BLM_CREATE( brnd_eval_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

brnd_eval_result_s* brnd_eval_set_s_run( const brnd_eval_set_s* o, brnd_eval_result_s* result )
{
    BFOR_EACH( i, &o->arr )
    {
        BLM_INIT();
        brnd_eval* eval = BLM_A_PUSH( bcore_inst_a_clone( (bcore_inst*)o->arr.data[ i ] ) );
        brnd_eval_a_set_param( eval, &o->param );
        brnd_eval_a_run( eval, result );
        if( result->error )
        {
            st_s_copy_fa( &result->msg, "At set entry #<sz_t>:\n#<st_s*>", i, BLM_CLONE( st_s, &result->msg ) );
            BLM_RETURNV( brnd_eval_result_s*, result );
        }
        BLM_DOWN();
    };
    return result;
}

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_show_param_s )
"aware brnd_eval"
"{"
    "brnd_eval_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

s2_t brnd_eval_show_param_s_main( brnd_eval_show_param_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    brnd_eval_result_s_resolve( brnd_eval_show_param_s_run( o, BLM_CREATE( brnd_eval_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_errf_s )
"aware brnd_eval"
"{"
    "brnd_eval_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

s2_t brnd_eval_errf_s_main( brnd_eval_errf_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    brnd_eval_result_s_resolve( brnd_eval_errf_s_run( o, BLM_CREATE( brnd_eval_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_eval_plain_s )
"aware brnd_eval"
"{"
    "brnd_eval_param_s param;"
    "func ^:set_param;"
    "func bcore_main:main;"
    "func ^:run;"
"}";

s2_t brnd_eval_plain_s_main( brnd_eval_plain_s* o, const bcore_arr_st_s* args )
{
    BLM_INIT();
    brnd_eval_result_s_resolve( brnd_eval_plain_s_run( o, BLM_CREATE( brnd_eval_result_s ) ) );
    BLM_RETURNV( s2_t, 0 );
}

brnd_eval_result_s* brnd_eval_plain_s_run( const brnd_eval_plain_s* o, brnd_eval_result_s* result )
{
    ASSERT( o->param.gen  );
    ASSERT( o->param.test );
    if( o->param.seed ) brnd_gen_a_reseed( o->param.gen, *o->param.seed );
    f3_t score = brnd_test_a_run( o->param.test, o->param.gen );
    if( o->param.verbosity > 0 )
    {
        bcore_sink_a_push_fa( o->param.log, "#<sc_t>( #<sc_t> ): ", ifnameof( o->param.test->_ ), ifnameof( o->param.gen->_ ) );
    }
    bcore_sink_a_push_fa( o->param.log, "score = #f3_t\n", score );
    return result;
}

BCORE_DEFINE_SPECT( bcore_inst, brnd_eval )
"{"
    "bcore_spect_header_s header;"
    "feature aware brnd_eval : run;"
    "feature aware brnd_eval : set_param;"
"}";

/**********************************************************************************************************************/
// source: brnd_gen.h
#include "brnd_gen.h"

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen_stamp

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_count_s )
"aware brnd_gen"
"{"
    "u2_t state = 0;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:gen_u3;"
    "func ^:gen_f3;"
    "func ^:reseed;"
"}";

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen_lcg

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_lcg_v00_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_lcg_v00_s_gen_f3( brnd_gen_lcg_v00_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_lcg_v00_s_gen_u3( o ) - brnd_gen_lcg_v00_s_min_u3( o ) ) / ( brnd_gen_lcg_v00_s_max_u3( o ) - brnd_gen_lcg_v00_s_min_u3( o ) ) );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_lcg_v01_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_lcg_v01_s_gen_f3( brnd_gen_lcg_v01_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_lcg_v01_s_gen_u3( o ) - brnd_gen_lcg_v01_s_min_u3( o ) ) / ( brnd_gen_lcg_v01_s_max_u3( o ) - brnd_gen_lcg_v01_s_min_u3( o ) ) );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_lcg_v02_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_lcg_v02_s_gen_f3( brnd_gen_lcg_v02_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_lcg_v02_s_gen_u3( o ) - brnd_gen_lcg_v02_s_min_u3( o ) ) / ( brnd_gen_lcg_v02_s_max_u3( o ) - brnd_gen_lcg_v02_s_min_u3( o ) ) );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_lcg_v03_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_lcg_v03_s_gen_f3( brnd_gen_lcg_v03_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_lcg_v03_s_gen_u3( o ) - brnd_gen_lcg_v03_s_min_u3( o ) ) / ( brnd_gen_lcg_v03_s_max_u3( o ) - brnd_gen_lcg_v03_s_min_u3( o ) ) );
}

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_gen_xsg

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_xsg_v00_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_xsg_v00_s_gen_f3( brnd_gen_xsg_v00_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_xsg_v00_s_gen_u3( o ) - brnd_gen_xsg_v00_s_min_u3( o ) ) / ( brnd_gen_xsg_v00_s_max_u3( o ) - brnd_gen_xsg_v00_s_min_u3( o ) ) );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_xsg_v01_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_xsg_v01_s_gen_f3( brnd_gen_xsg_v01_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_xsg_v01_s_gen_u3( o ) - brnd_gen_xsg_v01_s_min_u3( o ) ) / ( brnd_gen_xsg_v01_s_max_u3( o ) - brnd_gen_xsg_v01_s_min_u3( o ) ) );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_xsg_v02_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_xsg_v02_s_gen_f3( brnd_gen_xsg_v02_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_xsg_v02_s_gen_u3( o ) - brnd_gen_xsg_v02_s_min_u3( o ) ) / ( brnd_gen_xsg_v02_s_max_u3( o ) - brnd_gen_xsg_v02_s_min_u3( o ) ) );
}

BCORE_DEFINE_OBJECT_INST_P( brnd_gen_xsg_v03_s )
"aware brnd_gen"
"{"
    "func ^:gen_f3;"
    "u2_t state = 16432;"
    "func ^:max_u3;"
    "func ^:min_u3;"
    "func ^:reseed;"
    "func ^:gen_u3;"
"}";

f3_t brnd_gen_xsg_v03_s_gen_f3( brnd_gen_xsg_v03_s* o, f3_t min, f3_t max )
{
    return min + ( max - min ) * ( ( f3_t )( brnd_gen_xsg_v03_s_gen_u3( o ) - brnd_gen_xsg_v03_s_min_u3( o ) ) / ( brnd_gen_xsg_v03_s_max_u3( o ) - brnd_gen_xsg_v03_s_min_u3( o ) ) );
}

/**********************************************************************************************************************/
// source: brnd_test.h
#include "brnd_test.h"

//----------------------------------------------------------------------------------------------------------------------
// group: brnd_test_stamp

BCORE_DEFINE_OBJECT_INST_P( brnd_test_uniform_dist_s )
"aware brnd_test"
"{"
    "sz_t samples = 100000;"
    "sz_t slots = 100;"
    "func ^:run;"
"}";

/**********************************************************************************************************************/

vd_t brnd_planted_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "brnd_planted" ) ) )
    {
        case TYPEOF_init1:
        {
            // Comment or remove line below to rebuild this target.
            bcore_const_x_set_d( typeof( "brnd_planted_hash" ), sr_tp( 3325836641 ) );

            // --------------------------------------------------------------------
            // source: brnd_sketch.h

            // group: brnd
            BCORE_REGISTER_TRAIT( brnd, bcore_inst );

            // group: brnd_gen
            BCORE_REGISTER_FEATURE( brnd_gen_max_u3 );
            BCORE_REGISTER_FEATURE( brnd_gen_min_u3 );
            BCORE_REGISTER_FEATURE( brnd_gen_gen_u3 );
            BCORE_REGISTER_FEATURE( brnd_gen_gen_f3 );
            BCORE_REGISTER_FEATURE( brnd_gen_reseed );
            BCORE_REGISTER_SPECT( brnd_gen );

            // group: brnd_test
            BCORE_REGISTER_FEATURE( brnd_test_run );
            BCORE_REGISTER_SPECT( brnd_test );

            // --------------------------------------------------------------------
            // source: brnd_eval.h

            // group: brnd_eval
            BCORE_REGISTER_OBJECT( brnd_eval_result_s );
            BCORE_REGISTER_FEATURE( brnd_eval_run );
            BCORE_REGISTER_FFUNC( bcore_inst_call_init_x, brnd_eval_param_s_init_x );
            BCORE_REGISTER_OBJECT( brnd_eval_param_s );
            BCORE_REGISTER_FEATURE( brnd_eval_set_param );
            BCORE_REGISTER_OBJECT( brnd_eval_arr_s );
            BCORE_REGISTER_FFUNC( brnd_eval_set_param, brnd_eval_set_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, brnd_eval_set_s_main );
            BCORE_REGISTER_FFUNC( brnd_eval_run, brnd_eval_set_s_run );
            BCORE_REGISTER_OBJECT( brnd_eval_set_s );
            BCORE_REGISTER_FFUNC( brnd_eval_set_param, brnd_eval_show_param_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, brnd_eval_show_param_s_main );
            BCORE_REGISTER_FFUNC( brnd_eval_run, brnd_eval_show_param_s_run );
            BCORE_REGISTER_OBJECT( brnd_eval_show_param_s );
            BCORE_REGISTER_FFUNC( brnd_eval_set_param, brnd_eval_errf_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, brnd_eval_errf_s_main );
            BCORE_REGISTER_FFUNC( brnd_eval_run, brnd_eval_errf_s_run );
            BCORE_REGISTER_OBJECT( brnd_eval_errf_s );
            BCORE_REGISTER_FFUNC( brnd_eval_set_param, brnd_eval_plain_s_set_param );
            BCORE_REGISTER_FFUNC( bcore_main_main, brnd_eval_plain_s_main );
            BCORE_REGISTER_FFUNC( brnd_eval_run, brnd_eval_plain_s_run );
            BCORE_REGISTER_OBJECT( brnd_eval_plain_s );
            BCORE_REGISTER_SPECT( brnd_eval );

            // --------------------------------------------------------------------
            // source: brnd_gen.h

            // group: brnd_gen_stamp
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_count_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_count_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_count_s_gen_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_count_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_count_s_reseed );
            BCORE_REGISTER_OBJECT( brnd_gen_count_s );
            BCORE_REGISTER_TRAIT( brnd_gen_stamp, bcore_inst );

            // group: brnd_gen_lcg
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_lcg_v00_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_lcg_v00_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_lcg_v00_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_lcg_v00_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_lcg_v00_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_lcg_v00_s );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_lcg_v01_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_lcg_v01_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_lcg_v01_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_lcg_v01_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_lcg_v01_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_lcg_v01_s );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_lcg_v02_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_lcg_v02_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_lcg_v02_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_lcg_v02_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_lcg_v02_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_lcg_v02_s );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_lcg_v03_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_lcg_v03_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_lcg_v03_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_lcg_v03_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_lcg_v03_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_lcg_v03_s );
            BCORE_REGISTER_TRAIT( brnd_gen_lcg, brnd_gen_stamp );

            // group: brnd_gen_xsg
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_xsg_v00_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_xsg_v00_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_xsg_v00_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_xsg_v00_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_xsg_v00_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_xsg_v00_s );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_xsg_v01_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_xsg_v01_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_xsg_v01_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_xsg_v01_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_xsg_v01_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_xsg_v01_s );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_xsg_v02_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_xsg_v02_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_xsg_v02_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_xsg_v02_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_xsg_v02_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_xsg_v02_s );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_f3, brnd_gen_xsg_v03_s_gen_f3 );
            BCORE_REGISTER_FFUNC( brnd_gen_max_u3, brnd_gen_xsg_v03_s_max_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_min_u3, brnd_gen_xsg_v03_s_min_u3 );
            BCORE_REGISTER_FFUNC( brnd_gen_reseed, brnd_gen_xsg_v03_s_reseed );
            BCORE_REGISTER_FFUNC( brnd_gen_gen_u3, brnd_gen_xsg_v03_s_gen_u3 );
            BCORE_REGISTER_OBJECT( brnd_gen_xsg_v03_s );
            BCORE_REGISTER_TRAIT( brnd_gen_xsg, brnd_gen_stamp );

            // --------------------------------------------------------------------
            // source: brnd_test.h

            // group: brnd_test_stamp
            BCORE_REGISTER_FFUNC( brnd_test_run, brnd_test_uniform_dist_s_run );
            BCORE_REGISTER_OBJECT( brnd_test_uniform_dist_s );
            BCORE_REGISTER_TRAIT( brnd_test_stamp, bcore_inst );
        }
        break;
        default: break;
    }
    return NULL;
}
