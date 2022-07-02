#pragma once

#include "d3dApp.h"
#include "SceneInterface.h"
#include "SceneFactory.h"

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
	void setScene(std::string type);
	IScene* getScene() { return m_scene; }
private:
	IScene* m_scene{ nullptr };

private:
	float m_renderTargetViewColor[4]{0.0f, 0.0f, 0.0f, 1.0f};



};