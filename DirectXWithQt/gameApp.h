#pragma once

#include "d3dApp.h"
#include "SceneInterface.h"
#include "SceneFactory.h"
#include "KeyBoard.h"
#include "Mouse.h"



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

public:
	void onKeyPress(int key);
	void onKeyRelease(int key);

	void onLeftButtonPress(float x, float y);
	void onRightButtonMove(float deltaX, float deltaY);
	void onButtonRelease() { Mouse::m_whichButton = NoButton; }
	void onMouseMove(float x, float y);

public:
	void setScene(std::string type);
	IScene* getScene() { return m_scene; }
	void setRenderTargetViewColor(float x, float y, float z, float w)
	{ 
		m_renderTargetViewColor[0] = x;
		m_renderTargetViewColor[1] = y;
		m_renderTargetViewColor[2] = z;
		m_renderTargetViewColor[3] = w;
	};

private:
	IScene* m_scene{ nullptr };

private:
	float m_renderTargetViewColor[4]{0.0f, 0.0f, 0.0f, 1.0f};



};