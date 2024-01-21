//############################################################################
//
// FILE: lab_main_cpu1.c
//
// TITLE: Lab - Empty SysConfig Inter Processor Communications
//
// C2K ACADEMY URL: https://dev.ti.com/tirex/explore/node?node=AOpze8ebskysmgASY3VKSA__jEBbtmC__LATEST
//
//! \addtogroup academy_lab_list
//! <h1> Lab Solution on Inter Processor Communication (CPU1) </h1>
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
#include <math.h>
#include <shared.h>
#include "drv8323.h"
#include "structs.h"
#include "fsm.h"
#include "foc.h"
#include "can.h"
#include "user_config.h"
#include "hw_config.h"
#include "F021_F2837xD_C28x.h"
#include "flash_defines.h"
#include "flash_if.h"
//#include "math_ops.h"

#define PI_F        3.14159274101f
#define TWO_PI_F    6.28318548203f

#define ramFuncSection ".TI.ramfunc"

extern uint16_t IPCBootCPU2(uint32_t ulBootMode);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);

ControllerStruct controller;
ObserverStruct observer;
COMStruct com;
FSMStruct state;
//EncoderStruct comm_encoder; // defined below in CLADataLS2
DRVStruct drv;
CalStruct comm_encoder_cal;
CANTxMessage can_tx;
CANRxMessage can_rx;

uint32_t adcAResult;
uint32_t adcBResult;
uint32_t adcCResult;


#define  WORDS_IN_FLASH_BUFFER    0xFF

#pragma DATA_SECTION(Buffer,"BufferDataSection");
uint16   Buffer[WORDS_IN_FLASH_BUFFER + 1];
uint16   buff[8];
uint16_t   read_buff[20];
uint16 read_buffer[1];
uint32   *Buffer32 = (uint32 *)Buffer;

volatile uint32_t val_from_flash = 0;

float floatBufferOut[64];
int intBufferOut[256];
uint16_t uint16FloatBuffer[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t uint16IntBuffer[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* Flash Registers */
#pragma DATA_SECTION(__float_reg,"CLADataLS2");
float __float_reg[64];
#pragma DATA_SECTION(__int_reg,"CLADataLS2");
int __int_reg[256];


#pragma DATA_SECTION(cla_count,"CLADataLS2");
int cla_count = 0;

#pragma DATA_SECTION(spi_enc_raw,"CLADataLS2");
uint16_t spi_enc_raw = 0;
const void* spi_enc_raw_addr = (void*)&spi_enc_raw;

#pragma DATA_SECTION(enc_read_word,"CLADataLS2");
uint16_t enc_read_word = 0xFFFF;
const void* enc_read_word_addr = (void*)&enc_read_word;

#pragma DATA_SECTION(enc_pos,"CLADataLS2");
uint16_t enc_pos=0;

#pragma DATA_SECTION(comm_encoder,"CLADataLS2");
EncoderStruct comm_encoder;

#pragma DATA_SECTION(__can_tx_msg,"Cpu1ToCpu2MsgRAM");
uint8_t __can_tx_msg[8];


uint32_t adc_a_zeros[1000];
uint32_t adc_b_zeros[1000];
uint32_t adc_zeros_idx = 0;
float adc_a_off = 0;
float adc_b_off = 0;

int cal_adcs = 0;


uint16_t enc_vel=0;
int enc_vel_int=0;
uint16_t mid=0;

int pwm_count = 0;
int pwm_b_count = 0;

uint32_t counter = 500;

int run_motor = 0;

float delta_angle = 0.001;

void packCANMsg(uint16_t pos, uint16_t vel, uint16_t cur, uint8_t* packedArray);

#pragma CODE_SECTION(Example_CallFlashAPI, ramFuncSection);
void Example_CallFlashAPI(void);

#pragma CODE_SECTION(Example_Error,".TI.ramfunc");
void Example_Error(Fapi_StatusType status)
{
    //
    // Error code will be in the status parameter.
    // ESTOP0.
    //
    __asm("    ESTOP0");
}

//
// Example_Done - For this example, once we are done just stop here
//
#pragma CODE_SECTION(Example_Error,".TI.ramfunc");
void Example_Done(void)
{
    //
    // ESTOP0.
    //
    __asm("    ESTOP0");

    for(;;)
    {
    }
}

#ifdef _FLASH
#pragma CODE_SECTION(ipc1_ISR, ".TI.ramfunc");
#endif
__interrupt void ipc1_ISR(void)
{
    uint32_t cmd, addr, data;

    // Clear the interrupt flags.
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    // Get the next DAC sample from CPU2.
    IPC_readCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG1, false, &cmd, &addr, &data);

    // Acknowledge IPC1 flag from remote.
    IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG1);

    // Load the new sample on the DAC.
//    uint16_t recv_data = (uint16_t)data;
    uint8_t* candata = (uint8_t*)data;

    CANRxMessage rx_msg;
    memcpy(rx_msg.data, candata, sizeof(candata));

    float commands[5];
    unpack_cmd(rx_msg, commands);

    // Received CAN command packet, apply commands to controller struct:
    controller.p_des = commands[0];
    controller.v_des = commands[1];
    controller.kp = commands[2];
    controller.kd = commands[3];
    controller.t_ff = commands[4];

    // Old Serial interface:

//    if(recv_data == 1) counter++;
//    if(recv_data == 2) counter--;
//    if(recv_data == 3){
//        drv_enable_gd(drv);
//    }
//    if(recv_data == 4){
//        drv_disable_gd(drv);
//    }
//    if(recv_data == 5){
//        run_motor = 1;
//        GpioDataRegs.GPASET.bit.GPIO31 = 1;
//    }
//    if(recv_data == 6){
//        run_motor = 0;
//        GpioDataRegs.GPASET.bit.GPIO31 = 1;
//    }
//    if(recv_data == 7)
//    {
//        delta_angle = delta_angle/2.0;
//    }
//    if(recv_data == 8)
//    {
//        delta_angle = delta_angle*2.0;
//    }

}


void main(void)
{
//    // Temporary initialization until I add in the Flash storage
//    I_BW=1000.0;        // Current loop bandwidth
//    I_MAX=30.0;         // Current limit
//    THETA_MIN=-12.5;    // Minimum position setpoint
//    THETA_MAX=12.5;     // Maximum position setpoint
//    I_FW_MAX= 0.5;      // Maximum field weakening current
//    R_NOMINAL = 0.025;    // Nominal motor resistance, set during calibration
//    TEMP_MAX = 150;     // Temperature safety lmit
//    I_MAX_CONT = 15.0;   // Continuous max current
//    PPAIRS = 14; // Number of motor pole-pairs
//
//    R_PHASE=0.025; // Single phase resistance
//    KT=0.09; // Torque Constant (N-m/A)
//    R_TH = 1;  // Thermal resistance (C/W)
//    C_TH = 1; // Thermal mass (C/J)
//    GR = 6;             // Gear ratio
//    I_CAL = 2; // Calibration Current
//    P_MIN = -65.0;      // Position setpoint lower limit (rad)
//    P_MAX = 65.0;       // Position setupoint upper bound (rad)
//    V_MIN = -65.0;      // Velocity setpoint lower bound (rad/s)
//    V_MAX = 65.0;       // Velocity setpoint upper bound (rad/s)
//    KP_MAX = 1000; // Max position gain (N-m/rad)
//    KD_MAX = 5; // Max velocity gain (N-m/rad/s)


//    PHASE_ORDER=0;// Phase swapping during calibration
//    CAN_ID=1;// CAN bus ID
//    CAN_MASTER=0; // CAN bus "master" ID
//    CAN_TIMEOUT=0; // CAN bus timeout period

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

    // Assign the SCIA pins to CPU2
    GPIO_SetupPinMux(43, GPIO_MUX_CPU2, 15);
    GPIO_SetupPinOptions(43, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(42, GPIO_MUX_CPU2, 15);
    GPIO_SetupPinOptions(42, GPIO_OUTPUT, GPIO_PUSHPULL);

    // Assign the CAN pins to CPU2
    GPIO_SetupPinMux(70, GPIO_MUX_CPU2, 6);
    GPIO_SetupPinOptions(70, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(71, GPIO_MUX_CPU2, 6);
    GPIO_SetupPinOptions(71, GPIO_OUTPUT, GPIO_PUSHPULL);

    EALLOW;
    DevCfgRegs.CPUSEL5.bit.SCI_A = 1; // assign UART to CPU1
    DevCfgRegs.CPUSEL8.bit.CAN_A = 1; // assign CAN to CPU2
    EDIS;

//    EALLOW;
//    GpioCtrlRegs.GPACSEL3.bit.GPIO22 = 1; // 0=CPU1, 1=CPU1.CLA1, 2=CPU2, 3=CPU2.CLA
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO22 = 0;
//    GpioCtrlRegs.GPADIR.bit.GPIO22 = 1; // 1=OUTput, 0=INput
//    GpioDataRegs.GPACLEAR.bit.GPIO22 = 1; // Set High initially
//    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0; // 0= enables pullup, 1= disables pullup
//    EDIS;

    SpiaRegs.SPITXBUF = 0xFFFF;
    // Wait for SPIA to finish transmitting and receiving
    while(SpiaRegs.SPIFFRX.bit.RXFFST !=1) { }
    uint16_t dummy = SpiaRegs.SPIRXBUF & 0x3FFF;

    CLA_configClaMemory();

    readConfigFromFlash();

//    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);

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

    init_controller_params(&controller);

    GpioDataRegs.GPDSET.bit.GPIO122 = 1; // set DRV_EN high
    DEVICE_DELAY_US(1000);
    drv_calibrate(drv);
    DEVICE_DELAY_US(1000);
    drv_write_DCR(drv, 0x0, DIS_GDF_EN, 0x0, PWM_MODE_3X, 0x0, 0x0, 0x0, 0x0, 0x1);
    DEVICE_DELAY_US(1000);
//    int CSA_GAIN;
//    if(I_MAX <= 40.0f){CSA_GAIN = CSA_GAIN_40;} // Up to 40A use 40X amplifier gain
//    else{CSA_GAIN = CSA_GAIN_20;}                   // From 40-60A use 20X amplifier gain.  (Make this generic in the future)
    drv_write_CSACR(drv, 0x0, 0x1, 0x0, CSA_GAIN_40, 0x0, 0x1, 0x1, 0x1, SEN_LVL_1_0); // Default SEN_LVL_0_25
    DEVICE_DELAY_US(1000);
    drv_write_CSACR(drv, 0x0, 0x1, 0x0, CSA_GAIN_40, 0x1, 0x0, 0x0, 0x0, SEN_LVL_1_0); // Default SEN_LVL_0_25
    DEVICE_DELAY_US(1000);
//    zero_current(&controller);
    DEVICE_DELAY_US(1000);
    drv_write_OCPCR(drv, TRETRY_50US, DEADTIME_50NS, OCP_RETRY, OCP_DEG_8US, VDS_LVL_1_88); // Default OCP_DEG_4US, VDS_LVL_0_45
    DEVICE_DELAY_US(1000);
    drv_disable_gd(drv);
    DEVICE_DELAY_US(1000);

//    drv_enable_gd(drv);
    cal_adcs = 1;
    DEVICE_DELAY_US(26000);
//    drv_disable_gd(drv);
    cal_adcs = 0;
    int i=0;
    for(i=0;i<1000;i++)
    {
        adc_a_off = adc_a_off + adc_a_zeros[i];
        adc_b_off = adc_b_off + adc_b_zeros[i];
    }
    adc_a_off = adc_a_off/1000.0;
    adc_b_off = adc_b_off/1000.0;

    controller.adc_a_offset = (int)adc_a_off;
    controller.adc_b_offset = (int)adc_b_off;


    while(1)
    {
//        IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG0, false, 0, 0, counter);

//        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        DEVICE_DELAY_US(1000000);
    }
}

#ifdef _FLASH
#pragma CODE_SECTION(twoscomp14bit_to_int, ".TI.ramfunc");
#endif
int32_t twoscomp14bit_to_int(int16_t value) {
    // Extract the sign bit from the 14-bit number (bit 13)
    int32_t sign_bit = (value & 0x2000) ? 0xFFFFC000 : 0x00000000;

    // Extend the 14-bit number to 32 bits while preserving its sign
    int32_t result = (int32_t)(value | sign_bit);

    return result;
}

float32 angle = 0;
#ifdef _FLASH
#pragma CODE_SECTION(PWM_ISR, ".TI.ramfunc");
#endif
__interrupt void PWM_ISR(void)
{
    pwm_count++;
    //flags get cleared in ADC ISR since we need time for CLA to run before clearing
//    GpioDataRegs.GPBSET.bit.GPIO52 = 1;
//
//
//    GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;

}

#ifdef _FLASH
#pragma CODE_SECTION(INT_PHASE_B_ISR, ".TI.ramfunc");
#endif
__attribute__((interrupt)) void INT_PHASE_B_ISR(void)
{
    pwm_b_count++;
//    GpioDataRegs.GPBSET.bit.GPIO52 = 1;
//    Interrupt_clearACKGroup(INT_PHASE_B_INTERRUPT_ACK_GROUP);
//    EPWM_clearEventTriggerInterruptFlag(PHASE_B_BASE);
}


uint64_t print_counter = 0;
#ifdef _FLASH
#pragma CODE_SECTION(INT_myADC0_1_ISR, ".TI.ramfunc");
#endif
__attribute__((interrupt)) void INT_myADC0_1_ISR(void)
{
    GpioDataRegs.GPBSET.bit.GPIO52 = 1;
    pwm_count++;
    // 61 encoder counts = sine zero, 14 pole-pairs
//    GpioDataRegs.GPBSET.bit.GPIO52 = 1;

    adcAResult = AdcaResultRegs.ADCRESULT0;
    adcBResult = AdcbResultRegs.ADCRESULT0;
    adcCResult = AdccResultRegs.ADCRESULT0; // zero ~ 2360

    if(cal_adcs == 1 && adc_zeros_idx < 1000)
    {
        adc_a_zeros[adc_zeros_idx] = adcAResult;
        adc_b_zeros[adc_zeros_idx] = adcBResult;
        adc_zeros_idx = adc_zeros_idx + 1;
    }

    controller.adc_vbus_raw = AdcdResultRegs.ADCRESULT0;
    controller.v_bus = ((float)controller.adc_vbus_raw - VBUS_ADC_OFFSET)*V_SCALE;

    controller.adc_a_raw = adcAResult;
    controller.adc_b_raw = adcBResult;

   controller.i_a = controller.i_scale*(float)(controller.adc_a_raw - controller.adc_a_offset);    // Calculate phase currents from ADC readings
   controller.i_b = controller.i_scale*(float)(controller.adc_b_raw - controller.adc_b_offset);
   controller.i_c = -controller.i_a - controller.i_b;

   run_fsm(&state);

   controller.loop_count++;

   if(print_counter > 400)
   {
       CANTxMessage tx_msg;
       pack_reply(&tx_msg, 1, comm_encoder.angle_multiturn[0], comm_encoder.velocity, controller.i_q);
       memcpy(__can_tx_msg, tx_msg.data, sizeof(tx_msg.data));
       IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG0, false, 0, 0, (uint32_t)(&__can_tx_msg[0]));
       print_counter = 0;
   }
   print_counter++;


    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear interrupt flag
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP3;

//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);

    GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1;

}

__attribute__((interrupt)) void cla1Isr1 (void)
{
    pwm_b_count++;
//    GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1;

//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP3;
    EPWM_clearEventTriggerInterruptFlag(EPWM2_BASE);
    PieCtrlRegs.PIEACK.all |= PIEACK_GROUP11;
//    Interrupt_clearACKGroup(INT_myCLA01_INTERRUPT_ACK_GROUP);

}
//
// CLA_configClaMemory - Configure CLA memory sections
//
void CLA_configClaMemory(void)
{
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    EALLOW;

#ifdef _FLASH
    //
    // Copy over code from FLASH to RAM
    //
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

    //
    // Initialize and wait for CLA1ToCPUMsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};

    //
    // Initialize and wait for CPUToCLA1MsgRAM
    //
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};

    //
    // Select LS5RAM to be the programming space for the CLA
    // First configure the CLA to be the master for LS35 and then
    // set the space to be a program block
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 1; //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 1;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1;

    //
    // Next configure LS0RAM and LS1RAM as data spaces for the CLA
    // First configure the CLA to be the master for LS2 and then
    // set the spaces to be code blocks
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 0;

    EDIS;
}

void packCANMsg(uint16_t pos, uint16_t vel, uint16_t cur, uint8_t* packedArray)
{
    // Pack position (16 bits) into two bytes
    packedArray[0] = (uint8_t)(pos & 0xFF);
    packedArray[1] = (uint8_t)((pos >> 8) & 0xFF);

    // Pack velocity (16 bits) into two bytes
    packedArray[2] = (uint8_t)(vel & 0xFF);
    packedArray[3] = (uint8_t)((vel >> 8) & 0xFF);

    // Pack current (16 bits) into two bytes
    packedArray[4] = (uint8_t)(cur & 0xFF);
    packedArray[5] = (uint8_t)((cur >> 8) & 0xFF);
}
