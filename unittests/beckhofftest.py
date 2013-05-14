import pyuaf
import time
import threading
import sys

from pyuaf.util import NodeId, Node, ExpandedNodeId, BrowsePath, \
                       RelativePathElement, QualifiedName, opcuaidentifiers


class MyClient(pyuaf.client.Client):

    def __init__(self, settings, verbose):
        pyuaf.client.Client.__init__(self, settings)
        self.verbose = verbose
        self.noOfSuccessFullyReceivedNotifications = 0
            
    def dataChangesReceived(self, notifications):
        self.noOfSuccessFullyReceivedNotifications += len(notifications)
        if self.verbose:
            print("***** dataChangesReceived started *****")
            for i in xrange(len(notifications)):
                print("Notification %d:" %i)
                print(notifications[i])
            print("***** dataChangesReceived finished *****")

VERBOSE = sys.argv[-1] == "-v"
    
if VERBOSE:
    ll = pyuaf.util.loglevels.Debug
else:
    ll = pyuaf.util.loglevels.Disabled

    
# create a new ClientSettings instance and add the localhost to the URLs to discover
settings = pyuaf.client.settings.ClientSettings()
settings.discoveryUrls.append("opc.tcp://10.33.178.91:4840")
settings.applicationName = "client"
if VERBOSE:
    settings.logToStdOutLevel = pyuaf.util.loglevels.Debug

myClient = MyClient(settings, VERBOSE)

serverUri = "MAIA_IC/Beckhoff/TcOpcUaServer/1"

plcOpenNsUri = "http://PLCopen.org/OpcUa/IEC61131-3/"
    

node0 = Node(ExpandedNodeId(".HalfSecCounterValue", 4, serverUri))
node1 = Node(ExpandedNodeId(".OneSecCounterValue", 4, serverUri))
    
    
myClient.createMonitoredData([node0, node1])

time.sleep(10000)

