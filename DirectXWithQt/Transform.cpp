#include "Transform.h"

Transform::Transform(XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 position)
	: m_scale(scale), m_rotation(rotation), m_position(position)
{

}


XMMATRIX  Transform::getWVPMatrix()
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