#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter3Scene : public IScene
{
	struct DynamicMap
	{
		float enableDM;
		float enableMultiMap;
		XMMATRIX rotMatrix;
		XMFLOAT2 pad;
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

private:
	ComPtr<ID3D11Buffer> m_pDmCB;
	ComPtr<ID3D11ShaderResourceView> m_pTextureArr[6];
private:
	//四面墙
	GameObject m_wall;
	//底
	GameObject m_floor;
	//水面
	GameObject m_water;

	GameObject m_staticBox;
	GameObject m_dynamicBox;

	//六面贴不同图的盒子
	GameObject m_differetMapBox;
};

