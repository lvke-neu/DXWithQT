#include "SceneManager.h"
#include "../Core/base/Utility.h"

namespace LkEngine
{
	void SceneManager::init()
	{
		testComponent.initialize(m_pd3dDevice, m_pd3dImmediateContext);
		LOG_INFO("SceneManager initialization is complete");
	}

	void SceneManager::updateScene(float deltaTime)
	{
		testComponent.updateScene(deltaTime);
	}

	void SceneManager::drawScene()
	{
		testComponent.drawScene();
	}
}

