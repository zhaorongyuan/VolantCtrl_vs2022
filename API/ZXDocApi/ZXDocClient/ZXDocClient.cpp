#include "ZXDocClient.h"
#include <cstring> // for memcpy
#include <vector>

// ========================================================
// 构造与析构
// ========================================================

ZXDocClient::ZXDocClient() : m_handle(ZXDOC_INVALID_HANDLE) {
    // 1. 创建句柄
    m_handle = ZXDoc_Create();
    // 默认设置本地服务器
    if (m_handle != ZXDOC_INVALID_HANDLE) {
        ZXDoc_SetServerName(m_handle, "127.0.0.1");
    }
}

ZXDocClient::~ZXDocClient() {
    // 析构时确保断开并释放资源，防止悬挂
    if (m_handle != ZXDOC_INVALID_HANDLE) {
        Disconnect();
        ZXDoc_Free(m_handle);
        m_handle = ZXDOC_INVALID_HANDLE;
    }
}

// ========================================================
// 连接控制
// ========================================================

bool ZXDocClient::Connect(const std::string& projectPath) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;

    const char* path = projectPath.empty() ? nullptr : projectPath.c_str();

    // 连接 (noTrayIcon = False 表示保留托盘图标)
    ZXDocErrorCode err = ZXDoc_Connect(m_handle, path, ZXDoc_False);
    return (err == ZXDOC_E_OK);
}

void ZXDocClient::Disconnect() {
    if (m_handle != ZXDOC_INVALID_HANDLE) {
        ZXDoc_Disonnect(m_handle);
    }
}

bool ZXDocClient::Start() {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;
    // 启动测量 (Hardware Online)
    return (ZXDoc_Meas_Start(m_handle) == ZXDOC_E_OK);
}

bool ZXDocClient::Stop() {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;
    // 停止测量 (Hardware Offline)
    return (ZXDoc_Meas_Stop(m_handle) == ZXDOC_E_OK);
}

// ========================================================
// 报文发送 (核心逻辑)
// ========================================================

/**
 * @brief 私有辅助函数：统一填充 RawData 结构
 * * 关键逻辑：
 * 1. 自动截断超过 64 字节的数据。
 * 2. 自动设置 Direction = Tx。
 * 3. 核心：根据 isFd 设置 BRS 标志位，确保硬件加速生效。
 */
bool ZXDocClient::SetupCANFDData(ZXDoc_RawData* rawMsg, int channel, uint32_t id, const std::vector<uint8_t>& data, bool isFd, bool isExtended) {
    if (!rawMsg) return false;

    ZXDoc_CANFDData* canData = ZXDoc_RawData_Get_CANFDData(rawMsg);
    if (!canData) return false;

    // 通道设置
    rawMsg->channel = static_cast<uint8_t>(channel);

    // ID 与 帧类型
    canData->can_id = id;
    canData->flags.unionVal.EFF = isExtended ? 1 : 0; // 1=扩展帧(29bit), 0=标准帧(11bit)
    canData->flags.unionVal.FDF = isFd ? 1 : 0;       // 1=CANFD, 0=CAN

    // --------------------------------------------------------
    // 【性能关键点】开启 BRS (Bit Rate Switch)
    // 如果是 CAN FD 帧，必须置位 BRS，硬件才会切换到高速波特率 (如 2M/5M)
    // 否则硬件会强制使用仲裁域波特率 (500k) 发送整个数据段。
    // --------------------------------------------------------
    canData->flags.unionVal.BRS = isFd ? 1 : 0;

    canData->flags.unionVal.direction = 1; // 1=发送(Tx), 0=接收(Rx)

    // 数据长度处理
    uint8_t len = (uint8_t)data.size();
    canData->len = len;

    // DLC 映射 (简单映射为长度，底层 API 通常会自动查表映射标准 DLC)
    canData->DLC = len;

    // 内存安全拷贝 (最大 64 字节)
    size_t copySize = len > 64 ? 64 : len;
    if (copySize > 0) {
        std::memcpy(canData->data, data.data(), copySize);
    }

    return true;
}

bool ZXDocClient::SendCanMessage(int channel, uint32_t id, const std::vector<uint8_t>& data, bool isFd, bool isExtended) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;

    // 1. 申请内存
    ZXDoc_RawData* rawMsg = ZXDoc_RawData_New_CANFDData();
    if (!rawMsg) return false;

    // 2. 填充数据 (使用统一辅助函数)
    if (!SetupCANFDData(rawMsg, channel, id, data, isFd, isExtended)) {
        ZXDoc_RawData_Free(rawMsg);
        return false;
    }

    // 3. 发送
    uint32_t sentCount = 1;
    const ZXDoc_RawData* msgs[] = { rawMsg };
    ZXDocErrorCode err = ZXDoc_Chnl_Transmit(m_handle, msgs, &sentCount);

    // 4. 释放内存
    ZXDoc_RawData_Free(rawMsg);

    return (err == ZXDOC_E_OK);
}

bool ZXDocClient::SendCanMessagesBatch(int channel, uint32_t id, const std::vector<std::vector<uint8_t>>& batchData, bool isFd, bool isExtended) {
    if (m_handle == ZXDOC_INVALID_HANDLE || batchData.empty()) return false;

    size_t count = batchData.size();

    // 使用 vector 管理指针，方便后续统一释放
    std::vector<ZXDoc_RawData*> rawMsgPtrs;
    rawMsgPtrs.reserve(count);

    bool prepareSuccess = true;

    // 1. 批量构建
    for (const auto& payload : batchData) {
        ZXDoc_RawData* rawMsg = ZXDoc_RawData_New_CANFDData();
        if (!rawMsg) {
            prepareSuccess = false;
            break;
        }

        // 使用统一逻辑填充
        if (SetupCANFDData(rawMsg, channel, id, payload, isFd, isExtended)) {
            rawMsgPtrs.push_back(rawMsg);
        }
        else {
            ZXDoc_RawData_Free(rawMsg); // 当前这条失败，立即释放
            prepareSuccess = false;
            break;
        }
    }

    // 2. 发送 (仅当构建全部成功时)
    bool sendSuccess = false;
    if (prepareSuccess && !rawMsgPtrs.empty()) {
        uint32_t sentCount = (uint32_t)rawMsgPtrs.size();
        // 核心优化：一次 IPC 调用发送多帧
        ZXDocErrorCode err = ZXDoc_Chnl_Transmit(m_handle, rawMsgPtrs.data(), &sentCount);
        sendSuccess = (err == ZXDOC_E_OK);
    }

    // 3. 统一释放所有已申请的内存
    // 无论发送成功与否，rawMsgPtrs 里存的指针都需要释放
    for (auto* ptr : rawMsgPtrs) {
        ZXDoc_RawData_Free(ptr);
    }

    return (prepareSuccess && sendSuccess);
}

// ========================================================
// 报文接收回调
// ========================================================

void ZXDocClient::SetCanMessageCallback(OnCanMessageReceivedFunc callback) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return;

    m_userCallback = callback;

    if (callback) {
        // 设置无过滤器接收所有数据
        ZXDoc_Chnl_SetDataSinkCallback(m_handle, InternalDataSinkCallback, this, ZXDoc_FilterMode_NoFilter, nullptr, 0);
    }
    else {
        // 取消回调
        ZXDoc_Chnl_SetDataSinkCallback(m_handle, nullptr, nullptr, ZXDoc_FilterMode_NoFilter, nullptr, 0);
    }
}

// 静态跳转函数
void ZXDocClient::InternalDataSinkCallback(const ZXDoc_RawData* const* datas, uint32_t count, void* context) {
    ZXDocClient* client = static_cast<ZXDocClient*>(context);
    if (client) {
        for (uint32_t i = 0; i < count; ++i) {
            client->ProcessIncomingData(datas[i]);
        }
    }
}

// 数据解析逻辑
void ZXDocClient::ProcessIncomingData(const ZXDoc_RawData* rawData) {
    // 仅处理 CAN/CANFD 数据
    if (rawData->type == ZXDoc_RawDataType_CANFD && m_userCallback) {
        ZXDoc_CANFDData* canData = ZXDoc_RawData_Get_CANFDData(rawData);
        if (canData) {
            // 构造 vector 传递给用户
            std::vector<uint8_t> payload(canData->data, canData->data + canData->len);

            m_userCallback(
                rawData->channel,
                canData->can_id,
                payload,
                (canData->flags.unionVal.FDF == 1)
            );
        }
    }
}

// ========================================================
// 信号操作 (Signal API)
// ========================================================

bool ZXDocClient::SetSignal(const std::string& sourceId, const std::string& signalId, double value) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;
    return (ZXDoc_Signal_SetValueDouble(m_handle, sourceId.c_str(), signalId.c_str(), value, -1, -1) == ZXDOC_E_OK);
}

bool ZXDocClient::SetSignal(const std::string& sourceId, const std::string& signalId, int64_t value) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;
    return (ZXDoc_Signal_SetValueInt(m_handle, sourceId.c_str(), signalId.c_str(), value, -1, -1) == ZXDOC_E_OK);
}

bool ZXDocClient::GetSignal(const std::string& sourceId, const std::string& signalId, double& outValue) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;
    return (ZXDoc_Signal_GetValueDouble(m_handle, sourceId.c_str(), signalId.c_str(), &outValue, -1, -1) == ZXDOC_E_OK);
}

bool ZXDocClient::GetSignal(const std::string& sourceId, const std::string& signalId, std::string& outValue) {
    if (m_handle == ZXDOC_INVALID_HANDLE) return false;

    char buffer[256] = { 0 };
    uint32_t size = sizeof(buffer);
    ZXDocErrorCode err = ZXDoc_Signal_GetValueString(m_handle, sourceId.c_str(), signalId.c_str(), buffer, &size, -1, -1);

    if (err == ZXDOC_E_OK) {
        outValue = std::string(buffer);
        return true;
    }
    return false;
}
