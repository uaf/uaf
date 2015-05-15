# uaf/src/util/CMakeLists.txt

# Add all source files:
aux_source_directory(.          SOURCES_UAF_UTIL)
aux_source_directory(./errors   SOURCES_UAF_UTIL_ERRORS)

# Create a shared library consisting of the previously added source files.
add_library(uafutil SHARED ${SOURCES_UAF_UTIL} 
                           ${SOURCES_UAF_UTIL_ERRORS})

# Link the libraries.
if (WIN32)
    target_link_libraries(uafutil 
                          ${OPENSSL_LIBRARIES}
                          ${LIBXML2_LIBRARIES}
                          oleaut32 ole32 Version ws2_32 rpcrt4 crypt32 
                          uabase uapki uastack xmlparser )
else (WIN32)
    target_link_libraries(uafutil
                          ${OPENSSL_LIBRARIES}
                          ${LIBXML2_LIBRARIES}
                          dl rt pthread
                          uabase uapki uastack xmlparser )
endif (WIN32)