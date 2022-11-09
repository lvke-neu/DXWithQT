#pragma once

#include "Interface/ComponentInterface.h"

namespace LkEngine
{
	class SpatialImageComponent : public IComponent
	{
	public:
		SpatialImageComponent(void** parameter);
		SpatialImageComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
	};
}