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

/// Context framework

/**********************************************************************************************************************/

#ifndef OPAL_CONTEXT_H
#define OPAL_CONTEXT_H

#include "bcore_std.h"
#include "opal_xoila_out.h"

/**********************************************************************************************************************/

#define OPAL_CONTEXT_ERR_NOT_IMPLEMENTED() ERR_fa( "Feature is not implemented in #<sc_t>.", ifnameof( o->_ ) );

XOILA_DEFINE_GROUP( opal_context, bcore_inst )
#ifdef XOILA_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

feature 'a' bcore_prsg* get_prsg( mutable )     = { OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return NULL; };
feature 'a' sc_t   nameof(   const, tp_t name ) = { OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return NULL; };
feature 'a' sc_t ifnameof(   const, tp_t name ) = { OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return NULL; };
feature 'a' tp_t   typeof(   const, sc_t name ) = { OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return 0; };
feature 'a' tp_t entypeof( mutable, sc_t name ) = { OPAL_CONTEXT_ERR_NOT_IMPLEMENTED(); return 0; };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // XOILA_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // OPAL_CONTEXT_H
