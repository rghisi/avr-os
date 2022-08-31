################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NetworkInterfaceMock.cpp \
../src/NetworkService_test.cpp \
../src/Packet_test.cpp \
../src/main.cpp 

CPP_DEPS += \
./src/NetworkInterfaceMock.d \
./src/NetworkService_test.d \
./src/Packet_test.d \
./src/main.d 

OBJS += \
./src/NetworkInterfaceMock.o \
./src/NetworkService_test.o \
./src/Packet_test.o \
./src/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/NetworkInterfaceMock.d ./src/NetworkInterfaceMock.o ./src/NetworkService_test.d ./src/NetworkService_test.o ./src/Packet_test.d ./src/Packet_test.o ./src/main.d ./src/main.o

.PHONY: clean-src

