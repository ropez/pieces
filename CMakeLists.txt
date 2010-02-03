cmake_minimum_required(VERSION 2.6)

project(pieces)

enable_testing()
include(CTest)

include_directories(include)
add_subdirectory(include)
add_subdirectory(src)
