#include <tchar.h>
#include "ImGuiMenu.h"
//#include "../../includes/stb_image/stb_image.h"
#include "../Module/ModManager.h"
#include "Font/background_pic.h"
#include "Font/segue_font.h"
#include "../../Misc/icoA.h"
#include "../../Misc/icoB.h"
#include "Font/ico_font.h"
#include "../Menu/Hub.h"
#include "Font/Font.h"
#include "gui.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../includes/stb_image/imageloaderdx11.h"
//ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
HWND g_hWnd = nullptr;
ImFont* font = nullptr;
ImFont* fontG = nullptr;
ImFont* ico = nullptr;
ImFont* ico_combo = nullptr;
ImFont* ico_button = nullptr;
ImFont* ico_grande = nullptr;
ImFont* segu = nullptr;
ImFont* default_segu = nullptr;
ImFont* bold_segu = nullptr;
ImFont* ico_log = nullptr;
extern ImVec4* colors;
extern ImGuiStyle* style;

enum Color_
{
	rainbow,
	Grey,
	Blue,
	Custom
};
enum Module
{
	_Float,
	_Int,
	_Bool
};
ImVec4* ImColorRGB();
void CleanupRenderTarget();
void CreateRenderTarget();
void ImGuiMenu::InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiContext& g = *GImGui;
	ImFontConfig Font_cfg;
	Font_cfg.FontDataOwnedByAtlas = false;

	io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());
	font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 28.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	fontG = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
	default_segu = io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 22, NULL, io.Fonts->GetGlyphRangesCyrillic());
	segu = io.Fonts->AddFontFromMemoryTTF(&seguoe, sizeof seguoe, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());
	bold_segu = io.Fonts->AddFontFromMemoryTTF(&bold_segue, sizeof bold_segue, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 24, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_combo = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 19, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_button = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 25, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_grande = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ico_log = io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 24.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall ImGuiMenu::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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

float color_edit4[4] = { 1.00f, 1.00f, 1.00f, 1.000f };
float accent_color[4] = { 0.745f, 0.151f, 0.151f, 1.000f };
//float BackGround_color = ImColor(9, 9, 9, 180);
float size_child = 0;
bool init = false;
bool active = false;
int tab_count = 0, tabs = 0;
ImVec4 BackGround_color = ImVec4(0, 0, 0, 0.2000f);
bool gui_init = true;
HRESULT __stdcall ImGuiMenu::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;

			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ImGui::StyleColorsDark();

			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	static int Color_ = Grey;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	switch (Color_)
	{
	case rainbow:
		colors[ImGuiCol_Border] = *ImColorRGB();
		//	colors[ImGuiCol_FrameBg]= *ImColorRGB();
		colors[ImGuiCol_Text] = *ImColorRGB();
		break;
	case Grey:
		ImGui::StyleColorsDark();
		break;
	case Blue:
		style->Colors[ImGuiCol_Button] = ImColor(51, 120, 255, 255);
		style->Colors[ImGuiCol_ButtonHovered] = ImColor(71, 140, 255, 255);
		style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 100, 225, 255);

		style->Colors[ImGuiCol_FrameBg] = ImColor(54, 54, 54, 150);
		style->Colors[ImGuiCol_FrameBgActive] = ImColor(42, 42, 42, 150);
		style->Colors[ImGuiCol_FrameBgHovered] = ImColor(100, 100, 100, 150);

		style->Colors[ImGuiCol_CheckMark] = ImColor(51, 120, 255, 255);

		style->Colors[ImGuiCol_SliderGrab] = ImColor(51, 120, 255, 255);
		style->Colors[ImGuiCol_SliderGrabActive] = ImColor(31, 100, 225, 255);

		style->Colors[ImGuiCol_Header] = ImColor(51, 120, 255, 255);
		style->Colors[ImGuiCol_HeaderHovered] = ImColor(71, 140, 255, 255);
		style->Colors[ImGuiCol_HeaderActive] = ImColor(31, 100, 225, 255);
		break;
	case Custom:
		break;
	}
	if (gui_init) {
		ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(905, 624), ImGuiCond_Once);
		if (ImGui::Begin("Hola!", NULL,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoBackground)) {
				{
					ImVec2 P1, P2;
					ImDrawList* pDrawList;
					const auto& p = ImGui::GetWindowPos();
					const auto& pWindowDrawList = ImGui::GetWindowDrawList();
					const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
					pBackgroundDrawList->AddRectFilled(ImVec2(0.000f + p.x, 0.000f + p.y), ImVec2(905 + p.x, 624 + p.y), ImColor(BackGround_color), 10); // Background

					pWindowDrawList->AddRectFilled(ImVec2(189.000f + p.x, 75.000f + p.y), ImVec2(903 + p.x, 76 + p.y), ImColor(25, 25, 25, 180), 10); // bar line

					pWindowDrawList->AddRectFilled(ImVec2(0.000f + p.x, 0.000f + p.y), ImVec2(190 + p.x, 624 + p.y), ImGui::GetColorU32(ImGuiCol_ChildBg), 10, ImDrawFlags_RoundCornersLeft); // bar line

					const int vtx_idx_1 = pWindowDrawList->VtxBuffer.Size;

					pWindowDrawList->AddText(ico_log, 40.f, ImVec2(55.000f + p.x, 20.000f + p.y), ImColor(0.60f, 0.60f, 0.60f, 0.70f), u8"\u9B08");

					pWindowDrawList->AddText(bold_segu, 40.f, ImVec2(200.000f + p.x, 15.000f + p.y), ImColor(0.60f, 0.60f, 0.60f, 0.70f), "SimpleMod");

					pWindowDrawList->AddRectFilled(ImVec2(200.000f + p.x, 55.000f + p.y), ImVec2(223 + 200 + p.x, 52 + p.y), ImColor(colors[ImGuiCol_FrameBg]), 10); // bar line

					const int vtx_idx_2 = pWindowDrawList->VtxBuffer.Size;

					ImGui::ShadeVertsLinearColorGradientKeepAlpha(pWindowDrawList, vtx_idx_1, vtx_idx_2, ImVec2(0 + p.x, 0 + p.y), ImVec2(200 + p.x, 20 + p.y), ImColor(0.25f, 0.25f, 0.25f, 0.50f), ImColor(0.60f, 0.60f, 0.60f, 1.00f));

					ImGui::SetCursorPosY(80);
					//按钮控制
					{
						if (ImGui::TabButton("N", "Combet", ImVec2(190, 40)) && tab_count != Category::COMBAT) {
							tab_count = Category::COMBAT;
							active = true;
						}

						if (ImGui::TabButton("I", "Visuals", ImVec2(190, 40)) && tab_count != Category::VISUAL) {
							tab_count = Category::VISUAL;
							active = true;
						}

						if (ImGui::TabButton("R", "Player", ImVec2(190, 40)) && tab_count != Category::PLAYER) {
							tab_count = Category::PLAYER;
							active = true;
						}
						if (ImGui::TabButton("T", "Movement", ImVec2(190, 40)) && tab_count != Category::MOVEMENT) {
							tab_count = Category::MOVEMENT;
							active = true;
						}
						if (ImGui::TabButton("H", "World", ImVec2(190, 40)) && tab_count != Category::WORLD) {
							tab_count = Category::WORLD;
							active = true;
						}
						if (ImGui::TabButton("O", "Misc", ImVec2(190, 40)) && tab_count != Category::MISC) {
							tab_count = Category::MISC;
							active = true;
						}
						if (ImGui::TabButton("U", "Client", ImVec2(190, 40)) && tab_count != Category::CLIENT) {
							tab_count = Category::CLIENT;
							active = true;
						}
						ImGui::PushFont(font);
						if (ImGui::TabButton("", u8"赞助", ImVec2(190, 40))) {
							ShellExecuteA(NULL, "open", "https://afdian.net/a/QwQLL", NULL, NULL, SW_SHOWNORMAL);
						}
						ImGui::PopFont();
						if (active) {
							if (size_child <= 10) size_child += 1 / ImGui::GetIO().Framerate * 60.f;
							else { active = false; tabs = tab_count; };
						}
						else {
							if (size_child >= 0) size_child -= 1 / ImGui::GetIO().Framerate * 60.f;
						}
					}
					pWindowDrawList->AddText(segu, 40.f, ImVec2(51.000f + p.x, 548.000f + p.y), ImColor(colors[ImGuiCol_Text]), "QwQ");

					const int vtx_idx_3 = pWindowDrawList->VtxBuffer.Size;

					const int vtx_idx_4 = pWindowDrawList->VtxBuffer.Size;

					ImGui::ShadeVertsLinearColorGradientKeepAlpha(pWindowDrawList, vtx_idx_3, vtx_idx_4, ImVec2(97.000f + p.x, 547.000f + p.y), ImVec2(200.000f + p.x, 567.000f + p.y), ImColor(0.35f, 0.35f, 0.35f, 0.50f), ImColor(0.90f, 0.90f, 0.90f, 1.00f));

					hub.RenderMenu();
					ImGui::SetCursorPos(ImVec2(203, 88 - size_child));
					ImGui::PushFont(fontG);
					switch (tabs) {
					case Category::COMBAT: {
						ImGui::BeginChild("Combet", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::COMBAT)
									hub.RenderModSettings(mod.get());
							}
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("extend", ImVec2(339, 503), true); {
						}ImGui::EndChild();
					}break;
					case Category::MOVEMENT: {
						ImGui::BeginChild("Movement", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::MOVEMENT)
									hub.RenderModSettings(mod.get());
							}
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("extend", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::MOVEMENT)
									hub.Renderslidermodsettings(mod.get());
							}
						}ImGui::EndChild();
					}break;
					case Category::PLAYER: {
						ImGui::BeginChild("Player", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::PLAYER)
									hub.RenderModSettings(mod.get());
							}
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("extend", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::PLAYER)
									hub.Renderslidermodsettings(mod.get());
							}
						}ImGui::EndChild();
					}break;
					case Category::VISUAL: {
						ImGui::BeginChild("Visual", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::VISUAL)
									hub.RenderModSettings(mod.get());
							}
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("extend", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::VISUAL)
									hub.Renderslidermodsettings(mod.get());
							}
						}ImGui::EndChild();
					}break;
					case Category::WORLD: {
						ImGui::BeginChild("World", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::WORLD)
									hub.RenderModSettings(mod.get());
							}
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("extend", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::WORLD)
									hub.Renderslidermodsettings(mod.get());
							}
						}ImGui::EndChild();
					}break;
					case Category::MISC: {
						ImGui::BeginChild("Misc", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::MISC)
									hub.RenderModSettings(mod.get());
							}
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("extend", ImVec2(339, 503), true); {
							for (auto& mod : moduleMgr->moduleList) {
								if (mod->getCateg() == Category::MISC)
									hub.Renderslidermodsettings(mod.get());
							}
						}ImGui::EndChild();
					}break;
					case Category::CLIENT:
					{
						ImGui::BeginChild("Client", ImVec2(339, 260), true); {
							ImGui::ColorEdit4("Widget Color", (float*)&accent_color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("Background Color", (float*)&BackGround_color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("Text", (float*)&colors[ImGuiCol_Text], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							static const char* items[]{ "Rainbow","Grey","Blue","Custom" };
							ImGui::Combo("Aimbot Mode", &Color_, items, IM_ARRAYSIZE(items), 5);
						}ImGui::EndChild();
						ImGui::SetCursorPos(ImVec2(203, 353 - size_child));
						gui.group_box("Window properties", ImVec2(339, 250)); {
							ImGui::SetCursorPos(ImVec2(203, 0));
							ImGui::SliderFloat("WindowRounding", &style->WindowRounding, 0, 64, "%.f");
							ImGui::SliderFloat("WindowMinSize", (float*)&style->WindowMinSize, 0, 64, "%.f");
							ImGui::SliderFloat("WindowTitleAlign", (float*)&style->WindowTitleAlign, 0, 64, "%.f");
							ImGui::SliderFloat("PopupBorderSize", &style->PopupBorderSize, 0, 64, "%.f");
							ImGui::SliderFloat("FramePadding", (float*)&style->FramePadding, 0, 64, "%.f");
							ImGui::SliderFloat("FrameRounding", &style->FrameRounding, 0, 64, "%.f");
							ImGui::SliderFloat("FrameBorderSize", &style->FrameBorderSize, 0, 64, "%.f");
							ImGui::SliderFloat("ItemSpacing", (float*)&style->ItemSpacing, 0, 64, "%.f");
							ImGui::SliderFloat("ItemInnerSpacing", (float*)&style->ItemInnerSpacing, 0, 64, "%.f");
							ImGui::SliderFloat("IndentSpacing", &style->IndentSpacing, 0, 64, "%.f");
							ImGui::SliderFloat("ColumnsMinSpacing", &style->ColumnsMinSpacing, 0, 64, "%.f");
							ImGui::SliderFloat("ScrollbarSize", &style->ScrollbarSize, 0, 64, "%.f");
							ImGui::SliderFloat("ScrollbarRounding", &style->ScrollbarRounding, 0, 64, "%.f");
							ImGui::SliderFloat("WindowBorderSize", &style->WindowBorderSize, 0, 64, "%.f");
							ImGui::SliderFloat("GrabMinSize", &style->GrabMinSize, 0, 64, "%.f");
							ImGui::SliderFloat("GrabRounding", &style->GrabRounding, 0, 64, "%.f");
							ImGui::SliderFloat("TabRounding", &style->TabRounding, 0, 64, "%.f");
							ImGui::SliderFloat("TabBorderSize", &style->TabBorderSize, 0, 64, "%.f");
							ImGui::SliderFloat("ButtonTextAlign", (float*)&style->ButtonTextAlign, 0, 64, "%.f");
							ImGui::SliderFloat("SelectableTextAlign", (float*)&style->SelectableTextAlign, 0, 64, "%.f");

							ImGui::SliderFloat("WindowPadding", (float*)&style->WindowPadding, 0, 64, "%.f");
							ImGui::SliderFloat("ChildRounding", &style->ChildRounding, 0, 64, "%.f");
							ImGui::SliderFloat("ItemSpacing", (float*)&style->ItemSpacing, 0, 64, "%.f");
							ImGui::SliderFloat("ScrollbarSize", &style->ScrollbarSize, 0, 64, "%.f");
							ImGui::SliderFloat("FrameRounding", &style->FrameRounding, 0, 64, "%.f");
							ImGui::SliderFloat("PopupRounding", &style->PopupRounding, 0, 64, "%.f");
							ImGui::SliderFloat("ChildBorderSize", &style->ChildBorderSize, 0, 64, "%.f");
						}gui.end_group_box();
						ImGui::SetCursorPos(ImVec2(555, 88 - size_child));
						ImGui::BeginChild("##control", ImVec2(339, 520), false); {
							ImGui::SetCursorPos(ImVec2(0, 0));
							ImGui::ColorEdit4("TextDisabled", (float*)&colors[ImGuiCol_TextDisabled], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("WindowBg", (float*)&colors[ImGuiCol_WindowBg], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("ChildBg", (float*)&colors[ImGuiCol_ChildBg], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("Border", (float*)&colors[ImGuiCol_Border], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("FrameBg", (float*)&colors[ImGuiCol_FrameBg], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("CheckMark", (float*)&colors[ImGuiCol_CheckMark], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("Header", (float*)&colors[ImGuiCol_Header], ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
						}ImGui::EndChild();
					}break;
					}
					ImGui::PopFont();
				}ImGui::End();

		}
	}
	ImGui::EndFrame();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}
DWORD __stdcall ImGuiMenu::Init() {
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}
ImVec4* ImColorRGB() {
	float time = ImGui::GetTime() * 2; // 获取当前时间
	colors->x = sinf(0.6f * time + 0.0f) * 0.5f + 0.5f;
	colors->y = sinf(0.6f * time + 2.0f) * 0.5f + 0.5f;
	colors->z = sinf(0.6f * time + 4.0f) * 0.5f + 0.5f, 0.7f;
	return colors;
}
void CleanupRenderTarget()
{
	if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = nullptr; }
}
void CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
	pBackBuffer->Release();
}