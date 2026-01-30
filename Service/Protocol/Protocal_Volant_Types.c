/*
 * Protocal_Volant_Types.c
 *
 *  Created on: 2024年12月6日
 *      Author: sz-p1159
 */

#include "Protocal_Volant_Types.h"
//#include "MotParm_VOLANT_PHASE12.h"


///*版本号宏定义*/
//#define STRINGIFY(x) #x             //参数转换为字符串
//#define TO_STRING(x) STRINGIFY(x)   //确保宏先展开再转化为字符串
//const uint8_T SantrollSoftwareVersion[12] __attribute__((section(".Santroll_software_version"))) = TO_STRING(SANTROLLVER);
////拼接四个分段，每个分段先转化为字符转在用下划线链接
//#define CONCAT(a, b, c, d) TO_STRING(a)"_"TO_STRING(b)"_"TO_STRING(c)"_"TO_STRING(d)
//#define CONCAT_EXPAND(a, b, c, d) CONCAT(a, b, c, d)
////定义Volant版本号数组
//const uint8_T Volant_SW_VERSION[24] __attribute__((section(".Volant_software_version"))) =
//CONCAT_EXPAND(VOLANT_SW_VERSION_AVIATIONSW,
//              VOLANT_SW_VERSION_POWERMOTOR,
//              VOLANT_SW_VERSION_VOLANTVER,
//              VOLANT_SW_VERSION_INTERNALVER);
//
//const char compile_time[] __attribute__((section(".build.time"))) = __DATE__ " " __TIME__;

CanVolantData_t CanVolantData								=
				{
						.McuC								= 0,
						.IsMasterMCU						= 0,
						.LocNum								= 0,
						.SoftwareVersion					= 0,
						.McuID								= 0,
						.LocID								= 0,
						.IdOffset							= 0,
						.HandshakeCnt						= 0,
						.ArbitrateNum						= 0,
						.ArbitrateFlag						= 0,
						.ArbitrateFault						= 0,
						.NVM_SendFlag						= 0,
						.NVM_SendNum						= 0,
						.NVM_BlockNum						= 0,
						.InjectSlowFaultFlag				= 0,
						.InjectSlowFaultState				= 0,
						.InjectFastFaultFlag				= 0,
						.InjectFastFaultState				= 0,
						.IsrMsgMode							= 0,
						.IsrMsgFunc							= 0,
						.Heart								= 0,
						.PFCC_PrimaryChannelNum				= 0xFF,
						.Kp									= 0,
						.Ki									= 0,
						.CanVolantArbitrateData				=
						{
							.McuBit							= 0,
							.MasterSlaveBit					= 0,
							.LocationBit					= 0,
							.HandshakeBit					= 0,
							.SoftwareVersion				= 0,
							.McuBitFbk						= 0,
							.MasterSlaveBitFbk				= 0,
							.LocationBitFbk					= 0,
							.HandshakeBitFbk				= 0,
							.SoftwareVersionFbk				= 0,
							.RollingCounterFbk				= 0,
						},
						.CanVolantModuleData_1				=
						{
							.MsgAB_Flag						= 0,
							.EXT_RollingCounter_N			= 0,
							.EXT_RollingCounter_F			= 0,
							.INT_RollingCounter_C			= 0,
							.INT_RollingCounter_S			= 0,
							.EXT_IsPrimaryModule			= 0,
							.INT_IsPrimaryModule			= 0,
							.EXT_RollingCounterFbk			= 0,
							.INT_RollingCounter_Ctrl_Fbk	= 0,
							.INT_RollingCounter_State_Fbk	= 0,
							.EXT_CRC_PFCC1_Fault			= 0,
							.EXT_CRC_PFCC2_Fault			= 0,
							.EXT_CRC_PFCC3_Fault			= 0,
							.INT_CRC_Ctrl_Fault				= 0,
							.INT_CRC_State_Fault			= 0,
						},
						.CanVolantModuleData_2				=
						{
							.MsgAB_Flag	= 0,
							.EXT_RollingCounter_N			= 0,
							.EXT_RollingCounter_F			= 0,
							.INT_RollingCounter_C			= 0,
							.INT_RollingCounter_S			= 0,
							.EXT_IsPrimaryModule			= 0,
							.INT_IsPrimaryModule			= 0,
							.EXT_RollingCounterFbk			= 0,
							.INT_RollingCounter_Ctrl_Fbk	= 0,
							.INT_RollingCounter_State_Fbk	= 0,
							.EXT_CRC_PFCC1_Fault			= 0,
							.EXT_CRC_PFCC2_Fault			= 0,
							.EXT_CRC_PFCC3_Fault			= 0,
							.INT_CRC_Ctrl_Fault				= 0,
							.INT_CRC_State_Fault			= 0,
							.PFCC_PrimaryChannelAvailable	= 0,
						},
						.CanDebugData						=
						{
							.FunctionRequest				= 0,
							.SecurityKey					= 0,
							.MCU_LocNum						= 0,
							.MCU_AOrB						= 0,
							.MCUA_DebugMsgEnable			= 0,
							.MCUB_DebugMsgEnable			= 0,
							.SilenceAll						= 0,
							.InjectSlowFaultFlag			= 0,
							.InjectSlowFaultState			= 0,
							.InjectFastFaultFlag			= 0,
							.InjectFastFaultState			= 0,
							.IsrMsgMode						= 0,
							.IsrMsgFunc						= 0,
							.NVM_Block_Num					= 0,
							.Kp								= 0,
							.Ki								= 0,
							.ElecZeroComp					= 0,
							.SwapEncoderDir					= 0,
							.SwapPhase						= 0,
							.SlpTheta						= 0,
						},
				};
