/************************************************************************
Author: lvke
Date:2022/6/28 22:49
Description:
透视相机控制类，控制相机的操作。
************************************************************************/

#pragma once

#include "Transform.h"
#include <d3d11.h>
#include <wrl/client.h>


template <class T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
class Camera
{
	struct ViewMatrix
	{
		XMMATRIX g_view;
	};

	struct ProjMatrix
	{
		XMMATRIX g_proj;
	};

public:
	void init(ComPtr<ID3D11Device> pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	{
		m_pd3dDevice = pd3dDevice;
		m_pd3dImmediateContext = pd3dImmediateContext;
	}


	XMMATRIX getViewMatrix() { return m_transform.getWorldMatrix(); }
	XMMATRIX getProjMatrix() { return XMMatrixPerspectiveFovLH(m_fovAngleY, m_aspectRatio, m_nearZ, m_farZ); }
public:
	Transform& getTransform();
	void setTransform(Transform transform);
	void setFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ);
	void moveZAxis(float distance) { m_transform.moveZAxis(distance); changeViewMatrixCB(); }
	void moveXAxis(float distance) { m_transform.moveXAxis(distance); changeViewMatrixCB(); }
	void changeViewMatrixCB();
private:
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pd3dImmediateContext;

	ComPtr<ID3D11Buffer> m_pViewMatrixCB;//常量buffer，存放视图矩阵，放在槽1

	ComPtr<ID3D11Buffer> m_pProjMatrixCB;//常量buffer，存放视图矩阵，放在槽2

private:
	Transform m_transform;
	float m_fovAngleY;
	float m_aspectRatio;
	float m_nearZ;
	float m_farZ;
	
};