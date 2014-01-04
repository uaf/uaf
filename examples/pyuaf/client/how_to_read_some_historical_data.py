# examples/pyuaf/client/how_to_read_some_historical_data.py
"""
EXAMPLE: how to read some historical data
====================================================================================================

A UAF Client can read historical data in two ways:
  - either using the "convenience" methods: historyReadRaw() and historyReadModified()
  - or using the "generic" method: processRequest() 

The "convenience" methods (such as read(), write(), call(), ...) are conveniently to use 
 (since they accept the most frequently used parameters directly), 
but they are less powerful than the "generic" processRequest() method 
 (since this method accepts ReadRequests, WriteRequests, etc. that can be fully configured).

In this example, we will use both ways to read historical data.

As will be shown in this example, the UAF can automatically take care of subsequent 
history reading calls, when the first call returned a continuation point (because either the server
or the client restricted the number of results that were passed in one OPC UA message).
With this "automatic" UAF feature, you don't have to worry about incomplete results anymore!

To run the example, start the UaDemoServer of UnifiedAutomation first on the same machine. 
"""

import time, os, sys

import pyuaf
from pyuaf.client           import Client
from pyuaf.client.settings  import ClientSettings
from pyuaf.client.requests  import HistoryReadRawModifiedRequest
from pyuaf.client.configs   import HistoryReadRawModifiedConfig, SessionConfig
from pyuaf.util             import Address, NodeId
from pyuaf.util             import DateTime
from pyuaf.util             import DataValue
from pyuaf.util             import Status
from pyuaf.util             import RelativePathElement
from pyuaf.util             import QualifiedName
from pyuaf.util             import primitives
from pyuaf.util             import opcuaidentifiers
from pyuaf.util             import opcuastatuscodes
from pyuaf.util.errors      import UafError


# define the namespace URI and server URI of the UaDemoServer
demoNsUri     = "http://www.unifiedautomation.com/DemoServer"
demoServerUri = "urn:UnifiedAutomation:UaServerCpp"

# define the addresses of some useful nodes
# (demoAddress is an absolute address, all the others are relative ones) 
demoAddress             = Address( NodeId("Demo", demoNsUri), demoServerUri )
simulationActiveAddress = Address( demoAddress, [RelativePathElement(QualifiedName("SimulationActive", demoNsUri))] )
startSimulationAddress  = Address( demoAddress, [RelativePathElement(QualifiedName("StartSimulation" , demoNsUri))] )
historyAddress          = Address( demoAddress, [RelativePathElement(QualifiedName("History", demoNsUri))] )
loggingActiveAddress    = Address( historyAddress, [RelativePathElement(QualifiedName("DataLoggerActive", demoNsUri))] )
startLoggingAddress     = Address( historyAddress, [RelativePathElement(QualifiedName("StartLogging", demoNsUri))] )
doubleAddress           = Address( historyAddress, [RelativePathElement(QualifiedName("DoubleWithHistory", demoNsUri))] )

# define the ClientSettings:
settings = ClientSettings()
settings.applicationName = "MyClient"
settings.discoveryUrls.append("opc.tcp://localhost:48010")

# create the client
myClient = Client(settings)

# first, we need to start the simulation (if it's not already started),
# and we need to start the logging (if it's not already started)
res = myClient.read( [simulationActiveAddress,loggingActiveAddress]  )

if not res.overallStatus.isGood():
    raise Exception("Couldn't read some nodes of the server: is uaservercpp started and properly configured?")

isSimulationActive = res.targets[0].data.value
isLoggingActive    = res.targets[1].data.value

print("isSimulationActive : %s" %isSimulationActive)
print("isLoggingActive    : %s" %isLoggingActive)

if not isSimulationActive:
    res = myClient.call(demoAddress, startSimulationAddress)
    
    if res.overallStatus.isGood():
        print("The simulation was started")
    else:
        raise Exception("Couldn't start the simulation: %s" %res.overallStatus)

if not isLoggingActive:
    res = myClient.call(historyAddress, startLoggingAddress)
    
    if res.overallStatus.isGood():
        print("The logging was started")
    else:
        raise Exception("Couldn't start the logging: %s" %res.overallStatus)
    

# now wait a bit more than a second, so that we have at least one second of historical data
time.sleep(1.5)


try:
    print("")
    print("First option: use the convenience functions historyReadRaw() and historyReadModified()")
    print("======================================================================================")
    
    print("")
    print("First example:")
    print("-------------")
    
    # Read the raw historical data 
    #   - that is provided by the double node,
    #   - that was recorded during the past second
    #   - with a maximum of a 100 returned values 
    #     (we expect around 10 values, so 100 is a very safe margin) 
    #   - and let the UAF invoke at most 10 "continuation calls"
    #     (we expect that all data can be returned by a single call, so a maximum of 10 
    #      additional calls is again a very safe margin)
    result = myClient.historyReadRaw(addresses          = [doubleAddress],
                                     startTime          = DateTime(time.time() - 1.5),
                                     endTime            = DateTime(time.time()),
                                     numValuesPerNode   = 100, 
                                     maxAutoReadMore    = 10)
    
    # print the result:
    print(str(result))
    
    # do some processing on the result
    if result.targets[0].status.isNotGood():
        print("Could not read historical data from the double: %s" %str(result.targets[0].status))
    else:
        if len(result.targets[0].dataValues) == 0:
            # Strange, we didn't receive any historical data.
            # Check if this is expected behavior:
            if result.targets[0].status.opcUaStatusCode() == opcuastatuscodes.OpcUa_GoodNoData:
                print("OK, no data could be received because he server reports that there is "
                      "no data that matches your request")
        else:
            allStatuses     = []
            allDoubleValues = []
            allSourceTimes  = []
            
            for dataValue in result.targets[0].dataValues:
                # check the data type
                if type(dataValue.data) == primitives.Double:
                    
                    # NOTE that dataValue is just a POINTER!
                    # So if you want to copy any objects 
                    #  (like we're copying Status or DateTime objects to a Python list in this case),
                    # then you must use the copy constructors 
                    #  (like Status(...) and DateTime(...) in this case),
                    # to actually copy the data!
                    # If you don't do this, then you will just create pointers to the underlying data.
                    # And when Python garbage collects this data, your pointers will point to
                    # invalid memory, and your software will crash when you try to use them!
                    
                    allStatuses.append( Status(dataValue.status) )               # notice the copy constructor!
                    allDoubleValues.append( dataValue.data.value )                  # an int, no copy constructor needed
                    allSourceTimes.append( DateTime(dataValue.sourceTimestamp) ) # notice the copy constructor!
            
            # now print the lists 
            print("")
            print("The results are:")
            for i in xrange(len(allDoubleValues)):
                
                timeFloat  = allSourceTimes[i].ctime()
                timeTuple  = time.localtime( long(timeFloat) )
                timeString = time.strftime("%H:%M:%S", timeTuple)   \
                             + "."                                  \
                             + ("%.3d" %allSourceTimes[i].msec())
                
                print("Code=%d - Value=%s - Time=%s" %(allStatuses[i].statusCode(), allDoubleValues[i], timeString))
    
    print("")
    print("Second example:")
    print("--------------")
    # Now do the same, but this time get the modifications of the data of the last second.
    # Since we didn't do any modifications, none will be reported!
    result = myClient.historyReadModified(addresses          = [doubleAddress],
                                          startTime          = DateTime(time.time() - 1),
                                          endTime            = DateTime(time.time()),
                                          numValuesPerNode   = 100, 
                                          maxAutoReadMore    = 10)
    
    # print the result:
    print(str(result))
    
    
    print("")
    print("Third example:")
    print("--------------")
    
    # Now suppose we want to use the continuation points manually, 
    # instead of letting the UAF handle them.
    # We therefore put 
    #   - numValuesPerNode to a very low value, so that not all results will be retrieved at once
    #   - maxAutoReadMore to 0, so that the UAF may not invoke "continuation request" automatically
    
    startTime = DateTime(time.time() - 1)
    endTime   = DateTime(time.time())
    
    result = myClient.historyReadRaw(addresses          = [doubleAddress],
                                     startTime          = startTime,
                                     endTime            = endTime,
                                     numValuesPerNode   = 3, 
                                     maxAutoReadMore    = 0)
    
    # append all DataValues to the following list:
    allDataValues = []
    
    for dataValue in result.targets[0].dataValues:
        allDataValues.append( DataValue(dataValue) ) # notice the copy constructor!!!
    
    # as long as we get continuation points, we must continue to read the data
    while len(result.targets[0].continuationPoint) > 0:
        
        result = myClient.historyReadRaw(addresses          = [doubleAddress],
                                         startTime          = startTime,
                                         endTime            = endTime,
                                         numValuesPerNode   = 3, 
                                         maxAutoReadMore    = 0,
                                         continuationPoints = [result.targets[0].continuationPoint])
        
        for dataValue in result.targets[0].dataValues:
            allDataValues.append( DataValue(dataValue) ) # notice the copy constructor!!!
    
    print("The following values were received:")
    for dataValue in allDataValues:
        print(" - %s" %dataValue.toCompactString())
    
    
    
    print("")
    print("Second option: use the generic method processRequest()")
    print("======================================================")
    
    print("")
    print("Fourth example:")
    print("---------------")
    
    # create a request with 1 target
    request = HistoryReadRawModifiedRequest(1)
    request.targets[0].address = doubleAddress
    
    # configure the request:
    request.serviceConfig.serviceSettings.startTime                = DateTime(time.time() - 1)
    request.serviceConfig.serviceSettings.endTime                  = DateTime(time.time())
    request.serviceConfig.serviceSettings.callTimeoutSec           = 2.0                        # optional of course
    request.serviceConfig.serviceSettings.numValuesPerNode         = 100
    request.serviceConfig.serviceSettings.maxAutoReadMore          = 10
    request.serviceConfig.serviceSettings.isReadModified           = False                      # we want raw historical data
    request.sessionConfig.defaultSessionSettings.sessionTimeoutSec = 600.0                      # optional of course
    
    # process the request
    result = myClient.processRequest(request)
    
    # print the result
    print(str(result))
    
    # process the result in the same way as before
    
except UafError, e:
    print("Some error occurred: %s" %e)
    raise

# don't worry about closing sessions etc., the UAF client will cleanup everything
# when it's garbage collected


