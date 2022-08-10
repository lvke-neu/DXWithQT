#pragma once 

#include "SceneInterface.h"
#include "ModelObject.h"
#include "ListeningEvent.h"

#define RAND_TREE_NUM 256
class Chapter7Scene : public IScene, public ListeningEvent
{
public:
	Chapter7Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter7Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:

	void notifyAll();

private:
	ModelObject m_house;
	ModelObject m_tree;
	GameObject m_plane;
private:
	int m_randX[RAND_TREE_NUM];
	int m_randZ[RAND_TREE_NUM];

};

