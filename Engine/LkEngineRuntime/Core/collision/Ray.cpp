#include "Ray.h"
#include "../../Scene/Component/Camera/CameraManager.h"
namespace LkEngine
{
	Ray::Ray(const XMFLOAT3& origin, const XMFLOAT3& dir) :
		m_origin(origin)
	{
		XMStoreFloat3(&m_dir, XMVector3Normalize(XMLoadFloat3(&dir)));
	}

	bool Ray::hit(const BoundingBox& AABB, float& distance)
	{

		return AABB.Intersects(XMLoadFloat3(&m_origin), XMLoadFloat3(&m_dir), distance);
	}

	bool Ray::hit(const BoundingOrientedBox& OBB, float& distance)
	{
		return OBB.Intersects(XMLoadFloat3(&m_origin), XMLoadFloat3(&m_dir), distance);
	}

	Ray Ray::ScreenToRay(float screenPtX, float screenPtY)
	{


		//D3D11_VIEWPORT viewport = camera.getViewPort();

		//XMVECTOR scale = XMVectorSet(2.0f / viewport.Width, 2.0f / viewport.Height, 1.0f / (viewport.MaxDepth - viewport.MinDepth), 1.0f);
		//XMVECTOR offset = XMVectorSet((-2.0f * viewport.TopLeftX) / (viewport.Width) - 1, 
		//	(2.0f * viewport.TopLeftY) / (viewport.Height) + 1, 
		//	(-viewport.MinDepth) / (viewport.MaxDepth-viewport.MinDepth), 0.0f);

		////NDC->proj space
		//XMVECTOR screenPoint = XMVectorSet(x, y, 0.0f, 1.0f);
		//screenPoint = XMVectorMultiplyAdd(screenPoint, scale, offset);
		//

		////proj->world space
		//XMMATRIX vpInverse = XMMatrixInverse(nullptr, XMMatrixMultiply(XMMatrixInverse(nullptr, camera.getViewMatrix()), camera.getProjMatrix()));
		//screenPoint = XMVector3TransformCoord(screenPoint, vpInverse);

		////Ray
		//XMFLOAT3 dir;
		//XMStoreFloat3(&dir, XMVector3Normalize(screenPoint - XMLoadFloat3(&camera.getPosition())));
		//
		//return Ray(camera.getPosition(), dir);


		static const XMVECTORF32 D = { { { -1.0f, 1.0f, 0.0f, 0.0f } } };
		XMVECTOR V = XMVectorSet(screenPtX, screenPtY, 0.0f, 1.0f);
		D3D11_VIEWPORT viewPort = CameraManager::getInstance().getViewport();

		XMVECTOR Scale = XMVectorSet(viewPort.Width * 0.5f, -viewPort.Height * 0.5f, viewPort.MaxDepth - viewPort.MinDepth, 1.0f);
		Scale = XMVectorReciprocal(Scale);

		XMVECTOR Offset = XMVectorSet(-viewPort.TopLeftX, -viewPort.TopLeftY, -viewPort.MinDepth, 0.0f);
		Offset = XMVectorMultiplyAdd(Scale, Offset, D.v);

		XMMATRIX Transform = XMMatrixMultiply(CameraManager::getInstance().getViewMatrix(), CameraManager::getInstance().getProjMatrix());
		Transform = XMMatrixInverse(nullptr, Transform);

		XMVECTOR Target = XMVectorMultiplyAdd(V, Scale, Offset);
		Target = XMVector3TransformCoord(Target, Transform);


		XMFLOAT3 direction;
		XMFLOAT3 camPos = CameraManager::getInstance().getPosition();
		XMStoreFloat3(&direction, XMVector3Normalize(Target - XMLoadFloat3(&camPos)));
		return Ray(CameraManager::getInstance().getPosition(), direction);
	}

	void Ray::ScreenPointToWorld(XMFLOAT3 & worldPoint, float screenPtX, float screenPtY)
	{
		static const XMVECTORF32 D = { { { -1.0f, 1.0f, 0.0f, 0.0f } } };
		XMVECTOR V = XMVectorSet(screenPtX, screenPtY, 0.0f, 1.0f);
		D3D11_VIEWPORT viewPort = CameraManager::getInstance().getViewport();

		XMVECTOR Scale = XMVectorSet(viewPort.Width * 0.5f, -viewPort.Height * 0.5f, viewPort.MaxDepth - viewPort.MinDepth, 1.0f);
		Scale = XMVectorReciprocal(Scale);

		XMVECTOR Offset = XMVectorSet(-viewPort.TopLeftX, -viewPort.TopLeftY, -viewPort.MinDepth, 0.0f);
		Offset = XMVectorMultiplyAdd(Scale, Offset, D.v);

		XMMATRIX Transform = XMMatrixMultiply(CameraManager::getInstance().getViewMatrix(), CameraManager::getInstance().getProjMatrix());
		Transform = XMMatrixInverse(nullptr, Transform);

		XMVECTOR Target = XMVectorMultiplyAdd(V, Scale, Offset);
		XMStoreFloat3(&worldPoint, XMVector3TransformCoord(Target, Transform));
	}
}
