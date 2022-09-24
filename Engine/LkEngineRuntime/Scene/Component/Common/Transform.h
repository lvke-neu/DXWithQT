#pragma once 
#include <DirectXMath.h>
#include <string>

namespace LkEngine
{
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
		void rotXAxis(float angle);
		void rotYAxis(float angle);

		void lookTo(const XMFLOAT3& direction, const XMFLOAT3& up);
		XMFLOAT3 GetEulerAnglesFromRotationMatrix(const DirectX::XMFLOAT4X4& rotationMatrix);
		std::string to_string();
	public:
		XMFLOAT3 getScale() const { return m_scale; }
		void setScale(XMFLOAT3 scale) { m_scale = scale; }
		XMFLOAT3 getRotation() const { return m_rotation; }
		void setRotation(XMFLOAT3 rotation) { m_rotation = rotation; }
		XMFLOAT3 getPosition() const { return m_position; }
		void setPosition(XMFLOAT3 position) { m_position = position; }
	private:
		XMFLOAT3 m_scale;
		XMFLOAT3 m_rotation;
		XMFLOAT3 m_position;
	};
}
