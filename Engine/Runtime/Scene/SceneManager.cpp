#include "SceneManager.h"
#include "Component/TestComponent.h"

namespace Twinkle
{
	SceneManager::SceneManager()
	{
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