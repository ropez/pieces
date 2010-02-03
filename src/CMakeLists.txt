find_package(OpenThreads REQUIRED)
include(${OPENTHREADS_INCLUDE_DIR})

add_subdirectory(pieces)
add_subdirectory(examples)
add_subdirectory(test)
