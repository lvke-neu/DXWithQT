#include "PerspectiveCamera.h"
#include "Runtime/Platform/Windows/Bindable/BindableManager.h"

namespace Twinkle
{
	void PerspectiveCamera::Initialize()
	{
		m_viewMatrixCB = Singleton<BindableManager>::GetInstance().CreateConstantBuffer<ViewMatrix>(1);
		m_projMatrixCB = Singleton<BindableManager>::GetInstance().CreateConstantBuffer<ProjMatrix>(2);

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
		Singleton<BindableManager>::GetInstance().Release(m_viewMatrixCB);
		Singleton<BindableManager>::GetInstance().Release(m_projMatrixCB);
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