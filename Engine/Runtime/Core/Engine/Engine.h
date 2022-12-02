/***************************************************************************************
Author: lvke
Date:2022/11/30 19:41
Description:
Twinkle Engine
****************************************************************************************/
#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include "../Interface/SingletonInterface.h"
#include "../Timer/GameTimer.h"

namespace Twinkle
{
	class Engine
	{
		FRIEND_SINGLETON(Engine);
	public:
		void initialize(HWND hwndWindow, UINT width, UINT height);
		void onResize(UINT width, UINT height);
		void update();
		float getFps();
	public:
		ID3D11Device* getDevice();
		ID3D11DeviceContext* getDeviceContent();
		IDXGISwapChain* getSwapChain();
	private:
		void draw();
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
	};
}