#pragma once

#include <map>
#include "BindableInterface.h"

namespace Twinkle
{
	enum SamplerStateType
	{
		SSLinearWrap
	};

	enum RasterizerStateType
	{
		RSDefault,
		RSNoCull,
		RSWireframe
	};

	enum BlendStateType
	{
		BSDefault,
		BSTransparent
	};

	class StateDesc
	{
	public:
		static void init();
		static std::map<SamplerStateType, D3D11_SAMPLER_DESC> samplerStateTypeDesc;
		static std::map<RasterizerStateType, D3D11_RASTERIZER_DESC> rasterizerStateTypeDesc;
		static std::map<BlendStateType, D3D11_BLEND_DESC> blendStateTypeDesc;
	private:
		static bool bIsInit;
	};
}
