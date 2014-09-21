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

#include "uaf/util/pkirsakeypair.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    PkiRsaKeyPair::PkiRsaKeyPair()
    : uaPair_(1024)
    {}


    // Constructor
    // =============================================================================================
    PkiRsaKeyPair::PkiRsaKeyPair(int bits)
    : uaPair_(bits)
    {}


    // Constructor
    // =============================================================================================
    PkiRsaKeyPair::PkiRsaKeyPair(UaPkiRsaKeyPair uaPair)
    : uaPair_(uaPair)
    {}


    // Write a PEM file
    // =============================================================================================
    int PkiRsaKeyPair::toPEMFile(const string& fileName) const
    {
        return uaPair_.toPEMFile(fileName.c_str(), 0);
    }

    // Write a PEM file
    // =============================================================================================
    int PkiRsaKeyPair::toPEMFile(const string& fileName, const string& password) const
    {
        return uaPair_.toPEMFile(fileName.c_str(), password.c_str());
    }


    // Convert to DER
    // =============================================================================================
    ByteString PkiRsaKeyPair::toDER() const
    {
        ByteString ret;
        ret.fromSdk(uaPair_.toDER());
        return ret;
    }


    // Read from PEM file
    // =============================================================================================
    PkiRsaKeyPair PkiRsaKeyPair::fromPEMFile(const string& fileName)
    {
        return PkiRsaKeyPair( UaPkiRsaKeyPair::fromPEMFile(fileName.c_str(), 0) );
    }


    // Read from PEM file
    // =============================================================================================
    PkiRsaKeyPair PkiRsaKeyPair::fromPEMFile(const string& fileName, const string& password)
    {
        return PkiRsaKeyPair( UaPkiRsaKeyPair::fromPEMFile(fileName.c_str(), password.c_str()) );
    }


    // Static function to check a key pair
    // =============================================================================================
    bool PkiRsaKeyPair::checkKeyPair(const PkiPublicKey &publicKey, const PkiPrivateKey &privateKey)
    {
        return UaPkiRsaKeyPair::checkKeyPair(publicKey.uaPkiPublicKey_, privateKey.uaPkiPrivateKey_);
    }


    // Is the key pair valid?
    // =============================================================================================
    bool PkiRsaKeyPair::isValid()
    {
        return uaPair_.isValid();
    }


    // Get any errors
    // =============================================================================================
    std::vector<std::string> PkiRsaKeyPair::getErrors()
    {
        std::vector<std::string> ret;
        std::list<UaString> errors = uaPair_.getErrors();
        std::list<UaString>::const_iterator iter;
        for (iter = errors.begin(); iter != errors.end(); ++iter)
            ret.push_back(iter->toUtf8());
        return ret;
    }

    // Get a string representation
    // =============================================================================================
    string PkiRsaKeyPair::toString() const
    {
        stringstream ss;

        // ToDo add some useful info (can't use isValid() nor getErrors() because they're not const)

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const PkiRsaKeyPair& object1, const PkiRsaKeyPair& object2)
    {
        return object1.toDER() == object2.toDER();
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const PkiRsaKeyPair& object1, const PkiRsaKeyPair& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const PkiRsaKeyPair& object1, const PkiRsaKeyPair& object2)
    {
        return object1.toDER() < object2.toDER();
    }

}
