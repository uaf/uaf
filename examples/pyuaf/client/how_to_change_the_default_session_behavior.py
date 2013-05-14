# examples/pyuaf/client/how_to_change_the_default_session_behavior.py
"""
EXAMPLE: how to change the default session behavior
=================================================================================================

A SessionConfig instance can be used to configure one or more sessions that need to be created,
in order to successfully invoke an OPC UA service.

This is an example to show you some more advanced feature of the UAF, you can skip it if you're 
happy with the default session behavior of the UAF!

As always, in the UAF terminology, a "config" object holds one or more "settings" objects.

In this case, a SessionConfig holds
  - one SessionSettings object to specify "default" settings for sessions that need to be created
    during the service call
  - and optionally some particular SessionSettings objects for sessions to particular servers.

Because a SessionConfig can contain settings for many different servers, you can create and
configure one SessionConfig, and then re-use this SessionConfig for multiple service calls.
"""

import pyuaf
from pyuaf.util             import Address, NodeId
from pyuaf.util.primitives  import Byte, Double
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings, SessionSettings
from pyuaf.client.configs   import SessionConfig


print("This example will fail when executed, since it tries to connect to non-existing servers")


# create a single SessionConfig object that we will use for all our service calls
cfg = SessionConfig()

# configure the default settings for the sessions that will be created
cfg.defaultSessionSettings.sessionTimeoutSec = 100.0
cfg.defaultSessionSettings.connectTimeoutSec = 2.0

# for a particular server (an embedded device) we expect an unreliable connection,
# so we specify some settings that are more suitable for this particular server
cfg.specificSessionSettings["My/Unreliable/Device/Server"] = SessionSettings()
cfg.specificSessionSettings["My/Unreliable/Device/Server"].sessionTimeoutSec = 200.0
cfg.specificSessionSettings["My/Unreliable/Device/Server"].connectTimeoutSec = 5.0

# we also have a particular very reliable and fast server (some PLC), for which we want to
# specify other settings:
cfg.specificSessionSettings["My/Reliable/PLC/Server"] = SessionSettings()
cfg.specificSessionSettings["My/Reliable/PLC/Server"].connectTimeoutSec = 0.5

# Now we can use the same config for many different service calls.
# Sessions will be created silently in the background by the UAF, based on the
# settings we provided via the 'cfg' object.
# If sessions need to be created to the "My/Unreliable/Device/Uri" or "My/Reliable/PLC/Uri"
# servers, they will be created according to the specified settings.
# If sessions need to be created to other servers, they will be created according to the
# defaultSessionSettings settings.

# configure a client ...
clientSettings = ClientSettings() 
clientSettings.applicationName = "MyClient";
clientSettings.discoveryUrls.append("opc.tcp://10.133.78.42")
clientSettings.discoveryUrls.append("opc.tcp://10.133.78.81")
clientSettings.discoveryUrls.append("opc.tcp://10.134.25.16")

# ... and create the client
myClient = Client(clientSettings)

# define some addresses
temperature1 = Address(NodeId("temperature1" , "MyCompanyNamespace"), "Some/OPCUA/Server")
temperature2 = Address(NodeId("temperature2" , "MyCompanyNamespace"), "Some/OPCUA/Server")
pressure0005 = Address(NodeId("pressure0005" , "MyCompanyNamespace"), "My/Unreliable/Device/Server")
motorStatus3 = Address(NodeId("motorStatus3" , "MyCompanyNamespace"), "My/Reliable/PLC/Server")

# now we can read, write, ... any address(es) without worrying about the settings of the sessions!

# read the Value attribute of the 4 nodes
myReadResult = myClient.read([temperature1, temperature2, pressure0005, motorStatus3], sessionConfig=cfg)

# write a new motor status
myWriteResult = myClient.write([motorStatus3], [Byte(0x3)], sessionConfig=cfg)
                             
# do some other stuff like monitoring variables, calling methods, ... all using
# the same SessionConfig object ('cfg')
# ...

# don't worry about disconnecting sessions etc., these things will be done automatically
# when the client is destroyed.
