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

#ifndef UAF_CLIENTSETTINGS_H_
#define UAF_CLIENTSETTINGS_H_

// STD
#include <string>
#include <sstream>
#include <vector>
// SDK
#include "uabase/uadir.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/loglevels.h"
#include "uaf/util/status.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/readsettings.h"
#include "uaf/client/settings/writesettings.h"
#include "uaf/client/settings/methodcallsettings.h"
#include "uaf/client/settings/createmonitoreddatasettings.h"
#include "uaf/client/settings/createmonitoredeventssettings.h"
#include "uaf/client/settings/translatebrowsepathstonodeidssettings.h"
#include "uaf/client/settings/browsesettings.h"
#include "uaf/client/settings/browsenextsettings.h"
#include "uaf/client/settings/historyreadrawmodifiedsettings.h"
#include "uaf/client/settings/sessionsettings.h"
#include "uaf/client/settings/subscriptionsettings.h"


namespace uaf
{

    /*******************************************************************************************//**
    * An uaf::ClientSettings instance holds the settings of a uaf::Client instance.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAF_EXPORT ClientSettings
    {
    public:


        /**
         * Create a default ClientSettings instance.
         *
         * Default values are:
         *  - applicationName : ""
         *  - applicationUri : ""
         *  - productUri : ""
         *  - localeId : ""
         *  - discoveryFindServersTimeoutSec : 2.0
         *  - discoveryGetEndpointsTimeoutSec : 1.0
         *  - discoveryIntervalSec : 30.0
         *  - logToStdOutLevel : uaf::loglevels::Disabled
         *  - logToCallbackLevel : uaf::loglevels::Disabled
         *  - certificateTrustListLocation : "PKI/trusted/certs/"
         *  - certificateRevocationListLocation : "PKI/trusted/crl/"
         *  - issuersCertificatesLocation : "PKI/issuers/certs/"
         *  - issuersRevocationListLocation : "PKI/issuers/crl/"
         *  - createSecurityLocationsIfNeeded : true
         *  - clientPrivateKey : "PKI/client/private/client.pem"
         *  - clientCertificate : "PKI/client/certs/client.der"
         */
        ClientSettings();


        /**
         * Create a ClientSettings instance with default values except the name.
         */
        ClientSettings(const std::string& applicationName);


        /**
         * Create a ClientSettings instance with default values except the name and discoveryUrls.
         */
        ClientSettings(const std::string&               applicationName,
                       const std::vector<std::string>&  discoveryUrls);


        /////// Main ///////


        /** The application name of the client. */
        std::string applicationName;

        /** The unique application URI of the client. */
        std::string applicationUri;

        /** The unique product URI. */
        std::string productUri;

        /** The Locale identifier (e.g. "en", "de", "en-US", ...). */
        std::string localeId;


        /////// Logging ///////


        /** When logging to the stdout, only log messages from at least this loglevel. */
        uaf::loglevels::LogLevel logToStdOutLevel;

        /** When logging to the callback interface, only log messages from at least this loglevel.*/
        uaf::loglevels::LogLevel logToCallbackLevel;


        /////// Discovery ///////


        /** A list of the Servers and DiscoveryServers the client should be able to discover. */
        std::vector<std::string> discoveryUrls;

        /** The timeout value for the FindServers discovery service, in seconds. */
        float discoveryFindServersTimeoutSec;

        /** The timeout value for the GetEndpoints discovery service, in seconds. */
        float discoveryGetEndpointsTimeoutSec;

        /** The interval between discovery attempts which are continuously running in the
         *  background, in seconds. */
        float discoveryIntervalSec;


        /////// Security ///////

        /** The trust list location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/trusted/certs/". */
        std::string certificateTrustListLocation;

        /** The revocation list location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/trusted/crl/" */
        std::string certificateRevocationListLocation;

        /** The issuers certificates location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/issuers/certs/". */
        std::string issuersCertificatesLocation;

        /** The issuers revocation list location.
         *
         *  This directory can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/issuers/crl/". */
        std::string issuersRevocationListLocation;


        /** Automatically create the security-related directories if they don't exist yet.
         *
         *  The following directories will be created *if* the UAF needs to connect to a secured
         *  endpoint:
         *   - certificateTrustListLocation
         *   - certificateRevocationListLocation
         *   - issuersCertificatesLocation
         *   - issuersRevocationListLocation
         *
         *  Default: True
         */
        bool createSecurityLocationsIfNeeded;


        /** The private key of this client application.
         *
         *  This file can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/client/private/client.pem". */
        std::string clientPrivateKey;


        /** The certificate of this client application.
         *
         *  This file can be specified either as an absolute path, or as a path relative to
         *  the application path.
         *
         *  Default: "PKI/client/certs/client.der". */
        std::string clientCertificate;


        uaf::BrowseNextSettings                     defaultBrowseNextSettings;
        uaf::BrowseSettings                         defaultBrowseSettings;
        uaf::CreateMonitoredDataSettings            defaultCreateMonitoredDataSettings;
        uaf::CreateMonitoredEventsSettings          defaultCreateMonitoredEventsSettings;
        uaf::HistoryReadRawModifiedSettings         defaultHistoryReadRawModifiedSettings;
        uaf::ReadSettings                           defaultReadSettings;
        uaf::TranslateBrowsePathsToNodeIdsSettings  defaultTranslateBrowsePathsToNodeIdsSettings;
        uaf::WriteSettings                          defaultWriteSettings;

        /**
         * The default session settings.
         *
         * These settings will be used to create the sessions to servers that aren't specified in
         * the 'specificSessionSettings' map.
         */
        uaf::SessionSettings defaultSessionSettings;


        /**
         * The session settings for particular serverURIs.
         */
        std::map<std::string, uaf::SessionSettings> specificSessionSettings;

        /**
         * The default session settings.
         *
         * These settings will be used to create the sessions to servers that aren't specified in
         * the 'specificSessionSettings' map.
         */
        uaf::SubscriptionSettings defaultSubscriptionSettings;

        /**
         * Create the security locations (directories).
         *
         * These locations will be created (if they don't exist already):
         *   - certificateTrustListLocation
         *   - certificateRevocationListLocation
         *   - issuersCertificatesLocation
         *   - issuersRevocationListLocation
         *   - base path of clientPrivateKey
         *   - base path of clientCertificate
         *
         * @return: True if the locations were created (or if they existed already)
         */
        uaf::Status createSecurityLocations() const;


        /**
         * Get a nice string representation of the settings.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=50) const;


        // comparison operators
        friend UAF_EXPORT bool operator< (
                const ClientSettings& object1,
                const ClientSettings& object2);
        friend UAF_EXPORT bool operator==(
                const ClientSettings& object1,
                const ClientSettings& object2);
        friend UAF_EXPORT bool operator!=(
                const ClientSettings& object1,
                const ClientSettings& object2);

    };

    //must be in header file because the compiler needs to specialize it in different translation units:
    template<typename _ServiceSettings> _ServiceSettings    getDefaultServiceSettings                                               (const uaf::ClientSettings& clientSettings);

    //must be in header file to make sure the compiler doesn't make an implicit  specialization:
    template<> uaf::BrowseNextSettings                      getDefaultServiceSettings<uaf::BrowseNextSettings>                      (const uaf::ClientSettings& clientSettings);
    template<> uaf::BrowseSettings                          getDefaultServiceSettings<uaf::BrowseSettings>                          (const uaf::ClientSettings& clientSettings);
    template<> uaf::CreateMonitoredDataSettings             getDefaultServiceSettings<uaf::CreateMonitoredDataSettings>             (const uaf::ClientSettings& clientSettings);
    template<> uaf::CreateMonitoredEventsSettings           getDefaultServiceSettings<uaf::CreateMonitoredEventsSettings>           (const uaf::ClientSettings& clientSettings);
    template<> uaf::HistoryReadRawModifiedSettings          getDefaultServiceSettings<uaf::HistoryReadRawModifiedSettings>          (const uaf::ClientSettings& clientSettings);
    template<> uaf::ReadSettings                            getDefaultServiceSettings<uaf::ReadSettings>                            (const uaf::ClientSettings& clientSettings);
    template<> uaf::TranslateBrowsePathsToNodeIdsSettings   getDefaultServiceSettings<uaf::TranslateBrowsePathsToNodeIdsSettings>   (const uaf::ClientSettings& clientSettings);
    template<> uaf::WriteSettings                           getDefaultServiceSettings<uaf::WriteSettings>                           (const uaf::ClientSettings& clientSettings);


}





#endif /* UAF_CLIENTSETTINGS_H_ */
