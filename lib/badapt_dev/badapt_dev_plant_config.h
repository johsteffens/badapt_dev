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

#ifndef BADAPT_DEV_PLANT_CONFIG_H
#define BADAPT_DEV_PLANT_CONFIG_H

#include "bcore_std.h"
#include "badapt_dev_planted.h"
#include "badapt_dev_problem.h"
#include "badapt_dev_ern.h"
#include "badapt_dev_lstm.h"

BETH_PLANT_CONFIG_OPEN_PLANT( badapt_dev )
BETH_PLANT_CONFIG_USE_GROUP( badapt_dev_problem );
BETH_PLANT_CONFIG_USE_GROUP( badapt_dev_ern );
BETH_PLANT_CONFIG_USE_GROUP( badapt_dev_lstm );
BETH_PLANT_CONFIG_CLOSE_PLANT( badapt_dev )

#endif  // BADAPT_DEV_PLANT_CONFIG_H
