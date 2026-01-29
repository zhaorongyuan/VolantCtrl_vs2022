#include "DX11_Base.h"
#include "App_UI.h"
#include <iostream>
#include <thread>
#include <iomanip>
#include <vector>
#include <chrono>
#include <atomic>
#include "ZXDocClient.h"
#include <windows.h> 

/**
 * @file main.cpp
 * @brief ImGui 应用程序主入口文件
 * 
 * 该文件实现了基于 DirectX 11 的 ImGui 应用程序主函数，
 * 包括窗口创建、DirectX 11 设备初始化、ImGui 初始化和主循环等。
 */

/**
 * @brief 窗口宽度调整值
 * 
 * 该全局变量用于存储窗口宽度调整值，在 DX11_Base.cpp 中被 WndProc 修改。
 */
UINT g_ResizeWidth = 0;

/**
 * @brief 窗口高度调整值
 * 
 * 该全局变量用于存储窗口高度调整值，在 DX11_Base.cpp 中被 WndProc 修改。
 */
UINT g_ResizeHeight = 0;

/**
 * @brief 交换链是否被遮挡的标志
 * 
 * 该静态变量用于标记交换链是否被遮挡，用于优化渲染性能。
 */
static bool g_SwapChainOccluded = false;

// 声明 App_UI.cpp 里的辅助函数
extern ImVec4* GetClearColor();

/**
 * @brief 应用程序主函数
 * @param argc 命令行参数个数（未使用）
 * @param argv 命令行参数数组（未使用）
 * @return 程序退出码，0 表示成功，非 0 表示失败
 * 
 * 该函数执行以下操作：
 * 1. 初始化 DPI awareness
 * 2. 创建窗口
 * 3. 初始化 DirectX 11
 * 4. 初始化 ImGui 核心
 * 5. 初始化 Backend
 * 6. 初始化用户应用 (App_UI)
 * 7. 运行主循环
 * 8. 清理资源
 */
int test();
int main(int, char**)
{
    test();
    // 1. 初始化 DPI awareness
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

    // 2. 创建窗口
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_OVERLAPPEDWINDOW, 100, 100, (int)(1280 * main_scale), (int)(800 * main_scale), nullptr, nullptr, wc.hInstance, nullptr);

    // 3. 初始化 DX11
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // 4. 初始化 ImGui 核心
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // 开启 Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // 开启多视口

    // 缩放设置
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;
    io.ConfigDpiScaleFonts = true;
    io.ConfigDpiScaleViewports = true;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // 5. 初始化 Backend
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // 6. 初始化用户应用 (App_UI)
    App_Init();

    // 7. 主循环
    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done) break;

        // 处理最小化/遮挡
        if (g_SwapChainOccluded && g_pSwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        // 处理 Resize
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // 开始新的一帧
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // >>>>>>>>> 调用你的业务逻辑 <<<<<<<<<
        App_Render();
        // >>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<

        // 渲染
        ImGui::Render();
        ImVec4* clear_color = GetClearColor();
        const float clear_color_with_alpha[4] = { clear_color->x * clear_color->w, clear_color->y * clear_color->w, clear_color->z * clear_color->w, clear_color->w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT hr = g_pSwapChain->Present(1, 0);
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    // 8. 清理
    App_Shutdown();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

int test()
{
    ZXDocClient client;

    // 1. 连接
    std::cout << "1. Connecting..." << std::endl;
    if (!client.Connect()) return -1;

    // 2. 设置回调
    std::atomic<int> rx_count(0);
    client.SetCanMessageCallback([&rx_count](uint8_t ch, uint32_t id, const std::vector<uint8_t>& data, bool isFd) {
        rx_count++;
        });

    // 3. 启动
    std::cout << "2. Starting Measurement..." << std::endl;
    if (!client.Start()) return -1;

    // ==========================================
    // 4. 批量极速测试配置
    // ==========================================
    const int TOTAL_FRAMES = 50000;  // 总帧数 (加量到5万)
    const int BATCH_SIZE = 50;       // 每批 50 帧 (打包发送)
    const int CHANNEL = 1;
    const bool TEST_IS_FD = true;

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "3. BATCH SPEED TEST (Target: " << TOTAL_FRAMES << ")" << std::endl;
    std::cout << "   Batch Size: " << BATCH_SIZE << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    // 预先构造一批数据 (避免在循环里重复分配内存，进一步提速)
    std::vector<uint8_t> singlePayload(64, 0xAA);
    std::vector<std::vector<uint8_t>> batchPayloads(BATCH_SIZE, singlePayload);

    // 给这批数据打上标记
    for (int k = 0; k < BATCH_SIZE; ++k) {
        batchPayloads[k][0] = (uint8_t)k; // 第一个字节区分
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    int sent_batches = 0;

    int loops = TOTAL_FRAMES / BATCH_SIZE;

    // --- 极速循环 ---
    for (int i = 0; i < loops; ++i) {
        // 调用我们新写的批量接口
        // ID 使用 0x100 (标准帧范围), isFd=true, isExtended=false
        if (client.SendCanMessagesBatch(CHANNEL, 0x12345, batchPayloads, TEST_IS_FD, true)) {
            sent_batches++;
        }
        else {
            // 如果缓冲区满，稍微让出一点时间
            std::this_thread::yield();
        }

        // 批量模式下通常不需要 sleep，除非硬件真的顶不住
        // if (i % 20 == 0) std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    auto end_time_tx = std::chrono::high_resolution_clock::now();

    // 5. 等待接收
    std::cout << "4. Tx Loop Done. Waiting 5 seconds..." << std::endl;
    for (int k = 0; k < 50; ++k) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (k % 10 == 0) std::cout << "   Rx: " << rx_count.load() << std::endl;
    }

    client.Stop();

    // ==========================================
    // 6. 结果计算
    // ==========================================
    double duration_sec = std::chrono::duration<double>(end_time_tx - start_time).count();
    int tx_success = sent_batches * BATCH_SIZE;
    double fps = tx_success / duration_sec;
    double mbps = (tx_success * 64.0 * 8.0) / (1000000.0 * duration_sec);

    std::cout << "\n================ RESULT ================" << std::endl;
    std::cout << "Time (Tx Loop)   : " << std::fixed << std::setprecision(3) << duration_sec << " s" << std::endl;
    std::cout << "Total Sent       : " << tx_success << std::endl;
    std::cout << "Total Received   : " << rx_count.load() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Tx Speed (FPS)   : " << std::fixed << std::setprecision(2) << fps << " Frames/sec" << std::endl;
    std::cout << "Payload Tput     : " << std::fixed << std::setprecision(2) << mbps << " Mbps" << std::endl;
    std::cout << "========================================" << std::endl;

    std::cin.get();
    return 0;
}


