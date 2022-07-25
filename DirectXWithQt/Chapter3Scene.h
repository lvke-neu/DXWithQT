#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "ListeningEvent.h"

class Chapter3Scene : public IScene, public ListeningEvent
{
	struct DynamicMap
	{
		float enableDM;
		XMMATRIX rotMatrix;
		XMFLOAT3 pad;
	};

public:
	Chapter3Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter3Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;

public:
	void setWaterTransparency(float transparency);


	void notifyAll();
private:
	ComPtr<ID3D11Buffer> m_pDmCB;
private:
	//四面墙
	GameObject m_wall;
	//底
	GameObject m_floor;
	//水面
	GameObject m_water;

	GameObject m_staticBox;
	GameObject m_dynamicBox;
};

