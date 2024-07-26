################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32_F103C6_Drivers/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MY_RTOS/subdir.mk
-include HAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EXTI\ DRIVER.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EXTI\ DRIVER.list \

OBJCOPY_BIN += \
EXTI\ DRIVER.bin \


# All Target
all: EXTI\ DRIVER.axf secondary-outputs

# Tool invocations
EXTI\ DRIVER.axf: $(OBJS) $(USER_OBJS) E:\Embedded\ system\ (KS)\term\ 3\Unit\ 15_Create\ your\ Own\ RTOS_not\ complete\3-Create\ Your\ own\ RTOS\ Scheduler\ PART\ 1\My_RTOS\DRIVERS2(+EXTI)\EXTI\ DRIVER\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "EXTI DRIVER.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Embedded system (KS)\term 3\Unit 15_Create your Own RTOS_not complete\3-Create Your own RTOS Scheduler PART 1\My_RTOS\DRIVERS2(+EXTI)\EXTI DRIVER\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EXTI DRIVER.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EXTI\ DRIVER.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EXTI DRIVER.list"
	@echo 'Finished building: $@'
	@echo ' '

EXTI\ DRIVER.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "EXTI DRIVER.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
