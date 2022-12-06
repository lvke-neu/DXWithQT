#include "PerspectiveCamera.h"
#include "RenderSystem.h"

namespace Twinkle
{
	void PerspectiveCamera::Initialize()
	{
		m_viewMatrixCB = Singleton<RenderSystem>::GetInstance().CreateConstantBuffer<ViewMatrix>(1);
		m_projMatrixCB = Singleton<RenderSystem>::GetInstance().CreateConstantBuffer<ProjMatrix>(2);

		updateViewMatrix();
		updateProjMatrix();

		m_viewMatrixCB->bind();
		m_projMatrixCB->bind();
	}

	void PerspectiveCamera::SetPosition(float x, float y, float z)
	{
		m_transform.setPosition(x, y, z);
		updateViewMatrix();
	}

	void PerspectiveCamera::SetRotation(float x, float y, float z)
	{
		m_transform.setRotation(x, y, z);
		updateViewMatrix();
	}

	void PerspectiveCamera::SetFrustum(const Frustum & frustum)
	{
		m_frustum = frustum;
		updateProjMatrix();
	}

	void PerspectiveCamera::SetFrustum(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
	{
		m_frustum.FovAngleY = FovAngleY;
		m_frustum.AspectRatio = AspectRatio;
		m_frustum.NearZ = NearZ;
		m_frustum.FarZ = FarZ;
		updateProjMatrix();
	}

	void PerspectiveCamera::moveXAxis(float distance)
	{
		m_transform.moveXAxis(distance);
		updateViewMatrix();
	}

	void PerspectiveCamera::moveZAxis(float distance)
	{
		m_transform.moveZAxis(distance);
		updateViewMatrix();
	}

	XMMATRIX PerspectiveCamera::GetViewMatrix()
	{
		return XMMatrixInverse(nullptr, m_transform.getWorldMatrix());
	}

	XMMATRIX PerspectiveCamera::GetProjMatrix()
	{
		return XMMatrixPerspectiveFovLH(m_frustum.FovAngleY, m_frustum.AspectRatio, m_frustum.NearZ, m_frustum.FarZ);
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
		Singleton<RenderSystem>::GetInstance().Release(m_viewMatrixCB);
		Singleton<RenderSystem>::GetInstance().Release(m_projMatrixCB);
	}

	void PerspectiveCamera::updateViewMatrix()
	{
		ViewMatrix viewMatrix;
		viewMatrix.viewMatrix = XMMatrixTranspose(GetViewMatrix());

		dynamic_cast<ConstantBuffer<ViewMatrix>*>(m_viewMatrixCB)->update(viewMatrix);
	}

	void PerspectiveCamera::updateProjMatrix()
	{
		ProjMatrix projMatrix;
		projMatrix.projMatrix = XMMatrixTranspose(GetProjMatrix());

		dynamic_cast<ConstantBuffer<ProjMatrix>*>(m_projMatrixCB)->update(projMatrix);
	}
}