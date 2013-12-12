# This module searches the Unified Automation SDK and defines
# UASDK_FOUND, TRUE if the SDK has been found
# UASDK_LIBRARIES_DIR, where to find the libraries
# UASDK_INCLUDE_DIR, where to find the headers
# UASDK_DIR, the base directory of the SDK


# In case of Windows, we will try to find the Unified Automation SDK
# in the C:\ and C:\Program Files\ folders.


if (WIN32)
    # make a list of folders that may contain the SDK
    set(SDK_SEARCH_PATHS
        "C:/*[U,u]nified*/*sdk*/lib"
        "C:/*[U,u]nified*/lib"
        "C:/*[U,u][A,a][S,s][D,d][K,k]*/*/lib"
        "C:/Program Files/*[U,u][A,a][S,s][D,d][K,k]*/*/lib"
        "C:/Program Files/*[U,u]nified*/*/lib"
        "C:/Program Files/*[U,u]nified*/lib"
        "C:/Program Files (x86)/*[U,u][A,a][S,s][D,d][K,k]*/*/lib"
        "C:/Program Files (x86)/*[U,u]nified*/*/lib"
        "C:/Program Files (x86)/*[U,u]nified*/lib")
    set(SDK_SEARCH_LIB "uabase.lib")
else (WIN32)
    # make a list of folders that may contain the SDK
    set(SDK_SEARCH_PATHS
        "/opt/*[U,u]nified[A,a]utomation*/*sdk*/lib"
        "/opt/*[U,u]nified[A,a]utomation*/*SDK*/lib"
        "/opt/sdk*/lib"
        "/opt/SDK*/lib"
        "/opt/*[U,u]nified*/*sdk*/lib"
        "/opt/*[U,u]nified*/*SDK*/lib"
        "/opt/*sdk*/lib"
        "/opt/*SDK*/lib"
        "/opt/*[U,u][A,a][S,s][D,d][K,k]*/lib"
        "$ENV{HOME}/*[U,u][A,a][S,s][D,d][K,k]*/") # could be an easy hack: symlink ~/.UaSdk to the SDK directory
    set(SDK_SEARCH_LIB "libuabase.a")
endif (WIN32)


message(STATUS "Verifying if one of the following directories exist:")
foreach(SDK_SEARCH_PATH ${SDK_SEARCH_PATHS})
    message(STATUS " * ${SDK_SEARCH_PATH}")
    file(GLOB SDK_SEARCH_RESULTS ${SDK_SEARCH_PATH})
    foreach(SDK_SEARCH_RESULT ${SDK_SEARCH_RESULTS})
        get_filename_component(POTENTIAL_SDK_FOLDER "${SDK_SEARCH_RESULT}" ABSOLUTE)
        list(APPEND POTENTIAL_SDK_FOLDERS ${POTENTIAL_SDK_FOLDER})
    endforeach(SDK_SEARCH_RESULT)
endforeach(SDK_SEARCH_PATH)

if(NOT DEFINED POTENTIAL_SDK_FOLDERS)
    message(FATAL_ERROR "!!! No potential SDK directories were found !!!")
endif(NOT DEFINED POTENTIAL_SDK_FOLDERS)

list(REMOVE_DUPLICATES POTENTIAL_SDK_FOLDERS)

message(STATUS "Found the following potential SDK/lib directories:")
foreach(POTENTIAL_SDK_FOLDER ${POTENTIAL_SDK_FOLDERS})
    message(STATUS " * ${POTENTIAL_SDK_FOLDER}")
endforeach(POTENTIAL_SDK_FOLDER)


# for each of the found folders, try to find the uabase.lib library:

foreach(POTENTIAL_SDK_FOLDER ${POTENTIAL_SDK_FOLDERS})

    message(STATUS "Now searching recursively for ${SDK_SEARCH_LIB} in ${POTENTIAL_SDK_FOLDER}")
    
    file(GLOB_RECURSE LIBRESULTS "${POTENTIAL_SDK_FOLDER}/${SDK_SEARCH_LIB}")

    if(LIBRESULTS)
        
        list(GET LIBRESULTS 0 FIRST_LIBRESULT)
    
        message(STATUS "The ${SDK_SEARCH_LIB} library was found!")
    
        # get the path of the /lib directory:
        get_filename_component(UASDK_LIBRARIES_DIR "${FIRST_LIBRESULT}" PATH)

        # get the path of the SDK:
        get_filename_component(UASDK_DIR "${UASDK_LIBRARIES_DIR}/../" ABSOLUTE)

        # specify the include folder
        set(UASDK_INCLUDE_DIR "${UASDK_DIR}/include")

        message(STATUS "The SDK was found here: ${UASDK_DIR}")

        # break out of the foreach loop
        break()
    
    else(LIBRESULTS)
    
        message(STATUS "The ${SDK_SEARCH_LIB} library was not found recursively  this directory")
    
    endif(LIBRESULTS)

endforeach(POTENTIAL_SDK_FOLDER)



# handle the QUIETLY and REQUIRED arguments and set UASDK_FOUND to TRUE if all variables have been declared
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(UaSdk REQUIRED_VARS UASDK_DIR UASDK_INCLUDE_DIR UASDK_LIBRARIES_DIR)

# mark the following variables as "advanced" so they do onot appear in the CMake GUI
MARK_AS_ADVANCED(UASDK_INCLUDE_DIR UASDK_LIBRARIES_DIR UASDK_DIR)