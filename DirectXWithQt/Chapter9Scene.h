#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "ListeningEvent.h"

class Chapter9Scene : public IScene, public ListeningEvent
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
	Chapter9Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter9Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:
	void notifyAll();

private:
	GameObject m_box1;

};

