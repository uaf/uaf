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

#ifndef UAFC_CLIENTINFORMATION_H_
#define UAFC_CLIENTINFORMATION_H_

// STD
#include <string>
#include <sstream>
// SDK
#include "uaclient/uaclientsdk.h"
// UAF
#include "uaf/util/stringifiable.h"
#include "uaf/util/handles.h"
#include "uaf/util/datetime.h"
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/sessions/sessionstates.h"

namespace uafc
{

    /*******************************************************************************************//**
    * A ClientInformation object contains information about the client such as whether or not
    * a client certificate is loaded.
    *
    * @ingroup ClientSessions
    ***********************************************************************************************/
    class UAFC_EXPORT ClientInformation
    {
    public:


        /**
         * Create a default ClientInformation object.
         */
        ClientInformation();


        /** The status of the last connection attempt. */
        uaf::Status                         lastConnectionAttemptStatus;

        /**
         * Get a string representation of the information.
         */
        std::string toString(const std::string& indent="", std::size_t colon=31) const;


        // comparison operators
        friend UAFC_EXPORT bool operator==(
                const SessionInformation& object1,
                const SessionInformation& object2);
        friend UAFC_EXPORT bool operator!=(
                const SessionInformation& object1,
                const SessionInformation& object2);
        friend UAFC_EXPORT bool operator<(
                const SessionInformation& object1,
                const SessionInformation& object2);
    };


}


#endif /* UAFC_CLIENTINFORMATION_H_ */
