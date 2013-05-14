# examples/pyuaf/client/how_to_create_a_client.py
"""
EXAMPLE: how to create a client
====================================================================================================

The Client constructor signature looks like this: 

  pyuaf.client.Client.__init__(settings=None, loggingCallback=None)

with:
  - 'settings': optional: could be 
      - a pyuaf.client.settings.ClientSettings instance
      - or simply a string (the name of the client)
      - or None (so default pyuaf.client.settings.ClientSettings() are used).
  - 'loggingCallback': optional: a callback function to catch log messages of type pyuaf.util.LogMessage.

See the PyUAF HTML documentation for more info.
"""

import time, os

import pyuaf
from pyuaf.client          import Client
from pyuaf.client.settings import ClientSettings
from pyuaf.util            import loglevels, Address, NodeId

# we can create some ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:4841")
settings.logToStdOutLevel   = loglevels.Info   # print Info, Warning and Error logging to the console 
settings.logToCallbackLevel = loglevels.Debug  # send Debug, Info, Warning and Error logging to the callback

# And if you want to catch the logging output, you may also define a callback.
# In this case we define a callback to write the logging output to a file in the user's home directory.
# (but this callback is optional of course, only define one if you want to do something more with the
#  logging output than simply printing it to the console (i.e. sending it to the stdout))
f = open(os.path.expanduser("~/my_logging_output.txt"), "w")
def callback(msg):
    logDetailsString = ""
    logDetailsString += time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime(msg.ctime))
    logDetailsString += ".%.3d " %msg.msec
    logDetailsString += "%-10s " %msg.applicationName
    logDetailsString += "%-20s " %msg.loggerName
    logDetailsString += "%-8s "  %loglevels.toString(msg.level)
    # msg.message may contain multiple lines, so we prepend the other logging details in
    # front of each line:
    for line in msg.message.splitlines():
        f.write("%s: %s\n" %(logDetailsString, line))


# Example 0: create a client with the default settings and no logging callback
# --------------------------------------------------------------------------------------------------
client0 = Client()

# Example 1: create a client by specifying the settings
# --------------------------------------------------------------------------------------------------
client1 = Client(settings)

# Example 2: create a client by specifying the settings
# --------------------------------------------------------------------------------------------------
client2 = Client(settings, callback)

# Example 3: create a client by specifying only the logging callback
# --------------------------------------------------------------------------------------------------
client3 = Client(loggingCallback=callback)

# you can still provide settings and register a logging callback afterwards, but you'll need to use:
#  client0.setClientSettings(settings)
#  client0.registerLoggingCallback(callback)


# read the Value attribute of some non-existing node in order to have some Error output sent to the callback:
client2.read([Address(NodeId("InvalidIdentifier","InvalidNamespace"),"InvalidServerURI")])

f.close()