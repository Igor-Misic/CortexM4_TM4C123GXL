################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./core/src/vl53l1_api.obj" \
"./core/src/vl53l1_api_calibration.obj" \
"./core/src/vl53l1_api_core.obj" \
"./core/src/vl53l1_api_debug.obj" \
"./core/src/vl53l1_api_preset_modes.obj" \
"./core/src/vl53l1_api_strings.obj" \
"./core/src/vl53l1_core.obj" \
"./core/src/vl53l1_core_support.obj" \
"./core/src/vl53l1_error_strings.obj" \
"./core/src/vl53l1_register_funcs.obj" \
"./core/src/vl53l1_silicon_core.obj" \
"./core/src/vl53l1_wait.obj" \
"./platform/src/vl53l1_i2c_comms.obj" \
"./platform/src/vl53l1_platform.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include core/src/subdir_vars.mk
-include platform/src/subdir_vars.mk
-include subdir_rules.mk
-include core/src/subdir_rules.mk
-include platform/src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
VL53L1.out \

EXE_OUTPUTS__QUOTED += \
"VL53L1.out" \

BIN_OUTPUTS += \
VL53L1.hex \

BIN_OUTPUTS__QUOTED += \
"VL53L1.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "VL53L1.out"

# Tool invocations
VL53L1.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"VL53L1.map" --heap_size=0 --stack_size=512 -i"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/lib" -i"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="VL53L1_linkInfo.xml" --rom_model -o "VL53L1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

VL53L1.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armhex"  -o "VL53L1.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "core/src/vl53l1_api.obj" "core/src/vl53l1_api_calibration.obj" "core/src/vl53l1_api_core.obj" "core/src/vl53l1_api_debug.obj" "core/src/vl53l1_api_preset_modes.obj" "core/src/vl53l1_api_strings.obj" "core/src/vl53l1_core.obj" "core/src/vl53l1_core_support.obj" "core/src/vl53l1_error_strings.obj" "core/src/vl53l1_register_funcs.obj" "core/src/vl53l1_silicon_core.obj" "core/src/vl53l1_wait.obj" "platform/src/vl53l1_i2c_comms.obj" "platform/src/vl53l1_platform.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "core/src/vl53l1_api.d" "core/src/vl53l1_api_calibration.d" "core/src/vl53l1_api_core.d" "core/src/vl53l1_api_debug.d" "core/src/vl53l1_api_preset_modes.d" "core/src/vl53l1_api_strings.d" "core/src/vl53l1_core.d" "core/src/vl53l1_core_support.d" "core/src/vl53l1_error_strings.d" "core/src/vl53l1_register_funcs.d" "core/src/vl53l1_silicon_core.d" "core/src/vl53l1_wait.d" "platform/src/vl53l1_i2c_comms.d" "platform/src/vl53l1_platform.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

