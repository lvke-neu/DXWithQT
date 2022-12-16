/***************************************************************************************
Author: lvke
Date:2022/12/15 11:34
Description:
Encapsulate RasterizerState
****************************************************************************************/
#pragma once
#include "StateDesc.h"

namespace Twinkle
{
	class RasterizerState : public IBindable
	{
		friend class RenderSystem;
	private:
		RasterizerState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, RasterizerStateType rasterizerStateType);
		virtual ~RasterizerState();
		virtual void bind() override;
	private:
		ID3D11RasterizerState* m_pRasterizerState{ nullptr };
	};

	RasterizerState::RasterizerState(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, RasterizerStateType rasterizerStateType)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;

		m_pDevice->CreateRasterizerState(&StateDesc::rasterizerStateTypeDesc[rasterizerStateType], &m_pRasterizerState);
	}

	RasterizerState::~RasterizerState()
	{
		SAFE_RELEASE(m_pRasterizerState);
	}

	void RasterizerState::bind()
	{
		m_pDeviceContent->RSSetState(m_pRasterizerState);
	}
}