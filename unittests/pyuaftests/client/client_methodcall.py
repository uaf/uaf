import pyuaf
import time
import thread

from .. import testresults

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import MethodCallRequest, MethodCallRequestTarget
from pyuaf.client.results  import MethodCallResult,  MethodCallResultTarget
from pyuaf.util.primitives import Int32
from pyuaf.util.opcuaidentifiers import OpcUaId_ObjectsFolder


def test(args):
    
    print("client.client_methodcall")
    
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)


    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    
    print(" - testing pyuaf.client.Client().call()")
    
    address_Objects        = Address(ExpandedNodeId(OpcUaId_ObjectsFolder, 0, serverUri))
    address_MyDemoObject   = Address(address_Objects, [RelativePathElement(QualifiedName("MyDemoObject", demoNsUri))] )
    address_SetAllValues   = Address(address_MyDemoObject, [RelativePathElement(QualifiedName("SetAllValues", demoNsUri))] )
    
    result = client.call(address_MyDemoObject, address_SetAllValues, [Int32(-123)])
    
    assert result.targets[0].outputArguments[0].value == 1
    
    if args.verbose:
        print result
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    