#include "D3DEsp.h"
#include "../../../includes/kiero/kiero.h"

D3DEsp::D3DEsp() :IModule("D3DEsp",'0', Category::VISUAL, "") {
//	this->registerBoolSetting("D3dEsp", &this->Enable, this->Enable);
}

D3DEsp::~D3DEsp()
{
}
void D3DEsp::onEnable() {
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11))
		{
			kiero::bind(12, (void**)&oDrawIndexedl, DrawIndexed11::hkDrawIndexed11);
			LOG_INFO("Kiero Init {OK}");
			init_hook = true;
		}
	} while (!init_hook);
}

void D3DEsp::onDisable()
{
}

const char* D3DEsp::getModuleName()
{
	return "D3dEsp";
}
bool _init = false;
HRESULT DrawIndexed11::GenerateShader(ID3D11Device* pD3DDevice, ID3D11PixelShader** pShader, float r, float g, float b)
{
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
void __stdcall DrawIndexed11::hkDrawIndexed11(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {
	ID3D11Buffer* veBuffer;
	UINT veWidth;
	UINT Stride;
	UINT veBufferOffset;
	D3D11_BUFFER_DESC veDesc;

	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veWidth = veDesc.ByteWidth;
	}
	if (NULL != veBuffer) {
		veBuffer->Release();
		veBuffer = NULL;
	}
	ID3D11Buffer* inBuffer;
	DXGI_FORMAT inFormat;
	UINT        inOffset;
	D3D11_BUFFER_DESC indesc;
	UINT inWidth; // remove??
	pContext->IAGetIndexBuffer(&inBuffer, &inFormat, &inOffset);
	if (inBuffer) {
		inBuffer->GetDesc(&indesc);
		inWidth = indesc.ByteWidth;
	}

	if (inBuffer != NULL) { inBuffer->Release(); inBuffer = NULL; }

	ID3D11Buffer* pscBuffer;
	UINT pscWidth;
	D3D11_BUFFER_DESC pscdesc;

	//get pscdesc.ByteWidth
	pContext->PSGetConstantBuffers(0, 1, &pscBuffer);
	if (pscBuffer) {
		pscBuffer->GetDesc(&pscdesc);
		pscWidth = pscdesc.ByteWidth;
	}
	if (NULL != pscBuffer) {
		pscBuffer->Release();
		pscBuffer = NULL;
	}
	if (!sGreen) {
		DrawIndexed11::GenerateShader(pDevice, &sGreen, 0.0f, 1.0f, 0.0f); //green
	}
	pContext->PSSetShader(sGreen, NULL, NULL);

	return oDrawIndexedl(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}