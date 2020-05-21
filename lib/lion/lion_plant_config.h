/** Copyright 2020 Johannes Bernhard Steffens
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

#ifndef LION_PLANT_CONFIG_H
#define LION_PLANT_CONFIG_H

#include "bcore_std.h"
#include "lion_planted.h"

#include "lion_root.h"
#include "lion_nop.h"
#include "lion_eval_nop.h"
#include "lion_sem.h"
#include "lion_net.h"
#include "lion_frame.h"
#include "lion_eval_frame.h"
#include "lion_adaptive.h"
#include "lion_adaptive_bhpt.h"
#include "lion_adaptor.h"

BETH_PLANT_CONFIG_OPEN_PLANT( lion )
BETH_PLANT_CONFIG_USE_GROUP( lion_root );
BETH_PLANT_CONFIG_USE_GROUP( lion_nop );
BETH_PLANT_CONFIG_USE_GROUP( lion_eval_nop );
BETH_PLANT_CONFIG_USE_GROUP( lion_sem );
BETH_PLANT_CONFIG_USE_GROUP( lion_net );
BETH_PLANT_CONFIG_USE_GROUP( lion_frame );
BETH_PLANT_CONFIG_USE_GROUP( lion_eval_frame );
BETH_PLANT_CONFIG_USE_GROUP( lion_adaptive );
BETH_PLANT_CONFIG_USE_GROUP( lion_adaptor );
BETH_PLANT_CONFIG_USE_GROUP( lion_adaptive_bhpt );
BETH_PLANT_CONFIG_CLOSE_PLANT( lion )

#endif  // LION_PLANT_CONFIG_H
