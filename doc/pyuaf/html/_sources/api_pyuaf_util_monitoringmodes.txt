
``pyuaf.util.monitoringmodes``
====================================================================================================

.. automodule:: pyuaf.util.monitoringmodes

    This module defines the monitoring modes of monitored items. 
    

    * Attributes:
    
    
        .. autoattribute:: pyuaf.util.monitoringmodes.Disabled
        
            The data source is not monitored.
    
        .. autoattribute:: pyuaf.util.monitoringmodes.Sampling
        
            The data source is being sampled, but not reported.
        
        .. autoattribute:: pyuaf.util.monitoringmodes.Reporting
        
            The data source is being sampled and reported.
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.monitoringmodes.toString(monitoringMode)
        
            Get a string representation of the monitoring mode.
        
            :param monitoringMode: The monitoring mode, 
                                   e.g. :py:attr:`pyuaf.util.monitoringmodes.Reporting`.
            :type  monitoringMode: ``int``
            :return: The name of the monitoring mode, e.g. 'Reporting'.
            :rtype:  ``str``
        