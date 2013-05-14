# examples/pyuaf/util/how_to_use_a_stringvector.py
"""
Example: how to use a StringVector
====================================================================================================

A StringVector is a container that holds string elements. 
It is an artifact automatically generated from the C++ UAF code, and has the same functionality
as a list of str.

See the HTML documentation of PyUAF for more info!
""" 

import pyuaf
from pyuaf.util import StringVector

# construct a StringVector without elements:
strings = StringVector()

noOfElements = len(strings) # will be 0
print("noOfElements (should be 0): %d" %noOfElements)

strings.append("foo")

noOfElements = len(strings) # will be 1
print("noOfElements (should be 1): %d" %noOfElements)

strings.resize(4)

noOfElements = len(strings) # will be 4
print("noOfElements (should be 4): %d" %noOfElements)

# The first element (index 0) is "foo", the other 3 elements are empty strings ("")
# So we fill these strings now: 
strings[1] = "x"
strings[2] = "y"
strings[3] = "z"

print("'strings' element 0: %s" %strings[0])
print("'strings' element 1: %s" %strings[1])
print("'strings' element 2: %s" %strings[2])
print("'strings' element 3: %s" %strings[3])

# you may also construct a StringVector from a regular Python list:
otherStrings = StringVector( ["foo", "bar"] )

print("'otherStrings' element 0: %s" %otherStrings[0])
print("'otherStrings' element 1: %s" %otherStrings[1])