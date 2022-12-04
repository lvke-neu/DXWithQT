/***************************************************************************************
Author: lvke
Date:2022/12/04 10:45
Description:
DirextX11 Manager
****************************************************************************************/
#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include "Runtime/Utility/Utility.h"
#include "Runtime/Interface/SingletonInterface.h"

namespace Twinkle
{
	class DirectX11Manager
	{
		FRIEND_SINGLETON(DirectX11Manager);
	public:
		void Initialize(HWND hwndWindow, UINT width, UINT height);
		void OnResize(UINT width, UINT height);

		float GetAspectRatio();

		ID3DBlob* ReadFileToBlob(const std::string& relativeFilePath);
		ID3D11ShaderResourceView* LoadTexture(const std::string& relativeFilePath);

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContent();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetRenderTargetView();
		ID3D11Texture2D* GetDepthStencilBuffer();
		ID3D11DepthStencilView* GetDepthStencilView();
	private:
		DirectX11Manager() = default;
		virtual ~DirectX11Manager();
		DirectX11Manager(const DirectX11Manager&) = delete;
		DirectX11Manager& operator=(const DirectX11Manager&) = delete;
	private:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
		IDXGISwapChain* m_pSwapChain{ nullptr };
		ID3D11RenderTargetView* m_pRenderTargetView{ nullptr };
		ID3D11Texture2D* m_pDepthStencilBuffer{ nullptr };
		ID3D11DepthStencilView* m_pDepthStencilView{ nullptr };

		float m_AspectRatio = 1.0f;
	};
}