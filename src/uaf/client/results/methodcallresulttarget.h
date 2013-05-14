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

#ifndef UAFC_METHODCALLRESULTTARGET_H_
#define UAFC_METHODCALLRESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/variant.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clienthandles.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::MethodCallResultTarget is the "result target" of the corresponding
    * "request target" that specified the method to be called.
    *
    * It tells you whether or not the method was successfully called, the returned output parameters
    * of the method call, etc.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT MethodCallResultTarget : public uafc::BaseSessionResultTarget
    {
    public:

        /**
         * The resulting status of the method call.
         */
        uaf::Status status;


        /**
         * The resulting output arguments of the method call.
         */
        std::vector<uaf::Variant> outputArguments;


        /**
         * The status for each input argument.
         */
        std::vector<uaf::Status> inputArgumentStatuses;


        /**
         * Get a string representation of the request.
         *
         * @return  String representation.
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=22) const;
    };




}


#endif /* UAFC_METHODCALLRESULTTARGET_H_ */
