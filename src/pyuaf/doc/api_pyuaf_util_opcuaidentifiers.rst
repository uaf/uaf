


``pyuaf.util.opcuaidentifiers``
====================================================================================================

.. automodule:: pyuaf.util.opcuaidentifiers

    This module contains a very long list of (more than 5000!) numerical identifiers, as defined
    by the OPC UA standard. 
    
    This list is not shipped with the UAF, it is generated from the stack include files.
    
    The list is way too long to document here, so you are referred to the OPC UA specification
    documents.
    
    All identifiers start with an ``OpcUaId_`` prefix.
    
    Here are some examples:

        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_BaseDataType
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_Number
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_Integer
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_UInt32
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_VariableTypeNode
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_EUInformation
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_ConditionType_Disable
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_ExclusiveDeviationAlarmType
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_RootFolder
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_ObjectsFolder
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_TypesFolder
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_ViewsFolder
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_ServerType_VendorServerInfo
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_Server_NamespaceArray
        .. autoattribute:: pyuaf.util.opcuaidentifiers.OpcUaId_Server_ServerArray


    And here's a little script you can use to print all identifiers to the standard out ("stdout",
    e.g. the Windows DOS Prompt or the Linux shell) or write them to a file:
    
        .. literalinclude:: /../../../examples/pyuaf/util/how_to_print_all_opcua_identifiers.py
