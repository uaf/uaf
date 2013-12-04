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

#ifndef UAFC_RESOLVER_H_
#define UAFC_RESOLVER_H_


// STD
#include <vector>
#include <string>
#include <map>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/logger.h"
#include "uaf/util/status.h"
#include "uaf/util/address.h"
#include "uaf/util/mask.h"
#include "uaf/util/constants.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/sessions/sessionfactory.h"
#include "uaf/client/database/database.h"
#include "uaf/client/requests/requests.h"


namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::Resolver can resolve addresses (of type uafc::Address).
    *
    * The uafc::Resolver uses the TranslateBrowsePathsToNodeIds service to resolve the relative
    * addresses, and uses the uafc::AddressCache to cache the resolution results.
    *
    * @ingroup ClientResolution
    ***********************************************************************************************/
    class UAFC_EXPORT Resolver
    {
    public:


        /**
         * Construct a resolver based on an existing logger factory, session factory and database.
         *
         * @param loggerFactory     Logger factory to log all messages to.
         * @param sessionFactory    Session factory to create all sessions.
         * @param database          Shared database to cache resolved addresses.
         */
        Resolver(
                uaf::LoggerFactory*     loggerFactory,
                uafc::SessionFactory*   sessionFactory,
                uafc::Database*         database);


        /**
         * Destruct the resolver.
         */
        virtual ~Resolver();


        /**
         * Resolve an address.
         *
         * @param addresses         Addresses to resolve.
         * @param expandedNodeIds   Results of the resolution.
         * @param statuses          Statuses of the results of the resolution.
         * @return                  Good if the resolution went find, bad otherwise.
         */
        uaf::Status resolve(
                const std::vector<uaf::Address>&    addresses,
                std::vector<uaf::ExpandedNodeId>&   expandedNodeIds,
                std::vector<uaf::Status>&           statuses);


        /**
         * Resolve the masked targets of the given request.
         *
         * This function is a template member function, so all types of requests can be resolved
         * in the same generic way.
         *
         * @param request   Request of which the masked targets should be resolved.
         * @param mask      The mask indicating (by mask[targetNumber] == true) which targets
         *                  should be resolved.
         * @param result    Result of which the masked targets will be updated.
         * @return          Status, indicating errors on the client side (e.g. invalid formed
         *                  addresses).
         */
        template<typename _Service>
        uaf::Status resolve(
                typename _Service::Request& request,
                const uaf::Mask&            mask,
                typename _Service::Result&  result)
        {
            logger_->info("Resolving the request (%d targets, of which %d are masked)",
                          request.targets.size(), mask.setCount());

            // declare the return status
            uaf::Status ret;

            // verify if the input parameters make sense
            if (request.targets.size() == mask.size())
                ret.setGood();
            else
                ret.setStatus(uaf::statuscodes::UnexpectedError,
                              "Mask does not match request size");

            // resize the result
            result.targets.resize(request.targets.size());

            // get the resolvable items of all 'set' targets as one (big) list
            // This step is necessary because each target can have multiple resolvable items
            // (e.g. a method call target has 3).
            std::vector<uaf::Address> items;
            if (ret.isGood())
            {
                items = getResolvableItems<_Service>(request, mask);
                logger_->debug("%d resolvable items were extracted from the request",
                               items.size());
            }

            // resolve all resolvable items at once
            std::vector<uaf::ExpandedNodeId> itemExpandedNodeIds;
            std::vector<uaf::Status>         itemStatuses;
            if (ret.isGood())
                ret = resolve(items, itemExpandedNodeIds, itemStatuses);

            // update all 'set' targets
            if (ret.isGood())
            {
                logger_->debug("Now updating the masked targets");
                ret = setResolvedItems<_Service>(
                        itemExpandedNodeIds,
                        itemStatuses,
                        request,
                        mask,
                        result);
            }

            // log the result
            if (ret.isGood())
            {
                logger_->info("Resolution is finished");
            }
            else
            {
                ret.addDiagnostic("The request could not be resolved");
                logger_->error(ret);
            }

            return ret;
        }


    private:


        // no copying or assigning allowed
        DISALLOW_COPY_AND_ASSIGN(Resolver);


        /**
         * Resolve an address by only checking the cache.
         *
         * @param address                   Address to resolve.
         * @param resolvedExpandedNodeId    Result of the resolution.
         * @return                          Good if the resolution went find, bad otherwise.
         */
        uaf::Status resolveCached(
                const std::vector<uaf::Address>&    addresses,
                std::vector<uaf::ExpandedNodeId>&   expandedNodeIds,
                std::vector<uaf::Status>&           statuses,
                uaf::Mask&                          expandedNodeIdMask,
                uaf::Mask&                          relativePathMask);


        /**
         * Verify if the ExpandedNodeIds in a vector of Addresses can be resolved.
         *
         * In order to be resolvable, these ExpandedNodeIds must have a server URI.
         *
         * @param addresses         The addresses, which must be checked if indicated by the mask.
         * @param mask              The mask indicating the addresses that must be checked.
         * @param results           In-out parameter: the ExpandedNodeIds from the 'addresses'
         *                          parameter will be copied to this parameter if valid and if
         *                          indicated by the mask.
         * @param resultStatuses    In-out parameter: the Statuses indicated by the mask will be
         *                          updated to Good if the verification was OK, or Bad if not.
         * @return                  Good if all indicated addresses were valid, Bad if there were
         *                          one or more invalid ones.
         */
        uaf::Status verifyExpandedNodeIds(
                const std::vector<uaf::Address>&    addresses,
                const uaf::Mask&                    mask,
                std::vector<uaf::ExpandedNodeId>&   results,
                std::vector<uaf::Status>&           resultStatuses);


        /**
         * Resolve the starting addresses of some relative paths.
         *
         * @param relativePathAddresses The addresses that contain relative paths.
         * @param mask                  The mask indicating those addresses that are relative paths.
         *                              The mask will be updated: those addresses that are relative
         *                              paths but that cannot be processed further since the
         *                              starting address could not be resolved, will be 'unset'
         *                              (made false) in the mask.
         * @param results           Output parameter: the resulting BrowsePaths (this vector will
         *                          be resized to the same size as the 'relativePathAddresses'
         *                          parameter.
         * @param statuses          Output parameter: the resulting statuses (this vector will
         *                          be resized to the same size as the 'relativePathAddresses'
         *                          parameter.
         * @return                  Good if there were no errors on the client side (e.g. malformed
         *                          addresses), Bad otherwise.
         */
        uaf::Status resolveRelativePathsStartingAddresses(
                const std::vector<uaf::Address>&    relativePathAddresses,
                uaf::Mask&                          mask,
                std::vector<uaf::BrowsePath>&       results,
                std::vector<uaf::Status>&           statuses);


        /**
         * Resolve relative paths.
         *
         * @param addresses The addresses of which the mask indicates the relative paths.
         * @param mask      The mask that indicates which addresses are relative paths.
         * @param results   In-out parameter: the resulting ExpandedNodeIds.
         * @param statuses  In-out parameter: the resulting statuses.
         * @return          Good if there were no errors on the client side (e.g. malformed
         *                  addresses), Bad otherwise.
         */
        uaf::Status resolveRelativePaths(
                const std::vector<uaf::Address>&    addresses,
                const uaf::Mask&                    mask,
                std::vector<uaf::ExpandedNodeId>&   results,
                std::vector<uaf::Status>&           statuses);


        /**
         * Resolve BrowsePaths.
         *
         * @param browsePaths   The browse paths of which those indicated by the mask, will
         *                      be resolved.
         * @param mask          The mask that indicates the browse paths that will be resolved.
         * @param results       The resulting ExpandedNodeIds.
         * @param statuses      The resulting resolution statuses.
         * @return              Good if there were no errors on the client side (e.g. malformed
         *                      addresses), Bad otherwise.
         */
        uaf::Status resolveBrowsePaths(
                std::vector<uaf::BrowsePath>&       browsePaths,
                uaf::Mask&                          mask,
                std::vector<uaf::ExpandedNodeId>&   results,
                std::vector<uaf::Status>&           statuses);


        /**
         * Process the result of a browse path translation result, to see if the resolution was
         * OK, or whether the translation was not completed and additional translations are needed.
         *
         * @param target        The target to process.
         * @param rank          The order number of the browse path that is being resolved.
         * @param browsePaths   The browse paths that are being resolved.
         * @param mask          The mask indicating the browsepaths that still need to be resolved.
         *                      This mask will be updated: if browse paths are fully resolved,
         *                      the corresponding mask item will be 'unset' (False).
         * @param results       The resulting ExpandedNodeIds.
         * @param statuses      The resulting resolution statuses.
         * @return              Good if there were no errors on the client side (e.g. malformed
         *                      addresses), Bad otherwise.
         */
        void processBrowsePathsResolutionResultTarget(
                const uafc::TranslateBrowsePathsToNodeIdsResultTarget& target,
                std::size_t                                            rank,
                std::vector<uaf::BrowsePath>&                          browsePaths,
                uaf::Mask&                                             mask,
                std::vector<uaf::ExpandedNodeId>&                      results,
                std::vector<uaf::Status>&                              statuses);


        /**
         * Get the resolvable items from the indicated targets of a request.
         *
         * @param request   The request from which the resolvable items will be extracted.
         * @param mask      The mask indicating which targets of the request to consider.
         * @return          A vector containing all extracted resolvable items. So if a request
         *                  has 5 targets of which 3 are indicated by the mask, and each target
         *                  contains 2 resolvable items, then the resulting vector will contain
         *                  6 addresses.
         */
        template<typename _Service>
        std::vector<uaf::Address> getResolvableItems(
                const typename _Service::Request& request,
                const uaf::Mask& mask) const
        {
            std::vector<uaf::Address> ret;
            for (std::size_t i = 0; i < request.targets.size(); i++)
            {
                if (mask.isSet(i))
                {
                    std::vector<uaf::Address> resolvableItems(
                            request.targets[i].getResolvableItems());
                    ret.insert(ret.end(), resolvableItems.begin(), resolvableItems.end());
                }
            }
            return ret;
        }


        /**
         * Copy the resolved addresses to the request, and the resolution statuses to the
         * corresponding result.
         *
         * @param expandedNodeIds   The ExpandedNodeIds that resulted from the resolution.
         * @param statuses          The statuses that resulted from the resolution.
         * @param request           The request of which the targets should be updated with the
         *                          resolved addresses (i.e. the given ExpandedNodeIds).
         * @param mask              The mask indicating the targets of the request and result that
         *                          we have been resolving.
         * @param result            The result of which the targets should be updated with the
         *                          resolution statuses.
         */
        template<typename _Service>
        uaf::Status setResolvedItems(
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                const std::vector<uaf::Status>&         statuses,
                typename _Service::Request&             request,
                const uaf::Mask&                        mask,
                typename _Service::Result&              result)
        {
            uaf::Status ret;

            // do a couple of checks on the input
            if (   expandedNodeIds.size() != statuses.size()
                || mask.size() != request.targets.size())
                ret.setStatus(uaf::statuscodes::UnexpectedError,
                              "Bug: input arguments do not match");
            else
                ret.setGood();


            if (ret.isGood())
            {
                for (std::size_t i = 0, j = 0; i < request.targets.size() && ret.isGood(); i++)
                {
                    if (mask.isSet(i))
                    {
                        // get the number of items of the current target
                        std::size_t noOfItems = request.targets[i].resolvableItemsCount();

                        if (noOfItems > 0)
                        {
                            // create ExpandedNodeId and Status vectors for the current target
                            std::vector<uaf::ExpandedNodeId> targetExpandedNodeIds(
                                    expandedNodeIds.begin() + j     * noOfItems,
                                    expandedNodeIds.begin() + (j+1) * noOfItems);
                            std::vector<uaf::Status> targetStatuses(
                                    statuses.begin() + j     * noOfItems,
                                    statuses.begin() + (j+1) * noOfItems);

                            // set the newly created vectors
                            ret = request.targets[i].setResolvedItems(
                                    targetExpandedNodeIds,
                                    targetStatuses);

                            // in case of just one item per target, set the status of the first
                            // item as "resolution status"
                            if (noOfItems == 1)
                            {
                                result.targets[i].status = targetStatuses[0];
                            }
                            // in case of multiple items per target, make a summary
                            else
                            {
                                std::stringstream unresolvedStringStream;
                                for (std::size_t k = 0; k < targetStatuses.size(); k++)
                                {
                                    if (targetStatuses[k].isNotGood())
                                    {
                                        if (unresolvedStringStream.str().size() == 0)
                                            unresolvedStringStream << k;
                                        else
                                            unresolvedStringStream << ", " << k;
                                    }
                                }

                                if (unresolvedStringStream.str().size() == 0)
                                    result.targets[i].status.setGood();
                                else
                                    result.targets[i].status.setStatus(
                                            uaf::statuscodes::ResolutionError,
                                            "Resolvable items [%s] (of %d in total) could not be "
                                            "resolved",
                                            unresolvedStringStream.str().c_str(),
                                            noOfItems);
                            }
                        }

                        // go to the next 'set' item
                        j++;
                    }
                }

                ret.setGood();
            }

            return ret;
        }


        // logger of the resover
        uaf::Logger* logger_;
        // pointer to the session factory
        uafc::SessionFactory* sessionFactory_; // not owned!
        // pointer to the shared database
        uafc::Database* database_; // not owned!

    };

}


#endif /* UAFC_RESOLVER_H_ */
