/***************************************************************************************
Author: lvke
Date:2022/11/30 19:41
Description:
Twinkle Engine
****************************************************************************************/
#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include "../Interface/SingletonInterface.h"
#include "../Timer/GameTimer.h"

namespace Twinkle
{
	class Engine
	{
		FRIEND_SINGLETON(Engine);
	public:
		void Initialize(HWND hwndWindow, UINT width, UINT height);
		void OnResize(UINT width, UINT height);
		void Update();
		float GetFps();
		void Pause();
		void Start();
	public:
		ID3DBlob* ReadFileToBlob(const std::string& relativeFilePath);
		ID3D11ShaderResourceView* LoadTexture(const std::string& relativeFilePath);
	public:
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContent();
		IDXGISwapChain* GetSwapChain();
		ID3D11RenderTargetView* GetRenderTargetView();
		ID3D11Texture2D* GetDepthStencilBuffer();
		ID3D11DepthStencilView* GetDepthStencilView();
	private:
		Engine() = default;
		virtual ~Engine();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;

	private:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };
		IDXGISwapChain* m_pSwapChain{ nullptr };
		ID3D11RenderTargetView* m_pRenderTargetView{ nullptr };
		ID3D11Texture2D* m_pDepthStencilBuffer{ nullptr };
		ID3D11DepthStencilView* m_pDepthStencilView{ nullptr };
	private:
		GameTimer m_timer;
		bool m_bPause = false;
	};
}