################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32f103_Drivers/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS/subdir.mk
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
BlinkingLED_RTOS_Session1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BlinkingLED_RTOS_Session1.list \

OBJCOPY_BIN += \
BlinkingLED_RTOS_Session1.bin \


# All Target
all: BlinkingLED_RTOS_Session1.elf secondary-outputs

# Tool invocations
BlinkingLED_RTOS_Session1.elf: $(OBJS) $(USER_OBJS) E:\Embedded\ system\ (KS)\term\ 3\Unit\ 15_Create\ your\ Own\ RTOS_not\ complete\FreeRTOS\ Section\ 1\blinking\ led\ FreeRTOS\BlinkingLED_RTOS_Session1\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "BlinkingLED_RTOS_Session1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Embedded system (KS)\term 3\Unit 15_Create your Own RTOS_not complete\FreeRTOS Section 1\blinking led FreeRTOS\BlinkingLED_RTOS_Session1\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BlinkingLED_RTOS_Session1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BlinkingLED_RTOS_Session1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BlinkingLED_RTOS_Session1.list"
	@echo 'Finished building: $@'
	@echo ' '

BlinkingLED_RTOS_Session1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "BlinkingLED_RTOS_Session1.bin"
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
