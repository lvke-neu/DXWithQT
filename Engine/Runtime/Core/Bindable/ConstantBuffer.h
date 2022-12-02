/***************************************************************************************
Author: lvke
Date:2022/12/02 15:16
Description:
Encapsulate constantbuffer
****************************************************************************************/
#pragma once

#include "BindableInterface.h"
#include <vector>

namespace Twinkle
{
	template<class T>
	class ConstantBuffer : public IBindable
	{
		friend class BindableManager;
	public:
		void update(const T& t);
	private:
		ConstantBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, UINT startSlot);
		virtual ~ConstantBuffer();
		virtual void bind() override;
	private:
		ID3D11Buffer* m_pConstantBuffer{ nullptr };
		UINT m_startSlot = 10;
	};

	template<class T>
	ConstantBuffer<T>::ConstantBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, UINT startSlot)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		m_startSlot = startSlot;

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(T);
		if (m_pDevice)
			m_pDevice->CreateBuffer(&cbd, nullptr, &m_pConstantBuffer);
	}

	template<class T>
	ConstantBuffer<T>::~ConstantBuffer()
	{
		SAFE_RELEASE(m_pConstantBuffer);
	}

	template<class T>
	void ConstantBuffer<T>::update(const T& t)
	{
		if (m_pConstantBuffer)
		{
			D3D11_MAPPED_SUBRESOURCE mappedData;
			m_pDeviceContent->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
			memcpy_s(mappedData.pData, sizeof(T), &t, sizeof(T));
			m_pDeviceContent->Unmap(m_pConstantBuffer, 0);
		}
	}

	template<class T>
	void ConstantBuffer<T>::bind()
	{
		m_pDeviceContent->VSSetConstantBuffers(m_startSlot, 1, &m_pConstantBuffer);
		m_pDeviceContent->PSSetConstantBuffers(m_startSlot, 1, &m_pConstantBuffer);
	}
}