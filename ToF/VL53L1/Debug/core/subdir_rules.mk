################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
core/vl53l1_api.obj: ../core/vl53l1_api.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_api.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_api_calibration.obj: ../core/vl53l1_api_calibration.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_api_calibration.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_api_core.obj: ../core/vl53l1_api_core.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_api_core.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_api_debug.obj: ../core/vl53l1_api_debug.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_api_debug.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_api_preset_modes.obj: ../core/vl53l1_api_preset_modes.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_api_preset_modes.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_api_strings.obj: ../core/vl53l1_api_strings.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_api_strings.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_core.obj: ../core/vl53l1_core.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_core.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_core_support.obj: ../core/vl53l1_core_support.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_core_support.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_error_strings.obj: ../core/vl53l1_error_strings.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_error_strings.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_register_funcs.obj: ../core/vl53l1_register_funcs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_register_funcs.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_silicon_core.obj: ../core/vl53l1_silicon_core.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_silicon_core.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

core/vl53l1_wait.obj: ../core/vl53l1_wait.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/igor/workspace_v8/VL53L1" --include_path="/home/igor/workspace_v8/VL53L1/platform" --include_path="/home/igor/ti/tirex-content/TivaWare_C_Series-2.1.3.156" --include_path="/home/igor/workspace_v8/VL53L1/core" --include_path="/home/igor/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="core/vl53l1_wait.d_raw" --obj_directory="core" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


