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

#ifndef UAF_CLIENTSERVICES_H_
#define UAF_CLIENTSERVICES_H_

// STD
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/results.h"
#include "uaf/client/settings/allsettings.h"
#include "uaf/client/invocations/invocations.h"



#define DEFINE_SYNC_SERVICE(NAME)                                                                \
/** A xxxxService carries type information about the associated requests, targets, results, etc. \
    @ingroup ClientServices  */                                                                          \
struct UAF_EXPORT NAME##Service                                                                \
{                                                                                               \
    /** The type of the service Request. */                                                     \
    typedef uaf::NAME##Request         Request;                                                \
    /** The type of the service RequestTarget. */                                               \
    typedef uaf::NAME##RequestTarget   RequestTarget;                                          \
    /** The type of the service Result. */                                                      \
    typedef uaf::NAME##Result          Result;                                                 \
    /** The type of the service ResultTarget. */                                                \
    typedef uaf::NAME##ResultTarget    ResultTarget;                                           \
    /** The type of the service Config. */                                                      \
    typedef uaf::NAME##Settings        Settings;                                               \
    /** The type of the service Invocation. */                                                  \
    typedef uaf::NAME##Invocation      Invocation;                                             \
    /** A flag indicating whether the service is asynchronous or not. */                        \
    static const bool asynchronous = false;                                                     \
    /** Get the name of the service. */                                                         \
    static const std::string name() { return #NAME; }                                           \
};


#define DEFINE_ASYNC_SERVICE(NAME)                                                               \
/** A xxxxService carries type information about the associated requests, targets, results, etc. \
    @ingroup ClientServices  */                                                                          \
struct UAF_EXPORT Async##NAME##Service                                                         \
{                                                                                               \
    /** The type of the service Request. */                                                     \
    typedef uaf::Async##NAME##Request    Request;                                              \
    /** The type of the service RequestTarget. */                                               \
    typedef uaf::Async##NAME##Result     Result;                                               \
    /** The type of the service Result. */                                                      \
    typedef uaf::NAME##RequestTarget     RequestTarget;                                        \
    /** The type of the service ResultTarget. */                                                \
    typedef uaf::NAME##ResultTarget      ResultTarget;                                         \
    /** The type of the service Settings. */                                                    \
    typedef uaf::NAME##Settings          Settings;                                             \
    /** The type of the service Invocation. */                                                  \
    typedef uaf::NAME##Invocation        Invocation;                                           \
    /** A flag indicating whether the service is asynchronous or not. */                        \
    static const bool asynchronous = true;                                                      \
    /** Get the name of the service. */                                                         \
    static const std::string name() { return "Async" #NAME; }                                   \
};


namespace uaf
{
    // define the synchronous services
    DEFINE_SYNC_SERVICE(Read)
    DEFINE_SYNC_SERVICE(Write)
    DEFINE_SYNC_SERVICE(MethodCall)
    DEFINE_SYNC_SERVICE(TranslateBrowsePathsToNodeIds)
    DEFINE_SYNC_SERVICE(Browse)
    DEFINE_SYNC_SERVICE(BrowseNext)
    DEFINE_SYNC_SERVICE(CreateMonitoredData)
    DEFINE_SYNC_SERVICE(CreateMonitoredEvents)
    DEFINE_SYNC_SERVICE(HistoryReadRawModified)

    // define the asynchronous services
    DEFINE_ASYNC_SERVICE(Read)
    DEFINE_ASYNC_SERVICE(Write)
    DEFINE_ASYNC_SERVICE(MethodCall)
    DEFINE_ASYNC_SERVICE(CreateMonitoredData)
    DEFINE_ASYNC_SERVICE(CreateMonitoredEvents)
}


#endif /* UAF_CLIENTSERVICES_H_ */
