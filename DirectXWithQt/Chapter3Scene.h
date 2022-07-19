#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "ListeningEvent.h"

class Chapter3Scene : public IScene, public ListeningEvent
{
public:
	Chapter3Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter3Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;

	void notifyAll();
private:
	//四面墙
	GameObject m_wall;
	//底
	GameObject m_floor;
	//水面
	GameObject m_water;

};

