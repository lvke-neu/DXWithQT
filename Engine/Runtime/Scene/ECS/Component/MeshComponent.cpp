#include "MeshComponent.h"

namespace Twinkle
{
	MeshComponent::MeshComponent()
	{

	}

	MeshComponent::~MeshComponent()
	{
		Singleton<RenderSystem>::GetInstance().Release(m_vertexBuffer);
		Singleton<RenderSystem>::GetInstance().Release(m_indexBuffer);
		Singleton<RenderSystem>::GetInstance().Release(m_vertexShader);
		Singleton<RenderSystem>::GetInstance().Release(m_inputLayout);
		Singleton<RenderSystem>::GetInstance().Release(m_pixelShader);
		Singleton<RenderSystem>::GetInstance().Release(m_texture);
		Singleton<RenderSystem>::GetInstance().Release(m_samplerState);
	}

	void MeshComponent::setVsShader(const std::string & relativeFilePath)
	{
		Singleton<RenderSystem>::GetInstance().Release(m_vertexShader);
		m_vertexShader = Singleton<RenderSystem>::GetInstance().CreateVertexShader(relativeFilePath);
	}

	void MeshComponent::setInputLayout(const std::string & relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
	{
		Singleton<RenderSystem>::GetInstance().Release(m_inputLayout);
		m_inputLayout = Singleton<RenderSystem>::GetInstance().CreateInputLayout(relativeFilePath, ied);
	}

	void MeshComponent::setPsShader(const std::string & relativeFilePath)
	{
		Singleton<RenderSystem>::GetInstance().Release(m_pixelShader);
		m_pixelShader = Singleton<RenderSystem>::GetInstance().CreatePixelShader(relativeFilePath);
	}

	void MeshComponent::setTexture(const std::string & relativeFilePath)
	{
		Singleton<RenderSystem>::GetInstance().Release(m_texture);
		m_texture = Singleton<RenderSystem>::GetInstance().CreateTexture(0, relativeFilePath);
	}

	void MeshComponent::setSamplerState(SamplerStateType samplerStateType)
	{
		Singleton<RenderSystem>::GetInstance().Release(m_samplerState);
		m_samplerState = Singleton<RenderSystem>::GetInstance().CreateSamplerState(0, samplerStateType);
	}

	void MeshComponent::tick(float deltaTime)
	{
		Singleton<RenderSystem>::GetInstance().DrawCall<UINT32>(m_vertexBuffer, m_indexBuffer, m_vertexShader, m_inputLayout, m_pixelShader,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, m_texture, m_samplerState);
	}
}


