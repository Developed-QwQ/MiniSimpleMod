#pragma once
#include "../../Utils/logger.h"


#include <wtypes.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <D3D11.h>
#include <exception>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../../includes/imGui/imgui.h"
#include "../../includes/imGui/imgui_impl_dx11.h"
#include "../../includes/imGui/imgui_impl_win32.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d11.lib")
namespace impl {
	enum Color_ {
		rainbow,
		Grey,
		Blue,
		Custom
	};
	namespace D3D11 {
		static WNDPROC oWndProc;
		static HWND window = NULL;
		static ID3D11Device* pDevice = nullptr;
		static IDXGISwapChain* pSwapChain = nullptr;
		static ID3D11DeviceContext* pContext = nullptr;
		static ID3D11RenderTargetView* mainRenderTargetView = nullptr;

		void init();
		void CreateRenderTarget();
		void CleanupRenderTarget();
		HRESULT GenerateShader(ID3D11Device* pD3DDevice, ID3D11PixelShader** pShader, float r, float g, float b);
		HRESULT __stdcall hkPresent11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void __stdcall hkDrawIndexed11(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
	}
	namespace Opengl32 {
		BOOL __stdcall hkWGLSwapBuffers(HDC hdc);
		void init();
	}
}
