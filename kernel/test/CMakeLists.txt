set(TEST_PROJECT_NAME kernelTests)
project(${TEST_PROJECT_NAME} CXX C)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

set(LIBRARY_TESTS_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/KernelTests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/collections/ArrayTest.cpp
        collections/BlockingQueueTest.cpp
        collections/PriorityQueueTest.cpp
        collections/StaticPriorityQueueTest.cpp
        system/MemoryAllocatorTest.cpp
)

#if (NOT (TARGET gtest AND TARGET gtest_main))
#    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
#endif()

add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})
target_link_libraries(${TEST_PROJECT_NAME}
        gtest
        gmock
        ${LIBRARY_NAME}
)

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})