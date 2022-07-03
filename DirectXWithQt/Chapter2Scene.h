#pragma once 

#include "SceneInterface.h"
#include "PipeLine.h"


class Chapter2Scene:public IScene, PipeLine
{
	struct WVPMatrixCB
	{
		XMMATRIX g_world;
		XMMATRIX g_view;
		XMMATRIX g_proj;
	};

public:
	Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;

public:
	void bindCB2PipeLine();

public:
	void changeTexture();
private:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
private:
	GameObject m_box;



};

