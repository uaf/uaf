``pyuaf.client.configs``
====================================================================================================

.. automodule:: pyuaf.client.configs


In UAF terminology, a ``Config`` contains one or more ``Settings`` (which are defined in the
:mod:`pyuaf.client.settings` module).




*class* BrowseConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.BrowseConfig

    A BrowseConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.BrowseRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.BrowseSettings` instance, containing the settings for the
        actual Browse service (and subsequent BrowseNext services that are automatically invoked
        by the UAF, if you allow the UAF to do so).
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.BrowseRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.BrowseConfig.__init__
    
            Create a new BrowseConfig object.
            
    
        .. automethod:: pyuaf.client.configs.BrowseConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.BrowseConfig.serviceSettings

            The settings that will be used for the Browse service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.BrowseSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.BrowseConfig.translationSettings

            The settings that will be used if the browse request contains addresses that have 
            relative paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.



*class* BrowseNextConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.BrowseNextConfig

    A BrowseNextConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.BrowseNextRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.BrowseNextSettings` instance, containing the settings for 
        the actual BrowseNext service.
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.BrowseNextRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.BrowseNextConfig.__init__
    
            Create a new BrowseNextConfig object.
            
    
        .. automethod:: pyuaf.client.configs.BrowseNextConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.BrowseNextConfig.serviceSettings

            The settings that will be used for the Browse service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.BrowseSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.BrowseNextConfig.translationSettings

            The settings that will be used if the BrowseNext request contains addresses that have 
            relative paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.





*class* CreateMonitoredDataConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.CreateMonitoredDataConfig

    A CreateMonitoredDataConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.CreateMonitoredDataRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.CreateMonitoredDataSettings` instance, containing the settings for the
        actual CreateMonitoredData service.
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.CreateMonitoredDataRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.CreateMonitoredDataConfig.__init__
    
            Create a new CreateMonitoredDataConfig object.
            
    
        .. automethod:: pyuaf.client.configs.CreateMonitoredDataConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.CreateMonitoredDataConfig.serviceSettings

            The settings that will be used for the CreateMonitoredData service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.CreateMonitoredDataSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.CreateMonitoredDataConfig.translationSettings

            The settings that will be used if the CreateMonitoredData request contains addresses
            that have relative paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.




*class* CreateMonitoredEventsConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.CreateMonitoredEventsConfig

    A CreateMonitoredEventsConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.CreateMonitoredEventsSettings` instance, containing the settings for the
        actual CreateMonitoredEvents service.
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.CreateMonitoredEventsConfig.__init__
    
            Create a new CreateMonitoredEventsConfig object.
            
    
        .. automethod:: pyuaf.client.configs.CreateMonitoredEventsConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.CreateMonitoredEventsConfig.serviceSettings

            The settings that will be used for the CreateMonitoredEvents service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.CreateMonitoredEventsSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.CreateMonitoredEventsConfig.translationSettings

            The settings that will be used if the CreateMonitoredEvents request contains addresses 
            that have relative paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.






*class* HistoryReadRawModifiedConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.HistoryReadRawModifiedConfig

    A HistoryReadRawModifiedConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.HistoryReadRawModifiedSettings` instance, containing the 
        settings for the actual HistoryReadRawModified service (and subsequent 
        HistoryReadRawModified services that are automatically invoked
        by the UAF, if you allow the UAF to do so).
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.HistoryReadRawModifiedRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.HistoryReadRawModifiedConfig.__init__
    
            Create a new HistoryReadRawModifiedConfig object.
            
    
        .. automethod:: pyuaf.client.configs.HistoryReadRawModifiedConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.HistoryReadRawModifiedConfig.serviceSettings

            The settings that will be used for the HistoryReadRawModified service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.HistoryReadRawModifiedSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.HistoryReadRawModifiedConfig.translationSettings

            The settings that will be used if the HistoryReadRawModified request contains addresses 
            that have relative paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.





*class* MethodCallConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.MethodCallConfig

    A MethodCallConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.MethodCallRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.MethodCallSettings` instance, containing the settings for the
        actual method call service.
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.MethodCallRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.MethodCallConfig.__init__
    
            Create a new MethodCallConfig object.
            
    
        .. automethod:: pyuaf.client.configs.MethodCallConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.MethodCallConfig.serviceSettings

            The settings that will be used for the method call service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.MethodCallSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.MethodCallConfig.translationSettings

            The settings that will be used if the method call request contains addresses that have 
            relative paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.






*class* ReadConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.ReadConfig

    A ReadConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.ReadRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.ReadSettings` instance, containing the settings for the
        actual read service.
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.ReadRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.ReadConfig.__init__
    
            Create a new ReadConfig object.
            
    
        .. automethod:: pyuaf.client.configs.ReadConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.ReadConfig.serviceSettings

            The settings that will be used for the read service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.ReadSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.ReadConfig.translationSettings

            The settings that will be used if the read request contains addresses that have relative
            paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.



*class* SessionConfig
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.configs.SessionConfig

    A SessionConfig instance can be used to configure one or more sessions that need to be created,
    in order to successfully invoke an OPC UA service.
    
    .. seealso:: Check out example :ref:`sessionconfig-example` for more information.
    
    
    * Methods:

        .. automethod:: pyuaf.client.configs.SessionConfig.__init__
    
            Create a new SessionConfig object.
            
            :param defaultSettings: Optional parameter: the default session settings.
            :type defaultSettings: :class:`~pyuaf.client.settings.SessionSettings`
            
    
        .. automethod:: pyuaf.client.configs.SessionConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.SessionConfig.defaultSessionSettings

            The session settings that should be used for any session that needs to be created,
            and that is not specified (via its server URI) by the 
            :attr:`~pyuaf.client.configs.SessionConfig.specificSessionSettings`.
            
            This attribute is a :class:`~pyuaf.client.settings.SessionSettings` instance.
        
        .. autoattribute:: pyuaf.client.configs.SessionConfig.specificSessionSettings

            A container that maps <server URIs> (of type ``str``) to <session settings> 
            (of type :class:`~pyuaf.client.settings.SessionSettings`).
            
            When sessions need to be created to a server, the UAF will first check if the
            URI of this server is specified by this container. If so, then the corresponding 
            "specific" session settings will be used. If not, then the 
            :attr:`~pyuaf.client.configs.SessionConfig.defaultSessionSettings` will be used.
    
            This attribute is a :class:`~pyuaf.client.settings.SpecificSessionSettings` instance.
            
            Check out the example mentioned above for more info.

            


*class* SubscriptionConfig
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.client.configs.SubscriptionConfig

    A SubscriptionConfig instance can be used to configure one or more subscriptions that need to 
    be created, in order to successfully invoke an OPC UA service.
    
    .. seealso:: Check out example :ref:`subscriptionconfig-example` for more information.
    
    
    * Methods:

        .. automethod:: pyuaf.client.configs.SubscriptionConfig.__init__
    
            Create a new SubscriptionConfig object.
            
            :param defaultSettings: Optional parameter: the default subscription settings.
            :type defaultSettings: :class:`~pyuaf.client.settings.SubscriptionSettings`
            
    
        .. automethod:: pyuaf.client.configs.SubscriptionConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.SubscriptionConfig.defaultSubscriptionSettings

            The subscription settings that should be used for any subscription that needs to be 
            created, and that is not specified (via its server URI) by the 
            :attr:`~pyuaf.client.configs.SubscriptionConfig.specificSubscriptionSettings`.
            
            This attribute is a :class:`~pyuaf.client.settings.SubscriptionSettings` instance.
        
        .. autoattribute:: pyuaf.client.configs.SubscriptionConfig.specificSubscriptionSettings

            A container that maps <server URIs> (of type ``str``) to <subscription settings> 
            (of type :class:`~pyuaf.client.settings.SubscriptionSettings`).
            
            When subscription need to be created to a server, the UAF will first check if the
            URI of this server is specified by this container. If so, then the corresponding 
            "specific" subscription settings will be used. If not, then the 
            :attr:`~pyuaf.client.configs.SubscriptionConfig.defaultSubscriptionSettings` will be 
            used.
    
            This attribute is a :class:`~pyuaf.client.settings.SpecificSubscriptionSettings` instance.
            
            Check out the example mentioned above for more info.

            


*class* TranslateBrowsePathsToNodeIdsConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig

    A TranslateBrowsePathsToNodeIdsConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest`.
    
    It contains two :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` 
    instances, but only the 
    :attr:`~pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig.translationSettings`
    will be used.

    * Methods:

        .. automethod:: pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig.__init__
    
            Create a new TranslateBrowsePathsToNodeIdsConfig object.
            
    
        .. automethod:: pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig.serviceSettings

            Settings that won't be used, since the UAF will use the 
            :attr:`~pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig.translationSettings`
            in the first stage (the address resolution stage) of the processing of the request.
            This attribute is only here since the TranslateBrowsePathsToNodeIdsConfig is
            implementing the same C++ template class that is used by the other service configs. 
            
            This attribute is a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.TranslateBrowsePathsToNodeIdsConfig.translationSettings

            The settings that will be used if the TranslateBrowsePathsToNodeIds request contains addresses that have relative
            paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.



*class* WriteConfig
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.client.configs.WriteConfig

    A WriteConfig contains all service-related settings to process a 
    :class:`~pyuaf.client.requests.WriteRequest`.
    
    It contains:
    
      - a :class:`~pyuaf.client.settings.WriteSettings` instance, containing the settings for the
        actual write service.
        
      - a :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance, that
        will only be used to resolve the addresses that are part of the 
        :class:`~pyuaf.client.requests.WriteRequest` (if needed).


    * Methods:

        .. automethod:: pyuaf.client.configs.WriteConfig.__init__
    
            Create a new WriteConfig object.
            
    
        .. automethod:: pyuaf.client.configs.WriteConfig.__str__
    
            Get a formatted string representation of the config.


    * Attributes
    
        .. autoattribute:: pyuaf.client.configs.WriteConfig.serviceSettings

            The settings that will be used for the write service invocation.
            
            This attribute is a :class:`~pyuaf.client.settings.WriteSettings` instance.
    
        .. autoattribute:: pyuaf.client.configs.WriteConfig.translationSettings

            The settings that will be used if the write request contains addresses that have relative
            paths that need to be translated.
            
            This attribute is a 
            :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings` instance.

            
            
            