
``pyuaf.util.securitypolicies``
====================================================================================================

.. automodule:: pyuaf.util.securitypolicies

    This module defines the security policies as specified by the OPC UA standard.


    * Attributes:
    
        .. autoattribute:: pyuaf.util.securitypolicies.UA_None
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic128
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic128Rsa15
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic192
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic192Rsa15
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic256
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic256Rsa15
        .. autoattribute:: pyuaf.util.securitypolicies.UA_Basic256Sha256
        
        
    * Functions:
    
        
        .. autofunction:: pyuaf.util.securitypolicies.toCompactString(policy)
        
            Get a compact string representation of the security policy.
        
            :param policy: The policy, e.g. :py:attr:`pyuaf.util.securitypolicies.UA_Basic128`.
            :type  policy: ``str``
            :return: The name of the type, e.g. 'Basic128'.
            :rtype:  ``str``

