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

#include "uaf/util/statuscodes.h"

namespace uaf
{
    namespace statuscodes
    {

        using namespace uaf::statuscodes;

#define UAF_STATUSCODES_TOSTRING(ERROR)       \
        case ERROR: return #ERROR;

        // Get a string representation
        // =========================================================================================
        std::string toString(StatusCode code)
        {
            switch (code)
            {
                UAF_STATUSCODES_TOSTRING(Good)
                UAF_STATUSCODES_TOSTRING(Uncertain)
                UAF_STATUSCODES_TOSTRING(DiscoveryError)
                UAF_STATUSCODES_TOSTRING(InvalidRequestError)
                UAF_STATUSCODES_TOSTRING(FindServersError)
                UAF_STATUSCODES_TOSTRING(UnknownServerError)
                UAF_STATUSCODES_TOSTRING(EmptyUrlError)
                UAF_STATUSCODES_TOSTRING(NoParallelFindServersAllowedError)
                UAF_STATUSCODES_TOSTRING(NoDiscoveryUrlsFoundError)
                UAF_STATUSCODES_TOSTRING(ServerCertificateRejectedByUserError)
                UAF_STATUSCODES_TOSTRING(ServerCertificateSavingError)
                UAF_STATUSCODES_TOSTRING(OpenSSLStoreInitializationError)
                UAF_STATUSCODES_TOSTRING(ClientCertificateLoadingError)
                UAF_STATUSCODES_TOSTRING(ServerDidNotProvideCertificateError)
                UAF_STATUSCODES_TOSTRING(ConnectionError)
                UAF_STATUSCODES_TOSTRING(ConnectionFailedError)
                UAF_STATUSCODES_TOSTRING(SecurityError)
                UAF_STATUSCODES_TOSTRING(PathNotExistsError)
                UAF_STATUSCODES_TOSTRING(NoSecuritySettingsGivenError)
                UAF_STATUSCODES_TOSTRING(PathCreationError)
                UAF_STATUSCODES_TOSTRING(SecuritySettingsMatchError)
                UAF_STATUSCODES_TOSTRING(WrongTypeError)
                UAF_STATUSCODES_TOSTRING(UnexpectedError)
                UAF_STATUSCODES_TOSTRING(ServerArrayConversionError)
                UAF_STATUSCODES_TOSTRING(NamespaceArrayConversionError)
                UAF_STATUSCODES_TOSTRING(BadNamespaceArrayError)
                UAF_STATUSCODES_TOSTRING(BadServerArrayError)
                UAF_STATUSCODES_TOSTRING(UnknownServerIndexError)
                UAF_STATUSCODES_TOSTRING(InvalidAddressError)
                UAF_STATUSCODES_TOSTRING(UnknownNamespaceUriError)
                UAF_STATUSCODES_TOSTRING(NoNamespaceIndexOrUriGivenError)
                UAF_STATUSCODES_TOSTRING(UnknownNamespaceIndexError)
                UAF_STATUSCODES_TOSTRING(EmptyServerUriAndUnknownNamespaceIndexError)
                UAF_STATUSCODES_TOSTRING(ExpandedNodeIdAddressExpectedError)
                UAF_STATUSCODES_TOSTRING(EmptyServerUriError)
                UAF_STATUSCODES_TOSTRING(UnsupportedError)
                UAF_STATUSCODES_TOSTRING(UnsupportedNodeIdIdentifierTypeError)
                UAF_STATUSCODES_TOSTRING(SyncInvocationNotSupportedError)
                UAF_STATUSCODES_TOSTRING(AsyncInvocationNotSupportedError)
                UAF_STATUSCODES_TOSTRING(NoStatusesGivenError)
                UAF_STATUSCODES_TOSTRING(BadStatusesPresentError)
                UAF_STATUSCODES_TOSTRING(NotAllTargetsCouldBeResolvedError)
                UAF_STATUSCODES_TOSTRING(InvalidServerUriError)
                UAF_STATUSCODES_TOSTRING(SubscriptionNotCreatedError)
                UAF_STATUSCODES_TOSTRING(NoTargetsGivenError)
                UAF_STATUSCODES_TOSTRING(DataDontMatchAddressesError)
                UAF_STATUSCODES_TOSTRING(ItemNotFoundForTheGivenHandleError)
                UAF_STATUSCODES_TOSTRING(TargetRankOutOfBoundsError)
                UAF_STATUSCODES_TOSTRING(NoItemFoundForTheGivenRequestHandleError)
                UAF_STATUSCODES_TOSTRING(ContinuationPointsDontMatchAddressesError)
                UAF_STATUSCODES_TOSTRING(UnknownNamespaceIndexAndServerIndexError)
                UAF_STATUSCODES_TOSTRING(AsyncMultiMethodCallNotSupportedError)
                UAF_STATUSCODES_TOSTRING(EmptyAddressError)
                UAF_STATUSCODES_TOSTRING(MultipleTranslationResultsError)
                UAF_STATUSCODES_TOSTRING(UnknownClientSubscriptionHandleError)
                UAF_STATUSCODES_TOSTRING(UnknownClientHandleError)
                UAF_STATUSCODES_TOSTRING(UnknownClientConnectionIdError)
                UAF_STATUSCODES_TOSTRING(AsyncConnectionFailedError)
                UAF_STATUSCODES_TOSTRING(EmptyUserCertificateError)
                UAF_STATUSCODES_TOSTRING(InvalidPrivateKeyError)
                UAF_STATUSCODES_TOSTRING(SessionSecuritySettingsDontMatchEndpointError)
                UAF_STATUSCODES_TOSTRING(CouldNotManuallyUnsubscribeError)
                UAF_STATUSCODES_TOSTRING(CouldNotManuallySubscribeError)
                UAF_STATUSCODES_TOSTRING(SessionNotConnectedError)
                UAF_STATUSCODES_TOSTRING(SubscriptionHasBeenDeletedError)
                UAF_STATUSCODES_TOSTRING(NoDiscoveryUrlsExposedByServerError)
                UAF_STATUSCODES_TOSTRING(GetEndpointsError)
                UAF_STATUSCODES_TOSTRING(NoEndpointsProvidedByServerError)
                UAF_STATUSCODES_TOSTRING(DisconnectionFailedError)
                UAF_STATUSCODES_TOSTRING(NoConnectedSessionToUpdateArraysError)
                UAF_STATUSCODES_TOSTRING(BadDataReceivedError)
                UAF_STATUSCODES_TOSTRING(ServiceError)
                UAF_STATUSCODES_TOSTRING(CouldNotReadArraysError)
                UAF_STATUSCODES_TOSTRING(CreateMonitoredItemsError)
                UAF_STATUSCODES_TOSTRING(CreateMonitoredItemsInvocationError)
                UAF_STATUSCODES_TOSTRING(BeginCreateMonitoredItemsInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotCreateMonitoredItemsError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotBrowseNextError)
                UAF_STATUSCODES_TOSTRING(BrowseNextInvocationError)
                UAF_STATUSCODES_TOSTRING(ReadInvocationError)
                UAF_STATUSCODES_TOSTRING(BeginReadInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotReadError)
                UAF_STATUSCODES_TOSTRING(TranslateBrowsePathsToNodeIdsInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotTranslateBrowsePathsToNodeIdsError)
                UAF_STATUSCODES_TOSTRING(HistoryReadInvocationError)
                UAF_STATUSCODES_TOSTRING(HistoryReadRawModifiedInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotHistoryReadError)
                UAF_STATUSCODES_TOSTRING(MethodCallInvocationError)
                UAF_STATUSCODES_TOSTRING(AsyncMethodCallInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotCallMethodError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotBrowseError)
                UAF_STATUSCODES_TOSTRING(BrowseInvocationError)
                UAF_STATUSCODES_TOSTRING(WriteInvocationError)
                UAF_STATUSCODES_TOSTRING(AsyncWriteInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotWriteError)
                UAF_STATUSCODES_TOSTRING(CallCompleteError)
                UAF_STATUSCODES_TOSTRING(InputArgumentError)
                UAF_STATUSCODES_TOSTRING(ReadCompleteError)
                UAF_STATUSCODES_TOSTRING(WriteCompleteError)
                UAF_STATUSCODES_TOSTRING(SubscriptionError)
                UAF_STATUSCODES_TOSTRING(SetPublishingModeInvocationError)
                UAF_STATUSCODES_TOSTRING(ServerCouldNotSetMonitoringModeError)
                UAF_STATUSCODES_TOSTRING(CreateSubscriptionError)
                UAF_STATUSCODES_TOSTRING(DeleteSubscriptionError)
                UAF_STATUSCODES_TOSTRING(SetMonitoringModeInvocationError)
                UAF_STATUSCODES_TOSTRING(ConfigurationError)
                UAF_STATUSCODES_TOSTRING(CouldNotCreateCertificateTrustListLocationError)
                UAF_STATUSCODES_TOSTRING(CouldNotCreateCertificateRevocationListLocationError)
                UAF_STATUSCODES_TOSTRING(CouldNotCreateIssuersCertificateLocationError)
                UAF_STATUSCODES_TOSTRING(CouldNotCreateIssuersRevocationListLocationError)
                UAF_STATUSCODES_TOSTRING(CouldNotCreateClientPrivateKeyLocationError)
                UAF_STATUSCODES_TOSTRING(CouldNotCreateClientCertificateLocationError)
                // status codes kept for backwards compatibility:
                UAF_STATUSCODES_TOSTRING(DataFormatError)
                UAF_STATUSCODES_TOSTRING(DataSizeError)
                UAF_STATUSCODES_TOSTRING(DataSourceError)
                UAF_STATUSCODES_TOSTRING(DisconnectionError)
                UAF_STATUSCODES_TOSTRING(LowLevelError)
                UAF_STATUSCODES_TOSTRING(OtherError)
                UAF_STATUSCODES_TOSTRING(TimeoutError)
                UAF_STATUSCODES_TOSTRING(NoResultReceivedError)
                UAF_STATUSCODES_TOSTRING(UnknownHandleError)
                default:
                    return "UNKNOWN!";
            }
        }


    }
}
