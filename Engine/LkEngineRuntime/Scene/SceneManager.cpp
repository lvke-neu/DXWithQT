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

		//m_pBoxComponent = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		//m_pBoxComponent->setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		//m_pBoxComponent->setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		//m_pBoxComponent->setTexture("builtin\\Texture\\WoodCrate.dds");
		//m_pBoxComponent->setTransform(Transform(
		//	XMFLOAT3(1.0f, 1.0f, 1.0f),
		//	XMFLOAT3(0.0f, 0.0f, 0.0f),
		//	XMFLOAT3(0.0f, 0.0f, 20.0f)
		//));

		//m_pBoxComponent2 = new BoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		//m_pBoxComponent2->setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		//m_pBoxComponent2->setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		//m_pBoxComponent2->setTexture("builtin\\Texture\\WoodCrate.dds");
		//m_pBoxComponent2->setTransform(Transform(
		//	XMFLOAT3(1.0f, 1.0f, 1.0f),
		//	XMFLOAT3(0.0f, 0.0f, 0.0f),
		//	XMFLOAT3(3.0f, 0.0f, 20.0f)
		//));
		
		m_pPlaneComponent = new PlaneComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pPlaneComponent->setVsShader("builtin\\Shader\\BasicPrimitiveVS.cso");
		m_pPlaneComponent->setPsShader("builtin\\Shader\\BasicPrimitivePS.cso");
		m_pPlaneComponent->setTexture("builtin\\Texture\\floor.dds");
		m_pPlaneComponent->setTransform(Transform(
			XMFLOAT3(20.0f, 20.0f, 1.0f),
			XMFLOAT3(XM_PI / 2, 0.0f, 0.0f),
			XMFLOAT3(0.0f, -5.0f, 5.0f)
		));

		m_pSkyBoxComponent = new SkyBoxComponent(m_pd3dDevice, m_pd3dImmediateContext);
		m_pSkyBoxComponent->setVsShader("builtin\\Shader\\SkyBoxComponentVS.cso");
		m_pSkyBoxComponent->setPsShader("builtin\\Shader\\SkyBoxComponentPS.cso");
		m_pSkyBoxComponent->setTexture("builtin\\Texture\\SkyBox\\daylight.jpg");
		m_pSkyBoxComponent->setTransform(Transform(
			XMFLOAT3(1.0f, 1.0f, 1.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f),
			XMFLOAT3(0.0f, 0.0f, 0.0f)
		));


		m_pCameraController = new CameraController;

		LOG_INFO("SceneManager initialization is complete");
	}
	SceneManager::~SceneManager()
	{
		//SAFE_DELETE_SET_NULL(m_pBoxComponent);
		//SAFE_DELETE_SET_NULL(m_pBoxComponent2);
		SAFE_DELETE_SET_NULL(m_pPlaneComponent);
		SAFE_DELETE_SET_NULL(m_pSkyBoxComponent);
		
		SAFE_DELETE_SET_NULL(m_pCameraController);

	}

	void SceneManager::updateScene(float deltaTime)
	{
		static float rot = 0.0f;
		rot += deltaTime;
		//m_pBoxComponent->setRotation(rot, 0.0f, 0.0f);
		//CameraManager::getInstance().setRotation(0.0f, rot, 0.0f);
	}

	void SceneManager::drawScene()
	{
		//m_pBoxComponent->draw();
		//m_pBoxComponent2->draw();
		m_pPlaneComponent->draw();

		m_pSkyBoxComponent->draw();
	}

	std::string SceneManager::getSkyBoxTexture()
	{
		return m_pSkyBoxComponent->getTexture();
	}

	void SceneManager::setSkyBoxTexture(const std::string& skyBoxTexture)
	{
		m_pSkyBoxComponent->setTexture(skyBoxTexture);
	}

	void SceneManager::setWireFrame(bool b)
	{
		m_pd3dImmediateContext->RSSetState(b ? RenderStates::RSWireframe.Get() : RenderStates::RSNoCull.Get());
	}
}

