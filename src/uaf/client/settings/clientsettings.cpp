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


namespace uaf
{
    using namespace uaf;
    using std::size_t;
    using std::string;
    using std::stringstream;
    using std::vector;

    template<> uaf::BrowseNextSettings                      getDefaultServiceSettings<uaf::BrowseNextSettings>                      (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultBrowseNextSettings; }
    template<> uaf::BrowseSettings                          getDefaultServiceSettings<uaf::BrowseSettings>                          (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultBrowseSettings; }
    template<> uaf::CreateMonitoredDataSettings             getDefaultServiceSettings<uaf::CreateMonitoredDataSettings>             (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultCreateMonitoredDataSettings; }
    template<> uaf::CreateMonitoredEventsSettings           getDefaultServiceSettings<uaf::CreateMonitoredEventsSettings>           (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultCreateMonitoredEventsSettings; }
    template<> uaf::HistoryReadRawModifiedSettings          getDefaultServiceSettings<uaf::HistoryReadRawModifiedSettings>          (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultHistoryReadRawModifiedSettings; }
    template<> uaf::ReadSettings                            getDefaultServiceSettings<uaf::ReadSettings>                            (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultReadSettings; }
    template<> uaf::TranslateBrowsePathsToNodeIdsSettings   getDefaultServiceSettings<uaf::TranslateBrowsePathsToNodeIdsSettings>   (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultTranslateBrowsePathsToNodeIdsSettings; }
    template<> uaf::WriteSettings                           getDefaultServiceSettings<uaf::WriteSettings>                           (const uaf::ClientSettings& clientSettings) { return clientSettings.defaultWriteSettings; }



    // Constructor
    // =============================================================================================
    ClientSettings::ClientSettings()
    : logToStdOutLevel(uaf::loglevels::Disabled),
      logToCallbackLevel(uaf::loglevels::Disabled),
      discoveryFindServersTimeoutSec(2.0),
      discoveryGetEndpointsTimeoutSec(1.0),
      discoveryIntervalSec(30.0),
      certificateTrustListLocation("PKI/trusted/certs/"),
      certificateRevocationListLocation("PKI/trusted/crl/"),
      issuersCertificatesLocation("PKI/issuers/certs/"),
      issuersRevocationListLocation("PKI/issuers/crl/"),
      createSecurityLocationsIfNeeded(true),
      clientPrivateKey("PKI/client/private/client.pem"),
      clientCertificate("PKI/client/certs/client.der")

    {}

    // Constructor
    // =============================================================================================
    ClientSettings::ClientSettings(const string& applicationName)
    : applicationName(applicationName),
      logToStdOutLevel(uaf::loglevels::Disabled),
      logToCallbackLevel(uaf::loglevels::Disabled),
      discoveryFindServersTimeoutSec(2.0),
      discoveryGetEndpointsTimeoutSec(1.0),
      discoveryIntervalSec(30.0),
      certificateTrustListLocation("PKI/trusted/certs/"),
      certificateRevocationListLocation("PKI/trusted/crl/"),
      issuersCertificatesLocation("PKI/issuers/certs/"),
      issuersRevocationListLocation("PKI/issuers/crl/"),
      createSecurityLocationsIfNeeded(true),
      clientPrivateKey("PKI/client/private/client.pem"),
      clientCertificate("PKI/client/certs/client.der")
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
      discoveryIntervalSec(30.0),
      certificateTrustListLocation("PKI/trusted/certs/"),
      certificateRevocationListLocation("PKI/trusted/crl/"),
      issuersCertificatesLocation("PKI/issuers/certs/"),
      issuersRevocationListLocation("PKI/issuers/crl/"),
      createSecurityLocationsIfNeeded(true),
      clientPrivateKey("PKI/client/private/client.pem"),
      clientCertificate("PKI/client/certs/client.der")
    {}


    // Create the security locations
    // =============================================================================================
    Status ClientSettings::createSecurityLocations() const
    {
        Status ret;
        UaDir helperDir(UaUniString(""));

        UaUniString location;

        location = certificateTrustListLocation.c_str();
        if (helperDir.exists(location))
            ret = statuscodes::Good;
        else
            if (helperDir.mkpath(location))
                ret = statuscodes::Good;
            else
                ret = CouldNotCreateCertificateTrustListLocationError(certificateTrustListLocation);
        if (ret.isGood())
        {
            location = certificateRevocationListLocation.c_str();

            if (helperDir.exists(location))
                ret = statuscodes::Good;
            else
                if (helperDir.mkpath(location))
                    ret = statuscodes::Good;
                else
                    ret = CouldNotCreateCertificateRevocationListLocationError(
                            certificateRevocationListLocation);
        }

        if (ret.isGood())
        {
            location = issuersCertificatesLocation.c_str();

            if (helperDir.exists(location))
                ret = statuscodes::Good;
            else
                if (helperDir.mkpath(location))
                    ret = statuscodes::Good;
                else
                    ret = CouldNotCreateIssuersCertificateLocationError(
                            issuersCertificatesLocation);
        }

        if (ret.isGood())
        {
            location = issuersRevocationListLocation.c_str();

            if (helperDir.exists(location))
                ret = statuscodes::Good;
            else
                if (helperDir.mkpath(location))
                    ret = statuscodes::Good;
                else
                    ret = CouldNotCreateIssuersRevocationListLocationError(
                            issuersRevocationListLocation);
        }

        if (ret.isGood())
        {
            location = helperDir.filePath(UaUniString(clientPrivateKey.c_str()));

            if (helperDir.exists(location))
                ret = statuscodes::Good;
            else
                if (helperDir.mkpath(location))
                    ret = statuscodes::Good;
                else
                    ret = CouldNotCreateClientPrivateKeyLocationError(clientPrivateKey);
        }

        if (ret.isGood())
        {
            location = helperDir.filePath(UaUniString(clientCertificate.c_str()));

            if (helperDir.exists(location))
                ret = statuscodes::Good;
            else
                if (helperDir.mkpath(location))
                    ret = statuscodes::Good;
                else
                    ret = CouldNotCreateClientCertificateLocationError(clientCertificate);
        }

        return ret;
    }


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

        ss << indent << " - certificateTrustListLocation";
        ss << fillToPos(ss, colon);
        ss << ": " << certificateTrustListLocation << "\n";

        ss << indent << " - certificateRevocationListLocation";
        ss << fillToPos(ss, colon);
        ss << ": " << certificateRevocationListLocation << "\n";

        ss << indent << " - issuersCertificatesLocation";
        ss << fillToPos(ss, colon);
        ss << ": " << issuersCertificatesLocation << "\n";

        ss << indent << " - issuersRevocationListLocation";
        ss << fillToPos(ss, colon);
        ss << ": " << issuersRevocationListLocation << "\n";

        ss << indent << " - createSecurityLocationsIfNeeded";
        ss << fillToPos(ss, colon);
        ss << ": " << (createSecurityLocationsIfNeeded ? "true" : "false") << "\n";

        ss << indent << " - clientPrivateKey";
        ss << fillToPos(ss, colon);
        ss << ": " << clientPrivateKey << "\n";

        ss << indent << " - clientCertificate";
        ss << fillToPos(ss, colon);
        ss << ": " << clientCertificate << "\n";

        ss << indent << " - defaultSessionSettings\n";
        ss << defaultSessionSettings.toString(indent + "   ", colon) << "\n";

        ss << indent << " - specificSessionSettings[]";
        if (specificSessionSettings.size() > 0)
        {
            for (std::map<std::string, uaf::SessionSettings>::const_iterator it = specificSessionSettings.begin();
                    it != specificSessionSettings.end();
                    ++it)
            {
                ss << indent << "   " << " - specificSessionSettings['" << it->first << "']\n";
                ss << it->second.toString(indent + "      ", colon);
                if (std::distance(it, specificSessionSettings.end()) > 1)
                    ss << "\n";
            }
        }

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
               && object1.certificateTrustListLocation == object2.certificateTrustListLocation
               && object1.certificateRevocationListLocation == object2.certificateRevocationListLocation
               && object1.issuersCertificatesLocation == object2.issuersCertificatesLocation
               && object1.issuersRevocationListLocation == object2.issuersRevocationListLocation
               && object1.createSecurityLocationsIfNeeded == object2.createSecurityLocationsIfNeeded
               && object1.clientPrivateKey == object2.clientPrivateKey
               && object1.clientCertificate == object2.clientCertificate;
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
        else if (object1.certificateTrustListLocation != object2.certificateTrustListLocation)
            return object1.certificateTrustListLocation < object2.certificateTrustListLocation;
        else if (object1.certificateRevocationListLocation != object2.certificateRevocationListLocation)
            return object1.certificateRevocationListLocation < object2.certificateRevocationListLocation;
        else if (object1.issuersCertificatesLocation != object2.issuersCertificatesLocation)
            return object1.issuersCertificatesLocation < object2.issuersCertificatesLocation;
        else if (object1.issuersRevocationListLocation != object2.issuersRevocationListLocation)
            return object1.issuersRevocationListLocation < object2.issuersRevocationListLocation;
        else if (object1.createSecurityLocationsIfNeeded != object2.createSecurityLocationsIfNeeded)
            return object1.createSecurityLocationsIfNeeded < object2.createSecurityLocationsIfNeeded;
        else if (object1.clientPrivateKey != object2.clientPrivateKey)
            return object1.clientPrivateKey < object2.clientPrivateKey;
        else
            return object1.clientCertificate < object2.clientCertificate;
    }

}

