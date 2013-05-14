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

#ifndef UAFC_WRITERESULTTARGET_H_
#define UAFC_WRITERESULTTARGET_H_



// STD
// SDK
// UAF
#include "uaf/util/status.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/clienthandles.h"
#include "uaf/client/results/basesessionresulttarget.h"



namespace uafc
{



    /*******************************************************************************************//**
    * An uafc::WriteResultTarget is the "result target" of the corresponding
    * "request target" that specified the attribute and node and data etc. to be written.
    *
    * It tells you if the data was written successfully.
    *
    * @ingroup ClientResults
    ***********************************************************************************************/
    class UAFC_EXPORT WriteResultTarget : public uafc::BaseSessionResultTarget
    {
    public:


        /**
         * Create an empty target.
         */
        WriteResultTarget();


        /** The status of the write target (good if the attribute could be written, bad if not). */
        uaf::Status status;


        /**
         * Get a string representation of the target.
         */
        std::string toString(const std::string& indent="", std::size_t colon=10) const;


    };

}


#endif /* UAFC_WRITERESULTTARGET_H_ */
