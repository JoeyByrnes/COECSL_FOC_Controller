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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	I2C_init();
	IPC_SYSCFG_init();
	SCI_init();
	INTERRUPT_init();

	EDIS;
}


//*****************************************************************************
//
// I2C Configurations
//
//*****************************************************************************
void I2C_init(){
	myI2C0_init();
}

void myI2C0_init(){
	I2C_disableModule(myI2C0_BASE);
	I2C_initController(myI2C0_BASE, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_33);
	I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
	I2C_setTargetAddress(myI2C0_BASE, 0);
	I2C_disableLoopback(myI2C0_BASE);
	I2C_setBitCount(myI2C0_BASE, I2C_BITCOUNT_1);
	I2C_setDataCount(myI2C0_BASE, 1);
	I2C_setAddressMode(myI2C0_BASE, I2C_ADDR_MODE_7BITS);
	I2C_enableFIFO(myI2C0_BASE);
	I2C_setFIFOInterruptLevel(myI2C0_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RXEMPTY);
	I2C_setEmulationMode(myI2C0_BASE, I2C_EMULATION_STOP_SCL_LOW);
	I2C_enableModule(myI2C0_BASE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Setings for IPC_0
	Interrupt_register(IPC_0, &ipc0_ISR);
	Interrupt_enable(IPC_0);
	
	// Interrupt Setings for INT_debuggerSerial_RX
	Interrupt_register(INT_debuggerSerial_RX, &INT_debuggerSerial_RX_ISR);
	Interrupt_enable(INT_debuggerSerial_RX);
	
	// Interrupt Setings for INT_debuggerSerial_TX
	Interrupt_register(INT_debuggerSerial_TX, &INT_debuggerSerial_TX_ISR);
	Interrupt_disable(INT_debuggerSerial_TX);
}
//*****************************************************************************
//
// IPC Configurations
//
//*****************************************************************************
void IPC_SYSCFG_init(){
}
//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
void SCI_init(){
	debuggerSerial_init();
}

void debuggerSerial_init(){
	SCI_clearInterruptStatus(debuggerSerial_BASE, SCI_INT_RXFF | SCI_INT_TXFF | SCI_INT_FE | SCI_INT_OE | SCI_INT_PE | SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
	SCI_clearOverflowStatus(debuggerSerial_BASE);
	SCI_resetTxFIFO(debuggerSerial_BASE);
	SCI_resetRxFIFO(debuggerSerial_BASE);
	SCI_resetChannels(debuggerSerial_BASE);
	SCI_setConfig(debuggerSerial_BASE, DEVICE_LSPCLK_FREQ, debuggerSerial_BAUDRATE, (SCI_CONFIG_WLEN_8|SCI_CONFIG_STOP_ONE|SCI_CONFIG_PAR_NONE));
	SCI_disableLoopback(debuggerSerial_BASE);
	SCI_performSoftwareReset(debuggerSerial_BASE);
	SCI_enableInterrupt(debuggerSerial_BASE, SCI_INT_RXFF);
	SCI_setFIFOInterruptLevel(debuggerSerial_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);
	SCI_enableFIFO(debuggerSerial_BASE);
	SCI_enableModule(debuggerSerial_BASE);
}

