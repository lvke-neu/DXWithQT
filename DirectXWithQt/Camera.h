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
		XMFLOAT3 g_eyePoW;
		float pad;
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

		D3D11_BUFFER_DESC cbd;
		ZeroMemory(&cbd, sizeof(cbd));
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.ByteWidth = sizeof(ViewMatrix);
		m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pViewMatrixCB.GetAddressOf());
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

public:
	XMFLOAT3& getScale() { return m_transform.getScale(); }
	void setScale(float x, float y, float z)
	{
		m_transform.setScale(XMFLOAT3(x, y, z));
		changeViewMatrixCB();
	}

	XMFLOAT3& getRotation() { return m_transform.getRotation(); }
	void setRotation(float x, float y, float z)
	{
		m_transform.setRotation(XMFLOAT3(x, y, z));
		changeViewMatrixCB();
	}

	XMFLOAT3& getPosition() { return m_transform.getPosition(); }
	void setPosition(float x, float y, float z)
	{
		setPosition(XMFLOAT3(x, y, z));
	}
	void setPosition(const XMFLOAT3& pos)
	{
		m_transform.setPosition(pos);
		changeViewMatrixCB();
	}
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