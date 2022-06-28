/************************************************************************
Author: lvke
Date:2022/6/28 22:49
Description:
透视相机控制类，控制相机的操作。
************************************************************************/

#pragma once

#include "Transform.h"

class Camera
{

public:
	XMMATRIX getViewMatrix() { return m_transform.getWorldMatrix(); }
	XMMATRIX getProjMatrix() { return XMMatrixPerspectiveFovLH(m_fovAngleY, m_aspectRatio, m_nearZ, m_farZ); }
public:
	Transform& getTransform() { return m_transform; }
	void setTransform(Transform transform) { m_transform = transform; }
	void setFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
	{
		m_fovAngleY = FovAngleY;
		m_aspectRatio = AspectRatio;
		m_nearZ = NearZ;
		m_farZ = FarZ;
	}

private:
	Transform m_transform;

	float m_fovAngleY;
	float m_aspectRatio;
	float m_nearZ;
	float m_farZ;
	
};