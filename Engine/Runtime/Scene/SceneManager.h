/***************************************************************************************
Author: lvke
Date:2022/12/03 16:17
Description:
Scene Manager
****************************************************************************************/
#pragma once

#include "Runtime/Interface/SingletonInterface.h"
#include <vector>

namespace Twinkle
{
	class IGameObject;
	class SceneManager
	{
		FRIEND_SINGLETON(SceneManager);
	public:
		void Tick(float deltaTime);
	private:
		SceneManager();
		virtual ~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
	private:
		std::vector<IGameObject*> m_sceneGameObjects;
	};
}
