/************************************************************************
Author: lvke
Date:2022/6/26 14:15
Description:
 DirectX框架，包含初始化DX、更新场景、绘制场景
************************************************************************/
#pragma once

#include <wrl/client.h>
#include <d3d11_1.h>


template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class D3DApp
{
public:
	D3DApp(HWND hInstance, UINT windowWidth, UINT windowHeight);
	virtual ~D3DApp();
	
public:
	void InitD3D();
	void OnResize(UINT windowWidth, UINT windowHeight);
	virtual void UpdateScene(float deltaTime) = 0;
	virtual void DrawScene() = 0;
	
protected:
	HWND m_hInstance;
	UINT m_windowWidth;
	UINT m_windowHeight;

	UINT      m_4xMsaaQuality;

	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;
	ComPtr<IDXGISwapChain> m_pSwapChain;

	ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	D3D11_VIEWPORT m_ScreenViewport;
};