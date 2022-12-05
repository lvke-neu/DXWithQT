/***************************************************************************************
Author: lvke
Date:2022/12/03 20:02
Description:
Encapsulate texture
****************************************************************************************/
#pragma once

#include "BindableInterface.h"

namespace Twinkle
{
	class Texture : public IBindable
	{
		friend class RenderSystem;
	private:
		Texture(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, UINT startSlot, const std::string& relativeFilePath);
		virtual ~Texture();
		virtual void bind() override;
	private:
		ID3D11ShaderResourceView* m_pShaderResourceView{ nullptr };
		UINT m_startSlot = 0;
	};

	Texture::Texture(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, UINT startSlot, const std::string& relativeFilePath)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		m_startSlot = startSlot;

		SAFE_RELEASE(m_pShaderResourceView);
		m_pShaderResourceView = LoadTexture(relativeFilePath);
	}

	Texture::~Texture()
	{
		SAFE_RELEASE(m_pShaderResourceView);
	}

	void Texture::bind()
	{
		m_pDeviceContent->PSSetShaderResources(m_startSlot, 1u, &m_pShaderResourceView);
	}
}