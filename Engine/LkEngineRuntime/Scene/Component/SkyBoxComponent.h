/***************************************************************************************
Author: lvke
Date:
Description:
SkyBox Component
****************************************************************************************/

#pragma once

#include "BoxComponent.h"

namespace LkEngine
{
	class SkyBoxComponent : public BoxComponent
	{
	public:
		SkyBoxComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
		void setTexture(const std::string& texture);
		void draw();
	};
}