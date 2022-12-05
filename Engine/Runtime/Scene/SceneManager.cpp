#include "SceneManager.h"
#include "PerspectiveCamera.h"
#include "ECS/GameObject/PlayerGameObject.h"
#include "Runtime/Utility/Utility.h"


namespace Twinkle
{
	SceneManager::SceneManager()
	{
		Singleton<PerspectiveCamera>::GetInstance().SetPosition(0.0f, 0.0f, -10.0f);

		m_player = new PlayerGameObject;
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SETNULL(m_player);
	}

	void SceneManager::Tick(float deltaTime)
	{
		m_player->tick(deltaTime);
	}
}