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
		Cylinder,
		Plane,
		Sphere
	};

	class BasicGeometryGameObject : public IGameObject
	{
	public:
		BasicGeometryGameObject() = default;
		BasicGeometryGameObject(BasicGeometryType geometryType);
		virtual ~BasicGeometryGameObject() = default;

		virtual void tick(float deltaTime) override;
		virtual std::string getType() override;
	};
}