################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/Biblioteca Info 2" -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion" -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Primitivas" -I"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/Biblioteca Info 2/bibliotecaInfoII.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/maquinaControl.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/maquinaEjecutando.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/maquinaGeneral.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/Aplicacion/timers.h" -include"/home/lucas/Desktop/Informatica 2/TPO/gimbal_workspace/Gimbal/inc/main.h" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


