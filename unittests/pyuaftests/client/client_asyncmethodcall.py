import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import AsyncMethodCallRequest
from pyuaf.client.results  import MethodCallResult,  MethodCallResultTarget
from pyuaf.util.primitives import Double, UInt32


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.lock = threading.Lock()
        self.noOfCallCompletes = 0

    def callComplete(self, result):
        self.lock.acquire()
        self.noOfCallCompletes += 1
        self.lock.release()


# define a TestClass with a callback
class TestClass:
    def __init__(self):
        self.lock = threading.Lock()
        self.noOfSuccessFullyFinishedCallbacks = 0

    def myCallback(self, result):
        self.lock.acquire()
        self.noOfSuccessFullyFinishedCallbacks += 1
        self.lock.release()


# define a TestClass with a callback that lasts several seconds
class LongLastingTestClass:
    def __init__(self):
        self.noOfSuccessFullyFinishedCallbacks = 0
        self.lock = threading.Lock()

    def myCallback(self, result):
        time.sleep(2.0)
        self.lock.acquire()
        self.noOfSuccessFullyFinishedCallbacks += 1
        self.lock.release()


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientAsyncMethodCallTest)


class ClientAsyncMethodCallTest(unittest.TestCase):


    def setUp(self):
        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = MyClient(settings)

        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri

        self.address_Demo     = Address(ExpandedNodeId("Demo", demoNsUri, serverUri))
        self.address_Method   = Address(self.address_Demo, [RelativePathElement(QualifiedName("Method", demoNsUri))] )
        self.address_Multiply = Address(self.address_Method, [RelativePathElement(QualifiedName("Multiply", demoNsUri))] )
        self.address_SetSimulationSpeed = Address(self.address_Demo, [RelativePathElement(QualifiedName("SetSimulationSpeed", demoNsUri))] )

        self.request = AsyncMethodCallRequest(1)
        self.request.targets[0].objectAddress = self.address_Method
        self.request.targets[0].methodAddress = self.address_Multiply
        self.request.targets[0].inputArguments.append(Double(2.0))
        self.request.targets[0].inputArguments.append(Double(3.0))

    def test_client_Client_beginCall(self):

        result = self.client.beginCall(self.address_Method, self.address_Multiply, [Double(2.0), Double(3.0)])

        self.assertTrue( result.overallStatus.isGood() )

        t_timeout = time.time() + 5.0

        while time.time() < t_timeout and self.client.noOfCallCompletes == 0:
            time.sleep(0.01)

        # assert if the call was received
        self.assertEqual( self.client.noOfCallCompletes , 1 )



    def test_client_Client_beginCall_with_callback(self):
        t = TestClass()

        result = self.client.beginCall(self.address_Method, self.address_Multiply, [Double(2.0), Double(3.0)], callback=t.myCallback)

        self.assertTrue( result.overallStatus.isGood() )

        t_timeout = time.time() + 5.0

        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks == 0:
            time.sleep(0.01)

        # assert if the call was received
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 1 )


    def test_client_Client_beginCall_many_times_in_parallel_with_long_lasting_callback(self):
        t = LongLastingTestClass()

        # start 30 processes
        for i in range(30):
            result = self.client.beginCall(self.address_Method, self.address_Multiply, [Double(2.0), Double(3.0)], callback=t.myCallback)
            self.assertTrue( result.overallStatus.isGood() )

        t_timeout = time.time() + 10.0

        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks < 30:
            time.sleep(0.01)

        # assert if the calls were received
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 30 )


    def test_client_Client_processRequest_some_methodcall_request_many_times_in_parallel_with_long_lasting_callback(self):
        t = LongLastingTestClass()

        # start 30 processes
        for i in range(30):
            result = self.client.processRequest(self.request, resultCallback=t.myCallback)
            self.assertTrue( result.overallStatus.isGood() )

        t_timeout = time.time() + 10.0

        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks < 30:
            time.sleep(0.01)

        # assert if the calls were received
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 30 )



    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())