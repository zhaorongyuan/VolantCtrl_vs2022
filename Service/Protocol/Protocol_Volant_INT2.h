/*
 * Protocol_Volant_INT2.h
 *
 *  Created on: 2024年11月23日
 *      Author: sz-p1159
 */

#ifndef SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_INT2_H_
#define SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_INT2_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/*此处添加引用的头文件*/

#include "Protocal_Volant_Types.h"
#include "FlexCan_Ip.h"

/* Exported constants --------------------------------------------------------*/
/*此处添加向外暴露的宏定义常量*/

#define CCSP_NAME_INT2 "Volant_INT2_Protocol"

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
#define CCSP_BAUDRATE_INT2 500000

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
#define CCSP_FASTBAUDRATE_INT2 2000000

/**
 * @brief 定义协议层的 CAN 设备类型
 *
 * 此宏定义了协议层使用的 CAN 设备类型。在这个例子中，设备类型被设置为标准 CAN 类型。

 * @value 0 普通CAN设备类型。
 * @value 1 CAN FD设备类型。
 */
#define CCSP_DEVICETYPE_INT2		1

#define MCU_INT2_TX_CtrlMsg			0
#define MCU_INT2_RX_CtrlMsg			1

#define MCU_INT2_TX_StateMsg		2
#define MCU_INT2_RX_StateMsg		3

#define CCSP_FRAME_NUM_INT2			4

#define CCSP_EVENTFRAME_NUM_INT2	1   ///<最小为1

/* Exported macro ------------------------------------------------------------*/
/*此处添加向外暴露的宏定义函数*/

/* Exported types ------------------------------------------------------------*/
/*此处添加向外暴露的结构体声明*/

/* Exported variables --------------------------------------------------------*/
/*此处添加向外暴露的变量*/

extern CanStdProtocol_t g_VolantInt2Protocol;

/* Private inline functions --------------------------------------------------*/
/*此处添加向外暴露的内联函数*/

/* Exported functions prototypes ---------------------------------------------*/
/*此处添加向外暴露的函数声明*/

extern void CanProtocol_MCU_INT2_TX_CtrlMsg_Update(void *pframe);
extern void CanProtocol_MCU_INT2_RX_CtrlMsg_Update(void *pframe);

extern void CanProtocol_MCU_INT2_TX_StateMsg_Update(void *pframe);
extern void CanProtocol_MCU_INT2_RX_StateMsg_Update(void *pframe);

extern uint32 CanProtocol_Volant_INT2_Event_Trigger(void);

extern void CanProtocol_Volant_INT2_Event_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* SW_CONFIG_PROTOCOL_PROTOCOL_VOLANT_INT2_H_ */
