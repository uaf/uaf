# uaf/client/CMakeLists.txt

# Add all source files in this directory.
aux_source_directory(.                      SOURCES_UAF_CLIENT)
aux_source_directory(./configs              SOURCES_UAF_CLIENT_CONFIGS)
aux_source_directory(./database             SOURCES_UAF_CLIENT_DATABASE)
aux_source_directory(./discovery            SOURCES_UAF_CLIENT_DISCOVERY)
aux_source_directory(./invocations          SOURCES_UAF_CLIENT_INVOCATIONS)
aux_source_directory(./requests             SOURCES_UAF_CLIENT_REQUESTS)
aux_source_directory(./resolution           SOURCES_UAF_CLIENT_RESOLUTION)
aux_source_directory(./results              SOURCES_UAF_CLIENT_RESULTS)
aux_source_directory(./sessions             SOURCES_UAF_CLIENT_SESSIONS)
aux_source_directory(./settings             SOURCES_UAF_CLIENT_SETTINGS)
aux_source_directory(./subscriptions        SOURCES_UAF_CLIENT_SUBSCRIPTIONS)

# Include the client headers from the SDK
include_directories(${UASDK_INCLUDE_DIRS})

# Create a shared library consisting of the previously added source files.
add_library(uafclient SHARED ${SOURCES_UAF_CLIENT}
                             ${SOURCES_UAF_CLIENT_CONFIGS}
                             ${SOURCES_UAF_CLIENT_DATABASE}
                             ${SOURCES_UAF_CLIENT_DISCOVERY}
                             ${SOURCES_UAF_CLIENT_ERRORS}
                             ${SOURCES_UAF_CLIENT_INVOCATIONS}
                             ${SOURCES_UAF_CLIENT_REQUESTS}
                             ${SOURCES_UAF_CLIENT_RESOLUTION}
                             ${SOURCES_UAF_CLIENT_RESULTS}
                             ${SOURCES_UAF_CLIENT_SESSIONS}
                             ${SOURCES_UAF_CLIENT_SETTINGS}
                             ${SOURCES_UAF_CLIENT_SUBSCRIPTIONS})

link_directories(
    ${UASDK_LIBRARIES_DIRS}
)

# Link the libraries.
target_link_libraries(uafclient
    uafutil
    ${UASDK_LIBRARIES}
)
