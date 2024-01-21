################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2837xD_FLASH_CLA_lnk_cpu1.cmd 

SYSCFG_SRCS += \
../empty_ipc_lab_lp_cpu1.syscfg 

CLA_SRCS += \
../cla_tasks.cla 

LIB_SRCS += \
../F021_API_F2837xD_FPU32_EABI.lib \
C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib/ccs/Debug/driverlib.lib 

C_SRCS += \
C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/examples/cpu1/flash_programming_dcsm/cpu01/Fapi_UserDefinedFunctions.c \
../calibration.c \
../can.c \
../drv8323.c \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c \
../flash_if.c \
../flash_writer.c \
../foc.c \
../fsm.c \
../main_cpu1.c \
../math_ops.c \
../position_sensor.c \
../preference_writer.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

CLA_DEPS += \
./cla_tasks.d 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./Fapi_UserDefinedFunctions.d \
./calibration.d \
./can.d \
./drv8323.d \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d \
./flash_if.d \
./flash_writer.d \
./foc.d \
./fsm.d \
./main_cpu1.d \
./math_ops.d \
./position_sensor.d \
./preference_writer.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./Fapi_UserDefinedFunctions.obj \
./calibration.obj \
./can.obj \
./cla_tasks.obj \
./drv8323.obj \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj \
./flash_if.obj \
./flash_writer.obj \
./foc.obj \
./fsm.obj \
./main_cpu1.obj \
./math_ops.obj \
./position_sensor.obj \
./preference_writer.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/pinmux.csv \
./syscfg/epwm.dot \
./syscfg/adc.dot \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"Fapi_UserDefinedFunctions.obj" \
"calibration.obj" \
"can.obj" \
"cla_tasks.obj" \
"drv8323.obj" \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" \
"flash_if.obj" \
"flash_writer.obj" \
"foc.obj" \
"fsm.obj" \
"main_cpu1.obj" \
"math_ops.obj" \
"position_sensor.obj" \
"preference_writer.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\pinmux.csv" \
"syscfg\epwm.dot" \
"syscfg\adc.dot" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"Fapi_UserDefinedFunctions.d" \
"calibration.d" \
"can.d" \
"drv8323.d" \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" \
"flash_if.d" \
"flash_writer.d" \
"foc.d" \
"fsm.d" \
"main_cpu1.d" \
"math_ops.d" \
"position_sensor.d" \
"preference_writer.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

CLA_DEPS__QUOTED += \
"cla_tasks.d" 

C_SRCS__QUOTED += \
"C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2837xd/examples/cpu1/flash_programming_dcsm/cpu01/Fapi_UserDefinedFunctions.c" \
"../calibration.c" \
"../can.c" \
"../drv8323.c" \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" \
"../flash_if.c" \
"../flash_writer.c" \
"../foc.c" \
"../fsm.c" \
"../main_cpu1.c" \
"../math_ops.c" \
"../position_sensor.c" \
"../preference_writer.c" 

SYSCFG_SRCS__QUOTED += \
"../empty_ipc_lab_lp_cpu1.syscfg" 


