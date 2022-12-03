/***************************************************************************************
Author: lvke
Date:2022/12/03 16:17
Description:
Scene Manager
****************************************************************************************/
#pragma once

#include "Component/TestComponent.h"

namespace Twinkle
{
	class TestComponent;
	class SceneManager
	{
		FRIEND_SINGLETON(SceneManager);
	public:
		void Update(float deltaTime);
		void Draw();
	private:
		SceneManager();
		virtual ~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
	private:
		ID3D11Device* m_pDevice{ nullptr };
		ID3D11DeviceContext* m_pDeviceContent{ nullptr };

		TestComponent* m_testComponent{ nullptr };
	};
}
