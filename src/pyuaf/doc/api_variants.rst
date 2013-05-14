.. _note-variants:

A note on dynamic data types
====================================================================================================


The type of a data value (such as a numerical value) is often not "static", but it depends
on the circumstances. For example, if you read a variable via OPC UA, the type of the resulting data 
could be an unsigned 32-bit numerical value, or a floating point value, or even a LocalizedText or
something else. It all depends on the type of the variable you are reading.

In PyUAF, the type of the value you process (e.g. read or write or monitor or whatever) is 
therefore not always known in advance. 

The type of the instance can be:
  - None (for a NULL value)
  - a primitive:
     - :class:`pyuaf.util.primitives.Boolean`
     - :class:`pyuaf.util.primitives.SByte`
     - :class:`pyuaf.util.primitives.Byte`
     - :class:`pyuaf.util.primitives.UInt16`
     - :class:`pyuaf.util.primitives.Int16`
     - :class:`pyuaf.util.primitives.UInt32`
     - :class:`pyuaf.util.primitives.Int32`
     - :class:`pyuaf.util.primitives.UInt64`
     - :class:`pyuaf.util.primitives.Int64`
     - :class:`pyuaf.util.primitives.Float`
     - :class:`pyuaf.util.primitives.Double`
     - a ``str`` (UTF-8 encoded) or a ``unicode`` object
  - a non-primitive like:
     - :class:`pyuaf.util.NodeId`
     - :class:`pyuaf.util.ExpandedNodeId`
     - :class:`pyuaf.util.QualifiedName`
     - :class:`pyuaf.util.LocalizedText`
  - or an array of any of the above types (in other words: a list of instances of the same data type).


So suppose `x` is the instance, and we expect it to be a NULL value, or an unsigned 32-bit number, 
or an array of unsigned 32-bit numbers. Then we can process the instance like this::

    if x is None:
        print("NULL value!")
    elif isinstance(x, pyuaf.util.primitives.UInt32):
        print("The value is %d" %x.value)
    elif isinstance(x, list):
        # In an OPC UA array, all elements have the same type. 
        # So if we check the type of the first item, we don't have to check the type of the subsequent items.
        if len(x) == 0:
            print("The value is an empty array!")
        else:
            if isinstance(x[0], pyuaf.util.primitives.UInt32):
                print("The value is an array of the following UInt32 items:")
                for item in x:
                    print(" - element value: %d" %item.value)
            else:
                print("The value is an array of the wrong type (%s)!" %type(item))
    else:
        print("The value is of the wrong type (%s)!" %type(x))

        
Multiple values of a dynamic data type may be contained in a native Python container, but sometimes they 
may be presented to you as a :class:`pyuaf.util.VariantVector`.

