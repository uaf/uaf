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

#include "uaf/util/modificationinfo.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::size_t;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    ModificationInfo::ModificationInfo()
    : historyUpdateType(HistoryUpdateType_Insert)
    {}



    // Update a stack object
    // =============================================================================================
    void ModificationInfo::fromSdk(const OpcUa_ModificationInfo& uaInfo)
    {
        if (uaInfo.UpdateType == OpcUa_HistoryUpdateType_Insert)
            historyUpdateType = HistoryUpdateType_Insert;
        else if (uaInfo.UpdateType == OpcUa_HistoryUpdateType_Replace)
            historyUpdateType = HistoryUpdateType_Replace;
        else if (uaInfo.UpdateType == OpcUa_HistoryUpdateType_Update)
            historyUpdateType = HistoryUpdateType_Update;
        else if (uaInfo.UpdateType == OpcUa_HistoryUpdateType_Delete)
            historyUpdateType = HistoryUpdateType_Delete;

        modificationTime.fromSdk(UaDateTime(uaInfo.ModificationTime));

        if (!UaString(&uaInfo.UserName).isEmpty())
            userName = UaString(&uaInfo.UserName).toUtf8();
    }



    // Get a string representation
    // =============================================================================================
    string ModificationInfo::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - historyUpdateType";
        ss << fillToPos(ss, colon);
        ss << ": " << int(historyUpdateType) << " ";
        if      (historyUpdateType == HistoryUpdateType_Insert)  ss << "(Insert)\n";
        else if (historyUpdateType == HistoryUpdateType_Replace) ss << "(Replace)\n";
        else if (historyUpdateType == HistoryUpdateType_Update)  ss << "(Update)\n";
        else if (historyUpdateType == HistoryUpdateType_Delete)  ss << "(Delete)\n";
        else                                                     ss << "!!!INVALID!!!\n";

        ss << indent << " - modificationTime";
        ss << fillToPos(ss, colon);
        ss << ": " << modificationTime.toString() << "\n";

        ss << indent << " - userName";
        ss << fillToPos(ss, colon);
        ss << ": '" << userName << "'";

        return ss.str();
    }



    // Get a string representation
    // =============================================================================================
    string ModificationInfo::toCompactString() const
    {
        stringstream ss;

        if      (historyUpdateType == HistoryUpdateType_Insert)  ss << "Insert";
        else if (historyUpdateType == HistoryUpdateType_Replace) ss << "Replace";
        else if (historyUpdateType == HistoryUpdateType_Update)  ss << "Update";
        else if (historyUpdateType == HistoryUpdateType_Delete)  ss << "Delete";
        else                                                     ss << "!!!INVALID!!!\n";

        ss << "|" << modificationTime.toString();

        ss << "|'" << userName << "'";

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==( const ModificationInfo& object1, const ModificationInfo& object2)
    {
        return    (object1.historyUpdateType == object2.historyUpdateType)
               && (object1.modificationTime == object2.modificationTime)
               && (object1.userName == object2.userName);
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ModificationInfo& object1, const ModificationInfo& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ModificationInfo& object1, const ModificationInfo& object2)
    {
        if (object1.historyUpdateType != object2.historyUpdateType)
            return object1.historyUpdateType < object2.historyUpdateType;
        else if (object1.modificationTime != object2.modificationTime)
            return object1.modificationTime < object2.modificationTime;
        else
            return object1.userName < object2.userName;
    }

}

