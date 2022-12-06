/***************************************************************************************
Author: lvke
Date:2022/12/05 21:36
Description:
Transform Component
****************************************************************************************/
#pragma once
#include "Interface/ComponentInterface.h"
#include "Runtime/Platform/Windows/Math/Transform.h"

namespace Twinkle
{
	class IBindable;
	class TransformComponent : public IComponent
	{
	public:
		TransformComponent();
		virtual ~TransformComponent();

		XMFLOAT3 getScale() const;
		void setScale(float x, float y, float z);
		void setScale(const XMFLOAT3& scale);
		XMFLOAT3 getRotation() const;
		void setRotation(float x, float y, float z);
		void setRotation(const XMFLOAT3& rotation);
		XMFLOAT3 getPosition() const;
		void setPosition(float x, float y, float z);
		void setPosition(const XMFLOAT3& position);

		virtual void tick(float deltaTime) override;
	private:
		void updateWorldMatrix();
	private:
		IBindable* m_worldMatrixCB{ nullptr };
		Transform m_transform;
	};
}