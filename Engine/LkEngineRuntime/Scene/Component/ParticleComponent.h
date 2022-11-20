/***************************************************************************************
Author: lvke
Date:
Description:
Particle Component
****************************************************************************************/
#pragma once

#include "Interface/ComponentInterface.h"

namespace LkEngine
{
	class ParticleComponent : public IComponent
	{
	public:
		ParticleComponent(void** parameter);
		ParticleComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() {};
	};
}
