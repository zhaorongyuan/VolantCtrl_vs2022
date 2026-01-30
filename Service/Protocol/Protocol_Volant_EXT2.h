/*
 * Protocol_Volant_CAN1_EXT.h
 *
 *  Created on: 2024年11月22日
 *      Author: sz-p1159
 */

#ifndef SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_EXT2_H_
#define SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_EXT2_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/*此处添加引用的头文件*/

#include "Protocal_Volant_Types.h"
#include "FlexCAN_Ip.h"

/* Exported constants --------------------------------------------------------*/
/*此处添加向外暴露的宏定义常量*/

#define CCSP_NAME_EXT2 "Volant_EXT2_Protocol"

/**
 * @brief 定义协议层的CAN波特率
 *
 * 此宏定义了协议层使用的CAN通信波特率。在这个例子中，波特率被设置为500Kbps。
 *
 * @value 100000 CAN 波特率：100K。
 * @value 125000 CAN 波特率：125K。
 * @value 250000 CAN 波特率：250K。
 * @value 500000 CAN 波特率：500K。
 * @value 800000 CAN 波特率：800K。
 * @value 1000000 CAN 波特率：1000K。
 */
#define CCSP_BAUDRATE_EXT2 500000

/**
 * @brief 定义协议层的快速 CAN 波特率
 *
 * 此宏定义了协议层使用的快速 CAN 通信波特率。在这个例子中，波特率被设置为默认值。
 *
 * @value 0 数据域速率不变。
 * @value 1000000 快速CAN波特率为1000K。
 * @value 2000000 快速CAN波特率为2000K。
 * @value 3000000 快速CAN波特率为3000K。
 * @value 4000000 快速CAN波特率为4000K。
 * @value 5000000 快速CAN波特率为5000K。
 **/
#define CCSP_FASTBAUDRATE_EXT2 2000000

/**
 * @brief 定义协议层的 CAN 设备类型
 *
 * 此宏定义了协议层使用的 CAN 设备类型。在这个例子中，设备类型被设置为标准 CAN 类型。

 * @value 0 普通CAN设备类型。
 * @value 1 CAN FD设备类型。
 */
#define CCSP_DEVICETYPE_EXT2		1

#define PFCC1_CtrlMsg_MCU_EXT2		0
#define PFCC1_PHSM_MCU_EXT2			1

#define PFCC2_CtrlMsg_MCU_EXT2		2
#define PFCC2_PHSM_MCU_EXT2			3

#define PFCC3_CtrlMsg_MCU_EXT2		4
#define PFCC3_PHSM_MCU_EXT2			5

#define MCU_EXT2_FbkMsg_PFCC		6
#define MCU_EXT2_NormalMsg_PFCC		7
#define MCU_EXT2_PHSM				8
#define MCU_EXT2_ConfigMsg			9

#define UDS_RX_MB                   10
#define UDS_TX_MB                   11

#define CCSP_FRAME_NUM_EXT2			13

#define CCSP_EVENTFRAME_NUM_EXT2	1   ///<最小为1

#define CCP_RX_MB                   12
#define CCP_SET_MTA                 0x02
#define CCP_DNLOAD                  0x03
#define CCP_REPROT                  0x04

/* Exported macro ------------------------------------------------------------*/
/*此处添加向外暴露的宏定义函数*/

/* Exported types ------------------------------------------------------------*/
/*此处添加向外暴露的结构体声明*/

/* Exported variables --------------------------------------------------------*/
/*此处添加向外暴露的变量*/
extern CanStdProtocol_FrameInfo_t sg_frameInfoList_EXT2[CCSP_FRAME_NUM_EXT2];
extern CanStdProtocol_t g_VolantExt2Protocol;

extern uint8 Uds_Mode;
extern uint8 Jump_To_Load;


extern uint32 GcBSW_CcpRepoValue_numb;
extern uint32 GcBSW_CcpRepoAddr_numb;

/* Private inline functions --------------------------------------------------*/
/*此处添加向外暴露的内联函数*/

/* Exported functions prototypes ---------------------------------------------*/
/*此处添加向外暴露的函数声明*/

extern void CanProtocol_PFCC1_CtrlMsg_MCU_EXT2_Update(void *pframe);
extern void CanProtocol_PFCC1_PHSM_MCU_EXT2_Update(void *pframe);

extern void CanProtocol_PFCC2_CtrlMsg_MCU_EXT2_Update(void *pframe);
extern void CanProtocol_PFCC2_PHSM_MCU_EXT2_Update(void *pframe);

extern void CanProtocol_PFCC3_CtrlMsg_MCU_EXT2_Update(void *pframe);
extern void CanProtocol_PFCC3_PHSM_MCU_EXT2_Update(void *pframe);

extern void CanProtocol_MCU_EXT2_FbkMsg_PFCC_Update(void *pframe);
extern void CanProtocol_MCU_EXT2_NormalMsg_PFCC_Update(void *pframe);
extern void CanProtocol_MCU_EXT2_PHSM_Update(void *pframe);
extern void CanProtocol_MCU_EXT2_ConfigMsg_Update(void *pframe);

extern uint32 CanProtocol_Volant_EXT2_Event_Trigger(void);

extern void CanProtocol_Volant_EXT2_Event_Update(void);


#ifdef __cplusplus
}
#endif

#endif /* SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_EXT2_H_ */
