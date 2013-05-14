import pyuaf
import time
import thread, threading

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import MethodCallRequest, MethodCallRequestTarget
from pyuaf.client.results  import MethodCallResult,  MethodCallResultTarget
from pyuaf.util.primitives import Int32
from pyuaf.util.opcuaidentifiers import OpcUaId_ObjectsFolder



class MyClient(pyuaf.client.Client):

    def __init__(self, settings, verbose):
        pyuaf.client.Client.__init__(self, settings)
        self.verbose = verbose
        self.noOfCallCompletes = 0
        self.lock = threading.Lock()
            
    def callComplete(self, result):
        self.lock.acquire()
        self.noOfCallCompletes += 1
        
        if self.verbose:
            print("***** callComplete started *****")
            print(result)
            print("***** callComplete finished *****")
        
        self.lock.release()


def test(args):
    
    print("client.client_asyncmethodcall")
    
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel

    client = MyClient(settings, args.verbose)
    

    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    
    print(" - testing pyuaf.client.Client().beginCall()")
    

    address_Objects        = Address(ExpandedNodeId(OpcUaId_ObjectsFolder, 0, serverUri))
    address_MyDemoObject   = Address(address_Objects,      [RelativePathElement(QualifiedName("MyDemoObject", demoNsUri))] )
    address_SetAllValues   = Address(address_MyDemoObject, [RelativePathElement(QualifiedName("SetAllValues", demoNsUri))] )
    
    asyncResult = client.beginCall(address_MyDemoObject, address_SetAllValues, [Int32(-123)])
    
    if args.verbose:
        print("Async result:")
        print(asyncResult)
    
    if args.verbose:
        print("Waiting for the result...")
    
    t_timeout = time.time() + 5.0
    
    while time.time() < t_timeout and client.noOfCallCompletes == 0:
        time.sleep(0.01)
    
    # assert if the call was received
    assert client.noOfCallCompletes == 1
    
    
    print(" - testing pyuaf.client.Client().beginCall(..., callbackFunction)")
    
    # define a TestClass with a callback
    class TestClass:
        def __init__(self):
            self.noOfSuccessFullyFinishedCallbacks = 0
            self.lock = threading.Lock()
        
        def myCallback(self, result):
            self.lock.acquire()
            self.noOfSuccessFullyFinishedCallbacks += 1
            
            if args.verbose:
                print("--- Callback started ---")
                print(result)
                print("--- Callback finished ---")
            
            self.lock.release()
    
    t = TestClass()
    asyncResult = client.beginCall(address_MyDemoObject, address_SetAllValues, [Int32(-123)], callback=t.myCallback)
    
    if args.verbose:
        print("Asynchronous request was executed (handle assigned: %d)" %asyncResult.requestHandle)
        print("Wait for the result...")
    
    t_timeout = time.time() + 5.0
    while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks == 0:
        time.sleep(0.01)
    
    # assert if the callback function was successfully finished
    assert t.noOfSuccessFullyFinishedCallbacks == 1
    
    
    print(" - testing pyuaf.client.Client().processRequest(<AsyncWriteRequest>, <longLastingcallbackFunction>) 30 times in parallel")
    if args.verbose:
        print("   (you should notice that all 30 callback functions are running simultaneously and thus mixing their output)")
    
    
    # define a TestClass with a callback that lasts several seconds
    class LongLastingTestClass:
        def __init__(self):
            self.noOfSuccessFullyFinishedCallbacks = 0
            self.lock = threading.Lock()
        
        def myCallback(self, result):
            if args.verbose: print("Result %d is now started" %result.requestHandle)
            
            totalSeconds = 2
            for secondsFinished in xrange(totalSeconds):
                if args.verbose: print("Result %d is now busy for %d seconds" %(result.requestHandle, secondsFinished))
                time.sleep(1)
            
            if args.verbose: print("Result %d is now finished" %result.requestHandle)
            
            self.lock.acquire()
            self.noOfSuccessFullyFinishedCallbacks += 1
            self.lock.release()
    
    t = LongLastingTestClass()
    
    # start 30 processes
    for i in xrange(30):
        client.beginCall(address_MyDemoObject, address_SetAllValues, [Int32(-123)], callback=t.myCallback)
    
    # sleep while the callbacks are running
    if args.verbose: print("Waiting for the callbacks to finish...")
    
    t_timeout = time.time() + 10.0
    while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks < 30:
        time.sleep(0.01)
    
    # assert if all callback functions were successfully finished
    assert t.noOfSuccessFullyFinishedCallbacks == 30
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    