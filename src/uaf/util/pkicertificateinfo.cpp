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

#include "uaf/util/pkicertificateinfo.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    PkiCertificateInfo::PkiCertificateInfo()
    : validTime(0)
    {}


    // Get a string representation
    // =============================================================================================
    string PkiCertificateInfo::toString(const string& indentation, size_t colon) const
    {
        stringstream ss;

        ss << indentation << " - uri";
        ss << fillToPos(ss, colon);
        ss << ": " << uri << "\n";


        ss << indentation << " - ipAddresses[]";
        if (ipAddresses.size() == 0)
        {
            fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i<ipAddresses.size(); i++)
            {
                ss << indentation << "    - " << "ipAddresses[" << i << "]";
                fillToPos(ss, colon);
                ss << ": " << ipAddresses[i] << "\n";
            }
        }

        ss << indentation << " - dnsNames[]";
        if (dnsNames.size() == 0)
        {
            fillToPos(ss, colon);
            ss << ": []\n";
        }
        else
        {
            ss << "\n";
            for (size_t i = 0; i<dnsNames.size(); i++)
            {
                ss << indentation << "    - " << "dnsNames[" << i << "]";
                fillToPos(ss, colon);
                ss << ": " << dnsNames[i] << "\n";
            }
        }

        ss << indentation << " - eMail";
        ss << fillToPos(ss, colon);
        ss << ": " << eMail << "\n";

        ss << indentation << " - validTime";
        ss << fillToPos(ss, colon);
        ss << ": " << validTime << "s";

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const PkiCertificateInfo& object1, const PkiCertificateInfo& object2)
    {
        return    object1.uri == object2.uri
               && object1.ipAddresses == object2.ipAddresses
               && object1.dnsNames == object2.dnsNames
               && object1.eMail == object2.eMail
               && object1.validTime == object2.validTime;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const PkiCertificateInfo& object1, const PkiCertificateInfo& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const PkiCertificateInfo& object1, const PkiCertificateInfo& object2)
    {
        if (object1.uri != object2.uri)
            return object1.uri < object2.uri;
        else if (object1.ipAddresses != object2.ipAddresses)
            return object1.ipAddresses < object2.ipAddresses;
        else if (object1.dnsNames != object2.dnsNames)
            return object1.dnsNames < object2.dnsNames;
        else if (object1.eMail != object2.eMail)
            return object1.eMail < object2.eMail;
        else
            return object1.validTime < object2.validTime;
    }

}
