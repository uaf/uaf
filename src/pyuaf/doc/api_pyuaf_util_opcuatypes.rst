

``pyuaf.util.opcuatypes``
====================================================================================================

.. automodule:: pyuaf.util.opcuatypes

    This module defines the types of OPC UA objects such as primitives (UInt32, Float, ...), 
    NodeIds, QualifiedNames, .... 


    * Attributes:
    
    
        .. autoattribute:: pyuaf.util.opcuatypes.Null
        .. autoattribute:: pyuaf.util.opcuatypes.Boolean
        .. autoattribute:: pyuaf.util.opcuatypes.SByte
        .. autoattribute:: pyuaf.util.opcuatypes.Byte
        .. autoattribute:: pyuaf.util.opcuatypes.Int16
        .. autoattribute:: pyuaf.util.opcuatypes.UInt16
        .. autoattribute:: pyuaf.util.opcuatypes.Int32
        .. autoattribute:: pyuaf.util.opcuatypes.UInt32
        .. autoattribute:: pyuaf.util.opcuatypes.Int64
        .. autoattribute:: pyuaf.util.opcuatypes.UInt64
        .. autoattribute:: pyuaf.util.opcuatypes.Float
        .. autoattribute:: pyuaf.util.opcuatypes.Double
        .. autoattribute:: pyuaf.util.opcuatypes.String
        .. autoattribute:: pyuaf.util.opcuatypes.DateTime
        .. autoattribute:: pyuaf.util.opcuatypes.Guid
        .. autoattribute:: pyuaf.util.opcuatypes.ByteString
        .. autoattribute:: pyuaf.util.opcuatypes.XmlElement
        .. autoattribute:: pyuaf.util.opcuatypes.NodeId
        .. autoattribute:: pyuaf.util.opcuatypes.ExpandedNodeId
        .. autoattribute:: pyuaf.util.opcuatypes.StatusCode
        .. autoattribute:: pyuaf.util.opcuatypes.QualifiedName
        .. autoattribute:: pyuaf.util.opcuatypes.LocalizedText
        .. autoattribute:: pyuaf.util.opcuatypes.ExtensionObject
        .. autoattribute:: pyuaf.util.opcuatypes.DataValue
        .. autoattribute:: pyuaf.util.opcuatypes.Variant
        .. autoattribute:: pyuaf.util.opcuatypes.DiagnosticInfo
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.opcuatypes.toString(type)
        
            Get a string representation of the OPC UA type.
        
            :param type: The type, e.g. :py:attr:`pyuaf.util.opcuatypes.UInt64`.
            :type  type: ``int``
            :return: The name of the type, e.g. 'UInt64'.
            :rtype:  ``str``

