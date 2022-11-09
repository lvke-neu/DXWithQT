/***************************************************************************************
Author: lvke
Date:2022/11/06 10:58
Description:
Cylinder Component
****************************************************************************************/

#pragma once

#include "Interface/ComponentInterface.h"

namespace LkEngine
{
	class CylinderComponent : public IComponent
	{
	public:
		CylinderComponent(void** parameter);
		CylinderComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
	};
}

