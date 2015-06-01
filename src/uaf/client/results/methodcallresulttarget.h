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

#ifndef UAF_METHODCALLRESULTTARGET_H_
#define UAF_METHODCALLRESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/util/variant.h"
#include "uaf/util/handles.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uaf
{


    /*******************************************************************************************//**
    * An uaf::MethodCallResultTarget is the "result target" of the corresponding
    * "request target" that specified the method to be called.
    *
    * It tells you whether or not the method was successfully called, the returned output parameters
    * of the method call, etc.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAF_EXPORT MethodCallResultTarget : public uaf::BaseSessionResultTarget
    {
    public:

        MethodCallResultTarget();


        /**
         * The resulting status of the method call.
         */
        uaf::Status status;


        /** The OPC UA status code reported by the server. */
        uaf::OpcUaStatusCode opcUaStatusCode;


        /**
         * The resulting output arguments of the method call.
         */
        std::vector<uaf::Variant> outputArguments;


        /**
         * The status for each input argument (derived from inputArgumentOpcUaStatusCodes).
         */
        std::vector<uaf::Status> inputArgumentStatuses;


        /**
         * The OPC UA status code for each input argument, as reported by the server.
         */
        std::vector<uaf::OpcUaStatusCode> inputArgumentOpcUaStatusCodes;


        /**
         * Get a string representation of the request.
         *
         * @return  String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=35) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(
                const MethodCallResultTarget& object1,
                const MethodCallResultTarget& object2);
        friend bool UAF_EXPORT operator!=(
                const MethodCallResultTarget& object1,
                const MethodCallResultTarget& object2);
        friend bool UAF_EXPORT operator<(
                const MethodCallResultTarget& object1,
                const MethodCallResultTarget& object2);
    };




}


#endif /* UAF_METHODCALLRESULTTARGET_H_ */
