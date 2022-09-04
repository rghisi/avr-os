cmake_minimum_required(VERSION 3.14)
project(PlantWateringTests CXX C)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        src/Main.cpp
        ../../avr/src/Packet.h ../../avr/src/Packet.cpp src/PacketTest.cpp
        ../../avr/src/BlockingQueue.h ../../avr/src/BlockingQueue.cpp src/BlockingQueueTest.cpp
        ../../avr/src/PacketBuilder.h ../../avr/src/PacketBuilder.cpp src/PacketBuilderTest.cpp
        ../../avr/src/CRC.h ../../avr/src/CRC.cpp src/CRCTest.cpp)

target_link_libraries(${PROJECT_NAME} gtest)