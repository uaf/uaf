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

#include "uaf/util/genericstructurearray.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    GenericStructureArray::GenericStructureArray()
    : uaGenericStructureArray_(UaGenericStructureArray(UaStructureDefinition()))
    {}


    // Constructor
    // =============================================================================================
    GenericStructureArray::GenericStructureArray(const uaf::StructureDefinition& definition)
    : uaGenericStructureArray_(UaStructureDefinition())
    {

    	UaStructureDefinition uaDef;
    	definition.toSdk(uaDef);
    	uaGenericStructureArray_ = UaGenericStructureArray(uaDef);
    }


    // Clear the value
    // =============================================================================================
    void GenericStructureArray::clear()
    {
        uaGenericStructureArray_.clear();
    }

    // Create a number of structures
    // =============================================================================================
    void GenericStructureArray::create(uint32_t length)
    {
        uaGenericStructureArray_.create(length);
    }

    // Get the array size
    // =============================================================================================
    uint32_t GenericStructureArray::length() const
    {
        return uaGenericStructureArray_.length();
    }

	// Get the definition
	// =============================================================================================
	StructureDefinition GenericStructureArray::definition() const
	{
		StructureDefinition ret;
		ret.fromSdk( uaGenericStructureArray_.definition() );
		return ret;
	}

    // Get an item
    // =============================================================================================
	uaf::GenericStructureValue  GenericStructureArray::__getitem__(uint32_t index) const
    {
		uaf::GenericStructureValue ret;
		ret.fromSdk(uaGenericStructureArray_[index]);
		return ret;
    }

    // Set an item
    // =============================================================================================
	void GenericStructureArray::__setitem__(
			uint32_t index,
			const uaf::GenericStructureValue& value)
    {
		value.toSdk(uaGenericStructureArray_[index]);
    }


    // Get a string representation
    // =============================================================================================
    std::string GenericStructureArray::toString(const string& indent, size_t colon) const
    {
		stringstream ss;

		StructureDefinition def(definition());

		ss << indent << " - definition\n";
		ss << def.toString(indent + "   ", colon) << "\n";

		ss << indent << " - array length";
		ss << fillToPos(ss, colon);
		ss << ": " << length() << "\n";

		ss << indent << " - array items";

		if (length() == 0)
		{
			ss << fillToPos(ss, colon);
			ss << ": []";
		}
		else
		{
			for (uint32_t i=0; i<length(); i++)
			{
				ss << '\n';
				ss << indent << "   - item " << i << "\n";
				ss << __getitem__(i).toString(indent + string("   "), colon);
			}
		}


		return ss.str();
    }




}


