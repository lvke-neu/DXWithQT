#include "SceneManager.h"


namespace LkEngine
{
	void SceneManager::initialize(Microsoft::WRL::ComPtr<ID3D11Device> pd3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> pd3dImmediateContext)
	{
		m_pd3dDevice = pd3dDevice;
		m_pd3dImmediateContext = pd3dImmediateContext;

		testComponent.initialize(m_pd3dDevice, pd3dImmediateContext);
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

