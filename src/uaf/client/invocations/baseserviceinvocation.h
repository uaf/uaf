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

#ifndef UAFC_BASESERVICEINVOCATION_H_
#define UAFC_BASESERVICEINVOCATION_H_


// STD
#include <vector>
#include <string>
#include <map>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/logger.h"
#include "uaf/util/namespacearray.h"
#include "uaf/util/serverarray.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/sessions/sessioninformation.h"
#include "uaf/client/subscriptions/subscriptioninformation.h"
#include "uaf/client/requests/requests.h"
#include "uaf/client/results/results.h"
#include "uaf/client/configs/configs.h"



namespace uafc
{


    /**
     * The level at which a service should be invoked (i.e. saying whether a service should be
     * invoked within a Session, or within a Subscription).
     *
     * @ingroup ClientInvocations
     */
    enum InvocationLevel
    {
        SessionLevel,
        SubscriptionLevel
    };


    /*******************************************************************************************//**
    * A BaseServiceInvocation is a generic template to invoke an OPC UA service.
    *
    * Essentially, it's a way to make a service invocation (such as OPC UA Read, Write,
    * CreateMonitoredItems, ...) more generic.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    template<typename _ServiceSettings, typename _RequestTarget, typename _ResultTarget>
    class UAFC_EXPORT BaseServiceInvocation
    {
    public:

        // lot's of public typedefs that depend on the template arguments:
        typedef uafc::BaseServiceConfig<_ServiceSettings>                               ServiceConfigType;
        typedef uafc::BaseSessionRequest<ServiceConfigType, _RequestTarget, false>      SessionRequestType;
        typedef uafc::BaseSessionResult<_ResultTarget, false>                           SessionResultType;
        typedef uafc::BaseSessionRequest<ServiceConfigType, _RequestTarget, true>       AsyncSessionRequestType;
        typedef uafc::BaseSessionResult<uafc::AsyncResultTarget, true>                  AsyncSessionResultType;
        typedef uafc::BaseSubscriptionRequest<ServiceConfigType, _RequestTarget, false> SubscriptionRequestType;
        typedef uafc::BaseSubscriptionResult<_ResultTarget, false>                      SubscriptionResultType;
        typedef uafc::BaseSubscriptionRequest<ServiceConfigType, _RequestTarget, true>  AsyncSubscriptionRequestType;
        typedef uafc::BaseSubscriptionResult<uafc::AsyncResultTarget, true>             AsyncSubscriptionResultType;


        /**
         * Create a service invocation.
         */
        BaseServiceInvocation()
        : asynchronous_(false),
          transactionId_(0),
          requestHandle_(uaf::REQUESTHANDLE_NOT_ASSIGNED),
          invocationLevel_(uafc::SessionLevel)
        {}


        /**
         * Destruct the service invocation.
         */
        virtual ~BaseServiceInvocation() {}


        ////////////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Accessors
         *  Accessor methods.
         */
        ///@{


        /** Get the request targets of the service invocation. */
        const std::vector<_RequestTarget>&  requestTargets()        const { return requestTargets_; }

        /** Get the service settings of the service invocation. */
        const _ServiceSettings&             serviceSettings()       const { return serviceSettings_; }

        /** Get the session settings of the service invocation. */
        const uafc::SessionSettings&        sessionSettings()       const { return sessionSettings_; }

        /** Get the session settings of the service invocation. */
        const uafc::SubscriptionSettings&   subscriptionSettings()  const { return subscriptionSettings_; }

        /** Get the request handle associated with the request. */
        const uaf::RequestHandle&           requestHandle()         const { return requestHandle_; }

        /** Get the transaction id associated with the request (in case of an asynchronous one). */
        const uaf::TransactionId&           transactionId()         const { return transactionId_; }

        /** Get the resultTargets after the service invocation. */
        const std::vector<_ResultTarget>&   resultTargets()         const { return resultTargets_; }

        /** Get the non-const resultTargets after the service invocation. */
        std::vector<_ResultTarget>&         resultTargets()               { return resultTargets_; }

        /** Get the rank for each target. */
        const std::vector<std::size_t>      ranks()                 const { return ranks_; }

        /** Is the request asynchronous? */
        bool                                asynchronous()          const { return asynchronous_; }

        /** Get the level at which the service should be invoked. */
        uafc::InvocationLevel               invocationLevel()       const { return invocationLevel_; }


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Modifiers
         *  Modifier methods.
         */
        ///@{


        /** Add the targets with the given rank to the service invocation. */
        void addTarget(
                std::size_t             rank,
                const _RequestTarget&   requestTarget,
                const _ResultTarget&    resultTarget)
        {
            ranks_.push_back(rank);
            requestTargets_.push_back(requestTarget);
            resultTargets_.push_back(resultTarget);
        }


        /** Add the targets with the given rank for the service invocation. */
        void addTarget(
                std::size_t                     rank,
                const _RequestTarget&           requestTarget,
                const uafc::AsyncResultTarget&  asyncResultTarget)
        {
            ranks_.push_back(rank);
            requestTargets_.push_back(requestTarget);
        }


        /** Set the transaction Id associated with the request (in case of an asynchronous one). */
        void setTransactionId(uaf::TransactionId transactionId)
        { transactionId_ = transactionId; }


        /** Provide the information about the session. */
        void setSessionInformation(const uafc::SessionInformation& sessionInformation)
        {
            sessionInformation_ = sessionInformation;
        }


        /** Provide the information about the subscription. */
        void setSubscriptionInformation(const uafc::SubscriptionInformation& subscriptionInformation)
        {
            subscriptionInformation_ = subscriptionInformation;
        }


        /** Set the relevant settings from the given request, for the given server URI. */
        void setRequestSettings(const std::string& serverUri, const SessionRequestType& request)
        {
            invocationLevel_ = SessionLevel;
            setSessionRequestSettings<SessionRequestType>(serverUri, request);
        }


        /** Set the relevant settings from the given request, for the given server URI. */
        void setRequestSettings(const std::string& serverUri, const AsyncSessionRequestType& request)
        {
            invocationLevel_ = SessionLevel;
            setSessionRequestSettings<AsyncSessionRequestType>(serverUri, request);
        }


        /** Set the relevant settings from the given request, for the given server URI. */
        void setRequestSettings(const std::string& serverUri, const SubscriptionRequestType& request)
        {
            invocationLevel_ = SubscriptionLevel;
            setSubscriptionRequestSettings<SubscriptionRequestType>(serverUri, request);
        }


        /** Set the relevant settings from the given request, for the given server URI. */
        void setRequestSettings(const std::string& serverUri, const AsyncSubscriptionRequestType& request)
        {
            invocationLevel_ = SubscriptionLevel;
            setSubscriptionRequestSettings<AsyncSubscriptionRequestType>(serverUri, request);
        }


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name Invoke
         *  Invoke the service.
         */
        ///@{


        /**
         * Invoke the service at the session level.
         *
         * @param uaSession         Pointer to the SDK session object.
         * @param nameSpaceArray    The namespace array of the session.
         * @param serverArray       The server array of the session.
         * @param logger            Pointer to a logger.
         * @return                  Bad if the session could not be invoked.
         */
        uaf::Status invoke(
                UaClientSdk::UaSession*     uaSession,
                const uaf::NamespaceArray&  nameSpaceArray,
                const uaf::ServerArray&     serverArray,
                uaf::Logger*                logger)
        {
            uaf::Status ret;

            logger->debug("Invoking the service at the session level");

            if (asynchronous_)
            {
                logger->debug("Copying the data from the asynchronous UAF request to the SDK level");
                ret = fromAsyncUafToSdk(
                        requestTargets_,
                        serviceSettings_,
                        nameSpaceArray,
                        serverArray);

                if (ret.isGood())
                {
                    logger->debug("Invoking the asynchronous request at the SDK level");
                    ret = invokeAsyncSdkService(uaSession, transactionId_);
                }
            }
            else
            {
                logger->debug("Copying the data from the synchronous UAF request to the SDK level");
                ret = fromSyncUafToSdk(
                        requestTargets_,
                        serviceSettings_,
                        nameSpaceArray,
                        serverArray);

                if (ret.isGood())
                {
                    logger->debug("Invoking the synchronous request at the SDK level");
                    ret = invokeSyncSdkService(uaSession);
                }

                if (ret.isGood())
                {
                    logger->debug("Copying the data from SDK level to the UAF result");
                    ret = fromSyncSdkToUaf(nameSpaceArray, serverArray, resultTargets_);
                }
            }

            if (ret.isGood())
                logger->debug("The request has been invoked successfully");
            else
            {
                ret.addDiagnostic("Service invocation failed");
                logger->error(ret);
            }

            return ret;
        }


        /**
         * Invoke the service at the subscription level.
         *
         * @param uaSubscription    Pointer to the SDK subscription object.
         * @param nameSpaceArray    The namespace array of the session.
         * @param serverArray       The server array of the session.
         * @param logger            Pointer to a logger.
         * @return                  Bad if the session could not be invoked.
         */
        uaf::Status invoke(
                UaClientSdk::UaSubscription* uaSubscription,
                const uaf::NamespaceArray&   nameSpaceArray,
                const uaf::ServerArray&      serverArray,
                uaf::Logger*                 logger)
        {
            uaf::Status ret;

            logger->debug("Invoking the service at the subscription level");

            if (this->asynchronous())
            {
                logger->debug("Copying the data from the asynchronous UAF request to the SDK level");
                ret = this->fromAsyncUafToSdk(
                        this->requestTargets(),
                        this->serviceSettings(),
                        nameSpaceArray,
                        serverArray);

                if (ret.isGood())
                {
                    logger->debug("Invoking the asynchronous request at the SDK level");
                    ret = this->invokeAsyncSdkService(uaSubscription, this->transactionId());
                }
            }
            else
            {
                logger->debug("Copying the data from the synchronous UAF request to the SDK level");
                ret = this->fromSyncUafToSdk(
                        this->requestTargets(),
                        this->serviceSettings(),
                        nameSpaceArray,
                        serverArray);

                if (ret.isGood())
                {
                    logger->debug("Invoking the synchronous request at the SDK level");
                    ret = this->invokeSyncSdkService(uaSubscription);
                }

                if (ret.isGood())
                {
                    logger->debug("Copying the data from SDK level to the UAF result");
                    ret = this->fromSyncSdkToUaf(nameSpaceArray, serverArray, this->resultTargets());
                }
            }

            return ret;
        }


        ///@} //////////////////////////////////////////////////////////////////////////////////////
        /**
         *  @name CopyToResult.
         *  Copy the SDK service result data to the UAF result object.
         */
        ///@{


        /**
         * Copy the synchronous service result data of the invocation at the session level,
         * to the appropriate UAF object.
         *
         * @param result    The UAF result object.
         * @return          Good if the result data could be copied.
         */
        uaf::Status copyToResult(SessionResultType& result)
        {
            uaf::Status ret(uaf::statuscodes::Good);

            if (resultTargets_.size() != ranks_.size())
                ret.setStatus(uaf::statuscodes::UnexpectedError,
                              "Bug in BaseServiceInvocation: " \
                              "number of result targets (%d) != number of ranks (%d)",
                              resultTargets_.size(), ranks_.size());


            for (std::size_t i = 0; i < resultTargets_.size() && ret.isGood(); i++)
            {
                std::size_t rank = ranks_[i];

                if (rank < result.targets.size())
                {
                    result.targets[rank] = resultTargets_[i];
                    result.targets[rank].clientConnectionId
                        = sessionInformation_.clientConnectionId;
                }
                else
                {
                    ret.setStatus(uaf::statuscodes::UnexpectedError,
                                  "Bug in BaseServiceInvocation: rank (%d) > targets.size() (%d)",
                                  rank, result.targets.size());
                }
            }
            return ret;
        }


        /**
         * Copy the synchronous service result data of the invocation at the subscription level,
         * to the appropriate UAF object.
         *
         * @param result    The UAF result object.
         * @return          Good if the result data could be copied.
         */
        uaf::Status copyToResult(SubscriptionResultType& result)
        {
            uaf::Status ret(uaf::statuscodes::Good);

            if (resultTargets_.size() != ranks_.size())
                ret.setStatus(uaf::statuscodes::UnexpectedError,
                              "Bug in BaseServiceInvocation: " \
                              "number of result targets (%d) != number of ranks (%d)",
                              resultTargets_.size(), ranks_.size());


            for (std::size_t i = 0; i < resultTargets_.size() && ret.isGood(); i++)
            {
                std::size_t rank = ranks_[i];

                if (rank < result.targets.size())
                {
                    result.targets[rank] = resultTargets_[i];
                    result.targets[rank].clientConnectionId
                        = sessionInformation_.clientConnectionId;
                    result.targets[rank].clientSubscriptionHandle
                        = subscriptionInformation_.clientSubscriptionHandle;
                }
                else
                {
                    ret.setStatus(uaf::statuscodes::UnexpectedError,
                                  "Bug in BaseServiceInvocation: rank (%d) > targets.size() (%d)",
                                  rank, result.targets.size());
                }
            }
            return ret;
        }


        /**
         * Copy the asynchronous service result data of the invocation at the session level,
         * to the appropriate UAF object.
         *
         * @param result    The UAF result object.
         * @return          Good if the result data could be copied.
         */
        uaf::Status copyToResult(AsyncSessionResultType& result)
        {
            uaf::Status ret;

            if (ranks_.size() == resultTargets_.size())
            {
                ret.setGood();
            }
            else
            {
                ret.setStatus(uaf::statuscodes::UnexpectedError,
                              "Bug in BaseServiceInvocation: Ranks do not match the received " \
                              "result targets");
            }

            return ret;
        }


        /**
         * Copy the asynchronous service result data of the invocation at the subscription level,
         * to the appropriate UAF object.
         *
         * @param result    The UAF result object.
         * @return          Good if the result data could be copied.
         */
        uaf::Status copyToResult(AsyncSubscriptionResultType& result)
        {
            uaf::Status ret;

            if (ranks_.size() == resultTargets_.size())
            {
                ret.setGood();
            }
            else
            {
                ret.setStatus(uaf::statuscodes::UnexpectedError,
                              "Bug in BaseServiceInvocation: Ranks do not match the received " \
                              "result targets");
            }

            return ret;
        }

        ///@}


    private:


        DISALLOW_COPY_AND_ASSIGN(BaseServiceInvocation);


        /**
         * Set the session request settings.
         *
         * @param serverUri The URI of the server that will be used for the service invocation.
         * @param request   The request from which the session request settings will be
         *                  extracted.
         */
        template<typename _Request>
        void setSessionRequestSettings(const std::string serverUri, const _Request& request)
        {
            std::map<std::string, uafc::SessionSettings>::const_iterator it;
            it = request.sessionConfig.specificSessionSettings.find(serverUri);

            if (it != request.sessionConfig.specificSessionSettings.end())
                sessionSettings_ = it->second;
            else
                sessionSettings_ = request.sessionConfig.defaultSessionSettings;

            asynchronous_    = _Request::asynchronous;
            serviceSettings_ = request.serviceConfig.serviceSettings;
            requestHandle_   = request.requestHandle();
        }


        /**
         * Set the subscription request settings.
         *
         * @param serverUri The URI of the server that will be used for the service invocation.
         * @param request   The request from which the subscription request settings will be
         *                  extracted.
         */
        template<typename _Request>
        void setSubscriptionRequestSettings(const std::string serverUri, const _Request& request)
        {
            std::map<std::string, uafc::SubscriptionSettings>::const_iterator it;
            it = request.subscriptionConfig.specificSubscriptionSettings.find(serverUri);

            if (it != request.subscriptionConfig.specificSubscriptionSettings.end())
                subscriptionSettings_ = it->second;
            else
                subscriptionSettings_ = request.subscriptionConfig.defaultSubscriptionSettings;

            setSessionRequestSettings(serverUri, request);

        }


        /**
         * Copy the synchronous request data from the UAF objects to the SDK objects.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param targets           The targets of the request.
         * @param serviceSettings   The service settings of the request.
         * @param nameSpaceArray    The namespace array of the server that will be used for the
         *                          service invocation.
         * @param serverArray       The server array of the server that will be used for the
         *                          service invocation.
         * @return                  Good if the data could be copied, bad if not.
         */
        virtual uaf::Status fromSyncUafToSdk(
                const std::vector<_RequestTarget>&  targets,
                const _ServiceSettings&             serviceSettings,
                const uaf::NamespaceArray&          nameSpaceArray,
                const uaf::ServerArray&             serverArray)
        {
            if (asynchronous_)
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Synchronous invocation is not implemented");
        }


        /**
         * Copy the asynchronous request data from the UAF objects to the SDK objects.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param targets           The targets of the request.
         * @param serviceSettings   The service settings of the request.
         * @param nameSpaceArray    The namespace array of the server that will be used for the
         *                          service invocation.
         * @param serverArray       The server array of the server that will be used for the
         *                          service invocation.
         * @return                  Good if the data could be copied, bad if not.
         */
        virtual uaf::Status fromAsyncUafToSdk(
                const std::vector<_RequestTarget>& targets,
                const _ServiceSettings&     serviceSettings,
                const uaf::NamespaceArray&  nameSpaceArray,
                const uaf::ServerArray&     serverArray)
        {
            if (!asynchronous_)
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Asynchronous invocation is not implemented");
        }


        /**
         * Invoke the synchronous request data at the session level.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param uaSession     Pointer to the SDK session object that will be used for the
         *                      invocation.
         * @return              Good if the service could be invoked, bad if not.
         */
        virtual uaf::Status invokeSyncSdkService(
                UaClientSdk::UaSession*     uaSession)
        {
            if (asynchronous_ || (invocationLevel_ != SessionLevel))
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Synchronous invocation is not implemented");
        }


        /**
         * Invoke the asynchronous request data at the session level.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param uaSession     Pointer to the SDK session object that will be used for the
         *                      invocation.
         * @param transactionId Transaction id of the asynchronous call.
         * @return              Good if the service could be invoked, bad if not.
         */
        virtual uaf::Status invokeAsyncSdkService(
                UaClientSdk::UaSession*     uaSession,
                uaf::TransactionId          transactionId)
        {
            if (!asynchronous_ || (invocationLevel_ != SessionLevel))
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Asynchronous invocation is not implemented");
        }


        /**
         * Invoke the synchronous request data at the subscription level.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param uaSubscription    Pointer to the SDK subscription object that will be used for the
         *                          invocation.
         * @return                  Good if the service could be invoked, bad if not.
         */
        virtual uaf::Status invokeSyncSdkService(
                UaClientSdk::UaSubscription*    uaSubscription)
        {
            if (asynchronous_ || (invocationLevel_ != SubscriptionLevel))
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Synchronous invocation is not implemented");
        }


        /**
         * Invoke the asynchronous request data at the subscription level.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param uaSubscription    Pointer to the SDK subscription object that will be used for the
         *                          invocation.
         * @param transactionId     Transaction id of the asynchronous call.
         * @return                  Good if the service could be invoked, bad if not.
         */
        virtual uaf::Status invokeAsyncSdkService(
                UaClientSdk::UaSubscription*    uaSubscription,
                uaf::TransactionId              transactionId)
        {
            if (!asynchronous_ || (invocationLevel_ != SubscriptionLevel))
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Asynchronous invocation is not implemented");
        }


        /**
         * Copy the asynchronous result data from the SDK to the UAF objects.
         *
         * These are virtual functions, meant to be overwritten by the concrete services that
         * implement them.
         *
         * @param nameSpaceArray    The namespace array of the server that was used for the
         *                          service invocation.
         * @param serverArray       The server array of the server that was used for the
         *                          service invocation.
         * @param targets           Output parameter: the targets of the result to be updated.
         * @return                  Good if the data could be copied, bad if not.
         */
        virtual uaf::Status fromSyncSdkToUaf(
                const uaf::NamespaceArray&      nameSpaceArray,
                const uaf::ServerArray&         serverArray,
                std::vector<_ResultTarget>&     targets)
        {
            if (asynchronous_)
                return uaf::Status(uaf::statuscodes::UnexpectedError,
                                   "Method is not supposed to be called!");
            else
                return uaf::Status(uaf::statuscodes::UnsupportedError,
                                   "Synchronous invocation is not implemented");
        }


        // should the service be invoked asynchronously, or not?
        bool                        asynchronous_;
        // the transactionId of the service call, if it is asynchronous
        uaf::TransactionId          transactionId_;
        // the original request targets
        std::vector<_RequestTarget> requestTargets_;
        // the order number of the targets that were given
        std::vector<std::size_t>    ranks_;
        // the service settings, particular for this service
        _ServiceSettings            serviceSettings_;
        // the session settings of the session that will invoke the service
        uafc::SessionSettings       sessionSettings_;
        // the results of the service invocation
        std::vector<_ResultTarget>  resultTargets_;
        // the unique handle of the request (defined by the UAF, not by the OPC UA standard!)
        uaf::RequestHandle          requestHandle_;
        // some details about the session
        uafc::SessionInformation    sessionInformation_;
        // some details about the subscription
        uafc::SubscriptionInformation subscriptionInformation_;
        // the level at which the service should be invoked
        uafc::InvocationLevel       invocationLevel_;
        // the settings of the subscription that will be used for the service invocation
        uafc::SubscriptionSettings  subscriptionSettings_;

    };







}




#endif /* UAFC_BASESERVICEINVOCATION_H_ */
