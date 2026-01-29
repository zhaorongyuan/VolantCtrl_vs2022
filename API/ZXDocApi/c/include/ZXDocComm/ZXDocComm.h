#ifndef _ZXDOCCOMM_H
#define _ZXDOCCOMM_H

#include "ZXDocCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 回调函数
 */

typedef void (*ZXDoc_OnConnectedFunc)(void* context);
typedef void (*ZXDoc_OnDisconnectedFunc)(void* context);
typedef void (*ZXDoc_OnDataSinkFunc)(const ZXDoc_RawData* const* datas, uint32_t count, void* context);
typedef void (*ZXDoc_OOnMeasStatEventFunc)(uint8_t stat, void* context);
typedef void (*ZXDoc_SignalsObserverFunc)(const ZXDoc_SignalValue* const* values, uint32_t count, void* context);

ZXDOC_EXP const char* ZXDOC_API ZXDoc_BuildTime();
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Version();

/**
 * @brief 创建实例
 * @return 实例句柄。若创建失败返回 ZXDOC_INVALID_HANDLE。
 */
ZXDOC_EXP ZXDocHandle ZXDOC_API ZXDoc_Create();

/**
 * @brief 释放实例
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Free(ZXDocHandle handle);

/**
 * @brief 设置ZXDoc程序的服务器名称/IP地址
 * @param[in] handle 实例的句柄
 * @param[in] serverName 服务器名称/IP地址
 * @return 错误码，成功返回 ZXDOC_E_OK，失败则返回 ZXDOC_E_FAILED。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_SetServerName(ZXDocHandle handle, const char* serverName);

/**
 * @brief 设置与ZXDoc程序连接成功时的回调函数
 * @param[in] handle 实例的句柄
 * @param[in] func 回调函数
 * @param[in] context 回调时传递给func函数的上下文参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_SetOnConnectedCallback(ZXDocHandle handle, ZXDoc_OnConnectedFunc func,
                                                                void* context);

/**
 * @brief 设置与ZXDoc程序连接断开时的回调函数
 * @param[in] handle 实例的句柄
 * @param[in] func 回调函数
 * @param[in] context 回调时传递给func函数的上下文参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_SetOnDisconnectedCallback(ZXDocHandle handle, ZXDoc_OnDisconnectedFunc func,
                                                                   void* context);

/**
 * @brief 连接ZXDoc
 * @param[in] handle 实例的句柄
 * @param[in] projectFilePath 工程文件路径，如果不为空，则在连接后加载该工程
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Connect(ZXDocHandle handle, const char* projectFilePath,
                                                 ZXDoc_Bool noTrayIcon);

/**
 * @brief 与ZXDoc断开连接
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Disonnect(ZXDocHandle handle);

// APP

/**
 * @brief 在ZXDoc中输出一个日志信息
 * @param[in] handle 实例的句柄
 * @param[in] level 日志级别
 * @param[in] msg 日志内容
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_Log(ZXDocHandle handle, ZXDocLogLevel level, const char* msg);

/**
 * @brief 导出ZXDoc的日志到指定路径
 * @param[in] handle 实例的句柄
 * @param[in] logFilePath 导出的文件路径
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_ExportLog(ZXDocHandle handle, const char* logFilePath);

/**
 * @brief 获取当前工程文件的路径
 * @param[in] handle 实例的句柄
 * @param[in] buf 用于保存路径的缓冲区
 * @param[in] bufSize 缓冲区的大小。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_GetCurrentProjectPath(ZXDocHandle handle, char* buf, uint32_t bufSize);

/**
 * @brief 加载工程
 * @param[in] handle 实例的句柄
 * @param[in] projectFilePath 工程文件的路径
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_LoadProject(ZXDocHandle handle, const char* projectFilePath);

/**
 * @brief 添加一个自定义变量
 * @param[in] handle 实例的句柄
 * @param[in] var 自定义变量实例
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_AddUserVariable(ZXDocHandle handle, const ZXDoc_UserVariable* var);

/**
 * @brief 删除一个自定义变量
 * @param[in] handle 实例的句柄
 * @param[in] varName 自定义变量的名称
 * @param[in] group 自定义变量所在分组。如果变量没分组，应给空字符串""。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_DelUserVariable(ZXDocHandle handle, const char* varName,
                                                             const char* group);

/**
 * @brief 给指定的子窗口发送一个命令
 * @param[in] handle 实例的句柄
 * @param[in] subwindowIndex 子窗口的索引
 * @param[in] cmdline 命令行。
 * @param[in] waitForFinished 等待可能长时间执行的命令结束。
 * @param[in,out] response 命令行响应对象。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 *
 * @note 目前支持的命令：
 *  一、UDS诊断窗口
 *    send all; // 发送当前页面的所有诊断数据
 *    send group index=1; // 发送指定索引的分组
 *    send group name="默认分组"; // 发送指定名称的分组，注：如有重名分组，只发送第一个分组
 *    send item group_index=1,index=2;  // 发送指定分组的一条数据
 *    send item group_name="默认分组",index=2;  // 发送指定分组的一条数据
 *    switch page index=1; // 切换页面
 *    stop sending; //停止当前发送
 *    get send_status;  // 获取发送状态
 *
 *  二、ECU刷新窗口
 *    start flash; // 开始刷写
 *    stop flash; // 停止刷写
 *    get flash_status; // 获取刷写状态
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_SubwndCmdExec(ZXDocHandle handle, ZXDoc_Uint subwindowIndex,
                                                           const char* cmdline, ZXDoc_Bool waitForFinished,
                                                           ZCliResponseHandle* response);

/**
 * @brief 显示主窗口
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_ShowMainWindow(ZXDocHandle handle);

/**
 * @brief 隐藏主窗口
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_HideMainWindow(ZXDocHandle handle);

/**
 * @brief 关闭主窗口（退出应用程序）
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_App_CloseMainWindow(ZXDocHandle handle);

// Channel

/**
 * @brief 获取已有通道
 * @param[in] handle 实例的句柄
 * @param[in] busType 通道类型
 * @param[in,out] channels 通道实例对象的数组。
 * @param[in,out] count 通道实例对象的数量。入参值必须为channels的数量，调用成功时会改为实际返回的数量。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Chnl_GetChannels(ZXDocHandle handle, ZXDoc_BusType busType,
                                                          ZXDoc_Channel* channels, uint32_t* count);

/**
 * @brief 设置数据收发回调函数
 * @param[in] handle 实例的句柄
 * @param[in] func 回调函数
 * @param[in] context 回调时传递给func函数的上下文参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Chnl_SetDataSinkCallback(ZXDocHandle handle, ZXDoc_OnDataSinkFunc func,
                                                                  void* context, ZXDoc_FilterMode filterMode,
                                                                  const ZXDoc_DataSinkFilter* filters,
                                                                  uint32_t filterCnt);

/**
 * @brief 发送数据
 * @param[in] handle 实例的句柄
 * @param[in] datas 发送的数据
 * @param[in,out] count ZXDoc_RawData实例对象的数量。入参值必须为 datas 的数量，调用成功时会改为成功发送的数量。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Chnl_Transmit(ZXDocHandle handle, const ZXDoc_RawData* const* datas,
                                                       uint32_t* count);

/**
 * @brief 获取指定通道绑定的数据库
 * @param[in] handle 实例的句柄
 * @param[in] busType 通道类型
 * @param[in] logicalIndex 通道索引
 * @param[in,out] dbIds 用于储存数据库ID的数组。
 * @param[in,out] count 数据库I的数量。入参值必须为 dbIds 的数量，调用成功时会改为实际获取的数量。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Chnl_GetDatabases(ZXDocHandle handle, ZXDoc_BusType busType, int logicalIndex,
                                                           char dbIds[][64], uint32_t* count);

/**
 * @brief 设置指定通道绑定的数据库
 * @param[in] handle 实例的句柄
 * @param[in] busType 通道类型
 * @param[in] logicalIndex 通道索引
 * @param[in] dbIds 数据库ID的数组
 * @param[in] count 数据库ID的数量
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Chnl_SetDatabases(ZXDocHandle handle, ZXDoc_BusType busType, int logicalIndex,
                                                           const char* const* dbIds, uint32_t count);

/* Measurement */

/**
 * @brief 启动测量
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Meas_Start(ZXDocHandle handle);

/**
 * @brief 停止测量
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Meas_Stop(ZXDocHandle handle);

/**
 * @brief 测量是否已启动
 * @param[in] handle 实例的句柄
 * @param[out] isStarted 测量是否已启动，0：未启动 1：已启动
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Meas_IsStarted(ZXDocHandle handle, uint8_t* isStarted);

/**
 * @brief 设置测量状态变更的回调函数
 * @param[in] handle 实例的句柄
 * @param[in] func 回调函数
 * @param[in] context 回调时传递给func函数的上下文参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Meas_SetStatChangedCallback(ZXDocHandle handle,
                                                                     ZXDoc_OOnMeasStatEventFunc func, void* context);

/* Simulation */

/**
 * @brief 启动CAN仿真
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_StartCanSimulation(ZXDocHandle handle);

/**
 * @brief 停止CAN仿真
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_StopCanSimulation(ZXDocHandle handle);

/**
 * @brief 激活CAN仿真发送
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] isActive 是否激活
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_ActiveCanSend(ZXDocHandle handle, int32_t channelIndex,
                                                            const char* databaseId, const char* node,
                                                            const char* message, ZXDoc_Bool isActive);

/**
 * @brief 通过信号ID激活CAN仿真发送
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in] isActive 是否激活
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_ActiveCanSendBySignalId(ZXDocHandle handle, const char* sourceId,
                                                                      const char* signalId, ZXDoc_Bool isActive);

/**
 * @brief 设置CAN发送方式
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] type 发送方式
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_SetCanSendType(ZXDocHandle handle, int32_t channelIndex,
                                                             const char* databaseId, const char* node,
                                                             const char* message, ZXDoc_SimuSendType type);

/**
 * @brief 设置CAN发送周期
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] cycleTime 发送周期(ms)
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_SetCanCycleTime(ZXDocHandle handle, int32_t channelIndex,
                                                              const char* databaseId, const char* node,
                                                              const char* message, uint32_t cycleTime);

/**
 * @brief 设置CAN发送重复次数
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] repetitions 重复次数。小于0表示无限次。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_SetCanSendRepetitions(ZXDocHandle handle, int32_t channelIndex,
                                                                    const char* databaseId, const char* node,
                                                                    const char* message, int64_t repetitions);

/**
 * @brief 设置CAN仿真信号的值
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] signal DBC信号名称
 * @param[in] value 信号值
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_SetCanSignalValue(ZXDocHandle handle, int32_t channelIndex,
                                                                const char* databaseId, const char* node,
                                                                const char* message, const char* signal,
                                                                ZXDoc_Double value);

/**
 * @brief 设置是否使用CANFD报文
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] isCANFD 0时表示CAN，非0则为CANFD。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_SetCanFdType(ZXDocHandle handle, int32_t channelIndex,
                                                           const char* databaseId, const char* node,
                                                           const char* message, ZXDoc_Bool isCANFD);

/**
 * @brief 设置是否使用CANFD加速
 * @param[in] handle 实例的句柄
 * @param[in] channelIndex 通道索引
 * @param[in] databaseId 数据库ID
 * @param[in] node DBC节点名称
 * @param[in] message DBC消息名称
 * @param[in] isBRS 0时表示不加速，非0表示加速。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Simu_SetCanFdBrs(ZXDocHandle handle, int32_t channelIndex,
                                                          const char* databaseId, const char* node, const char* message,
                                                          ZXDoc_Bool isBRS);

/* Signals */

/**
 * @brief 取消订阅信号
 * @param[in] handle 实例的句柄
 * @param[in] ids 信号标识数组
 * @param[in] count 信号标识的数量
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_Unsubscribe(ZXDocHandle handle, const ZXDoc_SignalIdentifier* ids,
                                                            uint32_t count);

/**
 * @brief 订阅信号
 * @param[in] handle 实例的句柄
 * @param[in] ids 信号标识数组
 * @param[in] count 信号标识的数量
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_Subscribe(ZXDocHandle handle, const ZXDoc_SignalIdentifier* ids,
                                                          uint32_t count);

/**
 * @brief 设置信号观察者回调函数
 * @param[in] handle 实例的句柄
 * @param[in] func 回调函数
 * @param[in] context 回调时传递给func函数的上下文参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetSignalsObserver(ZXDocHandle handle, ZXDoc_SignalsObserverFunc func,
                                                                   void* context);
// Value setters

/**
 * @brief 设置信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetValueUint(ZXDocHandle handle, const char* sourceId,
                                                             const char* signalId, ZXDoc_Uint phyValue,
                                                             int32_t rowIndex, int32_t colIndex);

/**
 * @brief 设置信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetValueInt(ZXDocHandle handle, const char* sourceId,
                                                            const char* signalId, ZXDoc_Int phyValue, int32_t rowIndex,
                                                            int32_t colIndex);

/**
 * @brief 设置信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetValueDouble(ZXDocHandle handle, const char* sourceId,
                                                               const char* signalId, double phyValue, int32_t rowIndex,
                                                               int32_t colIndex);

/**
 * @brief 设置信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetValueString(ZXDocHandle handle, const char* sourceId,
                                                               const char* signalId, const char* phyValue,
                                                               int32_t rowIndex, int32_t colIndex);

/**
 * @brief 设置信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetValue(ZXDocHandle handle, const char* sourceId, const char* signalId,
                                                         const PZXDoc_SignalValue phyValue);

/**
 * @brief 设置信号值
 * @param[in] handle 实例的句柄
 * @param[in] phyValues 物理值
 * @param[in] count 数量。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_SetValues(ZXDocHandle handle, const PZXDoc_SignalValue* phyValues,
                                                          uint32_t count);

// Value getters

/**
 * @brief 读取信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetValue(ZXDocHandle handle, const char* sourceId, const char* signalId,
                                                         PZXDoc_SignalValue* phyValue, int32_t rowIndex,
                                                         int32_t colIndex);

/**
 * @brief 读取信号值
 * @param[in] handle 实例的句柄
 * @param[in] phyValues 物理值
 * @param[in] count 数量。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetValues(ZXDocHandle handle, PZXDoc_SignalValue* phyValue,
                                                          uint32_t count);

/**
 * @brief 读取信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetValueUint(ZXDocHandle handle, const char* sourceId,
                                                             const char* signalId, ZXDoc_Uint* phyValue,
                                                             int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetValueInt(ZXDocHandle handle, const char* sourceId,
                                                            const char* signalId, ZXDoc_Int* phyValue, int32_t rowIndex,
                                                            int32_t colIndex);

/**
 * @brief 读取信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetValueDouble(ZXDocHandle handle, const char* sourceId,
                                                               const char* signalId, double* phyValue, int32_t rowIndex,
                                                               int32_t colIndex);

/**
 * @brief 读取信号值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in,out] phyValue 物理值
 * @param[in,out] size 物理值的字节长度。入参值必须为 phyValue 的长度，调用成功时会改为读取到的实际长度。
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetValueString(ZXDocHandle handle, const char* sourceId,
                                                               const char* signalId, char* phyValue, uint32_t* size,
                                                               int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取信号的初始值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetInitValueUint(ZXDocHandle handle, const char* sourceId,
                                                                 const char* signalId, ZXDoc_Uint* phyValue,
                                                                 int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取信号的初始值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetInitValueInt(ZXDocHandle handle, const char* sourceId,
                                                                const char* signalId, ZXDoc_Int* phyValue,
                                                                int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取信号的初始值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetInitValueDouble(ZXDocHandle handle, const char* sourceId,
                                                                   const char* signalId, double* phyValue,
                                                                   int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取信号的初始值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[in,out] phyValue 物理值
 * @param[in,out] size 物理值的字节长度。入参值必须为 phyValue 的长度，调用成功时会改为读取到的实际长度。
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetInitValueString(ZXDocHandle handle, const char* sourceId,
                                                                   const char* signalId, char* phyValue, uint32_t* size,
                                                                   int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取信号的初始值
 * @param[in] handle 实例的句柄
 * @param[in] sourceId 信号源ID
 * @param[in] signalId 信号ID
 * @param[out] phyValue 物理值
 * @param[in] rowIndex 行索引，非数组元素信号应给-1。
 * @param[in] colIndex 列索引，非数组元素信号应给-1。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetInitValue(ZXDocHandle handle, const char* sourceId,
                                                             const char* signalId, PZXDoc_SignalValue* phyValue,
                                                             int32_t rowIndex, int32_t colIndex);

/**
 * @brief 读取所有信号的源和ID
 * @param[in] handle 实例的句柄
 * @param[in,out] pSrcSglHandle 指向ZXDocSourceSignalHandle的指针
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetAllSourceSignals(ZXDocHandle handle,
                                                                    ZXDocSourceSignalHandle* pSrcSglHandle);

/**
 * @brief 读取所有信号的源和ID
 * @param[in] handle 实例的句柄
 * @param[in,out] pSrcSglHandle 指向ZXDocSourceSignalHandle的指针
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Signal_GetSignalInfo(ZXDocHandle handle, const char* sourceId,
                                                              const char* signalId, ZSignalHandle* pSglHandle);

// Diagnostics

/**
 * @brief 创建CAN诊断接口实例
 * @param[in] handle 实例的句柄
 * @param[out] interfaceHandle UDS接口实例句柄
 * @param[in] cfg 诊断配置参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_CreateDoCANInterface(ZXDocHandle handle,
                                                                   PZXDoc_UdsInterfaceHandle interfaceHandle,
                                                                   const PZXDoc_DoCANCfg cfg);

/**
 * @brief 创建LIN诊断接口实例
 * @param[in] handle 实例的句柄
 * @param[out] interfaceHandle UDS接口实例句柄
 * @param[in] cfg 诊断配置参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_CreateDoLINInterface(ZXDocHandle handle,
                                                                   PZXDoc_UdsInterfaceHandle interfaceHandle,
                                                                   const PZXDoc_DoLINCfg cfg);

/**
 * @brief 创建DoIP诊断接口实例
 * @param[in] handle 实例的句柄
 * @param[out] interfaceHandle UDS接口实例句柄
 * @param[in] cfg 诊断配置参数
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_CreateDoIPInterface(ZXDocHandle handle,
                                                                  PZXDoc_UdsInterfaceHandle interfaceHandle,
                                                                  const PZXDoc_DoIPCfg cfg);

/**
 * @brief 释放CAN诊断接口实例
 * @param[in] handle 实例的句柄
 * @param[in] interfaceHandle UDS接口实例句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_FreeUdsInterface(ZXDocHandle handle,
                                                               ZXDoc_UdsInterfaceHandle interfaceHandle);

/**
 * @brief 发送UDS请求
 * @param[in] handle 实例的句柄
 * @param[in] req UDS请求
 * @param[in] requestData UDS请求的数据内容，数据长度应不小于req.dataLen。
 * @param[in, out] rsp UDS响应
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_UdsRequest(ZXDocHandle handle, PZXDoc_UdsRequest req,
                                                         const void* requestData, PZXDoc_UdsResponse rsp);

/**
 * @brief 获取UDS请求的错误信息
 * @param[in] handle 实例的句柄
 * @param[in] interfaceHandle UDS接口实例句柄
 * @param[in] rsp UDS请求的返回对象
 * @param[in, out] str 字符串缓存
 * @param[in] len 字符串缓存长度
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_GetErrorMssage(ZXDocHandle handle,
                                                             ZXDoc_UdsInterfaceHandle interfaceHandle,
                                                             const ZXDoc_UdsResponse* rsp, char* str, uint32_t len);

/**
 * @brief 取消当前UDS请求
 * @param[in] handle 实例的句柄
 * @param[in] interfaceHandle UDS接口实例句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_CancelRequest(ZXDocHandle handle,
                                                            ZXDoc_UdsInterfaceHandle interfaceHandle);

/**
 * @brief 开始发送会话保持报文
 * @param[in] handle 实例的句柄
 * @param[in] address 地址
 * @param[in] interval 发送间隔（ms）
 * @param[in] suppressResponse 是否抑制响应
 * @param[in] doNotSendWhenDataTrans 是否有其它数据发送时不发送会话保持报文
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_SatrtSessionKeep(ZXDocHandle handle,
                                                               ZXDoc_UdsInterfaceHandle interfaceHandle,
                                                               uint32_t address, uint32_t interval,
                                                               ZXDoc_Bool suppressResponse,
                                                               ZXDoc_Bool doNotSendWhenDataTrans);

/**
 * @brief 停止发送会话保持报文
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_StopSessionKeep(ZXDocHandle handle,
                                                              ZXDoc_UdsInterfaceHandle interfaceHandle);

/**
 * @brief 计算安全访问密钥
 * @param[in] handle 实例的句柄
 * @param[in] dllPath 安全访问链接库路径
 * @param[in] securityLevel 安全级别
 * @param[in] seed 种子
 * @param[in] seedSize 种子的长度
 * @param[in] variant 变量参数
 * @param[in,out] key 密钥的缓存
 * @param[in,out] keySize 密钥缓存的大小
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_CalcSecurityKey(ZXDocHandle handle, const char* dllPath,
                                                              uint8_t securityLevel, const uint8_t* seed,
                                                              uint32_t seedSize, const char* variant, uint8_t* key,
                                                              uint32_t* keySize);

ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Diag_LoadFlashFileBlocks(ZXDocHandle handle, const char* flashFilePath,
                                                                  ZXDoc_FlashFileInfo info);

/* Calibration */

/**
 * @brief 连接标定设备
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_Connect(ZXDocHandle handle);

/**
 * @brief 断开标定连接
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_Disonnect(ZXDocHandle handle);

/**
 * @brief 开始获取标定数据
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_StartDataAcquisition(ZXDocHandle handle);

/**
 * @brief 停止获取标定数据
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_StopDataAcquisition(ZXDocHandle handle);

/**
 * @brief 是否需要进行缓存同步
 * @param[in] handle 实例的句柄
 * @param[in, out] result 结果值
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_IsNeedCacheSyncAll(ZXDocHandle handle, ZXDoc_Bool* result);

/**
 * @brief 是否可以同步下载
 * @param[in] handle 实例的句柄
 * @param[in, out] result 结果值
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_CanSyncDownloadAll(ZXDocHandle handle, ZXDoc_Bool* result);

/**
 * @brief 缓存同步上传
 * @param[in] handle 实例的句柄
 * @param[in] asInit 使用初始值
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_SyncUploadAll(ZXDocHandle handle, ZXDoc_Bool asInit);

/**
 * @brief 缓存同步下载
 * @param[in] handle 实例的句柄
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_SyncDownloadAll(ZXDocHandle handle);

/**
 * @brief 切换内存页
 * @param[in] handle 实例的句柄
 * @param[in] type 内存页类型
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_SelectMemoryPageAll(ZXDocHandle handle, ZXDoc_EcuMemPageType type);

/**
 * @brief 是否可以切换内存页
 * @param[in] handle 实例的句柄
 * @param[in, out] result 结果值
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_CanSelectMemoryPage(ZXDocHandle handle, ZXDoc_Bool* result);

/**
 * @brief 是否可以切换内存页
 * @param[in] handle 实例的句柄
 * @param[in, out] type 内存页类型
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_GetCurrentMemoryPage(ZXDocHandle handle, ZXDoc_EcuMemPageType* type);

/**
 * @brief 添加标定信号到测量列表
 * @param[in] handle 实例的句柄
 * @param[in] deviceId 设备ID
 * @param[in] signalId 信号ID
 * @param[in] measEvent 测量模式
 * @param[in] eventChannel 事件通道
 * @param[in] pollingPeriod 轮询周期
 * @param[in] daqCyclic DAQ周期
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_AddSignalToMeasList(ZXDocHandle handle, const char* deviceId,
                                                                  const char* signalId, ZXDoc_MeasEvent measEvent,
                                                                  uint32_t eventChannel, uint32_t pollingPeriod,
                                                                  uint32_t daqCyclic);

/**
 * @brief 从测量列表移除标定信号
 * @param[in] handle 实例的句柄
 * @param[in] deviceId 设备ID
 * @param[in] signalId 信号ID
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Cali_RemoveSignalFromMeasList(ZXDocHandle handle, const char* deviceId,
                                                                       const char* signalId);

/* E2E */

/**
 * @brief 获取一个CRC计算器
 * @param[in] handle 实例的句柄
 * @param[in,out] calcHandle 计算器句柄
 * @param[in] type CRC类型
 * @param[in] parameters CRC参数（type为ZXDoc_CrcCustom时有效）
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_E2E_GetCrcCalculator(ZXDocHandle handle, uint64_t* calcHandle,
                                                              ZXDoc_E2ECrcType type,
                                                              const PZXDoc_E2ECRCCalculatorParameters parameters);

/**
 * @brief 计算CRC
 * @param[in] handle 实例的句柄
 * @param[in] calcHandle 计算器句柄
 * @param[in] data 待计算的数据
 * @param[in] dataLength 数据长度
 * @param[in, out] result CRC结果
 * @param[in] prevResult 上一次计算结果，若没有应给0值。
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_E2E_CrcCalculate(ZXDocHandle handle, uint64_t calcHandle, const void* data,
                                                          uint32_t dataLength, uint64_t* result, uint64_t prevResult);

/* Device */

/**
 * @brief 获取设备
 * @param[in] handle 实例的句柄
 * @param[in] deviceType 设备类型
 * @param[in] deviceInfos 设备数组
 * @param[in, out] count 数组长度
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_Dev_GetDevices(ZXDocHandle handle, ZXDoc_DeviceType deviceType,
                                                        PZXDoc_DeviceInfo deviceInfos, uint32_t* count);

/* Database */

/**
 * @brief 获取所有数据库
 * @param[in] handle 实例的句柄
 * @param[in] msg 数据库结构体数组
 * @param[out] dbcData 数组长度
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_DB_GetDatabases(ZXDocHandle handle, PZXDoc_Database databases,
                                                         uint32_t* count);
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_DB_DbcMessageEncode(ZXDocHandle handle, const char* dbId,
                                                             const PZXDoc_DBCMessageValue msg, PZXDoc_DBCData dbcData,
                                                             ZXDoc_DBCEncodeObject encodeObj);
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_DB_DbcMessageDecode(ZXDocHandle handle, const char* dbId,
                                                             const PZXDoc_DBCData dbcData, PZXDoc_DBCMessageValue msg);

/* Data Recorder */

/**
 * @brief 创建一个信号记录器
 * @param[in] handle 实例的句柄
 * @param[in] cfg 记录器配置
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_RC_AddMeasureDataRecorder(ZXDocHandle handle,
                                                                   ZXDoc_MeasureDataRecorderCfg cfg);

/**
 * @brief 创建一个报文记录器
 * @param[in] handle 实例的句柄
 * @param[in] cfg 记录器配置
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_RC_AddMessageRecorder(ZXDocHandle handle, ZXDoc_MessageRecorderCfg cfg);

/**
 * @brief 删除记录器
 * @param[in] handle 实例的句柄
 * @param[in] recorderName 记录器名称
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_RC_RemoveDataRecorder(ZXDocHandle handle, const char* recorderName);

/**
 * @brief 启动记录器
 * @param[in] handle 实例的句柄
 * @param[in] recorderName 记录器名称
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_RC_StartDataRecorder(ZXDocHandle handle, const char* recorderName);

/**
 * @brief 停止记录器
 * @param[in] handle 实例的句柄
 * @param[in] recorderName 记录器名称
 * @return 错误码。成功返回ZXDOC_E_OK，失败则返回对应的错误码值。
 */
ZXDOC_EXP ZXDocErrorCode ZXDOC_API ZXDoc_RC_StopDataRecorder(ZXDocHandle handle, const char* recorderName);

#ifdef __cplusplus
}
#endif

#endif  // _ZXDOCCOMM_H
