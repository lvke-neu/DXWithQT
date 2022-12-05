/***************************************************************************************
Author: lvke
Date:2022/12/02 10:50
Description:
Encapsulate vertexshader
****************************************************************************************/
#pragma once

#include "BindableInterface.h"

namespace Twinkle
{
	class VertexShader : public IBindable
	{
		friend class RenderSystem;
	private:
		VertexShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::string& relativeFilePath);
		virtual ~VertexShader();
	private:
		virtual void bind() override;
	private:
		ID3DBlob* m_pBlob{ nullptr };
		ID3D11VertexShader* m_pVertexShader{ nullptr };
	};

	VertexShader::VertexShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::string& relativeFilePath)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;

		m_pBlob = ReadFileToBlob(relativeFilePath);
		if (m_pBlob)
			m_pDevice->CreateVertexShader(m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	}

	VertexShader::~VertexShader()
	{
		SAFE_RELEASE(m_pBlob);
		SAFE_RELEASE(m_pVertexShader);
	}

	void VertexShader::bind()
	{
		m_pDeviceContent->VSSetShader(m_pVertexShader, nullptr, 0);
	}
}