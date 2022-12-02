/***************************************************************************************
Author: lvke
Date:2022/12/02 10:50
Description:
Encapsulate vertexshader
****************************************************************************************/
#pragma once
#include "BindableInterface.h"
#include "../Utility/Utility.h"

namespace Twinkle
{

	class VertexShader : public IBindable
	{
	public:
		VertexShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, ID3DBlob* pBlob);
		virtual ~VertexShader();
	public:
		void bind();
	private:
		ID3D11VertexShader* m_pVertexShader{ nullptr };
	};


	VertexShader::VertexShader(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, ID3DBlob* pBlob)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		if (pBlob)
			m_pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	}


	VertexShader::~VertexShader()
	{
		SAFE_RELEASE(m_pVertexShader);
	}


	void VertexShader::bind()
	{
		m_pDeviceContent->VSSetShader(m_pVertexShader, nullptr, 0);
	}
}