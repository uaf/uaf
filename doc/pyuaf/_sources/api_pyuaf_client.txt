
``pyuaf.client``
====================================================================================================


.. automodule:: pyuaf.client

**SUMMARY of submodules:**

.. autosummary:: 
    
        connectionsteps
        monitoreditemstates
        requests
        results
        sessionstates
        settings
        subscriptionstates
        
**SUMMARY of classes:**
        
        See sidebar.


*class* Client
----------------------------------------------------------------------------------------------------

**SUMMARY**:
    
    *Constructor:*
        .. autosummary:: 
                Client
    
    *Client settings:*
        .. autosummary:: 
                Client.clientSettings
                Client.setClientSettings
    
    *Synchronous service calls:*
        .. autosummary:: 
                Client.browse
                Client.browseNext
                Client.call
                Client.createMonitoredData
                Client.createMonitoredEvents
                Client.historyReadModified
                Client.historyReadRaw
                Client.read
                Client.setMonitoringMode
                Client.setPublishingMode
                Client.write
    
    *Asynchronous service calls:*
        .. autosummary:: 
                Client.beginCall
                Client.beginRead
                Client.beginWrite
    
    *Callback functions for asynchronous service calls:*
        .. autosummary:: 
                Client.callComplete
                Client.readComplete
                Client.writeComplete
    
    *Callback functions for sessions, subscriptions and monitored items:*
        .. autosummary:: 
                Client.dataChangesReceived
                Client.eventsReceived
                Client.connectionStatusChanged
                Client.subscriptionStatusChanged
                Client.keepAliveReceived
                Client.notificationsMissing
    
    *Register your own callback functions for sessions, subscriptions and monitored items:*
        .. autosummary:: 
                Client.registerConnectionStatusCallback
                Client.registerSubscriptionStatusCallback
                Client.registerKeepAliveCallback
                Client.registerNotificationsMissingCallback
    
    *Information about the current sessions, subscriptions and monitored items:*
        .. autosummary:: 
                Client.allSessionInformations
                Client.allSubscriptionInformations
                Client.monitoredItemInformation
                Client.sessionInformation
                Client.subscriptionInformation
                
    *Fully configurable generic service calls:*
        .. autosummary:: 
                Client.processRequest
    
    *Manually created sessions and subscriptions:*
        .. autosummary:: 
                Client.manuallyConnect
                Client.manuallyConnectToEndpoint
                Client.manuallyDisconnect
                Client.manuallySubscribe
                Client.manuallyUnsubscribe
    
    *Handle untrusted server certificates:*
        .. autosummary:: 
                Client.untrustedServerCertificateReceived
                Client.registerUntrustedServerCertificateCallback
                Client.unregisterUntrustedServerCertificateCallback
    
    *Catch the logging of the UAF:*
        .. autosummary:: 
                Client.logMessageReceived
                Client.registerLoggingCallback
                Client.unregisterLoggingCallback
    
    *Discovery:*
        .. autosummary:: 
                Client.serversFound
                Client.findServersNow


**DETAILED DESCRIPTION:**:
    
.. autoclass:: pyuaf.client.Client
    :members:
    

*class* MonitoredItemInformation
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.MonitoredItemInformation

    A MonitoredItemInformation object contains information about a monitored item.


    * Methods:

        .. automethod:: pyuaf.client.MonitoredItemInformation.__init__
    
            Construct a new MonitoredItemInformation object. 
        
        
        .. automethod:: pyuaf.client.MonitoredItemInformation.__str__
        
            Get a string representation.
    
    
    * Attributes:
  
        .. autoattribute:: pyuaf.client.MonitoredItemInformation.monitoredItemState
        
            An ``int`` representing the state of the monitored item 
            (e.g. :attr:`~pyuaf.client.monitoreditemstates.Created`).
            
            The possible states are defined in the :mod:`pyuaf.client.monitoreditemstates` module.
        
        .. autoattribute:: pyuaf.client.MonitoredItemInformation.clientConnectionId
            
            The id of the session that hosts the subscription (which in turn hosts the monitored 
            item), as a ``long``. 
        
        .. autoattribute:: pyuaf.client.MonitoredItemInformation.clientSubscriptionHandle
            
            The handle of the subscription that hosts the monitored item, as a ``long``.
        
        .. autoattribute:: pyuaf.client.MonitoredItemInformation.clientHandle
            
            The handle of the monitored item, as a ``long``.
  
        .. autoattribute:: pyuaf.client.MonitoredItemInformation.settings
        
            The settings of this particular monitored item, as an instance of type 
            :class:`~pyuaf.client.settings.MonitoredItemSettings`.



*class* MonitoredItemNotification
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.MonitoredItemNotification

    A MonitoredItemNotification is the common superclass class of 
    :class:`~pyuaf.client.DataChangeNotification` and :class:`~pyuaf.client.EventNotification`.


    * Methods:

        .. automethod:: pyuaf.client.MonitoredItemNotification.__init__
    
            Construct a new MonitoredItemNotification. 
            
            You'll never need to create notifications like this yourself because:
              - only the subclasses :class:`pyuaf.client.DataChangeNotification` and 
                :class:`pyuaf.client.EventNotification` will be instantiated, never the 
                superclass itself
              - the UAF will produce notifications and provide them to you, so you can consume them.
        
        
        .. automethod:: pyuaf.client.MonitoredItemNotification.__str__
        
            Get a string representation.
    
    
    * Attributes:
        
        .. autoattribute:: pyuaf.client.MonitoredItemNotification.clientHandle
        
            A clientHandle is a 32-bit number assigned by the UAF to newly created
            monitored items. Essentially, it allows you to identify the monitored item of which
            you receive this notification.
            
            You can store the client handle when you created the monitored item, see for 
            example the use case example at :meth:`pyuaf.client.results.CreateMonitoredDataResultTarget.clientHandle`.
            
            If you use "notification callbacks", you don't need to worry about client handles
            (because the notifications will be automatically mapped to your callback functions
            that implement behavior for a specific monitored item. 



*class* DataChangeNotification
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.DataChangeNotification


    A DataChangeNotification is a notification for a monitored data item.

    
    * Methods:
    
        .. automethod:: pyuaf.client.DataChangeNotification.__init__
    
            Construct a new DataChangeNotification. 
            
            You'll never need to create notifications like this yourself, because the UAF will 
            produce them and provide them to you, so you can consume them.
        

    * Attributes inherited from :class:`~pyuaf.client.MonitoredItemNotification`:
        
    
        .. autoattribute:: pyuaf.client.DataChangeNotification.clientHandle

            --> See :attr:`pyuaf.client.MonitoredItemNotification.clientHandle`.


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
        

    * Attributes inherited from :class:`~pyuaf.client.MonitoredItemNotification`:
        
    
        .. autoattribute:: pyuaf.client.EventNotification.clientHandle

            --> See :attr:`pyuaf.client.MonitoredItemNotification.clientHandle`.


    * Other attributes:

        .. autoattribute:: pyuaf.client.EventNotification.fields

            The values of the fields you are monitoring (in the same order as the select clauses which
            you specified in the :class:`pyuaf.client.requests.CreateMonitoredEventsRequestTarget`).

            Since the type of the fields depend on the type of the select clauses of your
            :class:`pyuaf.client.requests.CreateMonitoredEventsRequestTarget`, the fields are 
            presented to you as a :class:`pyuaf.util.VariantVector`.



*class* KeepAliveNotification
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.KeepAliveNotification


    A KeepAliveNotification is sent by the server to notify the client that the subscription is
    still alive. 
    
    It is sent when the data that is monitored by the client has not changed for a 
    while. E.g. suppose a client wants to monitor some data, and it specifies a 
    :attr:`~pyuaf.client.settings.SubscriptionSettings.publishingIntervalSec` of 1.0 seconds 
    and a :attr:`~pyuaf.client.settings.SubscriptionSettings.maxKeepAliveCount` of 5. 
    As a result, when the monitored data changes rapidly, the client will be notified once per 
    second. But every time the monitored data remains constant for 1.0 * 5 = 5.0 seconds,
    a KeepAliveNotification will be sent instead to notify the client that everything is still OK.
    

    
    * Methods:
    
        .. automethod:: pyuaf.client.KeepAliveNotification.__init__
    
            Construct a new KeepAliveNotification. 
            
            You'll never need to create notifications like this yourself, because the UAF will 
            produce them and provide them to you, so you can consume them.
        

    * Attributes inherited from :class:`~pyuaf.client.SubscriptionInformation`:
    
    
        .. autoattribute:: pyuaf.client.KeepAliveNotification.clientConnectionId

            --> See :attr:`pyuaf.client.SubscriptionInformation.clientConnectionId`.
        
    
        .. autoattribute:: pyuaf.client.KeepAliveNotification.clientSubscriptionHandle

            --> See :attr:`pyuaf.client.SubscriptionInformation.clientSubscriptionHandle`.
        
    
        .. autoattribute:: pyuaf.client.KeepAliveNotification.subscriptionState

            --> See :attr:`pyuaf.client.SubscriptionInformation.subscriptionState`.


    * Other attributes:

        .. autoattribute:: pyuaf.client.KeepAliveNotification.clientHandles

            The client handles assigned to the subscription that got a keep alive message,
            as a :class:`~pyuaf.util.UInt32Vector`.
            
            So if you receive a KeepAliveNotification, you know that the monitored items identified
            by these handles are OK. 



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
  
        .. autoattribute:: pyuaf.client.SessionInformation.serverState
        
            An ``int`` representing the state of the server 
            (e.g. :attr:`~pyuaf.util.serverstates.Running`).
            
            The possible states are defined in the :mod:`pyuaf.util.serverstates` module.
         
        .. autoattribute:: pyuaf.client.SessionInformation.serverUri
            
            The URI of the server to which the session should be connected, as a ``str``.
         
        .. autoattribute:: pyuaf.client.SessionInformation.lastConnectionAttemptStep
            
            The step of the connection process (corresponding to the 
            :attr:`~pyuaf.client.SessionInformation.lastConnectionAttemptStatus`), as an ``int``.
            
            The possible steps are defined in the :mod:`pyuaf.client.connectionsteps` module.
            
        .. autoattribute:: pyuaf.client.SessionInformation.lastConnectionAttemptStatus
            
            The status of the last connection attempt, as a :class:`~pyuaf.util.Status` instance.
        
        .. autoattribute:: pyuaf.client.SessionInformation.sessionSettings
            
            The session settings of the session (type: :class:`~pyuaf.client.settings.SessionSettings`).


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
        
        .. autoattribute:: pyuaf.client.SubscriptionInformation.subscriptionSettings
            
            The subscription settings of the subscription (type: :class:`~pyuaf.client.settings.SubscriptionSettings`).
            
            