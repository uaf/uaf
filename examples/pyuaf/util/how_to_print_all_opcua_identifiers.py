# examples/pyuaf/util/how_to_print_all_opcua_identifiers.py
"""
Example: how to print all OPC UA identifiers
====================================================================================================
""" 

import pyuaf

# create a list that will contain tuples of (<identifierName>, <numericIdentifier>)
# such as ('OpcUaId_ObjectsFolder', 85)
identifierItems = []

# add all identifier items from the module to the list
for item in pyuaf.util.opcuaidentifiers.__dict__.items():
    if isinstance(item[1], int) and item[0][0] != '_':
        identifierItems.append(item)

# sort the list
identifierItems = sorted(identifierItems, key=lambda x: x[1])

# modify these flags to instruct the script to print the items to
# the screen and/or to write them to a file:
printToScreen = True
writeToFile   = False

# print the items to the screen if necessary
if printToScreen:
    for item in identifierItems:
        print("%s %d" %item)

# write the items to a file if necessary
if writeToFile:
    f = open('opcuaidentifiers.txt', 'w')
    for item in identifierItems:
        f.write("%s %d\n" %item)
    f.close()