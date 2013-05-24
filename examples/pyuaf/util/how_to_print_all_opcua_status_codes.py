# examples/pyuaf/util/how_to_print_all_opcua_status_codes.py
"""
Example: how to print all OPC UA status codes
====================================================================================================
""" 

import pyuaf

# create a list that will contain tuples of (<codeName>, <codeIdentifier>)
# such as ('OpcUa_BadTimeout', -2146828288)
statusCodes = []

# add all identifier items from the module to the list
for item in pyuaf.util.opcuastatuscodes.__dict__.items():
    if isinstance(item[1], int) and item[0][0] != '_':
        statusCodes.append(item)

# sort the list
statusCodes = sorted(statusCodes, key=lambda x: x[1])

# modify these flags to instruct the script to print the items to
# the screen and/or to write them to a file:
printToScreen = True
writeToFile   = False

# print the items to the screen if necessary
if printToScreen:
    for item in statusCodes:
        print("%s %d" %item)

# write the items to a file if necessary
if writeToFile:
    f = open('opcuastatuscodes.txt', 'w')
    for item in statusCodes:
        f.write("%s %d\n" %item)
    f.close()