/***************************************************************************************
Author: lvke
Date:2022/9/21 19:03
Description:
Plane Component
****************************************************************************************/

#pragma once

#include "Interface/ComponentInterface.h"

namespace LkEngine
{
	class PlaneComponent : public IComponent
	{
	public:
		PlaneComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
		virtual void drawShadowMap() override;
		void setTextureTmp(ID3D11ShaderResourceView* pSRV) { m_pTexture = pSRV; }
	};
}

