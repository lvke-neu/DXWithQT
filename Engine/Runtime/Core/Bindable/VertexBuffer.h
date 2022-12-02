/***************************************************************************************
Author: lvke
Date:2022/12/02 10:39
Description:
Encapsulate vertexbuffer
****************************************************************************************/
#pragma once

#include "BindableInterface.h"
#include <vector>

namespace Twinkle
{
	template<class T>
	class VertexBuffer : public IBindable
	{
		friend class BindableManager;
	private:
		VertexBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::vector<T>& vertices);
		virtual ~VertexBuffer();
		virtual void bind() override;
	private:
		ID3D11Buffer* m_pVertexBuffer{ nullptr };
	};

	template<class T>
	VertexBuffer<T>::VertexBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContent, const std::vector<T>& vertices)
	{
		m_pDevice = pDevice;
		m_pDeviceContent = pDeviceContent;
		
		D3D11_BUFFER_DESC vbd;
		ZeroMemory(&vbd, sizeof(vbd));
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = (UINT)(sizeof(T) * vertices.size());
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.StructureByteStride = sizeof(T);
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices.data();
		if(m_pDevice)
			m_pDevice->CreateBuffer(&vbd, &InitData, &m_pVertexBuffer);
	}

	template<class T>
	VertexBuffer<T>::~VertexBuffer()
	{
		SAFE_RELEASE(m_pVertexBuffer);
	}

	template<class T>
	void VertexBuffer<T>::bind()
	{
		UINT stride = sizeof(T);
		UINT offset = 0;
		m_pDeviceContent->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	}
}