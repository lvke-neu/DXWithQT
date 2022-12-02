#include "BindableManager.h"
#include "../Engine/Engine.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "PixelShader.h"


namespace Twinkle
{
	BindableManager::BindableManager()
	{
		m_pDevice = Singleton<Engine>::GetInstance().getDevice();
		m_pDeviceContent = Singleton<Engine>::GetInstance().getDeviceContent();
	}

	IBindable* BindableManager::CreateVertexShader(ID3DBlob* pBlob)
	{
		return new VertexShader(m_pDevice, m_pDeviceContent, pBlob);
	}

	IBindable* BindableManager::CreateInputLayout(ID3DBlob* pBlob, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
	{
		return new InputLayout(m_pDevice, m_pDeviceContent, pBlob, ied);
	}

	IBindable* BindableManager::CreatePixelShader(ID3DBlob* pBlob)
	{
		return new PixelShader(m_pDevice, m_pDeviceContent, pBlob);
	}

	void BindableManager::DrawCall(IBindable* vertexBuffer, IBindable* indexbuffer,
		IBindable* vertexShader, IBindable* inputLayout, IBindable* pixelShader, D3D11_PRIMITIVE_TOPOLOGY drawType)
	{
		if(vertexBuffer)
			vertexBuffer->bind();
		if (indexbuffer)
			indexbuffer->bind();
		if (vertexShader)
			vertexShader->bind();
		if (inputLayout)
			inputLayout->bind();
		if (pixelShader)
			pixelShader->bind();
		m_pDeviceContent->IASetPrimitiveTopology(drawType);
		m_pDeviceContent->DrawIndexed(indexbuffer->getIndexCount(), 0, 0);
	}

	void BindableManager::Release(IBindable*& bindable)
	{
		SAFE_DELETE_SETNULL(bindable);
	}
}