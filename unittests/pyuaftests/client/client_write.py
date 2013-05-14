import pyuaf
import time
import thread

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import WriteRequest, WriteRequestTarget
from pyuaf.client.results  import WriteResult,  WriteResultTarget
from pyuaf.util.primitives import Byte, Int32, Float

def test(args):
    
    print("client.client_write")
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)


    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    
    print(" - testing pyuaf.client.Client().write() for some addresses")
    
    address_AnalogStatic   = Address(ExpandedNodeId("AnalogStatic", demoNsUri, serverUri))
    address_Byte           = Address(address_AnalogStatic, [RelativePathElement(QualifiedName("StaticAnalogByte", demoNsUri))] )
    address_Int32          = Address(address_AnalogStatic, [RelativePathElement(QualifiedName("StaticAnalogInt32", demoNsUri))] )
    address_Float          = Address(address_AnalogStatic, [RelativePathElement(QualifiedName("StaticAnalogFloat", demoNsUri))] )
    
    result = client.write([address_Byte, address_Int32, address_Float],  [Byte(2), Int32(-123), Float(1.2)])
    
    if args.verbose:
        print result
    
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    