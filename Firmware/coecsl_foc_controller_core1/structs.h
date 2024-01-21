/*
 * structs.h
 *
 *  Created on: Mar 5, 2020
 *      Author: Ben
 */

#ifndef STRUCTS_H
#define STRUCTS_H




#include <stdint.h>
#include "position_sensor.h"
//#include "preference_writer.h"
#include "fsm.h"
#include "drv8323.h"
#include "foc.h"
#include "calibration.h"
#include "can.h"

typedef struct{
    } GPIOStruct;

typedef struct{
    }COMStruct;


/* Global Structs */
extern ControllerStruct controller;
extern ObserverStruct observer;
extern COMStruct com;
extern FSMStruct state;
extern EncoderStruct comm_encoder;
extern DRVStruct drv;
//extern PreferenceWriter prefs;
extern CalStruct comm_encoder_cal;
extern CANTxMessage can_tx;
extern CANRxMessage can_rx;

//#pragma pack(1) // Pack struct members tightly without padding
//
//typedef struct {
//    float I_BW;
//    float I_MAX;
//    float THETA_MIN;
//    float THETA_MAX;
//    float I_FW_MAX;
//    float R_NOMINAL;
//    float TEMP_MAX;
//    float I_MAX_CONT;
//    float PPAIRS;
//    float R_PHASE;
//    float KT;
//    float R_TH;
//    float C_TH;
//    float GR;
//    float I_CAL;
//    float P_MIN;
//    float P_MAX;
//    float V_MIN;
//    float V_MAX;
//    float KP_MAX;
//    float KD_MAX;
//
//    int PHASE_ORDER;
//    int CAN_ID;
//    int CAN_MASTER;
//    int CAN_TIMEOUT;
//    int M_ZERO;
//    int E_ZERO;
//    int ENCODER_LUT[128]; // 128 elements
//} Configuration;
//
//#pragma pack() // Reset the packing to default


#endif
