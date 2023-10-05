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
// I2C Configurations
//
//*****************************************************************************
#define myI2C0_BASE I2CA_BASE
#define myI2C0_BITRATE 400000
#define myI2C0_TARGET_ADDRESS 0
#define myI2C0_OWN_TARGET_ADDRESS 0
void myI2C0_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for IPC_0
#define IPC_0 INT_IPC_0
#define IPC_0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void ipc0_ISR(void);

// Interrupt Settings for INT_debuggerSerial_RX
#define INT_debuggerSerial_RX INT_SCIA_RX
#define INT_debuggerSerial_RX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_debuggerSerial_RX_ISR(void);

// Interrupt Settings for INT_debuggerSerial_TX
#define INT_debuggerSerial_TX INT_SCIA_TX
#define INT_debuggerSerial_TX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_debuggerSerial_TX_ISR(void);

//*****************************************************************************
//
// IPC Configurations
//
//*****************************************************************************
#define CPU1_to_CPU2_IPC_FLAG0 IPC_FLAG0
#define IPC_SYNC IPC_FLAG31
#define CPU2_to_CPU1_IPC_FLAG1 IPC_FLAG1
#define IPC_SYNC IPC_FLAG31

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define debuggerSerial_BASE SCIA_BASE
#define debuggerSerial_BAUDRATE 115200
#define debuggerSerial_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define debuggerSerial_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define debuggerSerial_CONFIG_PAR SCI_CONFIG_PAR_NONE
#define debuggerSerial_FIFO_TX_LVL SCI_FIFO_TX0
#define debuggerSerial_FIFO_RX_LVL SCI_FIFO_RX1
void debuggerSerial_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define GPIO_DEBUG 52
#define CLA1_GPIO 22
#define DRV_EN 122
#define DRV_NFAULT 123
#define CPU1_LED_GPIO 31
#define CPU2_LED_GPIO 34

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	I2C_init();
void	INTERRUPT_init();
void	IPC_SYSCFG_init();
void	SCI_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
