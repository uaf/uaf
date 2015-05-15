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

#ifndef UAF_CREATEMONITOREDEVENTSREQUESTTARGET_H_
#define UAF_CREATEMONITOREDEVENTSREQUESTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/address.h"
#include "uaf/util/monitoringmodes.h"
#include "uaf/util/attributeids.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesubscriptionrequesttarget.h"
#include "uaf/client/settings/monitoreditemsettings.h"



namespace uaf
{



    /*******************************************************************************************//**
    * A uaf::CreateMonitoredEventTarget is the part of a uaf::CreateMonitoredEventsRequest that
    * specifies the target to monitor.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAF_EXPORT CreateMonitoredEventsRequestTarget
    : public uaf::BaseSubscriptionRequestTarget
    {
    public:

        /**
         * Construct an empty target.
         */
        CreateMonitoredEventsRequestTarget();


        /**
         * Construct a target for a given address.
         *
         * @param address   Address of the node to be monitored.
         */
        CreateMonitoredEventsRequestTarget(const uaf::Address& address);


        /**
         * Construct a target for a given address and event filter.
         *
         * @param address       Address of the node to be monitored.
         * @param eventFilter   The filter.
         */
        CreateMonitoredEventsRequestTarget(
                const uaf::Address&     address,
                const uaf::EventFilter& eventFilter);


        /**
         * Construct a target with specified settings.
         *
         * @param address               Address of the node to be monitored.
         * @param monitoringMode        The initial monitoring mode.
         * @param samplingIntervalSec   The sampling interval in seconds.
         * @param queueSize             The size of the queue on the server.
         * @param discardOldest         True to discard the oldest values in the queue.
         * @param eventFilter           The filter.
         */
        CreateMonitoredEventsRequestTarget(
                const uaf::Address&                  address,
                uaf::monitoringmodes::MonitoringMode monitoringMode,
                double                               samplingIntervalSec,
                uint32_t                             queueSize,
                bool                                 discardOldest,
                const uaf::EventFilter&              eventFilter);


        /**
         * Virtual destructor.
         */
        virtual ~CreateMonitoredEventsRequestTarget() {}


        /** The address of the node to be monitored for events. */
        uaf::Address address;

        /** The sampling interval of the monitored item, in seconds. */
        uaf::monitoringmodes::MonitoringMode monitoringMode;

        /** The sampling interval of the monitored item, in seconds. */
        double samplingIntervalSec;

        /** The queue size on the server side (1 by default!). */
        uint32_t queueSize;

        /** True to discard the oldest item in the queue (true by default!). */
        bool discardOldest;

        /** The event filter. */
        uaf::EventFilter eventFilter;


        /**
         * Get a string representation of the settings.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=23) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(
                const CreateMonitoredEventsRequestTarget& object1,
                const CreateMonitoredEventsRequestTarget& object2);
        friend bool UAF_EXPORT operator!=(
                const CreateMonitoredEventsRequestTarget& object1,
                const CreateMonitoredEventsRequestTarget& object2);
        friend bool UAF_EXPORT operator<(
                const CreateMonitoredEventsRequestTarget& object1,
                const CreateMonitoredEventsRequestTarget& object2);
    private:

        // the Resolver can see all private members
        friend class Resolver;

        /**
         * Get the resolvable items from the target as a "flat" list of Addresses.
         */
        std::vector<uaf::Address> getResolvableItems() const;


        /**
         * Get the number of resolvable items of this kind of target.
         */
        std::size_t resolvableItemsCount() const { return 1; }


        /**
         * Set the resolved items as a "flat" list of ExpandedNodeIds and statuses.
         */
        uaf::Status setResolvedItems(
                const std::vector<uaf::ExpandedNodeId>& expandedNodeIds,
                const std::vector<uaf::Status>&         resolutionStatuses);


        /**
         * Get the server URI to which the service should be invoked for this target.
         *
         * @param serverUri The server URI as an output parameter.
         * @return          A good status if a server URI could be synthesized, a bad one if not.
         */
        uaf::Status getServerUri(std::string& serverUri) const;
    };


}


#endif /* UAF_CREATEMONITOREDEVENTSREQUESTTARGET_H_ */
