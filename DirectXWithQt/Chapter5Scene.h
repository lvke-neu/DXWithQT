#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "ListeningEvent.h"

class Chapter5Scene : public IScene, public ListeningEvent
{
public:
	Chapter5Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter5Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
	void setDirLight(float x, float y, float z) { setDirLight(XMFLOAT3(x, y, z)); }
public:


	void notifyAll();

private:
	//四面墙
	GameObject m_wall;
	//底
	GameObject m_floor;

	GameObject m_box;

};

