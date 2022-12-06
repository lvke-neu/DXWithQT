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

	XMFLOAT3 TransformComponent::getScale() const
	{
		return m_transform.getScale();
	}

	void TransformComponent::setScale(float x, float y, float z)
	{
		m_transform.setScale(x, y, z);
		updateWorldMatrix();
	}

	void TransformComponent::setScale(const XMFLOAT3& scale)
	{
		m_transform.setScale(scale);
		updateWorldMatrix();
	}

	XMFLOAT3 TransformComponent::getRotation() const
	{
		return m_transform.getRotation();
	}

	void TransformComponent::setRotation(float x, float y, float z)
	{
		m_transform.setRotation(x, y, z);
		updateWorldMatrix();
	}

	void TransformComponent::setRotation(const XMFLOAT3& rotation)
	{
		m_transform.setRotation(rotation);
		updateWorldMatrix();
	}

	XMFLOAT3 TransformComponent::getPosition() const
	{
		return m_transform.getPosition();
	}

	void TransformComponent::setPosition(float x, float y, float z)
	{
		m_transform.setPosition(x, y, z);
		updateWorldMatrix();
	}

	void TransformComponent::setPosition(const XMFLOAT3& position)
	{
		m_transform.setPosition(position);
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