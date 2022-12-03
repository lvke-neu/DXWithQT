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
#include "ConstantBuffer.h"
#include "SamplerStateDesc.h"

namespace Twinkle
{
	class VertexShader;
	class InputLayout;
	class PixelShader;
	class Texture;

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

		IBindable* CreateVertexShader(const std::string& relativeFilePath);

		IBindable* CreateInputLayout(const std::string& relativeFilePath, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ied);

		IBindable* CreatePixelShader(const std::string& relativeFilePath);

		template <class T>
		IBindable* CreateConstantBuffer(UINT startSlot)
		{
			return new ConstantBuffer<T>(m_pDevice, m_pDeviceContent, startSlot);
		}

		IBindable* CreateTexture(UINT startSlot, const std::string& relativeFilePath);

		IBindable* CreateSamplerState(UINT startSlot, SamplerStateType samplerStateType);

		template <class IndexBufferType>
		void DrawCall(IBindable* vertexBuffer, IBindable* indexbuffer,
			IBindable* vertexShader, IBindable* inputLayout, IBindable* pixelShader, D3D11_PRIMITIVE_TOPOLOGY drawType, 
			IBindable* texture = nullptr, IBindable* samplerState = nullptr, const std::vector<IBindable*>& constantBuffers = defaultConstantBuffers)
		{
			if (vertexBuffer)
				vertexBuffer->bind();
			if (indexbuffer)
				indexbuffer->bind();
			if (vertexShader)
				vertexShader->bind();
			if (inputLayout)
				inputLayout->bind();
			if (pixelShader)
				pixelShader->bind();
			if (texture)
				texture->bind();
			if (samplerState)
				samplerState->bind();

			for (auto& constantBuffer : constantBuffers)
			{
				if (constantBuffer)
					constantBuffer->bind();
			}
		
			m_pDeviceContent->IASetPrimitiveTopology(drawType);
			m_pDeviceContent->DrawIndexed(dynamic_cast<IndexBuffer<IndexBufferType>*>(indexbuffer)->getIndexCount(), 0, 0);
		}

		void Release(IBindable*& bindable);
		void Release(std::vector<IBindable*>& constantBuffers);
	private:
		BindableManager();
		virtual ~BindableManager() =default;
		BindableManager(const BindableManager&) = delete;
		BindableManager& operator=(const BindableManager&) = delete;
	private:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };

		static std::vector<IBindable*> defaultConstantBuffers;
	};

	
}
