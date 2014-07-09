################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SvImage.cpp \
../src/SvMain.cpp \
../src/SvMultithreadProcessor.cpp \
../src/SvProcessorV1.cpp \
../src/SvProcessorV2.cpp 

OBJS += \
./src/SvImage.o \
./src/SvMain.o \
./src/SvMultithreadProcessor.o \
./src/SvProcessorV1.o \
./src/SvProcessorV2.o 

CPP_DEPS += \
./src/SvImage.d \
./src/SvMain.d \
./src/SvMultithreadProcessor.d \
./src/SvProcessorV1.d \
./src/SvProcessorV2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I/usr/include/pcl-1.7 -I/usr/include/vtk-5.8/ -I/usr/include/eigen3 -O3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


