#pragma once
#include "../../../Utils/logger.h"
#include "IModule.h"
#include <d3d11.h>
#include "../../Menu/ImGuiMenu.h"
#include "../../../includes/detours.h"
#include "../../../includes/imgui/imgui.h"
#include "../../../includes/imgui/imgui_impl_dx11.h"
#include "../../../includes/imgui/imgui_impl_win32.h"
#include <exception>
#include <d3dcompiler.h>
#include <string>
#include <DirectXMath.h>
#include <vector>
#pragma comment(lib, "winmm.lib ")
typedef void(__stdcall* DrawIndexed) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
static DrawIndexed oDrawIndexedl;
static ID3D11PixelShader* sGreen = NULL;
class D3DEsp :public IModule {
private:
	bool Enable = false;
public:
	D3DEsp();
	~D3DEsp();

	virtual void onEnable();
	virtual void onDisable();
	virtual const char* getModuleName();
};
namespace DrawIndexed11 {
	HRESULT GenerateShader(ID3D11Device* pD3DDevice, ID3D11PixelShader** pShader, float r, float g, float b);
	void __stdcall hkDrawIndexed11(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
}
