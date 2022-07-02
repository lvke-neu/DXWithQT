#pragma once 

#include "SceneInterface.h"
#include "PipeLine.h"


class Chapter2Scene:public IScene, PipeLine
{
public:
	Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
public:
	void initScene() override;
	void updateScene() override;
	void drawScene() override;

	void bindCB2PipeLine() {};
private:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
private:
	GameObject m_triangle;
};

