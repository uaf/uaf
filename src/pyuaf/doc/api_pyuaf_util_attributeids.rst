

``pyuaf.util.attributeids``
====================================================================================================

.. automodule:: pyuaf.util.attributeids

    This module defines the attribute ids. 
    
    Each node in an OPC UA address space contains several common attributes (a NodeId, a Display
    Name, a Browse Name, ... ) and some additional attributes depending on the class of the node 
    (e.g. the Value attribute if the node is of class Variable). The AttributeId specifies which
    attribute we're talking about.
    
    Usage example::
        
        import pyuaf
        from pyuaf.client import Client
        from pyuaf.util   import Address, ExpandedNodeId, attributeids
        
        myClient = Client()
        
        # define the address of the node of which we want to read the DisplayName and Value:
        address = Address(ExpandedNodeId("myNode", "myNameSpaceUri", "myServerUri"))
        
        # create a read request with two targets:
        request = pyuaf.client.requests.ReadRequest(2)
        request.targets[0].address     = address
        request.targets[0].attributeId = attributeids.DisplayName
        request.targets[1].address     = address
        request.targets[1].attributeId = attributeids.Value


    * Attributes:
    
        .. autoattribute:: pyuaf.util.attributeids.NodeId
        
            The NodeId is the "absolute address" of a node unique within a server's address space.
    
        .. autoattribute:: pyuaf.util.attributeids.NodeClass
        
            The NodeClass can be ObjectType, Object, VariableType, Variable, Method, View, ...
    
        .. autoattribute:: pyuaf.util.attributeids.BrowseName
        
            A BrowseName is a human readable name to browse the node within an address space.
    
        .. autoattribute:: pyuaf.util.attributeids.DisplayName
        
            A DisplayName is a localized, human readable name of the node.
    
        .. autoattribute:: pyuaf.util.attributeids.Description
        
            A Description is a localized string which describes the node.
    
        .. autoattribute:: pyuaf.util.attributeids.WriteMask
        
            A WriteMask specifies which node attributes can be written.
    
        .. autoattribute:: pyuaf.util.attributeids.UserWriteMask
        
            A UserWriteMask specifies which node attributes can be written by the current user.
    
        .. autoattribute:: pyuaf.util.attributeids.IsAbstract
        
            The IsAbstract flag specifies whether or not the ObjectType, VariableType or DataType can 
            be instantiated.
    
        .. autoattribute:: pyuaf.util.attributeids.Symmetric
        
            The Symmetric flag specifies whether or not the forward and inverse references of the 
            ReferenceType have the same meaning.
    
        .. autoattribute:: pyuaf.util.attributeids.InverseName
        
            The InverseName holds the browse name for an inverse reference.
    
        .. autoattribute:: pyuaf.util.attributeids.ContainsNoLoops
        
            The ContainsNoLoops flag specifies whether or not forward references of a View may result in a loop.
    
        .. autoattribute:: pyuaf.util.attributeids.EventNotifier
        
            Indicates that the node can be used to subscribe to events.
    
        .. autoattribute:: pyuaf.util.attributeids.Value
        
            The Value holds the value of a variable.
    
        .. autoattribute:: pyuaf.util.attributeids.DataType
        
            The DataType holds the node id of the data type of a Variable.
    
        .. autoattribute:: pyuaf.util.attributeids.ValueRank
        
            The ValueRank holds the number of dimensions in the value of a VariableType.
    
        .. autoattribute:: pyuaf.util.attributeids.ArrayDimensions
        
            The optional ArrayDimensions is an array of dimension lengths, in case the Variable is an 
            array.
    
        .. autoattribute:: pyuaf.util.attributeids.AccessLevel
        
           The AccessLevel byte specifies how a Variable may be accessed.
    
        .. autoattribute:: pyuaf.util.attributeids.UserAccessLevel
        
           The UserAccessLevel byte specifies how a Variable may be accessed by the current user.
    
        .. autoattribute:: pyuaf.util.attributeids.MinimumSamplingInterval
        
           The MinimumSamplingInterval specifies the minimum sampling time (in milliseconds!) for the Variable.
    
        .. autoattribute:: pyuaf.util.attributeids.Historizing
        
           The Historizing flag specifies whether or not the historical data is recorded for the Variable.
    
        .. autoattribute:: pyuaf.util.attributeids.Executable
        
           The Executable flag specifies whether or not the Method can be called.
    
        .. autoattribute:: pyuaf.util.attributeids.UserExecutable
        
           The UserExecutable flag specifies whether or not the Method can be called by the current user.



    * Functions:


        .. autofunction:: pyuaf.util.attributeids.toString(attributeId)
        
            Get a string representation of the application type.
        
            :param attributeId: The attribute id, e.g. :py:attr:`pyuaf.util.attributeids.Value`.
            :type  attributeId: ``int``
            :return: The name of the attribute id, e.g. 'Value'.
            :rtype:  ``str``

