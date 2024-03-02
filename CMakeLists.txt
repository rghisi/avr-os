cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_C_COMPILER /opt/avr-gcc/bin/avr-gcc)
#set(CMAKE_CXX_COMPILER /opt/avr-gcc/bin/avr-g++)
#set(CMAKE_FIND_ROOT_PATH /opt/avr-gcc)


project(avr_os LANGUAGES CXX C)

#add_library(kernel STATIC)
#target_include_directories(kernel PRIVATE "${PROJECT_SOURCE_DIR}/kernel")
add_subdirectory("kernel")

add_executable(tests)
target_sources(tests PRIVATE "kernel/test/KernelTests.cpp")

#add_subdirectory(ports/avr/avr-libstdcpp)
#add_subdirectory("ports/avr/atmega328p")