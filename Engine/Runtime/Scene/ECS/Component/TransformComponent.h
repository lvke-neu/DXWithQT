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

		void setScale(float x, float y, float z);
		void setRotation(float x, float y, float z);
		void setPosition(float x, float y, float z);

		virtual void tick(float deltaTime) override;
	private:
		void updateWorldMatrix();
	private:
		IBindable* m_worldMatrixCB{ nullptr };
		Transform m_transform;
	};
}