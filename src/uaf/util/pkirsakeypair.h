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

#ifndef UAF_PKIRSAKEYPAIR_H_
#define UAF_PKIRSAKEYPAIR_H_


// STD
#include <string>
#include <sstream>
#include <vector>
// SDK
#include "uapki/uapkirsakeypair.h"
// UAF
#include "uaf/util/pkiprivatekey.h"
#include "uaf/util/pkipublickey.h"


namespace uaf
{

    /*******************************************************************************************//**
    * A PkiRsaKeyPair holds a private and a public key pair.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT PkiRsaKeyPair
    {
    public:


        /**
         * Create an empty key pair with a default bitsize of 1024.
         *
         * (We're setting a bitsize by default, otherwise the SDK segfaults (bug has been reported)).
         */
        PkiRsaKeyPair();


        /**
         * Create an empty key pair with a default bitsize of 1024.
         */
        PkiRsaKeyPair(int bits);


        /**
         * Create an empty key pair via an SDK instance.
         */
        PkiRsaKeyPair(UaPkiRsaKeyPair uaPair);


        /** Get the private key of this pair. */
        uaf::PkiPrivateKey privateKey() const { return uaf::PkiPrivateKey(uaPair_.privateKey()); }


        /** Get the public key of this pair. */
        uaf::PkiPublicKey publicKey() const { return uaf::PkiPublicKey(uaPair_.publicKey()); }


        /**
         * Write the key pair to an unprotected PEM file.
         *
         * @return Zero on success.
         */
        int toPEMFile(const std::string& fileName) const;


        /**
         * Write the key pair to a password protected PEM file.
         *
         * @return Zero on success.
         */
        int toPEMFile(const std::string& fileName, const std::string& password) const;


        /**
         * Convert the key pair to DER data.
         */
        uaf::ByteString toDER() const;


        /**
         * Read the key pair from an unprotected PEM file.
         */
        static PkiRsaKeyPair fromPEMFile(const std::string& fileName);


        /**
         * Read the key pair from a protected PEM file.
         */
        static PkiRsaKeyPair fromPEMFile(const std::string& fileName, const std::string& password);


        /**
         * Check the key pair.
         *
         * !!! Warning !!! This method may crash (segfault) if empty keys are given.
         * This is a bug in the SDK !!!
         * ToDo: remove the warning when the bug in the SDK is solved.
         */
        static bool checkKeyPair(const uaf::PkiPublicKey &publicKey, const uaf::PkiPrivateKey &privateKey);


        /**
         * Check if the key pair is valid.
         */
        bool isValid();


        /** Get a list of errors. */
        std::vector<std::string> getErrors();


        /**
         * Get a string representation of the key pair.
         *
         * @param indent Indentation to add to each line (e.g. "  " to indent with 2 spaces).
         * @param colon  The position to put the colon (double point).
         * @return       A string representation (multiple lines, separated by newline-characters).
         */
        std::string toString() const;


        // comparison operators
        friend bool UAF_EXPORT operator==(const PkiRsaKeyPair& object1, const PkiRsaKeyPair& object2);
        friend bool UAF_EXPORT operator!=(const PkiRsaKeyPair& object1, const PkiRsaKeyPair& object2);
        friend bool UAF_EXPORT operator<(const PkiRsaKeyPair& object1, const PkiRsaKeyPair& object2);

    private:
        UaPkiRsaKeyPair uaPair_;
    };


}



#endif /* UAF_PKIRSAKEYPAIR_H_ */
