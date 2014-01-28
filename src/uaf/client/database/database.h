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

#ifndef UAFC_DATABASE_H_
#define UAFC_DATABASE_H_


// STD
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/clientservices.h"
#include "uaf/client/database/requeststore.h"
#include "uaf/client/database/addresscache.h"
#include "uaf/client/settings/clientsettings.h"


namespace uafc
{

    /*******************************************************************************************//**
    * A client database holds notification buffers, an address cache and client settings.
    *
    * The uafc::Client holds a single instance of this class, and shares its pointer to all
    * sessions, subscriptions and their factories.
    *
    * @ingroup ClientDatabase
    ***********************************************************************************************/
    class UAFC_EXPORT Database
    {
    public:


        /**
         * Create a client database instance.
         *
         * @param loggerFactory Pointer to the factory to use.
         */
        Database(uaf::LoggerFactory* loggerFactory);


        /** The configuration settings of the client. */
        uafc::ClientSettings clientSettings;

        /** The store for monitored data requests. */
        uafc::CreateMonitoredDataRequestStore createMonitoredDataRequestStore;

        /** The store for monitored event requests. */
        uafc::CreateMonitoredEventsRequestStore createMonitoredEventsRequestStore;

        /** The cache used by the resolver. */
        uafc::AddressCache addressCache;

        /** A vector storing all the client handles that were ever assigned. */
        std::vector<uaf::ClientHandle> allClientHandles;


        /**
         * Get a unique connection id.
         *
         * @return  A unique client connection ID.
         */
        uaf::ClientConnectionId createUniqueClientConnectionId();


        /**
         * Get a unique ClientSubscriptionHandle.
         *
         * @return  A new client handle for the subscription.
         */
        uaf::ClientSubscriptionHandle createUniqueClientSubscriptionHandle();


        /**
         * Get a unique ClientHandle.
         *
         * @return  A new client handle for the monitored item.
         */
        uaf::ClientHandle createUniqueClientHandle();


    private:

        // The current client connection ID.
        uaf::ClientConnectionId         clientConnectionId_;
        UaMutex                         clientConnectionIdMutex_;

        // The current client subscription handle.
        uaf::ClientSubscriptionHandle   clientSubscriptionHandle_;
        UaMutex                         clientSubscriptionHandleMutex_;

        // The current client handle of the monitored items.
        uaf::ClientHandle               clientHandle_;
        UaMutex                         clientHandleMutex_;

        // no copying or assigning allowed
        DISALLOW_COPY_AND_ASSIGN(Database);

    };


    /**
     * Template function to "catch" all requests that don't need to be stored.
     *
     * Request/Results that *do* need to be stored, will have a specialized storeIfNeeded()
     * function.
     *
     * @param request   The request.
     * @param result    The result.
     * @param mask      Only store the targets indicated by the mask.
     * @param database  The database to add the request to.
     * @return          Always good, since nothing need to be stored when the non-specialized
     *                  version of storeIfNeeded() is called.
     */
    template <typename _Service>
    uaf::Status UAFC_EXPORT storeIfNeeded(
            const typename _Service::Request& request,
            const typename _Service::Result&  result,
            const uaf::Mask&                  mask,
            uafc::Database*                   database)
    {
        return uaf::Status(uaf::statuscodes::Good);
    }


    /**
     * Store a uafc::CreateMonitoredDataRequest and corresponding result, if needed.
     *
     * @param request   The request to be stored.
     * @param result    The result corresponding with the request.
     * @param mask      Only store the targets indicated by the mask.
     * @param database  The database to add the request to.
     * @return          Good if the request could be stored, Bad if not.
     */
    template <>
    inline uaf::Status UAFC_EXPORT storeIfNeeded<uafc::CreateMonitoredDataService>(
            const uafc::CreateMonitoredDataRequest& request,
            const uafc::CreateMonitoredDataResult&  result,
            const uaf::Mask&                        mask,
            uafc::Database*                         database)
    {
        return database->createMonitoredDataRequestStore.storeIfNeeded(request, result, mask);
    }


    /**
     * Store a uafc::CreateMonitoredEventsRequest and corresponding result, if needed.
     *
     * @param request   The request to be stored.
     * @param result    The result corresponding with the request.
     * @param mask      Only store the targets indicated by the mask.
     * @param database  The database to add the request to.
     * @return          Good if the request could be stored, Bad if not.
     */
    template <>
    inline uaf::Status UAFC_EXPORT storeIfNeeded<uafc::CreateMonitoredEventsService>(
            const uafc::CreateMonitoredEventsRequest&   request,
            const uafc::CreateMonitoredEventsResult&    result,
            const uaf::Mask&                            mask,
            uafc::Database*                             database)
    {
        return database->createMonitoredEventsRequestStore.storeIfNeeded(request, result, mask);
    }


    /**
     * Template function to "catch" all results of non-persistent requests.
     *
     * Results that *do* need to be updated (because they belong to persistent requests),
     * will have a specialized updateResultIfNeeded() function.
     *
     * @param result    The new result.
     * @param mask      The mask indicating the updated targets of the result.
     * @param database  The database to update the result in.
     * @return          Always good, since nothing need to be updated when the non-specialized
     *                  version of updateResultIfNeeded() is called.
     */
    template<typename _Service>
    uaf::Status UAFC_EXPORT updateResultIfNeeded(
            const typename _Service::Result&    result,
            const uaf::Mask&                    mask,
            uafc::Database*                     database)
    {
        return uaf::Status(uaf::statuscodes::Good);
    }


    /**
     * Update the result of a persistent CreateMonitoredDataRequest.
     *
     * @param result    The new result.
     * @param mask      The mask indicating the updated targets of the result.
     * @param database  The database to update the result in.
     * @return          Good if the result could be updated, Bad if not.
     */
    template <>
    inline uaf::Status UAFC_EXPORT updateResultIfNeeded<uafc::CreateMonitoredDataService>(
            const uafc::CreateMonitoredDataResult&  result,
            const uaf::Mask&                        mask,
            uafc::Database*                         database)
    {
        return database->createMonitoredDataRequestStore.updateResult(result, mask);
    }


    /**
     * Update the result of a persistent CreateMonitoredEventsRequest.
     *
     * @param result    The new result.
     * @param mask      The mask indicating the updated targets of the result.
     * @param database  The database to update the result in.
     * @return          Good if the result could be updated, Bad if not.
     */
    template <>
    inline uaf::Status UAFC_EXPORT updateResultIfNeeded<uafc::CreateMonitoredEventsService>(
            const uafc::CreateMonitoredEventsResult&    result,
            const uaf::Mask&                            mask,
            uafc::Database*                             database)
    {
        return database->createMonitoredEventsRequestStore.updateResult(result, mask);
    }



    /**
     * Template function to "catch" all results that don't need to have client handles
     * assigned.
     *
     * Results that *do* need to have client handles assigned, will have a specialized
     * assignClientHandlesIfNeeded() function.
     *
     * @param result    The result.
     * @param mask      Only assign the targets indicated by the mask.
     * @param database  The database.
     * @param assigned  True if the function will (try to) assign clientHandles
     *                  (always false for this particular template function).
     */
    template <typename _Service>
    uaf::Status UAFC_EXPORT assignClientHandlesIfNeeded(
            typename _Service::Result&  result,
            const uaf::Mask&            mask,
            uafc::Database*             database,
            bool&                       assigned)
    {
        assigned = false;
        return uaf::Status(uaf::statuscodes::Good);
    }



    /**
     * Specialized template function to assign ClientHandles to CreateMonitoredDataResults.
     *
     * @param result    The result.
     * @param mask      Only assign the targets indicated by the mask.
     * @param database  The database.
     * @param assigned  True if the function will (try to) assign client handles (always true
     *                  for this particular template function).
     * @return          Good if client handles could be assigned, or if they were already
     *                  assigned.
     */
    template <>
    inline uaf::Status UAFC_EXPORT assignClientHandlesIfNeeded<uafc::CreateMonitoredDataService>(
            uafc::CreateMonitoredDataResult&    result,
            const uaf::Mask&                    mask,
            uafc::Database*                     database,
            bool&                               assigned)
    {
        uaf::Status ret;
        assigned = true;

        if (mask.size() == result.targets.size())
        {
            for (std::size_t i = 0; i < result.targets.size(); i++)
            {
                if (mask.isSet(i))
                {
                    if (result.targets[i].clientHandle == uaf::CLIENTHANDLE_NOT_ASSIGNED)
                    {
                        result.targets[i].clientHandle = database->createUniqueClientHandle();
                    }
                }
            }

            // add the client handles to the status diagnostics object!
            std::vector<uaf::ClientHandle> clientHandles;
            clientHandles.reserve(result.targets.size());

            for (std::size_t i = 0; i < result.targets.size(); i++)
                clientHandles.push_back(result.targets[i].clientHandle);

            ret.additionalDiagnostics().setClientHandles(clientHandles);

            ret.setGood();
        }
        else
        {
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "Could not assign client handles (mask has wrong size!)");
        }

        return ret;
    }


    /**
     * Specialized template function to assign ClientHandles to CreateMonitoredEventsResults.
     *
     * @param result    The result.
     * @param mask      Only assign the targets indicated by the mask.
     * @param database  The database.
     * @param assigned  True if the function will (try to) assign client handles (always true
     *                  for this particular template function).
     * @return          Good if client handles could be assigned, or if they were already
     *                  assigned.
     */
    template <>
    inline uaf::Status UAFC_EXPORT assignClientHandlesIfNeeded<uafc::CreateMonitoredEventsService>(
            uafc::CreateMonitoredEventsResult&  result,
            const uaf::Mask&                    mask,
            uafc::Database*                     database,
            bool&                               assigned)
    {
        uaf::Status ret;
        assigned = true;

        if (mask.size() == result.targets.size())
        {
            for (std::size_t i = 0; i < result.targets.size(); i++)
            {
                if (mask.isSet(i))
                {
                    if (result.targets[i].clientHandle == uaf::CLIENTHANDLE_NOT_ASSIGNED)
                    {
                        result.targets[i].clientHandle = database->createUniqueClientHandle();
                    }
                }
            }

            // add the client monitored item handles to the status diagnostics object!
            std::vector<uaf::ClientHandle> clientHandles;
            clientHandles.reserve(result.targets.size());

            for (std::size_t i = 0; i < result.targets.size(); i++)
                clientHandles.push_back(result.targets[i].clientHandle);

            ret.additionalDiagnostics().setClientHandles(clientHandles);

            ret.setGood();
        }
        else
        {
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "Could not assign ClientHandles (mask has wrong size!)");
        }

        return ret;
    }


}



#endif /* UAFC_DATABASE_H_ */
