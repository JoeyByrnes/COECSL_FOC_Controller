//############################################################################
//
// FILE: lab_main_cpu2.c
//
// TITLE: Lab - Empty SysConfig Inter Processor Communications
//
// C2K ACADEMY URL: https://dev.ti.com/tirex/explore/node?node=AOpze8ebskysmgASY3VKSA__jEBbtmC__LATEST
//
//! \addtogroup academy_lab_list
//! <h1> Lab Solution on Inter Processor Communication (CPU2)</h1>
//!
//! The objective of this lab exercise is to demonstrate and become familiar
//! with the operation of the IPC module. We will be using the basic IPC
//! features to send data in both directions between CPU1 and CPU2. As in
//! the previous lab exercise, PWM2 will be configured to provide a 50 kHz
//! SOC signal to ADC-A. An End-of-Conversion ISR on CPU1 will read each
//! result and write it into a data register in the IPC. An IPC interrupt
//! will then be triggered on CPU2 which fetches this data and stores it in
//! a circular buffer. The same ISR grabs a data point from a sine table and
//! loads it into a different IPC register for transmission to CPU1. This
//! triggers an interrupt on CPU1 to fetch the sine data and write it into
//! DAC-B. The DAC-B output is connected by a jumper wire to the ADCINA0 pin.
//! If the program runs as expected the sine table and ADC results buffer on
//! CPU2 should contain very similar data.
//!
//! \b External \b Connections \n
//!  - Jumper cable between ADCINA0 pin to the DACB pin
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//############################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//############################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "F28x_Project.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//
// Defines
//
#define TXCOUNT  100000
#define MSG_DATA_LENGTH    8
#define TX_MSG_OBJ_ID      1
#define RX_MSG_OBJ_ID      2

//
// Globals
//

#pragma DATA_SECTION(__can_rx_msg,"Cpu2ToCpu1MsgRAM");
uint16_t __can_rx_msg[8];

volatile unsigned long i;
volatile uint32_t txMsgCount = 0;
volatile uint32_t rxMsgCount = 0;
uint16_t txMsgData[8];
uint16_t rxMsgData[8];

uint16_t dataValue = 0;

uint64_t print_counter = 0;

uint8_t new_can_rx_data = 0;


void unpackCANMsg(uint8_t* packedArray, uint16_t* pos, uint16_t* vel, uint16_t* cur)
{
    // Unpack position (two bytes) into a 16-bit value
    *pos = ((uint16_t)packedArray[1] << 8) | packedArray[0];

    // Unpack velocity (two bytes) into a 16-bit value
    *vel = ((uint16_t)packedArray[3] << 8) | packedArray[2];

    // Unpack current (two bytes) into a 16-bit value
    *cur = ((uint16_t)packedArray[5] << 8) | packedArray[4];
}


#ifdef _FLASH
#pragma CODE_SECTION(ipc0_ISR, ".TI.ramfunc");
#endif
interrupt void ipc0_ISR(void)
{
    uint32_t cmd, addr, data;

    // Clear interrupt flags.
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    // Read the data from the IPC registers.
    IPC_readCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG0, false, &cmd, &addr, &data);

    // Acknowledge IPC1 flag from remote.
    IPC_ackFlagRtoL(IPC_CPU2_L_CPU1_R, IPC_FLAG0);

//    dataValue = (uint32_t)data;
    uint8_t* candata = (uint8_t*)data;
//    char msg[100];
//    sprintf(msg, "Data: %u \r\n\0", dataValue);
//    SCI_writeCharArray(debuggerSerial_BASE, (uint16_t*)msg, strlen(msg));

//    if(print_counter%5000 == 0)
//    {
//        uint16_t pos, vel,cur;
//        unpackCANMsg(candata,&pos,&vel,&cur);
//        char msg[100];
//        sprintf(msg, "CAN DATA: %u, %u, %u\r\n", pos,vel,cur);
//        SCI_writeCharArray(debuggerSerial_BASE, (uint16_t*)msg, strlen(msg));
//    }
//    print_counter++;

        if(new_can_rx_data)
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)(&__can_rx_msg[0]));
        }

        CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH, txMsgData);

        //
        // Poll TxOk bit in CAN_ES register to check completion of transmission
        //
        while(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) !=  CAN_ES_TXOK)
        {
        }

}

#ifdef _FLASH
#pragma CODE_SECTION(INT_debuggerSerial_RX_ISR, ".TI.ramfunc");
#endif
interrupt void INT_debuggerSerial_RX_ISR(void)
{
    char receivedChar = SciaRegs.SCIRXBUF.all;

    /* SCI PE or FE error */
    if (receivedChar & 0xC000) {
        SciaRegs.SCICTL1.bit.SWRESET = 0;
        SciaRegs.SCICTL1.bit.SWRESET = 1;
        SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;
        SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
    } else {
        receivedChar = receivedChar & 0x00FF;

        if (receivedChar == 'a')
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0001);
        }
        if (receivedChar == 'b')
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0002);
        }
        if (receivedChar == 'e')
        {
            GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0003);
        }
        if (receivedChar == 'd')
        {
            GpioDataRegs.GPBSET.bit.GPIO34 = 1;
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0004);
        }
        if (receivedChar == 'r')
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0005);
        }
        if (receivedChar == 's')
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0006);
        }
        if (receivedChar == '1')
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0007);
        }
        if (receivedChar == '2')
        {
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG1, false, 0, 0, (uint32_t)0x0008);
        }
    }

    // Acknowledge the interrupt and clear the RX flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;

    // Acknowledge this interrupt to allow more interrupts in the future
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
interrupt void INT_debuggerSerial_TX_ISR(void)
{

}

void main(void)
{
    // Configure system clock and PLL, enable peripherals, and configure
    // flash if used.
    Device_init();

    // Initialize the PIE module and vector table.
    Interrupt_initModule();
    Interrupt_initVectorTable();

    //
    // Initialize settings from SysConfig
    //
    Board_init();

    // Short delay to let the DAC and other peripherals start up.
//    DEVICE_DELAY_US(1000);

    //
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_SYNC);

    // Enable global interrupts.
    EINT;
    // Enable real-time debug.
    ERTM;

    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x1
    //      Message Frame: Standard
    //      Message Type: Receive
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: "Don't care" for a Receive mailbox
    //
    CAN_setupMessageObject(CANA_BASE, RX_MSG_OBJ_ID, 0x1,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    //
    // Initialize the transmit message object used for sending CAN messages.
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x01
    //      Message Frame: Standard
    //      Message Type: Transmit
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 4 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x1,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    while(1)
    {
        //
        // Poll RxOk bit in CAN_ES register to check completion of Reception
        //
        if(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_RXOK)) == CAN_ES_RXOK)
        {
            //
            // Get the received message
            //
            CAN_readMessage(CANA_BASE, RX_MSG_OBJ_ID, rxMsgData);
            new_can_rx_data = 1;
            rxMsgCount++;
        }
//        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
//        DEVICE_DELAY_US(1000000);
    }
}

