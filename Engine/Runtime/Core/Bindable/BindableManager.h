/***************************************************************************************
Author: lvke
Date:2022/12/02 11:31
Description:
Bindable Manager : create and drawcall
****************************************************************************************/
#pragma once

#include "../Interface/SingletonInterface.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


namespace Twinkle
{
	class VertexShader;
	class InputLayout;
	class PixelShader;

	class BindableManager
	{
		FRIEND_SINGLETON(BindableManager);
	public:
		template <class T>
		IBindable* CreateVertexBuffer(const std::vector<T>& vertices)
		{
			return new VertexBuffer<T>(m_pDevice, m_pDeviceContent, vertices);
		}

		template <class T>
		IBindable* CreateIndexBuffer(const std::vector<T>& indices, DXGI_FORMAT dxgiFormat)
		{
			return new IndexBuffer<T>(m_pDevice, m_pDeviceContent, indices, dxgiFormat);
		}

		IBindable* CreateVertexShader(ID3DBlob* pBlob);

		IBindable* CreateInputLayout(ID3DBlob* pBlob, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied);

		IBindable* CreatePixelShader(ID3DBlob* pBlob);

		void DrawCall(IBindable* vertexBuffer, IBindable* indexbuffer,
			IBindable* vertexShader, IBindable* inputLayout, IBindable* pixelShader, D3D11_PRIMITIVE_TOPOLOGY drawType);

		void Release(IBindable*& bindable);
	private:
		BindableManager();
		virtual ~BindableManager() =default;
		BindableManager(const BindableManager&) = delete;
		BindableManager& operator=(const BindableManager&) = delete;
	private:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
	};
}
