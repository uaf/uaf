# examples/pyuaf/client/how_to_configure_all_settings.py
"""
EXAMPLE: how to configure the client/session/subscription/service settings
=================================================================================================

With PyUAF you can configure sessions, subscriptions and services (like read, write, ...) in
great detail. This example shows how to change them. 

This is an example to show you some more advanced feature of the UAF, you can skip it if you're 
happy with the default session/subscription/service settings of the UAF!
"""

import pyuaf
from pyuaf.util             import Address, NodeId
from pyuaf.util.primitives  import UInt32, Boolean
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings, SubscriptionSettings, \
                                   ReadSettings


# Some constants needed during the rest of this example:
NAMESPACE_URI = "http://www.unifiedautomation.com/DemoServer"
SERVER_URI = "urn:UnifiedAutomation:UaServerCpp"

# ==================================================================================================
# 1) Setting the defaults
# ==================================================================================================

# using ClientSettings, you can configure all default session/subscription and service settings:
clientSettings = ClientSettings()

# first configure some general client settings:
clientSettings.applicationName = "MyClient";
clientSettings.discoveryUrls.append("opc.tcp://localhost:48010")
# etc. ...

# now configure the default session settings:
clientSettings.defaultSessionSettings.sessionTimeoutSec = 100.0
clientSettings.defaultSessionSettings.connectTimeoutSec = 2.0
# etc. ...

# now configure the default subscription settings:
clientSettings.defaultSubscriptionSettings.publishingIntervalSec = 0.5
clientSettings.defaultSubscriptionSettings.lifeTimeCount         = 600
# etc. ...

# now configure the default settings for the Read service:
clientSettings.defaultReadSettings.callTimeoutSec = 2.0
clientSettings.defaultReadSettings.maxAgeSec      = 10.0

# same for the writeSettings, methodCallSettings, ...
clientSettings.defaultMethodCallSettings.callTimeoutSec = 2.0
clientSettings.defaultWriteSettings.callTimeoutSec = 2.0
clientSettings.defaultBrowseSettings.callTimeoutSec = 2.0
# and so on, and so on ...

# NOTE: for clientSettings, you may also configure SessionSettings for specific servers:
clientSettings.specificSessionSettings["My/Unreliable/Device/Server/URI"] = SessionSettings()
clientSettings.specificSessionSettings["My/Unreliable/Device/Server/URI"].sessionTimeoutSec = 200.0
clientSettings.specificSessionSettings["My/Unreliable/Device/Server/URI"].connectTimeoutSec = 5.0
# If the client connects to the server with ServerUri = "My/Unreliable/Device/Server/URI",
# then it will use these settings instead of the defaultSessionSettings!

# Now you can simply create a client that uses these settings:
myClient = Client(clientSettings)
# or alternatively:
# myClient = Client()
# myClient.setClientSettings(clientSettings)

# let's read 2 nodes:
address0 = Address(NodeId("Demo.SimulationSpeed" , NAMESPACE_URI), SERVER_URI)
address1 = Address(NodeId("Demo.SimulationActive", NAMESPACE_URI), SERVER_URI)

# the next line will result in 
#  - a session being created, with the defaultSessionSettings which we configured before
#  - the Read service being invoked, with the defaultReadSettings we configured before
myClient.read( [address0, address1] ) 

# when the next line is executed, then:
#  - the session we created before will be reused (as we're requesting a session with the
#    defaultSessionSettings, but such a session exists already, so it can be reused!)
#  - the Write service will be invoked, with the defaultWriteSettings we configured before
myClient.write( [address0, address1] , [ UInt32(60), Boolean(True) ] )


# ==================================================================================================
# 2) Overriding the defaults
# ==================================================================================================

# If needed, you can also configure the settings for each service call, using the **kwargs arguments
# of read/write/call/...

# e.g. set some special session settings for a specific read() call:
mySessionSettings = SessionSettings()
mySessionSettings.connectTimeoutSec = 0.5
mySessionSettings.sessionTimeoutSec = 100.0
# simply mention 'sessionSettings = ...' to use these settings as a **kwarg:
myClient.read( [address0, address1], sessionSettings = mySessionSettings ) 

# e.g. set some special service settings for a specific read() call:
myReadSettings = ReadSettings()
myReadSettings.callTimeoutSec = 0.5
myReadSettings.maxAgeSec      = 1.0
# simply mention 'serviceSettings = ...' to use these settings as a **kwarg:
myClient.read( [address0, address1], serviceSettings = myReadSettings ) 
# or combine them:
myClient.read( [address0, address1], serviceSettings = myReadSettings, sessionSettings = mySessionSettings ) 

# e.g. set some special subscription settings for a specific createMonitoredData() call:
mySubscriptionSettings = SubscriptionSettings()
mySubscriptionSettings.publishingIntervalSec = 2.0
mySubscriptionSettings.priority = 20
myClient.createMonitoredData( [address0, address1], subscriptionSettings = mySubscriptionSettings )

# Both the SessionSettings and SubscriptionSettings have a special 'unique' attribute, which 
# can be True or False.
# By default it is False, which tells the PyUAF Client that it may re-use a session (or subscription)
# if there exists one with the same SessionSettings (or SubscriptionSettings).
# However, if you set the unique attribute to True, then the PyUAF Client will ignore any existing
# sessions (or subscriptions) and create a new unique one.
# This is useful, e.g. if your HMI (Human Machine Interface) has several tabs, then you can create
# a subscription for each tab (to hold all monitored items for that specific tab). Using the
# setPublishingMode() service, you can then temporarily enable the subscription for a visible
# tab, and temporarily disable the subscription for a hidden one. Like this: 
# tab 1:  
tab1SubscriptionSettings = SubscriptionSettings()
tab1SubscriptionSettings.unique = True
tab1SubscriptionSettings.publishingIntervalSec = 2.0
# tab 2:
tab2SubscriptionSettings = SubscriptionSettings()
tab2SubscriptionSettings.unique = True
tab2SubscriptionSettings.publishingIntervalSec = 2.0
# create the subscriptions and monitored items:
tab1Result = myClient.createMonitoredData( [address0] , subscriptionSettings = tab1SubscriptionSettings )
tab2Result = myClient.createMonitoredData( [address0] , subscriptionSettings = tab2SubscriptionSettings )
# disable the subscription for tab 2:
myClient.setPublishingMode(clientSubscriptionHandle = tab2Result.targets[0].clientSubscriptionHandle, 
                           publishingEnabled        = False)


# ==================================================================================================
# Keeping full control over the sessions and subscriptions
# ==================================================================================================

# By manually creating and configuring sessions and subscriptions, you can keep full control over 
# them. You'll have to take care of some things yourself (e.g. re-create monitored items in case
# a session or subscription dies due to a restart of the server), but you can still benefit from
# may of PyUAF's features such as automatic browsepath translation, discovery etc.

# create a Session and remember its clientConnectionId:
myClientConnectionId = myClient.manuallyConnect(serverUri       = SERVER_URI, 
                                                sessionSettings = mySessionSettings)

# use this clientConnectionId to read/write/call/...:
myClient.read( addresses          = [address0, address1], 
               clientConnectionId = myClientConnectionId )

# of course if you don't want to use the defaultReadSettings of the ClientSettings (see above)
# then you can provide the service settings as well:
myClient.read( addresses          = [address0, address1], 
               clientConnectionId = myClientConnectionId, 
               serviceSettings    = myReadSettings )

# you can also create a subscription "within" the session created before:
myClientSubscriptionHandle = myClient.manuallySubscribe(clientConnectionId   = myClientConnectionId, 
                                                        subscriptionSettings = mySubscriptionSettings)

# now you can add monitored items to this specific subscription of this specific session:
def myCallback(notification):
    print("new notification received:")
    print(notification)
    
myClient.createMonitoredData( addresses                = [address0], 
                              notificationCallbacks    = [myCallback],
                              clientConnectionId       = myClientConnectionId,
                              clientSubscriptionHandle = myClientSubscriptionHandle )

# allow some time to receive a notification:
import time
time.sleep(3)

# don't worry about disconnecting sessions etc., these things will be done automatically
# when the client is destroyed.
