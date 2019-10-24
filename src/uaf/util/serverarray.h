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

#ifndef UAF_SERVERARRAY_H_
#define UAF_SERVERARRAY_H_


// STD
#include <string>
#include <sstream>
#include <map>
#include <stdint.h>
// SDK
#include "uabasecpp/uaarraytemplates.h"
#include "uabasecpp/uastring.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/status.h"
#include "uaf/util/variant.h"


namespace uaf
{


    /*******************************************************************************************//**
    * A ServerArray maps server indexes to server URIs.
    *
    * A Server Array maps ServerIndexes (uint32_t) to ServerURIs (string). ServerArrays
    * are exposed by servers, so that clients can look up the URI of a server if for instance
    * they want to follow a reference to another server (via an ExpandedNodeId, which contains
    * the ServerIndex of the referenced Node).
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT ServerArray
    {
    public:
        /**
         * Construct an empty ServerArray.
         */
        ServerArray();


        /**
         * Fill the ServerArray with the information contained by the given OpcUa_DataValue stack
         * object.
         *
         * @param value     A data value as a stack object.
         * @return          The Status of this operation.
         */
        uaf::Status fromSdk(const OpcUa_DataValue& value);


        /**
         * Get a string representation of the ServerArray.
         * @return  The string representation.
         */
        std::string toString() const;


        /**
         * Find the ServerURI for a given ServerIndex.
         *
         * @param serverIndex   The ServerIndex that needs to be looked up.
         * @param serverUri     The ServerUri that will be overwritten.
         * @return              True if the server index was found.
         */
        bool findServerUri(ServerIndex serverIndex, std::string& serverUri) const;


        /**
         * Update the server array with a given index and URI.
         *
         * @param serverIndex   The ServerIndex that will be updated.
         * @param serverUri     The ServerUri that will be updated.
         */
        void update(ServerIndex serverIndex, const std::string& serverUri);


        /**
         * Find the ServerIndex for a given ServerURI.
         *
         * @param serverUri     the ServerURI that needs to be looked up
         * @param serverIndex   the ServerIndex that will be overwritten
         * @return              True if the server index was found.
         */
        bool findServerIndex(const std::string& serverUri, ServerIndex& serverIndex) const;


        /**
         * Update the server URI of an ExpandedNodeId by using the server index from an
         * OpcUa_ExpandedNodeId .
         *
         * @param opcUaExpandedNodeId   The OpcUa_ExpandedNodeId from which we want to extract
         *                              the server index.
         * @param expandedNodeId        The uaf::ExpandedNodeId which we want to update.
         * @return                      True if the uaf::ExpandedNodeId could be updated without
         *                              problems (i.e. if the namespace URI could be set).
         */
        uaf::Status fillExpandedNodeId(
                const OpcUa_ExpandedNodeId& opcUaExpandedNodeId,
                uaf::ExpandedNodeId&        expandedNodeId) const;


        /**
         * Fill a Variant, which *may* include filling out the server URI, if the variant
         * represents an ExpandedNodeId.
         *
         * @param variant         The uaf::Variant which we want to update.
         * @return                Good if the uaf::Variant could be updated without
         *                        problems (i.e. if the namespace URI could be set).
         */
        uaf::Status fillVariant(uaf::Variant& variant) const;


    private:
        // Define a map with key=serverIndex value=serverURI
        typedef std::map<ServerIndex, std::string> ServerArrayMap;

        // the internal map
        ServerArrayMap serverArrayMap_;

    };

}

#endif /* UAF_SERVERARRAY_H_ */
