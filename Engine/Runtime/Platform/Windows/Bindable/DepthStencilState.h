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
		DepthStencilState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, DepthStencilStateType depthStencilStateType);
		virtual ~DepthStencilState();
		virtual void bind() override;
	private:
		ID3D11DepthStencilState* m_pDepthStencilState{ nullptr };
	};

	DepthStencilState::DepthStencilState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, DepthStencilStateType depthStencilStateType)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;

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
		m_pDeviceContent->OMSetDepthStencilState(m_pDepthStencilState, 0);
	}
}