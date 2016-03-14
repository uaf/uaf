
``pyuaf.util.structurefielddatatypes``
====================================================================================================

.. automodule:: pyuaf.util.structurefielddatatypes

    This module defines the datatypes of the fields of structures. 
    


    * Attributes:
    
    
        .. autoattribute:: pyuaf.util.structurefielddatatypes.Variant
        
            The field is a built-in type (a Variant).
            
            .. seealso:: :ref:`note-variants`.
    
        .. autoattribute:: pyuaf.util.structurefielddatatypes.GenericStructure
        
            The field is a :class:`~pyuaf.util.GenericStructureValue`.
    
        .. autoattribute:: pyuaf.util.structurefielddatatypes.GenericStructureArray
        
            The field is a ``list`` of :class:`~pyuaf.util.GenericStructureValue` instances
            (or a :class:`~pyuaf.util.GenericStructureVector`, which is basically the same).
            
        .. autoattribute:: pyuaf.util.structurefielddatatypes.GenericUnion
        
            The field is a :class:`~pyuaf.util.GenericUnionValue`.
    
        .. autoattribute:: pyuaf.util.structurefielddatatypes.GenericUnionArray
        
            The field is a ``list`` of :class:`~pyuaf.util.GenericUnionValue` instances
            (or a :class:`~pyuaf.util.GenericUnionVector`, which is basically the same).
            
        .. autoattribute:: pyuaf.util.structurefielddatatypes.GenericOptionSet
        
            The field is a GenericOptionSet.
    
        .. autoattribute:: pyuaf.util.structurefielddatatypes.GenericUnionArray
        
            The field is a GenericOptionSetArray.
    
    
        .. autoattribute:: pyuaf.util.structurefielddatatypes.Empty
        
            The field is empty.
            
    * Functions:
    
    
        .. autofunction:: pyuaf.util.structurefielddatatypes.toString(datatype)
        
            Get a string representation of the StructureFieldDataType.
        
            :param datatype: The datatype, 
                             e.g. :py:attr:`~pyuaf.util.structurefielddatatypes.GenericUnionArray`.
            :type  datatype: ``int``
            :return: The name of the datatype, e.g. 'GenericUnionArray'.
            :rtype:  ``str``
        
        