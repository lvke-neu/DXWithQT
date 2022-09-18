/***************************************************************************************
Author: lvke
Date:2022/9/18 11:00
Description:
The Engine is responsible for initializing D3D and building the process of TICK
****************************************************************************************/

#pragma once


#include "../base/SingletonInterface.h"

#include <d3d11_1.h>
#include <wrl/client.h>

namespace LkEngine
{
	class Engine : public ISingleton<Engine>
	{
	public:
		Engine();
		~Engine();
	public:
		void initialize(HWND hInstance, UINT windowWidth, UINT windowHeight);
		void updateScene(float deltaTime);
		void drawScene();
		void onResize(UINT windowWidth, UINT windowHeight);
	private:
		HWND m_hInstance;
		UINT m_windowWidth;
		UINT m_windowHeight;

		UINT      m_4xMsaaQuality;

		Microsoft::WRL::ComPtr<ID3D11Device> m_pd3dDevice { nullptr };
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext { nullptr };
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain { nullptr };

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer { nullptr };
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView { nullptr };
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView { nullptr };

		D3D11_VIEWPORT m_ScreenViewport;
	};
}