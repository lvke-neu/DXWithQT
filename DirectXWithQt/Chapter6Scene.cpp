#include "Chapter6Scene.h"
#include "RenderStates.h"
#include "WICTextureLoader.h"


Chapter6Scene::Chapter6Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
{
	
	initCameraAndLight(pd3dDevice, pd3dImmediateContext);
	
}


void Chapter6Scene::initScene()
{
	m_pFireAnims.resize(120);
	char strFile[40];
	wchar_t tmpStrFile[40];
	for (int i = 1; i <= 120; ++i)
	{
		wsprintf(strFile, "Texture\\FireAnim\\Fire%03d.bmp", i);
		for (int j = 0; j < 40; j++)
		{
			tmpStrFile[j] = strFile[j];
		}
		CreateWICTextureFromFile(m_pd3dDevice.Get(), tmpStrFile, nullptr, m_pFireAnims[static_cast<size_t>(i) - 1].GetAddressOf());
	}

	m_pLightingAnims.resize(60);
	for (int i = 1; i <= 60; ++i)
	{
		wsprintf(strFile, "Texture\\BoltAnim\\Bolt%03d.bmp", i);
		for (int j = 0; j < 40; j++)
		{
			tmpStrFile[j] = strFile[j];
		}
		CreateWICTextureFromFile(m_pd3dDevice.Get(), tmpStrFile, nullptr, m_pLightingAnims[static_cast<size_t>(i) - 1].GetAddressOf());
	}

	m_2dPlane = GameObject(m_pd3dDevice, m_pd3dImmediateContext);
	m_2dPlane.setMesh(Geometry::buildPlaneMesh(1.0f, 1.0f));
	m_2dPlane.setShader(SceneShader::shaderPath[5]);

}


void Chapter6Scene::updateScene(float deltaTime)
{
	static float totDeltaTime = 0;
	static int CurrFrame = 0;

	if (KeyBoard::getInstance().isKeyPress('1'))
	{
		m_state = Fire;
	}
	else if (KeyBoard::getInstance().isKeyPress('2'))
	{
		m_state = Lighting;
	}

	if (m_state == Fire)
	{
		totDeltaTime += deltaTime;
		if (totDeltaTime > 1.0f / 60)
		{
			totDeltaTime -= 1.0f / 60;
			CurrFrame = (CurrFrame + 1) % 120;
			m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pFireAnims[CurrFrame].GetAddressOf());
		}
	}
	else if (m_state == Lighting)
	{
		totDeltaTime += deltaTime;
		if (totDeltaTime > 1.0f / 60)
		{
			totDeltaTime -= 1.0f / 60;
			CurrFrame = (CurrFrame + 1) % 60;
			m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pLightingAnims[CurrFrame].GetAddressOf());
		}
	}
	
}

void Chapter6Scene::drawScene()
{
	m_2dPlane.draw2d();
}




void Chapter6Scene::setDirLight(XMFLOAT3 dir)
{

}


