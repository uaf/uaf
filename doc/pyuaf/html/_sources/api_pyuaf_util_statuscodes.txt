

``pyuaf.util.statuscodes``
====================================================================================================

.. automodule:: pyuaf.util.statuscodes

    This module defines the status codes as specified by the UAF.
    These status codes are more general than the (more than hundred!) status codes specified by the
    OPC UA standard. Each "OPC UA status code" can be mapped to exactly one "UAF statuscode". 
    
    For instance, an ``OpcUa_BadUserAccessDenied``, ``OpcUa_BadCertificateInvalid``, 
    ``OpcUa_BadCertificateUntrusted`` (and many more) OPC UA status codes lead to a 
    :py:attr:`pyuaf.util.statuscodes.SecurityError` status code.  
    

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
