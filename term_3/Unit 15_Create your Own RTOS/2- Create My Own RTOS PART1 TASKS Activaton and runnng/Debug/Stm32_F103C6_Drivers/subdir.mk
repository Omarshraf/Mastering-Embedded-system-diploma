################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.c \
../Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.c 

OBJS += \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o \
./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d \
./Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_EXTI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.o: ../Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

