#include "DrawUtils.h"
#include "../../Utils/Utils.h"
#include "../../Memory/Hooks.h"
#include "../Module/ModManager.h"
#include "../Menu/GuiControls.h"
#include "../Menu/Guiprogram.h"
#include "bytes.hpp"
#include "hashes.hpp"
bool gui_init = false;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11PixelShader* sGreen = NULL;
ID3D11DepthStencilState* oDepthStencilState = NULL;
ID3D11DepthStencilState* depthStencilStateFalse;

HRESULT __stdcall impl::D3D11::hkPresent11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	static auto opresent = g_Hooks.oPresent->Getstdcall<HRESULT, IDXGISwapChain*, UINT, UINT>();
	if (!gui_init) {
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.Fonts->AddFontFromMemoryTTF(museo500_binary, sizeof museo500_binary, 22);
			static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
			ImFontConfig icons_config;
			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;

			ImFontConfig Font_cfg;
			Font_cfg.FontDataOwnedByAtlas = false;

			io.Fonts->AddFontFromMemoryTTF(&font_awesome_binary, sizeof font_awesome_binary, 20, &icons_config, icon_ranges);
			io.Fonts->AddFontFromMemoryTTF(museo900_binary, sizeof museo900_binary, 40);
			io.Fonts->AddFontFromMemoryTTF(&font_awesome_binary, sizeof font_awesome_binary, 40, &icons_config, icon_ranges);
			io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());

			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(pDevice, pContext);
			ImGui::StyleColorsDark();
			{
				D3D11_DEPTH_STENCIL_DESC depthStencilDescFalse = {};
				depthStencilDescFalse.DepthEnable = false;
				depthStencilDescFalse.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				depthStencilDescFalse.DepthFunc = D3D11_COMPARISON_GREATER;
				pDevice->CreateDepthStencilState(&depthStencilDescFalse, &depthStencilStateFalse);
			}
			gui_init = true;
		}
		else
			return opresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (!sGreen) GenerateShader(pDevice, &sGreen, 1.0f, 0.0f, 1.0f);

	Gui->Mainwindow();

	ImGui::EndFrame();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return opresent(pSwapChain, SyncInterval, Flags);
}
void __stdcall impl::D3D11::hkDrawIndexed11(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {
	static auto odrawIndexed = g_Hooks.oDrawIndexed->Getstdcall<HRESULT, ID3D11DeviceContext*, UINT, UINT, INT>();
	auto D3DESP = moduleMgr->getModule<D3DEsp>();
	ID3D11Buffer* veBuffer;UINT veWidth;
	UINT Stride;UINT veBufferOffset;D3D11_BUFFER_DESC veDesc;
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veBuffer->Release();veBuffer = NULL;
	}
	ID3D11Buffer* inBuffer;DXGI_FORMAT inFormat;
	UINT  inOffset;D3D11_BUFFER_DESC indesc;
	UINT inWidth;
	pContext->IAGetIndexBuffer(&inBuffer, &inFormat, &inOffset);
	if (inBuffer) {
		inBuffer->GetDesc(&indesc);	
		inBuffer->Release(); inBuffer = NULL;
	}
	if (Stride == 40 && D3DESP->isEnabled()) {
		if (IndexCount == 5124 ||
			IndexCount == 5250 ||
			IndexCount == 1776) {
			pContext->OMGetDepthStencilState(&oDepthStencilState, 0); //need stencilref for optimisation later
			pContext->OMSetDepthStencilState(depthStencilStateFalse, 0); //depth off
			pContext->PSSetShader(sGreen, NULL, NULL);
		}
	}
	odrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

LRESULT __stdcall impl::D3D11::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	switch (uMsg)
	{
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
		g_ResizeHeight = (UINT)HIWORD(lParam);
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
void impl::D3D11::CleanupRenderTarget() {
	if (mainRenderTargetView) { mainRenderTargetView->Release();mainRenderTargetView = nullptr; }
}
HRESULT impl::D3D11::GenerateShader(ID3D11Device* pD3DDevice, ID3D11PixelShader** pShader, float r, float g, float b) {
	char szCast[] = "struct VS_OUT"
		"{"
		"    float4 Position   : SV_Position;"
		"    float4 Color    : COLOR0;"
		"};"

		"float4 main( VS_OUT input ) : SV_Target"
		"{"
		"    float4 fake;"
		"    fake.a = 1.0f;"
		"    fake.r = %f;"
		"    fake.g = %f;"
		"    fake.b = %f;"
		"    return fake;"
		"}";
	ID3D10Blob* pBlob;
	char szPixelShader[1000];
	sprintf_s(szPixelShader, szCast, r, g, b);
	HRESULT hr = D3DCompile(szPixelShader, sizeof(szPixelShader), "shader", NULL, NULL, "main", "ps_4_0", NULL, NULL, &pBlob, NULL);
	if (FAILED(hr))
		return hr;
	hr = pD3DDevice->CreatePixelShader((DWORD*)pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pShader);
	if (FAILED(hr))
		return hr;
	return S_OK;
}
void impl::D3D11::CreateRenderTarget() {
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
	pBackBuffer->Release();
}

void impl::D3D11::init() {
	HMODULE hDXGIDLL = 0;
	do {
		hDXGIDLL = GetModuleHandle("dxgi.dll");
		LOG_INFO("GetModuleHandle with dxgi.dll..");
	} while (!hDXGIDLL);
	IDXGISwapChain* pSwapChain;
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
	LOG_INFO("CreateWindowA >> hWnd {%d}", hWnd);
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	LOG_INFO("Create directX device and swapchain!");
	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		requestedLevels, sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL), D3D11_SDK_VERSION,
		&scd, &pSwapChain, &pDevice, &obtainedLevel, &pContext))) {
		LOG_DEBUG("Failed to create directX device and swapchain! [Error]");return;
	}

	uintptr_t** pSwapChainVtable = reinterpret_cast<uintptr_t**>(reinterpret_cast<uintptr_t**>(pSwapChain)[0][8]);
	g_Hooks.oPresent = std::make_unique<FuncHook>(pSwapChainVtable, hkPresent11);

	uintptr_t** pContextVTable = reinterpret_cast<uintptr_t**>(reinterpret_cast<uintptr_t**>(pContext)[0][12]);
	g_Hooks.oDrawIndexed = std::make_unique<FuncHook>(pContextVTable, hkDrawIndexed11);
	LOG_INFO("pSwapChainVtable->[%p] and pContextVTable->[%p]", pSwapChainVtable, pContextVTable);

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();
}

BOOL __stdcall impl::Opengl32::hkWGLSwapBuffers(HDC hdc) {
	auto oWGLSwapbuffers = g_Hooks.oWGLSwapBuffers->Getstdcall<BOOL, HDC>();

	return oWGLSwapbuffers(hdc);
}

void impl::Opengl32::init() {
	HMODULE hPENGLDLL = 0;
	hPENGLDLL = GetModuleHandle("opengl32.dll");
	if (hPENGLDLL) {
		LOG_INFO("GetModuleHandle with opengl32.dll..{%p}", hPENGLDLL);
	}
	else LOG_DEBUG("GetModuleHandle with opengl32.dll is NULL!..{%p}", hPENGLDLL);
	BOOL oWGLSwapBuffers;void* oGLBegin;
	void* oGLClear;void* oGLColor4f;
	oWGLSwapBuffers = (BOOL)GetProcAddress(hPENGLDLL, "wglSwapBuffers");
	oGLBegin = GetProcAddress(hPENGLDLL, "glBegin");
	oGLClear = GetProcAddress(hPENGLDLL, "glClear");
	oGLColor4f = GetProcAddress(hPENGLDLL, "glColor4f");

	g_Hooks.oDrawIndexed = std::make_unique<FuncHook>(oWGLSwapBuffers, hkWGLSwapBuffers);
}