/***************************************************************************************
Author: lvke
Date:2022/12/02 11:14
Description:
Encapsulate pixelshader
****************************************************************************************/
#pragma once

#include "BindableInterface.h"

namespace Twinkle
{
	class PixelShader : public IBindable
	{
		friend class BindableManager;
	private:
		PixelShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::string& relativeFilePath);
		virtual ~PixelShader();
		virtual void bind() override;
	private:
		ID3DBlob* m_pBlob{ nullptr };
		ID3D11PixelShader* m_pPixelShader{ nullptr };
	};

	PixelShader::PixelShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::string& relativeFilePath)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;

		m_pBlob = Singleton<DirectX11Manager>::GetInstance().ReadFileToBlob(relativeFilePath);
		if (m_pBlob)
			m_pDevice->CreatePixelShader(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	}

	PixelShader::~PixelShader()
	{
		SAFE_RELEASE(m_pBlob);
		SAFE_RELEASE(m_pPixelShader);
	}

	void PixelShader::bind()
	{
		m_pDeviceContent->PSSetShader(m_pPixelShader, nullptr, 0);
	}
}