#include "StateDesc.h"

namespace Twinkle
{
	bool StateDesc::bIsInit = false;
	std::map<SamplerStateType, D3D11_SAMPLER_DESC> StateDesc::samplerStateTypeDesc;
	std::map<RasterizerStateType, D3D11_RASTERIZER_DESC> StateDesc::rasterizerStateTypeDesc;
	std::map<BlendStateType, D3D11_BLEND_DESC> StateDesc::blendStateTypeDesc;

	void StateDesc::init()
	{
		if (bIsInit)
			return;

		//SSLinearWrap
		D3D11_SAMPLER_DESC samplerDescSSLinearWrap;
		ZeroMemory(&samplerDescSSLinearWrap, sizeof(samplerDescSSLinearWrap));
		samplerDescSSLinearWrap.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
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

		//BSDefault
		D3D11_BLEND_DESC bsDesc1;
		ZeroMemory(&bsDesc1, sizeof(bsDesc1));
		bsDesc1.AlphaToCoverageEnable = false;
		bsDesc1.IndependentBlendEnable = false;
		bsDesc1.RenderTarget[0].BlendEnable = false;
		bsDesc1.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc1.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		bsDesc1.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bsDesc1.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc1.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bsDesc1.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bsDesc1.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blendStateTypeDesc.insert({ BSDefault, bsDesc1 });

		//BSTransparent
		D3D11_BLEND_DESC bsDesc2; 
		ZeroMemory(&bsDesc2, sizeof(bsDesc2));
		bsDesc2.AlphaToCoverageEnable = false;
		bsDesc2.IndependentBlendEnable = false;
		bsDesc2.RenderTarget[0].BlendEnable = true;
		bsDesc2.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		bsDesc2.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc2.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc2.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bsDesc2.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc2.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bsDesc2.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateTypeDesc.insert({ BSTransparent, bsDesc2 });

		bIsInit = true;
	}
}