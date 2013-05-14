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

#ifndef UAFC_BASESESSIONREQUESTTARGET_H_
#define UAFC_BASESESSIONREQUESTTARGET_H_


// STD
#include <string>
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/resolution/resolvable.h"


namespace uafc
{

    /*******************************************************************************************//**
    * An uafc::BaseSessionRequestTarget is the superclass for "request targets" such as
    * uafc:ReadRequestTarget and uafc::WriteRequestTarget.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAFC_EXPORT BaseSessionRequestTarget :  private uafc::Resolvable,
                                                  public uaf::Stringifiable
    {
    public:


        /**
         * A friend function to get the server URI (via the private getServerUri method) from a
         * target.
         *
         * @param target    The target to get the server URI from.
         * @param serverUri Output argument: the resulting server URI.
         * @return          Good if a server URI could be extracted from the target, Bad if not.
         */
        friend uaf::Status getServerUriFromTarget(
                const BaseSessionRequestTarget& target,
                std::string& serverUri)
        {
            return target.getServerUri(serverUri);
        }


        /**
         * Pure virtual method: get the server URI from a target.
         *
         * This method must be implemented by all targets, so that the client can know to which
         * server the corresponding service call should be sent.
         *
         * @param serverUri Output parameter: the server URI to which the service call should be
         *                  sent.
         * @return          Good if a server URI could be extracted, Bad if not.
         */
        virtual uaf::Status getServerUri(std::string& serverUri) const = 0;
    };


}




#endif /* UAFC_BASESESSIONREQUESTTARGET_H_ */
