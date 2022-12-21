/***************************************************************************************
Author: lvke
Date:2022/12/04 20:59
Description:
Perspective Camera:
	ViewMatrix is in slot 1
	ProjMatrix is in slot 2
****************************************************************************************/
#pragma once

#include "Math/Transform.h"
#include "Runtime/Interface/SingletonInterface.h"
#include <vector>

namespace Twinkle
{
	struct  Frustum
	{
		float FovAngleY = XM_PI / 3.0f;
		float AspectRatio = 1.7f;
		float NearZ = 1.0f;
		float FarZ = 1000.0f;
	};

	struct ViewMatrix
	{
		XMMATRIX viewMatrix;
	};

	struct ProjMatrix
	{
		XMMATRIX projMatrix;
	};

	class IBindable;
	class PerspectiveCamera
	{
		FRIEND_SINGLETON(PerspectiveCamera)
	public:
		void Initialize();

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetFrustum(const Frustum& frustum);
		void SetFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ);

		void moveXAxis(float distance);
		void moveZAxis(float distance);
		void rotateXY(float x, float y);

		const Transform& getTransform();
		void setTransform(const Transform& transform);
	public:
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();
	private:
		PerspectiveCamera() = default;
		virtual ~PerspectiveCamera();
		PerspectiveCamera(const PerspectiveCamera&) = delete;
		PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;

		void updateViewMatrix();
		void updateProjMatrix();
	private:
		Transform m_transform;
		Frustum m_frustum;
		IBindable* m_viewMatrixCB{ nullptr };
		IBindable* m_projMatrixCB{ nullptr };
	};
}