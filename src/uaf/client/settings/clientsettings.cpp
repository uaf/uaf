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

#include "uaf/client/settings/clientsettings.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::size_t;
    using std::string;
    using std::stringstream;
    using std::vector;


    // Constructor
    // =============================================================================================
    ClientSettings::ClientSettings()
    : logToStdOutLevel(uaf::loglevels::Disabled),
      logToCallbackLevel(uaf::loglevels::Disabled),
      discoveryFindServersTimeoutSec(2.0),
      discoveryGetEndpointsTimeoutSec(1.0),
      discoveryIntervalSec(30.0)
    {}

    // Constructor
    // =============================================================================================
    ClientSettings::ClientSettings(const string& applicationName)
    : applicationName(applicationName),
      logToStdOutLevel(uaf::loglevels::Disabled),
      logToCallbackLevel(uaf::loglevels::Disabled),
      discoveryFindServersTimeoutSec(2.0),
      discoveryGetEndpointsTimeoutSec(1.0),
      discoveryIntervalSec(30.0)
    {}

    // Constructor
    // =============================================================================================
    ClientSettings::ClientSettings(
            const string&           applicationName,
            const vector<string>&   discoveryUrls)
    : applicationName(applicationName),
      logToStdOutLevel(uaf::loglevels::Disabled),
      logToCallbackLevel(uaf::loglevels::Disabled),
      discoveryUrls(discoveryUrls),
      discoveryFindServersTimeoutSec(2.0),
      discoveryGetEndpointsTimeoutSec(1.0),
      discoveryIntervalSec(30.0)
    {}


    // Get a string representation
    // =============================================================================================
    string ClientSettings::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - applicationName";
        ss << fillToPos(ss, colon);
        ss << ": "  << applicationName << "\n";

        ss << indent << " - applicationUri";
        ss << fillToPos(ss, colon);
        ss << ": "  << applicationUri << "\n";

        ss << indent << " - productUri";
        ss << fillToPos(ss, colon);
        ss << ": " << productUri << "\n";

        ss << indent << " - localeId";
        ss << fillToPos(ss, colon);
        ss << ": "  << localeId << "\n";

        ss << indent << " - logToStdOutLevel";
        ss << fillToPos(ss, colon);
        ss << ": "  << logToStdOutLevel
                    << "(" << uaf::loglevels::toString(logToStdOutLevel) << ")" << "\n";

        ss << indent << " - logToCallbackLevel";
        ss << fillToPos(ss, colon);
        ss << ": "  << logToCallbackLevel
                    << "(" << uaf::loglevels::toString(logToCallbackLevel) << ")" << "\n";

        ss << indent << " - discoveryUrls[]";

        if (discoveryUrls.size() == 0)
        {
            ss << fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            ss << "\n";

            for (size_t i = 0; i<discoveryUrls.size(); i++)
            {
                ss << indent << "    - " << "discoveryUrls[" << i << "]";
                fillToPos(ss, colon);
                ss << ": " << discoveryUrls[i] << "\n";
            }
        }

        ss << indent << " - discoveryIntervalSec";
        ss << fillToPos(ss, colon);
        ss << ": " << discoveryIntervalSec << "\n";

        ss << indent << " - discoveryFindServersTimeoutSec";
        ss << fillToPos(ss, colon);
        ss << ": " << discoveryFindServersTimeoutSec << "\n";

        ss << indent << " - discoveryGetEndpointsTimeoutSec";
        ss << fillToPos(ss, colon);
        ss << ": " << discoveryGetEndpointsTimeoutSec << "\n";

        ss << indent << " - certificateRevocationListAbsoluteFileName";
        ss << fillToPos(ss, colon);
        ss << ": " << certificateRevocationListAbsoluteFileName << "\n";

        ss << indent << " - certificateTrustAbsoluteDirectory";
        ss << fillToPos(ss, colon);
        ss << ": " << certificateTrustAbsoluteDirectory << "\n";

        ss << indent << " - clientCertificateAbsoluteFileName";
        ss << fillToPos(ss, colon);
        ss << ": " << clientCertificateAbsoluteFileName << "\n";

        ss << indent << " - clientPrivateKeyAbsoluteFileName";
        ss << fillToPos(ss, colon);
        ss << ": " << clientPrivateKeyAbsoluteFileName << "\n";

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const ClientSettings& object1, const ClientSettings& object2)
    {
        return    object1.applicationName == object2.applicationName
               && object1.applicationUri == object2.applicationUri
               && object1.productUri == object2.productUri
               && object1.localeId == object2.localeId
               && object1.discoveryUrls == object2.discoveryUrls
               && object1.logToStdOutLevel == object2.logToStdOutLevel
               && object1.logToCallbackLevel == object2.logToCallbackLevel
               && object1.discoveryFindServersTimeoutSec == object2.discoveryFindServersTimeoutSec
               && object1.discoveryGetEndpointsTimeoutSec == object2.discoveryGetEndpointsTimeoutSec
               && object1.certificateRevocationListAbsoluteFileName == object2.certificateRevocationListAbsoluteFileName
               && object1.certificateTrustAbsoluteDirectory == object2.certificateTrustAbsoluteDirectory
               && object1.clientCertificateAbsoluteFileName == object2.clientCertificateAbsoluteFileName
               && object1.clientPrivateKeyAbsoluteFileName == object2.clientPrivateKeyAbsoluteFileName;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ClientSettings& object1, const ClientSettings& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ClientSettings& object1, const ClientSettings& object2)
    {
        if (object1.applicationName != object2.applicationName)
            return object1.applicationName < object2.applicationName;
        else if (object1.applicationUri != object2.applicationUri)
            return object1.applicationUri < object2.applicationUri;
        else if (object1.productUri != object2.productUri)
            return object1.productUri < object2.productUri;
        else if (object1.localeId != object2.localeId)
            return object1.localeId < object2.localeId;
        else if (object1.discoveryUrls != object2.discoveryUrls)
            return object1.discoveryUrls < object2.discoveryUrls;
        else if (object1.logToStdOutLevel != object2.logToStdOutLevel)
            return object1.logToStdOutLevel < object2.logToStdOutLevel;
        else if (object1.logToCallbackLevel != object2.logToCallbackLevel)
            return object1.logToCallbackLevel < object2.logToCallbackLevel;
        else if (object1.discoveryFindServersTimeoutSec != object2.discoveryFindServersTimeoutSec)
            return object1.discoveryFindServersTimeoutSec < object2.discoveryFindServersTimeoutSec;
        else if (object1.discoveryGetEndpointsTimeoutSec != object2.discoveryGetEndpointsTimeoutSec)
            return object1.discoveryGetEndpointsTimeoutSec < object2.discoveryGetEndpointsTimeoutSec;
        else if (object1.certificateRevocationListAbsoluteFileName != object2.certificateRevocationListAbsoluteFileName)
            return object1.certificateRevocationListAbsoluteFileName < object2.certificateRevocationListAbsoluteFileName;
        else if (object1.certificateTrustAbsoluteDirectory != object2.certificateTrustAbsoluteDirectory)
            return object1.certificateTrustAbsoluteDirectory < object2.certificateTrustAbsoluteDirectory;
        else if (object1.clientCertificateAbsoluteFileName != object2.clientCertificateAbsoluteFileName)
            return object1.clientCertificateAbsoluteFileName < object2.clientCertificateAbsoluteFileName;
        else
            return object1.clientPrivateKeyAbsoluteFileName < object2.clientPrivateKeyAbsoluteFileName;
    }

}

