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

#include "uaf/util/status.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::vector;


    // Constructor
    // =============================================================================================
    Status::Status(const Status& other)
    {
        copyErrors(other);
        statusCode = other.statusCode;

        if (other.isRaisedBy())
        {
            raisedBy_ = new Status(*other.raisedBy_);
        }
        else
        {
            raisedBy_ = NULL;
        }
    }


    // Assignment operator
    // =============================================================================================
    Status& Status::operator=(const Status& other)
    {
        // protect for self-assignment
        if (&other != this)
        {
            clearRaisedBy();
            copyErrors(other);
            statusCode = other.statusCode;
            if (other.isRaisedBy())
            {
                raisedBy_ = new Status(*other.raisedBy_);
            }
            else
            {
                raisedBy_ = NULL;
            }
        }
        return *this;
    }


    // Destructor
    // =============================================================================================
    Status::~Status()
    {
        clearRaisedBy();
    }


    // Clear the internal variables
    // =============================================================================================
    void Status::clearRaisedBy()
    {
        if (isRaisedBy())
        {
            delete raisedBy_;
            raisedBy_ = NULL;
        }
    }

    // Make a summary from other Statuses
    // =============================================================================================
    void Status::summarize(const vector<Status>& statuses)
    {
        uint32_t noOfGood      = 0;
        uint32_t noOfUncertain = 0;
        uint32_t noOfBad       = 0;
        for (vector<Status>::const_iterator it = statuses.begin(); it != statuses.end(); ++it)
        {
            if      (it->isGood())      noOfGood++;
            else if (it->isUncertain()) noOfUncertain++;
            else if (it->isBad())       noOfBad++;
        }

        if (statuses.size() == 0)
        {
            statusCode = uaf::statuscodes::NoStatusesGivenError;
            raisedBy_NoStatusesGivenError = NoStatusesGivenError();
        }
        else if (noOfGood == statuses.size())
            statusCode = uaf::statuscodes::Good;
        else if (noOfUncertain > 0 && noOfBad == 0)
            statusCode = uaf::statuscodes::Uncertain;
        else
        {
            statusCode = uaf::statuscodes::BadStatusesPresentError;
            raisedBy_BadStatusesPresentError = BadStatusesPresentError(noOfGood, noOfUncertain, noOfBad);
        }
    }


    // set the status to Good
    // =============================================================================================
    void Status::setGood()
    {
        clearRaisedBy();
        statusCode = uaf::statuscodes::Good;
    }

    // set the status to Uncertain
    // =============================================================================================
    void Status::setUncertain()
    {
        clearRaisedBy();
        statusCode = uaf::statuscodes::Uncertain;
    }


    // Add the status that caused this status (i.e. the current instance).
    // =============================================================================================
    void Status::setRaisedBy(const Status& status)
    {
        raisedBy_ = new uaf::Status(status);
    }

    // Check if this status is raised by some other status.
    // =============================================================================================
    bool Status::isRaisedBy() const
    {
        return raisedBy_ != NULL;
    }

    // If this status is raised by some other status, get a copy of this other status.
    // =============================================================================================
    Status Status::raisedBy() const
    {
        if (isRaisedBy())
            return *raisedBy_;
        else
            return Status();
    }

    // Get the name of the status code.
    // =============================================================================================
    string Status::statusCodeName() const
    {
       return uaf::statuscodes::toString(statusCode);
    }



#define UAF_STATUS_COPY_ERROR(ERROR)       \
        raisedBy_##ERROR = from.raisedBy_##ERROR;

    void Status::copyErrors(const Status& from)
    {
        //UAF_STATUS_COPY_ERROR(DiscoveryError)
        //UAF_STATUS_COPY_ERROR(InvalidRequestError)
        //UAF_STATUS_COPY_ERROR(ResolutionError)
        UAF_STATUS_COPY_ERROR(FindServersError)
        UAF_STATUS_COPY_ERROR(UnknownServerError)
        UAF_STATUS_COPY_ERROR(EmptyUrlError)
        UAF_STATUS_COPY_ERROR(NoParallelFindServersAllowedError)
        UAF_STATUS_COPY_ERROR(NoDiscoveryUrlsFoundError)
        UAF_STATUS_COPY_ERROR(ServerCertificateRejectedByUserError)
        UAF_STATUS_COPY_ERROR(ServerCertificateSavingError)
        UAF_STATUS_COPY_ERROR(OpenSSLStoreInitializationError)
        UAF_STATUS_COPY_ERROR(ClientCertificateLoadingError)
        UAF_STATUS_COPY_ERROR(ServerDidNotProvideCertificateError)
        //UAF_STATUS_COPY_ERROR(ConnectionError)
        UAF_STATUS_COPY_ERROR(PathNotExistsError)
        UAF_STATUS_COPY_ERROR(NoSecuritySettingsGivenError)
        UAF_STATUS_COPY_ERROR(PathCreationError)
        UAF_STATUS_COPY_ERROR(SecuritySettingsMatchError)
        UAF_STATUS_COPY_ERROR(WrongTypeError)
        UAF_STATUS_COPY_ERROR(UnexpectedError)
        UAF_STATUS_COPY_ERROR(ServerArrayConversionError)
        UAF_STATUS_COPY_ERROR(NamespaceArrayConversionError)
        UAF_STATUS_COPY_ERROR(BadNamespaceArrayError)
        UAF_STATUS_COPY_ERROR(BadServerArrayError)
        UAF_STATUS_COPY_ERROR(UnknownServerIndexError)
        UAF_STATUS_COPY_ERROR(InvalidAddressError)
        UAF_STATUS_COPY_ERROR(UnknownNamespaceUriError)
        UAF_STATUS_COPY_ERROR(NoNamespaceIndexOrUriGivenError)
        UAF_STATUS_COPY_ERROR(UnknownNamespaceIndexError)
        UAF_STATUS_COPY_ERROR(EmptyServerUriAndUnknownNamespaceIndexError)
        UAF_STATUS_COPY_ERROR(ExpandedNodeIdAddressExpectedError)
        UAF_STATUS_COPY_ERROR(EmptyServerUriError)
        UAF_STATUS_COPY_ERROR(UnsupportedError)
        UAF_STATUS_COPY_ERROR(UnsupportedNodeIdIdentifierTypeError)
        UAF_STATUS_COPY_ERROR(SyncInvocationNotSupportedError)
        UAF_STATUS_COPY_ERROR(AsyncInvocationNotSupportedError)
        UAF_STATUS_COPY_ERROR(NoStatusesGivenError)
        UAF_STATUS_COPY_ERROR(BadStatusesPresentError)
        UAF_STATUS_COPY_ERROR(NotAllTargetsCouldBeResolvedError)
        UAF_STATUS_COPY_ERROR(InvalidServerUriError)
        UAF_STATUS_COPY_ERROR(SubscriptionNotCreatedError)
        UAF_STATUS_COPY_ERROR(NoTargetsGivenError)
        UAF_STATUS_COPY_ERROR(DataDontMatchAddressesError)
        UAF_STATUS_COPY_ERROR(ItemNotFoundForTheGivenHandleError)
        UAF_STATUS_COPY_ERROR(TargetRankOutOfBoundsError)
        UAF_STATUS_COPY_ERROR(NoItemFoundForTheGivenRequestHandleError)
        UAF_STATUS_COPY_ERROR(ContinuationPointsDontMatchAddressesError)
        UAF_STATUS_COPY_ERROR(UnknownNamespaceIndexAndServerIndexError)
        UAF_STATUS_COPY_ERROR(AsyncMultiMethodCallNotSupportedError)
        UAF_STATUS_COPY_ERROR(EmptyAddressError)
        UAF_STATUS_COPY_ERROR(MultipleTranslationResultsError)
        UAF_STATUS_COPY_ERROR(UnknownClientSubscriptionHandleError)
        UAF_STATUS_COPY_ERROR(UnknownClientHandleError)
        UAF_STATUS_COPY_ERROR(UnknownClientConnectionIdError)
        UAF_STATUS_COPY_ERROR(AsyncConnectionFailedError)
        UAF_STATUS_COPY_ERROR(ConnectionFailedError)
        UAF_STATUS_COPY_ERROR(SessionSecuritySettingsDontMatchEndpointError)
        UAF_STATUS_COPY_ERROR(CouldNotManuallyUnsubscribeError)
        UAF_STATUS_COPY_ERROR(CouldNotManuallySubscribeError)
        UAF_STATUS_COPY_ERROR(SessionNotConnectedError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotSetMonitoringModeError)
        UAF_STATUS_COPY_ERROR(CreateSubscriptionError)
        UAF_STATUS_COPY_ERROR(DeleteSubscriptionError)
        UAF_STATUS_COPY_ERROR(SubscriptionHasBeenDeletedError)
        UAF_STATUS_COPY_ERROR(SetMonitoringModeInvocationError)
        UAF_STATUS_COPY_ERROR(NoDiscoveryUrlsExposedByServerError)
        UAF_STATUS_COPY_ERROR(GetEndpointsError)
        UAF_STATUS_COPY_ERROR(NoEndpointsProvidedByServerError)
        UAF_STATUS_COPY_ERROR(DisconnectionFailedError)
        UAF_STATUS_COPY_ERROR(NoConnectedSessionToUpdateArraysError)
        UAF_STATUS_COPY_ERROR(BadDataReceivedError)


        // service errors
        //UAF_STATUS_COPY_ERROR(ServiceError)
        UAF_STATUS_COPY_ERROR(CouldNotReadArraysError)
        UAF_STATUS_COPY_ERROR(CreateMonitoredItemsError)
        UAF_STATUS_COPY_ERROR(CreateMonitoredItemsInvocationError)
        UAF_STATUS_COPY_ERROR(BeginCreateMonitoredItemsInvocationError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotCreateMonitoredItemsError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotBrowseNextError)
        UAF_STATUS_COPY_ERROR(BrowseNextInvocationError)
        UAF_STATUS_COPY_ERROR(ReadInvocationError)
        UAF_STATUS_COPY_ERROR(BeginReadInvocationError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotReadError)
        UAF_STATUS_COPY_ERROR(TranslateBrowsePathsToNodeIdsInvocationError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotTranslateBrowsePathsToNodeIdsError)
        UAF_STATUS_COPY_ERROR(HistoryReadInvocationError)
        UAF_STATUS_COPY_ERROR(HistoryReadRawModifiedInvocationError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotHistoryReadError)
        UAF_STATUS_COPY_ERROR(MethodCallInvocationError)
        UAF_STATUS_COPY_ERROR(AsyncMethodCallInvocationError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotCallMethodError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotBrowseError)
        UAF_STATUS_COPY_ERROR(BrowseInvocationError)
        UAF_STATUS_COPY_ERROR(WriteInvocationError)
        UAF_STATUS_COPY_ERROR(AsyncWriteInvocationError)
        UAF_STATUS_COPY_ERROR(ServerCouldNotWriteError)
        UAF_STATUS_COPY_ERROR(CallCompleteError)
        UAF_STATUS_COPY_ERROR(InputArgumentError)
        UAF_STATUS_COPY_ERROR(ReadCompleteError)
        UAF_STATUS_COPY_ERROR(WriteCompleteError)
        UAF_STATUS_COPY_ERROR(EmptyUserCertificateError)
        UAF_STATUS_COPY_ERROR(InvalidPrivateKeyError)
        UAF_STATUS_COPY_ERROR(SetPublishingModeInvocationError)

        // configuration errors
        UAF_STATUS_COPY_ERROR(ConfigurationError)
        UAF_STATUS_COPY_ERROR(CouldNotCreateCertificateTrustListLocationError)
        UAF_STATUS_COPY_ERROR(CouldNotCreateCertificateRevocationListLocationError)
        UAF_STATUS_COPY_ERROR(CouldNotCreateIssuersCertificateLocationError)
        UAF_STATUS_COPY_ERROR(CouldNotCreateIssuersRevocationListLocationError)
        UAF_STATUS_COPY_ERROR(CouldNotCreateClientPrivateKeyLocationError)
        UAF_STATUS_COPY_ERROR(CouldNotCreateClientCertificateLocationError)
    }

#define UAF_STATUS_TOSTRING_IF(ERROR)       \
        if (statusCode == uaf::statuscodes::ERROR) return raisedBy_##ERROR.message;
#define UAF_STATUS_TOSTRING_ELSE_IF(ERROR)       \
        else UAF_STATUS_TOSTRING_IF(ERROR)

    // get a string representation
    // =============================================================================================
    string Status::toString() const
    {
        //UAF_STATUS_TOSTRING_IF(DiscoveryError)
        //UAF_STATUS_TOSTRING_ELSE_IF(InvalidRequestError)
        //UAF_STATUS_TOSTRING_ELSE_IF(ResolutionError)
        UAF_STATUS_TOSTRING_IF(FindServersError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownServerError)
        UAF_STATUS_TOSTRING_ELSE_IF(EmptyUrlError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoParallelFindServersAllowedError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoDiscoveryUrlsFoundError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCertificateRejectedByUserError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCertificateSavingError)
        UAF_STATUS_TOSTRING_ELSE_IF(OpenSSLStoreInitializationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ClientCertificateLoadingError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerDidNotProvideCertificateError)
        //UAF_STATUS_TOSTRING_ELSE_IF(ConnectionError)
        UAF_STATUS_TOSTRING_ELSE_IF(PathNotExistsError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoSecuritySettingsGivenError)
        UAF_STATUS_TOSTRING_ELSE_IF(PathCreationError)
        UAF_STATUS_TOSTRING_ELSE_IF(SecuritySettingsMatchError)
        UAF_STATUS_TOSTRING_ELSE_IF(WrongTypeError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnexpectedError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerArrayConversionError)
        UAF_STATUS_TOSTRING_ELSE_IF(NamespaceArrayConversionError)
        UAF_STATUS_TOSTRING_ELSE_IF(BadNamespaceArrayError)
        UAF_STATUS_TOSTRING_ELSE_IF(BadServerArrayError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownServerIndexError)
        UAF_STATUS_TOSTRING_ELSE_IF(InvalidAddressError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownNamespaceUriError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoNamespaceIndexOrUriGivenError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownNamespaceIndexError)
        UAF_STATUS_TOSTRING_ELSE_IF(EmptyServerUriAndUnknownNamespaceIndexError)
        UAF_STATUS_TOSTRING_ELSE_IF(ExpandedNodeIdAddressExpectedError)
        UAF_STATUS_TOSTRING_ELSE_IF(EmptyServerUriError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnsupportedError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnsupportedNodeIdIdentifierTypeError)
        UAF_STATUS_TOSTRING_ELSE_IF(SyncInvocationNotSupportedError)
        UAF_STATUS_TOSTRING_ELSE_IF(AsyncInvocationNotSupportedError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoStatusesGivenError)
        UAF_STATUS_TOSTRING_ELSE_IF(BadStatusesPresentError)
        UAF_STATUS_TOSTRING_ELSE_IF(NotAllTargetsCouldBeResolvedError)
        UAF_STATUS_TOSTRING_ELSE_IF(InvalidServerUriError)
        UAF_STATUS_TOSTRING_ELSE_IF(SubscriptionNotCreatedError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoTargetsGivenError)
        UAF_STATUS_TOSTRING_ELSE_IF(DataDontMatchAddressesError)
        UAF_STATUS_TOSTRING_ELSE_IF(ItemNotFoundForTheGivenHandleError)
        UAF_STATUS_TOSTRING_ELSE_IF(TargetRankOutOfBoundsError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoItemFoundForTheGivenRequestHandleError)
        UAF_STATUS_TOSTRING_ELSE_IF(ContinuationPointsDontMatchAddressesError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownNamespaceIndexAndServerIndexError)
        UAF_STATUS_TOSTRING_ELSE_IF(AsyncMultiMethodCallNotSupportedError)
        UAF_STATUS_TOSTRING_ELSE_IF(EmptyAddressError)
        UAF_STATUS_TOSTRING_ELSE_IF(MultipleTranslationResultsError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownClientSubscriptionHandleError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownClientHandleError)
        UAF_STATUS_TOSTRING_ELSE_IF(UnknownClientConnectionIdError)
        UAF_STATUS_TOSTRING_ELSE_IF(AsyncConnectionFailedError)
        UAF_STATUS_TOSTRING_ELSE_IF(ConnectionFailedError)
        UAF_STATUS_TOSTRING_ELSE_IF(SessionSecuritySettingsDontMatchEndpointError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotManuallyUnsubscribeError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotManuallySubscribeError)
        UAF_STATUS_TOSTRING_ELSE_IF(SessionNotConnectedError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotSetMonitoringModeError)
        UAF_STATUS_TOSTRING_ELSE_IF(CreateSubscriptionError)
        UAF_STATUS_TOSTRING_ELSE_IF(DeleteSubscriptionError)
        UAF_STATUS_TOSTRING_ELSE_IF(SubscriptionHasBeenDeletedError)
        UAF_STATUS_TOSTRING_ELSE_IF(SetMonitoringModeInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoDiscoveryUrlsExposedByServerError)
        UAF_STATUS_TOSTRING_ELSE_IF(GetEndpointsError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoEndpointsProvidedByServerError)
        UAF_STATUS_TOSTRING_ELSE_IF(DisconnectionFailedError)
        UAF_STATUS_TOSTRING_ELSE_IF(NoConnectedSessionToUpdateArraysError)
        UAF_STATUS_TOSTRING_ELSE_IF(BadDataReceivedError)


        // service errors
        //UAF_STATUS_TOSTRING_ELSE_IF(ServiceError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotReadArraysError)
        UAF_STATUS_TOSTRING_ELSE_IF(CreateMonitoredItemsError)
        UAF_STATUS_TOSTRING_ELSE_IF(CreateMonitoredItemsInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(BeginCreateMonitoredItemsInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotCreateMonitoredItemsError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotBrowseNextError)
        UAF_STATUS_TOSTRING_ELSE_IF(BrowseNextInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ReadInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(BeginReadInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotReadError)
        UAF_STATUS_TOSTRING_ELSE_IF(TranslateBrowsePathsToNodeIdsInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotTranslateBrowsePathsToNodeIdsError)
        UAF_STATUS_TOSTRING_ELSE_IF(HistoryReadInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(HistoryReadRawModifiedInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotHistoryReadError)
        UAF_STATUS_TOSTRING_ELSE_IF(MethodCallInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(AsyncMethodCallInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotCallMethodError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotBrowseError)
        UAF_STATUS_TOSTRING_ELSE_IF(BrowseInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(WriteInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(AsyncWriteInvocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(ServerCouldNotWriteError)
        UAF_STATUS_TOSTRING_ELSE_IF(CallCompleteError)
        UAF_STATUS_TOSTRING_ELSE_IF(InputArgumentError)
        UAF_STATUS_TOSTRING_ELSE_IF(ReadCompleteError)
        UAF_STATUS_TOSTRING_ELSE_IF(WriteCompleteError)
        UAF_STATUS_TOSTRING_ELSE_IF(EmptyUserCertificateError)
        UAF_STATUS_TOSTRING_ELSE_IF(InvalidPrivateKeyError)
        UAF_STATUS_TOSTRING_ELSE_IF(SetPublishingModeInvocationError)

        // configuration errors
        UAF_STATUS_TOSTRING_ELSE_IF(ConfigurationError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotCreateCertificateTrustListLocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotCreateCertificateRevocationListLocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotCreateIssuersCertificateLocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotCreateIssuersRevocationListLocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotCreateClientPrivateKeyLocationError)
        UAF_STATUS_TOSTRING_ELSE_IF(CouldNotCreateClientCertificateLocationError)

        else if (isUncertain())
            return "Uncertain";
        else if (isGood())
            return "Good";
        else if (isBad())
            return "Bad";
        else
            return "UNKNOWN!";
    }

    // operator==
    // =============================================================================================
    bool operator==(const Status& object1, const Status& object2)
    {
        return    object1.statusCode == object2.statusCode
               && object1.toString() == object2.toString();
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const Status& object1, const Status& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const Status& object1, const Status& object2)
    {
        if (object1.statusCode != object2.statusCode)
            return object1.statusCode < object2.statusCode;
        else
            return object1.toString() < object2.toString();
    }
}

