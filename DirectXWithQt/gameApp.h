#pragma once

#include "d3dApp.h"

class GameApp : public D3DApp
{
public:
	GameApp(HWND hInstance, UINT windowWidth, UINT windowHeight);
	~GameApp();
public:
	void InitD3D();
	void OnResize(UINT windowWidth, UINT windowHeight);
	virtual void UpdateScene(float deltaTime) override;
	virtual void DrawScene() override;

private:
	float m_renderTargetViewColor[4]{0.0f, 0.0f, 0.0f, 1.0f};

public:
	void setRenderTargetViewColor(float r, float g, float b, float a)
	{
		m_renderTargetViewColor[0] = r;
		m_renderTargetViewColor[1] = g;
		m_renderTargetViewColor[2] = b;
		m_renderTargetViewColor[3] = a;
	}
};