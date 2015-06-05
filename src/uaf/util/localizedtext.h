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

#ifndef UAF_LOCALIZEDTEXT_H_
#define UAF_LOCALIZEDTEXT_H_


// STD
#include <string>
// SDK
#include "uabase/ualocalizedtext.h"
// UAF
#include "uaf/util/util.h"


namespace uaf
{


    /*******************************************************************************************//**
     * A LocalizedText is text with a locale attached.
     *
     * @ingroup Util
     **********************************************************************************************/
    class UAF_EXPORT LocalizedText
    {
    public:

        /**
         * Construct an empty LocalizedText.
         */
        LocalizedText();


        /**
         * Construct a copy of another localized text.
         */
        LocalizedText(const LocalizedText& other);


        /**
         * Construct a LocalizedText with a locale and text.
         *
         * @param locale    The locale, e.g. "en" for English or "de" for German.
         * @param text      The text.
         */
        LocalizedText(const std::string& locale, const std::string& text);


        /**
         * Construct a LocalizedText from the OPC UA stack variable.
         *
         * @param opcUaLocalizedText    Stack variable.
         */
        LocalizedText(const OpcUa_LocalizedText& opcUaLocalizedText);


        /**
         * Get a string representation of the text part of the localized text.
         *
         * @return string representation of the text part.
         */
        std::string text() const;


        /**
         * Check if the localized text is NULL.
         */
        bool isNull() const { return uaLocalizedText_.isNull(); }


        /**
         * Get a string representation of the text part of the localized text.
         *
         * @return string representation of the locale part.
         */
        std::string locale() const;


        /**
         * Get a string representation of the text part of the localized text.
         *
         * @return string representation
         */
        std::string toString() const;


        /**
         * Get a string representation of the locale part + text part of the localized text.
         *
         * @return string representation
         */
        std::string toFullString() const;

        /**
         * Fill the localized text from an SDK object.
         */
        void fromSdk(const UaLocalizedText& uaLocalizedText);


        /**
         * Fill the SDK object.
         */
        void toSdk(UaLocalizedText& uaLocalizedText) const;


        /**
         * Fill the stack object.
         */
        void toSdk(OpcUa_LocalizedText* uaLocalizedText) const;


        // comparison operators
        friend UAF_EXPORT bool operator==(
                const LocalizedText& object1,
                const LocalizedText& object2);
        friend UAF_EXPORT bool operator!=(
                const LocalizedText& object1,
                const LocalizedText& object2);
        friend UAF_EXPORT bool operator<(
                const LocalizedText& object1,
                const LocalizedText& object2);


    private:
        UaLocalizedText uaLocalizedText_;
    };

}


#endif /* UAF_LOCALIZEDTEXT_H_ */
