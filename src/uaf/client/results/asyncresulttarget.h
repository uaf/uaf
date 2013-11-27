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

#ifndef UAFC_ASYNCRESULTTARGET_H_
#define UAFC_ASYNCRESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"
#include "uaf/util/handles.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * A uafc::AsyncResultTarget is part of a uafc::AsyncXXXXXResult (with XXXXXX being Read,
    * Write, CrateMonitoredData, ...) and contains the immediate result of the corresponding
    * asynchronous request target.
    *
    * The AsyncXXXXXXResult is returned immediately to the client, so it only contains the immediate
    * result of the request, which is just a Status really. This status indicates if the target
    * could be sent to the server. The real result of the asynchronous request will be given to
    * the client afterwards, via a callback mechanism.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT AsyncResultTarget : public uafc::BaseSessionResultTarget
    {
    public:


        /**
         * The result status of the corresponding asynchronous request target. This status
         * tells you only if the target could be sent to the server. So it will be Good if there
         * could be a Session established, if the addresses of the target could be resolved, ...
         */
        uaf::Status status;


        /**
         * Get a string representation of the request.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=10) const;
    };




}


#endif /* UAFC_ASYNCRESULTTARGET_H_ */
