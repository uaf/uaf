

``pyuaf.util.loglevels``
====================================================================================================

.. automodule:: pyuaf.util.loglevels

    This module defines the loglevels used by the UAF to log messages to the standard output.

    Usage example:
    
    .. literalinclude:: /../../../examples/pyuaf/client/how_to_setup_logging_for_a_client.py
        

    * Attributes:
    

        .. autoattribute:: pyuaf.util.loglevels.Disabled
        
            No logging whatsoever.
    
        .. autoattribute:: pyuaf.util.loglevels.Error
        
            Only log errors.
        
        .. autoattribute:: pyuaf.util.loglevels.Warning
        
            Only log warnings and errors.
        
        .. autoattribute:: pyuaf.util.loglevels.Info
        
            Only log regular info messages, warnings and errors.
        
        .. autoattribute:: pyuaf.util.loglevels.Debug
        
            Log everything (from low level debugging messages to high level errors).
        
        
    * Functions:
    
        
        .. autofunction:: pyuaf.util.loglevels.toString(logLevel)
        
            Get a string representation of the loglevel.
        
            :param applicationType: The application type, e.g. :py:attr:`pyuaf.util.loglevels.Error`.
            :type  applicationType: ``int``
            :return: The name of the application type, e.g. 'Error'.
            :rtype:  ``str``

            
