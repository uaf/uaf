

``pyuaf.util.applicationtypes``
====================================================================================================

.. automodule:: pyuaf.util.applicationtypes

    This module defines the types of OPC UA applications. 
    
    The type of application is, for instance, part of the :class:`pyuaf.util.ApplicationDescription` 
    as returned by :py:meth:`pyuaf.client.Client.serversFound`.



    * Attributes:
        
    
        .. autoattribute:: pyuaf.util.applicationtypes.Server
        
            The application is a Server.
    
        .. autoattribute:: pyuaf.util.applicationtypes.Client
        
            The application is a Client.
        
        .. autoattribute:: pyuaf.util.applicationtypes.ClientAndServer
        
            The application is a Client and Server.
        
        .. autoattribute:: pyuaf.util.applicationtypes.DiscoveryServer
        
            The application is a Discovery Server.
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.applicationtypes.toString(applicationType)
        
            Get a string representation of the application type.
        
            :param applicationType: The application type, e.g. :py:attr:`pyuaf.util.applicationtypes.Client`.
            :type  applicationType: ``int``
            :return: The name of the application type, e.g. 'Client'.
            :rtype:  ``str``


