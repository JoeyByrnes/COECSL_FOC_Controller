//############################################################################
//
// FILE: main_cpu1.c
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
#include "user_config.h"
#include "hw_config.h"

extern uint16_t IPCBootCPU2(uint32_t ulBootMode);
void CLA_configClaMemory(void);
void CLA_initCpu1Cla1(void);

//typedef struct
//{
//    float I_BW;          // Current loop bandwidth
//    float I_MAX;         // Current limit
//    float THETA_MIN;     // Minimum position setpoint
//    float THETA_MAX;     // Maximum position setpoint
//    float I_FW_MAX;      // Maximum field weakening current
//    float R_NOMINAL;     // Nominal motor resistance, set during calibration
//    float TEMP_MAX;      // Temperature safety lmit
//    float I_MAX_CONT;    // Continuous max current
//    float PPAIRS;        // Number of motor pole-pairs
//
//    float R_PHASE;       // Single phase resistance
//    float KT;            // Torque Constant (N-m/A)
//    float R_TH;          // Thermal resistance (C/W)
//    float C_TH;          // Thermal mass (C/J)
//    float GR;            // Gear ratio
//    float I_CAL;         // Calibration Current
//    float P_MIN;         // Position setpoint lower limit (rad)
//    float P_MAX;         // Position setupoint upper bound (rad)
//    float V_MIN;         // Velocity setpoint lower bound (rad/s)
//    float V_MAX;         // Velocity setpoint upper bound (rad/s)
//    float KP_MAX;        // Max position gain (N-m/rad)
//    float KD_MAX;        // Max velocity gain (N-m/rad/s)
//
//
//    int PHASE_ORDER;     // Phase swapping during calibration
//    int CAN_ID;          // CAN bus ID
//    int CAN_MASTER;      // CAN bus "master" ID
//    int CAN_TIMEOUT;     // CAN bus timeout period
//    int M_ZERO;
//    int E_ZERO;
//    //int ENCODER_LUT;     // Encoder offset LUT - 128 elements long
//}configData;

/* Flash Registers */
float __float_reg[64];
int __int_reg[256];
//PreferenceWriter prefs;

int count = 0;

/* Structs for control, etc */

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

#pragma DATA_SECTION(__floats,"NvDataStorage");
#pragma DATA_SECTION(__ints,"NvDataStorage");
float __floats[21];
int __ints[6];


#pragma DATA_SECTION(cla_count,"Cla1ToCpuMsgRAM");
int cla_count = 0;

#pragma DATA_SECTION(spi_enc_raw,"CLADataLS2");
uint16_t spi_enc_raw = 0;
const void* spi_enc_raw_addr = (void*)&spi_enc_raw;

#pragma DATA_SECTION(enc_read_word,"CLADataLS2");
uint16_t enc_read_word = 0xFFFF;
const void* enc_read_word_addr = (void*)&enc_read_word;

#pragma DATA_SECTION(enc_pos,"CLADataLS2");
uint16_t enc_pos=0;
#pragma DATA_SECTION(enc_pos_history,"CLADataLS2");
uint16_t enc_pos_history[20] = {0};
#pragma DATA_SECTION(enc_vel,"CLADataLS2");
float enc_vel=0;

#pragma DATA_SECTION(comm_encoder,"CLADataLS2");
EncoderStruct comm_encoder;


int enc_vel_int=0;
uint16_t mid=0;

int pwm_count = 0;
int pwm_b_count = 0;

int adc_calibration_samples = 0;
int calibrate_adc_offsets = 0;
int adc_a_offset = 0;
int adc_b_offset = 0;
#define NUM_ADC_CALIB_SAMPLES 1000

uint32_t counter = 500;

int run_motor = 0;

float delta_angle = 0.001;

#ifdef _FLASH
#pragma CODE_SECTION(ipc1_ISR, ".TI.ramfunc");
#endif
interrupt void ipc1_ISR(void)
{
    uint32_t cmd, addr, data;

    // Clear the interrupt flags.
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    // Get the next DAC sample from CPU2.
    IPC_readCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG1, false, &cmd, &addr, &data);

    // Acknowledge IPC1 flag from remote.
    IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG1);

    // Load the new sample on the DAC.
    uint16_t recv_data = (uint16_t)data;

    if(recv_data == 1) counter++;
    if(recv_data == 2) counter--;
    if(recv_data == 3){
        drv_enable_gd(drv);
    }
    if(recv_data == 4){
        drv_disable_gd(drv);
    }
    if(recv_data == 5){
        run_motor = 1;
        GpioDataRegs.GPASET.bit.GPIO31 = 1;
    }
    if(recv_data == 6){
        run_motor = 0;
        GpioDataRegs.GPASET.bit.GPIO31 = 1;
    }
    if(recv_data == 7)
    {
        delta_angle = delta_angle/2.0;
    }
    if(recv_data == 8)
    {
        delta_angle = delta_angle*2.0;
    }

//    IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG0, false, 0, 0,
//                            0x00FF);
//
//    // Toggle LED1 at a rate of 1Hz.
//    if (LedCtr1++ >= 50000) {
//        GPIO_togglePin(CPU1_LED);
//        LedCtr1 = 0;
//    }
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

    // Assign the SCIA pins to CPU2
    GPIO_SetupPinMux(43, GPIO_MUX_CPU2, 15);
    GPIO_SetupPinOptions(43, GPIO_INPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(42, GPIO_MUX_CPU2, 15);
    GPIO_SetupPinOptions(42, GPIO_OUTPUT, GPIO_PUSHPULL);
    EALLOW;
    DevCfgRegs.CPUSEL5.bit.SCI_A = 1;
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
//    CLA_initCpu1Cla1();
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_EPWM2INT);

//    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);

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

    controller.dtc_u = 0.f;
    controller.dtc_v = 0.f;
    controller.dtc_w = 0.f;
    set_dtc(&controller);

    // ADC zero offsets for current shunt amplifier readings ==========================================

    drv_enable_gd(drv);

    controller.dtc_u = 0.f;
    controller.dtc_v = 0.f;
    controller.dtc_w = 0.f;
    set_dtc(&controller);

    calibrate_adc_offsets = 1;
    while(adc_calibration_samples < NUM_ADC_CALIB_SAMPLES)
    {
        NOP; // wait for the ADC ISR to run for n samples in calibration mode
    }
    calibrate_adc_offsets = 0;

    controller.adc_a_offset = adc_a_offset/NUM_ADC_CALIB_SAMPLES;
    controller.adc_b_offset = adc_b_offset/NUM_ADC_CALIB_SAMPLES;

    drv_disable_gd(drv);

    // end ADC zero offsets for current shunt amplifier readings ======================================

    /*
     * TODO:
     * port flash writer to c2000 using Flash API   [ ]
     * add the ADC offset calibration here          [X] U
     * add v_bus ADC reading                        [~]
     * check the other TODO comments                [ ]
     * edit the calibration function and test       [ ]
     */

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
interrupt void PWM_ISR(void)
{

    pwm_count++;
    //flags get cleared in ADC ISR since we need time for CLA to run before clearing

}

#ifdef _FLASH
#pragma CODE_SECTION(INT_PHASE_B_ISR, ".TI.ramfunc");
#endif
interrupt void INT_PHASE_B_ISR(void)
{
    pwm_b_count++;

//    Interrupt_clearACKGroup(INT_PHASE_B_INTERRUPT_ACK_GROUP);
//    EPWM_clearEventTriggerInterruptFlag(PHASE_B_BASE);
}


uint64_t print_counter = 0;
#ifdef _FLASH
#pragma CODE_SECTION(INT_myADC0_1_ISR, ".TI.ramfunc");
#endif
interrupt void INT_myADC0_1_ISR(void)
{
    // 61 encoder counts = sine zero, 14 pole-pairs


    adcAResult = AdcaResultRegs.ADCRESULT0;
    adcBResult = AdcbResultRegs.ADCRESULT0;
    adcCResult = AdccResultRegs.ADCRESULT0; // zero ~ 2360

    // update controller with ADC data =====================================================

    if(!PHASE_ORDER)
    {
        controller.adc_a_raw = adcAResult;
        controller.adc_b_raw = adcBResult;
    }
    else
    {
        controller.adc_a_raw = adcBResult;
        controller.adc_b_raw = adcAResult;
    }

    if(calibrate_adc_offsets && adc_calibration_samples < NUM_ADC_CALIB_SAMPLES)
    {
        adc_a_offset +=  controller.adc_a_raw;
        adc_b_offset += controller.adc_b_raw;
        adc_calibration_samples++;
    }

    controller.adc_vbus_raw = AdcdResultRegs.ADCRESULT0;
    controller.v_bus = (float)controller.adc_vbus_raw*V_SCALE;

    controller.i_a = controller.i_scale*(float)(controller.adc_a_raw - controller.adc_a_offset);    // Calculate phase currents from ADC readings
    controller.i_b = controller.i_scale*(float)(controller.adc_b_raw - controller.adc_b_offset);
    controller.i_c = -controller.i_a - controller.i_b;

    // end update controller with ADC data =================================================

    angle = ( (float)(enc_pos) * (6.2831/1170.285) ) - 0.328 + 1.5708;
    while(angle > 6.2831) angle = angle - 6.2831;
    while(angle < 0) angle = angle + 6.2831;


    if(print_counter > 400)
    {
        IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG0, false, 0, 0, enc_pos);
        print_counter = 0;
    }
    print_counter++;

//    uint16_t duty0 = 0;//1250 + (int)(1240*sinf(angle));
//    uint16_t duty1 = 0;//1250 + (int)(1240*sinf(angle+2.09439));
//    uint16_t duty2 = 0;//1250 + (int)(1240*sinf(angle+4.18879));
//
//    if(run_motor == 1)
//    {
//        duty0 = 650 + (int)(300*sinf(angle));
//        duty1 = 650 + (int)(300*sinf(angle+2.09439));
//        duty2 = 650 + (int)(300*sinf(angle+4.18879));
//    }
//
////    angle = angle + delta_angle;
//
//    EPwm1Regs.CMPB.bit.CMPB = duty0;
//    EPwm2Regs.CMPB.bit.CMPB = duty1;
//    EPwm3Regs.CMPB.bit.CMPB = duty2;

    // ==================================================================================================
    // ========= BEGIN Motor control code here ==========================================================
    // ==================================================================================================

    // ADC <- these are ready when the isr starts
    // ENCODER <- the CLA is triggered 2us before this runs so that the data is ready by now
    // CAN <- CAN comms happens on CPU2, access the data to update the FSM & control
    // FSM
    run_fsm(&state);


    // ==================================================================================================
    // ========= END Motor control code here ============================================================
    // ==================================================================================================


    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    Interrupt_clearACKGroup(INT_PHASE_A_INTERRUPT_ACK_GROUP);
    EPWM_clearEventTriggerInterruptFlag(PHASE_A_BASE);



}

__interrupt void cla1Isr1 (void)
{

//    GpioDataRegs.GPATOGGLE.bit.GPIO22 = 1;
    Interrupt_clearACKGroup(INT_PHASE_B_INTERRUPT_ACK_GROUP);
    EPWM_clearEventTriggerInterruptFlag(PHASE_B_BASE);

    PieCtrlRegs.PIEACK.all = M_INT11;
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
