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


#ifndef UAFC_SECURITYERRORS_H_
#define UAFC_SECURITYERRORS_H_


// STD
#include <vector>
#include <string>
// SDK
// UAF
#include "uaf/util/sdkstatus.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/errors/clienterror.h"
#include "uaf/client/clientexport.h"

namespace uafc
{


    class UAFC_EXPORT SecurityError : public uafc::ClientError
    {
    public:
        SecurityError()
        : uafc::ClientError("Security error")
        {}

        SecurityError(const std::string& description)
        : uafc::ClientError(description)
        {}
    };


    class UAFC_EXPORT PathNotExistsError : public uafc::ClientError
    {
    public:
        PathNotExistsError()
        : uafc::ClientError("Patn does not exist")
        {}


        PathNotExistsError(const std::string& path, const std::string& description="path")
        : uafc::ClientError(uaf::format("The %s '%s' does not exist",
                                        description.c_str(), path.c_str()))
        {}
    };


    class UAFC_EXPORT PathCreationError : public uafc::ClientError
    {
    public:
        PathCreationError()
        : uafc::ClientError("Patn could not be created")
        {}

        PathCreationError(const std::string& path, const std::string& description="path")
        : uafc::ClientError(uaf::format("The %s '%s' could not be created",
                                        description.c_str(), path.c_str()))
        {}
    };


    class UAFC_EXPORT SecuritySettingsMatchError : public uafc::SecurityError
    {
    public:
        SecuritySettingsMatchError()
        : uafc::SecurityError("No session security settings matched an endpoint")
        {}
    };

    class UAFC_EXPORT NoSecuritySettingsGivenError : public uafc::SecurityError
    {
    public:
        NoSecuritySettingsGivenError()
        : uafc::SecurityError("No session security settings were given")
        {}
    };




    class UAFC_EXPORT ServerDidNotProvideCertificateError : public uafc::SecurityError
    {
    public:
        ServerDidNotProvideCertificateError()
        : uafc::SecurityError("The server did not provide a certificate")
        {}
    };


    class UAFC_EXPORT ClientCertificateLoadingError : public uafc::SecurityError
    {
    public:
        ClientCertificateLoadingError()
        : uafc::SecurityError("Could not load the client certificate")
        {}

        ClientCertificateLoadingError(const uaf::SdkStatus& sdkStatus)
        : uafc::SecurityError(uaf::format("Could not load the client certificate: %s",
                                          sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}
        uaf::SdkStatus sdkStatus;
    };


    class UAFC_EXPORT OpenSSLStoreInitializationError : public uafc::SecurityError
    {
    public:
        OpenSSLStoreInitializationError()
        : uafc::SecurityError("Could not initialize the OpenSSL PKI Provider")
        {}

        OpenSSLStoreInitializationError(const uaf::SdkStatus& sdkStatus)
        : uafc::SecurityError(uaf::format("Could not initialize the OpenSSL PKI Provider: %s",
                                          sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}
        uaf::SdkStatus sdkStatus;
    };




    class UAFC_EXPORT ServerCertificateSavingError : public uafc::SecurityError
    {
    public:
        ServerCertificateSavingError()
        : uafc::SecurityError("Could not save the server certificate")
        {}

        ServerCertificateSavingError(const uaf::SdkStatus& sdkStatus)
        : uafc::SecurityError(uaf::format("Could not save the server certificate: %s",
                                          sdkStatus.toString().c_str())),
          sdkStatus(sdkStatus)
        {}
        uaf::SdkStatus sdkStatus;
    };


    class UAFC_EXPORT ServerCertificateRejectedByUserError : public uafc::SecurityError
    {
    public:
        ServerCertificateRejectedByUserError()
        : uafc::SecurityError("The server certificate was rejected by the user")
        {}
        uaf::SdkStatus sdkStatus;
    };

}

#endif /* UAFC_SECURITYERRORS_H_ */
