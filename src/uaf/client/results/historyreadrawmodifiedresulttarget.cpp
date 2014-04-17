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

#include "uaf/client/results/historyreadrawmodifiedresulttarget.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    HistoryReadRawModifiedResultTarget::HistoryReadRawModifiedResultTarget()
    : autoReadMore(0)
    {}


    // Get a string representation
    // =============================================================================================
    string HistoryReadRawModifiedResultTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << int(clientConnectionId) << "\n";

        ss << indent << " - status";
        ss << fillToPos(ss, colon);
        ss << ": " << status.toString() << "\n";

        ss << indent << " - continuationPoint";
        ss << fillToPos(ss, colon);
        ss << ": " << continuationPoint.toString() << "\n";

        ss << indent << " - autoReadMore";
        ss << fillToPos(ss, colon);
        ss << ": " << int(autoReadMore) << "\n";

        ss << indent << " - dataValues";
        if (dataValues.size() == 0)
        {
            ss << fillToPos(ss, colon);
            ss << ": []";
        }
        else
        {
            for (size_t i = 0; i < dataValues.size(); i++)
            {
                ss << "\n" << indent << "    - dataValues" << "[" << int(i) << "]";
                ss << fillToPos(ss, colon);
                ss << ": " << dataValues[i].toCompactString();
            }
        }

        ss << "\n";

        ss << indent << " - modificationInfos";
        if (modificationInfos.size() == 0)
        {
            ss << fillToPos(ss, colon);
            ss << ": []";
        }
        else
        {
            for (size_t i = 0; i < modificationInfos.size(); i++)
            {
                ss << "\n" << indent << "    - modificationInfos" << "[" << int(i) << "]";
                ss << fillToPos(ss, colon);
                ss << ": " << modificationInfos[i].toCompactString();
            }
        }

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(
            const HistoryReadRawModifiedResultTarget& object1,
            const HistoryReadRawModifiedResultTarget& object2)
    {
        return    object1.clientConnectionId == object2.clientConnectionId
               && object1.status             == object2.status
               && object1.continuationPoint  == object2.continuationPoint
               && object1.autoReadMore       == object2.autoReadMore
               && object1.dataValues         == object2.dataValues
               && object1.modificationInfos  == object2.modificationInfos;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(
            const HistoryReadRawModifiedResultTarget& object1,
            const HistoryReadRawModifiedResultTarget& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(
            const HistoryReadRawModifiedResultTarget& object1,
            const HistoryReadRawModifiedResultTarget& object2)
    {
        if (object1.clientConnectionId != object2.clientConnectionId)
            return object1.clientConnectionId < object2.clientConnectionId;
        else if (object1.status != object2.status)
            return object1.status < object2.status;
        else if (object1.continuationPoint != object2.continuationPoint)
            return object1.continuationPoint < object2.continuationPoint;
        else if (object1.autoReadMore != object2.autoReadMore)
            return object1.autoReadMore < object2.autoReadMore;
        else if (object1.dataValues != object2.dataValues)
            return object1.dataValues < object2.dataValues;
        else
            return object1.modificationInfos < object2.modificationInfos;
    }


}
