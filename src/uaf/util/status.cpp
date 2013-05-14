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

#include "uaf/util/status.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using uaf::statuscodes::StatusCode;



    // Constructor
    // =============================================================================================
    Status::Status()
    : statusCode_(uaf::statuscodes::Uncertain),
      opcUaStatusCode_(0),
      hasOpcUaStatusCode_(false)
    {}


    // Constructor
    // =============================================================================================
    Status::Status(uaf::statuscodes::StatusCode statusCode)
    : statusCode_(statusCode),
      opcUaStatusCode_(0),
      hasOpcUaStatusCode_(false)
    {}


    // Constructor
    // =============================================================================================
    Status::Status(uaf::statuscodes::StatusCode statusCode, const char* description, ...)
    : statusCode_(statusCode),
      opcUaStatusCode_(0),
      hasOpcUaStatusCode_(false)
    {
        va_list args;
        va_start(args, description);
        char buffer[512];
        vsprintf(buffer, description, args);
        va_end(args);
        description_ = buffer;
    }


    // Add diagnostic info
    // =============================================================================================
    void Status::addDiagnostic(const char* info, ...)
    {
        va_list args;
        va_start(args, info);
        char buffer[512];
        vsprintf(buffer, info, args);
        va_end(args);
        description_ = std::string(buffer) + " (" + description_ + ")";
    }



    // Set the status to Good with a message
    // =============================================================================================
    void Status::setGood(const char* description, ...)
    {
        va_list args;
        va_start(args, description);
        char buffer[512];
        vsprintf(buffer, description, args);
        va_end(args);
        description_        = buffer;
        statusCode_         = uaf::statuscodes::Good;
        hasOpcUaStatusCode_ = false;
    }


    // Set the status to Uncertain with a message
    // =============================================================================================
    void Status::setUncertain(const char* description, ...)
    {
        va_list args;
        va_start(args, description);
        char buffer[512];
        vsprintf(buffer, description, args);
        va_end(args);
        description_        = buffer;
        statusCode_         = uaf::statuscodes::Uncertain;
        hasOpcUaStatusCode_ = false;
    }


    // Make a summary from other Statuses
    // =============================================================================================
    void Status::summarize(const vector<Status>& statuses)
    {
        Status summary;
        size_t noOfGood      = 0;
        size_t noOfUncertain = 0;
        size_t noOfBad       = 0;
        for (vector<Status>::const_iterator it = statuses.begin(); it != statuses.end(); it++)
        {
            if      (it->isGood())      noOfGood++;
            else if (it->isUncertain()) noOfUncertain++;
            else if (it->isBad())       noOfBad++;
        }

        if (statuses.size() == 0)
            setStatus(statuscodes::UnexpectedError, "Could not summarize, no statuses given");
        else if (noOfGood == statuses.size())
            setGood();
        else if (noOfUncertain > 0 && noOfBad == 0)
            setStatus(statuscodes::Uncertain,
                      "#Good: %d, #Uncertain: %d, #Bad: 0", noOfGood, noOfUncertain);
        else
            setStatus(statuscodes::OtherError,
                      "#Good: %d, #Uncertain: %d, #Bad: %d", noOfGood, noOfUncertain, noOfBad);
    }



    // Get a string representation
    // =============================================================================================
    string Status::toString() const
    {
        string ret;

        if (description_.empty())
            ret = statuscodes::toString(statusCode_);
        else
            ret = description_;

        if (hasOpcUaStatusCode())
        {
            ret += string(" [OPC-UA:")
                   + UaStatusCode(opcUaStatusCode_).toString().toUtf8()
                   + std::string("]");
        }

        return ret;
    }


    // Set the status from a UAF status code + description
    // =============================================================================================
    void Status::setStatus(uaf::statuscodes::StatusCode statusCode, const char* description, ...)
    {
        va_list args;
        va_start(args, description);
        char buffer[512];
        vsprintf(buffer, description, args);
        va_end(args);
        description_        = buffer;
        statusCode_         = statusCode;
        hasOpcUaStatusCode_ = false;
    }


    // Set the status from a SDK status code + description
    // =============================================================================================
    void Status::fromSdk(uint32_t opcUaCode, const char* diagnostic, ...)
    {
        opcUaStatusCode_    = opcUaCode;
        hasOpcUaStatusCode_ = true;
        statusCode_         = uaf::statuscodes::fromSdkToUaf(opcUaCode);
        if (isBad())
        {
            va_list args;
            va_start(args, diagnostic);
            char buffer[512];
            vsprintf(buffer, diagnostic, args);
            va_end(args);
            description_ = buffer;
        }
    }


    // operator==
    // =============================================================================================
    bool operator==(const Status& object1, const Status& object2)
    {
        return object1.opcUaStatusCode_ == object2.opcUaStatusCode_
            && object1.hasOpcUaStatusCode_ == object2.hasOpcUaStatusCode_
            && object1.statusCode_ == object2.statusCode_
            && object1.description_ == object2.description_;
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const Status& object1, const Status& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const Status& object1, const Status& object2)
    {
        if (object1.hasOpcUaStatusCode_ != object2.hasOpcUaStatusCode_)
        {
            return object1.hasOpcUaStatusCode_ < object2.hasOpcUaStatusCode_;
        }
        else if (object1.opcUaStatusCode_ != object2.opcUaStatusCode_)
        {
            return object1.opcUaStatusCode_ < object2.opcUaStatusCode_;
        }
        else if (object1.statusCode_ != object2.statusCode_)
        {
            return object1.statusCode_ < object2.statusCode_;
        }
        else
        {
            return object1.description_ < object2.description_;
        }
    }


}
