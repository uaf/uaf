# examples/pyuaf/client/how_to_change_the_default_subscription_behavior.py
"""
EXAMPLE: how to change the default subscription behavior.
=================================================================================================

A SubscriptionConfig instance can be used to configure one or more subscriptions that need to be
created, e.g. in order to successfully create some MonitoredItems.

This is an example to show you some more advanced feature of the UAF, you can skip it if you're 
happy with the default subscription behavior of the UAF!

As always, in the UAF terminology, a "config" object holds one or more "settings" objects.

In this case, a SubscriptionConfig holds
 - one SubscriptionSettings object to specify "default" settings for subscriptions that need to
   be created
 - and optionally some particular SubscriptionSettings objects for subscriptions to particular
   servers.

Because a SubscriptionConfig can contain settings for many different servers, you can create and
configure one SubscriptionConfig, and then re-use this SubscriptionConfig for multiple service
calls.
"""

import pyuaf
from pyuaf.util             import Address, NodeId
from pyuaf.util.primitives  import Byte, Double
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SubscriptionSettings
from pyuaf.client.configs   import SubscriptionConfig


print("This example will fail when executed, since it tries to connect to non-existing servers")


# create a single SubscriptionConfig object that we will use for all our service calls
cfg = SubscriptionConfig()

# configure the default settings for the sessions that will be created
cfg.defaultSubscriptionSettings.publishingIntervalSec = 1.0
cfg.defaultSubscriptionSettings.priority = 50

# for a particular server (a small embedded device) we want to create a subscription with a
# slow publishing interval, so that we don't require too much resources from the device:
cfg.specificSubscriptionSettings["My/Slow/Device/Server"] = SubscriptionSettings()
cfg.specificSubscriptionSettings["My/Slow/Device/Server"].publishingIntervalSec = 2.0

# we also have a very fast server (some high-end PLC), from which we want to receive updates
# much faster (4 times per second!):
cfg.specificSubscriptionSettings["My/Fast/PLC/Server"] = SubscriptionSettings()
cfg.specificSubscriptionSettings["My/Fast/PLC/Server"].publishingIntervalSec = 0.25

# Now we can use the same config for many different service calls.
# Subscriptions will be created silently in the background by the UAF, based on the
# settings we provided via the 'cfg' object.
# If subscriptions need to be created to the embedded device or the fast PLC, they will be
# created according to the specified settings.
# If subscriptions need to be created to other servers, they will be created according to the
# defaultSubscriptionSettings settings.

# First of all, configure a client ...
clientSettings = ClientSettings()
clientSettings.applicationName = "MyClient"
clientSettings.discoveryUrls.append("opc.tcp://10.133.78.42")
clientSettings.discoveryUrls.append("opc.tcp://10.133.78.81")
clientSettings.discoveryUrls.append("opc.tcp://10.134.25.16")

# ... and create the client
myClient = Client(clientSettings)

# define some node addresses
temperature1 = Address(NodeId("temperature1" , "MyCompanyNamespace"), "Some/OPCUA/Server")
temperature2 = Address(NodeId("temperature2" , "MyCompanyNamespace"), "Some/OPCUA/Server")
pressure0005 = Address(NodeId("pressure0005" , "MyCompanyNamespace"), "My/Slow/Device/Server")
motorStatus3 = Address(NodeId("motorStatus3" , "MyCompanyNamespace"), "My/Fast/PLC/Server")
safetyValve5 = Address(NodeId("safetyValve5" , "MyCompanyNamespace"), "My/Fast/PLC/Server")

# now we can monitor any variables or events without worrying about the settings of the subscriptions!

# monitor the 4 variables
myCreateMonitoredDataResult = myClient.createMonitoredData([temperature1, temperature2, pressure0005, motorStatus3], 
                                                           subscriptionConfig=cfg)

# monitor the valve object that may send events
# Note that the previous call already resulted in the creation of a "fast" subscription to
# our fast PLC server. So in the next call, this subscription will be re-used (so no new
# subscription will be created).
myCreateMonitoredEventsResult = myClient.createMonitoredEvents([safetyValve5], subscriptionConfig=cfg)

# do some other stuff, each time using the same SubscriptionConfig object ('cfg')
# ...

# don't worry about disconnecting sessions etc., these things will be done automatically
# when the client is destroyed.

