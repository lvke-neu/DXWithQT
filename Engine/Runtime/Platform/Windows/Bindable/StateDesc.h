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

	class StateDesc
	{
	public:
		static void init();
		static std::map<SamplerStateType, D3D11_SAMPLER_DESC> samplerStateTypeDesc;
		static std::map<RasterizerStateType, D3D11_RASTERIZER_DESC> rasterizerStateTypeDesc;
	private:
		static bool bIsInit;
	};
}
