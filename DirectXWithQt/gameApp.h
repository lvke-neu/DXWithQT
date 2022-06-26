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
};