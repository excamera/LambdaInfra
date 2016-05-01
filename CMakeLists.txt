cmake_minimum_required (VERSION 2.8)
project (helloworld C)

#version number
set (helloworld_VERSION_MAJOR 1)
set (helloworld_VERSION_MINOR 0)

# set commands
set(CMAKE_LINSTALL_COMMAND ${CMAKE_BINARY_DIR}/src/setuplambda.sh)
set(CMAKE_LUPDATE_COMMAND  ${CMAKE_BINARY_DIR}/src/updatelambda.sh)
set(CMAKE_CHECK_COMMAND    python ${CMAKE_SOURCE_DIR}/src/lambda/test_invoke.py)
set(ROLE		   $ROLE)
set(LAMBDA_NAME		   $LAMBDA_NAME)

#include the subdirectory containing our libs
add_subdirectory (src)
include_directories(src)

#indicate the entry point for the executable
#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable (helloworld src)

# set properties
set_target_properties(helloworld PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(helloworld PROPERTIES LINK_SEARCH_END_STATIC 1)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set_target_properties(helloworld PROPERTIES LINKER_LANGUAGE C)




# Indicate which libraries to include during the link process.
target_link_libraries (helloworld lambda)

# Install targets
install (TARGETS helloworld DESTINATION bin)

# Add custom targets
add_custom_target(check         COMMAND ${CMAKE_CHECK_COMMAND})
add_custom_target(lambdainstall COMMAND ${CMAKE_LINSTALL_COMMAND})
add_custom_target(lambdaupdate COMMAND ${CMAKE_LUPDATE_COMMAND})


configure_file (
  "${CMAKE_SOURCE_DIR}/src/lambda/setuplambda.sh"
  "${CMAKE_BINARY_DIR}/src/setuplambda.sh"

  )
configure_file (
  "${CMAKE_SOURCE_DIR}/src/lambda/updatelambda.sh"
  "${CMAKE_BINARY_DIR}/src/updatelambda.sh"
  )
