/***************************************************************************************
Author: lvke
Date:2022/12/04 20:53
Description:
Component Interface
****************************************************************************************/
#pragma once

#include "Runtime/Platform/Windows/Math/Transform.h"

namespace Twinkle
{
	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;
	public:
		virtual void update(float deltaTime);
		virtual void draw();
	protected:
		Transform m_transform;
	};
}