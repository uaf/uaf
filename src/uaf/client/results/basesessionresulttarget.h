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

#ifndef UAFC_BASESESSIONRESULTTARGET_H_
#define UAFC_BASESESSIONRESULTTARGET_H_


// STD
#include <string>
// SDK
// UAF
#include "uaf/util/stringifiable.h"
#include "uaf/client/clientexport.h"
#include "uaf/util/handles.h"


namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::BaseSessionResultTarget is the superclass of the result targets that are handled
    * at the session level.
    *
    * This is the superclass of an uafc::ReadResultTarget, uafc::WriteResultTarget,
    * uafc::MethodCallResultTarget, ... since these targets are all handled at the Session level
    * and not at the Subscription level.
    *
    * Result targets are part of a Result, and correspond one-to-one to the Request targets of a
    * Request.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT BaseSessionResultTarget : public uaf::Stringifiable
    {
    public:


        /**
         * Default constructor.
         */
        BaseSessionResultTarget()
        : clientConnectionId(0)
        {}


        /** The ClientConnectionId of the session that was used to handle this target. */
        uaf::ClientConnectionId clientConnectionId;

    };

}




#endif /* UAFC_BASESESSIONRESULTTARGET_H_ */
