


``pyuaf.util.errors``
====================================================================================================

.. automodule:: pyuaf.util.errors

    This module defines the exceptions that may be thrown by UAF functions.




*class* UafError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.UafError
    
    A UafError is the superclass of all UAF related exceptions.
    
    Catch this error to catch all errors thrown by the UAF.
    
    * Methods:

        .. method:: __init__(status)
        
            Create a UafError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* ConfigurationError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.ConfigurationError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a ConfigurationError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* ConnectionError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.ConnectionError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a ConnectionError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    



*class* DataFormatError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.DataFormatError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a DataFormatError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    




*class* DataSizeError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.DataSizeError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a DataSizeError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
            
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.


*class* DataSourceError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.DataSourceError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a DataSourceError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* DisconnectionError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.DisconnectionError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a DisconnectionError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    



*class* DiscoveryError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.DiscoveryError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a DiscoveryError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* InvalidRequestError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.InvalidRequestError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a InvalidRequestError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* LowLevelError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.LowLevelError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a LowLevelError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* ResolutionError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.ResolutionError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a ResolutionError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* WrongTypeError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.WrongTypeError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a WrongTypeError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    


*class* OtherError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.OtherError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a OtherError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    

*class* SecurityError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.SecurityError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a SecurityError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    


*class* TimeoutError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.TimeoutError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a TimeoutError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    

*class* NoResultReceivedError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.NoResultReceivedError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a NoResultReceivedError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    
    

*class* SubscriptionError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.SubscriptionError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a SubscriptionError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    

*class* UnexpectedError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.UnexpectedError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a UnexpectedError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    
    

*class* UnknownHandleError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.UnknownHandleError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a UnknownHandleError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    
    
    
    

*class* UnsupportedError
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.errors.UnsupportedError
    
    
    * Methods:

        .. method:: __init__(status)
        
            Create a UnsupportedError.
            
            :param status: The status object that caused the error to be raised.
            :type status: :class:`~pyuaf.util.Status`
             
    * Attributes:
  
        .. attribute:: status
        
            The :class:`~pyuaf.util.Status` object that caused the error to be raised.
    
    