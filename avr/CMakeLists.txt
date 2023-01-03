cmake_minimum_required(VERSION 3.23)
project(avr CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#include(CMakeVerifyCompiler.txt)

set(TARGET_CPU atmega328p)
set(F_CPU 16000000L)

set(AVR_DUDE_EXECUTABLE /usr/bin/avrdude)
set(AVR_DUDE_PORT /dev/ttyUSB0)

add_compile_definitions("F_CPU=${F_CPU}")
add_compile_options("-mmcu=${TARGET_CPU}")
add_compile_options("-I${CMAKE_SOURCE_DIR}/avr-libstdcpp/include")
add_compile_options("-fdata-sections")
add_compile_options("-ffunction-sections")

add_link_options(-Wl,--print-memory-usage,--gc-sections)
add_link_options("-mmcu=${TARGET_CPU}")

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/hw/Timer0.h
        src/hw/USART.h
#        src/hw/avr/ATMega32U4.cpp src/hw/avr/ATMega32U4.h
        src/hw/avr/ATMega328P.cpp src/hw/avr/ATMega328P.h
#        src/networking/Packet.h
#        src/networking/Packet.cpp
#        src/networking/NetworkInterface.h
#        src/network-interfaces/SerialNetworkInterface.h
#        src/network-interfaces/SerialNetworkInterface.cpp
#        src/networking/PacketBuilder.cpp src/networking/PacketBuilder.h
        src/collections/BlockingQueue.cpp src/collections/BlockingQueue.h
        src/collections/Array.cpp src/collections/Array.h
#        src/std/CRC.cpp src/std/CRC.h
#        src/std/Random.cpp src/std/Random.h
#        src/network-services/PacketSender.h
#        src/network-services/PacketReceiver.h
#        src/network-services/NetworkServices.cpp src/network-services/NetworkServices.h
#        src/network-services/Ping.cpp src/network-services/Ping.h
        src/system/WallClock.cpp src/system/WallClock.h
#        src/networking/PacketReader.cpp src/networking/PacketReader.h
        src/system/Message.cpp src/system/Message.h
        src/system/MessageType.h
        src/system/EventLoop.cpp src/system/EventLoop.h
        src/system/Subscriber.cpp src/system/Subscriber.h
        src/system/Messaging.cpp src/system/Messaging.h
#        src/network-services/Services.h
        src/system/TaskScheduler.cpp src/system/TaskScheduler.h
        src/system/Task.h
#        src/tasks/PeriodicPing.cpp src/tasks/PeriodicPing.h
        src/tasks/PeriodicCpuUsageReport.cpp src/tasks/PeriodicCpuUsageReport.h
        src/system/CpuStats.cpp src/system/CpuStats.h
        src/lcd/Display.cpp src/lcd/Display.h
        src/lcd/one/HD44780.h src/lcd/one/HD44780.c src/lcd/one/HD44780_Settings.h src/lcd/one/IO_Macros.h
        src/system/AsyncFunction.cpp src/system/AsyncFunction.h
        src/tasks/AsyncTaskTest.cpp src/tasks/AsyncTaskTest.h
        src/system/AsyncExecutor.cpp src/system/AsyncExecutor.h
        src/system/AsyncChain.cpp src/system/AsyncChain.h
        src/collections/PriorityQueue.cpp src/collections/PriorityQueue.h
        src/system/AsyncWaitTask.cpp src/system/AsyncWaitTask.h
        src/tasks/PeriodicMemoryReport.cpp src/tasks/PeriodicMemoryReport.h
        src/std/CRCTable.c
        src/lcd/two/HD44780.h src/lcd/two/HD44780.cpp
#        src/lcd/two/HD44780_Settings.h src/lcd/two/IO_Macros.h
        src/pid/PID.cpp src/pid/PID.h src/input/KeyPad.cpp src/input/KeyPad.h src/hw/Interrupts.h
        src/sensors/i2cmaster.h src/sensors/i2cmaster.c
        src/sensors/bme280_i2c.h src/sensors/bme280_i2c.c
        src/tasks/PeriodicSensorReport.cpp src/tasks/PeriodicSensorReport.h
        src/sensors/ClimateReport.cpp src/sensors/ClimateReport.h
        src/hw/Timer1.h src/hw/ExternalInterrupts.h
        src/dimmer/Dimmer.cpp src/dimmer/Dimmer.h
        src/tasks/TemperatureControl.cpp src/tasks/TemperatureControl.h
        src/input/Dial.h src/input/Dial.cpp
        src/input/UserInput.cpp src/input/UserInput.h
        src/app/Test.cpp src/app/Test.h
        src/time/TimeTicker.cpp src/time/TimeTicker.h
        src/time/TimeTick.cpp src/time/TimeTick.h
        src/app/TimedDrying.cpp src/app/TimedDrying.h
        src/lcd/DrawText.cpp src/lcd/DrawText.h
        src/system/TaskSchedulingRequested.cpp
        src/system/TaskSchedulingRequested.h src/system/AsyncChainSchedulingRequest.cpp
        src/system/AsyncChainSchedulingRequest.h
        src/lcd/EnableCursor.cpp src/lcd/EnableCursor.h
        src/lcd/DisplayCommand.cpp src/lcd/DisplayCommand.h
        src/system/HandlerMultiplexer.cpp src/system/HandlerMultiplexer.h
        src/app/Application.cpp src/app/Application.h
        src/app/ApplicationManager.cpp src/app/ApplicationManager.h
        src/lcd/ClearDisplay.cpp src/lcd/ClearDisplay.h
        src/lcd/DisableCursor.cpp src/lcd/DisableCursor.h
        src/tasks/TemperatureControlCommand.cpp src/tasks/TemperatureControlCommand.h
        src/system/SubscriberRegistry.h
        src/system/SubscriberRegistry.cpp src/system/SubscriberRegistry.h src/app/TimedMultiTrayDrying.cpp src/app/TimedMultiTrayDrying.h src/time/Timer.cpp src/time/Timer.h src/time/TimerState.cpp src/time/TimerState.h src/system/Math.cpp src/system/Math.h src/tasks/TemperatureControlStatus.cpp src/tasks/TemperatureControlStatus.h)

set(FLASH_VERBOSE_FLAG "-v")
add_custom_target(FLASH
        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -carduino -b57600 -P ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
        DEPENDS ${PROJECT_NAME}
        COMMENT "Flash to ${TARGET_CPU}")

#32u4
#add_custom_target(FLASH
#        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -cavr109 -b57600 -P ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
#        DEPENDS ${PROJECT_NAME}
#        COMMENT "Flash to ${TARGET_CPU}")
