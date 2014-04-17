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

#include "uaf/util/serverarray.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::map;
    using std::vector;


    // Constructor
    // =============================================================================================
    ServerArray::ServerArray() {}


    // Read the contents of a data value as returned when a client reads the ServerArray NodeId.
    // =============================================================================================
    Status ServerArray::fromSdk(const OpcUa_DataValue& value)
    {
        Status ret;

        // check if the status of the value is good:
        if (OpcUa_IsGood(value.StatusCode))
        {
            UaStringArray    stringArray;
            OpcUa_StatusCode uaConversionStatusCode;

            // convert the value to a StringArray
            uaConversionStatusCode = UaVariant(value.Value).toStringArray(stringArray);

            // if the conversion succeeded, fill the map
            if (OpcUa_IsGood(uaConversionStatusCode))
            {
                for (uint32_t i=0; i<stringArray.length(); i++)
                    update(i, string(UaString(&stringArray[i]).toUtf8()));
            }

            // update the status
            ret.fromSdk(uaConversionStatusCode,
                                   "Could not convert the received data value");
        }
        // if the status of the value was not good, just update the return status
        else
        {
            ret.fromSdk(value.StatusCode, "Could not process the received data value");
        }

        return ret;
    }


    // Look up the ServerURI for a given ServerIndex
    // =============================================================================================
    bool ServerArray::findServerUri(ServerIndex serverIndex, string& serverUri) const
    {
        // find the ServerIndex
        ServerArrayMap::const_iterator iter = serverArrayMap_.find(serverIndex);

        bool found = (iter != serverArrayMap_.end());

        // if the ServerIndex was not found, set the return status to bad
        if (found)
            serverUri = iter->second;

        return found;
    }


    // Look up the ServerURI for a given ServerIndex
    // =============================================================================================
    void ServerArray::update(ServerIndex serverIndex, const string& serverUri)
    {
        serverArrayMap_[serverIndex] = serverUri;
    }


    // Look up the ServerIndex for a given ServerURI
    // =============================================================================================
    bool ServerArray::findServerIndex(const string& serverUri, ServerIndex& serverIndex) const
    {
        // We need to do a "reverse" lookup, by iterating over the key:value pairs until we have
        // found the correct value.

        // iterate over the key:value pairs
        for (ServerArrayMap::const_iterator iter = serverArrayMap_.begin();
                iter != serverArrayMap_.end();
                iter++)
        {
            // if the ServerURI was found, assign the serverIndex, update the status, and return
            if (iter->second == serverUri)
            {
                serverIndex = iter->first;

                // we found the URI, so we can return!
                return true;
            }
        }

        // we haven't returned yet, so the URI was not found...
        return false;
    }


    // Update the server URI of an uaf::ExpandedNodeId
    // =============================================================================================
    Status ServerArray::fillExpandedNodeId(
            const OpcUa_ExpandedNodeId& opcUaExpandedNodeId,
            ExpandedNodeId&             expandedNodeId) const
    {
        Status ret;

        string serverUri;

        if (findServerUri(opcUaExpandedNodeId.ServerIndex, serverUri))
        {
            expandedNodeId.setServerUri(serverUri);
            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::ResolutionError,
                          "Unknown server index %d",
                          opcUaExpandedNodeId.ServerIndex);
        }

        return ret;
    }


    // Get a string representation of the Server Array (one line per ServerIndex:ServerURI pair)
    // =============================================================================================
    string ServerArray::toString() const
    {
        stringstream ss;

        // iterate over the map
        for (ServerArrayMap::const_iterator iter = serverArrayMap_.begin();
                iter != serverArrayMap_.end();
                iter++)
        {
            ss << " " << iter->first << ": " << iter->second << "\n";
        }

        return ss.str();
    }


#define FILL_OPCUA_VARIANT_SERVERURI(TYPE)                                                          \
        if (variant.isArray())                                                                      \
        {                                                                                           \
            vector<TYPE> vec;                                                                       \
            variant.to##TYPE##Array(vec);                                                           \
                                                                                                    \
            if (vec.size() == 0) ret.setGood();                                                     \
                                                                                                    \
            for (std::size_t i = 0; i < vec.size() && ret.isNotBad(); i++)                          \
            {                                                                                       \
                OpcUa_##TYPE opcUaObject;                                                           \
                vec[i].toSdk(&opcUaObject);                                                         \
                ret = fill##TYPE(opcUaObject, vec[i]);                                              \
            }                                                                                       \
                                                                                                    \
            if (ret.isGood()) variant.set##TYPE##Array(vec);                                        \
        }                                                                                           \
        else                                                                                        \
        {                                                                                           \
            TYPE value;                                                                             \
            variant.to##TYPE(value);                                                                \
                                                                                                    \
            OpcUa_##TYPE opcUaObject;                                                               \
            value.toSdk(&opcUaObject);                                                              \
            ret = fill##TYPE(opcUaObject, value);                                                   \
                                                                                                    \
            if (ret.isGood()) variant.set##TYPE(value);                                             \
        }

    // Fill out a Variant
    // =============================================================================================
    Status ServerArray::fillVariant(Variant& variant) const
    {
        Status ret;

        // only types with a namespace URI/index need to be filled:

        if (variant.type() == uaf::opcuatypes::ExpandedNodeId)
        {
            FILL_OPCUA_VARIANT_SERVERURI(ExpandedNodeId)
        }

        else
        {
            ret.setGood();
        }

        return ret;
    }


}
