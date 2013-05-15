
``pyuaf``
====================================================================================================


.. automodule:: pyuaf


:mod:`pyuaf` currently contains two modules: 

 - :mod:`pyuaf.util` for common utility code
 - :mod:`pyuaf.client` for all client related code.

 
It also contains an attribute:

    .. attribute:: initialized
        
        A ``bool``, telling you if the stack is initialized.
        
        The underlying OPC UA stack needs to be initialized before you use it. When you do::
        
            import pyuaf
            
        then the stack is automatically initialized, and this attribute will be ``True``.
        If some error happens instead, the attribute will be ``False``.