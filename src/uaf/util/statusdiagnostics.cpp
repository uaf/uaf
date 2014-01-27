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

#include "uaf/util/statusdiagnostics.h"


namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;
    using std::vector;
    using std::size_t;
    using uaf::ClientHandle;


    // Constructor
    // =============================================================================================
    StatusDiagnostics::StatusDiagnostics()
    : clientHandles_(0),
      description_(0)
    {}


    // Copy constructor
    // =============================================================================================
    StatusDiagnostics::StatusDiagnostics(const StatusDiagnostics& other)
    {
        if (other.hasClientHandles())
            clientHandles_ = new vector<ClientHandle>(*other.clientHandles_);
        else
            clientHandles_ = 0;

        if (other.hasDescription())
            description_ = new string(*other.description_);
        else
            description_ = 0;
    }


    // Assignment operator
    // =============================================================================================
    StatusDiagnostics& StatusDiagnostics::operator=(const StatusDiagnostics& other)
    {
        // protect for self-assignment
        if (&other != this)
        {
            clear();

            if (other.hasClientHandles())
                clientHandles_ = new vector<ClientHandle>(*other.clientHandles_);

            if (other.hasDescription())
                description_ = new string(*other.description_);

        }

        return *this;
    }


    // Destructor
    // =============================================================================================
    StatusDiagnostics::~StatusDiagnostics()
    {
        clear();
    }


    // Clear the internal variables
    // =============================================================================================
    void StatusDiagnostics::clear()
    {
        if (hasClientHandles())
        {
            delete clientHandles_;
            clientHandles_ = 0;
        }

        if (hasDescription())
        {
            delete description_;
            description_ = 0;
        }
    }


    // Is any diagnostic info given?
    // =============================================================================================
    bool StatusDiagnostics::isEmpty() const
    {
        return !(   hasClientHandles()
                 || hasDescription());
    }


    // Get the client handles
    // =============================================================================================
    vector<ClientHandle> StatusDiagnostics::getClientHandles() const
    {
        if (hasClientHandles())
            return *clientHandles_;
        else
            return vector<ClientHandle>();
    }


    // Set client handles
    // =============================================================================================
    void StatusDiagnostics::setClientHandles(const vector<ClientHandle>& handles)
    {
        clientHandles_ = new vector<ClientHandle>(handles);
    }


    // Get the additional description
    // =============================================================================================
    string StatusDiagnostics::getDescription() const
    {
        if (hasDescription())
            return *description_;
        else
            return string();
    }


    // Set additional description
    // =============================================================================================
    void StatusDiagnostics::setDescription(const string& desc)
    {
        description_ = new string(desc);
    }


    // Get a compact string representation
    // =============================================================================================
    string StatusDiagnostics::toCompactString() const
    {
        stringstream ss;
        bool empty = true; // is the stringstream empty?

        if (hasDescription())
        {
            ss << getDescription();
            empty = false;
        }
        if (hasClientHandles())
        {
            // add a space if text has been added before
            if (!empty) ss << " ";

            ss << "ClientHandles_=[";
            for(size_t i = 0; i < clientHandles_->size(); i++)
            {
                ss << clientHandles_->operator [](i);
                // add a comma unless we're printing the last handle
                if (i != clientHandles_->size() - 1)
                    ss << ",";
            }
            ss << "]";
            empty = false;
        }

        return ss.str();
    }

    // Get a string representation
    // =============================================================================================
    string StatusDiagnostics::toString(const string& indent, size_t colon) const
    {
        stringstream ss;

        bool textAdded = false;

        if (hasDescription())
        {
            ss << indent << " - description";
            ss << fillToPos(ss, colon);
            ss << ": "<< description_->c_str();

            textAdded = true;
        }
        if (hasClientHandles())
        {
            if (textAdded) ss << "\n";

            ss << indent << " - clientHandles[]";
            if (clientHandles_->size() == 0)
            {
                ss << fillToPos(ss, colon);
                ss << ": []";
            }
            else
            {
                for (size_t i = 0; i < clientHandles_->size(); i++)
                {
                    ss << "\n";
                    ss << indent << "    - clientHandles[" << i << "] = ";
                    ss << clientHandles_->operator [](i);
                }
            }

            textAdded = true;
        }

        return ss.str();
    }


    // operator==
    // =============================================================================================
    bool operator==(const StatusDiagnostics& object1, const StatusDiagnostics& object2)
    {
        if (object1.isEmpty() && object2.isEmpty())
            return true;
        else
        {
            if (object1.getDescription() != object2.getDescription())
                return false;
            else
                return object1.getClientHandles() == object2.getClientHandles();
        }
    }


    // operator!=
    // =============================================================================================
    bool operator!=(const StatusDiagnostics& object1, const StatusDiagnostics& object2)
    {
        return !(object1 == object2);
    }


    // operator<
    // =============================================================================================
    bool operator<(const StatusDiagnostics& object1, const StatusDiagnostics& object2)
    {
        if (object1.isEmpty() && object2.isEmpty())
            return false;
        else
        {
            if (object1.getDescription() != object2.getDescription())
                return object1.getDescription() < object2.getDescription();
            else
                return object1.getClientHandles() < object2.getClientHandles();
        }
    }


}
