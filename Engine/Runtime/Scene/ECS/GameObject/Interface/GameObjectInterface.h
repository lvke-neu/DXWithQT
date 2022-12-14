/***************************************************************************************
Author: lvke
Date:2022/12/05 21:19
Description:
GameObject Interface
****************************************************************************************/
#pragma once

#include "../../Component/TransformComponent.h"
#include "../../Component/MeshComponent.h"

namespace Twinkle
{
	class IGameObject
	{
	public:
		IGameObject();
		virtual ~IGameObject();

		virtual void tick(float deltaTime) = 0;
		TransformComponent* getTransformComponent() const;
		MeshComponent* getMeshComponent() const;
		std::string getGuid() const; 
	protected:
		std::string m_guid{ "" };

		TransformComponent* m_transformComponent{ nullptr };
		MeshComponent* m_meshComponent{ nullptr };
	};
}