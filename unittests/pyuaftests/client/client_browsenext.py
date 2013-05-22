import pyuaf
import time
import thread

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.util.opcuaidentifiers import OpcUaId_RootFolder, OpcUaId_ObjectsFolder
from pyuaf.client.requests import BrowseRequest, BrowseRequestTarget
from pyuaf.client.requests import BrowseNextRequest, BrowseNextRequestTarget
from pyuaf.client.results  import BrowseResult,  BrowseResultTarget


def test(args):
    
    print("client.client_browsenext")
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)

    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    
    address_RootFolder         = Address(NodeId(OpcUaId_RootFolder, 0), serverUri)
    address_ObjectsFolder      = Address(NodeId(OpcUaId_ObjectsFolder, 0), serverUri)
    address_AllDataTypesStatic = Address(NodeId("AllDataTypesStatic", demoNsUri), serverUri)
    
    print(" - testing pyuaf.client.Client().processRequest(<BrowseNextRequest>)")
    
    originalRequest = BrowseRequest(1) 
    
    originalRequest.targets[0].address = address_AllDataTypesStatic
    originalRequest.serviceConfig.serviceSettings.maxReferencesToReturn = 3 # ridiculously low, to force continuationPoints
    originalRequest.serviceConfig.serviceSettings.maxAutoBrowseNext = 0     # meaning: no automatic BrowseNext
    
    result = client.processRequest(originalRequest)
    
    assert result.overallStatus.isGood()
    
    assert len(result.targets[0].continuationPoint) > 0
    
    noOfManualBrowseNext = 0
    
    while len(result.targets[0].continuationPoint) > 0:
    
        result = client.browseNext([originalRequest.targets[0].address], [result.targets[0].continuationPoint])
    
        #nextRequest = BrowseNextRequest(1)
        #nextRequest.targets[0].address           = originalRequest.targets[0].address
        #nextRequest.targets[0].continuationPoint = result.targets[0].continuationPoint
        #result = client.processRequest(nextRequest)
        
        noOfManualBrowseNext += 1
    
    # we should have invoked BrowseNext at least 3 times!
    assert noOfManualBrowseNext > 3
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    