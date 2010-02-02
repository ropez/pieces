OPTION(BUILD_EXAMPLES "build the examples" OFF)

if(BUILD_EXAMPLES)
add_subdirectory(qchat)
add_subdirectory(pong)
endif(BUILD_EXAMPLES)
