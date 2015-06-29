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

%module requests
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/primitives.h"
#include "uaf/util/referencedescription.h"
#include "uaf/util/modificationinfo.h"
#include "uaf/client/resolution/resolvable.h"
#include "uaf/client/settings/clientsettings.h"
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
%}


// include common definitions
%include "../pyuaf.i"


// import the EXPORT macro and some numeric typedefs
%import "uaf/util/util.h"
%import "uaf/util/handles.h"


// import the necessary dependencies from pyuaf.util
%import(module="pyuaf.util.attributeids")       "pyuaf/util/util_attributeids.i"
%import(module="pyuaf.util.monitoringmodes")    "pyuaf/util/util_monitoringmodes.i"
%import(module="pyuaf.util.primitives")         "pyuaf/util/util_primitives.i"
%import(module="pyuaf.util.browsedirections")   "pyuaf/util/util_browsedirections.i"
%import(module="pyuaf.util.nodeclasses")        "pyuaf/util/util_nodeclasses.i"
%import(module="pyuaf.util.timestampstoreturn") "pyuaf/util/util_timestampstoreturn.i"
%import(module="pyuaf.util.constants")          "pyuaf/util/util_constants.i"
%import(module="pyuaf.util")                    "uaf/util/stringifiable.h"
%import(module="pyuaf.util")                    "uaf/util/browsepath.h"


// also include the typemap
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
    %include "pyuaf/util/util_variant_python.i"
#endif



// before including any classes in a generic way, specify the "special treatments" of certain classes:
%ignore getServerUriFromTarget(const BaseSessionRequestTarget& target, std::string& serverUri);
%ignore uaf::Resolvable;
%import "uaf/client/resolution/resolvable.h"
MAKE_NON_DYNAMIC(uaf::CreateMonitoredDataRequestTarget)
MAKE_NON_DYNAMIC(uaf::CreateMonitoredEventsRequestTarget)
MAKE_NON_DYNAMIC(uaf::MethodCallRequestTarget)
MAKE_NON_DYNAMIC(uaf::ReadRequestTarget)
MAKE_NON_DYNAMIC(uaf::TranslateBrowsePathsToNodeIdsRequestTarget)
MAKE_NON_DYNAMIC(uaf::BrowseRequestTarget)
MAKE_NON_DYNAMIC(uaf::BrowseNextRequestTarget)
MAKE_NON_DYNAMIC(uaf::WriteRequestTarget)
MAKE_NON_DYNAMIC(uaf::HistoryReadRawModifiedRequestTarget)
%ignore operator==(const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object1, const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object2);
%ignore operator!=(const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object1, const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object2);
%ignore operator< (const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object1, const BaseSessionRequest<_ServiceSettings, _Target, _Async>& object2);
%ignore operator==(const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object1, const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object2);
%ignore operator!=(const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object1, const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object2);
%ignore operator< (const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object1, const BaseSubscriptionRequest<_ServiceSettings, _Target, _Async>& object2);


// wrap some classes that are not defined by macros:
UAF_WRAP_CLASS("uaf/client/requests/basesessionrequesttarget.h"                  , uaf , BaseSessionRequestTarget                   , COPY_NO , TOSTRING_NO,  COMP_NO,  pyuaf.client.requests, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/requests/basesubscriptionrequesttarget.h"             , uaf , BaseSubscriptionRequestTarget              , COPY_NO , TOSTRING_NO,  COMP_NO,  pyuaf.client.requests, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/requests/browserequesttarget.h"                       , uaf , BrowseRequestTarget                        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, BrowseRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/browsenextrequesttarget.h"                   , uaf , BrowseNextRequestTarget                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, BrowseNextRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/createmonitoreddatarequesttarget.h"          , uaf , CreateMonitoredDataRequestTarget           , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, CreateMonitoredDataRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/createmonitoredeventsrequesttarget.h"        , uaf , CreateMonitoredEventsRequestTarget         , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, CreateMonitoredEventsRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/methodcallrequesttarget.h"                   , uaf , MethodCallRequestTarget                    , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, MethodCallRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/readrequesttarget.h"                         , uaf , ReadRequestTarget                          , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, ReadRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/translatebrowsepathstonodeidsrequesttarget.h", uaf , TranslateBrowsePathsToNodeIdsRequestTarget , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, TranslateBrowsePathsToNodeIdsRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/writerequesttarget.h"                        , uaf , WriteRequestTarget                         , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, WriteRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/historyreadrawmodifiedrequesttarget.h"       , uaf , HistoryReadRawModifiedRequestTarget        , COPY_YES, TOSTRING_YES, COMP_YES, pyuaf.client.requests, HistoryReadRawModifiedRequestTargetVector)
UAF_WRAP_CLASS("uaf/client/requests/basesessionrequest.h"                        , uaf , BaseSessionRequest                         , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.client.requests, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/requests/basesubscriptionrequest.h"                   , uaf , BaseSubscriptionRequest                    , COPY_YES, TOSTRING_YES, COMP_NO,  pyuaf.client.requests, VECTOR_NO)


// define a macro to create synchronous session requests
%define CREATE_UAF_SYNC_SESSIONREQUEST(SERVICE)
    %template(_##SERVICE##Request) uaf::BaseSessionRequest< uaf::BaseServiceSettings<uaf::SERVICE##Settings>, uaf::SERVICE##RequestTarget, false>;
    
    %pythoncode %{
    class SERVICE##Request(_##SERVICE##Request):
        def __init__(self, targets=0, serviceSettings=None, sessionSettings=None):
            if serviceSettings is None:
                serviceSettings = configs.SERVICE##Settings()
            if sessionSettings is None:
                sessionSettings = configs.SessionSettings()
            _##SERVICE##Request.__init__(self, targets, serviceSettings, sessionSettings)
        def __repr__(self):
            return pyuaf.util.__get__repr__("pyuaf.client.requests." + #SERVICE + "Request", str(self))
    %}
        
        
%enddef


// define a macro to create asynchronous session requests
%define CREATE_UAF_ASYNC_SESSIONREQUEST(SERVICE)
    %template(_Async##SERVICE##Request) uaf::BaseSessionRequest< uaf::BaseServiceSettings<uaf::SERVICE##Settings>, uaf::SERVICE##RequestTarget, true>;
    
    %pythoncode %{
    class Async##SERVICE##Request(_Async##SERVICE##Request):
        def __init__(self, targets=0, serviceSettings=None, sessionSettings=None):
            if serviceSettings is None:
                serviceSettings = configs.SERVICE##Settings()
            if sessionSettings is None:
                sessionSettings = configs.SessionSettings()
            _Async##SERVICE##Request.__init__(self, targets, serviceSettings, sessionSettings)
        def __repr__(self):
            return pyuaf.util.__get__repr__("pyuaf.client.requests.Async" + #SERVICE + "Request", str(self))
    %}
    
%enddef


// create synchronous session requests
CREATE_UAF_SYNC_SESSIONREQUEST(Read)
CREATE_UAF_SYNC_SESSIONREQUEST(Write)
CREATE_UAF_SYNC_SESSIONREQUEST(MethodCall)
CREATE_UAF_SYNC_SESSIONREQUEST(TranslateBrowsePathsToNodeIds)
CREATE_UAF_SYNC_SESSIONREQUEST(Browse)
CREATE_UAF_SYNC_SESSIONREQUEST(BrowseNext)
CREATE_UAF_SYNC_SESSIONREQUEST(HistoryReadRawModified)


// create asynchronous session requests
CREATE_UAF_ASYNC_SESSIONREQUEST(Read)
CREATE_UAF_ASYNC_SESSIONREQUEST(Write)
CREATE_UAF_ASYNC_SESSIONREQUEST(MethodCall)


// define a macro to create synchronous subscription requests
%define CREATE_UAF_SYNC_SUBSCRIPTIONREQUEST(SERVICE)
    %template(Base##SERVICE##Request) uaf::BaseSessionRequest< uaf::BaseServiceSettings<uaf::SERVICE##Settings>, uaf::SERVICE##RequestTarget, false>;
    %template(_##SERVICE##Request) uaf::BaseSubscriptionRequest< uaf::BaseServiceSettings<uaf::SERVICE##Settings>, uaf::SERVICE##RequestTarget, false>;

    %pythoncode %{
    class SERVICE##Request(_##SERVICE##Request):
        def __init__(self, targets=0, serviceSettings=None, sessionSettings=None, subscriptionSettings=None):
            if serviceSettings is None:
                serviceSettings = configs.SERVICE##Settings()
            if sessionSettings is None:
                sessionSettings = configs.SessionSettings()
            if subscriptionSettings is None:
                subscriptionSettings = configs.SubscriptionSettings()
            _##SERVICE##Request.__init__(self, targets, serviceSettings, sessionSettings, subscriptionSettings)
        def __repr__(self):
            return pyuaf.util.__get__repr__("pyuaf.client.requests." + #SERVICE + "Request", str(self))
    %}
%enddef


// define a macro to create asynchronous subscription requests
%define CREATE_UAF_ASYNC_SUBSCRIPTIONREQUEST(SERVICE)
    %template(BaseAsync##SERVICE##Request) uaf::BaseSessionRequest< uaf::BaseServiceSettings<uaf::SERVICE##Settings>, uaf::SERVICE##RequestTarget, true>;
    %template(_Async##SERVICE##Request) uaf::BaseSubscriptionRequest< uaf::BaseServiceSettings<uaf::SERVICE##Settings>, uaf::SERVICE##RequestTarget, true> ;

    %pythoncode %{
    class Async##SERVICE##Request(_Async##SERVICE##Request):
        def __init__(self, targets=0, serviceSettings=None, sessionSettings=None, subscriptionSettings=None):
            if serviceSettings is None:
                serviceSettings = configs.SERVICE##Settings()
            if sessionSettings is None:
                sessionSettings = configs.SessionSettings()
            if subscriptionSettings is None:
                subscriptionSettings = configs.SubscriptionSettings()
            _Async##SERVICE##Request.__init__(self, targets, serviceSettings, sessionSettings, subscriptionSettings)
        def __repr__(self):
            return pyuaf.util.__get__repr__("pyuaf.client.requests.Async" + #SERVICE + "Request", str(self))
    %}
%enddef


// create synchronous subscription requests
CREATE_UAF_SYNC_SUBSCRIPTIONREQUEST(CreateMonitoredData)
CREATE_UAF_SYNC_SUBSCRIPTIONREQUEST(CreateMonitoredEvents)


// create asynchronous subscription requests
CREATE_UAF_ASYNC_SUBSCRIPTIONREQUEST(CreateMonitoredData)
CREATE_UAF_ASYNC_SUBSCRIPTIONREQUEST(CreateMonitoredEvents)


// include the requests header
%include "uaf/client/requests/requests.h"
