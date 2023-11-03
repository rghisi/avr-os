cmake_minimum_required(VERSION 3.14)
project(AVROSTests CXX C)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/Main.cpp
        ../../avr/src/collections/BlockingQueue.h ../../avr/src/collections/BlockingQueue.cpp src/collections/BlockingQueueTest.cpp
        ../../avr/src/collections/Array.h ../../avr/src/collections/Array.cpp src/collections/ArrayTest.cpp
        ../../avr/src/collections/PriorityQueue.h ../../avr/src/collections/PriorityQueue.cpp src/collections/PriorityQueueTest.cpp
        src/system/MemoryAllocatorTest.cpp ../../avr/src/system/MemoryAllocator.h ../../avr/src/system/MemoryAllocator.cpp
        src/collections/StaticPriorityQueueTest.cpp ../../avr/src/collections/StaticPriorityQueue.h ../../avr/src/collections/StaticPriorityQueue.cpp )

target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)