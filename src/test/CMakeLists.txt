if(BUILD_TESTS)

include_directories(${CPPUNIT_INCLUDE_DIR})

set(test_SOURCES
    testrunner.cpp
    test_smart_pointers.cpp
    test_byte_array.cpp
    test_message.cpp
)

add_executable(testrunner ${test_SOURCES})
target_link_libraries(testrunner pieces ${CPPUNIT_LIBRARIES} ${OPENTHREADS_LIBRARIES})

set(tests
    TestSharedData
    TestAutoPointer
    TestByteArray
    TestByteArraySlicing
    TestByteArrayChopping
    TestByteArrayExtending
    TestByteArrayResize
    TestMessageType
    TestMessageFlags
    TestMessageProperties
)

foreach(test ${tests})
    add_test(NAME ${test} COMMAND testrunner ${test})
endforeach(test)

endif(BUILD_TESTS)
