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

	void set_light_material();
public:
	void changeBoxTexture();
	void changeFloorTexture();


private:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };

	ComPtr<ID3D11Buffer> m_plightAndMaterialCB{ nullptr };
private:
	GameObject m_box;
	GameObject m_plane;



//****************Test*****************
private:
	XMFLOAT4 m_ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	XMFLOAT4 m_diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMFLOAT4 m_specula = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
	float m_lightDir_y = -0.5f;
public:
	void setAmbient(XMFLOAT4 ambient) { m_ambient = ambient; set_light_material(); }
	void setDiffuse(XMFLOAT4 diffuse) { m_diffuse = diffuse; set_light_material(); }
	void setSpecula(XMFLOAT4 specula) { m_specula = specula; set_light_material(); }
	void setLightY(float y) { m_lightDir_y = y;  set_light_material();};

};

