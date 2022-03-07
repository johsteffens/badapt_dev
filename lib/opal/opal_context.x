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

// ---------------------------------------------------------------------------------------------------------------------

feature m bcore_prsg* get_prsg( m @* o )   { ERR_fa( "Feature is not implemented in #<sc_t>.", ifnameof( o->_ ) ); return NULL; };
feature sc_t   nameof( c @* o, tp_t name ) { ERR_fa( "Feature is not implemented in #<sc_t>.", ifnameof( o->_ ) ); return NULL; };
feature sc_t ifnameof( c @* o, tp_t name ) { ERR_fa( "Feature is not implemented in #<sc_t>.", ifnameof( o->_ ) ); return NULL; };
feature tp_t   typeof( c @* o, sc_t name ) { ERR_fa( "Feature is not implemented in #<sc_t>.", ifnameof( o->_ ) ); return 0; };
feature tp_t entypeof( m @* o, sc_t name ) { ERR_fa( "Feature is not implemented in #<sc_t>.", ifnameof( o->_ ) ); return 0; };

// ---------------------------------------------------------------------------------------------------------------------

/**********************************************************************************************************************/
