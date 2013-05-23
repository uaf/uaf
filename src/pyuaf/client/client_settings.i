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

%module settings
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/client/settings/clientsettings.h"
#include "uaf/client/settings/baseservicesettings.h"
#include "uaf/client/settings/browsesettings.h"
#include "uaf/client/settings/browsenextsettings.h"
#include "uaf/client/settings/createmonitoreddatasettings.h"
#include "uaf/client/settings/createmonitoredeventssettings.h"
#include "uaf/client/settings/methodcallsettings.h"
#include "uaf/client/settings/monitoreditemsettings.h"
#include "uaf/client/settings/readsettings.h"
#include "uaf/client/settings/sessionsecuritysettings.h"
#include "uaf/client/settings/sessionsettings.h"
#include "uaf/client/settings/subscriptionsettings.h"
#include "uaf/client/settings/translatebrowsepathstonodeidssettings.h"
#include "uaf/client/settings/writesettings.h"
#include "uaf/util/address.h"
#include "uaf/util/referencedescription.h"
#include "uaf/util/modificationinfo.h"
%}


// include common definitions
%include "../pyuaf.i"


// import the EXPORT macro and some numeric typedefs
%import "uaf/client/clientexport.h"
%import "uaf/client/clienthandles.h"


// import the necessary dependencies from pyuaf.util
%import(module="pyuaf.util")                        "uaf/util/util.h"
%import(module="pyuaf.util")                        "uaf/util/stringifiable.h"
%import(module="pyuaf.util")                        "uaf/util/status.h"
%import(module="pyuaf.util.messagesecuritymodes")   "pyuaf/util/util_messagesecuritymodes.i"
%import(module="pyuaf.util.usertokentypes")         "pyuaf/util/util_usertokentypes.i"
%import(module="pyuaf.util.loglevels")              "pyuaf/util/util_loglevels.i"
%import(module="pyuaf.util.applicationtypes")       "pyuaf/util/util_applicationtypes.i"
%import(module="pyuaf.util.attributeids")           "pyuaf/util/util_attributeids.i"
%import(module="pyuaf.util.constants")              "pyuaf/util/util_constants.i"
%import(module="pyuaf.util.nodeididentifiertypes")  "pyuaf/util/util_nodeididentifiertypes.i"
%import(module="pyuaf.util.statuscodes")            "pyuaf/util/util_statuscodes.i"
%import(module="pyuaf.util.opcuatypes")             "pyuaf/util/util_opcuatypes.i"
%import(module="pyuaf.util.opcuaidentifiers")       "pyuaf/util/util_opcuaidentifiers.i"
%import(module="pyuaf.util.primitives")             "pyuaf/util/util_primitives.i"
%import(module="pyuaf.util.securitypolicies")       "pyuaf/util/util_securitypolicies.i"
%import(module="pyuaf.util.monitoringmodes")        "pyuaf/util/util_monitoringmodes.i"
%import(module="pyuaf.util.browsedirections")       "pyuaf/util/util_browsedirections.i"
%import(module="pyuaf.util.nodeclasses")            "pyuaf/util/util_nodeclasses.i"
%import(module="pyuaf.util.timestampstoreturn")     "pyuaf/util/util_timestampstoreturn.i"
%import(module="pyuaf.util.__unittesthelper__")     "pyuaf/util/util___unittesthelper__.i"
%import(module="pyuaf.util")                        "pyuaf/util/util___init__.i"


// also include the typemaps
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
    %include "pyuaf/util/util_variant_python.i"
#endif


// before including any classes in a generic way, specify the "special treatments" of certain classes:
%ignore uafc::MonitoredItemSettings::operator=;


// wrap the classes:
UAF_WRAP_CLASS("uaf/client/settings/clientsettings.h"                        , uafc , ClientSettings                        , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/baseservicesettings.h"                   , uafc , BaseServiceSettings                   , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/sessionsecuritysettings.h"               , uafc , SessionSecuritySettings               , COPY_YES, TOSTRING_YES, COMP_NO,   pyuaf.client.settings, SessionSecuritySettingsVector)
UAF_WRAP_CLASS("uaf/client/settings/sessionsettings.h"                       , uafc , SessionSettings                       , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/subscriptionsettings.h"                  , uafc , SubscriptionSettings                  , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/monitoreditemsettings.h"                 , uafc , MonitoredItemSettings                 , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/readsettings.h"                          , uafc , ReadSettings                          , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/writesettings.h"                         , uafc , WriteSettings                         , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/methodcallsettings.h"                    , uafc , MethodCallSettings                    , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/translatebrowsepathstonodeidssettings.h" , uafc , TranslateBrowsePathsToNodeIdsSettings , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/browsesettings.h"                        , uafc , BrowseSettings                        , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/browsenextsettings.h"                    , uafc , BrowseNextSettings                    , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/createmonitoreddatasettings.h"           , uafc , CreateMonitoredDataSettings           , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/createmonitoredeventssettings.h"         , uafc , CreateMonitoredEventsSettings         , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)


// create the SpecificSessionSettings and SpecificSubscriptionSettings
%template(SpecificSessionSettings) std::map<std::string, uafc::SessionSettings>;
%template(SpecificSubscriptionSettings) std::map<std::string, uafc::SubscriptionSettings>;

