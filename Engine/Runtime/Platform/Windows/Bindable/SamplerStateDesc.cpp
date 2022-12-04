#include "SamplerStateDesc.h"

namespace Twinkle
{
	bool SamplerStateDesc::bIsInit = false;
	std::map<SamplerStateType, D3D11_SAMPLER_DESC> SamplerStateDesc::samplerStateTyPeDesc;

	void SamplerStateDesc::init()
	{
		if (bIsInit)
			return;

		D3D11_SAMPLER_DESC samplerDescSSLinearWrap;
		samplerDescSSLinearWrap.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDescSSLinearWrap.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescSSLinearWrap.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescSSLinearWrap.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDescSSLinearWrap.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDescSSLinearWrap.MinLOD = 0;
		samplerDescSSLinearWrap.MaxLOD = D3D11_FLOAT32_MAX;

		samplerStateTyPeDesc.insert({ SSLinearWrap , samplerDescSSLinearWrap });

		bIsInit = true;
	}
}