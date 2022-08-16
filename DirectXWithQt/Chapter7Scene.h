#pragma once 

#include "SceneInterface.h"
#include "ModelObject.h"
#include "ListeningEvent.h"
#include "SkyBox.h"

#define RAND_TREE_NUM 50
class Chapter7Scene : public IScene, public ListeningEvent
{
	struct Fog
	{
		XMFLOAT4 fogColor;
		int fogEnabled;
		float fogStart;
		float fogRange;
		float pad;
	};

public:
	Chapter7Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter7Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:
	void set_enableFrustumCulling(bool b) { m_enableFrustumCulling = b; }
	void setFogEnabled(bool b);
	void setFogRange(float range);
	void setWireframe(bool b);
	void notifyAll();
private:
	ModelObject m_house;
	std::vector<ModelObject> m_trees;
	GameObject m_plane;
	GameObject m_box1;
	bool m_enableFrustumCulling = false;
private:
	int m_randX[RAND_TREE_NUM];
	int m_randZ[RAND_TREE_NUM];
private:
	ComPtr<ID3D11Buffer> m_pFogCB;

};

