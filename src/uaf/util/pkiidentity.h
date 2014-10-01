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

#ifndef UAF_PKIIDENTITY_H_
#define UAF_PKIIDENTITY_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uapki/uapkiidentity.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A PkiIdentity holds the identity of the subject and issuer of a certificate.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT PkiIdentity
    {
    public:


        /**
         * Create an empty PKI identity.
         */
        PkiIdentity();

        std::string organization;
        std::string organizationUnit;
        std::string locality;
        std::string state;
        std::string country;
        std::string commonName;
        std::string domainComponent;


        /**
         * Is the PKI identity filled out, or empty?
         */
        bool isEmpty() const;


        /**
         * Get a string representation of the PKI identity.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString(const std::string& indent="", std::size_t colon=20) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(const PkiIdentity& object1, const PkiIdentity& object2);
        friend bool UAF_EXPORT operator!=(const PkiIdentity& object1, const PkiIdentity& object2);
        friend bool UAF_EXPORT operator<(const PkiIdentity& object1, const PkiIdentity& object2);

        // create a PkiIdentity from an SDK instance
        static PkiIdentity fromSdk(const UaPkiIdentity& uaId);

        // create an SDK instance from a UAF instance
        UaPkiIdentity toSdk() const;
    };


}



#endif /* UAF_PKIIDENTITY_H_ */
