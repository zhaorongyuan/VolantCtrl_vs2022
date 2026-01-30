/*
 * ARINC825.h
 *
 *  Created on: 2025Äê3ÔÂ13ÈÕ
 *      Author: sz-p1159
 */

#ifndef SW_CONFIG_CRC_ARINC825_H_
#define SW_CONFIG_CRC_ARINC825_H_

#include "Platform_Types.h"

extern _Bool checkA825CRC(uint32 canId, uint8 dataLen, const uint8 *pData);

extern void setA825CRC(uint32 canId, uint8 dataLen, uint8 *pData);

extern uint16 A825CRCCompute(uint16 CRC, const uint8 *pData, uint16 dataLen);

#endif /* SW_CONFIG_CRC_ARINC825_H_ */
