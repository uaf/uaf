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

#ifndef UAFC_CLIENTSTATUSES_H
#define UAFC_CLIENTSTATUSES_H

// STD
#include <string>
#include <vector>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"



namespace uafc
{

    class UAFC_EXPORT DiscovererStatus
    {
    public:
        DiscovererStatus() {}
    };

    class UAFC_EXPORT ResolverStatus
    {
    public:
        ResolverStatus() {}
    };


    class UAFC_EXPORT ClientStatus
    {
    public:
        ClientStatus(const DiscovererStatus* const raisedByDiscoveryStatus)
        : raisedByDiscoveryStatus(raisedByDiscoveryStatus),
          raisedByResolverStatus(NULL)
        {}

        ClientStatus(const ResolverStatus* const raisedByResolverStatus)
        : raisedByDiscoveryStatus(NULL),
          raisedByResolverStatus(raisedByResolverStatus)
        {}

        ~ClientStatus()
        {
            if (raisedByDiscoveryStatus != NULL) delete raisedByDiscoveryStatus;
            if (raisedByResolverStatus != NULL) delete raisedByResolverStatus;
        }
        const DiscovererStatus* const raisedByDiscoveryStatus;
        const ResolverStatus* const raisedByResolverStatus;
    };
}



#endif /* UAFC_CLIENTSTATUSES_H */
