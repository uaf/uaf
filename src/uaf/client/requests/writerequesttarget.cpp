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

#include "uaf/client/requests/writerequesttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;
    using uaf::attributeids::AttributeId;



    // Constructor
    // =============================================================================================
    WriteRequestTarget::WriteRequestTarget()
    : attributeId(attributeids::Value),
      opcUaStatusCode(OpcUa_Good)
    {}


    // Constructor
    // =============================================================================================
    WriteRequestTarget::WriteRequestTarget(
            const Address&                  address,
            const Variant&                  data,
            uaf::attributeids::AttributeId  attributeId)
    : address(address),
      data(data),
      opcUaStatusCode(OpcUa_Good),
      attributeId(attributeId)
    {}


    // Get a string representation
    // =============================================================================================
    string WriteRequestTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - address\n";
        ss << address.toString(indent + "   ", colon) << "\n";

        ss << indent << " - attributeId";
        ss << fillToPos(ss, colon);
        ss << ": " << attributeId << " (" << attributeids::toString(attributeId) << ")\n";

        ss << indent << " - data";
        ss << fillToPos(ss, colon);
        ss << ": " << data.toTextString() << "\n";

        ss << indent << " - opcUaStatusCode";
        ss << fillToPos(ss, colon);
        ss << ": " << opcUaStatusCode
                << " (" << UaStatusCode(opcUaStatusCode).toString().toUtf8() << ")";
        return ss.str();
    }

    // operator==
    // =============================================================================================
    bool operator==(const WriteRequestTarget& object1, const WriteRequestTarget& object2)
    {
        return    object1.address == object2.address
               && object1.data == object2.data
               && object1.opcUaStatusCode == object2.opcUaStatusCode
               && object1.attributeId == object2.attributeId;
    }

    // operator!=
    // =============================================================================================
    bool operator!=(const WriteRequestTarget& object1, const WriteRequestTarget& object2)
    {
        return !(object1 == object2);
    }

    // operator<
    // =============================================================================================
    bool operator<(const WriteRequestTarget& object1, const WriteRequestTarget& object2)
    {
        if (object1.address != object2.address)
            return object1.address < object2.address;
        else if (object1.data != object2.data)
            return object1.data < object2.data;
        else if (object1.opcUaStatusCode != object2.opcUaStatusCode)
            return object1.opcUaStatusCode < object2.opcUaStatusCode;
        else
            return object1.attributeId < object2.attributeId;
    }


    // Get the resolvable items
    // =============================================================================================
    vector<Address> WriteRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(address);
        return ret;
    }


    // Set the resolved items
    // =============================================================================================
    Status WriteRequestTarget::setResolvedItems(
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
    Status WriteRequestTarget::getServerUri(string& serverUri) const
    {
        return extractServerUri(address, serverUri);
    }





}
