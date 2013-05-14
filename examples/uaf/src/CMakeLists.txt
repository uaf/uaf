
# ==================================================================================================
project(uaf-examples)
# ==================================================================================================


# Specify a minimum version for CMake
cmake_minimum_required(VERSION 2.6)

# Define the base UAF path
get_filename_component(UAF_DIR "${PROJECT_SOURCE_DIR}/../../.." ABSOLUTE)

# Provide the path which contains CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${UAF_DIR}/src")

# Load the macros defined by the UAF
include(UafMacros)

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

# include the /src directory of the UAF
include_directories("${UAF_DIR}/src")

# Add the SDK include directories
include_directories("${UASDK_INCLUDE_DIR}")
include_directories("${UASDK_INCLUDE_DIR}/uabase")
include_directories("${UASDK_INCLUDE_DIR}/uapki")
include_directories("${UASDK_INCLUDE_DIR}/uastack")

# Include the OpenSSL headers
include_directories("${OPENSSL_INCLUDE_DIR}")

# Add the link directories
link_directories("${UAF_DIR}/lib")
link_directories("${UASDK_LIBRARIES_DIR}")

# Define the output directory for the examples
set(EXAMPLES_UAF_BIN_DIR  "${PROJECT_SOURCE_DIR}/../bin")

message(STATUS "The binaries will be installed in ${EXAMPLES_UAF_BIN_DIR}!")

# Add the subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/client)
