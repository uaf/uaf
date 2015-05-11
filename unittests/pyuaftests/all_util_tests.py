import unittest
from pyuaf.util.unittesting import parseArgs

import importlib

ARGS = parseArgs()

ALL_MODULES = [ "primitives",
                "expandednodeid",
                "localizedtext",
                "mask",
                "address",
                "nodeid",
                "nodeididentifier",
                "qualifiedname",
                "relativepathelement",
                "datetime",
                "browsepath",
                "status",
                "variant",
                "datavalue",
                "applicationdescription",
                "modificationinfo",
                "simpleattributeoperand",
                "usertokenpolicy",
                "endpointdescription",
                "referencedescription",
                "pkiidentity",
                "enumvalue",
                "pkicertificateinfo",
                "pkipublickey",
                "pkirsakeypair",
                "pkicertificate"
              ]


################ add the current path to sys.path ################ 
# This is needed if other python scripts need to be able to import
# this module.
# See http://stackoverflow.com/questions/279237/import-a-module-from-a-relative-path
import os, sys, inspect
# realpath() with make your script run, even if you symlink it :)
cmd_folder = os.path.realpath(os.path.abspath(os.path.split(inspect.getfile( inspect.currentframe() ))[0]))
if cmd_folder not in sys.path:
    sys.path.insert(0, cmd_folder)
##################################################################


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args
        
    suite = unittest.TestSuite()
    
    import util.address
    
    for module in ALL_MODULES:
        
        importedModule = __import__("util.%s" %module, fromlist=["suite"])
        importedSuite  = importedModule.suite(ARGS)
        
        suite.addTest(importedSuite)
    
    return suite


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())