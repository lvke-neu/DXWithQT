#pragma once 
#include <DirectXMath.h>

using namespace DirectX;
class Transform
{
public:
	Transform() = default;
	Transform(XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 position);

	XMMATRIX getWVPMatrix();

	void move(const XMFLOAT3& direction, float distance);
	void moveZAxis(float distance);
	void moveXAxis(float distance);

public:
	XMFLOAT3& getScale() { return m_scale; }
	void setScale(XMFLOAT3 scale) { m_scale = scale; }
	XMFLOAT3& getRotation() { return m_rotation; }
	void setRotation(XMFLOAT3 rotation) { m_rotation = rotation; }
	XMFLOAT3& getPosition() { return m_position; }
	void setPosition(XMFLOAT3 position) { m_position = position; }
private:
	XMFLOAT3 m_scale;
	XMFLOAT3 m_rotation;
	XMFLOAT3 m_position;
};