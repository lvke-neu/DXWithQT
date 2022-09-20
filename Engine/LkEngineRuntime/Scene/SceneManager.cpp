#include "SceneManager.h"
#include "../Core/base/Utility.h"
#include "Component/Common/RenderStates.h"
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

		m_pBoxComponent = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pBoxComponent->setVsShader("builtin\\Shader\\BoxComponentVS.cso");
		m_pBoxComponent->setPsShader("builtin\\Shader\\BoxComponentPS.cso");
		m_pBoxComponent->setTexture("builtin\\Texture\\WoodCrate.dds");
		m_pBoxComponent->setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 20.0f)
		));
		

		m_skyBoxComponent = new SkyBoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_skyBoxComponent->setVsShader("builtin\\Shader\\SkyBoxComponentVS.cso");
		m_skyBoxComponent->setPsShader("builtin\\Shader\\SkyBoxComponentPS.cso");
		m_skyBoxComponent->setTexture("builtin\\Texture\\SkyBox\\daylight.jpg");
		m_skyBoxComponent->setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));


		m_cameracontroller = new Cameracontroller;

		

		LOG_INFO("SceneManager initialization is complete");
	}
	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SET_NULL(m_pBoxComponent);
		SAFE_DELETE_SET_NULL(m_skyBoxComponent);
		SAFE_DELETE_SET_NULL(m_cameracontroller);
	}

	void SceneManager::updateScene(float deltaTime)
	{
		static float rot = 0.0f;
		rot += deltaTime;
		//pBoxComponent->setRotation(rot, 0.0f, 0.0f);
		//CameraManager::getInstance().setRotation(0.0f, rot, 0.0f);
	}

	void SceneManager::drawScene()
	{
		m_pBoxComponent->draw();

		m_skyBoxComponent->draw();
	}
}

