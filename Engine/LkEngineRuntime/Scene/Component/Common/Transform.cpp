#include "Transform.h"

namespace LkEngine
{
	Transform::Transform(XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 position)
		: m_scale(scale), m_rotation(rotation), m_position(position)
	{

	}

	Transform::Transform(const Transform& transform)
		: m_scale(transform.m_scale), m_rotation(transform.m_rotation), m_position(transform.m_position)
	{

	}

	Transform& Transform::operator=(const Transform& transform)
	{
		if (this != &transform)
		{
			m_scale = transform.m_scale;
			m_rotation = transform.m_rotation;
			m_position = transform.m_position;
		}
		return *this;
	}

	XMMATRIX  Transform::getWorldMatrix()
	{
		return XMMatrixScalingFromVector(XMLoadFloat3(&m_scale)) *
			XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotation)) *
			XMMatrixTranslationFromVector(XMLoadFloat3(&m_position));
	}

	void Transform::move(const XMFLOAT3& direction, float distance)
	{
		XMVECTOR pos = XMLoadFloat3(&m_position);
		XMVECTOR dir = XMLoadFloat3(&direction);
		pos += dir * distance;

		XMStoreFloat3(&m_position, pos);
	}

	void Transform::moveZAxis(float distance)
	{
		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotation));

		XMVECTOR pos = XMLoadFloat3(&m_position);
		XMVECTOR dir = rotMatrix.r[2];
		pos += dir * distance;

		XMStoreFloat3(&m_position, pos);
	}

	void Transform::moveXAxis(float distance)
	{
		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotation));

		XMVECTOR pos = XMLoadFloat3(&m_position);
		XMVECTOR dir = rotMatrix.r[0];
		pos += dir * distance;

		XMStoreFloat3(&m_position, pos);
	}

	void Transform::rotXAxis(float angle)
	{
		m_rotation.x += angle;
	}

	void Transform::rotYAxis(float angle)
	{
		m_rotation.y += angle;
	}

	void Transform::lookTo(const XMFLOAT3& direction, const XMFLOAT3& up)
	{
		XMMATRIX View = XMMatrixLookToLH(XMLoadFloat3(&m_position), XMLoadFloat3(&direction), XMLoadFloat3(&up));
		XMMATRIX InvView = XMMatrixInverse(nullptr, View);
		XMFLOAT4X4 rotMatrix;
		XMStoreFloat4x4(&rotMatrix, InvView);
		m_rotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
	}

	XMFLOAT3 Transform::GetEulerAnglesFromRotationMatrix(const XMFLOAT4X4& rotationMatrix)
	{
		float c = sqrtf(1.0f - rotationMatrix(2, 1) * rotationMatrix(2, 1));

		if (isnan(c))
			c = 0.0f;

		XMFLOAT3 rotation;
		rotation.z = atan2f(rotationMatrix(0, 1), rotationMatrix(1, 1));
		rotation.x = atan2f(-rotationMatrix(2, 1), c);
		rotation.y = atan2f(rotationMatrix(2, 0), rotationMatrix(2, 2));

		return rotation;
	}

}
