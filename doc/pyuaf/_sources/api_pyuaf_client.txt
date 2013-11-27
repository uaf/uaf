
``pyuaf.client``
====================================================================================================


.. automodule:: pyuaf.client


*class* Client
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.Client
    :members:



*class* BaseNotification
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.BaseNotification

    A BaseNotification is the common superclass class of :class:`~pyuaf.client.DataChangeNotification` 
    and :class:`~pyuaf.client.EventNotification`. It contains the common attributes of notifications 
    that are received when a subscription is made.


    * Methods:

        .. automethod:: pyuaf.client.BaseNotification.__init__
    
            Construct a new BaseNotification. 
            
            You'll never need to create notifications like this yourself because:
              - only the subclasses :class:`pyuaf.client.DataChangeNotification` and 
                :class:`pyuaf.client.EventNotification` will be instantiated, never the superclass itself
              - the UAF will produce notifications and provide them to you, so you can consume them.
        
        
        .. automethod:: pyuaf.client.BaseNotification.__str__
        
            Get a string representation.
    
    
    * Attributes:
  
  
        .. autoattribute:: pyuaf.client.BaseNotification.notificationHandle
            
            Deprecated! A notification handle is essentially the same as a client monitored item 
            handle, so soon these two handles will merge (notificationHandle will disappear, 
            the client monitored item handle will stay).
            
            A NotificationHandle is a handle (an ``int``) defined by the UAF (not by the OPC UA standard!) to
            associate monitored item notifications with the 
            :class:`~pyuaf.client.requests.CreateMonitoredDataRequestTarget` (or
            :class:`~pyuaf.client.requests.CreateMonitoredEventsRequestTarget`) that originally 
            created them. It is a 32-bit number
            that gets a unique value as soon as you create a monitored item. Even if the server of
            this monitored item would crash, and the UAF determines that the monitored item should be
            re-established on another server (e.g. because the browse path now points to a node in
            another redundant server), then this value will not change. So if you create monitored
            items once, you can be sure that the notification handle will always correctly identify
            the same item, for the whole lifetime of the client.
        
        .. autoattribute:: pyuaf.client.BaseNotification.clientHandle
        
            A clientHandle is a 32-bit number assigned by the UAF to newly created
            monitored items. The number will be incremented on each new item creation, so in
            theory it will take 2**32 items that have to be created before the number starts
            to count from 0 again. In practice, it will never happen.
         


*class* DataChangeNotification
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.DataChangeNotification


    A DataChangeNotification is a notification for a monitored data item.

    
    * Methods:
    
        .. automethod:: pyuaf.client.DataChangeNotification.__init__
    
            Construct a new DataChangeNotification. 
            
            You'll never need to create notifications like this yourself, because the UAF will 
            produce them and provide them to you, so you can consume them.
        

    * Attributes inherited from :class:`~pyuaf.client.BaseNotification`:
    
    
        .. autoattribute:: pyuaf.client.DataChangeNotification.notificationHandle

            --> See :attr:`pyuaf.client.BaseNotification.notificationHandle`.
        
    
        .. autoattribute:: pyuaf.client.DataChangeNotification.clientHandle

            --> See :attr:`pyuaf.client.BaseNotification.clientHandle`.


    * Other attributes:

        .. autoattribute:: pyuaf.client.DataChangeNotification.status

            The status of the data (a :class:`pyuaf.util.Status`).


        .. autoattribute:: pyuaf.client.DataChangeNotification.data

            The changed data.
 
            The type of this data depends on the type of the variable you are monitoring.
            This means that it has a dynamic data type.
            
            .. seealso:: :ref:`note-variants`.




*class* EventNotification
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.EventNotification


    An EventNotification is a notification for a monitored event item.

    
    * Methods:
    
        .. automethod:: pyuaf.client.EventNotification.__init__
    
            Construct a new EventNotification. 
            
            You'll never need to create notifications like this yourself, because the UAF will 
            produce them and provide them to you, so you can consume them.
        

    * Attributes inherited from :class:`~pyuaf.client.BaseNotification`:
    
    
        .. autoattribute:: pyuaf.client.EventNotification.notificationHandle

            --> See :attr:`pyuaf.client.BaseNotification.notificationHandle`.
        
    
        .. autoattribute:: pyuaf.client.EventNotification.clientHandle

            --> See :attr:`pyuaf.client.BaseNotification.clientHandle`.


    * Other attributes:

        .. autoattribute:: pyuaf.client.EventNotification.fields

            The values of the fields you are monitoring (in the same order as the select clauses which
            you specified in the :class:`pyuaf.client.requests.CreateMonitoredEventsRequestTarget`).

            Since the type of the fields depend on the type of the select clauses of your
            :class:`pyuaf.client.requests.CreateMonitoredEventsRequestTarget`, the fields are 
            presented to you as a :class:`pyuaf.util.VariantVector`.



*class* SessionInformation
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.SessionInformation

    A SessionInformation object contains information about a session such as the state of the
    session, the server URI of the server to which it is connected, etc.

    * Methods:

        .. automethod:: pyuaf.client.SessionInformation.__init__
    
            Construct a new SessionInformation object. 
        
        
        .. automethod:: pyuaf.client.SessionInformation.__str__
        
            Get a string representation.
    
    
    * Attributes:
        
        .. autoattribute:: pyuaf.client.SessionInformation.clientConnectionId
            
            The id of the session, as a ``long``. 
  
        .. autoattribute:: pyuaf.client.SessionInformation.sessionState
        
            An ``int`` representing the state of the session 
            (e.g. :attr:`~pyuaf.client.sessionstates.Connected`).
            
            The possible states are defined in the :mod:`pyuaf.client.sessionstates` module.
         
        .. autoattribute:: pyuaf.client.SessionInformation.serverUri
            
            The URI of the server to which the session should be connected, as a ``str``.
      

*class* SubscriptionInformation
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.SubscriptionInformation

    A SubscriptionInformation object contains information about a subscription such as the 
    state of the subscription, the handle, etc.

    * Methods:

        .. automethod:: pyuaf.client.SubscriptionInformation.__init__
    
            Construct a new SubscriptionInformation object. 
        
        
        .. automethod:: pyuaf.client.SubscriptionInformation.__str__
        
            Get a string representation.
    
    
    * Attributes:
        
        .. autoattribute:: pyuaf.client.SubscriptionInformation.clientConnectionId
            
            The id of the session that hosts the subscription, as a ``long``. 
        
        .. autoattribute:: pyuaf.client.SubscriptionInformation.clientSubscriptionHandle
            
            The handle of the subscription, as a ``long``.    
  
        .. autoattribute:: pyuaf.client.SubscriptionInformation.subscriptionState
        
            An ``int`` representing the state of the subscription 
            (e.g. :attr:`~pyuaf.client.subscriptionstates.Created`).
            
            The possible states are defined in the :mod:`pyuaf.client.subscriptionstates` module.
            
            