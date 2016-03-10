PyUAF - Python bindings for the UAF (Unified Architecture Framework) 
====================================================================================================


Introduction
----------------------------------------------------------------------------------------------------

This documentation is part of the UAF (Unified Architecture Framework) project, which 
is hosted at http://github.com/uaf.

It documents the Python bindings for the UAF, which is supported on both Linux and Microsoft Windows.

The PyUAF bindings provide a very convenient interface to create OPC UA applications. For instance,
an OPC UA variable can be read by a UAF client with just a few lines of Python code: 

.. literalinclude:: ../../../examples/pyuaf/client/easiest_client_example.py


As you can see, all session management is done automatically for you!

More in general, the UAF takes care of some "technical" aspects of the OPC UA communication
(such as Session and Subscription management, server discovery, node resolution, ...) 
so that you can concentrate on the "functional" aspects of your software application.  


Project details
----------------------------------------------------------------------------------------------------

**Project website:** http://github.com/uaf
 
**Author:** Wim Pessemier

**Contact:** ``Wxx.Pxxxxxxxx@ster.kuleuven.be`` (replace the ``x``'es)
 
**Organization:** Institute of Astronomy, KU Leuven (http://fys.kuleuven.be/ster)
 


Examples
----------------------------------------------------------------------------------------------------

.. toctree::
   :maxdepth: 3
   
   client_examples


API
----------------------------------------------------------------------------------------------------

.. toctree::
   :maxdepth: 2

   api_pyuaf
   api_pyuaf_client
   api_pyuaf_client_connectionsteps
   api_pyuaf_client_monitoreditemstates
   api_pyuaf_client_requests
   api_pyuaf_client_results
   api_pyuaf_client_settings
   api_pyuaf_client_sessionstates
   api_pyuaf_client_subscriptionstates
   api_pyuaf_util
   api_pyuaf_util_attributeids
   api_pyuaf_util_applicationtypes
   api_pyuaf_util_browsedirections
   api_pyuaf_util_constants
   api_pyuaf_util_errors
   api_pyuaf_util_loglevels
   api_pyuaf_util_messagesecuritymodes
   api_pyuaf_util_monitoringmodes
   api_pyuaf_util_nodeclasses
   api_pyuaf_util_nodeididentifiertypes
   api_pyuaf_util_opcuaidentifiers
   api_pyuaf_util_opcuastatuscodes
   api_pyuaf_util_opcuatypes
   api_pyuaf_util_primitives
   api_pyuaf_util_serverstates
   api_pyuaf_util_securitypolicies
   api_pyuaf_util_structurefielddatatypes
   api_pyuaf_util_statuscodes
   api_pyuaf_util_timestampstoreturn
   api_pyuaf_util_usertokentypes
   api_variants
   api_client_kwargs


Indices and tables
----------------------------------------------------------------------------------------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

This documentation was created using `Sphinx <http://sphinx-doc.org>`_.
