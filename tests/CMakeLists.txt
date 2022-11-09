cmake_minimum_required(VERSION 3.14)
project(PlantWateringTests CXX C)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/Main.cpp
#        ../../avr/src/networking/Packet.h ../../avr/src/networking/Packet.cpp src/networking/PacketTest.cpp
        ../../avr/src/collections/BlockingQueue.h ../../avr/src/collections/BlockingQueue.cpp src/collections/BlockingQueueTest.cpp
        ../../avr/src/collections/Array.h ../../avr/src/collections/Array.cpp src/collections/ArrayTest.cpp
#        ../../avr/src/networking/PacketBuilder.h ../../avr/src/networking/PacketBuilder.cpp src/networking/PacketBuilderTest.cpp
#        ../../avr/src/std/CRC.h ../../avr/src/std/CRC.cpp src/std/CRCTest.cpp
        ../../avr/src/network-services/PacketSender.h
#        ../../avr/src/network-services/Ping.h ../../avr/src/network-services/Ping.cpp src/network-services/PingTest.cpp
#        ../../avr/src/networking/PacketReader.h ../../avr/src/networking/PacketReader.cpp src/networking/PacketReaderTest.cpp
        ../../avr/src/collections/PriorityQueue.h ../../avr/src/collections/PriorityQueue.cpp src/collections/PriorityQueueTest.cpp)

target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} gmock)