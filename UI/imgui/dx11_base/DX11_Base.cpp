#include "DX11_Base.h"

/**
 * @file DX11_Base.cpp
 * @brief DirectX 11 基础实现文件
 */

// 链接库
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

/**
 * @brief Direct3D 11 设备指针
 */
ID3D11Device* g_pd3dDevice = nullptr;

/**
 * @brief Direct3D 11 设备上下文指针
 */
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;

/**
 * @brief DirectX 交换链指针
 */
IDXGISwapChain* g_pSwapChain = nullptr;

/**
 * @brief 主渲染目标视图指针
 */
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// 引用外部的消息处理函数 (ImGui 提供的)
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * @brief 创建 Direct3D 11 设备和交换链
 * @param hWnd 窗口句柄
 * @return 成功返回 true，失败返回 false
 * 
 * 该函数执行以下操作：
 * - 设置交换链描述
 * - 创建 Direct3D 11 设备和交换链
 * - 创建渲染目标视图
 */
bool CreateDeviceD3D(HWND hWnd)
{
    // 设置交换链
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    IDXGIFactory* pSwapChainFactory;
    if (SUCCEEDED(g_pSwapChain->GetParent(IID_PPV_ARGS(&pSwapChainFactory))))
    {
        pSwapChainFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
        pSwapChainFactory->Release();
    }

    CreateRenderTarget();
    return true;
}

/**
 * @brief 清理 Direct3D 11 设备资源
 * 
 * 该函数释放所有 Direct3D 11 相关资源，包括：
 * - 交换链
 * - 设备上下文
 * - 设备
 */
void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

/**
 * @brief 创建渲染目标视图
 * 
 * 该函数从交换链的后缓冲区创建渲染目标视图
 */
void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

/**
 * @brief 清理渲染目标视图
 * 
 * 该函数释放渲染目标视图资源
 */
void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// 这里的变量需要暴露给 main.cpp 处理 Resize，或者你可以封装得更好，但为了保持简单，我们先这样写
extern UINT g_ResizeWidth;
extern UINT g_ResizeHeight;

/**
 * @brief 窗口过程函数
 * @param hWnd 窗口句柄
 * @param msg 消息标识符
 * @param wParam 消息的附加信息
 * @param lParam 消息的附加信息
 * @return 消息处理结果
 * 
 * 该函数处理窗口消息，包括：
 * - 大小改变消息 (WM_SIZE)
 * - 系统命令消息 (WM_SYSCOMMAND)
 * - 窗口销毁消息 (WM_DESTROY)
 */
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam);
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
