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

#include "uaf/client/requests/methodcallrequesttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;




    // Constructor
    // =============================================================================================
    MethodCallRequestTarget::MethodCallRequestTarget()
    {}


    // Constructor
    // =============================================================================================
    MethodCallRequestTarget::MethodCallRequestTarget(
            const Address&          objectAddress,
            const Address&          methodAddress,
            const vector<Variant>&  inputArguments)
    : objectAddress(objectAddress),
      methodAddress(methodAddress),
      inputArguments(inputArguments)
    {}


    // Get a string representation
    // =============================================================================================
    string MethodCallRequestTarget::toString(const string& indent, std::size_t colon) const
    {
        stringstream ss;
        ss << indent << " - objectAddress\n";
        ss << objectAddress.toString(indent + "   ", colon) << "\n";

        ss << indent << " - methodAddress\n";
        ss << methodAddress.toString(indent + "   ", colon) << "\n";

        ss << indent << " - inputArguments[]";
        ss << fillToPos(ss, colon);
        ss << ": [";

        for (size_t i = 0; i < inputArguments.size(); i++ )
        {
            ss << inputArguments[i].toTextString().c_str();
            if (i < (inputArguments.size()-1))
                ss << ", ";
        }

        ss << "]";

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const MethodCallRequestTarget& object1, const MethodCallRequestTarget& object2)
    {
        bool ret = true;
        if ( object1.objectAddress != object2.objectAddress )
            ret = false;
        else if ( object1.methodAddress != object2.methodAddress )
            ret = false;
        else if ( object1.inputArguments.size() != object2.inputArguments.size() )
            ret = false;
        else
        {
            // check the input arguments
            for (size_t i = 0; i < object1.inputArguments.size(); i++ )
            {
                if ( object1.inputArguments[i] != object2.inputArguments[i] )
                {
                    ret = false;
                    break;
                }
            }
        }

        return ret;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const MethodCallRequestTarget& object1, const MethodCallRequestTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const MethodCallRequestTarget& object1, const MethodCallRequestTarget& object2)
    {
        bool ret = false;
        if ( object1.objectAddress < object2.objectAddress )
            ret = true;
        else if ( object1.methodAddress < object2.methodAddress )
            ret = true;
        else if ( object1.inputArguments.size() < object2.inputArguments.size() )
            ret = true;
        else
        {
            // check the input arguments
            for (size_t i = 0; i < object1.inputArguments.size(); i++ )
            {
                if ( object1.inputArguments[i] < object2.inputArguments[i] )
                {
                    ret = true;
                    break;
                }
            }
        }

        return ret;
    }


    // Get the resolvable items
    // =============================================================================================
    vector<Address> MethodCallRequestTarget::getResolvableItems() const
    {
        vector<Address> ret;
        ret.push_back(objectAddress);
        ret.push_back(methodAddress);
        return ret;
    }


    // Get a string representation
    // =============================================================================================
    Status MethodCallRequestTarget::getServerUri(string& serverUri) const
    {
        // we demand that both addresses have a valid serverURI, and we let the method call be
        // executed on the server owning the methodAddress
        string objectServerUri;
        Status objectStatus = extractServerUri(objectAddress, objectServerUri);

        if (objectStatus.isGood())
            return extractServerUri(methodAddress, serverUri);
        else
            return objectStatus;
    }



    // Set the resolved items
    // =============================================================================================
    Status MethodCallRequestTarget::setResolvedItems(
            const vector<ExpandedNodeId>& expandedNodeIds,
            const vector<Status>&         resolutionStatuses)
    {
        Status ret;

        if (   expandedNodeIds.size()    == resolvableItemsCount()
            && resolutionStatuses.size() == resolvableItemsCount())
        {
            if (resolutionStatuses[0].isGood())
                objectAddress = Address(expandedNodeIds[0]);

            if (resolutionStatuses[1].isGood())
                methodAddress = Address(expandedNodeIds[1]);

            ret.setGood();
        }
        else
        {
            ret.setStatus(statuscodes::UnexpectedError, "Could not set the resolved items");
        }

        return ret;
    }

}
