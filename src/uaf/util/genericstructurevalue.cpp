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
		UaAbstractGenericValue::Encoding uaEnc = static_cast<UaAbstractGenericValue::Encoding>(encoding);
		data.toSdk(uaData);
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


    // Set a field
	// =============================================================================================
	SdkStatus GenericStructureValue::setField(
			const std::string& fieldName,
			const std::vector<uaf::GenericStructureValue>& array)
	{
		UaString uaFieldName(fieldName.c_str());
		int index;
		bool found;
		for(index=0; index<uaGenericStructureValue_.definition().childrenCount() && !found; index++)
		{
			if (uaGenericStructureValue_.definition().child(index).name() == uaFieldName)
				found = true;
		}

		if (found)
		{
			return setField(index, array);
		}
		else
		{
			return SdkStatus(OpcUa_BadInvalidArgument);
		}
	}


    // Set a field
	// =============================================================================================
	SdkStatus GenericStructureValue::setField(
			int index,
			const std::vector<uaf::GenericStructureValue>& array)
	{
		UaGenericStructureArray uaArray(uaGenericStructureValue_.definition().child(index).structureDefinition());
		uaArray.create(array.size());
		for (std::size_t i = 0; i < array.size(); i++)
		{
			array[i].toSdk(uaArray[i]);
		}
		return SdkStatus( uaGenericStructureValue_.setField(index, uaArray) );
	}


	// Get the value
	// =============================================================================================
	Variant GenericStructureValue::value(const std::string& fieldName, uint32_t* opcUaStatusCode) const
	{
		UaString uaFieldName(fieldName.c_str());
		Variant ret;
        OpcUa_StatusCode uaCode;
		ret.fromSdk( uaGenericStructureValue_.value(uaFieldName, &uaCode) );
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
		return ret;
	}


	// Get the value
	// =============================================================================================
	Variant GenericStructureValue::value(int i, uint32_t* opcUaStatusCode) const
	{
		Variant ret;
        OpcUa_StatusCode uaCode;
		ret.fromSdk( uaGenericStructureValue_.value(i, &uaCode) );
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
		return ret;
	}


	// Get the generic structure value
	// =============================================================================================
	GenericStructureValue GenericStructureValue::genericStructure(const std::string& fieldName, uint32_t* opcUaStatusCode) const
	{
		UaString uaFieldName(fieldName.c_str());
		GenericStructureValue ret;
        OpcUa_StatusCode uaCode;
		ret.fromSdk( uaGenericStructureValue_.genericStructure(uaFieldName, &uaCode) );
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
        return ret;
		return ret;
	}


	// Get the generic structure value
	// =============================================================================================
	GenericStructureValue GenericStructureValue::genericStructure(int i, uint32_t* opcUaStatusCode) const
	{
		GenericStructureValue ret;
        OpcUa_StatusCode uaCode;
		ret.fromSdk( uaGenericStructureValue_.genericStructure(i, &uaCode) );
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
		return ret;
	}


	// Get the generic structure value
	// =============================================================================================
	std::vector<GenericStructureValue> GenericStructureValue::genericStructureArray(const std::string& fieldName, uint32_t* opcUaStatusCode) const
	{
		UaString uaFieldName(fieldName.c_str());
        OpcUa_StatusCode uaCode;
		UaGenericStructureArray uaArr = uaGenericStructureValue_.genericStructureArray(uaFieldName, &uaCode);
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
		std::vector<GenericStructureValue> ret(uaArr.length());
		for (uint32_t i=0; i<uaArr.length(); i++)
		{
			ret[i].fromSdk(uaArr[i]);
		}
		return ret;
	}


	// Get the generic structure value
	// =============================================================================================
	std::vector<GenericStructureValue> GenericStructureValue::genericStructureArray(int i, uint32_t* opcUaStatusCode) const
	{
        OpcUa_StatusCode uaCode;
		UaGenericStructureArray uaArr = uaGenericStructureValue_.genericStructureArray(i, &uaCode);
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
		std::vector<GenericStructureValue> ret(uaArr.length());
		for (uint32_t i=0; i<uaArr.length(); i++)
		{
			ret[i].fromSdk(uaArr[i]);
		}
		return ret;
	}



    // Get the generic union value
    // =============================================================================================
    GenericUnionValue GenericStructureValue::genericUnion(const std::string& fieldName, uint32_t* opcUaStatusCode) const
    {
        UaString uaFieldName(fieldName.c_str());
        GenericUnionValue ret;
        OpcUa_StatusCode uaCode;
        ret.fromSdk( uaGenericStructureValue_.genericUnion(uaFieldName, &uaCode) );
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
        return ret;
    }


    // Get the generic structure value
    // =============================================================================================
    GenericUnionValue GenericStructureValue::genericUnion(int i, uint32_t* opcUaStatusCode) const
    {
        GenericUnionValue ret;
        OpcUa_StatusCode uaCode;
        ret.fromSdk( uaGenericStructureValue_.genericUnion(i, &uaCode) );
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
        return ret;
    }


    // Get the generic structure value
    // =============================================================================================
    std::vector<GenericUnionValue> GenericStructureValue::genericUnionArray(const std::string& fieldName, uint32_t* opcUaStatusCode) const
    {
        UaString uaFieldName(fieldName.c_str());
        OpcUa_StatusCode uaCode;
        UaGenericUnionArray uaArr = uaGenericStructureValue_.genericUnionArray(uaFieldName, &uaCode);
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
        std::vector<GenericUnionValue> ret(uaArr.length());
        for (uint32_t i=0; i<uaArr.length(); i++)
        {
            ret[i].fromSdk(uaArr[i]);
        }
        return ret;
    }


    // Get the generic structure value
    // =============================================================================================
    std::vector<GenericUnionValue> GenericStructureValue::genericUnionArray(int i, uint32_t* opcUaStatusCode) const
    {
        OpcUa_StatusCode uaCode;
        UaGenericUnionArray uaArr = uaGenericStructureValue_.genericUnionArray(i, &uaCode);
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
        std::vector<GenericUnionValue> ret(uaArr.length());
        for (uint32_t i=0; i<uaArr.length(); i++)
        {
            ret[i].fromSdk(uaArr[i]);
        }
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


	//  Get the datatype
	// =============================================================================================
	uaf::structurefielddatatypes::StructureFieldDataType GenericStructureValue::valueType(int index, uint32_t* opcUaStatusCode) const
	{
        OpcUa_StatusCode uaCode;
		UaStructureFieldDataEnum uaDataType = uaGenericStructureValue_.valueType(index, &uaCode);
        *opcUaStatusCode = static_cast<uint32_t>(uaCode);
		return uaf::structurefielddatatypes::fromSdkToUaf(uaDataType);
	}


	//  Convert to an extension object
	// =============================================================================================
	void GenericStructureValue::toExtensionObject(
			ExtensionObject& extensionObject,
			Encoding valueEncoding) const
	{
		UaExtensionObject uaExt;
		UaAbstractGenericValue::Encoding uaEnc = static_cast<UaAbstractGenericValue::Encoding>(valueEncoding);
		uaGenericStructureValue_.toExtensionObject(uaExt, uaEnc);
		extensionObject.fromSdk(uaExt);
	}


    // Get a string representation
    // =============================================================================================
    std::string GenericStructureValue::toString(const string& indent, size_t colon) const
    {
		stringstream ss;

		StructureDefinition def(definition());
		uint32_t* opcUaStatusCode = 0;

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
					ss << indent << "   - field(" << i << ")\n";

					uaf::structurefielddatatypes::StructureFieldDataType theValueType = valueType(i, opcUaStatusCode);
					ss << indent << "      - valueType";
					ss << fillToPos(ss, colon) << ": ";
					ss << theValueType
					        << " ("
					        << uaf::structurefielddatatypes::toString(theValueType)
                            << ", opcUaStatusCode="
                            << UaStatusCode(*opcUaStatusCode).toString().toUtf8()
					        << ")\n";

					if (isFieldSet(i))
					{
						if (theValueType == uaf::structurefielddatatypes::Variant)
						{
							ss << indent << "      - value";
							ss << fillToPos(ss, colon) << ": ";
							ss << value(i, opcUaStatusCode).toString();
							ss << " (opcUaStatusCode=" << UaStatusCode(*opcUaStatusCode).toString().toUtf8() << ")\n";
						}
						else if (theValueType == uaf::structurefielddatatypes::GenericStructure)
						{
							ss << indent << "      - genericStructure:";
							ss << genericStructure(i, opcUaStatusCode).toString(indent + string("         "));
							ss << indent << "        (opcUaStatusCode=" <<  UaStatusCode(*opcUaStatusCode).toString().toUtf8() << ")\n";
						}
						else if (theValueType == uaf::structurefielddatatypes::GenericStructureArray)
						{
							ss << indent << "      - genericStructureArray:";
							std::vector<GenericStructureValue> array = genericStructureArray(i, opcUaStatusCode);
							for (int j=0; uint32_t(j)<array.size(); j++)
							{
								ss << genericStructure(i, opcUaStatusCode).toString(indent + string("         "), colon);
							}
							ss << "\n";
                            ss << indent << "        (opcUaStatusCode=" <<  UaStatusCode(*opcUaStatusCode).toString().toUtf8() << ")\n";
						}
                        else if (theValueType == uaf::structurefielddatatypes::GenericUnion)
                        {
                            ss << indent << "      - genericUnion:";
                            ss << genericUnion(i, opcUaStatusCode).toString(indent + string("         "));
                            ss << indent << "        (opcUaStatusCode=" <<  UaStatusCode(*opcUaStatusCode).toString().toUtf8() << ")\n";
                        }
                        else if (theValueType == uaf::structurefielddatatypes::GenericUnionArray)
                        {
                            ss << indent << "      - genericUnionArray:";
                            std::vector<GenericUnionValue> array = genericUnionArray(i, opcUaStatusCode);
                            for (int j=0; uint32_t(j)<array.size(); j++)
                            {
                                ss << genericUnion(i, opcUaStatusCode).toString(indent + string("         "), colon);
                            }
                            ss << "\n";
                            ss << indent << "        (opcUaStatusCode=" <<  UaStatusCode(*opcUaStatusCode).toString().toUtf8() << ")\n";
                        }
					}
					else
					{
						ss << "      (This field is not set!)";
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


