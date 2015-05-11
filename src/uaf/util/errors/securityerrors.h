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


#ifndef UAF_SECURITYERRORS_H_
#define UAF_SECURITYERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/errors/uaferror.h"
#include "uaf/util/errors/invalidrequesterror.h"
#include "uaf/util/util.h"

namespace uaf
{


    class UAF_EXPORT SecurityError : public uaf::InvalidRequestError
    {
    public:
        SecurityError()
        : uaf::InvalidRequestError("Security error")
        {}

        SecurityError(const std::string& description)
        : uaf::InvalidRequestError(description)
        {}
    };



    class UAF_EXPORT SecuritySettingsMatchError : public uaf::SecurityError
    {
    public:
        SecuritySettingsMatchError()
        : uaf::SecurityError("No session security settings matched an endpoint")
        {}
    };

    class UAF_EXPORT NoSecuritySettingsGivenError : public uaf::SecurityError
    {
    public:
        NoSecuritySettingsGivenError()
        : uaf::SecurityError("No session security settings were given")
        {}
    };




    class UAF_EXPORT ServerDidNotProvideCertificateError : public uaf::SecurityError
    {
    public:
        ServerDidNotProvideCertificateError()
        : uaf::SecurityError("The server did not provide a certificate")
        {}
    };


    class UAF_EXPORT ClientCertificateLoadingError : public uaf::SecurityError
    {
    public:
        ClientCertificateLoadingError()
        : uaf::SecurityError("Could not load the client certificate")
        {}

        ClientCertificateLoadingError(const uaf::SdkStatus& sdkStatus)
        : uaf::SecurityError(uaf::format("Could not load the client certificate: %s",
                                          sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}
        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT OpenSSLStoreInitializationError : public uaf::SecurityError
    {
    public:
        OpenSSLStoreInitializationError()
        : uaf::SecurityError("Could not initialize the OpenSSL PKI Provider")
        {}

        OpenSSLStoreInitializationError(const uaf::SdkStatus& sdkStatus)
        : uaf::SecurityError(uaf::format("Could not initialize the OpenSSL PKI Provider: %s",
                                          sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}
        uaf::SdkStatus sdkStatus;
    };




    class UAF_EXPORT ServerCertificateSavingError : public uaf::SecurityError
    {
    public:
        ServerCertificateSavingError()
        : uaf::SecurityError("Could not save the server certificate")
        {}

        ServerCertificateSavingError(const uaf::SdkStatus& sdkStatus)
        : uaf::SecurityError(uaf::format("Could not save the server certificate: %s",
                                          sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}
        uaf::SdkStatus sdkStatus;
    };


    class UAF_EXPORT ServerCertificateRejectedByUserError : public uaf::SecurityError
    {
    public:
        ServerCertificateRejectedByUserError()
        : uaf::SecurityError("The server certificate was rejected by the user")
        {}
    };


    class UAF_EXPORT EmptyUserCertificateError : public uaf::SecurityError
    {
    public:
        EmptyUserCertificateError()
        : uaf::SecurityError("The user certificate is empty")
        {}
        EmptyUserCertificateError(const std::string& certificate)
        : uaf::SecurityError(uaf::format("The user certificate %s is empty", certificate.c_str())),
          certificate(certificate)
        {}
        std::string certificate;
    };

    class UAF_EXPORT InvalidPrivateKeyError : public uaf::SecurityError
    {
    public:
        InvalidPrivateKeyError()
        : uaf::SecurityError("The private key is invalid")
        {}
        InvalidPrivateKeyError(const std::string& privateKey)
        : uaf::SecurityError(uaf::format("The private key %s is invalid", privateKey.c_str())),
          privateKey(privateKey)
        {}
        std::string privateKey;
    };



    class UAF_EXPORT SessionSecuritySettingsDontMatchEndpointError : public uaf::SecurityError
    {
    public:
        SessionSecuritySettingsDontMatchEndpointError()
        : uaf::SecurityError("The session security settings dont match the endpoint")
        {}
    };



}

#endif /* UAF_SECURITYERRORS_H_ */
