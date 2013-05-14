

``pyuaf.client.subscriptionstates``
====================================================================================================

.. automodule:: pyuaf.client.subscriptionstates

    This module defines the subscription states, from the point of view of the client. 
    
    
    * Attributes:
    
        .. autoattribute:: pyuaf.client.subscriptionstates.Created

            The subscription is established.
        
        .. autoattribute:: pyuaf.client.subscriptionstates.Deleted
        
            The subscription is not established.
            

    * Functions:


        .. autofunction:: pyuaf.client.subscriptionstates.toString(subscriptionState)
        
            Get a string representation of the subscription state.
        
            :param subscriptionState: The subscription state, e.g. :py:attr:`pyuaf.client.subscriptionstates.Created`.
            :type  subscriptionState: ``int``
            :return: The name of the subscription state, e.g. 'Created'.
            :rtype:  ``str``

