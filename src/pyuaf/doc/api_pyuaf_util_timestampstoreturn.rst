

``pyuaf.util.timestampstoreturn``
====================================================================================================

.. automodule:: pyuaf.util.timestampstoreturn

    This module defines the ways to return the timestamps when calling an OPC UA service. 


    * Attributes:
    
    
        .. autoattribute:: pyuaf.util.timestampstoreturn.Source
        
            Return only the source timestamp.
    
        .. autoattribute:: pyuaf.util.timestampstoreturn.Server
        
            Return only the server timestamp.
        
        .. autoattribute:: pyuaf.util.timestampstoreturn.Both
        
            Return both the source and server timestamps.
        
        .. autoattribute:: pyuaf.util.timestampstoreturn.Neither
        
            Don't return any timestamp.
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.timestampstoreturn.toString(timestamps)
        
            Get a string representation of the timestamps to return.
        
            :param timestamps: The timestamps to return 
                               e.g. :py:attr:`pyuaf.util.timestampstoreturn.Both`.
            :type  timestamps: ``int``
            :return: The name of the timestamps to return, e.g. 'Both'.
            :rtype:  ``str``

    