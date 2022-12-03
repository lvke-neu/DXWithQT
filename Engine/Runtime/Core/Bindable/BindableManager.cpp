#include "BindableManager.h"
#include "../Engine/Engine.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "PixelShader.h"
#include "Texture.h"
#include "SamplerState.h"

namespace Twinkle
{
	std::vector<IBindable*> BindableManager::defaultConstantBuffers;

	BindableManager::BindableManager()
	{
		m_pDevice = Singleton<Engine>::GetInstance().GetDevice();
		m_pDeviceContent = Singleton<Engine>::GetInstance().GetDeviceContent();
	}

	IBindable* BindableManager::CreateVertexShader(const std::string& relativeFilePath)
	{
		return new VertexShader(m_pDevice, m_pDeviceContent, relativeFilePath);
	}

	IBindable* BindableManager::CreateInputLayout(const std::string& relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
	{
		return new InputLayout(m_pDevice, m_pDeviceContent, relativeFilePath, ied);
	}

	IBindable* BindableManager::CreatePixelShader(const std::string& relativeFilePath)
	{
		return new PixelShader(m_pDevice, m_pDeviceContent, relativeFilePath);
	}

	IBindable * BindableManager::CreateTexture(UINT startSlot, const std::string & relativeFilePath)
	{
		return new Texture(m_pDevice, m_pDeviceContent, startSlot, relativeFilePath);
	}

	IBindable * BindableManager::CreateSamplerState(UINT startSlot, SamplerStateType samplerStateType)
	{
		return new SamplerState(m_pDevice, m_pDeviceContent, startSlot, samplerStateType);
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