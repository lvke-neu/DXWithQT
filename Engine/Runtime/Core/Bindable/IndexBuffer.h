/***************************************************************************************
Author: lvke
Date:2022/12/02 9:46
Description:
Encapsulate indexbuffer
****************************************************************************************/
#pragma once

#include "BindableInterface.h"
#include <vector>

namespace Twinkle
{
	template<class T>
	class IndexBuffer : public IBindable
	{
		friend class BindableManager;
	public:
		virtual UINT getIndexCount() override;
	private:
		IndexBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::vector<T>& indices, DXGI_FORMAT dxgiFormat);
		virtual ~IndexBuffer();
		virtual void bind() override;
	private:
		UINT m_indexCount{ 0 };
		DXGI_FORMAT m_dxgiFormat{ (DXGI_FORMAT)0 };
		ID3D11Buffer* m_pIndexBuffer{ nullptr };
	};

	template<class T>
	IndexBuffer<T>::IndexBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::vector<T>& indices, DXGI_FORMAT dxgiFormat)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		m_indexCount = (UINT)indices.size();
		m_dxgiFormat = dxgiFormat;

		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&ibd, sizeof(ibd));
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = (UINT)(sizeof(T) * indices.size());
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.StructureByteStride = sizeof(T);
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indices.data();
		if (m_pDevice)
			m_pDevice->CreateBuffer(&ibd, &InitData, &m_pIndexBuffer);
	}

	template<class T>
	IndexBuffer<T>::~IndexBuffer()
	{
		SAFE_RELEASE(m_pIndexBuffer);
	}

	template<class T>
	void IndexBuffer<T>::bind()
	{
		if (m_pDeviceContent)
			m_pDeviceContent->IASetIndexBuffer(m_pIndexBuffer, m_dxgiFormat, 0);
	}

	template<class T>
	UINT IndexBuffer<T>::getIndexCount()
	{
		return m_indexCount;
	}
}