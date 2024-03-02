cmake_minimum_required(VERSION 3.27)
project(kernel CXX C)

set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_NAME kernel)
set(LIBRARY_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(LIBRARY_HEADERS
        include/collections/Array.h
        include/collections/PriorityQueue.h
        include/comms/Serial.h
        include/system/MemoryAllocator.h
        include/comms/USART.h
        include/console/App.h
        include/console/Console.h
        include/console/Shell.h
        include/console/ShellCommand.h
        include/events/EventLoop.h
        include/events/HandlerMultiplexer.h
        include/events/Message.h
        include/events/MessageType.h
        include/events/Messaging.h
        include/events/Subscriber.h
        include/events/SubscriberRegistry.h
        include/io/Keyboard.h
        include/io/KeyPressEvent.h
        include/std/CRC.h
        include/std/Random.h
        include/system/ContextSwitcher.h
        include/system/Event.h
        include/system/HeapStack.h
        include/system/Math.h
        include/system/OS.h
        include/system/PeriodicTask.h
        include/system/PromiseWithReturn.h
        include/system/Stack.h
        include/system/StaticStack.h
        include/system/Task.h
        include/system/TaskExecPromise.h
        include/system/TaskScheduler.h
        include/system/TimeWaitPromise.h
        include/system/WallClock.h
)

set(LIBRARY_SOURCE
        src/comms/Serial.cpp
        src/console/Shell.cpp
        src/std/CRC.cpp
        src/std/Random.cpp
        src/system/OS.cpp
        src/system/Task.cpp
        src/system/TaskScheduler.cpp
        src/apps/AnnoyingTask.h
        src/apps/BuTask.h
        src/apps/InfiniteTask.cpp
        src/apps/InfiniteTask.h
        src/apps/PerformanceReporter.h
        src/apps/PiTask.h
)

add_library(${LIBRARY_NAME} STATIC
        ${LIBRARY_HEADERS}
        ${LIBRARY_SOURCE}
)

target_include_directories(${LIBRARY_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(${LIBRARY_NAME} PRIVATE
        ${LIBRARY_SOURCE}
)

#add_subdirectory(test)