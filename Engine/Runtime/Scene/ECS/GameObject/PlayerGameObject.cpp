#include "PlayerGameObject.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "Runtime/Utility/Utility.h"

namespace Twinkle
{
	PlayerGameObject::PlayerGameObject()
	{
		m_transformComponent = new TransformComponent;
		m_meshComponent = new MeshComponent;
	}

	PlayerGameObject::~PlayerGameObject()
	{
		SAFE_DELETE_SETNULL(m_transformComponent);
		SAFE_DELETE_SETNULL(m_meshComponent);
	}

	void PlayerGameObject::tick(float deltaTime)
	{
		m_transformComponent->tick(deltaTime);
		m_meshComponent->tick(deltaTime);
	}
}