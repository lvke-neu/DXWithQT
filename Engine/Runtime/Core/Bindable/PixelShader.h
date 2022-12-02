/***************************************************************************************
Author: lvke
Date:2022/12/02 11:14
Description:
Encapsulate pixelshader
****************************************************************************************/
#pragma once
#include "BindableInterface.h"
#include "../Utility/Utility.h"

namespace Twinkle
{
	class PixelShader : public IBindable
	{
	public:
		PixelShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, ID3DBlob* pBlob);
		virtual ~PixelShader();
	public:
		void bind();
	private:
		ID3D11PixelShader* m_pPixelShader{ nullptr };
	};

	PixelShader::PixelShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, ID3DBlob* pBlob)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		if (pBlob)
			m_pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	}

	PixelShader::~PixelShader()
	{
		SAFE_RELEASE(m_pPixelShader);
	}

	void PixelShader::bind()
	{
		m_pDeviceContent->PSSetShader(m_pPixelShader, nullptr, 0);
	}
}