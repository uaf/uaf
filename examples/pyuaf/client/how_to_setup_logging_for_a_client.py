# examples/pyuaf/client/how_to_setup_logging_for_a_client.py
"""
Example: how to setup logging for a client
====================================================================================================

See the HTML documentation of PyUAF for more info!
""" 
import pyuaf
from pyuaf.util            import loglevels
from pyuaf.client          import Client
from pyuaf.client.settings import ClientSettings
from pyuaf.util            import Address, NodeId

# create a client that
#  - logs everything to the standard out ("stdout", i.e. the Windows DOS Prompt or the Linux shell)
#  - only logs warnings and errors to an external callback function
settings = ClientSettings()
settings.discoveryUrls.append("opc.tcp://localhost:4841")
settings.applicationName = "myClient"
settings.logToStdOutLevel = loglevels.Debug
settings.logToCallbackLevel = loglevels.Error

# define the callback for the logging
def myLoggingCallback(msg):
    print("************ CALLBACK SAYS: ************")
    if msg.level == loglevels.Error:
        print("Error message received: %s" %str(msg))
    elif msg.level == loglevels.Warning:
        print("Warning message received: %s" %str(msg))
    else:
        print("Info or debug message received: %s" %str(msg))

# create the client
myClient = Client(settings, myLoggingCallback)

# try to read the Value attribute of some non-existing node (so errors will be sent to the callback)
try:
    nodeId  = NodeId("NonExistingIdentifier","NonExistingNameSpace")
    address = Address(nodeId, "NonExistingServerURI")
    myClient.read( [address] )
except pyuaf.util.errors.UafError, e:
    print("UAF error raised: %s" %e)

# alternatively:
myClient2 = Client()
myClient2.registerLoggingCallback(myLoggingCallback)
myClient2.setClientSettings(settings)