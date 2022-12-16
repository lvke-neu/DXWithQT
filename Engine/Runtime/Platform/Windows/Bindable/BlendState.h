/***************************************************************************************
Author: lvke
Date:2022/12/15 14:55
Description:
Encapsulate BlendState
****************************************************************************************/
#pragma once
#include "StateDesc.h"

namespace Twinkle
{
	class BlendState : public IBindable
	{
		friend class RenderSystem;
	private:
		BlendState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, BlendStateType blendStateType);
		virtual ~BlendState();
		virtual void bind() override;
	private:
		ID3D11BlendState* m_pBlendState{ nullptr };
	};

	BlendState::BlendState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, BlendStateType blendStateType)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;

		m_pDevice->CreateBlendState(&StateDesc::blendStateTypeDesc[blendStateType], &m_pBlendState);
	}

	BlendState::~BlendState()
	{
		SAFE_RELEASE(m_pBlendState);
	}

	void BlendState::bind()
	{
		m_pDeviceContent->OMSetBlendState(m_pBlendState, nullptr, 0xFFFFFFFF);
	}
}