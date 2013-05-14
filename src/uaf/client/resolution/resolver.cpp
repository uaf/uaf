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

#include "uaf/client/resolution/resolver.h"

namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::vector;
    using std::map;
    using std::size_t;


    // Constructor
    //==============================================================================================
    Resolver::Resolver(
            LoggerFactory*  loggerFactory,
            SessionFactory* sessionFactory,
            Database*       database)
    : sessionFactory_(sessionFactory),
      database_(database)
    {
        logger_ = new Logger(loggerFactory, "Resolver");
        logger_->debug("The resolver has been constructed");
    }

    // Destructor
    //==============================================================================================
    Resolver::~Resolver()
    {
        logger_->debug("Destructing the resolver");

        delete logger_;
        logger_ = 0;
    }



    Status Resolver::resolveCached(
            const vector<Address>&  addresses,
            vector<ExpandedNodeId>& expandedNodeIds,
            vector<Status>&         statuses,
            Mask&                   expandedNodeIdMask,
            Mask&                   relativePathMask)
    {
        logger_->debug("Resolving the addresses by querying the cache");

        // declare the return status
        Status ret(statuscodes::Good);

        // declare the number of addresses
        size_t noOfAddresses = addresses.size();

        // resize the masks
        expandedNodeIdMask.resize(noOfAddresses);
        relativePathMask.resize(noOfAddresses);

        // loop through the addresses
        for (size_t i=0; i<noOfAddresses; i++)
        {
            logger_->debug("Trying to find address %d in the cache", i);

            if (database_->addressCache.find(addresses[i], expandedNodeIds[i]))
            {
                statuses[i].setGood();
                logger_->debug("Address %d was already cached", i);
            }
            else
            {
                if (addresses[i].isExpandedNodeId())
                {
                    expandedNodeIdMask.set(i);
                    logger_->debug("Address %d is an ExpandedNodeId not found in the cache", i);
                }
                else if (addresses[i].isRelativePath())
                {
                    relativePathMask.set(i);
                    logger_->debug("Address %d is a RelativePath not found in the cache", i);
                }
                else
                {
                    ret.setStatus(statuscodes::InvalidRequestError,
                                  "Cannot resolve an empty address");
                    logger_->error("Address %d cannot be resolved since it's an empty address", i);
                    break;
                }
            }
        }

        return ret;
    }



    // Resolve some addresses
    //==============================================================================================
    Status Resolver::resolve(
            const vector<Address>&  addresses,
            vector<ExpandedNodeId>& expandedNodeIds,
            vector<Status>&         statuses)
    {
        // ToDo add session and security settings!

        // declare the status object to return
        Status ret;

        // declare the number of addresses
        size_t noOfAddresses = addresses.size();

        // log a nice message
        logger_->debug("Resolving the following addresses:");
        for (size_t i=0; i<noOfAddresses; i++)
        {
            logger_->debug(" - Address %d", i);
            logger_->debug(addresses[i].toString("   ", 28));
        }

        // prepare the output parameters by resizing them
        expandedNodeIds.resize(noOfAddresses);
        statuses.resize(noOfAddresses);

        // first use the cache to resolve the addresses, and to create masks for the remaining
        // addresses
        Mask expandedNodeIdMask;
        Mask relativePathMask;
        ret = resolveCached(addresses,
                            expandedNodeIds,
                            statuses,
                            expandedNodeIdMask,
                            relativePathMask);

        // log the current status
        if (expandedNodeIdMask.setCount() == 0 && relativePathMask.setCount() == 0)
        {
            logger_->debug("All addresses were cached, so the resolution is finished");
        }
        else
        {
            if (expandedNodeIdMask.setCount() != 0)
                ret = verifyExpandedNodeIds(addresses,
                                            expandedNodeIdMask,
                                            expandedNodeIds,
                                            statuses);

            if (ret.isGood() && relativePathMask.setCount() != 0)
                ret = resolveRelativePaths(addresses,
                                           relativePathMask,
                                           expandedNodeIds,
                                           statuses);
        }

        return ret;
    }



    Status Resolver::verifyExpandedNodeIds(
            const vector<Address>&  addresses,
            const Mask&             mask,
            vector<ExpandedNodeId>& results,
            vector<Status>&         resultStatuses)
    {
        logger_->debug("Now verifying %d ExpandedNodeIds", addresses.size());

        Status ret(statuscodes::Good);

        // verify the 'set' targets
        for (size_t i = 0; i < addresses.size() && ret.isGood(); i++)
        {
            if (mask.isSet(i))
            {
                // copy the ExpandedNodeId
                results[i] = addresses[i].getExpandedNodeId();

                // set the status
                if (results[i].hasServerUri())
                {
                    if (   results[i].nodeId().hasNameSpaceIndex() \
                        || results[i].nodeId().hasNameSpaceUri())
                    {
                        database_->addressCache.add(addresses[i], results[i]);
                        resultStatuses[i].setGood();
                    }
                    else
                    {
                        ret.setStatus(statuscodes::ResolutionError,
                                      "No namespace index or URI is given for address:\n%s",
                                      addresses[i].toString().c_str());
                    }
                }
                else
                {
                    ret.setStatus(statuscodes::ResolutionError,
                                  "No server URI is given for address:\n%s",
                                  addresses[i].toString().c_str());
                }
            }
        }

        return ret;
    }




    Status Resolver::resolveRelativePaths(
            const vector<Address>&  addresses,
            const Mask&             mask,
            vector<ExpandedNodeId>& results,
            vector<Status>&         statuses)
    {
        // declare the return status
        Status ret;

        // declare a vector of browse paths which we will try to translate into ExpandedNodeIds
        vector<BrowsePath> browsePaths;

        // declare a mask that will indicate which browse paths still need to be translated
        Mask remainingMask = mask;

        // first try to resolve the starting addresses (all at once!)
        // the 'remainingMask', 'browsePaths' and 'statuses' will be updated!
        ret = resolveRelativePathsStartingAddresses(
                addresses,
                remainingMask,
                browsePaths,
                statuses);

        // now try to resolve the relative paths (essentially browse paths since their starting
        // addresses have been resolved)
        if (ret.isGood())
            ret = resolveBrowsePaths(browsePaths, remainingMask, results, statuses);

        // add the resolved addresses to the cache
        for (size_t i = 0; i < addresses.size() && ret.isGood(); i++)
        {
            if (mask.isSet(i) && statuses[i].isGood())
            {
                database_->addressCache.add(addresses[i], results[i], true);
            }
        }

        return ret;
    }




    Status Resolver::resolveRelativePathsStartingAddresses(
            const vector<Address>&  relativePathAddresses,
            Mask&                   mask,
            vector<BrowsePath>&     results,
            vector<Status>&         statuses)
    {
        // declare the return status
        Status ret(statuscodes::Good);

        // declare the number of relative paths
        size_t noOfRelativePaths = relativePathAddresses.size();

        // resize the output parameters
        results.resize(noOfRelativePaths);
        statuses.resize(noOfRelativePaths);

        // fill a vector containing all starting addresses
        vector<Address> startingAddresses;
        for (size_t i = 0; i < noOfRelativePaths && ret.isGood(); i++)
        {
            if (mask.isSet(i))
                startingAddresses.push_back(*(relativePathAddresses[i].getStartingAddress()));
        }

        // resolve them (recursively!)
        vector<ExpandedNodeId>  startingAddressesResults;
        vector<Status>          startingAddressesStatuses;
        ret = resolve(startingAddresses, startingAddressesResults, startingAddressesStatuses);

        // update the results
        for (size_t i = 0, j = 0; i < noOfRelativePaths && ret.isGood(); i++)
        {
            if (mask.isSet(i))
            {
                // update the results
                results[i].startingExpandedNodeId = startingAddressesResults[j];
                results[i].relativePath           = relativePathAddresses[i].getRelativePath();

                // update the statuses
                statuses[i] = startingAddressesStatuses[j];

                // update the mask (only resolved starting addresses should be processed further!)
                if (statuses[i].isNotGood())
                    mask.unset(i);

                // increment the index of the startingAddressesResults
                j++;
            }
        }

        return ret;
    }



    // Resolve a relative path (which may span over multiple server address spaces!)
    //==============================================================================================
    Status Resolver::resolveBrowsePaths(
            vector<BrowsePath>&       browsePaths,
            Mask&                     mask,
            vector<ExpandedNodeId>&   results,
            vector<Status>&           statuses)
    {
        logger_->debug("Resolving %d browse paths", browsePaths.size());

        // declare the return status
        Status ret;

        // declare the number of browsePaths
        size_t noOfBrowsePaths = browsePaths.size();

        // resize the output arguments
        results.resize(noOfBrowsePaths);
        statuses.resize(noOfBrowsePaths);

        // check if the mask has the correct size
        if (mask.size() != noOfBrowsePaths)
        {
            ret.setStatus(statuscodes::UnexpectedError, "Mask does not have the correct size!");
        }
        else if (mask.setCount() == 0)
        {
            ret.setStatus(statuscodes::UnexpectedError,
                          "Mask does not mark any browse path to be translated!");
        }
        else
        {
            // create a request and a result
            TranslateBrowsePathsToNodeIdsRequest request;
            TranslateBrowsePathsToNodeIdsResult  result;

            for (size_t i = 0; i < noOfBrowsePaths; i++)
            {
                if (mask.isSet(i))
                    request.targets.push_back(
                            TranslateBrowsePathsToNodeIdsRequestTarget(browsePaths[i]));
            }

            ret = sessionFactory_->invokeRequest<TranslateBrowsePathsToNodeIdsService>(
                    request,
                    Mask(request.targets.size(), true),
                    result);

            if (ret.isGood())
            {
                // fill the remainingBrowsePaths and remainingMask
                for (size_t i = 0, j = 0; i < noOfBrowsePaths; i++)
                {
                    if (mask.isSet(i))
                    {
                        processBrowsePathsResolutionResultTarget(
                                result.targets[j], i, browsePaths, mask, results, statuses);

                        // increment the counter for the 'set' results
                        j++;
                    }
                }

                // check if we need to perform another (recursive!) translation
                if (mask.setCount() > 0)
                    ret = resolveBrowsePaths(browsePaths, mask, results, statuses);
            }
        }

        return ret;
    }



    void Resolver::processBrowsePathsResolutionResultTarget(
            const TranslateBrowsePathsToNodeIdsResultTarget&    target,
            size_t                                              rank,
            vector<BrowsePath>&                                 browsePaths,
            Mask&                                               mask,
            vector<ExpandedNodeId>&                             results,
            vector<Status>&                                     statuses)
    {
        // check the target status
        if (target.status.isBad())
        {
            logger_->error("Target %d could not be resolved: %s",
                           rank, target.status.toString().c_str());
            statuses[rank] = target.status;
            // we're finished with this target (unfortunately, because it failed),
            // so unset the mask item
            mask.unset(rank);
        }
        else
        {
            // check if only one ExpandedNodeId was found
            // (if not, we cannot "resolve" the target)
            if (target.expandedNodeIds.size() == 0)
            {
                // no matches, which would be unexpected since the status reported
                // by the server was not Bad
                statuses[rank].setStatus(statuscodes::UnexpectedError,
                                         "Server reported a Good translation result but no"
                                         "results were given");

                logger_->error(statuses[rank]);

                // we're finished with this target, so unset the mask item
                mask.unset(rank);
            }
            else if (target.expandedNodeIds.size() == 1)
            {
                // one match was found for the browse path, just as we expected!

                // we still need to check if the browse path was fully resolved:
                if (target.status.isGood())
                {
                    // update the result and status
                    results[rank]  = target.expandedNodeIds[0];
                    statuses[rank] = statuses[0];

                    logger_->debug("Target %d was successfully resolved to:", rank);
                    logger_->debug(results[rank].toString());

                    // we're finished with this target, so unset the mask item
                    mask.unset(rank);
                }
                else if (target.status.opcUaStatusCode() == OpcUa_UncertainReferenceOutOfServer)
                {
                    logger_->debug("Target %d could not be fully resolved, there is an "
                                   "out-of-server reference", rank);

                    // declare the remaining path index
                    uint32_t remainingIndex = target.remainingPathIndexes[0];
                    uint32_t noOfElements   = browsePaths[rank].relativePath.size();
                    uint32_t maxIndex       = noOfElements - 1;

                    logger_->debug("Remaining index: %d (max index: %d)", remainingIndex, maxIndex);

                    if (remainingIndex == 0 || remainingIndex >= maxIndex)
                    {
                        statuses[rank].setStatus(
                                statuscodes::UnexpectedError,
                                "Unexpected translation result returned by the server (StatusCode="
                                "UncertainReferenceOutOfServer, RemainingPathIndex=%d), while "
                                "the number of BrowsePath elements is %d",
                                remainingIndex, noOfElements);

                        logger_->error(statuses[rank]);

                        // we're finished with this target, so unset the mask item
                        mask.unset(rank);
                    }
                    else
                    {
                        // copy the remaining elements to a new vector
                        vector<RelativePathElement> newElements;
                        for (uint32_t i = remainingIndex; i < maxIndex; i++)
                            newElements.push_back(browsePaths[rank].relativePath[i]);

                        // set the new browse path based on the just created elements
                        browsePaths[rank] = BrowsePath(target.expandedNodeIds[0], newElements);

                        logger_->debug("New browse path: %s", browsePaths[rank].toString().c_str());

                        // we're not finished with this target, so leave the mask item 'set'
                    }
                }
                else
                {
                    statuses[rank].setStatus(
                            statuscodes::UnexpectedError,
                            "Unexpected translation result (status reported by server: %s)",
                            target.status.toString().c_str());

                    logger_->error(statuses[rank]);

                    // we're finished with this target, so unset the mask item
                    mask.unset(rank);
                }
            }
            else
            {
                // we received multiple matches for a single browse path!
                // This may be a valid result for a TranslateBrowsePathsToNodeIds service
                // invocation, but not in this case since we're trying to resolve an address.
                statuses[rank].setStatus(statuscodes::ResolutionError,
                                         "Resolution failed because of ambiguity: %d addresses "
                                         "matched the same BrowsePath",
                                         target.expandedNodeIds.size());

                logger_->error(statuses[rank]);

                // we're finished with this target, so unset the mask item
                mask.unset(rank);
            }
        }
    }



}


