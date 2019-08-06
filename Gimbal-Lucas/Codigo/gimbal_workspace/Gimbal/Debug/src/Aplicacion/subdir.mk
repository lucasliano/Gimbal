################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Aplicacion/maquinaControl.c \
../src/Aplicacion/maquinaEjecutando.c \
../src/Aplicacion/maquinaGeneral.c \
../src/Aplicacion/timers.c 

OBJS += \
./src/Aplicacion/maquinaControl.o \
./src/Aplicacion/maquinaEjecutando.o \
./src/Aplicacion/maquinaGeneral.o \
./src/Aplicacion/timers.o 

C_DEPS += \
./src/Aplicacion/maquinaControl.d \
./src/Aplicacion/maquinaEjecutando.d \
./src/Aplicacion/maquinaGeneral.d \
./src/Aplicacion/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/Aplicacion/%.o: ../src/Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/Biblioteca Info 2" -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion" -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Primitivas" -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/Biblioteca Info 2/bibliotecaInfoII.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/maquinaControl.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/maquinaEjecutando.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/maquinaGeneral.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/timers.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/main.h" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


