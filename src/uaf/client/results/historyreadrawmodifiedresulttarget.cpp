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
    {}


    // Get a string representation
    // =============================================================================================
    string HistoryReadRawModifiedResultTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

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
            ss << ": []\n";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i < dataValues.size(); i++)
            {
                ss << indent << "    - dataValues" << "[" << int(i) << "]";
                ss << fillToPos(ss, colon);
                ss << ": " << dataValues[i].toCompactString() << "\n";
            }
        }

        ss << indent << " - modificationInformation";
        ss << fillToPos(ss, colon);
        ss << ": " << modificationInformation.toString() << "\n";

        ss << indent << " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << int(clientConnectionId);

        return ss.str();
    }


}
