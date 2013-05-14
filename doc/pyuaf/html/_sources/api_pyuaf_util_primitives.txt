
``pyuaf.util.primitives``
====================================================================================================

.. automodule:: pyuaf.util.primitives

    This module defines some primitive data types (since Python does not differentiate clearly 
    between, for example, an UInt32 and an Int16 value.




*class* Boolean
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Boolean


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Boolean value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Boolean`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Boolean`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Boolean"``.
            
            :return: ``"Boolean"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            A bool value.
    
    

*class* SByte
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.SByte


    * Methods:

        .. method:: __init__([value])
    
            Construct a new SByte value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.SByte`.
            
            :return: :attr:`pyuaf.util.opcuatypes.SByte`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"SByte"``.
            
            :return: ``"SByte"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.
    


*class* Byte
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Byte


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Byte value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Byte`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Byte`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Byte"``.
            
            :return: ``"Byte"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* Int16
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Int16


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Int16 value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Int16`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Int16`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Int16"``.
            
            :return: ``"Int16"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* UInt16
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.UInt16


    * Methods:

        .. method:: __init__([value])
    
            Construct a new UInt16 value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.UInt16`.
            
            :return: :attr:`pyuaf.util.opcuatypes.UInt16`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"UInt16"``.
            
            :return: ``"UInt16"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* Int32
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Int32


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Int32 value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Int32`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Int32`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Int32"``.
            
            :return: ``"Int32"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* UInt32
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.UInt32


    * Methods:

        .. method:: __init__([value])
    
            Construct a new UInt32 value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.UInt32`.
            
            :return: :attr:`pyuaf.util.opcuatypes.UInt32`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"UInt32"``.
            
            :return: ``"UInt32"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* Int64
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Int64


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Int64 value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Int64`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Int64`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Int64"``.
            
            :return: ``"Int64"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* UInt64
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.UInt64


    * Methods:

        .. method:: __init__([value])
    
            Construct a new UInt64 value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.UInt64`.
            
            :return: :attr:`pyuaf.util.opcuatypes.UInt64`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"UInt64"``.
            
            :return: ``"UInt64"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            An ``int`` value.


*class* Float
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Float


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Float value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Float`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Float`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Float"``.
            
            :return: ``"Float"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            A float value.

*class* Double
----------------------------------------------------------------------------------------------------

.. autoclass:: pyuaf.util.primitives.Double


    * Methods:

        .. method:: __init__([value])
    
            Construct a new Double value with an optional initial value.
    
        .. method:: type()
        
            Get the type of the value, in this case :attr:`pyuaf.util.opcuatypes.Double`.
            
            :return: :attr:`pyuaf.util.opcuatypes.Double`
            :rtype: ``int``
            
        .. method:: typeName()
        
            Get the name of the type of the value, in this case ``"Double"``.
            
            :return: ``"Double"``
            :rtype: ``str``
               
    
    * Attributes:
  
        .. attribute:: value
        
            A float value.
