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

#ifndef UAF_QUALIFIEDNAME_H_
#define UAF_QUALIFIEDNAME_H_


// STD
#include <string>
#include <sstream>
#include <stdint.h>
// SDK
#include "uabase/uaqualifiedname.h"
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /*******************************************************************************************//**
    * A QualifiedName consists of a name and a corresponding namespace index or namespace URI.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT QualifiedName
    {
    public:
        /**
         * Construct an empty qualified name (with namespace index 0).
         */
        QualifiedName();


        /**
         * Construct an incomplete qualified name (without namespace information!)
         *
         * @param name              Name part of the qualified name.
         */
        QualifiedName(const std::string& name);


        /**
         * Construct a qualified name based on a name and a namespace index.
         *
         * @param name              Name part of the qualified name.
         * @param nameSpaceIndex    Namespace index corresponding to the name.
         */
        QualifiedName(
                const std::string&  name,
                uint16_t            nameSpaceIndex);


        /**
         * Construct a qualified name based on a name and a namespace URI.
         *
         * @param name              Name part of the qualified name.
         * @param nameSpaceUri      Namespace URI corresponding to the name.
         */
        QualifiedName(
                const std::string&  name,
                const std::string&  nameSpaceUri);


        /**
         * Construct a qualified name based on a name and a namespace URI and a namespace index.
         *
         * @param name              Name part of the qualified name.
         * @param nameSpaceUri      Namespace URI corresponding to the name.
         * @param nameSpaceIndex    Namespace index corresponding to the name.
         */
        QualifiedName(
                const std::string&  name,
                const std::string&  nameSpaceUri,
                uint16_t            nameSpaceIndex);


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        virtual std::string toString() const;


        /**
         * Change the name.
         *
         * @param name  The new name.
         */
        void setName(const std::string& name) { name_ = name; }


        /**
         * Change the namespace URI.
         *
         * @param nameSpaceUri      New namespace URI.
         */
        void setNameSpaceUri(const std::string& nameSpaceUri);


        /**
         * Change the namespace index.
         *
         * @param nameSpaceIndex    New namespace index.
         */
        void setNameSpaceIndex(uint16_t nameSpaceIndex);


        /**
         * Is a namespace index provided?
         *
         * @return True if a namespace index has been provided.
         */
        bool hasNameSpaceIndex() const { return nameSpaceIndexGiven_; }


        /**
         * Is a non-empty namespace URI provided?
         *
         * @return True if a non-empty namespace URI has been provided.
         */
        bool hasNameSpaceUri()   const { return nameSpaceUriGiven_ && (!nameSpaceUri_.empty()); }


        /**
         * Get the name.
         *
         * @return  The name part of the qualified name.
         */
        const std::string& name() const { return name_; };


        /**
         * Get the namespace URI (only do this in case hasNameSpaceUri equals True).
         *
         * @return  the namespace URI.
         */
        const std::string& nameSpaceUri() const { return nameSpaceUri_; };


        /**
         * Get the namespace index (only do this in case hasNameSpaceIndex equals True).
         *
         * @return  the namespace index.
         */
        uint16_t nameSpaceIndex() const { return nameSpaceIndex_; };


        /**
         * Update a stack OpcUa_QualifiedName instance.
         *
         * @param destination   OpcUa_QualifiedName instance (as defined by the stack) to be
         *                      modified.
         */
        void toSdk(OpcUa_QualifiedName* destination) const;


        /**
         * Update an SDK UaQualifiedName instance.
         *
         * @param destination   UaQualifiedName instance (as defined by the SDK) to be modified.
         */
        void toSdk(UaQualifiedName& destination) const;


        /**
         * Update the qualified name with the contents of an SDK UaQualifiedName instance.
         *
         * @param source    UaQualifiedName instance (as defined by the SDK) to fetch the contents.
         */
        void fromSdk(const UaQualifiedName& source);


        // comparison operators
        friend UAF_EXPORT bool operator==(const QualifiedName& object1, const QualifiedName& object2);
        friend UAF_EXPORT bool operator!=(const QualifiedName& object1, const QualifiedName& object2);
        friend UAF_EXPORT bool operator<(const QualifiedName& object1, const QualifiedName& object2);

    private:
        // name part of the qualified name
        std::string  name_;
        // namespace URI
        std::string  nameSpaceUri_;
        // namespace index
        uint16_t     nameSpaceIndex_;
        // true if a namespace URI is given
        bool         nameSpaceUriGiven_;
        // true if a namespace index is given
        bool         nameSpaceIndexGiven_;


    };
}




#endif /* UAF_QUALIFIEDNAME_H_ */
