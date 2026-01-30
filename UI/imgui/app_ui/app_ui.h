#pragma once

#include <string>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <time.h>   // 用于获取系统时间

#include "imgui.h"
#include "Font.h"

struct MotorControlParams {
    int motor_id_idx = 0;           // 电机编号索引 (0-10, 对应 ID 1-11)
    int ctrl_source_idx = 0;        // 控制源
    int machine_hv_idx = 0;         // 整机高压
    int hv_state_idx = 0;           // 高压状态
    int work_mode_idx = 0;          // 工作模式
    int speed_rpm = 0;              // 转速
    bool motor_id_enabled = true;   // 主通道
    bool crc_switch = true;         // CRC开关
    bool heartbeat_switch = true;   // 心跳开关
    bool is_sending = false;        // 发送开关
};

// 用于界面显示的数据结构 (对应图片下半部分)
struct MotorDisplayData {
    // --- Fbk 报文解析内容 ---
    char main_module[32] = "None";
    char speed_fbk[32] = "None";
    char cycle_count_fbk[32] = "None";
    char work_mode_fbk[32] = "None";
    char power_fbk[32] = "None";
    char crc_fbk[32] = "None";
    char fault_summary[32] = "None";

    // 0:红(3级), 1:橙(2级), 2:黄(1级), 3:绿(无故障)
    int  status_light_level = 0;

    // --- Normal 报文解析内容 ---
    // 第一列
    char motor_pos[32] = "None";
    char bus_vol_a[32] = "None";
    char fault_lvl_a[32] = "None";
    char warn_code_a[32] = "None";
    char err_code_a[32] = "None";
    char temp_front_bearing[32] = "None";
    char temp_sic[32] = "None";
    char cycle_count_norm[32] = "None";

    // 第二列
    char ab_flag[32] = "None";
    char bus_vol_b[32] = "None";
    char fault_lvl_b[32] = "None";
    char warn_code_b[32] = "None";
    char err_code_b[32] = "None";
    char temp_rear_bearing[32] = "None";
    char temp_motor[32] = "None";
    char crc_norm[32] = "None";

    // 第三列
    char curr_a_u[32] = "None";
    char curr_a_v[32] = "None";
    char curr_a_w[32] = "None";
    char curr_b_u[32] = "None";
    char curr_b_v[32] = "None";
    char curr_b_w[32] = "None";

    // 时间显示
    char time_str[32] = "16:40:33";
};


// 声明一个全局实例，让其他文件也能访问 (如果需要)
// extern MotorControlParams g_MotorParams;
extern MotorDisplayData g_MotorDisplay;

/**
 * @brief 初始化 UI 状态
 * 
 * 该函数用于初始化应用程序的 UI 状态，包括但不限于：
 * - 加载自定义字体
 * - 设置 ImGui 样式
 * - 初始化其他 UI 相关资源
 */
void App_Init();

/**
 * @brief 每一帧的渲染逻辑
 * 
 * 该函数在每一帧被调用，用于渲染 UI 内容。
 * 所有 ImGui::Begin/End 等渲染代码应该放置在此函数中。
 */
void App_Render();

/**
 * @brief 程序退出时的清理
 * 
 * 该函数在程序退出时被调用，用于释放 UI 相关资源。
 * 包括但不限于：
 * - 释放字体资源
 * - 清理 ImGui 上下文
 * - 释放其他 UI 相关资源
 */
void App_Shutdown();

void ShowMotorControlPanel(MotorControlParams* p_params);

MotorControlParams* GetMotorParams();

static void UpdateSystemTimeStr();

