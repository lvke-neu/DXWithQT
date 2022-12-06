#include "TransformComponent.h"
#include "Runtime/Platform/Windows/RenderSystem.h"

namespace Twinkle
{
	TransformComponent::TransformComponent()
	{
		m_worldMatrixCB = Singleton<RenderSystem>::GetInstance().CreateConstantBuffer<WorldMatrix>(0);
		updateWorldMatrix();
		m_worldMatrixCB->bind();
	}

	TransformComponent::~TransformComponent()
	{
		Singleton<RenderSystem>::GetInstance().Release(m_worldMatrixCB);
	}

	void TransformComponent::setScale(float x, float y, float z)
	{
		m_transform.setScale(x, y, z);
		updateWorldMatrix();
	}

	void TransformComponent::setRotation(float x, float y, float z)
	{
		m_transform.setRotation(x, y, z);
		updateWorldMatrix();
	}

	void TransformComponent::setPosition(float x, float y, float z)
	{
		m_transform.setPosition(x, y, z);
		updateWorldMatrix();
	}

	void TransformComponent::tick(float deltaTime)
	{

	}

	void TransformComponent::updateWorldMatrix()
	{
		WorldMatrix worldMatrix;
		worldMatrix.worldMatrix = XMMatrixTranspose(m_transform.getWorldMatrix());
		dynamic_cast<ConstantBuffer<WorldMatrix>*>(m_worldMatrixCB)->update(worldMatrix);
	}
}