 /**
 * @file Protocol_Volant_CAN0_EXT.c
 * @brief Can标准协议文件头文件
 * @mainpage 文件概览
 * @author
 * @email
 * @version 0.1
 * @date 2024-11-04
 *
 * @copyright Copyright (c) 2024, SANTROLL Co.,Ltd.
 *
 */

/* Includes ------------------------------------------------------------------*/
/*此处添加本文件需引用的头文件*/
#include <Protocol_Volant_EXT1.h>
#include "stdlib.h"
//#include "Pmsm_Param.h"
#include "Hal_NVM.h"
#include "CanSM.h"
#include "Interface.h"
#include "MTM.h"
#include "CanIsrMsg.h"
#include "SPL.h"
#include "AD2S1210.h"

/* Private define ------------------------------------------------------------*/
/*此处添加仅本文件使用的宏定义常量*/

/* Private macro -------------------------------------------------------------*/
/*此处添加仅本文件使用的宏定义函数*/

/* Private typedef -----------------------------------------------------------*/
/*′?′|ìí?ó??±????tê1ó?μ??á11ì?éù?÷*/

/* Private variables ---------------------------------------------------------*/
/*此处添加仅本文件使用的全局变量*/



static CanStdProtocol_FrameInfo_t sg_frameInfoList_EXT1[CCSP_FRAME_NUM_EXT1] =
{
	  {.SN = 0, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 10, .offset = 1, \
		.enableFlag = TRUE, .frameId = 0x08520204, .pfDataUpdateFunc = CanProtocol_PFCC1_CtrlMsg_MCU_EXT1_Update, .pfTriggerFunc = NULL},

		{.SN = 1, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 0, .sendType = 0, .interval = 1000, .offset = 2, \
		.enableFlag = TRUE, .frameId = 0x1BEEFA04, .pfDataUpdateFunc = CanProtocol_PFCC1_PHSM_MCU_EXT1_Update, .pfTriggerFunc = NULL},

		{.SN = 2, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 10, .offset = 3, \
		.enableFlag = TRUE, .frameId = 0x08520205, .pfDataUpdateFunc = CanProtocol_PFCC2_CtrlMsg_MCU_EXT1_Update, .pfTriggerFunc = NULL},

		{.SN = 3, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 0, .sendType = 0, .interval = 1000, .offset = 4, \
		.enableFlag = TRUE, .frameId = 0x1BEEFA05, .pfDataUpdateFunc = CanProtocol_PFCC2_PHSM_MCU_EXT1_Update, .pfTriggerFunc = NULL},

		{.SN = 4, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 10, .offset = 5, \
		.enableFlag = TRUE, .frameId = 0x08520206, .pfDataUpdateFunc = CanProtocol_PFCC3_CtrlMsg_MCU_EXT1_Update, .pfTriggerFunc = NULL},

		{.SN = 5, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 0, .sendType = 0, .interval = 1000, .offset = 6, \
		.enableFlag = TRUE, .frameId = 0x1BEEFA06, .pfDataUpdateFunc = CanProtocol_PFCC3_PHSM_MCU_EXT1_Update, .pfTriggerFunc = NULL},

		{.SN = 6, .frameFormat = 1, .frameMode = 2, .dataLength = 12, .direction = 1, .sendType = 0, .interval = 10, .offset = 1, \
		.enableFlag = FALSE, .frameId = 0x08522000, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_FbkMsg_PFCC_Update, .pfTriggerFunc = NULL},

		{.SN = 7, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 1, .sendType = 0, .interval = 100, .offset = 2, \
		.enableFlag = FALSE, .frameId = 0x08522200, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_NormalMsg_PFCC_Update, .pfTriggerFunc = NULL},

		{.SN = 8, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 1, .sendType = 0, .interval = 1000, .offset = 3, \
		.enableFlag = FALSE, .frameId = 0x1BEEFA00, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_PHSM_Update, .pfTriggerFunc = NULL},

		{.SN = 9, .frameFormat = 1, .frameMode = 2, .dataLength = 48, .direction = 1, .sendType = 0, .interval = 1000, .offset = 4, \
		.enableFlag = FALSE, .frameId = 0x1854CC00, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_ConfigMsg_Update, .pfTriggerFunc = NULL},

		// 调试报文
		{.SN = 10, .frameFormat = 1, .frameMode = 2, .dataLength = 16, .direction = 0, .sendType = 0, .interval = 10, .offset = 7, \
		.enableFlag = FALSE, .frameId = 0x18EF00AB, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_DebugMsg_Rx0_Update, .pfTriggerFunc = NULL},

		{.SN = 11, .frameFormat = 1, .frameMode = 2, .dataLength = 64, .direction = 1, .sendType = 0, .interval = 10, .offset = 5, \
		.enableFlag = FALSE, .frameId = 0x18EF0010, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_DebugMsg_Tx0_Update, .pfTriggerFunc = NULL},

		{.SN = 12, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 1, .sendType = 0, .interval = 10, .offset = 6, \
		.enableFlag = FALSE, .frameId = 0x18EF0011, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_DebugMsg_Tx1_Update, .pfTriggerFunc = NULL},

		// 中断报文
		{.SN = 13, .frameFormat = 1, .frameMode = 2, .dataLength = 48, .direction = 1, .sendType = 0, .interval = 10, .offset = 7, \
		.enableFlag = TRUE, .frameId = 0x18EF001F, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_DebugMsg_TxF_Update, .pfTriggerFunc = NULL},

		// FEE报文
		{.SN = 14, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 1, .sendType = 0, .interval = 100, .offset = 8, \
		.enableFlag = FALSE, .frameId = 0x18EE001F, .pfDataUpdateFunc = CanProtocol_MCU_EXT1_FeeMsg_Tx_Update, .pfTriggerFunc = NULL}
};

static uint32 sg_eventList_EXT1[CCSP_EVENTFRAME_NUM_EXT1] =
{
    0,
};

/* Exported variables --------------------------------------------------------*/
/*此处添加本文件向外暴露的变量*/



CanStdProtocol_t g_VolantExt1Protocol =
{
    .name = CCSP_NAME_EXT1,
    .baudrate = 500000,
    .fastBaudrate = 2000000,
    .deviceType = CCSP_DEVICETYPE_EXT1,
    .frameNum = CCSP_FRAME_NUM_EXT1,
    .pframeInfoList = sg_frameInfoList_EXT1,
    .pEventList = sg_eventList_EXT1,
    .pfEventUpdate = CanProtocol_Volant_EXT1_Event_Update
};

/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数声明*/

static void MCUA_EXT1_NormalMsg_Pack(void *pframe);

static void MCUB_EXT1_NormalMsg_Pack(void *pframe);

/* Exported functions --------------------------------------------------------*/
/*此处添加本文件向外暴露的函数定义*/

void CanProtocol_PFCC1_CtrlMsg_MCU_EXT1_Update(void *pframe)
{
	CANFD_EXT_RX1_OBJ *pCanFrame = (CANFD_EXT_RX1_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_EXT1[PFCC1_CtrlMsg_MCU_EXT1].frameId, sg_frameInfoList_EXT1[PFCC1_CtrlMsg_MCU_EXT1].dataLength, pframe))
	{
		Intf_Vlant_PFCC[CH1_PFCC1].CrcRightFlag = TRUE;

		Intf_Vlant_PFCC[CH1_PFCC1].PFCC_IsPrimaryChannel = pCanFrame->Data.PFCC_IsPrimaryChannel & 0x01;
		Intf_Vlant_PFCC[CH1_PFCC1].PFCC_HiVltgSW = pCanFrame->Data.PFCC_HiVltgSW & 0x03;
		Intf_Vlant_PFCC[CH1_PFCC1].PFCC_DisplayHVState = pCanFrame->Data.PFCC_DisplayHVState & 0x03;
		Intf_Vlant_PFCC[CH1_PFCC1].PFCC_CmdCommunicationConfirm = ((pCanFrame->Data.PFCC_CmdCommunicationConfirm_H & 0xFF) << 8) + (pCanFrame->Data.PFCC_CmdCommunicationConfirm_L & 0xFF);

		switch(CanVolantData.LocNum)
		{
			case 1:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU1WorkMod & 0x07;
				break;
			case 2:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU2WorkMod & 0x07;
				break;
			case 3:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU3WorkMod & 0x07;
				break;
			case 4:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU4WorkMod & 0x07;
				break;
			case 5:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU5WorkMod & 0x07;
				break;
			case 6:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU6WorkMod & 0x07;
				break;
			case 7:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU7WorkMod & 0x07;
				break;
			case 8:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU8WorkMod & 0x07;
				break;
			case 9:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU9WorkMod & 0x07;
				break;
			case 10:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU10WorkMod & 0x07;
				break;
			case 11:
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU11WorkMod & 0x07;
				break;
			default:
				// 报错
				break;
		}
	}
	else
	{
		Intf_Vlant_PFCC[CH1_PFCC1].CrcRightFlag = FALSE;
	}

	Intf_Vlant_PFCC[CH1_PFCC1].RollingCounter = pCanFrame->Data.RollingCounter & 0xFF;
	Intf_Vlant_PFCC[CH1_PFCC1].CRC = ((pCanFrame->Data.CRC_H & 0xFF) << 8) + (pCanFrame->Data.CRC_L & 0xFF);
}

void CanProtocol_PFCC1_PHSM_MCU_EXT1_Update(void *pframe)
{
	CanFrame_t *pCanFrame = (CanFrame_t *)pframe;

	pCanFrame->d16.d01 = (uint16)(0);
	pCanFrame->d16.d23 = (uint16)(0);
	pCanFrame->d16.d45 = (uint16)(0);
	pCanFrame->d16.d67 = (uint16)(0);
}

/* -------------------------------------------------------------------------- */

void CanProtocol_PFCC2_CtrlMsg_MCU_EXT1_Update(void *pframe)
{
	CANFD_EXT_RX1_OBJ *pCanFrame = (CANFD_EXT_RX1_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_EXT1[PFCC2_CtrlMsg_MCU_EXT1].frameId, sg_frameInfoList_EXT1[PFCC2_CtrlMsg_MCU_EXT1].dataLength, pframe))
	{
		Intf_Vlant_PFCC[CH1_PFCC2].CrcRightFlag = TRUE;

		Intf_Vlant_PFCC[CH1_PFCC2].PFCC_IsPrimaryChannel = pCanFrame->Data.PFCC_IsPrimaryChannel & 0x01;
		Intf_Vlant_PFCC[CH1_PFCC2].PFCC_HiVltgSW = pCanFrame->Data.PFCC_HiVltgSW & 0x03;
		Intf_Vlant_PFCC[CH1_PFCC2].PFCC_DisplayHVState = pCanFrame->Data.PFCC_DisplayHVState & 0x03;
		Intf_Vlant_PFCC[CH1_PFCC2].PFCC_CmdCommunicationConfirm = ((pCanFrame->Data.PFCC_CmdCommunicationConfirm_H & 0xFF) << 8) + (pCanFrame->Data.PFCC_CmdCommunicationConfirm_L & 0xFF);

		switch(CanVolantData.LocNum)
		{
			case 1:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU1WorkMod & 0x07;
				break;
			case 2:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU2WorkMod & 0x07;
				break;
			case 3:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU3WorkMod & 0x07;
				break;
			case 4:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU4WorkMod & 0x07;
				break;
			case 5:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU5WorkMod & 0x07;
				break;
			case 6:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU6WorkMod & 0x07;
				break;
			case 7:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU7WorkMod & 0x07;
				break;
			case 8:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU8WorkMod & 0x07;
				break;
			case 9:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU9WorkMod & 0x07;
				break;
			case 10:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU10WorkMod & 0x07;
				break;
			case 11:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU11WorkMod & 0x07;
				break;
			default:
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUSpdCtrl = 0;
				Intf_Vlant_PFCC[CH1_PFCC2].PFCC_ReqMCUWorkMod = 0;
				break;
			}
	}
	else
	{
		Intf_Vlant_PFCC[CH1_PFCC2].CrcRightFlag = FALSE;
	}

	Intf_Vlant_PFCC[CH1_PFCC2].RollingCounter = pCanFrame->Data.RollingCounter & 0xFF;
	Intf_Vlant_PFCC[CH1_PFCC2].CRC = ((pCanFrame->Data.CRC_H & 0xFF) << 8) + (pCanFrame->Data.CRC_L & 0xFF);
}

void CanProtocol_PFCC2_PHSM_MCU_EXT1_Update(void *pframe)
{
	CanFrame_t *pCanFrame = (CanFrame_t *)pframe;

	pCanFrame->d16.d01 = (uint16)(0);
	pCanFrame->d16.d23 = (uint16)(0);
	pCanFrame->d16.d45 = (uint16)(0);
	pCanFrame->d16.d67 = (uint16)(0);
}

/* -------------------------------------------------------------------------- */

void CanProtocol_PFCC3_CtrlMsg_MCU_EXT1_Update(void *pframe)
{
	CANFD_EXT_RX1_OBJ *pCanFrame = (CANFD_EXT_RX1_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_EXT1[PFCC3_CtrlMsg_MCU_EXT1].frameId, sg_frameInfoList_EXT1[PFCC3_CtrlMsg_MCU_EXT1].dataLength, pframe))
		{
			Intf_Vlant_PFCC[CH1_PFCC3].CrcRightFlag = TRUE;

			Intf_Vlant_PFCC[CH1_PFCC3].PFCC_IsPrimaryChannel = pCanFrame->Data.PFCC_IsPrimaryChannel & 0x01;
			Intf_Vlant_PFCC[CH1_PFCC3].PFCC_HiVltgSW = pCanFrame->Data.PFCC_HiVltgSW & 0x03;
			Intf_Vlant_PFCC[CH1_PFCC3].PFCC_DisplayHVState = pCanFrame->Data.PFCC_DisplayHVState & 0x03;
			Intf_Vlant_PFCC[CH1_PFCC3].PFCC_CmdCommunicationConfirm = ((pCanFrame->Data.PFCC_CmdCommunicationConfirm_H & 0xFF) << 8) + (pCanFrame->Data.PFCC_CmdCommunicationConfirm_L & 0xFF);

			switch(CanVolantData.LocNum)
			{
				case 1:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU1WorkMod & 0x07;
					break;
				case 2:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU2WorkMod & 0x07;
					break;
				case 3:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU3WorkMod & 0x07;
					break;
				case 4:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU4WorkMod & 0x07;
					break;
				case 5:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU5WorkMod & 0x07;
					break;
				case 6:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU6WorkMod & 0x07;
					break;
				case 7:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU7WorkMod & 0x07;
					break;
				case 8:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU8WorkMod & 0x07;
					break;
				case 9:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU9WorkMod & 0x07;
					break;
				case 10:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU10WorkMod & 0x07;
					break;
				case 11:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_L) & 0x1FFF), float, 4000, 1);
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU11WorkMod & 0x07;
					break;
				default:
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUSpdCtrl = 0;
					Intf_Vlant_PFCC[CH1_PFCC3].PFCC_ReqMCUWorkMod = 0;
					break;
				}
		}
		else
		{
			Intf_Vlant_PFCC[CH1_PFCC3].CrcRightFlag = FALSE;
		}

		Intf_Vlant_PFCC[CH1_PFCC3].RollingCounter = pCanFrame->Data.RollingCounter & 0xFF;
		Intf_Vlant_PFCC[CH1_PFCC3].CRC = ((pCanFrame->Data.CRC_H & 0xFF) << 8) + (pCanFrame->Data.CRC_L & 0xFF);
}

void CanProtocol_PFCC3_PHSM_MCU_EXT1_Update(void *pframe)
{
	CanFrame_t *pCanFrame = (CanFrame_t *)pframe;

	pCanFrame->d16.d01 = (uint16)(0);
	pCanFrame->d16.d23 = (uint16)(0);
	pCanFrame->d16.d45 = (uint16)(0);
	pCanFrame->d16.d67 = (uint16)(0);
}

/* -------------------------------------------------------------------------- */

void CanProtocol_MCU_EXT1_FbkMsg_PFCC_Update(void *pframe)
{
	CANFD_EXT_TX1_OBJ *pCanFrame = (CANFD_EXT_TX1_OBJ *)pframe;

	pCanFrame->Data.MCU_ControlModule				= (uint8)(((GbMSC_MstSlaveSts_flg && (!GbBSW_McuCh_flg))\
													|| ((!GbMSC_MstSlaveSts_flg) && GbBSW_McuCh_flg)) & 0x01);
	pCanFrame->Data.Rsvd_Byte0_Bit1					= 0;
	pCanFrame->Data.MCU_FaultLevelFbk				= (uint8)(GeMMS_SysErrLevel_enum & 0x07);
	pCanFrame->Data.MCU_WorkModFbk					= (uint8)(GeMMS_MOTStateSum_enum & 0x07);
	pCanFrame->Data.MCU_FbkCommunicationConfirm_H	= (uint8)((GcBSW_CmdConfirm_numb >> 8) & 0xFF);
	pCanFrame->Data.MCU_FbkCommunicationConfirm_L	= (uint8)(GcBSW_CmdConfirm_numb & 0xFF);
	pCanFrame->Data.MCU_SpdFbk_H					= (uint8)((CAN_DATA_PACK(GsSPH_MotSpd_rpm, uint16, 3000, 10) >> 8) & 0xFF);
	pCanFrame->Data.MCU_SpdFbk_L					= (uint8)(CAN_DATA_PACK(GsSPH_MotSpd_rpm, uint16, 3000, 10) & 0xFF);
	pCanFrame->Data.MCU_SpdFbkInvalid				= (uint8)(0 & 0x01);
	pCanFrame->Data.CANCmdMsgTimeout				= (uint8)(0 & 0x07);
	pCanFrame->Data.MCU_PowerFbkInvalid				= (uint8)(0 & 0x01);
	pCanFrame->Data.Rsvd_Byte4_Bit5_7				= 0;
	pCanFrame->Data.MCU_PowerFbk_H					= (uint8)((CAN_DATA_PACK(GsMMS_InvPwrSum_Kw, uint16, 255, 1) >> 1) & 0xFF);
	pCanFrame->Data.Rsvd_Byte6_Bit0_6				= 0;
	pCanFrame->Data.MCU_PowerFbk_L					= (uint8)(CAN_DATA_PACK(GsMMS_InvPwrSum_Kw, uint16, 255, 1) & 0x01);
	pCanFrame->Data.MCU_PowerPercentFbk				= 0;
	pCanFrame->Data.RollingCounter					= (uint8)(CanVolantData.CanVolantModuleData_1.EXT_RollingCounter_F & 0xFF);
	pCanFrame->Data.CRC_H							= 0;
	pCanFrame->Data.CRC_L							= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_EXT1[MCU_EXT1_FbkMsg_PFCC].frameId, sg_frameInfoList_EXT1[MCU_EXT1_FbkMsg_PFCC].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_1.EXT_RollingCounter_F++;
	/* ----------------------------------UNUSED---------------------------------- */
	pCanFrame->Data.Rsvd_Byte12						= 0;
	pCanFrame->Data.Rsvd_Byte13						= 0;
	pCanFrame->Data.Rsvd_Byte14						= 0;
	pCanFrame->Data.Rsvd_Byte15						= 0;
}

void CanProtocol_MCU_EXT1_NormalMsg_PFCC_Update(void *pframe)
{
	switch(CanVolantData.McuC)
	{
		case MCU_A:
		{
			MCUA_EXT1_NormalMsg_Pack(pframe);
			break;
		}
		case MCU_B:
		{
			MCUB_EXT1_NormalMsg_Pack(pframe);
			break;
		}
		default:
			CanVolantData.McuC = TRUE;
			break;
	}

	CanVolantData.CanVolantModuleData_1.MsgAB_Flag = !CanVolantData.CanVolantModuleData_1.MsgAB_Flag;
}

void CanProtocol_MCU_EXT1_PHSM_Update(void *pframe)
{
	CANFD_EXT_TX3_OBJ *pCanFrame = (CANFD_EXT_TX3_OBJ *)pframe;

//    pCanFrame->Data.NB_ERR_RX_H		= (uint8)((PMSM.CanData.CanMoudleData[0].RxErrNum >> 8) & 0xFF);
//    pCanFrame->Data.NB_ERR_RX_L		= (uint8)(PMSM.CanData.CanMoudleData[0].RxErrNum & 0xFF);
//    pCanFrame->Data.NB_ERR_TX_H		= (uint8)((PMSM.CanData.CanMoudleData[0].TxErrNum >> 8) & 0xFF);
//    pCanFrame->Data.NB_ERR_TX_L		= (uint8)(PMSM.CanData.CanMoudleData[0].TxErrNum & 0xFF);
//    pCanFrame->Data.NB_ERR_ACK_H	= (uint8)((PMSM.CanData.CanMoudleData[0].NackErrNum >> 8) & 0xFF);
//    pCanFrame->Data.NB_ERR_ACK_L	= (uint8)(PMSM.CanData.CanMoudleData[0].NackErrNum & 0xFF);
//    pCanFrame->Data.NB_BUS_OFF		= (uint8)(PMSM.CanData.CanMoudleData[0].BusOffErrNum & 0xFF);
//    pCanFrame->Data.REC_STATE		= (uint8)(PMSM.CanData.CanMoudleData[0].RecState & 0xF);
//    pCanFrame->Data.TEC_STATE		= (uint8)(PMSM.CanData.CanMoudleData[0].TecState & 0xF);
}

void CanProtocol_MCU_EXT1_ConfigMsg_Update(void *pframe)
{
	CANFD_EXT_TX4_OBJ *pCanFrame = (CANFD_EXT_TX4_OBJ *)pframe;

	pCanFrame->ALL[0] = 0;
	pCanFrame->ALL[1] = 0;
	pCanFrame->ALL[2] = 0;
	pCanFrame->ALL[3] = 0;
	pCanFrame->ALL[4] = 0;
	pCanFrame->ALL[5] = 0;
}

/* -------------------------------------------------------------------------- */

void CanProtocol_MCU_EXT1_DebugMsg_Rx0_Update(void *pframe)
{
	CANFD_EXT_DEBUG_RX0_OBJ *pCanFrame = (CANFD_EXT_DEBUG_RX0_OBJ *)pframe;

	CanVolantData.CanDebugData.FunctionRequest		= pCanFrame->Data.FunctionRequest & 0x07;
	CanVolantData.CanDebugData.SecurityKey			= pCanFrame->Data.SecurityKey & 0x1F;

	CanVolantData.CanDebugData.MCU_LocNum			= pCanFrame->Data.MCU_LocNum & 0x0F;
	CanVolantData.CanDebugData.MCU_AOrB				= pCanFrame->Data.MCU_AOrB & 0x01;

	CanVolantData.CanDebugData.MCUA_DebugMsgEnable	= pCanFrame->Data.MCUA_DebugMsgEnable & 0x01;
	CanVolantData.CanDebugData.MCUB_DebugMsgEnable	= pCanFrame->Data.MCUB_DebugMsgEnable & 0x01;

	CanVolantData.CanDebugData.SilenceAll			= pCanFrame->Data.SilenceAll & 0x01;

	CanVolantData.CanDebugData.InjectSlowFaultFlag	= pCanFrame->Data.InjectSlowFaultFlag & 0x01;
	CanVolantData.CanDebugData.InjectSlowFaultState	= pCanFrame->Data.InjectSlowFaultState & 0x01;
	CanVolantData.CanDebugData.InjectFastFaultFlag	= pCanFrame->Data.InjectFastFaultFlag & 0x01;
	CanVolantData.CanDebugData.InjectFastFaultState	= pCanFrame->Data.InjectFastFaultState & 0x01;

	CanVolantData.CanDebugData.IsrMsgMode			= pCanFrame->Data.IsrMsgMode & 0x01;
	CanVolantData.CanDebugData.IsrMsgFunc			= pCanFrame->Data.IsrMsgFunc & 0x03;

	CanVolantData.CanDebugData.NVM_Block_Num		= pCanFrame->Data.NVM_Block_Num & 0x0F;

	CanVolantData.CanDebugData.Kp					= pCanFrame->Data.Kp & 0xFFFF;
	CanVolantData.CanDebugData.Ki					= pCanFrame->Data.Ki & 0xFFFF;

	CanVolantData.CanDebugData.ElecZeroComp			= pCanFrame->Data.UPC_ElecZeroComp & 0x3FFF;
	CanVolantData.CanDebugData.SwapEncoderDir		= pCanFrame->Data.UPC_SwapEncoderDir & 0x01;
	CanVolantData.CanDebugData.SwapPhase			= pCanFrame->Data.UPC_SwapPhase & 0x01;
	CanVolantData.CanDebugData.SlpTheta				= pCanFrame->Data.UPC_SlpTheta & 0x3FFF;

	if((0 != pCanFrame->ALL[0]) || (0 != pCanFrame->ALL[1]))
	{
		pCanFrame->ALL[0] = 0;
		pCanFrame->ALL[1] = 0;
	}
}

void CanProtocol_MCU_EXT1_DebugMsg_Tx0_Update(void *pframe)
{
	CANFD_EXT_DEBUG_TX0_OBJ *pCanFrame = (CANFD_EXT_DEBUG_TX0_OBJ *)pframe;

	pCanFrame->Data.RDC_Speed		= (uint16)(CAN_DATA_PACK((GsSPH_MotSpd_rpm), uint16, 3000, 10) & 0xFFFF);
	pCanFrame->Data.SpeedFilter		= (uint16)(CAN_DATA_PACK((GsSPH_MotSpdFild3Fbk_rpm), uint16, 3000, 10) & 0xFFFF);

	pCanFrame->Data.CurBus			= (uint16)(CAN_DATA_PACK(GsSPL_CrntBus_A, uint16, 300, 100) & 0xFFFF);
	pCanFrame->Data.Vs				= (uint16)(CAN_DATA_PACK((GsCLC_Us_pu * 100), uint16, 0, 200) & 0xFFFF);

	pCanFrame->Data.Vd				= (uint16)(CAN_DATA_PACK((GsCLC_Ud_pu * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.Vq				= (uint16)(CAN_DATA_PACK((GsCLC_Uq_pu  * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.IsRef			= (uint16)(CAN_DATA_PACK((LsMTM_IsRefSum_pu  * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.IsFbk			= (uint16)(CAN_DATA_PACK((GsCPC_IsFbk_pu * (GsSPH_MotSpd_rpm * GsCPC_IqFbk_pu > 0 ? 100 : -100)), uint16, 150, 200) & 0xFFFF);

	pCanFrame->Data.IdRef			= (uint16)(CAN_DATA_PACK((GsMTM_IdRef_pu  * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.IdFbk			= (uint16)(CAN_DATA_PACK((GsCPC_IdFbk_pu  * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.IqRef			= (uint16)(CAN_DATA_PACK((GsMTM_IqRef_pu  * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.IqFbk			= (uint16)(CAN_DATA_PACK((GsCPC_IqFbk_pu  * 100), uint16, 150, 200) & 0xFFFF);

	pCanFrame->Data.FinalIsRef		= (uint16)(CAN_DATA_PACK((LsMTM_IsCurLimRef_pu * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.IntIsRef		= (uint16)(CAN_DATA_PACK((GsBSW_IsRefRd_pu * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.Speed_Out		= (uint16)(CAN_DATA_PACK((GsSLC_IsRef_pu * 100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.RampSpeed		= (uint16)(CAN_DATA_PACK((LsSLC_MotSpdRefRamp_rpm), uint16, 3000, 10) & 0xFFFF);

	pCanFrame->Data.UdComp		    = (uint16)(CAN_DATA_PACK((LsCLC_UdComp_pu * -100), uint16, 150, 200) & 0xFFFF);
	pCanFrame->Data.UqComp		    = (uint16)(CAN_DATA_PACK((LsCLC_UqComp_pu  * 100), uint16, 150, 200) & 0xFFFF);

	pCanFrame->Data.LocationNum		= (uint8)(GcBSW_LocnBit_numb & 0x0F);
	pCanFrame->Data.WorkModFbk		= (uint8)(GeMSM_MOTState_enum & 0x0F);
	pCanFrame->Data.IsMasterMcu		= (uint8)(GbMSC_MstSlaveSts_flg & 0x01);
	pCanFrame->Data.MotState		= (uint8)(GbMSM_MotSwtTubeStReq_flg & 0x07);

	pCanFrame->Data.ExtCanMoudle1	= (uint8)(CanVolantData.CanVolantModuleData_1.EXT_IsPrimaryModule & 0x01);
	pCanFrame->Data.ExtCanMoudle2	= (uint8)(CanVolantData.CanVolantModuleData_2.EXT_IsPrimaryModule & 0x01);
	pCanFrame->Data.IntCanMoudle1	= (uint8)(CanVolantData.CanVolantModuleData_1.INT_IsPrimaryModule & 0x01);
	pCanFrame->Data.IntCanMoudle2	= (uint8)(CanVolantData.CanVolantModuleData_2.INT_IsPrimaryModule & 0x01);

	pCanFrame->Data.FaultLevel		= (uint8)(GeEVL_ErrLevel_enum & 0x07);

	pCanFrame->Data.CPUTemp			= (uint8)(CAN_DATA_PACK((0), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MotTemp1		= (uint8)(CAN_DATA_PACK((GsSPL_MotTemp1_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MotTemp2		= (uint8)(CAN_DATA_PACK((GsSPL_MotTemp2_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.InvTempU1		= (uint8)(CAN_DATA_PACK((GsSPL_InvTempU1_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.InvTempV1		= (uint8)(CAN_DATA_PACK((GsSPL_InvTempU2_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.InvTempW1		= (uint8)(CAN_DATA_PACK((GsSPL_InvTempV1_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.InvTempU2		= (uint8)(CAN_DATA_PACK((GsSPL_InvTempV2_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.InvTempV2		= (uint8)(CAN_DATA_PACK((GsSPL_InvTempW1_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.InvTempW2		= (uint8)(CAN_DATA_PACK((GsSPL_InvTempW2_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.BearTemp1		= (uint8)(CAN_DATA_PACK((GsSPL_FrntBearTemp_C), uint16, 20, 1) & 0xFF);
	pCanFrame->Data.BearTemp2		= (uint8)(CAN_DATA_PACK((GsSPL_BackBearTemp_C), uint16, 20, 1) & 0xFF);

	pCanFrame->Data.Volt_Bus		= (uint16)(CAN_DATA_PACK((GsSPH_VltgBusFilter_V), uint16, 0, 50) & 0xFFFF);
	pCanFrame->Data.Volt_28			= (uint16)(CAN_DATA_PACK((GsSPL_Vltg28_V), uint16, 0, 1000) & 0xFFFF);
	pCanFrame->Data.Volt_05			= (uint16)(CAN_DATA_PACK((GsSPL_Vltg5_V), uint16, 0, 20) & 0xFF);

	pCanFrame->Data.RollingCounter	= (uint8)(GcBSW_RollCount_numb & 0xFF);

	pCanFrame->Data.AD2S1210_Fault		= (uint8)(AD2S1210_Data.FaultBit.ALL & 0xFF);
	pCanFrame->Data.U_FaultBit			= (uint8)(GbBSW_PwrModuleUFltFault_flg & 0x01);
	pCanFrame->Data.U_ReadyBit			= (uint8)(GbBSW_PwrModuleURdyFault_flg & 0x01);
	pCanFrame->Data.V_FaultBit			= (uint8)(GbBSW_PwrModuleVFltFault_flg & 0x01);
	pCanFrame->Data.V_ReadyBit			= (uint8)(GbBSW_PwrModuleVRdyFault_flg & 0x01);
	pCanFrame->Data.W_FaultBit			= (uint8)(GbBSW_PwrModuleWFltFault_flg & 0x01);
	pCanFrame->Data.W_ReadyBit			= (uint8)(GbBSW_PwrModuleWRdyFault_flg & 0x01);
	pCanFrame->Data.FaultPinLot			= (uint8)(AD2S1210_Data.FaultPinLot & 0x01);
	pCanFrame->Data.FaultPinDos			= (uint8)(AD2S1210_Data.FaultPinDos & 0x01);
	pCanFrame->Data.UnderVoltRecoverNum	= (uint8)(0 & 0xFF);
	pCanFrame->Data.ThetaFixTimes		= (uint8)(0 & 0xFF);
	pCanFrame->Data.DeltaTheta	 	    = (sint16)(0);
	pCanFrame->Data.DeltaThetaAvg   	= (sint16)(0);
}

void CanProtocol_MCU_EXT1_DebugMsg_Tx1_Update(void *pframe)
{
	CANFD_EXT_DEBUG_TX1_OBJ *pCanFrame = (CANFD_EXT_DEBUG_TX1_OBJ *)pframe;

	pCanFrame->Data.Debug_WarningBitFbk_7_0		= (uint8)((WltFaultNow.All[0]) & 0xFF);
	pCanFrame->Data.Debug_WarningBitFbk_15_8	= (uint8)((WltFaultNow.All[0] >> 8) & 0xFF);
	pCanFrame->Data.Debug_WarningBitFbk_23_16	= (uint8)((WltFaultNow.All[1]) & 0xFF);
	pCanFrame->Data.Debug_WarningBitFbk_31_24	= (uint8)((WltFaultNow.All[1] >> 8) & 0xFF);

	pCanFrame->Data.Debug_FaultBitFbk_7_0		= (uint8)((WltFaultNow.All[2]) & 0xFF);
	pCanFrame->Data.Debug_FaultBitFbk_15_8		= (uint8)((WltFaultNow.All[2] >> 8) & 0xFF);
	pCanFrame->Data.Debug_FaultBitFbk_23_16		= (uint8)((WltFaultNow.All[3]) & 0xFF);
	pCanFrame->Data.Debug_FaultBitFbk_31_24		= (uint8)((WltFaultNow.All[3] >> 8) & 0xFF);

	pCanFrame->Data.SoftwareVersion				= (uint16)(GcBSW_IsrTime_numb & 0xFFFF);
	pCanFrame->Data.ElecZeroComp				= (uint16)(CcSPH_RdcThetaZero_numb & 0x3FFF);
	pCanFrame->Data.SwapEncoderDir				= (uint16)(GbBSW_SwapPhase_flg & 0x01);
	pCanFrame->Data.SwapPhase					= (uint16)(GbBSW_SwapEncoderDir_flg & 0x01);

	pCanFrame->Data.BusPower					= (uint16)(CAN_DATA_PACK(0, uint16, 300, 100) & 0xFFFF);
	pCanFrame->Data.InvPower					= (uint16)(CAN_DATA_PACK(GsSPL_InvPwr_Kw, uint16, 300, 100) & 0xFFFF);
	pCanFrame->Data.MechPower					= (uint16)(CAN_DATA_PACK(0, uint16, 300, 100) & 0xFFFF);

	pCanFrame->Data.PwmPeriodUs					= (uint16)(CAN_DATA_PACK(1000000.0f / GcBSW_PwmFreq_Hz, uint16, 0, 10) & 0xFFFF);
	pCanFrame->Data.PFCC_Num					= (uint8)(CanVolantData.PFCC_PrimaryChannelNum & 0x0F);

	pCanFrame->Data.Cur_Kp_Now					= (uint16)(CsCLC_IdLoopKp_numb * 1000.0f);
	pCanFrame->Data.Cur_Ki_Now					= (uint16)(CsCLC_IdLoopKi_numb * 10000.0f);

	pCanFrame->Data.SlpTheta					= (uint16)(0 & 0x3FFF);
	pCanFrame->Data.SlpState					= (uint16)(GeSLP_SlpState_enum & 0x3);

	pCanFrame->Data.RDC_Theta					= (uint16)(GcBSW_RdcThetaAD_numb & 0x3FFF);

	pCanFrame->Data.ElecZeroState				= (uint16)(0 & 0x03);

	pCanFrame->Data.Spd_Kp_Now					= (uint16)(CsSLC_SpdLoopKp0_numb * 1000.0f);
	pCanFrame->Data.Spd_Ki_Now					= (uint16)(CsSLC_SpdLoopKi0_numb * 10000.0f);
}

void CanProtocol_MCU_EXT1_DebugMsg_TxF_Update(void *pframe)
{
	CANFD_EXT_DEBUG_TXF_OBJ *pCanFrame = (CANFD_EXT_DEBUG_TXF_OBJ *)pframe;

	uint16 MsgCnt = CAN_ISR_Get_CanLoopCnt();

	pCanFrame->Data.RDC_Speed				= CanIsrBuffer[MsgCnt].Data.RDC_Speed;
	pCanFrame->Data.ThetaRT					= CanIsrBuffer[MsgCnt].Data.ThetaRT;
	pCanFrame->Data.Vd						= CanIsrBuffer[MsgCnt].Data.Vd;
	pCanFrame->Data.Vq						= CanIsrBuffer[MsgCnt].Data.Vq;

	pCanFrame->Data.IdRef					= CanIsrBuffer[MsgCnt].Data.IdRef;
	pCanFrame->Data.IdFbk					= CanIsrBuffer[MsgCnt].Data.IdFbk;
	pCanFrame->Data.IqRef					= CanIsrBuffer[MsgCnt].Data.IqRef;
	pCanFrame->Data.IqFbk					= CanIsrBuffer[MsgCnt].Data.IqFbk;

	pCanFrame->Data.FinalIsRef				= CanIsrBuffer[MsgCnt].Data.FinalIsRef;
	pCanFrame->Data.IntIsRef				= CanIsrBuffer[MsgCnt].Data.IntIsRef;
	pCanFrame->Data.MsgCount				= CanIsrBuffer[MsgCnt].Data.MsgCount;
	pCanFrame->Data.PwmFreqKHz				= CanIsrBuffer[MsgCnt].Data.PwmFreqKHz;
	pCanFrame->Data.MsgTrigger				= CanIsrBuffer[MsgCnt].Data.MsgTrigger;
	pCanFrame->Data.IsMasterMcu				= CanIsrBuffer[MsgCnt].Data.IsMasterMcu;
	pCanFrame->Data.IsUseIntIsRef			= CanIsrBuffer[MsgCnt].Data.IsUseIntIsRef;
	pCanFrame->Data.ThetaFixFlag			= CanIsrBuffer[MsgCnt].Data.ThetaFixFlag;
	pCanFrame->Data.WorkModFbk				= CanIsrBuffer[MsgCnt].Data.WorkModFbk;

	pCanFrame->Data.DeltaTheta				= CanIsrBuffer[MsgCnt].Data.DeltaTheta;
	pCanFrame->Data.DeltaThetaAvg			= CanIsrBuffer[MsgCnt].Data.DeltaThetaAvg;
	pCanFrame->Data.Debug_FaultBitFbk_7_0	= CanIsrBuffer[MsgCnt].Data.Debug_FaultBitFbk_7_0;
	pCanFrame->Data.Debug_FaultBitFbk_15_8	= CanIsrBuffer[MsgCnt].Data.Debug_FaultBitFbk_15_8;
	pCanFrame->Data.Debug_FaultBitFbk_23_16	= CanIsrBuffer[MsgCnt].Data.Debug_FaultBitFbk_23_16;
	pCanFrame->Data.Debug_FaultBitFbk_31_24	= CanIsrBuffer[MsgCnt].Data.Debug_FaultBitFbk_31_24;

	pCanFrame->Data.CurU					= CanIsrBuffer[MsgCnt].Data.CurU;
	pCanFrame->Data.CurV					= CanIsrBuffer[MsgCnt].Data.CurV;
	pCanFrame->Data.CurW					= CanIsrBuffer[MsgCnt].Data.CurW;
	pCanFrame->Data.RdcBit					= CanIsrBuffer[MsgCnt].Data.RdcBit;
	pCanFrame->Data.Volt_5V					= CanIsrBuffer[MsgCnt].Data.Volt_5V;

	pCanFrame->Data.Volt_Bus				= CanIsrBuffer[MsgCnt].Data.Volt_Bus;
	pCanFrame->Data.Volt_28V				= CanIsrBuffer[MsgCnt].Data.Volt_28V;
	pCanFrame->Data.Rsvd_Byte44				= CanIsrBuffer[MsgCnt].Data.Rsvd_Byte44;
	pCanFrame->Data.Rsvd_Byte45				= CanIsrBuffer[MsgCnt].Data.Rsvd_Byte45;
	pCanFrame->Data.Rsvd_Byte46				= CanIsrBuffer[MsgCnt].Data.Rsvd_Byte46;
	pCanFrame->Data.Rsvd_Byte47				= CanIsrBuffer[MsgCnt].Data.Rsvd_Byte47;
}

/* -------------------------------------------------------------------------- */

void CanProtocol_MCU_EXT1_FeeMsg_Tx_Update(void *pframe)
{
//	NVM_Debug_Type *pCanFrame = (NVM_Debug_Type *)pframe;
//
//	uint8* RamAddress = NVM_Block[CanVolantData.CanDebugData.NVM_Block_Num].RAMAddress;
//
//	pCanFrame->ALL[0] = 0;
//	pCanFrame->ALL[1] = 0;
//	pCanFrame->ALL[2] = 0;
//	pCanFrame->ALL[3] = 0;
//
//	uint8* Addr = RamAddress + CanVolantData.NVM_SendNum * 32;
//
//	for(uint8 i = 0; i < 4; i++)
//	{
//		for(uint8 j = 0; j < 8; j++)
//		{
//			pCanFrame->ALL[i] |= (uint64)Addr[i * 8 + j] << (j * 8);
//		}
//	}
//
//	CanVolantData.NVM_SendNum++;
//
//	if(CanVolantData.NVM_SendNum > 63)
//	{
//		CanVolantData.NVM_SendNum = 0;
//		SRVL_CanSM_FEE_Close();
//	}
}

/* -------------------------------------------------------------------------- */

uint32 CanProtocol_Volant_EXT1_Event_Trigger(void)
{
	return 0;
}

void CanProtocol_Volant_EXT1_Event_Update(void)
{

}

/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数定义*/

static void MCUA_EXT1_NormalMsg_Pack(void *pframe)
{
	CANFD_EXT_TX2_OBJ *pCanFrame = (CANFD_EXT_TX2_OBJ *)pframe;

	switch(!CanVolantData.CanVolantModuleData_1.MsgAB_Flag)
	{
		case MCU_A:
		{
			pCanFrame->Data.MCU_InformationValid	= (uint8)(CanVolantData.CanVolantModuleData_1.MsgAB_Flag & 0x1);
			pCanFrame->Data.MCU_FaultLevelFbk		= (uint8)(GeEVL_ErrLevel_enum & 0x7);
			pCanFrame->Data.MCU_WarningBitFbk_31_24	= (uint8)((WltFaultNow.All[1] >> 8) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_23_16	= (uint8)((WltFaultNow.All[1]) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_15_8	= (uint8)((WltFaultNow.All[0] >> 8) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_7_0	= (uint8)((WltFaultNow.All[0]) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_31_24	= (uint8)((WltFaultNow.All[3] >> 8) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_23_16	= (uint8)((WltFaultNow.All[3]) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_15_8	= (uint8)((WltFaultNow.All[2] >> 8) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_7_0		= (uint8)((WltFaultNow.All[2]) & 0xFF);

			break;
		}
		case MCU_B:
		{
			pCanFrame->Data.MCU_InformationValid	= (uint8)(CanVolantData.CanVolantModuleData_1.MsgAB_Flag & 0x1);
			pCanFrame->Data.MCU_FaultLevelFbk		= (uint8)(GeBSW_ErrLevelRd_enum & 0x7);
			pCanFrame->Data.MCU_WarningBitFbk_31_24	= (uint8)((GcBSW_WarningBitFbk_flg >> 24) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_23_16	= (uint8)((GcBSW_WarningBitFbk_flg >> 16) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_15_8	= (uint8)((GcBSW_WarningBitFbk_flg >> 8) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_7_0	= (uint8)(GcBSW_WarningBitFbk_flg & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_31_24	= (uint8)((GcBSW_FaultBitFbk_flg >> 24) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_23_16	= (uint8)((GcBSW_FaultBitFbk_flg >> 16) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_15_8	= (uint8)((GcBSW_FaultBitFbk_flg >> 8) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_7_0		= (uint8)(GcBSW_FaultBitFbk_flg & 0xFF);

			break;
		}
		default:
			CanVolantData.CanVolantModuleData_1.MsgAB_Flag = FALSE;
			break;
	}

	pCanFrame->Data.MCU_PositionFbk				= (uint8)(GcBSW_LocnBit_numb & 0xF);

	pCanFrame->Data.MCUA_Udc_H					= (uint8)((CAN_DATA_PACK((GsSPH_VltgBusFilter_V), uint16, 0, 50) >> 8) & 0xFF);
	pCanFrame->Data.MCUA_Udc_L					= (uint8)(CAN_DATA_PACK((GsSPH_VltgBusFilter_V), uint16, 0, 50) & 0xFF);
	pCanFrame->Data.MCUB_Udc_H					= (uint8)((CAN_DATA_PACK(GsBSW_VltgBusFilterRd_V, uint16, 0, 50) >> 8) & 0xFF);
	pCanFrame->Data.MCUB_Udc_L					= (uint8)(CAN_DATA_PACK(GsBSW_VltgBusFilterRd_V, uint16, 0, 50) & 0xFF);

	pCanFrame->Data.MCU_FrontBearTemp			= (uint8)(CAN_DATA_PACK(GsMMS_FrntBearTempSum_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MCU_BackBearTemp			= (uint8)(CAN_DATA_PACK(GsMMS_BackBearTempSum_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MCU_SicTempFbk				= (uint8)(CAN_DATA_PACK(GsMMS_InvTempSum_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MCU_MotorTempFbk			= (uint8)(CAN_DATA_PACK(GsMMS_MotTempSum_C, uint16, 20, 1) & 0xFF);

//	pCanFrame->Data.MCUA_PhaseCurU				= (uint8)(CAN_DATA_PACK((PMSM.Var.CurU * PMSM.Var.CurBase), uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUA_PhaseCurV				= (uint8)(CAN_DATA_PACK((PMSM.Var.CurV * PMSM.Var.CurBase), uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUA_PhaseCurW				= (uint8)(CAN_DATA_PACK((PMSM.Var.CurW * PMSM.Var.CurBase), uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUB_PhaseCurU				= (uint8)(CAN_DATA_PACK(MS_Data.MS_StateMsg.PhaseCurU_Fbk, uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUB_PhaseCurV				= (uint8)(CAN_DATA_PACK(MS_Data.MS_StateMsg.PhaseCurV_Fbk, uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUB_PhaseCurW				= (uint8)(CAN_DATA_PACK(MS_Data.MS_StateMsg.PhaseCurW_Fbk, uint16, 0, 1) & 0xFF);
	pCanFrame->Data.MCUA_Volt28V_H              = (uint8)((CAN_DATA_PACK(GsSPL_Vltg28_V, uint16, 0, 10) >> 1) & 0xFF);
	pCanFrame->Data.MCUB_Volt28V_H              = (uint8)((CAN_DATA_PACK(GsBSW_Vltg28Rd_V, uint16, 0, 10) >> 2 ) & 0x7F);
	pCanFrame->Data.MCUA_Volt28V_L              = (uint8)(CAN_DATA_PACK(GsSPL_Vltg28_V, uint16, 0, 10) & 0x01);
	pCanFrame->Data.Reserve3                    = 0;
	pCanFrame->Data.MCUB_Volt28V_L              = (uint8)(CAN_DATA_PACK(GsBSW_Vltg28Rd_V, uint16, 0, 10) & 0x03);


	pCanFrame->Data.MCUA_UdcInvalid				= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_UdcInvalid				= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_FrontBearTempInvalid	= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_BackBearTempInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_SicTempFbkInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_MotorTempFbkInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUA_PhaseCurUInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUA_PhaseCurVInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUA_PhaseCurWInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_PhaseCurUInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_PhaseCurVInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_PhaseCurWInvalid		= (uint8)(0 & 0x01);

	pCanFrame->Data.RollingCounter				= (uint8)(CanVolantData.CanVolantModuleData_1.EXT_RollingCounter_N & 0xFF);
	pCanFrame->Data.CRC_H						= 0;
	pCanFrame->Data.CRC_L						= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_EXT1[MCU_EXT1_NormalMsg_PFCC].frameId, sg_frameInfoList_EXT1[MCU_EXT1_NormalMsg_PFCC].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_1.EXT_RollingCounter_N++;
}

static void MCUB_EXT1_NormalMsg_Pack(void *pframe)
{
	CANFD_EXT_TX2_OBJ *pCanFrame = (CANFD_EXT_TX2_OBJ *)pframe;

	switch(!CanVolantData.CanVolantModuleData_1.MsgAB_Flag)
	{
		case MCU_B:
		{
			pCanFrame->Data.MCU_InformationValid	= (uint8)(CanVolantData.CanVolantModuleData_1.MsgAB_Flag & 0x1);
			pCanFrame->Data.MCU_FaultLevelFbk		= (uint8)(GeEVL_ErrLevel_enum & 0x7);
			pCanFrame->Data.MCU_WarningBitFbk_31_24	= (uint8)((WltFaultNow.All[1] >> 8) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_23_16	= (uint8)((WltFaultNow.All[1]) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_15_8	= (uint8)((WltFaultNow.All[0] >> 8) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_7_0	= (uint8)((WltFaultNow.All[0]) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_31_24	= (uint8)((WltFaultNow.All[3] >> 8) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_23_16	= (uint8)((WltFaultNow.All[3]) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_15_8	= (uint8)((WltFaultNow.All[2] >> 8) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_7_0		= (uint8)((WltFaultNow.All[2]) & 0xFF);

			break;
		}
		case MCU_A:
		{
			pCanFrame->Data.MCU_InformationValid	= (uint8)(CanVolantData.CanVolantModuleData_1.MsgAB_Flag & 0x1);
			pCanFrame->Data.MCU_FaultLevelFbk		= (uint8)(GeBSW_ErrLevelRd_enum & 0x7);
			pCanFrame->Data.MCU_WarningBitFbk_31_24	= (uint8)((GcBSW_WarningBitFbk_flg >> 24) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_23_16	= (uint8)((GcBSW_WarningBitFbk_flg >> 16) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_15_8	= (uint8)((GcBSW_WarningBitFbk_flg >> 8) & 0xFF);
			pCanFrame->Data.MCU_WarningBitFbk_7_0	= (uint8)(GcBSW_WarningBitFbk_flg & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_31_24	= (uint8)((GcBSW_FaultBitFbk_flg >> 24) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_23_16	= (uint8)((GcBSW_FaultBitFbk_flg >> 16) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_15_8	= (uint8)((GcBSW_FaultBitFbk_flg >> 8) & 0xFF);
			pCanFrame->Data.MCU_FaultBitFbk_7_0		= (uint8)(GcBSW_FaultBitFbk_flg & 0xFF);

			break;
		}
		default:
			CanVolantData.CanVolantModuleData_1.MsgAB_Flag = FALSE;
			break;
	}

	pCanFrame->Data.MCU_PositionFbk				= (uint8)(CanVolantData.LocNum & 0xF);

	pCanFrame->Data.MCUA_Udc_H					= (uint8)((CAN_DATA_PACK(GsBSW_VltgBusFilterRd_V, uint16, 0, 50) >> 8) & 0xFF);
	pCanFrame->Data.MCUA_Udc_L					= (uint8)(CAN_DATA_PACK(GsBSW_VltgBusFilterRd_V, uint16, 0, 50) & 0xFF);
	pCanFrame->Data.MCUB_Udc_H					= (uint8)((CAN_DATA_PACK(GsSPH_VltgBusFilter_V, uint16, 0, 50) >> 8) & 0xFF);
	pCanFrame->Data.MCUB_Udc_L					= (uint8)(CAN_DATA_PACK(GsSPH_VltgBusFilter_V, uint16, 0, 50) & 0xFF);

	pCanFrame->Data.MCU_FrontBearTemp			= (uint8)(CAN_DATA_PACK(GsMMS_FrntBearTempSum_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MCU_BackBearTemp			= (uint8)(CAN_DATA_PACK(GsMMS_BackBearTempSum_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MCU_SicTempFbk				= (uint8)(CAN_DATA_PACK(GsMMS_InvTempSum_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MCU_MotorTempFbk			= (uint8)(CAN_DATA_PACK(GsMMS_MotTempSum_C, uint16, 20, 1) & 0xFF);

//	pCanFrame->Data.MCUA_PhaseCurU				= (uint8)(CAN_DATA_PACK(MS_Data.MS_StateMsg.PhaseCurU_Fbk, uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUA_PhaseCurV				= (uint8)(CAN_DATA_PACK(MS_Data.MS_StateMsg.PhaseCurV_Fbk, uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUA_PhaseCurW				= (uint8)(CAN_DATA_PACK(MS_Data.MS_StateMsg.PhaseCurW_Fbk, uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUB_PhaseCurU				= (uint8)(CAN_DATA_PACK((PMSM.Var.CurU * PMSM.Var.CurBase), uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUB_PhaseCurV				= (uint8)(CAN_DATA_PACK((PMSM.Var.CurV * PMSM.Var.CurBase), uint16, 0, 1) & 0xFF);
//	pCanFrame->Data.MCUB_PhaseCurW				= (uint8)(CAN_DATA_PACK((PMSM.Var.CurW * PMSM.Var.CurBase), uint16, 0, 1) & 0xFF);

	pCanFrame->Data.MCUA_Volt28V_H              = (uint8)((CAN_DATA_PACK(GsBSW_Vltg28Rd_V, uint16, 0, 10) >> 1) & 0xFF);
	pCanFrame->Data.MCUB_Volt28V_H              = (uint8)((CAN_DATA_PACK(GsSPL_Vltg28_V, uint16, 0, 10) >> 2) & 0x7F);
	pCanFrame->Data.MCUA_Volt28V_L              = (uint8)(CAN_DATA_PACK(GsBSW_Vltg28Rd_V, uint16, 0, 10) & 0x01);
	pCanFrame->Data.Reserve3                    = 0;
	pCanFrame->Data.MCUB_Volt28V_L              = (uint8)(CAN_DATA_PACK(GsSPL_Vltg28_V, uint16, 0, 10) & 0x03);

	pCanFrame->Data.MCUA_UdcInvalid				= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_UdcInvalid				= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_FrontBearTempInvalid	= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_BackBearTempInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_SicTempFbkInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCU_MotorTempFbkInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUA_PhaseCurUInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUA_PhaseCurVInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUA_PhaseCurWInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_PhaseCurUInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_PhaseCurVInvalid		= (uint8)(0 & 0x01);
	pCanFrame->Data.MCUB_PhaseCurWInvalid		= (uint8)(0 & 0x01);

	pCanFrame->Data.RollingCounter				= (uint8)(CanVolantData.CanVolantModuleData_1.EXT_RollingCounter_N & 0xFF);
	pCanFrame->Data.CRC_H						= 0;
	pCanFrame->Data.CRC_L						= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_EXT1[MCU_EXT1_NormalMsg_PFCC].frameId, sg_frameInfoList_EXT1[MCU_EXT1_NormalMsg_PFCC].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_1.EXT_RollingCounter_N++;
}

void CanProtocol_MCU_EXT1_Msg_Send(void)
{
//	FlexCAN_Ip_Send(INTCAN_2, MCUA_INTCAN2_TX_CTRLMSG_MB, &intcan2_tx_info[0], MCUA_INTCAN2_TX_CTRLMSG_ID, &IntCan2_CTRL);
//	FlexCAN_Ip_Send(INTCAN_2, MCUA_INTCAN2_TX_STATEMSG_MB, &intcan2_tx_info[1], MCUA_INTCAN2_TX_STATEMSG_ID, &IntCan2_STATE);
}



/************************ (C) COPYRIGHT SANTROLL *****END OF FILE****/
