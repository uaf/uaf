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

#ifndef UAFC_CREATEMONITOREDDATAREQUESTTARGET_H_
#define UAFC_CREATEMONITOREDDATAREQUESTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/address.h"
#include "uaf/util/monitoringmodes.h"
#include "uaf/util/attributeids.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesubscriptionrequesttarget.h"
#include "uaf/client/settings/monitoreditemsettings.h"



namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::CreateMonitoredDataRequestTarget is the part of a uafc::CreateMonitoredDataRequest
    * that specifies the target to monitor.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT CreateMonitoredDataRequestTarget : public uafc::BaseSubscriptionRequestTarget
    {
    public:

        /**
         * Construct an empty target.
         */
        CreateMonitoredDataRequestTarget();


        /**
         * Construct a target for a given address.
         *
         * @param address  Address of the node of which the attribute should be monitored.
         */
        CreateMonitoredDataRequestTarget(const uaf::Address& address);


        /**
         * Construct a target with specified settings.
         *
         * @param address               Address of the node of which the attribute should be
         *                              monitored.
         * @param attributeId           Attribute id to be monitored.
         * @param monitoringMode        The initial monitoring mode.
         * @param samplingIntervalSec   The sampling interval in seconds.
         * @param queueSize             The size of the queue on the server.
         * @param discardOldest         True to discard the oldest values in the queue.
         * @param dataChangeFilter      The data change filter.
         */
        CreateMonitoredDataRequestTarget(
                const uaf::Address&                     address,
                uaf::attributeids::AttributeId          attributeId,
                uaf::monitoringmodes::MonitoringMode    monitoringMode,
                double                                  samplingIntervalSec,
                uint32_t                                queueSize,
                bool                                    discardOldest,
                const uaf::DataChangeFilter&            dataChangeFilter);


        /**
         * Virtual destructor.
         */
        virtual ~CreateMonitoredDataRequestTarget() {}


        /** The address of the node of which the attribute should be monitored. */
        uaf::Address address;

        /** Attribute id to be monitored. */
        uaf::attributeids::AttributeId attributeId;

        /** Index range to be monitored. */
        std::string indexRange;

        /** The monitoring mode. */
        uaf::monitoringmodes::MonitoringMode monitoringMode;

        /** The sampling interval of the monitored item, in seconds. */
        double samplingIntervalSec;

        /** The queue size on the server side. */
        uint32_t queueSize;

        /** True to discard the oldest item in the queue. */
        bool discardOldest;

        /** The data change filter. */
        uaf::DataChangeFilter dataChangeFilter;


        /**
         * Get a string representation of the settings.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=23) const;


        // comparison operators
        friend bool UAFC_EXPORT operator==(
                const CreateMonitoredDataRequestTarget& object1,
                const CreateMonitoredDataRequestTarget& object2);
        friend bool UAFC_EXPORT operator!=(
                const CreateMonitoredDataRequestTarget& object1,
                const CreateMonitoredDataRequestTarget& object2);
        friend bool UAFC_EXPORT operator<(
                const CreateMonitoredDataRequestTarget& object1,
                const CreateMonitoredDataRequestTarget& object2);

        /**
         * Get the server URI to which the service should be invoked for this target.
         *
         * @param serverUri The server URI as an output parameter.
         * @return          A good status if a server URI could be synthesized, a bad one if not.
         */
        uaf::Status getServerUri(std::string& serverUri) const;

    private:

        // the Resolver can see all private members
        friend class Resolver;


        /**
         * Get the resolvable items from the target as a "flat" list of addresses.
         */
        std::vector<uaf::Address> getResolvableItems() const;


        /**
         * Get the number of resolvable items of this kind of target.
         */
        std::size_t resolvableItemsCount() const { return 1; }


        /**
         * Set the resolved items as a "flat" list of ExpandedNodeIds and Statuses.
         */
        uaf::Status setResolvedItems(
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                const std::vector<uaf::Status>&         resolutionStatuses);

    };

}


#endif /* UAFC_CREATEMONITOREDDATAREQUESTTARGET_H_ */
