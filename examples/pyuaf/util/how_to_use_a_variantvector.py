# examples/pyuaf/util/how_to_use_a_variantvector.py
"""
Example: how to use a VariantVector
====================================================================================================

A VariantVector is a container that holds elements of a dynamic data type.
It is an artifact automatically generated from the C++ UAF code, and has the same functionality
as a list of variables values, where the values can be instances of:

  - None
  - pyuaf.util.primitives.Boolean
  - pyuaf.util.primitives.UInt32
  - pyuaf.util.QualifiedName
  - pyuaf.util.LocalizedText
  - ...

See the HTML documentation of PyUAF for more info!
"""

import pyuaf
from pyuaf.util import VariantVector

# construct a VariantVector without elements:
vec = VariantVector()

noOfElements = len(vec)
print("noOfElements (should be 0): %d" %noOfElements)


# now we append an unsigned 32-bit integer, a boolean, and a localized text:
vec.append( pyuaf.util.primitives.UInt32(1234) )
vec.append( pyuaf.util.primitives.Boolean(True) )
vec.append( pyuaf.util.LocalizedText("en", "Some text.") )

noOfElements = len(vec)
print("noOfElements (should be 3): %d" %len(vec))
print("Vector contents:")
for i in range(noOfElements):
    print(" - vec[%d] = %s" %(i, repr(vec[i])))

# now we resize the vector so that it contains 4 elements (the last one being a None value)
vec.resize(4)

noOfElements = len(vec)
print("noOfElements (should be 4): %d" %noOfElements)
print("Vector contents:")
for i in range(noOfElements):
    print(" - vec[%d] = %s" %(i, repr(vec[i])))

# now we append an array of Floats.
# An OPC UA array can be defined as a python list.
# All elements should have the same type, otherwise you will get a TypeError!
vec.append( [pyuaf.util.primitives.Float(0.1),
             pyuaf.util.primitives.Float(0.2),
             pyuaf.util.primitives.Float(0.3) ] )

noOfElements = len(vec)

print("noOfElements (should be 5): %d" %noOfElements)
print("Vector contents:")
for i in range(noOfElements):
    print(" - vec[%d] = %s" %(i, repr(vec[i])))

print("Vector contents, using iterators:")
for element in vec:
    print(" - %s" %repr(element))

