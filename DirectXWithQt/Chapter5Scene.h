#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"


class Chapter5Scene : public IScene
{
	//是否开启阴影
	struct EnableShadow
	{
		float isShadow;
		XMFLOAT3 pad;
	};
	
	//阴影矩阵
	struct ShadowMatrix
	{
		XMMATRIX shadowMatrix;
	};
public:
	Chapter5Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter5Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;
	void setDirLight(float x, float y, float z) { setDirLight(XMFLOAT3(x, y, z)); }
public:

	void set_EnableShadow(bool b);
	void set_ShadowMatrix();

	void notifyAll();

private:
	//四面墙
	GameObject m_wall;
	//底
	GameObject m_floor;

	GameObject m_box;
	GameObject m_box2;
private:
	Material m_generalMaterial; 
	Material m_shadowMaterial;
private:
	ComPtr<ID3D11Buffer> m_pEnableShadowCB;
	ComPtr<ID3D11Buffer> m_pShadowMatrixCB;

};

