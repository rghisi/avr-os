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

add_link_options(-Wl,--print-memory-usage)
add_link_options("-mmcu=${TARGET_CPU}")

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/Packet.h
        src/Packet.cpp
        src/NetworkService.cpp
        src/NetworkInterface.h
        src/SerialNetworkInterface.h
        src/SerialNetworkInterface.cpp
        src/BlockingQueue.cpp
        src/BlockingQueue.h src/PacketBuilder.cpp src/PacketBuilder.h
        src/CRC.cpp src/CRC.h)

set(FLASH_VERBOSE_FLAG "-v")
add_custom_target(FLASH
        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -cavr109 -b57600 -P ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
        DEPENDS ${PROJECT_NAME}
        COMMENT "Flash to ${TARGET_CPU}")
