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

#ifndef UAFC_BROWSESETTINGS_H_
#define UAFC_BROWSESETTINGS_H_



// STD
// SDK
// UAF
#include "uaf/util/viewdescription.h"
#include "uaf/client/clientexport.h"
#include "uaf/client/settings/baseservicesettings.h"



namespace uafc
{


    /*******************************************************************************************//**
    * An uafc::MethodCallSettings object holds the service settings that are particular
    * for the MethodCall service.
    *
    * @ingroup ClientSettings
    ***********************************************************************************************/
    class UAFC_EXPORT BrowseSettings : public uafc::BaseServiceSettings
    {
    public:

        /**
         * Create default Browse settings.
         *
         * Defaults are:
         *  - maxAgeSec : 0.0
         */
        BrowseSettings();


        /** The maximum number of references to return. Default is 0, which means that the client
         *  is not imposing a limitation. */
        uint32_t maxReferencesToReturn;

        /** Attribute that specifies the View to browse. Don't touch if you want to browse the
         *  whole address space without restrictions. */
        uaf::ViewDescription view;

        /** A number defined by the UAF, to indicate how many times the UAF may automatically
         *  call BrowseNext. Default = 0, which means that there will be no BrowseNext being called
         *  automatically. But if you put this value to e.g. 10, then you can very easily browse
         *  large address spaces since you don't have to call BrowseNext manually every time
         *  (and there's no risk of ending up in an endless loop since the UAF client will stop
         *  processing the request after 10 BrowseNext calls). */
        uint32_t maxAutoBrowseNext;


        /**
         * Get a string representation of the settings.
         *
         * @return  String representation
         */
        virtual std::string toString(const std::string& indent="", std::size_t colon=26) const;

    };

}



#endif /* UAFC_BROWSESETTINGS_H_ */
