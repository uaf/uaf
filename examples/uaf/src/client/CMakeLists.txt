# examples/uaf/src/client/CMakeLists.txt



# declare the targets
set(  UAF_CLIENT_EXAMPLES
      easiest_client_example
      how_to_read_some_data
      how_to_browse_some_nodes
      how_to_read_some_historical_data
      how_to_change_the_default_session_behavior
      how_to_change_the_default_subscription_behavior
   )


foreach(UAF_CLIENT_EXAMPLE ${UAF_CLIENT_EXAMPLES})

    # Add an executable for the example
    add_executable(${UAF_CLIENT_EXAMPLE} ${UAF_CLIENT_EXAMPLE}.cpp)
    
    # Link the executable.
    if(WIN32)
        target_link_libraries(${UAF_CLIENT_EXAMPLE} 
                              uafclient uafutil 
                              uaclient ${OPENSSL_LIBRARIES}
                              uabase uapki uastack oleaut32 ole32 
                              Version ws2_32 rpcrt4 crypt32)
    else(WIN32)
        target_link_libraries(${UAF_CLIENT_EXAMPLE} 
                              uafclient uafutil
                              ssl crypto dl rt pthread 
                              uafutil uabase uapki uastack xmlparser)
    endif(WIN32)
    
    
    
    # Set the output directory for the C++ test to the previously defined output directory
    set_target_properties(${UAF_CLIENT_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY         "${EXAMPLES_UAF_BIN_DIR}")
    set_target_properties(${UAF_CLIENT_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${EXAMPLES_UAF_BIN_DIR}")
    set_target_properties(${UAF_CLIENT_EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXAMPLES_UAF_BIN_DIR}")
    

endforeach(UAF_CLIENT_EXAMPLE)
