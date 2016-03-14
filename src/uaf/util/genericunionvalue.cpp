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
#include "uaf/util/genericunionvalue.h"

namespace uaf
{
    using namespace uaf;
    using std::string;
    using std::stringstream;


    // Constructor
    // =============================================================================================
    GenericUnionValue::GenericUnionValue()
    {}


    // Constructor
    // =============================================================================================
    GenericUnionValue::GenericUnionValue(
    		const uaf::ExtensionObject& extensionObject,
    		const uaf::StructureDefinition& definition)
    {
    	UaExtensionObject uaExt;
    	UaStructureDefinition uaDef;
    	extensionObject.toSdk(uaExt);
    	definition.toSdk(uaDef);
    	uaGenericUnionValue_ = UaGenericUnionValue(uaExt, uaDef);
    }


    // Clear the value
    // =============================================================================================
    void GenericUnionValue::clear()
    {
        uaGenericUnionValue_.clear();
    }



    // Set a generic value
	// =============================================================================================
	SdkStatus GenericUnionValue::setGenericUnion(
		const ByteString&          data,
		Encoding                   encoding,
		const StructureDefinition& structureDefinition)
	{
		UaByteString uaData;
		UaStructureDefinition uaDef;
		UaAbstractGenericValue::Encoding uaEnc = static_cast<UaAbstractGenericValue::Encoding>(encoding);
		data.toSdk(uaData);
		structureDefinition.toSdk(uaDef);
		return SdkStatus( uaGenericUnionValue_.setGenericUnion(uaData, uaEnc, uaDef) );
	}

    // Set a generic value
	// =============================================================================================
	SdkStatus GenericUnionValue::setGenericUnion(
		const ExtensionObject&     extensionObject,
		const StructureDefinition& structureDefinition)
	{
		UaExtensionObject uaExt;
		UaStructureDefinition uaDef;
		extensionObject.toSdk(uaExt);
		structureDefinition.toSdk(uaDef);
		return SdkStatus( uaGenericUnionValue_.setGenericUnion(uaExt, uaDef) );
	}

    // Set a field
	// =============================================================================================
	SdkStatus GenericUnionValue::setValue(
			const std::string& fieldName,
			const uaf::Variant& value)
	{
		UaString uaFieldName(fieldName.c_str());
		UaVariant uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericUnionValue_.setValue(uaFieldName, uaValue) );
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericUnionValue::setValue(
			int index,
			const uaf::Variant& value)
	{
		UaVariant uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericUnionValue_.setValue(index, uaValue) );
	}


    // Set a field
    // =============================================================================================
    SdkStatus GenericUnionValue::setValue(
            const std::string& fieldName,
            const uaf::GenericStructureValue& value)
    {
        UaString uaFieldName(fieldName.c_str());
        UaGenericStructureValue uaValue;
        value.toSdk(uaValue);
        return SdkStatus( uaGenericUnionValue_.setValue(uaFieldName, uaValue) );
    }


    // Set a field
    // =============================================================================================
    SdkStatus GenericUnionValue::setValue(
            int index,
            const uaf::GenericStructureValue& value)
    {
        UaGenericStructureValue uaValue;
        value.toSdk(uaValue);
        return SdkStatus( uaGenericUnionValue_.setValue(index, uaValue) );
    }


    // Set a field
    // =============================================================================================
    SdkStatus GenericUnionValue::setValue(
            const std::string& fieldName,
            const std::vector<uaf::GenericStructureValue>& array)
    {
        UaString uaFieldName(fieldName.c_str());
        int index;
        bool found;
        for(index=0; index<uaGenericUnionValue_.definition().childrenCount() && !found; index++)
        {
            if (uaGenericUnionValue_.definition().child(index).name() == uaFieldName)
                found = true;
        }

        if (found)
        {
            return setValue(index, array);
        }
        else
        {
            return SdkStatus(OpcUa_BadInvalidArgument);
        }
    }


    // Set a field
    // =============================================================================================
    SdkStatus GenericUnionValue::setValue(
            int index,
            const std::vector<uaf::GenericStructureValue>& array)
    {
        UaGenericStructureArray uaArray(uaGenericUnionValue_.definition().child(index).structureDefinition());
        uaArray.create(array.size());
        for (std::size_t i = 0; i < array.size(); i++)
        {
            array[i].toSdk(uaArray[i]);
        }
        return SdkStatus( uaGenericUnionValue_.setValue(index, uaArray) );
    }

    // Set a field
	// =============================================================================================
	SdkStatus GenericUnionValue::setValue(
			const std::string& fieldName,
			const uaf::GenericUnionValue& value)
	{
		UaString uaFieldName(fieldName.c_str());
		UaGenericUnionValue uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericUnionValue_.setValue(uaFieldName, uaValue) );
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericUnionValue::setValue(
			int index,
			const uaf::GenericUnionValue& value)
	{
		UaGenericUnionValue uaValue;
		value.toSdk(uaValue);
		return SdkStatus( uaGenericUnionValue_.setValue(index, uaValue) );
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericUnionValue::setValue(
			const std::string& fieldName,
			const std::vector<uaf::GenericUnionValue>& array)
	{
		UaString uaFieldName(fieldName.c_str());
		int index;
		bool found;
		for(index=0; index<uaGenericUnionValue_.definition().childrenCount() && !found; index++)
		{
			if (uaGenericUnionValue_.definition().child(index).name() == uaFieldName)
				found = true;
		}

		if (found)
		{
			return setValue(index, array);
		}
		else
		{
			return SdkStatus(OpcUa_BadInvalidArgument);
		}
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericUnionValue::setValue(
			int index,
			const std::vector<uaf::GenericUnionValue>& array)
	{
		UaGenericUnionArray uaArray(uaGenericUnionValue_.definition().child(index).structureDefinition());
		uaArray.create(array.size());
		for (std::size_t i = 0; i < array.size(); i++)
		{
			array[i].toSdk(uaArray[i]);
		}
		return SdkStatus( uaGenericUnionValue_.setValue(index, uaArray) );
	}


	// Get the value
	// =============================================================================================
	Variant GenericUnionValue::value() const
	{
		Variant ret;
		ret.fromSdk( uaGenericUnionValue_.value() );
		return ret;
	}




    // Get the generic structure value
    // =============================================================================================
    GenericStructureValue GenericUnionValue::genericStructure(uint32_t* opcUaStatusCode) const
    {
        GenericStructureValue ret;
        OpcUa_StatusCode* pUaCode = NULL;
        ret.fromSdk( uaGenericUnionValue_.genericStructure(pUaCode) );
        opcUaStatusCode = static_cast<uint32_t*>(pUaCode);
        return ret;
    }



    // Get the generic structure value
    // =============================================================================================
    std::vector<GenericStructureValue> GenericUnionValue::genericStructureArray(uint32_t* opcUaStatusCode) const
    {
        OpcUa_StatusCode* pUaCode = NULL;
        UaGenericStructureArray uaArr = uaGenericUnionValue_.genericStructureArray(pUaCode);
        opcUaStatusCode = static_cast<uint32_t*>(pUaCode);
        std::vector<GenericStructureValue> ret(uaArr.length());
        for (uint32_t i=0; i<uaArr.length(); i++)
        {
            ret[i].fromSdk(uaArr[i]);
        }
        return ret;
    }




	// Get the generic structure value
	// =============================================================================================
	GenericUnionValue GenericUnionValue::genericUnion(uint32_t* opcUaStatusCode) const
	{
		GenericUnionValue ret;
        OpcUa_StatusCode* pUaCode = NULL;
		ret.fromSdk( uaGenericUnionValue_.genericUnion(pUaCode) );
        opcUaStatusCode = static_cast<uint32_t*>(pUaCode);
		return ret;
	}



	// Get the generic structure value
	// =============================================================================================
	std::vector<GenericUnionValue> GenericUnionValue::genericUnionArray(uint32_t* opcUaStatusCode) const
	{
        OpcUa_StatusCode* pUaCode = NULL;
		UaGenericUnionArray uaArr = uaGenericUnionValue_.genericUnionArray(pUaCode);
        opcUaStatusCode = static_cast<uint32_t*>(pUaCode);
		std::vector<GenericUnionValue> ret(uaArr.length());
		for (uint32_t i=0; i<uaArr.length(); i++)
		{
			ret[i].fromSdk(uaArr[i]);
		}
		return ret;
	}


	// Get the definition
	// =============================================================================================
	StructureDefinition GenericUnionValue::definition() const
	{
		StructureDefinition ret;
		ret.fromSdk( uaGenericUnionValue_.definition() );
		return ret;
	}

	// get the index of the currently used field
	// =============================================================================================
    int GenericUnionValue::switchValue() const
    {
    	return uaGenericUnionValue_.switchValue();
    }

	// get the currently used field
	// =============================================================================================
    uaf::StructureField GenericUnionValue::field() const
    {
    	uaf::StructureField ret;
    	UaStructureField uaField = uaGenericUnionValue_.field();
    	ret.fromSdk(uaField);
    	return ret;
    }


	//  Convert to an extension object
	// =============================================================================================
	void GenericUnionValue::toExtensionObject(
			ExtensionObject& extensionObject,
			Encoding valueEncoding) const
	{
		UaExtensionObject uaExt;
		UaAbstractGenericValue::Encoding uaEnc = static_cast<UaAbstractGenericValue::Encoding>(valueEncoding);
		uaGenericUnionValue_.toExtensionObject(uaExt, uaEnc);
		extensionObject.fromSdk(uaExt);
	}


    // Get a string representation
    // =============================================================================================
    std::string GenericUnionValue::toString(const string& indent, size_t colon) const
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
		        ss << indent << " - switchValue";
	            ss << fillToPos(ss, colon);
	            ss << ": " << switchValue() << "\n";

                ss << indent << " - field\n";
                ss << field().toString(indent + "   ", colon) << "\n";

                ss << indent << " - value\n";
                ss << value().toString(indent + "   ", colon) << "\n";
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


