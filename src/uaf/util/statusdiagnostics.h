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

#ifndef UAF_STATUSDIAGNOSTICS_H_
#define UAF_STATUSDIAGNOSTICS_H_

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
#include "uaf/util/handles.h"



namespace uaf
{

    /*******************************************************************************************//**
    * A StatusDiagnostics object holds some more detailed diagnostic info for a Status object,
    * depending on the use case of this Status object
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT StatusDiagnostics : public uaf::Stringifiable
    {
    public:

        /**
         * Construct an empty status diagnostics object.
         */
        StatusDiagnostics();


        /**
         * Copy constructor.
         *
         * @param other     StatusDiagnostics to be copied.
         */
        StatusDiagnostics(const StatusDiagnostics& other);


        /**
         * Destructor.
         */
        ~StatusDiagnostics();


        /**
         * Assignment operator.
         *
         * @param other     StatusDiagnostics to be assigned.
         * @return          Reference to this instance.
         */
        StatusDiagnostics& operator=(const StatusDiagnostics& other);


        /**
         * Remove any diagnostic information.
         */
        void clear();


        /**
         * Is any diagnostic info given?
         */
        bool isEmpty() const;


        /**
         * Does the diagnostic object has notification handles?
         */
        bool hasNotificationHandles() const { return notificationHandles_ != 0; }


        /**
         * Get the notification handles (only relevant if hasNotificationHandles() is true).
         */
        std::vector<uaf::NotificationHandle> getNotificationHandles() const;


        /**
         * Set notification handles.
         */
        void setNotificationHandles(const std::vector<uaf::NotificationHandle>& handles);


        /**
         * Does the diagnostic object has description text?
         */
        bool hasDescription() const { return description_ != 0; }


        /**
         * Get the description (only relevant if hasDescription() is true).
         */
        std::string getDescription() const;


        /**
         * Set description text.
         */
        void setDescription(const std::string& desc);


        /**
         * Get a compact string representation.
         *
         * @return String representation.
         */
        std::string toCompactString() const;


        /**
         * Get a string representation.
         *
         * @return String representation.
         */
        std::string toString(const std::string& indent="", std::size_t colon=20) const;


        // comparison operators
        friend bool UAF_EXPORT operator==(
                const StatusDiagnostics& object1,
                const StatusDiagnostics& object2);
        friend bool UAF_EXPORT operator!=(
                const StatusDiagnostics& object1,
                const StatusDiagnostics& object2);
        friend bool UAF_EXPORT operator<(
                const StatusDiagnostics& object1,
                const StatusDiagnostics& object2);


    private:
        // the following objects can be stored by the diagnostic object:
        std::vector<uaf::NotificationHandle>* notificationHandles_;
        std::string* description_;
    };
}



#endif /* UAF_STATUSDIAGNOSTICS_H_ */
