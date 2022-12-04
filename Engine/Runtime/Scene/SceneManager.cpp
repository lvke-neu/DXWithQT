#include "SceneManager.h"
#include "Component/TestComponent.h"
#include "Runtime/Platform/Windows/DirectX11Manager.h"
#include "Runtime/Scene/Component/PerspectiveCamera.h"

namespace Twinkle
{
	SceneManager::SceneManager()
	{
		m_testComponent = new TestComponent;

		Singleton<PerspectiveCamera>::GetInstance().SetPosition(-2.0f, 0.0f, -10.0f);
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SETNULL(m_testComponent);
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