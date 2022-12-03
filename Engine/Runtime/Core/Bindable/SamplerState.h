/***************************************************************************************
Author: lvke
Date:2022/12/03 20:56
Description:
Encapsulate SamplerState
****************************************************************************************/
#pragma once

#include "SamplerStateDesc.h"

namespace Twinkle
{
	class SamplerState : public IBindable
	{

		friend class BindableManager;
	private:
		SamplerState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, UINT startSlot, SamplerStateType samplerStateType);
		virtual ~SamplerState();
		virtual void bind() override;
	private:
		UINT m_startSlot = 0;
		ID3D11SamplerState* m_pSamplerState{ nullptr };
	};

	SamplerState::SamplerState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, UINT startSlot, SamplerStateType samplerStateType)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		m_startSlot = startSlot;

		SamplerStateDesc::init();
		
		m_pDevice->CreateSamplerState(&SamplerStateDesc::samplerStateTyPeDesc[samplerStateType], &m_pSamplerState);
	}

	SamplerState::~SamplerState()
	{
		SAFE_RELEASE(m_pSamplerState);
	}

	void SamplerState::bind()
	{
		m_pDeviceContent->PSSetSamplers(m_startSlot, 1, &m_pSamplerState);
	}
}