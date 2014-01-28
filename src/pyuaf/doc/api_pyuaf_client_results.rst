``pyuaf.client.results``
====================================================================================================

.. automodule:: pyuaf.client.results




*class* AsyncCreateMonitoredDataResult
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.results.AsyncCreateMonitoredDataResult

    An :class:`~pyuaf.client.results.AsyncCreateMonitoredDataResult` is the immediate result of an 
    :class:`~pyuaf.client.requests.AsyncCreateMonitoredDataRequest`. 
    It only gives you information about whether the client could successfully process 
    (e.g. resolve any addresses, create the necessary sessions, ...) the asynchronous request. 
    
    The actual useful asynchronous result of the request is given to you as a regular 
    :class:`~pyuaf.client.results.CreateMonitoredDataResult`, via a callback mechanism.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.AsyncCreateMonitoredDataResult.__init__
    
            Create a new AsyncCreateMonitoredDataResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.AsyncCreateMonitoredDataResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.AsyncCreateMonitoredDataResult.targets

            The targets, as an :class:`~pyuaf.client.results.AsyncResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.AsyncCreateMonitoredDataResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.AsyncCreateMonitoredDataResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.AsyncCreateMonitoredDataRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.AsyncCreateMonitoredDataResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.



*class* AsyncCreateMonitoredEventsResult
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.results.AsyncCreateMonitoredEventsResult

    An :class:`~pyuaf.client.results.AsyncCreateMonitoredEventsResult` is the immediate result of an 
    :class:`~pyuaf.client.requests.AsyncCreateMonitoredEventsRequest`. 
    It only gives you information about whether the client could successfully process 
    (e.g. resolve any addresses, create the necessary sessions, ...) the asynchronous request. 
    
    The actual useful asynchronous result of the request is given to you as a regular 
    :class:`~pyuaf.client.results.CreateMonitoredEventsResult`, via a callback mechanism.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.AsyncCreateMonitoredEventsResult.__init__
    
            Create a new AsyncCreateMonitoredEventsResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.AsyncCreateMonitoredEventsResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.AsyncCreateMonitoredEventsResult.targets

            The targets, as an :class:`~pyuaf.client.results.AsyncResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.AsyncCreateMonitoredEventsResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.AsyncCreateMonitoredEventsResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.AsyncCreateMonitoredEventsRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.AsyncCreateMonitoredEventsResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* AsyncMethodCallResult
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.results.AsyncMethodCallResult

    An :class:`~pyuaf.client.results.AsyncMethodCallResult` is the immediate result of an 
    :class:`~pyuaf.client.requests.AsyncMethodCallRequest`. 
    It only gives you information about whether the client could successfully process 
    (e.g. resolve any addresses, create the necessary sessions, ...) the asynchronous request. 
    
    The actual useful asynchronous result of the request is given to you as a regular 
    :class:`~pyuaf.client.results.MethodCallResult`, via a callback mechanism.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.AsyncMethodCallResult.__init__
    
            Create a new AsyncMethodCallResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.AsyncMethodCallResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.AsyncMethodCallResult.targets

            The targets, as an :class:`~pyuaf.client.results.AsyncResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.AsyncMethodCallResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.AsyncMethodCallResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.AsyncMethodCallRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.AsyncMethodCallResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.




*class* AsyncReadResult
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.results.AsyncReadResult

    An :class:`~pyuaf.client.results.AsyncReadResult` is the immediate result of an 
    :class:`~pyuaf.client.requests.AsyncReadRequest`. 
    It only gives you information about whether the client could successfully process 
    (e.g. resolve any addresses, create the necessary sessions, ...) the asynchronous request. 
    
    The actual useful asynchronous result of the request is given to you as a regular 
    :class:`~pyuaf.client.results.ReadResult`, via a callback mechanism.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.AsyncReadResult.__init__
    
            Create a new AsyncReadResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.AsyncReadResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.AsyncReadResult.targets

            The targets, as an :class:`~pyuaf.client.results.AsyncResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.AsyncReadResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.AsyncReadResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.AsyncReadRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.AsyncReadResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* AsyncResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.AsyncResultTarget

    A :class:`~pyuaf.client.results.AsyncResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.ReadRequestTarget` or 
    :class:`~pyuaf.client.requests.WriteRequestTarget` or ... that was part of the invoked
    request.
     
    So the first target of the asynchronous request (the ``AsyncxxxxxRequest``) corresponds to
     
      - the first target of the immediate result (the ``AsyncxxxxxResult``)
      - and the first target of the callback result (the ``xxxxxResult``)
    
    This target is the "immediate" result of an asynchronous request target. Meaning: it will only 
    give you information about whether the asynchronous target was successfully sent (it tells you
    for instance if the addresses of the target could be resolved). The actual useful
    result of the request will come asynchronously, via a callback function.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.AsyncResultTarget.__init__
    
            Create a new AsyncResultTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.AsyncResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.AsyncResultTarget.status

            Status of the result target (Good if the request target was used in the asynchronous
            request, Bad if not), as a :class:`~pyuaf.util.Status` instance.
    
            A Good status means only that this target was successfully resolved, and sent to the
            server.
        
        .. autoattribute:: pyuaf.client.results.AsyncResultTarget.clientConnectionId

            The id of the session that was used for this target.



*class* AsyncResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.AsyncResultTargetVector

    An AsyncResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.AsyncResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.AsyncResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import AsyncResultTarget, AsyncResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = AsyncResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood  = targets[0].status.isGood()
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(AsyncResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...


*class* AsyncWriteResult
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.results.AsyncWriteResult

    An :class:`~pyuaf.client.results.AsyncWriteResult` is the immediate result of an 
    :class:`~pyuaf.client.requests.AsyncWriteRequest`. 
    It only gives you information about whether the client could successfully process 
    (e.g. resolve any addresses, create the necessary sessions, ...) the asynchronous
    request. 
    
    The actual useful asynchronous result of the request is given to you as a regular 
    :class:`~pyuaf.client.results.WriteResult`, via a callback mechanism.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.AsyncWriteResult.__init__
    
            Create a new AsyncWriteResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.AsyncWriteResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.AsyncWriteResult.targets

            The targets, as an :class:`~pyuaf.client.results.AsyncResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.AsyncWriteResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.AsyncWriteResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.AsyncWriteRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.AsyncWriteResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.





*class* BrowseNextResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.BrowseNextResult

    A :class:`~pyuaf.client.results.BrowseNextResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.BrowseNextRequest`. 
    
    A :class:`~pyuaf.client.results.BrowseNextResult` is exactly the same as a 
    :class:`~pyuaf.client.results.BrowseResult`. See the latter class documentation
    for a description of the attributes and methods.
    
    
    

*class* BrowseResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.BrowseResult

    A :class:`~pyuaf.client.results.BrowseResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.BrowseRequest`. 
    
    It tells you whether or not the requested targets have been browsed, what were the resulting
    references that were found, etc.
    
    * Methods:

        .. automethod:: pyuaf.client.results.BrowseResult.__init__
    
            Create a new BrowseResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.BrowseResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.BrowseResult.targets

            The targets, as a :class:`~pyuaf.client.results.BrowseResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.BrowseResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.BrowseResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.BrowseRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.BrowseResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* BrowseResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.BrowseResultTarget

    A :class:`~pyuaf.client.results.BrowseResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.BrowseRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.BrowseRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.BrowseResultTarget.__init__
    
            Create a new BrowseRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.BrowseResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.BrowseResultTarget.status

            Status of the result target (Good if the request target was browsed, Bad if not), 
            as a :class:`~pyuaf.util.Status` instance.
    
        .. autoattribute:: pyuaf.client.results.BrowseResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.
    
        .. autoattribute:: pyuaf.client.results.BrowseResultTarget.autoBrowsedNext

            An ``int``, clarifying how many times the UAF automatically invoked 
            the "BrowseNext" OPC UA service in order to get the results?
    
        .. autoattribute:: pyuaf.client.results.BrowseResultTarget.continuationPoint

            The continuation point (a server-defined byte string) that should be provided 
            to the next BrowseNext call, to get the remaining browse results. The type 
            of this attribute is a built-in Python ``bytearray``. 
            Since the UAF can automatically call BrowseNext for you (via the
            :attr:`pyuaf.client.settings.BrowseSettings.maxAutoBrowseNext` attribute),
            you normally don't have to use the continuation point and the BrowseNext service
            yourself.
    
        .. autoattribute:: pyuaf.client.results.BrowseResultTarget.references
        
            The reference descriptions that were found during the browsing,
            as a :class:`~pyuaf.util.ReferenceDescriptionVector`.



*class* BrowseResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.BrowseResultTargetVector

    An BrowseResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.BrowseResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.BrowseResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import BrowseResultTarget, BrowseResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = BrowseResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> for i in xrange(len(targets)):
        ...     if(targets[i].status.isGood()):
        ...         for j in xrange(len(targets[i].references)):
        ...             print("Target %d Reference %d --> Display name = %s" 
        ...                   %(i, j, targets[i].references[j].displayName))
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(BrowseResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...




*class* CreateMonitoredDataResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.CreateMonitoredDataResult

    A :class:`~pyuaf.client.results.CreateMonitoredDataResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.CreateMonitoredDataRequest`. 
    
    It tells you whether or not the requested monitored items have been created, and some details
    about them.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.CreateMonitoredDataResult.__init__
    
            Create a new CreateMonitoredDataResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.CreateMonitoredDataResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResult.targets

            The targets, as a :class:`~pyuaf.client.results.CreateMonitoredDataResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.CreateMonitoredDataRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.CreateMonitoredDataResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* CreateMonitoredDataResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.CreateMonitoredDataResultTarget

    A :class:`~pyuaf.client.results.CreateMonitoredDataResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.CreateMonitoredDataRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.CreateMonitoredDataResultTarget.__init__
    
            Create a new CreateMonitoredDataRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.CreateMonitoredDataResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.status

            Status of the result (Good if the monitored item was created, Bad if not), 
            as a :class:`~pyuaf.util.Status` instance.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.clientSubscriptionHandle

            The handle of the subscription that owns this monitored item, as an ``int``
            
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.clientHandle

            The client handle that was assigned to the monitored item by the UAF, at the time when
            the monitored item was requested.
            E.g. you can get client handles like this:
        
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util.errors import UafError
                >>> from pyuaf.util import Address, NodeId
                >>> from pyuaf.client import Client
                >>> 
                >>> myClient     = Client("myClient", ["opc.tcp://localhost:4841"])
                >>>
                >>> nameSpaceUri = "http://mycompany.com/mymachine"
                >>> serverUri    = "http://mycompany.com/servers/plc1"
                >>> address0 = Address( NodeId("myMachine.myVariable0", nameSpaceUri), serverUri)
                >>> address1 = Address( NodeId("myMachine.myVariable1", nameSpaceUri), serverUri)
                >>>
                >>> def myCallback0(notification):
                ...      print("Variable 0 was received: %s" %notification)
                >>>
                >>> def myCallback1(notification):
                ...      print("Variable 1 was received: %s" %notification)
                >>>
                >>> try:
                ...     result = myClient.createMonitoredData([address0, address1], 
                ...                                           notificationCallbacks = [myCallback0, myCallback1])
                ...     clientHandle0 = result.targets[0].clientHandle 
                ...     clientHandle1 = result.targets[1].clientHandle 
                ... except UafError, e:
                ...     # The monitored items could not be created, because there was some failure
                ...     #  (maybe the server is off-line?).
                ...     # Nevertheless, the client handles were already assigned, and we can get them like this: 
                ...     diagnostics = e.status.additionalDiagnostics()
                ...     if diagnostics.hasClientHandles():
                ...         clientHandle0, clientHandle1 = diagnostics.getClientHandles()
        
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.monitoredItemId
    
            An id (an ``int``) that was assigned to the monitored item by the server (!).
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.revisedSamplingIntervalSec

            The rate, in seconds (as a ``float``), at which the monitored item are sampled 
            in reality by the server.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredDataResultTarget.revisedQueueSize

            The true size of the queue at the server side, as an ``int``.


*class* CreateMonitoredDataResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.CreateMonitoredDataResultTargetVector

    An CreateMonitoredDataResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.CreateMonitoredDataResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.CreateMonitoredDataResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import CreateMonitoredDataResultTarget, CreateMonitoredDataResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = CreateMonitoredDataResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood       = targets[0].status.isGood()
        >>> target0_clientHandle = targets[0].clientHandle
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(CreateMonitoredDataResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...



*class* CreateMonitoredEventsResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.CreateMonitoredEventsResult

    A :class:`~pyuaf.client.results.CreateMonitoredEventsResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest`. 
    
    It tells you whether or not the requested monitored items have been created, and some details
    about them.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.CreateMonitoredEventsResult.__init__
    
            Create a new CreateMonitoredEventsResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.CreateMonitoredEventsResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResult.targets

            The targets, as a :class:`~pyuaf.client.results.CreateMonitoredEventsResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.CreateMonitoredEventsResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* CreateMonitoredEventsResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.CreateMonitoredEventsResultTarget

    A :class:`~pyuaf.client.results.CreateMonitoredEventsResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.CreateMonitoredEventsResultTarget.__init__
    
            Create a new CreateMonitoredEventsRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.CreateMonitoredEventsResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.status

            Status of the result (Good if the monitored item was created, Bad if not), 
            as a :class:`~pyuaf.util.Status` instance.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.clientHandle

            The client handle that was assigned to the monitored item by the UAF, at the time when
            the monitored item was requested.
            
            See a similar use case example at :meth:`pyuaf.client.results.CreateMonitoredDataResultTarget.clientHandle`.
            
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.clientSubscriptionHandle

            The handle of the subscription that owns this monitored item, as an ``int``
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.monitoredItemId
    
            An id (an ``int``) that was assigned to the monitored item by the server (!).
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.revisedSamplingIntervalSec

            The rate, in seconds (as a ``float``), at which the monitored item are sampled 
            in reality by the server.
    
        .. autoattribute:: pyuaf.client.results.CreateMonitoredEventsResultTarget.revisedQueueSize

            The true size of the queue at the server side, as an ``int``.


*class* CreateMonitoredEventsResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.CreateMonitoredEventsResultTargetVector

    An CreateMonitoredEventsResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.CreateMonitoredEventsResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.CreateMonitoredEventsResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import CreateMonitoredEventsResultTarget, CreateMonitoredEventsResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = CreateMonitoredEventsResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood       = targets[0].status.isGood()
        >>> target0_clientHandle = targets[0].clientHandle
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(CreateMonitoredEventsResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...






*class* HistoryReadRawModifiedResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.HistoryReadRawModifiedResult

    A :class:`~pyuaf.client.results.HistoryReadRawModifiedResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest`. 
    
    It tells you whether or not the requested targets have returned some historical data, 
    it provides you the retrieved historical data, any continuation points left, etc.
    
    * Methods:

        .. automethod:: pyuaf.client.results.HistoryReadRawModifiedResult.__init__
    
            Create a new HistoryReadRawModifiedResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.HistoryReadRawModifiedResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResult.targets

            The targets, as a :class:`~pyuaf.client.results.HistoryReadRawModifiedResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.HistoryReadRawModifiedResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* HistoryReadRawModifiedResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.HistoryReadRawModifiedResultTarget

    A :class:`~pyuaf.client.results.HistoryReadRawModifiedResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.__init__
    
            Create a new HistoryReadRawModifiedRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.status

            Status of the result target (Good if the requested data was retrieved, Bad if not), 
            as a :class:`~pyuaf.util.Status` instance.
            Apart from the UAF status code (which are defined in the 
            :mod:`pyuaf.util.statuscodes` module), you may also check the OPC UA statuscode 
            (which are defined in the :mod:`pyuaf.util.opcuastatuscodes` module) since
            this provides more information (e.g. OpcUa_GoodNoData and OpcUa_GoodMoreData).
            
            .. doctest::
                
                >>> import pyuaf
                >>> from pyuaf.client.results        import HistoryReadRawModifiedResult
                >>> from pyuaf.util.opcuastatuscodes import OpcUa_GoodNoData
                
                >>> # create some simulated result, that we may have received from the client:
                >>> someReceivedResult = HistoryReadRawModifiedResult()
                >>> someReceivedResult.targets.resize(1)
                
                >>> # if the result didn't return any data values, you may want to check if there is
                >>> # simply no historical data that matches your request:
                >>> if len(someReceivedResult.targets[0].dataValues) == 0:
                ...    noDataFound = (someReceivedResult.targets[0].status.opcUaStatusCode() == OpcUa_GoodNoData)
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.autoReadMore

            An ``int``, clarifying how many times did the UAF automatically invoke the historical read OPC UA service
            in addition to the original request, in order to get the remaining results?
            In case the UAF did not read more data automatically, this value will be 0.
            See :attr:`pyuaf.client.settings.HistoryReadRawModifiedSettings.maxAutoReadMore` for more info.
    
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.continuationPoint
 
            The continuation point, in case there are still results left at the server.The type 
            of this attribute is a built-in Python ``bytearray``.
            If the continuation point is not NULL (i.e. if it contains more than 0 bytes),
            then you should copy the continuation point to the continuation point of the next
            HistoryReadRawModifiedRequest, and perform another call.
        
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.dataValues
        
            The requested historical data, as a :class:`~pyuaf.util.DataValueVector`.
        
        .. autoattribute:: pyuaf.client.results.HistoryReadRawModifiedResultTarget.modificationInfos
        
            The requested modification information, in case the 
            :attr:`pyuaf.client.settings.HistoryReadRawModifiedSettings.isReadModified` flag 
            was set in the settings of the original request.



*class* HistoryReadRawModifiedResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.HistoryReadRawModifiedResultTargetVector

    An HistoryReadRawModifiedResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.HistoryReadRawModifiedResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.HistoryReadRawModifiedResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import HistoryReadRawModifiedResultTarget, HistoryReadRawModifiedResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = HistoryReadRawModifiedResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood        = targets[0].status.isGood()
        >>> target0_retrievedData = targets[0].dataValues
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(HistoryReadRawModifiedResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...




*class* MethodCallResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.MethodCallResult

    A :class:`~pyuaf.client.results.MethodCallResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.MethodCallRequest`. 
    
    It tells you whether or not the requested targets have been called, what were the resulting 
    output arguments, etc.
    
    * Methods:

        .. automethod:: pyuaf.client.results.MethodCallResult.__init__
    
            Create a new MethodCallResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.MethodCallResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.MethodCallResult.targets

            The targets, as a :class:`~pyuaf.client.results.MethodCallResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.MethodCallResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.MethodCallResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.MethodCallRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.MethodCallResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* MethodCallResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.MethodCallResultTarget

    A :class:`~pyuaf.client.results.MethodCallResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.MethodCallRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.MethodCallRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.MethodCallResultTarget.__init__
    
            Create a new MethodCallRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.MethodCallResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.MethodCallResultTarget.status

            Status of the result target (Good if the request target was called successfully, 
            Bad if not), as a :class:`~pyuaf.util.Status` instance.
    
        .. autoattribute:: pyuaf.client.results.MethodCallResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.
    
        .. autoattribute:: pyuaf.client.results.MethodCallResultTarget.outputArguments

            The output arguments of the remote method call, as a :class:`pyuaf.util.VariantVector`. 
    
        .. autoattribute:: pyuaf.client.results.MethodCallResultTarget.inputArgumentStatuses

            The status for each input argument, as a :class:`pyuaf.util.StatusVector`. 



*class* MethodCallResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.MethodCallResultTargetVector

    An MethodCallResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.MethodCallResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.MethodCallResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import MethodCallResultTarget, MethodCallResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = MethodCallResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood     = targets[0].status.isGood()
        >>> target0_outputArgs = targets[0].outputArguments
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(MethodCallResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...






*class* ReadResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.ReadResult

    A :class:`~pyuaf.client.results.ReadResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.ReadRequest`. 
    
    It tells you whether or not the requested targets have been read, what was the resulting data, 
    etc.
    
    * Methods:

        .. automethod:: pyuaf.client.results.ReadResult.__init__
    
            Create a new ReadResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.ReadResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.ReadResult.targets

            The targets, as a :class:`~pyuaf.client.results.ReadResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.ReadResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.ReadResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.ReadRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.ReadResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* ReadResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.ReadResultTarget

    A :class:`~pyuaf.client.results.ReadResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.ReadRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.ReadRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.ReadResultTarget.__init__
    
            Create a new ReadRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.ReadResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.


    * Attributes inherited from :class:`pyuaf.util.DataValue`
    
    
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.status
        
            The status of the data, as a :class:`~pyuaf.util.Status` instance.
            The status contains the OPC UA status code of the data. 
    
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.data

            The data that was read, as one of the data types described in :ref:`note-variants`.
  
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.sourceTimestamp
        
            The source time stamp of the data, as a :class:`~pyuaf.util.DateTime` instance.
  
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.serverTimestamp
        
            The server time stamp of the data, as a :class:`~pyuaf.util.DateTime` instance.
  
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.sourcePicoseconds
    
            The number of 10 picosecond intervals that need to be added to the source timestamp
            (to get a higher time resolution), as an ``int``.
  
        .. autoattribute:: pyuaf.client.results.ReadResultTarget.serverPicoseconds
    
            The number of 10 picosecond intervals that need to be added to the server timestamp
            (to get a higher time resolution), as an ``int``.
    



*class* ReadResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.ReadResultTargetVector

    An ReadResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.ReadResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.ReadResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import ReadResultTarget, ReadResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = ReadResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood  = targets[0].status.isGood()
        >>> target0_data    = targets[0].data
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(ReadResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...






*class* TranslateBrowsePathsToNodeIdsResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult

    A :class:`~pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest`. 
    
    It tells you whether or not the requested targets have been translated, what were the resulting
    ExpandedNodeIds, etc.
    
    * Methods:

        .. automethod:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult.__init__
    
            Create a new TranslateBrowsePathsToNodeIdsResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult.targets

            The targets, as a :class:`~pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* TranslateBrowsePathsToNodeIdsResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget

    A :class:`~pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget.__init__
    
            Create a new TranslateBrowsePathsToNodeIdsRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget.status

            Status of the result target (Good if the request target was translated, Bad if not), 
            as a :class:`~pyuaf.util.Status` instance.
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget.expandedNodeIds

            The ExpandedNodeIds that were the result of the browse path, as an 
            :class:`~pyuaf.util.ExpandedNodeIdVector`.
    
        .. autoattribute:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget.remainingPathIndexes

            Any remaining path indexes, as an :class:`~pyuaf.util.UInt32Vector`.



*class* TranslateBrowsePathsToNodeIdsResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTargetVector

    An TranslateBrowsePathsToNodeIdsResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.TranslateBrowsePathsToNodeIdsResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import TranslateBrowsePathsToNodeIdsResultTarget, TranslateBrowsePathsToNodeIdsResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = TranslateBrowsePathsToNodeIdsResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood          = targets[0].status.isGood()
        >>> target0_expandedNodeIds = targets[0].expandedNodeIds
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(TranslateBrowsePathsToNodeIdsResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...









*class* WriteResult
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.WriteResult

    A :class:`~pyuaf.client.results.WriteResult` is the result of a corresponding 
    :class:`~pyuaf.client.requests.WriteRequest`. 
    
    It tells you whether or not the requested targets have been written successfully.
    
    * Methods:

        .. automethod:: pyuaf.client.results.WriteResult.__init__
    
            Create a new WriteResult object.
            
            You should never have to create result objects yourself, the UAF will produce them
            and you will consume them.
            
        .. automethod:: pyuaf.client.results.WriteResult.__str__
    
            Get a formatted string representation of the result.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.WriteResult.targets

            The targets, as a :class:`~pyuaf.client.results.WriteResultTargetVector`.
    
        .. autoattribute:: pyuaf.client.results.WriteResult.overallStatus

            The combined status of the targets, as a :class:`~pyuaf.util.Status` instance.
            
            If this status is Good, then you know for sure that all the statuses of the targets
            are all Good.
            If this status is Bad, then you know that at least one of the targets has a Bad status.
    
        .. autoattribute:: pyuaf.client.results.WriteResult.requestHandle

            The unique handle that was originally assigned to the 
            :class:`~pyuaf.client.requests.WriteRequest` 
            that resulted in this 
            :class:`~pyuaf.client.results.WriteResult`. 
            It's a 64-bit ``long`` value, assigned by the UAF during the processing of the request.


*class* WriteResultTarget
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.results.WriteResultTarget

    A :class:`~pyuaf.client.results.WriteResultTarget` corresponds exactly to the
    :class:`~pyuaf.client.requests.WriteRequestTarget` that was part of the invoked
    :class:`~pyuaf.client.requests.WriteRequest`. 
    So the first target of the request corresponds to the first target of the result, and so on.
    
    
    * Methods:

        .. automethod:: pyuaf.client.results.WriteResultTarget.__init__
    
            Create a new WriteRequestTarget object.
            
            You should never have to create result targets (or results for that matter) yourself, 
            the UAF will produce them and you will consume them.
            
        .. automethod:: pyuaf.client.results.WriteResultTarget.__str__
    
            Get a formatted string representation of the target.


    * Attributes
    
        .. autoattribute:: pyuaf.client.results.WriteResultTarget.status

            Status of the result target (Good if the request target was written, Bad if not), 
            as a :class:`~pyuaf.util.Status` instance.
    
        .. autoattribute:: pyuaf.client.results.WriteResultTarget.clientConnectionId

            The id of the session that was used for this target, as an ``int``.
    



*class* WriteResultTargetVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.results.WriteResultTargetVector

    An WriteResultTargetVector is a container that holds elements of type 
    :class:`pyuaf.client.results.WriteResultTarget`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.client.results.WriteResultTarget`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.client.results import WriteResultTarget, WriteResultTargetVector
        
        >>> # construct a realistic result, for instance one with 5 targets:
        >>> targets = WriteResultTargetVector(5)
        
        >>> noOfElements = len(targets) # will be 5  (alternative: targets.size())
        
        >>> target0_isGood  = targets[0].status.isGood()
        
        >>> # other methods of the vector:
        >>> targets.resize(6)
        >>> targets.append(WriteResultTarget())
        >>> someTarget = targets.pop()
        >>> targets.clear()
        >>> # ...

