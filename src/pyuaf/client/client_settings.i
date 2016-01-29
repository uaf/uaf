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
#include "uaf/client/settings/servicesettings.h"
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
#include "uaf/client/settings/historyreadrawmodifiedsettings.h"
#include "uaf/util/address.h"
#include "uaf/util/referencedescription.h"
#include "uaf/util/modificationinfo.h"
%}


// include common definitions
%include "../pyuaf.i"


// import the EXPORT macro and some numeric typedefs
%import "uaf/util/util.h"
%import "uaf/util/handles.h"


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
%import(module="pyuaf.util.opcuaidentifiers")       "pyuaf/util/util_opcuastatuscodes.i"
%import(module="pyuaf.util.primitives")             "pyuaf/util/util_primitives.i"
%import(module="pyuaf.util.securitypolicies")       "pyuaf/util/util_securitypolicies.i"
%import(module="pyuaf.util.serverstates")           "pyuaf/util/util_serverstates.i"
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
%ignore uaf::MonitoredItemSettings::operator=;


// wrap the classes:
UAF_WRAP_CLASS("uaf/client/settings/clientsettings.h"                        , uaf , ClientSettings                        , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/servicesettings.h"                       , uaf , ServiceSettings                       , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/sessionsecuritysettings.h"               , uaf , SessionSecuritySettings               , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/sessionsettings.h"                       , uaf , SessionSettings                       , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/subscriptionsettings.h"                  , uaf , SubscriptionSettings                  , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/monitoreditemsettings.h"                 , uaf , MonitoredItemSettings                 , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/readsettings.h"                          , uaf , ReadSettings                          , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/writesettings.h"                         , uaf , WriteSettings                         , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/historyreadrawmodifiedsettings.h"        , uaf , HistoryReadRawModifiedSettings        , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/methodcallsettings.h"                    , uaf , MethodCallSettings                    , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/translatebrowsepathstonodeidssettings.h" , uaf , TranslateBrowsePathsToNodeIdsSettings , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/browsesettings.h"                        , uaf , BrowseSettings                        , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/browsenextsettings.h"                    , uaf , BrowseNextSettings                    , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/createmonitoreddatasettings.h"           , uaf , CreateMonitoredDataSettings           , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/settings/createmonitoredeventssettings.h"         , uaf , CreateMonitoredEventsSettings         , COPY_YES, TOSTRING_YES, COMP_YES,  pyuaf.client.settings, VECTOR_NO)


// create the SpecificSessionSettings and SpecificSubscriptionSettings
%template(SpecificSessionSettings) std::map<std::string, uaf::SessionSettings>;
%template(SpecificSubscriptionSettings) std::map<std::string, uaf::SubscriptionSettings>;

