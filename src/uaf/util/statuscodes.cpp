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



        // Get a string representation
        // =========================================================================================
        std::string toString(StatusCode code)
        {
            switch (code)
            {
                case Good:                      return "Good";
                case Uncertain:                 return "Uncertain";
                case ConfigurationError:        return "ConfigurationError";
                case ConnectionError:           return "ConnectionError";
                case DataFormatError:           return "DataFormatError";
                case DataSizeError:             return "DataSizeError";
                case DataSourceError:           return "DataSourceError";
                case DisconnectionError:        return "DisconnectionError";
                case DiscoveryError:            return "DiscoveryError";
                case InvalidRequestError:       return "InvalidRequestError";
                case LowLevelError:             return "LowLevelError";
                case ResolutionError:           return "ResolutionError";
                case WrongTypeError:            return "WrongTypeError";
                case OtherError:                return "OtherError";
                case SecurityError:             return "SecurityError";
                case TimeoutError:              return "TimeoutError";
                case SubscriptionError:         return "SubscriptionError";
                case NoResultReceivedError:     return "NoResultReceivedError";
                case UnexpectedError:           return "UnexpectedError";
                case UnknownHandleError:        return "UnknownHandleError";
                case UnsupportedError:          return "UnsupportedError";
                default:                        return "UnknownStatusCodeBUG";
            }
        }


        // Convert the SDK/Stack instance to a UAF instance.
        // =========================================================================================
        StatusCode fromSdkToUaf(OpcUa_StatusCode uaCode)
        {
            StatusCode code;
            switch (uaCode)
            {
                case OpcUa_Good:
                case OpcUa_GoodResultsMayBeIncomplete:
                case OpcUa_GoodLocalOverride:
                case OpcUa_GoodEntryInserted:
                case OpcUa_GoodEntryReplaced:
                case OpcUa_GoodNoData:
                case OpcUa_GoodMoreData:
                case OpcUa_GoodDataIgnored:
                case OpcUa_GoodCommunicationEvent:
                case OpcUa_GoodShutdownEvent:
                case OpcUa_GoodCallAgain:
                case OpcUa_GoodNonCriticalTimeout:
                                                        code = Good;
                                                        break;
                case OpcUa_Uncertain:
                case OpcUa_UncertainNotAllNodesAvailable:
                case OpcUa_UncertainReferenceOutOfServer:
                case OpcUa_UncertainNoCommunicationLastUsableValue:
                case OpcUa_UncertainLastUsableValue:
                case OpcUa_UncertainSubstituteValue:
                case OpcUa_UncertainInitialValue:
                case OpcUa_UncertainSensorNotAccurate:
                case OpcUa_UncertainEngineeringUnitsExceeded:
                case OpcUa_UncertainSubNormal:
                case OpcUa_UncertainDataSubNormal:
                                                        code = Uncertain;
                                                        break;
                case OpcUa_BadNodeIdInvalid:
                case OpcUa_BadNodeIdUnknown:
                case OpcUa_BadAttributeIdInvalid:
                case OpcUa_BadObjectDeleted:
                case OpcUa_BadParentNodeIdInvalid:
                                                        code = ResolutionError;
                                                        break;
                case OpcUa_BadUserAccessDenied:
                case OpcUa_BadCertificateInvalid:
                case OpcUa_BadSecurityChecksFailed:
                case OpcUa_BadCertificateTimeInvalid:
                case OpcUa_BadCertificateIssuerTimeInvalid:
                case OpcUa_BadCertificateHostNameInvalid:
                case OpcUa_BadCertificateUriInvalid:
                case OpcUa_BadCertificateUseNotAllowed:
                case OpcUa_BadCertificateIssuerUseNotAllowed:
                case OpcUa_BadCertificateUntrusted:
                case OpcUa_BadCertificateRevocationUnknown:
                case OpcUa_BadCertificateIssuerRevocationUnknown:
                case OpcUa_BadCertificateRevoked:
                case OpcUa_BadCertificateIssuerRevoked:
                case OpcUa_BadIdentityTokenInvalid:
                case OpcUa_BadIdentityTokenRejected:
                case OpcUa_BadSecureChannelIdInvalid:
                case OpcUa_BadNonceInvalid:
                case OpcUa_BadSecurityModeRejected:
                case OpcUa_BadSecurityPolicyRejected:
                case OpcUa_BadUserSignatureInvalid:
                case OpcUa_BadApplicationSignatureInvalid:
                case OpcUa_BadNoValidCertificates:
                case OpcUa_BadIdentityChangeNotSupported:
                                                        code = SecurityError;
                                                        break;
                case OpcUa_BadNothingToDo:
                case OpcUa_BadTooManyOperations:
                case OpcUa_BadInvalidTimestamp:
                case OpcUa_BadSessionIdInvalid:
                case OpcUa_BadRequestHeaderInvalid:
                case OpcUa_BadTimestampsToReturnInvalid:
                case OpcUa_BadRequestCancelledByClient:
                case OpcUa_BadIndexRangeInvalid:
                case OpcUa_BadIndexRangeNoData:
                case OpcUa_BadNotReadable:
                case OpcUa_BadNotWritable:
                case OpcUa_BadOutOfRange:
                case OpcUa_BadNotFound:
                case OpcUa_BadMonitoringModeInvalid:
                case OpcUa_BadMonitoredItemIdInvalid:
                case OpcUa_BadMonitoredItemFilterInvalid:
                case OpcUa_BadFilterNotAllowed:
                case OpcUa_BadStructureMissing:
                case OpcUa_BadEventFilterInvalid:
                case OpcUa_BadContentFilterInvalid:
                case OpcUa_BadFilterOperatorInvalid:
                case OpcUa_BadFilterOperandCountMismatch:
                case OpcUa_BadFilterOperandInvalid:
                case OpcUa_BadFilterElementInvalid:
                case OpcUa_BadFilterLiteralInvalid:
                case OpcUa_BadContinuationPointInvalid:
                case OpcUa_BadNoContinuationPoints:
                case OpcUa_BadReferenceTypeIdInvalid:
                case OpcUa_BadBrowseDirectionInvalid:
                case OpcUa_BadNodeNotInView:
                case OpcUa_BadServerUriInvalid:
                case OpcUa_BadServerNameMissing:
                case OpcUa_BadDiscoveryUrlMissing:
                case OpcUa_BadSempahoreFileMissing:
                case OpcUa_BadRequestTypeInvalid:
                case OpcUa_BadRequestCancelledByRequest:
                case OpcUa_BadReferenceNotAllowed:
                case OpcUa_BadNodeIdRejected:
                case OpcUa_BadNodeIdExists:
                case OpcUa_BadNodeClassInvalid:
                case OpcUa_BadBrowseNameInvalid:
                case OpcUa_BadBrowseNameDuplicated:
                case OpcUa_BadNodeAttributesInvalid:
                case OpcUa_BadTypeDefinitionInvalid:
                case OpcUa_BadSourceNodeIdInvalid:
                case OpcUa_BadTargetNodeIdInvalid:
                case OpcUa_BadDuplicateReferenceNotAllowed:
                case OpcUa_BadInvalidSelfReference:
                case OpcUa_BadReferenceLocalOnly:
                case OpcUa_BadNoDeleteRights:
                case OpcUa_UncertainReferenceNotDeleted:
                case OpcUa_BadServerIndexInvalid:
                case OpcUa_BadViewIdUnknown:
                case OpcUa_BadViewTimestampInvalid:
                case OpcUa_BadViewParameterMismatch:
                case OpcUa_BadViewVersionInvalid:
                case OpcUa_BadNotTypeDefinition:
                case OpcUa_BadTooManyMatches:
                case OpcUa_BadQueryTooComplex:
                case OpcUa_BadNoMatch:
                case OpcUa_BadMaxAgeInvalid:
                case OpcUa_BadHistoryOperationInvalid:
                case OpcUa_BadInvalidTimestampArgument:
                case OpcUa_BadTypeMismatch:
                case OpcUa_BadMethodInvalid:
                case OpcUa_BadArgumentsMissing:
                case OpcUa_BadTooManyPublishRequests:
                case OpcUa_BadSequenceNumberUnknown:
                case OpcUa_BadMessageNotAvailable:
                case OpcUa_BadInsufficientClientProfile:
                case OpcUa_BadStateNotActive:
                case OpcUa_BadRequestInterrupted:
                case OpcUa_BadDeadbandFilterInvalid:
                case OpcUa_BadRefreshInProgress:
                case OpcUa_BadConditionAlreadyDisabled:
                case OpcUa_BadConditionAlreadyEnabled:
                case OpcUa_BadConditionDisabled:
                case OpcUa_BadEventIdUnknown:
                case OpcUa_BadEventNotAcknowledgeable:
                case OpcUa_BadDialogNotActive:
                case OpcUa_BadDialogResponseInvalid:
                case OpcUa_BadConditionBranchAlreadyAcked:
                case OpcUa_BadConditionBranchAlreadyConfirmed:
                case OpcUa_BadConditionAlreadyShelved:
                case OpcUa_BadConditionNotShelved:
                case OpcUa_BadShelvingTimeOutOfRange:
                case OpcUa_BadNoData:
                case OpcUa_BadBoundNotFound:
                case OpcUa_BadBoundNotSupported:
                case OpcUa_BadDataLost:
                case OpcUa_BadDataUnavailable:
                case OpcUa_BadEntryExists:
                case OpcUa_BadNoEntryExists:
                case OpcUa_BadTimestampNotSupported:
                case OpcUa_BadAggregateListMismatch:
                case OpcUa_BadAggregateNotSupported:
                case OpcUa_BadAggregateInvalidInputs:
                case OpcUa_BadAggregateConfigurationRejected:
                case OpcUa_BadInvalidArgument:
                case OpcUa_BadInvalidState:
                                                        code = InvalidRequestError;
                                                        break;
                case OpcUa_BadDataEncodingInvalid:
                case OpcUa_BadDataEncodingUnsupported:
                case OpcUa_BadEncodingError:
                case OpcUa_BadDecodingError:
                case OpcUa_BadUnknownResponse:
                case OpcUa_BadDataTypeIdUnknown:
                                                        code = DataFormatError;
                                                        break;
                case OpcUa_BadEncodingLimitsExceeded:
                case OpcUa_BadRequestTooLarge:
                case OpcUa_BadResponseTooLarge:
                                                        code = DataSizeError;
                                                        break;
                case OpcUa_BadInternalError:
                case OpcUa_BadOutOfMemory:
                case OpcUa_BadResourceUnavailable:
                case OpcUa_BadCommunicationError:
                case OpcUa_BadTcpServerTooBusy:
                case OpcUa_BadTcpMessageTypeInvalid:
                case OpcUa_BadTcpSecureChannelUnknown:
                case OpcUa_BadTcpMessageTooLarge:
                case OpcUa_BadTcpNotEnoughResources:
                case OpcUa_BadTcpInternalError:
                case OpcUa_BadTcpEndpointUrlInvalid:
                case OpcUa_BadSecureChannelTokenUnknown:
                case OpcUa_BadSequenceNumberInvalid:
                case OpcUa_BadProtocolVersionUnsupported:
                case OpcUa_BadEndOfStream:
                case OpcUa_BadNoDataAvailable:
                case OpcUa_BadWaitingForResponse:
                case OpcUa_BadOperationAbandoned:
                case OpcUa_BadExpectedStreamToBlock:
                case OpcUa_BadWouldBlock:
                case OpcUa_BadSyntaxError:
                                                        code = LowLevelError;
                                                        break;
                case OpcUa_BadShutdown:
                case OpcUa_BadServerNotConnected:
                case OpcUa_BadServerHalted:
                case OpcUa_BadSessionClosed:
                case OpcUa_BadSessionNotActivated:
                case OpcUa_BadTooManySessions:
                case OpcUa_BadSecureChannelClosed:
                case OpcUa_BadConnectionRejected:
                case OpcUa_BadDisconnect:
                case OpcUa_BadConnectionClosed:
                case OpcUa_BadMaxConnectionsReached:
                                                        code = ConnectionError;
                                                        break;
                case OpcUa_BadHostUnknown:
                                                        code = DiscoveryError;
                                                        break;
                case OpcUa_BadSubscriptionIdInvalid:
                case OpcUa_BadTooManySubscriptions:
                case OpcUa_BadNoSubscription:
                                                        code = SubscriptionError;
                                                        break;

                case OpcUa_BadTimeout:
                case OpcUa_BadRequestTimeout:
                                                        code = TimeoutError;
                                                        break;
                case OpcUa_BadServiceUnsupported:
                case OpcUa_BadNotSupported:
                case OpcUa_BadNotImplemented:
                case OpcUa_BadMonitoredItemFilterUnsupported:
                case OpcUa_BadFilterOperatorUnsupported:
                case OpcUa_BadHistoryOperationUnsupported:
                case OpcUa_BadWriteNotSupported:
                                                        code = UnsupportedError;
                                                        break;
                case OpcUa_BadConfigurationError:
                                                        code = ConfigurationError;
                                                        break;
                case OpcUa_BadNoCommunication:
                case OpcUa_BadWaitingForInitialData:
                case OpcUa_BadNotConnected:
                case OpcUa_BadDeviceFailure:
                case OpcUa_BadSensorFailure:
                case OpcUa_BadOutOfService:
                                                        code = DataSourceError;
                                                        break;
                case OpcUa_BadUnexpectedError:
                                                        code = UnexpectedError;
                                                        break;
                default:
                {
                    if (OpcUa_IsGood(uaCode))
                        code = Good;
                    else if (OpcUa_IsUncertain(uaCode))
                        code = Uncertain;
                    else
                        code = OtherError;
                }
            }

            return code;
        }


        // Convert the UAF code to a SDK/Stack code.
        // =========================================================================================
        OpcUa_StatusCode fromUafToSdk(StatusCode statusCode)
        {
            if (statusCode == statuscodes::Good)
                return OpcUa_Good;
            else if (statusCode == statuscodes::Uncertain)
                return OpcUa_Uncertain;
            else
                return OpcUa_Bad;
        }
    }
}
