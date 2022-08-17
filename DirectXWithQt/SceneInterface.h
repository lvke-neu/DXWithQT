/************************************************************************
Author: lvke
Date:2022/7/2 9:41
Description:
场景接口类，每个章节的场景均继承自该类（基类包含了透视相机、整个场景的光）
************************************************************************/
#pragma once 


#include <wrl/client.h>
#include "Camera.h"
#include "Light.h"
#include "ListeningEvent.h"

template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

class IScene : public ListeningEvent
{
public:
	virtual ~IScene() = default;
public:
	virtual void initScene() = 0;
	virtual void updateScene(float deltaTime) = 0;
	virtual void drawScene() = 0;
	virtual void setDirLight(XMFLOAT3 dir) = 0;

	void onResize(float width, float height, const D3D11_VIEWPORT& viewPort);
public:
	XMFLOAT3 get_dirLight_dir() { return m_dirLight_dir; }
protected:
	void initCameraAndLight(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext);

protected:
	ComPtr<ID3D11Device> m_pd3dDevice{ nullptr };
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext{ nullptr };
	ComPtr<ID3D11Buffer> m_pLightCB{ nullptr };
	Camera m_perspectiveCamera;

	XMFLOAT3 m_dirLight_dir = XMFLOAT3(0.0f, 0.0f, 0.0f);

};