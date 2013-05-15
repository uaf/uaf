

``pyuaf.util.usertokentypes``
====================================================================================================

.. automodule:: pyuaf.util.usertokentypes

    This module defines the types user tokens, i.e. the ways how users can identify themselves.
    

    * Attributes:
    

        .. autoattribute:: pyuaf.util.usertokentypes.Anonymous
        
            No token is required.
        
        .. autoattribute:: pyuaf.util.usertokentypes.UserName
        
            Username/password token is required.
        
        .. autoattribute:: pyuaf.util.usertokentypes.Certificate
        
            Certificate token is required.
        
        .. autoattribute:: pyuaf.util.usertokentypes.IssuedToken
        
            A WS-Security token is required.



    * Functions:
    
    
        .. autofunction:: pyuaf.util.usertokentypes.toString(type)
        
            Get a string representation of the user token type type.
        
            :param type: The type, e.g. :py:attr:`pyuaf.util.usertokentypes.UserName`.
            :type  type: ``int``
            :return: The name of the type, e.g. 'UserName'.
            :rtype:  ``str``

        
        