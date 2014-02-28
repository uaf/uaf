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

#include "uaf/util/applicationdescription.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    ApplicationDescription::ApplicationDescription()
    : applicationType(applicationtypes::Client)
    {}


    // Constructor
    // =============================================================================================
    ApplicationDescription::ApplicationDescription(const OpcUa_ApplicationDescription& desc)
    : applicationName(desc.ApplicationName),
      applicationType(applicationtypes::fromSdkToUaf(desc.ApplicationType))
    {
        if (!UaString(&desc.ApplicationUri).isEmpty())
            applicationUri = UaString(&desc.ApplicationUri).toUtf8();
        if (!UaString(&desc.ProductUri).isEmpty())
            applicationUri = UaString(&desc.ProductUri).toUtf8();
        if (!UaString(&desc.GatewayServerUri).isEmpty())
            applicationUri = UaString(&desc.GatewayServerUri).toUtf8();
        if (!UaString(&desc.DiscoveryProfileUri).isEmpty())
            applicationUri = UaString(&desc.DiscoveryProfileUri).toUtf8();

        // set the discovery URLs
        for (int32_t i = 0; i < desc.NoOfDiscoveryUrls; i++)
        {
            if (!UaString(&desc.DiscoveryUrls[i]).isEmpty())
                discoveryUrls.push_back(string(UaString(&desc.DiscoveryUrls[i]).toUtf8()));
        }
    }


    // Constructor
    // =============================================================================================
    ApplicationDescription::ApplicationDescription(
            string                              applicationUri,
            string                              productUri,
            LocalizedText                       applicationName,
            applicationtypes::ApplicationType   applicationType,
            string                              gatewayServerUri,
            string                              discoveryProfileUri,
            vector<string>                      discoveryUrls)
    : applicationUri(applicationUri),
      productUri(productUri),
      applicationName(applicationName),
      applicationType(applicationType),
      gatewayServerUri(gatewayServerUri),
      discoveryProfileUri(discoveryProfileUri),
      discoveryUrls(discoveryUrls)
    {}


    // Is the application description empty?
    // =============================================================================================
    bool ApplicationDescription::isEmpty() const
    {
        return applicationUri.empty();
    }


    // Get a string representation
    // =============================================================================================
    string ApplicationDescription::toString(const string& indentation, size_t colon) const
    {
        stringstream ss;

        ss << indentation << " - applicationType";
        ss << fillToPos(ss, colon);
        ss << ": " << applicationType;
        ss << " (" << applicationtypes::toString(applicationType) << ")\n";

        ss << indentation << " - applicationName";
        ss << fillToPos(ss, colon);
        ss << ": " << applicationName.toString() << "\n";

        ss << indentation << " - applicationUri";
        ss << fillToPos(ss, colon);
        ss << ": " << applicationUri << "\n";

        ss << indentation << " - productUri";
        ss << fillToPos(ss, colon);
        ss << ": " << productUri << "\n";

        ss << indentation << " - discoveryUrls[]";

        if (discoveryUrls.size() == 0)
        {
            fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i<discoveryUrls.size(); i++)
            {
                ss << indentation << "    - " << "discoveryUrls[" << i << "]";
                fillToPos(ss, colon);
                ss << ": " << discoveryUrls[i] << "\n";
            }
        }

        ss << indentation << " - discoveryProfileUri";
        fillToPos(ss, colon);
        ss << ": " << discoveryProfileUri << "\n";

        ss << indentation << " - gatewayServerUri";
        fillToPos(ss, colon);
        ss << ": " << gatewayServerUri;

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const ApplicationDescription& object1, const ApplicationDescription& object2)
    {
        return    object1.applicationType == object2.applicationType
               && object1.applicationName == object2.applicationName
               && object1.applicationUri == object2.applicationUri
               && object1.productUri == object2.productUri
               && object1.discoveryUrls == object2.discoveryUrls
               && object1.discoveryProfileUri == object2.discoveryProfileUri
               && object1.gatewayServerUri == object2.gatewayServerUri;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ApplicationDescription& object1, const ApplicationDescription& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ApplicationDescription& object1, const ApplicationDescription& object2)
    {
        if (object1.applicationType != object2.applicationType)
            return object1.applicationType < object2.applicationType;
        else if (object1.applicationName != object2.applicationName)
            return object1.applicationName < object2.applicationName;
        else if (object1.applicationUri != object2.applicationUri)
            return object1.applicationUri < object2.applicationUri;
        else if (object1.productUri != object2.productUri)
            return object1.productUri < object2.productUri;
        else if (object1.discoveryUrls != object2.discoveryUrls)
            return object1.discoveryUrls < object2.discoveryUrls;
        else if (object1.discoveryProfileUri != object2.discoveryProfileUri)
            return object1.discoveryProfileUri < object2.discoveryProfileUri;
        else
            return object1.gatewayServerUri < object2.gatewayServerUri;
    }

}
