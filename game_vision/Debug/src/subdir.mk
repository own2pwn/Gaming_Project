################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SendDataToPython.cpp \
../src/SeperateObjects.cpp \
../src/featureextraction.cpp \
../src/main.cpp \
../src/yingyang.cpp 

OBJS += \
./src/SendDataToPython.o \
./src/SeperateObjects.o \
./src/featureextraction.o \
./src/main.o \
./src/yingyang.o 

CPP_DEPS += \
./src/SendDataToPython.d \
./src/SeperateObjects.d \
./src/featureextraction.d \
./src/main.d \
./src/yingyang.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/python2.7 -I/usr/include/boost/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


