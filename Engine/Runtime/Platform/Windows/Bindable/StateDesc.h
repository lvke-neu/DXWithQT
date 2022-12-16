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

	enum DepthStencilStateType
	{
		DSSDefault,
		DSSNoDepthTest
	};

	class StateDesc
	{
	public:
		static void init();
		static std::map<SamplerStateType, D3D11_SAMPLER_DESC> samplerStateTypeDesc;
		static std::map<RasterizerStateType, D3D11_RASTERIZER_DESC> rasterizerStateTypeDesc;
		static std::map<BlendStateType, D3D11_BLEND_DESC> blendStateTypeDesc;
		static std::map<DepthStencilStateType, D3D11_DEPTH_STENCIL_DESC> depthStencilStateTypeDesc;
	private:
		static bool bIsInit;
	};
}
