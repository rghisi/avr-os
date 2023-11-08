cmake_minimum_required(VERSION 3.23)
project(avr CXX C)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_DEBUG "-Os")

#include(CMakeVerifyCompiler.txt)

set(TARGET_CPU atmega328p)
set(F_CPU 16000000L)

set(AVR_DUDE_EXECUTABLE /usr/bin/avrdude)
set(AVR_DUDE_PORT /dev/ttyUSB0)

add_compile_definitions("F_CPU=${F_CPU}")
add_compile_options("-mmcu=${TARGET_CPU}")
add_compile_options("-mcall-prologues")
add_compile_options("-I${CMAKE_SOURCE_DIR}/avr-libstdcpp/include")
add_compile_options("-fdata-sections")
add_compile_options("-ffunction-sections")
#add_compile_options("-mdouble=64")
#add_compile_options("-fpermissive")

add_link_options(-Wl,--print-memory-usage,--gc-sections,-u,vfprintf -lprintf_flt -lm)
add_link_options("-mmcu=${TARGET_CPU}")

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/hw/Timer0.h
        src/hw/USART.h
#        src/hw/avr/ATMega32U4.cpp src/hw/avr/ATMega32U4.h
        src/hw/avr/ATMega328P.cpp src/hw/avr/ATMega328P.h
        src/collections/BlockingQueue.h
        src/collections/Array.cpp src/collections/Array.h
#        src/std/CRC.cpp src/std/CRC.h
        src/std/Random.cpp src/std/Random.h
        src/system/WallClock.cpp src/system/WallClock.h
        src/events/Message.cpp src/events/Message.h
        src/events/MessageType.h
        src/events/EventLoop.cpp src/events/EventLoop.h
        src/events/Subscriber.cpp src/events/Subscriber.h
        src/events/Messaging.cpp src/events/Messaging.h
        src/system/TaskScheduler.cpp src/system/TaskScheduler.h
        src/system/Task.h src/system/Task.cpp
        src/system/CpuStats.cpp src/system/CpuStats.h
        src/collections/PriorityQueue.cpp src/collections/PriorityQueue.h
        src/std/CRCTable.c
        src/hw/Timer1.h src/hw/ExternalInterrupts.h
        src/events/TaskSchedulingRequested.cpp
        src/events/TaskSchedulingRequested.h
        src/events/HandlerMultiplexer.cpp src/events/HandlerMultiplexer.h
        src/events/SubscriberRegistry.h
        src/events/SubscriberRegistry.cpp src/events/SubscriberRegistry.h
        src/system/Math.h
        src/comms/Serial.cpp src/comms/Serial.h
        src/comms/SerialPacket.cpp src/comms/SerialPacket.h
        src/system/OS.h src/system/OS.cpp
        src/services/InfiniteTask.cpp src/services/InfiniteTask.h
        src/services/PerformanceReporter.cpp src/services/PerformanceReporter.h
        src/collections/StaticPriorityQueue.h
        src/system/MemoryAllocator.h src/system/MemoryAllocator.cpp
        src/services/PiTask.h
        src/services/PiTask.cpp
        src/system/StaticTask.h
        src/system/Promise.h)

set(FLASH_VERBOSE_FLAG "-v")
add_custom_target(FLASH
        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -carduino -b115200 -P ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
        DEPENDS ${PROJECT_NAME}
        COMMENT "Flash to ${TARGET_CPU}")

add_custom_command(
        POST_BUILD
        TARGET ${PROJECT_NAME}
        COMMAND avr-size --mcu=atmega328p -C ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
        COMMENT "Size:"
)

#32u4
#add_custom_target(FLASH
#        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -cavr109 -b57600 -Kp ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
#        DEPENDS ${PROJECT_NAME}
#        COMMENT "Flash to ${TARGET_CPU}")
