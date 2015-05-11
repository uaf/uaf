
``pyuaf.client.connectionsteps``
====================================================================================================

.. automodule:: pyuaf.client.connectionsteps

    This module defines the steps during the connection process.
    
    
    * Attributes:
    
        .. autoattribute:: pyuaf.client.connectionsteps.NoAttemptYet

            Connection has not started yet.
    
        .. autoattribute:: pyuaf.client.connectionsteps.CertificateValidation

            Certificate validation step.
        
        .. autoattribute:: pyuaf.client.connectionsteps.OpenSecureChannel
        
            Opening a secure channel.
            
        .. autoattribute:: pyuaf.client.connectionsteps.CreateSession
        
            Creating the session.
        
        .. autoattribute:: pyuaf.client.connectionsteps.ActivateSession
        
            Activating the session.
        
        .. autoattribute:: pyuaf.client.connectionsteps.Unknown
        
            This connection step is unknown.


    * Functions:


        .. autofunction:: pyuaf.client.connectionsteps.toString(step)
        
            Get a string representation of the connection step.
        
            :param step: The connection step, e.g. :py:attr:`pyuaf.client.connectionsteps.OpenSecureChannel`.
            :type  step: ``int``
            :return: The name of the connection step, e.g. 'OpenSecureChannel'.
            :rtype:  ``str``
