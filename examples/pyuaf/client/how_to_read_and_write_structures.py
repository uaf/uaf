# examples/pyuaf/client/how_to_read_and_write_structures.py
"""
EXAMPLE: how to read and write structures
====================================================================================================

To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine. 
($SDK/bin/uaservercpp, this executable is part of the SDK).
"""

import time, os, sys

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings
from pyuaf.util             import Address, NodeId, ExtensionObject, SdkStatus
from pyuaf.util             import GenericStructureValue, GenericStructureVector, GenericUnionValue
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers, attributeids, opcuatypes, structurefielddatatypes
from pyuaf.util.errors      import UafError


# define the namespace URI and server URI of the UaServerCPP demo server
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"
demoNamespaceUri = "http://www.unifiedautomation.com/DemoServer/"

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)



print("#**************************************************************************************************#")
print("#                                                                                                  #")
print("# 1) To understand a GenericStructureValue instance, let's define the function below to print one: #")
print("#                                                                                                  #")
print("#**************************************************************************************************#")

def printStructure(structure, indentation=""):
    """
    Print a structure.
    
    Parameters:
      structure:   a pyuaf.util.GenericStructureValue instance. May represent a structure
                   or union or optionset.
      indentation: a string to print at the beginning of each line (to add indentation when
                   this function is called recursively).
    """
    # get the definition of the structure:
    definition = structure.definition()
    
    # we'll print the contents of the structure
    print(indentation + "Structure contents:")
    
    # loop through the fields of the structure, by looking at the definition:
    for i in xrange(definition.childrenCount()):
        
        # retrieve information both from the definition and from the structure itself:
        child = definition.child(i)
        childName  = child.name()           # a string
        childType  = child.valueType()      # datatype, e.g. Double
        fieldType, opcUaStatusCode  = structure.valueType(i) # e.g. Variant, GenericStructure, GenericStructureArray...
        
        if not SdkStatus(opcUaStatusCode).isGood():
            raise Exception("Oops, we could not get the valueType due to: %s" %SdkStatus(opcUaStatusCode))
        
        print(indentation + "  * child number %d:"         %i)
        print(indentation + "     - child name = %s"       %childName)
        print(indentation + "     - child type = %d (%s)"  %(childType, opcuatypes.toString(childType)))
        print(indentation + "     - field type = %s (%s)"  %(fieldType, structurefielddatatypes.toString(fieldType)))
        
        if fieldType == structurefielddatatypes.Variant:
            print(indentation + "     - value      = %s" %structure.value(i))
        elif fieldType == structurefielddatatypes.GenericStructure:
            print(indentation + "     - value:")
            # recursive call
            printStructure(structureValue.genericStructureValue(i), indentation + "   ")
        elif fieldType == structurefielddatatypes.GenericStructureArray:
            array, opcUaStatusCode = structureValue.genericStructureArray(i)
            
            if not SdkStatus(opcUaStatusCode).isGood():
                raise Exception("Oops, we could not get the structure due to: %s" %SdkStatus(opcUaStatusCode))
            
            print(indentation + "     - value:")
            # recursive calls to all array items:
            for j in xrange(len(array)):
                print(indentation + "        array[%d]:" %j)
                printStructure(array[j], indentation + "          ")
        
    print("") # empty line



print("#******************************************************************************************#")
print("#                                                                                          #")
print("# 2) How to read and write a scalar structure (i.e. a single structure, not an array)      #")
print("#                                                                                          #")
print("#******************************************************************************************#")

# define the address of the Structure which we would like to read
address = Address( NodeId("Demo.Static.Scalar.Vector", demoNamespaceUri), demoServerUri )

# try to read a structure
result = myClient.read( [address] )

# we're expecting an ExtensionObject. Let's check this:
if isinstance(result.targets[0].data, ExtensionObject):
    print("We received an ExtensionObject")
    print("")
else:
    raise Exception("Oops, we were expecting an ExtensionObject, but we received a: %s" %result.targets[0].data)

extensionObject = result.targets[0].data

# now let's find out the datatype of the ExtensionObject
result = myClient.read( [address] , attributeId = attributeids.DataType)

dataTypeId = result.targets[0].data # data represents a NodeId

print("The datatype of the ExtensionObject is: NodeId: %s" %dataTypeId)
print("")

# using the datatypeId, get the definition of the structure
definition = myClient.structureDefinition(dataTypeId)

print("The definition of the structure:")
print(str(definition))
print("")

# using the original ExtensionObject the StructureDefinition, we can now create the GenericStructureValue:
structureValue = GenericStructureValue(extensionObject, definition)

# print the structure:
print("So we can now print the full structure:")
printStructure(structureValue)

# now change the value of the first child (i = 0):
structureValue.setField(0, primitives.Double(0.1))

# we can also change a field via its name:
structureValue.setField("Y", primitives.Double(0.2))

# write back the structure
newExtensionObject = ExtensionObject()
structureValue.toExtensionObject(newExtensionObject)

print("Now writing {structure}.X = 0.1 and {structure}.Y = 0.2")
print("")
try:
    result = myClient.write( [address], [newExtensionObject] )
    if result.overallStatus.isGood():
        print("OK, the new structure value has been written successfully")
    else:
        print("Oops, some OPC UA problem occurred. Here's the result:\n%s" %result)
except UafError, e:
    print("Oops, some error occurred on the client side. Here's the error message: %s" %e)

print("")
print("Let's read the same structure again, to verify that the values have changed:")
result          = myClient.read( [address] )
extensionObject = result.targets[0].data
structureValue  = GenericStructureValue(extensionObject, definition)
printStructure(structureValue)



print("#******************************************************************************************#")
print("#                                                                                          #")
print("# 3) How to read and write an array of structures                                          #")
print("#                                                                                          #")
print("#******************************************************************************************#")

# let's now read an array of structures
arrayAddress = Address( NodeId("Demo.Static.Arrays.Vector", demoNamespaceUri), demoServerUri )

# try to read a structure
result = myClient.read( [arrayAddress] )

# we're expecting a list of ExtensionObjects. Let's check this:
if isinstance(result.targets[0].data, list) and isinstance(result.targets[0].data[0], ExtensionObject):
    print("We received a list of ExtensionObjects")
    print("")
else:
    raise Exception("Oops, we were expecting a list of ExtensionObjects, but we received a: %s" %result.targets[0].data)

extensionObjectList = result.targets[0].data

# get the datatype
result = myClient.read( [arrayAddress] , attributeId = attributeids.DataType)

arrayDataTypeId = result.targets[0].data # data represents a NodeId


print("The datatype of the ExtensionObjects of this array is: NodeId: %s" %dataTypeId)
print("")

# using the datatypeId, get the definition of the structure
definition = myClient.structureDefinition(dataTypeId)

print("The definition of the structures is:")
print(str(definition))
print("")

print("Now let's loop through the list:")

for i in xrange(len(extensionObjectList)):
    
    extensionObject = extensionObjectList[i]
    
    # using the original ExtensionObject the StructureDefinition, we can now create the GenericStructureValue:
    structureValue = GenericStructureValue(extensionObject, definition)
    
    # print the structure in one line:
    print("item[%d]: " %i)
    printStructure(structureValue)
    
print("")

# now change the values of the first child of the first array item:
firstItem = GenericStructureValue(extensionObjectList[0], definition)
firstItem.setField(0, primitives.Double(0.1))
firstItem.setField("Y", primitives.Double(0.2))

# write back the structure
firstItem.toExtensionObject(extensionObjectList[0])
 
print("Now writing the modified structure array")
print("")
try:
    result = myClient.write( [arrayAddress], [extensionObjectList] )
    if result.overallStatus.isGood():
        print("OK, the new structure array has been written successfully")
        print("")
    else:
        print("Oops, some OPC UA problem occurred. Here's the result:\n%s" %result)
except UafError, e:
    print("Oops, some error occurred on the client side. Here's the error message: %s" %e)



print("#*************************************************************************************************#")
print("#                                                                                                 #")
print("# 4) How to read and write a structure which contains an array of structures as one of its fields #")
print("#                                                                                                 #")
print("#*************************************************************************************************#")

# define the address of the Structure which has an array of structure as one of its fields 
address = Address( NodeId("Demo.Static.Scalar.WorkOrder", demoNamespaceUri), demoServerUri )

# read the structure
result = myClient.read( [address] )

# make sure it's an ExtensionObject
assert type(result.targets[0].data) == ExtensionObject
extensionObject = result.targets[0].data

# read the datatype
result = myClient.read( [address] , attributeId = attributeids.DataType)
dataTypeId = result.targets[0].data # data represents a NodeId

# get the definition of the structure
definition = myClient.structureDefinition(dataTypeId)

# using the original ExtensionObject the StructureDefinition, we can now create the GenericStructureValue:
structureValue = GenericStructureValue(extensionObject, definition)

print("")
print("Let's read a structure which has an array of WorkOrder structures as child number 3:")
printStructure(structureValue)

print("")
print("Let's change one of the array items")
array, opcUaStatusCode = structureValue.genericStructureArray(3) # child number 3 of the main structure

if not SdkStatus(opcUaStatusCode).isGood():
    raise Exception("Oops, we could not get the structure array due to: %s" %SdkStatus(opcUaStatusCode))

status = array[1].setField(2, pyuaf.util.LocalizedText("en", "THIS FIELD WAS CHANGED!!!"))
assert status.isGood()

status = structureValue.setField(3, array)
assert status.isGood()

structureValue.toExtensionObject(extensionObject)

print("Now writing the modified structure")
print("")
try:
    result = myClient.write( [address], [extensionObject] )
    if result.overallStatus.isGood():
        print("OK, the new structure array has been written successfully")
        print("")
    else:
        print("Oops, some OPC UA problem occurred. Here's the result:\n%s" %result)
except UafError, e:
    print("Oops, some error occurred on the client side. Here's the error message: %s" %e)



print("#*************************************************************************************************#")
print("#                                                                                                 #")
print("# 4) How to read and write a union                                                                #")
print("#                                                                                                 #")
print("#*************************************************************************************************#")

def printUnion(union, indentation=""):
    """
    Print a structure.
    
    Parameters:
      union:       a pyuaf.util.GenericUnionValue instance. 
      indentation: a string to print at the beginning of each line (to add indentation when
                   this function is called recursively).
    """
    # get the definition of the structure:
    definition = union.definition()
    
    # we'll print the contents of the structure
    print(indentation + "Union contents:")
    
    if not definition.isUnion():
        raise Exception("The given union is no union!")
    
    # let's show the possible values by looking at the definition:
    for i in xrange(definition.childrenCount()):
        
        # retrieve information both from the definition and from the structure itself:
        child = definition.child(i)
        childName   = child.name()           # a string
        childType   = child.valueType()      # datatype, e.g. Double
        
        print(indentation + "  * child number %d:"         %i)
        print(indentation + "     - child name = %s"       %childName)
        print(indentation + "     - child type = %d (%s)"  %(childType, opcuatypes.toString(childType)))
        
    # show the active value (the "switchValue")    
    switchValue = union.switchValue()
    field       = union.field()
    
    print(indentation + "Switch value: %d" %switchValue)
    print(indentation + "Field name: %s" %union.field().name())
    print(indentation + "Value: %s" %union.value())
    print("") # empty line


# define the address of the Union
address = Address( NodeId("Demo.Static.Scalar.Structures.AnalogMeasurement", demoNamespaceUri), demoServerUri )

# try to read a structure
result = myClient.read( [address] )

assert type(result.targets[0].data) == ExtensionObject
extensionObject = result.targets[0].data

# now let's find out the datatype of the ExtensionObject
result = myClient.read( [address] , attributeId = attributeids.DataType)
dataTypeId = result.targets[0].data # data represents a NodeId

# using the datatypeId, get the definition of the structure
definition = myClient.structureDefinition(dataTypeId)

print("The definition of the union:")
print(str(definition))
print("")

# we can now create the union:
union = GenericUnionValue(extensionObject, definition)

# print the union:
print("So we can now print the full union:")
printUnion(union)

# now change the active value
union.setValue(union.field().name(), primitives.Float(111.222))

# write back the union
newExtensionObject = ExtensionObject()
union.toExtensionObject(newExtensionObject)

print("Now writing union['%s'] = 111.222333" %union.field().name())
print("")
try:
    result = myClient.write( [address], [newExtensionObject] )
    if result.overallStatus.isGood():
        print("OK, the new structure value has been written successfully")
    else:
        print("Oops, some OPC UA problem occurred. Here's the result:\n%s" %result)
except UafError, e:
    print("Oops, some error occurred on the client side. Here's the error message: %s" %e)

print("")
print("Let's read the same union again, to verify that the active value have changed:")
result          = myClient.read( [address] )
extensionObject = result.targets[0].data
union           = GenericUnionValue(extensionObject, definition)
printUnion(union)

