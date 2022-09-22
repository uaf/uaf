# pyuaf/CMakeLists.txt

# define the lib/pyuaf directory
set(LIB_PYUAF_DIR ${PROJECT_SOURCE_DIR}/../lib/pyuaf)

# create the lib/pyuaf directory
file(MAKE_DIRECTORY ${LIB_PYUAF_DIR})

# Copy the __init__.py file
configure_file(  "__init__.py"   "${LIB_PYUAF_DIR}"  )


# add the subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/pyuaf/util)
add_subdirectory(${PROJECT_SOURCE_DIR}/pyuaf/client)

