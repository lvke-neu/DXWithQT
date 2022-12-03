#include "SceneManager.h"


namespace Twinkle
{
	SceneManager::SceneManager()
	{
		m_pDevice = Singleton<Engine>::GetInstance().GetDevice();
		m_pDeviceContent = Singleton<Engine>::GetInstance().GetDeviceContent();

		m_testComponent = new TestComponent;
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::Update(float deltaTime)
	{

	}

	void SceneManager::Draw()
	{
		if (m_testComponent)
			m_testComponent->draw();

	}
}