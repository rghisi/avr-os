cmake_minimum_required(VERSION 3.14)
project(PlantWateringTests CXX C)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        src/Main.cpp
        ../../avr/src/networking/Packet.h ../../avr/src/networking/Packet.cpp src/PacketTest.cpp
        ../../avr/src/collections/BlockingQueue.h ../../avr/src/collections/BlockingQueue.cpp src/BlockingQueueTest.cpp
        ../../avr/src/networking/PacketBuilder.h ../../avr/src/networking/PacketBuilder.cpp src/PacketBuilderTest.cpp
        ../../avr/src/std/CRC.h ../../avr/src/std/CRC.cpp src/CRCTest.cpp)

target_link_libraries(${PROJECT_NAME} gtest)