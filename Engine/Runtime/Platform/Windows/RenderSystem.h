/***************************************************************************************
Author: lvke
Date:2022/12/04 10:45
Description:
DirextX11 Manager
****************************************************************************************/
#pragma once

#include <d3d11.h>
#include "Runtime/Interface/SingletonInterface.h"
#include "Bindable/VertexBuffer.h"
#include "Bindable/IndexBuffer.h"
#include "Bindable/ConstantBuffer.h"
#include "Bindable/StateDesc.h"

namespace Twinkle
{
	class VertexShader;
	class InputLayout;
	class PixelShader;
	class Texture;
	class RenderSystem
	{
		FRIEND_SINGLETON(RenderSystem);
	public:
		void Initialize(HWND hwndWindow, UINT width, UINT height);
		void OnResize(UINT width, UINT height);

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContent();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetRenderTargetView();
		ID3D11Texture2D* GetDepthStencilBuffer();
		ID3D11DepthStencilView* GetDepthStencilView();
	private:
		RenderSystem() = default;
		virtual ~RenderSystem();
		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;
	private:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
		IDXGISwapChain* m_pSwapChain{ nullptr };
		ID3D11RenderTargetView* m_pRenderTargetView{ nullptr };
		ID3D11Texture2D* m_pDepthStencilBuffer{ nullptr };
		ID3D11DepthStencilView* m_pDepthStencilView{ nullptr };
		

		/*******************************************Bindabel Manager*********************************************************/
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

		IBindable* CreateRasterizerState(RasterizerStateType rasterizerStateType);
		void SetRasterizerState(IBindable* rasterizerState);

		IBindable* CreateBlendState(BlendStateType blendStateType);
		void SetBlendState(IBindable* blendState);

		IBindable* CreateDepthStencilState(DepthStencilStateType depthStencilStateType, UINT StencilRef);
		void SetDepthStencilState(IBindable* depthStencilState);

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
		static std::vector<IBindable*> defaultConstantBuffers;
	};
}