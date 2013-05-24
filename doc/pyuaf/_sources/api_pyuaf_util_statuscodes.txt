

``pyuaf.util.statuscodes``
====================================================================================================

.. automodule:: pyuaf.util.statuscodes

    This module defines the status codes as specified by the UAF.
    
    The *UAF status codes* 
    (which are defined in the :mod:`pyuaf.util.statuscodes` module)
    are not to be confused with the *OPC UA status codes* 
    (which are defined in the :mod:`pyuaf.util.opcuastatuscodes` module). 
    The *OPC UA status codes* are more than 200 "detailed" codes defined by the OPC UA standard, 
    while the *UAF status codes* are around 20 more "general" codes.
    Each one of the more than 200 *OPC UA status codes* can be mapped to exactly one *UAF status code*.
    
    E.g. the OPC UA :attr:`~pyuaf.util.opcuastatuscodes.OpcUa_GoodMoreData`, 
    :attr:`~pyuaf.util.opcuastatuscodes.OpcUa_GoodNoData`, 
    :attr:`~pyuaf.util.opcuastatuscodes.OpcUa_GoodShutdownEvent` etc. codes are 
    all mapped to the UAF :attr:`~pyuaf.util.statuscodes.Good` code since there is only one 
    "Good" *UAF status code*.
    
    Similarly, an  :attr:`~pyuaf.util.opcuastatuscodes.OpcUa_BadUserAccessDenied`, 
    :attr:`~pyuaf.util.opcuastatuscodes.OpcUa_BadCertificateInvalid`, 
    :attr:`~pyuaf.util.opcuastatuscodes.OpcUa_BadCertificateUntrusted` (and many more) 
    *OPC UA status codes* lead to a 
    :py:attr:`~pyuaf.util.statuscodes.SecurityError` *UAF status code*.  
    
    Simply read the *UAF status code* (e.g. with :meth:`pyuaf.util.Status.statusCode`) if you're 
    happy with general status information, or read the *UAF + OPC UA status codes* (e.g. with 
    :meth:`pyuaf.util.Status.statusCode` and :meth:`pyuaf.util.Status.opcUaStatusCode`) if you 
    want more detailed status information. 
    
    

    * Attributes:
    
        .. autoattribute:: pyuaf.util.statuscodes.Good
        .. autoattribute:: pyuaf.util.statuscodes.Uncertain
        .. autoattribute:: pyuaf.util.statuscodes.ConfigurationError
        .. autoattribute:: pyuaf.util.statuscodes.ConnectionError
        .. autoattribute:: pyuaf.util.statuscodes.DataFormatError
        .. autoattribute:: pyuaf.util.statuscodes.DataSizeError
        .. autoattribute:: pyuaf.util.statuscodes.DataSourceError
        .. autoattribute:: pyuaf.util.statuscodes.DisconnectionError
        .. autoattribute:: pyuaf.util.statuscodes.DiscoveryError
        .. autoattribute:: pyuaf.util.statuscodes.InvalidRequestError
        .. autoattribute:: pyuaf.util.statuscodes.LowLevelError
        .. autoattribute:: pyuaf.util.statuscodes.ResolutionError
        .. autoattribute:: pyuaf.util.statuscodes.WrongTypeError
        .. autoattribute:: pyuaf.util.statuscodes.OtherError
        .. autoattribute:: pyuaf.util.statuscodes.SecurityError
        .. autoattribute:: pyuaf.util.statuscodes.TimeoutError
        .. autoattribute:: pyuaf.util.statuscodes.NoResultReceivedError
        .. autoattribute:: pyuaf.util.statuscodes.SubscriptionError
        .. autoattribute:: pyuaf.util.statuscodes.UnexpectedError
        .. autoattribute:: pyuaf.util.statuscodes.UnknownHandleError
        .. autoattribute:: pyuaf.util.statuscodes.UnsupportedError
               
    * Functions:
         
        .. autofunction:: pyuaf.util.statuscodes.toString(code)
        
            Get a string representation of the UAF status code.
        
            :param code: The code, e.g. :py:attr:`pyuaf.util.statuscodes.SecurityError`.
            :type  code: ``int``
            :return: The name of the type, e.g. 'SecurityError'.
            :rtype:  ``str``
