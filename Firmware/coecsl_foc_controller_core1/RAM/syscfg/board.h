/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM1 -> PHASE_A Pinmux
//
//
// EPWM1A - GPIO Settings
//
#define GPIO_PIN_EPWM1A 0
#define PHASE_A_EPWMA_GPIO 0
#define PHASE_A_EPWMA_PIN_CONFIG GPIO_0_EPWM1A
//
// EPWM1B - GPIO Settings
//
#define GPIO_PIN_EPWM1B 1
#define PHASE_A_EPWMB_GPIO 1
#define PHASE_A_EPWMB_PIN_CONFIG GPIO_1_EPWM1B

//
// EPWM2 -> PHASE_B Pinmux
//
//
// EPWM2A - GPIO Settings
//
#define GPIO_PIN_EPWM2A 2
#define PHASE_B_EPWMA_GPIO 2
#define PHASE_B_EPWMA_PIN_CONFIG GPIO_2_EPWM2A
//
// EPWM2B - GPIO Settings
//
#define GPIO_PIN_EPWM2B 3
#define PHASE_B_EPWMB_GPIO 3
#define PHASE_B_EPWMB_PIN_CONFIG GPIO_3_EPWM2B

//
// EPWM3 -> PHASE_C Pinmux
//
//
// EPWM3A - GPIO Settings
//
#define GPIO_PIN_EPWM3A 4
#define PHASE_C_EPWMA_GPIO 4
#define PHASE_C_EPWMA_PIN_CONFIG GPIO_4_EPWM3A
//
// EPWM3B - GPIO Settings
//
#define GPIO_PIN_EPWM3B 5
#define PHASE_C_EPWMB_GPIO 5
#define PHASE_C_EPWMB_PIN_CONFIG GPIO_5_EPWM3B
//
// GPIO52 - GPIO Settings
//
#define GPIO_DEBUG_GPIO_PIN_CONFIG GPIO_52_GPIO52
//
// GPIO22 - GPIO Settings
//
#define CLA1_GPIO_GPIO_PIN_CONFIG GPIO_22_GPIO22
//
// GPIO122 - GPIO Settings
//
#define DRV_EN_GPIO_PIN_CONFIG GPIO_122_GPIO122
//
// GPIO123 - GPIO Settings
//
#define DRV_NFAULT_GPIO_PIN_CONFIG GPIO_123_GPIO123
//
// GPIO31 - GPIO Settings
//
#define CPU1_LED_GPIO_GPIO_PIN_CONFIG GPIO_31_GPIO31
//
// GPIO34 - GPIO Settings
//
#define CPU2_LED_GPIO_GPIO_PIN_CONFIG GPIO_34_GPIO34

//
// SPIA -> mySPI0 Pinmux
//
//
// SPIA_PICO - GPIO Settings
//
#define GPIO_PIN_SPIA_PICO 58
#define mySPI0_SPIPICO_GPIO 58
#define mySPI0_SPIPICO_PIN_CONFIG GPIO_58_SPISIMOA
//
// SPIA_POCI - GPIO Settings
//
#define GPIO_PIN_SPIA_POCI 59
#define mySPI0_SPIPOCI_GPIO 59
#define mySPI0_SPIPOCI_PIN_CONFIG GPIO_59_SPISOMIA
//
// SPIA_CLK - GPIO Settings
//
#define GPIO_PIN_SPIA_CLK 60
#define mySPI0_SPICLK_GPIO 60
#define mySPI0_SPICLK_PIN_CONFIG GPIO_60_SPICLKA
//
// SPIA_PTE - GPIO Settings
//
#define GPIO_PIN_SPIA_PTE 61
#define mySPI0_SPIPTE_GPIO 61
#define mySPI0_SPIPTE_PIN_CONFIG GPIO_61_SPISTEA

//
// SPIB -> mySPI1 Pinmux
//
//
// SPIB_PICO - GPIO Settings
//
#define GPIO_PIN_SPIB_PICO 63
#define mySPI1_SPIPICO_GPIO 63
#define mySPI1_SPIPICO_PIN_CONFIG GPIO_63_SPISIMOB
//
// SPIB_POCI - GPIO Settings
//
#define GPIO_PIN_SPIB_POCI 64
#define mySPI1_SPIPOCI_GPIO 64
#define mySPI1_SPIPOCI_PIN_CONFIG GPIO_64_SPISOMIB
//
// SPIB_CLK - GPIO Settings
//
#define GPIO_PIN_SPIB_CLK 65
#define mySPI1_SPICLK_GPIO 65
#define mySPI1_SPICLK_PIN_CONFIG GPIO_65_SPICLKB
//
// SPIB_PTE - GPIO Settings
//
#define GPIO_PIN_SPIB_PTE 66
#define mySPI1_SPIPTE_GPIO 66
#define mySPI1_SPIPTE_PIN_CONFIG GPIO_66_SPISTEB

//
// I2CA -> myI2C0 Pinmux
//
//
// SDAA - GPIO Settings
//
#define GPIO_PIN_SDAA 104
#define myI2C0_I2CSDA_GPIO 104
#define myI2C0_I2CSDA_PIN_CONFIG GPIO_104_SDAA
//
// SCLA - GPIO Settings
//
#define GPIO_PIN_SCLA 105
#define myI2C0_I2CSCL_GPIO 105
#define myI2C0_I2CSCL_PIN_CONFIG GPIO_105_SCLA

//
// SCIA -> debuggerSerial Pinmux
//
//
// SCIRXDA - GPIO Settings
//
#define GPIO_PIN_SCIRXDA 43
#define debuggerSerial_SCIRX_GPIO 43
#define debuggerSerial_SCIRX_PIN_CONFIG GPIO_43_SCIRXDA
//
// SCITXDA - GPIO Settings
//
#define GPIO_PIN_SCITXDA 42
#define debuggerSerial_SCITX_GPIO 42
#define debuggerSerial_SCITX_PIN_CONFIG GPIO_42_SCITXDA

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define myADC0_BASE ADCA_BASE
#define myADC0_RESULT_BASE ADCARESULT_BASE
#define myADC0_SOC0 ADC_SOC_NUMBER0
#define myADC0_FORCE_SOC0 ADC_FORCE_SOC0
#define myADC0_SAMPLE_WINDOW_SOC0 80
#define myADC0_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_EPWM1_SOCA
#define myADC0_CHANNEL_SOC0 ADC_CH_ADCIN4
void myADC0_init();

#define myADC1_BASE ADCB_BASE
#define myADC1_RESULT_BASE ADCBRESULT_BASE
#define myADC1_SOC0 ADC_SOC_NUMBER0
#define myADC1_FORCE_SOC0 ADC_FORCE_SOC0
#define myADC1_SAMPLE_WINDOW_SOC0 80
#define myADC1_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_EPWM1_SOCA
#define myADC1_CHANNEL_SOC0 ADC_CH_ADCIN4
void myADC1_init();

#define myADC2_BASE ADCC_BASE
#define myADC2_RESULT_BASE ADCCRESULT_BASE
#define myADC2_SOC0 ADC_SOC_NUMBER0
#define myADC2_FORCE_SOC0 ADC_FORCE_SOC0
#define myADC2_SAMPLE_WINDOW_SOC0 80
#define myADC2_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_EPWM1_SOCA
#define myADC2_CHANNEL_SOC0 ADC_CH_ADCIN4
void myADC2_init();

#define myADC3_BASE ADCD_BASE
#define myADC3_RESULT_BASE ADCDRESULT_BASE
#define myADC3_SOC0 ADC_SOC_NUMBER0
#define myADC3_FORCE_SOC0 ADC_FORCE_SOC0
#define myADC3_SAMPLE_WINDOW_SOC0 80
#define myADC3_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_EPWM1_SOCA
#define myADC3_CHANNEL_SOC0 ADC_CH_ADCIN14
void myADC3_init();


//*****************************************************************************
//
// CLA Configurations
//
//*****************************************************************************
#define myCLA0_BASE CLA1_BASE

//
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them global
// and the main CPU can make use of them.
//
__attribute__((interrupt)) void Cla1Task1();
__attribute__((interrupt)) void Cla1Task2();
__attribute__((interrupt)) void Cla1Task3();
__attribute__((interrupt)) void Cla1Task4();
__attribute__((interrupt)) void Cla1Task5();
__attribute__((interrupt)) void Cla1Task6();
__attribute__((interrupt)) void Cla1Task7();
__attribute__((interrupt)) void Cla1Task8();
void myCLA0_init();


//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define PHASE_A_BASE EPWM1_BASE
#define PHASE_A_TBPRD 2500
#define PHASE_A_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define PHASE_A_TBPHS 0
#define PHASE_A_CMPA 2
#define PHASE_A_CMPB 0
#define PHASE_A_CMPC 0
#define PHASE_A_CMPD 2495
#define PHASE_A_DBRED 0
#define PHASE_A_DBFED 0
#define PHASE_A_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define PHASE_A_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define PHASE_A_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO
#define PHASE_B_BASE EPWM2_BASE
#define PHASE_B_TBPRD 2500
#define PHASE_B_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define PHASE_B_TBPHS 2497
#define PHASE_B_CMPA 0
#define PHASE_B_CMPB 0
#define PHASE_B_CMPC 2300
#define PHASE_B_CMPD 2495
#define PHASE_B_DBRED 0
#define PHASE_B_DBFED 0
#define PHASE_B_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define PHASE_B_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define PHASE_B_INTERRUPT_SOURCE EPWM_INT_TBCTR_U_CMPC
#define PHASE_C_BASE EPWM3_BASE
#define PHASE_C_TBPRD 2500
#define PHASE_C_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define PHASE_C_TBPHS 2497
#define PHASE_C_CMPA 0
#define PHASE_C_CMPB 0
#define PHASE_C_CMPC 0
#define PHASE_C_CMPD 2495
#define PHASE_C_DBRED 0
#define PHASE_C_DBFED 0
#define PHASE_C_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define PHASE_C_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define PHASE_C_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// FLASH Configurations
//
//*****************************************************************************
#define myFMC0_BASE FLASH0CTRL_BASE
#define myFMC0_ECCBASE FLASH0ECC_BASE
#define myFMC0_WAITSTATES 3
#define myFMC0_ERRORTHRESHOLD 0

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define GPIO_DEBUG 52
void GPIO_DEBUG_init();
#define CLA1_GPIO 22
void CLA1_GPIO_init();
#define DRV_EN 122
void DRV_EN_init();
#define DRV_NFAULT 123
void DRV_NFAULT_init();
#define CPU1_LED_GPIO 31
void CPU1_LED_GPIO_init();
#define CPU2_LED_GPIO 34
void CPU2_LED_GPIO_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myCLA01
#define INT_myCLA01 INT_CLA1_1
#define INT_myCLA01_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP11
extern __interrupt void cla1Isr1(void);

// Interrupt Settings for INT_myADC0_1
#define INT_myADC0_1 INT_ADCA1
#define INT_myADC0_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_myADC0_1_ISR(void);

// Interrupt Settings for INT_PHASE_A
#define INT_PHASE_A INT_EPWM1
#define INT_PHASE_A_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP3
extern __interrupt void PWM_ISR(void);

// Interrupt Settings for INT_PHASE_B
#define INT_PHASE_B INT_EPWM2
#define INT_PHASE_B_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP3
extern __interrupt void INT_PHASE_B_ISR(void);

// Interrupt Settings for IPC_1
#define IPC_1 INT_IPC_1
#define IPC_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void ipc1_ISR(void);

//*****************************************************************************
//
// IPC Configurations
//
//*****************************************************************************
#define CPU1_to_CPU2_IPC_FLAG0 IPC_FLAG0
#define IPC_SYNC IPC_FLAG31
#define CPU2_to_CPU1_IPC_FLAG1 IPC_FLAG1
#define IPC_SYNC IPC_FLAG31
#define BOOT_MODE_CPU2 C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH

//*****************************************************************************
//
// MEMCFG Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
#define mySPI0_BASE SPIA_BASE
#define mySPI0_BITRATE 20000000
void mySPI0_init();
#define mySPI1_BASE SPIB_BASE
#define mySPI1_BITRATE 2500000
void mySPI1_init();

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	CLA_init();
void	EPWM_init();
void	FLASH_init();
void	GPIO_init();
void	INTERRUPT_init();
void	IPC_SYSCFG_init();
void	MEMCFG_init();
void	SPI_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
