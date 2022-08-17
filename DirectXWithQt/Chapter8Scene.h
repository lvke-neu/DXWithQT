#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter8Scene : public IScene
{

public:
	Chapter8Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter8Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:

	void notifyAll();

private:
	GameObject m_box1;
	GameObject m_box2;
	GameObject m_rectangle;
};

