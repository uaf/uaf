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

%module (directors="1", "threads"=1) __init__
// Directors are enabled to implement the callbacks for the 
// asynchronous communication.
// Threads must also be enabled, because the overridden callbacks 
// are called from multiple C++ threads 

%{
#define SWIG_FILE_WITH_INIT
#include "uaf/client/client.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientinterface.h"
#include "uaf/client/requests/basesessionrequesttarget.h"
#include "uaf/client/requests/basesubscriptionrequesttarget.h"
#include "uaf/client/requests/createmonitoreddatarequesttarget.h"
#include "uaf/client/requests/createmonitoredeventsrequesttarget.h"
#include "uaf/client/requests/methodcallrequesttarget.h"
#include "uaf/client/requests/readrequesttarget.h"
#include "uaf/client/requests/browserequesttarget.h"
#include "uaf/client/requests/browsenextrequesttarget.h"
#include "uaf/client/requests/translatebrowsepathstonodeidsrequesttarget.h"
#include "uaf/client/requests/writerequesttarget.h"
#include "uaf/client/requests/historyreadrawmodifiedrequesttarget.h"
#include "uaf/client/requests/basesessionrequest.h"
#include "uaf/client/requests/basesubscriptionrequest.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/asyncresulttarget.h"
#include "uaf/client/results/basesessionresult.h"
#include "uaf/client/results/basesubscriptionresult.h"
#include "uaf/client/results/basesessionresulttarget.h"
#include "uaf/client/results/basesubscriptionresulttarget.h"
#include "uaf/client/results/createmonitoreddataresulttarget.h"
#include "uaf/client/results/createmonitoredeventsresulttarget.h"
#include "uaf/client/results/methodcallresulttarget.h"
#include "uaf/client/results/readresulttarget.h"
#include "uaf/client/results/browseresulttarget.h"
#include "uaf/client/results/browsenextresulttarget.h"
#include "uaf/client/results/translatebrowsepathstonodeidsresulttarget.h"
#include "uaf/client/results/writeresulttarget.h"
#include "uaf/client/results/historyreadrawmodifiedresulttarget.h"
#include "uaf/client/results/results.h"
#include "uaf/client/subscriptions/monitoreditemnotification.h"
#include "uaf/client/subscriptions/datachangenotification.h"
#include "uaf/client/subscriptions/eventnotification.h"
#include "uaf/client/subscriptions/keepalivenotification.h"
#include "uaf/client/subscriptions/subscriptioninformation.h"
#include "uaf/client/subscriptions/monitorediteminformation.h"
#include "uaf/client/sessions/sessionstates.h"
#include "uaf/client/sessions/sessioninformation.h"
%}


// add some import stuff to the __init__.py file that will be produced
%pythoncode %{
import pyuaf.util.errors
import threading
%}


// enable directors for the Client
%feature("director") uafc::Client;  


// include common definitions
%include "../pyuaf.i"


// also include the typemaps
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
    %include "pyuaf/util/util_variant_python.i"
#endif


// import the wrapped modules from pyuaf.util
%import(module="pyuaf.util.loglevels")              "pyuaf/util/util_loglevels.i"
%import(module="pyuaf.util.applicationtypes")       "pyuaf/util/util_applicationtypes.i"
%import(module="pyuaf.util.attributeids")           "pyuaf/util/util_attributeids.i"
%import(module="pyuaf.util.constants")              "pyuaf/util/util_constants.i"
%import(module="pyuaf.util.usertokentypes")         "pyuaf/util/util_usertokentypes.i" 
%import(module="pyuaf.util.nodeididentifiertypes")  "pyuaf/util/util_nodeididentifiertypes.i"
%import(module="pyuaf.util.statuscodes")            "pyuaf/util/util_statuscodes.i"
%import(module="pyuaf.util.opcuatypes")             "pyuaf/util/util_opcuatypes.i"
%import(module="pyuaf.util.primitives")             "pyuaf/util/util_primitives.i"
%import(module="pyuaf.util.opcuaidentifiers")       "pyuaf/util/util_opcuaidentifiers.i"
%import(module="pyuaf.util.opcuaidentifiers")       "pyuaf/util/util_opcuastatuscodes.i"
%import(module="pyuaf.util.securitypolicies")       "pyuaf/util/util_securitypolicies.i"
%import(module="pyuaf.util.messagesecuritymodes")   "pyuaf/util/util_messagesecuritymodes.i"
%import(module="pyuaf.util.monitoringmodes")        "pyuaf/util/util_monitoringmodes.i"
%import(module="pyuaf.util.browsedirections")       "pyuaf/util/util_browsedirections.i"
%import(module="pyuaf.util.nodeclasses")            "pyuaf/util/util_nodeclasses.i"
%import(module="pyuaf.util.timestampstoreturn")     "pyuaf/util/util_timestampstoreturn.i"
%import(module="pyuaf.util.__unittesthelper__")     "pyuaf/util/util___unittesthelper__.i"
%import(module="pyuaf.util")                        "pyuaf/util/util___init__.i"

 
// import the EXPORT macro and some numeric types
%include "uaf/client/clientexport.h"
%import "uaf/util/handles.h"


// now import the submodules of pyuaf.client
%import "pyuaf/client/client_sessionstates.i" 
%import "pyuaf/client/client_subscriptionstates.i" 
%import "pyuaf/client/client_settings.i"
%import "pyuaf/client/client_configs.i"
%import "pyuaf/client/client_requests.i"
%import "pyuaf/client/client_results.i"


// before including any classes in a generic way, specify the "special treatments" of certain classes:
%rename(__dispatch_readComplete__)          uafc::ClientInterface::readComplete;
%rename(__dispatch_writeComplete__)         uafc::ClientInterface::writeComplete;
%rename(__dispatch_callComplete__)          uafc::ClientInterface::callComplete;
%rename(__dispatch_dataChangesReceived__)   uafc::ClientInterface::dataChangesReceived;
%rename(__dispatch_eventsReceived__)        uafc::ClientInterface::eventsReceived;
%rename(__dispatch_keepAliveReceived__)     uafc::ClientInterface::keepAliveReceived;


// now include all classes in a generic way
UAF_WRAP_CLASS("uaf/client/subscriptions/subscriptioninformation.h"   , uafc , SubscriptionInformation   , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client, SubscriptionInformationVector)
UAF_WRAP_CLASS("uaf/client/subscriptions/monitorediteminformation.h"  , uafc , MonitoredItemInformation  , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client, MonitoredItemInformationVector)
UAF_WRAP_CLASS("uaf/client/subscriptions/monitoreditemnotification.h" , uafc , MonitoredItemNotification , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.client, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/subscriptions/datachangenotification.h"    , uafc , DataChangeNotification    , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.client, DataChangeNotificationVector)
UAF_WRAP_CLASS("uaf/client/subscriptions/eventnotification.h"         , uafc , EventNotification         , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.client, EventNotificationVector)
UAF_WRAP_CLASS("uaf/client/subscriptions/keepalivenotification.h"     , uafc , KeepAliveNotification     , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.client, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/sessions/sessioninformation.h"             , uafc , SessionInformation        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client, SessionInformationVector)
UAF_WRAP_CLASS("uaf/client/clientinterface.h"                         , uafc , ClientInterface           , COPY_NO,  TOSTRING_NO,  COMP_NO,  pyuaf.client, VECTOR_NO)


// Client is quite a special class so we treat it here:
%rename(ClientBase) uafc::Client;
%include <typemaps.i>
// apply the OUTPUT and INOUT directives
%apply uaf::ClientConnectionId & OUTPUT { uaf::ClientConnectionId & clientConnectionId };
%apply uaf::ClientSubscriptionHandle & OUTPUT { uaf::ClientSubscriptionHandle & clientSubscriptionHandle };
%include "uaf/client/client.h"
// clear the OUTPUT and INOUT directives
%clear uafc::ClientConnectionId & clientConnectionId;
%clear uafc::ClientConnectionId & clientSubscriptionHandle;
// finally, include the client code:
%include "pyuaf/client/client.py"

