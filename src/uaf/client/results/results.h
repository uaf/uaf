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

#ifndef UAF_RESULTS_H_
#define UAF_RESULTS_H_

// STD
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/results/basesessionresult.h"
#include "uaf/client/results/basesubscriptionresult.h"
#include "uaf/client/results/asyncresulttarget.h"
#include "uaf/client/results/readresulttarget.h"
#include "uaf/client/results/writeresulttarget.h"
#include "uaf/client/results/methodcallresulttarget.h"
#include "uaf/client/results/createmonitoreddataresulttarget.h"
#include "uaf/client/results/createmonitoredeventsresulttarget.h"
#include "uaf/client/results/translatebrowsepathstonodeidsresulttarget.h"
#include "uaf/client/results/browseresulttarget.h"
#include "uaf/client/results/browsenextresulttarget.h"
#include "uaf/client/results/historyreadrawmodifiedresulttarget.h"




#define DEFINE_SYNC_SESSIONRESULT(NAME) \
/** This is a synchronous service result handled at the session level.  @ingroup ClientResults */ \
typedef UAF_EXPORT uaf::BaseSessionResult<uaf::NAME##ResultTarget, false> NAME##Result;


#define DEFINE_ASYNC_SESSIONRESULT(NAME) \
/** This is an asynchronous service result handled at the session level.  @ingroup ClientResults */ \
typedef UAF_EXPORT uaf::BaseSessionResult<uaf::AsyncResultTarget, true> Async##NAME##Result;


#define DEFINE_SYNC_SUBSCRIPTIONRESULT(NAME) \
/** This is a synchronous service result handled at the subscription level.  @ingroup ClientResults */ \
typedef UAF_EXPORT uaf::BaseSubscriptionResult<uaf::NAME##ResultTarget, false> NAME##Result;


#define DEFINE_ASYNC_SUBSCRIPTIONRESULT(NAME) \
/** This is an asynchronous service result handled at the subscription level.  @ingroup ClientResults */ \
typedef UAF_EXPORT uaf::BaseSubscriptionResult<uaf::AsyncResultTarget, true> Async##NAME##Result;


namespace uaf
{
    // synchronous session results
    DEFINE_SYNC_SESSIONRESULT(Read)
    DEFINE_SYNC_SESSIONRESULT(Write)
    DEFINE_SYNC_SESSIONRESULT(MethodCall)
    DEFINE_SYNC_SESSIONRESULT(TranslateBrowsePathsToNodeIds)
    DEFINE_SYNC_SESSIONRESULT(Browse)
    typedef UAF_EXPORT uaf::BrowseResult BrowseNextResult;
    DEFINE_SYNC_SESSIONRESULT(HistoryReadRawModified)

    // synchronous subscription results
    DEFINE_SYNC_SUBSCRIPTIONRESULT(CreateMonitoredData)
    DEFINE_SYNC_SUBSCRIPTIONRESULT(CreateMonitoredEvents)

    // asynchronous session results
    DEFINE_ASYNC_SESSIONRESULT(Read)
    DEFINE_ASYNC_SESSIONRESULT(Write)
    DEFINE_ASYNC_SESSIONRESULT(MethodCall)

    // asynchronous subscription results
    DEFINE_ASYNC_SUBSCRIPTIONRESULT(CreateMonitoredData)
    DEFINE_ASYNC_SUBSCRIPTIONRESULT(CreateMonitoredEvents)

}


#endif /* UAF_RESULTS_H_ */
