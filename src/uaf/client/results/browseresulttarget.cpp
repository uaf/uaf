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

#include "uaf/client/results/browseresulttarget.h"


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
    BrowseResultTarget::BrowseResultTarget()
    : autoBrowsedNext(0)
    {}


    // Get a string representation
    // =============================================================================================
    string BrowseResultTarget::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - status";
        ss << fillToPos(ss, colon);
        ss << ": " << status.toString() << "\n";

        ss << indent << " - continuationPoint";
        ss << fillToPos(ss, colon);
        ss << ": " << int(continuationPoint.length()) << " bytes\n";

        ss << indent << " - autoBrowsedNext";
        ss << fillToPos(ss, colon);
        ss << ": " << int(autoBrowsedNext) << "\n";

        ss << indent << " - clientConnectionId";
        ss << fillToPos(ss, colon);
        ss << ": " << int(clientConnectionId) << "\n";

        // don't fully log all references because the resulting string could be huge!
        ss << indent << " - references[]";

        if (references.size() == 0)
        {
            ss << fillToPos(ss, colon);
            ss << ": []";
        }
        else
        {
            for (size_t i = 0; i < references.size(); i++)
            {
                ss << "\n" << indent << "   " << " - references[" << int(i) << "]\n";
                ss << references[i].toString(indent + "      ", colon);
            }
        }

        return ss.str();
    }


}
