/** Author and Copyright 2020 Johannes Bernhard Steffens
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

/**********************************************************************************************************************/

/// The adaptor defines a method for updating adaptive holors from accumulated gradients.

/**********************************************************************************************************************/

// ---------------------------------------------------------------------------------------------------------------------

stamp :frame_s = aware bhpt_adaptor
{
    /// source should define cell ( axon_out, grad_out <- axon_in, grad_in ) { ... };
    aware x_inst => src; // source (bcore_file_path_s or st_s with inline code)

    hidden opal_frame_s => frame;

    func bhpt_adaptor.reset = { if( o.frame ) o.frame.cyclic_reset(); };
    func bhpt_adaptor.adapt;
};

// ---------------------------------------------------------------------------------------------------------------------

func (:frame_s) bhpt_adaptor.adapt =
{
    if( !o.frame )
    {
        m bcore_source* source = NULL;

        switch( o.src._ )
        {
            case bcore_file_path_s~:
            {
                source = bcore_file_open_source_path( o.src.cast( c bcore_file_path_s* ) )^^;
            }
            break;

            case st_s~:
            {
                source = bcore_source_string_s_create_from_string( o.src.cast( c st_s* ) )^^;
            }
            break;

            default:
            {
                ERR_fa( "Invalid source type '#<sc_t>'.", ifnameof( *(aware_t*)o.src ) );
            }
            break;
        }

        o.frame = opal_frame_s!;
        o.frame.setup_from_source( source, verbatim_C{ ( const bhvm_holor_s*[] ){ node->axon, node->grad } }, 2 );

        ASSERT( o.frame.get_size_en() == 2 );
        ASSERT( o.frame.get_size_ex() == 2 );
    }

    o.frame.run_axon_pass
    (
        verbatim_C{ ( const bhvm_holor_s*[] ){ node->axon, node->grad } },
        2,
        verbatim_C{ ( bhvm_holor_s*[] ){ node->axon, node->grad } },
        2
    );
};

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/

