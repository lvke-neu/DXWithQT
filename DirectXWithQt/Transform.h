#pragma once 
#include <DirectXMath.h>

/*
注意拷贝构造函数与 “=”的区别

调用拷贝构造函数:
	Transform a;
	Transform b = a;

调用重载的 “=” 号:
	Transform a;
	Transform b;
	a = b;

*/

using namespace DirectX;
class Transform
{
public:
	Transform() = default;
	Transform(XMFLOAT3 scale, XMFLOAT3 rotation, XMFLOAT3 position);
	Transform(const Transform& transform);
	Transform& operator=(const Transform& transform);

public:
	XMMATRIX getWorldMatrix();

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