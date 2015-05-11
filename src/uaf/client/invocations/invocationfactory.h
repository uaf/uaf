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

#ifndef UAF_INVOCATIONFACTORY_H_
#define UAF_INVOCATIONFACTORY_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientservices.h"

namespace uaf
{

    /*******************************************************************************************//**
    * An uaf::InvocationFactory is a factory to produce service invocations for a given request.
    *
    * A single request may lead to several invocations, e.g. an uaf::ReadRequest of some variables
    * will result in multiple invocations if the variables are not all exposed by the same server.
    *
    * An invocation therefore "groups" targets of a specific service (e.g. Read, Write, ...)
    * per server URI.
    *
    * @ingroup ClientInvocations
    ***********************************************************************************************/
    template<typename _Service>
    class InvocationFactory
    {
    public:

        // some public typedefs that depend on the service type
        typedef typename _Service::Invocation InvocationType;
        typedef typename _Service::Request    RequestType;
        typedef typename _Service::Result     ResultType;


        /**
         * Create an invocation factory.
         */
        InvocationFactory() {}


        /**
         * Destroy an invocation factory.
         *
         * This method will take care of clearing the memory occupied by the invocations.
         */
        ~InvocationFactory()
        {
            clear();
        }


        /** The invocations that were created. */
        std::map<std::string, InvocationType*> invocations;


        /**
         * Create a number of invocations, based on the request, the result and the mask.
         *
         * @param request   The request that will be "translated" into invocations.
         * @param result    The result that will contain the results of the invocations.
         * @param mask      The mask that specifies which targets of the 'request' and 'result'
         *                  parameters should be taken into account.
         */
        uaf::Status create(
                const RequestType&  request,
                const ResultType&   result,
                const uaf::Mask&    mask)
        {
            // declare the return Status
            uaf::Status ret;

            // check the input parameters
            if (request.targets.size() == mask.size())
                ret = uaf::statuscodes::Good;
            else
                ret = uaf::UnexpectedError("The mask does not match the number of targets");

            std::string serverUri;

            if (ret.isGood())
            {
                for (std::size_t i = 0; i < request.targets.size() && ret.isGood(); i++)
                {
                    //if (request.targets[i].getServerUri(serverUri).isGood() && mask.isSet(i))
                    if (mask.isSet(i))
                    {
                        if (getServerUriFromTarget(request.targets[i], serverUri).isGood())
                        {
                            if (invocations.find(serverUri) == invocations.end())
                            {
                                invocations[serverUri] = new InvocationType;
                                // depending on the type of the Invocation, either
                                // SessionServiceInvocation::setRequestSettings() or
                                // SubscriptionServiceInvocation::setRequestSettings() will be invoked:
                                invocations[serverUri]->setRequestSettings(serverUri, request);
                            }

                            invocations[serverUri]->addTarget(
                                    i,
                                    request.targets[i],
                                    result.targets[i]);
                        }
                        else
                        {
                            ret = uaf::InvalidServerUriError(serverUri);
                        }
                    }
                }
            }

            // asynchronous requests can (in this UAF version) only have targets on the same server
            if (RequestType::asynchronous && invocations.size() > 1)
                ret = uaf::AsyncInvocationOnMultipleSessionsNotSupportedError();

            return ret;
        }


    private:


        DISALLOW_COPY_AND_ASSIGN(InvocationFactory);


        /**
         * Clear the memory occupied by the invocations.
         */
        void clear()
        {
            typename std::map<std::string, InvocationType*>::iterator it;

            for (it = invocations.begin(); it != invocations.end(); ++it)
                delete it->second;

            invocations.clear();
        }

    };

}


#endif /* UAF_INVOCATIONFACTORY_H_ */
