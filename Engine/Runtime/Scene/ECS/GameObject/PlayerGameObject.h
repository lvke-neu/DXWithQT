/***************************************************************************************
Author: lvke
Date:2022/12/05 21:33
Description:
Player GameObject
****************************************************************************************/
#pragma once
#include "Interface/GameObjectInterface.h"

namespace Twinkle
{
	class PlayerGameObject : public IGameObject
	{
	public:
		PlayerGameObject();
		virtual ~PlayerGameObject();

		virtual void tick(float deltaTime) override;
	private:
		IComponent* m_transformComponent{ nullptr };
		IComponent* m_meshComponent{ nullptr };
	};
}