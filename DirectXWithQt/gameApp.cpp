#include "gameApp.h"
#include "RenderStates.h"



GameApp::GameApp(HWND hInstance, UINT windowWidth, UINT windowHeight)
	:D3DApp(hInstance, windowWidth, windowHeight)
{
	InitD3D();

	RenderStates::Init(m_pd3dDevice);
}

GameApp::~GameApp()
{
	if (m_scene)
	{
		delete m_scene;
		m_scene = nullptr;
	}
}

void GameApp::InitD3D()
{
	D3DApp::InitD3D();

}

void GameApp::OnResize(UINT windowWidth, UINT windowHeight)
{
	D3DApp::OnResize(windowWidth, windowHeight);
	if(m_scene)
		m_scene->onResize(windowWidth, windowHeight);
}

void GameApp::UpdateScene(float deltaTime)
{
	if (m_scene)
	{
		m_scene->updateScene(deltaTime);
	}

	
}

void GameApp::DrawScene()
{
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), m_renderTargetViewColor);
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	if (m_scene)
	{
		m_scene->drawScene();
	}
	m_pSwapChain->Present(0, 0);

	//float static aa = 0.0f;
	//aa += 0.001;
	//Connector::notify(aa);

}




void GameApp::setScene(std::string type)
{
	if (m_scene)
	{
		delete m_scene;
		m_scene = nullptr;
	}
	m_scene = SceneFactory::createChpaterScene(type, m_pd3dDevice, m_pd3dImmediateContext);
	if (m_scene)
	{
		m_scene->onResize(m_windowWidth, m_windowHeight);
		m_scene->initScene();
	}
		
}

void GameApp::onKeyPress(int key)
{
	KeyBoard::getInstance().pressKey(key);
}

void GameApp::onKeyRelease(int key)
{
	KeyBoard::getInstance().releaseKey(key);
}

void GameApp::onRightButtonMove(float deltaX, float deltaY)
{
	Mouse::m_whichButton = RightButton;
	Mouse::m_delta.m_x = deltaX;
	Mouse::m_delta.m_y = deltaY;
}
