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

#ifndef UAFC_CLIENTSTATUS_H
#define UAFC_CLIENTSTATUS_H

// STD
#include <string>
#include <vector>
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/errors/discoveryerrors.h"
#include "uaf/client/errors/securityerrors.h"



namespace uafc
{

    class UAFC_EXPORT ClientStatus
    {
    public:

        enum State {
            Uncertain = 0,
            Good      = 1,
            Bad       = 2
        };

        ClientStatus()
        : state_(Uncertain)
        {}

        ClientStatus(State state)
        : state_(state)
        {}

        ClientStatus(const uafc::DiscoveryError& error)
        : raisedBy_DiscoveryError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::FindServersError& error)
        : raisedBy_FindServersError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::EmptyUrlError& error)
        : raisedBy_EmptyUrlError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::NoParallelFindServersAllowedError& error)
        : raisedBy_NoParallelFindServersAllowedError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::NoDiscoveryUrlsFoundError& error)
        : raisedBy_NoDiscoveryUrlsFoundError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::ServerCertificateRejectedByUserError& error)
        : raisedBy_ServerCertificateRejectedByUserError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::ServerCertificateSavingError& error)
        : raisedBy_ServerCertificateSavingError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::OpenSSLStoreInitializationError& error)
        : raisedBy_OpenSSLStoreInitializationError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::ClientCertificateLoadingError& error)
        : raisedBy_ClientCertificateLoadingError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::ServerDidNotProvideCertificateError& error)
        : raisedBy_ServerDidNotProvideCertificateError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::CouldNotConnectError& error)
        : raisedBy_CouldNotConnectError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::PathNotExistsError& error)
        : raisedBy_PathNotExistsError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::NoSecuritySettingsGivenError& error)
        : raisedBy_NoSecuritySettingsGivenError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::PathCreationError& error)
        : raisedBy_PathCreationError(error),
          state_(Bad)
        {}

        ClientStatus(const uafc::SecuritySettingsMatchError& error)
        : raisedBy_SecuritySettingsMatchError(error),
          state_(Bad)
        {}


        bool isUncertain()      const { return state_ == Uncertain;   }
        bool isGood()           const { return state_ == Good;        }
        bool isBad()            const { return state_ == Bad;         }

        bool isNotUncertain()   const { return state_ != Uncertain;   }
        bool isNotGood()        const { return state_ != Good;        }
        bool isNotBad()         const { return state_ != Bad;         }

        uafc::DiscoveryError                        raisedBy_DiscoveryError;
        uafc::FindServersError                      raisedBy_FindServersError;
        uafc::NoParallelFindServersAllowedError     raisedBy_NoParallelFindServersAllowedError;
        uafc::EmptyUrlError                         raisedBy_EmptyUrlError;
        uafc::NoDiscoveryUrlsFoundError             raisedBy_NoDiscoveryUrlsFoundError;
        uafc::ServerCertificateRejectedByUserError  raisedBy_ServerCertificateRejectedByUserError;
        uafc::ServerCertificateSavingError          raisedBy_ServerCertificateSavingError;
        uafc::OpenSSLStoreInitializationError       raisedBy_OpenSSLStoreInitializationError;
        uafc::ClientCertificateLoadingError         raisedBy_ClientCertificateLoadingError;
        uafc::ServerDidNotProvideCertificateError   raisedBy_ServerDidNotProvideCertificateError;
        uafc::CouldNotConnectError                  raisedBy_CouldNotConnectError;
        uafc::PathNotExistsError                    raisedBy_PathNotExistsError;
        uafc::NoSecuritySettingsGivenError          raisedBy_NoSecuritySettingsGivenError;
        uafc::PathCreationError                     raisedBy_PathCreationError;
        uafc::SecuritySettingsMatchError            raisedBy_SecuritySettingsMatchError;


        std::string toString() const
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


        // comparison operators
        friend UAFC_EXPORT bool operator==(const ClientStatus& object1, const ClientStatus& object2);
        friend UAFC_EXPORT bool operator!=(const ClientStatus& object1, const ClientStatus& object2);
        friend UAFC_EXPORT bool operator<(const ClientStatus& object1, const ClientStatus& object2);

    private:

        State state_;
    };
}



#endif /* UAFC_CLIENTSTATUS_H */
