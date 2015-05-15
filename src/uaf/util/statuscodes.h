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

#ifndef UAF_STATUSCODES_H_
#define UAF_STATUSCODES_H_

// STD
#include <string>
#include <vector>
// SDK
#include "uabase/uaplatformlayer.h"
// UAF
#include "uaf/util/util.h"


/** @file */


namespace uaf
{

    namespace statuscodes
    {

        /**
         * This enum defines the status codes as specified by the UAF.
         *
         * @ingroup Util
         */
        enum StatusCode
        {
            Good,
            Uncertain,
            DiscoveryError,
            ResolutionError,
            InvalidRequestError,
            FindServersError,
            UnknownServerError,
            EmptyUrlError,
            NoParallelFindServersAllowedError,
            NoDiscoveryUrlsFoundError,
            ServerCertificateRejectedByUserError,
            ServerCertificateSavingError,
            OpenSSLStoreInitializationError,
            ClientCertificateLoadingError,
            ServerDidNotProvideCertificateError,
            ConnectionError,
            PathNotExistsError,
            SecurityError,
            NoSecuritySettingsGivenError,
            PathCreationError,
            SecuritySettingsMatchError,
            WrongTypeError,
            UnexpectedError,
            ServerArrayConversionError,
            NamespaceArrayConversionError,
            BadNamespaceArrayError,
            BadServerArrayError,
            UnknownServerIndexError,
            InvalidAddressError,
            UnknownNamespaceUriError,
            NoNamespaceIndexOrUriGivenError,
            UnknownNamespaceIndexError,
            EmptyServerUriAndUnknownNamespaceIndexError,
            ExpandedNodeIdAddressExpectedError,
            EmptyServerUriError,
            UnsupportedError,
            UnsupportedNodeIdIdentifierTypeError,
            SyncInvocationNotSupportedError,
            AsyncInvocationNotSupportedError,
            NoStatusesGivenError,
            BadStatusesPresentError,
            NotAllTargetsCouldBeResolvedError,
            InvalidServerUriError,
            SubscriptionNotCreatedError,
            NoTargetsGivenError,
            DataDontMatchAddressesError,
            ItemNotFoundForTheGivenHandleError,
            TargetRankOutOfBoundsError,
            NoItemFoundForTheGivenRequestHandleError,
            ContinuationPointsDontMatchAddressesError,
            UnknownNamespaceIndexAndServerIndexError,
            AsyncMultiMethodCallNotSupportedError,
            EmptyAddressError,
            MultipleTranslationResultsError,
            UnknownClientSubscriptionHandleError,
            UnknownClientHandleError,
            UnknownClientConnectionIdError,
            AsyncConnectionFailedError,
            ConnectionFailedError,
            EmptyUserCertificateError,
            InvalidPrivateKeyError,
            SessionSecuritySettingsDontMatchEndpointError,
            CouldNotManuallyUnsubscribeError,
            CouldNotManuallySubscribeError,
            SessionNotConnectedError,
            SubscriptionHasBeenDeletedError,
            NoDiscoveryUrlsExposedByServerError,
            GetEndpointsError,
            NoEndpointsProvidedByServerError,
            DisconnectionFailedError,
            NoConnectedSessionToUpdateArraysError,
            BadDataReceivedError,
            ServiceError,
            CouldNotReadArraysError,
            CreateMonitoredItemsError,
            CreateMonitoredItemsInvocationError,
            BeginCreateMonitoredItemsInvocationError,
            ServerCouldNotCreateMonitoredItemsError,
            ServerCouldNotBrowseNextError,
            BrowseNextInvocationError,
            ReadInvocationError,
            BeginReadInvocationError,
            ServerCouldNotReadError,
            TranslateBrowsePathsToNodeIdsInvocationError,
            ServerCouldNotTranslateBrowsePathsToNodeIdsError,
            HistoryReadInvocationError,
            HistoryReadRawModifiedInvocationError,
            ServerCouldNotHistoryReadError,
            MethodCallInvocationError,
            AsyncMethodCallInvocationError,
            ServerCouldNotCallMethodError,
            ServerCouldNotBrowseError,
            BrowseInvocationError,
            WriteInvocationError,
            AsyncWriteInvocationError,
            ServerCouldNotWriteError,
            CallCompleteError,
            InputArgumentError,
            ReadCompleteError,
            WriteCompleteError,
            SubscriptionError,
            SetPublishingModeInvocationError,
            ServerCouldNotSetMonitoringModeError,
            CreateSubscriptionError,
            DeleteSubscriptionError,
            SetMonitoringModeInvocationError,
            ConfigurationError,
            CouldNotCreateCertificateTrustListLocationError,
            CouldNotCreateCertificateRevocationListLocationError,
            CouldNotCreateIssuersCertificateLocationError,
            CouldNotCreateIssuersRevocationListLocationError,
            CouldNotCreateClientPrivateKeyLocationError,
            CouldNotCreateClientCertificateLocationError,
            // status codes kept for backwards compatibility:
            DataFormatError,
            DataSizeError,
            DataSourceError,
            DisconnectionError,
            LowLevelError,
            OtherError,
            TimeoutError,
            NoResultReceivedError,
            UnknownHandleError
        };


        /**
         * Get a string representation of the status code.
         *
         * @param code  The status code (as an enum).
         * @return      The corresponding name of the status code.
         *
         * @ingroup Util
         */
        std::string UAF_EXPORT toString(uaf::statuscodes::StatusCode code);



    }


}


#endif /* UAF_STATUSCODES_H_ */
