

``pyuaf.util.messagesecuritymodes``
====================================================================================================

.. automodule:: pyuaf.util.messagesecuritymodes

    This module defines the ways to secure the OPC UA communication (for instance, by signing and 
    encrypting the messages). 
    
    The modes have a prefix ``Mode_`` to not confuse Mode_None with the python 'None' type.


    * Attributes:
    
    
        .. autoattribute:: pyuaf.util.messagesecuritymodes.Mode_Invalid
        
            Invalid message security mode.
    
        .. autoattribute:: pyuaf.util.messagesecuritymodes.Mode_None
        
            No signing, no encryption.
        
        .. autoattribute:: pyuaf.util.messagesecuritymodes.Mode_Sign
        
            Signing only.
        
        .. autoattribute:: pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt
        
            Signing and encryption.
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.messagesecuritymodes.toString(messageSecurityMode)
        
            Get a string representation of the message security mode.
        
            :param messageSecurityMode: The message security mode, 
                                        e.g. :py:attr:`pyuaf.util.messagesecuritymodes.Mode_Sign`.
            :type  messageSecurityMode: ``int``
            :return: The name of the message security mode, e.g. 'Sign'.
            :rtype:  ``str``

    