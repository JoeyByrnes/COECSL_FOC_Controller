################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := --cmd_file="syscfg/board.opt" --cmd_file="syscfg/c2000ware_libraries.opt" 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Fapi_UserDefinedFunctions.obj" \
"./calibration.obj" \
"./can.obj" \
"./cla_tasks.obj" \
"./drv8323.obj" \
"./syscfg/board.obj" \
"./syscfg/c2000ware_libraries.obj" \
"./flash_if.obj" \
"./flash_writer.obj" \
"./foc.obj" \
"./fsm.obj" \
"./main_cpu1.obj" \
"./math_ops.obj" \
"./position_sensor.obj" \
"./preference_writer.obj" \
"./device/F2837xD_CodeStartBranch.obj" \
"./device/device.obj" \
"./driver_files/F28379dSerial.obj" \
"./driver_files/F2837xD_Adc.obj" \
"./driver_files/F2837xD_EPwm.obj" \
"./driver_files/F2837xD_GlobalVariableDefs.obj" \
"./driver_files/F2837xD_Gpio.obj" \
"./driver_files/F2837xD_Ipc.obj" \
"./driver_files/F2837xD_Ipc_Driver_Util.obj" \
"./driver_files/F2837xD_PieCtrl.obj" \
"./driver_files/F2837xD_PieVect.obj" \
"./driver_files/F2837xD_Spi.obj" \
"./driver_files/F2837xD_SysCtrl.obj" \
"./driver_files/F2837xD_usDelay.obj" \
"../2837xD_FLASH_CLA_lnk_cpu1.cmd" \
"../F021_API_F2837xD_FPU32_EABI.lib" \
"C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib/ccs/Debug/driverlib.lib" \
"../driver_files/F2837xD_Headers_nonBIOS_cpu1.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include device/subdir_vars.mk
-include driver_files/subdir_vars.mk
-include subdir_rules.mk
-include device/subdir_rules.mk
-include driver_files/subdir_rules.mk
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
coecsl_foc_controller_core1.out \

EXE_OUTPUTS__QUOTED += \
"coecsl_foc_controller_core1.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "coecsl_foc_controller_core1.out"

# Tool invocations
coecsl_foc_controller_core1.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O3 --opt_for_speed=5 --fp_mode=relaxed --advice:performance=all --define=CLA_C --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_signed_compare_workaround=on -z -m"coecsl_foc_controller_core1.map" --stack_size=0x100 --warn_sections -i"C:/ti/c2000/C2000Ware_5_00_00_00/libraries/flash_api/f2837xd/lib" -i"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"C:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --reread_libs --define=CLA_C --diag_wrap=off --display_error_number --xml_link_info="coecsl_foc_controller_core1_linkInfo.xml" --entry_point=code_start --rom_model -o "coecsl_foc_controller_core1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Fapi_UserDefinedFunctions.obj" "calibration.obj" "can.obj" "cla_tasks.obj" "drv8323.obj" "syscfg\board.obj" "syscfg\c2000ware_libraries.obj" "flash_if.obj" "flash_writer.obj" "foc.obj" "fsm.obj" "main_cpu1.obj" "math_ops.obj" "position_sensor.obj" "preference_writer.obj" "device\F2837xD_CodeStartBranch.obj" "device\device.obj" "driver_files\F28379dSerial.obj" "driver_files\F2837xD_Adc.obj" "driver_files\F2837xD_EPwm.obj" "driver_files\F2837xD_GlobalVariableDefs.obj" "driver_files\F2837xD_Gpio.obj" "driver_files\F2837xD_Ipc.obj" "driver_files\F2837xD_Ipc_Driver_Util.obj" "driver_files\F2837xD_PieCtrl.obj" "driver_files\F2837xD_PieVect.obj" "driver_files\F2837xD_Spi.obj" "driver_files\F2837xD_SysCtrl.obj" "driver_files\F2837xD_usDelay.obj" 
	-$(RM) "Fapi_UserDefinedFunctions.d" "calibration.d" "can.d" "drv8323.d" "syscfg\board.d" "syscfg\c2000ware_libraries.d" "flash_if.d" "flash_writer.d" "foc.d" "fsm.d" "main_cpu1.d" "math_ops.d" "position_sensor.d" "preference_writer.d" "device\device.d" "driver_files\F28379dSerial.d" "driver_files\F2837xD_Adc.d" "driver_files\F2837xD_EPwm.d" "driver_files\F2837xD_GlobalVariableDefs.d" "driver_files\F2837xD_Gpio.d" "driver_files\F2837xD_Ipc.d" "driver_files\F2837xD_Ipc_Driver_Util.d" "driver_files\F2837xD_PieCtrl.d" "driver_files\F2837xD_PieVect.d" "driver_files\F2837xD_Spi.d" "driver_files\F2837xD_SysCtrl.d" 
	-$(RM) "cla_tasks.d" 
	-$(RM) "device\F2837xD_CodeStartBranch.d" "driver_files\F2837xD_usDelay.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

