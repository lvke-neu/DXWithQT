#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter2Scene:public IScene
{
public:
	Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter2Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;

	void setLight();
public:
	void changeBox1Texture();
	void changeBox2Texture();
	void changeFloorTexture();


private:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

	ComPtr<ID3D11Buffer> m_pLightCB{ nullptr };
private:
	GameObject m_box1;
	GameObject m_box2;
	GameObject m_plane;



//****************Test*****************
private:

	float m_lightDir_y = -0.5f;
public:
	void setLightY(float y) { m_lightDir_y = y;  setLight();};

};

