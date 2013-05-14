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

#include "uaf/client/database/addresscache.h"




namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::vector;
    using std::map;
    using std::size_t;


    // Constructor
    // =============================================================================================
    AddressCache::AddressCache(LoggerFactory* loggerFactory)
    {
        logger_ = new Logger(loggerFactory, "AddressCache");
        logger_->debug("The address cache has been constructed");
    }


    // Destructor
    // =============================================================================================
    AddressCache::~AddressCache()
    {
        logger_->debug("Destructing the address cache");

        clear();

        delete logger_;
        logger_ = 0;
    }


    // Remove all items from the cache
    // =============================================================================================
    void AddressCache::clear()
    {
        logger_->info("Clearing the address cache");

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        cache_.clear();
    }


    // Remove all items from the cache with the given server URI
    // =============================================================================================
    void AddressCache::clear(const string& serverUri)
    {
        logger_->info("Clearing the cached addresses for ServerUri '%s':", serverUri.c_str());

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        Cache::iterator it = cache_.begin();
        while(it != cache_.end())
        {
            if (it->second.serverUri() == serverUri)
            {
                logger_->debug("Removing the address from the cache");
                cache_.erase(it++);  // The post increment increments the iterator but returns the
                                     // original value for use by erase
            }
            else
            {
                ++it; // Can use pre-increment here to make sure you have the efficient version
            }
        }

        logger_->debug("All cached addresses for ServerUri '%s' have been cleared",
                       serverUri.c_str());

    }


    // Add an address and its resolved ExpandedNodeId to the cache
    // =============================================================================================
    void AddressCache::add(
            const Address&          address,
            const ExpandedNodeId&   expandedNodeId,
            bool                    replaceIfExists)
    {

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        Cache::iterator iter = cache_.find(address);

        if (iter == cache_.end() || replaceIfExists)
        {
            logger_->info("The address is now cached");

            cache_[address] = expandedNodeId;
        }
        else
        {
            logger_->info("The address was already cached and we mustn't replace it");
        }
    }


    // Add multiple addresses and their resolved ExpandedNodeIds to the cache
    // =============================================================================================s
    void AddressCache::add(
            const vector<Address>&          addresses,
            const vector<ExpandedNodeId>&   expandedNodeIds,
            bool                            replaceIfExists)
    {
        if (replaceIfExists)
            logger_->debug("Caching %d addresses (existing items will be replaced)",
                           addresses.size());
        else
            logger_->debug("Caching %d addresses (existing items will NOT be replaced)",
                           addresses.size());

        for (size_t i = 0; i < addresses.size(); i++)
            add(addresses[i], expandedNodeIds[i], replaceIfExists);
    }


    // Find the resolved ExpandedNodeId for a particular address
    // =============================================================================================
    bool AddressCache::find(const Address& address, uaf::ExpandedNodeId& expandedNodeId)
    {
        logger_->debug("Trying to find the address in the cache");

        UaMutexLocker locker(&mutex_); // unlocks when locker goes out of scope

        Cache::iterator iter = cache_.find(address);

        bool found = (iter != cache_.end());

        if (found)
        {
            expandedNodeId = iter->second;
            logger_->info("The address was found in the cache");
            logger_->info("It corresponds to %s", expandedNodeId.toString().c_str());
        }
        else
        {
            logger_->info("The address was not found in the cache");
        }

        return found;
    }




}


