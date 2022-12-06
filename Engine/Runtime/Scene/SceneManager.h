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
	class CameraController;
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
		IGameObject* m_cube{ nullptr };
		IGameObject* m_plane{ nullptr };
		CameraController* m_cameraController{ nullptr };
	};
}
