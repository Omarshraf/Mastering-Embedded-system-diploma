################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32f103_Drivers/Stm32_F103C6_RCC_driver.c \
../Stm32f103_Drivers/Stm32_F103C6_gpio_driver.c 

OBJS += \
./Stm32f103_Drivers/Stm32_F103C6_RCC_driver.o \
./Stm32f103_Drivers/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./Stm32f103_Drivers/Stm32_F103C6_RCC_driver.d \
./Stm32f103_Drivers/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32f103_Drivers/Stm32_F103C6_RCC_driver.o: ../Stm32f103_Drivers/Stm32_F103C6_RCC_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/FreeRTOS Section 1/blinking led FreeRTOS/BlinkingLED_RTOS_Session1/FreeRTOS/include" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/FreeRTOS Section 1/blinking led FreeRTOS/BlinkingLED_RTOS_Session1/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32f103_Drivers/Stm32_F103C6_RCC_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32f103_Drivers/Stm32_F103C6_gpio_driver.o: ../Stm32f103_Drivers/Stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/FreeRTOS Section 1/blinking led FreeRTOS/BlinkingLED_RTOS_Session1/FreeRTOS/include" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/FreeRTOS Section 1/blinking led FreeRTOS/BlinkingLED_RTOS_Session1/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32f103_Drivers/Stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

