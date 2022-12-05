#include "TransformComponent.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

namespace Twinkle
{
	TransformComponent::TransformComponent()
	{
		m_worldMatrixCB = Singleton<RenderSystem>::GetInstance().CreateConstantBuffer<WorldMatrix>(0);
		updateWorldMatrix();
	}

	TransformComponent::~TransformComponent()
	{
		Singleton<RenderSystem>::GetInstance().Release(m_worldMatrixCB);
	}

	void TransformComponent::tick(float deltaTime)
	{
		static float rotY = 0.0f;
		rotY += deltaTime;
		m_transform.setRotation(0.0f, rotY, 0.0f);
		updateWorldMatrix();
	}

	void TransformComponent::updateWorldMatrix()
	{
		WorldMatrix worldMatrix;
		worldMatrix.worldMatrix = m_transform.getWorldMatrix();
		dynamic_cast<ConstantBuffer<WorldMatrix>*>(m_worldMatrixCB)->update(worldMatrix);
		m_worldMatrixCB->bind();
	}
}