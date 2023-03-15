################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/15"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf_driver/subdir.mk
-include zf_device/subdir.mk
-include zf_common/subdir.mk
-include user_c/subdir.mk
-include sdk/Startup/subdir.mk
-include sdk/Peripheral/subdir.mk
-include sdk/Core/subdir.mk
-include code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
SECONDARY_FLASH += \
Bicycle_Code.hex \

SECONDARY_LIST += \
Bicycle_Code.lst \

SECONDARY_SIZE += \
Bicycle_Code.siz \


# 所有目标
all: Bicycle_Code.elf secondary-outputs

# 工具调用
Bicycle_Code.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"C:\Users\86152\Desktop\单车越野\我的\代码调试\Bicycle_Code\libraries\zf_device" -Wl,-Map,"Bicycle_Code.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -Wl,--print-memory-usage -o "Bicycle_Code.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
Bicycle_Code.hex: Bicycle_Code.elf
	@	riscv-none-embed-objcopy -O ihex "Bicycle_Code.elf"  "Bicycle_Code.hex"
	@	@
Bicycle_Code.lst: Bicycle_Code.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "Bicycle_Code.elf" > "Bicycle_Code.lst"
	@	@
Bicycle_Code.siz: Bicycle_Code.elf
	@	riscv-none-embed-size --format=berkeley "Bicycle_Code.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Bicycle_Code.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
