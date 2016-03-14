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

#ifndef UAF_STATUS_H
#define UAF_STATUS_H

// STD
#include <string>
#include <vector>
#include <iostream>
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/statuscodes.h"
#include "uaf/util/errors/generalerrors.h"
#include "uaf/util/errors/discoveryerrors.h"
#include "uaf/util/errors/resolutionerrors.h"
#include "uaf/util/errors/invalidrequesterror.h"
#include "uaf/util/errors/unsupportederrors.h"
#include "uaf/util/errors/securityerrors.h"
#include "uaf/util/errors/connectionerrors.h"
#include "uaf/util/errors/subscriptionerrors.h"
#include "uaf/util/errors/serviceerrors.h"
#include "uaf/util/errors/configurationerrors.h"
#include "uaf/util/errors/backwardscompatibilityerrors.h"


#define UAF_STATUS_CONSTRUCTOR(ERROR)           \
        Status(const uaf::ERROR& error)         \
        : raisedBy_##ERROR(error),              \
          statusCode(uaf::statuscodes::ERROR),  \
          raisedBy_(NULL)                       \
        {}                                      \
                                                \
        uaf::ERROR raisedBy_##ERROR;


namespace uaf
{

    class UAF_EXPORT Status
    {
    public:

        Status()
        : statusCode(uaf::statuscodes::Uncertain),
          raisedBy_(NULL)
        {}

        Status(uaf::statuscodes::StatusCode statusCode)
        : statusCode(statusCode),
          raisedBy_(NULL)
        {}


        /** Copy constructor.*/
        Status(const Status& other);

        /**
         * Destructor.
         */
        ~Status();


        /**
         * Assignment operator.
         */
        Status& operator=(const Status& other);


        UAF_STATUS_CONSTRUCTOR(FindServersError)
        UAF_STATUS_CONSTRUCTOR(UnknownServerError)
        UAF_STATUS_CONSTRUCTOR(EmptyUrlError)
        UAF_STATUS_CONSTRUCTOR(NoParallelFindServersAllowedError)
        UAF_STATUS_CONSTRUCTOR(NoDiscoveryUrlsFoundError)
        UAF_STATUS_CONSTRUCTOR(ServerCertificateRejectedByUserError)
        UAF_STATUS_CONSTRUCTOR(ServerCertificateSavingError)
        UAF_STATUS_CONSTRUCTOR(OpenSSLStoreInitializationError)
        UAF_STATUS_CONSTRUCTOR(ClientCertificateLoadingError)
        UAF_STATUS_CONSTRUCTOR(ServerDidNotProvideCertificateError)
        UAF_STATUS_CONSTRUCTOR(PathNotExistsError)
        UAF_STATUS_CONSTRUCTOR(NoSecuritySettingsGivenError)
        UAF_STATUS_CONSTRUCTOR(PathCreationError)
        UAF_STATUS_CONSTRUCTOR(SecuritySettingsMatchError)
        UAF_STATUS_CONSTRUCTOR(WrongTypeError)
        UAF_STATUS_CONSTRUCTOR(UnexpectedError)
        UAF_STATUS_CONSTRUCTOR(ServerArrayConversionError)
        UAF_STATUS_CONSTRUCTOR(NamespaceArrayConversionError)
        UAF_STATUS_CONSTRUCTOR(BadNamespaceArrayError)
        UAF_STATUS_CONSTRUCTOR(BadServerArrayError)
        UAF_STATUS_CONSTRUCTOR(UnknownServerIndexError)
        UAF_STATUS_CONSTRUCTOR(InvalidAddressError)
        UAF_STATUS_CONSTRUCTOR(UnknownNamespaceUriError)
        UAF_STATUS_CONSTRUCTOR(NoNamespaceIndexOrUriGivenError)
        UAF_STATUS_CONSTRUCTOR(UnknownNamespaceIndexError)
        UAF_STATUS_CONSTRUCTOR(EmptyServerUriAndUnknownNamespaceIndexError)
        UAF_STATUS_CONSTRUCTOR(ExpandedNodeIdAddressExpectedError)
        UAF_STATUS_CONSTRUCTOR(EmptyServerUriError)
        UAF_STATUS_CONSTRUCTOR(UnsupportedError)
        UAF_STATUS_CONSTRUCTOR(UnsupportedNodeIdIdentifierTypeError)
        UAF_STATUS_CONSTRUCTOR(SyncInvocationNotSupportedError)
        UAF_STATUS_CONSTRUCTOR(AsyncInvocationNotSupportedError)
        UAF_STATUS_CONSTRUCTOR(NoStatusesGivenError)
        UAF_STATUS_CONSTRUCTOR(BadStatusesPresentError)
        UAF_STATUS_CONSTRUCTOR(NotAllTargetsCouldBeResolvedError)
        UAF_STATUS_CONSTRUCTOR(InvalidServerUriError)
        UAF_STATUS_CONSTRUCTOR(SubscriptionNotCreatedError)
        UAF_STATUS_CONSTRUCTOR(NoTargetsGivenError)
        UAF_STATUS_CONSTRUCTOR(DataDontMatchAddressesError)
        UAF_STATUS_CONSTRUCTOR(ItemNotFoundForTheGivenHandleError)
        UAF_STATUS_CONSTRUCTOR(TargetRankOutOfBoundsError)
        UAF_STATUS_CONSTRUCTOR(NoItemFoundForTheGivenRequestHandleError)
        UAF_STATUS_CONSTRUCTOR(ContinuationPointsDontMatchAddressesError)
        UAF_STATUS_CONSTRUCTOR(UnknownNamespaceIndexAndServerIndexError)
        UAF_STATUS_CONSTRUCTOR(AsyncMultiMethodCallNotSupportedError)
        UAF_STATUS_CONSTRUCTOR(EmptyAddressError)
        UAF_STATUS_CONSTRUCTOR(MultipleTranslationResultsError)
        UAF_STATUS_CONSTRUCTOR(UnknownClientSubscriptionHandleError)
        UAF_STATUS_CONSTRUCTOR(UnknownClientHandleError)
        UAF_STATUS_CONSTRUCTOR(UnknownClientConnectionIdError)
        UAF_STATUS_CONSTRUCTOR(AsyncConnectionFailedError)
        UAF_STATUS_CONSTRUCTOR(ConnectionFailedError)
        UAF_STATUS_CONSTRUCTOR(EmptyUserCertificateError)
        UAF_STATUS_CONSTRUCTOR(InvalidPrivateKeyError)
        UAF_STATUS_CONSTRUCTOR(SessionSecuritySettingsDontMatchEndpointError)
        UAF_STATUS_CONSTRUCTOR(CouldNotManuallyUnsubscribeError)
        UAF_STATUS_CONSTRUCTOR(CouldNotManuallySubscribeError)
        UAF_STATUS_CONSTRUCTOR(SessionNotConnectedError)
        UAF_STATUS_CONSTRUCTOR(SubscriptionHasBeenDeletedError)
        UAF_STATUS_CONSTRUCTOR(NoDiscoveryUrlsExposedByServerError)
        UAF_STATUS_CONSTRUCTOR(GetEndpointsError)
        UAF_STATUS_CONSTRUCTOR(NoEndpointsProvidedByServerError)
        UAF_STATUS_CONSTRUCTOR(DisconnectionFailedError)
        UAF_STATUS_CONSTRUCTOR(NoConnectedSessionToUpdateArraysError)
        UAF_STATUS_CONSTRUCTOR(BadDataReceivedError)

        // service errors
        UAF_STATUS_CONSTRUCTOR(CouldNotReadArraysError)
        UAF_STATUS_CONSTRUCTOR(CreateMonitoredItemsError)
        UAF_STATUS_CONSTRUCTOR(CreateMonitoredItemsInvocationError)
        UAF_STATUS_CONSTRUCTOR(BeginCreateMonitoredItemsInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotCreateMonitoredItemsError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotBrowseNextError)
        UAF_STATUS_CONSTRUCTOR(BrowseNextInvocationError)
        UAF_STATUS_CONSTRUCTOR(ReadInvocationError)
        UAF_STATUS_CONSTRUCTOR(BeginReadInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotReadError)
        UAF_STATUS_CONSTRUCTOR(TranslateBrowsePathsToNodeIdsInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotTranslateBrowsePathsToNodeIdsError)
        UAF_STATUS_CONSTRUCTOR(HistoryReadInvocationError)
        UAF_STATUS_CONSTRUCTOR(HistoryReadRawModifiedInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotHistoryReadError)
        UAF_STATUS_CONSTRUCTOR(MethodCallInvocationError)
        UAF_STATUS_CONSTRUCTOR(AsyncMethodCallInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotCallMethodError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotBrowseError)
        UAF_STATUS_CONSTRUCTOR(BrowseInvocationError)
        UAF_STATUS_CONSTRUCTOR(WriteInvocationError)
        UAF_STATUS_CONSTRUCTOR(AsyncWriteInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotWriteError)
        UAF_STATUS_CONSTRUCTOR(CallCompleteError)
        UAF_STATUS_CONSTRUCTOR(InputArgumentError)
        UAF_STATUS_CONSTRUCTOR(ReadCompleteError)
        UAF_STATUS_CONSTRUCTOR(WriteCompleteError)
        UAF_STATUS_CONSTRUCTOR(SetPublishingModeInvocationError)
        UAF_STATUS_CONSTRUCTOR(ServerCouldNotSetMonitoringModeError)
        UAF_STATUS_CONSTRUCTOR(CreateSubscriptionError)
        UAF_STATUS_CONSTRUCTOR(DeleteSubscriptionError)
        UAF_STATUS_CONSTRUCTOR(SetMonitoringModeInvocationError)
        UAF_STATUS_CONSTRUCTOR(DefinitionNotFoundError)

        // configuration errors
        UAF_STATUS_CONSTRUCTOR(ConfigurationError)
        UAF_STATUS_CONSTRUCTOR(CouldNotCreateCertificateTrustListLocationError)
        UAF_STATUS_CONSTRUCTOR(CouldNotCreateCertificateRevocationListLocationError)
        UAF_STATUS_CONSTRUCTOR(CouldNotCreateIssuersCertificateLocationError)
        UAF_STATUS_CONSTRUCTOR(CouldNotCreateIssuersRevocationListLocationError)
        UAF_STATUS_CONSTRUCTOR(CouldNotCreateClientPrivateKeyLocationError)
        UAF_STATUS_CONSTRUCTOR(CouldNotCreateClientCertificateLocationError)

        /** The UAF status code */
        uaf::statuscodes::StatusCode statusCode;

        /** Check if the Status is good/bad/uncertain/... */
        bool isUncertain()      const { return statusCode == uaf::statuscodes::Uncertain;   }
        bool isGood()           const { return statusCode == uaf::statuscodes::Good;        }
        bool isBad()            const { return !(isUncertain() || isGood());                }
        bool isNotUncertain()   const { return !isUncertain();  }
        bool isNotGood()        const { return !isGood();       }
        bool isNotBad()         const { return !isBad();        }

        /** Change the status into Good */
        void setGood();

        /** Change the status into Uncertain */
        void setUncertain();

        /** Get a string representation. */
        std::string toString() const;

        /**
         * Make a "summary" of other statuses.
         *
         * Bad is dominant to Uncertain, which is dominant to Good.
         * So if any Bad status is present, the summary will be "Bad".
         * If no Bad statuses are present but any Uncertain status is present, the summary will be
         * Uncertain.
         * And if only Good statuses are present, the summary will be Good.
         *
         * @param statuses  The statuses to summarize.
         */
        void summarize(const std::vector<uaf::Status>& statuses);


        /** Remove the raisedBy status. */
        void clearRaisedBy();


        /** Add the status that caused this status (i.e. the current instance). */
        void setRaisedBy(const uaf::Status& status);

        /** Check if this status is raised by some other status. */
        bool isRaisedBy() const;

        /** If this status is raised by some other status, get a copy of this other status. */
        Status raisedBy() const;


        /** Get the name of the status code. */
        std::string statusCodeName() const;


        // comparison operators
        friend UAF_EXPORT bool operator==(const Status& object1, const Status& object2);
        friend UAF_EXPORT bool operator!=(const Status& object1, const Status& object2);
        friend UAF_EXPORT bool operator<(const Status& object1, const Status& object2);

    private:
        Status* raisedBy_;

        void copyErrors(const Status& from);
    };
}



#endif /* UAF_STATUS_H */
