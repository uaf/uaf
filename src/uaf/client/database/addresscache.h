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

#ifndef UAF_ADDRESSCACHE_H_
#define UAF_ADDRESSCACHE_H_

// STD
#include <string>
#include <sstream>
#include <vector>
#include <map>
// SDK
#include "uabasecpp/uamutex.h"
// UAF
#include "uaf/util/expandednodeid.h"
#include "uaf/util/status.h"
#include "uaf/util/logger.h"
#include "uaf/util/address.h"
#include "uaf/client/clientexport.h"


namespace uaf
{


    /*******************************************************************************************//**
    * A uaf::AddressCache can speed up address resolution by storing the ExpandedNodeId for each
    * Address.
    *
    * @ingroup ClientDatabase
    ***********************************************************************************************/
    class UAF_EXPORT AddressCache
    {
    public:


        /**
         * Create an address cache which logs to the specified logger factory.
         *
         * @param loggerFactory The logger factory to log to.
         */
        AddressCache(uaf::LoggerFactory* loggerFactory);


        /**
         * Destruct the cache.
         */
        virtual ~AddressCache();


        /**
         * Clear the cache.
         */
        void clear();


        /**
         * Remove all cached addresses that belong to the given server URI.
         */
        void clear(const std::string& serverUri);


        /**
         * Add an address (and its resolved ExpandedNodeId) to the cache.
         *
         * @param address           The address to cache.
         * @param resolvedNodeId    The resolved expanded node id of the first argument.
         * @param replaceIfExists   True to replace the cached value if an entry exists already.
         */
        void add(
                const uaf::Address&         address,
                const uaf::ExpandedNodeId&  resolvedNodeId,
                bool                        replaceIfExists = false);


        /**
         * Add a number of addresses (and their resolved ExpandedNodeIds) to the cache.
         *
         * @param addresses         The addresses to cache.
         * @param expandedNodeIds   The expanded node ids of the first argument.
         * @param replaceIfExists   True to replace the cached values if they exist already.
         */
        void add(
                const std::vector<uaf::Address>&        addresses,
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                bool                                    replaceIfExists = false);


        /**
         * Find a the resolved expanded node id of the specified address in the cache.
         *
         * @param address           The address to look up.
         * @param expandedNodeId    The found expandedNodeId (if the address was cached of course).
         * @return                  True if the address was found, false if not.
         */
        bool find(const uaf::Address& address, uaf::ExpandedNodeId& expandedNodeId);



    private:


        // no copying or assigning allowed
        DISALLOW_COPY_AND_ASSIGN(AddressCache);


        // private typedefs


        /** A cache stores the addresses and their corresponding ExpandedNodeIds. */
        typedef std::map<uaf::Address, uaf::ExpandedNodeId> Cache;


        // private members


        /** The logger of the address cache. */
        uaf::Logger* logger_;

        /** The map containing the cached addresses. */
        Cache cache_;

        /** The mutex to safely manipulate the map. */
        UaMutex mutex_;

    };

}


#endif /* UAF_ADDRESSCACHE_H_ */
