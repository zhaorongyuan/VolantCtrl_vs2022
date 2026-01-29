#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>

/**
 * @file DX11_Base.h
 * @brief DirectX 11 基础头文件
 * 
 * 该头文件声明了 DirectX 11 相关的全局变量和函数，
 * 用于创建和管理 Direct3D 11 设备、交换链和渲染目标视图。
 */

/**
 * @brief Direct3D 11 设备指针
 * 
 * 该全局变量用于访问 Direct3D 11 设备，可用于创建资源、渲染等操作。
 */
extern ID3D11Device* g_pd3dDevice;

/**
 * @brief Direct3D 11 设备上下文指针
 * 
 * 该全局变量用于访问 Direct3D 11 设备上下文，用于执行渲染命令。
 */
extern ID3D11DeviceContext* g_pd3dDeviceContext;

/**
 * @brief DirectX 交换链指针
 * 
 * 该全局变量用于访问 DirectX 交换链，用于管理渲染目标和呈现。
 */
extern IDXGISwapChain* g_pSwapChain;

/**
 * @brief 主渲染目标视图指针
 * 
 * 该全局变量用于访问主渲染目标视图，用于渲染到屏幕。
 */
extern ID3D11RenderTargetView* g_mainRenderTargetView;

/**
 * @brief 创建 Direct3D 11 设备和交换链
 * @param hWnd 窗口句柄
 * @return 成功返回 true，失败返回 false
 * 
 * 该函数用于创建 Direct3D 11 设备和交换链，并初始化渲染目标视图。
 */
bool CreateDeviceD3D(HWND hWnd);

/**
 * @brief 清理 Direct3D 11 设备资源
 * 
 * 该函数用于释放所有 Direct3D 11 相关资源，包括设备、设备上下文和交换链。
 */
void CleanupDeviceD3D();

/**
 * @brief 创建渲染目标视图
 * 
 * 该函数用于从交换链的后缓冲区创建渲染目标视图。
 */
void CreateRenderTarget();

/**
 * @brief 清理渲染目标视图
 * 
 * 该函数用于释放渲染目标视图资源。
 */
void CleanupRenderTarget();

/**
 * @brief 窗口过程函数
 * @param hWnd 窗口句柄
 * @param msg 消息标识符
 * @param wParam 消息的附加信息
 * @param lParam 消息的附加信息
 * @return 消息处理结果
 * 
 * 该函数用于处理窗口消息，包括大小改变、系统命令和窗口销毁等消息。
 */
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
