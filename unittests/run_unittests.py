
import sys

try:
    import argparse
except:
    raise ImportError("Cannot import argparse, Python >= 2.7 is required to run " 
                      "the unit tests (but not to use the UAF)")

# add the uaf/lib directory to the PYTHONPATH
sys.path.append("../lib")


ALL_MODULES = [ "util.expandednodeid",
                "util.localizedtext",
                "util.mask",
                "util.address",
                "util.nodeid",
                "util.nodeididentifier",
                "util.qualifiedname",
                "util.relativepathelement",
                "util.datetime",
                "util.browsepath",
                "util.status",
                "util.variant",
                "client.client_client",
                "client.client_clientsettings",
                "client.client_discovery",
                "client.client_manualconnection",
                "client.client_read",
                "client.client_asyncread",
                "client.client_write",
                "client.client_asyncwrite",
                "client.client_methodcall",
                "client.client_asyncmethodcall",
                "client.client_manualsubscription",
                "client.client_monitordata",
                "client.client_monitorevents",
                "client.client_browse",
                "client.client_browsenext",
                "client.client_historyreadrawmodified" ]


import pyuaftests

examples =  "examples:\n"
examples += "  1) run all unit tests without debugging info:\n" \
            "      %s\n" %sys.argv[0]
examples += "  2) run all unit tests in 'verbose' mode (meaning: with debugging info):\n" \
            "      %s -v \n" %sys.argv[0]
examples += "  3) run specific unit tests in 'verbose' mode:\n" \
            "      %s -v client.client_read client.client_write  \n" %sys.argv[0]
examples += "  4) just show all possible unit tests:\n" \
            "      %s -s\n" %sys.argv[0]
            
parser = argparse.ArgumentParser(
             formatter_class = argparse.RawDescriptionHelpFormatter,
             description     = "Run the unit tests.\n"
                               "\n"
                               "To run some tests, you must start the UaDemoServer of Unified\n"
                               "Automation first.\n"
                               "\n"
                               "%s" %examples)
                                

parser.add_argument("TEST", 
                    nargs   = '*', 
                    help    = "Specific tests to be run. If no specific tests are specified, " 
                              "then all tests will be run.")
parser.add_argument('-s',  "--show-all", 
                    dest    = "show", 
                    action  = 'store_true', 
                    help    = "Don't run any test, but show a list of all tests.")

parser.add_argument('-l',  "--loglevel",
                    dest    = "loglevel",
                    type    = str,
                    help    = "Run the tests with the given loglevel, which can be one of:\n" 
                              "  Debug  Info  Warning  Error  Disabled"
                              "  (or their corresponding integer values). "
                              "If not specified, the logging will be Disabled.")

parser.add_argument('-v', "--verbose", 
                    dest    = "verbose", 
                    action  = 'store_true', 
                    help    = "Run the test(s) in verbose mode. This is a shortcut to '-l Debug'")

parser.add_argument("--demo-url", 
                    dest    = "demo_url", 
                    type    = str,
                    default = 'opc.tcp://localhost:4841',
                    help    = "UaDemoserver URL. If not specified, the default " 
                              "'opc.tcp://localhost:4841' will be used.")
parser.add_argument("--demo-ns-uri", 
                    dest    = "demo_ns_uri", 
                    type    = str,
                    default = 'DemoNodeManager',
                    help    = "UaDemoserver namespace URI. If not specified, the default "
                              "'DemoNodeManager' will be used.")
parser.add_argument("--demo-server-uri", 
                    dest    = "demo_server_uri", 
                    type    = str,
                    default = 'urn:UnifiedAutomation:UaDemoserver',
                    help    = "UaDemoserver server URI. If not specified, the default "
                              "'urn:UnifiedAutomation:UaDemoserver' will be used.")

args = parser.parse_args()


# try to import pyuaf
try:
    import pyuaf
except:
    print("******************* ERROR: Could not import pyuaf! ********************")
    print("Make sure that the UAF and PyUaf libraries are compiled without errors,")
    print("and make sure their location is included in your PYTHONPATH variable!")
    print("***********************************************************************")
    raise


# if -l is specified, only list the modules, then exit
if args.show:
    for testModule in ALL_MODULES:
        print(testModule)
    sys.exit()

# if -v is specified, the loglevel is fixed
if args.verbose:
    args.loglevel = pyuaf.util.loglevels.Debug
elif args.loglevel:
    if args.loglevel.lower() in ["debug", str(pyuaf.util.loglevels.Debug)]:
        args.loglevel = pyuaf.util.loglevels.Debug
        args.verbose = True
    elif args.loglevel.lower() in ["info", str(pyuaf.util.loglevels.Info)]: 
        args.loglevel = pyuaf.util.loglevels.Info
    elif args.loglevel.lower() in ["warning", str(pyuaf.util.loglevels.Warning)]: 
        args.loglevel = pyuaf.util.loglevels.Warning
    elif args.loglevel.lower() in ["error", str(pyuaf.util.loglevels.Error)]: 
        args.loglevel = pyuaf.util.loglevels.Error
    elif args.loglevel.lower() in ["disabled", str(pyuaf.util.loglevels.Disabled)]: 
        args.loglevel = pyuaf.util.loglevels.Disabled
    else:
        print("******************* ERROR: Invalid loglevel! ********************")
        print("Provide one of these:")
        print(" Debug")
        print(" Info")
        print(" Warning")
        print(" Error")
        print(" Disabled")
        print("*****************************************************************")
        sys.exit()
else:
    args.loglevel = pyuaf.util.loglevels.Disabled


# create a list of the tests to be run
if len(args.TEST) == 0:
    modulesToTest = ALL_MODULES
else:
    modulesToTest = args.TEST

# run the tests one by one
for module in modulesToTest:
    try:
        importedModule = __import__("pyuaftests.%s" %module, fromlist=["pyuaftests"])
        importedModule.test(args)
    except ImportError:
        print("******** ERROR: '%s' is not a valid test! ********" %module)
        print "Valid tests are:"
        for testModule in ALL_MODULES:
            print("  %s" %testModule)
        raise
        sys.exit()

if len(modulesToTest) > 0:
    print("")
    print("All tests passed successfully.")
    print("")


