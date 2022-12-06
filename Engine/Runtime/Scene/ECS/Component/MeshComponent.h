/***************************************************************************************
Author: lvke
Date:2022/12/05 21:36
Description:
Transform Component
****************************************************************************************/
#pragma once
#include "Interface/ComponentInterface.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

namespace Twinkle
{
	class MeshComponent : public IComponent
	{
	public:
		MeshComponent();
		virtual ~MeshComponent();

		template<class VertexType, class IndexType>
		void setMesh(const std::vector<VertexType>& vertices, const std::vector<IndexType>& indices, DXGI_FORMAT dxgi);
		void setVsShader(const std::string& relativeFilePath);
		void setInputLayout(const std::string& relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied);
		void setPsShader(const std::string& relativeFilePath);
		void setTexture(const std::string& relativeFilePath);
		void setSamplerState(SamplerStateType samplerStateType);

		virtual void tick(float deltaTime) override;
	private:
		IBindable* m_vertexBuffer{ nullptr };
		IBindable* m_indexBuffer{ nullptr };
		IBindable* m_vertexShader{ nullptr };
		IBindable* m_inputLayout{ nullptr };
		IBindable* m_pixelShader{ nullptr };
		IBindable* m_texture{ nullptr };
		IBindable* m_samplerState{ nullptr };
	};

	template<class VertexType, class IndexType>
	void MeshComponent::setMesh(const std::vector<VertexType>& vertices, const std::vector<IndexType>& indices, DXGI_FORMAT dxgiFormat)
	{
		Singleton<RenderSystem>::GetInstance().Release(m_vertexBuffer);
		Singleton<RenderSystem>::GetInstance().Release(m_indexBuffer);
		m_vertexBuffer = Singleton<RenderSystem>::GetInstance().CreateVertexBuffer<VertexType>(vertices);
		m_indexBuffer = Singleton<RenderSystem>::GetInstance().CreateIndexBuffer<IndexType>(indices, dxgiFormat);
	}
}