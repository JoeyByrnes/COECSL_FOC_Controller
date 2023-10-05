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
C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f2837xd/driverlib/ccs/Debug/driverlib.lib 

C_SRCS += \
../calibration.c \
../can.c \
../drv8323.c \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c \
../foc.c \
../fsm.c \
../main_cpu1.c \
../math_ops.c \
../position_sensor.c 

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
./calibration.d \
./can.d \
./drv8323.d \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d \
./foc.d \
./fsm.d \
./main_cpu1.d \
./math_ops.d \
./position_sensor.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./calibration.obj \
./can.obj \
./cla_tasks.obj \
./drv8323.obj \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj \
./foc.obj \
./fsm.obj \
./main_cpu1.obj \
./math_ops.obj \
./position_sensor.obj 

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
"calibration.obj" \
"can.obj" \
"cla_tasks.obj" \
"drv8323.obj" \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" \
"foc.obj" \
"fsm.obj" \
"main_cpu1.obj" \
"math_ops.obj" \
"position_sensor.obj" 

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
"calibration.d" \
"can.d" \
"drv8323.d" \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" \
"foc.d" \
"fsm.d" \
"main_cpu1.d" \
"math_ops.d" \
"position_sensor.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

CLA_DEPS__QUOTED += \
"cla_tasks.d" 

C_SRCS__QUOTED += \
"../calibration.c" \
"../can.c" \
"../drv8323.c" \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" \
"../foc.c" \
"../fsm.c" \
"../main_cpu1.c" \
"../math_ops.c" \
"../position_sensor.c" 

SYSCFG_SRCS__QUOTED += \
"../empty_ipc_lab_lp_cpu1.syscfg" 


