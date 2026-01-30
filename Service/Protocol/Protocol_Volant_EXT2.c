/**
 * @file Protocol_Volant_CAN1_EXT.c
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
#include <Protocol_Volant_EXT2.h>
#include "stdlib.h"
#include "Hal_IO.h"
//#include "math.h"
//#include "Pmsm_Param.h"
#include "CanSM.h"
/* Private define ------------------------------------------------------------*/
/*此处添加仅本文件使用的宏定义常量*/

/* Private macro -------------------------------------------------------------*/
/*此处添加仅本文件使用的宏定义函数*/
#define TX_PHYBase_ID 			(0x700)    /*can tx  ID*/
#define RX_FUNBase_ID		  	(0x7DF)	   /*can rx fun ID*/
#define	RX_PHYBase_ID 			(0x620u)   /*can rx phy ID*/
/* Private typedef -----------------------------------------------------------*/
/*此处添加仅本文件使用的结构体声明*/

/* Private variables ---------------------------------------------------------*/
/*此处添加仅本文件使用的全局变量*/
void (*UDS_CanCallBackRx_Ptr)(uint32 CanMessage_ID, uint32_t CanMessage_Len, uint8_t *CanMessage_Data);
extern Flexcan_Ip_MsgBuffType ExtCan2_Frame[CCSP_FRAME_NUM_EXT2];


uint8 Uds_Mode = 0;
uint8 Jump_To_Load = 0;

static void Uds_Manual_Process(void *pframe)
{

	(void) pframe;

	UDS_CanCallBackRx_Ptr(ExtCan2_Frame[UDS_RX_MB].msgId,
				ExtCan2_Frame[UDS_RX_MB].dataLen,ExtCan2_Frame[UDS_RX_MB].data);

#if 0
	switch(ExtCan2_Frame[UDS_RX_MB].data[1])
	{
	  case 0x10:
		if(0x03 == ExtCan2_Frame[UDS_RX_MB].data[2])
		{
			Uds_Mode = TRUE;
			if(ExtCan2_Frame[UDS_RX_MB].data[3] == SRVL_Get_LocNum() && ExtCan2_Frame[UDS_RX_MB].data[4] == (SRVL_Get_McuC() ? 0xA : 0xB))
			{
				Uds_TX_Response.msgId = 0x7F0;
				Uds_TX_Response.dataLen = 8;
				Uds_TX_Response.data[0] = 0x02;
				Uds_TX_Response.data[1] = 0x50;
				Uds_TX_Response.data[2] = 0x03;
				Uds_TX_Response.data[4] = 0;
				Uds_TX_Response.data[5] = 0;
				Uds_TX_Response.data[6] = 0;
				Uds_TX_Response.data[7] = 0;

				Jump_To_Load = TRUE;
			}
			else
			{
				SRVL_CanSM_EXT_SilentMode();
			}
		}
	  break;

	  case 0x11://reset mcu
	 		if(0x01 == ExtCan2_Frame[UDS_RX_MB].data[2])
	 		{
	 			HAL_WATCHDOG_SystemRest();
	 		}
	 	  break;
	  default:break;
	}
#endif

}

//void CCP_Process(void *pframe)
//{
//	CCP_DATA *pCanFrame = (CCP_DATA *)pframe;
//
//	CanVolantData.CcpData.CMD   =  pCanFrame->Data.CMD;
//	CanVolantData.CcpData.CTR   =  pCanFrame->Data.CTR;
//	CanVolantData.CcpData.DATA0 =  pCanFrame->Data.DATA0;
//	CanVolantData.CcpData.DATA1 =  pCanFrame->Data.DATA1;
//	CanVolantData.CcpData.DATA2 =  pCanFrame->Data.DATA2;
//	CanVolantData.CcpData.DATA3 =  pCanFrame->Data.DATA3;
//	CanVolantData.CcpData.DATA4 =  pCanFrame->Data.DATA4;
//	CanVolantData.CcpData.DATA5 =  pCanFrame->Data.DATA5;
//}
//
//void CCP_REPORT(void *pframe)
//{
//	CCP_REPORT_DATA *pCanFrame = (CCP_REPORT_DATA *)pframe;
//
//	pCanFrame->Data.ADREE0         = (uint8)((GcBSW_CcpRepoAddr_numb >> 24) & 0xFF);
//	pCanFrame->Data.ADREE1         = (uint8)((GcBSW_CcpRepoAddr_numb >> 16) & 0xFF);
//	pCanFrame->Data.ADREE2         = (uint8)((GcBSW_CcpRepoAddr_numb >> 8) & 0xFF);
//	pCanFrame->Data.ADREE3         = (uint8)(GcBSW_CcpRepoAddr_numb & 0xFF);
//	pCanFrame->Data.VALUE0         = (uint8)((GcBSW_CcpRepoValue_numb >> 24) & 0xFF);
//	pCanFrame->Data.VALUE1         = (uint8)((GcBSW_CcpRepoValue_numb >> 16) & 0xFF);
//	pCanFrame->Data.VALUE2         = (uint8)((GcBSW_CcpRepoValue_numb >> 8) & 0xFF);
//	pCanFrame->Data.VALUE3         = (uint8)(GcBSW_CcpRepoValue_numb & 0xFF);
//}



 CanStdProtocol_FrameInfo_t sg_frameInfoList_EXT2[CCSP_FRAME_NUM_EXT2] =
{
    {.SN = 0, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 10, \
    .enableFlag = TRUE, .frameId = 0x08520204, .pfDataUpdateFunc = CanProtocol_PFCC1_CtrlMsg_MCU_EXT2_Update, .pfTriggerFunc = NULL},

    {.SN = 1, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 0, .sendType = 0, .interval = 1000, \
    .enableFlag = TRUE, .frameId = 0x1BEEFA04, .pfDataUpdateFunc = CanProtocol_PFCC1_PHSM_MCU_EXT2_Update, .pfTriggerFunc = NULL},

    {.SN = 2, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 10, \
    .enableFlag = TRUE, .frameId = 0x08520205, .pfDataUpdateFunc = CanProtocol_PFCC2_CtrlMsg_MCU_EXT2_Update, .pfTriggerFunc = NULL},

    {.SN = 3, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 0, .sendType = 0, .interval = 1000, \
    .enableFlag = TRUE, .frameId = 0x1BEEFA05, .pfDataUpdateFunc = CanProtocol_PFCC2_PHSM_MCU_EXT2_Update, .pfTriggerFunc = NULL},

    {.SN = 4, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 10, \
    .enableFlag = TRUE, .frameId = 0x08520206, .pfDataUpdateFunc = CanProtocol_PFCC3_CtrlMsg_MCU_EXT2_Update, .pfTriggerFunc = NULL},

    {.SN = 5, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 0, .sendType = 0, .interval = 1000, \
    .enableFlag = TRUE, .frameId = 0x1BEEFA06, .pfDataUpdateFunc = CanProtocol_PFCC3_PHSM_MCU_EXT2_Update, .pfTriggerFunc = NULL},

    {.SN = 6, .frameFormat = 1, .frameMode = 2, .dataLength = 12, .direction = 1, .sendType = 0, .interval = 10, .offset = 1, \
    .enableFlag = FALSE, .frameId = 0x08522000, .pfDataUpdateFunc = CanProtocol_MCU_EXT2_FbkMsg_PFCC_Update, .pfTriggerFunc = NULL},

    {.SN = 7, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 1, .sendType = 0, .interval = 100, .offset = 2, \
    .enableFlag = FALSE, .frameId = 0x08522200, .pfDataUpdateFunc = CanProtocol_MCU_EXT2_NormalMsg_PFCC_Update, .pfTriggerFunc = NULL},

    {.SN = 8, .frameFormat = 1, .frameMode = 2, .dataLength = 8, .direction = 1, .sendType = 0, .interval = 1000, .offset = 3, \
    .enableFlag = FALSE, .frameId = 0x1BEEFA00, .pfDataUpdateFunc = CanProtocol_MCU_EXT2_PHSM_Update, .pfTriggerFunc = NULL},

    {.SN = 9, .frameFormat = 1, .frameMode = 2, .dataLength = 48, .direction = 1, .sendType = 0, .interval = 1000, .offset = 4, \
    .enableFlag = FALSE, .frameId = 0x1854CC00, .pfDataUpdateFunc = CanProtocol_MCU_EXT2_ConfigMsg_Update, .pfTriggerFunc = NULL},
/*********************************************************UDS**********************************************************************/
    {.SN = 10, .frameFormat = 0, .frameMode = 2, .dataLength = 64, .direction = 0, .sendType = 0, .interval = 0, \
     .enableFlag = TRUE, .frameId = RX_PHYBase_ID, .pfDataUpdateFunc = Uds_Manual_Process, .pfTriggerFunc = NULL},

	{.SN = 11, .frameFormat = 0, .frameMode = 2, .dataLength = 64, .direction = 1, .sendType = 1, .interval = 0,.offset = 1,\
	 .enableFlag = TRUE, .frameId = TX_PHYBase_ID, .pfDataUpdateFunc = NULL_PTR, .pfTriggerFunc = NULL},

	{.SN = 12, .frameFormat = 0, .frameMode = 2, .dataLength = 64, .direction = 1, .sendType = 0, .interval = 0, .offset = 0,\
	 .enableFlag = TRUE, .frameId =RX_FUNBase_ID , .pfDataUpdateFunc = NULL_PTR, .pfTriggerFunc = NULL}
/**********************************************************************************************************************************/

};

static uint32 sg_eventList_EXT2[CCSP_EVENTFRAME_NUM_EXT2] =
{
    0,
};

/* Exported variables --------------------------------------------------------*/
/*此处添加本文件向外暴露的变量*/

CanStdProtocol_t g_VolantExt2Protocol =
{
    .name = CCSP_NAME_EXT2,
    .baudrate = CCSP_BAUDRATE_EXT2,
    .fastBaudrate = CCSP_FASTBAUDRATE_EXT2,
    .deviceType = CCSP_DEVICETYPE_EXT2,
    .frameNum = CCSP_FRAME_NUM_EXT2,
    .pframeInfoList = sg_frameInfoList_EXT2,
    .pEventList = sg_eventList_EXT2,
    .pfEventUpdate = CanProtocol_Volant_EXT2_Event_Update
};

/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数声明*/

static void MCUA_EXT2_NormalMsg_Pack(void *pframe);

static void MCUB_EXT2_NormalMsg_Pack(void *pframe);

/* Exported functions --------------------------------------------------------*/
/*此处添加本文件向外暴露的函数定义*/

void CanProtocol_PFCC1_CtrlMsg_MCU_EXT2_Update(void *pframe)
{
	CANFD_EXT_RX1_OBJ *pCanFrame = (CANFD_EXT_RX1_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_EXT2[PFCC1_CtrlMsg_MCU_EXT2].frameId, sg_frameInfoList_EXT2[PFCC1_CtrlMsg_MCU_EXT2].dataLength, pframe))
	{
		Intf_Vlant_PFCC[CH2_PFCC1].CrcRightFlag = TRUE;

		Intf_Vlant_PFCC[CH2_PFCC1].PFCC_IsPrimaryChannel = pCanFrame->Data.PFCC_IsPrimaryChannel & 0x01;
		Intf_Vlant_PFCC[CH2_PFCC1].PFCC_HiVltgSW = pCanFrame->Data.PFCC_HiVltgSW & 0x03;
		Intf_Vlant_PFCC[CH2_PFCC1].PFCC_DisplayHVState = pCanFrame->Data.PFCC_DisplayHVState & 0x03;
		Intf_Vlant_PFCC[CH2_PFCC1].PFCC_CmdCommunicationConfirm = ((pCanFrame->Data.PFCC_CmdCommunicationConfirm_H & 0xFF) << 8) + (pCanFrame->Data.PFCC_CmdCommunicationConfirm_L & 0xFF);

		switch(CanVolantData.LocNum)
		{
			case 1:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU1WorkMod & 0x07;
				break;
			case 2:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU2WorkMod & 0x07;
				break;
			case 3:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU3WorkMod & 0x07;
				break;
			case 4:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU4WorkMod & 0x07;
				break;
			case 5:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU5WorkMod & 0x07;
				break;
			case 6:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU6WorkMod & 0x07;
				break;
			case 7:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU7WorkMod & 0x07;
				break;
			case 8:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU8WorkMod & 0x07;
				break;
			case 9:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU9WorkMod & 0x07;
				break;
			case 10:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU10WorkMod & 0x07;
				break;
			case 11:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU11WorkMod & 0x07;
				break;
			default:
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUSpdCtrl = 0;
				Intf_Vlant_PFCC[CH2_PFCC1].PFCC_ReqMCUWorkMod = 0;
				break;
			}
	}
	else
	{
		Intf_Vlant_PFCC[CH2_PFCC1].CrcRightFlag = FALSE;
	}

	Intf_Vlant_PFCC[CH2_PFCC1].RollingCounter = pCanFrame->Data.RollingCounter & 0xFF;
	Intf_Vlant_PFCC[CH2_PFCC1].CRC = ((pCanFrame->Data.CRC_H & 0xFF) << 8) + (pCanFrame->Data.CRC_L & 0xFF);
}

void CanProtocol_PFCC1_PHSM_MCU_EXT2_Update(void *pframe)
{
	CanFrame_t *pCanFrame = (CanFrame_t *)pframe;

	pCanFrame->d16.d01 = (uint16)(0);
	pCanFrame->d16.d23 = (uint16)(0);
	pCanFrame->d16.d45 = (uint16)(0);
	pCanFrame->d16.d67 = (uint16)(0);
}

/* -------------------------------------------------------------------------- */

void CanProtocol_PFCC2_CtrlMsg_MCU_EXT2_Update(void *pframe)
{
	CANFD_EXT_RX1_OBJ *pCanFrame = (CANFD_EXT_RX1_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_EXT2[PFCC2_CtrlMsg_MCU_EXT2].frameId, sg_frameInfoList_EXT2[PFCC2_CtrlMsg_MCU_EXT2].dataLength, pframe))
	{
		Intf_Vlant_PFCC[CH2_PFCC2].CrcRightFlag = TRUE;

		Intf_Vlant_PFCC[CH2_PFCC2].PFCC_IsPrimaryChannel = pCanFrame->Data.PFCC_IsPrimaryChannel & 0x01;
		Intf_Vlant_PFCC[CH2_PFCC2].PFCC_HiVltgSW = pCanFrame->Data.PFCC_HiVltgSW & 0x03;
		Intf_Vlant_PFCC[CH2_PFCC2].PFCC_DisplayHVState = pCanFrame->Data.PFCC_DisplayHVState & 0x03;
		Intf_Vlant_PFCC[CH2_PFCC2].PFCC_CmdCommunicationConfirm = ((pCanFrame->Data.PFCC_CmdCommunicationConfirm_H & 0xFF) << 8) + (pCanFrame->Data.PFCC_CmdCommunicationConfirm_L & 0xFF);

		switch(CanVolantData.LocNum)
		{
			case 1:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU1WorkMod & 0x07;
				break;
			case 2:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU2WorkMod & 0x07;
				break;
			case 3:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU3WorkMod & 0x07;
				break;
			case 4:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU4WorkMod & 0x07;
				break;
			case 5:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU5WorkMod & 0x07;
				break;
			case 6:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU6WorkMod & 0x07;
				break;
			case 7:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU7WorkMod & 0x07;
				break;
			case 8:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU8WorkMod & 0x07;
				break;
			case 9:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU9WorkMod & 0x07;
				break;
			case 10:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU10WorkMod & 0x07;
				break;
			case 11:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU11WorkMod & 0x07;
				break;
			default:
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUSpdCtrl = 0;
				Intf_Vlant_PFCC[CH2_PFCC2].PFCC_ReqMCUWorkMod = 0;
				break;
			}
	}
	else
	{
		Intf_Vlant_PFCC[CH2_PFCC2].CrcRightFlag = FALSE;
	}

	Intf_Vlant_PFCC[CH2_PFCC2].RollingCounter = pCanFrame->Data.RollingCounter & 0xFF;
	Intf_Vlant_PFCC[CH2_PFCC2].CRC = ((pCanFrame->Data.CRC_H & 0xFF) << 8) + (pCanFrame->Data.CRC_L & 0xFF);
}

void CanProtocol_PFCC2_PHSM_MCU_EXT2_Update(void *pframe)
{
	CanFrame_t *pCanFrame = (CanFrame_t *)pframe;

	pCanFrame->d16.d01 = (uint16)(0);
	pCanFrame->d16.d23 = (uint16)(0);
	pCanFrame->d16.d45 = (uint16)(0);
	pCanFrame->d16.d67 = (uint16)(0);
}

/* -------------------------------------------------------------------------- */

void CanProtocol_PFCC3_CtrlMsg_MCU_EXT2_Update(void *pframe)
{
	CANFD_EXT_RX1_OBJ *pCanFrame = (CANFD_EXT_RX1_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_EXT2[PFCC3_CtrlMsg_MCU_EXT2].frameId, sg_frameInfoList_EXT2[PFCC3_CtrlMsg_MCU_EXT2].dataLength, pframe))
	{
		Intf_Vlant_PFCC[CH2_PFCC3].CrcRightFlag = TRUE;

		Intf_Vlant_PFCC[CH2_PFCC3].PFCC_IsPrimaryChannel = pCanFrame->Data.PFCC_IsPrimaryChannel & 0x01;
		Intf_Vlant_PFCC[CH2_PFCC3].PFCC_HiVltgSW = pCanFrame->Data.PFCC_HiVltgSW & 0x03;
		Intf_Vlant_PFCC[CH2_PFCC3].PFCC_DisplayHVState = pCanFrame->Data.PFCC_DisplayHVState & 0x03;
		Intf_Vlant_PFCC[CH2_PFCC3].PFCC_CmdCommunicationConfirm = ((pCanFrame->Data.PFCC_CmdCommunicationConfirm_H & 0xFF) << 8) + (pCanFrame->Data.PFCC_CmdCommunicationConfirm_L & 0xFF);

		switch(CanVolantData.LocNum)
		{
			case 1:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU1SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU1WorkMod & 0x07;
				break;
			case 2:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU2SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU2WorkMod & 0x07;
				break;
			case 3:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU3SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU3WorkMod & 0x07;
				break;
			case 4:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU4SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU4WorkMod & 0x07;
				break;
			case 5:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU5SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU5WorkMod & 0x07;
				break;
			case 6:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU6SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU6WorkMod & 0x07;
				break;
			case 7:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU7SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU7WorkMod & 0x07;
				break;
			case 8:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU8SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU8WorkMod & 0x07;
				break;
			case 9:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU9SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU9WorkMod & 0x07;
				break;
			case 10:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU10SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU10WorkMod & 0x07;
				break;
			case 11:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_H, pCanFrame->Data.PFCC_ReqMCU11SpdCtrl_L) & 0x1FFF), float, 4000, 1);
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = pCanFrame->Data.PFCC_ReqMCU11WorkMod & 0x07;
				break;
			default:
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUSpdCtrl = 0;
				Intf_Vlant_PFCC[CH2_PFCC3].PFCC_ReqMCUWorkMod = 0;
				break;
			}
	}
	else
	{
		Intf_Vlant_PFCC[CH2_PFCC3].CrcRightFlag = FALSE;
	}

	Intf_Vlant_PFCC[CH2_PFCC3].RollingCounter = pCanFrame->Data.RollingCounter & 0xFF;
	Intf_Vlant_PFCC[CH2_PFCC3].CRC = ((pCanFrame->Data.CRC_H & 0xFF) << 8) + (pCanFrame->Data.CRC_L & 0xFF);
}

void CanProtocol_PFCC3_PHSM_MCU_EXT2_Update(void *pframe)
{
	CanFrame_t *pCanFrame = (CanFrame_t *)pframe;

	pCanFrame->d16.d01 = (uint16)(0);
	pCanFrame->d16.d23 = (uint16)(0);
	pCanFrame->d16.d45 = (uint16)(0);
	pCanFrame->d16.d67 = (uint16)(0);
}

/* -------------------------------------------------------------------------- */

void CanProtocol_MCU_EXT2_FbkMsg_PFCC_Update(void *pframe)
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
	setA825CRC(sg_frameInfoList_EXT2[MCU_EXT2_FbkMsg_PFCC].frameId, sg_frameInfoList_EXT2[MCU_EXT2_FbkMsg_PFCC].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_2.EXT_RollingCounter_F++;
	/* ----------------------------------UNUSED---------------------------------- */
	pCanFrame->Data.Rsvd_Byte12						= 0;
	pCanFrame->Data.Rsvd_Byte13						= 0;
	pCanFrame->Data.Rsvd_Byte14						= 0;
	pCanFrame->Data.Rsvd_Byte15						= 0;
}

void CanProtocol_MCU_EXT2_NormalMsg_PFCC_Update(void *pframe)
{
	switch(CanVolantData.McuC)
	{
		case MCU_A:
		{
			MCUA_EXT2_NormalMsg_Pack(pframe);
			break;
		}
		case MCU_B:
		{
			MCUB_EXT2_NormalMsg_Pack(pframe);
			break;
		}
		default:
			CanVolantData.McuC = TRUE;
			break;
	}

	CanVolantData.CanVolantModuleData_2.MsgAB_Flag = !CanVolantData.CanVolantModuleData_2.MsgAB_Flag;
}

void CanProtocol_MCU_EXT2_PHSM_Update(void *pframe)
{
	CANFD_EXT_TX3_OBJ *pCanFrame = (CANFD_EXT_TX3_OBJ *)pframe;

//    pCanFrame->Data.NB_ERR_RX_H		= (uint8)((PMSM.CanData.CanMoudleData[1].RxErrNum >> 8) & 0xFF);
//    pCanFrame->Data.NB_ERR_RX_L		= (uint8)(PMSM.CanData.CanMoudleData[1].RxErrNum & 0xFF);
//    pCanFrame->Data.NB_ERR_TX_H		= (uint8)((PMSM.CanData.CanMoudleData[1].TxErrNum >> 8) & 0xFF);
//    pCanFrame->Data.NB_ERR_TX_L		= (uint8)(PMSM.CanData.CanMoudleData[1].TxErrNum & 0xFF);
//    pCanFrame->Data.NB_ERR_ACK_H	= (uint8)((PMSM.CanData.CanMoudleData[1].NackErrNum >> 8) & 0xFF);
//    pCanFrame->Data.NB_ERR_ACK_L	= (uint8)(PMSM.CanData.CanMoudleData[1].NackErrNum & 0xFF);
//    pCanFrame->Data.NB_BUS_OFF		= (uint8)(PMSM.CanData.CanMoudleData[1].BusOffErrNum & 0xFF);
//    pCanFrame->Data.REC_STATE		= (uint8)(PMSM.CanData.CanMoudleData[1].RecState & 0xF);
//    pCanFrame->Data.TEC_STATE		= (uint8)(PMSM.CanData.CanMoudleData[1].TecState & 0xF);
}

void CanProtocol_MCU_EXT2_ConfigMsg_Update(void *pframe)
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

uint32 CanProtocol_Volant_EXT2_Event_Trigger(void)
{
	return 0;
}

void CanProtocol_Volant_EXT2_Event_Update(void)
{

}

/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数定义*/

static void MCUA_EXT2_NormalMsg_Pack(void *pframe)
{
	CANFD_EXT_TX2_OBJ *pCanFrame = (CANFD_EXT_TX2_OBJ *)pframe;

	switch(!CanVolantData.CanVolantModuleData_2.MsgAB_Flag)
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
			CanVolantData.CanVolantModuleData_2.MsgAB_Flag = FALSE;
			break;
	}

	pCanFrame->Data.MCU_PositionFbk				= (uint8)(CanVolantData.LocNum & 0xF);

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

	pCanFrame->Data.RollingCounter				= (uint8)(CanVolantData.CanVolantModuleData_2.EXT_RollingCounter_N & 0xFF);
	pCanFrame->Data.CRC_H						= 0;
	pCanFrame->Data.CRC_L						= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_EXT2[MCU_EXT2_NormalMsg_PFCC].frameId,sg_frameInfoList_EXT2[MCU_EXT2_NormalMsg_PFCC].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_2.EXT_RollingCounter_N++;
}

static void MCUB_EXT2_NormalMsg_Pack(void *pframe)
{
	CANFD_EXT_TX2_OBJ *pCanFrame = (CANFD_EXT_TX2_OBJ *)pframe;

	switch(!CanVolantData.CanVolantModuleData_2.MsgAB_Flag)
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
			CanVolantData.CanVolantModuleData_2.MsgAB_Flag = FALSE;
			break;
	}

	pCanFrame->Data.MCU_PositionFbk				= (uint8)(GcBSW_LocnBit_numb & 0xF);

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

	pCanFrame->Data.RollingCounter				= (uint8)(CanVolantData.CanVolantModuleData_2.EXT_RollingCounter_N & 0xFF);
	pCanFrame->Data.CRC_H						= 0;
	pCanFrame->Data.CRC_L						= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_EXT2[MCU_EXT2_NormalMsg_PFCC].frameId, sg_frameInfoList_EXT2[MCU_EXT2_NormalMsg_PFCC].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_2.EXT_RollingCounter_N++;
}

/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数定义*/

/************************ (C) COPYRIGHT SANTROLL *****END OF FILE****/
