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

%module results
%{
#define SWIG_FILE_WITH_INIT
#include "uaf/util/primitives.h"
#include "uaf/util/modificationinfo.h"
#include "uaf/client/results/asyncresulttarget.h"
#include "uaf/client/results/basesessionresult.h"
#include "uaf/client/results/basesubscriptionresult.h"
#include "uaf/client/results/basesessionresulttarget.h"
#include "uaf/client/results/basesubscriptionresulttarget.h"
#include "uaf/client/results/createmonitoreddataresulttarget.h"
#include "uaf/client/results/createmonitoredeventsresulttarget.h"
#include "uaf/client/results/methodcallresulttarget.h"
#include "uaf/client/results/readresulttarget.h"
#include "uaf/client/results/translatebrowsepathstonodeidsresulttarget.h"
#include "uaf/client/results/writeresulttarget.h"
#include "uaf/client/results/historyreadrawmodifiedresulttarget.h"
#include "uaf/client/results/results.h"
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
%import(module="pyuaf.util")                    "uaf/util/datavalue.h"
%import(module="pyuaf.util")                    "uaf/util/modificationinfo.h"


// also include the typemaps
#if defined(SWIGPYTHON)
    %include "pyuaf/util/util_bytestring_python.i"
    %include "pyuaf/util/util_variant_python.i"
#endif


// before including any classes in a generic way, specify the "special treatments" of certain classes:
%ignore operator==(const BaseSessionResult<R, A>& object1, const BaseSessionResult<R, A>& object2);
%ignore operator!=(const BaseSessionResult<R, A>& object1, const BaseSessionResult<R, A>& object2);
%ignore operator< (const BaseSessionResult<R, A>& object1, const BaseSessionResult<R, A>& object2);
%ignore operator==(const BaseSubscriptionResult<_Target, _Async>& object1, const BaseSubscriptionResult<_Target, _Async>& object2);
%ignore operator!=(const BaseSubscriptionResult<_Target, _Async>& object1, const BaseSubscriptionResult<_Target, _Async>& object2);
%ignore operator< (const BaseSubscriptionResult<_Target, _Async>& object1, const BaseSubscriptionResult<_Target, _Async>& object2);
%rename(__str__) uafc::BaseSessionResult::toString const;
%rename(__str__) uafc::BaseSubscriptionResult::toString const;

// wrap some classes that are not defined by macros:
UAF_WRAP_CLASS("uaf/client/results/basesessionresulttarget.h"                   , uafc , BaseSessionResultTarget                   , COPY_NO , TOSTRING_NO,  COMP_NO,  pyuaf.client.results, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/results/basesubscriptionresulttarget.h"              , uafc , BaseSubscriptionResultTarget              , COPY_NO , TOSTRING_NO,  COMP_NO,  pyuaf.client.results, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/results/asyncresulttarget.h"                         , uafc , AsyncResultTarget                         , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, AsyncResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/browseresulttarget.h"                        , uafc , BrowseResultTarget                        , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, BrowseResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/createmonitoreddataresulttarget.h"           , uafc , CreateMonitoredDataResultTarget           , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, CreateMonitoredDataResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/createmonitoredeventsresulttarget.h"         , uafc , CreateMonitoredEventsResultTarget         , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, CreateMonitoredEventsResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/methodcallresulttarget.h"                    , uafc , MethodCallResultTarget                    , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, MethodCallResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/readresulttarget.h"                          , uafc , ReadResultTarget                          , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, ReadResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/translatebrowsepathstonodeidsresulttarget.h" , uafc , TranslateBrowsePathsToNodeIdsResultTarget , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, TranslateBrowsePathsToNodeIdsResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/writeresulttarget.h"                         , uafc , WriteResultTarget                         , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, WriteResultTargetVector)
UAF_WRAP_CLASS("uaf/client/results/historyreadrawmodifiedresulttarget.h"        , uafc , HistoryReadRawModifiedResultTarget        , COPY_NO , TOSTRING_YES, COMP_NO,  pyuaf.client.results, HistoryReadRawModifiedVector)
UAF_WRAP_CLASS("uaf/client/results/basesessionresult.h"                         , uafc , BaseSessionResult                         , COPY_YES, TOSTRING_NO,  COMP_NO,  pyuaf.client.results, VECTOR_NO)
UAF_WRAP_CLASS("uaf/client/results/basesubscriptionresult.h"                    , uafc , BaseSubscriptionResult                    , COPY_YES, TOSTRING_NO,  COMP_NO,  pyuaf.client.results, VECTOR_NO)



// define a macro to create synchronous session results
%define CREATE_UAFC_SYNC_SESSIONRESULT(SERVICE)
    %template(SERVICE##Result) uafc::BaseSessionResult<uafc::SERVICE##ResultTarget, false>;
%enddef


// define a macro to create asynchronous session results
%define CREATE_UAFC_ASYNC_SESSIONRESULT(SERVICE)
    %template(Async##SERVICE##Result) uafc::BaseSessionResult<uafc::AsyncResultTarget, true>;
%enddef


// create the synchronous session results
CREATE_UAFC_SYNC_SESSIONRESULT(Read)
CREATE_UAFC_SYNC_SESSIONRESULT(Write)
CREATE_UAFC_SYNC_SESSIONRESULT(MethodCall)
CREATE_UAFC_SYNC_SESSIONRESULT(TranslateBrowsePathsToNodeIds)
CREATE_UAFC_SYNC_SESSIONRESULT(Browse)
%template(BrowseNextResult) uafc::BaseSessionResult<uafc::BrowseResultTarget, false>;
CREATE_UAFC_SYNC_SESSIONRESULT(HistoryReadRawModified)

// create the asynchronous session results
CREATE_UAFC_ASYNC_SESSIONRESULT(Read)
CREATE_UAFC_ASYNC_SESSIONRESULT(Write)
CREATE_UAFC_ASYNC_SESSIONRESULT(MethodCall)


// define a macro to create synchronous subscription results
%define CREATE_UAFC_SYNC_SUBSCRIPTIONRESULT(SERVICE)
    %template(Base##SERVICE##Result) uafc::BaseSessionResult<uafc::SERVICE##ResultTarget, false>;
    %template(SERVICE##Result) uafc::BaseSubscriptionResult<uafc::SERVICE##ResultTarget, false>;
%enddef


// define a macro to create asynchronous subscription results
%define CREATE_UAFC_ASYNC_SUBSCRIPTIONRESULT(SERVICE)
    %template(BaseAsync##SERVICE##Result) uafc::BaseSessionResult<uafc::AsyncResultTarget, true>;
    %template(Async##SERVICE##Result) uafc::BaseSubscriptionResult<uafc::AsyncResultTarget, true>;
%enddef


// create the synchronous subscription results
CREATE_UAFC_SYNC_SUBSCRIPTIONRESULT(CreateMonitoredData)
CREATE_UAFC_SYNC_SUBSCRIPTIONRESULT(CreateMonitoredEvents)


// create the asynchronous subscription results
CREATE_UAFC_ASYNC_SUBSCRIPTIONRESULT(CreateMonitoredData)
CREATE_UAFC_ASYNC_SUBSCRIPTIONRESULT(CreateMonitoredEvents)


// include the results header
%include "uaf/client/results/results.h"

