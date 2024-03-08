cmake_minimum_required(VERSION 3.23)
project(avr CXX C)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
#set(CMAKE_CXX_FLAGS_DEBUG "-Os")

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
add_compile_options("-finline-functions")
#add_compile_options("-mdouble=64")
#add_compile_options("-fpermissive")

add_link_options(-Wl,--print-memory-usage,--gc-sections,-u,vfprintf -lprintf_flt -lm)
add_link_options("-mmcu=${TARGET_CPU}")

add_executable(${PROJECT_NAME}
        src/port/avr/atmega328p/SerialPort0.h
        src/port/avr/atmega328p/SerialPort0.cpp
        src/port/avr/atmega328p/WallClock.cpp
        src/port/avr/AVRContextSwitcher.h
        src/system/WallClock.h
        src/Main.cpp
        src/comms/USART.h
        src/collections/BlockingQueue.h
        src/collections/Array.h
        src/std/Random.cpp src/std/Random.h
        src/std/String.h
        src/events/Message.h
        src/events/MessageType.h
        src/events/EventLoop.h
        src/events/Subscriber.h
        src/events/Messaging.h
        src/system/TaskScheduler.cpp src/system/TaskScheduler.h
        src/system/Task.h src/system/Task.cpp
        src/collections/PriorityQueue.cpp src/collections/PriorityQueue.h
        src/events/HandlerMultiplexer.h
        src/events/SubscriberRegistry.h
        src/events/SubscriberRegistry.h
        src/system/Math.h
        src/comms/Serial.cpp src/comms/Serial.h
        src/system/OS.h src/system/OS.cpp
        src/collections/StaticPriorityQueue.h
        src/system/MemoryAllocator.h src/system/MemoryAllocator.cpp
        src/system/Promise.h
        src/system/TaskExecPromise.h
        src/system/PeriodicTask.h
        src/system/Stack.h
        src/system/StaticStack.h
        src/system/PromiseWithReturn.h
        src/system/ContextSwitcher.h
        src/console/Shell.h
        src/console/App.h
        src/apps/InfiniteTask.cpp src/apps/InfiniteTask.h
        src/apps/PerformanceReporter.h
        src/apps/PiTask.h
        src/apps/BuTask.h
        src/console/Console.h
        src/system/TimeWaitPromise.h
        src/console/ShellCommand.h
        src/console/commands/List.h
        src/console/Shell.cpp
        src/console/commands/Clear.h
        src/io/Keyboard.h
        src/io/KeyPressEvent.h
        src/system/Event.h
        src/apps/NewTaskModel.h
        src/apps/NewTaskModel.cpp
        src/apps/Process.h
)

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
