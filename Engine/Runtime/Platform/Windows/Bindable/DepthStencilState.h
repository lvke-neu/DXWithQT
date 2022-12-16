/***************************************************************************************
Author: lvke
Date:2022/12/16 14:10
Description:
Encapsulate DepthStencilState
****************************************************************************************/
#pragma once
#include "StateDesc.h"

namespace Twinkle
{
	class DepthStencilState : public IBindable
	{
		friend class RenderSystem;
	private:
		DepthStencilState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, DepthStencilStateType depthStencilStateType, UINT StencilRef);
		virtual ~DepthStencilState();
		virtual void bind() override;
	private:
		ID3D11DepthStencilState* m_pDepthStencilState{ nullptr };
		UINT m_StencilRef = 0;
	};

	DepthStencilState::DepthStencilState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, DepthStencilStateType depthStencilStateType, UINT StencilRef)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		m_StencilRef = StencilRef;

		if (depthStencilStateType == DSSDefault)
			m_pDepthStencilState = nullptr;
		else
			m_pDevice->CreateDepthStencilState(&StateDesc::depthStencilStateTypeDesc[depthStencilStateType], &m_pDepthStencilState);
	}

	DepthStencilState::~DepthStencilState()
	{
		SAFE_RELEASE(m_pDepthStencilState);
	}

	void DepthStencilState::bind()
	{
		m_pDeviceContent->OMSetDepthStencilState(m_pDepthStencilState, m_pDepthStencilState == nullptr ? 0 : m_StencilRef);
	}
}