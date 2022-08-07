#pragma once 

#include "SceneInterface.h"
#include "GameObject.h"
#include "ListeningEvent.h"

class Chapter6Scene : public IScene, public ListeningEvent
{
	enum Chpat6State
	{
		Fire,
		Lighting
	};
public:
	Chapter6Scene(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);
	~Chapter6Scene() {};
public:
	void initScene() override;
	void updateScene(float deltaTime) override;
	void drawScene() override;
	void setDirLight(XMFLOAT3 dir) override;



private:
	GameObject m_2dPlane;

private:
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pFireAnims; 
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_pLightingAnims;

	Chpat6State m_state = Fire;
};

