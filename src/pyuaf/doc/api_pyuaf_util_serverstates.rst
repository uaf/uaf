

``pyuaf.util.serverstates``
====================================================================================================

.. automodule:: pyuaf.util.serverstates

    This module defines the server states.
    
    * Attributes:

        .. autoattribute:: pyuaf.util.serverstates.Running
        
            The server is running normally.
            
        .. autoattribute:: pyuaf.util.serverstates.Failed
        
            The server is in a failed state.
            
        .. autoattribute:: pyuaf.util.serverstates.NoConfiguration
        
            The server is running but has no configuration.
            
        .. autoattribute:: pyuaf.util.serverstates.Suspended
        
            The server is suspended.
            
        .. autoattribute:: pyuaf.util.serverstates.Shutdown
        
            The server is shutdown.
            
        .. autoattribute:: pyuaf.util.serverstates.Test
        
            The server is in a test state.
            
        .. autoattribute:: pyuaf.util.serverstates.CommunicationFault
        
            The server is having trouble to access its data sources due to a communication fault.
            
        .. autoattribute:: pyuaf.util.serverstates.Unknown
        
            The underlying servers state is unknown.
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.serverstates.toString(state)
        
            Get a string representation of the server state
        
            :param state: The state, e.g. :py:attr:`pyuaf.util.serverstates.Running`.
            :type  state: ``int``
            :return: The name of the state, e.g. "Running".
            :rtype:  ``str``
