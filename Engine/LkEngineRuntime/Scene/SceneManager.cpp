#include "SceneManager.h"
#include "../Core/base/Utility.h"
#include "Component/Common/RenderStates.h"
#include "Component/BoxComponent.h"
#include "Component/Camera/CameraManager.h"

namespace LkEngine
{
	void SceneManager::init()
	{
		RenderStates::Init(m_pd3dDevice);

		CameraManager::getInstance().setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));

		pBoxComponent = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		pBoxComponent->setVsShader("builtin\\Shader\\BoxComponentVS.cso");
		pBoxComponent->setPsShader("builtin\\Shader\\BoxComponentPS.cso");
		pBoxComponent->setTexture("builtin\\Texture\\WoodCrate.dds");
		pBoxComponent->setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 20.0f)
		));
		pBoxComponent->bindPipeState();

		//m_pd3dImmediateContext->RSSetState(RenderStates::RSWireframe.Get());

		LOG_INFO("SceneManager initialization is complete");
	}
	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SET_NULL(pBoxComponent);
	}

	void SceneManager::updateScene(float deltaTime)
	{
		static float rot = 0.0f;
		rot += deltaTime;
		pBoxComponent->setRotation(rot, 0.0f, 0.0f);
		//CameraManager::getInstance().setRotation(0.0f, rot, 0.0f);
	}

	void SceneManager::drawScene()
	{
		pBoxComponent->draw();
	}
}

