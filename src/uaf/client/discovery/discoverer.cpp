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

#include "uaf/client/discovery/discoverer.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::map;
    using std::vector;


    // Constructor
    // =============================================================================================
    Discoverer::Discoverer(LoggerFactory* loggerFactory, Database* database)
    : database_(database),
      findServersBusy_(false)
    {
        logger_ = new Logger(loggerFactory, "Discoverer");
        logger_->info("The discoverer has been constructed");
    }


    // Destructor
    // =============================================================================================
    Discoverer::~Discoverer()
    {
        logger_->debug("Destructing the discoverer");

        delete logger_;
        logger_ = 0;
    }


    // Update the application descriptions
    // =============================================================================================
    ClientStatus Discoverer::findServers()
    {
        ClientStatus ret;

        logger_->debug("Finding all configured servers");

        // check if findServers() is already busy
        bool alreadyBusy;

        findServersBusyMutex_.lock();
        if (findServersBusy_)
        {
            alreadyBusy = true;
        }
        else
        {
            findServersBusy_ = true;
            alreadyBusy = false;
        }
        findServersBusyMutex_.unlock();

        if (alreadyBusy)
        {
            ret = NoParallelFindServersAllowedError();
            logger_->error(ret.toString());
        }
        else
        {
            if (database_->clientSettings.discoveryUrls.size() > 0)
            {
                // store the results in a temporary variable, and copy this temporary variable to the
                // serverDescriptions_ member when finished
                vector<ApplicationDescription> serverDescriptions;

                // set the call timeout
                UaClientSdk::ServiceSettings serviceSettings;
                serviceSettings.callTimeout = int32_t(
                        database_->clientSettings.discoveryFindServersTimeoutSec * 1000);

                UaClientSdk::ClientSecurityInfo clientSecurityInfo;

                // create a copy of the URLs
                vector<string> discoveryUrls = database_->clientSettings.discoveryUrls;

                // store the statuses and the number of failures
                size_t noOfErrors = 0;
                vector<SdkStatus> sdkStatuses;
                sdkStatuses.reserve(discoveryUrls.size());
                // loop through the URLs
                for (vector<string>::const_iterator iter = discoveryUrls.begin();
                     iter != discoveryUrls.end();
                     ++iter)
                {
                    string url(*iter);

                    logger_->debug("Finding the servers for URL '%s' (timeout %dms)",
                                   url.c_str(),
                                   serviceSettings.callTimeout);

                    // invoke the FindServers service for the current URL
                    UaApplicationDescriptions desc;
                    SdkStatus discoveryStatus = uaDiscovery_.findServers(
                            serviceSettings,
                            UaString(url.c_str()),
                            clientSecurityInfo, // ToDo replace
                            desc);

                    // store the status
                    sdkStatuses.push_back(discoveryStatus);

                    // if the service call went OK, process the result
                    if (discoveryStatus.isGood())
                    {
                        // loop through the results
                        for (uint32_t i=0; i<desc.length(); i++)
                        {
                            // create an UAF::ApplicationDescription from the SDK ApplicationDescription
                            ApplicationDescription applicationDescription(desc[i]);
                            serverDescriptions.push_back(applicationDescription);

                            logger_->debug("Found server at URL '%s':", url.c_str());
                            logger_->debug(applicationDescription.toString());
                        }
                    }
                    else
                    {
                        noOfErrors++;
                        logger_->error(discoveryStatus.toString());
                    }
                }

                if (noOfErrors > 0)
                {
                    ret = FindServersError(sdkStatuses, noOfErrors, discoveryUrls.size());
                    logger_->error(ret.toString());
                }
                else
                {
                    ret = ClientStatus::Good;
                    logger_->debug("The FindServers service was successfully invoked on all URLs");
                }

                // copy the temporary application descriptions to the class member
                serverDescriptions_ = serverDescriptions;
            }
            else
            {
                logger_->warning("Nothing to do: no discoveryUrls specified in the ClientConfig");

                // clear the server descriptions
                serverDescriptions_.clear();

                // all done
                ret = ClientStatus::Good;
            }

            // reset the findServersBusy_ flag
            findServersBusyMutex_.lock();
            findServersBusy_ = false;
            findServersBusyMutex_.unlock();
        }

        return ret;
    }


    // Get the discovery URL for a given server URI
    // =============================================================================================
    ClientStatus Discoverer::getDiscoveryUrls(const string& serverUri, vector<string>& discoveryUrls)
    {
        ClientStatus ret;

        std::vector<uaf::ApplicationDescription>::const_iterator it;
        for (it = serverDescriptions_.begin(); it != serverDescriptions_.end(); ++it)
        {
            if (it->applicationUri == serverUri)
            {
                discoveryUrls = it->discoveryUrls;
                ret = ClientStatus::Good;
            }
        }

        if (ret.isNotGood())
        {
            ret = UnknownServerError(serverUri);
        }
        else if (discoveryUrls.size() == 0)
        {
            ret = NoDiscoveryUrlsExposedByServerError(serverUri);
        }

        return ret;
    }


    // Get all servers found
    // =============================================================================================
    const vector<ApplicationDescription>& Discoverer::serversFound() const
    {
        return serverDescriptions_;
    }


    // Update the endpoint descriptions
    // =============================================================================================
    ClientStatus Discoverer::getEndpoints(
            const string&                   discoveryUrl,
            vector<EndpointDescription>&    endpointDescriptions)
    {
        logger_->debug("Getting the endpoints for '%s'", discoveryUrl.c_str());

        // create the Status to return
        ClientStatus ret;

        // check if we got a non-empty URL (shouldn't be happening, may be a bug)
        if (discoveryUrl.empty())
        {
            ret = EmptyUrlError();
            logger_->error(ret.toString().c_str());
        }
        else
        {
            // create the SDK variables
            UaEndpointDescriptions uaEndpointDescriptions;
            UaClientSdk::ServiceSettings serviceSettings;
            UaClientSdk::ClientSecurityInfo clientSecurityInfo; // ToDo replace

            // set the service timeout
            serviceSettings.callTimeout = int32_t(
                    database_->clientSettings.discoveryGetEndpointsTimeoutSec * 1000);

            logger_->debug("Now invoking the GetEndpoints service");

            // perform the service call
            SdkStatus sdkStatus = uaDiscovery_.getEndpoints(
                    serviceSettings,
                    UaString(discoveryUrl.c_str()),
                    clientSecurityInfo,
                    uaEndpointDescriptions);

            logger_->log(sdkStatus);

            if (sdkStatus.isNotGood())
                ret = GetEndpointsError(sdkStatus);

            if (ret.isGood())
            {
                if (uaEndpointDescriptions.length() > 0)
                {
                    logger_->debug("A total of %d endpoint(s) have been gotten successfully:",
                                   uaEndpointDescriptions.length());

                    // fill this temporary variable and log each endpoint description
                    for (uint32_t i = 0; i < uaEndpointDescriptions.length(); i++)
                    {
                        endpointDescriptions.push_back(
                                EndpointDescription(uaEndpointDescriptions[i]));
                        logger_->debug(" - endpoint[%d]", i);
                        logger_->debug(string("   ") + endpointDescriptions[i].toString("   "));
                    }
                }
                else
                {
                    ret = NoEndpointsProvidedByServerError();
                    logger_->error(ret.toString().c_str());
                }
            }
            else
            {
                logger_->error(ret.toString());
            }
        }

        return ret;
    }



}






