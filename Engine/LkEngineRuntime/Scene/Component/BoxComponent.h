/***************************************************************************************
Author: lvke
Date:2022/9/19 20:17
Description:
Box Component
****************************************************************************************/

#pragma once

#include "Interface/ComponentInterface.h"

namespace LkEngine
{


	class BoxComponent : public IComponent
	{
	public:
		BoxComponent(void** parameter);
		BoxComponent(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	public:
		virtual void buildMesh() override;
		virtual void createVertexLayout(const ComPtr<ID3DBlob>& blob) override;
		virtual void bindPipeState() override;
		virtual void draw() override;
	private:
		ComPtr<ID3D11Buffer> m_pVertexBuffer{ nullptr };
		ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };

		UINT m_indexCount = 0;
	};
}

