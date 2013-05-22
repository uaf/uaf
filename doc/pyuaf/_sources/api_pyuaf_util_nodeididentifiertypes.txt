

``pyuaf.util.nodeididentifiertypes``
====================================================================================================

.. automodule:: pyuaf.util.nodeididentifiertypes

    This module defines the types of NodeId identifiers. 
    
    A NodeId is essentially an identifier defined by a namespace.  The identifier 
    (:class:`pyuaf.util.NodeIdIdentifier`) can be represented by a string, a numerical value, 
    a GUID (Globally Unique ID) or an Opaque value. These possible types are defined within this 
    module. 


    * Attributes:
    

        .. autoattribute:: pyuaf.util.nodeididentifiertypes.Identifier_Numeric
        
            The NodeId identifier is a numerical value.
        
        .. autoattribute:: pyuaf.util.nodeididentifiertypes.Identifier_String
        
            The NodeId identifier is a string.
        
        .. autoattribute:: pyuaf.util.nodeididentifiertypes.Identifier_Guid
        
            The NodeId identifier is a globally unique identifier (GUID).
        
        .. autoattribute:: pyuaf.util.nodeididentifiertypes.Identifier_Opaque
        
            The NodeId identifier is an opaque value.
    
    
    * Functions:
    
    
        .. autofunction:: pyuaf.util.nodeididentifiertypes.toString(type)
        
            Get a string representation of the NodeIdIdentifier type.
        
            :param type: The type, e.g. :py:attr:`pyuaf.util.nodeididentifiertypes.Identifier_String`.
            :type  type: ``int``
            :return: The name of the type, e.g. 'String'.
            :rtype:  ``str``
