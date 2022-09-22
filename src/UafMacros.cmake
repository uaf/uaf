# ----------------------------------------------------------------------------
# setDefaultBuildTypeToRelease()
#    This macro sets the build type to Release, if no
#    build type has been set yet.
# ----------------------------------------------------------------------------
MACRO(setDefaultBuildTypeToRelease)

    IF(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
        set (CMAKE_BUILD_TYPE Release)
        set (CMAKE_CONFIGURATION_TYPES "Release")
    ENDIF()

ENDMACRO(setDefaultBuildTypeToRelease)

# ----------------------------------------------------------------------------
# handleOptions()
#    This macro handles some command line options.
# ----------------------------------------------------------------------------
MACRO(handleOptions)

    OPTION( UASTACK_WITH_HTTPS   "Set to OFF if the Stack was built without HTTPS support." ON )

    IF ( UASTACK_WITH_HTTPS )
        ADD_DEFINITIONS( -DOPCUA_HAVE_HTTPS=1 )
    ELSE ( UASTACK_WITH_HTTPS )
        ADD_DEFINITIONS( -DOPCUA_HAVE_HTTPS=0 )
    ENDIF ( UASTACK_WITH_HTTPS )

    OPTION( NO_THIRD_PARTY_MSINTTYPES "Set to ON if you want to avoid msinttypes to be included for certain compilers" OFF)

    OPTION( COPY_SDK_LIBS  "Set to OFF if you don't want the SDK libraries to be copied to the UAF/lib folder" ON )

    OPTION( BUILD_WITH_MULTIPLE_PROCESSES   "Set to ON if you want to build the UAF with multiple processes" OFF )

ENDMACRO(handleOptions)

# ----------------------------------------------------------------------------
# setUnifiedAutomationSdkCompilerDir(NEW_VAR)
#    This macro sets NEW_VAR to the compiler dir used by the
#    Unified Automation C++ SDK.
# ----------------------------------------------------------------------------
MACRO(setUnifiedAutomationSdkCompilerDir _NEW_VAR)

    IF (WIN32)
        IF (MSVC80)
            SET(${_NEW_VAR} vs2005sp1)
        ELSEIF (MSVC90)
            SET(${_NEW_VAR} vs2008sp1)
        ELSEIF (MSVC60)
            SET (${_NEW_VAR} vs6sp6)
        ELSEIF (MSVC10)
            SET (${_NEW_VAR} vs2010sp1)
        ELSEIF (MSVC11)
            SET (${_NEW_VAR} vs2012sp4 )
        ELSEIF (MINGW)
            SET (${_NEW_VAR} mingw)
        ELSE ()
            MESSAGE(FATAL_ERROR "Unknown Win32 Compiler!")
        ENDIF()

        MESSAGE("-- Using compiler: ${${_NEW_VAR}}")

    ENDIF (WIN32)

ENDMACRO(setUnifiedAutomationSdkCompilerDir)

# ----------------------------------------------------------------------------
# setUafCompilerFlags()
#    This macro will set the correct compiler flags for the UAF.
# ----------------------------------------------------------------------------
MACRO(setUafCompilerFlags)

    if (WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
        if (BUILD_WITH_MULTIPLE_PROCESSES)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
        endif (BUILD_WITH_MULTIPLE_PROCESSES)
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE -D_UA_STACK_USE_DLL)
    else (WIN32)
        if (FORCE32)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-comment -m32 -Wno-maybe-uninitialized")
        else (FORCE32)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-function -Wno-comment -Wno-maybe-uninitialized")
        endif (FORCE32)
        if (BUILD_WITH_MULTIPLE_PROCESSES)
            message(FATAL_ERROR "BUILD_WITH_MULTIPLE_PROCESSES is not allowed on this platform. Try 'make -j' instead, when compiling.")
        endif (BUILD_WITH_MULTIPLE_PROCESSES)
    endif (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

ENDMACRO(setUafCompilerFlags)

# ----------------------------------------------------------------------------
# setUafLinkerRestrictions()
#    This macro will set the correct linker restrictions.
# ----------------------------------------------------------------------------
MACRO(setUafLinkerRestrictions)

    if (FORCE32)
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
    else (FORCE32)
        set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)
    endif (FORCE32)

ENDMACRO(setUafLinkerRestrictions)

# ----------------------------------------------------------------------------
# includeThirdPartyCodeIfNeeded()
#    This macro will include third party code (if needed)
# ----------------------------------------------------------------------------
MACRO(includeThirdPartyCodeIfNeeded)
    if (MSVC90)
        message(STATUS "Compiling for VS2008")
        message(STATUS "The third-party project 'msinttypes' needs to be included for this compiler")
        if (NO_THIRD_PARTY_MSINTTYPES)
            message(WARNING "However, msinttypes will NOT be included since NO_THIRD_PARTY_MSINTTYPES=ON" )
        else (NO_THIRD_PARTY_MSINTTYPES)
            message(STATUS "If you don't want msinttypes to be included, set NO_THIRD_PARTY_MSINTTYPES=ON" )
            message(STATUS "Now including ${PROJECT_SOURCE_DIR}/third-party/msinttypes" )
            include_directories("${PROJECT_SOURCE_DIR}/third-party/msinttypes")
        endif (NO_THIRD_PARTY_MSINTTYPES)
    endif (MSVC90)

ENDMACRO(includeThirdPartyCodeIfNeeded)

# ----------------------------------------------------------------------------
# handleUnifiedAutomationSdk()
#    This macro will set the necessary UnifiedAutomation SDK variables
#    (UASDK_FOUND, UASDK_RI, UASDK_LIBRARIES_DIRS, UASDK_INCLUDE_DIRS).
# ----------------------------------------------------------------------------
MACRO(handleUnifiedAutomationSdk)

    if (UASDK)

        if (EXISTS "${UASDK}/include")
            message(STATUS "The specified Unified Automation SDK directory was found (${UASDK})" )
            set(UASDK_FOUND TRUE)
            set(UASDK_DIR "${UASDK}")
            set(UASDK_INCLUDE_DIR "${UASDK}/include")
        else (EXISTS "${UASDK}/include")
            set(UASDK_FOUND FALSE)
            message("")
            message(FATAL_ERROR
                    "The Unified Automation SDK path was specified (${UASDK}) "
                    "but doesn't exist!")
        endif (EXISTS "${UASDK}/include")

    else (UASDK)

        message(STATUS "The Unified Automation SDK directory was not specified using "
                "the -DUASDK flag, so we will try to find it")
        find_package(UaSdk REQUIRED)

    endif (UASDK)

    # figure out if the source code version of the SDK is installed
    if (EXISTS "${UASDK_DIR}/src")
        # The source code version of the SDK compiles with option UASTACK_WITH_HTTPS=OFF by default!
        # Check if the UAF is compiled with the same option
        IF ( UASTACK_WITH_HTTPS )
            message(WARNING "\n!!!!!!!!\nIt appears that the SDK is a 'source code license' version, which probably means that you compiled the SDK yourself. The SDK compiles by default with -DUASTACK_WITH_HTTPS=OFF, while the UAF compiles by default (and will be compiled right now) with -DUASTACK_WITH_HTTPS=ON. You must make sure that both the UAF and the SDK are compiled with the same options. So either compile both the SDK and the UAF with -DUASTACK_WITH_HTTPS=ON, or both with -DUASTACK_WITH_HTTPS=OFF. If you're sure this is the case, you can safely ignore this warning.\n!!!!!!!!\n")
        ENDIF ( UASTACK_WITH_HTTPS )
    endif (EXISTS "${UASDK_DIR}/src")

    # figure out if the SDK version is at least 1.4 by checking if include/uabase/uafile.h exists
    if (EXISTS "${UASDK_INCLUDE_DIR}/uabasecpp/uafile.h")
        message(STATUS "OK, the SDK has version 1.4 or higher")
    else (EXISTS "${UASDK_INCLUDE_DIR}/uabasecpp/uafile.h")
        message(FATAL_ERROR "The Unified Automation SDK must be at least version 1.4.0")
    endif (EXISTS "${UASDK_INCLUDE_DIR}/uabasecpp/uafile.h")

    # figure out if the SDK version is 1.5 or 1.4 by checking if include/uastack/opcua_p_config.h exists
    if (EXISTS "${UASDK_INCLUDE_DIR}/uastack/opcua_p_config.h")
        set(UASDK_VERSION 15)
        message(STATUS "OK, the SDK has version 1.5 or higher")
    else (EXISTS "${UASDK_INCLUDE_DIR}/uastack/opcua_p_config.h")
        set(UASDK_VERSION 14)
        message(STATUS "The SDK has version 1.4")
    endif (EXISTS "${UASDK_INCLUDE_DIR}/uastack/opcua_p_config.h")

    # add the version number as a definition
    add_definitions( -DUASDK_VERSION=${UASDK_VERSION} )

    # store the path to the UaServerCPP executable, since it is required for the unit tests
    if (WIN32)
        set(DEMOSERVER_COMMAND "${UASDK_DIR}/bin/uaservercppd.exe")
    else (WIN32)
        set(DEMOSERVER_COMMAND "${UASDK_DIR}/bin/uaservercppd")
    endif (WIN32)

    # display a warning if the UaServerCPP demoserver cannot be found
    if (EXISTS ${DEMOSERVER_COMMAND})
        message(STATUS "The UaServerCPP demo server was found, so the unit tests can be run.")
    else (EXISTS ${DEMOSERVER_COMMAND})
        message(WARNING "The demo server (UaServerCPP) cannot be found: ${DEMOSERVER_COMMAND} does not exist! This demo server is only needed to run the client unit tests, so you can safely ignore this warning if you do not intend to run unit tests.\n")
    endif (EXISTS ${DEMOSERVER_COMMAND})

    set(UASDK_LIBRARIES_DIRS
        "${UASDK}/lib"
        "${UASDK}/lib64")
    set(UASDK_INCLUDE_DIRS
        SYSTEM "${UASDK_INCLUDE_DIR}"
        SYSTEM "${UASDK_INCLUDE_DIR}/uabasecpp"
        SYSTEM "${UASDK_INCLUDE_DIR}/uaclientcpp"
        SYSTEM "${UASDK_INCLUDE_DIR}/uamodels"
        SYSTEM "${UASDK_INCLUDE_DIR}/uapkicpp"
        SYSTEM "${UASDK_INCLUDE_DIR}/uaservercpp"
        SYSTEM "${UASDK_INCLUDE_DIR}/uastack"
        SYSTEM "${UASDK_INCLUDE_DIR}/xmlparsercpp")
    set(UASDK_LIBRARIES
        debug uabasecppd optimized uabasecpp
        debug uaclientcppd optimized uaclientcpp
        debug uamodelsd optimized uamodels
        debug uapkicppd optimized uapkicpp
        debug uastackd optimized uastack
        debug xmlparsercppd optimized xmlparsercpp)

ENDMACRO(handleUnifiedAutomationSdk)

# ----------------------------------------------------------------------------
# handleLibXml2()
#    This macro will set the necessary LibXml2 variables
#    (LIBXML2_FOUND, LIBXML2_INCLUDE_DIR, LIBXML2_LIBRARIES)
#    and install the dlls in case of Windows.
# ----------------------------------------------------------------------------
MACRO(handleLibXml2)

    if (WIN32)
        if(EXISTS ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2)
            SET(LIBXML2_FOUND TRUE)
            SET(LIBXML2_INCLUDE_DIR ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/include)
            SET(LIBXML2_LIBRARIES
                optimized ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/out32dll/libxml2.lib
                debug ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/out32dll.dbg/libxml2d.lib)
            INSTALL(FILES ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/libxml2/out32dll/libxml2.dll
                    DESTINATION "${PROJECT_OUTPUT_DIR}")
            MESSAGE(STATUS "found libxml2: " ${LIBXML2_LIBRARIES})
        else()
            message(FATAL_ERROR "\n"
                    "The LibXml2 libraries could not be found\n")
        endif()
    else (WIN32)
        find_package(LibXml2 REQUIRED)
    endif (WIN32)

ENDMACRO(handleLibXml2)

# ----------------------------------------------------------------------------
# handleOpenSsl()
#    This macro will set the necessary OpenSSL variables
#    (OPENSSL_FOUND, OPENSSL_INCLUDE_DIR, OPENSSL_LIBRARIES)
#    and install the dlls in case of Windows.
# ----------------------------------------------------------------------------
MACRO(handleOpenSsl)

    if (WIN32)
        if ( EXISTS ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl )
            SET(OPENSSL_FOUND TRUE)
            SET(OPENSSL_INCLUDE_DIR ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/inc32)
            SET(OPENSSL_LIBRARIES
                optimized ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/out32dll/libeay32.lib
                debug ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/out32dll.dbg/libeay32d.lib)
            INSTALL(FILES ${UASDK_DIR}/third-party/win32/${COMPILER_DIR}/openssl/out32dll/libeay32.dll
                    DESTINATION "${PROJECT_OUTPUT_DIR}")
            MESSAGE(STATUS "found openssl: " ${OPENSSL_LIBRARIES})
        else ()
            message(FATAL_ERROR "\n"
                    "The OpenSSL libraries could not be found\n")
        endif ()
    else (WIN32)
        find_package(OpenSSL REQUIRED)
    endif (WIN32)

ENDMACRO(handleOpenSsl)

# ----------------------------------------------------------------------------
# handleSwig()
#    This macro will set the necessary SWIG variables.
# ----------------------------------------------------------------------------
MACRO(handleSwig)

    if(WIN32)

        if (SWIG)

            if (EXISTS "${SWIG}/swig.exe")
                message(STATUS "The specified SWIG installation was found" )
                set(SWIG_FOUND TRUE)
                set(SWIG_DIR "${SWIG}")
                set(SWIG_EXECUTABLE "${SWIG}/swig.exe")

                EXECUTE_PROCESS(COMMAND ${SWIG_EXECUTABLE} -version
                                OUTPUT_VARIABLE SWIG_version_output
                                ERROR_VARIABLE SWIG_version_output
                                RESULT_VARIABLE SWIG_version_result)
                IF(SWIG_version_result)
                    MESSAGE(SEND_ERROR "Command \"${SWIG_EXECUTABLE} -version\" failed with output:\n${SWIG_version_output}")
                ELSE(SWIG_version_result)
                    STRING(REGEX REPLACE ".*SWIG Version[^0-9.]*\([0-9.]+\).*" "\\1"
                    SWIG_version_output "${SWIG_version_output}")
                    SET(SWIG_VERSION ${SWIG_version_output} CACHE STRING "Swig version" FORCE)
                ENDIF(SWIG_version_result)

            else (EXISTS "${SWIG}/swig.exe")
                set(SWIG_FOUND FALSE)
                message("")
                message(FATAL_ERROR "The SWIG path was specified (${SWIG}) but doesn't exist!")
            endif ()

        else(SWIG)

        	# in case of windows, we will search for a folder named *swig* in
        	# C:\ or C:\Program Files, and append this path to the CMAKE_PREFIX_PATH
        	# in case SWIG was found.

    		# make a list of folders that may contain SWIG:
    	    file(GLOB TMP "C:/*swig*")
    	    list(APPEND POTENTIAL_SWIG_FOLDERS ${TMP})
    	    file(GLOB TMP "C:/Program Files/*swig*")
    	    list(APPEND POTENTIAL_SWIG_FOLDERS ${TMP})

    	    if(POTENTIAL_SWIG_FOLDERS)
    		    message(STATUS "Found the following potential SWIG directories:")
    		    foreach(POTENTIAL_SWIG_FOLDER ${POTENTIAL_SWIG_FOLDERS})
    		    	message(STATUS " * ${POTENTIAL_SWIG_FOLDER}")
    		    	list(APPEND CMAKE_PREFIX_PATH ${POTENTIAL_SWIG_FOLDER})
    		    endforeach(POTENTIAL_SWIG_FOLDER)
    	    else(POTENTIAL_SWIG_FOLDERS)
    	    	message(STATUS "Unfortunately, a *swig* folder could not be found")
    	    endif(POTENTIAL_SWIG_FOLDERS)

    		message(STATUS "Trying to find SWIG")

            find_package(SWIG)

    	endif(SWIG)

    else(WIN32)

    	find_package(SWIG)

    endif(WIN32)



ENDMACRO(handleSwig)

# ----------------------------------------------------------------------------
# handlePythonLibs()
#    This macro will set the necessary PythonLibs variables.
# ----------------------------------------------------------------------------
MACRO(handlePythonLibs)

    # the provided find_package script seems to do a decent job in finding
    # the python installation, also on Windows...
    find_package(PythonLibs ${PYUAF_PYTHONLIBS_VERSION} ${PYUAF_PYTHONLIBS_REQUIRED})

ENDMACRO(handlePythonLibs)

# ----------------------------------------------------------------------------
# setUafOutputDirectories()
#    This macro will set the correct output directories for the UAF.
# ----------------------------------------------------------------------------
MACRO(setUafOutputDirectories)

    if (WIN32)
        set_target_properties(uafutil    PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafutil    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${PROJECT_OUTPUT_DIR}")
        set_target_properties(uafclient  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_OUTPUT_DIR}")
    endif(WIN32)

    set_target_properties(uafutil    PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
    set_target_properties(uafclient  PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
    set_target_properties(uafutil    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")
    set_target_properties(uafclient  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIR}")

ENDMACRO(setUafOutputDirectories)

# ----------------------------------------------------------------------------
# setPyUafTargetProperties()
#    This macro will set the correct target properties for PyUAF
# ----------------------------------------------------------------------------
MACRO(setPyUafTargetProperties  _PREFIX _NAME _OUTDIR _UAFLINKLIB)

    set(_TARGET "${_PREFIX}_${_NAME}")

    # Set the source file properties to C++
    set_source_files_properties(  ${_TARGET}.i  PROPERTIES  CPLUSPLUS ON  )

    if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_GREATER 3.11)
        # Add the SWIG interface module
        swig_add_library(  ${_TARGET}  TYPE SHARED  LANGUAGE python  SOURCES ${_TARGET}.i  )
    else()
        # Add the SWIG interface module
         swig_add_module(  ${_TARGET}  python  ${_TARGET}.i  )
    endif()

    # link the libraries to the Python libraries and UAF libraries
    swig_link_libraries(  ${_TARGET}  ${PYTHON_LIBRARIES}  ${_UAFLINKLIB}  )

    # NOT USED set_source_files_properties( ${_TARGET} PROPERTIES COMPILE_FLAGS "-relativeimport")

    if (WIN32)
        set_target_properties(  _${_TARGET}   PROPERTIES   LIBRARY_OUTPUT_DIRECTORY_DEBUG           "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   LIBRARY_OUTPUT_DIRECTORY_RELEASE         "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO  "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   RUNTIME_OUTPUT_DIRECTORY_DEBUG           "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   RUNTIME_OUTPUT_DIRECTORY_RELEASE         "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO  "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   ARCHIVE_OUTPUT_DIRECTORY_DEBUG           "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   ARCHIVE_OUTPUT_DIRECTORY_RELEASE         "${_OUTDIR}"  )
        set_target_properties(  _${_TARGET}   PROPERTIES   ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO  "${_OUTDIR}"  )
    endif(WIN32)

    # Set the compiler flags
    set_target_properties(  _${_TARGET} PROPERTIES COMPILER_FLAGS "/EHsc")

    set_target_properties(  _${_TARGET} PROPERTIES OUTPUT_NAME _${_NAME})

ENDMACRO(setPyUafTargetProperties)

# ----------------------------------------------------------------------------
# copyFile(file, to)
#    This function will copy the given file to the given destination.
# ----------------------------------------------------------------------------
FUNCTION(copyFile _FILE _TO)

    if( EXISTS "${_FILE}" )
        MESSAGE(STATUS "Copying ${_FILE} to ${_TO}")
        file(COPY "${_FILE}" DESTINATION "${_TO}" )
    else( EXISTS "${_FILE}" )
        MESSAGE(FATAL_ERROR "Copying ${_FILE} failed: file not found!")
    endif( EXISTS "${_FILE}" )

ENDFUNCTION(copyFile)

# ----------------------------------------------------------------------------
# copySdkLibraries()
#    This macro will copy the necessary SDK libraries to the lib folder
# ----------------------------------------------------------------------------
MACRO(copySdkLibraries)

    if (COPY_SDK_LIBS)

        message(STATUS "Trying to copy the SDK libraries (set COPY_SDK_LIBS to OFF if you dont want this)")

        if (WIN32)

            copyFile("${UASDK_DIR}/bin/uastack.dll"  "${PROJECT_OUTPUT_DIR}")
            copyFile("${UASDK_DIR}/bin/ssleay32.dll" "${PROJECT_OUTPUT_DIR}")
            copyFile("${UASDK_DIR}/bin/libeay32.dll" "${PROJECT_OUTPUT_DIR}")
            copyFile("${UASDK_DIR}/bin/libxml2.dll"  "${PROJECT_OUTPUT_DIR}")

        else(WIN32)

            copyFile("${UASDK_DIR}/lib/libuastack.so" "${PROJECT_OUTPUT_DIR}")

        endif(WIN32)

    else(COPY_SDK_LIBS)

        message(STATUS "Not trying to copy the SDK libraries (because COPY_SDK_LIBS is OFF)")

    endif(COPY_SDK_LIBS)

ENDMACRO(copySdkLibraries)

