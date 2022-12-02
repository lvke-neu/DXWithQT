/***************************************************************************************
Author: lvke
Date:2022/12/02 11:02
Description:
Encapsulate inputlayout
****************************************************************************************/
#pragma once
#include "BindableInterface.h"
#include "../Utility/Utility.h"
#include <vector>

namespace Twinkle
{
	class InputLayout : public IBindable
	{
	public:
		InputLayout(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, ID3DBlob* pBlob, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied);
		virtual ~InputLayout();
	public:
		void bind();
	private:
		ID3D11InputLayout* m_pInputLayout{ nullptr };
	};

	InputLayout::InputLayout(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, ID3DBlob* pBlob, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		if (pBlob)
		{
			m_pDevice->CreateInputLayout(ied.data(), (UINT)ied.size(), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &m_pInputLayout);
		}	
	}

	InputLayout::~InputLayout()
	{
		SAFE_RELEASE(m_pInputLayout);
	}

	void InputLayout::bind()
	{
		m_pDeviceContent->IASetInputLayout(m_pInputLayout);
	}
}