import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import AsyncReadRequest, ReadRequestTarget
from pyuaf.client.results  import AsyncReadResult,  ReadResultTarget
from pyuaf.util.primitives import Byte, Int32, Float


ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(ClientAsyncReadTest)


class MyClient(pyuaf.client.Client):

    def __init__(self, settings):
        pyuaf.client.Client.__init__(self, settings)
        self.lock = threading.Lock()
        self.noOfReadCompletes = 0

    def readComplete(self, result):
        self.lock.acquire()
        self.noOfReadCompletes += 1
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


class ClientAsyncReadTest(unittest.TestCase):


    def setUp(self):

        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = MyClient(settings)


        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri
        plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"

        self.address_Scalar = Address(ExpandedNodeId("Demo.Static.Scalar", demoNsUri, serverUri))
        self.address_Byte   = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Byte", demoNsUri))] )
        self.address_Int32  = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Int32", demoNsUri))] )
        self.address_Float  = Address(self.address_Scalar, [RelativePathElement(QualifiedName("Float", demoNsUri))] )

        self.target0  = ReadRequestTarget(self.address_Byte)
        self.target1  = ReadRequestTarget(self.address_Int32)
        self.target2  = ReadRequestTarget(self.address_Float)
        self.request = AsyncReadRequest([self.target0, self.target1, self.target2])

    def test_client_Client_processRequest_for_an_async_read_request(self):
        asyncResult = self.client.processRequest(self.request)

        # wait for the result
        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and self.client.noOfReadCompletes == 0:
            time.sleep(0.01)

        # assert if the read was received
        self.assertEqual( self.client.noOfReadCompletes , 1 )


    def test_client_Client_processRequest_for_an_async_read_request_with_callback(self):
        t = TestClass()
        asyncResult = self.client.processRequest(self.request, t.myCallback)

        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks == 0:
            time.sleep(0.01)

        # assert if the callback function was successfully finished
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 1 )


    def test_client_Client_beginRead(self):
        t = TestClass()
        asyncResult = self.client.beginRead([self.address_Byte, self.address_Int32, self.address_Float], callback=t.myCallback)

        t_timeout = time.time() + 5.0
        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks == 0:
            time.sleep(0.01)

        # assert if the callback function was successfully finished
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 1 )


    def test_client_Client_processRequest_for_an_async_read_request_with_long_lasting_callback_many_times_in_parallel(self):

        t = LongLastingTestClass()

        # start 30 processes
        for i in range(30):
            self.client.processRequest(self.request, t.myCallback)

        # sleep while the callbacks are running
        t_timeout = time.time() + 10.0
        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks < 30:
            time.sleep(0.01)

        # assert if all callback functions were successfully finished
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 30 )


    def test_client_Client_beginRead_with_long_lasting_callback_many_times_in_parallel(self):

        t = LongLastingTestClass()

        # start 30 processes
        for i in range(30):
            self.client.beginRead([self.address_Byte, self.address_Int32, self.address_Float], callback=t.myCallback)

        # sleep while the callbacks are running
        t_timeout = time.time() + 10.0
        while time.time() < t_timeout and t.noOfSuccessFullyFinishedCallbacks < 30:
            time.sleep(0.01)

        # assert if all callback functions were successfully finished
        self.assertEqual( t.noOfSuccessFullyFinishedCallbacks , 30 )

    def tearDown(self):
        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client



if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())