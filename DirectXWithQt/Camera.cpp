#include "Camera.h"
Transform& Camera::getTransform() 
{
	changeViewMatrixCB();

	return m_transform; 
}
void Camera::setTransform(Transform transform)
{
	m_transform = transform;

	changeViewMatrixCB();
}

void Camera::changeViewMatrixCB()
{
	ViewMatrix viewMatrix;
	viewMatrix.g_view = XMMatrixTranspose(getViewMatrix());
	viewMatrix.g_eyePoW = XMFLOAT3(m_transform.getPosition());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pViewMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(ViewMatrix), &viewMatrix, sizeof(ViewMatrix));
	m_pd3dImmediateContext->Unmap(m_pViewMatrixCB.Get(), 0);

	m_pd3dImmediateContext->VSSetConstantBuffers(1, 1, m_pViewMatrixCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pViewMatrixCB.GetAddressOf());
}

void Camera::changeViewMatrixCB(const XMMATRIX& view)
{
	ViewMatrix viewMatrix;
	viewMatrix.g_view = XMMatrixTranspose(view);
	viewMatrix.g_eyePoW = XMFLOAT3(m_transform.getPosition());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pViewMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(ViewMatrix), &viewMatrix, sizeof(ViewMatrix));
	m_pd3dImmediateContext->Unmap(m_pViewMatrixCB.Get(), 0);

	m_pd3dImmediateContext->VSSetConstantBuffers(1, 1, m_pViewMatrixCB.GetAddressOf());
	m_pd3dImmediateContext->PSSetConstantBuffers(1, 1, m_pViewMatrixCB.GetAddressOf());
}

void Camera::changeProjMatrixCB()
{
	ProjMatrix projMatrix;
	projMatrix.g_proj = XMMatrixTranspose(getProjMatrix());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	m_pd3dImmediateContext->Map(m_pProjMatrixCB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(ProjMatrix), &projMatrix, sizeof(ProjMatrix));
	m_pd3dImmediateContext->Unmap(m_pProjMatrixCB.Get(), 0);

	m_pd3dImmediateContext->VSSetConstantBuffers(2, 1, m_pProjMatrixCB.GetAddressOf());
}

void Camera::setFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
{
	m_fovAngleY = FovAngleY;
	m_aspectRatio = AspectRatio;
	m_nearZ = NearZ;
	m_farZ = FarZ;

	changeProjMatrixCB();
}

bool Camera::isNeedFrustumCulling(const BoundingBox& AABB)
{
	BoundingFrustum worldBoundingFrustum;
	BoundingFrustum viewBoundingFrustum;
	BoundingFrustum::CreateFromMatrix(viewBoundingFrustum, getProjMatrix());
	viewBoundingFrustum.Transform(worldBoundingFrustum, DirectX::XMMatrixInverse(nullptr, getViewMatrix()));


	return !worldBoundingFrustum.Intersects(AABB);
}