import unittest
from pyuaf.util.unittesting import parseArgs

import importlib

ARGS = parseArgs()

ALL_MODULES = [ "client_client",
                "client_clientsettings",
                "client_discovery",
                "client_manualconnection",
                "client_manualconnectiontoendpoint",
                "client_read",
                "client_asyncread",
                "client_write",
                "client_asyncwrite",
                "client_methodcall",
                "client_asyncmethodcall",
                "client_manualsubscription",
                "client_monitordata",
                "client_monitorevents",
                "client_setpublishingmode",
                "client_browse",
                "client_browsenext",
                "client_historyreadrawmodified",
                "subscriptioninformation",
                "sessioninformation",
                "monitorediteminformation",
                "datachangenotification",
                "eventnotification",
                "requests.browserequesttarget",
                "requests.browsenextrequesttarget",
                "requests.createmonitoreddatarequesttarget",
                "requests.createmonitoredeventsrequesttarget",
                "requests.methodcallrequesttarget",
                "requests.readrequesttarget",
                "requests.translatebrowsepathsnodeidsrequesttarget",
                "requests.writerequesttarget"
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
        
        importedModule = __import__("client.%s" %module, fromlist=["suite"])
        importedSuite  = importedModule.suite(ARGS)
        
        suite.addTest(importedSuite)
    
    return suite


if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())