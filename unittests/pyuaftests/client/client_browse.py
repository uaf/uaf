import pyuaf
import time
import thread

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.util.opcuaidentifiers import OpcUaId_RootFolder, OpcUaId_ObjectsFolder
from pyuaf.client.requests import BrowseRequest, BrowseRequestTarget
from pyuaf.client.results  import BrowseResult,  BrowseResultTarget


def test(args):
    
    print("client.client_browse")
    
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
    
    print(" - testing pyuaf.client.Client().browse() for 3 addresses")
    
    result = client.browse([address_RootFolder, address_ObjectsFolder, address_AllDataTypesStatic])
    
    assert result.overallStatus.isGood()
    
    assert len(result.targets[1].references) > 10
    
    assert len(result.targets[2].references) > 10
    
    if args.verbose:
        print result
    
    print(" - testing pyuaf.client.Client().processRequest(<BrowseRequest>) for 3 addresses")
    
    request = BrowseRequest(3) 
    
    request.targets[0].address = address_RootFolder
    request.targets[1].address = address_ObjectsFolder
    request.targets[2].address = address_AllDataTypesStatic
    request.serviceConfig.serviceSettings.maxReferencesToReturn = 3 # ridiculously low, to force automatic BrowseNext calls
    request.serviceConfig.serviceSettings.maxAutoBrowseNext = 100
    
    result = client.processRequest(request)
    
    assert result.overallStatus.isGood()
    
    assert len(result.targets[1].references) > 10
    
    assert len(result.targets[2].references) > 10
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    