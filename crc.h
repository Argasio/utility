/*!
 *    @file             $Source: common/utility/crc.h $
 *    @brief            Header file for CRC 16 calculation methods.
 *
 *    @author           $Author: David Vescovi (dvescovi) $
 *
 *    @version          $Revision: 1.2 $
 *
 *    @date             $Date: 2018/01/31 19:49:01EST $
 *
 *    @par Copyright
 *                      (C) 2020 Medtronic. All rights reserved.
 */

#ifndef __CRC_H__
#define __CRC_H__
#include <stdint.h>

#define POLYNOMIAL 0x1021
typedef uint16_t crc_t;

#ifdef __cplusplus
extern "C"
{
#endif

extern int crc_ok;
extern void crcInit(void);
extern crc_t crc16(uint8_t const message[], int nBytes);
extern crc_t crc16_EscapeEncoded(const uint8_t* message, int bytes, uint8_t escapeChar);
extern crc_t crc16_Remainder(uint8_t const message[], int nBytes, crc_t current_remainder);

uint32_t crc32(uint32_t crc, uint8_t *buf, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __CRC_H__ */
