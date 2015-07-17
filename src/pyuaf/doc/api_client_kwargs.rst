
.. _note-client-kwargs:


A note on \*\*kwargs for Client services
====================================================================================================

Most Client methods (such as read, write, createMonitoredData, ...) have a special \*\*kwargs 
attribute. Similar to a Python dictionary, the \*\*kwargs attribute allows you to provide
additional key:value pairs, in order to configure the read/write/... call more in detail.

.. note::

    See the :ref:`configure-settings-example` example for more info!

1. Session-related

   The following kwargs are available to configure session(s). If neither of them is given, then
   the :attr:`~pyuaf.client.settings.ClientSettings.defaultSessionSettings` of the client will be used instead.

      
      - **clientConnectionId** 
   
         - Type: ``int``
         - Example: ``myClient.read([address], clientConnectionId = 2)``
         - Meaning: If provided, the client will use the existing session with the given clientConnectionId,
           to process the service call.
      
      - **sessionSettings**
 
         - Type: :class:`~pyuaf.client.settings.SessionSettings`
         - Example: ``myClient.read([address], sessionSettings = mySessionSettings)``
         - Meaning: If provided, then a session will be created with the given session settings,
           in order to process the service call. If a session with these settings exists already,
           then this session will be reused (unless :attr:`~pyuaf.client.settings.SessionSettings.unique`
           is set to True). If ``clientConnectionId`` was provided, then the ``sessionSettings`` kwarg
           will be ignored.
  
2. Subscription-related

   The following kwargs are available to configure session(s). If neither of them is given, then
   the :attr:`~pyuaf.client.settings.ClientSettings.defaultSubscriptionSettings` of the client will be used 
   instead. Naturally, these kwargs are only available for subscription-level requests (such
   as CreateMonitoredData).
   
      - **clientSubscriptionHandle**
 
         - Type: ``int``
         - Example: ``myClient.createMonitoredData([address], clientConnectionId = 2, clientSubscriptionHandle = 1)``
         - Meaning: If provided, the client will use the existing session with the given clientConnectionId,
           and the existing subscription with the given clientSubscriptionHandle, to process the service call.
               
      - **subscriptionSettings**
 
         - Type: :class:`~pyuaf.client.settings.SubscriptionSettings`
         - Example: ``myClient.createMonitoredData([address], subscriptionSettings = mySubscriptionSettings)``
         - Meaning: If provided, then a subscription will be created with the given subscription settings,
           in order to process the service call. If a subscription with these settings exists already,
           then this subscription will be reused (unless :attr:`~pyuaf.client.settings.SubscriptionSettings.unique`
           is set to True). If ``clientSubscriptionHandle`` was provided, then the ``subscriptionSettings`` kwarg
           will be ignored.
   
  
3. Service-related

   The following kwarg is available to configure the service call. If it is not given, then
   the default service settings (e.g. :attr:`~pyuaf.client.settings.ClientSettings.defaultReadSettings`) 
   of the client will be used instead.

      - **serviceSettings**
 
         - Type: :class:`~pyuaf.client.settings.ReadSettings`, :class:`~pyuaf.client.settings.WriteSettings`, etc. 
         - Example: ``myClient.read([address], serviceSettings = myReadSettings)``
         - Meaning: If provided, the client will use these settings to process the service call.
           If not provided, the client will use the defaults as configured by the :class:`~pyuaf.client.settings.ClientSettings`.
            
  
4. Node resolution related

   Most services also accept a ``translateSettings`` kwarg to configure the TranslateBrowsePathToNodeIds service,
   which may be needed to automatically resolve any browsepaths:

      - **translateSettings**
 
         - Type: :class:`~pyuaf.client.settings.TranslateBrowsePathsToNodeIdsSettings`
         - Example: ``myClient.read([address], translateSettings = myTranslateSettings)``
         - Meaning: If provided, these settings will be used to resolve any relative addresses into
           absolute addresses. If not provided, then the
           :attr:`~pyuaf.client.settings.ClientSettings.defaultTranslateBrowsePathsToNodeIdsSettings` will be
           used instead.

