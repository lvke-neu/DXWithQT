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
		std::string getGuid() const;
		virtual std::string getType() = 0;

		TransformComponent* getTransformComponent() const;
		void setTransformComponent(TransformComponent* transformComponent);

		MeshComponent* getMeshComponent() const;
		void setMeshComponent(MeshComponent* meshComponent);
	protected:
		std::string m_guid{ "" };

		TransformComponent* m_transformComponent{ nullptr };
		MeshComponent* m_meshComponent{ nullptr };
	};
}