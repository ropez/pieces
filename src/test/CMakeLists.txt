OPTION(BUILD_TESTS "build the tests" OFF)

if(BUILD_TESTS)

set(test_SOURCES
    testrunner.cpp
    test_message.cpp
)

add_executable(testrunner ${test_SOURCES})
target_link_libraries(testrunner cppunit dl pieces ${OPENTHREADS_LIBRARIES})

set(tests
    TestMessageType
    TestMessageFlags
)

foreach(test ${tests})
    add_test(NAME ${test} COMMAND testrunner ${test})
endforeach(test)

endif(BUILD_TESTS)
