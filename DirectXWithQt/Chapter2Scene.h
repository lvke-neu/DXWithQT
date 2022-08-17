#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter2Scene : public IScene
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
	Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter2Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
public:
	void changeBox1Texture();
	void changeBox2Texture();
	void changeFloorTexture();
	void setWireframe(bool b);
	void setNoCull(bool b);
	void setFogEnabled(bool b);
	void setFogRange(float range);

	void notifyAll();

private:
	GameObject m_box1;
	GameObject m_box2;
	GameObject m_box3;
	GameObject m_plane;
private:
	ComPtr<ID3D11Buffer> m_pFogCB;


};

