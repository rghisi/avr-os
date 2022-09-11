cmake_minimum_required(VERSION 3.23)
project(avr CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

include(CMakeVerifyCompiler.txt)

set(TARGET_CPU atmega32u4)
set(F_CPU 16000000L)

set(AVR_DUDE_EXECUTABLE /usr/bin/avrdude)
set(AVR_DUDE_PORT /dev/ttyACM0)

add_compile_definitions("F_CPU=${F_CPU}")
add_compile_options("-mmcu=${TARGET_CPU}")
add_compile_options("-I${CMAKE_SOURCE_DIR}/avr-libstdcpp/include")

add_link_options(-Wl,--print-memory-usage)
add_link_options("-mmcu=${TARGET_CPU}")

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/networking/Packet.h
        src/networking/Packet.cpp
        src/networking/NetworkInterface.h
        src/networking/SerialNetworkInterface.h
        src/networking/SerialNetworkInterface.cpp
        src/networking/PacketBuilder.cpp src/networking/PacketBuilder.h
        src/collections/BlockingQueue.cpp src/collections/BlockingQueue.h
        src/collections/Array.cpp src/collections/Array.h
        src/std/CRC.cpp src/std/CRC.h
        src/hw/USART.h
        src/hw/avr/ATMega32U4.cpp src/hw/avr/ATMega32U4.h
        src/std/Random.cpp src/std/Random.h
        src/network-services/Sender.h
        src/network-services/Message.cpp src/network-services/Message.h
        src/network-services/Receiver.h
        src/network-services/NetworkServices.cpp src/network-services/NetworkServices.h
        src/network-services/Ping.cpp src/network-services/Ping.h)

set(FLASH_VERBOSE_FLAG "-v")
add_custom_target(FLASH
        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -cavr109 -b57600 -P ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
        DEPENDS ${PROJECT_NAME}
        COMMENT "Flash to ${TARGET_CPU}")
