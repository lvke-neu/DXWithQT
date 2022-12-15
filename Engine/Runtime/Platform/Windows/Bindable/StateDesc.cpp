#include "StateDesc.h"

namespace Twinkle
{
	bool StateDesc::bIsInit = false;
	std::map<SamplerStateType, D3D11_SAMPLER_DESC> StateDesc::samplerStateTypeDesc;
	std::map<RasterizerStateType, D3D11_RASTERIZER_DESC> StateDesc::rasterizerStateTypeDesc;

	void StateDesc::init()
	{
		if (bIsInit)
			return;

		//SSLinearWrap
		D3D11_SAMPLER_DESC samplerDescSSLinearWrap;
		ZeroMemory(&samplerDescSSLinearWrap, sizeof(samplerDescSSLinearWrap));
		samplerDescSSLinearWrap.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDescSSLinearWrap.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescSSLinearWrap.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescSSLinearWrap.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescSSLinearWrap.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDescSSLinearWrap.MinLOD = 0;
		samplerDescSSLinearWrap.MaxLOD = D3D11_FLOAT32_MAX;
		samplerStateTypeDesc.insert({ SSLinearWrap , samplerDescSSLinearWrap });

		//RSDefault
		D3D11_RASTERIZER_DESC rsDesc1;
		ZeroMemory(&rsDesc1, sizeof(rsDesc1));
		rsDesc1.FillMode = D3D11_FILL_SOLID;
		rsDesc1.CullMode = D3D11_CULL_BACK;
		rsDesc1.FrontCounterClockwise = FALSE;
		rsDesc1.DepthBias = 0;
		rsDesc1.SlopeScaledDepthBias = 0.0f;
		rsDesc1.DepthBiasClamp = 0.0f;
		rsDesc1.DepthClipEnable = TRUE;
		rsDesc1.ScissorEnable = FALSE;
		rsDesc1.MultisampleEnable = FALSE;
		rsDesc1.AntialiasedLineEnable = FALSE;
		rasterizerStateTypeDesc.insert({RSDefault, rsDesc1 });

		//RSNoCull
		D3D11_RASTERIZER_DESC rsDesc2;
		ZeroMemory(&rsDesc2, sizeof(rsDesc2));
		rsDesc2.FillMode = D3D11_FILL_SOLID;
		rsDesc2.CullMode = D3D11_CULL_NONE;
		rsDesc2.FrontCounterClockwise = false;
		rsDesc2.DepthClipEnable = true;
		rasterizerStateTypeDesc.insert({ RSNoCull, rsDesc2 });

		//RSWireframe
		D3D11_RASTERIZER_DESC rsDesc3;
		ZeroMemory(&rsDesc3, sizeof(rsDesc3));
		rsDesc3.FillMode = D3D11_FILL_WIREFRAME;
		rsDesc3.CullMode = D3D11_CULL_NONE;
		rsDesc3.FrontCounterClockwise = false;
		rsDesc3.DepthClipEnable = true;
		rasterizerStateTypeDesc.insert({ RSWireframe, rsDesc3 });

		bIsInit = true;
	}
}