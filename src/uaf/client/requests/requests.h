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

#ifndef UAFC_REQUESTS_H_
#define UAFC_REQUESTS_H_

// STD
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesessionrequest.h"
#include "uaf/client/requests/basesubscriptionrequest.h"
#include "uaf/client/configs/configs.h"
#include "uaf/client/requests/readrequesttarget.h"
#include "uaf/client/requests/writerequesttarget.h"
#include "uaf/client/requests/methodcallrequesttarget.h"
#include "uaf/client/requests/createmonitoreddatarequesttarget.h"
#include "uaf/client/requests/createmonitoredeventsrequesttarget.h"
#include "uaf/client/requests/translatebrowsepathstonodeidsrequesttarget.h"





#define DEFINE_SYNC_SESSIONREQUEST(name) \
/** This is a synchronous service request handled at the session level.  @ingroup ClientRequests */ \
typedef UAFC_EXPORT uafc::BaseSessionRequest<uafc::name##Config, uafc::name##RequestTarget, false> name##Request;

#define DEFINE_ASYNC_SESSIONREQUEST(name) \
/** This is an asynchronous service request handled at the session level.  @ingroup ClientRequests */ \
typedef UAFC_EXPORT uafc::BaseSessionRequest<uafc::name##Config, uafc::name##RequestTarget, true> Async##name##Request;


#define DEFINE_SYNC_SUBSCRIPTIONREQUEST(name) \
/** This is a synchronous service request handled at the subscription level.  @ingroup ClientRequests */ \
typedef UAFC_EXPORT uafc::BaseSubscriptionRequest<uafc::name##Config, uafc::name##RequestTarget, false> name##Request;

#define DEFINE_ASYNC_SUBSCRIPTIONREQUEST(name) \
/** This is an asynchronous service request handled at the subscription level.  @ingroup ClientRequests */ \
typedef UAFC_EXPORT uafc::BaseSubscriptionRequest<uafc::name##Config, uafc::name##RequestTarget, true> Async##name##Request;




namespace uafc
{
    // synchronous
    DEFINE_SYNC_SESSIONREQUEST(Read)
    DEFINE_SYNC_SESSIONREQUEST(Write)
    DEFINE_SYNC_SESSIONREQUEST(MethodCall)
    DEFINE_SYNC_SESSIONREQUEST(TranslateBrowsePathsToNodeIds)
    DEFINE_SYNC_SUBSCRIPTIONREQUEST(CreateMonitoredData)
    DEFINE_SYNC_SUBSCRIPTIONREQUEST(CreateMonitoredEvents)

    // asynchronous
    DEFINE_ASYNC_SESSIONREQUEST(Read)
    DEFINE_ASYNC_SESSIONREQUEST(Write)
    DEFINE_ASYNC_SESSIONREQUEST(MethodCall)
    DEFINE_ASYNC_SUBSCRIPTIONREQUEST(CreateMonitoredData)
    DEFINE_ASYNC_SUBSCRIPTIONREQUEST(CreateMonitoredEvents)
}


#endif /* UAFC_REQUESTS_H_ */
