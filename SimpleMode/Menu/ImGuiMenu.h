#pragma once
#include <string.h>
#include <iostream>
#include <time.h>
#include <D3D11.h>
#include <tchar.h>
#include <DXGI.h>
#include "../../includes/imgui/imgui.h"
#include "../../includes/imgui/imgui_impl_dx11.h"
#include "../../includes/imgui/imgui_impl_win32.h"
#include "../../includes/imgui/imgui_internal.h"
#include "../../includes/kiero/kiero.h"
#include "../../includes/imgui/Hub/blur.hpp"
#define DEPTH_BIAS_D32_FLOAT(d) (d/(1/pow(2,23)))
namespace ImGuiMenu {
	void InitImGui();
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	DWORD WINAPI Init();
};
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

static ID3D11Device* g_pd3dDevice = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static Present oPresent;

static HWND window = NULL;
static WNDPROC oWndProc;
static ID3D11Device* pDevice = NULL;
static ID3D11DeviceContext* pContext = NULL;
static ID3D11RenderTargetView* mainRenderTargetView;

static ID3D11RasterizerState* DEPTHBIASState_FALSE;
static ID3D11RasterizerState* DEPTHBIASState_TRUE;
static ID3D11RasterizerState* DEPTHBIASState_ORIG;
static ID3D11SamplerState* pSamplerState;
static WNDPROC oWndProcHandler = nullptr;
static ID3D11Texture2D* textureRed = nullptr;
static ID3D11Texture2D* textureGreen = nullptr;
static ID3D11ShaderResourceView* textureViewRed;
static ID3D11ShaderResourceView* textureViewGreen;
static ID3D11DepthStencilState* depthStencilStateFalse;