#include "Transform.h"

namespace Twinkle
{
	Transform::Transform(const XMFLOAT3 & scale, const XMFLOAT3 & rotation, const XMFLOAT3 & position)
	{
		m_scale = scale;
		m_rotation = rotation;
		m_position = position;
	}

	void Transform::moveXAxis(float distance)
	{
		XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

		XMVECTOR position = XMLoadFloat3(&m_position);
		XMVECTOR direction = rotationMatrix.r[0];
		position += direction * distance;

		XMStoreFloat3(&m_position, position);
	}

	void Transform::moveZAxis(float distance)
	{
		XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

		XMVECTOR position = XMLoadFloat3(&m_position);
		XMVECTOR direction = rotationMatrix.r[2];
		position += direction * distance;

		XMStoreFloat3(&m_position, position);
	}

	void Transform::rotateXY(float x, float y)
	{
		m_rotation.x -= x;
		m_rotation.y -= y;
	}

	XMMATRIX Transform::getWorldMatrix() const
	{
		return XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
			XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z) *
			XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	}

	XMFLOAT3 Transform::getScale() const
	{
		return m_scale;
	}

	void Transform::setScale(float x, float y, float z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;

	}

	void Transform::setScale(const XMFLOAT3 & scale)
	{
		m_scale = scale;
	}

	XMFLOAT3 Transform::getRotation() const
	{
		return m_rotation;
	}

	void Transform::setRotation(float x, float y, float z)
	{
		m_rotation.x = x;
		m_rotation.y = y;
		m_rotation.z = z;
	}

	void Transform::setRotation(const XMFLOAT3 & rotation)
	{
		m_rotation = rotation;
	}

	XMFLOAT3 Transform::getPosition() const
	{
		return m_position;
	}

	void Transform::setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	void Transform::setPosition(const XMFLOAT3 & position)
	{
		m_position = position;
	}

}
