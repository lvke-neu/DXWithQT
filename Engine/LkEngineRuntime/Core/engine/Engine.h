/***************************************************************************************
Author: lvke
Date:2022/9/18 11:00
Description:
The Engine is responsible for initializing D3D and building the process of TICK
****************************************************************************************/

#pragma once

#include <d3d11_1.h>
#include <wrl/client.h>
#include "../base/SingletonInterface.h"
#include "../Event/InputEventManager.h"
#include "../Event/FrameMoveEventManager.h"

namespace LkEngine
{
	using namespace Microsoft::WRL;
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
	public:
		void onKeyPress(const Keys& key) { InputEventManager::getInstance().onKeyPress(key); }
		void onKeyRelease(const Keys& key){ InputEventManager::getInstance().onKeyRelease(key); }
		void onMousePress(const MouseState& mouseState) { InputEventManager::getInstance().onMousePress(mouseState); }
		void onMouseRelease(const MouseState& mouseState) { InputEventManager::getInstance().onMouseRelease(mouseState); }
		void onMouseMove(const MouseState& mouseState) { InputEventManager::getInstance().onMouseMove(mouseState); }
		void onMouseWheelEvent(const MouseState& mouseState) { InputEventManager::getInstance().onMouseWheelEvent(mouseState); }
	private:
		HWND m_hInstance;
		UINT m_windowWidth;
		UINT m_windowHeight;

		UINT      m_4xMsaaQuality;

		ComPtr<ID3D11Device> m_pd3dDevice { nullptr };
		ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext { nullptr };
		ComPtr<IDXGISwapChain> m_pSwapChain { nullptr };

		ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer { nullptr };
		ComPtr<ID3D11RenderTargetView> m_pRenderTargetView { nullptr };
		ComPtr<ID3D11DepthStencilView> m_pDepthStencilView { nullptr };

		D3D11_VIEWPORT m_ScreenViewport;
	};
}