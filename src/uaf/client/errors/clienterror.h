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

#ifndef UAFC_CLIENTERROR_H
#define UAFC_CLIENTERROR_H

// STD
#include <string>
// SDK
#include "uabase/statuscode.h"
// UAF
#include "uaf/client/clientexport.h"



namespace uafc
{

    class UAFC_EXPORT ClientError
    {
    public:
        ClientError()
        : description(""), isNull_(true)
        {}
        ClientError(const std::string& description)
        : description(description), isNull_(false)
        {}
        std::string description;
        bool isNull() const { return isNull_; }

        std::string toString() const { return description; }

    private:
        bool isNull_;
    };


}



#endif /* UAFC_CLIENTERROR_H */
