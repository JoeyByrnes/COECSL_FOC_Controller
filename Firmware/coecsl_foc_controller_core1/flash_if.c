#include "flash_if.h"

extern uint32_t   read_buff[8];

extern uint16 read_buffer[1];

extern float __float_reg[64];
extern int __int_reg[256];

volatile int length_remaining;
volatile int buff_index;
volatile int addr_index;

void readBufferFromFlash(uint32_t address_offset,uint32_t* buffer, uint32_t buffer_length)
{
    Fapi_StatusType oReturnCheck;
    volatile Fapi_FlashStatusType oFlashStatus;
    Fapi_FlashStatusWordType oFlashStatusWord;

    // Grab flash semaphore for Zone1 to enable access to flash registers.
    EALLOW;
    DcsmCommonRegs.FLSEM.all = 0xA501;
    EDIS;

    //
    // Call flash initialization to setup flash waitstates.
    // This function must reside in RAM.
    //
    InitFlash();

    SeizeFlashPump();

    // Disable ECC.
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0x0;

    // This function is required to initialize the Flash API based on system
    // frequency before any other Flash API operation can be performed.
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 200);

    // Fapi_setActiveFlashBank function sets the flash bank and FMC for further
    // flash operations to be performed on the bank.
    //
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

    uint32_t val;

//
//    oReturnCheck = Fapi_doMarginRead(0x0BE000+address_offset,buffer,buffer_length,Fapi_NormalRead);
//    int i = 0;
//    length_remaining = buffer_length;
//    buff_index = 0;
//    addr_index = 0;
//
//    while(length_remaining > 8)
//    {
//        Fapi_doMarginRead((uint32 *)0x0BE000+address_offset+addr_index,&buffer[buff_index],8,Fapi_NormalRead);
//
//        length_remaining = length_remaining - 8;
//        buff_index = buff_index + 8;
//        addr_index = addr_index + 4;
//    }
//    if(length_remaining > 0)
//    {
//        Fapi_doMarginRead((uint32 *)0x0BE000+address_offset+addr_index,&buffer[buff_index],length_remaining,Fapi_NormalRead);
//
//    }

    Fapi_doMarginRead((uint32 *)0x0BE000+address_offset,buffer,buffer_length,Fapi_NormalRead);

    //
    // Enable ECC.
    //
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    //
    // Release flash semaphore.
    //
    DcsmCommonRegs.FLSEM.all = 0xA500;

    EDIS;

}

void writeBufferToFlash(uint32_t address_offset,uint16_t* buffer, uint32_t buffer_length)
{
    Fapi_StatusType oReturnCheck;
    volatile Fapi_FlashStatusType oFlashStatus;
    Fapi_FlashStatusWordType oFlashStatusWord;

    // Grab flash semaphore for Zone1 to enable access to flash registers.
    EALLOW;
    DcsmCommonRegs.FLSEM.all = 0xA501;
    EDIS;

    //
    // Call flash initialization to setup flash waitstates.
    // This function must reside in RAM.
    //
    InitFlash();

    SeizeFlashPump();

    // Disable ECC.
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0x0;

    // This function is required to initialize the Flash API based on system
    // frequency before any other Flash API operation can be performed.
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 200);

    // Fapi_setActiveFlashBank function sets the flash bank and FMC for further
    // flash operations to be performed on the bank.
    //
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);

    // Erase Sector N.
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorN_start);

    // Wait until FSM is done with erase sector operation.
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady)
    {
    }

    // Verify that Sector N is erased. The erase step itself does verification
    // as it goes. This verify is a second verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorN_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);

    int i = 0;
    length_remaining = buffer_length;
    buff_index = 0;
    addr_index = 0;

    while(length_remaining > 8)
    {
        Fapi_issueProgrammingCommand((uint32 *)0x0BE000+address_offset+addr_index,&buffer[buff_index], 8, 0, 0, Fapi_DataOnly);
        // Wait until FSM is done with program operation.
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy)
        {
        }
        length_remaining = length_remaining - 8;
        buff_index = buff_index + 8;
        addr_index = addr_index + 4;
    }
    if(length_remaining > 0)
    {
        Fapi_issueProgrammingCommand((uint32 *)0x0BE000+address_offset+addr_index,&buffer[buff_index], length_remaining, 0, 0, Fapi_DataOnly);
        // Wait until FSM is done with program operation.
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy)
        {
        }
    }


    //
    // Enable ECC.
    //
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    //
    // Release flash semaphore.
    //
    DcsmCommonRegs.FLSEM.all = 0xA500;

    EDIS;

}

//void serializeConfig(const Configuration* config, uint16_t* buffer)
//{
//    const uint8_t* configBytes = (const uint8_t*)config;
//    int i;
//    for (i = 0; i < sizeof(Configuration); ++i) {
//        buffer[i / 2] |= configBytes[i] << ((i % 2) * 8);
//    }
//}
//
//void deserializeConfig(const uint16_t* buffer, Configuration* config)
//{
//    uint8_t* configBytes = (uint8_t*)config;
//    int i;
//    for (i = 0; i < sizeof(Configuration); ++i) {
//        configBytes[i] = (buffer[i / 2] >> ((i % 2) * 8)) & 0xFF;
//    }
//}

void floatToUint16Buffer(const float* floatBuffer, size_t floatBufferLength, uint16_t* uint16Buffer)
{
    int i;
    for(i=0; i<floatBufferLength*2;i+=2)
    {
        FloatUint16Union un;
        un.floatValue = floatBuffer[i/2];
        uint16Buffer[i] = un.uint16Values[0];
        uint16Buffer[i+1] = un.uint16Values[1];
    }
}

void intToUint16Buffer(const int* intBuffer, size_t intBufferLength, uint16_t* uint16Buffer)
{
    int i;
    for(i=0; i<intBufferLength*2;i+=2)
    {
        Int32Uint16Union un;
        un.int32Value = intBuffer[i/2];
        uint16Buffer[i] = un.uint16Values[0];
        uint16Buffer[i+1] = un.uint16Values[1];
    }
}

void uint32ToUint16Buffer(const uint32_t* intBuffer, size_t intBufferLength, uint16_t* uint16Buffer)
{
    int i;
    for(i=0; i<intBufferLength*2;i+=2)
    {
        Uint32Uint16Union un;
        un.uint32Value = intBuffer[i/2];
        uint16Buffer[i] = un.uint16Values[0];
        uint16Buffer[i+1] = un.uint16Values[1];
    }
}

void uint16ToFloatBuffer(const uint16_t* uint16Buffer, size_t uint16BufferLength, float* floatBuffer)
{
    int i;
    for(i=0; i<uint16BufferLength;i+=2)
    {
        FloatUint16Union un;
        un.uint16Values[0] = uint16Buffer[i];
        un.uint16Values[1] = uint16Buffer[i+1];
        floatBuffer[i/2] = un.floatValue;
    }
}

void uint16ToIntBuffer(const uint16_t* uint16Buffer, size_t uint16BufferLength, int* intBuffer)
{
    int i;
    for(i=0; i<uint16BufferLength;i+=2)
    {
        Int32Uint16Union un;
        un.uint16Values[0] = uint16Buffer[i];
        un.uint16Values[1] = uint16Buffer[i+1];
        intBuffer[i/2] = un.int32Value;
    }
}

void writeConfigToFlash()
{
    uint16_t uint16FloatRegBuffer[128];
    floatToUint16Buffer(__float_reg,64,uint16FloatRegBuffer);

    uint16_t uint16IntRegBuffer[512];
    intToUint16Buffer(__int_reg,256,uint16IntRegBuffer);

    uint16_t combinedBuffer[640];
    int i;
    for(i=0;i<128;i++) combinedBuffer[i] = uint16FloatRegBuffer[i];
    for(i=128;i<640;i++) combinedBuffer[i] = uint16IntRegBuffer[i-128];

    writeBufferToFlash(0,combinedBuffer,640);

}

void readConfigFromFlash()
{
    uint32_t combinedBufferUint32[320];
    uint16_t combinedBuffer[640];
    uint16_t uint16FloatRegBuffer[128];
    uint16_t uint16IntRegBuffer[512];

    readBufferFromFlash(0,combinedBufferUint32,320);

    uint32ToUint16Buffer(combinedBufferUint32,320,combinedBuffer);

    int i;
    for(i=0;i<128;i++) uint16FloatRegBuffer[i] = combinedBuffer[i];
    for(i=128;i<640;i++) uint16IntRegBuffer[i-128] = combinedBuffer[i];

    uint16ToFloatBuffer(uint16FloatRegBuffer, 128, __float_reg);

    uint16ToIntBuffer(uint16IntRegBuffer, 512, __int_reg);

}


