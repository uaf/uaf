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

#include "uaf/client/requests/createmonitoreddatarequesttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::size_t;
    using std::vector;
    using uaf::attributeids::AttributeId;
    using uaf::monitoringmodes::MonitoringMode;



    // Constructor
    // =============================================================================================
    CreateMonitoredDataRequestTarget::CreateMonitoredDataRequestTarget()
    : attributeId(uaf::attributeids::Value),
      monitoringMode(uaf::monitoringmodes::Reporting),
      samplingIntervalSec(0.0),
      queueSize(0),
      discardOldest(false)
    {}


    // Constructor
    // =============================================================================================
    CreateMonitoredDataRequestTarget::CreateMonitoredDataRequestTarget(const Address& address)
    : address(address),
      attributeId(uaf::attributeids::Value),
      monitoringMode(uaf::monitoringmodes::Reporting),
      samplingIntervalSec(0.0),
      queueSize(0),
      discardOldest(false)
    {}


    // Constructor
    // =============================================================================================
    CreateMonitoredDataRequestTarget::CreateMonitoredDataRequestTarget(
            const uaf::Address&                     address,
            uaf::attributeids::AttributeId          attributeId,
            uaf::monitoringmodes::MonitoringMode    monitoringMode,
            double                                  samplingIntervalSec,
            uint32_t                                queueSize,
            bool                                    discardOldest,
            const uaf::DataChangeFilter&            dataChangeFilter)
    : address(address),
      attributeId(attributeId),
      monitoringMode(monitoringMode),
      samplingIntervalSec(samplingIntervalSec),
      queueSize(queueSize),
      discardOldest(discardOldest),
      dataChangeFilter(dataChangeFilter)
    {}


    // Get a string representation
    // =============================================================================================
    string CreateMonitoredDataRequestTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << indent << " - address\n";
        ss << address.toString(indent + "   ", colon) << "\n";

        ss << indent << " - attributeId";
        ss << fillToPos(ss, colon);
        ss << ": " << attributeId << " (" << attributeids::toString(attributeId) << ")\n";

        ss << indent << " - indexRange";
        ss << fillToPos(ss, colon);
        ss << ": '" << indexRange << "'\n";

        ss << indent << " - monitoringMode";
        ss << fillToPos(ss, colon);
        ss << ": " << monitoringMode << " (" << monitoringmodes::toString(monitoringMode) << ")\n";

        ss << indent << " - samplingIntervalSec";
        ss << fillToPos(ss, colon);
        ss << ": " << samplingIntervalSec << "\n";

        ss << indent << " - queueSize";
        ss << fillToPos(ss, colon);
        ss << ": " << queueSize << "\n";

        ss << indent << " - discardOldest";
        ss << fillToPos(ss, colon);
        ss << ": " << (discardOldest ? "true" : "false") << "\n";

        ss << indent << " - dataChangeFilter\n";
        ss << dataChangeFilter.toString(indent + "   ", colon);

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const CreateMonitoredDataRequestTarget& object1,
            const CreateMonitoredDataRequestTarget& object2)
    {
        return    (object1.address == object2.address)
               && (object1.attributeId == object2.attributeId)
               && (object1.indexRange == object2.indexRange)
               && (object1.monitoringMode == object2.monitoringMode)
               && (int(object1.samplingIntervalSec*1000) == int(object2.samplingIntervalSec*1000))
               && (object1.queueSize == object2.queueSize)
               && (object1.discardOldest == object2.discardOldest)
               && (object1.dataChangeFilter == object2.dataChangeFilter);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const CreateMonitoredDataRequestTarget& object1,
            const CreateMonitoredDataRequestTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const CreateMonitoredDataRequestTarget& object1,
            const CreateMonitoredDataRequestTarget& object2)
    {
        if (object1.address != object2.address)
            return (object1.address < object2.address);

        if (object1.attributeId != object2.attributeId)
            return (object1.attributeId < object2.attributeId);

        if (object1.indexRange != object2.indexRange)
            return (object1.indexRange < object2.indexRange);

        if (object1.monitoringMode != object2.monitoringMode)
            return (object1.monitoringMode < object2.monitoringMode);

        if (int(object1.samplingIntervalSec*1000) != int(object2.samplingIntervalSec*1000))
            return (int(object1.samplingIntervalSec*1000) < int(object2.samplingIntervalSec*1000));

        if (object1.queueSize != object2.queueSize)
            return (object1.queueSize < object2.queueSize);

        if (object1.discardOldest != object2.discardOldest)
            return (object1.discardOldest < object2.discardOldest);

        if (object1.dataChangeFilter != object2.dataChangeFilter)
            return (object1.dataChangeFilter < object2.dataChangeFilter);

        // everything is equal
        return false;
    }





    // Get the resolvable items
    // =============================================================================================
    vector<Address> CreateMonitoredDataRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(address);
        return ret;
    }


    // Set the resolved items
    // =============================================================================================
    Status CreateMonitoredDataRequestTarget::setResolvedItems(
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
    Status CreateMonitoredDataRequestTarget::getServerUri(string& serverUri) const
    {
        return extractServerUri(address, serverUri);
    }


}
