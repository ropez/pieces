cmake_minimum_required(VERSION 2.6)

option(BUILD_TESTS "Build the test suite"  OFF)
option(BUILD_EXAMPLES "Build the examples"  OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

project(pieces)

include_directories(include)

find_package(OpenThreads REQUIRED)
include_directories(${OPENTHREADS_INCLUDE_DIR})

enable_testing()
include(CTest)

find_package(CppUnit)

if(NOT CppUnit_FOUND AND BUILD_TESTS)
    message(STATUS "CppUnit not found, disabling tests.")
    set(BUILD_TESTS OFF)
endif(NOT CppUnit_FOUND AND BUILD_TESTS)

add_subdirectory(include)
add_subdirectory(src)
