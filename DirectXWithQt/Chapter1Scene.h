#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter1Scene : public IScene
{
public:
	Chapter1Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
public:
	//override IScene
	virtual void initScene() override;
	virtual void updateScene(float deltaTime) override;
	virtual void drawScene() override;
	void setDirLight(XMFLOAT3 dir) {};

public:
	void setColor(float r, float g, float b, float a);



	XMFLOAT4 m_color{ 0.0f, 1.0f, 0.0f, 1.0f };
	
private:
	GameObject m_triangle;
	ComPtr<ID3D11Buffer> m_psConstantBuffer;
};

