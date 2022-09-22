import pyuaf
import time
import _thread, threading
import unittest
from pyuaf.util.unittesting import parseArgs


from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName
from pyuaf.util import DateTime, DataValue
from pyuaf.client.requests import HistoryReadRawModifiedRequest, HistoryReadRawModifiedRequestTarget
from pyuaf.client.results  import HistoryReadRawModifiedResult,  HistoryReadRawModifiedResultTarget



ARGS = parseArgs()


def suite(args=None):
    if args is not None:
        global ARGS
        ARGS = args

    return unittest.TestLoader().loadTestsFromTestCase(HistoryReadRawModifiedTest)




class HistoryReadRawModifiedTest(unittest.TestCase):


    def setUp(self):

        # create a new ClientSettings instance and add the localhost to the URLs to discover
        settings = pyuaf.client.settings.ClientSettings()
        settings.discoveryUrls.append(ARGS.demo_url)
        settings.applicationName = "client"
        settings.logToStdOutLevel = ARGS.loglevel

        self.client = pyuaf.client.Client(settings)

        serverUri    = ARGS.demo_server_uri
        demoNsUri    = ARGS.demo_ns_uri

        self.address_demo     = Address(NodeId("Demo"                           , demoNsUri), serverUri)
        self.address_startSim = Address(NodeId("Demo.StartSimulation"           , demoNsUri), serverUri)
        self.address_stopSim  = Address(NodeId("Demo.StopSimulation"            , demoNsUri), serverUri)
        self.address_history  = Address(NodeId("Demo.History"                   , demoNsUri), serverUri)
        self.address_startLog = Address(NodeId("Demo.History.StartLogging"      , demoNsUri), serverUri)
        self.address_stopLog  = Address(NodeId("Demo.History.StopLogging"       , demoNsUri), serverUri)
        self.address_byte     = Address(NodeId("Demo.History.ByteWithHistory"   , demoNsUri), serverUri)
        self.address_double   = Address(NodeId("Demo.History.DoubleWithHistory" , demoNsUri), serverUri)

        # start the simulation and the logging
        self.assertTrue( self.client.call(self.address_demo, self.address_startSim).overallStatus.isGood() )
        self.client.call(self.address_history, self.address_startLog).overallStatus.isGood()

        self.startTime = time.time()

        # sleep a little more than a second, to make sure we have some historical data
        time.sleep(2)


    def test_client_Client_historyReadRaw(self):

        result = self.client.historyReadRaw([self.address_byte, self.address_double], # addresses
                                            DateTime(time.time() - 1.0),              # startTime
                                            DateTime(time.time()))                    # endTime

        self.assertTrue( result.overallStatus.isGood() )
        self.assertGreater( len(result.targets[0].dataValues) , 0 )
        self.assertGreater( len(result.targets[1].dataValues) , 0 )


    def test_client_Client_processRequest_some_historyReadRawModifiedRequest(self):

        request = HistoryReadRawModifiedRequest(2)

        request.targets[0].address = self.address_byte
        request.targets[1].address = self.address_double
        request.serviceSettingsGiven = True
        serviceSettings = pyuaf.client.settings.HistoryReadRawModifiedSettings()
        serviceSettings.startTime = DateTime(time.time() - 1.0)
        serviceSettings.endTime   = DateTime(time.time())
        request.serviceSettings = serviceSettings
        result = self.client.processRequest(request)

        self.assertTrue( result.overallStatus.isGood() )
        self.assertGreater( len(result.targets[0].dataValues) , 0 )
        self.assertGreater( len(result.targets[1].dataValues) , 0 )


    def test_client_Client_processRequest_some_historyReadRawModifiedRequest_with_automatic_continuation(self):

        request = HistoryReadRawModifiedRequest(2)

        request.targets[0].address = self.address_byte
        request.targets[1].address = self.address_double

        request.serviceSettingsGiven = True
        serviceSettings = pyuaf.client.settings.HistoryReadRawModifiedSettings()
        serviceSettings.startTime        = DateTime(self.startTime)
        serviceSettings.endTime          = DateTime(time.time())
        serviceSettings.maxAutoReadMore  = 20
        serviceSettings.numValuesPerNode = 1   # ridiculously low, to force automatic calls
        request.serviceSettings = serviceSettings

        result = self.client.processRequest(request)

        self.assertTrue( result.overallStatus.isGood() )
        self.assertGreater( len(result.targets[0].dataValues) , 0 )
        self.assertGreater( len(result.targets[1].dataValues) , 0 )
        self.assertGreater( result.targets[0].autoReadMore , 0 )
        self.assertGreater( result.targets[1].autoReadMore , 0 )

    def test_client_Client_processRequest_some_historyReadRawModifiedRequest_with_manual_continuation(self):

        request = HistoryReadRawModifiedRequest(1)

        request.targets[0].address = self.address_byte
        serviceSettings = pyuaf.client.settings.HistoryReadRawModifiedSettings()
        serviceSettings.startTime        = DateTime(self.startTime)
        serviceSettings.endTime          = DateTime(time.time())
        serviceSettings.maxAutoReadMore  = 0   # force no automatic calls by the UAF
        serviceSettings.numValuesPerNode = 1   # ridiculously low, to force automatic calls

        request.serviceSettingsGiven = True
        request.serviceSettings = serviceSettings

        noOfManualBrowseNext = 0
        allData = pyuaf.util.DataValueVector()

        result = self.client.processRequest(request)

        while len(result.targets[0].continuationPoint) > 0 and noOfManualBrowseNext < 50:

            request.targets[0].continuationPoint = result.targets[0].continuationPoint

            result = self.client.processRequest(request)

            for i in range(len(result.targets[0].dataValues)):
                # IMPORTANT: use     <DataValueVector>.allData.append(result.targets[0].dataValues[i])
                #            or      <Python list>.append(DataValue(result.targets[0].dataValues[i]))
                #            but NOT <Python list>.append(result.targets[0].dataValues[i]))
                #
                #            because <Python list>.append() will NOT COPY THE DATA! It will only
                #            store the the pointer that was returned by (...).dataValues[i]!
                allData.append(result.targets[0].dataValues[i])

            noOfManualBrowseNext += 1

        self.assertTrue( result.overallStatus.isGood() )
        self.assertGreater( len(allData) , 2 )
        self.assertGreater( noOfManualBrowseNext , 0 )


    def tearDown(self):
        # stop the simulation and the logging
        self.assertTrue( self.client.call(self.address_demo   , self.address_stopSim).overallStatus.isGood() )
        self.assertTrue( self.client.call(self.address_history, self.address_stopLog).overallStatus.isGood() )

        # delete the client instances manually (now!) instead of letting them be garbage collected
        # automatically (which may happen during a another test, and which may cause logging output
        # of the destruction to be mixed with the logging output of the other test).
        del self.client




if __name__ == '__main__':
    unittest.TextTestRunner(verbosity = ARGS.verbosity).run(suite())

