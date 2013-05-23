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

%module configs
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/client/configs/baseserviceconfig.h"
#include "uaf/client/configs/configs.h"
#include "uaf/client/configs/sessionconfig.h"
#include "uaf/client/configs/subscriptionconfig.h"
#include "uaf/client/settings/monitoreditemsettings.h"
#include "uaf/client/settings/clientsettings.h"
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
%import(module="pyuaf.util.attributeids")       "pyuaf/util/util_attributeids.i"
%import(module="pyuaf.util.monitoringmodes")    "pyuaf/util/util_monitoringmodes.i"
%import(module="pyuaf.util.primitives")         "pyuaf/util/util_primitives.i"
%import(module="pyuaf.util.browsedirections")   "pyuaf/util/util_browsedirections.i"
%import(module="pyuaf.util.nodeclasses")        "pyuaf/util/util_nodeclasses.i"
%import(module="pyuaf.util.timestampstoreturn") "pyuaf/util/util_timestampstoreturn.i"
%import(module="pyuaf.util")                    "uaf/util/stringifiable.h"
%import(module="pyuaf.util")                    "uaf/util/browsepath.h"


// also include the typemaps
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
    %include "pyuaf/util/util_variant_python.i"
#endif


// also import the wrapped xxxxSettings classes
%import "pyuaf/client/client_settings.i"


// wrap some configs that are not defined by macros:
UAF_WRAP_CLASS("uaf/client/configs/baseserviceconfig.h"  , uafc , BaseServiceConfig  , COPY_NO, TOSTRING_YES, COMP_NO,  pyuaf.client.configs, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/configs/sessionconfig.h"      , uafc , SessionConfig      , COPY_NO, TOSTRING_YES, COMP_NO,  pyuaf.client.configs, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/configs/subscriptionconfig.h" , uafc , SubscriptionConfig , COPY_NO, TOSTRING_YES, COMP_NO,  pyuaf.client.configs, VECTOR_NO)


// define a macro to create the service configs (which are just typedefs)
%define CREATE_UAFC_CONFIG(SERVICE)
    %template(SERVICE##Config) uafc::BaseServiceConfig< uafc::SERVICE##Settings >;
%enddef


// create the service configs
CREATE_UAFC_CONFIG(Read)
CREATE_UAFC_CONFIG(Write)
CREATE_UAFC_CONFIG(MethodCall)
CREATE_UAFC_CONFIG(TranslateBrowsePathsToNodeIds)
CREATE_UAFC_CONFIG(Browse)
CREATE_UAFC_CONFIG(BrowseNext)
CREATE_UAFC_CONFIG(HistoryReadRawModified)
CREATE_UAFC_CONFIG(CreateMonitoredData)
CREATE_UAFC_CONFIG(CreateMonitoredEvents)


// include configs header
%include "uaf/client/configs/configs.h"
