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

#include "uaf/client/settings/historyreadrawmodifiedsettings.h"




namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;
    using std::stringstream;
    using std::vector;



    // Constructor
    // =============================================================================================
    HistoryReadRawModifiedSettings::HistoryReadRawModifiedSettings()
    : BaseServiceSettings(),
      isReadModified(false)
    {}


    // Get a string representation
    // =============================================================================================
    string HistoryReadRawModifiedSettings::toString(const string& indent, std::size_t colon) const
    {
        std::stringstream ss;
        ss << BaseServiceSettings::toString(indent, colon) << "\n";

        ss << indent << " - startTime";
        ss << fillToPos(ss, colon);
        ss << ": " << startTime.toString() << "\n";

        ss << indent << " - endTime";
        ss << fillToPos(ss, colon);
        ss << ": " << endTime.toString() << "\n";

        ss << indent << " - isReadModified";
        ss << fillToPos(ss, colon);
        ss << ": " << (isReadModified ? "True" : "False") << "\n";

        ss << indent << " - maxAutoReadMore";
        ss << fillToPos(ss, colon);
        ss << ": " << int(maxAutoReadMore) << "\n";

        ss << indent << " - numValuesPerNode";
        ss << fillToPos(ss, colon);
        ss << ": " << int(numValuesPerNode) << "\n";

        ss << indent << " - returnBounds";
        ss << fillToPos(ss, colon);
        ss << ": " << (returnBounds ? "True" : "False") << "\n";

        ss << indent << " - timestampsToReturn";
        ss << fillToPos(ss, colon);
        ss << ": " << int(timestampsToReturn);
        ss << " (" << timestampstoreturn::toString(timestampsToReturn) << ")\n";

        ss << indent << " - releaseContinuationPoints";
        ss << fillToPos(ss, colon);
        ss << ": " << (releaseContinuationPoints ? "True" : "False");

        return ss.str();
    }


}
