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

#include "uaf/util/pkicertificate.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;


    // Constructor
    // =============================================================================================
    PkiCertificate::PkiCertificate()
    : uaCert_()
    {}


    // Constructor
    // =============================================================================================
    PkiCertificate::PkiCertificate(
        const PkiCertificateInfo& info,
        const PkiIdentity& subject,
        const PkiRsaKeyPair& subjectKeyPair,
        bool bCACert)
    : uaCert_(info.toSdk(),
              subject.toSdk(),
              subjectKeyPair.uaPair_,
              bCACert,
              UaPkiCertificate::SignatureAlgorithm_Sha256)
    {}


    // Constructor
    // =============================================================================================
    PkiCertificate::PkiCertificate(
        const uaf::PkiCertificateInfo& info,
        const uaf::PkiIdentity& subject,
        const uaf::PkiPublicKey& subjectPublicKey,
        const uaf::PkiCertificate& issuerCert,
        const uaf::PkiPrivateKey& issuerPrivateKey,
        bool bCACert)
    : uaCert_(info.toSdk(),
              subject.toSdk(),
              subjectPublicKey.uaPkiPublicKey_,
              issuerCert.uaCert_,
              issuerPrivateKey.uaPkiPrivateKey_,
              bCACert,
              UaPkiCertificate::SignatureAlgorithm_Sha256)
    {}


    // Constructor
    // =============================================================================================
    PkiCertificate::PkiCertificate(const UaPkiCertificate& uaCert)
    : uaCert_(uaCert)
    {}


    // publicKey
    // =============================================================================================
    PkiPublicKey PkiCertificate::publicKey() const
    {
        if (uaCert_.isNull())
            return uaf::PkiPublicKey();
        else
            return uaf::PkiPublicKey(uaCert_.publicKey());
    }

    // commonName
    // =============================================================================================
    string PkiCertificate::commonName() const
    {
        if (uaCert_.commonName().isNull())
            return string();
        else
            return string(uaCert_.commonName().toUtf8());
    }

    // subject
    // =============================================================================================
    PkiIdentity PkiCertificate::subject() const
    {
        return uaf::PkiIdentity::fromSdk(uaCert_.subject());
    }

    // issuer
    // =============================================================================================
    PkiIdentity PkiCertificate::issuer() const
    {
        return uaf::PkiIdentity::fromSdk(uaCert_.issuer());
    }

    // subjectNameHash
    // =============================================================================================
    unsigned long PkiCertificate::subjectNameHash() const
    {
        return uaCert_.subjectNameHash();
    }

    // info
    // =============================================================================================
    PkiCertificateInfo PkiCertificate::info() const
    {
        return uaf::PkiCertificateInfo::fromSdk(uaCert_.info());
    }

    // validFrom
    // =============================================================================================
    DateTime PkiCertificate::validFrom() const
    {
        uaf::DateTime dt;
        dt.fromSdk(uaCert_.validFrom());
        return dt;
    }

    // validTo
    // =============================================================================================
    DateTime PkiCertificate::validTo() const
    {
        uaf::DateTime dt;
        dt.fromSdk(uaCert_.validTo());
        return dt;
    }

    // serialNumber
    // =============================================================================================
    string PkiCertificate::serialNumber() const
    {
        if (uaCert_.serialNumber().isNull())
            return string();
        else
            return string(uaCert_.serialNumber().toUtf8());
    }

    // signatureTypeNID
    // =============================================================================================
    int PkiCertificate::signatureTypeNID() const
    {
        return uaCert_.signatureTypeNID();
    }

    // signatureTypeNID
    // =============================================================================================
    string PkiCertificate::signatureTypeString() const
    {
        if (uaCert_.signatureTypeString().isNull())
            return string();
        else
            return string(uaCert_.signatureTypeString().toUtf8());
    }

    // isValid
    // =============================================================================================
    bool PkiCertificate::isValid() const
    {
        return uaCert_.isValid();
    }

    // isSelfSigned
    // =============================================================================================
    bool PkiCertificate::isSelfSigned() const
    {
        if (uaCert_.isNull())
            return false;
        else
            return uaCert_.isSelfSigned();
    }

    // hasExtension
    // =============================================================================================
    bool PkiCertificate::hasExtension(PkiCertificate::Extension extension) const
    {
        switch(extension)
        {
            case Extension_SubjectAltName          : return uaCert_.hasExtension(UaPkiCertificate::Extension_SubjectAltName);
            case Extension_BasicConstraints        : return uaCert_.hasExtension(UaPkiCertificate::Extension_BasicConstraints);
            case Extension_NetscapeComment         : return uaCert_.hasExtension(UaPkiCertificate::Extension_NetscapeComment);
            case Extension_SubjectKeyIdentifier    : return uaCert_.hasExtension(UaPkiCertificate::Extension_SubjectKeyIdentifier);
            case Extension_AuthorityKeyIdentifier  : return uaCert_.hasExtension(UaPkiCertificate::Extension_AuthorityKeyIdentifier);
            case Extension_KeyUsage                : return uaCert_.hasExtension(UaPkiCertificate::Extension_KeyUsage);
            case Extension_ExtendedKeyUsage        : return uaCert_.hasExtension(UaPkiCertificate::Extension_ExtendedKeyUsage);
            default                                : return false;
        }
    }


    // extensionValue
    // =============================================================================================
    string PkiCertificate::extensionValue(PkiCertificate::Extension extension) const
    {
        switch(extension)
        {
            case Extension_SubjectAltName         : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_SubjectAltName).toUtf8());
            case Extension_BasicConstraints       : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_BasicConstraints).toUtf8());
            case Extension_NetscapeComment        : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_NetscapeComment).toUtf8());
            case Extension_SubjectKeyIdentifier   : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_SubjectKeyIdentifier).toUtf8());
            case Extension_AuthorityKeyIdentifier : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_AuthorityKeyIdentifier).toUtf8());
            case Extension_KeyUsage               : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_KeyUsage).toUtf8());
            case Extension_ExtendedKeyUsage       : return string(uaCert_.extensionValue(UaPkiCertificate::Extension_ExtendedKeyUsage).toUtf8());
            default                               : return string();
        }
    }


    // Get a DER encoded bytestring of the certificate
    // =============================================================================================
    ByteString PkiCertificate::toDER() const
    {
        UaByteArray uaByteArray = uaCert_.toDER();
        ByteString ret;
        ret.fromSdk(uaByteArray);
        return ret;
    }


    // Write a DER encoded bytestring of the certificate
    // =============================================================================================
    int PkiCertificate::toDERFile(const string& fileName) const
    {
        return uaCert_.toDERFile(fileName.c_str());
    }


    // Write a PEM encoded bytestring of the certificate
    // =============================================================================================
    int PkiCertificate::toPEMFile(const string& fileName) const
    {
        return uaCert_.toPEMFile(fileName.c_str());
    }


    // Get a thumb print
    // =============================================================================================
    ByteString PkiCertificate::thumbPrint() const
    {
        UaByteArray uaByteArray = uaCert_.thumbPrint();
        ByteString ret;
        ret.fromSdk(uaByteArray);
        return ret;
    }


    // Check if the certificate is null
    // =============================================================================================
    bool PkiCertificate::isNull() const
    {
        return uaCert_.isNull();
    }


    // Get a certificate from DER encoded data
    // =============================================================================================
    PkiCertificate PkiCertificate::fromDER(const ByteString& data)
    {
        UaByteArray ar;
        data.toSdk(ar);
        return PkiCertificate(UaPkiCertificate::fromDER(ar));
    }


    // Get a certificate from a DER encoded file
    // =============================================================================================
    PkiCertificate PkiCertificate::fromDERFile(const string& fileName)
    {
        return PkiCertificate(UaPkiCertificate::fromDERFile(fileName.c_str()));
    }


    // Get a certificate from a PEM encoded file
    // =============================================================================================
    PkiCertificate PkiCertificate::fromPEMFile(const string& fileName)
    {
        return PkiCertificate(UaPkiCertificate::fromPEMFile(fileName.c_str()));
    }


    // Get a string representation
    // =============================================================================================
    string PkiCertificate::toString(const string& indentation, size_t colon) const
    {
        stringstream ss;

        ss << indentation << " - isNull";
        ss << fillToPos(ss, colon);
        ss << ": " << (isNull() ? "true" : "false") << "\n";

        ss << indentation << " - publicKey";
        ss << fillToPos(ss, colon);
        ss << ": " << publicKey().toString() << "\n";

        ss << indentation << " - commonName";
        ss << fillToPos(ss, colon);
        ss << ": " << commonName() << "\n";

        ss << indentation << " - subject\n";
        ss << subject().toString(indentation + string("   "), colon) << "\n";

        ss << indentation << " - issuer\n";
        ss << issuer().toString(indentation + string("   "), colon) << "\n";

        ss << indentation << " - subjectNameHash";
        ss << fillToPos(ss, colon);
        ss << ": " << subjectNameHash() << "\n";

        ss << indentation << " - info\n";
        ss << info().toString(indentation + string("   "), colon) << "\n";

        ss << indentation << " - validFrom";
        ss << fillToPos(ss, colon);
        ss << ": " << validFrom().toString() << "\n";

        ss << indentation << " - validTo";
        ss << fillToPos(ss, colon);
        ss << ": " << validTo().toString() << "\n";

        ss << indentation << " - serialNumber";
        ss << fillToPos(ss, colon);
        ss << ": " << serialNumber() << "\n";

        ss << indentation << " - signatureTypeNID";
        ss << fillToPos(ss, colon);
        ss << ": " << signatureTypeNID() << "\n";

        ss << indentation << " - signatureTypeString";
        ss << fillToPos(ss, colon);
        ss << ": " << signatureTypeString() << "\n";

        ss << indentation << " - isValid";
        ss << fillToPos(ss, colon);
        ss << ": " << isValid() << "\n";

        ss << indentation << " - isSelfSigned";
        ss << fillToPos(ss, colon);
        ss << ": " << isSelfSigned();


        return ss.str();
    }


    // Get any errors
    // =============================================================================================
    std::vector<std::string> PkiCertificate::getErrors()
    {
        std::vector<std::string> ret;
        std::list<UaString> errors = uaCert_.getErrors();
        std::list<UaString>::const_iterator iter;
        for (iter = errors.begin(); iter != errors.end(); ++iter)
            ret.push_back(iter->toUtf8());
        return ret;
    }


    // operator==
    // =============================================================================================
    bool operator==(const PkiCertificate& object1, const PkiCertificate& object2)
    {
        return object1.thumbPrint() == object2.thumbPrint();
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const PkiCertificate& object1, const PkiCertificate& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const PkiCertificate& object1, const PkiCertificate& object2)
    {
        return object1.thumbPrint() < object2.thumbPrint();
    }

}
