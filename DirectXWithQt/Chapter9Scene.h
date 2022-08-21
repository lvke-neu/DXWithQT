#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "SkyBox.h"


class Chapter9Scene : public IScene
{

	struct EnableReflect
	{
		float g_ReflectionEnabled;
		XMFLOAT3 pad;
	};
public:
	Chapter9Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter9Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:
	void setReflect(bool b);
	void notifyAll();

private:
	GameObject m_box1;
	GameObject m_sphere;
	GameObject m_terrain;
	SkyBox m_skyBox;
private:
	ComPtr<ID3D11Buffer> m_pEnableReflect;
};

