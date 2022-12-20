/***************************************************************************************
Author: lvke
Date:2022/12/18 14:47
Description:
ImGui Manager
****************************************************************************************/
#pragma once
#include "Runtime/Interface/SingletonInterface.h"
#include <vector>

namespace Twinkle
{
	class IGameObject;
	class ImGuiManager
	{
		FRIEND_SINGLETON(ImGuiManager);
		PRIVATE_CONSTRUCTOR(ImGuiManager);
	public:
		void Initialize(void* hwnd);
		void Destroy();
		void Tick();
		__int64 WndProcHandler(void* hwnd, unsigned int msg, unsigned __int64 wParam, __int64 lParam);

		void setSceneGameObjects(const std::vector<IGameObject*>& sceneGameObjects);
	private:
		void showSceneGameObjects();
		void showSelectedGameObjectDetail();
		void showTransformComponent();
		void showMeshComponent();
	private:
		IGameObject* m_currentSelectedGo{ nullptr };
		std::vector<IGameObject*> m_sceneGameObjects;
	};
}