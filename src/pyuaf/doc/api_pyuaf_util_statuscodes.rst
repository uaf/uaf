

``pyuaf.util.statuscodes``
====================================================================================================

.. automodule:: pyuaf.util.statuscodes

    This module defines the status codes as specified by the UAF.
    
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
      See the example below:
    
        .. doctest::
    
            >>> import pyuaf
            >>> from pyuaf.util import Status
            >>> from pyuaf.util import errors, statuscodes
            >>> 
            >>> sts = Status( errors.InvalidServerUriError("my/invalid/server/uri"))
            >>>
            >>> assert sts.statusCode == statuscodes.InvalidServerUriError
            >>>
            >>> try:
            ...    sts.test()
            ...    raised = False;
            ... except errors.InvalidServerUriError:
            ...    raised = True;
            ...
            >>> assert raised
    

    * Attributes:
    
        .. include:: generated_statuscodes.txt
    
    * Functions:
         
        .. autofunction:: pyuaf.util.statuscodes.toString(code)
        
            Get a string representation of the UAF status code.
        
            :param code: The code, e.g. :py:attr:`pyuaf.util.statuscodes.InvalidServerUriError`.
            :type  code: ``int``
            :return: The name of the type, e.g. 'InvalidServerUriError'.
            :rtype:  ``str``
