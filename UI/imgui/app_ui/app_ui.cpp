// =================================================================================
// 文件名: App_UI_Impl.cpp
// 描述:  ImGui 界面实现逻辑，包含电机控制与状态反馈窗口。
// 优化:  结构梳理与详细注释添加
// =================================================================================

// ---------------------------------------------------------------------------------
// 1. 头文件与宏定义
// ---------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS // 允许使用标准库中的不安全函数 (如 strncpy, sprintf)

#include "App_UI.h"


// ---------------------------------------------------------------------------------
// 2. 全局数据与状态管理
// ---------------------------------------------------------------------------------

// [业务数据实例]
// 这些实例通常由后端线程更新，UI层主要负责读取展示或写入控制指令
MotorControlParams g_MotorParams;   // 电机控制参数（下发）
MotorDisplayData   g_MotorDisplay;  // 电机反馈数据（显示）

// [UI 状态标志]
static bool g_IsWindowLocked = false; // 全局窗口锁定标志：true=禁止移动/缩放/关闭

// [窗口显示控制]
static bool show_demo_window = true;  // ImGui 官方 Demo 窗口
static bool show_control_window = true;  // 电机控制指令窗口
static bool show_feedback_window = true;  // 电机状态反馈窗口

// [样式配置]
// 默认清除颜色 (背景色)
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// ---------------------------------------------------------------------------------
// 3. 接口函数实现 (Getters & Lifecycle)
// ---------------------------------------------------------------------------------

/**
 * @brief 获取电机控制参数指针
 * 外部模块通过此接口获取UI层设置的参数
 */
MotorControlParams* GetMotorParams() {
    return &g_MotorParams;
}

/**
 * @brief 获取背景清除颜色
 */
ImVec4* GetClearColor() {
    return &clear_color;
}

/**
 * @brief 应用程序初始化
 * 配置 ImGui 样式、字体及全局缩放
 */
void App_Init()
{
    // [样式] 使用 ImGui 自带的亮色主题
    ImGui::StyleColorsLight();

    // [缩放] 设置全局缩放系数，适配不同分辨率
    // 注意：ScaleAllSizes 会影响所有样式尺寸
    float global_scale = 0.9f;
    ImGui::GetStyle().ScaleAllSizes(global_scale);

    // [配置] IO 配置
    ImGuiIO& io = ImGui::GetIO();
    // 启用停靠功能 (Docking)，允许窗口拖拽合并
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // [字体] 加载中文字体
    // 如果加载失败，回退到默认字体，避免程序崩溃
    if (io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 20.0f * global_scale, NULL, io.Fonts->GetGlyphRangesChineseFull()) == NULL) {
        fprintf(stderr, "[Error] Failed to load font. Using default.\n");
        io.Fonts->AddFontDefault();
    }
}

/**
 * @brief 应用程序关闭清理
 * 目前为空，保留接口以备后续资源释放需求
 */
void App_Shutdown() {}

// ---------------------------------------------------------------------------------
// 4. 辅助工具函数
// ---------------------------------------------------------------------------------

// 前置声明业务窗口函数
void ShowMotorControlWindow(MotorControlParams* p_params);
void ShowMotorFeedbackWindow(MotorDisplayData* p_data);

/**
 * @brief 获取当前的通用窗口锁定标志位
 * * @return ImGuiWindowFlags 组合标志位
 * - 如果 g_IsWindowLocked 为 true，返回禁止调整大小、移动、折叠及停靠的标志。
 * - 否则返回 0 (无限制)。
 */
ImGuiWindowFlags GetLockFlags()
{
    if (g_IsWindowLocked) {
        return ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoDocking;
    }
    return 0;
}

// ---------------------------------------------------------------------------------
// 5. 主渲染循环 (App_Render)
// ---------------------------------------------------------------------------------

/**
 * @brief 主渲染函数，每帧调用
 * 负责调度所有子窗口的绘制
 */
void App_Render()
{
    UpdateSystemTimeStr();
    // 1. 渲染 ImGui 官方 Demo (用于参考/调试)
    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

    // 2. 渲染主菜单/控制面板窗口 (Hello, zxdoc!)
    {
        ImGuiWindowFlags main_flags = 0;
        // 应用全局锁定策略
        main_flags |= GetLockFlags();

        // 开始绘制主控窗口
        ImGui::Begin(u8"Hello, zxdoc!", NULL, main_flags);

        // --- 窗口显示开关 ---
        ImGui::Text(u8"窗口管理:");
        ImGui::Checkbox(u8"显示控制窗口 (Motor Controls)", &show_control_window);
        ImGui::Checkbox(u8"显示反馈窗口 (Motor Feedback)", &show_feedback_window);
        ImGui::Checkbox(u8"显示 ImGui Demo", &show_demo_window);

        ImGui::Separator(); // 分割线

        // --- 布局锁定控制 ---
        // 这里的 Checkbox 直接修改全局静态变量 g_IsWindowLocked
        if (ImGui::Checkbox(u8"锁定所有窗口布局", &g_IsWindowLocked)) {
            // [扩展点] 如果需要在锁定状态切换时执行额外逻辑（如保存配置），可在此处添加
        }

        ImGui::Separator();

        // --- 性能监控 ---
        ImGui::Text(u8"性能监控:");
        // 计算帧生成时间 (ms) 和 帧率 (FPS)
        ImGui::Text(u8"Avg %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }

    // 3. 渲染业务子窗口
    if (show_control_window)  ShowMotorControlWindow(&g_MotorParams);
    if (show_feedback_window) ShowMotorFeedbackWindow(&g_MotorDisplay);
}

// ---------------------------------------------------------------------------------
// 6. 业务窗口 A：电机控制 (Motor Controls)
// ---------------------------------------------------------------------------------

/**
 * @brief 绘制电机控制窗口
 * 功能：设置电机ID、控制模式、高压状态、转速设定及CAN发送控制
 * * @param p_params 控制参数结构体指针
 */
void ShowMotorControlWindow(MotorControlParams* p_params)
{
    // [安全检查] 空指针保护
    if (p_params == nullptr) return;
    MotorControlParams& params = *p_params;

    // --- 静态变量 (保留状态) ---
    // ui_speed_rpm: 用于滑块/输入框的临时缓存，与 params.speed_rpm 分离以实现平滑交互
    static int ui_speed_rpm = 0;

    // --- 限制参数 (Constants) ---
    static int speed_min_limit = 0;
    static int speed_max_limit = 3000;
    static int step_size = 20; // 按钮步进值

    // --- 下拉菜单数据源 ---
    const int motor_count = 11;
    const char* ctrl_sources[] = { u8"0-PFCC1", u8"1-PFCC2", u8"2-PFCC3", u8"3-BFCC" };
    const char* machine_hv_items[] = { u8"0-unknow", u8"1-整机上电", u8"2-整机下电", u8"3-预留" };
    const char* hv_state_items[] = { u8"0-未知状态", u8"1-高压不可用", u8"2-高压可用", u8"3-高压可用，电池丢包" };
    const char* work_modes[] = { u8"0-不开管", u8"1-转速控制", u8"2-锁桨控制", u8"3-主动放电", u8"4-其他..." };

    // --- 窗口属性设置 ---
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar; // 启用菜单栏
    flags |= GetLockFlags(); // 应用锁定状态

    ImGui::Begin(u8"Motor Controls", &show_control_window, flags);

    // =========================================================================
    // 6.1 菜单栏区域
    // =========================================================================
    if (ImGui::BeginMenuBar()) {
        ImGui::Text(u8"CAN0 控制参数");

        // [布局计算] 将时间显示右对齐
        float right_w = 160.0f;
        float avail = ImGui::GetContentRegionAvail().x;
        // 确保不会因为窗口过小导致负边距
        if (avail > right_w) ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - right_w);
        else ImGui::SameLine();

        // 显示系统时间 (蓝色)
        ImGui::TextColored(ImVec4(0.2f, 0.5f, 1.0f, 1.0f), "%s", g_MotorDisplay.time_str);

        ImGui::SameLine();
        // 快捷锁定按钮
        if (ImGui::Button(g_IsWindowLocked ? u8"解锁" : u8"锁定", ImVec2(50, 0))) {
            g_IsWindowLocked = !g_IsWindowLocked;
        }
        ImGui::EndMenuBar();
    }

    // 设置窗口内部元素的内边距
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

    // =========================================================================
    // 6.2 参数配置表 (Table Layout)
    // =========================================================================
    ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings;
    if (ImGui::BeginTable("CtrlTable", 2, table_flags)) {
        // 定义两列：L=标签列(固定宽), V=值列(自适应)
        ImGui::TableSetupColumn("L", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("V", ImGuiTableColumnFlags_WidthStretch);

        // --- Row 1: 电机编号选择 ---
        ImGui::TableNextColumn(); ImGui::AlignTextToFramePadding(); ImGui::Text(u8"电机编号");
        ImGui::TableNextColumn();
        {
            // 动态生成当前的 Preview 字符串
            char id_str[32];
            snprintf(id_str, 32, u8"ID = %d", params.motor_id_idx + 1);

            ImGui::SetNextItemWidth(130);
            if (ImGui::BeginCombo(u8"##MotorID", id_str)) {
                for (int i = 0; i < motor_count; i++) {
                    snprintf(id_str, 32, u8"ID = %d", i + 1);
                    if (ImGui::Selectable(id_str, params.motor_id_idx == i))
                        params.motor_id_idx = i;
                }
                ImGui::EndCombo();
            }
            ImGui::SameLine();
            ImGui::Checkbox(u8"##主通道", &params.motor_id_enabled);
        }

        // --- Row 2: 控制源选择 ---
        ImGui::TableNextColumn(); ImGui::AlignTextToFramePadding(); ImGui::Text(u8"控制源");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(130);
        ImGui::Combo(u8"##Src", &params.ctrl_source_idx, ctrl_sources, IM_ARRAYSIZE(ctrl_sources));
        ImGui::SameLine(); ImGui::Text(u8"主通道");

        // --- Row 3: 整机高压设置 ---
        ImGui::TableNextColumn(); ImGui::AlignTextToFramePadding(); ImGui::Text(u8"整机高压");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(200);
        ImGui::Combo(u8"##HV", &params.machine_hv_idx, machine_hv_items, IM_ARRAYSIZE(machine_hv_items));

        // --- Row 4: 高压状态设置 ---
        ImGui::TableNextColumn(); ImGui::AlignTextToFramePadding(); ImGui::Text(u8"高压状态");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(200);
        ImGui::Combo(u8"##St", &params.hv_state_idx, hv_state_items, IM_ARRAYSIZE(hv_state_items));

        // --- Row 5: 工作模式设置 ---
        ImGui::TableNextColumn(); ImGui::AlignTextToFramePadding(); ImGui::Text(u8"工作模式");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(200);
        ImGui::Combo(u8"##Md", &params.work_mode_idx, work_modes, IM_ARRAYSIZE(work_modes));

        ImGui::EndTable();
    }

    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // =========================================================================
    // 6.3 转速控制区域 (Advanced Logic)
    // =========================================================================

    // 设置转速的上下限
    ImGui::Text(u8"转速限制范围:");
    ImGui::SameLine();
    ImGui::PushItemWidth(60);
    // Min Limit Input
    if (ImGui::InputInt(u8"##Min", &speed_min_limit, 0, 0)) {
        if (speed_min_limit >= speed_max_limit) speed_min_limit = speed_max_limit - 100;
    }
    ImGui::SameLine(); ImGui::Text(u8"~"); ImGui::SameLine();
    // Max Limit Input
    if (ImGui::InputInt(u8"##Max", &speed_max_limit, 0, 0)) {
        if (speed_max_limit <= speed_min_limit) speed_max_limit = speed_min_limit + 100;
    }
    ImGui::PopItemWidth();

    // [逻辑说明] 数据同步机制
    // is_editing_speed 标志用于判断用户是否正在操作 UI。
    // 如果用户在操作，我们将 UI 值写入 Params；
    // 如果用户未操作，我们将 Params 值回写到 UI，以保持与后端逻辑同步。
    bool is_editing_speed = false;

    // 1. 滑块控制 (Slider)
    ImGui::SetNextItemWidth(-10); // 填满宽度
    if (ImGui::SliderInt(u8"##Slider", &ui_speed_rpm, speed_min_limit, speed_max_limit, "")) {
        params.speed_rpm = ui_speed_rpm;
        is_editing_speed = true;
    }
    if (ImGui::IsItemActive()) is_editing_speed = true; // 处理长按拖拽状态

    ImGui::Dummy(ImVec2(0, 4)); // 垂直间距

    // 2. 精确输入控制 (InputInt)
    ImGui::AlignTextToFramePadding();
    ImGui::Text(u8"转速设定:");
    ImGui::SameLine();
    ImGui::PushItemWidth(80);
    // EnterReturnsTrue 使得只有按下回车时才提交数据
    if (ImGui::InputInt(u8"##In", &ui_speed_rpm, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue)) {
        // 边界钳制
        if (ui_speed_rpm < speed_min_limit) ui_speed_rpm = speed_min_limit;
        if (ui_speed_rpm > speed_max_limit) ui_speed_rpm = speed_max_limit;
        params.speed_rpm = ui_speed_rpm;
        is_editing_speed = true;
    }
    if (ImGui::IsItemActive()) is_editing_speed = true;
    ImGui::PopItemWidth();

    // [同步] 如果没有在编辑，从数据源更新UI显示
    if (!is_editing_speed) {
        ui_speed_rpm = params.speed_rpm;
    }

    // 3. 步进微调按钮 (+/-)
    ImGui::SameLine();
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2, 0)); // 按钮紧挨着
    if (ImGui::Button("-", ImVec2(30, 0))) {
        params.speed_rpm -= step_size;
        if (params.speed_rpm < speed_min_limit) params.speed_rpm = speed_min_limit;
        ui_speed_rpm = params.speed_rpm; // 立即更新 UI
    }
    ImGui::SameLine();
    // 步进值设置
    ImGui::PushItemWidth(60); ImGui::InputInt(u8"##Stp", &step_size, 0, 0); ImGui::PopItemWidth();
    ImGui::SameLine();
    if (ImGui::Button("+", ImVec2(30, 0))) {
        params.speed_rpm += step_size;
        if (params.speed_rpm > speed_max_limit) params.speed_rpm = speed_max_limit;
        ui_speed_rpm = params.speed_rpm; // 立即更新 UI
    }
    ImGui::PopStyleVar();

    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // =========================================================================
    // 6.4 底部控制开关与发送按钮
    // =========================================================================
    ImGui::Indent(5);

    // 功能开关
    ImGui::Checkbox(u8"CRC", &params.crc_switch);
    ImGui::SameLine(80);
    ImGui::Checkbox(u8"心跳", &params.heartbeat_switch);
    ImGui::SameLine(160);

    // 发送状态按钮 (颜色随状态变化)
    if (params.is_sending) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f)); // 发送中: 红色
    else ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.2f, 1.0f)); // 停止中: 绿色

    if (ImGui::Button(params.is_sending ? u8"停止发送" : u8"开始发送", ImVec2(100, 30)))
        params.is_sending = !params.is_sending;

    ImGui::PopStyleColor();

    ImGui::Unindent(10);
    ImGui::PopStyleVar(); // Pop WindowPadding
    ImGui::End();
}

// ---------------------------------------------------------------------------------
// 7. 业务窗口 B：电机反馈 (Motor Feedback)
// ---------------------------------------------------------------------------------

/**
 * @brief 绘制电机反馈窗口
 * 功能：解析并只读显示Fbk与Normal报文数据
 * * @param p_display 反馈数据结构体指针
 */
void ShowMotorFeedbackWindow(MotorDisplayData* p_display)
{
    // [安全检查] 空指针保护
    if (p_display == nullptr) return;
    MotorDisplayData& data = *p_display;

    // 应用锁定标志
    ImGuiWindowFlags flags = 0;
    flags |= GetLockFlags();

    ImGui::Begin(u8"Motor Feedback", &show_feedback_window, flags);

    // --- 样式自定义 ---
    // 将 InputText 样式修改为白底黑字，模仿数据表格效果
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

    // [Lambda] 辅助函数：绘制表格的一行
    // label: 标签名称
    // value: 显示的数值字符串
    auto DisplayRow = [](const char* label, const char* value) {
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", label);

        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN); // 填满列宽

        // 生成唯一ID，避免ImGui冲突
        char id[64];
        snprintf(id, sizeof(id), "##%s", label);

        // 安全字符串处理：防止 value 为 NULL 导致崩溃
        char temp_buf[128];
        if (value) strncpy(temp_buf, value, sizeof(temp_buf) - 1);
        else temp_buf[0] = '\0';
        temp_buf[sizeof(temp_buf) - 1] = '\0'; // 确保结尾符

        // 使用 ReadOnly 标志，禁止用户修改反馈数据
        ImGui::InputText(id, temp_buf, sizeof(temp_buf), ImGuiInputTextFlags_ReadOnly);
        };

    // 表格通用标志：内部竖线 | 隔行变色 | 固定尺寸
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_NoSavedSettings |
        ImGuiTableFlags_SizingFixedFit;

    // =========================================================================
    // 7.1 Fbk 报文数据表
    // =========================================================================
    ImGui::TextColored(ImVec4(0.6f, 0.4f, 0.9f, 1.0f), u8"Fbk报文解析内容");

    if (ImGui::BeginTable("Fbk", 4, table_flags)) {
        // 设置4列布局：L1, V1, L2, V2
        ImGui::TableSetupColumn("L1", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("V1", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("L2", ImGuiTableColumnFlags_WidthFixed, 80.0f);
        ImGui::TableSetupColumn("V2", ImGuiTableColumnFlags_WidthStretch);

        DisplayRow(u8"主模块", data.main_module);     DisplayRow(u8"转速反馈", data.speed_fbk);
        DisplayRow(u8"工作模式", data.work_mode_fbk); DisplayRow(u8"功率反馈", data.power_fbk);
        DisplayRow(u8"故障汇总", data.fault_summary);

        // --- 特殊处理：状态指示灯 (绘制圆形) ---
        ImGui::TableNextColumn(); ImGui::AlignTextToFramePadding(); ImGui::Text(u8"状态指示");
        ImGui::TableNextColumn(); {
            // 根据状态值决定颜色 (3=绿色/正常, 其他=红色/异常)
            ImU32 col = (data.status_light_level == 3) ? IM_COL32(50, 205, 50, 255) : IM_COL32(255, 50, 50, 255);

            // 计算绘制位置，使其垂直居中
            ImVec2 p = ImGui::GetCursorScreenPos();
            float y_offset = (ImGui::GetFrameHeight() - 16.0f) * 0.5f;

            // 调用 DrawList 直接绘制
            ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(p.x + 10, p.y + y_offset + 8.0f), 8.0f, col);
        }

        DisplayRow(u8"循环计数", data.cycle_count_fbk); DisplayRow(u8"CRC", data.crc_fbk);
        ImGui::EndTable();
    }

    ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();

    // =========================================================================
    // 7.2 Normal 报文数据表 (Part 1)
    // =========================================================================
    ImGui::TextColored(ImVec4(0.6f, 0.4f, 0.9f, 1.0f), u8"Normal报文解析内容");

    if (ImGui::BeginTable("Norm1", 4, table_flags)) {
        ImGui::TableSetupColumn("L1", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("V1", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("L2", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("V2", ImGuiTableColumnFlags_WidthStretch);

        DisplayRow(u8"电机位置", data.motor_pos);           DisplayRow(u8"AB标志位", data.ab_flag);
        DisplayRow(u8"A母线电压", data.bus_vol_a);          DisplayRow(u8"B母线电压", data.bus_vol_b);
        DisplayRow(u8"A故障等级", data.fault_lvl_a);        DisplayRow(u8"B故障等级", data.fault_lvl_b);
        DisplayRow(u8"前轴温", data.temp_front_bearing);    DisplayRow(u8"后轴温", data.temp_rear_bearing);
        DisplayRow(u8"SiC温度", data.temp_sic);             DisplayRow(u8"电机温度", data.temp_motor);
        DisplayRow(u8"循环计数", data.cycle_count_norm);    DisplayRow(u8"CRC校验", data.crc_norm);
        ImGui::EndTable();
    }

    // =========================================================================
    // 7.3 Normal 报文数据表 (Part 2: 警告与错误码)
    // =========================================================================
    // 这里使用2列布局，因为错误码通常较长
    if (ImGui::BeginTable("Norm2", 2, table_flags)) {
        ImGui::TableSetupColumn("L1", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("V1", ImGuiTableColumnFlags_WidthStretch);

        DisplayRow(u8"A警告码", data.warn_code_a);
        DisplayRow(u8"B警告码", data.warn_code_b);
        DisplayRow(u8"A错误码", data.err_code_a);
        DisplayRow(u8"B错误码", data.err_code_b);
        ImGui::EndTable();
    }

    // =========================================================================
    // 7.4 Normal 报文数据表 (Part 3: 电流数据)
    // =========================================================================
    if (ImGui::BeginTable("Norm13", 4, table_flags)) {
        ImGui::TableSetupColumn("L1", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("V1", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("L2", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn("V2", ImGuiTableColumnFlags_WidthStretch);

        DisplayRow(u8"A相电流U", data.curr_a_u); DisplayRow(u8"B相电流U", data.curr_b_u);
        DisplayRow(u8"A相电流V", data.curr_a_v); DisplayRow(u8"B相电流V", data.curr_b_v);
        DisplayRow(u8"A相电流W", data.curr_a_w); DisplayRow(u8"B相电流W", data.curr_b_w);

        ImGui::EndTable();
    }

    // 恢复样式
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(2);

    ImGui::End();
}

// 更新系统时间
static void UpdateSystemTimeStr()
{
    // 获取当前系统时间
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (g_MotorDisplay.time_str != nullptr) {
        strftime(g_MotorDisplay.time_str, 32, "%H:%M:%S", timeinfo);
    }
}