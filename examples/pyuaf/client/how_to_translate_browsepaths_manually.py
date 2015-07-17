# examples/pyuaf/client/how_to_translate_browsepaths_manually.py
"""
EXAMPLE: how to translate browsepaths *manually*
====================================================================================================

One of the features of (py)UAF is that browsepaths are automatically translated by the client when
needed. So you can simply read/write/monitor/... a browsepath, and the UAF will automatically
translate them before invoking the read/write/monitor/... service.

Bottomline: this example is only relevant in the rare cases where you want to translate browsepaths
manually, for some reason...
"""

import time, os

import pyuaf
from pyuaf.client                import Client
from pyuaf.client.settings       import ClientSettings
from pyuaf.client.requests       import TranslateBrowsePathsToNodeIdsRequest
from pyuaf.util                  import Address, NodeId, RelativePathElement, QualifiedName, BrowsePath, ExpandedNodeId
from pyuaf.util                  import primitives
from pyuaf.util.errors           import UafError
from pyuaf.util.opcuaidentifiers import OpcUaId_RootFolder
from pyuaf.util.constants        import OPCUA_NAMESPACE_URI


# define the namespace URI and server URI of the UaDemoServer
demoNsUri     = "http://www.unifiedautomation.com/DemoServer"
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"

# define a browse path to the HeaterStatus node
myStartingPoint = ExpandedNodeId( NodeId(OpcUaId_RootFolder, OPCUA_NAMESPACE_URI), demoServerUri )
myRelativePath  = [ RelativePathElement(QualifiedName("Objects"     , OPCUA_NAMESPACE_URI)),
                    RelativePathElement(QualifiedName("Demo"        , demoNsUri)),
                    RelativePathElement(QualifiedName("BoilerDemo"  , demoNsUri)),
                    RelativePathElement(QualifiedName("Boiler1"     , demoNsUri)),
                    RelativePathElement(QualifiedName("HeaterStatus", demoNsUri)) ]
myBrowsePath = BrowsePath(myStartingPoint, myRelativePath)

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")
# settings.logToStdOutLevel = pyuaf.util.loglevels.Debug # uncomment for seeing debugging information

# create the client
myClient = Client(settings)

# create a request with one target
request = TranslateBrowsePathsToNodeIdsRequest(1)
request.targets[0].browsePath = myBrowsePath

# invoke the request
try:
    result = myClient.processRequest(request)

    if result.overallStatus.isGood():
        print("The browse path was translated into the following ExpandedNodeIds:")
        for expandedNodeId in result.targets[0].expandedNodeIds:
            print(" - %s" %expandedNodeId)
        
        print("")
        print("Full translation result:")
        print(result)
    else:
        print("Problem when translating the target: %s" %result.targets[0].status)

except UafError, e:
    print("Some error occurred!")
    raise


# As mentioned in the top description of this example, in most cases you don't need to translate
# browsepaths manually. You can simply read/write/monitor/... the node directly:
try:
    readResult = myClient.read( Address(myBrowsePath) )
    print("")
    print("Full read result:")
    print(readResult)
except UafError, e:
    print("Some error occurred!")
    raise

# Note: in fact, during the above myClient.read() call, no translation request is being sent 
# to the server, because the UAF had already internally cached the translation results during 
# the myClient.processRequest() invocation. 
# Of course, if the browsepath wouldn't have been cached, the UAF *would* have automatically
# sent a translation request to the server prior to reading the data. So the UAF takes care
# of translating browsepaths in the most efficient way, all done automatically for you!

