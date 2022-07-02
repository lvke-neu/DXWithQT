#pragma once 

#include "SceneInterface.h"
#include "PipeLine.h"


class Chapter1Scene : public IScene, PipeLine
{
public:
	Chapter1Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
public:
	//override IScene
	virtual void initScene() override;
	virtual void updateScene() override;
	virtual void drawScene() override;

	//override PipeLine
	virtual void bindCB2PipeLine() override;

public:
	void setColor(float r, float g, float b, float a);

private:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

	XMFLOAT4 m_color{ 0.0f, 1.0f, 0.0f, 1.0f };
	
private:
	GameObject m_triangle;
};

