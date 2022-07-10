#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter2Scene:public IScene
{
public:
	Chapter2Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;

	void set_light_material();
public:
	void changeBoxTexture();
	void changeFloorTexture();
	void changeLight();
private:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
private:
	GameObject m_box;
	GameObject m_plane;





};

