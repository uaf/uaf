# ==================================================================================================
project(uaf)
# ==================================================================================================


# Specify a minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Provide the path which contains CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}")

# Load the macros defined by the UAF
include(UafMacros)

# Handle some command line options (default values are the same as for the SDK!)
handleOptions()

# Set the build type to release
setBuildTypeToRelease()

# Set the UAF compiler flags
setUafCompilerFlags()

# Set the compiler dir used by the Unified Automation C++ SDK
setUnifiedAutomationSdkCompilerDir(COMPILER_DIR)

# Set linker restrictions
setUafLinkerRestrictions()

# Make sure the necessary third-party packages are found
handleUnifiedAutomationSdk()
handleOpenSsl()
handleLibXml2()
handleSwig()
handlePythonLibs()

# Include any required third-party code
includeThirdPartyCodeIfNeeded()

# Include the common SDK headers
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uastack")

# Include the OpenSSL headers
include_directories("${OPENSSL_INCLUDE_DIR}")

# link the SDK libraries
link_directories("${UASDK_LIBRARIES_DIR}")

# Include the src/ directory.
include_directories("${PROJECT_SOURCE_DIR}")

# add the uaf subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/uaf)

# if SWIG and the PythonLibs are present, also include the pyuaf directory
if (SWIG_FOUND)
    # build a SWIG module for Python
    include(UseSWIG)
    if (PYTHONLIBS_FOUND)
        message(STATUS "Including Python include path: ${PYTHON_INCLUDE_PATH}")
        include_directories(${PYTHON_INCLUDE_PATH})
        add_subdirectory(${PROJECT_SOURCE_DIR}/pyuaf)
    endif (PYTHONLIBS_FOUND)
endif (SWIG_FOUND)

# set the output directories
setUafOutputDirectories()

# Print the include dirs
message(STATUS "The following directories are included:")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS " * ${dir}")
endforeach()

# Print a summary
message(STATUS "")
message(STATUS "========== SUMMARY ==========")
message(STATUS "SDK was found    : TRUE (${UASDK_DIR})")
message(STATUS "SWIG was found   : ${SWIG_FOUND} (${SWIG_EXECUTABLE})")
message(STATUS "Python was found : ${PYTHONLIBS_FOUND} (${PYTHON_LIBRARIES})")
message(STATUS "Options          : UASTACK_WITH_HTTPS = ${UASTACK_WITH_HTTPS}")
if(SWIG_FOUND)
	if (PYTHONLIBS_FOUND)
        message(STATUS "This means that the UAF will be built, including Python wrappers")
	else (PYTHONLIBS_FOUND)
		message(STATUS "This means that the UAF will be built, without Python wrappers")
	endif (PYTHONLIBS_FOUND)
else (SWIG_FOUND)
	message(STATUS "This means that the UAF will be built, without any wrappers")
endif(SWIG_FOUND)
