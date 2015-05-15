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

#include "uaf/client/results/writeresulttarget.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    WriteResultTarget::WriteResultTarget()
    : opcUaStatusCode(OpcUa_Uncertain)
    {}


    // Get a string representation
    // =============================================================================================
    string WriteResultTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;
        ss << "status: " << status.toString();
        ss << fillToPos(ss, colon);
        ss << ": " << status.toString() << "\n";

        ss << indent << " - opcUaStatusCode";
        ss << fillToPos(ss, colon);
        ss << ": " << double(opcUaStatusCode);

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const WriteResultTarget& object1,
            const WriteResultTarget& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.status             == object2.status
               && object1.opcUaStatusCode    == object2.opcUaStatusCode;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const WriteResultTarget& object1,
            const WriteResultTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const WriteResultTarget& object1,
            const WriteResultTarget& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.opcUaStatusCode != object2.opcUaStatusCode)
            return object1.opcUaStatusCode < object2.opcUaStatusCode;
        else
            return object1.status < object2.status;
    }


}
