/** Author and Copyright 2019 Johannes Bernhard Steffens
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

/// node operator

/**********************************************************************************************************************/

#ifndef OPAL_NOP_H
#define OPAL_NOP_H

#include "bmath_std.h"
#include "bhvm_mcode.h"
#include "opal_holor.h"
#include "opal_context.h"
#include "opal.xo.h"

/**********************************************************************************************************************/

BCORE_FORWARD_OBJECT( opal_net_node_s );
BCORE_FORWARD_OBJECT( opal_net_node_adl_s );

XOILA_DEFINE_GROUP( opal_nop, bcore_inst, "opal_nop.x" )

/**********************************************************************************************************************/

#endif // OPAL_NOP_H
