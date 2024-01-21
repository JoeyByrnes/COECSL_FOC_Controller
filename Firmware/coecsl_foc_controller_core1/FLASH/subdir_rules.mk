################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Fapi_UserDefinedFunctions.obj: C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/examples/cpu1/flash_programming_dcsm/cpu01/Fapi_UserDefinedFunctions.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/libraries/flash_api/f2837xd/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/driver_files" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=CLA_C --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/libraries/flash_api/f2837xd/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/driver_files" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=CLA_C --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/libraries/flash_api/f2837xd/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/driver_files" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=CLA_C --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1805240815: ../empty_ipc_lab_lp_cpu1.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1210/ccs/utils/sysconfig_1.17.0/sysconfig_cli.bat" -s "C:/ti/c2000/C2000Ware_5_00_00_00/.metadata/sdk.json" --script "C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core2/empty_ipc_lab_lp_cpu2.syscfg" --script "C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/empty_ipc_lab_lp_cpu1.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1805240815 ../empty_ipc_lab_lp_cpu1.syscfg
syscfg/board.h: build-1805240815
syscfg/board.cmd.genlibs: build-1805240815
syscfg/board.opt: build-1805240815
syscfg/pinmux.csv: build-1805240815
syscfg/epwm.dot: build-1805240815
syscfg/adc.dot: build-1805240815
syscfg/c2000ware_libraries.cmd.genlibs: build-1805240815
syscfg/c2000ware_libraries.opt: build-1805240815
syscfg/c2000ware_libraries.c: build-1805240815
syscfg/c2000ware_libraries.h: build-1805240815
syscfg/clocktree.h: build-1805240815
syscfg/: build-1805240815

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/libraries/flash_api/f2837xd/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/driver_files" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/common/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/headers/include" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib" --include_path="C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=CLA_C --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/joeyb/Documents/Github/Joey/COECSL_FOC_Controller/Firmware/coecsl_foc_controller_core1/FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


