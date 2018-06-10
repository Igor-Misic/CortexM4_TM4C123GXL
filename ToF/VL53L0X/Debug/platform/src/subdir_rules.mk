################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
platform/src/vl53l0x_i2c_comms.obj: ../platform/src/vl53l0x_i2c_comms.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L0X" --include_path="/home/igor/workspace_v8/VL53L0X/platform/inc" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L0X/core/inc" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="platform/src/vl53l0x_i2c_comms.d_raw" --obj_directory="platform/src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

platform/src/vl53l0x_platform.obj: ../platform/src/vl53l0x_platform.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L0X" --include_path="/home/igor/workspace_v8/VL53L0X/platform/inc" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L0X/core/inc" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="platform/src/vl53l0x_platform.d_raw" --obj_directory="platform/src" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


