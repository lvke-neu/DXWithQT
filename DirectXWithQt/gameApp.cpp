#include "gameApp.h"


GameApp::GameApp(HWND hInstance, UINT windowWidth, UINT windowHeight)
	:D3DApp(hInstance, windowWidth, windowHeight)
{
	InitD3D();
}

GameApp::~GameApp()
{

}

void GameApp::InitD3D()
{
	D3DApp::InitD3D();
}

void GameApp::OnResize(UINT windowWidth, UINT windowHeight)
{
	D3DApp::OnResize(windowWidth, windowHeight);
}

void GameApp::UpdateScene(float deltaTime)
{

}

void GameApp::DrawScene()
{
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), m_renderTargetViewColor);
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pSwapChain->Present(0, 0);
}