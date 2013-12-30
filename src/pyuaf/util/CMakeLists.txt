# pyuaf/util/CMakeLists.txt


# Include the C++ header directories
include_directories(  "${PROJECT_SOURCE_DIR}/uaf/util"  )
include_directories(  "${PROJECT_SOURCE_DIR}"  )


# define and create the lib/pyuaf/util directory
set(   LIB_PYUAF_UTIL_DIR   ${LIB_PYUAF_DIR}/util  )
file(  MAKE_DIRECTORY       ${LIB_PYUAF_UTIL_DIR}  )

# define the unittests/pyuaf directory
set(UNITTESTS_PYUAF_DIR ${PROJECT_SOURCE_DIR}/../unittests/pyuaf)

# update the output dirs
set(  LIBRARY_OUTPUT_PATH   ${LIB_PYUAF_UTIL_DIR} )
set(  CMAKE_SWIG_OUTDIR     ${LIB_PYUAF_UTIL_DIR} )

# Copy the errors.py file
configure_file(  "errors.py"       "${LIB_PYUAF_UTIL_DIR}"   )
configure_file(  "demoserver.py"   "${UNITTESTS_PYUAF_DIR}"  )


# declare the targets
set(  PYUAF_UTIL_TARGETS
      __init__
      applicationtypes
      attributeids
      bytestring_python
      loglevels
      usertokentypes
      nodeididentifiertypes
      statuscodes
      opcuatypes
      opcuaidentifiers
      opcuastatuscodes
      securitypolicies
      messagesecuritymodes
      timestampstoreturn
      monitoringmodes
      browsedirections
      nodeclasses
      primitives
      constants
      variant_python
      __unittesthelper__
   )



# set the target properties
foreach(PYUAF_UTIL_TARGET ${PYUAF_UTIL_TARGETS})
    setPyUafTargetProperties(    util    ${PYUAF_UTIL_TARGET}   ${LIB_PYUAF_UTIL_DIR}  uafutil)
endforeach(PYUAF_UTIL_TARGET)


 