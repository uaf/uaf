
``pyuaf.client.sessionstates``
====================================================================================================

.. automodule:: pyuaf.client.sessionstates

    This module defines the session states, from the point of view of the client. 
    
    
    * Attributes:
    
        .. autoattribute:: pyuaf.client.sessionstates.Disconnected

            The session was disconnected by the user on the client side. A disconnected session
            may be "cleaned up" automatically by the UAF.
        
        .. autoattribute:: pyuaf.client.sessionstates.Connected
        
            The session is established, and is in a healthy state.
            
        .. autoattribute:: pyuaf.client.sessionstates.ConnectionWarningWatchdogTimeout
        
            There was a watchdog timeout, indicating a potential connection problem. 
            When this state is active, the UAF will try to re-establish the connection.
        
        .. autoattribute:: pyuaf.client.sessionstates.ConnectionErrorApiReconnect
        
            The UAF client is trying to reconnect after a connection problem.
        
        .. autoattribute:: pyuaf.client.sessionstates.ServerShutdown
        
            The UAF client is trying to reconnect after the server announced its shutdown.
        
        .. autoattribute:: pyuaf.client.sessionstates.NewSessionCreated
        
            A new session has been created since the old one could not be reused.


    * Functions:


        .. autofunction:: pyuaf.client.sessionstates.toString(sessionState)
        
            Get a string representation of the session state.
        
            :param sessionState: The session state, e.g. :py:attr:`pyuaf.client.sessionstates.ServerShutdown`.
            :type  sessionState: ``int``
            :return: The name of the session state, e.g. 'ServerShutdown'.
            :rtype:  ``str``
