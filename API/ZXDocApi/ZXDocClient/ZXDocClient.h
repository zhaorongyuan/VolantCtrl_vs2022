#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>

// 包含原始 API 头文件
#include "ZXDocComm.h" 

// 自动链接库 (建议在项目属性中配置，这里保留作为备选)
#ifdef _WIN64
#pragma comment(lib, "../../API/ZXDocApi/c/lib/x64/ZXDocComm.lib")
#else
#pragma comment(lib, "../../API/ZXDocApi/c/lib/x86/ZXDocComm.lib")
#endif

/**
 * @class ZXDocClient
 * @brief ZXDoc API 的 C++ 高级封装类
 * * 功能覆盖：
 * 1. 设备连接管理 (Connect/Disconnect)
 * 2. 测量控制 (Start/Stop)
 * 3. 高性能报文收发 (支持 CAN FD BRS 加速、扩展帧、批量发送)
 * 4. 信号读写 (DBC 信号操作)
 */
class ZXDocClient {
public:
    // 定义接收数据的回调函数类型
    // 参数: channel(通道号), id(CAN ID), data(数据负载), isFd(是否CANFD)
    using OnCanMessageReceivedFunc = std::function<void(uint8_t channel, uint32_t id, const std::vector<uint8_t>& data, bool isFd)>;

public:
    ZXDocClient();
    ~ZXDocClient();

    /**
     * @brief 连接到 ZXDoc 软件后台服务
     * @param projectPath 工程文件路径 (.zcp)。传空字符串则保持当前工程不变。
     * @return true 连接成功, false 失败
     */
    bool Connect(const std::string& projectPath = "");

    /**
     * @brief 断开与软件的连接
     */
    void Disconnect();

    /**
     * @brief 启动测量 (硬件上线)
     * 调用此函数后，CAN 卡才真正初始化并接入总线。
     */
    bool Start();

    /**
     * @brief 停止测量 (硬件离线)
     */
    bool Stop();

    /**
     * @brief 发送单帧 CAN/CANFD 报文
     * * @param channel 通道逻辑索引 (通常 0 或 1，取决于映射)
     * @param id CAN ID (支持标准帧 11-bit 或 扩展帧 29-bit)
     * @param data 数据载荷 (最大 64 字节)
     * @param isFd 是否为 CANFD 帧 (true: 开启 BRS 加速, false: 普通 CAN)
     * @param isExtended 是否为扩展帧 (true: 29-bit ID, false: 11-bit ID)
     * @return true 写入缓冲区成功
     */
    bool SendCanMessage(int channel, uint32_t id, const std::vector<uint8_t>& data, bool isFd = false, bool isExtended = false);

    /**
     * @brief 批量发送 CAN/CANFD 报文 (高性能推荐)
     * 一次系统调用发送多帧数据，极大降低 CPU 开销，适合高负载场景。
     * * @param channel 通道逻辑索引
     * @param id CAN ID
     * @param batchData 数据载荷列表 (例如 50 帧数据)
     * @param isFd 是否为 CANFD 帧 (自动开启 BRS)
     * @param isExtended 是否为扩展帧
     * @return true 全部写入成功
     */
    bool SendCanMessagesBatch(int channel, uint32_t id, const std::vector<std::vector<uint8_t>>& batchData, bool isFd, bool isExtended);

    /**
     * @brief 设置 CAN 报文接收回调函数
     * @param callback 用户定义的处理函数 (注意：回调在子线程触发，需注意线程安全)
     */
    void SetCanMessageCallback(OnCanMessageReceivedFunc callback);

    // ========================================================
    // 信号操作 (Signal Access) - 基于加载的 DBC/A2L
    // ========================================================

    // --- 写入 (Set Value) ---
    bool SetSignal(const std::string& sourceId, const std::string& signalId, double value);
    bool SetSignal(const std::string& sourceId, const std::string& signalId, int64_t value);

    // --- 读取 (Get Value) ---
    bool GetSignal(const std::string& sourceId, const std::string& signalId, double& outValue);
    bool GetSignal(const std::string& sourceId, const std::string& signalId, std::string& outValue);

private:
    /**
     * @brief 内部辅助函数：填充 CANFD 原始数据结构
     * 统一处理 BRS、DLC、Payload 拷贝逻辑
     */
    bool SetupCANFDData(ZXDoc_RawData* rawMsg, int channel, uint32_t id, const std::vector<uint8_t>& data, bool isFd, bool isExtended);

    // 内部静态回调函数 (适配 C 接口)
    static void InternalDataSinkCallback(const ZXDoc_RawData* const* datas, uint32_t count, void* context);

    // 实例级数据处理逻辑
    void ProcessIncomingData(const ZXDoc_RawData* rawData);

private:
    ZXDocHandle m_handle;
    OnCanMessageReceivedFunc m_userCallback;
};
