cmake_minimum_required(VERSION 3.27)
project(avr-atmega328p CXX C)
set(CMAKE_CXX_STANDARD 17)

set(TARGET_CPU atmega328p)
set(F_CPU 16000000L)

set(AVR_DUDE_EXECUTABLE /usr/bin/avrdude)
set(AVR_DUDE_PORT /dev/ttyUSB0)

#set(CMAKE_C_COMPILER avr-gcc)
#set(CMAKE_CXX_COMPILER avr-g++)
#set(CMAKE_FIND_ROOT_PATH /opt/avr-gcc)

add_compile_definitions("F_CPU=${F_CPU}")
add_compile_options("-mmcu=${TARGET_CPU}")
add_compile_options("-mcall-prologues")
#add_compile_options("-I${CMAKE_CURRENT_SOURCE_DIR}../avr-libstdcpp/include")
#add_compile_options("-I${CMAKE_SOURCE_DIR}/kernel/src")
add_compile_options("-fdata-sections")
add_compile_options("-ffunction-sections")
add_compile_options("-finline-functions")
#add_compile_options("-mdouble=64")
#add_compile_options("-fpermissive")

add_link_options(-Wl,--print-memory-usage,--gc-sections,-u,vfprintf -lprintf_flt -lm)
add_link_options("-mmcu=${TARGET_CPU}")

#set_target_properties(kernel PROPERTIES LINKER_LANGUAGE CXX)
#add_subdirectory(impl)
add_executable(avr-atmega328p
        Atmega328p.cpp
        src/SerialPort0.cpp
        src/SerialPort0.h
        src/WallClock.cpp
)

target_link_libraries(avr-atmega328p kernel)
target_link_libraries(avr-atmega328p AVR-LibStdCpp)


set(FLASH_VERBOSE_FLAG "-v")
add_custom_target(FLASH
        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -carduino -b115200 -P ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
        DEPENDS ${PROJECT_NAME}
        COMMENT "Flash to ${TARGET_CPU}")

add_custom_command(
        POST_BUILD
        TARGET avr-atmega328p
        COMMAND avr-size --mcu=atmega328p -C ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
        COMMENT "Size:"
)

#32u4
#add_custom_target(FLASH
#        ${AVR_DUDE_EXECUTABLE} -p ${TARGET_CPU} -cavr109 -b57600 -Kp ${AVR_DUDE_PORT} ${FLASH_VERBOSE_FLAG} -F -D -U flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}:a
#        DEPENDS ${PROJECT_NAME}
#        COMMENT "Flash to ${TARGET_CPU}")
