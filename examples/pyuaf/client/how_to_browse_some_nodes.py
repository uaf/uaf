# examples/pyuaf/client/how_to_browse_some_nodes.py
"""
EXAMPLE: how to browse some nodes
====================================================================================================

A UAF Client can browse nodes in two ways:
  - either using the "convenience" method: browse()
  - or using the "generic" method: processRequest() 

The "convenience" methods (such as read(), write(), call(), ...) are conveniently to use 
 (since they accept the most frequently used parameters directly), 
but they are less powerful than the "generic" processRequest() method 
 (since this method accepts ReadRequests, WriteRequests, etc. that can be fully configured).

In this example, we will use both ways to browse nodes.

As will be shown in this example, the UAF can automatically take care of BrowseNext calls,
so as a user you don't have to worry about incomplete Browse results!

To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine. 
($SDK/bin/uaservercpp, this executable is part of the SDK).
"""

import time, os, sys

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, BrowseSettings, SessionSettings
from pyuaf.client.requests  import BrowseRequest, BrowseRequestTarget
from pyuaf.util             import Address, NodeId
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers
from pyuaf.util.errors      import UafError


# define the namespace URI and server URI of the UaServerCPP demo server
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"

# define the address of the Root node which we would like to start browsing
rootNode = Address( NodeId(opcuaidentifiers.OpcUaId_RootFolder, 0), demoServerUri )

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)



try:
    print("")
    print("First option: use the convenience function \"browse()\"")
    print("===================================================")
    
    # now browse the root node
    # (notice that there is also an argument called 'maxAutoBrowseNext', which we don't mention
    #  here because we can leave it at the default value (100), to make sure that BrowseNext is 
    # automatically being called for us as much as needed!)
    firstLevelBrowseResult = myClient.browse([rootNode])
    
    # Notice too that you can optionally provide a BrowseSettings and/or a SessionSettings argument
    # for more detailed configuration, like this:
    # OPTIONAL: let's specify a small call timeout, since the UaDemoServer is running 
    #           on the local machine anyway:
    browseSettings = BrowseSettings()
    browseSettings.callTimeoutSec = 2.0
    # OPTIONAL: and finally let's also specify that sessions should have a timeout of 600 seconds:
    sessionSettings = SessionSettings()
    sessionSettings.sessionTimeoutSec = 600.0
    # now call the browse() function:
    myClient.browse([rootNode], browseSettings = browseSettings, sessionSettings = sessionSettings)
    
    # print the result
    print(" - Browse result of the first level:")
    print("   ---------------------------------")
    print(firstLevelBrowseResult)
    
    # we don't expect that "manual" BrowseNext calls are still needed, as the UAF will
    # have done the BrowseNext calls up to 100 times automatically for us! If there would still be
    # some continuation points left, then we surely have some unexpected problem!
    assert len(firstLevelBrowseResult.targets[0].continuationPoint) == 0
    
    # we can now continue browsing the other nodes that we discovered, all simultaneously!!!
    noOfFoundReferences = len(firstLevelBrowseResult.targets[0].references)
    newNodesToBeBrowsed = []
    for i in xrange(noOfFoundReferences):
        newNodesToBeBrowsed.append( Address(firstLevelBrowseResult.targets[0].references[i].nodeId) )
    
    secondLevelBrowseResult = myClient.browse(newNodesToBeBrowsed)
    
    # print the result
    print(" - Browse result of the second level:")
    print("   ----------------------------------")
    print(secondLevelBrowseResult)
    
    
    print("")
    print("Second option: use the generic function \"processRequest()\"")
    print("==========================================================")
    
    # create a request with 1 target, and re-use the browseSettings and sessionSettings 
    # which we created earlier:
    firstLevelBrowseRequest = BrowseRequest(1)
    firstLevelBrowseRequest.targets[0].address = rootNode
    firstLevelBrowseRequest.serviceSettings = browseSettings
    firstLevelBrowseRequest.sessionSettings = sessionSettings
    
    # process the request
    firstLevelBrowseResult = myClient.processRequest(firstLevelBrowseRequest)
    
    # print the result
    print(" - Browse result of the first level:")
    print("   ---------------------------------")
    print(firstLevelBrowseResult)
    
    # we don't expect that "manual" BrowseNext calls are still needed, as the UAF will
    # have done the BrowseNext calls up to 100 times automatically for us! If there would still be
    # some continuation points left, then we surely have some unexpected problem!
    assert len(firstLevelBrowseResult.targets[0].continuationPoint) == 0
    
    # we can now continue browsing the other nodes that we discovered, all simultaneously!!!
    noOfFoundReferences = len(firstLevelBrowseResult.targets[0].references)
    secondLevelBrowseRequest = BrowseRequest(noOfFoundReferences)
    for i in xrange(noOfFoundReferences):
        secondLevelBrowseRequest.targets[i].address = Address(firstLevelBrowseResult.targets[0].references[i].nodeId)
    
    secondLevelBrowseResult =  myClient.processRequest(secondLevelBrowseRequest)
    
    # print the result
    print(" - Browse result of the second level:")
    print("   ----------------------------------")
    print(secondLevelBrowseResult)
    
    
except UafError, e:
    print("Some error occurred: %s" %e)
    raise



