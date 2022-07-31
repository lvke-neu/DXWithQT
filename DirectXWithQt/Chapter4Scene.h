#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "ListeningEvent.h"

class Chapter4Scene : public IScene, public ListeningEvent
{
	struct Reflection
	{
		float isEnableReflec;
		XMMATRIX reflectionMatrix;
		XMFLOAT3 pad;
	};

public:
	Chapter4Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter4Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:
	void setIsReflection(bool b);
	void setMirrorTransparency(float transparency);
	void setFirstPerson(bool b) { m_isFirstPerson = b; if(m_isFirstPerson)m_perspectiveCamera.setRotation(0.0f, 1.5f, 0.0f); }

	void notifyAll();
private:
	ComPtr<ID3D11Buffer> m_pRelectionCB;
private:
	GameObject m_wall;
	GameObject m_mirrorWall;
	GameObject m_floor;
	GameObject m_mirror;
	GameObject m_box;

	GameObject m_firstPersonBox;
private:
	bool m_isFirstPerson = false;

};

