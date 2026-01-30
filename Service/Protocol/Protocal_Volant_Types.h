/*
 * Protocal_Volant_Types.h
 *
 *  Created on: 2024年11月28日
 *      Author: sz-p1159
 */

#ifndef SW_CONFIG_PROTOCOL_PROTOCAL_VOLANT_TYPES_H_
#define SW_CONFIG_PROTOCOL_PROTOCAL_VOLANT_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/*此处添加引用的头文件*/

#include "Platform_Types.h"
#include "ARINC825.h"

/* Exported constants --------------------------------------------------------*/
/*此处添加向外暴露的宏定义常量*/

#define CAN_SANTROLL_MODE			0
#define CAN_SANTROLL_ADJUST_MODE	0

#define CAN_VOLANT_DEBUG_MODE		0

#define CAN_DATA_PACK(Data, Type, Offset, Factor)		((Type)((Data + Offset) * Factor))
#define CAN_DATA_CALC(Data_H, Data_L)					(((Data_H & 0xFF) << 8) + (Data_L & 0xFF))
#define CAN_DATA_ANSYS(Data, Type, Offset, Factor)		((((Type)Data) / Factor) - Offset)

/* Exported macro ------------------------------------------------------------*/
/*此处添加向外暴露的宏定义函数*/

#define DEBUG_KEY	1
#define FEE_KEY		6
#define PARA_KEY	31
#define SILENCE_KEY	4
#define RESET_KEY	11

/* ------------------------------------------*/
#define PFCC_NUM					6
#define PFCC_PERIOD					100
/* ------------------------------------------*/
#define KP_RES						0.001f
#define KI_RES						0.0001f
/* ------------------------------------------*/
#define SP_KP_MAX					8000.0f
#define SP_KP_MIN					2000.0f

#define SP_KI_MAX					200.0f
#define SP_KI_MIN					20.0f
/* ------------------------------------------*/
#define CUR_KP_MAX					800.0f
#define CUR_KP_MIN					200.0f

#define CUR_KI_MAX					200.0f
#define CUR_KI_MIN					20.0f
/* ------------------------------------------*/
#define DEBUG_KEY					1
#define FEE_KEY						6
#define PARA_KEY					31
#define SILENCE_KEY					4
#define ISRMSG_KEY					11
#define CAL_KEY						15
#define INJECT_KEY					7
/* ------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/*此处添加向外暴露的结构体声明*/

typedef enum
{
	CH1_PFCC1		= 0,
	CH1_PFCC2		= 1,
	CH1_PFCC3		= 2,

	CH2_PFCC1		= 3,
	CH2_PFCC2		= 4,
	CH2_PFCC3		= 5,

	NULL_PFCC		= 0xFF,
}PFCC_NUM_e;

typedef enum
{
	NULL_FUNC		= 0,
	DEBUG_FUNC		= 1,
	FEE_FUNC		= 2,
	PARA_FUNC		= 3,
	SILENCE_FUNC	= 4,
	ISRMSG_FUNC		= 5,
	CAL_FUNC		= 6,
	INJECT_FUNC		= 7,
}FUN_REQ_e;

typedef enum
{
	FAULT_TRIGGER_MODE	= 0,
	MANUAL_TRIGGER_MODE	= 1,
}FUN_ISR_MSG_MODE_e;

typedef enum
{
	NULL_MSG_FUNC		= 0,
	RECORD_MSG_FUNC		= 1,
	CLEAR_MSG_FUNC		= 2,
	FAULT_MSG_FUNC		= 3,
}FUN_ISR_MSG_FUNC_e;

typedef enum
{
	MCU_A		= 1,
	MCU_B		= 0
} MCU_C;

typedef enum
{
	MODE_NULL	= 0,
	MODE_MASTER	= 1,
	MODE_SLAVE	= 2,
	MODE_ERR	= 3
} MASTER_SLAVE;

typedef struct
{
	// 发送的数据
	boolean	McuBit;
	uint8	MasterSlaveBit;
	uint8	LocationBit;
	boolean	HandshakeBit;
	uint16	SoftwareVersion;
	// 接收的数据
	boolean	McuBitFbk;
	uint8	MasterSlaveBitFbk;
	uint8	LocationBitFbk;
	boolean	HandshakeBitFbk;
	uint16	SoftwareVersionFbk;
	uint8	RollingCounterFbk;
} CanVolantArbitrateData_t;

typedef struct
{
	boolean	MsgAB_Flag;

	uint8	EXT_RollingCounter_N;
	uint8	EXT_RollingCounter_F;
	uint8	INT_RollingCounter_C;
	uint8	INT_RollingCounter_S;

	boolean	EXT_IsPrimaryModule;
	boolean	INT_IsPrimaryModule;

	uint8	EXT_RollingCounterFbk;

	uint8	INT_RollingCounter_Ctrl_Fbk;
	uint8	INT_RollingCounter_State_Fbk;

	boolean EXT_CRC_PFCC1_Fault;
	boolean EXT_CRC_PFCC2_Fault;
	boolean EXT_CRC_PFCC3_Fault;

	boolean INT_CRC_Ctrl_Fault;
	boolean INT_CRC_State_Fault;

	boolean	PFCC_PrimaryChannelAvailable;
	boolean	PFCC_ChannelRefresh;
} CanVolantModuleData_t;

typedef struct
{
	uint8	FunctionRequest;
	uint8	SecurityKey;

	uint8	MCU_LocNum;
	boolean	MCU_AOrB;

	boolean MCUA_DebugMsgEnable;
	boolean MCUB_DebugMsgEnable;

	boolean SilenceAll;

	boolean InjectSlowFaultFlag;
	boolean InjectSlowFaultState;
	boolean InjectFastFaultFlag;
	boolean InjectFastFaultState;

	boolean IsrMsgMode;
	uint8 IsrMsgFunc;

	uint8 NVM_Block_Num;

	uint16	Kp;
	uint16	Ki;

	uint16	ElecZeroComp;
	boolean	SwapEncoderDir;
	boolean	SwapPhase;
	uint16	SlpTheta;
} CanDebugData_t;

typedef struct
{
	// 通用数据
	boolean	McuC;
	boolean	IsMasterMCU;
	uint8	LocNum;
	uint16	SoftwareVersion;

	uint8	McuID;
	uint8	LocID;
	uint8	IdOffset;
	uint8	HandshakeCnt;
	uint16	ArbitrateNum;
	boolean	ArbitrateFlag;
	boolean	ArbitrateFault;

	boolean NVM_SendFlag;
	uint16 NVM_SendNum;
	uint8 NVM_BlockNum;

	boolean InjectSlowFaultFlag;
	boolean InjectSlowFaultState;
	boolean InjectFastFaultFlag;
	boolean InjectFastFaultState;

	boolean IsrMsgMode;
	uint8 IsrMsgFunc;

	uint8 Heart;

	uint16 Kp;
	uint16 Ki;

	PFCC_NUM_e PFCC_PrimaryChannelNum;

	// 仲裁数据
	CanVolantArbitrateData_t CanVolantArbitrateData;

	// 模块0数据
	CanVolantModuleData_t CanVolantModuleData_1;
	// 模块1数据
	CanVolantModuleData_t CanVolantModuleData_2;

	// Debug数据
	CanDebugData_t CanDebugData;
} CanVolantData_t;

typedef struct
{
    uint8 SN;							/**< @brief 帧序号*/
    uint8 frameFormat;					/**< @brief 虚拟邮箱对应的Can帧格式 0:标准帧 1:扩展帧 */
    uint8 frameMode;					/**< @brief CAN帧模式选择 0:经典Can帧 1:CanFD长帧 2:CanFD长快帧 */
    uint8 dataLength;					/**< @brief CAN帧数据域长度 0:0byte, ..., 8:8byte, 9:12byte, 10:16byte, 11:20byte, 12:24byte, 13:32byte, 14:48byte 15:64byte(最大)*/
    uint8 direction;					/**< @brief CAN帧 收发选择 0:接收 1:发送 */
    uint8 sendType;						/**< @brief 发送类型 0:循环发送 1:事件发送 */
    uint16 interval;					/**< @brief CAN帧 收发间隔，单位ms*/
    uint8  offset;						/**< @brief 时序偏移*/
    uint32 frameId;						/**< @brief CAN帧ID */
    boolean enableFlag;					/**< @brief CAN帧是否启用 */
    void (*pfDataUpdateFunc)(void*);	/**< @brief 数据更新函数指针 */
    uint32 (*pfTriggerFunc)(void);		/**< @brief 触发函数指针 */
    uint8 *data;
} CanStdProtocol_FrameInfo_t;

typedef struct
{
	 char name[63];                                             /**< @brief 协议名称，最大长度为63字节 */
	uint32 baudrate;                                           /**< @brief 波特率 */
	uint32 fastBaudrate;                                       /**< @brief 高速波特率 */
	uint8 deviceType;                                          /**< @brief 设备类型 */
	uint8 frameNum;                                            /**< @brief 协议帧数量 */
	CanStdProtocol_FrameInfo_t *pframeInfoList;                /**< @brief 协议帧信息列表指针 */
	uint32 *pEventList;                                        /**< @brief 事件列表指针 */
	void (*pfEventUpdate)(void);                               /**< @brief 事件更新函数指针 */
	} CanStdProtocol_t;

/* ---------------------------------------------------------------------------------- */

typedef union
{
	uint64 ALL;
    struct
    {
        uint32 dLow;
        uint32 dHigh;
    }d32;
    struct
    {
        uint32 d01:16;
        uint32 d23:16;
        uint32 d45:16;
        uint32 d67:16;
    }d16;
    struct
    {
        uint32 d0:8;
        uint32 d1:8;
        uint32 d2:8;
        uint32 d3:8;
        uint32 d4:8;
        uint32 d5:8;
        uint32 d6:8;
        uint32 d7:8;
    }d8;
} CanFrame_t;

typedef struct
{
    CanFrame_t data[8];
} CanFDFrame_t;

/* ---------------------------------------------------------------------------------- */

typedef union
{
	uint64 ALL[4];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0 */
		uint8 PFCC_IsPrimaryChannel				:1;
		uint8 Rsvd_Byte0_Bit1_3					:3;
		uint8 PFCC_HiVltgSW                     :2;
		uint8 PFCC_DisplayHVState				:2;
		/* Byte1 */
		uint8 PFCC_CmdCommunicationConfirm_H	:8;
		/* Byte2 */
		uint8 PFCC_CmdCommunicationConfirm_L	:8;
		/* ------------- MUC1 START ------------- */
		/* Byte3 */
		uint8 PFCC_ReqMCU1SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU1WorkMod				:3;
		/* Byte4 */
		uint8 PFCC_ReqMCU1SpdCtrl_L				:8;
		/* ------------- MUC2 START ------------- */
		/* Byte5 */
		uint8 PFCC_ReqMCU2SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU2WorkMod				:3;
		/* Byte6 */
		uint8 PFCC_ReqMCU2SpdCtrl_L				:8;
		/* ------------- MUC3 START ------------- */
		/* Byte7 */
		uint8 PFCC_ReqMCU3SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU3WorkMod				:3;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8 */
		uint8 PFCC_ReqMCU3SpdCtrl_L				:8;
		/* ------------- MUC4 START ------------- */
		/* Byte9 */
		uint8 PFCC_ReqMCU4SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU4WorkMod				:3;
		/* Byte10 */
		uint8 PFCC_ReqMCU4SpdCtrl_L				:8;
		/* ------------- MUC5 START ------------- */
		/* Byte11 */
		uint8 PFCC_ReqMCU5SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU5WorkMod				:3;
		/* Byte12 */
		uint8 PFCC_ReqMCU5SpdCtrl_L				:8;
		/* ------------- MUC6 START ------------- */
		/* Byte13 */
		uint8 PFCC_ReqMCU6SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU6WorkMod				:3;
		/* Byte14 */
		uint8 PFCC_ReqMCU6SpdCtrl_L				:8;
		/* ------------- MUC7 START ------------- */
		/* Byte15 */
		uint8 PFCC_ReqMCU7SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU7WorkMod				:3;
		/* ----------------------------------ALL[2]---------------------------------- */
		/* Byte16 */
		uint8 PFCC_ReqMCU7SpdCtrl_L				:8;
		/* ------------- MUC8 START ------------- */
		/* Byte17 */
		uint8 PFCC_ReqMCU8SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU8WorkMod				:3;
		/* Byte18 */
		uint8 PFCC_ReqMCU8SpdCtrl_L				:8;
		/* ------------- MUC9 START ------------- */
		/* Byte19 */
		uint8 PFCC_ReqMCU9SpdCtrl_H				:5;
		uint8 PFCC_ReqMCU9WorkMod				:3;
		/* Byte20 */
		uint8 PFCC_ReqMCU9SpdCtrl_L				:8;
		/* ------------- MUC10 START ------------ */
		/* Byte21 */
		uint8 PFCC_ReqMCU10SpdCtrl_H			:5;
		uint8 PFCC_ReqMCU10WorkMod				:3;
		/* Byte22 */
		uint8 PFCC_ReqMCU10SpdCtrl_L			:8;
		/* ------------- MUC11 START ------------ */
		/* Byte23 */
		uint8 PFCC_ReqMCU11SpdCtrl_H			:5;
		uint8 PFCC_ReqMCU11WorkMod				:3;
		/* ----------------------------------ALL[3]---------------------------------- */
		/* Byte24 */
		uint8 PFCC_ReqMCU11SpdCtrl_L			:8;
		/* ----------------- END ---------------- */
		/* Byte25 */
		uint8 Rsvd_Byte25						:8;
		/* Byte26 */
		uint8 Rsvd_Byte26						:8;
		/* Byte27 */
		uint8 Rsvd_Byte27						:8;
		/* Byte28 */
		uint8 Rsvd_Byte28						:8;
		/* Byte29 */
		uint8 RollingCounter					:8;
		/* Byte30 */
		uint8 CRC_H								:8;
		/* Byte31 */
		uint8 CRC_L								:8;
    }Data;
}CANFD_EXT_RX1_OBJ;

typedef union
{
	uint64 ALL[2];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0 */
		uint8 MCU_ControlModule				:1;
		uint8 Rsvd_Byte0_Bit1				:1;
		uint8 MCU_FaultLevelFbk				:3;
		uint8 MCU_WorkModFbk				:3;
		/* Byte1 */
		uint8 MCU_FbkCommunicationConfirm_H	:8;
		/* Byte2 */
		uint8 MCU_FbkCommunicationConfirm_L	:8;
		/* Byte3 */
		uint8 MCU_SpdFbk_H					:8;
		/* Byte4 */
		uint8 MCU_SpdFbk_L					:8;
		/* Byte5 */
		uint8 MCU_SpdFbkInvalid				:1;
		uint8 CANCmdMsgTimeout				:3;
		uint8 MCU_PowerFbkInvalid			:1;
		uint8 Rsvd_Byte4_Bit5_7				:3;
		/* Byte6 */
		uint8 MCU_PowerFbk_H				:8;
		/* Byte7 */
		uint8 Rsvd_Byte6_Bit0_6				:7;
		uint8 MCU_PowerFbk_L				:1;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8 */
		uint8 MCU_PowerPercentFbk			:8;
		/* Byte9 */
		uint8 RollingCounter				:8;
		/* Byte10 */
		uint8 CRC_H							:8;
		/* Byte11 */
		uint8 CRC_L							:8;
		/* ----------------------------------UNUSED---------------------------------- */
		/* Byte12 */
		uint8 Rsvd_Byte12					:8;
		/* Byte13 */
		uint8 Rsvd_Byte13					:8;
		/* Byte14 */
		uint8 Rsvd_Byte14					:8;
		/* Byte15 */
		uint8 Rsvd_Byte15					:8;
    }Data;
}CANFD_EXT_TX1_OBJ;

typedef union
{
	uint64 ALL[4];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0 */
		uint8 MCU_PositionFbk					:4;
		uint8 MCU_InformationValid				:1;
		uint8 MCU_FaultLevelFbk					:3;
		/* Byte1 */
		uint8 MCU_WarningBitFbk_31_24			:8;
		/* Byte2 */
		uint8 MCU_WarningBitFbk_23_16			:8;
		/* Byte3 */
		uint8 MCU_WarningBitFbk_15_8			:8;
		/* Byte4 */
		uint8 MCU_WarningBitFbk_7_0				:8;
		/* Byte5 */
		uint8 MCU_FaultBitFbk_31_24				:8;
		/* Byte6 */
		uint8 MCU_FaultBitFbk_23_16				:8;
		/* Byte7 */
		uint8 MCU_FaultBitFbk_15_8				:8;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8 */
		uint8 MCU_FaultBitFbk_7_0				:8;
		/* Byte9 */
		uint8 MCUA_Udc_H						:8;
		/* Byte10 */
		uint8 MCUA_Udc_L						:8;
		/* Byte11 */
		uint8 MCUB_Udc_H						:8;
		/* Byte12 */
		uint8 MCUB_Udc_L						:8;
		/* Byte13 */
		uint8 MCU_FrontBearTemp					:8;
		/* Byte14 */
		uint8 MCU_BackBearTemp					:8;
		/* Byte15 */
		uint8 MCU_SicTempFbk					:8;
		/* ----------------------------------ALL[2]---------------------------------- */
		/* Byte16 */
		uint8 MCU_MotorTempFbk					:8;
		/* Byte17 */
		uint8 MCUA_PhaseCurU					:8;
		/* Byte18 */
		uint8 MCUA_PhaseCurV					:8;
		/* Byte19 */
		uint8 MCUA_PhaseCurW					:8;
		/* Byte20 */
		uint8 MCUA_Volt28V_H				    :8;
		/* Byte21 */
		uint8 MCUB_Volt28V_H					:7;
		uint8 MCUA_Volt28V_L				    :1;
		/* Byte22 */
		uint8 Reserve3				     		:6;
		uint8 MCUB_Volt28V_L					:2;
		/* Byte23 */
		uint8 MCUB_PhaseCurU					:8;
		/* ----------------------------------ALL[3]---------------------------------- */
		/* Byte24 */
		uint8 MCUB_PhaseCurV					:8;
		/* Byte25 */
		uint8 MCUB_PhaseCurW					:8;
		/* Byte26 */
		uint8 Rsvd_Byte26						:8;
		/* Byte27 */
		uint8 MCUA_UdcInvalid					:1;
		uint8 MCUB_UdcInvalid					:1;
		uint8 MCU_FrontBearTempInvalid			:1;
		uint8 MCU_BackBearTempInvalid			:1;
		uint8 MCU_SicTempFbkInvalid				:1;
		uint8 MCU_MotorTempFbkInvalid			:1;
		uint8 MCUA_PhaseCurUInvalid				:1;
		uint8 MCUA_PhaseCurVInvalid				:1;
		/* Byte28 */
		uint8 MCUA_PhaseCurWInvalid				:1;
		uint8 MCUB_PhaseCurUInvalid				:1;
		uint8 MCUB_PhaseCurVInvalid				:1;
		uint8 MCUB_PhaseCurWInvalid				:1;
		uint8 Rsvd_Byte28_Bit4_7				:4;
		/* Byte29 */
		uint8 RollingCounter					:8;
		/* Byte30 */
		uint8 CRC_H								:8;
		/* Byte31 */
		uint8 CRC_L								:8;
    }Data;
}CANFD_EXT_TX2_OBJ;

typedef union
{
	uint64 ALL;
	struct
	{
		uint16 Byte01;
		uint16 Byte23;
		uint16 Byte45;
		uint16 Byte67;
	}D16;
    struct
    {
		/* Byte0 */
		uint8 NB_ERR_RX_H					:8;
		/* Byte1 */
		uint8 NB_ERR_RX_L					:8;
		/* Byte2 */
		uint8 NB_ERR_TX_H					:8;
		/* Byte3 */
		uint8 NB_ERR_TX_L					:8;
		/* Byte4 */
		uint8 NB_ERR_ACK_H					:8;
		/* Byte5 */
		uint8 NB_ERR_ACK_L					:8;
		/* Byte6 */
		uint8 NB_BUS_OFF					:8;
		/* Byte7 */
		uint8 REC_STATE						:4;
		uint8 TEC_STATE						:4;
    }Data;
}CANFD_EXT_TX3_OBJ;

typedef union
{
	uint64 ALL[6];
}CANFD_EXT_TX4_OBJ;

typedef union
{
	uint64 ALL[2];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0 */
		uint8	FunctionRequest			:3;
		uint8	SecurityKey				:5;
		/* Byte1 */
		uint8	MCU_LocNum				:4;
		uint8	MCU_AOrB				:1;
		uint8	MCUA_DebugMsgEnable		:1;
		uint8	MCUB_DebugMsgEnable		:1;
		uint8	SilenceAll				:1;
		/* Byte2 */
		uint8	InjectSlowFaultFlag		:1;
		uint8	InjectSlowFaultState	:1;
		uint8	InjectFastFaultFlag		:1;
		uint8	InjectFastFaultState	:1;
		uint8	IsrMsgMode				:1;
		uint8	IsrMsgFunc				:2;
		uint8	Rsvd_Byte2_Bit7			:1;
		/* Byte3 */
		uint8	NVM_Block_Num;
		/* Byte4-5 */
		uint16	Kp;
		/* Byte6-7 */
		uint16	Ki;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8-9 */
		uint16	UPC_ElecZeroComp		:14;
		uint8	UPC_SwapEncoderDir		:1;
		uint8	UPC_SwapPhase			:1;
		/* Byte10-11 */
		uint16	UPC_SlpTheta			:14;
		uint8	UPC_Rsvd_Byte11_Bit6_7	:2;
		/* Byte12-13 */
		uint16	UPC_Rsvd_Byte12_13;
		/* Byte14-15 */
		uint16	UPC_Rsvd_Byte14_15;
    }Data;
}CANFD_EXT_DEBUG_RX0_OBJ;

typedef union
{
	uint64 ALL[8];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0-1 */
		uint16 RDC_Speed;
		/* Byte2-3 */
		uint16 SpeedFilter;
		/* Byte4-5 */
		uint16 CurBus;
		/* Byte6-7 */
		uint16 Vs;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8-9 */
		uint16 Vd;
		/* Byte10-11 */
		uint16 Vq;
		/* Byte12-13 */
		uint16 IsRef;
		/* Byte14-15 */
		uint16 IsFbk;
		/* ----------------------------------ALL[2]---------------------------------- */
		/* Byte16-17 */
		uint16 IdRef;
		/* Byte18-19 */
		uint16 IdFbk;
		/* Byte20-21 */
		uint16 IqRef;
		/* Byte22-23 */
		uint16 IqFbk;
		/* ----------------------------------ALL[3]---------------------------------- */
		/* Byte24-25 */
		uint16 FinalIsRef;
		/* Byte26-27 */
		uint16 IntIsRef;
		/* Byte28-29 */
		uint16 Speed_Out;
		/* Byte30-31 */
		uint16 RampSpeed;
		/* ----------------------------------ALL[4]---------------------------------- */
		/* Byte32-33 */
		uint16 UdComp;
		/* Byte34-35 */
		uint16 UqComp;
		/* Byte36 */
		uint8 LocationNum		:4;
		uint8 WorkModFbk		:4;
		/* Byte37 */
		uint8 IsMasterMcu		:1;
		uint8 MotState			:3;
		uint8 ExtCanMoudle1		:1;
		uint8 ExtCanMoudle2		:1;
		uint8 IntCanMoudle1		:1;
		uint8 IntCanMoudle2		:1;
		/* Byte38 */
		uint8 FaultLevel		:3;
		uint8 Rsvd_Byte38_Bit3_7:5;
		/* Byte39 */
		uint8 CPUTemp;
		/* ----------------------------------ALL[5]---------------------------------- */
		/* Byte40 */
		uint8 MotTemp1;
		/* Byte41 */
		uint8 MotTemp2;
		/* Byte42 */
		uint8 InvTempU1;
		/* Byte43 */
		uint8 InvTempV1;
		/* Byte44 */
		uint8 InvTempW1;
		/* Byte45 */
		uint8 InvTempU2;
		/* Byte46 */
		uint8 InvTempV2;
		/* Byte47 */
		uint8 InvTempW2;
		/* ----------------------------------ALL[6]---------------------------------- */
		/* Byte48 */
		uint8 BearTemp1;
		/* Byte49 */
		uint8 BearTemp2;
		/* Byte50-51 */
		uint16 Volt_Bus;
		/* Byte52-53 */
		uint16 Volt_28;
		/* Byte54 */
		uint8 Volt_05;
		/* Byte55 */
		uint8 RollingCounter;
		/* ----------------------------------ALL[7]---------------------------------- */
		/* Byte56 */
		uint8 AD2S1210_Fault;
		/* Byte57 */
		uint8 U_FaultBit		:1;
		uint8 U_ReadyBit		:1;
		uint8 V_FaultBit		:1;
		uint8 V_ReadyBit		:1;
		uint8 W_FaultBit		:1;
		uint8 W_ReadyBit		:1;
		uint8 FaultPinLot		:1;
		uint8 FaultPinDos		:1;
		/* Byte58 */
		uint8 UnderVoltRecoverNum;
		/* Byte59 */
		uint8 ThetaFixTimes;
		/* Byte60-61 */
		uint16 DeltaTheta;
		/* Byte62-63 */
		uint16 DeltaThetaAvg;
    }Data;
}CANFD_EXT_DEBUG_TX0_OBJ;

typedef union
{
	uint64 ALL[4];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0 */
		uint8 Debug_WarningBitFbk_7_0;
		/* Byte1 */
		uint8 Debug_WarningBitFbk_15_8;
		/* Byte2 */
		uint8 Debug_WarningBitFbk_23_16;
		/* Byte3 */
		uint8 Debug_WarningBitFbk_31_24;
		/* Byte4 */
		uint8 Debug_FaultBitFbk_7_0;
		/* Byte5 */
		uint8 Debug_FaultBitFbk_15_8;
		/* Byte6 */
		uint8 Debug_FaultBitFbk_23_16;
		/* Byte7 */
		uint8 Debug_FaultBitFbk_31_24;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8-9 */
		uint16 SoftwareVersion;
		/* Byte10-11 */
		uint16 ElecZeroComp					:14;
		uint8 SwapEncoderDir				:1;
		uint8 SwapPhase						:1;
		/* Byte12-13 */
		uint16 BusPower;
		/* Byte14-15 */
		uint16 InvPower;
		/* ----------------------------------ALL[2]---------------------------------- */
		/* Byte16-17 */
		uint16 MechPower;
		/* Byte18-19 */
		uint16 PwmPeriodUs					:12;
		uint8  PFCC_Num						:4;
		/* Byte20-21 */
		uint16 Cur_Kp_Now;
		/* Byte22-23 */
		uint16 Cur_Ki_Now;
		/* ----------------------------------ALL[3]---------------------------------- */
		/* Byte24-25 */
		uint16 SlpTheta						:14;
		uint8  SlpState						:2;
		/* Byte26-27 */
		uint16 RDC_Theta					:14;
		uint16 ElecZeroState				:2;
		/* Byte28-29 */
		uint16 Spd_Kp_Now;
		/* Byte30-31 */
		uint16 Spd_Ki_Now;
    }Data;
}CANFD_EXT_DEBUG_TX1_OBJ;

typedef union
{
	uint64 ALL[6];

    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0-1 */
		uint16 RDC_Speed;
		/* Byte2-3 */
		uint16 ThetaRT;
		/* Byte4-5 */
		uint16 Vd;
		/* Byte6-7 */
		uint16 Vq;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8-9 */
		uint16 IdRef;
		/* Byte10-11 */
		uint16 IdFbk;
		/* Byte12-13 */
		uint16 IqRef;
		/* Byte14-15 */
		uint16 IqFbk;
		/* ----------------------------------ALL[2]---------------------------------- */
		/* Byte16-17 */
		uint16 FinalIsRef;
        /* Byte18-19 */
		uint16 IntIsRef;
		/* Byte20-21 */
		uint16 MsgCount;
		/* Byte22 */
		uint8 PwmFreqKHz;
		/* Byte23 */
		uint8 MsgTrigger		:1;
		uint8 IsMasterMcu		:1;
		uint8 IsUseIntIsRef		:1;
		uint8 ThetaFixFlag		:1;
		uint8 WorkModFbk		:4;
		/* ----------------------------------ALL[3]---------------------------------- */
		/* Byte24-25 */
		uint16 DeltaTheta;
		/* Byte26-27 */
		uint16 DeltaThetaAvg;
		/* Byte28 */
		uint8 Debug_FaultBitFbk_7_0;
		/* Byte29 */
		uint8 Debug_FaultBitFbk_15_8;
		/* Byte30 */
		uint8 Debug_FaultBitFbk_23_16;
		/* Byte31 */
		uint8 Debug_FaultBitFbk_31_24;
		/* ----------------------------------ALL[4]---------------------------------- */
		/* Byte32-33 */
		uint16 CurU;
		/* Byte34-35 */
		uint16 CurV;
		/* Byte36-37 */
		uint16 CurW;
		/* Byte38 */
		uint8 RdcBit;
		/* Byte39 */
		uint8 Volt_5V;
		/* ----------------------------------ALL[5]---------------------------------- */
		/* Byte40-41 */
		uint16 Volt_Bus;
		/* Byte42-43 */
		uint16 Volt_28V;
		/* Byte44 */
		uint8 Rsvd_Byte44;
		/* Byte45 */
		uint8 Rsvd_Byte45;
		/* Byte46 */
		uint8 Rsvd_Byte46;
		/* Byte47 */
		uint8 Rsvd_Byte47;
    }Data;
}CANFD_EXT_DEBUG_TXF_OBJ;

/* ---------------------------------------------------------------------------------- */

typedef union
{
        uint64 ALL[2];
    struct
    {
                /* ----------------------------------ALL[0]---------------------------------- */
                /* Byte0 */
                uint8 McuChannel		:1;
                uint8 MstSlaveSts		:1;
                uint8 MstSlaveStsLock	:1;
                uint8 Rsvd_Byte1_Bit3	:1;
                uint8 LocationBit		:4;
                /* Byte1 */
                uint8 SwtRef_RxOrTx		:1;
                uint8 MstSlaveStsFin	:1;
                uint8 Rsvd_Byte1_Bit2_3	:2;
                uint8 SwitchState		:4;
                /* Byte2 */
                uint8 FaultLevel		:3;
                uint8 Rsvd_Byte2_Bit3_7	:5;
                /* Byte3 */
                uint8 WorkMod_RxOrTx	:8;
                /* Byte4 */
                uint8 Is_RxOrTx_H		:8;
                /* Byte5 */
                uint8 Is_RxOrTx_L		:8;
                /* Byte6 */
                uint8 SoftwareVersion_H	:8;
                /* Byte7 */
                uint8 SoftwareVersion_L	:8;
                /* ----------------------------------ALL[1]---------------------------------- */
                /* Byte8 */
                uint8 Rsvd_Byte8		:8;
        		/* Byte9 */
        		uint8 RollingCounter_Ctrl:8;
        		/* Byte10 */
        		uint8 CRC_Ctrl_H		:8;
        		/* Byte11 */
        		uint8 CRC_Ctrl_L		:8;
                /* ----------------------------------UNUSED---------------------------------- */
                /* Byte12 */
                uint8 Rsvd_Byte12		:8;
                /* Byte13 */
                uint8 Rsvd_Byte13		:8;
                /* Byte14 */
                uint8 Rsvd_Byte14		:8;
                /* Byte15 */
                uint8 Rsvd_Byte15		:8;
    }Data;
}CANFD_INT_CTRL_OBJ;

typedef union
{
	uint64 ALL[4];
    struct
    {
		/* ----------------------------------ALL[0]---------------------------------- */
		/* Byte0 */
		uint8 MCUWorkMod_Fbk				:4;
		uint8 CommunicationConfirm_Fbk		:4;
		/* Byte1 */
		uint8 WarningBit_Fbk_31_24			:8;
		/* Byte2 */
		uint8 WarningBit_Fbk_23_16			:8;
		/* Byte3 */
		uint8 WarningBit_Fbk_15_8			:8;
		/* Byte4 */
		uint8 WarningBit_Fbk_7_0			:8;
		/* Byte5 */
		uint8 FaultBit_Fbk_31_24			:8;
		/* Byte6 */
		uint8 FaultBit_Fbk_23_16			:8;
		/* Byte7 */
		uint8 FaultBit_Fbk_15_8				:8;
		/* ----------------------------------ALL[1]---------------------------------- */
		/* Byte8 */
		uint8 FaultBit_Fbk_7_0				:8;
		/* Byte9 */
		uint8 Rsvd_Byte9_Bit0_1				:2;
		uint8 MotRdcErr                     :1;
		uint8 PowerFbk_H					:5;
		/* Byte10 */
		uint8 PowerFbk_L					:8;
		/* Byte11 */
		uint8 Udc_Fbk_H						:8;
		/* Byte12 */
		uint8 Udc_Fbk_L						:8;
		/* Byte13 */
		uint8 FrontBearTemp_Fbk				:8;
		/* Byte14 */
		uint8 BackBearTemp_Fbk				:8;
		/* Byte15 */
		uint8 SicTemp_Fbk					:8;
		/* ----------------------------------ALL[2]---------------------------------- */
		/* Byte16 */
		uint8 MotorTemp_Fbk					:8;
		/* Byte17 */
		uint8 PhaseCurU_Fbk					:8;
		/* Byte18 */
		uint8 PhaseCurV_Fbk					:8;
		/* Byte19 */
		uint8 PhaseCurW_Fbk					:8;
		/* Byte20 */
		uint8 Volt28V_H				        :8;
		/* Byte21 */
		uint8 Volt28V_L				        :1;
		uint8 Rsvd_Byte21_bit0_6			:7;
		/* Byte22 */
		uint8 Is_Fbk_H						:8;
		/* Byte23 */
		uint8 Is_Fbk_L						:8;
		/* ----------------------------------ALL[3]---------------------------------- */
		/* Byte24 */
		uint8 Spd_Fbk_H						:8;
		/* Byte25 */
		uint8 Spd_Fbk_L						:8;
		/* Byte26 */
		uint8 EST_Spd_Fbk_H					:8;
		/* Byte27 */
		uint8 EST_Spd_Fbk_L					:8;
		/* Byte28 */
		uint8 Rsvd_Byte28			        :8;
		/* Byte29 */
		uint8 RollingCounter_State			:8;
		/* Byte30 */
		uint8 CRC_H							:8;
		/* Byte31 */
		uint8 CRC_L							:8;
    }Data;
}CANFD_INT_STATE_OBJ;

typedef union
{
	uint64 ALL[1];
    struct
    {
		/* Byte0 */
		uint8 CMD   				:8;
		/* Byte1 */
		uint8 CTR			        :8;
		/* Byte2 */
		uint8 DATA0			        :8;
		/* Byte3 */
		uint8 DATA1			        :8;
		/* Byte4 */
		uint8 DATA2			        :8;
		/* Byte5 */
		uint8 DATA3			        :8;
		/* Byte6 */
		uint8 DATA4       			:8;
		/* Byte7 */
		uint8 DATA5		    		:8;
    }Data;
}CCP_DATA;

typedef union
{
	uint64 ALL[1];
    struct
    {
		/* Byte0 */
		uint8 ADREE0   				:8;
		/* Byte1 */
		uint8 ADREE1			    :8;
		/* Byte2 */
		uint8 ADREE2			    :8;
		/* Byte3 */
		uint8 ADREE3			    :8;
		/* Byte4 */
		uint8 VALUE0			    :8;
		/* Byte5 */
		uint8 VALUE1			    :8;
		/* Byte6 */
		uint8 VALUE2       			:8;
		/* Byte7 */
		uint8 VALUE3		        :8;
    }Data;
}CCP_REPORT_DATA;

/* Private inline functions --------------------------------------------------*/
/*此处添加向外暴露的内联函数*/

extern uint8 CRC_Length[16];

extern CanVolantData_t CanVolantData;

#ifdef __cplusplus
}
#endif

#endif /* SW_CONFIG_PROTOCOL_PROTOCAL_VOLANT_TYPES_H_ */
