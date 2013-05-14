<p align="center">
  <img src="http://github.com/uaf/uaf/raw/master/doc/img/logo/uaf_logo_200x67_opaque.png" alt="Logo"/>
</p>


UAF - the Unified Architecture Framework
========================================


What?
-------------------------------------------------------------------------------

 - The Unified Architecture Framework (UAF) is an open source software 
   framework to simplify the development of **OPC UA** applications 
   on **Linux** and **Microsoft Windows**, in **C++** and **Python**.
   
Why?
-------------------------------------------------------------------------------

 - The UAF is a framework (or "toolkit") that helps you to create advanced 
   OPC UA applications with minimal effort. Essentially, it takes care of
   some *technical* aspects (such as Session and Subscription management,
   server discovery, node resolution, ...) so that you can concentrate on 
   the *functional* aspects of your software application.  

 - The following Python example shows you some advantages of the UAF.
   In C++, the example would look quite similar.

    - **Intuitive API:**

      All code from the Software Developers Kit is wrapped into some 
      convenient namespaces and classes (many more than can be seen below 
      of course).

        ```python
        import pyuaf
        from pyuaf.util            import Node, NodeId, QualifiedName
        from pyuaf.util            import RelativePathElement, LocalizedText
        from pyuaf.util.primitives import UInt16
        from pyuaf.client          import Client
        from pyuaf.client.settings import ClientSettings
        ```
    
    - **Automatic discovery:**
    
       Just provide one or more Discovery URL(s), and the UAF will then
       automatically and periodically perform the discovery for you.
    
        ```python
        settings = ClientSettings()
        settings.applicationName = "myClient"
        settings.discoveryUrls.append("opc.tcp://localhost:4841")
        
        # create the client with the given settings
        myClient = Client(settings)
        ```
    
    - **Easy node addressing**
    
       You can address nodes in an absolute way 
        (via "NodeIds" and "ExpandedNodeIds")
       or in a relative way
        (via "RelativePaths").
       The UAF will resolve the nodes, regardless on what server they are hosted.
       
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
    
       You can now read/write/monitor/... the Value (or any other attribute) of the nodes 
       that we addressed above. **Even if these nodes are hosted by multiple servers**,
       the UAF will automatically:
       
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
        - even if the server that hosts your monitored items dies, and the 
           relative addresses of your monitored items now suddenly point to  
           nodes hosted by another (redundant) server!!
       
        ```python
        def myCallback(notification):
            print("New sensor status received: %d" %notification.data.value)
            
        myClient.createMonitoredData([tank5_sensor3_status], notificationCallbacks = [myCallback])
        ```
    
    - **More stuff**
        
        For instance, UAF clients have also a generic `processRequest` method that can process
        fully configurable `ReadRequest`s, `WriteRequest`s, `MethodCallRequest`s, ...
        
        Dive into the documentation or the examples to find out more!



Dependencies?
-------------------------------------------------------------------------------

 - The UAF is based on the commercial C++ Software Developers Kit from 
   Unified Automation. A demo version of this SDK can be downloaded
   from their website for free:
   http://www.unified-automation.com

 - More info about the dependencies: see dependencies.rst.txt

   
Status?
-------------------------------------------------------------------------------

 - Supported on the Client side:
   - read (synchronous + asynchronous)
   - write (synchronous + asynchronous)
   - method call (synchronous + asynchronous)
   - translate browse paths (synchronous)
   - create monitored data items (synchronous)
   - create monitored events items (synchronous)
 - Supported on the Server side:
   - nothing yet so far!


Installation?
-------------------------------------------------------------------------------

  - **Linux installation guide**: see install_linux.rst.txt
  
  - **Windows installation guide**: see install_windows.rst.txt


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

