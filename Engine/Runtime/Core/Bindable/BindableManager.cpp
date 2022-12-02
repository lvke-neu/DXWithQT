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

	void BindableManager::Release(IBindable*& bindable)
	{
		SAFE_DELETE_SETNULL(bindable);
	}

	void BindableManager::Release(std::vector<IBindable*>& constantBuffers)
	{
		for (auto& constantBuffer : constantBuffers)
		{
			Release(constantBuffer);
		}
	}
}