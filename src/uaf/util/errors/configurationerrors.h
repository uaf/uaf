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


#ifndef UAF_CONFIGURATIONERRORS_H_
#define UAF_CONFIGURATIONERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/uaferror.h"

namespace uaf
{

    class UAF_EXPORT ConfigurationError : public uaf::UafError
    {
    public:
        ConfigurationError()
        : uaf::UafError("configuration error")
        {}

        ConfigurationError(const std::string& description)
        : uaf::UafError(description)
        {}
    };




    class UAF_EXPORT CouldNotCreateCertificateTrustListLocationError : public uaf::ConfigurationError
    {
    public:
        CouldNotCreateCertificateTrustListLocationError()
        : uaf::ConfigurationError("The certificate trust list location could not be created")
        {}

        CouldNotCreateCertificateTrustListLocationError(const std::string& certificateTrustListLocation)
        : uaf::ConfigurationError(
                uaf::format("The certificate trust list location '%s' could not be created",
                            certificateTrustListLocation.c_str())),
          certificateTrustListLocation(certificateTrustListLocation)
        {}

        std::string certificateTrustListLocation;
    };

    class UAF_EXPORT CouldNotCreateCertificateRevocationListLocationError : public uaf::ConfigurationError
    {
    public:
        CouldNotCreateCertificateRevocationListLocationError()
        : uaf::ConfigurationError("The certificate trust list location could not be created")
        {}

        CouldNotCreateCertificateRevocationListLocationError(const std::string& certificateRevocationListLocation)
        : uaf::ConfigurationError(
                uaf::format("The certificate revocation list location '%s' could not be created",
                        certificateRevocationListLocation.c_str())),
          certificateRevocationListLocation(certificateRevocationListLocation)
        {}

        std::string certificateRevocationListLocation;
    };

    class UAF_EXPORT CouldNotCreateIssuersCertificateLocationError : public uaf::ConfigurationError
    {
    public:
        CouldNotCreateIssuersCertificateLocationError()
        : uaf::ConfigurationError("The issuers certificate location could not be created")
        {}

        CouldNotCreateIssuersCertificateLocationError(const std::string& issuersCertificatesLocation)
        : uaf::ConfigurationError(
                uaf::format("The issuers certificate location '%s' could not be created",
                        issuersCertificatesLocation.c_str())),
          issuersCertificatesLocation(issuersCertificatesLocation)
        {}

        std::string issuersCertificatesLocation;
    };

    class UAF_EXPORT CouldNotCreateIssuersRevocationListLocationError : public uaf::ConfigurationError
    {
    public:
        CouldNotCreateIssuersRevocationListLocationError()
        : uaf::ConfigurationError("The issuers revocation list location could not be created")
        {}

        CouldNotCreateIssuersRevocationListLocationError(const std::string& issuersRevocationListLocation)
        : uaf::ConfigurationError(
                uaf::format("The issuers revocation list location '%s' could not be created",
                        issuersRevocationListLocation.c_str())),
          issuersRevocationListLocation(issuersRevocationListLocation)
        {}

        std::string issuersRevocationListLocation;
    };

    class UAF_EXPORT CouldNotCreateClientPrivateKeyLocationError : public uaf::ConfigurationError
    {
    public:
        CouldNotCreateClientPrivateKeyLocationError()
        : uaf::ConfigurationError("The client private key location could not be created")
        {}

        CouldNotCreateClientPrivateKeyLocationError(const std::string& clientPrivateKey)
        : uaf::ConfigurationError(
                uaf::format("The client private key location for '%s' could not be created",
                            clientPrivateKey.c_str())),
          clientPrivateKey(clientPrivateKey)
        {}

        std::string clientPrivateKey;
    };

    class UAF_EXPORT CouldNotCreateClientCertificateLocationError : public uaf::ConfigurationError
    {
    public:
        CouldNotCreateClientCertificateLocationError()
        : uaf::ConfigurationError("The client certificate location could not be created")
        {}

        CouldNotCreateClientCertificateLocationError(const std::string& clientCertificate)
        : uaf::ConfigurationError(
                uaf::format("The client certificate location for '%s' could not be created",
                            clientCertificate.c_str())),
          clientCertificate(clientCertificate)
        {}

        std::string clientCertificate;
    };



}

#endif /* UAF_CONFIGURATIONERRORS_H_ */
