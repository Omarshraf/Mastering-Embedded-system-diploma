################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEY_PAD.c \
../HAL/LCD.c 

OBJS += \
./HAL/KEY_PAD.o \
./HAL/LCD.o 

C_DEPS += \
./HAL/KEY_PAD.d \
./HAL/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KEY_PAD.o: ../HAL/KEY_PAD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/KEY_PAD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/LCD.o: ../HAL/LCD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

