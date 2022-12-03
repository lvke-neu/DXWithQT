#pragma once

#include <map>
#include "BindableInterface.h"

namespace Twinkle
{
	enum SamplerStateType
	{
		SSLinearWrap
	};

	class SamplerStateDesc
	{
	public:
		static void init();
		static std::map<SamplerStateType, D3D11_SAMPLER_DESC> samplerStateTyPeDesc;
	private:
		static bool bIsInit;
	};
}
