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

#include "uaf/client/requests/createmonitoredeventsrequesttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;
    using uaf::monitoringmodes::MonitoringMode;




    // Constructor
    // =============================================================================================
    CreateMonitoredEventsRequestTarget::CreateMonitoredEventsRequestTarget()
    : monitoringMode(uaf::monitoringmodes::Reporting),
      samplingIntervalSec(0.0),
      queueSize(1),
      discardOldest(true)
    {}


    // Constructor
    // =============================================================================================
    CreateMonitoredEventsRequestTarget::CreateMonitoredEventsRequestTarget(const Address& address)
    : address(address),
      monitoringMode(uaf::monitoringmodes::Reporting),
      samplingIntervalSec(0.0),
      queueSize(1),
      discardOldest(true)
    {}


    // Constructor
    // =============================================================================================
    CreateMonitoredEventsRequestTarget::CreateMonitoredEventsRequestTarget(
            const Address&      address,
            const EventFilter&  eventFilter)
    : address(address),
      monitoringMode(uaf::monitoringmodes::Reporting),
      samplingIntervalSec(0.0),
      queueSize(1),
      discardOldest(true),
      eventFilter(eventFilter)
    {}


    // Constructor
    // =============================================================================================
    CreateMonitoredEventsRequestTarget::CreateMonitoredEventsRequestTarget(
            const Address&      address,
            MonitoringMode      monitoringMode,
            double              samplingIntervalSec,
            uint32_t            queueSize,
            bool                discardOldest,
            const EventFilter&  eventFilter)
    : address(address),
      monitoringMode(monitoringMode),
      samplingIntervalSec(samplingIntervalSec),
      queueSize(queueSize),
      discardOldest(discardOldest),
      eventFilter(eventFilter)
    {}


    // Get a string representation
    // =============================================================================================
    string CreateMonitoredEventsRequestTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << indent << " - address\n";
        ss << address.toString(indent + "   ", colon) << "\n";

        ss << indent << " - monitoringMode";
        ss << fillToPos(ss, colon);
        ss << ": " << monitoringMode << " (" << monitoringmodes::toString(monitoringMode)  << ")\n";

        ss << indent << " - samplingIntervalSec";
        ss << fillToPos(ss, colon);
        ss << ": " << samplingIntervalSec << "\n";

        ss << indent << " - queueSize";
        ss << fillToPos(ss, colon);
        ss << ": " << queueSize << "\n";

        ss << indent << " - discardOldest";
        ss << fillToPos(ss, colon);
        ss << ": " << (discardOldest ? "true" : "false") << "\n";

        ss << indent << " - eventFilter\n";
        ss << eventFilter.toString(indent + "   ", colon);

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const CreateMonitoredEventsRequestTarget& object1,
            const CreateMonitoredEventsRequestTarget& object2)
    {
        return    (object1.address == object2.address)
               && (object1.monitoringMode == object2.monitoringMode)
               && (int(object1.samplingIntervalSec*1000) == int(object2.samplingIntervalSec*1000))
               && (object1.queueSize == object2.queueSize)
               && (object1.discardOldest == object2.discardOldest)
               && (object1.eventFilter == object2.eventFilter);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const CreateMonitoredEventsRequestTarget& object1,
            const CreateMonitoredEventsRequestTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const CreateMonitoredEventsRequestTarget& object1,
            const CreateMonitoredEventsRequestTarget& object2)
    {
        if (object1.address != object2.address)
            return (object1.address < object2.address);

        if (object1.monitoringMode != object2.monitoringMode)
            return (object1.monitoringMode < object2.monitoringMode);

        if (int(object1.samplingIntervalSec*1000) != int(object2.samplingIntervalSec*1000))
            return (int(object1.samplingIntervalSec*1000) < int(object2.samplingIntervalSec*1000));

        if (object1.queueSize != object2.queueSize)
            return (object1.queueSize < object2.queueSize);

        if (object1.discardOldest != object2.discardOldest)
            return (object1.discardOldest < object2.discardOldest);

        if (object1.eventFilter != object2.eventFilter)
            return (object1.eventFilter < object2.eventFilter);

        // everything is equal
        return false;
    }





    // Get the resolvable items
    // =============================================================================================
    vector<Address> CreateMonitoredEventsRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(address);



        return ret;
    }


    // Set the resolved items
    // =============================================================================================
    Status CreateMonitoredEventsRequestTarget::setResolvedItems(
            const vector<ExpandedNodeId>& expandedNodeIds,
            const vector<Status>&         resolutionStatuses)
    {
        Status ret;

        if (   expandedNodeIds.size()    == resolvableItemsCount()
            && resolutionStatuses.size() == resolvableItemsCount())
        {
            if (resolutionStatuses[0].isGood())
                address = expandedNodeIds[0];

            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError, "Could not set the resolved items");
        }

        return ret;
    }


    // Get the server URI
    // =============================================================================================
    Status CreateMonitoredEventsRequestTarget::getServerUri(string& serverUri) const
    {
        return extractServerUri(address, serverUri);
    }





}
