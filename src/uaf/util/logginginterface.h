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

#ifndef UAF_LOGGINGINTERFACE_H_
#define UAF_LOGGINGINTERFACE_H_


// STD
// SDK
// UAF
#include "uaf/util/util.h"
#include "uaf/util/logmessage.h"


namespace uaf
{


    /*******************************************************************************************//**
    * The uaf::LoggingInterface must be implemented to handle log messages.
    *
    * @ingroup Util
    ***********************************************************************************************/
    class UAF_EXPORT LoggingInterface
    {
    public:
        /**
         * Virtual destructor.
         */
        virtual ~LoggingInterface() {}


        /**
         * Override this method to handle log messages.
         */
        virtual void logMessageReceived(const uaf::LogMessage& message) {}

    };
}


#endif /* UAF_LOGGINGINTERFACE_H_ */
