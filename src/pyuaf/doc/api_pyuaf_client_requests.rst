``pyuaf.client.requests``
====================================================================================================

.. automodule:: pyuaf.client.requests




*class* AsyncCreateMonitoredDataRequest
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.requests.AsyncCreateMonitoredDataRequest
    
    An :class:`~pyuaf.client.requests.AsyncCreateMonitoredDataRequest` is an asynchronous request 
    to create one or more monitored data items.
    
    This class has the exact same methods and attributes as a 
    :class:`~pyuaf.client.requests.CreateMonitoredDataRequest`, so see the documentation
    of the latter.



*class* AsyncCreateMonitoredEventsRequest
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.requests.AsyncCreateMonitoredEventsRequest
    
    An :class:`~pyuaf.client.requests.AsyncCreateMonitoredEventsRequest` is an asynchronous request 
    to create one or more monitored event items.
    
    This class has the exact same methods and attributes as a 
    :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest`, so see the documentation
    of the latter.



*class* AsyncMethodCallRequest
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.requests.AsyncMethodCallRequest
    
    An :class:`~pyuaf.client.requests.AsyncMethodCallRequest` is an asynchronous request 
    to call one or more methods.
    
    This class has the exact same methods and attributes as a 
    :class:`~pyuaf.client.requests.MethodCallRequest`, so see the documentation
    of the latter.



*class* AsyncReadRequest
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.requests.AsyncReadRequest
    
    An :class:`~pyuaf.client.requests.AsyncReadRequest` is an asynchronous request 
    to read an attribute of one or more nodes.
    
    This class has the exact same methods and attributes as a 
    :class:`~pyuaf.client.requests.ReadRequest`, so see the documentation
    of the latter.



*class* AsyncWriteRequest
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.requests.AsyncWriteRequest
    
    An :class:`~pyuaf.client.requests.AsyncWriteRequest` is an asynchronous request 
    to write an attribute of one or more nodes.
    
    This class has the exact same methods and attributes as a 
    :class:`~pyuaf.client.requests.WriteRequest`, so see the documentation
    of the latter.




*class* BrowseNextRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.BrowseNextRequest

    A :class:`~pyuaf.client.requests.BrowseNextRequest` is a synchronous request to continue a
    previous browsing of one or more nodes.
    
    You only need to use this BrowseNext request if you have put maxAutoBrowseNext to 0 in the 
    previous Browse request (or if the automatic BrowseNext calls still resulted in 
    continuationPoints). For your convenience, it's much easier to simply use the BrowseRequest, 
    and let the UAF do the BrowseNext calls automatically for you!
    
    * Methods:

        .. automethod:: pyuaf.client.requests.BrowseNextRequest.__init__
    
            Create a new BrowseNextRequest object.
            
            :param targets: The targets of the request, either as:
            
                 - an ``int``, specifying the number of targets (0 by default)
                 - a single target (a :class:`~pyuaf.client.requests.BrowseNextRequestTarget`)
                 - a vector of targets (a :class:`~pyuaf.client.requests.BrowseNextRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.BrowseNextConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. automethod:: pyuaf.client.requests.BrowseNextRequest.__str__
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.BrowseNextRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.BrowseNextRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.BrowseNextRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.BrowseNextConfig`.
    
        .. autoattribute:: pyuaf.client.requests.BrowseNextRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.


*class* BrowseNextRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.BrowseNextRequestTarget

    A :class:`~pyuaf.client.requests.BrowseNextRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.BrowseNextRequest` that specifies the target that we were 
    browsing and the corresponding continuation point.
    
    You only need to use the BrowseNext request if you have put maxAutoBrowseNext to 0 in the 
    previous Browse request (or if the automatic BrowseNext calls still resulted in 
    continuationPoints). For your convenience, it's much easier to simply use the BrowseRequest, 
    and let the UAF do the BrowseNext calls automatically for you!

    
    * Methods:

        .. automethod:: pyuaf.client.requests.BrowseNextRequestTarget.__init__
    
            Create a new BrowseNextRequestTarget object.
            
            You can specify a BrowseNextRequestTarget either by providing nothing, or by providing
            an address (of type :class:`~pyuaf.util.Address`) and a continuation point (of type
            ``bytearray``).
            
    
        .. automethod:: pyuaf.client.requests.BrowseNextRequestTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.BrowseNextRequestTarget.address

            The address of the node that was already being browsed, as an 
            :class:`~pyuaf.util.Address`. So you can copy the address of the original
            BrowseRequest to here, so that the UAF can use this address to find out 
            to which server the BrowseNext call should be sent.
    
        .. autoattribute:: pyuaf.client.requests.BrowseNextRequestTarget.continuationPoint

            The continuation point, as received by the previous Browse or BrowseNext call.
            This attribute is of the Python built-in type ``bytearray``.
    

*class* BrowseNextRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.BrowseNextRequestTargetVector

    An BrowseNextRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.BrowseNextRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.BrowseNextRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import BrowseRequest, BrowseNextRequestTarget, BrowseNextRequestTargetVector
        >>> from pyuaf.client.results  import BrowseResult
        >>> from pyuaf.util            import Address, ExpandedNodeId, NodeId
        
        >>> # we simulate the request and result of a previous Browse call with two targets 
        >>> # (i.e. two nodes that were being browsed simultaneously)
        >>> originalRequest = BrowseRequest(2)
        >>> originalResult = BrowseResult()
        >>> originalResult.targets.resize(2)
        
        >>> # construct a vector without elements:
        >>> vec = BrowseNextRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(BrowseNextRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address = originalRequest.targets[0].address
        >>> vec[0].continuationPoint = originalResult.targets[0].continuationPoint
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = BrowseNextRequestTargetVector( 
        ...             [ BrowseNextRequestTarget(Address(NodeId("myId0", "myNs"), "myServerUri"), bytearray("abcd")),
        ...               BrowseNextRequestTarget(Address(NodeId("myId1", "myNs"), "myServerUri"), bytearray()) ] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = BrowseNextRequestTargetVector(3)
        >>> yetAnotherVec[0].address = Address(ExpandedNodeId("SomeId0", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].address = Address(ExpandedNodeId("SomeId1", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].address = Address(ExpandedNodeId("SomeId2", "SomeNs", "SomeServerUri"))


*class* BrowseRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.BrowseRequest

    A :class:`~pyuaf.client.requests.BrowseRequest` is a synchronous request to browse the 
    references of one or more nodes.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.BrowseRequest.__init__
    
            Create a new BrowseRequest object.
            
            :param targets: The targets of the request, either as:
            
                 - an ``int``, specifying the number of targets (0 by default)
                 - a single target (a :class:`~pyuaf.client.requests.BrowseRequestTarget`)
                 - a vector of targets (a :class:`~pyuaf.client.requests.BrowseRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.BrowseConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.BrowseRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.BrowseConfig`.
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.



*class* BrowseRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.BrowseRequestTarget

    A :class:`~pyuaf.client.requests.BrowseRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.BrowseRequest` that specifies the target to be browsed.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new BrowseRequestTarget object.
            
            You can specify a BrowseRequestTarget in two ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util                 import Address, ExpandedNodeId
                >>> from pyuaf.client.requests      import BrowseRequestTarget
                
                >>> addressOfNodeToBeBrowsed = Address(ExpandedNodeId("someId", "someNs", "someServerUri"))
                
                >>> # there are 2 ways to define a target:
                >>> target0 = BrowseRequestTarget()
                >>> target1 = BrowseRequestTarget(addressOfNodeToBeBrowsed)
                
                >>> # in case of the first target, you still need to specify an Address:
                >>> target0.address = addressOfNodeToBeBrowsed
    
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequestTarget.address

            The address of the node to be browsed, as an :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequestTarget.browseDirection

            Direction to follow when browsing the nodes, as an ``int`` defined in the 
            :mod:`~pyuaf.util.browsedirections` module. 
            :attr:`~pyuaf.util.browsedirections.Forward` by default.
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequestTarget.referenceTypeId
    
            The ExpandedNodeId of the type of references (i.e. the ReferenceType) to follow 
            (or its subtypes if the :attr:`~pyuaf.client.requests.BrowseRequestTarget.includeSubtypes` 
            flag is ``True``). The type of this attribute is an :class:`~pyuaf.util.ExpandedNodeId`.
            By default, the nodeId is not initialized with contents (i.e. nodeId.isNull() returns
            ``True``), so that all references will be followed.
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequestTarget.includeSubtypes

            A ``bool`` indicating that, if the 
            :attr:`~pyuaf.client.requests.BrowseRequestTarget.referenceTypeId` points to a 
            valid node, also the subtypes of the 
            :attr:`~pyuaf.client.requests.BrowseRequestTarget.referenceTypeId` 
            should be followed.
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequestTarget.nodeClassMask
        
            A 32-bit ``int`` representing a mask that specifies the node classes that should be 
            returned. The mask has the following bits assigned:
            
             - 0: Object
             - 1: Variable
             - 2: Method
             - 3: ObjectType
             - 4: VariableType
             - 5: ReferenceType
             - 6: DataType
             - 7: View
          
            Leave the mask 0 (=default!) to return all node classes. 
    
        .. autoattribute:: pyuaf.client.requests.BrowseRequestTarget.resultMask
        
            A 32-bit ``int`` representing a mask that specifies the fields in the reference 
            description to be returned. The mask has the following bits assigned:
            
             - 0: ReferenceType
             - 1: IsForward
             - 2: NodeClass
             - 3: BrowseName
             - 4: DisplayName
             - 5: TypeDefinition
          
            By default, this mask is 63 (so 0b111111).



*class* BrowseRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.BrowseRequestTargetVector

    An BrowseRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.BrowseRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.BrowseRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import BrowseRequestTarget, BrowseRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId, NodeId
        
        >>> # construct a vector without elements:
        >>> vec = BrowseRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(BrowseRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address = Address(NodeId("SomeId", "SomeNs"), "SomeServerUri")
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = BrowseRequestTargetVector( 
        ...             [ BrowseRequestTarget(Address(NodeId("myId0", "myNs"), "myServerUri")),
        ...               BrowseRequestTarget(Address(NodeId("myId1", "myNs"), "myServerUri")) ] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = BrowseRequestTargetVector(3)
        >>> yetAnotherVec[0].address = Address(ExpandedNodeId("SomeId0", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].address = Address(ExpandedNodeId("SomeId1", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].address = Address(ExpandedNodeId("SomeId2", "SomeNs", "SomeServerUri"))







*class* CreateMonitoredDataRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.CreateMonitoredDataRequest

    A :class:`~pyuaf.client.requests.CreateMonitoredDataRequest` is a synchronous request to 
    create one or more monitored data items.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.CreateMonitoredDataRequest.__init__
    
            Create a new CreateMonitoredDataRequest object.
            
            :param targets: The targets of the request, either as:
            
                             - an ``int``, specifying the number of targets (0 by default)
                             - a single target (a :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTarget`)
                             - a vector of targets (a :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.CreateMonitoredDataConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
            :param subscriptionConfig: The config containing the subscription settings.
            :type subscriptionConfig: :class:`~pyuaf.client.configs.SubscriptionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.CreateMonitoredDataConfig`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequest.subscriptionConfig

            The subscription config, as a :class:`~pyuaf.client.configs.SubscriptionConfig`.


*class* CreateMonitoredDataRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.CreateMonitoredDataRequestTarget

    A :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.CreateMonitoredDataRequest` that specifies the target to be 
    monitored.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new CreateMonitoredDataRequestTarget object.
            
            The default 
              - attributeId is :attr:`~pyuaf.util.attributeids.Value`
              - monitoringMode is :attr:`~pyuaf.util.monitoringmodes.Reporting`
              - samplingIntervalSec is 0.0
              - queueSize is 1
              - discardOldest is True.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.address

            The address of the node of which the attribute will be monitored, 
            as a :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.attributeId

            The attribute id to be monitored, as an ``int`` defined 
            in :mod:`~pyuaf.util.attributeids`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.indexRange
    
            The index range (as a ``str``), in case you want to partially monitor an array.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.monitoringMode

            The monitoring mode, as an ``int`` defined in :mod:`~pyuaf.util.monitoringmodes`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.samplingIntervalSec

            The rate, in seconds (as a ``float``), at which the monitored item should be sampled 
            by the server. 0.0 means as fast as possible.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.queueSize

            The size of the queue at the server side, as an ``int``.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.discardOldest

            ``bool``: Discard the oldest item in the queue, or not.

        .. autoattribute:: pyuaf.client.requests.CreateMonitoredDataRequestTarget.dataChangeFilter

            The data change filter settings, as a :class:`~pyuaf.util.DataChangeFilter`.



*class* CreateMonitoredDataRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.CreateMonitoredDataRequestTargetVector

    An CreateMonitoredDataRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.CreateMonitoredDataRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import CreateMonitoredDataRequestTarget, CreateMonitoredDataRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId
        
        >>> # construct a vector without elements:
        >>> vec = CreateMonitoredDataRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(CreateMonitoredDataRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address   = Address(ExpandedNodeId("SomeId", "SomeNs", "SomeServerUri"))
        >>> vec[0].queueSize = 5
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = CreateMonitoredDataRequestTargetVector( [CreateMonitoredDataRequestTarget(), CreateMonitoredDataRequestTarget()] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = CreateMonitoredDataRequestTargetVector(3)
        >>> yetAnotherVec[0].queueSize = 10
        >>> yetAnotherVec[1].queueSize = 10
        >>> yetAnotherVec[2].queueSize = 10



*class* CreateMonitoredEventsRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.CreateMonitoredEventsRequest

    A :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest` is a synchronous request to 
    create one or more monitored event items.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.CreateMonitoredEventsRequest.__init__
    
            Create a new CreateMonitoredEventsRequest object.
            
            :param targets: The targets of the request, either as:
            
                             - an ``int``, specifying the number of targets (0 by default)
                             - a single target (a :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTarget`)
                             - a vector of targets (a :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.CreateMonitoredEventsConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
            :param subscriptionConfig: The config containing the subscription settings.
            :type subscriptionConfig: :class:`~pyuaf.client.configs.SubscriptionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.CreateMonitoredEventsConfig`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequest.subscriptionConfig

            The subscription config, as a :class:`~pyuaf.client.configs.SubscriptionConfig`.


*class* CreateMonitoredEventsRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget

    A :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest` that specifies the target to be 
    monitored.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new CreateMonitoredEventsRequestTarget object.
            
            The default 
              - monitoringMode is :attr:`~pyuaf.util.monitoringmodes.Reporting`
              - samplingIntervalSec is 0.0
              - queueSize is 1
              - discardOldest is True.
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget.address

            The address of the node of which the attribute will be monitored, 
            as a :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget.monitoringMode

            The monitoring mode, as an ``int`` defined in :mod:`~pyuaf.util.monitoringmodes`.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget.samplingIntervalSec

            The rate, in seconds (as a ``float``), at which the monitored item should be sampled 
            by the server. 0.0 means as fast as possible.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget.queueSize

            The size of the queue at the server side, as an ``int``.
    
        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget.discardOldest

            ``bool``: Discard the oldest item in the queue, or not.

        .. autoattribute:: pyuaf.client.requests.CreateMonitoredEventsRequestTarget.eventFilter

            The event filter settings, as an :class:`~pyuaf.util.EventFilter`.



*class* CreateMonitoredEventsRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.CreateMonitoredEventsRequestTargetVector

    An CreateMonitoredEventsRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.CreateMonitoredEventsRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import CreateMonitoredEventsRequestTarget, CreateMonitoredEventsRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId
        
        >>> # construct a vector without elements:
        >>> vec = CreateMonitoredEventsRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(CreateMonitoredEventsRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address   = Address(ExpandedNodeId("SomeId", "SomeNs", "SomeServerUri"))
        >>> vec[0].queueSize = 5
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = CreateMonitoredEventsRequestTargetVector( [CreateMonitoredEventsRequestTarget(), CreateMonitoredEventsRequestTarget()] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = CreateMonitoredEventsRequestTargetVector(3)
        >>> yetAnotherVec[0].queueSize = 10
        >>> yetAnotherVec[1].queueSize = 10
        >>> yetAnotherVec[2].queueSize = 10










*class* HistoryReadRawModifiedRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.HistoryReadRawModifiedRequest

    A :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest` is a synchronous request to 
    read historical data within a given time interval.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.HistoryReadRawModifiedRequest.__init__
    
            Create a new HistoryReadRawModifiedRequest object.
            
            :param targets: The targets of the request, either as:
            
                 - an ``int``, specifying the number of targets (0 by default)
                 - a single target (a :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequestTarget`)
                 - a vector of targets (a :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.HistoryReadRawModifiedConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.HistoryReadRawModifiedConfig`.
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.



*class* HistoryReadRawModifiedRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.HistoryReadRawModifiedRequestTarget

    A :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest` that specifies the node
    that provides the historical information, the continuation point in case you want to 
    manually continue a history reading, etc.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new HistoryReadRawModifiedRequestTarget object.
            
            You can specify a HistoryReadRawModifiedRequestTarget in three ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util                 import Address, ExpandedNodeId
                >>> from pyuaf.client.requests      import HistoryReadRawModifiedRequestTarget
                
                >>> addressOfNodeToBeRead = Address(ExpandedNodeId("someId", "someNs", "someServerUri"))
                >>> somePreviousContinuationPoint = bytearray() # normally you would copy the bytearray
                >>>                                             # from a previous HistoryReadRawModifiedResult
                
                >>> # there are 3 ways to define a target:
                >>> target0 = HistoryReadRawModifiedRequestTarget()
                >>> target1 = HistoryReadRawModifiedRequestTarget(addressOfNodeToBeRead)
                >>> target2 = HistoryReadRawModifiedRequestTarget(addressOfNodeToBeRead, somePreviousContinuationPoint)
                
                >>> # in case of the first target, you still need to specify an Address:
                >>> target0.address = addressOfNodeToBeBrowsed
    
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequestTarget.address

            The address of the node from which the historical data should be retrieved, 
            as an :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequestTarget.continuationPoint

            The continuation point of a previous HistoryRead service call, as a built-in Python ``bytearray``.
            The UAF can automatically handle continuation points, for more info take a look
            at the documentation of :attr:`pyuaf.client.settings.HistoryReadRawModifiedSettings.maxAutoReadMore`.
            If you decide to use the continuation points manually, you can still do so of course
            by copying the continuation point of a previous result
            (:attr:`pyuaf.client.results.HistoryReadRawModifiedResultTarget.continuationPoint`) to here.
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequestTarget.indexRange
    
            The index range in case the node is an array, as a ``str``.
    
        .. autoattribute:: pyuaf.client.requests.HistoryReadRawModifiedRequestTarget.dataEncoding

            The data encoding, as a :class:`~pyuaf.util.QualifiedName`.
            Leave NULL (i.e. don't touch) if you want to use the default encoding.
    



*class* HistoryReadRawModifiedRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.HistoryReadRawModifiedRequestTargetVector

    An HistoryReadRawModifiedRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.HistoryReadRawModifiedRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import HistoryReadRawModifiedRequestTarget, HistoryReadRawModifiedRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId, NodeId
        
        >>> # construct a vector without elements:
        >>> vec = HistoryReadRawModifiedRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(HistoryReadRawModifiedRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address = Address(NodeId("SomeId", "SomeNs"), "SomeServerUri")
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = HistoryReadRawModifiedRequestTargetVector( 
        ...             [ HistoryReadRawModifiedRequestTarget(Address(NodeId("myId0", "myNs"), "myServerUri")),
        ...               HistoryReadRawModifiedRequestTarget(Address(NodeId("myId1", "myNs"), "myServerUri")) ] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = HistoryReadRawModifiedRequestTargetVector(3)
        >>> yetAnotherVec[0].address = Address(ExpandedNodeId("SomeId0", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].address = Address(ExpandedNodeId("SomeId1", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].address = Address(ExpandedNodeId("SomeId2", "SomeNs", "SomeServerUri"))











*class* MethodCallRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.MethodCallRequest

    A :class:`~pyuaf.client.requests.MethodCallRequest` is a synchronous request to call one or 
    more methods.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.MethodCallRequest.__init__
    
            Create a new MethodCallRequest object.
            
            :param targets: The targets of the request, either as:
            
                             - an ``int``, specifying the number of targets (0 by default)
                             - a single target (a :class:`~pyuaf.client.requests.MethodCallRequestTarget`)
                             - a vector of targets (a :class:`~pyuaf.client.requests.MethodCallRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.MethodCallConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.MethodCallRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.MethodCallRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.MethodCallRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.MethodCallConfig`.
    
        .. autoattribute:: pyuaf.client.requests.MethodCallRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.


*class* MethodCallRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.MethodCallRequestTarget

    A :class:`~pyuaf.client.requests.MethodCallRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.MethodCallRequest` that specifies the target to be called.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new MethodCallRequestTarget object.
            
            You can specify a MethodCallRequestTarget in two ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util             import Address, ExpandedNodeId, VariantVector
                >>> from pyuaf.util.primitives  import UInt32, Double
                >>> from pyuaf.client.requests  import MethodCallRequestTarget
                
                >>> objectAddress  = Address(ExpandedNodeId("someId", "someNs", "someServerUri"))
                >>> methodAddress  = Address(ExpandedNodeId("someOtherId", "someNs", "someServerUri"))
                >>> inputArguments = VariantVector()
                >>> inputArguments.append(UInt32(123))
                >>> inputArguments.append("some string")
                >>> inputArguments.append(Double(-3.14))
                
                >>> # there are 2 ways to define a target:
                >>> target0 = MethodCallRequestTarget()
                >>> target1 = MethodCallRequestTarget(objectAddress, methodAddress, inputArguments)
                
                >>> # in case of the first target, you still need to specify the addresses and arguments:
                >>> target0.objectAddress  = objectAddress
                >>> target0.methodAddress  = methodAddress
                >>> target0.inputArguments = inputArguments
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.MethodCallRequestTarget.objectAddress

            The address of the context node of the method call, as a :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.MethodCallRequestTarget.methodAddress

            The address of the node representing the method, as a :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.MethodCallRequestTarget.inputArguments
    
            The input arguments of the method call, as a :class:`~pyuaf.util.VariantVector`.



*class* MethodCallRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.MethodCallRequestTargetVector

    An MethodCallRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.MethodCallRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.MethodCallRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import MethodCallRequestTarget, MethodCallRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId
        
        >>> # construct a vector without elements:
        >>> vec = MethodCallRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(MethodCallRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].objectAddress = Address(ExpandedNodeId("SomeId"     , "SomeNs", "SomeServerUri"))
        >>> vec[0].methodAddress = Address(ExpandedNodeId("SomeOtherId", "SomeNs", "SomeServerUri"))
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = MethodCallRequestTargetVector( [MethodCallRequestTarget(), MethodCallRequestTarget()] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = MethodCallRequestTargetVector(3)
        >>> yetAnotherVec[0].objectAddress = Address(ExpandedNodeId("SomeId"     , "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[0].methodAddress = Address(ExpandedNodeId("SomeOtherId", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].objectAddress = Address(ExpandedNodeId("SomeId"     , "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].methodAddress = Address(ExpandedNodeId("SomeOtherId", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].objectAddress = Address(ExpandedNodeId("SomeId"     , "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].methodAddress = Address(ExpandedNodeId("SomeOtherId", "SomeNs", "SomeServerUri"))



*class* ReadRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.ReadRequest

    A :class:`~pyuaf.client.requests.ReadRequest` is a synchronous request to read an attribute of 
    one or more nodes.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.ReadRequest.__init__
    
            Create a new ReadRequest object.
            
            :param targets: The targets of the request, either as:
            
                             - an ``int``, specifying the number of targets (0 by default)
                             - a single target (a :class:`~pyuaf.client.requests.ReadRequestTarget`)
                             - a vector of targets (a :class:`~pyuaf.client.requests.ReadRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.ReadConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.ReadRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.ReadRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.ReadRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.ReadConfig`.
    
        .. autoattribute:: pyuaf.client.requests.ReadRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.


*class* ReadRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.ReadRequestTarget

    A :class:`~pyuaf.client.requests.ReadRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.ReadRequest` that specifies the target to be read.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new ReadRequestTarget object.
            
            The default attributeId is :attr:`~pyuaf.util.attributeids.Value`.
            
            You can specify a ReadRequestTarget in three ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util                 import Address, ExpandedNodeId
                >>> from pyuaf.util.attributeids    import DisplayName
                >>> from pyuaf.client.requests      import ReadRequestTarget
                
                >>> addressOfNodeToBeRead = Address(ExpandedNodeId("someId", "someNs", "someServerUri"))
                
                >>> # there are 3 ways to define a target:
                >>> target0 = ReadRequestTarget()
                >>> target1 = ReadRequestTarget(addressOfNodeToBeRead)              # attribute id = Value
                >>> target2 = ReadRequestTarget(addressOfNodeToBeRead, DisplayName) # attribute id = DisplayName
                
                >>> # in case of the first target, you still need to specify an Address:
                >>> target0.address = addressOfNodeToBeRead
    
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.ReadRequestTarget.address

            The address of the node of which the attribute will be read, 
            as a :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.ReadRequestTarget.attributeId

            The id of the attribute to be read, as an ``int`` defined 
            in :mod:`~pyuaf.util.attributeids`.
    
        .. autoattribute:: pyuaf.client.requests.ReadRequestTarget.indexRange
    
            The index range (as a ``str``), in case you want to partially read an array.



*class* ReadRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.ReadRequestTargetVector

    An ReadRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.ReadRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.ReadRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import ReadRequestTarget, ReadRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId
        
        >>> # construct a vector without elements:
        >>> vec = ReadRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(ReadRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address = Address(ExpandedNodeId("SomeId", "SomeNs", "SomeServerUri"))
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = ReadRequestTargetVector( [ReadRequestTarget(), ReadRequestTarget()] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = ReadRequestTargetVector(3)
        >>> yetAnotherVec[0].address = Address(ExpandedNodeId("SomeId0", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].address = Address(ExpandedNodeId("SomeId1", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].address = Address(ExpandedNodeId("SomeId2", "SomeNs", "SomeServerUri"))


*class* TranslateBrowsePathsToNodeIdsRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest

    A :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest` is a synchronous request 
    to translate one or more browse paths to NodeIds.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest.__init__
    
            Create a new TranslateBrowsePathsToNodeIdsRequest object.
            
            :param targets: The targets of the request, either as:
            
                             - an ``int``, specifying the number of targets (0 by default)
                             - a single target (a :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget`)
                             - a vector of targets (a :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig`.
    
        .. autoattribute:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.


*class* TranslateBrowsePathsToNodeIdsRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget

    A :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest` that specifies the target 
    to be translated.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new TranslateBrowsePathsToNodeIdsRequestTarget object.
            
            You can specify a TranslateBrowsePathsToNodeIdsRequestTarget in two ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util             import BrowsePath
                >>> from pyuaf.client.requests  import TranslateBrowsePathsToNodeIdsRequestTarget
                
                >>> browsePathToBeTranslated = BrowsePath()
                
                >>> # there are 2 ways to define a target:
                >>> target0 = TranslateBrowsePathsToNodeIdsRequestTarget()
                >>> target1 = TranslateBrowsePathsToNodeIdsRequestTarget(browsePathToBeTranslated)
                
                >>> # in case of the first target, you still need to specify a node and some data:
                >>> target0.browsePath = browsePathToBeTranslated
    
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget.browsePath

            The browse path to be translated, as a :class:`~pyuaf.util.BrowsePath`.
    


*class* TranslateBrowsePathsToNodeIdsRequestTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTargetVector

    An TranslateBrowsePathsToNodeIdsRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import TranslateBrowsePathsToNodeIdsRequestTarget, \
        ...                                   TranslateBrowsePathsToNodeIdsRequestTargetVector
        >>> from pyuaf.util            import BrowsePath, ExpandedNodeId, RelativePathElement, QualifiedName
        
        >>> # construct a vector without elements:
        >>> vec = TranslateBrowsePathsToNodeIdsRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> # define a starting ExpandedNodeId for the browse path
        >>> startOfBrowsePath = ExpandedNodeId("SomeId", "SomeNs", "SomeServerUri")
        
        >>> vec.append(TranslateBrowsePathsToNodeIdsRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].browsePath = BrowsePath(startOfBrowsePath, [RelativePathElement(QualifiedName("SomeName", "SomeNs"))] )
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = TranslateBrowsePathsToNodeIdsRequestTargetVector( 
        ...               [TranslateBrowsePathsToNodeIdsRequestTarget(), 
        ...                TranslateBrowsePathsToNodeIdsRequestTarget()] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = TranslateBrowsePathsToNodeIdsRequestTargetVector(3)
        >>> yetAnotherVec[0].browsePath = BrowsePath(startOfBrowsePath, [RelativePathElement(QualifiedName("SomeName0", "SomeNs"))] )
        >>> yetAnotherVec[1].browsePath = BrowsePath(startOfBrowsePath, [RelativePathElement(QualifiedName("SomeName1", "SomeNs"))] )
        >>> yetAnotherVec[2].browsePath = BrowsePath(startOfBrowsePath, [RelativePathElement(QualifiedName("SomeName2", "SomeNs"))] )


*class* WriteRequest
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.WriteRequest

    A :class:`~pyuaf.client.requests.WriteRequest` is a synchronous request to write an attribute 
    of one or more nodes.
    
    * Methods:

        .. automethod:: pyuaf.client.requests.WriteRequest.__init__
    
            Create a new WriteRequest object.
            
            :param targets: The targets of the request, either as:
            
                             - an ``int``, specifying the number of targets (0 by default)
                             - a single target (a :class:`~pyuaf.client.requests.WriteRequestTarget`)
                             - a vector of targets (a :class:`~pyuaf.client.requests.WriteRequestTargetVector`)
    
            :param serviceConfig: The config for the service settings.
            :type serviceConfig: :class:`~pyuaf.client.configs.WriteConfig`
    
            :param sessionConfig: The config containing the session settings.
            :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
    
        .. method:: __str__()
    
            Get a formatted string representation of the request.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.WriteRequest.targets

            The targets, as a :class:`~pyuaf.client.requests.WriteRequestTargetVector`.
    
        .. autoattribute:: pyuaf.client.requests.WriteRequest.serviceConfig

            The service config, as a :class:`~pyuaf.client.configs.WriteConfig`.
    
        .. autoattribute:: pyuaf.client.requests.WriteRequest.sessionConfig

            The session config, as a :class:`~pyuaf.client.configs.SessionConfig`.



*class* WriteRequestTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.WriteRequestTarget

    A :class:`~pyuaf.client.requests.WriteRequestTarget` is the part of 
    a :class:`~pyuaf.client.requests.WriteRequest` that specifies the target to be written.

    
    * Methods:

        .. method:: __init__(args*)
    
            Create a new WriteRequestTarget object.
            
            The default attributeId is :attr:`~pyuaf.util.attributeids.Value`.
            
            You can specify a WriteRequestTarget in three ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util                 import Address, ExpandedNodeId, LocalizedText
                >>> from pyuaf.util.attributeids    import DisplayName
                >>> from pyuaf.util.primitives      import UInt32
                >>> from pyuaf.client.requests      import WriteRequestTarget
                
                >>> addressOfNodeToBeWritten  = Address(ExpandedNodeId("someId", "someNs", "someServerUri"))
                
                >>> # there are 3 ways to define a target:
                >>> target0 = WriteRequestTarget()
                >>> target1 = WriteRequestTarget(addressOfNodeToBeWritten, UInt32(332))                                     # attribute id = Value
                >>> target2 = WriteRequestTarget(addressOfNodeToBeWritten, LocalizedText("en", "Some name"), DisplayName)   # attribute id = DisplayName
                
                >>> # in case of the first target, you still need to specify an address and some data:
                >>> target0.address = addressOfNodeToBeWritten
                >>> target0.data    = UInt32(332)
    
    
        .. method:: __str__()
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.address

            The address of the node of which the attribute will be written, 
            as a :class:`~pyuaf.util.Address`.
    
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.attributeId

            The attribute id to be written, as an ``int`` defined 
            in :mod:`~pyuaf.util.attributeids`.
            
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.indexRange
    
            The index range (as a ``str``), in case you want to partially write an array.


    * Attributes inherited from :class:`pyuaf.util.DataValue`
    
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.status
        
            The status of the data, as a :class:`~pyuaf.util.Status` instance.
            The status contains the OPC UA status code of the data. 
    
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.data

            The data to be written, as one of the data types described in :ref:`note-variants`.
  
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.sourceTimestamp
        
            The source time stamp of the data, as a :class:`~pyuaf.util.DateTime` instance.
  
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.serverTimestamp
        
            The server time stamp of the data, as a :class:`~pyuaf.util.DateTime` instance.
  
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.sourcePicoseconds
    
            The number of 10 picosecond intervals that need to be added to the source timestamp
            (to get a higher time resolution), as an ``int``.
  
        .. autoattribute:: pyuaf.client.requests.WriteRequestTarget.serverPicoseconds
    
            The number of 10 picosecond intervals that need to be added to the server timestamp
            (to get a higher time resolution), as an ``int``.
    


*class* WriteRequestTargetVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.requests.WriteRequestTargetVector

    An WriteRequestTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.requests.WriteRequestTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.requests.WriteRequestTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.requests import WriteRequestTarget, WriteRequestTargetVector
        >>> from pyuaf.util            import Address, ExpandedNodeId
        >>> from pyuaf.util.primitives import UInt32, Float
        
        >>> # construct a vector without elements:
        >>> vec = WriteRequestTargetVector()
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(WriteRequestTarget())
        >>> noOfElements = len(vec) # will be 1
        >>> vec[0].address = Address(ExpandedNodeId("SomeId", "SomeNs", "SomeServerUri"))
        >>> vec[0].data    = UInt32(1234)
        
        >>> vec.resize(4)
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a vector from a regular Python list:
        >>> otherVec = WriteRequestTargetVector( [WriteRequestTarget(), WriteRequestTarget()] )
        
        >>> # or you may specify a number of targets directly
        >>> yetAnotherVec = WriteRequestTargetVector(3)
        >>> yetAnotherVec[0].address = Address(ExpandedNodeId("SomeId0", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[0].data    = UInt32(1234)
        >>> yetAnotherVec[1].address = Address(ExpandedNodeId("SomeId1", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[1].data    = Float(0.1234)
        >>> yetAnotherVec[2].address = Address(ExpandedNodeId("SomeId2", "SomeNs", "SomeServerUri"))
        >>> yetAnotherVec[2].data    = "test"

        
        