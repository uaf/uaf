/* This file is part of the UAF (Unified Architecture Framework) project.
 *
 * Copyright (C) 2012 Wim Pessemier (Institute of Astronomy, KULeuven)
 *
 * Project website: http://www.ster.kuleuven.be/uaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


%pythoncode %{
#### BEGINNING OF INCLUDED PYTHON FILE


class Client(ClientBase):
    
    def __init__(self, settings=None, loggingCallback=None):
        """
        Construct a UAF client.
        
        Usage example:
        
        .. literalinclude:: /../../../examples/pyuaf/client/how_to_create_a_client.py
        
        :param settings: Can be:
        
          - the settings of the client (of type :class:`pyuaf.client.settings.ClientSettings`)
          - or simply the name of the client application (as a ``str``)
          - or None for defaults.
        
        :type  settings: :class:`pyuaf.client.settings.ClientSettings` or ``str`` or None
        :param callback: A callback function for the logging. This function should have one 
                         input argument, which you should call "msg" or so,
                         because this argument is of type :class:`pyuaf.util.LogMessage`.
        """
        # define the logging callback
        self.__loggingCallback__ = loggingCallback
        
        # initialize the base class
        if settings is None:
            ClientBase.__init__(self)
        else:
            ClientBase.__init__(self, settings)
        
        # define the dictionaries that hold the requestHandle:callback pairs
        self.__asyncReadCallbacks__ = dict()
        self.__asyncWriteCallbacks__ = dict()
        self.__asyncCallCallbacks__ = dict()
        self.__dataNotificationCallbacks__ = dict()
        self.__eventNotificationCallbacks__ = dict()
        # define the corresponding locks (to make sure we can register the callback
        # before the result is dispatched! --> critical section in Client::processRequest())
        self.__asyncReadLock__ = threading.Lock()
        self.__asyncWriteLock__ = threading.Lock()
        self.__asyncCallLock__ = threading.Lock()
        self.__dataNotificationLock__ = threading.Lock()
        self.__eventNotificationLock__ = threading.Lock()
    
    
    def __dispatch_readComplete__(self, result):
        """
        Dispatch the result of the asynchronous request either to a virtual readComplete function,
        or to a callback function (if one is found for the given requestHandle).
        """
        try:
            self.__asyncReadLock__.acquire()
            f = self.__asyncReadCallbacks__.pop(result.requestHandle)
        except:
            f = None
        finally:
            self.__asyncReadLock__.release()
        
        if f is None:
            try:
                self.readComplete(result)
            except:
                pass # nothing we can do at this point!
        else:
            try:
                f(result)
            except:
                pass # nothing we can do at this point!
                
    def readComplete(self, result):
        """
        Override this method to catch the result of asynchronous read requests.
        
        This method will only be called by the UAF if you didn't provide an "external" callback
        function already when you began the asynchronous read request.
        
        In other words, there are two ways how you can catch the result of asynchronous read requests:
        
         - either by calling :meth:`~pyuaf.client.Client.processRequest` *without* providing an external callback function
           via the 'resultCallback' argument --> then you need to override :meth:`~pyuaf.client.Client.callComplete`
         - or by calling :meth:`~pyuaf.client.Client.processRequest` *with* providing an external callback function
           via the 'resultCallback' argument --> then only the external callback function will be called.
        
        :param result: The asynchronously received read result.
        :type  result: :class:`~pyuaf.client.results.ReadResult`
        """
        pass
    
    def __dispatch_writeComplete__(self, result):
        """
        Dispatch the result of the asynchronous request either to a virtual writeComplete function,
        or to a callback function (if one is found for the given requestHandle).
        """
        try:
            self.__asyncWriteLock__.acquire()
            f = self.__asyncWriteCallbacks__.pop(result.requestHandle)
        except:
            f = None
        finally:
            self.__asyncWriteLock__.release()
        
        if f is None:
            try:
                self.writeComplete(result)
            except:
                pass # nothing we can do at this point!
        else:
            try:
                f(result)
            except:
                pass # nothing we can do at this point!
                
    def writeComplete(self, result):
        """
        Override this method to catch the result of asynchronous write requests.
        
        This method will only be called by the UAF if you didn't provide an "external" callback
        function already when you began the asynchronous write request.
        
        In other words, there are two ways how you can catch the result of asynchronous write requests:
        
         - either by calling :meth:`~pyuaf.client.Client.processRequest` *without* providing an external callback function
           via the 'resultCallback' argument --> then you need to override :meth:`~pyuaf.client.Client.callComplete`
         - or by calling :meth:`~pyuaf.client.Client.processRequest` *with* providing an external callback function
           via the 'resultCallback' argument --> then only the external callback function will be called.
        
        :param result: The asynchronously received write result.
        :type  result: :class:`~pyuaf.client.results.WriteResult`
        """
        pass
    
    def __dispatch_callComplete__(self, result):
        """
        Dispatch the result of the asynchronous request either to a virtual callComplete function,
        or to a callback function (if one is found for the given requestHandle).
        """
        try:
            self.__asyncCallLock__.acquire()
            f = self.__asyncCallCallbacks__.pop(result.requestHandle)
        except:
            f = None
        finally:
            self.__asyncCallLock__.release()
        
        if f is None:
            try:
                self.callComplete(result)
            except:
                pass # nothing we can do at this point!
        else:
            try:
                f(result)
            except:
                pass # nothing we can do at this point!
                
    def callComplete(self, result):
        """
        Override this method to catch the result of asynchronous method call requests.
        
        This method will only be called by the UAF if you didn't provide an "external" callback
        function already when you began the asynchronous method call request.
        
        In other words, there are two ways how you can catch the result of asynchronous method calls:
        
         - either by calling :meth:`~pyuaf.client.Client.processRequest` *without* providing an external callback function
           via the 'resultCallback' argument --> then you need to override :meth:`~pyuaf.client.Client.callComplete`
         - or by calling :meth:`~pyuaf.client.Client.processRequest` *with* providing an external callback function
           via the 'resultCallback' argument --> then only the external callback function will be called.
        
        :param result: The asynchronously received method call result.
        :type  result: :class:`~pyuaf.client.results.MethodCallResult`
        """
        pass
    
    
    def __dispatch_dataChangesReceived__(self, dataNotifications):
        """
        Dispatch the DataNofications either to a virtual dataChangesReceived function,
        or to a callback function (if one is found for the given notificationHandle).
        """
        notificationsWithoutCallback = []
        
        try:
            self.__dataNotificationLock__.acquire()
            
            for notification in dataNotifications:
                try:
                    f = self.__dataNotificationCallbacks__[notification.notificationHandle]
                    t = threading.Thread(target=f, args=[notification])
                    t.start()
                except:
                    notificationsWithoutCallback.append(notification)
        finally:
            self.__dataNotificationLock__.release()
        
        if len(notificationsWithoutCallback) > 0:
            try:
                self.dataChangesReceived(notificationsWithoutCallback)
            except:
                pass # nothing we can do at this point!
    
    def dataChangesReceived(self, dataNotifications):
        """
        Override this method to catch the "data change" notifications of MonitoredItems.
        
        This method will only be called by the UAF if you didn't provide "external" callback
        functions already when you created the monitored items.
        
        In other words, there are two ways how you can catch the data change notifications of 
        monitored data items:
        
         - either by calling :meth:`~pyuaf.client.Client.processRequest` 
           or :meth:`~pyuaf.client.Client.createMonitoredData` 
           *without* providing external callback functions
           via the 'notificationCallbacks' argument 
           --> then you need to override :meth:`~pyuaf.client.Client.dataChangesReceived`
         - or by calling :meth:`~pyuaf.client.Client.processRequest` 
           or :meth:`~pyuaf.client.Client.createMonitoredData` 
           *with* providing external callback functions
           via the 'notificationCallbacks' argument
           --> then only the external callback functions will be called.
        
        :param result: The asynchronously received notifications.
        :type  result: ``list`` of :class:`~pyuaf.client.DataChangeNotification`
        """
        pass
    
    
    def __dispatch_eventsReceived__(self, eventNotifications):
        """
        Dispatch the EventNofications either to a virtual dataChangesReceived function,
        or to a callback function (if one is found for the given notificationHandle).
        """
        notificationsWithoutCallback = []
        
        try:
            self.__eventNotificationLock__.acquire()
            
            for notification in eventNotifications:
                try:
                    f = self.__eventNotificationCallbacks__[notification.notificationHandle]
                    t = threading.Thread(target=f, args=[notification])
                    t.start()
                except:
                    notificationsWithoutCallback.append(notification)
        finally:
            self.__eventNotificationLock__.release()
        
        if len(notificationsWithoutCallback) > 0:
            try:
                self.eventsReceived(notificationsWithoutCallback)
            except:
                pass # nothing we can do at this point!
    
    
    def eventsReceived(self, eventNotifications):
        """
        Override this method to catch the "event" notifications of MonitoredItems.
        
        This method will only be called by the UAF if you didn't provide "external" callback
        functions already when you created the monitored items.
        
        In other words, there are two ways how you can catch the event notifications of 
        monitored event items:
        
         - either by calling :meth:`~pyuaf.client.Client.processRequest` 
           or :meth:`~pyuaf.client.Client.createMonitoredEvents` 
           *without* providing external callback functions
           via the 'notificationCallbacks' argument 
           --> then you need to override :meth:`~pyuaf.client.Client.eventsReceived`
         - or by calling :meth:`~pyuaf.client.Client.processRequest` 
           or :meth:`~pyuaf.client.Client.createMonitoredEvents` 
           *with* providing external callback functions
           via the 'notificationCallbacks' argument
           --> then only the external callback functions will be called.
        
        :param result: The asynchronously received notifications.
        :type  result: ``list`` of :class:`~pyuaf.client.EventNotification`
        """
        pass
    
    def __dispatch_logMessageReceived__(self, message):
        try:
            if self.__loggingCallback__ is None:
                self.logMessageReceived(message)
            else:
                self.__loggingCallback__(message)
        except:
            pass # nothing we can do at this point!
    
    
    def logMessageReceived(self, message):
        """
        You should override this method if you want to process logging output from the UAF. 
        
        This method is called by the UAF if:
          - :attr:`pyuaf.client.settings.ClientSettings.logToCallbackLevel` is not set to :attr:`pyuaf.util.loglevels.Disabled`
          - no external logging callback function is registered 
            (via :meth:`~pyuaf.client.Client` or via :meth:`~pyuaf.client.Client.registerLoggingCallback`).
        
        :param message: The received LogMessage.
        :type  message: :class:`pyuaf.util.LogMessage`
        """
        pass
    
    
    def registerLoggingCallback(self, callback):
        """
        Register a callback function to receive all log messages.
        
        If you register a callback function, this callback function will be called instead of 
        the :meth:`~pyuaf.client.Client.logMessageReceived` function (so the latter function will 
        NOT be called anymore!).
        
        :param callback: A callback function for the logging. This function should have one 
                         input argument, which you should call "msg" or so,
                         because this argument is of type :class:`pyuaf.util.LogMessage`.
        """
        self.__loggingCallback__ = callback
    
    
    
    def unregisterLoggingCallback(self):
        """
        Unregister a callback function to stop receiving all log messages.
        
        If you unregister a callback function, and callback logging is still enabled (via the 
        client settings), the log messages will be sent to the :meth:logMessageReceived method 
        (so you can virtually override this method to receive the log messages).
        """
        self.__loggingCallback__ = None
    
    
    def clientSettings(self):
        """
        Get a copy of the current client settings.
        
        :return: The currently active settings.
        :rtype:  :class:`pyuaf.client.settings.ClientSettings`
        """
        return ClientBase.clientSettings(self)
    
    
    def setClientSettings(self, settings):
        """
        Change the client settings. 
        
        :param settings: The new settings.
        :type  settings: :class:`pyuaf.client.settings.ClientSettings`
        """
        return ClientBase.setClientSettings(self, settings)
    
    
    def findServersNow(self):
       """ 
       Discover the servers immediately (instead of waiting for the background thread) by 
       using the OPC UA FindServers service.
           
       The URLs to use for discovery are specified 
       by the :attr:`~pyuaf.client.settings.ClientSettings.discoveryUrls` attribute of the 
       :class:`~pyuaf.client.settings.ClientSettings`.
       Since discovery is also handled silently (and periodically) in the background, 
       you normally don't have to call :meth:`~pyuaf.client.Client.findServersNow` manually.
       
       :raise pyuaf.util.errors.DiscoveryError:
            Raised in case the FindServers service failed for one or more URLs.
       :raise pyuaf.util.errors.InvalidRequestError:
            Raised in case the FindServers service is already being invoked by the client (because
            no parallel FindServers invocations are allowed!). This can happen for instance when
            multiple threads (created by the user, or running in the background of the Client
            instance) try to use the FindServers service at the same time.
       :raise pyuaf.util.errors.UafError:
            Base exception, catch this to handle any other errors.
       """
       status = ClientBase.findServersNow(self)
       pyuaf.util.errors.evaluate(status)
    
    
    def serversFound(self):
        """
        Get a list of the application descriptions of the servers found in the discovery process.
        
        The discovery is periodically being run in the background, so the returned list may 
        change. The cycle time is of the discovery is configurable
        via the :class:`~pyuaf.client.settings.ClientSettings`.
        
        :return: A list of the application descriptions that were found.
        :rtype: ``list`` of :class:`pyuaf.util.ApplicationDescription`
        """
        descriptionVector = ClientBase.serversFound(self)
        # put the elements in a normal python list
        l = []
        for desc in descriptionVector:
            l.append(desc)
        return l
    
    
    def manuallyConnect(self, serverUri, sessionSettings):
       """
       Create a session manually (instead of having the UAF do it behind the scenes).
       
       One of the advantages of the UAF is that you can just define the addresses of some nodes, and 
       then read/write/monitor/... them without worrying about the technical concerns such as
       session creation, subscription creation etc. So you don't have to create sessions
       yourself, because the UAF will do it for you.
       However, if you want to "keep control" over the session/subscription/... management
       yourself, you can use methods like 
       :meth:`~pyuaf.client.Client.manuallyConnect`, 
       :meth:`~pyuaf.client.Client.manuallyDisconnect`,
       :meth:`~pyuaf.client.Client.manuallySubscribe`, etc. 
       In this case, you can create the sessions/subscriptions/...
       in advance, and then afterwards read/write/... variables by using the same sessions
       and subscriptions. So these "manual" methods allow you to use OPC UA in the "traditional
       way", however it's much easier to do it the "UAF way" and simply forget about the
       creation and deletion of sessions, subscriptions, and monitored items.
           
       The URL(s) needed to discover the server with the given server URI, can be specified 
       via the :class:`~pyuaf.client.settings.ClientSettings` (which you can set via 
       :meth:`~pyuaf.client.Client` and via :meth:`~pyuaf.client.Client.setClientSettings`).
       
       
       :param serverUri: The server URI to manually connect to.
       :type  serverUri: ``str``
       :param sessionSettings: The settings for the session.
       :type  sessionSettings: :class:`~pyuaf.client.settings.SessionSettings`
       :return: The client connection id: a number identifying the session.
       :rtype: ``int``
       
       :raise pyuaf.util.errors.DiscoveryError:
            Raised in case the FindServers service failed to discover a server that matches the 
            given server URI.
       :raise pyuaf.util.errors.UafError:
            Base exception, catch this to handle any other errors.
       """
       status, clientConnectionId = ClientBase.manuallyConnect(self, serverUri, sessionSettings)
       pyuaf.util.errors.evaluate(status)
       return clientConnectionId
    
    
    def manuallyDisconnect(self, clientConnectionId):
       """
       Disconnect the session manually.
       
       A session which has been disconnected manually is "garbage collected" on the client side.
       When a session is created afterwards, a new ClientConnectionId will be assigned to this
       session (even if the properties of the new session are exactly the same as the old one). 
       
       Only use this for sessions that were created via the manuallyConnect method!
         
       :param clientConnectionId: The id of the session (that was returned by
                                  the :meth:`~pyuaf.client.Client.manuallyConnect` method).
       :type clientConnectionId: ``int``
       :raise pyuaf.util.errors.InvalidRequestError:
            Raised in case no session is known for the given client connection id.
       :raise pyuaf.util.errors.UafError:
            Base exception, catch this to handle any other errors.
       """
       status = ClientBase.manuallyDisconnect(self, clientConnectionId)
       pyuaf.util.errors.evaluate(status)
    
    
    def manuallySubscribe(self, clientConnectionId, subscriptionSettings):
       """
       Create a subscription manually.
       
       For more info about "manual" methods, see the documentation on the
       :meth:`~pyuaf.client.Client.manuallyConnect` method.
    
       :param clientConnectionId:  The id of the session which should host the subscription.
       :type clientConnectionId:   ``int``
       :param settings:            The settings of the subscription you'd like to create.
       :type settings:             :class:`~pyuaf.client.settings.SubscriptionSettings`
       :return:                    The clientSubscriptionHandle: the handle identifying the newly
                                   created subscription.
       :rtype: ``int``
       
       :raise pyuaf.util.errors.UafError:
            Base exception, catch this to handle any other errors.
       """
       status, clientSubscriptionHandle = ClientBase.manuallySubscribe(self, clientConnectionId, subscriptionSettings)
       pyuaf.util.errors.evaluate(status)
       return clientSubscriptionHandle
    
    
    def manuallyUnsubscribe(self, clientConnectionId, clientSubscriptionHandle):
       """
       Delete the subscription manually.
       
       A subscription which has been deleted manually is "garbage collected" on the client side.
       When a subscription is created afterwards, a new clientSubscriptionHandle will be assigned to this
       session (even if the properties of the new subscription are exactly the same as the old one). 
       
       :param clientConnectionId:  The id of the session that hosts the subscription.
       :type clientConnectionId:   ``int``
       :param clientSubscriptionHandle:  The id of the subscription.
       :type clientSubscriptionHandle:   ``int``
       
       :raise pyuaf.util.errors.InvalidRequestError:
            Raised in case no session is known for the given clientSubscriptionHandle.
       :raise pyuaf.util.errors.UafError:
            Base exception, catch this to handle any other errors.
       """
       status = ClientBase.manuallyUnsubscribe(self, clientConnectionId, clientSubscriptionHandle)
       pyuaf.util.errors.evaluate(status)
    
    
    def sessionInformation(self, clientConnectionId):
        """
        Get information about the specified session.
       
        :param clientConnectionId: The client connection id 
                                   (always assigned by the client, not by the user!).
        :type  clientConnectionId: ``int``
        :return: Information about the specified session.
        :rtype:  :class:`pyuaf.client.SessionInformation`
        :raise pyuaf.util.errors.InvalidRequestError:
             Raised in case no session is known for the given client connection id.
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any other errors.
        """
        sessionInfo = pyuaf.client.SessionInformation()
        status = ClientBase.sessionInformation(self, clientConnectionId, sessionInfo)
        pyuaf.util.errors.evaluate(status)
        return sessionInfo
    
    
    def allSessionInformations(self):
        """
        Get information about all sessions.
        
        :return: A list of information objects about all sessions.
        :rtype:  ``list`` of :class:`~pyuaf.client.SessionInformation`
        """
        l = []
        vec = ClientBase.allSessionInformations(self)
        for i in xrange(len(vec)):
            l.append(vec[i])
        return l
    
    
    def subscriptionInformation(self, clientSubscriptionHandle):
        """
        Get information about the specified subscription.
       
        :param clientSubscriptionHandle: The client subscription handle 
                                         (always assigned by the UAF, not by the user!).
        :type  clientSubscriptionHandle: ``int``
        :return: Information about the specified subscription.
        :rtype:  :class:`~pyuaf.client.SubscriptionInformation`
        :raise pyuaf.util.errors.InvalidRequestError:
             Raised in case no subscription is known for the given client subscription handle.
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any other errors.
        """
        subscriptionInfo = pyuaf.client.SubscriptionInformation()
        status = ClientBase.subscriptionInformation(self, clientSubscriptionHandle, subscriptionInfo)
        pyuaf.util.errors.evaluate(status)
        return subscriptionInfo
    
    
    def allSubscriptionInformations(self):
        """
        Get information about all subscriptions.
        
        :return: A list of information objects about all subscriptions.
        :rtype:  ``list`` of :class:`~pyuaf.client.SubscriptionInformation`
        """
        l = []
        vec = ClientBase.allSubscriptionInformations(self)
        for i in xrange(len(vec)):
            l.append(vec[i])
        return l
    
    
    def read(self, addresses, attributeId=pyuaf.util.attributeids.Value, serviceConfig=None, sessionConfig=None):
        """
        Read a number of node attributes synchronously.
        
        This is a convenience function for calling :class:`~pyuaf.client.Client.processRequest` with 
        a :class:`~pyuaf.client.requests.ReadRequest` as its first argument.
        For full flexibility, use that function.
        
        :param addresses: A single address or a list of addresses of nodes of which the specified 
                          attribute should be read.
        :type  addresses: :class:`~pyuaf.util.Address` or a ``list`` of :class:`~pyuaf.util.Address` 
        :param attributeId: The id of the attribute to be read (e.g. :attr:`pyuaf.util.attributeids.Value`
                            or :attr:`pyuaf.util.attributeids.DisplayName`).
        :type attributeId: ``int``
        :param serviceConfig: Additional settings for processing the read request.
                              Leave None for defaults.
        :type serviceConfig: :class:`~pyuaf.client.configs.ReadConfig`
        :param sessionConfig: A config holding settings for the session creation.
                              Leave None for defaults.
        :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
        :return: The result of the read request.
        :rtype:  :class:`~pyuaf.client.results.ReadResult`
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        if type(addresses) == pyuaf.util.Address:
            addressVector = pyuaf.util.AddressVector([addresses])
        else:
            addressVector = pyuaf.util.AddressVector(addresses)
        result = pyuaf.client.results.ReadResult()
        
        # make sure the arguments are valid (to avoid the ugly SWIG error output)
        pyuaf.util.errors.evaluateArg(attributeId, "attributeId", 
                                      int, [pyuaf.util.attributeids.Value])
        pyuaf.util.errors.evaluateArg(serviceConfig, "serviceConfig",   
                                      pyuaf.client.configs.ReadConfig, [None])
        pyuaf.util.errors.evaluateArg(sessionConfig, "sessionConfig",
                                      pyuaf.client.configs.SessionConfig, [None])
        
        if serviceConfig is None:
            serviceConfig = pyuaf.client.configs.ReadConfig()
        
        if sessionConfig is None:
            sessionConfig = pyuaf.client.configs.SessionConfig()
        
        status = ClientBase.read(self, addressVector, attributeId, serviceConfig, sessionConfig, result)
        
        pyuaf.util.errors.evaluate(status)
        return result
    
    
    def write(self, addresses, data, attributeId=pyuaf.util.attributeids.Value, serviceConfig=None, sessionConfig=None):
        """
        Write a number of node attributes synchronously.
        
        This is a convenience function for calling :class:`~pyuaf.client.Client.processRequest` with 
        a :class:`~pyuaf.client.requests.WriteRequest` as its first argument.
        For full flexibility, use that function.
        
        :param addresses: A single address or a list of addresses of nodes of which the specified 
                          attribute should be written.
        :type  addresses: :class:`~pyuaf.util.Address` or a ``list`` of :class:`~pyuaf.util.Address` 
        :param data: A single value or a list of values to be written.
        :type  data: :class:`~pyuaf.util.primitives.UInt32` or ``list`` of :class:`~pyuaf.util.primitives.UInt32`
                     or any other data type of the supported dynamic data types (or a ``list`` of them).
        :param attributeId: The id of the attribute to be written (e.g. :attr:`pyuaf.util.attributeids.Value`
                            or :attr:`pyuaf.util.attributeids.DisplayName`) for all addresses.
        :type attributeId: ``int``
        :param serviceConfig: Additional settings for processing the write request.
                              Leave None for defaults.
        :type serviceConfig: :class:`~pyuaf.client.configs.WriteConfig`
        :param sessionConfig: A config holding settings for the session creation.
                              Leave None for defaults.
        :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
        :return: The result of the write request.
        :rtype:  :class:`~pyuaf.client.results.WriteResult`
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        if len(addresses) != len(data):
            raise TypeError("The 'addresses' and 'data' arguments must either be both a " 
                            "single object, or both a list of the same size") 
        
        # if a single Address and single value are given, create vectors out of them:
        if type(addresses) == pyuaf.util.Address:
            addressVector = pyuaf.util.AddressVector([addresses])
            dataVector    = pyuaf.util.VariantVector()
            dataVector.append(data)
        # if lists are already provided, convert the lists to vectors
        else:
            addressVector = pyuaf.util.AddressVector(addresses)
            dataVector    = pyuaf.util.VariantVector()
            for item in data:
                dataVector.append(item)
        
        result = pyuaf.client.results.WriteResult()
        
        # make sure the arguments are valid (to avoid the ugly SWIG error output)
        pyuaf.util.errors.evaluateArg(attributeId, "attributeId", int, 
                                      [pyuaf.util.attributeids.Value])
        pyuaf.util.errors.evaluateArg(serviceConfig, "serviceConfig",   
                                      pyuaf.client.configs.WriteConfig, [None])
        pyuaf.util.errors.evaluateArg(sessionConfig, "sessionConfig",
                                      pyuaf.client.configs.SessionConfig, [None])
        
        
        if serviceConfig is None:
            serviceConfig = pyuaf.client.configs.WriteConfig()
        
        if sessionConfig is None:
            sessionConfig = pyuaf.client.configs.SessionConfig()
        
        status = ClientBase.write(self, addressVector, dataVector, attributeId, serviceConfig, 
                                  sessionConfig, result)
        
        pyuaf.util.errors.evaluate(status)
        return result
    
    
    def call(self, objectAddress, methodAddress, inputArgs=[], serviceConfig=None, sessionConfig=None):
        """
        Invoke a remote method call.
        
        Unlike "strict object-oriented" method calling, a method is called by specifying both 
         - the method itself (parameter methodAddress)
         - the object in which context the method should be invoked (parameter objectAddress).
        
        In other words, in OPC UA you can call a method on different objects. In contrast to strict
        object-oriented languages, where a method can only be called on the object that "owns" the
        method.
        
        This is a convenience function for calling :class:`~pyuaf.client.Client.processRequest` with 
        a :class:`~pyuaf.client.requests.MethodCallRequest` as its first argument.
        For full flexibility, use that function. For instance, if you want to call multiple 
        methods at once, you can do so by creating a :class:`~pyuaf.client.requests.MethodCallRequest` 
        and adding multiple targets.
        
        
        :param objectAddress: The address of the object node on which to call the method.
        :type  objectAddress: :class:`~pyuaf.util.Address` 
        :param methodAddress: The address of the method node to call.
        :type  methodAddress: :class:`~pyuaf.util.Address`
        :param inputArgs: A list of input arguments.
        :type  inputArgs: ``list`` of :class:`~pyuaf.util.primitives.UInt32`,
                          or ``list`` of any other supported data type.
        :param serviceConfig: Additional settings for processing the method call request.
                              Leave None for defaults.
        :type serviceConfig: :class:`~pyuaf.client.configs.MethodCallConfig`
        :param sessionConfig: A config holding settings for the session creation.
                              Leave None for defaults.
        :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
        :return: The result of the method call request.
        :rtype:  :class:`~pyuaf.client.results.MethodCallResult`
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        if inputArgs is None:
            inputArgs = []
        elif type(inputArgs) != list:
            raise TypeError("The inputArgs parameter must be a list of input arguments")
        
        # make sure the arguments are valid (to avoid the ugly SWIG error output)
        pyuaf.util.errors.evaluateArg(serviceConfig, "serviceConfig",   
                                      pyuaf.client.configs.MethodCallConfig, [None])
        pyuaf.util.errors.evaluateArg(sessionConfig, "sessionConfig",
                                      pyuaf.client.configs.SessionConfig, [None])
        
        inputArgsVector = pyuaf.util.VariantVector()
        for item in inputArgs:
            inputArgsVector.append(item)
        
        result = pyuaf.client.results.MethodCallResult()
        
        if serviceConfig is None:
            serviceConfig = pyuaf.client.configs.MethodCallConfig()
        
        if sessionConfig is None:
            sessionConfig = pyuaf.client.configs.SessionConfig()
        
        status = ClientBase.call(self, objectAddress, methodAddress, inputArgsVector, 
                                 serviceConfig, sessionConfig, result)
        
        pyuaf.util.errors.evaluate(status)
        return result
    
    
    def beginCall(self, objectAddress, methodAddress, inputArgs=[], serviceConfig=None, 
                  sessionConfig=None, callback=None):
        """
        Invoke a remote method call asynchronously.
        
        Unlike "strict object-oriented" method calling, a method is called by specifying both 
         - the method itself (parameter methodAddress)
         - the object in which context the method should be invoked (parameter objectAddress).
        
        In other words, in OPC UA you can call a method on different objects. In contrast to strict
        object-oriented languages, where a method can only be called on the object that "owns" the
        method.
        
        This is a convenience function for calling :class:`~pyuaf.client.Client.processRequest` with 
        a :class:`~pyuaf.client.requests.MethodCallRequest` as its first argument.
        For full flexibility, use that function. For instance, if you want to call multiple 
        methods at once, you can do so by creating a :class:`~pyuaf.client.requests.MethodCallRequest` 
        and adding multiple targets.
        
        :param objectAddress: The address of the object node on which to call the method.
        :type  objectAddress: :class:`~pyuaf.util.Address` 
        :param methodAddress: The address of the method node to call.
        :type  methodAddress: :class:`~pyuaf.util.Address`
        :param inputArgs: A list of input arguments.
        :type  inputArgs: ``list`` of :class:`~pyuaf.util.primitives.UInt32`,
                          or ``list`` of any other supported data type.
        :param serviceConfig: Additional settings for processing the method call request.
                              Leave None for defaults.
        :type serviceConfig: :class:`~pyuaf.client.configs.MethodCallConfig`
        :param sessionConfig: A config holding settings for the session creation.
                              Leave None for defaults.
        :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
        :param callback: A callback function to receive the result. This function should have one
                         argument (which will be of type :class:`~pyuaf.client.results.MethodCallResult`).
        :return: The result of the asynchronous method call request.
        :rtype:  :class:`~pyuaf.client.results.AsyncMethodCallResult`
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        # make sure the arguments are valid (to avoid the ugly SWIG error output)
        
        if callback is not None:
            if not hasattr(callback, '__call__'):
                raise TypeError("Callback argument must be callable (i.e. a function!)")
        
        if inputArgs is None:
            inputArgs = []
        elif type(inputArgs) != list:
            raise TypeError("The inputArgs parameter must be a list of input arguments")
        
        pyuaf.util.errors.evaluateArg(serviceConfig, "serviceConfig",   
                                      pyuaf.client.configs.MethodCallConfig, [None])
        pyuaf.util.errors.evaluateArg(sessionConfig, "sessionConfig",
                                      pyuaf.client.configs.SessionConfig, [None])
        
        inputArgsVector = pyuaf.util.VariantVector()
        for item in inputArgs:
            inputArgsVector.append(item)
        
        result = pyuaf.client.results.AsyncMethodCallResult()
        
        if serviceConfig is None:
            serviceConfig = pyuaf.client.configs.MethodCallConfig()
        
        if sessionConfig is None:
            sessionConfig = pyuaf.client.configs.SessionConfig()
        
        try:
            self.__asyncCallLock__.acquire()
            
            status = ClientBase.beginCall(self, objectAddress, methodAddress, inputArgsVector, 
                                          serviceConfig, sessionConfig, result)
            
            pyuaf.util.errors.evaluate(status)
                    
            # register the callback function if necessary
            if callback is not None:
                self.__asyncCallCallbacks__[result.requestHandle] = callback
            
            return result
        finally:
            self.__asyncCallLock__.release()
    
    
    def createMonitoredData(self, addresses, serviceConfig=None, sessionConfig=None, 
                            subscriptionConfig=None, notificationCallbacks=[]):
        """
        Create one or more monitored data items.
        
        This is a convenience function for calling :class:`~pyuaf.client.Client.processRequest` with 
        a :class:`~pyuaf.client.requests.CreateMonitoredDataRequest` as its first argument.
        For full flexibility, use that function.
        
        :param addresses: A single address or a list of addresses, identifying the nodes to be monitored.
        :type  addresses: :class:`~pyuaf.util.Address` or a ``list`` of :class:`~pyuaf.util.Address` 
        :param serviceConfig: Additional settings for processing the request.
                              Leave None for defaults.
        :type serviceConfig: :class:`~pyuaf.client.configs.CreateMonitoredDataConfig`
        :param sessionConfig: A config holding settings for the session creation.
                              Leave None for defaults.
        :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
        :param subscriptionConfig: A config holding settings for the subscription creation.
                                   Leave None for defaults.
        :type subscriptionConfig: :class:`~pyuaf.client.configs.SubscriptionConfig`
        :param notificationCallbacks: A list of callback functions (one for each node to be monitored).
                                      These callback functions should have a single argument, which
                                      will be of type :class:`~pyuaf.client.DataChangeNotification`.
                                      If you don't provide callback functions in this way, you'll need
                                      to override :meth:`~pyuaf.client.Client.dataChangesReceived` 
                                      in order to receive the notifications.
        :type notificationCallbacks: ``list`` of functions
        :return: The result of the CreateMonitoredData request.
        :rtype:  :class:`~pyuaf.client.results.CreateMonitoredDataResult`
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        # check the argiments
        if type(addresses) == pyuaf.util.Address:
            addressVector = pyuaf.util.AddressVector([addresses])
        elif type(addresses) == list:
            addressVector = pyuaf.util.AddressVector(addresses)
        else:
            raise TypeError("addresses should be a list of pyuaf.util.Address")
        
        # make sure the arguments are valid (to avoid the ugly SWIG error output)
        pyuaf.util.errors.evaluateArg(serviceConfig, "serviceConfig",   
                                      pyuaf.client.configs.CreateMonitoredDataConfig, [None])
        pyuaf.util.errors.evaluateArg(sessionConfig, "sessionConfig",
                                      pyuaf.client.configs.SessionConfig, [None])
        pyuaf.util.errors.evaluateArg(subscriptionConfig, "subscriptionConfig",
                                      pyuaf.client.configs.SubscriptionConfig, [None])
        pyuaf.util.errors.evaluateArg(notificationCallbacks, "notificationCallbacks",
                                      list, [])
        
        # check if the number of notificationCallbacks (if provided) correspond to the number of targets
        if len(notificationCallbacks) > 0 and len(notificationCallbacks) != len(addresses):
            raise TypeError("The number of nofificationCallbacks must correspond to the number of "
                            "addresses")
        
        # check if the notificationCallbacks are valid
        for callback in notificationCallbacks:
            if not hasattr(callback, '__call__'):
                raise TypeError("The callbacks in the notificationCallbacks argument must be " 
                                "callable (i.e. functions!)")
        
        result = pyuaf.client.results.CreateMonitoredDataResult()
        
        if serviceConfig is None:
            serviceConfig = pyuaf.client.configs.CreateMonitoredDataConfig()
        
        if sessionConfig is None:
            sessionConfig = pyuaf.client.configs.SessionConfig()
        
        if subscriptionConfig is None:
            subscriptionConfig = pyuaf.client.configs.SubscriptionConfig()
        
        try:
            self.__dataNotificationLock__.acquire()
            
            status = ClientBase.createMonitoredData(self, addressVector, serviceConfig, 
                                                    sessionConfig, subscriptionConfig, result)
            
            # register the callback functions if necessary
            if len(notificationCallbacks) > 0:
                if len(notificationCallbacks) == len(result.targets):
                    for i in xrange(len(notificationCallbacks)):
                        self.__dataNotificationCallbacks__[result.targets[i].notificationHandle] \
                                = notificationCallbacks[i]
                else:
                    raise TypeError("The number of result targets does not correspond to the "
                                    "number of nofificationCallbacks")
            
            pyuaf.util.errors.evaluate(status)
            
            return result
        
        finally:
            self.__dataNotificationLock__.release()



    
    def createMonitoredEvents(self, addresses, eventFilter=None, serviceConfig=None, 
                              sessionConfig=None, subscriptionConfig=None, 
                              notificationCallbacks=[]):
        """
        Create one or more monitored event items.
        
        This is a convenience function for calling :class:`~pyuaf.client.Client.processRequest` with 
        a :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest` as its first argument.
        For full flexibility, use that function.
        
        :param addresses: A single address or a list of addresses, identifying the nodes to be monitored.
        :type  addresses: :class:`~pyuaf.util.Address` or a ``list`` of :class:`~pyuaf.util.Address` 
        :param eventFilter: The event filter, common to all nodes that you want to monitor!
                            If you want to specify a different filter for each target, you need to 
                            use the generic :meth:`~pyuaf.client.Client.processRequest` method
                            with a :class:`~pyuaf.client.requests.CreateMonitoredEventsRequest` as 
                            argument. Leave None for defaults.
        :type  eventFilter: :class:`~pyuaf.util.EventFilter` 
        :param serviceConfig: Additional settings for processing the request.
                              Leave None for defaults.
        :type serviceConfig: :class:`~pyuaf.client.configs.CreateMonitoredEventsConfig`
        :param sessionConfig: A config holding settings for the session creation.
                              Leave None for defaults.
        :type sessionConfig: :class:`~pyuaf.client.configs.SessionConfig`
        :param subscriptionConfig: A config holding settings for the subscription creation.
                                   Leave None for defaults.
        :type subscriptionConfig: :class:`~pyuaf.client.configs.SubscriptionConfig`
        :param notificationCallbacks: A list of callback functions (one for each node to be monitored).
                                      These callback functions should have a single argument, which
                                      will be of type :class:`~pyuaf.client.EventNotification`.
                                      If you don't provide callback functions in this way, you'll need
                                      to override :meth:`~pyuaf.client.Client.eventsReceived` 
                                      in order to receive the notifications.
        :type notificationCallbacks: ``list`` of functions
        :return: The result of the CreateMonitoredEvents request.
        :rtype:  :class:`~pyuaf.client.results.CreateMonitoredEventsResult`
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        # check the argiments
        if type(addresses) == pyuaf.util.Address:
            addressVector = pyuaf.util.AddressVector([addresses])
        elif type(addresses) == list:
            addressVector = pyuaf.util.AddressVector(addresses)
        else:
            raise TypeError("addresses should be a list of pyuaf.util.Address")
        
        # make sure the other arguments are valid (to avoid the ugly SWIG error output)
        pyuaf.util.errors.evaluateArg(eventFilter, "eventFilter",   
                                      pyuaf.util.EventFilter, [None])
        pyuaf.util.errors.evaluateArg(serviceConfig, "serviceConfig",   
                                      pyuaf.client.configs.CreateMonitoredEventsConfig, [None])
        pyuaf.util.errors.evaluateArg(sessionConfig, "sessionConfig",
                                      pyuaf.client.configs.SessionConfig, [None])
        pyuaf.util.errors.evaluateArg(subscriptionConfig, "subscriptionConfig",
                                      pyuaf.client.configs.SubscriptionConfig, [None])
        pyuaf.util.errors.evaluateArg(notificationCallbacks, "notificationCallbacks",
                                      list, [])
        
        # check if the number of notificationCallbacks (if provided) correspond to the number of targets
        if len(notificationCallbacks) > 0 and len(notificationCallbacks) != len(addresses):
            raise TypeError("The number of nofificationCallbacks must correspond to the number of "
                            "addresses")
        
        # check if the notificationCallbacks are valid
        for callback in notificationCallbacks:
            if not hasattr(callback, '__call__'):
                raise TypeError("The callbacks in the notificationCallbacks argument must be " 
                                "callable (i.e. functions!)")
        
        result = pyuaf.client.results.CreateMonitoredEventsResult()
        
        if eventFilter is None:
            eventFilter = pyuaf.util.EventFilter()
        
        if serviceConfig is None:
            serviceConfig = pyuaf.client.configs.CreateMonitoredEventsConfig()
        
        if sessionConfig is None:
            sessionConfig = pyuaf.client.configs.SessionConfig()
        
        if subscriptionConfig is None:
            subscriptionConfig = pyuaf.client.configs.SubscriptionConfig()
        
        try:
            self.__eventNotificationLock__.acquire()
            
            status = ClientBase.createMonitoredEvents(self, addressVector, eventFilter, 
                                                      serviceConfig, sessionConfig, 
                                                      subscriptionConfig, result)
            
            # register the callback functions if necessary
            if len(notificationCallbacks) > 0:
                if len(notificationCallbacks) == len(result.targets):
                    for i in xrange(len(notificationCallbacks)):
                        self.__eventNotificationCallbacks__[result.targets[i].notificationHandle] \
                                = notificationCallbacks[i]
                else:
                    raise TypeError("The number of result targets does not correspond to the "
                                    "number of nofificationCallbacks")
            
            pyuaf.util.errors.evaluate(status)
            
            return result
        
        finally:
            self.__eventNotificationLock__.release()



    def processRequest(self, request, resultCallback=None, notificationCallbacks=[]):
        """
        Process a generic request (as found in :mod:`pyuaf.client.requests`).
        
        Note that asynchronous requests MUST be invoked on a single session. Meaning:
        the targets of asynchronous requests MUST belong to the same server (as the UAF can 
        currently not reconstruct an asynchronous request that must be "split up" to be called
        on multiple servers).
        
        As for callbacks, you may:
         - specify no callbacks at all. In this case, you need to override ("virtually inherit")
           the :meth:`~pyuaf.client.Client.readComplete`/:meth:`~pyuaf.client.Client.writeComplete`/:meth:`~pyuaf.client.Client.dataChangesReceived`/... functions
         - specify a resultCallback function (only for AsyncXXXXX functions!). 
           In this case, the ReadResult/WriteResult/MethodCallResult/...
           of the corresponding asynchronous requests will be forwarded to the resultCallback
           function. 
         - specify a list of notificationCallback functions (only for CreateMonitoredDataRequests,
           CreateMonitoredEventsRequests, AsyncCreateMonitoredDataRequests and 
           AsyncCreateMonitoredEventsRequests!). The number of callbacks must correspond exactly to
           the number of targets of the request.
        
        :param request: The request (e.g. a :class:`~pyuaf.client.requests.ReadRequest` 
                        or class:`~pyuaf.client.requests.WriteRequest` or ... 
        :return: The result of the request (e.g. a :class:`~pyuaf.client.results.ReadResult` 
                 or :class:`~pyuaf.client.results.WriteResult` or ...
        :raise pyuaf.util.errors.UafError:
             Base exception, catch this to handle any UAF errors.
        """
        # check if the resultCallback is valid
        if resultCallback is not None:
            if not hasattr(resultCallback, '__call__'):
                raise TypeError("resultCallback argument must be callable (i.e. a function!)")
        
        # check if the number of notificationCallbacks (if provided) correspond to the number of targets
        if len(notificationCallbacks) > 0 and len(notificationCallbacks) != len(request.targets):
            raise TypeError("The number of nofificationCallbacks must correspond to the number of targets")
        
        # check if the notificationCallbacks are valid
        for callback in notificationCallbacks:
            if not hasattr(callback, '__call__'):
                raise TypeError("The callbacks in the notificationCallbacks argument must be callable (i.e. functions!)")
        
        # create a result for the given request
        if   type(request) == pyuaf.client.requests.ReadRequest:
            result = pyuaf.client.results.ReadResult()
        elif type(request) == pyuaf.client.requests.AsyncReadRequest:
            result = pyuaf.client.results.AsyncReadResult()
        elif type(request) == pyuaf.client.requests.WriteRequest:
            result = pyuaf.client.results.WriteResult()
        elif type(request) == pyuaf.client.requests.AsyncWriteRequest:
            result = pyuaf.client.results.AsyncWriteResult()
        elif type(request) == pyuaf.client.requests.TranslateBrowsePathsToNodeIdsRequest:
            result = pyuaf.client.results.TranslateBrowsePathsToNodeIdsResult()
        elif type(request) == pyuaf.client.requests.MethodCallRequest:
            result = pyuaf.client.results.MethodCallResult()
        elif type(request) == pyuaf.client.requests.AsyncMethodCallRequest:
            result = pyuaf.client.results.AsyncMethodCallResult()
        elif type(request) == pyuaf.client.requests.CreateMonitoredDataRequest:
            result = pyuaf.client.results.CreateMonitoredDataResult()
        elif type(request) == pyuaf.client.requests.CreateMonitoredEventsRequest:
            result = pyuaf.client.results.CreateMonitoredEventsResult()
        else:
            raise TypeError("%s is not a supported request type" %type(request))
         
        try:
            # acquire the locks in case of asynchronous requests
            if type(request) == pyuaf.client.requests.AsyncReadRequest:
                self.__asyncReadLock__.acquire()
            elif type(request) == pyuaf.client.requests.AsyncWriteRequest:
                self.__asyncWriteLock__.acquire()
            elif type(request) == pyuaf.client.requests.AsyncMethodCallRequest:
                self.__asyncCallLock__.acquire()
            
            try:
                # also acquire the locks in case of monitored item callbacks
                if len(notificationCallbacks) > 0:
                    if type(request) == pyuaf.client.requests.CreateMonitoredDataRequest:
                        self.__dataNotificationLock__.acquire()
                    elif type(request) == pyuaf.client.requests.CreateMonitoredEventsRequest:
                        self.__eventNotificationLock__.acquire()
                
                # process the request
                status = ClientBase.processRequest(self, request, result)
                
                # register the notificationCallbacks if necessary
                # (do this before evaluating the status, because notification callbacks must always 
                # be registered since they belong to CreateMonitoredDataRequests or 
                # CreateMonitoredEventsRequests, which are persistent requests (i.e. if they fail,
                # the UAF will try to re-establish them later)). 
                if len(notificationCallbacks) > 0:
                    if len(notificationCallbacks) == len(result.targets):
                        for i in xrange(len(notificationCallbacks)):
                            if type(request) == pyuaf.client.requests.CreateMonitoredDataRequest:
                                self.__dataNotificationCallbacks__[result.targets[i].notificationHandle] = notificationCallbacks[i]
                
                pyuaf.util.errors.evaluate(status)
                
                # register the resultCallback if necessary
                if resultCallback is not None:
                    if type(request) == pyuaf.client.requests.AsyncReadRequest:
                        self.__asyncReadCallbacks__[result.requestHandle] = resultCallback
                    elif type(request) == pyuaf.client.requests.AsyncWriteRequest:
                        self.__asyncWriteCallbacks__[result.requestHandle] = resultCallback
                    elif type(request) == pyuaf.client.requests.AsyncMethodCallRequest:
                        self.__asyncCallCallbacks__[result.requestHandle] = resultCallback
                
                return result
            finally:
                # release the locks in case of monitored item callbacks
                if len(notificationCallbacks) > 0:
                    if type(request) == pyuaf.client.requests.CreateMonitoredDataRequest:
                        self.__dataNotificationLock__.release()
                    elif type(request) == pyuaf.client.requests.CreateMonitoredEventsRequest:
                        self.__eventNotificationLock__.release()
        finally:
            # always release the locks in case of asynchronous requests
            if type(request) == pyuaf.client.requests.AsyncReadRequest:
                self.__asyncReadLock__.release()
            elif type(request) == pyuaf.client.requests.AsyncWriteRequest:
                self.__asyncWriteLock__.release()
            elif type(request) == pyuaf.client.requests.AsyncMethodCallRequest:
                self.__asyncCallLock__.release()


#### END OF INCLUDED PYTHON FILE
%}