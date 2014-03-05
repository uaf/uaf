# examples/pyuaf/client/easiest_client_tutorial.py

print("")
print("################################################################################################################")
print("Start the 'UaServerCpp' demo server of Unified Automation before running this script!")
print("################################################################################################################")
print("")


import pyuaf
from pyuaf.util                   import Address
from pyuaf.util                   import NodeId, ExpandedNodeId                # needed for absolute addresses
from pyuaf.util                   import RelativePathElement, QualifiedName    # needed for relative addresses
from pyuaf.util.opcuaidentifiers  import OpcUaId_RootFolder                    # standard OPC UA numerical identifiers
from pyuaf.util                   import attributeids
from pyuaf.util                   import EventFilter
from pyuaf.util.primitives        import Byte, UInt32, Int32, Float, Double, String
from pyuaf.util.errors            import ConnectionError, UafError
from pyuaf.util                   import DateTime
from pyuaf.client                 import Client
from pyuaf.client                 import DataChangeNotification, EventNotification
from pyuaf.client.settings        import ClientSettings
from pyuaf.client.requests        import ReadRequest 
from pyuaf.client.results         import ReadResult
from pyuaf.client.configs         import ReadConfig, SessionConfig

import time

print("")
print("################################################################################################################")
print("Step 1: Define some useful constants")
print("################################################################################################################")
print("")

# Define the namespace URI and server URI of the UaServerCpp demo server
demoNsUri     = "http://www.unifiedautomation.com/DemoServer"
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"

print("")
print("################################################################################################################")
print("Step 2: Configure and create the client")
print("################################################################################################################")
print("")

# Define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryIntervalSec = 20.0 # try to re-discover the servers in the network every 20 seconds
# ... many more settings
settings.discoveryUrls.append("opc.tcp://localhost:48010")
# ... append as many Discovery URLs as you want. 
#
# FYI: what are Discovery URLs?
#  -> A Discovery URL is the URL of a so-called "Discovery Endpoint".
#  -> Clients can use this Discovery Endpoint to learn ("discover") how they can connect to the server, by
#     learning the other endpoints of the server. For example, a server may expose (besides a Discovery Endpoint)
#     an unsecured endpoint and a secured one. The client can then choose to connect to the server via one
#     of these endpoints, and start reading/writing/monitoring/... data.
#  -> Discovery URLs are often of the form opc.tcp://<someIpAddressOrHostname>:4840 or :4841
#  -> The UAF makes it easy for you to deal with discovery: just specify the discovery URLs of the servers you may
#     want to use later on, and specify your favorite way of connecting to a server (e.g. without security). The UAF
#     will take care of the Discovery process and the connection process for you. A background thread will check 
#     every 20 seconds (configurable, see above) the URLs you provided, and keep an inventory of all discovered 
#     endpoints. If at some point the UAF thinks it's necessary to connect to one of these servers (e.g. because
#     you want to read a variable on a particular server), it will automatically create the necessary session
#     for you. 
#  -> Bottomline: just provide the discovery URLs to the UAF, and afterwards you can directly start
#     reading data or monitoring events or calling methods or whatever. No need to manage connections yourself! 
#  -> All OPC UA servers have such a Discovery endpoint, but additionally there are also "dedicated" discovery servers
#     that do nothing more than provide endpoints to other servers. Most people will never have to deal with such a 
#     server, however. 
#  -> In the (advanced!) scenario where a hierarchy of dedicated discovery servers is used, you only need to specify
#     the top discovery server. The UAF will automatically discover the discovery servers that are lower in the 
#     hierarchy.


# create the client
myClient = Client(settings)



print("")
print("################################################################################################################")
print("Step 3: Specify the addresses to some nodes which we would like to read/write/browse/monitor/call/...")
print("################################################################################################################")
print("")


# There are *many* ways how you can identify (address) a node, see the examples below:
# 1) absolute address to the standard OPC UA "RootFolder" node (notice the standard OPC UA index 0)
# 2) absolute address to the non-standard "Demo" node (notice the demo server namespace URI)
# 3) absolute address to the non-standard "BoilerDemo" node (notice that we use an ExpandedNodeId this time)
# 4) relative address to the "Boiler1" node (relative to the previous address)
# 5) relative address to the "TemperatureSetpoint" Double variable (relative to the previous relative (!!!) address)
# 6) relative address to the "HeaterStatus" node (relative to the standard "Root" folder)
address_Root         = Address( NodeId(OpcUaId_RootFolder , 0        ), demoServerUri )
address_Demo         = Address( NodeId("Demo"             , demoNsUri), demoServerUri )
address_BoilerDemo   = Address( ExpandedNodeId("Demo.BoilerDemo", demoNsUri, demoServerUri) )
address_Boiler1      = Address( address_BoilerDemo , [ RelativePathElement(QualifiedName("Boiler1"            , demoNsUri)) ] )
address_TSetpoint    = Address( address_Boiler1    , [ RelativePathElement(QualifiedName("TemperatureSetPoint", demoNsUri)) ] )
address_HeaterStatus = Address( address_Root       , [ RelativePathElement(QualifiedName("Objects"            , 0        )),
                                                       RelativePathElement(QualifiedName("Demo"               , demoNsUri)),
                                                       RelativePathElement(QualifiedName("BoilerDemo"         , demoNsUri)),
                                                       RelativePathElement(QualifiedName("Boiler1"            , demoNsUri)),
                                                       RelativePathElement(QualifiedName("HeaterStatus"       , demoNsUri)) ] )


# In the above examples, 0 is used to identify the "standard OPC UA namespace" (which is ALWAYS 0).
# We could also have replaced 0 with the standard OPC UA namespace URI ('http://opcfoundation.org/UA/').
# This namespace URI is available as a constant: pyuaf.util.constants.OPCUA_NAMESPACE_URI.

# As you can see above, there are a variety of ways how you can address a node. 
# But there are even more things you can do:
#  - for each ExpandedNodeId, NodeId or QualifiedName, you may include namespace indexes, or namespace URIs, or both
#  - relative addresses (relative "paths") may span over multiple servers!
# The UAF is capable of resolving these addresses fully automatically. You don't have to create sessions
# or subscriptions to servers in advance, the UAF can take care of that automatically as well. 

# Obviously for most applications, you don't have to make things as complicated as above.
# You probably want to specify just one absolute address (to a well-known node on a well-known server), 
# and then specify the addresses to the nodes you want to read/write/whatever via relative paths. 
# But the above examples demonstrate that with just one or two lines of code, you can address 
# any node within any address space very easily, in a variety of ways.

# We now define a few more addresses that we will need later on:
address_StartSimulation    = Address(address_Demo,    [ RelativePathElement(QualifiedName("StartSimulation"           , demoNsUri)) ] )
address_StopSimulation     = Address(address_Demo,    [ RelativePathElement(QualifiedName("StopSimulation"            , demoNsUri)) ] )
address_SetSimulationSpeed = Address(address_Demo,    [ RelativePathElement(QualifiedName("SetSimulationSpeed"        , demoNsUri)) ] )
address_Scalar             = Address(address_Demo,    [ RelativePathElement(QualifiedName("Dynamic"                   , demoNsUri)),
                                                        RelativePathElement(QualifiedName("Scalar"                    , demoNsUri)) ] )
address_Byte               = Address(address_Scalar,  [ RelativePathElement(QualifiedName("Byte"                      , demoNsUri)) ] )
address_Int32              = Address(address_Scalar,  [ RelativePathElement(QualifiedName("Int32"                     , demoNsUri)) ] )
address_Float              = Address(address_Scalar,  [ RelativePathElement(QualifiedName("Float"                     , demoNsUri)) ] )
address_Events             = Address(address_Demo,    [ RelativePathElement(QualifiedName("Events"                    , demoNsUri)) ] )
address_Alarms             = Address(address_Events,  [ RelativePathElement(QualifiedName("AlarmsWithNodes"           , demoNsUri)) ] )
address_Alarm              = Address(address_Alarms,  [ RelativePathElement(QualifiedName("ExclusiveLevelAlarm"       , demoNsUri)) ] )
address_Trigger            = Address(address_Alarms,  [ RelativePathElement(QualifiedName("ExclusiveLevelAlarmTrigger", demoNsUri)) ] )
address_LowLow             = Address(address_Alarm,   [ RelativePathElement(QualifiedName("LowLowLimit"               , 0        )) ] )
address_Low                = Address(address_Alarm,   [ RelativePathElement(QualifiedName("LowLimit"                  , 0        )) ] )
address_High               = Address(address_Alarm,   [ RelativePathElement(QualifiedName("HighLimit"                 , 0        )) ] )
address_HighHigh           = Address(address_Alarm,   [ RelativePathElement(QualifiedName("HighHighLimit"             , 0        )) ] )
address_History            = Address(address_Demo,    [ RelativePathElement(QualifiedName("History"                   , demoNsUri)) ] )
address_StartLogging       = Address(address_History, [ RelativePathElement(QualifiedName("StartLogging"              , demoNsUri)) ] )
address_StopLogging        = Address(address_History, [ RelativePathElement(QualifiedName("StopLogging"               , demoNsUri)) ] )
address_ByteWithHistory    = Address(address_History, [ RelativePathElement(QualifiedName("ByteWithHistory"           , demoNsUri)) ] )
address_DoubleWithHistory  = Address(address_History, [ RelativePathElement(QualifiedName("DoubleWithHistory"         , demoNsUri)) ] )



print("")
print("################################################################################################################")
print("Step 4: Read/write/browse/monitor/call/... the nodes the easy way, with some default settings")
print("################################################################################################################")
print("")



# =====================================================================================================================
print("")
print("Synchronous reading")
print("===================")
print("")

# Now that we have created a Client and specified some nodes, we can 
#  - read the Value attribute of some nodes
#  - print the resulting values

try:
    result = myClient.read( [address_TSetpoint, address_HeaterStatus] ) 
    
    if result.overallStatus.isGood():
        
        temperatureSetpoint = result.targets[0].data # data is an instance of pyuaf.util.primitives.Double
        heaterStatus        = result.targets[0].data # data is an instance of pyuaf.util.primitives.Int32
        
        print("Temperature setpoint = %.3f" %temperatureSetpoint.value)
        print("Heater status        = %d"   %heaterStatus.value)
    
    else:
        raise Exception("Read failed, this was the result: %s" %result)
    
    
    # result.overallStatus will be good iff all targets were read correctly, in other words when:
    # result.targets[0].status.isGood() and result.targets[1].status.isGood()
    
    # As you can see, primitive data types are represented by objects (pyuaf.util.primitives.*).
    # These primitive objects have a "value" attribute, as you can see above.
    
    # You also notice that we don't have to create Sessions or perform discovery or anything,
    # the UAF takes care of that for you! 
    
    # In the examples above, we've been reading the "Value" attribute of the TemperatureSetpoint
    # and HeaterStatus nodes. These nodes represent OPC UA variables, and therefore they have
    # such a Value attribute.
    # Of course, we may also read other attributes, such as the DisplayName. In the example below, 
    # we read the "DisplayName" attribute of the BoilerDemo, which is a LocalizedText:
    
    result = myClient.read( [address_BoilerDemo], attributeId=pyuaf.util.attributeids.DisplayName )
    
    if result.overallStatus.isGood():
        displayName = result.targets[0].data
        print("Display name         = %s (locale='%s')" %(displayName.text(), displayName.locale()))
    
except ConnectionError, e:
    print("Oops we have a connection error (%s), did you start the UA Demo Server?" %e)
    raise
except UafError, e:
    print("Other UAF error! %s" %e)
    raise
  
# For clarity, we won't use try-except anymore in the rest of this tutorial, but obviously you should!
  


# =====================================================================================================================
print("")
print("Synchronous writing")
print("===================")
print("")

# We can also easily 
#  - write one or more Value attributes (or other attributes such as the DisplayName)
#  - assert that the value was written properly
  
result = myClient.write( [address_Float], [Float(20.5)] )

# Note that we use lists for the address and data-to-be-written, because we can write many variables
# in one single OPC UA command.
# These nodes don't have to be exposed by a the same server! The UAF is smart enough to break your 
# request into sub-requests (one sub-request per server), handle all sub-requests, and gather all
# results for you. In other words, you don't have to worry about "which node is exposed by which 
# server?", because the UAF will handle that for you.


if result.overallStatus.isGood(): # or (since there is only 1 target): result.targets[0].status.isGood()
    print("The float was written without any problems!")

else:
    raise Exception("Write failed, this was the result:\n %s" %result)


# =====================================================================================================================
print("")
print("Synchronous method calling")
print("==========================")
print("")


# We may also want to 
#  - call the "Demo.SetSimulationSpeed(UInt32)" method
#  - and print the output argument

result = myClient.call(address_Demo, address_SetSimulationSpeed, [UInt32(20)])

print("Result of the method call:")
print(result)

# we also start the simulation:
result = myClient.call(address_Demo, address_StartSimulation)

if result.overallStatus.isNotGood():
    print("Couldn't start the simulation (status=%s)" %result.targets[0].status)


# =====================================================================================================================
print("")
print("Synchronous browsing")
print("====================")
print("")

# We may also want to 
#  - browse the Root node and the Demo node simultaneously
#  - print the DisplayName of all nodes that we found

result = myClient.browse( [address_Root, address_Demo] )

print("Nodes below the Root node:")
for ref in result.targets[0].references:
    print(" - %s" %ref.displayName) 

print("Nodes below the Demo node:")
for ref in result.targets[1].references:
    print(" - %s" %ref.displayName) 


# =====================================================================================================================
print("")
print("Synchronous creating monitored data items")
print("=========================================")
print("")

# Let's monitor the dynamic counterNode and temperatureNode, via two callback functions:

def byteCallback(notification):
    if isinstance(notification, DataChangeNotification):
        print(" --> received new Byte value: %d" %notification.data.value)

def floatCallback(notification):
    if isinstance(notification, DataChangeNotification):
        print(" --> received new Float value: %d" %notification.data.value)

result = myClient.createMonitoredData( addresses             = [address_Byte, address_Float],
                                       notificationCallbacks = [byteCallback, floatCallback] )

# let's wait a second, so that a number of notifications can arrive:
print("Waiting for notifications...")
time.sleep(5.0)

# delete the client and create a new instance, so we can proceed cleanly with the next step of the tutorial
del myClient
myClient = Client(settings)


# =====================================================================================================================
print("")
print("Synchronous creating monitored event items")
print("==========================================")
print("")

# Let's 
#  - create an event filter that specifies the "SELECT clause" of our events
#  - create a callback function for the events
#  - read the limits (otherwise the dynamic variables won't change in the demo server)
#  - make sure the alarm trigger has a default value (50)
#  - start to monitor the Alarms node for events
#  - change the trigger to a high value, so that the high alarms will be triggered, and
#    so that events will arrive!

eventFilter = EventFilter()
eventFilter.selectClauses.resize(3)
eventFilter.selectClauses[0].attributeId = pyuaf.util.attributeids.Value
eventFilter.selectClauses[0].browsePath.append(QualifiedName("Message", 0))
eventFilter.selectClauses[0].typeId = NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_BaseEventType, 0)
eventFilter.selectClauses[1].attributeId = pyuaf.util.attributeids.Value
eventFilter.selectClauses[1].browsePath.append(QualifiedName("SourceName", 0))
eventFilter.selectClauses[1].typeId = NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_BaseEventType, 0)
eventFilter.selectClauses[2].attributeId = pyuaf.util.attributeids.Value
eventFilter.selectClauses[2].browsePath.append(QualifiedName("Severity", 0))
eventFilter.selectClauses[2].typeId = NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_BaseEventType, 0)


def eventCallback(notification):
    if isinstance(notification, EventNotification):
        print(" --> received new Event:")
        print("      - Message    : %s" %notification.fields[0])
        print("      - SourceName : %s" %notification.fields[1])
        print("      - Severity   : %s" %notification.fields[2])

# read the triggers (otherwise the dynamic variables won't change)
result = myClient.read( [address_LowLow, address_Low, address_High, address_HighHigh] )

if result.overallStatus.isNotGood():
    raise Exception("Couldn't read the alarm limits!")

lowLowLimit   = result.targets[0].data.value
lowLimit      = result.targets[1].data.value
highLimit     = result.targets[2].data.value
highHighLimit = result.targets[3].data.value

# set the trigger to a default value
result = myClient.write([address_Trigger], [Double(50.0)])

# start monitoring the events
result = myClient.createMonitoredEvents( addresses             = [address_Alarms], 
                                         eventFilter           = eventFilter, 
                                         notificationCallbacks = [eventCallback] )

# now set the trigger to a high value
result = myClient.write([address_Trigger], [Double( highHighLimit + 1.0 )])


# now wait a second, so that the alarm-events can arrive!
print("Waiting for notifications...")
time.sleep(1.0)

# delete the client and create a new instance, so we can proceed cleanly with the next step of the tutorial
del myClient
myClient = Client(settings)


# =====================================================================================================================
print("")
print("Synchronous reading of historical data")
print("======================================")
print("")

# Let's 
#  - instruct the server to start logging historical data, by calling History.StartLogging()
#  - wait a few seconds, so that the server stores at least a second of historical data
#  - read the historical data

myClient.call(address_History, address_StartLogging)

if result.overallStatus.isNotGood():
    raise Exception("Couldn't start the logging!")


print("Now waiting some seconds, while the server is logging data")
time.sleep(3.0)


# Now read the historical data.
# Notice the 'maxAutoReadMore' argument: it says that *if* the historical data was split up into
# several chunks, then the UAF may automatically fetch the remaining data by sending additional
# requests for 10 times in a row. 
# The reason is that a server (or a client) can choose to receive a large number of historical
# data in chunks, instead of all at once. Normally, as a client, you need to check the result
# of the HistoryRead request to see if all historical data is received (by checking the 
# "continuationPoint"). If there is still historical data left on the server, you would have to
# fetch the remaining data manually by invoking more HistoryRead requests.
# Luckily, the UAF implements this behavior for you: you just have to specify the maximum number of
# requests that the UAF may automatically invoke for you.

now = time.time()
result = myClient.historyReadRaw(addresses       = [address_ByteWithHistory, address_DoubleWithHistory],
                                 startTime       = DateTime(now - 5.0),
                                 endTime         = DateTime(now),
                                 maxAutoReadMore = 10)


print("Result of the historical read:")
print(result)


# delete the client and create a new instance, so we can proceed cleanly with the next step of the tutorial
del myClient
myClient = Client(settings)


# =====================================================================================================================
print("")
print("Asynchronous calling methods")
print("============================")
print("")


def printMyAsyncCallResult(asyncResult):
    print(" --> received async method call result:")
    print(asyncResult)

immediateResult = myClient.beginCall(objectAddress = address_Demo, 
                                     methodAddress = address_SetSimulationSpeed, 
                                     inputArgs     = [UInt32(20)], 
                                     callback      = printMyAsyncCallResult )

if immediateResult.overallStatus.isGood():
    print("OK, the async call request was sent without problems, we now need to wait for the asynchronous result")

time.sleep(1) # wait one second for the async call result to arrive (and the callback function to be called)



# =====================================================================================================================
print("")
print("Asynchronous reading")
print("====================")
print("")

def printMyAsyncReadResult(asyncResult):
    print(" --> received async read result:")
    print("     - temperature setpoint : %.3f" %asyncResult.targets[0].data.value)
    print("     - heater setpoint      : %d"   %asyncResult.targets[1].data.value)

immediateResult = myClient.beginRead( addresses = [address_TSetpoint, address_HeaterStatus],
                                      callback  = printMyAsyncReadResult ) 

time.sleep(1) # wait one second for the async call result to arrive (and the callback function to be called)



# =====================================================================================================================
print("")
print("Asynchronous writing")
print("====================")
print("")

def printMyAsyncWriteResult(asyncResult):
    print(" --> received async write result:")
    print("      - write status : %s" %asyncResult.targets[0].status)

immediateResult = myClient.beginWrite(addresses = [address_Float], 
                                      data      = [Float(20.5)],
                                      callback  = printMyAsyncWriteResult ) 

time.sleep(1) # wait one second for the async call result to arrive (and the callback function to be called)





print("")
print("################################################################################################################")
print("Step 5: Using the API that we've just seen, configure the OPC UA requests more in detail")
print("################################################################################################################")
print("")


# Fist of all, you must realize that the above methods have been called with some default arguments.
# For instance, it's possible to read other attributes than just the Value attribute:
result = myClient.read(addresses   = [address_TSetpoint, address_HeaterStatus],
                       attributeId = pyuaf.util.attributeids.DisplayName)

# We may also provide 
#  - a "service config", which configures the Read/Write/MethodCall/... OPC UA service more in detail
#  - a "session config", which configures the sessions that the UAF creates more in detail
#  - in some cases: a "subscription config", which configures the subscriptions that the UAF creates more in detail

# The service config:
readConfig = ReadConfig()
readConfig.serviceSettings.maxAgeSec = 10.0
readConfig.serviceSettings.callTimeoutSec = 0.5
# ...

# The session config:
sessionConfig = SessionConfig()
sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0
sessionConfig.defaultSessionSettings.connectTimeoutSec = 3.0
# ...


# we can now configure our read request more in detail:

result = myClient.read(addresses     = [address_TSetpoint, address_HeaterStatus],
                       attributeId   = pyuaf.util.attributeids.DisplayName,
                       serviceConfig = readConfig,
                       sessionConfig = sessionConfig)



print("")
print("################################################################################################################")
print("Step 6: Learn how 'requests' and 'results' actually look like, and how you can configure them even more in detail")
print("################################################################################################################")
print("")



# Instead of the "convenience" function read(), we could have also used the "generic" function processRequest():
request = ReadRequest(2)
request.targets[0].address = address_TSetpoint
request.targets[1].address = address_HeaterStatus

result = myClient.processRequest(request)

# Internally, myClient.read() does exactly the same, only the API is different! 
# (So myClient.read(...) also creates a similar ReadRequest behind the scenes, and it also uses 
# the processRequest(<ReadRequest>) method afterwards). 
#
# So in both cases, a request (a "ReadRequest" in this case) is created either implicitly or explicitly.
# This request is then processed by the UAF client, and finally leads to a result (a "ReadResult" in this case). 
# 
# The structure of this request is like this:
# 
#  request                                          <ReadRequest>
#    |
#    |__targets                                     <ReadRequestTargetVector> (a sort-of "list" of targets)
#    |     |
#    |     |__[0]                                   <ReadRequestTarget>
#    |     |   |__address     = address_TSetpoint   <Address>
#    |     |   |__attributeId = attributeids.Value  <int>                     (not specified above, we used the defaults)
#    |     |   |__ ... more target details
#    |     |
#    |     |__[1]
#    |     |   |__address     = address_HeaterStatus <Address>
#    |     |   |__attributeId = attributeids.Value   <int>                    (not specified above, we used the defaults)
#    |     |   |__ ... more target details
#    |     |
#    |     |__ ... more targets, if needed
#    |
#    |
#    |__serviceConfig                                <ReadConfig>             (configures the service call)
#    |     |
#    |     |__serviceSettings                        <ReadSettings>           (not specified above, we used the defaults)
#    |     |     |__maxAgeSec      = 0.0             <double>                 (not specified above, we used the defaults)
#    |     |     |__callTimeoutSec = 1.0             <double>                 (not specified above, we used the defaults)
#    |     |     |__ ... more settings
#    |     |
#    |     |__translationSettings                    <TranslateBrowsePathsToNodeIdsSettings> (configures relative path resolution)
#    |           |__callTimeoutSec = 1.0             <double>                 (not specified above, we used the defaults)
#    |           |__ ... more settings
#    |
#    |__sessionConfig                                <SessionConfig>          (allows you to configure the behavior of how
#                                                                              sessions are created in the background. See  
#                                                                              the how_to_change_the_default_session_behavior.py
#                                                                              example for more info.)


# All requests have the same structure, so they contain:
#  - a vector of "request targets" (of type ReadRequestTarget, WriteRequestTarget, BrowseRequestTarget, ...)
#  - a "service config" to configure the service call (of type ReadConfig, WriteConfig, BrowseConfig, ...)
#  - a "session config" to specify how the UAF should create the necessary Sessions
#  - (for certain types of request, also an optional "subscription config", to specify how the UAF should create Subscriptions)




# An OPC UA service request will lead to a result.
# E.g. a WriteRequest (having one or more WriteRequestTargets) will lead to a WriteResult (with one or more 
# corresponding WriteResultTargets). 
# So in the case of the above ReadRequest, we could receive a result that looks like this:
# 
#  result                                           <ReadResult>
#    |
#    |__targets                                     <ReadResultTargetVector> (a sort-of "list" of targets)
#    |     |__[0]                                   <ReadResultTarget>
#    |     |   |__status          = Status(Good)    <Status>
#    |     |   |__data            = Double(20.0)    <Double>                 (could be any type of data, depends on the target)
#    |     |   |__sourceTimestamp = DateTime(...)   <DateTime>
#    |     |   |__ ... more target details
#    |     |
#    |     |__[1]                                   <ReadResultTarget>
#    |     |   |__status          = Status(Good)    <Status>
#    |     |   |__data            = Int32(2)        <Int32>                 (could be any type of data, depends on the target)
#    |     |   |__sourceTimestamp = DateTime(...)   <DateTime>
#    |     |   |__ ... more target details
#    |     |
#    |     |__ ... more targets (one "result target" for each "request target')
#    |
#    |__overallStatus = Status(Good)                <Status>                 (a sort-of summary of the target statuses)
#    |__requestHandle = 1                           <long>                   (an integer linking the result with a request) 
#

# ALL results have the same structure, so they contain:
#  - a list of "result targets", corresponding one-to-one with the "request targets" of the request
#  - an overall status, which is only "Good" if all statuses of all targets are "Good"
#  - a request handle, which is a 64-bit numerical identifier that is incremented for each request that is processed

# So we could do:
print("Result overall status: %s" %result.overallStatus)
print("Number of ReadResultTargets: %d" %len(result.targets))
for i in xrange(len(result.targets)):
    target = result.targets[i]
    if target.status.isGood():
        print(" - result target is good: data is %s (of type %s)" %(target.data, type(target.data)))
    else:
        print(" - result target is NOT good! (reason=%s)" %target.status)


