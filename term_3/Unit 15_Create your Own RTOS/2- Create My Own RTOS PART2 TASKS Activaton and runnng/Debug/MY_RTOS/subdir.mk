################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_RTOS/Cortex_Mx_OS_Porting.c \
../MY_RTOS/MY_RTOS_FIFO.c \
../MY_RTOS/scheduler.c 

OBJS += \
./MY_RTOS/Cortex_Mx_OS_Porting.o \
./MY_RTOS/MY_RTOS_FIFO.o \
./MY_RTOS/scheduler.o 

C_DEPS += \
./MY_RTOS/Cortex_Mx_OS_Porting.d \
./MY_RTOS/MY_RTOS_FIFO.d \
./MY_RTOS/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MY_RTOS/Cortex_Mx_OS_Porting.o: ../MY_RTOS/Cortex_Mx_OS_Porting.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MY_RTOS/Cortex_Mx_OS_Porting.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MY_RTOS/MY_RTOS_FIFO.o: ../MY_RTOS/MY_RTOS_FIFO.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MY_RTOS/MY_RTOS_FIFO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MY_RTOS/scheduler.o: ../MY_RTOS/scheduler.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/MY_RTOS/inc" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/CMSIS_V5" -I"E:/Embedded system (KS)/term 3/Unit 15_Create your Own RTOS_not complete/3-Create Your own RTOS Scheduler PART 1/My_RTOS/DRIVERS2(+EXTI)/EXTI DRIVER/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MY_RTOS/scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

