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
	enum BasicGeometryType
	{
		Cube,
		Cylinder
	};

	class BasicGeometryGameObject : public IGameObject
	{
	public:
		BasicGeometryGameObject(BasicGeometryType geometryType);
		virtual ~BasicGeometryGameObject();

		virtual void tick(float deltaTime) override;
	public:
		IComponent* getTransformComponent();
		IComponent* getMeshComponent();
	private:
		IComponent* m_transformComponent{ nullptr };
		IComponent* m_meshComponent{ nullptr };
	};
}