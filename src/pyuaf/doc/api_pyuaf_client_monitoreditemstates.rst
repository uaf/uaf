

``pyuaf.client.monitoreditemstates``
====================================================================================================

.. automodule:: pyuaf.client.monitoreditemstates

    This module defines the monitored item states, from the point of view of the client. 
    
    
    * Attributes:
    
        .. autoattribute:: pyuaf.client.monitoreditemstates.Created

            The monitored item is created on the server.
        
        .. autoattribute:: pyuaf.client.monitoreditemstates.NotCreated

            The monitored item is NOT created on the server.
            

    * Functions:


        .. autofunction:: pyuaf.client.monitoreditemstates.toString(monitoredItemState)
        
            Get a string representation of the monitored item state.
        
            :param monitoredItemState: The monitored item state, e.g. :py:attr:`pyuaf.client.monitoreditemstates.Created`.
            :type  monitoredItemState: ``int``
            :return: The name of the monitored item state, e.g. 'Created'.
            :rtype:  ``str``

