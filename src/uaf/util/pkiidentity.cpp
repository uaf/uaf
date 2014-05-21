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

#include "uaf/util/pkiidentity.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    PkiIdentity::PkiIdentity()
    {}


    // Is the application description empty?
    // =============================================================================================
    bool PkiIdentity::isEmpty() const
    {
        return organization.empty()
            && organizationUnit.empty()
            && locality.empty()
            && state.empty()
            && country.empty()
            && commonName.empty()
            && domainComponent.empty();
    }


    // Get a string representation
    // =============================================================================================
    string PkiIdentity::toString(const string& indentation, size_t colon) const
    {
        stringstream ss;

        ss << indentation << " - organization";
        ss << fillToPos(ss, colon);
        ss << ": " << organization << "\n";

        ss << indentation << " - organizationUnit";
        ss << fillToPos(ss, colon);
        ss << ": " << organizationUnit << "\n";

        ss << indentation << " - locality";
        ss << fillToPos(ss, colon);
        ss << ": " << locality << "\n";

        ss << indentation << " - state";
        ss << fillToPos(ss, colon);
        ss << ": " << state << "\n";

        ss << indentation << " - country";
        ss << fillToPos(ss, colon);
        ss << ": " << country << "\n";

        ss << indentation << " - commonName";
        ss << fillToPos(ss, colon);
        ss << ": " << commonName << "\n";

        ss << indentation << " - domainComponent";
        ss << fillToPos(ss, colon);
        ss << ": " << domainComponent;

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const PkiIdentity& object1, const PkiIdentity& object2)
    {
        return    object1.organization == object2.organization
               && object1.organizationUnit == object2.organizationUnit
               && object1.locality == object2.locality
               && object1.state == object2.state
               && object1.country == object2.country
               && object1.commonName == object2.commonName
               && object1.domainComponent == object2.domainComponent;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const PkiIdentity& object1, const PkiIdentity& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const PkiIdentity& object1, const PkiIdentity& object2)
    {
        if (object1.organization != object2.organization)
            return object1.organization < object2.organization;
        else if (object1.organizationUnit != object2.organizationUnit)
            return object1.organizationUnit < object2.organizationUnit;
        else if (object1.locality != object2.locality)
            return object1.locality < object2.locality;
        else if (object1.state != object2.state)
            return object1.state < object2.state;
        else if (object1.country != object2.country)
            return object1.country < object2.country;
        else if (object1.commonName != object2.commonName)
            return object1.commonName < object2.commonName;
        else
            return object1.commonName < object2.commonName;
    }

}
