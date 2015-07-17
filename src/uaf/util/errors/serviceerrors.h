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


#ifndef UAF_SERVICEERRORS_H_
#define UAF_SERVICEERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/uaferror.h"
#include "uaf/util/errors/invalidrequesterror.h"
#include "uaf/util/util.h"
#include "uaf/util/constants.h"

namespace uaf
{


    class UAF_EXPORT ServiceError : public uaf::UafError
    {
    public:
        ServiceError()
        : uaf::UafError("Service error")
        {}

        ServiceError(const std::string& description)
        : uaf::UafError(description)
        {}
    };

    class UAF_EXPORT CouldNotReadArraysError : public uaf::ServiceError
    {
    public:
        CouldNotReadArraysError()
        : uaf::ServiceError("Could not read the namespace and server arrays")
        {}

        CouldNotReadArraysError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not read the namespace and server arrays: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT CreateMonitoredItemsError : public uaf::ServiceError
    {
    public:
        CreateMonitoredItemsError()
        : uaf::ServiceError("The monitored items could not be created")
        {}

        CreateMonitoredItemsError(const std::vector<uaf::ClientHandle>& assignedClientHandles)
        : uaf::ServiceError(),
          assignedClientHandles(assignedClientHandles)
        {
            message = uaf::format("The following monitored items could not be created: %s",
                                  uaf::uint32ArrayToString(assignedClientHandles).c_str());
        }

        std::vector<uaf::ClientHandle> assignedClientHandles;
    };

    class UAF_EXPORT CreateMonitoredItemsInvocationError : public uaf::ServiceError
    {
    public:
        CreateMonitoredItemsInvocationError()
        : uaf::ServiceError("Could not invoke the CreateMontitoredItem service")
        {}

        CreateMonitoredItemsInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the CreateMontitoredItem service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT BeginCreateMonitoredItemsInvocationError : public uaf::ServiceError
    {
    public:
        BeginCreateMonitoredItemsInvocationError()
        : uaf::ServiceError("Could not invoke the BeginCreateMontitoredItem service")
        {}

        BeginCreateMonitoredItemsInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the BeginCreateMontitoredItem service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotCreateMonitoredItemsError : public uaf::ServiceError
    {
    public:
        ServerCouldNotCreateMonitoredItemsError()
        : uaf::ServiceError("The server could not create the requested monitored items")
        {}

        ServerCouldNotCreateMonitoredItemsError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not create the requested monitored items: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT BrowseNextInvocationError : public uaf::ServiceError
    {
    public:
        BrowseNextInvocationError()
        : uaf::ServiceError("Could not invoke the BrowseNext service")
        {}

        BrowseNextInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the BrowseNext service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotBrowseNextError : public uaf::ServiceError
    {
    public:
        ServerCouldNotBrowseNextError()
        : uaf::ServiceError("The server could not successfully process the BrowseNext service")
        {}

        ServerCouldNotBrowseNextError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the BrowseNext service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT BrowseInvocationError : public uaf::ServiceError
    {
    public:
        BrowseInvocationError()
        : uaf::ServiceError("Could not invoke the Browse service")
        {}

        BrowseInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the Browse service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotBrowseError : public uaf::ServiceError
    {
    public:
        ServerCouldNotBrowseError()
        : uaf::ServiceError("The server could not successfully process the Browse service")
        {}

        ServerCouldNotBrowseError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the Browse service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ReadInvocationError : public uaf::ServiceError
    {
    public:
        ReadInvocationError()
        : uaf::ServiceError("Could not invoke the Read service")
        {}

        ReadInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the Read service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT BeginReadInvocationError : public uaf::ServiceError
    {
    public:
        BeginReadInvocationError()
        : uaf::ServiceError("Could not invoke the async Read service")
        {}

        BeginReadInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the async Read service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotReadError : public uaf::ServiceError
    {
    public:
        ServerCouldNotReadError()
        : uaf::ServiceError("The server could not successfully process the Read service")
        {}

        ServerCouldNotReadError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the Read service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT TranslateBrowsePathsToNodeIdsInvocationError : public uaf::ServiceError
    {
    public:
        TranslateBrowsePathsToNodeIdsInvocationError()
        : uaf::ServiceError("Could not invoke the TranslateBrowsePathsToNodeIds service")
        {}

        TranslateBrowsePathsToNodeIdsInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the TranslateBrowsePathsToNodeIds service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotTranslateBrowsePathsToNodeIdsError : public uaf::ServiceError
    {
    public:
        ServerCouldNotTranslateBrowsePathsToNodeIdsError()
        : uaf::ServiceError("The server could not successfully process the TranslateBrowsePathsToNodeIds service")
        {}

        ServerCouldNotTranslateBrowsePathsToNodeIdsError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the TranslateBrowsePathsToNodeIds service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT HistoryReadInvocationError : public uaf::ServiceError
    {
    public:
        HistoryReadInvocationError()
        : uaf::ServiceError("Could not invoke the HistoryRead service")
        {}

        HistoryReadInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the HistoryRead service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT HistoryReadRawModifiedInvocationError : public uaf::ServiceError
    {
    public:
        HistoryReadRawModifiedInvocationError()
        : uaf::ServiceError("Could not invoke the HistoryReadRawModified service")
        {}

        HistoryReadRawModifiedInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the HistoryReadRawModified service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotHistoryReadError : public uaf::ServiceError
    {
    public:
        ServerCouldNotHistoryReadError()
        : uaf::ServiceError("The server could not successfully process the HistoryRead service")
        {}

        ServerCouldNotHistoryReadError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the HistoryRead service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT MethodCallInvocationError : public uaf::ServiceError
    {
    public:
        MethodCallInvocationError()
        : uaf::ServiceError("Could not invoke the MethodCall service")
        {}

        MethodCallInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the MethodCall service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT AsyncMethodCallInvocationError : public uaf::ServiceError
    {
    public:
        AsyncMethodCallInvocationError()
        : uaf::ServiceError("Could not invoke the async MethodCall service")
        {}

        AsyncMethodCallInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the async MethodCal service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT ServerCouldNotCallMethodError : public uaf::ServiceError
    {
    public:
        ServerCouldNotCallMethodError()
        : uaf::ServiceError("The server could not successfully process the MethodCall service")
        {}

        ServerCouldNotCallMethodError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the MethodCall service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT WriteInvocationError : public uaf::ServiceError
    {
    public:
        WriteInvocationError()
        : uaf::ServiceError("Could not invoke the Write service")
        {}

        WriteInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the Write service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT AsyncWriteInvocationError : public uaf::ServiceError
    {
    public:
        AsyncWriteInvocationError()
        : uaf::ServiceError("Could not invoke the async Write service")
        {}

        AsyncWriteInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the async Write service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT ServerCouldNotWriteError : public uaf::ServiceError
    {
    public:
        ServerCouldNotWriteError()
        : uaf::ServiceError("The server could not successfully process the Write service")
        {}

        ServerCouldNotWriteError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not successfully process the Write service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };



    class UAF_EXPORT CallCompleteError : public uaf::ServiceError
    {
    public:
        CallCompleteError()
        : uaf::ServiceError("The async call was completed with error")
        {}

        CallCompleteError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The async call was completed with error: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };



    class UAF_EXPORT InputArgumentError : public uaf::ServiceError
    {
    public:
        InputArgumentError()
        : uaf::ServiceError("There was an error for the given input argument")
        {}

        InputArgumentError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("There was an error for the given input argument: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ReadCompleteError : public uaf::ServiceError
    {
    public:
        ReadCompleteError()
        : uaf::ServiceError("The async read was completed with error")
        {}

        ReadCompleteError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The async read was completed with error: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

    class UAF_EXPORT WriteCompleteError : public uaf::ServiceError
    {
    public:
        WriteCompleteError()
        : uaf::ServiceError("The async write was completed with error")
        {}

        WriteCompleteError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("The async write was completed with error: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT SetPublishingModeInvocationError : public uaf::ServiceError
    {
    public:
        SetPublishingModeInvocationError()
        : uaf::ServiceError("Could not invoke the SetPublishingMode service")
        {}

        SetPublishingModeInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the SetPublishingMode service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT SetMonitoringModeInvocationError : public uaf::ServiceError
    {
    public:
        SetMonitoringModeInvocationError()
        : uaf::ServiceError("Could not invoke the SetMonitoringMode service")
        {}

        SetMonitoringModeInvocationError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Could not invoke the SetMonitoringMode service: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCouldNotSetMonitoringModeError : public uaf::ServiceError
    {
    public:
        ServerCouldNotSetMonitoringModeError()
        : uaf::ServiceError("The server could not set the monitoring mode successfully"),
          clientHandle(uaf::constants::CLIENTHANDLE_NOT_ASSIGNED)
        {}

        ServerCouldNotSetMonitoringModeError(uaf::ClientHandle clientHandle, uaf::SdkStatus sdkStatus)
        : uaf::ServiceError(uaf::format("The server could not set the monitoring mode successfully for clientHandle %d: %s",
                                        clientHandle,
                                        sdkStatus.toString().c_str())),
          clientHandle(clientHandle),
          sdkStatus(sdkStatus)
        {}

        uaf::ClientHandle clientHandle;
        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT BadDataReceivedError : public uaf::ServiceError
    {
    public:
        BadDataReceivedError()
        : uaf::ServiceError("Bad data received")
        {}

        BadDataReceivedError(const uaf::SdkStatus& sdkStatus)
        : uaf::ServiceError(uaf::format("Bad data received: %s",
                            sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}

        uaf::SdkStatus sdkStatus;
    };

}

#endif /* UAF_SERVICEERRORS_H_ */
