/* This file is part of the UAF (Unified Architecture Framework) project.
 *
 * Copyright (C) 2012 Wim Pessemier (Institute of Astronomy, KULeuven)
 *
 * Project website: http://www.ster.kuleuven.be/uaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UAFC_CONFIGS_H_
#define UAFC_CONFIGS_H_

// STD
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/configs/baseserviceconfig.h"
#include "uaf/client/settings/readsettings.h"
#include "uaf/client/settings/writesettings.h"
#include "uaf/client/settings/methodcallsettings.h"
#include "uaf/client/settings/createmonitoreddatasettings.h"
#include "uaf/client/settings/createmonitoredeventssettings.h"
#include "uaf/client/settings/translatebrowsepathstonodeidssettings.h"
#include "uaf/client/settings/browsesettings.h"
#include "uaf/client/settings/browsenextsettings.h"





#define DEFINE_CONFIG(NAME)                                                         \
/** Config class holding the service settings and the address resolution settings.  \
 *                                                                                  \
 * @ingroup ClientConfigs */ \
typedef UAFC_EXPORT uafc::BaseServiceConfig< uafc::NAME##Settings > NAME##Config;


namespace uafc
{
    DEFINE_CONFIG(Read)
    DEFINE_CONFIG(Write)
    DEFINE_CONFIG(MethodCall)
    DEFINE_CONFIG(Browse)
    DEFINE_CONFIG(BrowseNext)
    DEFINE_CONFIG(TranslateBrowsePathsToNodeIds)
    DEFINE_CONFIG(CreateMonitoredData)
    DEFINE_CONFIG(CreateMonitoredEvents)

}


#endif /* UAFC_CONFIGS_H_ */
