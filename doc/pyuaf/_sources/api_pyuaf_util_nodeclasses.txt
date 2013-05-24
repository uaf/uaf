

``pyuaf.util.nodeclasses``
====================================================================================================

.. automodule:: pyuaf.util.nodeclasses

    This module defines the different classes of nodes (e.g. an Object node, an ObjectType node, 
    a Variable node, ...).
        

    * Attributes:

        .. autoattribute:: pyuaf.util.nodeclasses.Unspecified
        
        .. autoattribute:: pyuaf.util.nodeclasses.Object
        
        .. autoattribute:: pyuaf.util.nodeclasses.Variable
        
        .. autoattribute:: pyuaf.util.nodeclasses.Method
        
        .. autoattribute:: pyuaf.util.nodeclasses.ObjectType
        
        .. autoattribute:: pyuaf.util.nodeclasses.VariableType
        
        .. autoattribute:: pyuaf.util.nodeclasses.ReferenceType
        
        .. autoattribute:: pyuaf.util.nodeclasses.DataType
        
        .. autoattribute:: pyuaf.util.nodeclasses.View
        
        
    * Functions:
    
        
        .. autofunction:: pyuaf.util.nodeclasses.toString(nodeClass)
        
            Get a string representation of the node class.
        
            :param nodeClass: The node class, e.g. :py:attr:`pyuaf.util.nodeclasses.Variable`.
            :type  nodeClass: ``int``
            :return: The name of the node class, e.g. 'Variable'.
            :rtype:  ``str``

            
