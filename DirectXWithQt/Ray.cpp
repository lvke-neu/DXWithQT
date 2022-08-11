#include "Ray.h"

Ray::Ray(const XMFLOAT3& origin, const XMFLOAT3& dir):
	m_origin(origin)
{
	XMStoreFloat3(&m_dir, XMVector3Normalize(XMLoadFloat3(&dir)));
}

bool Ray::hit(const BoundingBox& AABB, float& distance)
{
	return AABB.Intersects(XMLoadFloat3(&m_origin), XMLoadFloat3(&m_dir), distance);
}

Ray Ray::ScreenToRay(Camera camera, float x, float y)
{
	
	
	D3D11_VIEWPORT viewport = camera.getViewPort();

	XMVECTOR scale = XMVectorSet(2.0f / viewport.Width, 2.0f / viewport.Height, 1.0f / (viewport.MaxDepth - viewport.MinDepth), 1.0f);
	XMVECTOR offset = XMVectorSet((-2.0f * viewport.TopLeftX) / (viewport.Width) - 1, 
		(2.0f * viewport.TopLeftY) / (viewport.Height) + 1, 
		(-viewport.MinDepth) / (viewport.MaxDepth-viewport.MinDepth), 0.0f);

	//NDC->proj space
	XMVECTOR screenPoint = XMVectorSet(x, y, 0.0f, 1.0f);
	screenPoint = XMVectorMultiplyAdd(screenPoint, scale, offset);
	

	//proj->world space
	XMMATRIX vpInverse = XMMatrixInverse(nullptr, XMMatrixMultiply(camera.getViewMatrix(), camera.getProjMatrix()));
	screenPoint = XMVector3TransformCoord(screenPoint, vpInverse);

	//Ray
	XMFLOAT3 dir;
	XMStoreFloat3(&dir, XMVector3Normalize(screenPoint - XMLoadFloat3(&camera.getPosition())));
	
	return Ray(camera.getPosition(), dir);
}