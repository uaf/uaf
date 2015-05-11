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

#ifndef UAF_SUBSCRIPTIONREQUESTTARGET_H_
#define UAF_SUBSCRIPTIONREQUESTTARGET_H_


// STD
#include <string>
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/requests/basesessionrequesttarget.h"


namespace uaf
{

    /*******************************************************************************************//**
    * An uaf::BaseSubscriptionRequestTarget is the superclass for "request targets" that need to
    * be handled at the subscription level, such as uaf::CreateMonitoredDataRequestTarget.
    *
    * @ingroup ClientRequests
    ***********************************************************************************************/
    class UAF_EXPORT BaseSubscriptionRequestTarget : public uaf::BaseSessionRequestTarget
    {
    public:


        /**
         * Overridden pure virtual method (see uaf::BaseSessionRequestTarget::getServerUri).
         */
        virtual uaf::Status getServerUri(std::string& serverUri) const = 0;
    };


}




#endif /* UAF_SUBSCRIPTIONREQUESTTARGET_H_ */
