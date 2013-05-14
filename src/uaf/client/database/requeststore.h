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

#ifndef UAFC_REQUESTSTORE_H_
#define UAFC_REQUESTSTORE_H_



// STD
#include <map>
#include <vector>
// SDK
#include "uabase/uamutex.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/status.h"
#include "uaf/util/mask.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clientservices.h"


namespace uafc
{

    /*******************************************************************************************//**
    * A request store stores the requests (and their results) that always need to be reconstructed,
    * even after severe failures.
    *
    * @ingroup ClientDatabase
    ***********************************************************************************************/
    template <typename _Service>
    class UAFC_EXPORT RequestStore
    {
    public:

        // typedefs
        typedef _Service                   ServiceType;
        typedef typename _Service::Request RequestType;
        typedef typename _Service::Result  ResultType;


        /***************************************************************************************//**
         * A request store item holds the request, the result and a mask of the targets.
        *******************************************************************************************/
        struct Item
        {
            /**
             * Construct an Item from a given request, result and the mask specifying the
             * targets that need to be re-processed.
             */
            Item(const RequestType& request,
                 const ResultType&  result,
                 const uaf::Mask&   badTargetsMask)
            : request(request), result(result), badTargetsMask(badTargetsMask) {}


            /** The original persistent request. */
            RequestType request;

            /** The result in it's current state. */
            ResultType  result;

            /** The mask specifying the bad targets (= the targets to be re-processed). */
            uaf::Mask   badTargetsMask;
        };


        /**
         * Construct a new request store that logs to a given logger factory and that has a given
         * name.
         *
         * @param loggerFactory     Pointer to the logger factory to log all messages to.
         * @param name              The name of the store (only used for logging).
         */
        RequestStore(uaf::LoggerFactory* loggerFactory, const std::string& name);


        /**
         * Destruct the request store.
         */
        virtual ~RequestStore();


        /**
         * Remove all the stored items.
         */
        void clear();

        /**
         * Log current state.
         */
        void logCurrentState();


        /**
         * Remove an item by specifying its handle.
         *
         * @param handle    Handle of the item to be removed.
         * @return          Good if handle was found and the item could be removed,
         *                  InvalidRequestError if not.
         */
        uaf::Status remove(uafc::RequestHandle handle);


        /**
         * Get the item for a given handle.
         *
         * @param handle    The handle of the item to obtain.
         * @param item      The stored item.
         * @return          Good if the item was present, InvalidRequestError if not.
         */
        uaf::Status get(uafc::RequestHandle handle, Item& item);


        /**
         * Get the items of which the mask indicates that 1 or more targets need to be re-processed.
         *
         * @return  Items to be re-processed.
         */
        std::vector<Item> getBadItems();


        uaf::Status updateTargetStatus(
                uafc::RequestHandle requestHandle,
                std::size_t         targetRank,
                const uaf::Status&  status);


        /**
         * Update a stored item.
         *
         * @param result    The new result, containing the masked targets that will be used to
         *                  overwrite the stored targets.
         * @param mask      The mask of the targets that need to be updated.
         * @return          Good if the stored result could be updated, UnexpectedError if not.
         */
        uaf::Status updateResult(const ResultType& result, const uaf::Mask& mask);


        /**
         * Store a request and corresponding result, if a request with the same UAF handle doesn't
         * exist already.
         *
         * @param request           Request to be stored.
         * @param result            Corresponding result to be stored.
         * @param badTargetsMask    Mask specifying which targets are 'Bad'.
         */
        uaf::Status storeIfNeeded(
                const RequestType& request,
                const ResultType&  result,
                const uaf::Mask&   badTargetsMask);


    private:


        // no copying or assigning allowed
        DISALLOW_COPY_AND_ASSIGN(RequestStore);


        // typedef the map to store the items
        typedef typename std::map<uafc::RequestHandle, Item> ItemsMap;

        /* The map that stores the items. */
        ItemsMap itemsMap_;

        /* The mutex to manipulate the map safely. */
        UaMutex mutex_;

        /* The logger of the store. */
        uaf::Logger* logger_;
    };


    // Constructor
    // =============================================================================================
    template <typename _Service>
    RequestStore<_Service>::RequestStore(uaf::LoggerFactory* loggerFactory, const std::string& name)
    {
        logger_ = new uaf::Logger(loggerFactory, name);
    }


    // Destructor
    // =============================================================================================
    template <typename _Service>
    RequestStore<_Service>::~RequestStore()
    {
        clear();

        delete logger_;
    }


    // Clear the store
    // =============================================================================================
    template <typename _Service>
    void RequestStore<_Service>::clear()
    {
        logger_->debug("Now clearing the whole store");
        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        itemsMap_.clear();
    }


    // Log the current state
    // =============================================================================================
    template <typename _Service>
    void RequestStore<_Service>::logCurrentState()
    {
        logger_->debug("Current state:");
        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        typedef typename ItemsMap::const_iterator Iter;
        for (Iter it = itemsMap_.begin(); it != itemsMap_.end(); ++it)
        {
            logger_->debug("Item %d:", it->first);
            logger_->debug(" - badTargetsMask: %s", it->second.badTargetsMask.toString().c_str());
            logger_->debug(" - request:");
            logger_->debug(it->second.request.toString("   ", 39));
            logger_->debug(" - result:");
            logger_->debug(it->second.result.toString("   ", 39));
        }
    }


    // Remove a result
    // =============================================================================================
    template <typename _Service>
    uaf::Status RequestStore<_Service>::remove(uafc::RequestHandle handle)
    {
        logger_->debug("Now removing handle %d", handle);

        uaf::Status ret;

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        typename ItemsMap::iterator iter = itemsMap_.find(handle);

        if (iter != itemsMap_.end())
        {
            itemsMap_.erase(iter);
            ret.setGood();
        }
        else
        {
            ret.setStatus(uaf::statuscodes::InvalidRequestError,
                          "No item found for the given handle");
        }

        return ret;
    }


    // Update the status of a target
    // =============================================================================================
    template <typename _Service>
    uaf::Status RequestStore<_Service>::updateTargetStatus(
                    uafc::RequestHandle requestHandle,
                    std::size_t         targetRank,
                    const uaf::Status&  status)
    {
        uaf::Status ret;

        logger_->debug("Setting the status of request %d target %d to %s",
                       requestHandle, targetRank, status.toString().c_str());

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        typename ItemsMap::iterator iter = itemsMap_.find(requestHandle);

        if (iter != itemsMap_.end())
        {
            if (targetRank < iter->second.result.targets.size())
            {
                iter->second.result.targets[targetRank].status = status;
                if (status.isGood())
                    iter->second.badTargetsMask.unset(targetRank);
                else
                    iter->second.badTargetsMask.set(targetRank);

                // updated successfully:
                ret.setGood();
            }
            else
            {
                ret.setStatus(
                        uaf::statuscodes::InvalidRequestError,
                        "The target rank (%d) is higher or equal to the number of targets (%d)",
                        targetRank, iter->second.result.targets.size());
            }
        }
        else
        {
            ret.setStatus(uaf::statuscodes::InvalidRequestError,
                          "No item found for the given request handle");
        }

        if (ret.isGood())
            logger_->debug("The item was updated");
        else
            logger_->error(ret);

        return ret;
    }

    // Get a pointer to a result
    // =============================================================================================
    template <typename _Service>
    uaf::Status RequestStore<_Service>::get(
            uafc::RequestHandle                     handle,
            typename RequestStore<_Service>::Item&  item)
    {
        uaf::Status ret;

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        typename ItemsMap::const_iterator iter = itemsMap_.find(handle);

        if (iter != itemsMap_.end())
        {
            item = iter->second;
            ret.setGood();
        }
        else
        {
            ret.setStatus(uaf::statuscodes::InvalidRequestError,
                          "No item found for the given handle");
        }

        return ret;
    }


    // Get a pointer to a result
    // =============================================================================================
    template <typename _Service>
    std::vector< typename uafc::RequestStore<_Service>::Item > RequestStore<_Service>::getBadItems()
    {
        typename std::vector<Item> ret;

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        typedef typename ItemsMap::const_iterator Iter;
        for (Iter it = itemsMap_.begin(); it != itemsMap_.end(); ++it)
        {
            if (it->second.badTargetsMask.setCount() > 0)
                ret.push_back(it->second);
        }

        logCurrentState();

        return ret;
    }


    // Update a result
    // =============================================================================================
    template <typename _Service>
    uaf::Status RequestStore<_Service>::updateResult(
            const ResultType&   result,
            const uaf::Mask&    mask)
    {
        logger_->debug("Now updating the result with RequestHandle %d (mask: %s)",
                       result.requestHandle, mask.toString().c_str());

        uaf::Status ret;

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        typename ItemsMap::iterator it = itemsMap_.find(result.requestHandle);

        if (it != itemsMap_.end())
        {
            // the item was found, so update the return status
            ret.setGood();

            // loop over the targets
            for (std::size_t i = 0; i < result.targets.size(); i++)
            {

                // update the target if needed
                if (mask.isSet(i))
                    it->second.result.targets[i] = result.targets[i];

                // update the badTargetsMask, since we're iterating over the targets anyway
                if (it->second.result.targets[i].status.isNotGood())
                    it->second.badTargetsMask.set(i);
                else
                    it->second.badTargetsMask.unset(i);

            }
        }
        else
        {
            ret.setStatus(uaf::statuscodes::UnexpectedError,
                          "No item was found for the given handle");
        }

        return ret;
    }



    // Store a request and its corresponding result
    // =============================================================================================
    template <typename _Service>
    uaf::Status RequestStore<_Service>::storeIfNeeded(
            const RequestType& request,
            const ResultType&  result,
            const uaf::Mask&   badTargetsMask)
    {
        logger_->debug("Storing the request and result if needed");

        uaf::Status ret;

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        // check if an item exists already for the given handle
        if (itemsMap_.find(result.requestHandle) == itemsMap_.end())
        {
            // add a new item
            itemsMap_.insert(std::pair<uafc::RequestHandle, Item>(
                    result.requestHandle,
                    Item(request, result, badTargetsMask)));

            logger_->debug("The request and result are now stored");
        }
        else
        {
            logger_->debug("The request and result were already stored");
        }

        // ToDo add checks, e.g. if a valid handle is found, and update the return status
        ret.setGood();

        return ret;
    }





    /*******************************************************************************************//**
    * A CreateMonitoredDataRequestStore is used to re-create monitored data items after failures.
    *
    * @ingroup ClientDatabase
    ***********************************************************************************************/
    typedef uafc::RequestStore<uafc::CreateMonitoredDataService> CreateMonitoredDataRequestStore;




    /*******************************************************************************************//**
    * A CreateMonitoredEventsRequestStore is used to re-create monitored event items after failures.
    *
    * @ingroup ClientDatabase
    ***********************************************************************************************/
    typedef uafc::RequestStore<uafc::CreateMonitoredEventsService> CreateMonitoredEventsRequestStore;




}

#endif /* UAFC_REQUESTSTORE_H_ */
