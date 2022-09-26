/***************************************************************************************
Author: lvke
Date:2022/9/18 23:39
Description:
 The Perspective Camera 
****************************************************************************************/

#pragma once 

#include <d3d11.h>
#include <wrl/client.h>

#include "../Common/Transform.h"
#include "../../../Core/base/ManagerInterface.h"
#include "../../../Core/base/SingletonInterface.h"
#include "../../../Core/Event/CameraChangedManager.h"

namespace LkEngine
{
	using namespace Microsoft::WRL;

	class CameraManager : public ISingleton<CameraManager>, public IManager
	{
	public:
		struct ViewMatrix
		{
			XMMATRIX g_view;
			XMFLOAT3 g_eyePoW;
			float pad;
		};

		struct ProjMatrix
		{
			XMMATRIX g_proj;
			XMFLOAT4 g_viewportSize;
		};
	public:
		virtual void init() override;
	public:
		XMMATRIX getViewMatrix();
		XMMATRIX getProjMatrix();
	public:
		void onViewMatrixChanged();
		void onProjMatrixChanged();
		void changeViewMatrixCB(const XMMATRIX& view);
	public:
		Transform getTransform() { return m_transform; }
		void setTransform(const Transform& transform) { m_transform = transform; onViewMatrixChanged(); }

		XMFLOAT3 getScale() { return m_transform.getScale(); }
		void setScale(float x, float y, float z) { setScale(XMFLOAT3(x, y, z)); }
		void setScale(const XMFLOAT3& scale) { m_transform.setScale(scale); onViewMatrixChanged(); }

		XMFLOAT3 getRotation() { return m_transform.getRotation(); }
		void setRotation(float x, float y, float z) { setRotation(XMFLOAT3(x, y, z)); }
		void setRotation(const XMFLOAT3& rot) { m_transform.setRotation(rot); onViewMatrixChanged(); }

		XMFLOAT3 getPosition() { return m_transform.getPosition(); }
		void setPosition(float x, float y, float z) { setPosition(XMFLOAT3(x, y, z)); }
		void setPosition(const XMFLOAT3& pos) { m_transform.setPosition(pos); onViewMatrixChanged(); }

		void getFrustum(float& FovAngleY, float& AspectRatio, float& NearZ, float& FarZ)
		{
			FovAngleY =  m_fovAngleY ;
			AspectRatio =  m_aspectRatio ;
			NearZ = m_nearZ;
			FarZ = m_farZ;
		}
		void setFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
		{
			m_fovAngleY = FovAngleY;
			m_aspectRatio = AspectRatio;
			m_nearZ = NearZ;
			m_farZ = FarZ;

			onProjMatrixChanged();

			CameraChangedManager::getInstance().onCameraFrustumChanged();
		}

		void setViewport(const D3D11_VIEWPORT& viewport) { m_ScreenViewport = viewport; }
		D3D11_VIEWPORT getViewport() { return m_ScreenViewport; }
	public:
		void moveZAxis(float distance) { m_transform.moveZAxis(distance); onViewMatrixChanged(); }
		void moveXAxis(float distance) { m_transform.moveXAxis(distance); onViewMatrixChanged(); }
		void rotXAxis(float angle) { m_transform.rotXAxis(angle); onViewMatrixChanged(); }
		void rotYAxis(float angel) { m_transform.rotYAxis(angel); onViewMatrixChanged(); }
	private:
		ComPtr<ID3D11Buffer> m_pViewMatrixCB;
		ComPtr<ID3D11Buffer> m_pProjMatrixCB;
	private:
		Transform m_transform;

		float m_fovAngleY;
		float m_aspectRatio;
		float m_nearZ;
		float m_farZ;

		D3D11_VIEWPORT m_ScreenViewport;

	};
}
