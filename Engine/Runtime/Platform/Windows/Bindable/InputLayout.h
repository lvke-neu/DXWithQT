/***************************************************************************************
Author: lvke
Date:2022/12/02 11:02
Description:
Encapsulate inputlayout
****************************************************************************************/
#pragma once

#include "BindableInterface.h"
#include <vector>

namespace Twinkle
{
	class InputLayout : public IBindable
	{
		friend class BindableManager;
	private:
		InputLayout(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::string& relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied);
		virtual ~InputLayout();
		virtual void bind() override;
	private:
		ID3DBlob* m_pBlob{ nullptr };
		ID3D11InputLayout* m_pInputLayout{ nullptr };
	};

	InputLayout::InputLayout(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::string& relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;

		m_pBlob = Singleton<DirectX11Manager>::GetInstance().ReadFileToBlob(relativeFilePath);
		if (m_pBlob)
		{
			m_pDevice->CreateInputLayout(ied.data(), (UINT)ied.size(), m_pBlob->GetBufferPointer(), m_pBlob->GetBufferSize(), &m_pInputLayout);
		}	
	}

	InputLayout::~InputLayout()
	{
		SAFE_RELEASE(m_pBlob);
		SAFE_RELEASE(m_pInputLayout);
	}

	void InputLayout::bind()
	{
		m_pDeviceContent->IASetInputLayout(m_pInputLayout);
	}
}