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

#include "uaf/client/clientstatus.h"


namespace uafc
{
    using namespace uaf;
    using namespace uafc;
    using std::string;


    // get a string representation
    // =============================================================================================
    string ClientStatus::toString() const
    {
        if      (!raisedBy_DiscoveryError.isNull())                         return raisedBy_DiscoveryError.description;
        else if (!raisedBy_FindServersError.isNull())                       return raisedBy_FindServersError.description;
        else if (!raisedBy_NoParallelFindServersAllowedError.isNull())      return raisedBy_NoParallelFindServersAllowedError.description;
        else if (!raisedBy_EmptyUrlError.isNull())                          return raisedBy_EmptyUrlError.description;
        else if (!raisedBy_NoDiscoveryUrlsFoundError.isNull())              return raisedBy_NoDiscoveryUrlsFoundError.description;
        else if (!raisedBy_ServerCertificateRejectedByUserError.isNull())   return raisedBy_ServerCertificateRejectedByUserError.description;
        else if (!raisedBy_ServerCertificateSavingError.isNull())           return raisedBy_ServerCertificateSavingError.description;
        else if (!raisedBy_OpenSSLStoreInitializationError.isNull())        return raisedBy_OpenSSLStoreInitializationError.description;
        else if (!raisedBy_ClientCertificateLoadingError.isNull())          return raisedBy_ClientCertificateLoadingError.description;
        else if (!raisedBy_ServerDidNotProvideCertificateError.isNull())    return raisedBy_ServerDidNotProvideCertificateError.description;
        else if (!raisedBy_CouldNotConnectError.isNull())                   return raisedBy_CouldNotConnectError.description;
        else if (!raisedBy_PathNotExistsError.isNull())                     return raisedBy_PathNotExistsError.description;
        else if (!raisedBy_NoSecuritySettingsGivenError.isNull())           return raisedBy_NoSecuritySettingsGivenError.description;
        else if (!raisedBy_PathCreationError.isNull())                      return raisedBy_PathCreationError.description;
        else if (!raisedBy_SecuritySettingsMatchError.isNull())             return raisedBy_SecuritySettingsMatchError.description;
        else if (isUncertain())
            return "Uncertain";
        else if (isGood())
            return "Good";
        else if (isBad())
            return "Bad";
        else
            return "UNKNOWN!";
    }

    // operator==
    // =============================================================================================
    bool operator==(const ClientStatus& object1, const ClientStatus& object2)
    {
        return    object1.state_ == object2.state_
               && object1.toString() == object2.toString();
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const ClientStatus& object1, const ClientStatus& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const ClientStatus& object1, const ClientStatus& object2)
    {
        if (object1.state_ != object2.state_)
            return object1.state_ < object2.state_;
        else
            return object1.toString() < object2.toString();
    }
}

