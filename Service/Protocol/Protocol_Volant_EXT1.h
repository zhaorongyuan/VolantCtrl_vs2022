/*
 * Protocol_Volant_CAN0_EXT.h
 *
 *  Created on: 2024年11月22日
 *      Author: sz-p1159
 */

#ifndef SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_EXT1_H_
#define SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_EXT1_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/*此处添加引用的头文件*/

#include "Protocal_Volant_Types.h"

/* Exported constants --------------------------------------------------------*/
/*此处添加向外暴露的宏定义常量*/

#define CCSP_NAME_EXT1 "Volant_EXT1_Protocol"



/**
 * @brief 定义协议层的 CAN 设备类型
 *
 * 此宏定义了协议层使用的 CAN 设备类型。在这个例子中，设备类型被设置为标准 CAN 类型。

 * @value 0 普通CAN设备类型。
 * @value 1 CAN FD设备类型。
 */
#define CCSP_DEVICETYPE_EXT1		1

#define PFCC1_CtrlMsg_MCU_EXT1		0
#define PFCC1_PHSM_MCU_EXT1			1

#define PFCC2_CtrlMsg_MCU_EXT1		2
#define PFCC2_PHSM_MCU_EXT1			3

#define PFCC3_CtrlMsg_MCU_EXT1		4
#define PFCC3_PHSM_MCU_EXT1			5

#define MCU_EXT1_FbkMsg_PFCC		6
#define MCU_EXT1_NormalMsg_PFCC		7
#define MCU_EXT1_PHSM				8
#define MCU_EXT1_ConfigMsg			9

#define MCU_EXT1_DebugMsg_Rx0		10
#define MCU_EXT1_DebugMsg_Tx0		11
#define MCU_EXT1_DebugMsg_Tx1		12

#define MCU_EXT1_DebugMsg_TxF		13

#define MCU_EXT1_FeeMsg_Tx			14

#define CCSP_FRAME_NUM_EXT1			15

#define CCSP_EVENTFRAME_NUM_EXT1	1   ///<最小为1

/* Exported macro ------------------------------------------------------------*/
/*此处添加向外暴露的宏定义函数*/

/* Exported types ------------------------------------------------------------*/
/*此处添加向外暴露的结构体声明*/

/* Exported variables --------------------------------------------------------*/
/*此处添加向外暴露的变量*/

extern CanStdProtocol_t g_VolantExt1Protocol;

/* Private inline functions --------------------------------------------------*/
/*此处添加向外暴露的内联函数*/

/* Exported functions prototypes ---------------------------------------------*/
/*此处添加向外暴露的函数声明*/

extern void CanProtocol_PFCC1_CtrlMsg_MCU_EXT1_Update(void *pframe);
extern void CanProtocol_PFCC1_PHSM_MCU_EXT1_Update(void *pframe);

extern void CanProtocol_PFCC2_CtrlMsg_MCU_EXT1_Update(void *pframe);
extern void CanProtocol_PFCC2_PHSM_MCU_EXT1_Update(void *pframe);

extern void CanProtocol_PFCC3_CtrlMsg_MCU_EXT1_Update(void *pframe);
extern void CanProtocol_PFCC3_PHSM_MCU_EXT1_Update(void *pframe);

extern void CanProtocol_MCU_EXT1_FbkMsg_PFCC_Update(void *pframe);
extern void CanProtocol_MCU_EXT1_NormalMsg_PFCC_Update(void *pframe);
extern void CanProtocol_MCU_EXT1_PHSM_Update(void *pframe);
extern void CanProtocol_MCU_EXT1_ConfigMsg_Update(void *pframe);

extern void CanProtocol_MCU_EXT1_DebugMsg_Rx0_Update(void *pframe);
extern void CanProtocol_MCU_EXT1_DebugMsg_Tx0_Update(void *pframe);
extern void CanProtocol_MCU_EXT1_DebugMsg_Tx1_Update(void *pframe);

extern void CanProtocol_MCU_EXT1_DebugMsg_TxF_Update(void *pframe);

extern void CanProtocol_MCU_EXT1_FeeMsg_Tx_Update(void *pframe);

extern uint32 CanProtocol_Volant_EXT1_Event_Trigger(void);

extern void CanProtocol_Volant_EXT1_Event_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_EXT1_H_ */
