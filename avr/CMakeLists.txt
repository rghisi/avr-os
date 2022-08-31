cmake_minimum_required(VERSION 3.23)
project(avr CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

include(CMakeVerifyCompiler.txt)

set(TARGET_CPU ATmega32U4)
set(F_CPU 16000000L)


add_compile_definitions("__AVR_${TARGET_CPU}__")
add_compile_definitions("F_CPU=${F_CPU}")
add_link_options(-Wl,--print-memory-usage)

add_executable(${PROJECT_NAME} src/Main.cpp src/Packet.cpp src/PacketFactory.cpp src/NetworkService.cpp)
