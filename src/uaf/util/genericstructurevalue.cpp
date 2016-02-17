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

#include "uaf/util/genericstructurevalue.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    GenericStructureValue::GenericStructureValue()
    {}


    // Constructor
    // =============================================================================================
    GenericStructureValue::GenericStructureValue(
    		const uaf::ExtensionObject& extensionObject,
    		const uaf::StructureDefinition& definition)
    {
    	UaExtensionObject uaExt;
    	UaStructureDefinition uaDef;
    	extensionObject.toSdk(uaExt);
    	definition.toSdk(uaDef);
    	uaGenericStructureValue_ = UaGenericStructureValue(uaExt, uaDef);
    }


    // Clear the value
    // =============================================================================================
    void GenericStructureValue::clear()
    {
        uaGenericStructureValue_.clear();
    }



    // Set a generic value
	// =============================================================================================
	SdkStatus GenericStructureValue::setGenericValue(
		const ByteString&          data,
		Encoding                   encoding,
		const StructureDefinition& structureDefinition)
	{
		UaByteString uaData;
		UaStructureDefinition uaDef;
		UaAbstractGenericValue::Encoding uaEnc;
		data.toSdk(uaData);
		if (encoding == GenericStructureValue::Binary)
			uaEnc = UaAbstractGenericValue::Encoding_Binary;

		structureDefinition.toSdk(uaDef);
		return SdkStatus( uaGenericStructureValue_.setGenericValue(uaData, uaEnc, uaDef) );
	}

    // Set a generic value
	// =============================================================================================
	SdkStatus GenericStructureValue::setGenericValue(
		const ExtensionObject&     extensionObject,
		const StructureDefinition& structureDefinition)
	{
		UaExtensionObject uaExt;
		UaStructureDefinition uaDef;
		extensionObject.toSdk(uaExt);
		structureDefinition.toSdk(uaDef);
		return SdkStatus( uaGenericStructureValue_.setGenericValue(uaExt, uaDef) );
	}

    // Set a field
	// =============================================================================================
	SdkStatus GenericStructureValue::setField(
			const std::string& fieldName,
			const uaf::Variant& value)
	{
		UaString uaFieldName(fieldName.c_str());
		UaVariant uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericStructureValue_.setField(uaFieldName, uaValue) );
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericStructureValue::setField(
			int index,
			const uaf::Variant& value)
	{
		UaVariant uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericStructureValue_.setField(index, uaValue) );
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericStructureValue::setField(
			const std::string& fieldName,
			const uaf::GenericStructureValue& value)
	{
		UaString uaFieldName(fieldName.c_str());
		UaGenericStructureValue uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericStructureValue_.setField(uaFieldName, uaValue) );
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericStructureValue::setField(
			int index,
			const uaf::GenericStructureValue& value)
	{
		UaGenericStructureValue uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericStructureValue_.setField(index, uaValue) );
	}

	// Get the value
	// =============================================================================================
	Variant GenericStructureValue::value(const std::string& fieldName) const
	{
		UaString uaFieldName(fieldName.c_str());
		Variant ret;
		ret.fromSdk( uaGenericStructureValue_.value(uaFieldName) );
		return ret;
	}

	// Get the value
	// =============================================================================================
	Variant GenericStructureValue::value(int i) const
	{
		Variant ret;
		ret.fromSdk( uaGenericStructureValue_.value(i) );
		return ret;
	}


	// Get the definition
	// =============================================================================================
	StructureDefinition GenericStructureValue::definition() const
	{
		StructureDefinition ret;
		ret.fromSdk( uaGenericStructureValue_.definition() );
		return ret;
	}

    // Set a definition
	// =============================================================================================
	void GenericStructureValue::setDefinition(
			const StructureDefinition& definition,
			bool createDefaultValues)
	{
		UaStructureDefinition uaDef;
		definition.toSdk(uaDef);
		uaGenericStructureValue_.setDefinition(uaDef, createDefaultValues);
	}

	// Is a field set?
	// =============================================================================================
	bool GenericStructureValue::isFieldSet(const std::string& fieldName) const
	{
		UaString uaFieldName(fieldName.c_str());
		return uaGenericStructureValue_.isFieldSet(uaFieldName);
	}

	// Is a field set?
	// =============================================================================================
	bool GenericStructureValue::isFieldSet(int i) const
	{
		return uaGenericStructureValue_.isFieldSet(i);
	}

	// Unset a field
	// =============================================================================================
	SdkStatus GenericStructureValue::unsetField(const std::string& fieldName)
	{
		UaString uaFieldName(fieldName.c_str());
		return SdkStatus( uaGenericStructureValue_.unsetField(uaFieldName) );
	}

	//  Unset a field
	// =============================================================================================
	SdkStatus GenericStructureValue::unsetField(int i)
	{
		return SdkStatus( uaGenericStructureValue_.unsetField(i) );
	}

	//  Convert to an extension object
	// =============================================================================================
	void GenericStructureValue::toExtensionObject(
			ExtensionObject& extensionObject,
			Encoding valueEncoding) const
	{
		UaExtensionObject uaExt;
		if (valueEncoding == GenericStructureValue::Binary)
			uaGenericStructureValue_.toExtensionObject(uaExt, UaAbstractGenericValue::Encoding_Binary);

		extensionObject.fromSdk(uaExt);
	}


    // Get a string representation
    // =============================================================================================
    std::string GenericStructureValue::toString(const string& indent, size_t colon) const
    {
		stringstream ss;

		StructureDefinition def(definition());

		ss << indent << " - definition\n";
		ss << def.toString(indent + "   ", colon) << "\n";

		ss << indent << " - fields";

		if (def.isNull())
		{
			ss << fillToPos(ss, colon);
			ss << ": (No fields to display, definition is NULL)";
		}
		else
		{
			if (def.childrenCount() > 0)
			{
				for (int i=0; i<def.childrenCount(); i++)
				{
					ss << '\n';
					ss << indent << "   - field(" << i << ")";
					ss << fillToPos(ss, colon) << ": ";
					if (isFieldSet(i))
					{
						ss << value(i).toString();
					}
					else
					{
						ss << "(This field is not set!)";
					}
				}
			}
			else
			{
				ss << fillToPos(ss, colon);
				ss << ": (No fields to display: definition has 0 children)";
			}
		}


		return ss.str();
    }




}


