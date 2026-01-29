#ifndef _ZXDOC_COMMON_H
#define _ZXDOC_COMMON_H

#include <stdint.h>

#ifdef _WIN32

#define ZXDOC_API __stdcall

#ifdef __MINGW32__
#define ZXDOC_EXP
#else

#ifdef ZXDOC_STATIC_LIB
#define ZXDOC_EXP
#else
#ifdef ZXDOC_EXPORTS
#define ZXDOC_EXP __declspec(dllexport)
#else
#define ZXDOC_EXP __declspec(dllimport)
#endif
#endif

#endif  // __MINGW32__

#else  // _WIN32 else

#define ZXDOC_API
#define ZXDOC_EXP

#endif  // _WIN32

#pragma pack(push, 1)

typedef uint64_t ZXDocHandle;                 // 实例句柄
#define ZXDOC_INVALID_HANDLE ZXDocHandle(-1)  // 无效句柄值

typedef int64_t ZXDoc_Int;
typedef uint64_t ZXDoc_Uint;
typedef double ZXDoc_Double;
typedef uint8_t ZXDoc_Bool;
#define ZXDoc_True 1
#define ZXDoc_False 0

typedef uint32_t ZXDocErrorCode;  // 错误码
enum ZXDoc_ErrorCodeEnum {
    ZXDOC_E_OK,                 // 正确，无错误
    ZXDOC_E_FAILED,             // 失败
    ZXDOC_E_INVALID_HANDLE,     // 句柄无效
    ZXDOC_E_NULL_POINTER,       // 空指针
    ZXDOC_E_INVALID_DATA_TYPE,  // 数据类型无效
    ZXDOC_E_INVALID_PARAM,      // 参数无效
    ZXDOC_E_BUFFER_IS_TO_SMALL  // 缓存过小
};

/* log levels */
typedef uint8_t ZXDocLogLevel;
#define ZXDOC_LOG_LVL_DBG 0
#define ZXDOC_LOG_LVL_INFO 1
#define ZXDOC_LOG_LVL_WARNING 2
#define ZXDOC_LOG_LVL_ERR 3

// CAN/CANFD数据
typedef struct _ZXDoc_CANFDData {
    uint32_t can_id;
    union {
        struct {
            uint32_t EFF : 1;           // 0:标准帧, 1:扩展帧
            uint32_t FDF : 1;           // 0:CAN帧, 1:CANFD帧
            uint32_t RTR : 1;           // CAN帧有效 0:数据帧, 1:远程帧
            uint32_t BRS : 1;           // CANFD帧有效
            uint32_t ESI : 1;           // CANFD帧有效
            uint32_t direction : 1;     // 0:接收, 1:发送
            uint32_t txDelay : 2;       // 队列发送延时, 发送有效. 0:无发送延时,
                                        // 1:发送延时单位ms, 2:发送延时单位100us.
                                        // 启用队列发送延时，延时时间存放在timeStamp字段
            uint32_t transmitType : 4;  // 发送类型, 发送有效. 0:正常发送,
                                        // 1:单次发送, 2:自发自收, 3:单次自发自收.
                                        // 所有设备支持正常发送，其他类型请参考具体使用手册
            uint32_t reserved : 20;     // 保留
        } unionVal;
        uint32_t rawVal;  // 帧标志位raw数据
    } flags;              // CAN/CANFD帧标志位
    uint8_t data[64] /* __attribute__((aligned(8)))*/;
    uint8_t len; /* frame payload length in byte */
    uint8_t DLC;
    uint8_t __res0; /* reserved / padding */
    uint8_t __res1; /* reserved / padding */
} ZXDoc_CANFDData, *PZXDoc_CANFDData;

// 错误数据
typedef struct _ZXDoc_CANFDErrorData {
    uint8_t errType;     // 错误类型, 参考eZCANErrorDEF中 总线错误类型 部分值定义
    uint8_t errSubType;  // 错误子类型, 参考eZCANErrorDEF中 总线错误子类型
    // 部分值定义
    uint8_t nodeState;   // 节点状态, 参考eZCANErrorDEF中 节点状态 部分值定义
    uint8_t rxErrCount;  // 接收错误计数
    uint8_t txErrCount;  // 发送错误计数
    uint8_t errData;     // 错误数据, 和当前错误类型以及错误子类型定义的具体错误相关,
    // 具体请参考使用手册
    uint8_t reserved[2];  // 保留
} ZXDoc_CANFDErrorData, *PZXDoc_CANFDErrorData;

// GPS数据
typedef struct _ZXDoc_GPSData {
    struct {
        uint16_t year;    // 年
        uint16_t mon;     // 月
        uint16_t day;     // 日
        uint16_t hour;    // 时
        uint16_t min;     // 分
        uint16_t sec;     // 秒
        uint16_t milsec;  // 毫秒
    } time;               // UTC时间
    union {
        struct {
            uint16_t timeValid : 1;         // 时间数据是否有效
            uint16_t latlongValid : 1;      // 经纬度数据是否有效
            uint16_t altitudeValid : 1;     // 海拔数据是否有效
            uint16_t speedValid : 1;        // 速度数据是否有效
            uint16_t courseAngleValid : 1;  // 航向角数据是否有效
            uint16_t reserved : 13;         // 保留
        } unionVal;
        uint16_t rawVal;
    } flags;             // 标志信息
    double latitude;     // 纬度 正数表示北纬, 负数表示南纬
    double longitude;    // 经度 正数表示东经, 负数表示西经
    double altitude;     // 海拔 单位: 米
    double speed;        // 速度 单位: km/h
    double courseAngle;  // 航向角
} ZXDoc_GPSData, *PZXDoc_GPSData;

// LIN校验和类型
enum ZXDoc_LINChecksumType {
    LINChksum_Classic = 1,   // 经典
    LINChksum_Enhanced = 2,  // 增强
};

enum ZXDoc_LINFrameType { HeaderAndResponse = 0, HeaderOnly = 1, ResponseOnly = 2 };

typedef struct _ZXDoc_LINData {
    union {
        struct {
            uint8_t ID : 6;      // 帧ID
            uint8_t Parity : 2;  // 帧ID校验
        } unionVal;
        uint8_t rawVal;  // 受保护的ID原始值
    } PID;               // 受保护的ID
    struct {
        uint64_t timeStamp;        // 设备接收到报文的时间戳，单位微秒(us)
        uint8_t dataLen;           // 数据长度
        uint8_t dir;               // 传输方向，0-接收 1-发送
        uint8_t chkSum;            // 数据校验, 部分设备不支持校验数据的获取
        uint8_t reserved[4];       // 保留
        uint8_t data[64];          // 数据
    } rxData;                      // 仅DataType=1时有效
    ZXDoc_LINFrameType frameType;  // lin数据结构体传输类型
    ZXDoc_LINChecksumType checksumType;
} ZXDoc_LINData, *PZXDoc_LINData;

typedef struct _ZXDoc_LINErrorData {
    union {
        struct {
            uint8_t ID : 6;      // 帧ID
            uint8_t Parity : 2;  // 帧ID校验
        } unionVal;
        uint8_t rawVal;  // 受保护的ID原始值
    } PID;               // 受保护的ID

    uint8_t dataLen;      // 数据长度
    uint8_t dir;          // 传输方向，0-接收 1-发送
    uint8_t errorState;   // 错误状态
    uint8_t errorReason;  // 错误原因
    uint8_t chksum;       // 校验和
    uint8_t reserved[2];  // 保留
    uint8_t data[8];      // 数据
} ZXDoc_LINErrorData, *PZXDoc_LINErrorData;

enum ZXDoc_LINEventType { ZXDoc_LINEventType_Unknown = 0, ZXDoc_LINEventType_WakeUp = 1 };

typedef struct _ZXDoc_LINEventData {
    ZXDoc_LINEventType type;
    uint8_t reserved[7];
} ZXDoc_LINEventData, *PZXDoc_LINEventData;

// 总线利用率数据
typedef struct _ZXDoc_BusUsageData {
    uint64_t duration;    // 时长，单位us
    uint16_t busUsage;    // 总线利用率(%)，取值0~10000，如8050表示80.50%
    uint32_t frameCount;  // 帧数量
} ZXDoc_BusUsageData, *PZXDoc_BusUsageData;

enum ZXDoc_EthernetType {
    ZXDoc_EthernetType_IP = 0x0800,
    ZXDoc_EthernetType_ARP = 0x0806,
    ZXDoc_EthernetType_ETHBRIDGE = 0x6558,
    ZXDoc_EthernetType_REVARP = 0x8035,
    ZXDoc_EthernetType_AT = 0x809B,
    ZXDoc_EthernetType_AARP = 0x80F3,
    ZXDoc_EthernetType_VLAN = 0x8100,
    ZXDoc_EthernetType_IPX = 0x8137,
    ZXDoc_EthernetType_IPV6 = 0x86dd,
    ZXDoc_EthernetType_LOOPBACK = 0x9000,
    ZXDoc_EthernetType_PPPOED = 0x8863,
    ZXDoc_EthernetType_PPPOES = 0x8864,
    ZXDoc_EthernetType_MPLS = 0x8847,
    ZXDoc_EthernetType_PPP = 0x880B,
    ZXDoc_EthernetType_ROCEV1 = 0x8915,
    ZXDoc_EthernetType_IEEE_802_1AD = 0x88A8,
    ZXDoc_EthernetType_WAKE_ON_LAN = 0x0842
};

enum ZXDoc_EthernetFamily {
    ZXDoc_EthernetFamily_INET = 2,
    ZXDoc_EthernetFamily_NS = 6,
    ZXDoc_EthernetFamily_ISO = 7,
    ZXDoc_EthernetFamily_APPLETALK = 16,
    ZXDoc_EthernetFamily_IPX = 23,
    ZXDoc_EthernetFamily_INET6_BSD = 24,
    ZXDoc_EthernetFamily_INET6_FREEBSD = 28,
    ZXDoc_EthernetFamily_INET6_DARWIN = 30
};

enum ZXDoc_EthernetDataType {
    ZXDoc_EthernetDataType_ETHERNET = 1,
    ZXDoc_EthernetDataType_ETHERNET_DOT_3 = 2,
    ZXDoc_EthernetDataType_LOOPBACK = 3
};

// 以太网数据
typedef struct _ZXDoc_EthernetData {
    union Header {
        struct Ethernet {
            /** Destination MAC */
            uint8_t dstMac[6];
            /** Source MAC */
            uint8_t srcMac[6];
            /** EtherType */
            uint16_t etherType;  // ZXDoc_EthernetType
        } ethernet;
        struct EthernetDot3 {
            /** Destination MAC */
            uint8_t dstMac[6];
            /** Source MAC */
            uint8_t srcMac[6];
            uint16_t length;
        } ethernetDot3;
        struct Loopback {
            uint32_t family;  // ZXDoc_EthernetFamily
        } loopback;
    } header;
    uint8_t isLocal : 1;
    uint8_t type : 2;  // ZXDoc_EthernetDataType
    uint8_t reserved : 5;

    uint16_t length;
    uint8_t data[1];  // The first byte of data
} ZXDoc_EthernetData, *PZXDoc_EthernetData;

enum ZXDoc_RawDataType {
    ZXDoc_RawDataType_Unknown = 0,
    ZXDoc_RawDataType_CANFD = 1,       // ZXDoc_CANFDData
    ZXDoc_RawDataType_CANFDError = 2,  // ZXDoc_CANFDErrorData
    ZXDoc_RawDataType_Event = 3,       // Not implemented
    ZXDoc_RawDataType_GPS = 4,         // ZXDoc_GPSData
    ZXDoc_RawDataType_LIN = 5,         // ZXDoc_LINData
    ZXDoc_RawDataType_LINError = 6,    // ZXDoc_LINErrorData
    ZXDoc_RawDataType_BusUsage = 7,    // ZXDoc_BusUsageData
    ZXDoc_RawDataType_LINEvent = 8,    // Not implemented
    ZXDoc_RawDataType_Ethernet = 9     // ZXDoc_EthernetData
};

// 合并接收数据数据结构，支持CAN/CANFD/LIN/GPS/错误等不同类型数据
typedef struct _ZXDoc_RawData {
    uint64_t number;             // 数据编号
    uint64_t absoluteTimeStamp;  // 绝对时间戳,单位微秒(us)
    int64_t relativeTimeStamp;   // 相对时间戳,单位微秒(us)
    uint8_t channel;             // 数据通道
    ZXDoc_RawDataType type;
    uint8_t data[1];  // The first byte of the data
} ZXDoc_RawData, *PZXDoc_RawData;

enum ZXDoc_UserVariableType {
    ZXDoc_VarType_Undefined = 0,
    ZXDoc_VarType_Int = 1,
    ZXDoc_VarType_Uint = 2,
    ZXDoc_VarType_Double = 4,
    ZXDoc_VarType_String = 5
};

typedef struct _ZXDoc_UserVariable {
    const char* name;
    const char* group;
    ZXDoc_UserVariableType valueType;
    const char* unit;
    const char* initValue;
    const char* minValue;
    const char* maxValue;
    const char* comment;
} ZXDoc_UserVariable, *PZXDoc_UserVariable;

enum ZXDoc_BusType {
    ZXDoc_BusType_Unknown = 0,
    ZXDoc_BusType_CAN = 1,
    ZXDoc_BusType_LIN = 2,
    ZXDoc_BusType_Ethernet = 3
};

typedef struct _ZXDoc_Channel {
    ZXDoc_BusType busType;
    int32_t logicalIndex;
    int32_t physicalIndex;
    uint8_t enabled;
    uint8_t activated;
} ZXDoc_Channel, *PZXDoc_Channel;

enum ZXDoc_SignalValueType {
    ZXDOC_SGL_VALUE_TYPE_INVALID,
    ZXDOC_SGL_VALUE_TYPE_U8,
    ZXDOC_SGL_VALUE_TYPE_U16,
    ZXDOC_SGL_VALUE_TYPE_U32,
    ZXDOC_SGL_VALUE_TYPE_U64,
    ZXDOC_SGL_VALUE_TYPE_I8,
    ZXDOC_SGL_VALUE_TYPE_I16,
    ZXDOC_SGL_VALUE_TYPE_I32,
    ZXDOC_SGL_VALUE_TYPE_I64,
    ZXDOC_SGL_VALUE_TYPE_FLOAT,
    ZXDOC_SGL_VALUE_TYPE_DOUBLE,
    ZXDOC_SGL_VALUE_TYPE_STR,
    ZXDOC_SGL_VALUE_TYPE_ARRAY
};

typedef struct _ZXDoc_SignalVariant ZXDoc_SignalVariant, *PZXDoc_SignalVariant;

/**
 * @brief 信号值类型
 */
typedef struct _ZXDoc_SignalVariant {
    ZXDoc_SignalValueType type;  // 值类型
    union {
        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;
        float f;
        double db;
        char* str;
        PZXDoc_SignalVariant** arr; /* arr[row][col] */
    };
    int32_t length;  // length in bytes
} ZXDoc_SignalVariant, *PZXDoc_SignalVariant;

/**
 * @brief 信号值
 */
typedef struct _ZXDoc_SignalValue {
    const char* sourceId;           // 信号源ID
    const char* signalId;           // 信号ID
    uint64_t timestamp;             // 时间戳
    uint64_t frameNumber;           // 帧序号
    PZXDoc_SignalVariant rawValue;  // 原始值
    PZXDoc_SignalVariant phyValue;  // 物理值
    int32_t rowIndex;               // 行索引，信号类型为数组时有效
    int32_t colIndex;               // 列索引，信号类型为数组时有效
} ZXDoc_SignalValue, *PZXDoc_SignalValue;

/**
 * @brief 信号标识
 */
typedef struct _ZXDoc_SignalIdentifier {
    const char* sourceId;  // 信号源ID
    const char* signalId;  // 信号ID
} ZXDoc_SignalIdentifier, *PZXDoc_SignalIdentifier;

typedef int32_t ZXDoc_UdsInterfaceHandle, *PZXDoc_UdsInterfaceHandle;

enum ZXDoc_CANFrameType {
    ZXDOC_CAN_FRAME_TYPE_CAN = 0,       // CAN 帧
    ZXDOC_CAN_FRAME_TYPE_CANFD = 1,     // CAN FD 帧
    ZXDOC_CAN_FRAME_TYPE_CANFD_BRS = 2  // CAN FD 加速帧
};

enum ZXDoc_CANTpVersion { ZXDOC_CAN_TP_ISO15765_2_2004 = 0, ZXDOC_CAN_TP_ISO15765_2_2016 = 1 };

typedef struct _ZXDoc_DoCANCfg {
    uint32_t channelIndex;               // 通道索引
    ZXDoc_CANFrameType frameType;        // CAN帧类型
    ZXDoc_CANTpVersion protocolVersion;  // 协议版本
    uint8_t fillByte;                    // 填充字节
    ZXDoc_Bool isfillByte;               // 是否填充字节
    uint16_t p2Timeout;                  // P2超时
    uint16_t p2xTimeout;                 // P2*超时
    ZXDoc_Bool isModifyEcuSTmin;         // 是否替换远程STmin
    uint8_t remoteSTmin;                 // 远程STmin
    uint16_t fcTimeout;                  // 流控响应超时(ms)
} ZXDoc_DoCANCfg, *PZXDoc_DoCANCfg;

typedef struct _ZXDoc_DoLINCfg {
    uint32_t channelIndex;        // 通道索引
    uint8_t fillByte;             // 填充字节
    ZXDoc_Bool isfillByte;        // 是否填充字节
    uint16_t p2Timeout;           // P2超时
    uint16_t p2xTimeout;          // P2*超时
    ZXDoc_Bool isModifyEcuSTmin;  // 是否替换远程STmin
    uint8_t remoteSTmin;          // 远程STmin
} ZXDoc_DoLINCfg, *PZXDoc_DoLINCfg;

enum ZXDoc_DoipProtocolVersion {
    DOIP_TP_ISO_13400_2_2010 = 1,
    ZXDOC_DOIP_TP_ISO_13400_2_2012 = 2,
    ZXDOC_DOIP_TP_ISO_13400_2_2019 = 3,
    ZXDOC_DOIP_TP_ISO_13400_2_2019_AMD_1 = 4
};

enum ZXDoc_DoipRoutingActivationType {
    ZXDOC_DOIP_ACTIVATION_DEFAULT = 0x00,          // 默认激活类型
    ZXDOC_DOIP_ACTIVATION_WWH_OBD = 0x01,          // WWH-OBD
    ZXDOC_DOIP_ACTIVATION_CENTRAL_SECURITY = 0xE0  // 安全模式
};

typedef struct _ZXDoc_DoIPCfg {
    const char* vehicleIp;                                  // DoIP实体的IP地址
    const char* localIp;                                    // 本地IP地址，0.0.0.0表示使用任意地址。
    uint16_t localPort;                                     // 本地端口，0表示任意端口。
    ZXDoc_DoipProtocolVersion protocolVersion;              // 协议版本
    uint16_t testerAddress;                                 // 测试仪地址（源逻辑地址）
    ZXDoc_DoipRoutingActivationType routingActivationType;  //  路由激活类型
    ZXDoc_Bool withOEMSpecificData;                         // 是否有OEM特定的数据
    uint8_t oemSpecificData[4];                             // OEM特定的数据
    uint32_t aliveCheckMaxIdleTimeMs;        // 主动保活的周期，单位为毫秒，0表示不主动保活
    ZXDoc_Bool isResponseAliveCheckEnabled;  // 是否响应存活检查
    uint16_t p2Timeout;                      // P2超时(ms)
    uint16_t p2xTimeout;                     // P2*超时(ms)
    ZXDoc_Bool waitForACK;                   // 每次请求是否等待ACK
    uint32_t ackTimeoutMs;                   // 等待ACK的超时时间
    uint16_t connectTimeout;
} ZXDoc_DoIPCfg, *PZXDoc_DoIPCfg;

typedef struct _ZXDoc_UdsRequest {
    ZXDoc_UdsInterfaceHandle handle = 0;  // UDS接口句柄
    uint32_t reqAddr;                     // 请求地址
    uint32_t rspAddr;                     // 响应地址
    ZXDoc_Bool extend;                    // 扩展帧
    ZXDoc_Bool suppressResponse;          // 1:抑制响应
    uint8_t sid;                          // 请求服务id
    uint32_t dataLen;                     // 参数数组的长度
} ZXDoc_UdsRequest, *PZXDoc_UdsRequest;

enum ZXDoc_UdsResponseStatus {
    ZXDoc_UdsResp_Ok = 0,                // 成功
    ZXDoc_UdsResp_Canceled = 1,          // 取消操作
    ZXDoc_UdsResp_SuppressResponse = 2,  // 抑制响应
    ZXDoc_UdsResp_Failed = 3,            // 失败
    ZXDoc_UdsResp_Unknown = 0xFF
};

enum ZXDoc_UdsResponseType {
    ZXDoc_UdsRespType_Negative = 0,  // 消极响应
    ZXDoc_UdsRespType_Positive = 1,  // 积极响应
    ZXDoc_UdsRespType_Unknown = 0xFF
};

typedef struct _ZXDoc_UdsResponse {
    ZXDoc_UdsResponseStatus status;      // 响应状态
    ZXDoc_UdsResponseType responseType;  // 响应类型
    uint32_t errorCode;                  // 错误码
    uint8_t sid;                         // 响应服务id
    uint8_t* data;                       // 响应数据缓冲区
    uint32_t dataLen;                    // 参数数组的长度
    uint8_t NRC;                         // 消极响应错误码
} ZXDoc_UdsResponse, *PZXDoc_UdsResponse;

enum ZXDoc_MeasEvent {
    ZXDoc_Polling = 1,  // 轮询获取
    ZXDoc_DaqEvent,     // ECU按指定DAQ事件上送
    ZXDoc_DaqCyclic,    // ECU按DAQ事件的整数倍周期上送, 周期小于1ms的事件不支持Cyclic模式
    ZXDoc_OnInput,      // 依赖输入信号，自己不轮询
};

enum ZXDoc_E2ECrcType {
    ZXDoc_Crc8,
    ZXDoc_Crc8Sae,
    ZXDoc_Crc8H2f,
    ZXDoc_Crc16,
    ZXDoc_Crc16Ccitt,
    ZXDoc_Crc16CcittFalse,
    ZXDoc_Crc32,
    ZXDoc_Crc32P4,
    ZXDoc_Crc64Ecma,
    ZXDoc_CrcCustom
};

typedef struct _ZXDoc_E2ECRCCalculatorParameters {
    uint8_t width;  // 8, 16, 32, 64
    uint64_t polynomial;
    uint64_t initialValue;
    uint64_t xorValue;
    ZXDoc_Bool reflectInput;
    ZXDoc_Bool reflectOutput;
} ZXDoc_E2ECRCCalculatorParameters, *PZXDoc_E2ECRCCalculatorParameters;

// 仿真信号发送类型
enum ZXDoc_SimuSendType {
    ZXDoc_Cycle = 0,     // 循环发送
    ZXDoc_OnChange = 1,  // 当信号值变更时
    ZXDoc_OnWrite = 2    // 当信号值被设置时（即使是相同值）
};

enum ZXDoc_DeviceType {
    ZXDoc_CcpDevice = 0,            // CCP协议的ECU
    ZXDoc_XcpDevice = 1,            // XCP协议的ECU
    ZXDoc_DiagnosticDevice = 2,     // 诊断
    ZXDoc_CanfdDevice = 3,          // CAN或CANFD总线监测
    ZXDoc_LinDevice = 4,            // LIN总线监测
    ZXDoc_OBDDiagnosticDevice = 5,  // OBD诊断
    ZXDoc_AcquistionDevice = 6,     // 传感器设备采集

    ZXDoc_UnknownDevice = 0xff
};

typedef struct _ZXDoc_DeviceInfo {
    char id[64];
    ZXDoc_DeviceType type;
    char name[128];
    ZXDoc_BusType busType;
    int32_t logicalChannel;
    ZXDoc_Bool enabled;
    char databaseId[64];
    char databaseName[128];
} ZXDoc_DeviceInfo, *PZXDoc_DeviceInfo;

typedef struct _ZXDoc_DBCData {
    uint32_t id;       // ID，带扩展帧标记位
    uint32_t length;   // 长度
    uint8_t data[64];  // 数据
} ZXDoc_DBCData, *PZXDoc_DBCData;

enum ZXDoc_DBCSignalValueType {
    ZXDoc_DBCSignalValue_unknown,
    ZXDoc_DBCSignalValue_int,
    ZXDoc_DBCSignalValue_uint,
    ZXDoc_DBCSignalValue_float,
    ZXDoc_DBCSignalValue_double
};

enum ZXDoc_DBCEncodeObject { ZXDoc_DBCEncodeObject_raw = 1, ZXDoc_DBCEncodeObject_phy = 2 };

typedef struct _ZXDoc_DBCSignalValue {
    char name[128];
    union {
        uint64_t u;
        int64_t n;
        float f;
        double d;
    } rawValue;
    ZXDoc_DBCSignalValueType rawValueType;
    double phyValue;
} ZXDoc_DBCSignalValue, *PZXDoc_DBCSignalValue;

typedef struct _ZXDoc_DBCMessageValue {
    uint32_t id;  // ID，带扩展帧标记位
    char name[128];
    ZXDoc_Bool isFd;
    ZXDoc_Bool isJ1939Frame;  // 是否为J1939帧类型
    PZXDoc_DBCSignalValue* signalValues;
} ZXDoc_DBCMessageValue, *PZXDoc_DBCMessageValue;

enum ZXDoc_DBType {
    ZXDoc_DBType_UNKNOWN = 0x00,
    ZXDoc_DBType_DBC = 0x01,
    ZXDoc_DBType_ODX = 0x02,
    ZXDoc_DBType_A2L = 0x04,
    ZXDoc_DBType_LDF = 0x08,
    ZXDoc_DBType_SysVar = 0x10,
    ZXDoc_DBType_FuncVar = 0x20,
    ZXDoc_DBType_UserVar = 0x40,
    ZXDoc_DBType_Plugin = 0x80,
    ZXDoc_DBType_ALL = 0xFFFF
};

typedef struct _ZXDoc_Database {
    ZXDoc_DBType type;
    char id[64];
    char name[128];
    char filePath[256];
} ZXDoc_Database, *PZXDoc_Database;

enum ZXDoc_DataRecorderType {
    ZXDoc_MeasureDataRecorder,
    ZXDoc_MessageRecorder,
    ZXDoc_MatDataRecorder,
};

enum ZXDoc_EcuMemPageType { ZXDoc_RAM, ZXDoc_FLASH };

// Data sink filter
enum ZXDoc_FilterMode { ZXDoc_FilterMode_Accept = 0, ZXDoc_FilterMode_Reject = 1, ZXDoc_FilterMode_NoFilter = 3 };

enum ZXDoc_FilterDirection {
    ZXDoc_FilterDirection_Rx = 0x01,
    ZXDoc_FilterDirection_Tx = 0x02,
    ZXDoc_FilterDirection_All = 0xFF
};

enum ZXDoc_CANFilterFrameType {
    ZXDoc_CANFilterFrameType_Std = 0x01,
    ZXDoc_CANFilterFrameType_Ext = 0x02,
    ZXDoc_CANFilterFrameType_All = 0xFF
};

enum ZXDoc_DataSinkFilterType {
    ZXDoc_CANErrorFilterType = 0,
    ZXDoc_CANIDRangeFilterType = 1,
    ZXDoc_LINErrorFilterType = 2,
    ZXDoc_LINWakeUpEventFilterType = 3,
    ZXDoc_LINIDRangeFilterType = 4
};

struct ZXDoc_CANErrorFilter {
    int32_t channelIndex;
};

struct ZXDoc_CANIDRangeFilter {
    int32_t channelIndex;
    ZXDoc_FilterDirection direction;
    ZXDoc_CANFilterFrameType frameType;
    uint32_t idMin;
    uint32_t idMax;
};

struct ZXDoc_LINErrorFilter {
    int32_t channelIndex;
};

struct ZXDoc_LINWakeUpEventFilter {
    int32_t channelIndex;
};

struct ZXDoc_LINIDRangeFilter {
    int32_t channelIndex;
    ZXDoc_FilterDirection direction;
    uint32_t idMin;
    uint32_t idMax;
};

struct ZXDoc_DataSinkFilter {
    ZXDoc_DataSinkFilterType type;
    union {
        ZXDoc_CANErrorFilter canErrorFilter;
        ZXDoc_CANIDRangeFilter canIDRangeFilter;
        ZXDoc_LINErrorFilter linErrorFilter;
        ZXDoc_LINWakeUpEventFilter linWakeUpEventFilter;
        ZXDoc_LINIDRangeFilter linIDRangeFilter;
    };
};

enum ZXDoc_FalshFileType {
    ZFlashFileType_GAC = 0,
    ZFlashFileType_GACFlashDriver,
    ZFlashFileType_SRec,  // S19
    ZFlashFileType_IHex,  // hex
    ZFlashFileType_Bin,   // raw files
    ZFlashFileType_Script,
    ZFlashFileType_Unknown = 0xFF
};

#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

ZXDOC_EXP void* ZXDOC_API ZXDoc_MemoryAlloc(uint64_t size);
ZXDOC_EXP void ZXDOC_API ZXDoc_MemoryFree(void* data);
ZXDOC_EXP char* ZXDOC_API ZXDoc_StrClone(const char* src);
ZXDOC_EXP void ZXDOC_API ZXDoc_StrFree(char* str);

// ZXDoc_SignalVariant
ZXDOC_EXP ZXDoc_SignalVariant* ZXDOC_API ZXDoc_SignalVariant_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_Init(ZXDoc_SignalVariant* sv);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_InitArr(ZXDoc_SignalVariant* sv, int row, int col);
ZXDOC_EXP int ZXDOC_API ZXDoc_SignalVariant_ArrGetRows(const ZXDoc_SignalVariant* sv);
ZXDOC_EXP int ZXDOC_API ZXDoc_SignalVariant_ArrGetCols(const ZXDoc_SignalVariant* sv);
ZXDOC_EXP ZXDoc_SignalVariant* ZXDOC_API ZXDoc_SignalVariant_ArrAt(const ZXDoc_SignalVariant* sv, int row, int col);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_ArrSet(ZXDoc_SignalVariant* svArr, int row, int col,
                                                    ZXDoc_SignalVariant* item);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetInt8(ZXDoc_SignalVariant* sv, int8_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetInt16(ZXDoc_SignalVariant* sv, int16_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetInt32(ZXDoc_SignalVariant* sv, int32_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetInt64(ZXDoc_SignalVariant* sv, int64_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetUint8(ZXDoc_SignalVariant* sv, uint8_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetUint16(ZXDoc_SignalVariant* sv, uint16_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetUint32(ZXDoc_SignalVariant* sv, uint32_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetUint64(ZXDoc_SignalVariant* sv, uint64_t val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetFloat(ZXDoc_SignalVariant* sv, float val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetDouble(ZXDoc_SignalVariant* sv, double val);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_SetStr(ZXDoc_SignalVariant* sv, const char* val);

ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_Clear(ZXDoc_SignalVariant* sv);
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalVariant_Free(ZXDoc_SignalVariant* sv);

ZXDOC_EXP ZXDoc_SignalValue* ZXDOC_API ZXDoc_SignalValue_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_SignalValue_Free(ZXDoc_SignalValue* val);

// ZXDoc_RawData
ZXDOC_EXP ZXDoc_CANFDData* ZXDOC_API ZXDoc_CANFDData_New();
ZXDOC_EXP ZXDoc_CANFDErrorData* ZXDOC_API ZXDoc_CANFDErrorData_New();
ZXDOC_EXP ZXDoc_GPSData* ZXDOC_API ZXDoc_GPSData_New();
ZXDOC_EXP ZXDoc_LINData* ZXDOC_API ZXDoc_LINData_New();
ZXDOC_EXP ZXDoc_LINErrorData* ZXDOC_API ZXDoc_LINErrorData_New();
ZXDOC_EXP ZXDoc_BusUsageData* ZXDOC_API ZXDoc_BusUsageData_New();
ZXDOC_EXP ZXDoc_EthernetData* ZXDOC_API ZXDoc_EthernetData_New(uint16_t dataLength);

ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_CANFDData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_CANFDErrorData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_GPSData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_LINData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_LINErrorData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_LINEventData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_BusUsageData();
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_EthernetData(uint16_t dataLength);
ZXDOC_EXP ZXDoc_RawData* ZXDOC_API ZXDoc_RawData_New_LegacyEthernetData(uint16_t dataLength);

ZXDOC_EXP ZXDoc_CANFDData* ZXDOC_API ZXDoc_RawData_Get_CANFDData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_CANFDErrorData* ZXDOC_API ZXDoc_RawData_Get_CANFDErrorData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_GPSData* ZXDOC_API ZXDoc_RawData_Get_GPSData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_LINData* ZXDOC_API ZXDoc_RawData_Get_LINData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_LINErrorData* ZXDOC_API ZXDoc_RawData_Get_LINErrorData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_LINEventData* ZXDOC_API ZXDoc_RawData_Get_LINEventData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_BusUsageData* ZXDOC_API ZXDoc_RawData_Get_BusUsageData(const ZXDoc_RawData* rawData);
ZXDOC_EXP ZXDoc_EthernetData* ZXDOC_API ZXDoc_RawData_Get_EthernetData(const ZXDoc_RawData* rawData);
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_RawData_Size(const ZXDoc_RawData* rawData);
ZXDOC_EXP void ZXDOC_API ZXDoc_RawData_Free(ZXDoc_RawData* rawData);

// DBC message
ZXDOC_EXP PZXDoc_DBCSignalValue ZXDOC_API ZXDoc_DBCSignalValue_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_Free(PZXDoc_DBCSignalValue sgl);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_SetName(PZXDoc_DBCSignalValue sgl, const char* name);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_SetPhyValue(PZXDoc_DBCSignalValue sgl, double value);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_SetRawInt(PZXDoc_DBCSignalValue sgl, int64_t value);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_SetRawUint(PZXDoc_DBCSignalValue sgl, uint64_t value);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_SetRawFloat(PZXDoc_DBCSignalValue sgl, float value);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCSignalValue_SetRawDouble(PZXDoc_DBCSignalValue sgl, double value);

ZXDOC_EXP PZXDoc_DBCMessageValue ZXDOC_API ZXDoc_DBCMsgValue_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCMsgValue_Free(PZXDoc_DBCMessageValue msg);
ZXDOC_EXP void ZXDOC_API ZXDoc_DBCMsgValue_AppendSignal(PZXDoc_DBCMessageValue msg, PZXDoc_DBCSignalValue sgl);
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_DBCMsgValue_SignalCount(PZXDoc_DBCMessageValue msg);
ZXDOC_EXP PZXDoc_DBCSignalValue ZXDOC_API ZXDoc_DBCMsgValue_SignalAt(PZXDoc_DBCMessageValue msg, uint32_t index);
ZXDOC_EXP PZXDoc_DBCSignalValue ZXDOC_API ZXDoc_DBCMsgValue_GetSignal(PZXDoc_DBCMessageValue msg,
                                                                      const char* signalName);

// Source Signals
typedef void* ZXDocSourceSignalHandle;
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_SrcSgl_GetSourceCount(ZXDocSourceSignalHandle srcSgl);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_SrcSgl_GetSource(ZXDocSourceSignalHandle srcSgl, uint32_t srcIndex);
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_SrcSgl_GetSignalCount(ZXDocSourceSignalHandle srcSgl, uint32_t srcIndex);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_SrcSgl_GetSignal(ZXDocSourceSignalHandle srcSgl, uint32_t srcIndex,
                                                       uint32_t sglIndex);
ZXDOC_EXP void ZXDOC_API ZXDoc_SrcSgl_Free(ZXDocSourceSignalHandle srcSgl);

// ZSignal
typedef void* ZSignalHandle;
ZXDOC_EXP uint8_t ZXDOC_API ZXDoc_Sgl_GetType(ZSignalHandle h);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_Sgl_IsValid(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetId(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetName(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetLongName(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetNickName(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetComment(ZSignalHandle h);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_Sgl_IsReadOnly(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetUnit(ZSignalHandle h);
ZXDOC_EXP uint8_t ZXDOC_API ZXDoc_Sgl_GetPhyType(ZSignalHandle h);
ZXDOC_EXP double ZXDOC_API ZXDoc_Sgl_GetPhyLimitMax(ZSignalHandle h);
ZXDOC_EXP double ZXDOC_API ZXDoc_Sgl_GetPhyLimitMin(ZSignalHandle h);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_Sgl_IsScalar(ZSignalHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_Sgl_GetDimension(ZSignalHandle h);
ZXDOC_EXP void ZXDOC_API ZXDoc_Sgl_Free(ZSignalHandle h);

typedef void* ZCliResponseHandle;
ZXDOC_EXP int32_t ZXDOC_API ZXDoc_CliResp_GetReturnCode(ZCliResponseHandle h);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_CliResp_GetMessage(ZCliResponseHandle h);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_CliResp_GetValue(ZCliResponseHandle h, uint32_t index, const char** key,
                                                      const char** value);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_CliResp_GetValueByKey(ZCliResponseHandle h, const char* key, const char** value);
ZXDOC_EXP void ZXDOC_API ZXDoc_CliResp_Free(ZCliResponseHandle h);

/* 记录器配置 */
typedef void* ZXDoc_MeasureDataRecorderCfg;
ZXDOC_EXP ZXDoc_MeasureDataRecorderCfg ZXDOC_API ZXDoc_MeasureDataRecorderCfg_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_Free(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_MeasureDataRecorderCfg_GetRecorderName(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_SetRecorderName(ZXDoc_MeasureDataRecorderCfg cfg,
                                                                      const char* recorderName);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_MeasureDataRecorderCfg_GetFilePath(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_SetFilePath(ZXDoc_MeasureDataRecorderCfg cfg,
                                                                  const char* filePath);
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_MeasureDataRecorderCfg_GetMaxFileSize(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_SetMaxFileSize(ZXDoc_MeasureDataRecorderCfg cfg,
                                                                     uint32_t maxFileSize);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_MeasureDataRecorderCfg_GetComment(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_SetComment(ZXDoc_MeasureDataRecorderCfg cfg, const char* comment);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API
    ZXDoc_MeasureDataRecorderCfg_GetFileNameAutoAddTimeSuffix(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_SetFileNameAutoAddTimeSuffix(
    ZXDoc_MeasureDataRecorderCfg cfg, ZXDoc_Bool fileNameAutoAddTimeSuffix);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_MeasureDataRecorderCfg_GetMf4Compression(ZXDoc_MeasureDataRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_SetMf4Compression(ZXDoc_MeasureDataRecorderCfg cfg,
                                                                        ZXDoc_Bool mf4Compression);
ZXDOC_EXP void ZXDOC_API ZXDoc_MeasureDataRecorderCfg_AddSignal(ZXDoc_MeasureDataRecorderCfg cfg,
                                                                ZXDoc_SignalIdentifier* sglIdentifier);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_MeasureDataRecorderCfg_GetSignal(ZXDoc_MeasureDataRecorderCfg cfg, uint32_t index,
                                                                      ZXDoc_SignalIdentifier* sglIdentifier);

typedef void* ZXDoc_MessageRecorderCfg;
ZXDOC_EXP ZXDoc_MessageRecorderCfg ZXDOC_API ZXDoc_MessageRecorderCfg_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_Free(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_MessageRecorderCfg_GetRecorderName(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_SetRecorderName(ZXDoc_MessageRecorderCfg cfg,
                                                                  const char* recorderName);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_MessageRecorderCfg_GetFilePath(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_SetFilePath(ZXDoc_MessageRecorderCfg cfg, const char* filePath);
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_MessageRecorderCfg_GetMaxFileSize(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_SetMaxFileSize(ZXDoc_MessageRecorderCfg cfg, uint32_t maxFileSize);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_MessageRecorderCfg_GetComment(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_SetComment(ZXDoc_MessageRecorderCfg cfg, const char* comment);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_MessageRecorderCfg_GetFileNameAutoAddTimeSuffix(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_SetFileNameAutoAddTimeSuffix(ZXDoc_MessageRecorderCfg cfg,
                                                                               ZXDoc_Bool fileNameAutoAddTimeSuffix);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_MessageRecorderCfg_GetMf4Compression(ZXDoc_MessageRecorderCfg cfg);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_SetMf4Compression(ZXDoc_MessageRecorderCfg cfg,
                                                                    ZXDoc_Bool mf4Compression);
ZXDOC_EXP void ZXDOC_API ZXDoc_MessageRecorderCfg_AddChannel(ZXDoc_MeasureDataRecorderCfg cfg, ZXDoc_BusType busType,
                                                             int32_t logicalIndex);

typedef void* ZXDoc_FlashFileInfo;
ZXDOC_EXP ZXDoc_FlashFileInfo ZXDOC_API ZXDoc_FlashFileInfo_New();
ZXDOC_EXP void ZXDOC_API ZXDoc_FlashFileInfo_Free(ZXDoc_FlashFileInfo info);
ZXDOC_EXP const char* ZXDOC_API ZXDoc_FlashFileInfo_GetFilePath(ZXDoc_FlashFileInfo info);
ZXDOC_EXP ZXDoc_FalshFileType ZXDOC_API ZXDoc_FlashFileInfo_GetType(ZXDoc_FlashFileInfo info);
ZXDOC_EXP uint32_t ZXDOC_API ZXDoc_FlashFileInfo_GetBlockCount(ZXDoc_FlashFileInfo info);
ZXDOC_EXP ZXDoc_Bool ZXDOC_API ZXDoc_FlashFileInfo_GetBlock(ZXDoc_FlashFileInfo info, int32_t index, uint64_t* address,
                                                            const uint8_t** data, uint32_t* dataSize);

#ifdef __cplusplus
}
#endif

#endif  // _ZXDOC_COMMON_H
