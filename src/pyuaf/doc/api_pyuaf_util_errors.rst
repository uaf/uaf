


``pyuaf.util.errors``
====================================================================================================

.. automodule:: pyuaf.util.errors

    This module defines the exceptions (errors) that may be raised by the UAF.
    
    PyuAF defines an error for each situation that may go wrong. The errors are subclasses of
    the python ``Exception`` class, so they can be raised, and they contain a ``message`` attribute.
    In other words, they are normal python exceptions.
    
    Many many errors are defined, so based on their type, you (the user) have a good idea of what's
    going wrong. In some cases the errors have additional attributes for more diagnostics.
    Since they are normal python exceptions, all pyuaf errors also have a ``message`` attribute
    that conveys the error information in a human readable way. 
    
    The UAF defines one "root" error, i.e. a superclass of all other errors: `~pyuaf.util.errors.UafError`.
    Further below this documentation, you'll see the whole subclassing hierarchy of all errors.
    When an error has attributes, these attributes (name and type) are displayed too.  
    
    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import NodeId, Address
        >>> from pyuaf.client import Client
        >>> from pyuaf.client.settings import ClientSettings
        >>> from pyuaf.util.errors import UnknownServerError, UafError
        >>>
        >>> # dummy logger function: 
        >>> def log(msg): pass
        >>>
        >>> c = Client(ClientSettings('my client', ['opc.tcp://localhost:4841']))
        >>> 
        >>> # let's try to read a node on the server with server URI 'urn:my:server:uri'
        >>> try:
        ...    c.read( Address(NodeId('identifier', 'http://my/ns/uri'), 'urn:my:server:uri') )
        ... except UnknownServerError, e:
        ...    log("The server %s is unknown to the client!" %e.unknownServerUri)
        ...    log("These are the servers that *are* known to the client:")
        ...    for knownServerUri in e.knownServerUris:
        ...        log(" - %s" %knownServerUri)
        ... except UafError, e:
        ...    log("Oops, an OPC UA error occurred that we didn't anticipate:")
        ...    log(str(e))
        ... except Exception, e:
        ...    log("Oops, another non-OPC UA error occurred that we didn't anticipate:")
        ...    log(str(e))



Inheritance tree of all UAF errors
----------------------------------------------------------------------------------------------------


.. literalinclude:: generated_error_inheritance_tree.txt
    

*class* UafError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.UafError
    
    A UafError is the superclass of all UAF related exceptions.
    
    Catch this error to catch all errors raised by the UAF.
    
             
    * Attributes inherited from the built-in class ``Exception``:
  
        .. attribute:: message
        
            The message of the error.
    
    
*Subclasses of UafError*
----------------------------------------------------------------------------------------------------


.. include:: generated_error_list.txt


    