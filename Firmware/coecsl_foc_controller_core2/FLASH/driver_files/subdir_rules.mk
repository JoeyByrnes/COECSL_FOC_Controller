################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
driver_files/%.obj: ../driver_files/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2/driver_files" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU2 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driver_files/$(basename $(<F)).d_raw" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2/FLASH/syscfg" --obj_directory="driver_files" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

driver_files/%.obj: ../driver_files/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2/driver_files" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU2 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="driver_files/$(basename $(<F)).d_raw" --include_path="C:/Users/joeyb/workspace_v12_CC/coecsl_foc_controller_core2/FLASH/syscfg" --obj_directory="driver_files" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


