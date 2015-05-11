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

#ifndef UAF_PKICERTIFICATE_H_
#define UAF_PKICERTIFICATE_H_


// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uapki/uapkicertificate.h"
// UAF
#include "uaf/util/pkipublickey.h"
#include "uaf/util/pkiprivatekey.h"
#include "uaf/util/pkicertificateinfo.h"
#include "uaf/util/pkirsakeypair.h"
#include "uaf/util/pkiidentity.h"
#include "uaf/util/datetime.h"

namespace uaf
{

    /*******************************************************************************************//**
    * A PkiCertificate holds an X.509 certificate.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT PkiCertificate
    {
    public:

        enum Action
        {
            Action_Reject            = 0,
            Action_AcceptTemporarily = 1,
            Action_AcceptPermanently = 2
        };

        enum Extension
        {
            Extension_SubjectAltName          = UaPkiCertificate::Extension_SubjectAltName,
            Extension_BasicConstraints        = UaPkiCertificate::Extension_BasicConstraints,
            Extension_NetscapeComment         = UaPkiCertificate::Extension_NetscapeComment,
            Extension_SubjectKeyIdentifier    = UaPkiCertificate::Extension_SubjectKeyIdentifier,
            Extension_AuthorityKeyIdentifier  = UaPkiCertificate::Extension_AuthorityKeyIdentifier,
            Extension_KeyUsage                = UaPkiCertificate::Extension_KeyUsage,
            Extension_ExtendedKeyUsage        = UaPkiCertificate::Extension_ExtendedKeyUsage
        };


        /**
         * Create an empty certificate.
         */
        PkiCertificate();

        /**
         * Create a certificate.
         */
        PkiCertificate(
                const uaf::PkiCertificateInfo& info,
                const uaf::PkiIdentity& subject,
                const uaf::PkiPublicKey& subjectPublicKey,
                const uaf::PkiIdentity& issuer,
                const uaf::PkiPrivateKey& issuerPrivateKey);

        /**
         * Create a certificate based on an SDK instance.
         */
        PkiCertificate(const UaPkiCertificate& uaCert);

        /** Check if the certificate is empty. */
        bool isNull() const;

        /** Check if the signature is not expired. */
        bool isValid() const;

        /** Check if the certificate is self-signed (i.e. if the subject and issuer are the same). */
        bool isSelfSigned() const;

        /** Get the public key of the certificate. */
        uaf::PkiPublicKey publicKey() const;

        /**
         * Convenience method to get the common name of the subject
         * (equals PkiCertificate.subject().commonName).
         */
        std::string commonName() const;

        /** Get the identity of the subject of the certificate. */
        uaf::PkiIdentity subject() const;

        /** Get the identity of the issuer of the certificate. */
        uaf::PkiIdentity issuer() const;

        /** Get the hash of the subject name. */
        unsigned long subjectNameHash() const;

        /**
         * Get information from the X509v3 extension "subjectAltName" (SAN). It allows various
         * values to be associated with a security certificate.
         * Warning: validTime will not be filled, use validFrom() and validTo() instead!
         */
        uaf::PkiCertificateInfo info() const;

        /** Get the start date from when the certificate is valid. */
        uaf::DateTime validFrom() const;

        /** Get the end date until when the certificate is valid. */
        uaf::DateTime validTo() const;

        /**
         * Get the X.509 serial number (a unique number issued by the certificate issuer),
         * as a hexadecimal string.
         */
        std::string serialNumber() const;

        /**
         * Get the numerical ID (NID) of the signature algorithm type.
         */
        int signatureTypeNID() const;

        /** Get a string representation of the numerical ID (NID) of the signature algorithm type. */
        std::string signatureTypeString() const;

        /** Check if the certificate has the given extension. */
        bool hasExtension(PkiCertificate::Extension extension) const;

        /** Get the value of the given extension if the extension is present. */
        std::string extensionValue(PkiCertificate::Extension extension) const;

        /** Get a DER encoded bytestring of the certificate. */
        uaf::ByteString toDER() const;

        /** Write the certificate to a DER-encoded file with the given filename.
         *  An error code is returned (0 if success).*/
        int toDERFile(const std::string& fileName) const;

        /** Write the certificate to a PEM-encoded file with the given filename.
         *  An error code is returned (0 if success).*/
        int toPEMFile(const std::string& fileName) const;

        /** Get a SHA1 thumb print (finger print) of the certficate. It is a short sequence of
         * bytes used to identify a certificate efficiently. */
        uaf::ByteString thumbPrint() const;

        /** Static method to get a certificate from a DER encoded bytestring. */
        static uaf::PkiCertificate fromDER(const uaf::ByteString& data);

        /** Static method to get a certificate from a DER encoded file. */
        static uaf::PkiCertificate fromDERFile(const std::string& fileName);

        /** Static method to get a certificate from a PEM encoded file. */
        static uaf::PkiCertificate fromPEMFile(const std::string& fileName);

        /** Get a string representation of the certificate. */
        std::string toString(const std::string& indent="", std::size_t colon=23) const;

        /** Get a list of errors. */
        std::vector<std::string> getErrors();

        // comparison operators
        friend bool UAF_EXPORT operator==(const PkiCertificate& object1, const PkiCertificate& object2);
        friend bool UAF_EXPORT operator!=(const PkiCertificate& object1, const PkiCertificate& object2);
        friend bool UAF_EXPORT operator<(const PkiCertificate& object1, const PkiCertificate& object2);

    private:
        UaPkiCertificate uaCert_;
    };


}



#endif /* UAF_PKICERTIFICATE_H_ */
