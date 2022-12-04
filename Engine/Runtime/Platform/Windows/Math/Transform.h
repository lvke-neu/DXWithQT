/***************************************************************************************
Author: lvke
Date:2022/12/04 19:55
Description:
Transform : scale, ratation, position
****************************************************************************************/
#pragma once
#include <DirectXMath.h>

namespace Twinkle
{
	using namespace DirectX;

	struct WorldMatrix
	{
		XMMATRIX worldMatrix;
	};

	class Transform
	{
	public:
		Transform() = default;
		~Transform() = default;
		Transform(const XMFLOAT3& scale, const XMFLOAT3& rotation, const XMFLOAT3& position);
		Transform(const Transform&) = default;
		Transform& operator=(const Transform&) = default;
	public:
		void moveXAxis(float distance);
		void moveZAxis(float distance);
	public:
		XMMATRIX getWorldMatrix() const;

		XMFLOAT3 getScale() const;
		void setScale(float x, float y, float z);
		void setScale(const XMFLOAT3& scale);

		XMFLOAT3 getRotation() const;
		void setRotation(float x, float y, float z);
		void setRotation(const XMFLOAT3& rotation);

		XMFLOAT3 getPosition() const;
		void setPosition(float x, float y, float z);
		void setPosition(const XMFLOAT3& position);
	private:
		XMFLOAT3 m_scale{ 1.0f, 1.0f, 1.0f };
		XMFLOAT3 m_rotation{ 0.0f, 0.0f, 0.0f }; // radian
		XMFLOAT3 m_position{ 0.0f, 0.0f, 0.0f };
	};
}