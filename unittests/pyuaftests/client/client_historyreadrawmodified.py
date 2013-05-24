import pyuaf
import time
import thread

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName
from pyuaf.util import DateTime, DataValue
from pyuaf.client.requests import HistoryReadRawModifiedRequest, HistoryReadRawModifiedRequestTarget
from pyuaf.client.results  import HistoryReadRawModifiedResult,  HistoryReadRawModifiedResultTarget


def test(args):
    
    print("client.client_historyreadrawmodified")
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)

    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    
    address_CounterWithHistory = Address(NodeId("CounterWithHistory", demoNsUri), serverUri)
    
    # apparently, the counter starts only to keep history after we read it once
    result = client.read([address_CounterWithHistory])
    assert result.overallStatus.isGood()
    
    # sleep a little more than a second, to make sure we have some historical data
    time.sleep(1.5)
    
    print(" - testing pyuaf.client.Client().processRequest(<HistoryReadRawModifiedRequest>) for 2 addresses")
    
    request = HistoryReadRawModifiedRequest(2) 
    
    request.targets[0].address = address_CounterWithHistory
    request.targets[1].address = address_CounterWithHistory
    request.serviceConfig.serviceSettings.startTime = DateTime(time.time() - 1.0)
    request.serviceConfig.serviceSettings.endTime   = DateTime(time.time())
    
    result = client.processRequest(request)
    
    assert result.overallStatus.isGood()
    
    assert len(result.targets[0].dataValues) > 0
    assert len(result.targets[1].dataValues) > 0
    
    
    
    print(" - testing pyuaf.client.Client().processRequest(<HistoryReadRawModifiedRequest>) for 2 addresses,\n"
          "   while provoking automatic continuation point calls")
    
    request.serviceConfig.serviceSettings.maxAutoReadMore  = 20
    request.serviceConfig.serviceSettings.numValuesPerNode = 3   # ridiculously low, to force automatic calls
    
    result = client.processRequest(request)
    
    assert result.overallStatus.isGood()
    assert len(result.targets[0].dataValues) > 0
    assert len(result.targets[1].dataValues) > 0
    assert result.targets[0].autoReadMore > 0
    assert result.targets[1].autoReadMore > 0
    
    
    print(" - testing pyuaf.client.Client().processRequest(<HistoryReadRawModifiedRequest>) for 1 address,\n"
          "   while provoking manual continuation point calls")
    
    request.targets.resize(1)
    request.serviceConfig.serviceSettings.maxAutoReadMore  = 0
    request.serviceConfig.serviceSettings.numValuesPerNode = 3   # ridiculously low, to force automatic calls
    
    noOfManualBrowseNext = 0
    allData = pyuaf.util.DataValueVector()
    
    result = client.processRequest(request)
    
    while len(result.targets[0].continuationPoint) > 0 and noOfManualBrowseNext < 50:
        request.targets[0].continuationPoint = result.targets[0].continuationPoint
        
        result = client.processRequest(request)
        
        for i in xrange(len(result.targets[0].dataValues)):
            # IMPORTANT: use     <DataValueVector>.allData.append(result.targets[0].dataValues[i])
            #            or      <Python list>.append(DataValue(result.targets[0].dataValues[i]))
            #            but NOT <Python list>.append(result.targets[0].dataValues[i]))
            #            
            #            because <Python list>.append() will NOT COPY THE DATA! It will only 
            #            store the the pointer that was returned by (...).dataValues[i]! 
            allData.append(result.targets[0].dataValues[i])
        
        noOfManualBrowseNext += 1
    
    assert result.overallStatus.isGood()
    assert len(allData) > 5
    assert noOfManualBrowseNext > 0
    
    
    
    
    
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    