``pyuaf.client.settings``
====================================================================================================

.. automodule:: pyuaf.client.settings


*class* ServiceSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.ServiceSettings

    A ServiceSettings object is the superclass of :class:`~pyuaf.client.settings.ReadSettings`,
    :class:`~pyuaf.client.settings.WriteSettings`, etc.

    
    * Methods:

        .. method:: __init__()
    
            Create a new ServiceSettings object.
            
            The default callTimeoutSec is 1 second.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.
    

*class* BrowseNextSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.BrowseNextSettings

    A BrowseNextSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA BrowseNext service invocation.

    
    * Methods:

        .. automethod:: pyuaf.client.settings.BrowseNextSettings.__init__()
    
            Create a new BrowseNextSettings object.
            
    
        .. method:: pyuaf.client.settings.BrowseNextSettings.__str__
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.
    
    * Additional attributes:
        
        .. autoattribute:: pyuaf.client.settings.BrowseNextSettings.releaseContinuationPoints
        
            A ``bool`` indicating if the memory associated with the continuation point in the 
            server should be released (``True``) or not (``False``).
        





*class* BrowseSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.BrowseSettings

    A BrowseSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA Browse service invocation.

    
    * Methods:

        .. automethod:: pyuaf.client.settings.BrowseSettings.__init__()
    
            Create a new BrowseSettings object.
            
    
        .. method:: pyuaf.client.settings.BrowseSettings.__str__
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.
    
    * Additional attributes:
        
        .. autoattribute:: pyuaf.client.settings.BrowseSettings.maxReferencesToReturn
        
            An ``int``: the maximum number of references to return. Default is 0, 
            which means that the client is not imposing a limitation.
        
        .. autoattribute:: pyuaf.client.settings.BrowseSettings.view
        
            Attribute of type :class:`~pyuaf.util.ViewDescription` that specifies 
            the View to browse. Don't touch if you want to browse the whole address 
            space without restrictions.
        
        .. autoattribute:: pyuaf.client.settings.BrowseSettings.maxAutoBrowseNext
        
            An ``int`` defined by the UAF, to indicate how many times the UAF may automatically
            call the BrowseNext service. Default = 0, which means that there will be no 
            BrowseNext being called automatically. But if you put this value to e.g. 10, then you 
            can very easily browse large address spaces since you don't have to call BrowseNext 
            manually every time (and there's no risk of ending up in an endless loop since the 
            UAF client will stop processing the request after 10 BrowseNext calls).




*class* ClientSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.ClientSettings

    A ClientSettings object stores the settings of a :class:`pyuaf.client.Client`.

    Usage example::
    
        import pyuaf

        # create a default ClientSettings instance
        settings = pyuaf.client.settings.ClientSettings()

        # set the name and URI of the client
        settings.applicationName = "MyClient"
        settings.applicationUri  = "/some/company/uri/myclient"

        # update the URLs to be used for the discovery of servers
        settings.discoveryUrls.append("opc.tcp://localhost:4841")
        settings.discoveryUrls.append("opc.tcp://10.33.178.81:4841")
        
        # alternative:
        alternativeSettings = pyuaf.client.settings.ClientSettings()
        alternativeSettings.discoveryUrls.resize(2)
        alternativeSettings.discoveryUrls[0] = "opc.tcp://localhost:4841"
        alternativeSettings.discoveryUrls[1] = "opc.tcp://10.33.178.81:4841"
      
            
    
    * Methods:

        .. method:: __init__()
    
            Construct a new ClientSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.
            
    
        .. automethod:: pyuaf.client.settings.ClientSettings.createSecurityLocations()
    
            Create the security locations (directories).
            
            These locations will be created (if they don't exist already):
            
            - certificateTrustListLocation
            - certificateRevocationListLocation
            - issuersCertificatesLocation
            - issuersRevocationListLocation
            - base path of clientPrivateKey
            - base path of clientCertificate
            
            :return: A Good status if the locations were created (or if they already existed).
                     A Bad status if some location could not be created (e.g. due to wrong 
                     permissions).
            :rtype: :class:`~pyuaf.util.Status`
            
    
    
    * Attributes
    
    
       * Main attributes:
    
        
            .. autoattribute:: pyuaf.client.settings.ClientSettings.applicationName
            
                The application name of the client (as a ``str``).
            
            .. autoattribute:: pyuaf.client.settings.ClientSettings.applicationUri
            
                The unique application URI of the client (as a ``str``).
            
            .. autoattribute:: pyuaf.client.settings.ClientSettings.productUri
            
                The unique product URI of the client (as a ``str``).
            
            .. autoattribute:: pyuaf.client.settings.ClientSettings.localeId
             
                The Locale identifier (e.g. "en", "de", "en-US", ...) (as a ``str``).
                
                
       * Attributes related to the logging
        
        
           .. autoattribute:: pyuaf.client.settings.ClientSettings.logToStdOutLevel
           
               When logging to the stdout, only log messages from at least this loglevel.
               The loglevels are of type ``int``, as defined in :mod:`pyuaf.util.loglevels`. 
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.logToCallbackLevel
           
               When logging to the callback interface, only log messages from at least this loglevel.
               The loglevels are of type ``int``, as defined in :mod:`pyuaf.util.loglevels`. 
           
           
       * Attributes related to the discovery process
       
       
           .. autoattribute:: pyuaf.client.settings.ClientSettings.discoveryUrls
       
               The list of URLs to be used by the client to discover servers 
               (as a :class:`~pyuaf.util.StringVector`, which can be treated more or less 
               as a ``list`` of ``str``).
       
           .. autoattribute:: pyuaf.client.settings.ClientSettings.discoveryFindServersTimeoutSec
           
               The timeout value for the FindServers discovery service, in seconds, as a ``float``.
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.discoveryGetEndpointsTimeoutSec
           
               The timeout value for the GetEndpoints discovery service, in seconds, as a ``float``.
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.discoveryIntervalSec
           
               The interval between discovery attempts which are continuously running in the
               background, in seconds, as a ``float``.
           
           
       * Attributes related to security
           
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.certificateTrustListLocation
           
               The trust list location as a ``str``.
               
               This directory can be specified either as an absolute path, or as a path relative to
               the application path.
          
               Default: "PKI/trusted/certs/".
           
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.certificateRevocationListLocation
           
               The revocation list location as a ``str``.
               
               This directory can be specified either as an absolute path, or as a path relative to
               the application path.
          
               Default: "PKI/trusted/crl/".
           
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.issuersCertificatesLocation
           
               The issuers certificates location as a ``str``.
               
               This directory can be specified either as an absolute path, or as a path relative to
               the application path.
          
               Default: "PKI/issuers/certs/".
           
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.issuersRevocationListLocation
           
               The issuers revocation list location as a ``str``.
               
               This directory can be specified either as an absolute path, or as a path relative to
               the application path.
          
               Default: "PKI/issuers/crl/".
           
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.createSecurityLocationsIfNeeded
           
               A ``bool`` to automatically create the security-related directories if they don't 
               exist yet, or not.
               
               The following directories will be created *if* this boolean is ``True`` and *if* 
               the UAF needs to connect to a secured endpoint and *if* these directories don't 
               exist already:
               - certificateTrustListLocation
               - certificateRevocationListLocation
               - issuersCertificatesLocation
               - issuersRevocationListLocation
               
               If this boolean is ``False`` and the UAF needs to connect to a secured endpoint,
               the UAF will simply check if the above directories exist. If they don't exist,
               the connection will fail and you'll get an exception.
          
               Default: True
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.clientPrivateKey
           
               The private key of this client application as a ``str``.
               
               This file can be specified either as an absolute path, or as a path relative to
               the application path.
          
               Default: "PKI/client/private/client.pem".
           
           
           .. autoattribute:: pyuaf.client.settings.ClientSettings.clientCertificate
           
               The certificate of this client application as a ``str``.
               
               This file can be specified either as an absolute path, or as a path relative to
               the application path.
          
               Default: "PKI/client/certs/client.der".
           



*class* CreateMonitoredDataSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.CreateMonitoredDataSettings

    A CreateMonitoredDataSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA CreateMonitoredItems service invocation for data changes.

    
    * Methods:

        .. method:: __init__()
    
            Create a new CreateMonitoredDataSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.



*class* CreateMonitoredEventsSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.CreateMonitoredEventsSettings

    A CreateMonitoredEventsSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA CreateMonitoredItems service invocation for events.

    
    * Methods:

        .. method:: __init__()
    
            Create a new CreateMonitoredEventsSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.







*class* HistoryReadRawModifiedSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.HistoryReadRawModifiedSettings

    A HistoryReadRawModifiedSettings is a subclass of 
    :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA HistoryReadRawModified service invocation.

    
    * Methods:

        .. automethod:: pyuaf.client.settings.HistoryReadRawModifiedSettings.__init__
    
            Create a new HistoryReadRawModifiedSettings object.
            
        .. automethod:: pyuaf.client.settings.HistoryReadRawModifiedSettings.__str__
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.
    
    * Additional attributes:
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.startTime
        
            Begin of the time interval to read, as a :class:`pyuaf.util.DateTime` instance.
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.endTime
        
            End of the time interval to read, as a :class:`pyuaf.util.DateTime` instance.
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.isReadModified
        
            ``bool`` flag: False if the values stored in the history database should be returned
            directly, True if the values that are replaced by other values (with the same
            timestamps) should be returned. Default is False.
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.maxAutoReadMore
        
            An ``int`` defined by the UAF, to indicate how many times the UAF may automatically
            call the history read OPC UA service **additionally** to the original request,
            in order to get more data.
            Default = 0, which means that there will be no extra service calls being invoked
            automatically. But if you put this value to e.g. 10, then you can very easily retrieve
            large amounts of historical data since you don't have to call the service manually
            every time you get a non-NULL continuation point. You don't need to use this
            attribute if you don't want it (you can leave it at 0 to effectively disable it),
            but it can make your life easier!
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.numValuesPerNode
        
            An ``int`` specifying the maximum number of values that may be returned for each node.
            Default = 0 = no limit.
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.returnBounds
        
            ``bool`` flag: True if the bounds (a value at or just before the start time and a value
            at or just after the end time) should be returned, False if not.
            Default is False.
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.timestampsToReturn
        
            Select and return the timestamps as specified by this ``int`` attribute (as defined
            in the :mod:`pyuaf.util.timestampstoreturn` module).
            If :attr:`pyuaf.util.timestampstoreturn.Both` is specified, the Source timestamp
            will be used for selection.
            Default is :attr:`pyuaf.util.timestampstoreturn.Source`.
            Default = 0 = no limit.
        
        .. autoattribute:: pyuaf.client.settings.HistoryReadRawModifiedSettings.releaseContinuationPoints
        
            ``bool`` flag: True to let the Server know that no more historical data is needed,
            and so the server may release any resources associated with the call.
            Default is False. 






*class* MethodCallSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.MethodCallSettings

    A MethodCallSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA MethodCall service invocation.

    
    * Methods:

        .. method:: __init__()
    
            Create a new MethodCallSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.



*class* MonitoredItemSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.MonitoredItemSettings

    A MonitoredItemSettings object holds the properties of monitored items (both for monitoring
    data, and monitoring events). 
    
    
    * Methods:

        .. method:: __init__(*args)
    
            Create a new MonitoredItemSettings object, by default for monitoring data.
            
            Usage example::
            
                import pyuaf
                from pyuaf.client.settings import MonitoredItemSettings
                
                # 1) create a default monitored item settings --> to monitor data changes
                # -----------------------------------------------------------------------
                monIt = MonitoredItemSettings()
                # alternative: monIt = MonitoredItemSettings(MonitoredItemSettings.Data)
                monIt.samplingIntervalSec = 1.0
                monIt.kind() # equals MonitoredItemSettings.Data
                monIt.dataChangeFilter.deadBandEnabled = True
                monIt.dataChangeFilter.deadBandValue   = 1.0
                # (monIt.eventFilter is None)
                
                # 2) create a monitored item settings to monitor events
                # -----------------------------------------------------------------------
                monIt = MonitoredItemSettings(MonitoredItemSettings.Event)
                monIt.samplingIntervalSec = 1.0
                monIt.kind() # equals MonitoredItemSettings.Event
                monIt.eventFilter.selectClauses.resize(3)
                # (monIt.dataChangeFilter is None)
    
    
        .. automethod:: pyuaf.client.settings.MonitoredItemSettings.kind
    
            Get the kind of monitored item settings: is it to monitor data changes, or events?
            
            :return: Either :attr:`pyuaf.client.settings.MonitoredItemSettings.Data`
                     or :attr:`pyuaf.client.settings.MonitoredItemSettings.Event`.
            :rtype: ``int``
    
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Class attributes:

        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.Data

            An ``int`` identifying the kind of MonitoredItemSettings as to monitor data changes.

        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.Event

            An ``int`` identifying the kind of MonitoredItemSettings as to monitor events.


    * Attributes:
    
        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.samplingIntervalSec

            The sampling interval of the monitored item, in seconds, as a ``float``.
    
        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.queueSize

            The queue size on the server side, as an ``int``.
    
        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.discardOldest

            True to discard the oldest item in the queue.
            
            Type of the attribute: ``bool``.
    
        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.dataChangeFilter

            The :class:`~pyuaf.util.DataChangeFilter` in case the
            :meth:`~pyuaf.client.settings.MonitoredItemSettings.kind` 
            is :attr:`pyuaf.client.settings.MonitoredItemSettings.Data`.
            
            ``None`` otherwise! 
            
        .. autoattribute:: pyuaf.client.settings.MonitoredItemSettings.eventFilter

            The :class:`~pyuaf.util.EventFilter` in case the
            :meth:`~pyuaf.client.settings.MonitoredItemSettings.kind` 
            is :attr:`pyuaf.client.settings.MonitoredItemSettings.Event`.
            
            ``None`` otherwise! 
            



*class* ReadSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.ReadSettings

    A ReadSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA Read service invocation.

    
    * Methods:

        .. method:: __init__()
    
            Create a new ReadSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.
    
    * Additional attributes:
        
        .. autoattribute:: pyuaf.client.settings.ReadSettings.maxAgeSec
        
            The maximum age (in seconds) that the attribute that is read, should have, 
            as a ``float``.


    
*class* SessionSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.SessionSettings

    A SessionSettings object stores the settings of an OPC UA session.

    
    * Methods:

        .. method:: __init__()
    
            Construct a new SessionSettings object with the following default values:
            
              - sessionTimeoutSec  = 1200.0
              - connectTimeoutSec  = 2.0
              - watchdogTimeoutSec = 2.0
              - watchdogTimeSec    = 5.0
              - securitySettingsList = a list of 1 instance: a default :class:`~pyuaf.client.settings.SessionSecuritySettings` instance.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.
    
    
    * Attributes
    
        .. autoattribute:: pyuaf.client.settings.SessionSettings.sessionTimeoutSec
        
            The time a session should remain valid on the server after a connection error, 
            as a ``float``.
        
        .. autoattribute:: pyuaf.client.settings.SessionSettings.connectTimeoutSec
        
            The timeout for the connect call, as a ``float``.
        
        .. autoattribute:: pyuaf.client.settings.SessionSettings.watchdogTimeSec
        
            The time between watchdog calls, as a ``float``.
        
        .. autoattribute:: pyuaf.client.settings.SessionSettings.watchdogTimeoutSec
        
            The timeout of watchdog calls, as a ``float``.

        .. autoattribute:: pyuaf.client.settings.SessionSettings.readServerInfoSettings

            The settings to be used to read the namespace array and server array, when the session
            is first connected (UAF clients will do this automatically in the background).
            The type of this attribute is :class:`~pyuaf.client.settings.ReadSettings`.

        .. autoattribute:: pyuaf.client.settings.SessionSettings.securitySettingsList
        
            The allowed security settings to be used to connect the session, in the order they
            are given in the list.
            
            So securitySettingsList[0] will be tried first, then securitySettingsList[1],
            and so on.
        
            The type of this attribute is :class:`~pyuaf.client.settings.SessionSecuritySettingsVector`.
        

    
    
*class* SessionSecuritySettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.SessionSecuritySettings

    A SessionSecuritySettings object stores the security settings of an OPC UA session.

    
    * Methods:

        .. method:: __init__()
    
            Create a default SessionSecuritySettings object.
            
            A default instance has 
             - no security policy (:attr:`pyuaf.util.securitypolicies.UA_None`)
             - no security mode (:attr:`pyuaf.util.messagesecuritymodes.Mode_None`)
             - no authentication (:attr:`pyuaf.util.usertokentypes.Anonymous`)
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.securityPolicy

            The security policy to be used (e.g. :attr:`pyuaf.util.securitypolicies.UA_Basic128`), 
            as a ``str``.
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.messageSecurityMode

            The message security mode to be used 
            (e.g. :attr:`pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt`), as an ``int``.
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.userTokenType

            The type of the User token, to be used
            (e.g. :attr:`pyuaf.util.usertokentypes.Anonymous`), as an ``int``.
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.userName

            The user name, as a ``str``
            (only relevant if 
            the :attr:`~pyuaf.client.settings.SessionSecuritySettings.userTokenType` 
            == :attr:`pyuaf.util.usertokentypes.UserName`).
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.userPassword

            The user password, as a ``str``
            (only relevant if 
            the :attr:`~pyuaf.client.settings.SessionSecuritySettings.userTokenType` 
            == :attr:`pyuaf.util.usertokentypes.UserName`).
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.userCertificateFileName

            The user certificate file name, as a ``str``
            (only relevant if
            the :attr:`~pyuaf.client.settings.SessionSecuritySettings.userTokenType` 
            == :attr:`pyuaf.util.usertokentypes.Certificate`).
    
        .. autoattribute:: pyuaf.client.settings.SessionSecuritySettings.userPrivateKeyFileName

            The user certificate private key file name, as a ``str``
            (only relevant if 
            the :attr:`~pyuaf.client.settings.SessionSecuritySettings.userTokenType` 
            == :attr:`pyuaf.util.usertokentypes.Certificate`).

    
    
*class* SessionSecuritySettingsVector
----------------------------------------------------------------------------------------------------


.. class:: pyuaf.client.settings.SessionSecuritySettingsVector

    A SessionSecuritySettingsVector is a container that holds elements of type 
    :class:`~pyuaf.client.settings.SessionSecuritySettings`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`pyuaf.client.settings.SessionSecuritySettings`.

    Usage example::
    
        import pyuaf
        from pyuaf.client.settings import SessionSecuritySettings, SessionSecuritySettingsVector
        
        # construct a SessionSecuritySettingsVector without elements:
        vec = SessionSecuritySettingsVector()
        
        noOfElements = len(vec) # will be 0
        
        vec.append(SessionSecuritySettings())
        
        vec[0].securityPolicy      = pyuaf.util.securitypolicies.UA_Basic128
        vec[0].messageSecurityMode = pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt
        vec[0].userTokenType       = pyuaf.util.usertokentypes.UserName
        vec[0].userName            = "John"
        
        noOfElements = len(vec) # will be 1
        
        vec.resize(4)
        
        noOfElements = len(vec) # will be 4
        
        # you may construct an ApplicationDescriptionVector from a regular Python list:
        #  - create a first SessionSecuritySettings object
        settings0 = SessionSecuritySettings()
        settings0.securityPolicy = pyuaf.util.securitypolicies.UA_None
        #  - create a second SessionSecuritySettings object
        settings1 = SessionSecuritySettings()
        settings1.securityPolicy      = pyuaf.util.securitypolicies.UA_Basic128
        settings1.messageSecurityMode = pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt
        settings1.userTokenType       = pyuaf.util.usertokentypes.UserName
        settings1.userName            = "John"
        #  - create the vector
        otherVec = SessionSecuritySettingsVector( [settings0, settings1] )


    
*class* SpecificSessionSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.SpecificSessionSettings

    SpecificSessionSettings is a container that maps serverURIs (of type ``str``) to session 
    settings (of type :class:`~pyuaf.client.settings.SessionSettings`).
     
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``dict`` of :class:`~pyuaf.client.settings.SessionSettings`.

    Usage example::
    
        import pyuaf
        from pyuaf.client.settings import SessionSettings, SpecificSessionSettings
        
        # construct an empty SpecificSessionSettings map:
        specifics = SpecificSessionSettings()
        
        noOfPairs = len(vec) # will be 0
        
        # add some specific session settings for a server with URI "/some/URI/"
        specifics["/some/URI/"] = SessionSettings()
        specifics["/some/URI/"].sessionTimeoutSec = 600.0
        specifics["/some/URI/"].connectTimeoutSec = 2.0
        
        noOfPairs = len(vec) # will be 1
        
        # add some other specific session settings for a server with URI "/some/other/URI/"
        specifics["/some/other/URI/"] = SessionSettings()
        specifics["/some/other/URI/"].sessionTimeoutSec = 800.0
        specifics["/some/other/URI/"].connectTimeoutSec = 3.0
        
        noOfPairs = len(vec) # will be 2
        
        # now remove the first entry
        specifics.erase("/some/other/URI/")
        
        # get the keys, the values, the items
        keys = specifics.keys()
        values = specifics.values()
        items = specifics.items()
        
        # clear the whole map
        specifics.clear()
        
        # check if a key is present
        specifics.has_key("/some/other/URI/")
        
        # ...


*class* SpecificSubscriptionSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.SpecificSubscriptionSettings

    SpecificSubscriptionSettings is a container that maps serverURIs (of type ``str``) to subscription 
    settings (of type :class:`~pyuaf.client.settings.SubscriptionSettings`).
     
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``dict`` of :class:`~pyuaf.client.settings.SubscriptionSettings`.

    Usage example::
    
        import pyuaf
        from pyuaf.client.settings import SubscriptionSettings, SpecificSubscriptionSettings
        
        # construct an empty SpecificSubscriptionSettings map:
        specifics = SpecificSubscriptionSettings()
        
        noOfPairs = len(vec) # will be 0
        
        # add some specific subscription settings for a server with URI "/some/URI/"
        specifics["/some/URI/"] = SubscriptionSettings()
        specifics["/some/URI/"].publishingIntervalSec = 2.0
        
        noOfPairs = len(vec) # will be 1
        
        # add some other specific subscription settings for a server with URI "/some/other/URI/"
        specifics["/some/other/URI/"] = SubscriptionSettings()
        specifics["/some/URI/"].publishingIntervalSec = 0.5
        
        noOfPairs = len(vec) # will be 2
        
        # now remove the first entry
        specifics.erase("/some/other/URI/")
        
        # get the keys, the values, the items
        keys = specifics.keys()
        values = specifics.values()
        items = specifics.items()
        
        # clear the whole map
        specifics.clear()
        
        # check if a key is present
        specifics.has_key("/some/other/URI/")
        
        # ...


*class* SubscriptionSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.SubscriptionSettings

    A SubscriptionSettings object stores the settings of an OPC UA subscription.

    
    * Methods:

        .. method:: __init__()
    
            Construct a new SubscriptionSettings object with the following default values:
            
              - unique                     = False
              - publishingIntervalSec      = 1.0
              - lifeTimeCount              = 1200
              - maxKeepAliveCount          = 5
              - maxNotificationsPerPublish = 0
              - priority                   = 0
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.
    
    
    * Attributes
    
        .. autoattribute:: pyuaf.client.settings.SubscriptionSettings.unique
        
            Set this flag to True, to force the UAF to create a *new* subscription. 
            If you leave this flag False, the UAF may choose to re-use an existing subscription 
            (if one is found that has the same properties).
            
            The type of this attribute is ``bool``.
    
        .. autoattribute:: pyuaf.client.settings.SubscriptionSettings.publishingIntervalSec
        
            The publishing interval in seconds, as a ``float``.
    
        .. autoattribute:: pyuaf.client.settings.SubscriptionSettings.lifeTimeCount
        
            The life time count, as an ``int``.
    
        .. autoattribute:: pyuaf.client.settings.SubscriptionSettings.maxKeepAliveCount
        
            The max keep alive count, as an ``int``.
    
        .. autoattribute:: pyuaf.client.settings.SubscriptionSettings.maxNotificationsPerPublish
        
            The max number of notifications per publish, as an ``int``.
            
    
        .. autoattribute:: pyuaf.client.settings.SubscriptionSettings.priority
        
            The priority of the subscription, as an ``int``.
            Since this value is only 8-bit, the maximum priority is 255.
            


*class* TranslateBrowsePathsToNodeIdsSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings

    A TranslateBrowsePathsToNodeIdsSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA TranslateBrowsePathsToNodeIds service invocation.

    
    * Methods:

        .. method:: __init__()
    
            Create a new TranslateBrowsePathsToNodeIdsSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.



*class* WriteSettings
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.settings.WriteSettings

    A WriteSettings is a subclass of :class:`pyuaf.client.settings.ServiceSettings` and 
    defines some properties of an OPC UA Write service invocation.

    
    * Methods:

        .. method:: __init__()
    
            Create a new WriteSettings object.
            
    
        .. method:: __str__()
    
            Get a formatted string representation of the settings.


    * Attributes inherited from :class:`pyuaf.client.settings.ServiceSettings`:
    
        .. autoattribute:: pyuaf.client.settings.ServiceSettings.callTimeoutSec

            The maximum time allowed for each service communication between client and server,
            in seconds, as a ``float``.





