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

/** Semantic Cell Unique Identifier
 *  String based identifier used to associate an element (cell, node, holor) with a unique location
 *  in the semantic tree structure of cells.
 */

/**********************************************************************************************************************/

#ifndef OPAL_SCID_H
#define OPAL_SCID_H

#include "bhvm_holor.h"
#include "bhvm_mcode.h"
#include "opal_planted.h"

/**********************************************************************************************************************/

BETH_PLANT_DEFINE_GROUP( opal_scid, bcore_inst )
#ifdef PLANT_SECTION // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

signature void clear(       mutable );
signature void set(         mutable, sc_t sc );
signature void push_child(  mutable, sc_t sc );
signature void push_parent( mutable, sc_t sc );

stamp : = aware :
{
    st_s st;
    func : :clear       = { st_s_clear(     &o->st ); };
    func : :set         = { st_s_copy_sc(   &o->st, sc ); };
    func : :push_child  = { st_s_push_fa(   &o->st,    ".#<sc_t>", sc ); };
    func : :push_parent = { st_s_insert_fa( &o->st, 0, "#<sc_t>.", sc ); };
};

/// for use in other objects
signature void get_scid( const, :s* scid );

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#endif // PLANT_SECTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**********************************************************************************************************************/

#endif // OPAL_SCID_H
