///*
// * flash_writer.h
// *
// *  Created on: Apr 12, 2020
// *      Author: Ben
// */
//
//#ifndef INC_FLASH_WRITER_H_
//#define INC_FLASH_WRITER_H_
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//
//#include "stdbool.h"
//
///* Base address of the Flash sectors */
//#define ADDR_FLASH_SECTOR_A     ((uint32_t)0x080002) /* Base @ of Sector A, ? Kbytes, length = 0x001FFE */
//#define ADDR_FLASH_SECTOR_B     ((uint32_t)0x082000) /* Base @ of Sector B, ? Kbytes, length = 0x002000 */
//#define ADDR_FLASH_SECTOR_C     ((uint32_t)0x084000) /* Base @ of Sector C, ? Kbytes, length = 0x002000 */
//#define ADDR_FLASH_SECTOR_D     ((uint32_t)0x086000) /* Base @ of Sector D, ? Kbytes, length = 0x002000 */
//#define ADDR_FLASH_SECTOR_E     ((uint32_t)0x088000) /* Base @ of Sector E, ? Kbytes, length = 0x008000 */
//#define ADDR_FLASH_SECTOR_F     ((uint32_t)0x090000) /* Base @ of Sector F, ? Kbytes, length = 0x008000 */
//#define ADDR_FLASH_SECTOR_G     ((uint32_t)0x098000) /* Base @ of Sector G, ? Kbytes, length = 0x008000 */
//#define ADDR_FLASH_SECTOR_H     ((uint32_t)0x0A0000) /* Base @ of Sector H, ? Kbytes, length = 0x008000 */
//#define ADDR_FLASH_SECTOR_I     ((uint32_t)0x0A8000) /* Base @ of Sector I, ? Kbytes, length = 0x008000 */
//#define ADDR_FLASH_SECTOR_J     ((uint32_t)0x0B0000) /* Base @ of Sector J, ? Kbytes, length = 0x008000 */
//#define ADDR_FLASH_SECTOR_K     ((uint32_t)0x0B8000) /* Base @ of Sector K, ? Kbytes, length = 0x002000 */
//#define ADDR_FLASH_SECTOR_L     ((uint32_t)0x0BA000) /* Base @ of Sector L, ? Kbytes, length = 0x002000 */
//#define ADDR_FLASH_SECTOR_M     ((uint32_t)0x0BC000) /* Base @ of Sector M, ? Kbytes, length = 0x002000 */
//#define ADDR_FLASH_SECTOR_N     ((uint32_t)0x0BE000) /* Base @ of Sector N, ? Kbytes, length = 0x001FF0 */
//
//static uint32_t __SECTOR_ADDRS[] = {ADDR_FLASH_SECTOR_A,
//                                    ADDR_FLASH_SECTOR_B,
//                                    ADDR_FLASH_SECTOR_C,
//                                    ADDR_FLASH_SECTOR_D,
//                                    ADDR_FLASH_SECTOR_E,
//                                    ADDR_FLASH_SECTOR_F,
//                                    ADDR_FLASH_SECTOR_G,
//                                    ADDR_FLASH_SECTOR_H,
//                                    ADDR_FLASH_SECTOR_I,
//                                    ADDR_FLASH_SECTOR_J,
//                                    ADDR_FLASH_SECTOR_K,
//                                    ADDR_FLASH_SECTOR_L,
//                                    ADDR_FLASH_SECTOR_M,
//                                    ADDR_FLASH_SECTOR_N,
//                                    };
//static uint32_t __SECTORS[] = {FLASH_Sector_0,
//                               FLASH_Sector_1,
//                               FLASH_Sector_2,
//                               FLASH_Sector_3,
//                               FLASH_Sector_4,
//                               FLASH_Sector_6,
//                               FLASH_Sector_6,
//                               FLASH_Sector_7
//                               };
//
//typedef struct {
//	bool ready;
//	uint32_t base;
//	uint32_t sector;
//}FlashWriter;
//
//void flash_writer_init(FlashWriter *fw, uint32_t sector);
//bool flash_writer_ready(FlashWriter fw);
//void flash_writer_open(FlashWriter *fw);
//void flash_writer_write_int(FlashWriter fw, uint32_t index, int x);
//void flash_writer_write_uint(FlashWriter fw, uint32_t index, unsigned int x);
//void flash_writer_write_float(FlashWriter fw, uint32_t index, float x);
//void flash_writer_close(FlashWriter *fw);
//int flash_read_int(FlashWriter fw, uint32_t index);
//uint32_t flash_read_uint(FlashWriter fw, uint32_t index);
//float flash_read_float(FlashWriter fw, uint32_t index);
//
//#ifdef __cplusplus
//}
//#endif
//
//#endif /* INC_FLASH_WRITER_H_ */
