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

#ifndef UAF_STATUS_H_
#define UAF_STATUS_H_

// STD
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
// SDK
#include "uabase/statuscode.h"
#include "uabase/uastring.h"
// UAF
#include "uaf/util/util.h"
#include "uaf/util/stringifiable.h"
#include "uaf/util/statuscodes.h"



namespace uaf
{

    /*******************************************************************************************//**
    * A Status object holds a UAF status code, a description and optionally an OPC UA status code.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT Status
    {
    public:


        /**
         * Construct an uninitialized (therefore Uncertain!) Status.
         */
        Status();


        /**
         * Construct a Status based on a UAF status code.
         *
         * @param statusCode  Status code as defined by the UAF.
         */
        Status(uaf::statuscodes::StatusCode statusCode);


        /**
         * Construct a Status based on a UAF status code and a description.
         *
         * @param statusCode  Status code as defined by the UAF.
         * @param description Message given by the UAF.
         */
        Status(uaf::statuscodes::StatusCode statusCode, const char* description, ...);


        /**
         * Change the Status based on the UAF status code and message.
         *
         * @param statusCode    Status code as defined by the UAF.
         * @param description   Additional information given by the UAF.
         */
        void setStatus(uaf::statuscodes::StatusCode statusCode, const char* description, ...);


        /**
         * Change the Status based on the UAF status code and message.
         *
         * @param statusCode    Status code as defined by the UAF.
         * @param description   Additional information given by the UAF.
         */
        void setStatus(uaf::statuscodes::StatusCode statusCode,
                       std::string                  description)
        { setStatus(statusCode, description.c_str()); }


        /**
         * Change the Status based on the UAF status code, message and OPC UA status code
         *
         * @param opcUaCode     Status code as defined by OPC UA.
         * @param diagnostic    Additional diagnostic in case of an error.
         */
        void fromSdk(uint32_t opcUaCode, const char* diagnostic, ...);


        /**
         * Change the Status based on the UAF status code and message.
         *
         * @param opcUaCode     Status code as defined by OPC UA.
         * @param diagnostic    Additional diagnostic in case of an error.
         */
        void fromSdk(uint32_t opcUaCode, const std::string& diagnostic)
        { fromSdk(opcUaCode, diagnostic.c_str()); }


        /**
         * Add diagnostic information.
         *
         *@param info  additional information given by the UAF
         */
        void addDiagnostic(const char* info, ...);


        /**
         * Add diagnostic information.
         *
         *@param msg  Additional information given by the UAF.
         */
        void addDiagnostic(const std::string& msg) { addDiagnostic(msg.c_str()); }


        /**
         * Set the OPC UA status code.
         *
         * @param opcUaStatusCode   The status code as defined by the OPC UA specs.
         */
        void setOpcUaStatusCode(uint32_t opcUaStatusCode) {
            opcUaStatusCode_    = opcUaStatusCode;
            statusCode_         = uaf::statuscodes::fromSdkToUaf(opcUaStatusCode); }


        /**
         * Does the status object have a specific OPC UA status code attached?
         *
         * With "specific" we mean anything more than just OpcUa_Good, OpcUa_Bad,
         * or OpcUa_Uncertain.
         *
         * @return  True if a specific OPC UA status code is present, false if not
         */
        bool hasSpecificOpcUaStatusCode() const;



        /**
         * Get the OPC UA status code.
         *
         * @return the OPC UA status code.
         */
        uint32_t opcUaStatusCode() const { return uint32_t(opcUaStatusCode_); }


        /**
         * Set the current status to Good.
         */
        void setGood() { setGood(""); }


        /**
         * Set the current status to Good.
         */
        void setGood(const char* description, ...);



        /**
         * Set the current status to Uncertain.
         */
        void setUncertain() { setUncertain(""); }


        /**
         * Set the current status to Uncertain.
         */
        void setUncertain(const char* description, ...);


        /**
         * Check if the status is Good.
         *
         * @return True if good, False if bad.
         */
        bool isGood() const { return statusCode_ == uaf::statuscodes::Good; }


        /**
         * Check if the status is not Good.
         *
         * @return True if not good, False if good.
         */
        bool isNotGood() const { return !isGood(); }


        /**
         * Check if the status is uncertain.
         *
         * @return True if uncertain, False if good or bad.
         */
        bool isUncertain() const { return statusCode_ == uaf::statuscodes::Uncertain; }


        /**
         * Check if the status is not uncertain.
         *
         * @return True if not uncertain, False if uncertain.
         */
        bool isNotUncertain() const { return !isUncertain(); }


        /**
         * Check if the status is Bad.
         *
         * @return True if bad, False if good.
         */
        bool isBad() const { return !(isGood() || isUncertain()); }


        /**
         * Check if the status is not bad.
         *
         * @return True if not bad, False if bad.
         */
        bool isNotBad() const { return !isBad(); }


        /**
         * Get the UAF status code.
         *
         * @return The currently assigned status code (as defined by the UAF).
         */
        uaf::statuscodes::StatusCode statusCode() const { return statusCode_; }


        /**
         * Get the UAF status code name.
         *
         * @return The name of the currently assigned status code (as defined by the UAF).
         */
        std::string statusCodeName() const { return uaf::statuscodes::toString(statusCode_); }


        /**
         * Make a "summary" of other statuses.
         *
         * Bad is dominant to Uncertain, which is dominant to Good.
         * So if any Bad status is present, the summary will be "Bad".
         * If no Bad statuses are present but any Uncertain status is present, the summary will be
         * Uncertain.
         * And if only Good statuses are present, the summary will be Good.
         *
         * @param statuses  The statuses to summarize.
         */
        void summarize(const std::vector<uaf::Status>& statuses);


        /**
         * Get a string representation.
         *
         * @return a string representation of the status
         */
        virtual std::string toString() const;



        // comparison operators
        friend UAF_EXPORT bool operator==(const Status& object1, const Status& object2);
        friend UAF_EXPORT bool operator!=(const Status& object1, const Status& object2);
        friend UAF_EXPORT bool operator<(const Status& object1, const Status& object2);


    private:

        /** The UAF status code (so defined by the UAF and not by the OPC UA standard!). */
        uaf::statuscodes::StatusCode    statusCode_;
        /** The description of the status. */
        std::string                     description_;
        /** The OPC UA status code. */
        OpcUa_StatusCode                opcUaStatusCode_;
    };

}





#endif /* UAF_STATUS_H_ */
