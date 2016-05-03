# examples/pyuaf/client/how_to_monitor_data_changes.py

# Start the demo server ($SDK/bin/uaservercpp) of Unified Automation before running this script!
import time
import pyuaf
from pyuaf.util             import Address, NodeId, DataChangeFilter
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SubscriptionSettings, MonitoredItemSettings
from pyuaf.client.requests  import CreateMonitoredDataRequestTarget

# define the namespace URI and server URI of the UaServerCPP demo server
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"
demoNamespaceUri = "http://www.unifiedautomation.com/DemoServer/"

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)


# 1) optionally: configure the subscription
# ------------------------------------------
subSettings = SubscriptionSettings()
subSettings.publishingIntervalSec = 1.0 
subSettings.maxKeepAliveCount = 5
 
# Explanation:
# - The subscription will send at most one bunch of changed data samples per second, due to the 
#   publishing interval of 1 second.
# - If the sampled data does not change, then the server does not have to send notifications to 
#   the client. However, when the sampled data does not change for 5 seconds in a row 
#   (5 seconds = maxKeepAliveCount * publishingIntervalSec), then the server 
#   will send a KeepAlive notification to the client, as a kind of "heartbeat".


# 2) configure the monitored items
# --------------------------------
target0 = CreateMonitoredDataRequestTarget()
target0.address = Address( NodeId("Demo.Dynamic.Scalar.Float", demoNamespaceUri), demoServerUri )
target0.queueSize = 5
target0.samplingIntervalSec = 0.2
target0.discardOldest = True

filter = DataChangeFilter()
filter.deadBandType = DataChangeFilter.DeadBandType_Absolute
filter.deadBandValue = 0.1
target0.dataChangeFilter = filter

# Explanation:
# The variable we will monitor, must be sampled 5 times per second (see samplingIntervalSec of 0.2 seconds).
# Note that this is 5 times faster than the publishing interval of the subscription! Indeed, to make 
# the data transmission more efficient, OPC UA will bundle (in this case) up to 5 data changes in one
# transmission, every second. 
# Of course, it means that we need to instruct the server to reserve a queue, so it can store up to 5 samples 
# per second (cfr. 'queueSize'). 
# If the queue would overflow (which is theoretically not possible in the above case), it would discard
# the oldest values, due to the 'discardOldest' setting.
# To make sure that the server is not sending irrelevant data changes (e.g. noise), we have
# also specified a filter. In this case, if the value changes are smaller than 0.1 (in absolute value),
# no notifications will be sent.

target1 = CreateMonitoredDataRequestTarget()
target1.address = Address( NodeId("Demo.Dynamic.Scalar.String", demoNamespaceUri), demoServerUri )

# 3) define our callbacks:
# ------------------------

def keepAliveReceivedCallback(notification):
    # notification is of type pyuaf.client.KeepAliveNotification
    print("No data changes have been received, but the subscription is still alive!")

def floatChangeReceivedCallback(notification):
    # notification is of type pyuaf.client.DataChangeNotification
    print("New float has been received: %.1f" %notification.data.value)

def stringChangeReceivedCallback(notification):
    # notification is of type pyuaf.client.DataChangeNotification
    print("New string has been received: %s" %notification.data.value)
    
# 4) create the request and start monitoring some variable(s)
# -----------------------------------------------------------

# start listening for KeepAlive messages
myClient.registerKeepAliveCallback(keepAliveReceivedCallback)

# configure the request
request = pyuaf.client.requests.CreateMonitoredDataRequest()
request.subscriptionSettings = subSettings
request.subscriptionSettingsGiven = True
request.targets.append(target0)
request.targets.append(target1)

# start listening to changes of both targets:
myClient.processRequest(request, notificationCallbacks=[floatChangeReceivedCallback, stringChangeReceivedCallback])

# listen for some seconds:
time.sleep(10)

# No need to remove subscriptions or monitored items manually:
# when the client is garbage collected, they will be removed automatically.

