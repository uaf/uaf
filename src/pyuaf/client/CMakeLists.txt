# pyuaf/client/CMakeLists.txt


# Include the C++ header directories
include_directories(  "${PROJECT_SOURCE_DIR}/uaf/util"  )
include_directories(  "${PROJECT_SOURCE_DIR}/uaf/client"  )
include_directories(  "${PROJECT_SOURCE_DIR}"  )

# define and create the lib/pyuaf/util directory
set(   LIB_PYUAF_CLIENT_DIR   ${LIB_PYUAF_DIR}/client  )
file(  MAKE_DIRECTORY         ${LIB_PYUAF_CLIENT_DIR}  )

# update the output dirs
set(  LIBRARY_OUTPUT_PATH   ${LIB_PYUAF_CLIENT_DIR} )
set(  CMAKE_SWIG_OUTDIR     ${LIB_PYUAF_CLIENT_DIR} )


# declare the targets
set(  PYUAF_CLIENT_TARGETS
      __init__
      sessionstates
      connectionsteps
      subscriptionstates
      monitoreditemstates
      settings
      requests
      results
   )

# set the target properties
foreach(PYUAF_CLIENT_TARGET ${PYUAF_CLIENT_TARGETS})
    setPyUafTargetProperties( client   ${PYUAF_CLIENT_TARGET}  ${LIB_PYUAF_CLIENT_DIR}  uafclient )
endforeach(PYUAF_CLIENT_TARGET)
