# examples/pyuaf/client/how_to_manually_connect_to_an_endpoint_without_discovery.py
"""
EXAMPLE: how to browse some nodes
====================================================================================================

A UAF client normally uses the discovery process to identify a server and connect to it.
The user therefore doesn't have to worry about connecting, disconnecting, session management, etc.

However, in certain cases you may want to connect manually to a specific endpoint, without using
the discovery process (i.e. without relying on the discovery endpoint of the server). 

This example will show you how to manually connect to the UaServerCPP demo server of Untified 
Automation, without any discovery involved. 

To run the example, start the UaServerCPP of UnifiedAutomation first on the same machine. 
($SDK/bin/uaservercpp, this executable is part of the SDK).
"""

import time, os, sys

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings
from pyuaf.util             import Address, NodeId
from pyuaf.util.errors      import UafError, ConnectionError


# define the ClientSettings (note that we do NOT provide a discoveryUrl!!!):
settings = ClientSettings()
settings.applicationName = "MyClient"
# settings.logToStdOutLevel = pyuaf.util.loglevels.Debug # uncomment to see the full UAF logging

# create the client
myClient = Client(settings)

# Now manually connect to an endpoint of the demo server using 'manuallyConnectToEndpoint()'.
#  - The first argument (endpointUrl) is the URL of the endpoint you want to connect to 
#  - The optional (!) second argument (sessionSettings) a SessionSettings instance.
#    If you don't provide one, then a default SessionSettings instance will be used.
#    A default SessionSettings instance has:
#     - no security policy (pyuaf.util.securitypolicies.UA_None)
#     - no security mode (pyuaf.util.messagesecuritymodes.Mode_None)
#     - no authentication (pyuaf.util.usertokentypes.Anonymous)
try:
    print("")
    print("Now connecting")
    clientConnectionId = myClient.manuallyConnectToEndpoint("opc.tcp://localhost:48010")
except ConnectionError, e:
    # if an error was raised, then no Session has been created! 
    # In other words, the client is back in it's original state, there is no 
    # session that tries to reconnect in the background.
    print(e)
    print("ConnectionError -> sys.exit()")
    sys.exit()
except UafError, e:
    print(e)
    print("UafError -> sys.exit()")
    sys.exit()


# The clientConnectionId is a number that identifies the session.
# You can use it to request some information about the Session that you just created:
try:
    print("")
    print("Now getting the session information")
    
    info = myClient.sessionInformation(clientConnectionId)
    
    print("")
    print("SessionInformation:")
    print(info)
    
except UafError, e:
    print("Couldn't read the session information: %s" %e)
    print("Exiting...")
    sys.exit()


# now use the server URI to read some variables
try:
    print("")
    print("Now reading some variables")
    
    # define the namespace URI of the UaDemoServer:
    demoNsUri = "http://www.unifiedautomation.com/DemoServer"
    
    # define some addresses:
    someDoubleNode = Address( NodeId("Demo.Static.Scalar.Double", demoNsUri), info.serverUri )
    someUInt32Node = Address( NodeId("Demo.Static.Scalar.UInt32", demoNsUri), info.serverUri )
    
    # read the nodes of the addresses:
    result = myClient.read([someDoubleNode, someUInt32Node])
    
    print("")
    print("ReadResult:")
    print(result)
    
except UafError, e:
    print("Couldn't read some variables: %s" %e)
    print("Exiting...")
    sys.exit()


