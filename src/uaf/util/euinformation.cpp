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

#include "uaf/util/euinformation.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    EUInformation::EUInformation()
    {}


    // Constructor
    // =============================================================================================
    EUInformation::EUInformation(
            const std::string &namespaceUri,
            int32_t unitId,
            const uaf::LocalizedText& displayName,
            const uaf::LocalizedText& description)
    {
        UaString uaNamespaceUri(namespaceUri.c_str());
        UaLocalizedText uaDisplayName;
        displayName.toSdk(uaDisplayName);
        UaLocalizedText uaDescription;
        description.toSdk(uaDescription);

    	uaEUInformation_ = UaEUInformation(uaNamespaceUri, unitId, uaDisplayName, uaDescription);
    }


    // Constructor
    // =============================================================================================
    EUInformation::EUInformation(const uaf::ExtensionObject& extensionObject)
    {
        UaExtensionObject uaExt;
        extensionObject.toSdk(uaExt);
        uaEUInformation_ = UaEUInformation(uaExt);
    }


    // Clear the range
    // =============================================================================================
    void EUInformation::clear()
    {
        uaEUInformation_.clear();
    }


    // Get a string representation
    // =============================================================================================
    std::string EUInformation::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        ss << indent << " - namespaceUri";
        ss << fillToPos(ss, colon);
        ss << ": " << getNamespaceUri() << "\n";

        ss << indent << " - unitId";
        ss << fillToPos(ss, colon);
        ss << ": " << getUnitId() << "\n";

        ss << indent << " - displayName";
        ss << fillToPos(ss, colon);
        ss << ": " << getDisplayName().toString() << "\n";

        ss << indent << " - description";
        ss << fillToPos(ss, colon);
        ss << ": " << getDescription().toString();

        return ss.str();
    }


}


