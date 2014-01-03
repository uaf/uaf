# examples/pyuaf/client/how_to_read_some_data.py
"""
EXAMPLE: how to read some data
====================================================================================================

A UAF Client can read data in two ways:
  - either using the "convenience" method: read()
  - or using the "generic" method: processRequest() 

The "convenience" methods (such as read(), beginRead(), write(), ...) are conveniently to use 
 (since they accept the most frequently used parameters directly), 
but they are less powerful than the "generic" processRequest() method 
 (since this method accepts ReadRequests, AsyncReadRequests, etc. that can be fully configured).

In this example, we will use several ways to read data:
 - first option  : "convenience" synchronous  function read()
 - second option : "generic"     synchronous  function processRequest()
 - third option  : "convenience" asynchronous function beginRead()       , with external callback
 - fourth option : "generic"     asynchronous function processRequest()  , with external callback
 - fifth option  : "convenience" asynchronous function beginRead()       , with overridden callback
 - sixth option  : "generic"     asynchronous function processRequest()  , with overridden callback

To run the example, start the UaDemoServer of UnifiedAutomation first on the same machine. 
"""

import time, os

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings
from pyuaf.client.requests  import ReadRequest, AsyncReadRequest, ReadRequestTarget 
from pyuaf.client.configs   import ReadConfig, SessionConfig
from pyuaf.util             import Address, NodeId, RelativePathElement, QualifiedName, LocalizedText
from pyuaf.util             import primitives
from pyuaf.util.errors      import UafError


# define the namespace URI and server URI of the UaDemoServer
demoNsUri     = "http://www.unifiedautomation.com/DemoServer"
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"

# define some addresses of nodes of which we will read the Value attribute
# (you could also define addresses as Relative Paths to other addresses, 
#  see the example that shows you how to define addresses)
someDoubleNode        = Address( NodeId("Demo.Static.Scalar.Byte"                , demoNsUri), demoServerUri )
someUInt32Node        = Address( NodeId("Demo.Static.Scalar.UInt32"              , demoNsUri), demoServerUri )
someStringNode        = Address( NodeId("Demo.Static.Scalar.String"              , demoNsUri), demoServerUri )
someLocalizedTextNode = Address( NodeId("Demo.Static.Scalar.LocalizedText"       , demoNsUri), demoServerUri )
someSByteArrayNode    = Address( NodeId("Demo.Static.Arrays.SByte"               , demoNsUri), demoServerUri )

# define a function to print the readResult (which is of type pyuaf.client.results.ReadResult)
def printResult(readResult):
    # overall result
    print("The overall status is: %s" %str(readResult.overallStatus))
    
    # target 0:
    status = readResult.targets[0].status                         # 'status' has type pyuaf.util.Status
    data   = readResult.targets[0].data                           # 'data' has type pyuaf.util.primitives.Double
    if status.isGood() and isinstance(data, primitives.Double):
        print("The temperature is: %.3f" %data.value)
    
    # target 1:
    status = readResult.targets[1].status                         # 'status' has type pyuaf.util.Status
    data   = readResult.targets[1].data                           # 'data' has type pyuaf.util.primitives.UInt32
    if status.isGood() and isinstance(data, primitives.UInt32):
        print("The counter is: %d" %data.value)
    
    # target 2:
    status = readResult.targets[2].status                         # 'status' has type pyuaf.util.Status
    data   = readResult.targets[2].data                           # 'data' has type pyuaf.util.primitives.String
    if status.isGood() and isinstance(data, primitives.String):
        print("The string is: '%s'" %data.value)
    
    # target 3:
    status = readResult.targets[3].status                         # 'status' has type pyuaf.util.Status
    data   = readResult.targets[3].data                           # 'data' has type pyuaf.util.LocalizedText
    if status.isGood() and isinstance(data, LocalizedText):
        print("The locale is: '%s', the text is: '%s'" %(data.locale(), data.text()))
    
    # target 4:
    status = readResult.targets[4].status                         # 'status' has type pyuaf.util.Status
    data   = readResult.targets[4].data                           # 'data' is a list of pyuaf.util.primitives.SByte
    if status.isGood() and isinstance(data, list):
        print("The array is:")
        for i in xrange(len(data)):
            print(" - array[%d] = %d" %(i, data[i].value))


# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)



# read the node attributes all at once
print("")
print("First option: use the convenience function read() to read data synchronously")
print("============================================================================")
    
# OPTIONAL: You could also provide a ReadConfig to configure a call timeout, 
#           or maximum age of the values, or ... 
serviceConfig = ReadConfig()
serviceConfig.serviceSettings.callTimeoutSec = 0.5
serviceConfig.serviceSettings.maxAgeSec = 1.0

# OPTIONAL: And you could also provide a SessionConfig to configure the sessions 
#           (e.g. set the timeout to 600.0 seconds)
#           For more info about SessionConfigs, see the sessionconfig_example
sessionConfig = SessionConfig()
sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0

try:
    # now read the node attributes
    readResult = myClient.read( addresses     = [someDoubleNode, someUInt32Node, someStringNode, 
                                                 someLocalizedTextNode, someSByteArrayNode],
                                serviceConfig = serviceConfig, # optional argument
                                sessionConfig = sessionConfig) # optional argument
    
    # print the result using the function we defined before
    printResult(readResult)
except UafError, e:
    print("Some error occurred: %s" %e)



print("")
print("Second option: use the generic function processRequest() to read data synchronously")
print("===================================================================================")

# create a request with 5 targets
readRequest = ReadRequest(5)
readRequest.targets[0].address = someDoubleNode
readRequest.targets[1].address = someUInt32Node
readRequest.targets[2].address = someStringNode
readRequest.targets[3].address = someLocalizedTextNode
readRequest.targets[4].address = someSByteArrayNode

# we could also add a 6th node, of which we want to read the DisplayName (= of type LocalizedText)
readRequest.targets.append(ReadRequestTarget()) # or readRequest.targets.resize(6)
readRequest.targets[5].address     = someDoubleNode
readRequest.targets[5].attributeId = pyuaf.util.attributeids.DisplayName

# OPTIONAL: let's also specify a small call timeout, since the UaDemoServer is running 
#           on the local machine anyway
readRequest.serviceConfig.serviceSettings.callTimeoutSec = 0.5
# OPTIONAL: let's also specify that the values cannot be older than 1 second
readRequest.serviceConfig.serviceSettings.maxAgeSec = 1.0
# OPTIONAL: and finally let's also specify that sessions should have a timeout of 600 seconds
#           For more info about SessionConfigs, see the sessionconfig_example
readRequest.sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0

try:    
    # process the request
    readResult = myClient.processRequest(readRequest)
    
    # print the result
    printResult(readResult)
    
    # also print the display name of the 6th node:
    status = readResult.targets[5].status
    data   = readResult.targets[5].data
    if status.isGood() and isinstance(data, LocalizedText):
        print("The DisplayName-locale is: '%s', the DisplayName-text is: '%s'" %(data.locale(), data.text()))
except UafError, e:
    print("Some error occurred: %s" %e)
    
    

print("")
print("Third option: use the convenience function beginRead() to read data asynchronously")
print("==================================================================================")

# notice we enable asynchronous communication now by providing the printResult() method as 
# a callback function!

try:
    asyncReadResult = myClient.beginRead(addresses     = [someDoubleNode, someUInt32Node, 
                                                          someStringNode, someLocalizedTextNode, 
                                                          someSByteArrayNode],
                                         serviceConfig = serviceConfig, # optional argument
                                         sessionConfig = sessionConfig, # optional argument
                                         callback      = printResult) # callback function!
    
    # check if there was an "immediate" error on the client side when executing the asynchronous 
    # service call:
    if asyncReadResult.overallStatus.isGood():
        print("OK, the client could invoke the asynchronous request without problems.")
        print("Let's wait a second for the result ...")
        
        time.sleep(1)
        
        print("The read result should have been received by now!")

except UafError, e:
    print("Some error occurred: %s" %e)


print("")
print("Fourth option: use the generic function processRequest() to read data asynchronously")
print("====================================================================================")

# notice we enable asynchronous communication now by providing the printResult() method as 
# a callback function!

# create an asynchronous (!) request with 5 targets
asyncReadRequest = AsyncReadRequest(5)

# we can simply copy the targets of the synchronous request to the asynchronous request:
for i in xrange(5):
    asyncReadRequest.targets[i] = readRequest.targets[i]
    
# OPTIONAL: also copy the service config and session config:
asyncReadRequest.serviceConfig = readRequest.serviceConfig
asyncReadRequest.sessionConfig = readRequest.sessionConfig

try:
    # process the request
    asyncReadResult = myClient.processRequest(asyncReadRequest, resultCallback=printResult)
    
    # check if there was an "immediate" error on the client side when executing the asynchronous 
    # service call:
    if asyncReadResult.overallStatus.isGood():
        print("OK, the client could invoke the asynchronous request without problems.")
        print("Let's wait a second for the result ...")
        
        time.sleep(1)
        
        print("The read result should have been received by now!")

    
except UafError, e:
    print("Some error occurred: %s" %e)



print("")
print("Fifth option: read data asynchronously using beginRead() without specifying external callbacks")
print("==============================================================================================")

# instead of using "external" callback functions (such as printResult() above), we can also use
# the "internal" callback function of the Client class. If the argument 'callback' of beginRead() is 
# not used (or 'resultCallback' is not used in case of processRequest()), the asynchronous result
# will be dispatched to the readComplete() method of the Client class. 
# In other words, when you subclass Client, you can simply override the readComplete() method
# to receive the asynchronous read results.

class MySubClasssedClient(Client):
    
    def __init__(self, settings):
        Client.__init__(self, settings)

    def readComplete(self, result): # overridden method!
        print("This is the overridden method readComplete() speaking:")
        printResult(result)

# create the client
mySubClassedClient = MySubClasssedClient(settings)
    
try:
    asyncReadResult = mySubClassedClient.beginRead(
                                         addresses     = [someDoubleNode, someUInt32Node, 
                                                          someStringNode, someLocalizedTextNode, 
                                                          someSByteArrayNode],
                                         serviceConfig = serviceConfig, # optional argument
                                         sessionConfig = sessionConfig) # optional argument!
    # note: the 'callback' argument is not used in the above call!
    
    # check if there was an "immediate" error on the client side when executing the asynchronous 
    # service call:
    if asyncReadResult.overallStatus.isGood():
        print("OK, the client could invoke the asynchronous request without problems.")
        print("Let's wait a second for the result ...")
        
        time.sleep(1)
        
        print("The read result should have been received by now!")
    
except UafError, e:
    print("Some error occurred: %s" %e)
    


print("")
print("Sixth option: read data asynchronously using processRequest() without specifying external callbacks")
print("===================================================================================================")

try:
    # process the request
    asyncReadResult = mySubClassedClient.processRequest(asyncReadRequest) 
    # note: the 'resultCallback' argument is not used in the above call!
    
    # check if there was an "immediate" error on the client side when executing the asynchronous 
    # service call:
    if asyncReadResult.overallStatus.isGood():
        print("OK, the client could invoke the asynchronous request without problems.")
        print("Let's wait a second for the result ...")
        
        time.sleep(1)
        
        print("The read result should have been received by now!")

except UafError, e:
    print("Some error occurred: %s" %e)
    

