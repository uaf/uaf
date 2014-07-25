


``pyuaf.util.opcuastatuscodes``
====================================================================================================

.. automodule:: pyuaf.util.opcuastatuscodes

    This module contains a very long list of numerical OPC UA status codes, as defined
    by the OPC UA standard. 
    
    The *OPC UA status codes* 
    (which are defined in the :mod:`pyuaf.util.opcuastatuscodes` module)
    are not to be confused with the *UAF status codes* 
    (which are defined in the :mod:`pyuaf.util.statuscodes` module). 
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
    
    The list of OPC UA status codes is not shipped with the UAF, as it is generated from the stack
    header files.
    
    The list is way too long to document here, so you are referred to the OPC UA specification
    documents.
    
    All codes start with an ``OpcUa_`` prefix.
    
    All pyuaf.util.opcuastatuscodes correspond *bitwise* to the 32-bit unsigned numbers as defined
    by the OPC UA standard. This means that some statuscodes may appear to be negative, since 
    python interprets the 32-bit data as signed integers.  
    
    Here are some examples:

        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_Good
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_GoodMoreData
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_GoodNoData
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_GoodShutdownEvent
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_Uncertain
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_UncertainReferenceOutOfServer
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_Bad
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadArgumentsMissing
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadAttributeIdInvalid
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadConnectionClosed
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadCertificateRevoked
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadCertificateInvalid
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadCertificateUntrusted
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadUserAccessDenied
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadMaxAgeInvalid


    And here's a little script you can use to print all status codes to the standard out ("stdout",
    e.g. the Windows DOS Prompt or the Linux shell) or write them to a file:
    
        .. literalinclude:: /../../../examples/pyuaf/util/how_to_print_all_opcua_status_codes.py
