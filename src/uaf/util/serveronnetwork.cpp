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

#include "uaf/util/serveronnetwork.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    ServerOnNetwork::ServerOnNetwork()
    : recordId(0)
    {}


    // Constructor
    // =============================================================================================
    ServerOnNetwork::ServerOnNetwork(const OpcUa_ServerOnNetwork& desc)
    : recordId(desc.RecordId)
    {
        if (!UaString(&desc.ServerName).isEmpty())
            serverName = UaString(&desc.ServerName).toUtf8();
        if (!UaString(&desc.DiscoveryUrl).isEmpty())
            discoveryUrl = UaString(&desc.DiscoveryUrl).toUtf8();

        // set the discovery URLs
        for (int32_t i = 0; i < desc.NoOfServerCapabilities; i++)
        {
            if (!UaString(&desc.ServerCapabilities[i]).isEmpty())
                serverCapabilities.push_back(string(UaString(&desc.ServerCapabilities[i]).toUtf8()));
        }
    }

    // Get a string representation
    // =============================================================================================
    string ServerOnNetwork::toString(const string& indentation, size_t colon) const
    {
        stringstream ss;

        ss << indentation << " - recordId";
        ss << fillToPos(ss, colon);
        ss << ": " << recordId << "\n";

        ss << indentation << " - serverName";
        ss << fillToPos(ss, colon);
        ss << ": " << serverName << "\n";

        ss << indentation << " - discoveryUrl";
        ss << fillToPos(ss, colon);
        ss << ": " << discoveryUrl << "\n";

        ss << indentation << " - serverCapabilities[]";

        if (serverCapabilities.size() == 0)
        {
            fillToPos(ss, colon);
            ss << ": []";
        }
        else
        {
            for (size_t i = 0; i<serverCapabilities.size(); i++)
            {
                ss << "\n";
                ss << indentation << "    - " << "serverCapabilities[" << i << "]";
                fillToPos(ss, colon);
                ss << ": " << serverCapabilities[i];
            }
        }

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const ServerOnNetwork& object1, const ServerOnNetwork& object2)
    {
        return    object1.recordId == object2.recordId
               && object1.serverName == object2.serverName
               && object1.discoveryUrl == object2.discoveryUrl
               && object1.serverCapabilities == object2.serverCapabilities;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ServerOnNetwork& object1, const ServerOnNetwork& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ServerOnNetwork& object1, const ServerOnNetwork& object2)
    {
        if (object1.recordId != object2.recordId)
            return object1.recordId < object2.recordId;
        else if (object1.serverName != object2.serverName)
            return object1.serverName < object2.serverName;
        else if (object1.discoveryUrl != object2.discoveryUrl)
            return object1.discoveryUrl < object2.discoveryUrl;
        else
            return object1.serverCapabilities < object2.serverCapabilities;
    }

}
