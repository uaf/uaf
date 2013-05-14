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

#ifndef UAF_SECURITY_H_
#define UAF_SECURITY_H_


// STD
#include <string>
#include <stdint.h>
// SDK
// UAF
#include "uaf/util/util.h"


namespace uaf
{

    /*******************************************************************************************//**
    * An OpenSslStoreSettings instance contains the settings for an OpenSSL store.
    *
    * @ingroup Util
    ***********************************************************************************************/
    struct UAF_EXPORT OpenSslStoreSettings
    {
        std::string trustListLocation;
        std::string revocationListLocation;
        std::string certificate;
        std::string privateKey;
    };


    /*******************************************************************************************//**
    * A CertificateSettings instance contains the settings for an OpenSSL certificate.
    *
    * @ingroup Util
    ***********************************************************************************************/
    // copied from the SDK (UaPkiIdentity)
    struct UAF_EXPORT CertificateSettings
    {
        std::string commonName;
        std::string organization;
        std::string organizationUnit;
        std::string locality;
        std::string state;
        std::string country;
        int32_t     validTime;
    };


}



#endif /* UAF_SECURITY_H_ */
