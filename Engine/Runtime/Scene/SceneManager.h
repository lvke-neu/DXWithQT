/***************************************************************************************
Author: lvke
Date:2022/12/03 16:17
Description:
Scene Manager
****************************************************************************************/
#pragma once

#include "Runtime/Interface/SingletonInterface.h"

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
		IGameObject* m_player{ nullptr };
	};
}
