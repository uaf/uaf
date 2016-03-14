


``pyuaf.util.opcuastatuscodes``
====================================================================================================

.. automodule:: pyuaf.util.opcuastatuscodes

    This module contains a very long list of numerical OPC UA status codes, as defined
    by the OPC UA standard. 
    
    The *UAF status codes* 
    (which are defined in the :mod:`pyuaf.util.statuscodes` module)
    are not to be confused with the *OPC UA status codes* 
    (which are defined in the :mod:`pyuaf.util.opcuastatuscodes` module). 
    
    - The *OPC UA status codes* are 32-bit integers defined by the OPC UA standard. They provide 
      low-level information about the OPC UA communication. Whenever
      you see an OPC UA status code (often as an attribute called ``opcUaStatusCode``), it is 
      produced by the SDK or the Stack (in other words, not by the UAF).
    
    - The *UAF status codes* are 32-bit integers defined by the UAF. 
      They provide high-level information. For all "bad" status codes (those ending with ``Error``),
      there is a corresponding error defined in :mod:`pyuaf.util.errors`. 
      For instance, a :attr:`pyuaf.util.statuscodes.InvalidServerUriError` corresponds to a 
      :class:`pyuaf.util.errors.InvalidServerUriError`. UAF status codes are used exclusively to 
      determine which error is held by a :class:`pyuaf.util.Status` object. 
      For instance, if the :attr:`~pyuaf.util.Status.statusCode` attribute of a 
      :class:`pyuaf.util.Status` instance is equal to :attr:`pyuaf.util.statuscodes.InvalidServerUriError`,
      then the Status object in fact holds a :class:`pyuaf.util.errors.InvalidServerUriError` instance.
    
    The list of OPC UA status codes is not shipped with the UAF, as it is generated from the stack
    header files.
    
    The list is way too long to document here, so you are referred to the OPC UA specification
    documents.
    
    All codes start with an ``OpcUa_`` prefix.
    
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
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadInvalidArgument
        .. autoattribute:: pyuaf.util.opcuastatuscodes.OpcUa_BadNoData

    And here's a little script you can use to print all status codes to the standard out ("stdout",
    e.g. the Windows DOS Prompt or the Linux shell) or write them to a file:
    
        .. literalinclude:: /../../../examples/pyuaf/util/how_to_print_all_opcua_status_codes.py
