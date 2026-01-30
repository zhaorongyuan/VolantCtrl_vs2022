/**
 * @file Protocol_Volant_INT1.c
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
#include <Protocol_Volant_INT1.h>
#include "stdlib.h"
//#include "MS_Ctrl.h"
//#include "PMSM_Param.h"
/* Private define ------------------------------------------------------------*/
/*此处添加仅本文件使用的宏定义常量*/

/* Private macro -------------------------------------------------------------*/
/*此处添加仅本文件使用的宏定义函数*/

/* Private typedef -----------------------------------------------------------*/
/*此处添加仅本文件使用的结构体声明*/

/* Private variables ---------------------------------------------------------*/
/*此处添加仅本文件使用的全局变量*/

static CanStdProtocol_FrameInfo_t sg_frameInfoList_INT1[CCSP_FRAME_NUM_INT1] =
{
	// 控制信息
    {.SN = 0, .frameFormat = 1, .frameMode = 2, .dataLength = 12, .direction = 1, .sendType = 0, .interval = 1, \
    .enableFlag = TRUE, .frameId = 0x18EF0E10, .pfDataUpdateFunc = CanProtocol_MCU_INT1_TX_CtrlMsg_Update, .pfTriggerFunc = NULL},

    {.SN = 1, .frameFormat = 1, .frameMode = 2, .dataLength = 12, .direction = 0, .sendType = 0, .interval = 1, \
    .enableFlag = TRUE, .frameId = 0x18EF0E10, .pfDataUpdateFunc = CanProtocol_MCU_INT1_RX_CtrlMsg_Update, .pfTriggerFunc = NULL},

	// 状态信息
    {.SN = 2, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 1, .sendType = 0, .interval = 1, \
    .enableFlag = TRUE, .frameId = 0x18EF0F01, .pfDataUpdateFunc = CanProtocol_MCU_INT1_TX_StateMsg_Update, .pfTriggerFunc = NULL},

    {.SN = 3, .frameFormat = 1, .frameMode = 2, .dataLength = 32, .direction = 0, .sendType = 0, .interval = 1, \
    .enableFlag = TRUE, .frameId = 0x18EF0F01, .pfDataUpdateFunc = CanProtocol_MCU_INT1_RX_StateMsg_Update, .pfTriggerFunc = NULL}
};

static uint32 sg_eventList_INT1[CCSP_EVENTFRAME_NUM_INT1] =
{
    0,
};

/* Exported variables --------------------------------------------------------*/
/*此处添加本文件向外暴露的变量*/

CANFD_INT_CTRL_OBJ IntCan1_CTRL;
CANFD_INT_STATE_OBJ IntCan1_STATE;
Flexcan_Ip_DataInfoType intcan1_tx_info[2] =
{
	{
	.msg_id_type = FLEXCAN_MSG_ID_EXT,
	.data_length = 12u,
	.is_polling = FALSE,
	.is_remote = FALSE,
	},
	{
	.msg_id_type = FLEXCAN_MSG_ID_EXT,
	.data_length = 32u,
	.is_polling = FALSE,
	.is_remote = FALSE,
	},
};



CanStdProtocol_t g_VolantInt1Protocol =
{
    .name = CCSP_NAME_INT1,
    .baudrate = CCSP_BAUDRATE_INT1,
    .fastBaudrate = CCSP_FASTBAUDRATE_INT1,
    .deviceType = CCSP_DEVICETYPE_INT1,
    .frameNum = CCSP_FRAME_NUM_INT1,
    .pframeInfoList = sg_frameInfoList_INT1,
    .pEventList = sg_eventList_INT1,
    .pfEventUpdate = CanProtocol_Volant_INT1_Event_Update
};

/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数声明*/

/* Exported functions --------------------------------------------------------*/
/*此处添加本文件向外暴露的函数定义*/

void CanProtocol_MCU_INT1_TX_CtrlMsg_Update(void *pframe)
{
	CANFD_INT_CTRL_OBJ *pCanFrame			= (CANFD_INT_CTRL_OBJ *)pframe;

	// 握手信息
	pCanFrame->Data.McuChannel		    	= (uint8)(GbBSW_McuCh_flg & 0x01);
	pCanFrame->Data.MstSlaveSts		    	= (uint8)(GbAIS_MstSlaveStsChked_flg & 0x01);
	pCanFrame->Data.MstSlaveStsLock			= (uint8)(GbAIS_MstSlaveStsLock_flg & 0x01);
	pCanFrame->Data.LocationBit				= (uint8)(GcBSW_LocnBit_numb & 0x0F);

	// 主从切换信息
	pCanFrame->Data.SwtRef_RxOrTx			= (uint8)(GbMSC_SwtRef_flg & 0x01);
	pCanFrame->Data.MstSlaveStsFin          = (uint8)(GbMSC_MstSlaveSts_flg & 0x01);
	pCanFrame->Data.SwitchState             = (uint8)(GeMSC_SwitchState_enum & 0x0F);

	pCanFrame->Data.FaultLevel              = (uint8)(GeEVL_ErrLevel_enum & 0x07);

	pCanFrame->Data.WorkMod_RxOrTx			= (uint8)(GeMSM_SMModReq_enum  & 0x0F);

	pCanFrame->Data.Is_RxOrTx_H				= (uint8)((CAN_DATA_PACK((GsSLC_IsRef_pu * 1000), uint16, 1500, 20) >> 8) & 0xFF);
	pCanFrame->Data.Is_RxOrTx_L				= (uint8)(CAN_DATA_PACK((GsSLC_IsRef_pu * 1000), uint16, 1500, 20) & 0xFF);

	pCanFrame->Data.SoftwareVersion_H		= (uint8)((CAN_DATA_PACK(GcBSW_SoftVers_numb, uint16, 0, 1) >> 8) & 0xFF);
	pCanFrame->Data.SoftwareVersion_L		= (uint8)(CAN_DATA_PACK(GcBSW_SoftVers_numb, uint16, 0, 1) & 0xFF);

//	pCanFrame->Data.McuChannelBit			= (uint8)(CanVolantData.CanVolantArbitrateData.McuBit & 0x01);
//	pCanFrame->Data.MasterSlaveBit			= (uint8)(CanVolantData.CanVolantArbitrateData.MasterSlaveBit & 0x03);
//	pCanFrame->Data.LocationBit				= (uint8)(CanVolantData.CanVolantArbitrateData.LocationBit & 0x0F);
//	pCanFrame->Data.HandshakeBit			= (uint8)(CanVolantData.CanVolantArbitrateData.HandshakeBit & 0x01);
//
//	pCanFrame->Data.SwitchMS_RxOrTx			= (uint8)(MS_Data.SwitchMS_Tx & 0x01);
//	pCanFrame->Data.SwitchFinish_RxOrTx		= (uint8)(MS_Data.SwitchFinish_Tx & 0x01);
//
//	pCanFrame->Data.DisplayHVState_RxOrTx	= (uint8)(PMSM.Intf_Vlant.PFCC_DisplayHVState & 0x03);
//
//	pCanFrame->Data.WorkMod_RxOrTx			= (uint8)(PMSM.Intf_Vlant.PFCC_ReqMCUWorkMod & 0x0F);
//	pCanFrame->Data.SpeedRef_RxOrTx_H		= (uint8)((CAN_DATA_PACK(PMSM.Intf_Vlant.PFCC_ReqMCUSpdCtrl, uint16, 3000, 10) >> 8) & 0xFF);
//	pCanFrame->Data.SpeedRef_RxOrTx_L		= (uint8)(CAN_DATA_PACK(PMSM.Intf_Vlant.PFCC_ReqMCUSpdCtrl, uint16, 3000, 10) & 0xFF);
//	pCanFrame->Data.Is_RxOrTx_H				= (uint8)((CAN_DATA_PACK((PMSM.PI_Spd.Out * 1000), uint16, 1500, 20) >> 8) & 0xFF);
//	pCanFrame->Data.Is_RxOrTx_L				= (uint8)(CAN_DATA_PACK((PMSM.PI_Spd.Out * 1000), uint16, 1500, 20) & 0xFF);
//
//	pCanFrame->Data.SoftwareVersion_H		= (uint8)((CAN_DATA_PACK(CanVolantData.CanVolantArbitrateData.SoftwareVersion, uint16, 0, 1) >> 8) & 0xFF);
//	pCanFrame->Data.SoftwareVersion_L		= (uint8)(CAN_DATA_PACK(CanVolantData.CanVolantArbitrateData.SoftwareVersion, uint16, 0, 1) & 0xFF);
//
//	pCanFrame->Data.Rsvd_Byte8				= 0;
//
	pCanFrame->Data.RollingCounter_Ctrl		= (uint8)(CanVolantData.CanVolantModuleData_1.INT_RollingCounter_C & 0xFF);
	pCanFrame->Data.CRC_Ctrl_H				= 0;
	pCanFrame->Data.CRC_Ctrl_L				= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_INT1[MCU_INT1_TX_CtrlMsg].frameId, sg_frameInfoList_INT1[MCU_INT1_TX_CtrlMsg].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_1.INT_RollingCounter_C++;
}

void CanProtocol_MCU_INT1_RX_CtrlMsg_Update(void *pframe)
{
	CANFD_INT_CTRL_OBJ *pCanFrame		= (CANFD_INT_CTRL_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_INT1[MCU_INT1_RX_CtrlMsg].frameId, sg_frameInfoList_INT1[MCU_INT1_RX_CtrlMsg].dataLength, pframe))
	{
		CanVolantData.CanVolantModuleData_1.INT_CRC_Ctrl_Fault 			= FALSE;

		if(CanVolantData.CanVolantModuleData_1.INT_IsPrimaryModule)
		{
			// 握手信息
			GbBSW_McuChRd_flg				    = pCanFrame->Data.McuChannel & 0x01;
			GbBSW_MstSlaveStsChkedRd_flg		= pCanFrame->Data.MstSlaveSts & 0x01;
			GbBSW_MstSlaveStsLockRd_flg		    = pCanFrame->Data.MstSlaveStsLock & 0x01;
			GcBSW_LocnBitRd_numb			    = pCanFrame->Data.LocationBit & 0x0F;

			// 主从切换信息
			GbBSW_SwtRefRd_flg				    = pCanFrame->Data.SwtRef_RxOrTx & 0x01;
			GbBSW_MstSlaveStsRd_flg             = pCanFrame->Data.MstSlaveStsFin & 0x01;
			GeBSW_SwitchStateRd_enum            = pCanFrame->Data.SwitchState & 0x0F;

			GeBSW_ErrLevelRd_enum               = pCanFrame->Data.FaultLevel & 0x07;

			GeBSW_ModReqRd_enum                 = pCanFrame->Data.WorkMod_RxOrTx & 0x0F;

			GsBSW_IsRefRd_pu					= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.Is_RxOrTx_H, pCanFrame->Data.Is_RxOrTx_L), float, 1500, 20) / 1000;

			GcBSW_SoftVersRd_numb		        = ((pCanFrame->Data.SoftwareVersion_H & 0xFF) << 8) + (pCanFrame->Data.SoftwareVersion_L & 0xFF);

//			MS_Data.MS_CtrlMsg.McuChannelBit							= pCanFrame->Data.McuChannelBit & 0x01;
//			MS_Data.MS_CtrlMsg.MasterSlaveBit							= pCanFrame->Data.MasterSlaveBit & 0x03;
//			MS_Data.MS_CtrlMsg.LocationBit								= pCanFrame->Data.LocationBit & 0x0F;
//			MS_Data.MS_CtrlMsg.HandshakeBit								= pCanFrame->Data.HandshakeBit & 0x01;
//			MS_Data.MS_CtrlMsg.SoftwareVersion							= ((pCanFrame->Data.SoftwareVersion_H & 0xFF) << 8) + (pCanFrame->Data.SoftwareVersion_L & 0xFF);
//
//			MS_Data.MS_CtrlMsg.DisplayHVState_Rx						= pCanFrame->Data.DisplayHVState_RxOrTx & 0x03;
//
//			MS_Data.MS_CtrlMsg.WorkMod_Rx								= pCanFrame->Data.WorkMod_RxOrTx & 0x0F;
//			MS_Data.MS_CtrlMsg.SpeedRef_Rx								= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.SpeedRef_RxOrTx_H, pCanFrame->Data.SpeedRef_RxOrTx_L), float, 3000, 10);
//
//			MS_Data.MS_CtrlMsg.RollingCounter_Ctrl						= pCanFrame->Data.RollingCounter_Ctrl & 0xFF;
//			MS_Data.MS_CtrlMsg.CRC_Ctrl									= ((pCanFrame->Data.CRC_Ctrl_H & 0xFF) << 8) + (pCanFrame->Data.CRC_Ctrl_L & 0xFF);
		}
	}
	else
	{
		CanVolantData.CanVolantModuleData_1.INT_CRC_Ctrl_Fault 			= TRUE;
	}
	CanVolantData.CanVolantModuleData_1.INT_RollingCounter_Ctrl_Fbk	= pCanFrame->Data.RollingCounter_Ctrl & 0xFF;
}

/* ---------------------------------------------------------------------------------- */

void CanProtocol_MCU_INT1_TX_StateMsg_Update(void *pframe)
{
	CANFD_INT_STATE_OBJ *pCanFrame = (CANFD_INT_STATE_OBJ *)pframe;
	pCanFrame->Data.MCUWorkMod_Fbk				= (uint8)(GeMSM_MOTState_enum & 0x0F);
	pCanFrame->Data.CommunicationConfirm_Fbk	= 0;

	pCanFrame->Data.WarningBit_Fbk_31_24		= (uint8)((WltFaultNow.All[1] >> 8) & 0xFF);
	pCanFrame->Data.WarningBit_Fbk_23_16		= (uint8)((WltFaultNow.All[1]) & 0xFF);
	pCanFrame->Data.WarningBit_Fbk_15_8			= (uint8)((WltFaultNow.All[0] >> 8) & 0xFF);
	pCanFrame->Data.WarningBit_Fbk_7_0			= (uint8)((WltFaultNow.All[0]) & 0xFF);
	pCanFrame->Data.FaultBit_Fbk_31_24			= (uint8)((WltFaultNow.All[3] >> 8) & 0xFF);
	pCanFrame->Data.FaultBit_Fbk_23_16			= (uint8)((WltFaultNow.All[3]) & 0xFF);
	pCanFrame->Data.FaultBit_Fbk_15_8			= (uint8)((WltFaultNow.All[2] >> 8) & 0xFF);
	pCanFrame->Data.FaultBit_Fbk_7_0			= (uint8)((WltFaultNow.All[2]) & 0xFF);

	pCanFrame->Data.MotRdcErr                   = (uint8)(GbBSW_MotRdcFault_flg & 0x01);

	pCanFrame->Data.PowerFbk_H					= (uint8)((CAN_DATA_PACK(GsSPL_InvPwr_Kw, uint16, 400, 10) >> 8) & 0x1F);
	pCanFrame->Data.PowerFbk_L					= (uint8)(CAN_DATA_PACK(GsSPL_InvPwr_Kw, uint16, 400, 10) & 0xFF);

	pCanFrame->Data.Udc_Fbk_H					= (uint8)((CAN_DATA_PACK((GsSPH_VltgBusFilter_V), uint16, 0, 50) >> 8) & 0xFF);
	pCanFrame->Data.Udc_Fbk_L					= (uint8)(CAN_DATA_PACK((GsSPH_VltgBusFilter_V), uint16, 0, 50) & 0xFF);
	pCanFrame->Data.FrontBearTemp_Fbk			= (uint8)(CAN_DATA_PACK(GsSPL_FrntBearTemp_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.BackBearTemp_Fbk			= (uint8)(CAN_DATA_PACK(GsSPL_BackBearTemp_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.SicTemp_Fbk					= (uint8)(CAN_DATA_PACK(GsSPL_InvTemp_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.MotorTemp_Fbk				= (uint8)(CAN_DATA_PACK(GsSPL_MotTemp_C, uint16, 20, 1) & 0xFF);
	pCanFrame->Data.PhaseCurU_Fbk				= 0;
	pCanFrame->Data.PhaseCurV_Fbk				= 0;
	pCanFrame->Data.PhaseCurW_Fbk				= 0;

	pCanFrame->Data.Volt28V_H				    = (uint8)((CAN_DATA_PACK(GsSPL_Vltg28_V, uint16, 0, 10) >> 1 ) & 0xFF);;
	pCanFrame->Data.Volt28V_L				    = (uint8)(CAN_DATA_PACK(GsSPL_Vltg28_V, uint16, 0, 10) & 0x01);

	pCanFrame->Data.Is_Fbk_H					= 0;
	pCanFrame->Data.Is_Fbk_L					= 0;
	pCanFrame->Data.Spd_Fbk_H					= 0;
	pCanFrame->Data.Spd_Fbk_L					= 0;
	pCanFrame->Data.EST_Spd_Fbk_H				= 0;
	pCanFrame->Data.EST_Spd_Fbk_L				= 0;

	pCanFrame->Data.Rsvd_Byte28			        = 0;

	pCanFrame->Data.RollingCounter_State		= 0;
	pCanFrame->Data.CRC_H						= 0;
	pCanFrame->Data.CRC_L						= 0;
	/* ----------------------------------CRC------------------------------------- */
	setA825CRC(sg_frameInfoList_INT1[MCU_INT1_TX_StateMsg].frameId, sg_frameInfoList_INT1[MCU_INT1_TX_StateMsg].dataLength, pframe);
	/* -----------------------------RollingCounter------------------------------- */
	CanVolantData.CanVolantModuleData_1.INT_RollingCounter_S++;
}

void CanProtocol_MCU_INT1_RX_StateMsg_Update(void *pframe)
{
	CANFD_INT_STATE_OBJ *pCanFrame = (CANFD_INT_STATE_OBJ *)pframe;

	if(checkA825CRC(sg_frameInfoList_INT1[MCU_INT1_RX_StateMsg].frameId, sg_frameInfoList_INT1[MCU_INT1_RX_StateMsg].dataLength, pframe))
	{
		CanVolantData.CanVolantModuleData_1.INT_CRC_State_Fault				= FALSE;

		if(CanVolantData.CanVolantModuleData_1.INT_IsPrimaryModule)
		{
			GeBSW_MOTStateRd_enum								            = pCanFrame->Data.MCUWorkMod_Fbk & 0x0F;
//			MS_Data.MS_StateMsg.CommunicationConfirm_Fbk					= pCanFrame->Data.CommunicationConfirm_Fbk & 0x0F;

			GcBSW_WarningBitFbk_flg							            	= ((pCanFrame->Data.WarningBit_Fbk_31_24 & 0xFF) << 24) + ((pCanFrame->Data.WarningBit_Fbk_23_16 & 0xFF) << 16)\
																			+ ((pCanFrame->Data.WarningBit_Fbk_15_8 & 0xFF) << 8) + (pCanFrame->Data.WarningBit_Fbk_7_0 & 0xFF);
			GcBSW_FaultBitFbk_flg								            = ((pCanFrame->Data.FaultBit_Fbk_31_24 & 0xFF) << 24) + ((pCanFrame->Data.FaultBit_Fbk_23_16 & 0xFF) << 16)\
																			+ ((pCanFrame->Data.FaultBit_Fbk_15_8 & 0xFF) << 8) + (pCanFrame->Data.FaultBit_Fbk_7_0 & 0xFF);

			GbBSW_MotRdcFaultRd_flg                                   	    = (pCanFrame->Data.MotRdcErr & 0x01);

			GsBSW_InvPwrRd_Kw			                                    = CAN_DATA_ANSYS((CAN_DATA_CALC(pCanFrame->Data.PowerFbk_H, pCanFrame->Data.PowerFbk_L) & 0x1FFF), float, 400, 10);

			GsBSW_VltgBusFilterRd_V					        				= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.Udc_Fbk_H, pCanFrame->Data.Udc_Fbk_L), float, 0, 50);

			GsBSW_FrntBearTempRd_C							                = CAN_DATA_ANSYS(pCanFrame->Data.FrontBearTemp_Fbk, float, 20, 1);
			GsBSW_BackBearTempRd_C							                = CAN_DATA_ANSYS(pCanFrame->Data.BackBearTemp_Fbk, float, 20, 1);
			GsBSW_InvTempRd_C								            	= CAN_DATA_ANSYS(pCanFrame->Data.SicTemp_Fbk, float, 20, 1);
			GsBSW_MotTempRd_C								                = CAN_DATA_ANSYS(pCanFrame->Data.MotorTemp_Fbk, float, 20, 1);
//
//			MS_Data.MS_StateMsg.PhaseCurU_Fbk								= pCanFrame->Data.PhaseCurU_Fbk & 0xFF;
//			MS_Data.MS_StateMsg.PhaseCurV_Fbk								= pCanFrame->Data.PhaseCurV_Fbk & 0xFF;
//			MS_Data.MS_StateMsg.PhaseCurW_Fbk								= pCanFrame->Data.PhaseCurW_Fbk & 0xFF;
//
//			MS_Data.MS_StateMsg.Is_Fbk										= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.Is_Fbk_H, pCanFrame->Data.Is_Fbk_L), float, 1500, 20);
//			MS_Data.MS_StateMsg.Spd_Fbk										= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.Spd_Fbk_H, pCanFrame->Data.Spd_Fbk_L), float, 3000, 10);
//			MS_Data.MS_StateMsg.EST_Spd_Fbk									= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.EST_Spd_Fbk_H, pCanFrame->Data.EST_Spd_Fbk_L), float, 3000, 10);
//
//			MS_Data.MS_StateMsg.RollingCounter_State						= pCanFrame->Data.RollingCounter_State & 0xFF;
//			MS_Data.MS_StateMsg.CRC											= CAN_DATA_ANSYS(CAN_DATA_CALC(pCanFrame->Data.CRC_H, pCanFrame->Data.CRC_L), float, 0, 1);
//
			WltFaultNowRd.All[0]											= ((pCanFrame->Data.WarningBit_Fbk_15_8 & 0xFF) << 8) + (pCanFrame->Data.WarningBit_Fbk_7_0 & 0xFF);
			WltFaultNowRd.All[1]											= ((pCanFrame->Data.WarningBit_Fbk_31_24 & 0xFF) << 8) + (pCanFrame->Data.WarningBit_Fbk_23_16 & 0xFF);
			WltFaultNowRd.All[2]											= ((pCanFrame->Data.FaultBit_Fbk_15_8 & 0xFF) << 8) + (pCanFrame->Data.FaultBit_Fbk_7_0 & 0xFF);
			WltFaultNowRd.All[3]											= ((pCanFrame->Data.FaultBit_Fbk_31_24 & 0xFF) << 8) + (pCanFrame->Data.FaultBit_Fbk_23_16 & 0xFF);

			GsBSW_Vltg28Rd_V                                         	    = CAN_DATA_ANSYS((((pCanFrame->Data.Volt28V_H & 0xFF) << 1) + (pCanFrame->Data.Volt28V_L & 0x01)), float, 0, 10);
		}

		CanVolantData.CanVolantModuleData_1.INT_RollingCounter_State_Fbk	= pCanFrame->Data.RollingCounter_State & 0xFF;
	}
	else
	{
		CanVolantData.CanVolantModuleData_1.INT_CRC_State_Fault				= TRUE;
	}
}

uint32 CanProtocol_Volant_INT1_Event_Trigger(void)
{
	return 0;
}

void CanProtocol_Volant_INT1_Event_Update(void)
{

}



/* Private function prototypes -----------------------------------------------*/
/*此处添加仅本文件使用的函数定义*/

/************************ (C) COPYRIGHT SANTROLL *****END OF FILE****/



