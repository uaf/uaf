``pyuaf.util``
====================================================================================================


.. automodule:: pyuaf.util



*class* Address
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.Address


    An Address points to a node within an server address space by means of an
    absolute address (an ExpandedNodeId) or by means of a relative address (a path relative to
    another address).
    
    An "address" is a term defined by the UAF, and *not* by the OPC UA standard. It's basically
    a union class that holds the information to identify a node within an address space.
    Several addresses can all point to the same node.
    
    A relative address may point to other relative addresses. More formally, the starting
    point of an Address based on a relative path, may also be an Address based on a 
    relative path in turn. This way you can define large and complex hierarchies of relative 
    addresses, with just a single absolute address (based on an ExpandedNodeId) as the starting 
    point.


    * Methods:

        .. automethod:: pyuaf.util.Address.__init__
    
            Construct a new Address by providing either
            
               * an :class:`~pyuaf.util.ExpandedNodeId`
               
               * another :class:`~pyuaf.util.Address` (the starting point) and a 
                 :class:`~pyuaf.util.RelativePath` (the path).
            
            Usage example:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util import Address, NodeId, ExpandedNodeId, RelativePathElement, QualifiedName
                
                >>> # the following ways of constructing a Address are possible:
                >>> address0 = Address( ExpandedNodeId("someId", "someNsUri", "someServerUri") )
                >>> address1 = Address( NodeId("someId", "someNsUri"), "someServerUri" )
                >>> address2 = Address( address0, [RelativePathElement(QualifiedName("someName", "someNsUri"))] )
                >>> address3 = Address( address1, [RelativePathElement(QualifiedName("someOtherName", 3))] )
            
            
            
        .. automethod:: pyuaf.util.Address.isExpandedNodeId
        
            Check if the address is defined as an ExpandedNodeId.
            
            :return: True if the address is based on an :class:`~pyuaf.util.ExpandedNodeId` 
                     (and you're allowed to call :meth:`~pyuaf.util.Address.getExpandedNodeId`), False if not.
            :rtype:  bool


        .. automethod:: pyuaf.util.Address.isRelativePath
        
            Check if the address is defined as a RelativePath.
            
            :return: True if the address is based on a :class:`~pyuaf.util.RelativePath`
                     and another :class:`~pyuaf.util.Address`  
                     (and you're allowed to call :meth:`~pyuaf.util.Address.getStartingAddress` 
                     and :meth:`~pyuaf.util.Address.getRelativePath`), False if not.
            :rtype:  bool

            
        .. automethod:: pyuaf.util.Address.getExpandedNodeId
        
            Get the ExpandedNodeId in case :meth:`~pyuaf.util.Address.isExpandedNodeId` returns True.
            
            :return: The ExpandedNodeId corresponding with this Address.
            :rtype:  :class:`~pyuaf.util.ExpandedNodeId`

            
        .. automethod:: pyuaf.util.Address.getRelativePath
        
            Get the RelativePath in case :meth:`~pyuaf.util.Address.isRelativePath` returns True.
            
            :return: The RelativePath corresponding with this Address, as a ``tuple`` 
                     of :class:`~pyuaf.util.RelativePathElement`.

            
        .. automethod:: pyuaf.util.Address.getStartingAddress
        
            Get a pointer (not a copy of the actual object itself!) to the starting address in case 
            :meth:`~pyuaf.util.Address.isRelativePath` returns True.
            
            :return: A reference to the starting address.
            :rtype:  :class:`~pyuaf.util.Address`




*class* ApplicationDescription
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.ApplicationDescription

    An ApplicationDescription instance describes a Server or Client or ClientAndServer, or a
    DiscoveryServer.


    * Methods:

        .. automethod:: pyuaf.util.ApplicationDescription.__init__
    
            Construct a new ApplicationDescription.
    
        .. automethod:: pyuaf.util.ApplicationDescription.isEmpty
    
            Is this a valid application description or an empty one?
            
            :rtype: ``bool``


    * Attributes:
  
  
        .. autoattribute:: pyuaf.util.ApplicationDescription.applicationUri
        
            The application URI as a string (type ``str``).
    
        .. autoattribute:: pyuaf.util.ApplicationDescription.productUri
        
            The product URI as a string (type ``str``).
    
        .. autoattribute:: pyuaf.util.ApplicationDescription.applicationName
        
            The application name as a localized text (type :class:`~pyuaf.util.LocalizedText`).
    
        .. autoattribute:: pyuaf.util.ApplicationDescription.applicationType
        
            The application type as an int (as defined in :mod:`pyuaf.util.applicationtypes`).
    
        .. autoattribute:: pyuaf.util.ApplicationDescription.gatewayServerUri
        
             The gateway server URI as a string (type ``str``).
    
        .. autoattribute:: pyuaf.util.ApplicationDescription.discoveryProfileUri
        
             The discovery profile URI as a string (type ``str``).
    
        .. autoattribute:: pyuaf.util.ApplicationDescription.discoveryUrls
        
             The discovery URLs as a list of strings (type :class:`~pyuaf.util.StringVector`).
    



*class* ApplicationDescriptionVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.ApplicationDescriptionVector

    An ApplicationDescriptionVector is a container that holds elements of type 
    :class:`pyuaf.util.ApplicationDescription`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.util.ApplicationDescription`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import ApplicationDescriptionVector, ApplicationDescription
        
        >>> # construct a ApplicationDescriptionVector without elements:
        >>> descriptions = ApplicationDescriptionVector()
        
        >>> noOfElements = len(descriptions) # will be 0
        
        >>> descriptions.append(ApplicationDescription())
        
        >>> noOfElements = len(descriptions) # will be 1
        
        >>> descriptions.resize(4)
        
        >>> noOfElements = len(descriptions) # will be 4
        
        >>> description0 = descriptions[0]
        
        >>> # you may construct an ApplicationDescriptionVector from a regular Python list:
        >>> otherDescriptions = ApplicationDescriptionVector( [ApplicationDescription(), ApplicationDescription()] )


*class* BrowsePath
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.BrowsePath

    A BrowsePath holds a path from a resolved starting node (an ExpandedNodeId) to another node 
    within the address space.


    * Methods:

        .. method:: __init__([startingExpandedNodeId [, relativePath]])
    
            Construct a new BrowsePath.
            
            You may optionally provide a starting point for the browse path 
            (a :class:`pyuaf.util.ExpandedNodeId`) and optionally provide a relative path
            (which is a :class:`~pyuaf.util.RelativePath`, resembling a ``list`` of 
            :class:`~pyuaf.util.RelativePathElement`).


    * Attributes:
  
  
        .. autoattribute:: pyuaf.util.BrowsePath.startingExpandedNodeId
        
            The starting point (as an :class:`~pyuaf.util.ExpandedNodeId`)) of the relative path.
    
        .. autoattribute:: pyuaf.util.BrowsePath.relativePath
        
             The relative path as a list of qualified names 
             The type of this attribute is :class:`~pyuaf.util.RelativePath`, 
             which resembles a ``list`` of :class:`~pyuaf.util.RelativePathElement`.



*class* DataChangeFilter
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.DataChangeFilter

    A DataChangeFilter specifies a deadband filter for monitored data items.
    
    
    * Methods:

        .. automethod:: pyuaf.util.DataChangeFilter.__init__
            
            Create a default DataChangeFilter instance.
            
            Defaults:
              
               - :attr:`~pyuaf.util.DataChangeFilter.trigger`: :attr:`~pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValue`
               - :attr:`~pyuaf.util.DataChangeFilter.deadBandType`: :attr:`~pyuaf.util.DataChangeFilter.DeadBandType_None`
               - :attr:`~pyuaf.util.DataChangeFilter.deadBandValue`: 0.0

        .. automethod:: pyuaf.util.DataChangeFilter.__str__
            
            Get a string representation.


    * Class attributes:

        * for the dead band type:

            .. autoattribute:: pyuaf.util.DataChangeFilter.DeadBandType_None
    
                An ``int`` identifying the kind of deadband: in this case no deadband at all!
    
            .. autoattribute:: pyuaf.util.DataChangeFilter.DeadBandType_Absolute
    
                An ``int`` identifying the kind of deadband: in this case an absolute deadband.
    
            .. autoattribute:: pyuaf.util.DataChangeFilter.DeadBandType_Percent
    
                An ``int`` identifying the kind of deadband: in this case a relative deadband 
                (in percent).

        * for the data change trigger:

            .. autoattribute:: pyuaf.util.DataChangeFilter.DataChangeTrigger_Status
    
                An ``int`` identifying the kind of trigger: in this case trigger when the status 
                changes!
    
            .. autoattribute:: pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValue
    
                An ``int`` identifying the kind of trigger: in this case trigger when the status 
                or the value changes!
    
            .. autoattribute:: pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValueTimestamp
    
                An ``int`` identifying the kind of trigger: in this case trigger when the status 
                or the value or the timestamp changes!


    * Attributes:
    
        .. autoattribute:: pyuaf.util.DataChangeFilter.trigger
        
            The kind of trigger, as one of these ``int`` values:
            :attr:`~pyuaf.util.DataChangeFilter.DataChangeTrigger_Status` 
            or :attr:`~pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValue` 
            or :attr:`~pyuaf.util.DataChangeFilter.DataChangeTrigger_StatusValueTimestamp`.
    
        .. autoattribute:: pyuaf.util.DataChangeFilter.deadBandType
        
            The type of dead band, as one of these ``int`` values:
            :attr:`~pyuaf.util.DataChangeFilter.DeadBandType_None` 
            or :attr:`~pyuaf.util.DataChangeFilter.DeadBandType_Absolute` 
            or :attr:`~pyuaf.util.DataChangeFilter.DeadBandType_Percent`.

        .. autoattribute:: pyuaf.util.DataChangeFilter.deadBandValue
        
            Value of the deadband, as a ``float``.






*class* EndpointDescription
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.EndpointDescription

    An EndpointDescription instance describes an endpoint of a Server (as returned during the
    discovery process, so that the client can choose an endpoint and connect to it).


    * Methods:

        .. automethod:: pyuaf.util.EndpointDescription.__init__
    
            Construct a new EndpointDescription.
    
        .. automethod:: pyuaf.util.EndpointDescription.isEmpty
    
            Is this a valid endpoint description or an empty one?
            
            :rtype: ``bool``


    * Attributes:
  
  
        .. autoattribute:: pyuaf.util.EndpointDescription.endpointUrl
        
            The endpoint URL (type ``str``).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.server
        
            The application description of the server (type :class:`~pyuaf.util.ApplicationDescription`).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.serverCertificate
        
            The server certificate (as a byte string).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.securityMode
        
            The message security mode (e.g. :attr:`pyuaf.util.messagesecuritymodes.Mode_SignAndEncrypt`)
            (an ``int``, as defined in :mod:`pyuaf.util.messagesecuritymodes`).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.securityPolicyUri
        
            The security policy URI (e.g. :attr:`pyuaf.util.securitypolicies.UA_Basic128`),
            (an ``int``, as defined in :mod:`pyuaf.util.securitypolicies`).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.userIdentityTokens
        
             The allowed user identity token policies (as a :class:`pyuaf.util.UserTokenPolicyVector`).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.transportProfileUri
        
             The transport profile URI (type :class:`~pyuaf.util.StringVector`).
    
        .. autoattribute:: pyuaf.util.EndpointDescription.securityLevel
        
             The security level (type ``int``).
    
    
    


*class* EndpointDescriptionVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.EndpointDescriptionVector

    An EndpointDescriptionVector is a container that holds elements of type 
    :class:`pyuaf.util.EndpointDescription`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`pyuaf.util.EndpointDescription`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import EndpointDescriptionVector, EndpointDescription
        
        >>> # construct a EndpointDescriptionVector without elements:
        >>> descriptions = EndpointDescriptionVector()
        
        >>> noOfElements = len(descriptions) # will be 0
        
        >>> descriptions.append(EndpointDescription())
        
        >>> noOfElements = len(descriptions) # will be 1
        
        >>> descriptions.resize(4)
        
        >>> noOfElements = len(descriptions) # will be 4
        
        >>> description0 = descriptions[0]
        
        >>> # you may construct an EndpointDescriptionVector from a regular Python list:
        >>> otherDescriptions = EndpointDescriptionVector( [EndpointDescription(), EndpointDescription()] )
        
    



*class* EventFilter
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.EventFilter

    An EventFilter selects and filters the events to be received by a client.
    
    
    * Methods:

        .. automethod:: pyuaf.util.EventFilter.__init__
            
            Create a default EventFilter instance.

        .. automethod:: pyuaf.util.EventFilter.__str__
            
            Get a string representation.

    * Attributes:
    
        .. autoattribute:: pyuaf.util.EventFilter.selectClauses
        
            The select clauses, as a :class:`~pyuaf.util.SimpleAttributeOperandVector`.




*class* ExpandedNodeId
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.ExpandedNodeId


    An ExpandedNodeId fully identifies the node by means of a NodeId part, and a part containing
    the serverIndex and/or serverUri of the server hosting the node.


    * Methods:

        .. automethod:: pyuaf.util.ExpandedNodeId.__init__
    
            Construct a new ExpandedNodeId in one of the following ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util import ExpandedNodeId, NodeId
        
                >>> # suppose we have a node with the following properties:
                >>> nodeIdStringIdentifier = "myStringIdentifier"
                >>> nameSpaceUri           = "myNameSpaceUri"
                >>> nameSpaceIndex         = 3
                >>> serverUri              = "myServerUri"
                >>> serverIndex            = 2
        
                >>> # and one with the same namespace and server properties, but with a different identifier:
                >>> nodeIdNumericIdentifier = 1234
                
                >>> # then these ExpandedNodeIds all point to the nodes:
                >>> exp0  = ExpandedNodeId(nodeIdStringIdentifier  , nameSpaceUri   , serverUri   )
                >>> exp1  = ExpandedNodeId(nodeIdStringIdentifier  , nameSpaceUri   , serverIndex )
                >>> exp2  = ExpandedNodeId(nodeIdStringIdentifier  , nameSpaceUri   , serverUri   , serverIndex)
                >>> exp3  = ExpandedNodeId(nodeIdStringIdentifier  , nameSpaceIndex , serverUri   )
                >>> exp4  = ExpandedNodeId(nodeIdStringIdentifier  , nameSpaceIndex , serverIndex )
                >>> exp5  = ExpandedNodeId(nodeIdStringIdentifier  , nameSpaceIndex , serverUri   , serverIndex)
                >>> exp6  = ExpandedNodeId(nodeIdNumericIdentifier , nameSpaceUri   , serverUri   )
                >>> exp7  = ExpandedNodeId(nodeIdNumericIdentifier , nameSpaceUri   , serverIndex )
                >>> exp8  = ExpandedNodeId(nodeIdNumericIdentifier , nameSpaceUri   , serverUri   , serverIndex)
                >>> exp9  = ExpandedNodeId(nodeIdNumericIdentifier , nameSpaceIndex , serverUri   )
                >>> exp10 = ExpandedNodeId(nodeIdNumericIdentifier , nameSpaceIndex , serverIndex )
                >>> exp11 = ExpandedNodeId(nodeIdNumericIdentifier , nameSpaceIndex , serverUri   , serverIndex)
                
                >>> # you can also define the NodeId first and provide this + serverIndex and/or serverUri 
                >>> nodeId = NodeId(nodeIdStringIdentifier, nameSpaceUri, nameSpaceIndex)
                >>> exp12 = ExpandedNodeId(nodeId, serverUri   )
                >>> exp13 = ExpandedNodeId(nodeId, serverIndex )
                >>> exp14 = ExpandedNodeId(nodeId, serverUri   , serverIndex)

    
        .. automethod:: pyuaf.util.ExpandedNodeId.hasServerIndex
        
            Check if a server index was given.
            
            :return: True if a serverIndex has been defined, False if not.
            :rtype:  ``bool``

    
        .. automethod:: pyuaf.util.ExpandedNodeId.hasServerUri
        
            Check if a non-empty server URI was given.
            
            :return: True if this ExpandedNodeId contains a non-empty server URI, False if not.
            :rtype:  ``bool``

    
        .. automethod:: pyuaf.util.ExpandedNodeId.serverIndex
        
            Get the server index of the ExpandedNodeId.
          
            This function will always return an ``int``, so call hasServerIndex() to see if it's a
            valid one.
            
            :return: The server index.
            :rtype:  ``int``

    
        .. automethod:: pyuaf.util.ExpandedNodeId.serverUri
        
            Get the server URI of the ExpandedNodeId.
          
            This function will always return a string, so call hasServerUri() to see if it's a
            valid one.
            
            :return: The server URI.
            :rtype:  ``str``

    
        .. automethod:: pyuaf.util.ExpandedNodeId.nodeId()
        
            Get the NodeId part of the ExpandedNodeId.
            
            :return: The NodeId part.
            :rtype:  :class:`pyuaf.util.NodeId`



*class* ExpandedNodeIdVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.ExpandedNodeIdVector

    A ExpandedNodeIdVector is a container that holds elements of type 
    :class:`pyuaf.util.ExpandedNodeId`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.util.ExpandedNodeId`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import ExpandedNodeIdVector, ExpandedNodeId
        
        >>> # construct a ExpandedNodeIdVector without elements:
        >>> vec = ExpandedNodeIdVector()
        
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(ExpandedNodeId("some id", "http://Some/Namespace/URI", "Some:Server:URI"))
        
        >>> noOfElements = len(vec) # will be 1
        
        >>> if vec[0].hasServerUri():
        ...    serverUri = vec[0].serverUri()
        ... else:
        ...    serverUri = None
        
        >>> vec.resize(2)
        
        >>> noOfElements = len(vec) # will be 2
        
        >>> # you may construct a ExpandedNodeIdVector from a regular Python list:
        >>> someOtherVec = ExpandedNodeIdVector( [ ExpandedNodeId("id 0", "MyNamespace", "serverX"), 
        ...                                        ExpandedNodeId("id 1", "MyNamespace", "serverY") ] )


    


*class* LocalizedText
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.LocalizedText


    A LocalizedText is text with a locale attached.


    * Methods:

        .. automethod:: pyuaf.util.LocalizedText.__init__([locale[, text]])
    
            Construct a new LocalizedText in one of the following ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util import LocalizedText
                
                >>> # the following ways of constructing a QualifiedName are possible:
                >>> lText0 = LocalizedText()                        # incomplete, no information given!
                >>> lText1 = LocalizedText("en", "My English Text") # OK
                >>> lText2 = LocalizedText("", "My Text")           # OK (no specific locale given)
                
                >>> # strings are assumed to be UTF-8 encoded!
                >>> unicodeObject = u"40\u00B0 Celsius ist eine hei\u00DFe Temperatur!"
                >>> lText3 = LocalizedText("de", unicodeObject.encode("UTF-8"))

    
        .. automethod:: pyuaf.util.LocalizedText.text
        
            Get the text part of the LocalizedText, as an UTF-8 encoded string.
            
            :return: The text part.
            :rtype:  ``str``
    
    
        .. automethod:: pyuaf.util.LocalizedText.locale
        
            Get the locale part of the LocalizedText.
            
            :return: The locale part (e.g. "en", "de", "nl", "", ...).
            :rtype:  ``str``
    
    
        .. automethod:: pyuaf.util.LocalizedText.toFullString
        
            Get a string of the locale part + the text part.
            
            :return: The localized text.
            :rtype:  ``str``




*class* LoggingInterface
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.LoggingInterface

    A LoggingInterface interface class can be implemented to receive log messages.
    
    For instance, the pyuaf.client.Client class is implementing this interface.
    As a regular UAF user, you should not have to deal with this interface directly.
    
    * Methods:

        .. automethod:: pyuaf.util.LoggingInterface.__dispatch_logMessageReceived__(message)

            A new log message was received.

            :param message: The log message that was received.
            :type  message: :class:`pyuaf.util.LogMessage`



*class* LogMessage
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.LogMessage

    A LogMessage instance contains a timestamp, a log level, an informative message, etc.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> import time
        
        >>> # normally you receive log messages from a pyuaf.client.Client instance,
        >>> # but in this case we'll create a log message manually:
        >>> msg = pyuaf.util.LogMessage(pyuaf.util.loglevels.Debug, 
        ...                             "MyApp", 
        ...                             "MyLogger", 
        ...                             "Something has happened,\n" 
        ...                             + "requiring a big multi-line description!")
        
        >>> niceLocalTimeString =  time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime(msg.ctime))
        >>> niceLocalTimeString += ".%.3d" %msg.msec
        
        >>> stringToWrittenToFile  = "New log message:"
        >>> stringToWrittenToFile += " - time received    : %s" %niceLocalTimeString
        >>> stringToWrittenToFile += " - application name : %s" %msg.applicationName
        >>> stringToWrittenToFile += " - logger name      : %s" %msg.loggerName
        >>> stringToWrittenToFile += " - level            : %d = %s" %(msg.level, pyuaf.util.loglevels.toString(msg.level))
        >>> for line in msg.message.splitlines():
        ...     stringToWrittenToFile += " - message lines    : %s" %line
        
        >>> theWholeMessageAtOnce = str(msg)
        

    * Methods:

        .. automethod:: pyuaf.util.LogMessage.__init__(level, applicationName, loggerName, message)
    
            Construct a new LogMessage.
            
            The 'ctime' timestamp will be set to the construction time.
            
    
        .. automethod:: pyuaf.util.LogMessage.__str__
    
            Get a formatted string representation of the log message.


    * Attributes:
  
  
        .. autoattribute:: pyuaf.util.LogMessage.ctime
        
            The timestamp as a 64-bit number (the "c-time") expressing the seconds that passed
            since the epoch, as an ``int``.
  
        .. autoattribute:: pyuaf.util.LogMessage.msec
        
            The number of milliseconds past the ctime, as an ``int``.
  
        .. autoattribute:: pyuaf.util.LogMessage.level
        
            The log level as an ``int`` (as defined in :mod:`pyuaf.util.loglevels`).
    
        .. autoattribute:: pyuaf.util.LogMessage.applicationName
        
            The name of the application that owns the logger (type ``str``).
    
        .. autoattribute:: pyuaf.util.LogMessage.loggerName
        
            The name of the logger that produced the log message (type ``str``).
    
        .. autoattribute:: pyuaf.util.LogMessage.message
        
            The actual informative message to be logged (type ``str``).
    
    



*class* Mask
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.Mask


    This is a boolean mask to mark items as 'set' (boolean True) or 'unset' (boolean False).
    
    The mask keeps track of the number of 'set' and 'unset' values. This means you can
    very efficiently call countSet() and countUnset().


    * Methods:

        .. automethod:: pyuaf.util.Mask.__init__([initialSize[, initialValue]])
    
            Construct a new Mask.
            
            The initial size can optionally be given. 
            If the initial size is given, also the initial value of all initial elements can be 
            given.
            
            :param initialSize: (Optional) Initial number of elements of the mask.
            :type  initialSize: ``int``
            :param initialValue: (Optional) Value (True or False) of the initial elements.
            :type  initialValue: ``bool``
                
                
    
        .. automethod:: pyuaf.util.Mask.resize(newSize)
        
            Resize the mask.
            
            :param newSize: The size the mask should be having.
            :type  newSize: ``int``
    
    
        .. automethod:: pyuaf.util.Mask.size
        
            The current size of the mask.
            
            :return: The current number of elements.
            :rtype:  ``int``
    
    
        .. automethod:: pyuaf.util.Mask.setCount
        
            Get the number of 'set' elements.
            
            :return: The current number of 'set' elements.
            :rtype:  ``int``
    
    
        .. automethod:: pyuaf.util.Mask.unsetCount
        
            Get the number of 'unset' elements.
            
            :return: The current number of 'unset' elements.
            :rtype:  ``int``
    
    
        .. automethod:: pyuaf.util.Mask.set(i)
        
            Set the i'th mask item (i.e. make it True).
            
            :param i: The number of the item that should be 'set'.
            :type  i: ``int``
    
    
        .. automethod:: pyuaf.util.Mask.unset(i)
        
            Unset the i'th mask item (i.e. make it False).
            
            :param i: The number of the item that should be 'unset'.
            :type  i: ``int``
    
    
        .. automethod:: pyuaf.util.Mask.__and__(otherMask)
        
            Logically AND this mask with another mask element-wise.
            
            :param otherMask: The other mask.
            :type  otherMask: :class:`pyuaf.util.Mask`
            :return: A new mask, the logical AND result of the current one and the other one.
            :rtype:  :class:`pyuaf.util.Mask`





*class* NodeId
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.NodeId


    A NodeId identifies the node within an address space. It is not bound to a specific server
    (use an :class:`pyuaf.util.ExpandedNodeId` for that).


    * Methods:

        .. automethod:: pyuaf.util.NodeId.__init__
    
            Construct a NodeId.
            
            A NodeId should contain an identifier (e.g. a string or a numeric value) and 
            some information about the namespace (a namespace URI and/or a namespace index).
            
            Usage example:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util import NodeId
                
                >>> nodeId0 = NodeId()                                          # contains no information
                >>> nodeId1 = NodeId("myStringIdentifier", "myNameSpaceUri")    
                >>> nodeId2 = NodeId("myStringIdentifier", "myNameSpaceUri", 3) # 3 = namespace index
                >>> nodeId3 = NodeId("myStringIdentifier", 3)                   # 3 = namespace index
                >>> nodeId4 = NodeId(2345, "myNameSpaceUri")    
                >>> nodeId5 = NodeId(2345, "myNameSpaceUri", 3)                 # 2345 = numeric id, 3 = namespace index
                >>> nodeId6 = NodeId(2345, 3)                                   # 2345 = numeric id, 3 = namespace index
                

    
        .. automethod:: pyuaf.util.NodeId.hasNameSpaceUri
        
            Check if a non-empty namespace URI was given.
            
            :return: True if this NodeId contains a non-empty server URI, False if not.
            :rtype:  ``bool``
    
    
        .. automethod:: pyuaf.util.NodeId.hasNameSpaceIndex
        
            Check if a namespace index was given.
            
            :return: True if a namespaceIndex has been defined, False if not.
            :rtype:  ``bool``

    

        .. automethod:: pyuaf.util.NodeId.nameSpaceUri
        
            Get the namespace URI of the NodeId.
          
            This function will always return a string, so call hasNameSpaceUri() to see if it's a
            valid one.
            
            :return: The namespace URI.
            :rtype:  ``str``

    
        .. automethod:: pyuaf.util.NodeId.nameSpaceIndex
        
            Get the namespace index of the NodeId.
          
            This function will always return an ``int``, so call hasNameSpaceIndex() to see if it's
            a valid one.
            
            :return: The namespace index.
            :rtype:  ``int``

    
        .. automethod:: pyuaf.util.NodeId.identifier
        
            Get the NodeIdIdentifier part of the NodeId.
            
            :return: The NodeIdIdentifier part.
            :rtype:  :class:`pyuaf.util.NodeIdIdentifier`


    
        .. automethod:: pyuaf.util.NodeId.setNameSpaceUri(uri)
        
            Set the namespace URI of the NodeId.
            
            :param uri: The namespace URI.
            :type  uri:  ``str``

    
        .. automethod:: pyuaf.util.NodeId.setNameSpaceIndex(index)
        
            Set the namespace index of the NodeId.
            
            :param uri: The namespace index.
            :type  uri:  ``int``




*class* NodeIdIdentifier
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.NodeIdIdentifier


    A NodeIdIdentifier is the identifier part of a NodeId.
    

    * Methods:

        .. automethod:: pyuaf.util.NodeIdIdentifier.__init__
    
            Construct a NodeIdIdentifier by providing a string or a numeric value (or nothing at 
            all).
        

    * Attributes:
    
        .. autoattribute:: pyuaf.util.NodeIdIdentifier.type
        
            The type of the NodeIdIdentifier (e.g. :attr:`pyuaf.util.nodeididentifiertypes.String`)
            as defined within :mod:`pyuaf.util.nodeididentifiertypes`.
    
        .. autoattribute:: pyuaf.util.NodeIdIdentifier.idString
        
            The string value in case :attr:`~pyuaf.util.NodeIdIdentifier.type` equals 
            :attr:`pyuaf.util.nodeididentifiertypes.String`.
    
        .. autoattribute:: pyuaf.util.NodeIdIdentifier.idNumeric
        
            The ``int`` value in case :attr:`~pyuaf.util.NodeIdIdentifier.type` equals 
            :attr:`pyuaf.util.nodeididentifiertypes.Numeric`.



*class* QualifiedName
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.QualifiedName


    An QualifiedName consists of a name and a corresponding namespace index or namespace URI.


    * Methods:

        .. automethod:: pyuaf.util.QualifiedName.__init__([name[, nameSpaceUri[, nameSpaceIndex]]])
    
            Construct a new QualifiedName in one of the following ways:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util import QualifiedName
                
                >>> name    = "MyName"
                >>> nsUri   = "myNameSpaceUri"
                >>> nsIndex = 2
                
                >>> # the following ways of constructing a QualifiedName are possible:
                >>> qName0 = QualifiedName()                        # incomplete, no information given!
                >>> qName1 = QualifiedName(name)                    # incomplete, no namespace information! 
                >>> qName2 = QualifiedName(name, nsUri)             # OK, fully qualified 
                >>> qName3 = QualifiedName(name, nsIndex)           # OK, fully qualified 
                >>> qName4 = QualifiedName(name, nsUri, nsIndex)    # OK, fully qualified 
                
                >>> # strings are assumed to be UTF-8 encoded!
                >>> unicodeObject = u"40\u00B0 Celsius ist eine hei\u00DFe Temperatur!"
                >>> qName5 = QualifiedName(unicodeObject.encode("UTF-8"), nsUri)
    
    
        .. automethod:: pyuaf.util.QualifiedName.hasNameSpaceUri
        
            Check if a non-empty namespace URI was given.
            
            :return: True if this QualifiedName contains a non-empty server URI, False if not.
            :rtype:  ``bool``
    
    
        .. automethod:: pyuaf.util.QualifiedName.hasNameSpaceIndex
        
            Check if a namespace index was given.
            
            :return: True if a namespaceIndex has been defined, False if not.
            :rtype:  ``bool``

    
        .. automethod:: pyuaf.util.QualifiedName.name
        
            Get the name part of the QualifiedName.
            
            :return: The name part.
            :rtype:  ``str``

    
        .. automethod:: pyuaf.util.QualifiedName.nameSpaceUri
        
            Get the namespace URI of the QualifiedName.
          
            This function will always return a string, so call hasNameSpaceUri() to see if it's a
            valid one.
            
            :return: The namespace URI.
            :rtype:  ``str``

    
        .. automethod:: pyuaf.util.QualifiedName.nameSpaceIndex
        
            Get the namespace index of the QualifiedName.
          
            This function will always return an ``int``, so call hasNameSpaceIndex() to see if it's
            a valid one.
            
            :return: The namespace index.
            :rtype:  ``int``

    
        .. automethod:: pyuaf.util.QualifiedName.setName(name)
        
            Set the name part of the QualifiedName.
            
            :param name: The name part.
            :type  name: ``str``

    
        .. automethod:: pyuaf.util.QualifiedName.setNameSpaceUri(uri)
        
            Set the namespace URI of the QualifiedName.
            
            :param uri: The namespace URI.
            :type  uri:  ``str``

    
        .. automethod:: pyuaf.util.QualifiedName.setNameSpaceIndex(index)
        
            Set the namespace index of the QualifiedName.
            
            :param uri: The namespace index.
            :type  uri:  ``int``





*class* QualifiedNameVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.QualifiedNameVector

    A QualifiedNameVector is a container that holds elements of type 
    :class:`pyuaf.util.QualifiedName`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.util.QualifiedName`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import QualifiedNameVector, QualifiedName
        
        >>> # construct a QualifiedNameVector without elements:
        >>> vec = QualifiedNameVector()
        
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(QualifiedName("some name", "/some/URI/"))
        
        >>> noOfElements = len(vec) # will be 1
        
        >>> vec.resize(2)
        
        >>> vec[1].setName("Some other name")
        >>> vec[1].setNameSpaceUri("/some/other/URI/")
        
        >>> noOfElements = len(vec) # will be 2
        
        >>> # you may construct a QualifiedNameVector from a regular Python list:
        >>> someOtherVec = QualifiedNameVector( [ QualifiedName("a", "uriA"), 
        ...                                       QualifiedName("b", "uriB") ] )



*class* RelativePath
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.RelativePath

    A RelativePath is a container that holds elements of type 
    :class:`pyuaf.util.RelativePathElement`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`pyuaf.util.RelativePathElement`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import RelativePath, RelativePathElement
        
        >>> # construct a RelativePath without elements:
        >>> path = RelativePath()
        
        >>> noOfElements = len(path) # will be 0
        
        >>> path.append(RelativePathElement())
        
        >>> noOfElements = len(path) # will be 1
        
        >>> path.resize(4)
        
        >>> noOfElements = len(path) # will be 4
        
        >>> element0 = path[0]
        
        >>> # you may construct a RelativePath from a regular Python list:
        >>> someOtherPath = RelativePath( [RelativePathElement(), RelativePathElement()] )



*class* RelativePathElement
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.RelativePathElement


    A RelativePathElement describes one element of a RelativePath and basically contains a target 
    (a qualified name), the type of the reference to this target, and some other properties.
    

    * Methods:

        .. automethod:: pyuaf.util.RelativePathElement.__init__
    
            Construct a NodeIdIdentifier by providing a string or a numeric value (or nothing at 
            all).
        
            You can construct a RelativePathElement like this:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util                  import RelativePathElement, QualifiedName, NodeId
                >>> from pyuaf.util.opcuaidentifiers import OpcUaId_HierarchicalReferences
            
                >>> elem0 = RelativePathElement()
                >>> elem1 = RelativePathElement(QualifiedName("SomeBrowseName", 42))
                >>> elem2 = RelativePathElement(QualifiedName("SomeBrowseName", 42), NodeId(OpcUaId_HierarchicalReferences, 0), True, False)
        

    * Attributes:
    
        .. autoattribute:: pyuaf.util.RelativePathElement.targetName
        
            The target name (a :class:`~pyuaf.util.QualifiedName`).
    
        .. autoattribute:: pyuaf.util.RelativePathElement.referenceType
        
            The reference type as a :class:`~pyuaf.util.NodeId` (which may, or may not be resolved).
    
        .. autoattribute:: pyuaf.util.RelativePathElement.isInverse
        
            Flag specifying whether or not the inverse reference is meant (as a ``bool``).
    
        .. autoattribute:: pyuaf.util.RelativePathElement.includeSubtypes
        
            Flag specifying if subtypes of the reference type should be included (as a ``bool``).



*class* SimpleAttributeOperand
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.SimpleAttributeOperand

    A SimpleAttributeOperand is part of a filter and can describe select clauses, where clauses, etc.


    * Methods:

        .. automethod:: pyuaf.util.SimpleAttributeOperand.__init__
    
            Construct a new SimpleAttributeOperand.
    
        .. automethod:: pyuaf.util.SimpleAttributeOperand.__str__
    
            Get a string representation of the SimpleAttributeOperand.


    * Attributes:
  
  
        .. autoattribute:: pyuaf.util.SimpleAttributeOperand.attributeId
        
            The attribute id (e.g. :attr:`pyuaf.util.attributeids.Value`) as an ``int`` as 
            defined in :mod:`pyuaf.util.attributeids`.
  
  
        .. autoattribute:: pyuaf.util.SimpleAttributeOperand.browsePath
        
            A "simple" browse path (actually just a list of qualified names),
            as a :class:`~pyuaf.util.QualifiedNameVector`.
  
  
        .. autoattribute:: pyuaf.util.SimpleAttributeOperand.typeId
        
            The type id, as a :class:`~pyuaf.util.NodeId`.
  
  
        .. autoattribute:: pyuaf.util.SimpleAttributeOperand.indexRange
        
            The index range of an array, as a ``str``.
            
    


*class* SimpleAttributeOperandVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.SimpleAttributeOperandVector

    A SimpleAttributeOperandVector is a container that holds elements of type 
    :class:`pyuaf.util.SimpleAttributeOperand`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`pyuaf.util.SimpleAttributeOperand`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import SimpleAttributeOperandVector, \
        ...                        SimpleAttributeOperand, \
        ...                        QualifiedName, \
        ...                        NodeId
        
        >>> # construct a SimpleAttributeOperandVector without elements:
        >>> vec = SimpleAttributeOperandVector()
        
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(SimpleAttributeOperand())
        
        >>> vec[0].attributeId = pyuaf.util.attributeids.Value
        >>> vec[0].browsePath.append(QualifiedName("some name", 3))
        >>> vec[0].typeId = NodeId(pyuaf.util.opcuaidentifiers.OpcUaId_BaseEventType, 0)
        
        >>> noOfElements = len(vec) # will be 1
        
        >>> vec.resize(4)
        
        >>> noOfElements = len(vec) # will be 4
        
        >>> # you may construct a SimpleAttributeOperandVector from a regular Python list:
        >>> someOtherVec = SimpleAttributeOperandVector( [ SimpleAttributeOperand(), 
        ...                                                SimpleAttributeOperand() ] )



*class* Status
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.Status


     A Status object holds a UAF status code, a description and optionally an OPC UA status code.
    

    * Methods:

        .. automethod:: pyuaf.util.Status.__init__
        
            Construct a Status by providing a UAF status code (as defined by 
            :mod:`pyuaf.util.statuscodes`) and optionally a description (a string).
            
            UAF Status objects are Uncertain by default.
        
            You can construct a Status like this:
            
            .. doctest::
            
                >>> import pyuaf
                >>> from pyuaf.util import Status, statuscodes
            
                >>> status0 = Status() # Uncertain by default!
                >>> status1 = Status(statuscodes.Good)
                >>> status2 = Status(statuscodes.InvalidRequestError, "This is an invalid request!")
                
        
        .. automethod:: pyuaf.util.Status.statusCode
        
            Get the UAF status code (as defined by :class:`pyuaf.util.statuscodes`).
            
            :return: The UAF status code (as defined by :class:`pyuaf.util.statuscodes`).
            :rtype:  ``int``
        
        
        .. automethod:: pyuaf.util.Status.statusCodeName
        
            Get the name of the UAF status code.
            
            :return: The name of the UAF status code.
            :rtype:  ``str``
        
        
        .. automethod:: pyuaf.util.Status.addDiagnostic
        
            Add some diagnostic info.
            
            :param name: The extra diagnostic info.
            :type  name: ``str``

    
        .. automethod:: pyuaf.util.Status.hasOpcUaStatusCode
        
            Check if the Status object, besides a UAF status code, also contains an OPC UA status 
            code (which can be gotten with :meth:`~pyuaf.util.Status.opcUaStatusCode`.
            
            :return: True if the status object has an OPC UA status code.
            :rtype:  bool


        .. automethod:: pyuaf.util.Status.opcUaStatusCode
        
            Get the OPC UA status code (only relevant 
            if :meth:`~pyuaf.util.Status.hasOpcUaStatusCode` is True!).
            
            :return: The OPC UA status code.
            :rtype:  ``int``

        
        .. automethod:: pyuaf.util.Status.setGood([message])
        
            Set the status to Good (and optionally add a message).
            
            :param message: The optional message.
            :type  message: ``str``

        
        .. automethod:: pyuaf.util.Status.setUncertain([message])
        
            Set the status to Uncertain (and optionally add a message).
            
            :param message: The optional message.
            :type  message: ``str``
        
        
        .. automethod:: pyuaf.util.Status.setStatus(statusCode[, message])
        
            Set the status to the given status code (and optionally add a message).
            
            :param statusCode: The new UAF status code (as defined by :class:`pyuaf.util.statuscodes`).
            :type  statusCode: ``int``
            :param message: The optional message.
            :type  message: ``str``

    
        .. automethod:: pyuaf.util.Status.isGood
        
            Check if the status has a "good" status code.
            
            :return: True if the status is Good.
            :rtype:  bool
    
    
        .. automethod:: pyuaf.util.Status.isNotGood
        
            Check if the status does not have a "good" status code.
            
            :return: True if the status is not Good.
            :rtype:  bool
    
    
        .. automethod:: pyuaf.util.Status.isUncertain
        
            Check if the status has an "uncertain" status code.
            
            :return: True if the status is Uncertain.
            :rtype:  bool
    
    
        .. automethod:: pyuaf.util.Status.isNotUncertain
        
            Check if the status does not have a "uncertain" status code.
            
            :return: True if the status is not Uncertain.
            :rtype:  bool
    
    
        .. automethod:: pyuaf.util.Status.isBad
        
            Check if the status has a "bad" status code.
            
            :return: True if the status is Bad.
            :rtype:  bool
    
    
        .. automethod:: pyuaf.util.Status.isNotBad
        
            Check if the status does not have a "bad" status code.
            
            :return: True if the status is not Bad.
            :rtype:  bool
    
    
        .. automethod:: pyuaf.util.Status.summarize(statuses)
        
            Make a "summary" of other statuses.
            
            Bad is dominant to Uncertain, which is dominant to Good. 
            So if any Bad status is present, the summary will be "Bad".
            If no Bad statuses are present but any Uncertain status is present, the summary will be
            Uncertain. And if only Good statuses are present, the summary will be Good.
            
            :param statuses: The statuses to summarize.
            :type  statuses: :class:`pyuaf.util.StatusVector`.



*class* StatusVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.StatusVector

    A StatusVector is a container that holds elements of type  :class:`pyuaf.util.Status`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`pyuaf.util.Status`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import Status, StatusVector
        
        >>> # construct a StatusVector without elements:
        >>> statuses = StatusVector()
        
        >>> noOfElements = len(statuses) # will be 0
        
        >>> statuses.append(Status())
        
        >>> noOfElements = len(statuses) # will be 1
        
        >>> statuses.resize(4)
        
        >>> noOfElements = len(statuses) # will be 4
        
        >>> element0 = statuses[0]
        
        >>> # you may construct a StatusVector from a regular Python list:
        >>> otherStatuses = StatusVector( [Status(), Status()] )




*class* Stringifiable
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.Stringifiable


     Stringifiable is an abstract class, subclassed by classes that must be able to be represented
     as a string.
    

    * Methods:
        
        .. automethod:: pyuaf.util.Stringifiable.__str__(indent, colon)
        
            Get a string representation.
            
            :param indent: Indentation to add in front of each new line.
            :type  indent: ``str``
            :param colon: Position from the beginning of the line, where a colon (double point) 
                          should be placed in case of key : value pairs.
            :type  colon: ``int``.
            

*class* StringVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.StringVector

    A StringVector is a container that holds string elements. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of string.

    Usage example:
    
    .. literalinclude:: /../../../examples/pyuaf/util/how_to_use_a_stringvector.py




*class* UInt32Vector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.UInt32Vector

    An UInt32Vector is a container that holds unsigned 32-bit ``int`` elements 
    (not :class:`~pyuaf.util.primitives.UInt32` objects!)
    
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of ``int``.
    
    An :class:`~pyuaf.util.UInt32Vector` is exactly the same as a :class:`~pyuaf.util.StringVector`, 
    except of course that it holds ``int`` elements instead of ``str`` elements. 
    For an elaborate example, check out the example at the :class:`~pyuaf.util.StringVector` 
    documentation.



*class* UserTokenPolicy
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.UserTokenPolicy

    A UserTokenPolicy instance describes the type, ID, issued token type, etc. of a user token.


    * Methods:

        .. automethod:: pyuaf.util.UserTokenPolicy.__init__
    
            Construct a new UserTokenPolicy.
    
    
    * Attributes:
  
  
        .. autoattribute:: pyuaf.util.UserTokenPolicy.policyId
        
            The policy ID as a ``str``, as defined in :mod:`pyuaf.util.securitypolicies`.
            
            By default, the policyId is :attr:`~pyuaf.util.securitypolicies.UA_None`.
    
        .. autoattribute:: pyuaf.util.UserTokenPolicy.tokenType
        
            The token type (e.g. :attr:`~pyuaf.util.usertokentypes.UserName`)
            (an ``int``, as defined in :mod:`pyuaf.util.usertokentypes`).
            
            By default, the tokenType is :attr:`~pyuaf.util.usertokentypes.Anonymous`.
    
        .. autoattribute:: pyuaf.util.UserTokenPolicy.issuedTokenType
        
            The issued token type as a ``str``.
    
        .. autoattribute:: pyuaf.util.UserTokenPolicy.issuerEndpointUrl
        
            The issuer endpoint URL as a ``str``.
    
        .. autoattribute:: pyuaf.util.UserTokenPolicy.securityPolicyUri
        
            The security policy URI as a ``str``.



*class* UserTokenPolicyVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.UserTokenPolicyVector

    A QualifiedNameVector is a container that holds elements of type 
    :class:`~pyuaf.util.UserTokenPolicy`. 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of :class:`~pyuaf.util.UserTokenPolicy`.

    Usage example:
    
    .. doctest::
    
        >>> import pyuaf
        >>> from pyuaf.util import UserTokenPolicyVector, UserTokenPolicy
        
        >>> # construct a UserTokenPolicyVector without elements:
        >>> vec = UserTokenPolicyVector()
        
        >>> noOfElements = len(vec) # will be 0
        
        >>> vec.append(UserTokenPolicy())
        >>> vec[0].policyId = pyuaf.util.securitypolicies.UA_Basic128Rsa15
        
        >>> noOfElements = len(vec) # will be 1
        
        >>> vec.resize(2)
        >>> vec[1].policyId = pyuaf.util.securitypolicies.UA_Basic256Rsa15
        
        >>> noOfElements = len(vec) # will be 2
        
        >>> # you may construct a UserTokenPolicyVector from a regular Python list:
        >>> someOtherVec = UserTokenPolicyVector( [ UserTokenPolicy(), UserTokenPolicy() ] )





     
*class* VariantVector
----------------------------------------------------------------------------------------------------


.. autoclass:: pyuaf.util.VariantVector

    A VariantVector is a container that holds variants (so variables with a dynamic data type). 
    It is an artifact automatically generated from the C++ UAF code, and has the same functionality
    as a ``list`` of values, where the values can be instances of:
    
     - None
     - :class:`pyuaf.util.primitives.Boolean`
     - :class:`pyuaf.util.primitives.UInt32`
     - ``str``
     - :class:`pyuaf.util.QualifiedName`
     - :class:`pyuaf.util.LocalizedText`
     - a ``list`` of any of the above types --> represents an OPC UA array!
     - ...
     
    .. seealso:: :ref:`note-variants`.

    Usage example:
    
    .. literalinclude:: /../../../examples/pyuaf/util/how_to_use_a_variantvector.py






    


        


