#include "flash_defines.h"
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
#include "F021_F2837xD_C28x.h"


#define ramFuncSection ".TI.ramfunc"

void readBufferFromFlash(uint32_t address_offset,uint32_t* buffer, uint32_t buffer_length);

void writeBufferToFlash(uint32_t address_offset,uint16_t* buffer, uint32_t buffer_length);


//void serializeConfig(const Configuration* config, uint16_t* buffer);
//void deserializeConfig(const uint16_t* buffer, Configuration* config);

void floatToUint16Buffer(const float* floatBuffer, size_t floatBufferLength, uint16_t* uint16Buffer);
void intToUint16Buffer(const int* intBuffer, size_t intBufferLength, uint16_t* uint16Buffer);

void uint32ToUint16Buffer(const uint32_t* intBuffer, size_t intBufferLength, uint16_t* uint16Buffer);

void uint16ToFloatBuffer(const uint16_t* uint16Buffer, size_t uint16BufferLength, float* floatBuffer);
void uint16ToIntBuffer(const uint16_t* uint16Buffer, size_t uint16BufferLength, int* intBuffer);

void writeConfigToFlash();
void readConfigFromFlash();

typedef union {
    float floatValue;
    uint16_t uint16Values[2];
} FloatUint16Union;

typedef union {
    int32_t int32Value;
    uint16_t uint16Values[2];
} Int32Uint16Union;

typedef union {
    uint32_t uint32Value;
    uint16_t uint16Values[2];
} Uint32Uint16Union;

