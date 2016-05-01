cmake_minimum_required(VERSION 3.2)
project (helloworld)
#version number
set (helloworld_VERSION_MAJOR 1)
set (helloworld_VERSION_MINOR 0)
# set commands
set(CMAKE_LINSTALL_COMMAND ${CMAKE_BINARY_DIR}/src/setuplambda.sh)
set(CMAKE_LUPDATE_COMMAND  ${CMAKE_BINARY_DIR}/src/updatelambda.sh)
set(CMAKE_CHECK_COMMAND    python ${CMAKE_SOURCE_DIR}/src/lambda/test_invoke.py)
set(ROLE		   $ROLE)
set(LAMBDA_NAME		   $LAMBDA_NAME)


if(NOT ${CMAKE_VERSION} LESS 3.2)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else()
    message(STATUS "Checking compiler flags for C++11 support.")
    # Set C++11 support flags for various compilers
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
    check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        message(STATUS "C++11 is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        endif()
    elseif(COMPILER_SUPPORTS_CXX0X)
        message(STATUS "C++0x is supported.")
        if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        endif()
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

SET(GCC_COVERAGE_COMPILE_FLAGS "-pedantic -pedantic-errors -std=c++11 -g -O2")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#include the subdirectory containing our libs
add_subdirectory (src)
include_directories(src)
add_subdirectory(opt)
link_directories("/usr/local/lib")
include_directories("/usr/include/openssl")
include_directories("/usr/local/include" ${CPR_INCLUDE_DIRS})
add_executable(rahul src/signinvoke/main.cpp src/signinvoke/awsv4.cpp src/signinvoke/awsv4.hpp)
target_link_libraries(rahul crypto PocoNet PocoFoundation ${CPR_LIBRARIES})


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
