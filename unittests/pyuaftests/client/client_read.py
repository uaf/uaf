import pyuaf
import time
import thread

from pyuaf.util import NodeId, Address, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers
from pyuaf.client.requests import ReadRequest, ReadRequestTarget
from pyuaf.client.results  import ReadResult,  ReadResultTarget

def test(args):
    
    print("client.client_read")
    
    # create a new ClientSettings instance and add the localhost to the URLs to discover
    settings = pyuaf.client.settings.ClientSettings()
    settings.discoveryUrls.append(args.demo_url)
    settings.applicationName = "client"
    settings.logToStdOutLevel = args.loglevel
    
    client = pyuaf.client.Client(settings)


    serverUri = args.demo_server_uri
    demoNsUri = args.demo_ns_uri
    plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    
    # define some simple standard nodes
    id0 = NodeId(opcuaidentifiers.OpcUaId_Server_Auditing, 0)
    id1 = NodeId(opcuaidentifiers.OpcUaId_Server_ServerCapabilities_MaxHistoryContinuationPoints, 0)
    address0 = Address(ExpandedNodeId(id0, serverUri))
    address1 = Address(ExpandedNodeId(id1, serverUri))

    print(" - testing pyuaf.client.Client().read() for a single standard node (based on a NodeId)")
    
    res0 = client.read(address0)
    assert res0.targets[0].data.value == False
    
    if args.verbose:
        print res0

    res1 = client.read(address1)
    assert res1.targets[0].status.isGood() == True
    
    if args.verbose:
        print res1

    print(" - testing pyuaf.client.Client().read() for some standard nodes (based on NodeIds)")
    
    res0res1 = client.read([address0, address1])
    assert res0res1.targets[0].data.value == False
    assert res0res1.targets[1].status.isGood() == True
    

    print(" - testing pyuaf.client.Client().read() for some non-standard nodes (based on NodeIds)")
    
    id2 = NodeId("MyDemoObject.Counter", 4)
    id3 = NodeId("MyDemoObject.Temperature", demoNsUri)
    address2 = Address(ExpandedNodeId(id2, serverUri))
    address3 = Address(ExpandedNodeId(id3, serverUri))
    
    res2res3 = client.read([address2, address3])
    
    assert res2res3.overallStatus.isGood()
    
    
    print(" - testing pyuaf.client.Client().read() for the ServerArray")
    
    id4 = NodeId(opcuaidentifiers.OpcUaId_Server_ServerArray, 0)
    node4 = Address(ExpandedNodeId(id4, serverUri))
    res4 = client.read([node4])
    
    assert res4.overallStatus.isGood()
    
    
    print(" - testing pyuaf.client.Client().read() for a node (based on a RelativePath)")
    
    # create the starting node
    id5 = NodeId("MyDemoObject", demoNsUri)
    start5 = Address(ExpandedNodeId(id5, serverUri))
    
    # create the relative path
    name5 = QualifiedName("Counter", demoNsUri)
    elem5 = RelativePathElement(name5)
    path5 = [elem5]
    
    # create the node to be read
    node5 = Address(start5, path5)
    
    # read the node
    res5 = client.read(node5)
    
    # assert the result
    assert res5.targets[0].data.type() == pyuaf.util.opcuatypes.UInt32
    assert res5.targets[0].status.isGood()
    assert res5.overallStatus.isGood()
    
    print(" - testing pyuaf.client.Client().read() for a node (based on a complex RelativePath)")
    
    # create the starting node
    start6 = Address(ExpandedNodeId("PLC1", demoNsUri, serverUri))
    
    # create the relative path elements
    elem6a = RelativePathElement(QualifiedName("Programs", plcOpenNsUri))
    elem6b = RelativePathElement(QualifiedName("MAIN", demoNsUri))
    path6  = [elem6a, elem6b]
    
    # create the node pointing to MAIN
    node6 = Address(start6, path6)
    
    # use this node as a starting node for another relative path
    elem7a = RelativePathElement(QualifiedName("fbBoiler1", demoNsUri))
    elem7b = RelativePathElement(QualifiedName("Drum1001", demoNsUri))
    elem7c = RelativePathElement(QualifiedName("LI1001", demoNsUri))
    elem7d = RelativePathElement(QualifiedName("DataItem", demoNsUri))
    path7  = [elem7a, elem7b, elem7c, elem7d]
    
    # create the final node, of which the value must be read
    node7 = Address(node6, path7)
    
    # read the node
    res7 = client.read(node7)
    
    # assert the result
    assert res7.targets[0].data.type() == pyuaf.util.opcuatypes.Float
    assert res7.targets[0].status.isGood()
    assert res7.overallStatus.isGood()
    
    print(" - testing pyuaf.client.Client().processRequest() for a ReadRequest")
    
    # create some targets to be read
    target8a = ReadRequestTarget(node6, pyuaf.util.attributeids.DisplayName)
    target8b = ReadRequestTarget(node7, pyuaf.util.attributeids.Historizing)
    
    # create the request
    req8 = ReadRequest([target8a, target8b])
    
    # process the request
    res8 = client.processRequest(req8)
    
    # assert the result
    assert res8.targets[0].data == pyuaf.util.LocalizedText("", "MAIN")
    assert res8.targets[1].data.value == False
    
    # delete the client instances manually (now!) instead of letting them be garbage collected 
    # automatically (which may happen during a another test, and which may cause logging output
    # of the destruction to be mixed with the logging output of the other test).
    del client
    