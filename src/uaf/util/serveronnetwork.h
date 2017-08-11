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

#ifndef UAF_SERVERONNETWORK_H_
#define UAF_SERVERONNETWORK_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uaclient/uadiscovery.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/localizedtext.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/applicationtypes.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A ServerOnNetwork instance describes a Server found on the network using the
    * FindServersOnNetwork service.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ServerOnNetwork
    {
    public:


        /**
         * Create an empty server on network description.
         */
        ServerOnNetwork();


        /**
         * Create an server on network description based on the corresponding stack variable.
         */
        ServerOnNetwork(const OpcUa_ServerOnNetwork& desc);

        /** The record ID. */
        uint32_t                    recordId;
        /** The server name. */
        std::string                 serverName;
        /** The discovery url. */
        std::string                 discoveryUrl;
        /** The server capabilities. */
        std::vector<std::string>    serverCapabilities;

        /**
         * Get a string representation.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=11) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const ServerOnNetwork& object1,
                const ServerOnNetwork& object2);
        friend UAF_EXPORT bool operator!=(
                const ServerOnNetwork& object1,
                const ServerOnNetwork& object2);
        friend UAF_EXPORT bool operator<(
                const ServerOnNetwork& object1,
                const ServerOnNetwork& object2);

    };


}



#endif /* UAF_SERVERONNETWORK_H_ */
