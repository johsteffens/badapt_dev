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

#ifndef OPAL_SEM_H
#define OPAL_SEM_H

/**********************************************************************************************************************/

/// Syntax & Semantic

/**********************************************************************************************************************/

/**
 *  Symbolic language to describe a graph of operators on holors.
 *
 *  Semantic Cell Concept:
 *  A semantic graph communicates with the objects outside its body through input an output channels.
 *  All links of a graph 'x' to outside objects the node must pass though an input channel of 'x'.
 *  Inside objects may not be referenced directly by outside objects.
 *  A graph adhering to this concept is called 'cell'
 *  A construction of a new graph must conclude with converting it to a cell.
 *  Cells can be used as objects for constructing new graphs.
 *
 *  Static Links:
 *  Defined links of an input channel of a semantic graph are never changed or freed again.
 *  Different use cases of a graph are achieved by creating graph-copies and assigning links of those copies differently.
 *
 *  Binary operators:
 *  Binary operators have a priority-level. Higher priority is resolved before lower priority.
 *
 *  Available binary operators
 *  Symbol  Notation Priority  Type
 *   :      Infix      6     Constructive Concatenation
 *  ::      Infix      8     Conservative Concatenation
 *  <:      Infix            Cell Catenation
 *   [      Infix     21     order-increment bin operator (l-value: dim). (Yielding) Example: 2[# = (#:#), 2[2[# = (#:#):(#:#)
 *   ]      Infix     20     order-decrement bin operator (r-value: idx). Example: (1:2:3)]1 = 2
 *   +      Infix      8     (ECI) addition
 *   -      Infix      8     (ECI) subtraction
 *   *      Infix     10     (ECI) multiplication
 *   /      Infix     10     (ECI) division
 *   ^      Infix     12     (ECI) power
 *  **,     Infix     10     holor-product for holors up to order 2; transposition state is considered
 *  *~      Infix     10     convolution?
 *
 *  Unary operators
 *  -     Prefix       8     negates holor
 *  ~     Postfix     12     toggles transposition state (represents a reinterpret cast) (priority must be above multiplication)
 *
 *  Holors
 *    #   Vacant scalar
 *    7   Determined Scalar
 *
 *  Dendpass-Algorithm:
 *  specific method to compute the local gradient via automatic differentiation
 *  using reverse accumulation to backpropagate gradients:
 *  - Each node holds a gradient holor of same shape as its output holor
 *  - The gradient holor represents the gradient with respect to the last input given the current state of the network.
 *  - The backpass algorithm for a specific node computes the gradient through a specific node-channel and adds it to (accumulates)
 *    the gradient of the node linked to the input channel. This step is done by s singe virtual operation.
 *  - The backpass procedure is compiled by recursively passing each node starting from the adaptive node downward through
 *    all downlinks.
 *
 *  More details: See opal_design.txt
 */

/**********************************************************************************************************************/

#include "bmath_std.h"
#include "opal.xo.h"

/**********************************************************************************************************************/

BCORE_FORWARD_OBJECT( opal_sem_context_s );

/// returns global context
opal_sem_context_s* opal_sem_get_context( void );

//XOILA_DEFINE_GROUP( opal_sem, x_inst )
//#ifdef XOILA_SECTION
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//
//// ---------------------------------------------------------------------------------------------------------------------
//
//embed "opal_sem.x";
//
//#endif // XOILA_SECTION

/**********************************************************************************************************************/

#endif // OPAL_SEM_H
