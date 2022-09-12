#pragma once 

#include "SceneInterface.h"
#include "AssimpModelObject.h"


class Chapter10Scene : public IScene
{

public:
	Chapter10Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter10Scene() 
	{ 

	}
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
private:
	GameObject m_box1;
	GameObject m_plane;

	AssimpModelObject m_house;

	bool m_enableNormalMap = true;
};

