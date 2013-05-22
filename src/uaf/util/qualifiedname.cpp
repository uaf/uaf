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

#include "uaf/util/qualifiedname.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    QualifiedName::QualifiedName()
    : nameSpaceIndex_(0),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    QualifiedName::QualifiedName(const string& name)
    : name_(name),
      nameSpaceIndex_(0),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    QualifiedName::QualifiedName(const string& name, uint16_t nameSpaceIndex)
    : name_(name),
      nameSpaceIndex_(nameSpaceIndex),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(false)
    {}


    // Constructor
    // =============================================================================================
    QualifiedName::QualifiedName(const string& name, const string& nameSpaceUri)
    : name_(name),
      nameSpaceIndex_(0),
      nameSpaceUri_(nameSpaceUri),
      nameSpaceIndexGiven_(false),
      nameSpaceUriGiven_(true)
    {}


    // Constructor
    // =============================================================================================
    QualifiedName::QualifiedName(
            const string&   name,
            const string&   nameSpaceUri,
            uint16_t        nameSpaceIndex)
    : name_(name),
      nameSpaceIndex_(nameSpaceIndex),
      nameSpaceUri_(nameSpaceUri),
      nameSpaceIndexGiven_(true),
      nameSpaceUriGiven_(true)
    {}


    // Is the qualified name NULL?
    // =============================================================================================
    bool QualifiedName::isNull() const
    {
        return nameSpaceIndexGiven_ || nameSpaceUriGiven_ || (!nameSpaceUri_.empty());
    }


    // Update a stack qualified name
    // =============================================================================================
    void QualifiedName::toSdk(OpcUa_QualifiedName *destination) const
    {
        if (!isNull())
            UaQualifiedName(name_.c_str(), nameSpaceIndex_).copyTo(destination);
    }


    // Update an SDK qualified name
    // =============================================================================================
    void QualifiedName::toSdk(UaQualifiedName& destination) const
    {
        if (!isNull())
            destination = UaQualifiedName(name_.c_str(), nameSpaceIndex_);
    }


    // Fill the qualified name
    // =============================================================================================
    void QualifiedName::fromSdk(const UaQualifiedName& destination)
    {

        if (destination.isNull())
        {
            name_ = "";
            nameSpaceIndex_ = 0;
            nameSpaceIndexGiven_ = false;
            nameSpaceUriGiven_ = false;

        }
        else
        {
            if (UaString(destination.name()).isNull())
                name_ = "";
            else
                name_ = string(UaString(destination.name()).toUtf8());

            nameSpaceIndex_ = destination.namespaceIndex();
            nameSpaceIndexGiven_ = true;
            nameSpaceUriGiven_ = false;
        }
    }


    // Fill the qualified name
    // =============================================================================================
    void QualifiedName::fromSdk(const UaQualifiedName& destination, const string& nameSpaceUri)
    {

        if (destination.isNull())
        {
            name_ = "";
            nameSpaceIndex_ = 0;
            nameSpaceIndexGiven_ = false;
            nameSpaceUriGiven_ = false;

        }
        else
        {
            if (UaString(destination.name()).isNull())
                name_ == "";
            else
                name_ = string(UaString(destination.name()).toUtf8());

            nameSpaceIndex_ = destination.namespaceIndex();
            nameSpaceIndexGiven_ = true;
            nameSpaceUri_ = nameSpaceUri;
            nameSpaceUriGiven_ = true;
        }
    }


    // Set the namespace index
    // =============================================================================================
    void QualifiedName::setNameSpaceIndex(uint16_t nameSpaceIndex)
    {
        nameSpaceIndex_      = nameSpaceIndex;
        nameSpaceIndexGiven_ = true;
    }


    // Set the namespace URI
    // =============================================================================================
    void QualifiedName::setNameSpaceUri(const std::string& nameSpaceUri)
    {
        nameSpaceUri_      = nameSpaceUri;
        nameSpaceUriGiven_ = true;
    }


    // Get a string representation
    // =============================================================================================
    std::string QualifiedName::toString() const
    {
        stringstream ss;

        if (isNull())
        {
            ss << "NULL";
        }
        else
        {
            ss << "Ns";

            if (nameSpaceIndexGiven_)
                ss << "=" << nameSpaceIndex_;

            if (nameSpaceUriGiven_)
                ss << "='" << nameSpaceUri_ << "'";

            if ( (!nameSpaceIndexGiven_) && (!nameSpaceUriGiven_) )
                ss << "=???";

            ss << "|'" << name_ << "'";
        }

        return ss.str();
    }


    // Comparison operator ==
    // =============================================================================================
    bool operator==(const QualifiedName& object1, const QualifiedName& object2)
    {
        return    object1.name_ == object2.name_
               && object1.nameSpaceIndex_ == object2.nameSpaceIndex_
               && object1.nameSpaceUri_ == object2.nameSpaceUri_;
    }


    // Comparison operator !=
    // =============================================================================================
    bool operator!=(const QualifiedName& object1, const QualifiedName& object2)
    {
        return !(object1 == object2);
    }


    // comparison operator <
    // =============================================================================================
    bool operator<(const QualifiedName& object1, const QualifiedName& object2)
    {
        if (object1.name_ != object2.name_)
            return object1.name_ < object2.name_;
        else if (object1.nameSpaceIndex_ != object2.nameSpaceIndex_)
            return object1.nameSpaceIndex_ < object2.nameSpaceIndex_;
        else
            return object1.nameSpaceUri_ < object2.nameSpaceUri_;
    }

}


