/** Copyright 2019 Johannes Bernhard Steffens
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "bcore_std.h"
#include "bmath_std.h"
#include "bmath_plot.h"
#include "badapt_mlp.h"
#include "badapt_test.h"

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------
#ifdef TYPEOF_badapt_mlp_s
sz_t badapt_mlp_s_get_in_size(  const badapt_mlp_s* o )
{
    return o->input_size;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_set_in_size( badapt_mlp_s* o, sz_t size )
{
    if( o->input_size != size )
    {
        o->input_size = size;
        badapt_mlp_s_reset( o );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

sz_t badapt_mlp_s_get_out_size( const badapt_mlp_s* o )
{
    return o->output_kernels;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_set_out_size( badapt_mlp_s* o, sz_t size )
{
    if( o->output_kernels != size )
    {
        o->output_kernels = size;
        badapt_mlp_s_reset( o );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

f3_t badapt_mlp_s_get_rate( const badapt_mlp_s* o )
{
    return o->epsilon / o->epsilon_rate;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_set_rate( badapt_mlp_s* o, f3_t val )
{
    o->epsilon = val * o->epsilon_rate;
}

// ---------------------------------------------------------------------------------------------------------------------

f3_t badapt_mlp_s_get_lambda_l1( const badapt_mlp_s* o )
{
    return o->lambda_l1;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_set_lambda_l1( badapt_mlp_s* o, f3_t val )
{
    o->lambda_l1 = val;
}

// ---------------------------------------------------------------------------------------------------------------------

f3_t badapt_mlp_s_get_lambda_l2( const badapt_mlp_s* o )
{
    return o->lambda_l2;
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_set_lambda_l2( badapt_mlp_s* o, f3_t val )
{
    o->lambda_l2 = val;
}

// ---------------------------------------------------------------------------------------------------------------------

/// Preserves weights if already initialized, otherwise randomly initializes weights
void badapt_mlp_s_setup( badapt_mlp_s* o )
{
    bl_t learning = true;
    ASSERT( o->layers >= 2 );

    if( !bcore_trait_is_of( sr_s_type( &o->act_mid ), TYPEOF_badapt_activator ) ) ERR_fa( "act_mid: '#<sc_t>' is not of badapt_activator", ifnameof( sr_s_type( &o->act_mid ) ) );
    if( !bcore_trait_is_of( sr_s_type( &o->act_out ), TYPEOF_badapt_activator ) ) ERR_fa( "act_out: '#<sc_t>' is not of badapt_activator", ifnameof( sr_s_type( &o->act_out ) ) );

    BCORE_LIFE_INIT();

    typedef struct
    {
        sz_t size;
        sz_t kernels;
    } bmath_snn_arc_item_s;

    sc_t bmath_snn_arc_item_s_def =
    "{"
        "sz_t size;"
        "sz_t kernels;"
    "}";

    tp_t typeof_bmath_snn_arc_item_s = bcore_flect_type_parse_fa( "bmath_snn_arc_item_s = #<sc_t>;", bmath_snn_arc_item_s_def );
    tp_t typeof_arr_bmath_snn_arc_item_s = bcore_flect_type_parse_fa( "{ aware_t _; bmath_snn_arc_item_s [] arr; };" );
    bcore_array* arr_bmath_snn_arc_item_s = BCORE_LIFE_A_PUSH( bcore_inst_t_create( typeof_arr_bmath_snn_arc_item_s ) );

    bmath_snn_arc_item_s item = { 0 };

    f3_t kernels = o->input_kernels;

    // first layer
    {
        item.size    = o->input_size;
        item.kernels = lrint( kernels );
        bcore_array_a_push( arr_bmath_snn_arc_item_s, sr_twc( typeof_bmath_snn_arc_item_s, &item ) );
    }

    for( sz_t i = 1; i < o->layers - 1; i++ )
    {
        kernels *= ( 1.0 + o->kernels_rate );
        sz_t prev_kernels = item.kernels;
        item.size         = prev_kernels;
        item.kernels      = lrint( kernels );
        ASSERT( item.kernels > 0 );
        bcore_array_a_push( arr_bmath_snn_arc_item_s, sr_twc( typeof_bmath_snn_arc_item_s, &item ) );
    }

    // last layer
    {
        const bmath_snn_arc_item_s* last_item = bcore_array_a_get_last( arr_bmath_snn_arc_item_s ).o;
        item = *last_item;
        sz_t prev_kernels = item.kernels;
        item.size  = prev_kernels;
        item.kernels = o->output_kernels;
        bcore_array_a_push( arr_bmath_snn_arc_item_s, sr_twc( typeof_bmath_snn_arc_item_s, &item ) );
    }

    bmath_arr_vf3_s_set_size( &o->arr_a, o->layers );
    bmath_arr_vf3_s_set_size( &o->arr_b, o->layers );

    // preexisting weights are reused
    if( o->arr_w.size != o->layers )
    {
        bmath_arr_mf3_s_clear( &o->arr_w );
        bmath_arr_mf3_s_set_size( &o->arr_w, o->layers );
    }

    sz_t buf_full_size = o->input_size;
    o->max_buffer_size = 0;

    // preexisting activators are reused
    if( o->arr_activator.size != o->layers )
    {
        bcore_arr_sr_s_set_size( &o->arr_activator, o->layers );
        for( sz_t i = 0; i < o->layers; i++ )
        {
            sr_s_copy( &o->arr_activator.data[ i ], ( i < o->layers - 1 ) ? &o->act_mid : &o->act_out );
        }
    }

    // set up matrices
    for( sz_t i = 0; i < o->layers; i++ )
    {
        badapt_activator_r_setup( &o->arr_activator.data[ i ] );

        const bmath_snn_arc_item_s* item = bcore_array_a_get( arr_bmath_snn_arc_item_s, i ).o;

        bmath_vf3_s* a  = &o->arr_a.data[ i ];
        bmath_vf3_s* b  = &o->arr_b.data[ i ];
        bmath_mf3_s* w  = &o->arr_w.data[ i ];

        a->size   = item->size;
        a->space  = 0; // not owning data
        b->size   = item->kernels;
        b->space  = 0; // not owning data

        if( w->size == 0 )
        {
            bmath_mf3_s_set_size( w, item->kernels, item->size );
            bmath_mf3_s_set_random( w, false, false, 0, 1.0, -0.5, 0.5, &o->random_state );
        }
        else
        {
            ASSERT( w->rows == item->kernels );
            ASSERT( w->cols == item->size );
        }

        buf_full_size += b->size;
        o->max_buffer_size = sz_max( o->max_buffer_size, a->size );
        o->max_buffer_size = sz_max( o->max_buffer_size, b->size );
    }

    bcore_arr_sr_s_set_spect( &o->arr_activator, TYPEOF_badapt_activator_s );

    sz_t buf_part_size = o->max_buffer_size * 2;

    if( learning )
    {
        bmath_vf3_s_set_size( &o->buf_ab,  buf_full_size );
    }
    else
    {
        bmath_vf3_s_set_size( &o->buf_ab, buf_part_size );
    }

    sz_t buf_index = 0;

    // distribute buffer space
    for( sz_t i = 0; i < o->layers; i++ )
    {
        bl_t even_layer = ( ( i & 1 ) == 0 );

        bmath_vf3_s* a  = &o->arr_a.data[ i ];
        bmath_vf3_s* b  = &o->arr_b.data[ i ];

        if( learning )
        {
            a->data = o->buf_ab.data + buf_index;
            b->data = o->buf_ab.data + buf_index + a->size;
        }
        else
        {
            a->data =  even_layer ? o->buf_ab.data : o->buf_ab.data + o->max_buffer_size;
            b->data = !even_layer ? o->buf_ab.data : o->buf_ab.data + o->max_buffer_size;
        }

        buf_index += a->size;

        ASSERT( a->data - o->buf_ab.data + a->size <= o->buf_ab.size );
        ASSERT( b->data - o->buf_ab.data + b->size <= o->buf_ab.size );

        // first layer
        if( i == 0 )
        {
            bmath_vf3_s_clear( &o->in );
            o->in.data = a->data;
            o->in.size = o->input_size;
        }

        // last layer
        if( i == o->layers - 1 )
        {
            bmath_vf3_s_clear( &o->out );
            o->out.data = b->data;
            o->out.size = o->output_kernels;
        }
    }

    if( o->epsilon < 0 ) o->epsilon = o->epsilon_rate;

    BCORE_LIFE_DOWN();
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_reset( badapt_mlp_s* o )
{
    bmath_arr_mf3_s_clear( &o->arr_w );
    bmath_arr_vf3_s_clear( &o->arr_a );
    bmath_arr_vf3_s_clear( &o->arr_b );
    bmath_vf3_s_clear( &o->buf_ab );
    bmath_vf3_s_clear( &o->in );
    bmath_vf3_s_clear( &o->out );
    bcore_arr_sr_s_clear( &o->arr_activator );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_arc_to_sink( const badapt_mlp_s* o, bcore_sink* sink )
{
    sz_t pad = 24;
    sz_t weights = 0;
    sz_t ops = 0;
    for( sz_t i = 0; i < o->arr_w.size; i++ )
    {
        const bmath_mf3_s* w = &o->arr_w.data[ i ];
        weights += w->size;
        ops     += w->size;
    }

    bcore_sink_a_push_fa( sink, "#pn.{input size } #pl3 {#<sz_t>}\n", pad, o->input_size );
    bcore_sink_a_push_fa( sink, "#pn.{input kernels } #pl3 {#<sz_t>}\n", pad, o->input_kernels );
    bcore_sink_a_push_fa( sink, "#pn.{output kernels } #pl3 {#<sz_t>}\n", pad, o->output_kernels );
    bcore_sink_a_push_fa( sink, "#pn.{kernels rate}   #<f3_t>\n", pad, o->kernels_rate );

    bcore_sink_a_push_fa( sink, "#pn.{layers } #pl3 {#<sz_t>}\n",  pad, o->layers );
    bcore_sink_a_push_fa( sink, "#pn.{weights } #pl3 {#<sz_t>}\n", pad, weights );
    bcore_sink_a_push_fa( sink, "#pn.{ops } #pl3 {#<sz_t>}\n",     pad, ops );

    for( sz_t i = 0; i < o->arr_w.size; i++ )
    {
        const bmath_vf3_s* a = &o->arr_a.data[ i ];
        const bmath_mf3_s* w = &o->arr_w.data[ i ];
        const bmath_vf3_s* b = &o->arr_b.data[ i ];
        st_s* st_activation = st_s_create();
        st_s_push_fa( st_activation, "#<sc_t>", ifnameof( sr_s_type( &o->arr_activator.data[ i ] ) ) );
        st_s_push_fa( st_activation, " : #<sc_t>", ifnameof( sr_s_type( badapt_activator_a_get_activation( ( badapt_activator* )o->arr_activator.data[ i ].o ) ) ) );

        bcore_sink_a_push_fa( sink,
                              "layer #pl2 {#<sz_t>}:"
                              " a(#pl2 {#<sz_t>})"
                              " w(#pl2 {#<sz_t>} x #pl2 {#<sz_t>})"
                              " b(#pl2 {#<sz_t>})"
                              " #<sc_t>"
                              "\n",
                            i, a->size, w->rows, w->cols, b->size, st_activation->sc );

        st_s_discard( st_activation );
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_infer( const badapt_mlp_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    if( o->arr_a.size == 0 ) ERR_fa( "Network was not setup. Call setup() first." );
    bmath_vf3_s a, b;
    bmath_vf3_s_init( &a );
    bmath_vf3_s_init( &b );
    bmath_vf3_s_set_space( &a, o->max_buffer_size );
    bmath_vf3_s_set_space( &b, o->max_buffer_size );

    ASSERT( in->size == o->input_size );

    bmath_vf3_s_copy( &a, in );

    for( sz_t i = 0; i < o->arr_w.size; i++ )
    {
        const bmath_mf3_s* w = &o->arr_w.data[ i ];
        b.size = w->rows;
        bmath_mf3_s_mul_vec( w, &a, &b );       // b = w * a
        badapt_activator_r_infer( &o->arr_activator.data[ i ], &b, &b );
        bmath_vf3_s_swapr( &a, &b );
    }

    if( out ) bmath_vf3_s_cpy( &a, out );

    bmath_vf3_s_down( &a );
    bmath_vf3_s_down( &b );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_minfer( badapt_mlp_s* o, const bmath_vf3_s* in, bmath_vf3_s* out )
{
    if( o->arr_a.size == 0 ) ERR_fa( "Network was not setup. Call setup() first." );
    bmath_vf3_s_cpy( in, &o->in );
    for( sz_t i = 0; i < o->arr_w.size; i++ )
    {
        const bmath_vf3_s* a = &o->arr_a.data[ i ];
              bmath_vf3_s* b = &o->arr_b.data[ i ];
        const bmath_mf3_s* w = &o->arr_w.data[ i ];
        bmath_mf3_s_mul_vec( w, a, b );       // b = w * a
        badapt_activator_r_infer( &o->arr_activator.data[ i ], b, b );
    }
    if( out ) bmath_vf3_s_cpy( &o->out, out );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_bgrad( const badapt_mlp_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    ASSERT( grad_out->size == o->output_kernels );

    bmath_vf3_s ga, gb;
    bmath_vf3_s_init( &ga );
    bmath_vf3_s_init( &gb );
    bmath_vf3_s_set_space( &ga, o->max_buffer_size );
    bmath_vf3_s_set_space( &gb, o->max_buffer_size );
    bmath_vf3_s_copy( &gb, grad_out );

    for( sz_t i = o->arr_w.size - 1; i >= 0; i-- )
    {
        const bmath_vf3_s*  b = &o->arr_b.data[ i ];
        const bmath_mf3_s*  w = &o->arr_w.data[ i ];
        ga.size = w->cols;
        badapt_activator_r_bgrad( &o->arr_activator.data[ i ], &gb, &gb, b );
        bmath_mf3_s_htp_mul_vec( w, &gb, &ga );          // GA <- W^T * GB
        bmath_vf3_s_swapr( &ga, &gb );
    }

    if( grad_in ) bmath_vf3_s_cpy( &gb, grad_in );

    bmath_vf3_s_down( &ga );
    bmath_vf3_s_down( &gb );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_bgrad_adapt( badapt_mlp_s* o, bmath_vf3_s* grad_in, const bmath_vf3_s* grad_out )
{
    ASSERT( grad_out->size == o->output_kernels );

    bmath_vf3_s ga, gb;
    bmath_vf3_s_init( &ga );
    bmath_vf3_s_init( &gb );
    bmath_vf3_s_set_space( &ga, o->max_buffer_size );
    bmath_vf3_s_set_space( &gb, o->max_buffer_size );
    bmath_vf3_s_copy( &gb, grad_out );

    for( sz_t i = o->arr_w.size - 1; i >= 0; i-- )
    {
        const bmath_vf3_s*  a = &o->arr_a.data[ i ];
        const bmath_vf3_s*  b = &o->arr_b.data[ i ];
              bmath_mf3_s*  w = &o->arr_w.data[ i ];

        ga.size = w->cols;

        badapt_activator_r_adapt( &o->arr_activator.data[ i ], &gb, &gb, b, o->epsilon );
        bmath_mf3_s_htp_mul_vec( w, &gb, &ga );          // GA <- W^T * GB


        f3_t l2_reg_factor = ( 1.0 - o->lambda_l2  * o->epsilon );
        f3_t l1_reg_offset = o->lambda_l1 * o->epsilon;

        for( sz_t i = 0; i < w->rows; i++ )
        {
            f3_t* wr = w->data + i * w->stride;
            f3_t gi = o->epsilon * gb.data[ i ];
            for( sz_t j = 0; j < w->cols; j++ ) wr[ j ] = ( wr[ j ] + a->data[ j ] * gi ) * l2_reg_factor;
            if( l1_reg_offset > 0 )
            {
                for( sz_t j = 0; j < w->cols; j++ ) wr[ j ] += ( wr[ j ] > 0 ) ? -l1_reg_offset : l1_reg_offset;
            }
        }

        bmath_vf3_s_swapr( &ga, &gb );
    }

    if( grad_in ) bmath_vf3_s_cpy( &gb, grad_in );

    bmath_vf3_s_down( &ga );
    bmath_vf3_s_down( &gb );
}

// ---------------------------------------------------------------------------------------------------------------------

void badapt_mlp_s_decay( badapt_mlp_s* o, f3_t decay )
{
    f3_t f = ( 1.0 - decay );
    f = f3_max( 0, f );
    for( sz_t i = 0; i < o->arr_w.size; i++ ) bmath_mf3_s_mul_scl_f3( &o->arr_w.data[ i ], f, &o->arr_w.data[ i ] );
}

// ---------------------------------------------------------------------------------------------------------------------

static void selftest()
{
    BCORE_LIFE_INIT();
    BCORE_LIFE_CREATE( badapt_mlp_s, mlp );

    mlp->input_kernels = 32;
    mlp->layers = 8;
    mlp->kernels_rate = 0;
    mlp->random_state = 124;

    mlp->act_mid = sr_asd( badapt_activator_bias_s_create_activation( sr_create( TYPEOF_badapt_activation_leaky_relu_s ) ) );
    mlp->act_out = sr_asd( badapt_activator_bias_s_create_activation( sr_create( TYPEOF_badapt_activation_tanh_s       ) ) );

    badapt_mlp_s_arc_to_sink( mlp, BCORE_STDOUT );

    badapt_adaptive_a_test_sine_random( ( badapt_adaptive* )mlp );

    BCORE_LIFE_RETURN();
}

#endif

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

vd_t badapt_mlp_signal_handler( const bcore_signal_s* o )
{
    switch( bcore_signal_s_handle_type( o, typeof( "badapt_mlp" ) ) )
    {
        case TYPEOF_init1:
        {
        }
        break;

        case TYPEOF_selftest:
        {
            selftest();
        }
        break;

        case TYPEOF_precoder:
        {
            bcore_precoder_compile( "badapt_precoded", __FILE__ );
        }
        break;

        default: break;
    }

    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/


