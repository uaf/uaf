<p align="center">
  <img src="http://github.com/uaf/uaf/raw/master/doc/img/logo/uaf_logo_200x67_opaque.png" alt="Logo"/>
</p>


UAF - the Unified Architecture Framework
========================================


Project website?
-------------------------------------------------------------------------------

 - **Main code repository: http://github.com/uaf/uaf**


What?
-------------------------------------------------------------------------------

 - The Unified Architecture Framework (UAF) is an open source software framework to simplify the 
   development of **OPC UA** applications on **Linux** and **Microsoft Windows**, in **C++** and **Python**.
   
 - OPC UA (OPC Unified Architecture) is the next generation standard for secure, reliable
   and scalable industrial communication.
   
 - In short, the UAF / pyUAF is **OPC UA made easy!**


Why?
-------------------------------------------------------------------------------

 - The UAF is a framework (or "toolkit") that helps you to create advanced OPC UA applications with 
   minimal effort. Essentially, it takes care of some *technical* aspects (such as Session and 
   Subscription management, server discovery, address resolution, ...) so that you can concentrate on 
   the *functional* aspects of your software application.
   
 - Some very concise and easy to understand examples can be found here:
 
    - in Python:   [easiest_client_example.py](http://github.com/uaf/uaf/blob/master/examples/pyuaf/client/easiest_client_example.py)
    - in C++:      [easiest_client_example.cpp](http://github.com/uaf/uaf/blob/master/examples/uaf/src/client/easiest_client_example.cpp)

 - The following example (a single example, split up into several pieces) shows you some advantages 
   of the UAF, in Python. In C++, the equivalent code would be a bit more verbose, but the C++ API 
   is essentially the same as the Python API.

    - **Intuitive API:**

      All code from the Software Developers Kit is wrapped into some convenient namespaces and 
      classes (many more than can be seen below of course).

        ```python
        import pyuaf
        from pyuaf.util            import Node, NodeId, QualifiedName
        from pyuaf.util            import RelativePathElement, LocalizedText
        from pyuaf.util.primitives import UInt16
        from pyuaf.client          import Client
        from pyuaf.client.settings import ClientSettings
        ```
    
    - **Automatic discovery:**
    
      Just provide one or more Discovery URL(s), and the UAF will then automatically and periodically 
      perform the discovery for you.
    
        ```python
        settings = ClientSettings()
        settings.applicationName = "myClient"
        settings.discoveryUrls.append("opc.tcp://localhost:4841")
        
        # create the client with the given settings
        myClient = Client(settings)
        ```
    
    - **Easy node addressing**
    
      You can address nodes 
        - in an absolute way (via "NodeIds" and "ExpandedNodeIds") 
        - or in a relative way (via "RelativePaths").
      
      The UAF will resolve the addresses of the nodes, regardless on what server the nodes are hosted.
       
        ```python
        # first define some URIs (Uniform Resource Identifiers):
        ns      = "MyOrganization"      # the "namespace URI" of the organization or company
        plc12   = "PLC/12/Server/URI"   # the "server URI" of the OPC UA server running on some PLC
        
        # now define some absolute addresses:
        tank5      = Address( NodeId("Tank5"    , ns), plc12) )
        tank5_name = Address( NodeId("Tank5Name", ns), plc12) )
        
        # now define some relative addresses (Tank5/Sensor3 and Tank5/Sensor3/Status):
        tank5_sensor3        = Address( tank5, [ RelativePathElement(QualifiedName("Sensor3", ns)) ] )
        tank5_sensor3_status = Address( tank5, [ RelativePathElement(QualifiedName("Sensor3", ns)),
                                                 RelativePathElement(QualifiedName("Status" , ns)) ] )
        
        # the UAF accepts even relative addresses to relative addresses! So you could also do:
        tank5_sensor3_status = Address( tank5_sensor3, [ RelativePathElement(QualifiedName("Status", ns)) ] )
        ```

    - **Automatic address resolution**
    
      You can now read/write/monitor/... the Value (or any other attribute) of the nodes that we 
      addressed above. **Even if these nodes are hosted by multiple servers**, the UAF will automatically:
       
       - create the necessary Sessions and Subscriptions to the correct servers
         (or re-use existing ones if possible)
       - resolve the addresses
         (i.e. translate the relative paths to absolute ExpandedNodeIds)
       - group the targets of the request into optimal service calls 
         (so the UAF ideally only has to perform one service call per server)
       - perform the necessary service calls 
         (i.e. invoke the actual OPC UA Read/Write/... service)
       - join and re-order the results of the service calls
         (so that the user doesn't notice that the call was actually split up into multiple calls).
       
      This can be seen in the following lines: reading or writing just takes a single line of code!
       
        ```python
        # let's read 
        #   - the tank name         (a LocalizedText, which may be exposed by an OPC UA-enabled PLC) 
        #   - and the sensor status (an UInt16, which may be exposed by some OPC UA-enabled smart sensor)
        result = myClient.read([tank5_name, tank5_sensor3_status])
        
        if isinstance(result.targets[0].data, LocalizedText):
            name   = result.targets[0].data.text()
        
        if isinstance(result.targets[1].data, UInt16):
            status = result.targets[1].data.value
        
        # we can also write a new name
        result = myClient.write( [tank5_name], [LocalizedText("Oil tank", "EN")] )
        
        if result.targets[0].status.isGood():
            print("OK, the new name was written successfully!")
        ```

    - **Persistent monitored items**

      You can create monitored items once, and then forget about them...
       - even if the server that hosts your monitored items is not online yet!
       - even if the server that hosts your monitored items dies, and the relative addresses of your 
         monitored items now suddenly point to nodes hosted by another (redundant) server!!
       
        ```python
        def myCallback(notification):
            print("New sensor status received: %d" %notification.data.value)
            
        myClient.createMonitoredData([tank5_sensor3_status], notificationCallbacks = [myCallback])
        ```
    
    - **More stuff**
        
      For instance, UAF clients have also a generic `processRequest` method that can process fully
      configurable `ReadRequest`s, `WriteRequest`s, `MethodCallRequest`s, ...
        
      Dive into the [documentation] or the [examples] to find out more!



Dependencies?
-------------------------------------------------------------------------------

 - The UAF is based on the commercial C++ OPC UA Software Developers Kit from Unified Automation. A demo 
   version of this SDK can be downloaded from their website for free: http://www.unified-automation.com

 - More info about the dependencies: see [dependencies.rst.txt](http://github.com/uaf/uaf/blob/master/dependencies.rst.txt)



Examples?
-------------------------------------------------------------------------------

 - [C++ examples](http://github.com/uaf/uaf/tree/master/examples/uaf/src)
 
 - [Python examples](http://github.com/uaf/uaf/tree/master/examples/pyuaf)


Documentation?
-------------------------------------------------------------------------------

 - The Python documentation is online [here](http://uaf.github.io/uaf/doc/pyuaf).
 
 - The C++ documentation you can easily generate yourself by using [Doxygen].
   Use the Doxyfile in the [src] directory.
 

Status?
-------------------------------------------------------------------------------

 - Supported on the Client side:
   - read (synchronous + asynchronous)
   - write (synchronous + asynchronous)
   - method call (synchronous + asynchronous)
   - translate browse paths (synchronous)
   - create monitored data items (synchronous)
   - create monitored events items (synchronous)
   - browse and browse next (synchronous)
   - read historical data (raw data + modifications) (synchronous)
   - set publishing mode (synchronous)
 - Supported on the Server side:
   - nothing yet so far!


Installation?
-------------------------------------------------------------------------------

 - **Linux installation guide**: see [install_linux.rst.txt](http://github.com/uaf/uaf/blob/master/install_linux.rst.txt)
  
 - **Windows installation guide**: see [install_windows.rst.txt](http://github.com/uaf/uaf/blob/master/install_windows.rst.txt)


Who?
-------------------------------------------------------------------------------

 - **Author**: Wim Pessemier

 - **Contact**: `W**.P********@ster.kuleuven.be` (replace the asterisks)

 - **Organization**: Institute of Astronomy, KU Leuven (Belgium)

 - **Project website**: http://github.com/uaf
 

License?
-------------------------------------------------------------------------------

 - This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.


[documentation]: http://uaf.github.io/uaf/doc/pyuaf
[examples]: http://uaf.github.io/uaf/doc/pyuaf/client_examples.html
[Doxygen]: http://www.doxygen.org
[src]: http://github.com/uaf/uaf/blob/master/src
