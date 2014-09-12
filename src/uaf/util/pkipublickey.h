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

#ifndef UAF_PKIPUBLICKEY_H_
#define UAF_PKIPUBLICKEY_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <iostream>
// SDK
#include "uapki/uapkipublickey.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/bytestring.h"
#include "uaf/util/stringifiable.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A PkiPublicKey can hold an RSA or DSA encrypted public key.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT PkiPublicKey
    {
    public:

        /**
         * Key encryption algorithm.
         *
         * @ingroup Util
         */
        enum KeyType
        {
            RSA     = 0,
            DSA     = 1,
            Unknown = 2
        };


        /**
         * Create an empty key.
         */
        PkiPublicKey();


        /**
         * Copy constructor (to avoid bug in SDK!)
         * Copying and assignment of UaPkiPublicKey in SDKv1.4.2 segfaults! Bug reported.
         */
        PkiPublicKey(const uaf::PkiPublicKey& copy);


        /**
         * Constructor (to avoid bug in SDK!)
         * Copying and assignment of UaPkiPublicKey in SDKv1.4.2 segfaults! Bug reported.
         */
        PkiPublicKey(const UaByteArray& uaByteArray);


        /**
         * Assignment operator (to avoid bug in SDK!)
         * Copying and assignment of UaPkiPublicKey in SDKv1.4.2 segfaults! Bug reported.
         */
        PkiPublicKey operator=(const PkiPublicKey& copy);


        /**
         * Write the public key to a DER encoded bytestring.
         */
        uaf::ByteString toDER() const;


        /**
         * Read the public key from a DER encoded bytestring.
         */
        static PkiPublicKey fromDER(const uaf::ByteString& data);


        /** Get the key type. */
        KeyType keyType() const;


        /** Get the size of the key */
        int keySize() const;


        /** Get a list of errors. */
        std::vector<std::string> getErrors();


        /**
         * Get a string representation of the PKI certificate information.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString() const;


        // comparison operators
        friend bool UAF_EXPORT operator==(const PkiPublicKey& object1, const PkiPublicKey& object2);
        friend bool UAF_EXPORT operator!=(const PkiPublicKey& object1, const PkiPublicKey& object2);
        friend bool UAF_EXPORT operator<(const PkiPublicKey& object1, const PkiPublicKey& object2);

    private:
        UaPkiPublicKey uaPkiPublicKey_;
    };


}



#endif /* UAF_PKIPUBLICKEY_H_ */
