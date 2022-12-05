/***************************************************************************************
Author: lvke
Date:2022/12/05 21:19
Description:
GameObject Interface
****************************************************************************************/
#pragma once
#include <string>

namespace Twinkle
{
	class IComponent;
	class IGameObject
	{
	public:
		IGameObject();
		virtual ~IGameObject() = default;

		virtual void tick(float deltaTime) = 0;
		std::string getGuid() const;
	private:
		std::string m_guid{ "" };
	};
}