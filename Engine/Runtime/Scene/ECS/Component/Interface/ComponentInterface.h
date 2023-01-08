/***************************************************************************************
Author: lvke
Date:2022/12/05 21:18
Description:
Component Interface
****************************************************************************************/
#pragma once

namespace Twinkle
{
	class IComponent
	{
	public:
		IComponent() = default;
		virtual ~IComponent() = default;

		virtual void tick(float deltaTime) = 0;
	};
}