#include "SceneManager.h"
#include "ECS/GameObject/BasicGeometryGameObject.h"
#include "Runtime/Utility/Utility.h"
#include "Runtime/Platform/Windows/PerspectiveCamera.h"

namespace Twinkle
{
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);

		m_basicGeometryGameObject = new BasicGeometryGameObject(Cube);
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SETNULL(m_basicGeometryGameObject);
	}

	void SceneManager::Tick(float deltaTime)
	{
		m_basicGeometryGameObject->tick(deltaTime);
	}
}