
import sys
import threading

try:
    import argparse
except:
    raise ImportError("Cannot import argparse, Python >= 2.7 is required to run " 
                      "the unit tests (but not to use the UAF)")



DEFAULT_DEMOSERVER_URL        = "opc.tcp://localhost:48010"
DEFAULT_DEMOSERVER_NS_URI     = "http://www.unifiedautomation.com/DemoServer"
DEFAULT_DEMOSERVER_SERVER_URI = "urn:UnifiedAutomation:UaServerCpp"



class TestResults:
    def __init__(self, total):
        self.__total      = total
        self.__finished   = 0
        self.__failed     = 0
        self.__lock       = threading.Lock()
        self.__extraInts  = {}
        self.__extraLists = {}
    
    def clear(self):
        self.__lock.acquire()
        self.__finished = 0
        self.__failed   = 0
        self.__lock.release()
    
    def initializeInt(self, name, value=0):
        try:
            self.__lock.acquire()
            self.__extraInts[name] = value
        finally:
            self.__lock.release()
    
    def initializeList(self, name, value=[]):
        try:
            self.__lock.acquire()
            self.__extraLists[name] = value[:]
        finally:
            self.__lock.release()
    
    def appendToList(self, name, value):
        try:
            self.__lock.acquire()
            self.__extraLists[name].append(value)
        finally:
            self.__lock.release()
    
    def removeFromList(self, name, value):
        try:
            self.__lock.acquire()
            self.__extraLists[name].remove(value)
        finally:
            self.__lock.release()
    
    def getListCopy(self, name):
        try:
            self.__lock.acquire()
            copiedList = self.__extraLists[name][:]
            return copiedList
        finally:
            self.__lock.release()
    
    def incrementInt(self, name):
        try:
            self.__lock.acquire()
            self.__extraInts[name] += 1
        finally:
            self.__lock.release()
    
    def decrementInt(self, name):
        try:
            self.__lock.acquire()
            self.__extraInts[name] -= 1
        finally:
            self.__lock.release()
    
    def setInt(self, name, value):
        try:
            self.__lock.acquire()
            self.__extraInts[name] = value
        finally:
            self.__lock.release()
    
    def getIntValue(self, name):
        try:
            self.__lock.acquire()
            return self.__extraInts[name]
        finally:
            self.__lock.release()
    
    def finish(self):
        try:
            self.__lock.acquire()
            self.__finished += 1
        finally:
            self.__lock.release()
    
    def fail(self):
        try:
            self.__lock.acquire()
            self.__failed += 1
        finally:
            self.__lock.release()
    
    def total(self):
        return self.__total
    
    def finished(self):
        return self.__finished

    def failed(self):
        return self.__failed




def testVector(testCase, vectorClass, testItems=[]):
    
    # create and fill a vector using append
    vec0 = vectorClass()
    for item in testItems:
        vec0.append(item)
    
    # create a vector using resize/assignments
    vec1 = vectorClass()
    vec1.resize( len(testItems) )
    for i in xrange(len(testItems)):
        vec1[i] = testItems[i]
    
    for vec in [vec0, vec1]:
        
        # test __len__
        testCase.assertEqual( len(vec), len(testItems) )
        
        # test __getitem__
        for i in xrange(len(testItems)):
            testCase.assertEqual( vec[i], testItems[i] )
        
        # test iterator
        i = 0
        for item in vec:
            testCase.assertEqual( item, testItems[i] )
            i += 1
        
        # test slicing
        vecShortened = vec[1:]
        testCase.assertEqual( len(vecShortened), len(vec) - 1 )
        testCase.assertEqual( vec[1], vecShortened[0] )
        
        # test more slicing
        vecShortened = vec[:-1]
        testCase.assertEqual( len(vecShortened), len(vec) - 1 )
        testCase.assertEqual( vec[-2], vecShortened[-1] )
        
        # test insert
        vec.insert(vec.begin() + 1, testItems[-1])
        testCase.assertEqual( vec[1], testItems[-1] )
        



def parseArgs():
    
    parser = argparse.ArgumentParser(
                 formatter_class = argparse.RawDescriptionHelpFormatter,
                 description     = "Run the unit tests.\n"
                                   "\n"
                                   "To run the client tests, you must start the UaServerCPP demoserver \n"
                                   "of Unified Automation first. \n"
                                   "\n"
                                   "e.g. $SDK/bin/uaservercpp      in Linux\n" 
                                   "e.g. $SDK\\bin\\uaservercpp.exe  in Windows\n"
                                   )
    
    parser.add_argument('-l',  "--loglevel",
                        dest    = "loglevel",
                        type    = str,
                        help    = "Run the tests with the UAF having a specific loglevel.\n"
                                  "This can be one of:\n" 
                                  "  Debug  Info  Warning  Error  Disabled\n"
                                  "  (or their corresponding integer values).\n"
                                  "If not specified, the UAF logging will be Disabled.")
    
    parser.add_argument('-q', "--quiet", 
                        dest    = "quiet", 
                        action  = 'store_true', 
                        help    = "Run the unit test(s) in quiet mode.\n"
                                  "-q and -v only affect the unit testing framework,\n"
                                  "they are independent of the UAF loglevel (-l).")
    
    parser.add_argument('-v', "--verbose", 
                        dest    = "verbose", 
                        action  = 'store_true', 
                        help    = "Run the test(s) in verbose mode.\n"
                                  "-q and -v only affect the unit testing framework,\n"
                                  "they are independent of the UAF loglevel (-l).")
    
    parser.add_argument("--demo-url", 
                        dest    = "demo_url", 
                        type    = str,
                        default = DEFAULT_DEMOSERVER_URL,
                        help    = "UaDemoserver URL. If not specified, the default " 
                                  "'%s' will be used." %DEFAULT_DEMOSERVER_URL)
    parser.add_argument("--demo-ns-uri", 
                        dest    = "demo_ns_uri", 
                        type    = str,
                        default = DEFAULT_DEMOSERVER_NS_URI,
                        help    = "UaDemoserver namespace URI. If not specified, the default "
                                  "'%s' will be used." %DEFAULT_DEMOSERVER_NS_URI)
    parser.add_argument("--demo-server-uri", 
                        dest    = "demo_server_uri", 
                        type    = str,
                        default = DEFAULT_DEMOSERVER_SERVER_URI,
                        help    = "UaDemoserver server URI. If not specified, the default "
                                  "'%s' will be used." %DEFAULT_DEMOSERVER_SERVER_URI)
    
    args = parser.parse_args()
    
    
    uafDebug    = 4
    uafInfo     = 3
    uafWarning  = 2
    uafError    = 1
    uafDisabled = 0
    
    
    # if -v is specified, the loglevel is fixed
    if args.verbose:
        args.verbosity = 2
    elif args.quiet:
        args.verbosity = 0
    else:
        args.verbosity = 1
    
    if args.loglevel:
        if args.loglevel.lower() in ["debug", str(uafDebug)]:
            args.loglevel = uafDebug
        elif args.loglevel.lower() in ["info", str(uafInfo)]: 
            args.loglevel = uafInfo
        elif args.loglevel.lower() in ["warning", str(uafWarning)]: 
            args.loglevel = uafWarning
        elif args.loglevel.lower() in ["error", str(uafError)]: 
            args.loglevel = uafError
        elif args.loglevel.lower() in ["disabled", str(uafDisabled)]: 
            args.loglevel = uafDisabled
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
        args.loglevel = uafDisabled
    
    return args

