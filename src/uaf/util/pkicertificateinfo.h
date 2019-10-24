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

#ifndef UAF_PKICERTIFICATEINFO_H_
#define UAF_PKICERTIFICATEINFO_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uapkicpp/uapkicertificate.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A PkiCertificateInfo holds some information about a Certificate.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT PkiCertificateInfo
    {
    public:


        /**
         * Create an empty PKI certificate information.
         */
        PkiCertificateInfo();


        std::string uri;
        std::vector<std::string> ipAddresses;
        std::vector<std::string> dnsNames;
        std::string eMail;
        long validTime;


        /**
         * Get a string representation of the PKI certificate information.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=17) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(const PkiCertificateInfo& object1, const PkiCertificateInfo& object2);
        friend bool UAF_EXPORT operator!=(const PkiCertificateInfo& object1, const PkiCertificateInfo& object2);
        friend bool UAF_EXPORT operator<(const PkiCertificateInfo& object1, const PkiCertificateInfo& object2);

        // create a PkiCertificateInfo from an SDK instance
        static PkiCertificateInfo fromSdk(const UaPkiCertificateInfo& uaInfo);

        // create a SDK instance from a UAF instance
        UaPkiCertificateInfo toSdk() const;
    };


}



#endif /* UAF_PKICERTIFICATEINFO_H_ */
