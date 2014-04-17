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

#ifndef UAFC_READSETTINGS_H_
#define UAFC_READSETTINGS_H_



// STD
// SDK
// UAF
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/servicesettings.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::ReadSettings object holds the service settings that are particular
    * for the Read service.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT ReadSettings : public uafc::ServiceSettings
    {
    public:

        /**
         * Create default Read settings.
         *
         * Defaults are:
         *  - maxAgeSec : 0.0
         */
        ReadSettings();


        /**
         * Virtual destructor.
         */
        virtual ~ReadSettings() {}


        /** The maximum age (in seconds) that the attribute that is read, should have.
          * When maxAgeSec = 0.0, the server is forced to fetch the most recent value from its
          * data source. */
        double maxAgeSec;


        /**
         * Get a string representation of the settings.
         *
         * @return  String representation
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=18) const;

    };

}



#endif /* UAFC_READSETTINGS_H_ */
