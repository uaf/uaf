# examples/pyuaf/client/how_to_read_and_write_matrices.py
"""
EXAMPLE: how to read and write matrices
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
from pyuaf.util             import Matrix
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers, attributeids, opcuatypes
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



print("#******************************************************************************#")
print("#                                                                              #")
print("# 1) To understand matrices, let's define the function below to print one:     #")
print("#                                                                              #")
print("#******************************************************************************#")

def printMatrix(matrix):
    """
    Print a matrix.

    Parameters:
      structure:   a pyuaf.util.Matrix instance.
    """
    print("The matrix dimensions:")
    for i in range(len(matrix.dimensions)):
        print(" - dimensions[%d] = %s" %(i, matrix.dimensions[i]))
    print("The matrix elements as a contiguous list:")
    for i in range(len(matrix.elements)):
        print(" - elements[%d] = %s (%s)" %(i, matrix.elements[i].value, type(matrix.elements[i]).__name__))
    print("The matrix elements per dimension:")
    # we know the matrix has 3 dimensions in this example
    for i in range(matrix.dimensions[0]):
        for j in range(matrix.dimensions[1]):
            for k in range(matrix.dimensions[2]):
                print(" - matrix[%d][%d][%d] = %s" %(i, j, k, matrix.getElement([i,j,k]).value))




print("#******************************************************************************#")
print("#                                                                              #")
print("# 2) Read a matrix                                                             #")
print("#                                                                              #")
print("#******************************************************************************#")

# define the address of the matrix which we would like to read
address = Address( NodeId("Demo.Static.Matrix.Int32", demoNamespaceUri), demoServerUri )

# try to read it
result = myClient.read( [address] )

if not result.overallStatus.isGood():
    sys.exit("The matrix could not be read: %s" %result.targets[0].status)

# ok we expect to have a matrix:
matrix = result.targets[0].data

if not type(matrix) == Matrix:
    sys.exit("Wrong type: %s" %type(matrix))


# print the matrix:
printMatrix(matrix)

# for this example, we'll manipulate the matrix a bit, and then write it back to the server:
# First, we'll double all values of the matrix:
for i in range(len(matrix.elements)):
    matrix.elements[i] = primitives.Int32(matrix.elements[i].value * 2)
# Then, we change one particular element:
matrix.setElement([1,2,1], primitives.Int32(-100))
# the above line is a shortcut for the following three lines:
elementNumber = matrix.getElementNumber([1,2,1])
if 0 <= elementNumber < len(matrix.elements):
    matrix.elements[elementNumber] = primitives.Int32(-100)



# try to write the changed matrix back
result = myClient.write( [address], [matrix] )

if not result.overallStatus.isGood():
    sys.exit("The matrix could not be written: %s" %result.targets[0].status)


